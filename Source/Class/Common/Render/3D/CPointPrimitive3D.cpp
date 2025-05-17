

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Class/Common/Scene/CSceneModelActorObject.h"
#include "Class/Common/Render/3D/CPointPrimitive3D.h"
#include "Class/Platform/Surface/CTexture.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Class/Platform/Render/Shader/CShader.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;
using namespace Object;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPoint3D::CPoint3D( CRender *pRender, CRenderObjectMgr *pMgr ) : CPrimitive3DBase( pRender, pMgr )
{
	SetName( "3D�|�C���g�v���~�e�B�u" );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPoint3D::~CPoint3D()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPoint3D::Create( Sint32 VertexMax, Bool IsDynamic )
{
	Bool bRet = false;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "����" );
	Log_PrintCellKind( m_Name );
	Log_CellBegin( 0 );

	//--------------------------------------------------------------
	// ���_�o�b�t�@
	//--------------------------------------------------------------
	Sint32 Size = m_pRender->GetSize( VERTEX_ELEMENT_3DBASE );
	m_pVB_Base = m_pRender->CreateVertexBuffer( VertexMax, Size, IsDynamic );
	if ( m_pVB_Base == NULL )
	{
		Log_PrintStrong( 0xFF0000, "���_�o�b�t�@�̐����Ɏ��s" );
		goto EXIT;
	}

	//--------------------------------------------------------------
	// ���_�X�g���[��
	//--------------------------------------------------------------
	m_pVS = m_pRender->CreateVertexStream( VERTEX_ELEMENT_3DBASE );
	if ( m_pVS == NULL )
	{
		Log_PrintStrong( 0xFF0000, "���_�X�g���[���̐����Ɏ��s" );
		goto EXIT;
	}

	char Temp[64] = "";
	StringCbPrintf( Temp, sizeof(Temp), "0x%016X", (Uint64)this );
	Log_PrintLine( 0x0000000, Temp );

	bRet = true;

EXIT:
	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return bRet;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPoint3D::Push( const SVertex3DBase *pPoint, Sint32 PointCount )
{
	return CPrimitive3DBase::Push( pPoint, PointCount );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPoint3D::Begin( void )
{
	CPrimitive3DBase::Begin( true, true, true );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPoint3D::End( void )
{
	CPrimitive3DBase::End();
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CPoint3D::CreateRenderActor( Scene::CScenePointActorObject *pActor )
{
	//------------------------------------------------------------
	// ���b�V���f�[�^
	//------------------------------------------------------------
	pActor->SetStream( m_pIB, m_pVS, m_pVB_Base, NULL, NULL, NULL, NULL );

	//------------------------------------------------------------
	// �}�e���A��
	//------------------------------------------------------------
	pActor->SetMateriaCount( 1 );
	Scene::CSceneActorMaterial &Mtrl = pActor->GetSceneRenderMaterial( 0 );
	// �e�N�X�`��
	for ( Sint32 j = 0; j < MATERIAL_TEXTURE_MAX; j++ )
	{
		Mtrl.SetTexture( (eTextureStage)j, NULL );
	}
}

