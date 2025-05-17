

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Class/Common/Scene/CSceneInstanceModelControllerObject.h"
#include "Class/Common/Render/Model/CMesh.h"
#include "Class/Common/Render/Model/CMaterial.h"
#include "Class/Common/Render/Model/CFrame.h"
#include "Class/Common/Render/3D/CLinePrimitive3D.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CVertexLayout.h"
#include "Class/Platform/Surface/CTexture.h"
#include "Collision/Box.h"


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
CMesh::CMesh( CRender *pRender, CRenderObjectMgr *pMgr ) : CRenderPrimitiveObject( pRender, pMgr )
	, m_pParentFrame			( NULL )
	, m_MaterialCount			( 0 )
	, m_pMaterials				( NULL )
	, m_BoneCount				( 0 )
	, m_VertexFlag				( 0 )
	, m_ppBoneFramePointer		( NULL )
	, m_pCollision				( new CCollision )
{
	SetName( "���b�V��" );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMesh::~CMesh()
{
	SAFE_DELETE( m_pCollision );
	SAFE_DELETE_ARRAY( m_pMaterials );
	SAFE_DELETE_ARRAY( m_ppBoneFramePointer );

	Log_TableBegin();
	Log_PrintCellTitle( 0xFF0000, "���" );
	Log_PrintCellKind( "���b�V��" );
	Log_CellBegin( 0 );
	Log_Print( 0x000000, m_Name );

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::SetParentFrame( CFrame *pFrame )
{
	m_pParentFrame = pFrame;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::SetBoneCount( Sint32 Count )
{
	m_BoneCount = Count;
	m_ppBoneFramePointer = new CFrame * [ Count ];
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::SetBoneData( Sint32 Index, CFrame *pFrame )
{
	m_ppBoneFramePointer[Index] = pFrame;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::SetBounding( Collision::CBox &Box )
{
	for ( Sint32 i = 0; i < 8; i++ )
	{
		m_vCullBoxPoints[i] = Box.Points[i];
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::CreateMaterialList( Sint32 MaterialCount )
{
	m_MaterialCount = MaterialCount;
	m_pMaterials = new CMaterial [ MaterialCount ];
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::CreateVertex( eVertexElement Type, Sint32 Count )
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
void CMesh::CreateIndex( Sint32 Count )
{
	m_pIB = m_pRender->CreateIndexBuffer( Count, false );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::LockVertex( eVertexElement Type )
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
void CMesh::UnLockVertex( eVertexElement Type )
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
void CMesh::LockIndex( void )
{
	m_pIB->Lock();
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::UnLockIndex( void )
{
	m_pIB->UnLock();
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::UpdateStream( void )
{
	Sint32 Flag = m_VertexFlag;

	// �ꉞ�f�[�^�`�F�b�N
	if ( m_pVB_Animation == NULL )
	{
		Flag &= ~VERTEX_ELEMENT_3DANIMATION;
	}
	if ( m_pVB_Bump == NULL )
	{
		Flag &= ~VERTEX_ELEMENT_3DBUMP;
	}
	if ( m_pVB_Light == NULL )
	{
		Flag &= ~(VERTEX_ELEMENT_3DLIGHT | VERTEX_ELEMENT_3DBUMP);
	}
	if ( m_pVB_Tex == NULL )
	{
		Flag &= ~(VERTEX_ELEMENT_3DTEXTURE | VERTEX_ELEMENT_3DBUMP);
	}

	// �X�g���[���Đ���
	SAFE_RELEASE( m_pVS );
	m_pVS = m_pRender->CreateVertexStream( Flag );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMesh::Push( const void *pIndex, Sint32 IndexCount )
{
	if ( m_pIB == NULL ) return false;
	if ( !m_pIB->Push( pIndex, IndexCount ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMesh::Push( const SVertex3DBase *pVtx, Sint32 Count )
{
	if ( m_pVB_Base == NULL ) return false;
	if ( !m_pVB_Base->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMesh::Push( const SVertex3DTexture *pVtx, Sint32 Count )
{
	if ( m_pVB_Tex == NULL ) return false;
	if ( !m_pVB_Tex->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMesh::Push( const SVertex3DLight *pVtx, Sint32 Count )
{
	if ( m_pVB_Light == NULL ) return false;
	if ( !m_pVB_Light->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMesh::Push( const SVertex3DBump *pVtx, Sint32 Count )
{
	if ( m_pVB_Bump == NULL ) return false;
	if ( !m_pVB_Bump->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMesh::Push( const SVertex3DAnimation *pVtx, Sint32 Count )
{
	if ( m_pVB_Animation == NULL ) return false;
	if ( !m_pVB_Animation->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMesh::GetSupportTexture( void )
{
	return m_pVB_Tex != NULL;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMesh::GetSupportLight( void )
{
	return m_pVB_Light!= NULL;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CMesh::GetSupportBump( void )
{
	return m_pVB_Bump != NULL;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::CreateRenderActor( Scene::CModelActorObject *pActor )
{
	Bool IsParallax = false;
	Bool IsSpecular = false;
	Bool IsEnvironment = false;

	//------------------------------------------------------------
	// ���b�V���ւ̎Q��
	//------------------------------------------------------------
	pActor->SetMeshPointer( this );

	//------------------------------------------------------------
	// ���b�V���f�[�^
	//------------------------------------------------------------
	pActor->SetStream( m_pIB, m_pVS, m_pVB_Base, m_pVB_Tex, m_pVB_Light, m_pVB_Bump, m_pVB_Animation );

	//------------------------------------------------------------
	// ���S�ʒu
	//------------------------------------------------------------
	pActor->SetCenter( m_vCenter );

	//------------------------------------------------------------
	// �{�[��
	//------------------------------------------------------------
	pActor->SetBoneCount( m_BoneCount, m_ppBoneFramePointer );
	pActor->SetParentFrame( m_pParentFrame );

	//------------------------------------------------------------
	// �o�E���f�B���O
	//------------------------------------------------------------
	pActor->SetCullBoxPoints( m_vCullBoxPoints );

	//------------------------------------------------------------
	// �}�e���A��
	//------------------------------------------------------------
	pActor->SetMateriaCount( m_MaterialCount );
	for ( Sint32 i = 0; i < m_MaterialCount; i++ )
	{
		Scene::CSceneActorMaterial &Mtrl = pActor->GetSceneRenderMaterial( i );

		// �e�N�X�`��
		for ( Sint32 j = 0; j < MATERIAL_TEXTURE_MAX; j++ )
		{
			Mtrl.SetTexture( (eTextureStage)j, m_pMaterials[i].GetTexturePointer( (eTextureStage)j ) );
		}

		// �X�e�[�g
		Mtrl.SetDrawType( m_pMaterials[i].GetDrawType() );
		Mtrl.SetCullType( m_pMaterials[i].GetCullType() );
		Mtrl.SetAlphaBoundary( m_pMaterials[i].GetAlphaBoundary() );
		Mtrl.SetAlphaTestEnable( m_pMaterials[i].GetAlphaTestEnable() );
		Mtrl.SetZTestEnable( m_pMaterials[i].GetDepthTestEnable() );
		Mtrl.SetZWriteEnable( m_pMaterials[i].GetDepthWriteEnable() );
		Mtrl.SetLightEnable( m_pMaterials[i].GetLightEnable() );

		// �p�����[�^�[
		Mtrl.SetDiffuseColor( m_pMaterials[i].GetDiffuseColor() );
		Mtrl.SetEmissiveColor( m_pMaterials[i].GetEmissiveColor() );
		Mtrl.SetSpecularColor( m_pMaterials[i].GetSpecularColor() );
		Mtrl.SetSpecularRefractive( m_pMaterials[i].GetSpecularRefractive() );
		Mtrl.SetSpecularRoughly( m_pMaterials[i].GetSpecularRoughly() );
		Mtrl.SetParallaxDepth( m_pMaterials[i].GetParallaxDepth() );

		// �V�F�[�_�[
		Mtrl.SetBumpType( m_pMaterials[i].GetBumpmapMode() );
		Mtrl.SetSpecularType( m_pMaterials[i].GetSpecularType() );

		// �v���~�e�B�u
		Mtrl.SetVertexStart( m_pMaterials[i].GetVertexStart() );
		Mtrl.SetVertexCount( m_pMaterials[i].GetVertexCount() );
		Mtrl.SetIndexStart( m_pMaterials[i].GetIndexStart() );
		Mtrl.SetIndexCount( m_pMaterials[i].GetIndexCount() );

		// �t���O
		if ( m_pMaterials[i].GetBumpmapMode()  != BUMP_TYPE_NONE ) IsParallax = true;
		if ( m_pMaterials[i].GetSpecularType() != SPECULAR_TYPE_NONE ) IsSpecular = true;
		if ( m_pMaterials[i].GetTexturePointer( TEXTURE_STAGE_ENVIRONMENT ) != NULL ) IsEnvironment = true;
	}

	// �o���v�ƃX�y�L�����̗L����ݒ�
	pActor->SetParallaxEnable( IsParallax );
	pActor->SetSpecularEnable( IsSpecular );
	pActor->SetEnvironmentEnable( IsEnvironment );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::CreateRenderActor( Scene::CSceneInstanceModelActorObject *pActor, Sint32 InstanceCount )
{
	Bool IsParallax = false;
	Bool IsSpecular = false;
	Bool IsEnvironment = false;

	//------------------------------------------------------------
	// �{�[��
	//------------------------------------------------------------
	Sint32 ControllerCount = pActor->GetControllerCount();
	for ( Sint32 i = 0; i < ControllerCount; i++ )
	{
		pActor->GetControllerObject( i )->SetBoneCount( m_BoneCount, m_ppBoneFramePointer );
		pActor->GetControllerObject( i )->SetParentFrame( m_pParentFrame );
	}

	//------------------------------------------------------------
	// ���b�V���f�[�^
	//------------------------------------------------------------
	pActor->SetStream( m_pIB, m_pVS, m_pVB_Base, m_pVB_Tex, m_pVB_Light, m_pVB_Bump, m_pVB_Animation );
	// �C���X�^���X�p
	pActor->CreateMaterialVertex( m_MaterialCount );

	//------------------------------------------------------------
	// �C���X�^���X��
	//------------------------------------------------------------
	pActor->SetInstanceMaxCount( InstanceCount );

	//------------------------------------------------------------
	// �}�e���A��
	//------------------------------------------------------------
	pActor->SetMateriaCount( m_MaterialCount );
	for ( Sint32 i = 0; i < m_MaterialCount; i++ )
	{
		Scene::CSceneActorMaterial &Mtrl = pActor->GetSceneRenderMaterial( i );

		Sint32 VertexStart = m_pMaterials[i].GetVertexStart();
		Sint32 VertexCount = m_pMaterials[i].GetVertexCount();
		Sint32 IndexStart  = m_pMaterials[i].GetIndexStart();
		Sint32 IndexCount  = m_pMaterials[i].GetIndexCount();

		// �e�N�X�`��
		for ( Sint32 j = 0; j < MATERIAL_TEXTURE_MAX; j++ )
		{
			Mtrl.SetTexture( (eTextureStage)j, m_pMaterials[i].GetTexturePointer( (eTextureStage)j ) );
		}

		// �X�e�[�g
		Mtrl.SetDrawType( m_pMaterials[i].GetDrawType() );
		Mtrl.SetCullType( m_pMaterials[i].GetCullType() );
		Mtrl.SetAlphaBoundary( m_pMaterials[i].GetAlphaBoundary() );
		Mtrl.SetAlphaTestEnable( m_pMaterials[i].GetAlphaTestEnable() );
		Mtrl.SetZTestEnable( m_pMaterials[i].GetDepthTestEnable() );
		Mtrl.SetZWriteEnable( m_pMaterials[i].GetDepthWriteEnable() );
		Mtrl.SetLightEnable( m_pMaterials[i].GetLightEnable() );

		// �p�����[�^�[
		Mtrl.SetDiffuseColor( m_pMaterials[i].GetDiffuseColor() );
		Mtrl.SetEmissiveColor( m_pMaterials[i].GetEmissiveColor() );
		Mtrl.SetSpecularColor( m_pMaterials[i].GetSpecularColor() );
		Mtrl.SetSpecularRefractive( m_pMaterials[i].GetSpecularRefractive() );
		Mtrl.SetSpecularRoughly( m_pMaterials[i].GetSpecularRoughly() );
		Mtrl.SetParallaxDepth( m_pMaterials[i].GetParallaxDepth() );

		// �V�F�[�_�[
		Mtrl.SetBumpType( m_pMaterials[i].GetBumpmapMode() );
		Mtrl.SetSpecularType( m_pMaterials[i].GetSpecularType() );

		// �v���~�e�B�u
		Mtrl.SetVertexStart( VertexStart );
		Mtrl.SetVertexCount( VertexCount );
		Mtrl.SetIndexStart( IndexStart );
		Mtrl.SetIndexCount( IndexCount );

		// �t���O
		if ( m_pMaterials[i].GetBumpmapMode()  != BUMP_TYPE_NONE ) IsParallax = true;
		if ( m_pMaterials[i].GetSpecularType() != SPECULAR_TYPE_NONE ) IsSpecular = true;
		if ( m_pMaterials[i].GetTexturePointer( TEXTURE_STAGE_ENVIRONMENT ) != NULL ) IsEnvironment = true;

		// �C���X�^���X�f�[�^
		CVertexBuffer *pVB_Base = NULL, *pVB_Tex = NULL, *pVB_Light = NULL, *pVB_Bump = NULL;
		CIndexBuffer *pIB = NULL;

		// �o�b�t�@����
		pIB = m_pRender->CreateIndexBuffer( IndexCount * InstanceCount, false );
		if ( m_pVB_Base  != NULL ) pVB_Base  = m_pRender->CreateVertexBuffer( VertexCount * InstanceCount, m_pRender->GetSize( VERTEX_ELEMENT_3DBASE ),    true );
		if ( m_pVB_Tex   != NULL ) pVB_Tex   = m_pRender->CreateVertexBuffer( VertexCount * InstanceCount, m_pRender->GetSize( VERTEX_ELEMENT_3DTEXTURE ), false );
		if ( m_pVB_Light != NULL ) pVB_Light = m_pRender->CreateVertexBuffer( VertexCount * InstanceCount, m_pRender->GetSize( VERTEX_ELEMENT_3DLIGHT ),   true );
		if ( m_pVB_Bump  != NULL ) pVB_Bump  = m_pRender->CreateVertexBuffer( VertexCount * InstanceCount, m_pRender->GetSize( VERTEX_ELEMENT_3DBUMP ),    true );

		// ���_�̌��f�[�^��ݒ�
		pActor->SetMaterialData( i, pVB_Base, pVB_Light, pVB_Bump, pVB_Tex, pIB );

		// �C���f�b�N�X�o�b�t�@�̕ύX�͖����̂ōŏ��ɑS������Ă���
		pIB->Lock();
		for ( Sint32 j = 0; j < InstanceCount; j++ )
		{
			pIB->Add( m_pIB, IndexStart, IndexCount, (VertexCount * j) - VertexStart );
		}
		pIB->UnLock();

		// �e�N�X�`���͕ύX���Ȃ��̂Ŏ��O�ɍ��
		if ( m_pVB_Tex != NULL )
		{
			Renderer::SVertex3DTexture *pSrcT = (Renderer::SVertex3DTexture*)m_pVB_Tex->GetBufferAddress( 0 );

			pVB_Tex->Lock();

			for ( Sint32 j = 0; j < InstanceCount; j++ )
			{
				Renderer::SVertex3DTexture *pDstT = (Renderer::SVertex3DTexture*)pVB_Tex->GetBufferPointer( VertexCount );

				Sint32 Offset = 0;

				for ( Sint32 k = VertexStart; k < VertexStart + VertexCount; k++ )
				{
					pDstT[Offset].TexColor = pSrcT[k].TexColor;
					pDstT[Offset].TexLight = pSrcT[k].TexLight;
					Offset++;
				}
			}

			pVB_Tex->UnLock();
		}
	}

	// �o���v�ƃX�y�L�����̗L����ݒ�
	pActor->SetParallaxEnable( IsParallax );
	pActor->SetSpecularEnable( IsSpecular );
	pActor->SetEnvironmentEnable( IsEnvironment );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::CreateCollisionAttribute( SCollisionAttribute *pAttr, Sint32 Count )
{
	m_pCollision->CreateCollisionAttribute( pAttr, Count );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::CreateCollisionFace( SCollisionFace *pFace, Sint32 Count )
{
	m_pCollision->CreateCollisionFace( pFace, Count );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CMesh::CreateCollisionVertex( SCollisionVertex *pVtx, Sint32 Count )
{
	m_pCollision->CreateCollisionVertex( pVtx, Count );

	Collision::CBox Box;
	Box.Transform( m_vCullBoxPoints, Math::Matrix::GetIdentity() );
	m_pCollision->SetBounding( Box );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCollision *CMesh::GetCollision( void )
{
	return m_pCollision;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CMesh::GetMaterialCount( void )
{
	return m_MaterialCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMesh::GetMaterial( Sint32 Index, CMaterial *&pMaterial )
{
	if ( Index < m_MaterialCount )
	{
		pMaterial = &m_pMaterials[Index];
		pMaterial->AddRef();
		return true;
	}
	else
	{
		pMaterial = NULL;
		return false;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMesh::HitCheckByRay( const Collision::CLine3D &Ray )
{
	return m_pCollision->HitCheckByRay( Ray );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMesh::HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box )
{
	return m_pCollision->HitCheckByRay( Ray, Box );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMesh::HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResult &Out )
{
	return m_pCollision->HitCheckByRay( Ray, Out );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMesh::HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResult &Out, Collision::CBox &Box )
{
	return m_pCollision->HitCheckByRay( Ray, Out, Box );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMesh::HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResultExtend &Out )
{
	return m_pCollision->HitCheckByRay( Ray, Out );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMesh::HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResultExtend &Out, Collision::CBox &Box )
{
	return m_pCollision->HitCheckByRay( Ray, Out, Box );
}

