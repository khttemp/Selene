

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Surface/CTexture.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Render/3D/CSprite3D.h"
#include "Class/Common/Scene/CSceneManagerBase.h"


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
CSprite3D::CSprite3D( CRender *pRender, CRenderObjectMgr *pMgr ) : CPrimitive3D( pRender, pMgr, false, false )
	, m_pTexture		( NULL )
{
	SetName( "3Dスプライト" );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSprite3D::~CSprite3D()
{
	SAFE_RELEASE( m_pTexture );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSprite3D::Create( Sint32 VertexMax, Sint32 IndexMax, ITexture *pTexture )
{
	Bool bRet = false;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( m_Name );
	Log_CellBegin( 0 );

	//--------------------------------------------------------------
	// ポリゴンタイプ
	//--------------------------------------------------------------
	m_VertexFlag = VERTEX_ELEMENT_3DBASE | VERTEX_ELEMENT_3DTEXTURE;

	//--------------------------------------------------------------
	// 頂点バッファ
	//--------------------------------------------------------------
	{
		Sint32 Size = m_pRender->GetSize( VERTEX_ELEMENT_3DBASE );
		m_pVB_Base = m_pRender->CreateVertexBuffer( VertexMax, Size, true );
		if ( m_pVB_Base == NULL )
		{
			Log_PrintStrong( 0xFF0000, "頂点バッファの生成に失敗" );
			goto EXIT;
		}
	}

	{
		Sint32 Size = m_pRender->GetSize( VERTEX_ELEMENT_3DTEXTURE );
		m_pVB_Tex = m_pRender->CreateVertexBuffer( VertexMax, Size, true );
		if ( m_pVB_Tex == NULL )
		{
			Log_PrintStrong( 0xFF0000, "頂点バッファの生成に失敗" );
			goto EXIT;
		}
	}

	//--------------------------------------------------------------
	// インデックスバッファ
	//--------------------------------------------------------------
	m_pIB = m_pRender->CreateIndexBuffer( IndexMax, false );
	if ( m_pIB == NULL )
	{
		Log_PrintStrong( 0xFF0000, "インデックスバッファの生成に失敗" );
		goto EXIT;
	}

	//--------------------------------------------------------------
	// 頂点ストリーム
	//--------------------------------------------------------------
	m_pVS = m_pRender->CreateVertexStream( m_VertexFlag );
	if ( m_pVS == NULL )
	{
		Log_PrintStrong( 0xFF0000, "頂点ストリームの生成に失敗" );
		goto EXIT;
	}

	//--------------------------------------------------------------
	// テクスチャ
	//--------------------------------------------------------------
	if ( (pTexture != NULL) && pTexture->IsInvalid() )
	{
		pTexture = NULL;
	}

	m_pTexture = pTexture;
	if ( pTexture != NULL )
	{
		m_pTexture->AddRef();
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
/**
*/
//-----------------------------------------------------------------------------------
void CSprite3D::Begin( void )
{
	CPrimitive3D::Begin( true, true, true );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite3D::End( void )
{
	CPrimitive3D::End();
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CSprite3D::CreateRenderActor( Scene::CSpriteActorObject *pActor )
{
	//------------------------------------------------------------
	// メッシュデータ
	//------------------------------------------------------------
	pActor->SetStream( m_pIB, m_pVS, m_pVB_Base, m_pVB_Tex, m_pVB_Light, m_pVB_Bump, m_pVB_Animation );

	//------------------------------------------------------------
	// マテリアル
	//------------------------------------------------------------
	pActor->SetMateriaCount( 1 );
	Scene::CSceneActorMaterial &Mtrl = pActor->GetSceneRenderMaterial( 0 );
	// テクスチャ
	for ( Sint32 j = 1; j < MATERIAL_TEXTURE_MAX; j++ )
	{
		Mtrl.SetTexture( (eTextureStage)j, NULL );
	}

	Mtrl.SetTexture( TEXTURE_STAGE_COLOR, m_pTexture );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CSprite3D::Draw( const Math::Matrix &mWorld, const Math::Point2DF &Size, const Math::Rect2DI &Src, CColor Color )
{
	Float fSx = Size.x * 0.5f;
	Float fSy = Size.y * 0.5f;

	Math::Vector2D PtTbl[] = {
		Math::Vector2D( -fSx, +fSy ), Math::Vector2D( +fSx, +fSy ),
		Math::Vector2D( -fSx, -fSy ), Math::Vector2D( +fSx, -fSy ),
	};

	Draw( mWorld, PtTbl, Src, Color );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CSprite3D::Draw( const Math::Matrix &mWorld, const Math::Vector2D PtTbl[], const Math::Rect2DI &Src, CColor Color )
{
	//--------------------------------------------------
	// インデックス
	//--------------------------------------------------
	Uint16 Idx = (Uint16)m_pVB_Base->GetCount();
	Uint16 IdxTbl[6] = {
		Idx + 0, Idx + 1, Idx + 2,
		Idx + 2, Idx + 1, Idx + 3,
	};
	Push( IdxTbl, 6 );

	//--------------------------------------------------
	// 位置
	//--------------------------------------------------
	SVertex3DBase VtxBase[4] = {
		{ Math::Vector3D( PtTbl[0].x, PtTbl[0].y, 0.0f ), Color },
		{ Math::Vector3D( PtTbl[1].x, PtTbl[1].y, 0.0f ), Color },
		{ Math::Vector3D( PtTbl[2].x, PtTbl[2].y, 0.0f ), Color },
		{ Math::Vector3D( PtTbl[3].x, PtTbl[3].y, 0.0f ), Color },
	};

	// 変換
	VtxBase[0].Pos.TransformCoord( mWorld );
	VtxBase[1].Pos.TransformCoord( mWorld );
	VtxBase[2].Pos.TransformCoord( mWorld );
	VtxBase[3].Pos.TransformCoord( mWorld );

	Push( VtxBase, 4 );

	//--------------------------------------------------
	// テクスチャ
	//--------------------------------------------------
	Float u1, v1, u2, v2;
	if ( m_pTexture != NULL )
	{
		Math::Point2DF vTransform = m_pTexture->GetPixelToTexelTransform();
		u1 = toF(Src.x         + 0.5f) * vTransform.x;
		v1 = toF(Src.y         + 0.5f) * vTransform.y;
		u2 = toF(Src.x + Src.w - 0.5f) * vTransform.x;
		v2 = toF(Src.y + Src.h - 0.5f) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	SVertex3DTexture VtxTex[4] = {
		{ Math::Vector2D( u1, v1 ) },
		{ Math::Vector2D( u2, v1 ) },
		{ Math::Vector2D( u1, v2 ) },
		{ Math::Vector2D( u2, v2 ) },
	};

	Push( VtxTex, 4 );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CSprite3D::DrawPolyLine( const Math::Vector3D &vCameraPosition, const Math::Vector3D Pos[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src )
{
	//--------------------------------------------------
	// インデックス
	//--------------------------------------------------
	Uint16 Idx = (Uint16)m_pVB_Base->GetCount();
	for ( Sint32 i = 0; i < Count - 1; i++ )
	{
		Uint16 IdxTbl[6] = {
			Idx + 0, Idx + 1, Idx + 2,
			Idx + 1, Idx + 3, Idx + 2,
		};

		Push( IdxTbl, 6 );

		Idx += 2;
	}

	//--------------------------------------------------
	// 位置
	//--------------------------------------------------
	for ( Sint32 i = 0; i < Count; i++ )
	{
		// 接線
		Sint32 Pt1 = i - 1;
		Sint32 Pt2 = i + 1;
		if ( Pt1 <=    -1 ) Pt1 =       0;
		if ( Pt2 >= Count ) Pt2 = Count-1;
		Math::Vector3D vTangent = (Pos[Pt1] - Pos[Pt2]).NormalizeFast();

		// 視線
		Math::Vector3D vEye = (vCameraPosition - Pos[i]).NormalizeFast();

		// 頂点における横方向
		Math::Vector3D vCross;
		vCross.Cross( vTangent, vEye );
		vCross.NormalizeFast();

		// 頂点データ
		SVertex3DBase VtxBase[2] = {
			{ Pos[i] - (vCross * Width), Color[i] },
			{ Pos[i] + (vCross * Width), Color[i] },
		};

		Push( VtxBase, 2 );
	}

	//--------------------------------------------------
	// テクスチャ
	//--------------------------------------------------
	Float u1, v1, u2, v2;
	if ( m_pTexture != NULL )
	{
		Math::Point2DF vTransform = m_pTexture->GetPixelToTexelTransform();
		u1 = toF(Src.x         + 0.5f) * vTransform.x;
		v1 = toF(Src.y         + 0.5f) * vTransform.y;
		u2 = toF(Src.x + Src.w - 0.5f) * vTransform.x;
		v2 = toF(Src.y + Src.h - 0.5f) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	for ( Sint32 i = 0; i < Count; i++ )
	{
		Float v = (v2 - v1) * toF(i) / toF(Count-1);

		SVertex3DTexture VtxTex[2] = {
			{ Math::Vector2D( u1, v1 + v ) },
			{ Math::Vector2D( u2, v1 + v ) },
		};

		Push( VtxTex, 2 );
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CSprite3D::DrawPolyLine( const Math::Vector3D &vCameraPosition, const Math::Vector3D Pos[], const CColor Color[], const Float Width[], Sint32 Count, const Math::Rect2DF &Src )
{
	//--------------------------------------------------
	// インデックス
	//--------------------------------------------------
	Uint16 Idx = (Uint16)m_pVB_Base->GetCount();
	for ( Sint32 i = 0; i < Count - 1; i++ )
	{
		Uint16 IdxTbl[6] = {
			Idx + 0, Idx + 1, Idx + 2,
			Idx + 1, Idx + 3, Idx + 2,
		};

		Push( IdxTbl, 6 );

		Idx += 2;
	}

	//--------------------------------------------------
	// 位置
	//--------------------------------------------------
	for ( Sint32 i = 0; i < Count; i++ )
	{
		// 接線
		Sint32 Pt1 = i - 1;
		Sint32 Pt2 = i + 1;
		if ( Pt1 <=    -1 ) Pt1 =       0;
		if ( Pt2 >= Count ) Pt2 = Count-1;
		Math::Vector3D vTangent = (Pos[Pt1] - Pos[Pt2]).NormalizeFast();

		// 視線
		Math::Vector3D vEye = (vCameraPosition - Pos[i]).NormalizeFast();

		// 頂点における横方向
		Math::Vector3D vCross;
		vCross.Cross( vTangent, vEye );
		vCross.NormalizeFast();

		// 頂点データ
		SVertex3DBase VtxBase[2] = {
			{ Pos[i] - (vCross * Width[i]), Color[i] },
			{ Pos[i] + (vCross * Width[i]), Color[i] },
		};

		Push( VtxBase, 2 );
	}

	//--------------------------------------------------
	// テクスチャ
	//--------------------------------------------------
	Float u1, v1, u2, v2;
	if ( m_pTexture != NULL )
	{
		Math::Point2DF vTransform = m_pTexture->GetPixelToTexelTransform();
		u1 = toF(Src.x         + 0.5f) * vTransform.x;
		v1 = toF(Src.y         + 0.5f) * vTransform.y;
		u2 = toF(Src.x + Src.w - 0.5f) * vTransform.x;
		v2 = toF(Src.y + Src.h - 0.5f) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	for ( Sint32 i = 0; i < Count; i++ )
	{
		Float v = (v2 - v1) * toF(i) / toF(Count-1);

		SVertex3DTexture VtxTex[2] = {
			{ Math::Vector2D( u1, v1 + v ) },
			{ Math::Vector2D( u2, v1 + v ) },
		};

		Push( VtxTex, 2 );
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CSprite3D::DrawPolyLine( const Math::Vector3D &vCameraPosition, const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src )
{
	//--------------------------------------------------
	// インデックス
	//--------------------------------------------------
	Uint16 Vtx = (Uint16)m_pVB_Base->GetCount();
	for ( Sint32 i = 0; i < Count - 1; i++ )
	{
		Uint16 IdxTbl[6] = {
			Vtx + 0, Vtx + 1, Vtx + 2,
			Vtx + 1, Vtx + 3, Vtx + 2,
		};

		Push( IdxTbl, 6 );

		Vtx += 2;
	}

	//--------------------------------------------------
	// 位置
	//--------------------------------------------------
	for ( Sint32 i = 0; i < Count; i++ )
	{
		// 接線
		Sint32 Pt1 = i - 1;
		Sint32 Pt2 = i + 1;
		if ( Pt1 <=    -1 ) Pt1 =       0;
		if ( Pt2 >= Count ) Pt2 = Count-1;
		Math::Vector3D vTangent = (List[Pt1].Pos - List[Pt2].Pos).NormalizeFast();

		// 視線
		Math::Vector3D vEye = (vCameraPosition - List[i].Pos).NormalizeFast();

		// 頂点における横方向
		Math::Vector3D vCross;
		vCross.Cross( vTangent, vEye );
		vCross.NormalizeFast();

		// 頂点データ
		SVertex3DBase VtxBase[2] = {
			{ List[i].Pos - (vCross * List[i].Width), List[i].Color },
			{ List[i].Pos + (vCross * List[i].Width), List[i].Color },
		};

		Push( VtxBase, 2 );
	}

	//--------------------------------------------------
	// テクスチャ
	//--------------------------------------------------
	Float u1, v1, u2, v2;
	if ( m_pTexture != NULL )
	{
		Math::Point2DF vTransform = m_pTexture->GetPixelToTexelTransform();
		u1 = toF(Src.x         + 0.5f) * vTransform.x;
		v1 = toF(Src.y         + 0.5f) * vTransform.y;
		u2 = toF(Src.x + Src.w - 0.5f) * vTransform.x;
		v2 = toF(Src.y + Src.h - 0.5f) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	for ( Sint32 i = 0; i < Count; i++ )
	{
		Float v = (v2 - v1) * toF(i) / toF(Count-1);

		SVertex3DTexture VtxTex[2] = {
			{ Math::Vector2D( u1, v1 + v ) },
			{ Math::Vector2D( u2, v1 + v ) },
		};

		Push( VtxTex, 2 );
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CSprite3D::DrawListXY( const Math::Vector3D Pos[], const Sint32 Angle[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src )
{
	//--------------------------------------------------
	// インデックス
	//--------------------------------------------------
	Uint16 Idx = (Uint16)m_pVB_Base->GetCount();
	for ( Sint32 i = 0; i < Count - 1; i++ )
	{
		Uint16 IdxTbl[6] = {
			Idx + 0, Idx + 1, Idx + 2,
			Idx + 1, Idx + 3, Idx + 2,
		};

		Push( IdxTbl, 6 );

		Idx += 2;
	}

	//--------------------------------------------------
	// 位置
	//--------------------------------------------------
	for ( Sint32 i = 0; i < Count; i++ )
	{
		Math::Vector3D Pt = Math::Vector3D( Width, 0.0f, 0.0f );
		Pt.RotationZ( Angle[i] );

		SVertex3DBase VtxBase[2] = {
			{ Pos[i] - Pt, Color[i] },
			{ Pos[i] + Pt, Color[i] },
		};

		Push( VtxBase, 2 );
	}

	//--------------------------------------------------
	// テクスチャ
	//--------------------------------------------------
	Float u1, v1, u2, v2;
	if ( m_pTexture != NULL )
	{
		Math::Point2DF vTransform = m_pTexture->GetPixelToTexelTransform();
		u1 = toF(Src.x         + 0.5f) * vTransform.x;
		v1 = toF(Src.y         + 0.5f) * vTransform.y;
		u2 = toF(Src.x + Src.w - 0.5f) * vTransform.x;
		v2 = toF(Src.y + Src.h - 0.5f) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	for ( Sint32 i = 0; i < Count; i++ )
	{
		Float v = (v2 - v1) * toF(i) / toF(Count-1);

		SVertex3DTexture VtxTex[2] = {
			{ Math::Vector2D( u1, v1 + v ) },
			{ Math::Vector2D( u2, v1 + v ) },
		};

		Push( VtxTex, 2 );
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CSprite3D::DrawListYZ( const Math::Vector3D Pos[], const Sint32 Angle[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src )
{
	//--------------------------------------------------
	// インデックス
	//--------------------------------------------------
	Uint16 Idx = (Uint16)m_pVB_Base->GetCount();
	for ( Sint32 i = 0; i < Count - 1; i++ )
	{
		Uint16 IdxTbl[6] = {
			Idx + 0, Idx + 1, Idx + 2,
			Idx + 1, Idx + 3, Idx + 2,
		};

		Push( IdxTbl, 6 );

		Idx += 2;
	}

	//--------------------------------------------------
	// 位置
	//--------------------------------------------------
	for ( Sint32 i = 0; i < Count; i++ )
	{
		Math::Vector3D Pt = Math::Vector3D( 0.0f, Width, 0.0f );
		Pt.RotationX( Angle[i] );

		SVertex3DBase VtxBase[2] = {
			{ Pos[i] - Pt, Color[i] },
			{ Pos[i] + Pt, Color[i] },
		};

		Push( VtxBase, 2 );
	}

	//--------------------------------------------------
	// テクスチャ
	//--------------------------------------------------
	Float u1, v1, u2, v2;
	if ( m_pTexture != NULL )
	{
		Math::Point2DF vTransform = m_pTexture->GetPixelToTexelTransform();
		u1 = toF(Src.x         + 0.5f) * vTransform.x;
		v1 = toF(Src.y         + 0.5f) * vTransform.y;
		u2 = toF(Src.x + Src.w - 0.5f) * vTransform.x;
		v2 = toF(Src.y + Src.h - 0.5f) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	for ( Sint32 i = 0; i < Count; i++ )
	{
		Float v = (v2 - v1) * toF(i) / toF(Count-1);

		SVertex3DTexture VtxTex[2] = {
			{ Math::Vector2D( u1, v1 + v ) },
			{ Math::Vector2D( u2, v1 + v ) },
		};

		Push( VtxTex, 2 );
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CSprite3D::DrawListZX( const Math::Vector3D Pos[], const Sint32 Angle[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src )
{
	//--------------------------------------------------
	// インデックス
	//--------------------------------------------------
	Uint16 Idx = (Uint16)m_pVB_Base->GetCount();
	for ( Sint32 i = 0; i < Count - 1; i++ )
	{
		Uint16 IdxTbl[6] = {
			Idx + 0, Idx + 1, Idx + 2,
			Idx + 1, Idx + 3, Idx + 2,
		};

		Push( IdxTbl, 6 );

		Idx += 2;
	}

	//--------------------------------------------------
	// 位置
	//--------------------------------------------------
	for ( Sint32 i = 0; i < Count; i++ )
	{
		Math::Vector3D Pt = Math::Vector3D( 0.0f, 0.0f, Width );
		Pt.RotationY( Angle[i] );

		SVertex3DBase VtxBase[2] = {
			{ Pos[i] - Pt, Color[i] },
			{ Pos[i] + Pt, Color[i] },
		};

		Push( VtxBase, 2 );
	}

	//--------------------------------------------------
	// テクスチャ
	//--------------------------------------------------
	Float u1, v1, u2, v2;
	if ( m_pTexture != NULL )
	{
		Math::Point2DF vTransform = m_pTexture->GetPixelToTexelTransform();
		u1 = toF(Src.x         + 0.5f) * vTransform.x;
		v1 = toF(Src.y         + 0.5f) * vTransform.y;
		u2 = toF(Src.x + Src.w - 0.5f) * vTransform.x;
		v2 = toF(Src.y + Src.h - 0.5f) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	for ( Sint32 i = 0; i < Count; i++ )
	{
		Float v = (v2 - v1) * toF(i) / toF(Count-1);

		SVertex3DTexture VtxTex[2] = {
			{ Math::Vector2D( u1, v1 + v ) },
			{ Math::Vector2D( u2, v1 + v ) },
		};

		Push( VtxTex, 2 );
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CSprite3D::DrawListXY( const Math::Vector3D Pos[], const Float Width[], const Sint32 Angle[], const CColor Color[], Sint32 Count, const Math::Rect2DF &Src )
{
	//--------------------------------------------------
	// インデックス
	//--------------------------------------------------
	Uint16 Idx = (Uint16)m_pVB_Base->GetCount();
	for ( Sint32 i = 0; i < Count - 1; i++ )
	{
		Uint16 IdxTbl[6] = {
			Idx + 0, Idx + 1, Idx + 2,
			Idx + 1, Idx + 3, Idx + 2,
		};

		Push( IdxTbl, 6 );

		Idx += 2;
	}

	//--------------------------------------------------
	// 位置
	//--------------------------------------------------
	for ( Sint32 i = 0; i < Count; i++ )
	{
		Math::Vector3D Pt = Math::Vector3D( Width[i], 0.0f, 0.0f );
		Pt.RotationZ( Angle[i] );

		SVertex3DBase VtxBase[2] = {
			{ Pos[i] - Pt, Color[i] },
			{ Pos[i] + Pt, Color[i] },
		};

		Push( VtxBase, 2 );
	}

	//--------------------------------------------------
	// テクスチャ
	//--------------------------------------------------
	Float u1, v1, u2, v2;
	if ( m_pTexture != NULL )
	{
		Math::Point2DF vTransform = m_pTexture->GetPixelToTexelTransform();
		u1 = toF(Src.x         + 0.5f) * vTransform.x;
		v1 = toF(Src.y         + 0.5f) * vTransform.y;
		u2 = toF(Src.x + Src.w - 0.5f) * vTransform.x;
		v2 = toF(Src.y + Src.h - 0.5f) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	for ( Sint32 i = 0; i < Count; i++ )
	{
		Float v = (v2 - v1) * toF(i) / toF(Count-1);

		SVertex3DTexture VtxTex[2] = {
			{ Math::Vector2D( u1, v1 + v ) },
			{ Math::Vector2D( u2, v1 + v ) },
		};

		Push( VtxTex, 2 );
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CSprite3D::DrawListYZ( const Math::Vector3D Pos[], const Float Width[], const Sint32 Angle[], const CColor Color[], Sint32 Count, const Math::Rect2DF &Src )
{
	//--------------------------------------------------
	// インデックス
	//--------------------------------------------------
	Uint16 Idx = (Uint16)m_pVB_Base->GetCount();
	for ( Sint32 i = 0; i < Count - 1; i++ )
	{
		Uint16 IdxTbl[6] = {
			Idx + 0, Idx + 1, Idx + 2,
			Idx + 1, Idx + 3, Idx + 2,
		};

		Push( IdxTbl, 6 );

		Idx += 2;
	}

	//--------------------------------------------------
	// 位置
	//--------------------------------------------------
	for ( Sint32 i = 0; i < Count; i++ )
	{
		Math::Vector3D Pt = Math::Vector3D( 0.0f, Width[i], 0.0f );
		Pt.RotationX( Angle[i] );

		SVertex3DBase VtxBase[2] = {
			{ Pos[i] - Pt, Color[i] },
			{ Pos[i] + Pt, Color[i] },
		};

		Push( VtxBase, 2 );
	}

	//--------------------------------------------------
	// テクスチャ
	//--------------------------------------------------
	Float u1, v1, u2, v2;
	if ( m_pTexture != NULL )
	{
		Math::Point2DF vTransform = m_pTexture->GetPixelToTexelTransform();
		u1 = toF(Src.x         + 0.5f) * vTransform.x;
		v1 = toF(Src.y         + 0.5f) * vTransform.y;
		u2 = toF(Src.x + Src.w - 0.5f) * vTransform.x;
		v2 = toF(Src.y + Src.h - 0.5f) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	for ( Sint32 i = 0; i < Count; i++ )
	{
		Float v = (v2 - v1) * toF(i) / toF(Count-1);

		SVertex3DTexture VtxTex[2] = {
			{ Math::Vector2D( u1, v1 + v ) },
			{ Math::Vector2D( u2, v1 + v ) },
		};

		Push( VtxTex, 2 );
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CSprite3D::DrawListZX( const Math::Vector3D Pos[], const Float Width[], const Sint32 Angle[], const CColor Color[], Sint32 Count, const Math::Rect2DF &Src )
{
	//--------------------------------------------------
	// インデックス
	//--------------------------------------------------
	Uint16 Idx = (Uint16)m_pVB_Base->GetCount();
	for ( Sint32 i = 0; i < Count - 1; i++ )
	{
		Uint16 IdxTbl[6] = {
			Idx + 0, Idx + 1, Idx + 2,
			Idx + 1, Idx + 3, Idx + 2,
		};

		Push( IdxTbl, 6 );

		Idx += 2;
	}

	//--------------------------------------------------
	// 位置
	//--------------------------------------------------
	for ( Sint32 i = 0; i < Count; i++ )
	{
		Math::Vector3D Pt = Math::Vector3D( 0.0f, 0.0f, Width[i] );
		Pt.RotationY( Angle[i] );

		SVertex3DBase VtxBase[2] = {
			{ Pos[i] - Pt, Color[i] },
			{ Pos[i] + Pt, Color[i] },
		};

		Push( VtxBase, 2 );
	}

	//--------------------------------------------------
	// テクスチャ
	//--------------------------------------------------
	Float u1, v1, u2, v2;
	if ( m_pTexture != NULL )
	{
		Math::Point2DF vTransform = m_pTexture->GetPixelToTexelTransform();
		u1 = toF(Src.x         + 0.5f) * vTransform.x;
		v1 = toF(Src.y         + 0.5f) * vTransform.y;
		u2 = toF(Src.x + Src.w - 0.5f) * vTransform.x;
		v2 = toF(Src.y + Src.h - 0.5f) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	for ( Sint32 i = 0; i < Count; i++ )
	{
		Float v = (v2 - v1) * toF(i) / toF(Count-1);

		SVertex3DTexture VtxTex[2] = {
			{ Math::Vector2D( u1, v1 + v ) },
			{ Math::Vector2D( u2, v1 + v ) },
		};

		Push( VtxTex, 2 );
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CSprite3D::DrawListXY( const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src )
{
	//--------------------------------------------------
	// インデックス
	//--------------------------------------------------
	Uint16 Idx = (Uint16)m_pVB_Base->GetCount();
	for ( Sint32 i = 0; i < Count - 1; i++ )
	{
		Uint16 IdxTbl[6] = {
			Idx + 0, Idx + 1, Idx + 2,
			Idx + 1, Idx + 3, Idx + 2,
		};

		Push( IdxTbl, 6 );

		Idx += 2;
	}

	//--------------------------------------------------
	// 位置
	//--------------------------------------------------
	for ( Sint32 i = 0; i < Count; i++ )
	{
		Math::Vector3D Pt = Math::Vector3D( List[i].Width, 0.0f, 0.0f );
		Pt.RotationZ( List[i].Angle );

		SVertex3DBase VtxBase[2] = {
			{ List[i].Pos - Pt, List[i].Color },
			{ List[i].Pos + Pt, List[i].Color },
		};

		Push( VtxBase, 2 );
	}

	//--------------------------------------------------
	// テクスチャ
	//--------------------------------------------------
	Float u1, v1, u2, v2;
	if ( m_pTexture != NULL )
	{
		Math::Point2DF vTransform = m_pTexture->GetPixelToTexelTransform();
		u1 = toF(Src.x         + 0.5f) * vTransform.x;
		v1 = toF(Src.y         + 0.5f) * vTransform.y;
		u2 = toF(Src.x + Src.w - 0.5f) * vTransform.x;
		v2 = toF(Src.y + Src.h - 0.5f) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	for ( Sint32 i = 0; i < Count; i++ )
	{
		Float v = (v2 - v1) * toF(i) / toF(Count-1);

		SVertex3DTexture VtxTex[2] = {
			{ Math::Vector2D( u1, v1 + v ) },
			{ Math::Vector2D( u2, v1 + v ) },
		};

		Push( VtxTex, 2 );
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CSprite3D::DrawListYZ( const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src )
{
	//--------------------------------------------------
	// インデックス
	//--------------------------------------------------
	Uint16 Idx = (Uint16)m_pVB_Base->GetCount();
	for ( Sint32 i = 0; i < Count - 1; i++ )
	{
		Uint16 IdxTbl[6] = {
			Idx + 0, Idx + 1, Idx + 2,
			Idx + 1, Idx + 3, Idx + 2,
		};

		Push( IdxTbl, 6 );

		Idx += 2;
	}

	//--------------------------------------------------
	// 位置
	//--------------------------------------------------
	for ( Sint32 i = 0; i < Count; i++ )
	{
		Math::Vector3D Pt = Math::Vector3D( 0.0f, List[i].Width, 0.0f );
		Pt.RotationX( List[i].Angle );

		SVertex3DBase VtxBase[2] = {
			{ List[i].Pos - Pt, List[i].Color },
			{ List[i].Pos + Pt, List[i].Color },
		};

		Push( VtxBase, 2 );
	}

	//--------------------------------------------------
	// テクスチャ
	//--------------------------------------------------
	Float u1, v1, u2, v2;
	if ( m_pTexture != NULL )
	{
		Math::Point2DF vTransform = m_pTexture->GetPixelToTexelTransform();
		u1 = toF(Src.x         + 0.5f) * vTransform.x;
		v1 = toF(Src.y         + 0.5f) * vTransform.y;
		u2 = toF(Src.x + Src.w - 0.5f) * vTransform.x;
		v2 = toF(Src.y + Src.h - 0.5f) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	for ( Sint32 i = 0; i < Count; i++ )
	{
		Float v = (v2 - v1) * toF(i) / toF(Count-1);

		SVertex3DTexture VtxTex[2] = {
			{ Math::Vector2D( u1, v1 + v ) },
			{ Math::Vector2D( u2, v1 + v ) },
		};

		Push( VtxTex, 2 );
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CSprite3D::DrawListZX( const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src )
{
	//--------------------------------------------------
	// インデックス
	//--------------------------------------------------
	Uint16 Idx = (Uint16)m_pVB_Base->GetCount();
	for ( Sint32 i = 0; i < Count - 1; i++ )
	{
		Uint16 IdxTbl[6] = {
			Idx + 0, Idx + 1, Idx + 2,
			Idx + 1, Idx + 3, Idx + 2,
		};

		Push( IdxTbl, 6 );

		Idx += 2;
	}

	//--------------------------------------------------
	// 位置
	//--------------------------------------------------
	for ( Sint32 i = 0; i < Count; i++ )
	{
		Math::Vector3D Pt = Math::Vector3D( 0.0f, 0.0f, List[i].Width );
		Pt.RotationY( List[i].Angle );

		SVertex3DBase VtxBase[2] = {
			{ List[i].Pos - Pt, List[i].Color },
			{ List[i].Pos + Pt, List[i].Color },
		};

		Push( VtxBase, 2 );
	}

	//--------------------------------------------------
	// テクスチャ
	//--------------------------------------------------
	Float u1, v1, u2, v2;
	if ( m_pTexture != NULL )
	{
		Math::Point2DF vTransform = m_pTexture->GetPixelToTexelTransform();
		u1 = toF(Src.x         + 0.5f) * vTransform.x;
		v1 = toF(Src.y         + 0.5f) * vTransform.y;
		u2 = toF(Src.x + Src.w - 0.5f) * vTransform.x;
		v2 = toF(Src.y + Src.h - 0.5f) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	for ( Sint32 i = 0; i < Count; i++ )
	{
		Float v = (v2 - v1) * toF(i) / toF(Count-1);

		SVertex3DTexture VtxTex[2] = {
			{ Math::Vector2D( u1, v1 + v ) },
			{ Math::Vector2D( u2, v1 + v ) },
		};

		Push( VtxTex, 2 );
	}
}

