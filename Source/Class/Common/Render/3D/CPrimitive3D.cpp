

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Class/Common/Scene/CSceneModelActorObject.h"
#include "Class/Common/Render/3D/CPrimitive3D.h"
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
CPrimitive3D::CPrimitive3D( CRender *pRender, CRenderObjectMgr *pMgr, Bool IsBillboard, Bool IsSoftBillboard ) : CPrimitive3DBase( pRender, pMgr )
	, m_IsBillboard			( IsBillboard )
	, m_IsSoftBillboard		( IsSoftBillboard )
{
	SetName( "3D�v���~�e�B�u" );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPrimitive3D::~CPrimitive3D()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3D::Create( Sint32 VertexMax, Sint32 IndexMax, Sint32 VertexFlag, Bool IsDynamicVertex, Bool IsDynamicIndex )
{
	Bool bRet = false;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "����" );
	Log_PrintCellKind( m_Name );
	Log_CellBegin( 0 );

	//--------------------------------------------------------------
	// �t���O�`�F�b�N
	//--------------------------------------------------------------
	if ( (VertexFlag & VERTEX_ELEMENT_SPRITE) != 0 )
	{
		Log_PrintStrong( 0xFF0000, "VERTEX_ELEMENT_SPRITE�t���O�̓T�|�[�g����Ă��܂���" );
		goto EXIT;
	}

	if ( (VertexFlag & VERTEX_ELEMENT_3DBASE) == 0 )
	{
		Log_PrintStrong( 0xFF0000, "VERTEX_ELEMENT_3DBASE�t���O������܂���" );
		goto EXIT;
	}

	//--------------------------------------------------------------
	// �|���S���^�C�v
	//--------------------------------------------------------------
	m_VertexFlag = VertexFlag;

	//--------------------------------------------------------------
	// ���_�o�b�t�@
	//--------------------------------------------------------------
	if ( (VertexFlag & VERTEX_ELEMENT_3DBASE) != 0 )
	{
		Sint32 Size = m_pRender->GetSize( VERTEX_ELEMENT_3DBASE );
		m_pVB_Base = m_pRender->CreateVertexBuffer( VertexMax, Size, IsDynamicVertex );
		if ( m_pVB_Base == NULL )
		{
			Log_PrintStrong( 0xFF0000, "���_�o�b�t�@�̐����Ɏ��s" );
			goto EXIT;
		}
	}

	if ( (VertexFlag & VERTEX_ELEMENT_3DTEXTURE) != 0 )
	{
		Sint32 Size = m_pRender->GetSize( VERTEX_ELEMENT_3DTEXTURE );
		m_pVB_Tex = m_pRender->CreateVertexBuffer( VertexMax, Size, IsDynamicVertex );
		if ( m_pVB_Tex == NULL )
		{
			Log_PrintStrong( 0xFF0000, "���_�o�b�t�@�̐����Ɏ��s" );
			goto EXIT;
		}
	}

	if ( (VertexFlag & VERTEX_ELEMENT_3DLIGHT) != 0 )
	{
		Sint32 Size = m_pRender->GetSize( VERTEX_ELEMENT_3DLIGHT );
		m_pVB_Light = m_pRender->CreateVertexBuffer( VertexMax, Size, IsDynamicVertex );
		if ( m_pVB_Light == NULL )
		{
			Log_PrintStrong( 0xFF0000, "���_�o�b�t�@�̐����Ɏ��s" );
			goto EXIT;
		}

		if ( (VertexFlag & VERTEX_ELEMENT_3DBUMP) != 0 )
		{
			Sint32 Size = m_pRender->GetSize( VERTEX_ELEMENT_3DBUMP );
			m_pVB_Bump = m_pRender->CreateVertexBuffer( VertexMax, Size, IsDynamicVertex );
			if ( m_pVB_Bump == NULL )
			{
				Log_PrintStrong( 0xFF0000, "���_�o�b�t�@�̐����Ɏ��s" );
				goto EXIT;
			}
		}
	}

	if ( (VertexFlag & VERTEX_ELEMENT_3DANIMATION) != 0 )
	{
		Sint32 Size = m_pRender->GetSize( VERTEX_ELEMENT_3DANIMATION );
		m_pVB_Animation = m_pRender->CreateVertexBuffer( VertexMax, Size, IsDynamicVertex );
		if ( m_pVB_Animation == NULL )
		{
			Log_PrintStrong( 0xFF0000, "���_�o�b�t�@�̐����Ɏ��s" );
			goto EXIT;
		}
	}

	//--------------------------------------------------------------
	// �C���f�b�N�X�o�b�t�@
	//--------------------------------------------------------------
	m_pIB = m_pRender->CreateIndexBuffer( IndexMax, IsDynamicIndex );
	if ( m_pIB == NULL )
	{
		Log_PrintStrong( 0xFF0000, "�C���f�b�N�X�o�b�t�@�̐����Ɏ��s" );
		goto EXIT;
	}

	//--------------------------------------------------------------
	// ���_�X�g���[��
	//--------------------------------------------------------------
	m_pVS = m_pRender->CreateVertexStream( VertexFlag );
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
Bool CPrimitive3D::Push( const void *pIndex, Sint32 IndexCount )
{
	return CPrimitive3DBase::Push( pIndex, IndexCount );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3D::Push( const SVertex3DBase *pVtx, Sint32 Count )
{
	return CPrimitive3DBase::Push( pVtx, Count );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3D::Push( const SVertex3DTexture *pVtx, Sint32 Count )
{
	return CPrimitive3DBase::Push( pVtx, Count );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3D::Push( const SVertex3DLight *pVtx, Sint32 Count )
{
	return CPrimitive3DBase::Push( pVtx, Count );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3D::Push( const SVertex3DBump *pVtx, Sint32 Count )
{
	return CPrimitive3DBase::Push( pVtx, Count );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3D::Push( const SVertex3DAnimation *pVtx, Sint32 Count )
{
	return CPrimitive3DBase::Push( pVtx, Count );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CPrimitive3D::GetVertexCount( void )
{
	return CPrimitive3DBase::GetVertexCount();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CPrimitive3D::GetIndexCount( void )
{
	return CPrimitive3DBase::GetIndexCount();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive3D::Begin( Bool IsVertex, Bool IsIndex, Bool IsDirect )
{
	CPrimitive3DBase::Begin( IsVertex, IsIndex, IsDirect );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive3D::End( void )
{
	CPrimitive3DBase::End();
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CPrimitive3D::CreateRenderActor( Scene::CPrimitiveActorObject *pActor )
{
	//------------------------------------------------------------
	// ���b�V���f�[�^
	//------------------------------------------------------------
	pActor->SetStream( m_pIB, m_pVS, m_pVB_Base, m_pVB_Tex, m_pVB_Light, m_pVB_Bump, m_pVB_Animation );

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

