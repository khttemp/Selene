//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Class/Common/Render/3D/CLinePrimitive3D.h"
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
CLine3D::CLine3D( CRender *pRender, CRenderObjectMgr *pMgr ) : CPrimitive3DBase( pRender, pMgr )
{
	SetName( "3Dラインプリミティブ" );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CLine3D::~CLine3D()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CLine3D::Create( Sint32 VertexMax, Bool IsDynamic )
{
	Bool bRet = false;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( m_Name );
	Log_CellBegin( 0 );

	//--------------------------------------------------------------
	// 頂点バッファ
	//--------------------------------------------------------------
	Sint32 Size = m_pRender->GetSize( VERTEX_ELEMENT_3DBASE );
	m_pVB_Base = m_pRender->CreateVertexBuffer( VertexMax, Size, IsDynamic );
	if ( m_pVB_Base == NULL )
	{
		Log_PrintStrong( 0xFF0000, "頂点バッファの生成に失敗" );
		goto EXIT;
	}

	//--------------------------------------------------------------
	// 頂点ストリーム
	//--------------------------------------------------------------
	m_pVS = m_pRender->CreateVertexStream( VERTEX_ELEMENT_3DBASE );
	if ( m_pVS == NULL )
	{
		Log_PrintStrong( 0xFF0000, "頂点ストリームの生成に失敗" );
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
void CLine3D::PushBox( Collision::CBox &Box, CColor Color )
{
	// 箱の枠
	{
		SLineVertex3D LineData[] = {
			{ { Box.Points[0], Color }, { Box.Points[1], Color } },
			{ { Box.Points[1], Color }, { Box.Points[2], Color } },
			{ { Box.Points[2], Color }, { Box.Points[3], Color } },
			{ { Box.Points[3], Color }, { Box.Points[0], Color } },

			{ { Box.Points[4], Color }, { Box.Points[5], Color } },
			{ { Box.Points[5], Color }, { Box.Points[6], Color } },
			{ { Box.Points[6], Color }, { Box.Points[7], Color } },
			{ { Box.Points[7], Color }, { Box.Points[4], Color } },

			{ { Box.Points[0], Color }, { Box.Points[4], Color } },
			{ { Box.Points[1], Color }, { Box.Points[5], Color } },
			{ { Box.Points[2], Color }, { Box.Points[6], Color } },
			{ { Box.Points[3], Color }, { Box.Points[7], Color } },
		};
		Push( LineData, sizeof(LineData) / sizeof(SLineVertex3D) );
	}

	// 箱の対角線
	{
		CColor ColorD( Color.r/2, Color.g/2, Color.b/2, Color.a );

		SLineVertex3D LineData[] = {
			{ { Box.Points[0], Color }, { Box.Points[2], ColorD } },
			{ { Box.Points[1], Color }, { Box.Points[3], ColorD } },
			{ { Box.Points[4], Color }, { Box.Points[6], ColorD } },
			{ { Box.Points[7], Color }, { Box.Points[5], ColorD } },

			{ { Box.Points[1], Color }, { Box.Points[4], ColorD } },
			{ { Box.Points[0], Color }, { Box.Points[5], ColorD } },
			{ { Box.Points[6], Color }, { Box.Points[3], ColorD } },
			{ { Box.Points[7], Color }, { Box.Points[2], ColorD } },

			{ { Box.Points[1], Color }, { Box.Points[6], ColorD } },
			{ { Box.Points[5], Color }, { Box.Points[2], ColorD } },
			{ { Box.Points[0], Color }, { Box.Points[7], ColorD } },
			{ { Box.Points[3], Color }, { Box.Points[4], ColorD } },
		};
		Push( LineData, sizeof(LineData) / sizeof(SLineVertex3D) );
	}

	// 箱の法線
	{
		CColor ColorD( Color.r/3, Color.g/3, Color.b/3, Color.a );

		Math::Vector3D vCenter[] = {
			(Box.Points[0] + Box.Points[1] + Box.Points[2] + Box.Points[3]) / 4.0f,
			(Box.Points[6] + Box.Points[5] + Box.Points[4] + Box.Points[7]) / 4.0f,
			(Box.Points[1] + Box.Points[5] + Box.Points[6] + Box.Points[2]) / 4.0f,
			(Box.Points[0] + Box.Points[3] + Box.Points[7] + Box.Points[4]) / 4.0f,
			(Box.Points[1] + Box.Points[5] + Box.Points[4] + Box.Points[0]) / 4.0f,
			(Box.Points[6] + Box.Points[2] + Box.Points[3] + Box.Points[7]) / 4.0f,
		};

		Float fScale = (Box.Points[0] - Box.Points[6]).Length() / 10.0f;

		SLineVertex3D LineData[] = {
			{ { vCenter[0], Color }, { vCenter[0] + (Box.Planes[0].n * fScale), ColorD } },
			{ { vCenter[1], Color }, { vCenter[1] + (Box.Planes[1].n * fScale), ColorD } },
			{ { vCenter[2], Color }, { vCenter[2] + (Box.Planes[2].n * fScale), ColorD } },
			{ { vCenter[3], Color }, { vCenter[3] + (Box.Planes[3].n * fScale), ColorD } },
			{ { vCenter[4], Color }, { vCenter[4] + (Box.Planes[4].n * fScale), ColorD } },
			{ { vCenter[5], Color }, { vCenter[5] + (Box.Planes[5].n * fScale), ColorD } },
		};

		Push( LineData, sizeof(LineData) / sizeof(SLineVertex3D) );
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CLine3D::Push( SLineVertex3D *pLine, Sint32 LineCount )
{
	for ( Sint32 i = 0; i < LineCount; i++ )
	{
		if ( !CPrimitive3DBase::Push( &pLine[i].v1, 1 ) ) return false;
		if ( !CPrimitive3DBase::Push( &pLine[i].v2, 1 ) ) return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CLine3D::Begin( void )
{
	CPrimitive3DBase::Begin( true, true, true );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CLine3D::End( void )
{
	CPrimitive3DBase::End();
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CLine3D::CreateRenderActor( Scene::CSceneLineActorObject *pActor )
{
	//------------------------------------------------------------
	// メッシュデータ
	//------------------------------------------------------------
	pActor->SetStream( m_pIB, m_pVS, m_pVB_Base, NULL, NULL, NULL, NULL );

	//------------------------------------------------------------
	// マテリアル
	//------------------------------------------------------------
	pActor->SetMateriaCount( 1 );
	Scene::CSceneActorMaterial &Mtrl = pActor->GetSceneRenderMaterial( 0 );
	// テクスチャ
	for ( Sint32 j = 0; j < MATERIAL_TEXTURE_MAX; j++ )
	{
		Mtrl.SetTexture( (eTextureStage)j, NULL );
	}
}

