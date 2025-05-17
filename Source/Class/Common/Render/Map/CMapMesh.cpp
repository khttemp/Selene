

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Class/Common/Render/Map/CMapModel.h"
#include "Class/Common/Render/Map/CMapMesh.h"
#include "Class/Common/Render/Map/CMapMaterial.h"
#include "Class/Common/Render/Map/CMapFrame.h"
#include "Class/Common/Render/3D/CLinePrimitive3D.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CVertexLayout.h"
#include "Class/Platform/Render/Shader/CShader.h"
#include "Class/Platform/Surface/CTexture.h"
#include "Collision/Collision.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;
using namespace Object;


//-----------------------------------------------------------------------------------
// PROTOTYPE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
	Bool Line_Triangle( const Math::Vector3D *pPtTbl[], const CPlane &Plane, const Math::Vector3D *pPlanePoints[], Math::Vector3D &vIntersect );
}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapMesh::CMapMesh( CRender *pRender, CRenderObjectMgr *pMgr ) : CRenderPrimitiveObject( pRender, pMgr )
	, m_pParentFrame		( NULL )
	, m_VertexFlag			( 0 )
	, m_pRenderTable		( NULL )
	, m_RenderTblCount		( 0 )
{
	SetName( "���b�V��" );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapMesh::~CMapMesh()
{
	SAFE_DELETE_ARRAY( m_pRenderTable );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMapMesh::SetCenter( Math::Vector3D &vCenter )
{
	m_vCenter = vCenter;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
const Collision::CBox &CMapMesh::GetOBB( void )
{
	return m_pParentFrame->GetOBB();
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMapMesh::SetParentFrame( CMapFrame *pFrame )
{
	m_pParentFrame = pFrame;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMapMesh::CreateRenderTable( Sint32 Count )
{
	m_pRenderTable = new SRenderTable [ Count ];
	m_RenderTblCount = Count;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMapMesh::SetRenderTable( Sint32 Index, SRenderTable &Tbl )
{
	m_pRenderTable[Index] = Tbl;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMapMesh::CreateVertex( eVertexElement Type, Sint32 Count )
{
	Sint32 Size;

	// �t���O�ǉ�
	m_VertexFlag |= Type;

	// �t���O���Ƀo�b�t�@����
	switch ( Type )
	{
	// �ʒu�{�F
	case VERTEX_ELEMENT_3DBASE:
		SAFE_RELEASE( m_pVB_Base );
		Size = m_pRender->GetSize( VERTEX_ELEMENT_3DBASE );
		m_pVB_Base = m_pRender->CreateVertexBuffer( Count, Size, false );
		break;
	// �e�N�X�`���t�u���Q
	case VERTEX_ELEMENT_3DTEXTURE:
		SAFE_RELEASE( m_pVB_Tex );
		Size = m_pRender->GetSize( VERTEX_ELEMENT_3DTEXTURE );
		m_pVB_Tex = m_pRender->CreateVertexBuffer( Count, Size, false );
		break;
	// �@��
	case VERTEX_ELEMENT_3DLIGHT:
		SAFE_RELEASE( m_pVB_Light );
		Size = m_pRender->GetSize( VERTEX_ELEMENT_3DLIGHT );
		m_pVB_Light = m_pRender->CreateVertexBuffer( Count, Size, false );
		break;
	// �ڐ�
	case VERTEX_ELEMENT_3DBUMP:
		SAFE_RELEASE( m_pVB_Bump );
		Size = m_pRender->GetSize( VERTEX_ELEMENT_3DBUMP );
		m_pVB_Bump = m_pRender->CreateVertexBuffer( Count, Size, false );
		break;
	// �E�F�C�g�{�C���f�b�N�X
	case VERTEX_ELEMENT_3DANIMATION:
		SAFE_RELEASE( m_pVB_Animation );
		Size = m_pRender->GetSize( VERTEX_ELEMENT_3DANIMATION );
		m_pVB_Animation = m_pRender->CreateVertexBuffer( Count, Size, false );
		break;
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMapMesh::CreateIndex( Sint32 Count )
{
	m_pIB = m_pRender->CreateIndexBuffer( Count, false );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMapMesh::LockVertex( eVertexElement Type )
{
	switch ( Type )
	{
	// �ʒu�{�F
	case VERTEX_ELEMENT_3DBASE:
		m_pVB_Base->Lock();
		break;
	// �e�N�X�`���t�u���Q
	case VERTEX_ELEMENT_3DTEXTURE:
		m_pVB_Tex->Lock();
		break;
	// �@��
	case VERTEX_ELEMENT_3DLIGHT:
		m_pVB_Light->Lock();
		break;
	// �ڐ�
	case VERTEX_ELEMENT_3DBUMP:
		m_pVB_Bump->Lock();
		break;
	// �E�F�C�g�{�C���f�b�N�X
	case VERTEX_ELEMENT_3DANIMATION:
		m_pVB_Animation->Lock();
		break;
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMapMesh::UnLockVertex( eVertexElement Type )
{
	switch ( Type )
	{
	// �ʒu�{�F
	case VERTEX_ELEMENT_3DBASE:
		m_pVB_Base->UnLock();
		break;
	// �e�N�X�`���t�u���Q
	case VERTEX_ELEMENT_3DTEXTURE:
		m_pVB_Tex->UnLock();
		break;
	// �@��
	case VERTEX_ELEMENT_3DLIGHT:
		m_pVB_Light->UnLock();
		break;
	// �ڐ�
	case VERTEX_ELEMENT_3DBUMP:
		m_pVB_Bump->UnLock();
		break;
	// �E�F�C�g�{�C���f�b�N�X
	case VERTEX_ELEMENT_3DANIMATION:
		m_pVB_Animation->UnLock();
		break;
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMapMesh::LockIndex( void )
{
	m_pIB->Lock();
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMapMesh::UnLockIndex( void )
{
	m_pIB->UnLock();
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMapMesh::UpdateStream( void )
{
	Sint32 Flag = m_VertexFlag;

	// �K�{�f�[�^��������ĂȂ��Ƃ��̓o���vOFF
	if ( (m_pVB_Bump == NULL) || (m_pVB_Light == NULL) || (m_pVB_Tex == NULL) )
	{
		Flag &= ~VERTEX_ELEMENT_3DBUMP;
	}

	// �X�g���[���Đ���
	SAFE_RELEASE( m_pVS );
	m_pVS = m_pRender->CreateVertexStream( Flag );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMapMesh::Push( const void *pIndex, Sint32 IndexCount )
{
	if ( m_pIB == NULL ) return false;
	if ( !m_pIB->Push( pIndex, IndexCount ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMapMesh::Push( const SVertex3DBase *pVtx, Sint32 Count )
{
	if ( m_pVB_Base == NULL ) return false;
	if ( !m_pVB_Base->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMapMesh::Push( const SVertex3DTexture *pVtx, Sint32 Count )
{
	if ( m_pVB_Tex == NULL ) return false;
	if ( !m_pVB_Tex->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMapMesh::Push( const SVertex3DLight *pVtx, Sint32 Count )
{
	if ( m_pVB_Light == NULL ) return false;
	if ( !m_pVB_Light->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMapMesh::Push( const SVertex3DBump *pVtx, Sint32 Count )
{
	if ( m_pVB_Bump == NULL ) return false;
	if ( !m_pVB_Bump->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMapMesh::CreateRenderActor( Scene::CMapActorObject *pActor )
{
	Sint32 MaterialCnt = m_RenderTblCount;

	Bool IsParallax = false;
	Bool IsSpecular = false;
	Bool IsEnvironment = false;

	//------------------------------------------------------------
	// ���b�V���f�[�^
	//------------------------------------------------------------
	pActor->SetStream( m_pIB, m_pVS, m_pVB_Base, m_pVB_Tex, m_pVB_Light, m_pVB_Bump, m_pVB_Animation );

	//------------------------------------------------------------
	// ���S�ʒu
	//------------------------------------------------------------
	pActor->SetCenter( m_vCenter );

	//------------------------------------------------------------
	// �}�e���A��
	//------------------------------------------------------------
	pActor->SetMateriaCount( MaterialCnt );
	CMapModel *pModel = (CMapModel*)GetParent();
	for ( Sint32 i = 0; i < MaterialCnt ; i++ )
	{
		CMapMaterial *pMtrl = pModel->GetMaterialPointer( m_pRenderTable[i].MaterialId );
		Scene::CSceneActorMaterial &Mtrl = pActor->GetSceneRenderMaterial( i );

		// �e�N�X�`��
		for ( Sint32 j = 0; j < MATERIAL_TEXTURE_MAX; j++ )
		{
			Mtrl.SetTexture( (eTextureStage)j, pMtrl->GetTexturePointer( j ) );
		}

		// �X�e�[�g
		Mtrl.SetDrawType( pMtrl->GetDrawType() );
		Mtrl.SetCullType( pMtrl->GetCullType() );
		Mtrl.SetAlphaBoundary( pMtrl->GetAlphaBoundary() );
		Mtrl.SetAlphaTestEnable( pMtrl->GetAlphaTestEnable() );
		Mtrl.SetZTestEnable( pMtrl->GetDepthTestEnable() );
		Mtrl.SetZWriteEnable( pMtrl->GetDepthWriteEnable() );

		// �p�����[�^�[
		Mtrl.SetDiffuseColor( pMtrl->GetDiffuseColor() );
		Mtrl.SetEmissiveColor( pMtrl->GetEmissiveColor() );
		Mtrl.SetSpecularColor( pMtrl->GetSpecularColor() );
		Mtrl.SetSpecularRefractive( pMtrl->GetSpecularRefractive() );
		Mtrl.SetSpecularRoughly( pMtrl->GetSpecularRoughly() );
		Mtrl.SetParallaxDepth( pMtrl->GetParallaxDepth() );

		// �V�F�[�_�[
		Mtrl.SetBumpType( pMtrl->GetBumpmapMode() );
		Mtrl.SetSpecularType( pMtrl->GetSpecularType() );

		// �v���~�e�B�u
		Mtrl.SetVertexStart( m_pRenderTable[i].VertexStart );
		Mtrl.SetVertexCount( m_pRenderTable[i].VertexCount );
		Mtrl.SetIndexStart( m_pRenderTable[i].PolygonStart * 3 );
		Mtrl.SetIndexCount( m_pRenderTable[i].PolygonCount * 3 );

		// �t���O
		if ( pMtrl->GetBumpmapMode()  != BUMP_TYPE_NONE ) IsParallax = true;
		if ( pMtrl->GetSpecularType() != SPECULAR_TYPE_NONE ) IsSpecular = true;
		if ( pMtrl->GetTexturePointer( TEXTURE_STAGE_ENVIRONMENT ) != NULL ) IsEnvironment = true;
	}

	// �o���v�ƃX�y�L�����̗L����ݒ�
	pActor->SetParallaxEnable( IsParallax );
	pActor->SetSpecularEnable( IsSpecular );
	pActor->SetEnvironmentEnable( IsEnvironment );
}

