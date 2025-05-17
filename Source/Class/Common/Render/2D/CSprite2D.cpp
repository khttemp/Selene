

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Math/Math.h"
#include "Math/Vector2D.h"
#include "Math/Vector4D.h"
#include "Math/Matrix.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Render/2D/CSprite2D.h"
#include "Class/Platform/Surface/CTexture.h"


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
CSprite2D::CSprite2D( CRender *pRender, CRenderObjectMgr *pMgr, ITexture *pTexture, Bool IsFiltering, Bool IsOffset ) : CPrimitive2D( pRender, pMgr )
	, m_IsFiltering		( IsFiltering )
	, m_IsOffset		( IsOffset )
{
	SetName( "2Dスプライト" );

	if ( (pTexture != NULL) && pTexture->IsInvalid() )
	{
		pTexture = NULL;
	}

	m_pTexture[0] = pTexture;
	m_pTexture[1] = NULL;

	if ( m_pTexture[0] != NULL )
	{
		m_pTexture[0]->AddRef();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSprite2D::~CSprite2D()
{
	SAFE_RELEASE( m_pTexture[0] )
	SAFE_RELEASE( m_pTexture[1] )
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::Rendering( void )
{
	// フィルタ
	if ( m_IsFiltering )
	{
		m_pRender->SetTextureFilterType( TEXTURE_STAGE_COLOR, TEXTURE_FILTER_2D );
		m_pRender->SetTextureFilterType( TEXTURE_STAGE_LIGHT, TEXTURE_FILTER_2D );
	}
	else
	{
		m_pRender->SetTextureFilterType( TEXTURE_STAGE_COLOR, TEXTURE_FILTER_DISABLE );
		m_pRender->SetTextureFilterType( TEXTURE_STAGE_LIGHT, TEXTURE_FILTER_2D );
	}

	// テクスチャをデバイスに設定
	m_pRender->SetTexture( TEXTURE_STAGE_COLOR, m_pTexture[0] );
	m_pRender->SetTexture( TEXTURE_STAGE_LIGHT, m_pTexture[1] );

	// プリミティブレンダリング
	m_pRender->ResetShader();
	m_pRender->Start2D( m_pTexture[1] != NULL );
	CPrimitive2D::RenderingNoStateChange();

}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::SetDecoration( ITexture *pTex )
{
	SAFE_RELEASE( m_pTexture[1] );

	if ( (pTex != NULL) && !pTex->IsInvalid() )
	{
		m_pTexture[1] = pTex;
		m_pTexture[1]->AddRef();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::Begin( void )
{
	CPrimitive2D::Begin();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::End( void )
{
	CPrimitive2D::End();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSprite2D::Push( SPrimitiveVertex2D *pPrimitive, Sint32 Count )
{
	return CPrimitive2D::Push( pPrimitive, Count );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CSprite2D::GetRequestedVertexCount( void )
{
	return CPrimitive2D::GetRequestedVertexCount();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CSprite2D::GetRequestedVertexCountMax( void )
{
	return CPrimitive2D::GetRequestedVertexCountMax();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::DrawSquare( Math::Rect2DF &DstRect, Math::Rect2DF &SrcRect, CColor Color )
{
	Float fOffset = (m_IsFiltering && m_IsOffset) ? 0.5f : 0.0f;

	// 描画座標
	Float x1 = DstRect.x;
	Float y1 = DstRect.y;
	Float x2 = x1 + DstRect.w;
	Float y2 = y1 + DstRect.h;

	Float u1, v1, u2, v2;

	// ＵＶ変換
	if ( m_pTexture[0] != NULL )
	{
		Math::Point2DF vTransform = m_pTexture[0]->GetPixelToTexelTransform();
		u1 = (SrcRect.x             + fOffset) * vTransform.x;
		v1 = (SrcRect.y             + fOffset) * vTransform.y;
		u2 = (SrcRect.x + SrcRect.w - fOffset) * vTransform.x;
		v2 = (SrcRect.y + SrcRect.h - fOffset) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	// 頂点データ
	static SPrimitiveVertex2D Primitive[] = {
		{
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(0.0f,0.0f) },
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(1.0f,0.0f) },
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(1.0f,1.0f) },
		},
		{
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(1.0f,1.0f) },
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(0.0f,1.0f) },
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(0.0f,0.0f) },
		},
	};

	// 位置
	Primitive[0].v1.Pos.x = x1;					Primitive[0].v1.Pos.y = y1;
	Primitive[0].v2.Pos.x = x2;					Primitive[0].v2.Pos.y = y1;
	Primitive[0].v3.Pos.x = x2;					Primitive[0].v3.Pos.y = y2;

	Primitive[1].v1.Pos.x = x2;					Primitive[1].v1.Pos.y = y2;
	Primitive[1].v2.Pos.x = x1;					Primitive[1].v2.Pos.y = y2;
	Primitive[1].v3.Pos.x = x1;					Primitive[1].v3.Pos.y = y1;

	// 色
	Primitive[0].v1.Col = Color;
	Primitive[0].v2.Col = Color;
	Primitive[0].v3.Col = Color;

	Primitive[1].v1.Col = Color;
	Primitive[1].v2.Col = Color;
	Primitive[1].v3.Col = Color;

	// UV
	Primitive[0].v1.Tex[0].x = u1;			Primitive[0].v1.Tex[0].y = v1;
	Primitive[0].v2.Tex[0].x = u2;			Primitive[0].v2.Tex[0].y = v1;
	Primitive[0].v3.Tex[0].x = u2;			Primitive[0].v3.Tex[0].y = v2;

	Primitive[1].v1.Tex[0].x = u2;			Primitive[1].v1.Tex[0].y = v2;
	Primitive[1].v2.Tex[0].x = u1;			Primitive[1].v2.Tex[0].y = v2;
	Primitive[1].v3.Tex[0].x = u1;			Primitive[1].v3.Tex[0].y = v1;

	// プリミティブに追加
	Push( Primitive, 2 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::DrawSquareRotate( Math::Rect2DF &DstRect, Math::Rect2DF &SrcRect, CColor Color, Sint32 Angle )
{
	Float fOffset = (m_IsFiltering && m_IsOffset) ? 0.5f : 0.0f;

	// 描画先
	Float x1 = DstRect.x;
	Float y1 = DstRect.y;
	Float x2 = DstRect.x + DstRect.w;
	Float y2 = DstRect.y + DstRect.h;

	Float u1, v1, u2, v2;

	// 中心
	Math::Vector3D Center( (x1 + x2) * 0.5f, (y1 + y2) * 0.5f, 0.0f );

	// 回転
	Math::Vector3D Pt[4] = {
		Math::Vector3D( x1, y1, 0.0f ), Math::Vector3D( x2, y1, 0.0f ),
		Math::Vector3D( x1, y2, 0.0f ), Math::Vector3D( x2, y2, 0.0f ),
	};

	for ( Sint32 i = 0; i < 4; i++ )
	{
		Pt[i] -= Center;
		Pt[i].RotationZ( Angle );
		Pt[i] += Center;
	}

	// ＵＶ変換
	if ( m_pTexture[0] != NULL )
	{
		Math::Point2DF vTransform = m_pTexture[0]->GetPixelToTexelTransform();
		u1 = (SrcRect.x             + fOffset) * vTransform.x;
		v1 = (SrcRect.y             + fOffset) * vTransform.y;
		u2 = (SrcRect.x + SrcRect.w - fOffset) * vTransform.x;
		v2 = (SrcRect.y + SrcRect.h - fOffset) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	// 頂点データ
	static SPrimitiveVertex2D Primitive[] = {
		{
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(0.0f,0.0f) },
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(1.0f,0.0f) },
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(1.0f,1.0f) },
		},
		{
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(1.0f,1.0f) },
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(0.0f,1.0f) },
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(0.0f,0.0f) },
		},
	};

	// 位置
	Primitive[0].v1.Pos.x = Pt[0].x;					Primitive[0].v1.Pos.y = Pt[0].y;
	Primitive[0].v2.Pos.x = Pt[1].x;					Primitive[0].v2.Pos.y = Pt[1].y;
	Primitive[0].v3.Pos.x = Pt[3].x;					Primitive[0].v3.Pos.y = Pt[3].y;

	Primitive[1].v1.Pos.x = Pt[3].x;					Primitive[1].v1.Pos.y = Pt[3].y;
	Primitive[1].v2.Pos.x = Pt[2].x;					Primitive[1].v2.Pos.y = Pt[2].y;
	Primitive[1].v3.Pos.x = Pt[0].x;					Primitive[1].v3.Pos.y = Pt[0].y;

	// 色
	Primitive[0].v1.Col = Color;
	Primitive[0].v2.Col = Color;
	Primitive[0].v3.Col = Color;

	Primitive[1].v1.Col = Color;
	Primitive[1].v2.Col = Color;
	Primitive[1].v3.Col = Color;

	// UV
	Primitive[0].v1.Tex[0].x = u1;			Primitive[0].v1.Tex[0].y = v1;
	Primitive[0].v2.Tex[0].x = u2;			Primitive[0].v2.Tex[0].y = v1;
	Primitive[0].v3.Tex[0].x = u2;			Primitive[0].v3.Tex[0].y = v2;

	Primitive[1].v1.Tex[0].x = u2;			Primitive[1].v1.Tex[0].y = v2;
	Primitive[1].v2.Tex[0].x = u1;			Primitive[1].v2.Tex[0].y = v2;
	Primitive[1].v3.Tex[0].x = u1;			Primitive[1].v3.Tex[0].y = v1;

	// プリミティブに追加
	Push( Primitive, 2 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::DrawSquareRotateXYZ( Math::Rect2DF &DstRect, Math::Rect2DF &SrcRect, CColor Color, Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ )
{
	Float fOffset = (m_IsFiltering && m_IsOffset) ? 0.5f : 0.0f;

	// 描画先
	Float x1 = DstRect.x;
	Float y1 = DstRect.y;
	Float x2 = DstRect.x + DstRect.w;
	Float y2 = DstRect.y + DstRect.h;

	Float u1, v1, u2, v2;

	// 回転行列
	Math::Matrix mWorld;
	mWorld.RotationZXY( AngleX, AngleY, AngleZ );

	// 中心
	Math::Vector3D Center( (x1 + x2) * 0.5f, (y1 + y2) * 0.5f, 0.0f );

	// 回転
	Math::Vector3D Pt[4] = {
		Math::Vector3D( x1, y1, 0.0f ), Math::Vector3D( x2, y1, 0.0f ),
		Math::Vector3D( x1, y2, 0.0f ), Math::Vector3D( x2, y2, 0.0f ),
	};

	for ( Sint32 i = 0; i < 4; i++ )
	{
		Pt[i] -= Center;
		Pt[i].TransformCoord( mWorld );
		Pt[i] += Center;
	}

	// ＵＶ変換
	if ( m_pTexture[0] != NULL )
	{
		Math::Point2DF vTransform = m_pTexture[0]->GetPixelToTexelTransform();
		u1 = (SrcRect.x             + fOffset) * vTransform.x;
		v1 = (SrcRect.y             + fOffset) * vTransform.y;
		u2 = (SrcRect.x + SrcRect.w - fOffset) * vTransform.x;
		v2 = (SrcRect.y + SrcRect.h - fOffset) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	// 頂点データ
	static SPrimitiveVertex2D Primitive[] = {
		{
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(0.0f,0.0f) },
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(1.0f,0.0f) },
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(1.0f,1.0f) },
		},
		{
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(1.0f,1.0f) },
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(0.0f,1.0f) },
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(0.0f,0.0f) },
		},
	};

	// 位置
	Primitive[0].v1.Pos.x = Pt[0].x;					Primitive[0].v1.Pos.y = Pt[0].y;
	Primitive[0].v2.Pos.x = Pt[1].x;					Primitive[0].v2.Pos.y = Pt[1].y;
	Primitive[0].v3.Pos.x = Pt[3].x;					Primitive[0].v3.Pos.y = Pt[3].y;

	Primitive[1].v1.Pos.x = Pt[3].x;					Primitive[1].v1.Pos.y = Pt[3].y;
	Primitive[1].v2.Pos.x = Pt[2].x;					Primitive[1].v2.Pos.y = Pt[2].y;
	Primitive[1].v3.Pos.x = Pt[0].x;					Primitive[1].v3.Pos.y = Pt[0].y;

	// 色
	Primitive[0].v1.Col = Color;
	Primitive[0].v2.Col = Color;
	Primitive[0].v3.Col = Color;

	Primitive[1].v1.Col = Color;
	Primitive[1].v2.Col = Color;
	Primitive[1].v3.Col = Color;

	// UV
	Primitive[0].v1.Tex[0].x = u1;			Primitive[0].v1.Tex[0].y = v1;
	Primitive[0].v2.Tex[0].x = u2;			Primitive[0].v2.Tex[0].y = v1;
	Primitive[0].v3.Tex[0].x = u2;			Primitive[0].v3.Tex[0].y = v2;

	Primitive[1].v1.Tex[0].x = u2;			Primitive[1].v1.Tex[0].y = v2;
	Primitive[1].v2.Tex[0].x = u1;			Primitive[1].v2.Tex[0].y = v2;
	Primitive[1].v3.Tex[0].x = u1;			Primitive[1].v3.Tex[0].y = v1;

	// プリミティブに追加
	Push( Primitive, 2 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::DrawSquareMatrix( Math::Matrix &mWorld, Math::Rect2DF &SrcRect, CColor Color )
{
	Float fOffset = (m_IsFiltering && m_IsOffset) ? 0.5f : 0.0f;

	Float x1 = -SrcRect.w / 2.0f;
	Float y1 = -SrcRect.h / 2.0f;
	Float x2 = +SrcRect.w / 2.0f;
	Float y2 = +SrcRect.h / 2.0f;

	Float u1, v1, u2, v2;

	// 中心
	Math::Vector3D Center( (x1 + x2) * 0.5f, (y1 + y2) * 0.5f, 0.0f );

	// 回転
	Math::Vector3D Pt[4] = {
		Math::Vector3D( x1, y1, 0.0f ), Math::Vector3D( x2, y1, 0.0f ),
		Math::Vector3D( x1, y2, 0.0f ), Math::Vector3D( x2, y2, 0.0f ),
	};

	for ( Sint32 i = 0; i < 4; i++ )
	{
		Pt[i] -= Center;
		Pt[i].TransformCoord( mWorld );
		Pt[i] += Center;
	}

	// ＵＶ変換
	if ( m_pTexture[0] != NULL )
	{
		Math::Point2DF vTransform = m_pTexture[0]->GetPixelToTexelTransform();
		u1 = (SrcRect.x             + fOffset) * vTransform.x;
		v1 = (SrcRect.y             + fOffset) * vTransform.y;
		u2 = (SrcRect.x + SrcRect.w - fOffset) * vTransform.x;
		v2 = (SrcRect.y + SrcRect.h - fOffset) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	// 頂点データ
	static SPrimitiveVertex2D Primitive[] = {
		{
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(0.0f,0.0f) },
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(1.0f,0.0f) },
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(1.0f,1.0f) },
		},
		{
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(1.0f,1.0f) },
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(0.0f,1.0f) },
			{ Math::Vector4D(0.0f,0.0f,0.0f,1.0f), 0xFFFFFFFF, Math::Vector2D(0.0f,0.0f), Math::Vector2D(0.0f,0.0f) },
		},
	};

	// 位置
	Primitive[0].v1.Pos.x = Pt[0].x;					Primitive[0].v1.Pos.y = Pt[0].y;
	Primitive[0].v2.Pos.x = Pt[1].x;					Primitive[0].v2.Pos.y = Pt[1].y;
	Primitive[0].v3.Pos.x = Pt[3].x;					Primitive[0].v3.Pos.y = Pt[3].y;

	Primitive[1].v1.Pos.x = Pt[3].x;					Primitive[1].v1.Pos.y = Pt[3].y;
	Primitive[1].v2.Pos.x = Pt[2].x;					Primitive[1].v2.Pos.y = Pt[2].y;
	Primitive[1].v3.Pos.x = Pt[0].x;					Primitive[1].v3.Pos.y = Pt[0].y;

	// 色
	Primitive[0].v1.Col = Color;
	Primitive[0].v2.Col = Color;
	Primitive[0].v3.Col = Color;

	Primitive[1].v1.Col = Color;
	Primitive[1].v2.Col = Color;
	Primitive[1].v3.Col = Color;

	// UV
	Primitive[0].v1.Tex[0].x = u1;			Primitive[0].v1.Tex[0].y = v1;
	Primitive[0].v2.Tex[0].x = u2;			Primitive[0].v2.Tex[0].y = v1;
	Primitive[0].v3.Tex[0].x = u2;			Primitive[0].v3.Tex[0].y = v2;

	Primitive[1].v1.Tex[0].x = u2;			Primitive[1].v1.Tex[0].y = v2;
	Primitive[1].v2.Tex[0].x = u1;			Primitive[1].v2.Tex[0].y = v2;
	Primitive[1].v3.Tex[0].x = u1;			Primitive[1].v3.Tex[0].y = v1;

	// プリミティブに追加
	Push( Primitive, 2 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::DrawList( Math::Point2DF Pos[], Sint32 Angle[], CColor Color[], Sint32 Count, Float Width, Math::Rect2DF &Src )
{
	Float fOffset = (m_IsFiltering && m_IsOffset) ? 0.5f : 0.0f;

	Float u1, v1, u2, v2;

	// ＵＶ変換
	if ( m_pTexture[0] != NULL )
	{
		Math::Point2DF vTransform = m_pTexture[0]->GetPixelToTexelTransform();
		u1 = (Src.x         + fOffset) * vTransform.x;
		v1 = (Src.y         + fOffset) * vTransform.y;
		u2 = (Src.x + Src.w - fOffset) * vTransform.x;
		v2 = (Src.y + Src.h - fOffset) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	// 頂点データ生成
	for ( Sint32 i = 0; i < Count - 1; i++ )
	{
		Math::Vector2D Pt1 = Math::Vector2D( 0, Width );
		Math::Vector2D Pt2 = Math::Vector2D( 0, Width );

		Pt1.RotationZ( Angle[i+0] );
		Pt2.RotationZ( Angle[i+1] );

		Float x[] = {
			Pos[i+0].x - Pt1.x,
			Pos[i+0].x + Pt1.x,
			Pos[i+1].x - Pt2.x,
			Pos[i+1].x + Pt2.x,
		};

		Float y[] = {
			Pos[i+0].y - Pt1.y,
			Pos[i+0].y + Pt1.y,
			Pos[i+1].y - Pt2.y,
			Pos[i+1].y + Pt2.y,
		};

		Float u[] = {
			u1,
			u2
		};
		Float v[] = {
			v1 + ((v2 - v1) * toF(i+0) / toF(Count - 1)),
			v1 + ((v2 - v1) * toF(i+1) / toF(Count - 1))
		};

		SPrimitiveVertex2D Primitive[] = {
			{
				{ Math::Vector4D( x[0], y[0], 0.0f, 1.0f ), Color[i+0], Math::Vector2D( u[0], v[0] ), Math::Vector2D( 0.0f, 0.0f ) },
				{ Math::Vector4D( x[1], y[1], 0.0f, 1.0f ), Color[i+0], Math::Vector2D( u[1], v[0] ), Math::Vector2D( 1.0f, 0.0f ) },
				{ Math::Vector4D( x[2], y[2], 0.0f, 1.0f ), Color[i+1], Math::Vector2D( u[0], v[1] ), Math::Vector2D( 0.0f, 1.0f ) },
			},
			{
				{ Math::Vector4D( x[2], y[2], 0.0f, 1.0f ), Color[i+1], Math::Vector2D( u[0], v[1] ), Math::Vector2D( 0.0f, 1.0f ) },
				{ Math::Vector4D( x[3], y[3], 0.0f, 1.0f ), Color[i+1], Math::Vector2D( u[1], v[1] ), Math::Vector2D( 1.0f, 1.0f ) },
				{ Math::Vector4D( x[1], y[1], 0.0f, 1.0f ), Color[i+0], Math::Vector2D( u[1], v[0] ), Math::Vector2D( 1.0f, 0.0f ) },
			}
		};

		// プリミティブに追加
		Push( Primitive, 2 );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::DrawList( Math::Point2DF Pos[], Float Width[], Sint32 Angle[], CColor Color[], Sint32 Count, Math::Rect2DF &Src )
{
	Float fOffset = (m_IsFiltering && m_IsOffset) ? 0.5f : 0.0f;

	Float u1, v1, u2, v2;

	// ＵＶ変換
	if ( m_pTexture[0] != NULL )
	{
		Math::Point2DF vTransform = m_pTexture[0]->GetPixelToTexelTransform();
		u1 = (Src.x         + fOffset) * vTransform.x;
		v1 = (Src.y         + fOffset) * vTransform.y;
		u2 = (Src.x + Src.w - fOffset) * vTransform.x;
		v2 = (Src.y + Src.h - fOffset) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	// 頂点データ生成
	for ( Sint32 i = 0; i < Count - 1; i++ )
	{
		Math::Vector2D Pt1 = Math::Vector2D( 0, Width[i+0] );
		Math::Vector2D Pt2 = Math::Vector2D( 0, Width[i+1] );

		Pt1.RotationZ( Angle[i+0] );
		Pt2.RotationZ( Angle[i+1] );

		Float x[] = {
			Pos[i+0].x - Pt1.x,
			Pos[i+0].x + Pt1.x,
			Pos[i+1].x - Pt2.x,
			Pos[i+1].x + Pt2.x,
		};

		Float y[] = {
			Pos[i+0].y - Pt1.y,
			Pos[i+0].y + Pt1.y,
			Pos[i+1].y - Pt2.y,
			Pos[i+1].y + Pt2.y,
		};

		Float u[] = {
			u1,
			u2
		};
		Float v[] = {
			v1 + ((v2 - v1) * toF(i+0) / toF(Count - 1)),
			v1 + ((v2 - v1) * toF(i+1) / toF(Count - 1))
		};

		SPrimitiveVertex2D Primitive[] = {
			{
				{ Math::Vector4D( x[0], y[0], 0.0f, 1.0f ), Color[i+0], Math::Vector2D( u[0], v[0] ), Math::Vector2D( 0.0f, 0.0f ) },
				{ Math::Vector4D( x[1], y[1], 0.0f, 1.0f ), Color[i+0], Math::Vector2D( u[1], v[0] ), Math::Vector2D( 1.0f, 0.0f ) },
				{ Math::Vector4D( x[2], y[2], 0.0f, 1.0f ), Color[i+1], Math::Vector2D( u[0], v[1] ), Math::Vector2D( 0.0f, 1.0f ) },
			},
			{
				{ Math::Vector4D( x[2], y[2], 0.0f, 1.0f ), Color[i+1], Math::Vector2D( u[0], v[1] ), Math::Vector2D( 0.0f, 1.0f ) },
				{ Math::Vector4D( x[3], y[3], 0.0f, 1.0f ), Color[i+1], Math::Vector2D( u[1], v[1] ), Math::Vector2D( 1.0f, 1.0f ) },
				{ Math::Vector4D( x[1], y[1], 0.0f, 1.0f ), Color[i+0], Math::Vector2D( u[1], v[0] ), Math::Vector2D( 1.0f, 0.0f ) },
			}
		};

		// プリミティブに追加
		Push( Primitive, 2 );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::DrawList( SSpriteListData2D List[], Sint32 Count, Math::Rect2DF &Src )
{
	Float fOffset = (m_IsFiltering && m_IsOffset) ? 0.5f : 0.0f;

	Float u1, v1, u2, v2;

	// ＵＶ変換
	if ( m_pTexture[0] != NULL )
	{
		Math::Point2DF vTransform = m_pTexture[0]->GetPixelToTexelTransform();
		u1 = (Src.x         + fOffset) * vTransform.x;
		v1 = (Src.y         + fOffset) * vTransform.y;
		u2 = (Src.x + Src.w - fOffset) * vTransform.x;
		v2 = (Src.y + Src.h - fOffset) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	// 頂点データ生成
	for ( Sint32 i = 0; i < Count - 1; i++ )
	{
		Math::Vector2D Pt1 = Math::Vector2D( 0, List[i+0].Width );
		Math::Vector2D Pt2 = Math::Vector2D( 0, List[i+1].Width );

		Pt1.RotationZ( List[i+0].Angle );
		Pt2.RotationZ( List[i+1].Angle );

		Float x[] = {
			List[i+0].Pos.x - Pt1.x,
			List[i+0].Pos.x + Pt1.x,
			List[i+1].Pos.x - Pt2.x,
			List[i+1].Pos.x + Pt2.x,
		};

		Float y[] = {
			List[i+0].Pos.y - Pt1.y,
			List[i+0].Pos.y + Pt1.y,
			List[i+1].Pos.y - Pt2.y,
			List[i+1].Pos.y + Pt2.y,
		};

		Float u[] = {
			u1,
			u2
		};
		Float v[] = {
			v1 + ((v2 - v1) * toF(i+0) / toF(Count - 1)),
			v1 + ((v2 - v1) * toF(i+1) / toF(Count - 1))
		};

		SPrimitiveVertex2D Primitive[] = {
			{
				{ Math::Vector4D( x[0], y[0], 0.0f, 1.0f ), List[i+0].Color, Math::Vector2D( u[0], v[0] ), Math::Vector2D( 0.0f, 0.0f ) },
				{ Math::Vector4D( x[1], y[1], 0.0f, 1.0f ), List[i+0].Color, Math::Vector2D( u[1], v[0] ), Math::Vector2D( 1.0f, 0.0f ) },
				{ Math::Vector4D( x[2], y[2], 0.0f, 1.0f ), List[i+1].Color, Math::Vector2D( u[0], v[1] ), Math::Vector2D( 0.0f, 1.0f ) },
			},
			{
				{ Math::Vector4D( x[2], y[2], 0.0f, 1.0f ), List[i+1].Color, Math::Vector2D( u[0], v[1] ), Math::Vector2D( 0.0f, 1.0f ) },
				{ Math::Vector4D( x[3], y[3], 0.0f, 1.0f ), List[i+1].Color, Math::Vector2D( u[1], v[1] ), Math::Vector2D( 1.0f, 1.0f ) },
				{ Math::Vector4D( x[1], y[1], 0.0f, 1.0f ), List[i+0].Color, Math::Vector2D( u[1], v[0] ), Math::Vector2D( 1.0f, 0.0f ) },
			}
		};

		// プリミティブに追加
		Push( Primitive, 2 );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::CircleFade( Math::Rect2DF &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha )
{
	Float fOffset = (m_IsFiltering && m_IsOffset) ? 0.5f : 0.0f;

	Float fRange;
	Sint32 w, h, cx, cy;

	Float u1, v1, u2, v2;

	// 画面サイズ取得
	m_pCore->GetScreenData( &w, &h, NULL );
	cx = w / 2;
	cy = h / 2;

	Float fW = 1.0f / toF(w);
	Float fH = 1.0f / toF(h);

	fRange = FastSqrt( toF((cx * cx) + (cy * cy)) ) * 1.1f;

	// テクスチャ情報
	if ( m_pTexture[0] != NULL )
	{
		Math::Point2DF vTransform = m_pTexture[0]->GetPixelToTexelTransform();
		u1 = (SrcRect.x             + fOffset) * vTransform.x;
		v1 = (SrcRect.y             + fOffset) * vTransform.y;
		u2 = (SrcRect.x + SrcRect.w - fOffset) * vTransform.x;
		v2 = (SrcRect.y + SrcRect.h - fOffset) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	// 円状に展開
	for ( Sint32 i = 0; i < Side; i++ )
	{
		Sint32 alpha0 = 255 - (255 * (i + 0) / Side) + Alpha;
		Sint32 alpha1 = 255 - (255 * (i + 1) / Side) + Alpha;
		Float fIn  = toF(i + 0) * fRange / toF(Side);
		Float fOut = toF(i + 1) * fRange / toF(Side);

		if ( alpha0 <   0 ) alpha0 =   0;
		if ( alpha0 > 255 ) alpha0 = 255;

		if ( alpha1 <   0 ) alpha1 =   0;
		if ( alpha1 > 255 ) alpha1 = 255;

		for ( Sint32 j = 0; j < Divide; j++ )
		{
			Sint32 angle0 = (j + 0) * ANGLE_MAX / Divide;
			Sint32 angle1 = (j + 1) * ANGLE_MAX / Divide;

			Float x0 = cx + Math::Cos( angle0 ) * fOut;
			Float y0 = cy + Math::Sin( angle0 ) * fOut;
			Float x1 = cx + Math::Cos( angle1 ) * fOut;
			Float y1 = cy + Math::Sin( angle1 ) * fOut;
			Float x2 = cx + Math::Cos( angle1 ) * fIn;
			Float y2 = cy + Math::Sin( angle1 ) * fIn;
			Float x3 = cx + Math::Cos( angle0 ) * fIn;
			Float y3 = cy + Math::Sin( angle0 ) * fIn;

			CColor Col0( 255, 255, 255, (Uint8)alpha0 );
			CColor Col1( 255, 255, 255, (Uint8)alpha1 );

			SPrimitiveVertex2D Vtx[] = {
				{
					{ Math::Vector4D(x0, y0, 0.0f, 1.0f), Col1, Math::Vector2D(u1 + (u2 * x0 * fW), v1 + (v2 * y0 * fH)) },
					{ Math::Vector4D(x1, y1, 0.0f, 1.0f), Col1, Math::Vector2D(u1 + (u2 * x1 * fW), v1 + (v2 * y1 * fH)) },
					{ Math::Vector4D(x2, y2, 0.0f, 1.0f), Col0, Math::Vector2D(u1 + (u2 * x2 * fW), v1 + (v2 * y2 * fH)) },
				},
				{
					{ Math::Vector4D(x2, y2, 0.0f, 1.0f), Col0, Math::Vector2D(u1 + (u2 * x2 * fW), v1 + (v2 * y2 * fH)) },
					{ Math::Vector4D(x3, y3, 0.0f, 1.0f), Col0, Math::Vector2D(u1 + (u2 * x3 * fW), v1 + (v2 * y3 * fH)) },
					{ Math::Vector4D(x0, y0, 0.0f, 1.0f), Col1, Math::Vector2D(u1 + (u2 * x0 * fW), v1 + (v2 * y0 * fH)) },
				},
			};

			// プリミティブに追加
			Push( Vtx, 2 );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSprite2D::CircleRoundFade( Math::Rect2DF &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha )
{
	Float fOffset = (m_IsFiltering && m_IsOffset) ? 0.5f : 0.0f;

	Float fRange;
	Sint32 w, h, cx, cy;

	Float u1, v1, u2, v2;

	// 画面サイズ取得
	m_pCore->GetScreenData( &w, &h, NULL );
	cx = w / 2;
	cy = h / 2;

	Float fW = 1.0f / toF(w);
	Float fH = 1.0f / toF(h);

	fRange = FastSqrt( toF((cx * cx) + (cy * cy)) ) * 1.1f;

	// テクスチャ情報
	if ( m_pTexture[0] != NULL )
	{
		Math::Point2DF vTransform = m_pTexture[0]->GetPixelToTexelTransform();
		u1 = (SrcRect.x             + fOffset) * vTransform.x;
		v1 = (SrcRect.y             + fOffset) * vTransform.y;
		u2 = (SrcRect.x + SrcRect.w - fOffset) * vTransform.x;
		v2 = (SrcRect.y + SrcRect.h - fOffset) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2 = 0.0f;
	}

	// 円状に展開
	for ( Sint32 i = 0; i < Side; i++ )
	{
		Float fIn  = toF(i + 0) * fRange / toF(Side);
		Float fOut = toF(i + 1) * fRange / toF(Side);

		for ( Sint32 j = 0; j < Divide; j++ )
		{
			Sint32 alpha0 = 255 - (255 * (j + 0) / Divide) + Alpha;
			Sint32 alpha1 = 255 - (255 * (j + 1) / Divide) + Alpha;

			if ( alpha0 <   0 ) alpha0 =   0;
			if ( alpha0 > 255 ) alpha0 = 255;

			if ( alpha1 <   0 ) alpha1 =   0;
			if ( alpha1 > 255 ) alpha1 = 255;

			Sint32 angle0 = ((j + 0) * ANGLE_MAX / Divide) - (ANGLE_MAX / 4);
			Sint32 angle1 = ((j + 1) * ANGLE_MAX / Divide) - (ANGLE_MAX / 4);

			Float x0 = cx + Math::Cos( angle0 ) * fOut;
			Float y0 = cy + Math::Sin( angle0 ) * fOut;
			Float x1 = cx + Math::Cos( angle1 ) * fOut;
			Float y1 = cy + Math::Sin( angle1 ) * fOut;
			Float x2 = cx + Math::Cos( angle1 ) * fIn;
			Float y2 = cy + Math::Sin( angle1 ) * fIn;
			Float x3 = cx + Math::Cos( angle0 ) * fIn;
			Float y3 = cy + Math::Sin( angle0 ) * fIn;

			CColor Col0( 255, 255, 255, (Uint8)alpha0 );
			CColor Col1( 255, 255, 255, (Uint8)alpha1 );

			SPrimitiveVertex2D Vtx[] = {
				{
					{ Math::Vector4D(x0, y0, 0.0f, 1.0f), Col0, Math::Vector2D(u1 + (u2 * x0 * fW), v1 + (v2 * y0 * fH)) },
					{ Math::Vector4D(x1, y1, 0.0f, 1.0f), Col1, Math::Vector2D(u1 + (u2 * x1 * fW), v1 + (v2 * y1 * fH)) },
					{ Math::Vector4D(x2, y2, 0.0f, 1.0f), Col1, Math::Vector2D(u1 + (u2 * x2 * fW), v1 + (v2 * y2 * fH)) },
				},
				{
					{ Math::Vector4D(x2, y2, 0.0f, 1.0f), Col1, Math::Vector2D(u1 + (u2 * x2 * fW), v1 + (v2 * y2 * fH)) },
					{ Math::Vector4D(x3, y3, 0.0f, 1.0f), Col0, Math::Vector2D(u1 + (u2 * x3 * fW), v1 + (v2 * y3 * fH)) },
					{ Math::Vector4D(x0, y0, 0.0f, 1.0f), Col0, Math::Vector2D(u1 + (u2 * x0 * fW), v1 + (v2 * y0 * fH)) },
				},
			};

			// プリミティブに追加
			Push( Vtx, 2 );
		}
	}
}

