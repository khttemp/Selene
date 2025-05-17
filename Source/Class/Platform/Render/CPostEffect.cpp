

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Core/CCore.h"
#include "Class/Platform/Core/CGraphicCard.h"
#include "Class/Platform/Render/CPostEffect.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CVertexLayout.h"
#include "Class/Platform/Render/Shader/CShader.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Surface/CTexture.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPostEffect::CPostEffect( CRender *pRender, void *pShader, long Size )
	: m_pRender			( pRender )
	, m_pShader			( NULL )
	, m_pVS_PostEffect	( NULL )
	, m_pVB_PostEffect	( NULL )
{
	//------------------------------------------------------------------
	// エフェクト用シェーダー
	//------------------------------------------------------------------
	m_pShader = pRender->CreateShaderFromMemory( pShader, Size, true );
	if ( m_pShader == NULL ) return;

	m_hTech_Simple					= m_pShader->GetTechnique( "TECH_Simple" );
	m_hTech_DownSample				= m_pShader->GetTechnique( "TECH_DownSample" );
	m_hTech_HDR_DownSample			= m_pShader->GetTechnique( "TECH_HDR_DownSample" );
	m_hTech_HDR_BloomFx				= m_pShader->GetTechnique( "TECH_HDR_BloomFx" );
	m_hTech_HDR_CrossFx				= m_pShader->GetTechnique( "TECH_HDR_CrossFx" );
	m_hTech_DOF_Blur				= m_pShader->GetTechnique( "TECH_DOF_Blur" );
	m_hTech_MSAA					= m_pShader->GetTechnique( "TECH_MSAA" );
	m_hTech_Velocity_High			= m_pShader->GetTechnique( "TECH_Velocity_High" );
	m_hTech_Velocity_Low			= m_pShader->GetTechnique( "TECH_Velocity_Low" );
	m_hTech_NormalDepthEdge			= m_pShader->GetTechnique( "TECH_NormalDepthEdge" );
	m_hTech_ShowAlpha				= m_pShader->GetTechnique( "TECH_SHOW_ALPHA" );
	m_hTech_Gaussian				= m_pShader->GetTechnique( "TECH_GAUSSIAN" );

	m_hDOF_PARAMETER				= m_pShader->GetParameterBySemantic( "DOF_PARAMETER" );
	m_hBLEND_RATE					= m_pShader->GetParameterBySemantic( "BLEND_RATE" );
	m_hBLUR_OFFSET					= m_pShader->GetParameterBySemantic( "BLUR_OFFSET" );
	m_hHDR_POWER					= m_pShader->GetParameterBySemantic( "HDR_POWER" );
	m_hHDR_BOUNDARY					= m_pShader->GetParameterBySemantic( "HDR_BOUNDARY" );
	m_hEDGE_POWER					= m_pShader->GetParameterBySemantic( "EDGE_POWER" );
	m_hOFFSET						= m_pShader->GetParameterBySemantic( "OFFSET" );

	m_hTEXTURE[0]					= m_pShader->GetParameterBySemantic( "TEXTURE0" );
	m_hTEXTURE[1]					= m_pShader->GetParameterBySemantic( "TEXTURE1" );
	m_hTEXTURE[2]					= m_pShader->GetParameterBySemantic( "TEXTURE2" );
	m_hTEXTURE[3]					= m_pShader->GetParameterBySemantic( "TEXTURE3" );
	m_hTEXTURE[4]					= m_pShader->GetParameterBySemantic( "TEXTURE4" );
	m_hTEXTURE[5]					= m_pShader->GetParameterBySemantic( "TEXTURE5" );
	m_hTEXTURE[6]					= m_pShader->GetParameterBySemantic( "TEXTURE6" );
	m_hTEXTURE[7]					= m_pShader->GetParameterBySemantic( "TEXTURE7" );

	//------------------------------------------------------------------
	// マルチテクスチャ用
	//------------------------------------------------------------------
	m_pVB_PostEffect = pRender->CreateVertexBuffer( 4, sizeof(SVertexPostEffect), true );
	m_pVS_PostEffect = pRender->CreateVertexStream( VERTEX_ELEMENT_POSTEFFECT );

	//------------------------------------------------------------------
	// ガウス用テーブル
	//------------------------------------------------------------------
	Float fAll = 0.0f;

	for ( Sint32 i = 0; i <= 16; i++ )
    {
		Float fRate = toF(i - 8) / 8.0f;

		Float fTemp1 = 1.0f / sqrtf( PI2 );
		Float fTemp2 = expf( -(fRate * fRate) / 2.0f );

		m_vOffset[i].x = 0.0f;
		m_vOffset[i].y = 0.0f;
		m_vOffset[i].z = fTemp1 * fTemp2;
		m_vOffset[i].w = 0.0f;

		fAll += m_vOffset[i].z;
    }

	for ( Sint32 i = 0; i <= 16; i++ )
    {
		m_vOffset[i].z /= fAll;
    }
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPostEffect::~CPostEffect()
{
	SAFE_RELEASE( m_pVS_PostEffect );
	SAFE_RELEASE( m_pVB_PostEffect );
	SAFE_RELEASE( m_pShader );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::Simple( const Math::Rect2DI &Dst, ITexture *pTex )
{
	//--------------------------------------------------------
	// 頂点更新
	//--------------------------------------------------------
	SVertexPostEffect Vtx[4] = {
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
	};

	//--------------------------------------------------------
	// テクスチャUV更新
	//--------------------------------------------------------
	Vtx[0].Tex[0] = Math::Vector2D( 0.0f, 0.0f );
	Vtx[1].Tex[0] = Math::Vector2D( 1.0f, 0.0f );
	Vtx[2].Tex[0] = Math::Vector2D( 0.0f, 1.0f );
	Vtx[3].Tex[0] = Math::Vector2D( 1.0f, 1.0f );

	//--------------------------------------------------------
	// 頂点データ
	//--------------------------------------------------------
	m_pVB_PostEffect->Lock( true );
	m_pVB_PostEffect->Push( Vtx, 4 );
	m_pVB_PostEffect->UnLock();

	//--------------------------------------------------------
	// 頂点定義
	//--------------------------------------------------------
	m_pRender->SetVertexStream( m_pVS_PostEffect );

	//--------------------------------------------------------
	// 頂点バッファ
	//--------------------------------------------------------
	m_pRender->SetVertexBuffer( &m_pVB_PostEffect, 1 );

	//--------------------------------------------------------
	// シェーダーパラメーター更新
	//--------------------------------------------------------
	m_pShader->SetTexture( m_hTEXTURE[0], pTex );
	m_pShader->UpdateParameter();

	//--------------------------------------------------------
	// テクニック
	//--------------------------------------------------------
	m_pShader->SetTechnique( m_hTech_Simple );

	//--------------------------------------------------------
	// レンダリング
	//--------------------------------------------------------
	if ( m_pShader->Begin( NULL, true ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();
		m_pShader->End();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::DownSample( const Math::Rect2DI &Dst, ITexture *pTex )
{
	//--------------------------------------------------------
	// 頂点更新
	//--------------------------------------------------------
	SVertexPostEffect Vtx[4] = {
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
	};

	//--------------------------------------------------------
	// テクスチャUV更新
	//--------------------------------------------------------
	Vtx[0].Tex[0] = Math::Vector2D( 0.0f, 0.0f );
	Vtx[1].Tex[0] = Math::Vector2D( 1.0f, 0.0f );
	Vtx[2].Tex[0] = Math::Vector2D( 0.0f, 1.0f );
	Vtx[3].Tex[0] = Math::Vector2D( 1.0f, 1.0f );

	//--------------------------------------------------------
	// 頂点データ
	//--------------------------------------------------------
	m_pVB_PostEffect->Lock( true );
	m_pVB_PostEffect->Push( Vtx, 4 );
	m_pVB_PostEffect->UnLock();

	//--------------------------------------------------------
	// 頂点定義
	//--------------------------------------------------------
	m_pRender->SetVertexStream( m_pVS_PostEffect );

	//--------------------------------------------------------
	// 頂点バッファ
	//--------------------------------------------------------
	m_pRender->SetVertexBuffer( &m_pVB_PostEffect, 1 );

	//--------------------------------------------------------
	// シェーダーパラメーター更新
	//--------------------------------------------------------
	m_pShader->SetTexture( m_hTEXTURE[0], pTex );
	m_pShader->UpdateParameter();

	//--------------------------------------------------------
	// テクニック
	//--------------------------------------------------------
	m_pShader->SetTechnique( m_hTech_DownSample );

	//--------------------------------------------------------
	// レンダリング
	//--------------------------------------------------------
	if ( m_pShader->Begin( NULL, true ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();
		m_pShader->End();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::HDR_DownSample( const Math::Rect2DI &Dst, ITexture *pTex, Float fHDRPower, Float fHDRBoundary )
{
	//--------------------------------------------------------
	// 頂点更新
	//--------------------------------------------------------
	SVertexPostEffect Vtx[4] = {
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
	};

	//--------------------------------------------------------
	// テクスチャUV更新
	//--------------------------------------------------------
	Vtx[0].Tex[0] = Math::Vector2D( 0.0f, 0.0f );
	Vtx[1].Tex[0] = Math::Vector2D( 1.0f, 0.0f );
	Vtx[2].Tex[0] = Math::Vector2D( 0.0f, 1.0f );
	Vtx[3].Tex[0] = Math::Vector2D( 1.0f, 1.0f );

	//--------------------------------------------------------
	// 頂点データ
	//--------------------------------------------------------
	m_pVB_PostEffect->Lock( true );
	m_pVB_PostEffect->Push( Vtx, 4 );
	m_pVB_PostEffect->UnLock();

	//--------------------------------------------------------
	// 頂点定義
	//--------------------------------------------------------
	m_pRender->SetVertexStream( m_pVS_PostEffect );

	//--------------------------------------------------------
	// 頂点バッファ
	//--------------------------------------------------------
	m_pRender->SetVertexBuffer( &m_pVB_PostEffect, 1 );

	//--------------------------------------------------------
	// シェーダーパラメーター更新
	//--------------------------------------------------------
	m_pShader->SetFloat( m_hHDR_POWER, fHDRPower );
	m_pShader->SetFloat( m_hHDR_BOUNDARY, fHDRBoundary );
	m_pShader->SetTexture( m_hTEXTURE[0], pTex );
	m_pShader->UpdateParameter();

	//--------------------------------------------------------
	// テクニック
	//--------------------------------------------------------
	m_pShader->SetTechnique( m_hTech_HDR_DownSample );

	//--------------------------------------------------------
	// レンダリング
	//--------------------------------------------------------
	if ( m_pShader->Begin( NULL, true ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();
		m_pShader->End();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::HDR_BloomFx( const Math::Rect2DI &Dst, ITexture *pTexTbl[] )
{
	//--------------------------------------------------------
	// 頂点更新
	//--------------------------------------------------------
	SVertexPostEffect Vtx[4] = {
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
	};

	//--------------------------------------------------------
	// テクスチャUV更新
	//--------------------------------------------------------
	Vtx[0].Tex[0] = Math::Vector2D( 0.0f, 0.0f );
	Vtx[1].Tex[0] = Math::Vector2D( 1.0f, 0.0f );
	Vtx[2].Tex[0] = Math::Vector2D( 0.0f, 1.0f );
	Vtx[3].Tex[0] = Math::Vector2D( 1.0f, 1.0f );

	//--------------------------------------------------------
	// 頂点データ
	//--------------------------------------------------------
	m_pVB_PostEffect->Lock( true );
	m_pVB_PostEffect->Push( Vtx, 4 );
	m_pVB_PostEffect->UnLock();

	//--------------------------------------------------------
	// 頂点定義
	//--------------------------------------------------------
	m_pRender->SetVertexStream( m_pVS_PostEffect );

	//--------------------------------------------------------
	// 頂点バッファ
	//--------------------------------------------------------
	m_pRender->SetVertexBuffer( &m_pVB_PostEffect, 1 );

	//--------------------------------------------------------
	// シェーダーパラメーター更新
	//--------------------------------------------------------
	m_pShader->SetTexture( m_hTEXTURE[0], pTexTbl[0] );
	m_pShader->SetTexture( m_hTEXTURE[1], pTexTbl[1] );
	m_pShader->SetTexture( m_hTEXTURE[2], pTexTbl[2] );
	m_pShader->SetTexture( m_hTEXTURE[3], pTexTbl[3] );
	m_pShader->UpdateParameter();

	//--------------------------------------------------------
	// テクニック
	//--------------------------------------------------------
	m_pShader->SetTechnique( m_hTech_HDR_BloomFx );

	//--------------------------------------------------------
	// シェーダー
	//--------------------------------------------------------
	if ( m_pShader->Begin( NULL, true ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();
		m_pShader->End();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::HDR_CrossFx( const Math::Rect2DI &Dst, ITexture *pTexTbl[] )
{
	//--------------------------------------------------------
	// 頂点更新
	//--------------------------------------------------------
	SVertexPostEffect Vtx[4] = {
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
	};

	//--------------------------------------------------------
	// テクスチャUV更新
	//--------------------------------------------------------
	Vtx[0].Tex[0] = Math::Vector2D( 0.0f, 0.0f );
	Vtx[1].Tex[0] = Math::Vector2D( 1.0f, 0.0f );
	Vtx[2].Tex[0] = Math::Vector2D( 0.0f, 1.0f );
	Vtx[3].Tex[0] = Math::Vector2D( 1.0f, 1.0f );

	//--------------------------------------------------------
	// 頂点データ
	//--------------------------------------------------------
	m_pVB_PostEffect->Lock( true );
	m_pVB_PostEffect->Push( Vtx, 4 );
	m_pVB_PostEffect->UnLock();

	//--------------------------------------------------------
	// 頂点定義
	//--------------------------------------------------------
	m_pRender->SetVertexStream( m_pVS_PostEffect );

	//--------------------------------------------------------
	// 頂点バッファ
	//--------------------------------------------------------
	m_pRender->SetVertexBuffer( &m_pVB_PostEffect, 1 );

	//--------------------------------------------------------
	// シェーダーパラメーター更新
	//--------------------------------------------------------
	m_pShader->SetTexture( m_hTEXTURE[0], pTexTbl[0] );
	m_pShader->SetTexture( m_hTEXTURE[1], pTexTbl[1] );
	m_pShader->SetTexture( m_hTEXTURE[2], pTexTbl[2] );
	m_pShader->SetTexture( m_hTEXTURE[3], pTexTbl[3] );
	m_pShader->SetTexture( m_hTEXTURE[4], pTexTbl[4] );
	m_pShader->UpdateParameter();

	//--------------------------------------------------------
	// テクニック
	//--------------------------------------------------------
	m_pShader->SetTechnique( m_hTech_HDR_CrossFx );

	//--------------------------------------------------------
	// シェーダー
	//--------------------------------------------------------
	if ( m_pShader->Begin( NULL, true ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();
		m_pShader->End();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::Gaussian( const Math::Rect2DI &Dst, ITexture *pTex, Sint32 Angle )
{
	//--------------------------------------------------------
	// 頂点更新
	//--------------------------------------------------------
	SVertexPostEffect Vtx[4] = {
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
	};

	//--------------------------------------------------------
	// UV更新
	//--------------------------------------------------------
	Vtx[0].Tex[0] = Math::Vector2D( 0.0f, 0.0f );
	Vtx[1].Tex[0] = Math::Vector2D( 1.0f, 0.0f );
	Vtx[2].Tex[0] = Math::Vector2D( 0.0f, 1.0f );
	Vtx[3].Tex[0] = Math::Vector2D( 1.0f, 1.0f );

	//--------------------------------------------------------
	// ガウス分布
	//--------------------------------------------------------
	Math::Point2DF P2T = pTex->GetPixelToTexelTransform();
	Float x = Math::Cos( Angle ) * P2T.x;
	Float y = Math::Sin( Angle ) * P2T.y;
    for ( Sint32 i = 0; i <= 16; i++ )
    {
        m_vOffset[i].x = x * toF(i - 8);
        m_vOffset[i].y = y * toF(i - 8);
    }

	//--------------------------------------------------------
	// 頂点データ
	//--------------------------------------------------------
	m_pVB_PostEffect->Lock( true );
	m_pVB_PostEffect->Push( Vtx, 4 );
	m_pVB_PostEffect->UnLock();

	//--------------------------------------------------------
	// 頂点定義
	//--------------------------------------------------------
	m_pRender->SetVertexStream( m_pVS_PostEffect );

	//--------------------------------------------------------
	// 頂点バッファ
	//--------------------------------------------------------
	m_pRender->SetVertexBuffer( &m_pVB_PostEffect, 1 );

	//--------------------------------------------------------
	// シェーダーパラメーター更新
	//--------------------------------------------------------
	m_pShader->SetTexture( m_hTEXTURE[0], pTex );
	m_pShader->SetVectorArray( m_hOFFSET, m_vOffset, 17 );
	m_pShader->UpdateParameter();

	//--------------------------------------------------------
	// テクニック
	//--------------------------------------------------------
	m_pShader->SetTechnique( m_hTech_Gaussian );

	//--------------------------------------------------------
	// シェーダー
	//--------------------------------------------------------
	if ( m_pShader->Begin( NULL, true ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();
		m_pShader->End();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::NormalDepthEdge( const Math::Rect2DI &Dst, ITexture *pTex, Float fNormalPower, Float fDepthPower, Bool IsBold )
{
	//--------------------------------------------------------
	// 頂点更新
	//--------------------------------------------------------
	SVertexPostEffect Vtx[4] = {
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
	};

	//--------------------------------------------------------
	// テクスチャUV更新
	//--------------------------------------------------------
	if ( IsBold )
	{
		Float x_tbl[] = { -1.0f, +1.0f, -1.0f, +1.0f };
		Float y_tbl[] = { -1.0f, -1.0f, +1.0f, +1.0f };
		Math::Point2DF P2T = pTex->GetPixelToTexelTransform();
		for ( Sint32 i = 0; i < 4; i++ )
		{
			Vtx[0].Tex[i] = Math::Vector2D( 0.0f, 0.0f );
			Vtx[1].Tex[i] = Math::Vector2D( 1.0f, 0.0f );
			Vtx[2].Tex[i] = Math::Vector2D( 0.0f, 1.0f );
			Vtx[3].Tex[i] = Math::Vector2D( 1.0f, 1.0f );

			Math::Vector4D vOffset( x_tbl[i] * P2T.x, y_tbl[i] * P2T.y, 0.0f, 0.0f );
			Vtx[0].Tex[i] += vOffset;
			Vtx[1].Tex[i] += vOffset;
			Vtx[2].Tex[i] += vOffset;
			Vtx[3].Tex[i] += vOffset;
		}
	}
	else
	{
		Float x_tbl[] = { 0.0f, +1.0f, 0.0f, 1.0f };
		Float y_tbl[] = { 0.0f,  0.0f, 1.0f, 1.0f };
		Math::Point2DF P2T = pTex->GetPixelToTexelTransform();
		for ( Sint32 i = 0; i < 4; i++ )
		{
			Vtx[0].Tex[i] = Math::Vector2D( 0.0f, 0.0f );
			Vtx[1].Tex[i] = Math::Vector2D( 1.0f, 0.0f );
			Vtx[2].Tex[i] = Math::Vector2D( 0.0f, 1.0f );
			Vtx[3].Tex[i] = Math::Vector2D( 1.0f, 1.0f );

			Math::Vector4D vOffset( x_tbl[i] * P2T.x, y_tbl[i] * P2T.y, 0.0f, 0.0f );
			Vtx[0].Tex[i] += vOffset;
			Vtx[1].Tex[i] += vOffset;
			Vtx[2].Tex[i] += vOffset;
			Vtx[3].Tex[i] += vOffset;
		}
	}

	//--------------------------------------------------------
	// 頂点データ
	//--------------------------------------------------------
	m_pVB_PostEffect->Lock( true );
	m_pVB_PostEffect->Push( Vtx, 4 );
	m_pVB_PostEffect->UnLock();

	//--------------------------------------------------------
	// 頂点定義
	//--------------------------------------------------------
	m_pRender->SetVertexStream( m_pVS_PostEffect );

	//--------------------------------------------------------
	// 頂点バッファ
	//--------------------------------------------------------
	m_pRender->SetVertexBuffer( &m_pVB_PostEffect, 1 );

	//--------------------------------------------------------
	// シェーダーパラメーター更新
	//--------------------------------------------------------
	Math::Vector4D vTemp( fDepthPower, fNormalPower, fNormalPower, fNormalPower );
	m_pShader->SetVector( m_hEDGE_POWER, &vTemp );
	m_pShader->SetTexture( m_hTEXTURE[0], pTex );
	m_pShader->UpdateParameter();

	//--------------------------------------------------------
	// テクニック
	//--------------------------------------------------------
	m_pShader->SetTechnique( m_hTech_NormalDepthEdge );

	//--------------------------------------------------------
	// シェーダー
	//--------------------------------------------------------
	if ( m_pShader->Begin( NULL, true ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();
		m_pShader->End();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::DOF_Blur( const Math::Rect2DI &Dst, ITexture *pTexColor, ITexture *pTexDepth, Float fDofCenter, Float fDofScale )
{
	//--------------------------------------------------------
	// 頂点更新
	//--------------------------------------------------------
	SVertexPostEffect Vtx[4] = {
		{ Math::Vector4D( toF(Dst.x      ), toF(Dst.y      ) ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w), toF(Dst.y      ) ) },
		{ Math::Vector4D( toF(Dst.x      ), toF(Dst.y+Dst.h) ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w), toF(Dst.y+Dst.h) ) },
	};

	//--------------------------------------------------------
	// テクスチャUV更新
	//--------------------------------------------------------
	Vtx[0].Tex[0] = Math::Vector2D( 0.0f, 0.0f );
	Vtx[1].Tex[0] = Math::Vector2D( 1.0f, 0.0f );
	Vtx[2].Tex[0] = Math::Vector2D( 0.0f, 1.0f );
	Vtx[3].Tex[0] = Math::Vector2D( 1.0f, 1.0f );

	// テクスチャUV更新
	Math::Point2DF P2T = pTexColor->GetPixelToTexelTransform();
	Sint32 Idx = 0;
	for ( Sint32 i = 0; i < 8; i++ )
	{
		Sint32 Angle = DEG_TO_ANGLE(i * 360 / 8);
		m_vOffset[Idx].x = Math::Cos( Angle ) * 1.5f * P2T.x;
		m_vOffset[Idx].y = Math::Sin( Angle ) * 1.5f * P2T.y;
		Idx++;
	}
	for ( Sint32 i = 0; i < 8; i++ )
	{
		Sint32 Angle = DEG_TO_ANGLE(i * 360 / 8) + DEG_TO_ANGLE(360 / 16);
		m_vOffset[Idx].x = Math::Cos( Angle ) * 3.0f * P2T.x;
		m_vOffset[Idx].y = Math::Sin( Angle ) * 3.0f * P2T.y;
		Idx++;
	}

	//--------------------------------------------------------
	// 頂点データ
	//--------------------------------------------------------
	m_pVB_PostEffect->Lock( true );
	m_pVB_PostEffect->Push( Vtx, 4 );
	m_pVB_PostEffect->UnLock();

	//--------------------------------------------------------
	// 頂点定義
	//--------------------------------------------------------
	m_pRender->SetVertexStream( m_pVS_PostEffect );

	//--------------------------------------------------------
	// 頂点バッファ
	//--------------------------------------------------------
	m_pRender->SetVertexBuffer( &m_pVB_PostEffect, 1 );

	//--------------------------------------------------------
	// シェーダーパラメーター更新
	//--------------------------------------------------------
	Float ParamTbl[] = { fDofCenter, fDofScale };
	m_pShader->SetFloatArray( m_hDOF_PARAMETER, ParamTbl, 2 );
	m_pShader->SetVectorArray( m_hOFFSET, m_vOffset, 16 );
	m_pShader->SetTexture( m_hTEXTURE[0], pTexColor );
	m_pShader->SetTexture( m_hTEXTURE[1], pTexDepth );
	m_pShader->UpdateParameter();

	//--------------------------------------------------------
	// テクニック
	//--------------------------------------------------------
	m_pShader->SetTechnique( m_hTech_DOF_Blur );

	//--------------------------------------------------------
	// シェーダー
	//--------------------------------------------------------
	if ( m_pShader->Begin( NULL, true ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();
		m_pShader->End();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::MSAA( const Math::Rect2DI &Dst, ITexture *pTex, Float fPower )
{
	//--------------------------------------------------------
	// 頂点更新
	//--------------------------------------------------------
	SVertexPostEffect Vtx[4] = {
		{ Math::Vector4D( toF(Dst.x      ), toF(Dst.y      ) ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w), toF(Dst.y      ) ) },
		{ Math::Vector4D( toF(Dst.x      ), toF(Dst.y+Dst.h) ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w), toF(Dst.y+Dst.h) ) },
	};

	//--------------------------------------------------------
	// テクスチャUV更新
	//--------------------------------------------------------
	// テクスチャUV更新
	Float x_tbl[] = { -fPower, +fPower, -fPower, +fPower };
	Float y_tbl[] = { -fPower, -fPower, +fPower, +fPower };
	Math::Point2DF P2T = pTex->GetPixelToTexelTransform();
	for ( Sint32 i = 0; i < 4; i++ )
	{
		Vtx[0].Tex[i] = Math::Vector4D( 0.0f, 0.0f, 0.0f, 0.0f );
		Vtx[1].Tex[i] = Math::Vector4D( 1.0f, 0.0f, 0.0f, 0.0f );
		Vtx[2].Tex[i] = Math::Vector4D( 0.0f, 1.0f, 0.0f, 0.0f );
		Vtx[3].Tex[i] = Math::Vector4D( 1.0f, 1.0f, 0.0f, 0.0f );

		Math::Vector4D vOffset( x_tbl[i] * P2T.x, y_tbl[i] * P2T.y, 0.0f, 0.0f );
		Vtx[0].Tex[i] += vOffset;
		Vtx[1].Tex[i] += vOffset;
		Vtx[2].Tex[i] += vOffset;
		Vtx[3].Tex[i] += vOffset;
	}

	//--------------------------------------------------------
	// 頂点データ
	//--------------------------------------------------------
	m_pVB_PostEffect->Lock( true );
	m_pVB_PostEffect->Push( Vtx, 4 );
	m_pVB_PostEffect->UnLock();

	//--------------------------------------------------------
	// 頂点定義
	//--------------------------------------------------------
	m_pRender->SetVertexStream( m_pVS_PostEffect );

	//--------------------------------------------------------
	// 頂点バッファ
	//--------------------------------------------------------
	m_pRender->SetVertexBuffer( &m_pVB_PostEffect, 1 );

	//--------------------------------------------------------
	// シェーダーパラメーター更新
	//--------------------------------------------------------
	m_pShader->SetTexture( m_hTEXTURE[0], pTex );
	m_pShader->UpdateParameter();

	//--------------------------------------------------------
	// テクニック
	//--------------------------------------------------------
	m_pShader->SetTechnique( m_hTech_MSAA );

	//--------------------------------------------------------
	// シェーダー
	//--------------------------------------------------------
	if ( m_pShader->Begin( NULL, true ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();
		m_pShader->End();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::Velocity_High( const Math::Rect2DI &Dst, ITexture *pTex, ITexture *pTexVelocity )
{
	//--------------------------------------------------------
	// 頂点更新
	//--------------------------------------------------------
	SVertexPostEffect Vtx[4] = {
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
	};

	//--------------------------------------------------------
	// テクスチャUV更新
	//--------------------------------------------------------
	Vtx[0].Tex[0] = Math::Vector2D( 0.0f, 0.0f );
	Vtx[1].Tex[0] = Math::Vector2D( 1.0f, 0.0f );
	Vtx[2].Tex[0] = Math::Vector2D( 0.0f, 1.0f );
	Vtx[3].Tex[0] = Math::Vector2D( 1.0f, 1.0f );

	//--------------------------------------------------------
	// 頂点データ
	//--------------------------------------------------------
	m_pVB_PostEffect->Lock( true );
	m_pVB_PostEffect->Push( Vtx, 4 );
	m_pVB_PostEffect->UnLock();

	//--------------------------------------------------------
	// 頂点定義
	//--------------------------------------------------------
	m_pRender->SetVertexStream( m_pVS_PostEffect );

	//--------------------------------------------------------
	// 頂点バッファ
	//--------------------------------------------------------
	m_pRender->SetVertexBuffer( &m_pVB_PostEffect, 1 );

	//--------------------------------------------------------
	// シェーダーパラメーター更新
	//--------------------------------------------------------
	m_pShader->SetTexture( m_hTEXTURE[0], pTex );
	m_pShader->SetTexture( m_hTEXTURE[1], pTexVelocity );
	m_pShader->UpdateParameter();

	//--------------------------------------------------------
	// テクニック
	//--------------------------------------------------------
	m_pShader->SetTechnique( m_hTech_Velocity_High );

	//--------------------------------------------------------
	// シェーダー
	//--------------------------------------------------------
	if ( m_pShader->Begin( NULL, true ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();
		m_pShader->End();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::Velocity_Low( const Math::Rect2DI &Dst, ITexture *pTex, ITexture *pTexVelocity )
{
	//--------------------------------------------------------
	// 頂点更新
	//--------------------------------------------------------
	SVertexPostEffect Vtx[4] = {
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
	};

	//--------------------------------------------------------
	// テクスチャUV更新
	//--------------------------------------------------------
	Vtx[0].Tex[0] = Math::Vector2D( 0.0f, 0.0f );
	Vtx[1].Tex[0] = Math::Vector2D( 1.0f, 0.0f );
	Vtx[2].Tex[0] = Math::Vector2D( 0.0f, 1.0f );
	Vtx[3].Tex[0] = Math::Vector2D( 1.0f, 1.0f );

	//--------------------------------------------------------
	// 頂点データ
	//--------------------------------------------------------
	m_pVB_PostEffect->Lock( true );
	m_pVB_PostEffect->Push( Vtx, 4 );
	m_pVB_PostEffect->UnLock();

	//--------------------------------------------------------
	// 頂点定義
	//--------------------------------------------------------
	m_pRender->SetVertexStream( m_pVS_PostEffect );

	//--------------------------------------------------------
	// 頂点バッファ
	//--------------------------------------------------------
	m_pRender->SetVertexBuffer( &m_pVB_PostEffect, 1 );

	//--------------------------------------------------------
	// シェーダーパラメーター更新
	//--------------------------------------------------------
	m_pShader->SetTexture( m_hTEXTURE[0], pTex );
	m_pShader->SetTexture( m_hTEXTURE[1], pTexVelocity );
	m_pShader->UpdateParameter();

	//--------------------------------------------------------
	// テクニック
	//--------------------------------------------------------
	m_pShader->SetTechnique( m_hTech_Velocity_Low );

	//--------------------------------------------------------
	// シェーダー
	//--------------------------------------------------------
	if ( m_pShader->Begin( NULL, true ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();
		m_pShader->End();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPostEffect::AlphaRendering( const Math::Rect2DF &Dst, ITexture *pTex )
{
	//--------------------------------------------------------
	// 頂点更新
	//--------------------------------------------------------
	SVertexPostEffect Vtx[4] = {
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y      )-0.5f ) },
		{ Math::Vector4D( toF(Dst.x      )-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
		{ Math::Vector4D( toF(Dst.x+Dst.w)-0.5f, toF(Dst.y+Dst.h)-0.5f ) },
	};

	//--------------------------------------------------------
	// テクスチャUV更新
	//--------------------------------------------------------
	Vtx[0].Tex[0] = Math::Vector2D( 0.0f, 0.0f );
	Vtx[1].Tex[0] = Math::Vector2D( 1.0f, 0.0f );
	Vtx[2].Tex[0] = Math::Vector2D( 0.0f, 1.0f );
	Vtx[3].Tex[0] = Math::Vector2D( 1.0f, 1.0f );

	//--------------------------------------------------------
	// 頂点データ
	//--------------------------------------------------------
	m_pVB_PostEffect->Lock( true );
	m_pVB_PostEffect->Push( Vtx, 4 );
	m_pVB_PostEffect->UnLock();

	//--------------------------------------------------------
	// 頂点定義
	//--------------------------------------------------------
	m_pRender->SetVertexStream( m_pVS_PostEffect );

	//--------------------------------------------------------
	// 頂点バッファ
	//--------------------------------------------------------
	m_pRender->SetVertexBuffer( &m_pVB_PostEffect, 1 );

	//--------------------------------------------------------
	// シェーダーパラメーター更新
	//--------------------------------------------------------
	m_pShader->SetTexture( m_hTEXTURE[0], pTex );
	m_pShader->UpdateParameter();

	//--------------------------------------------------------
	// テクニック
	//--------------------------------------------------------
	m_pShader->SetTechnique( m_hTech_ShowAlpha );

	//--------------------------------------------------------
	// シェーダー
	//--------------------------------------------------------
	if ( m_pShader->Begin( NULL, true ) )
	{
		m_pShader->BeginPass( 0 );

		// レンダリング
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );

		m_pShader->EndPass();
		m_pShader->End();
	}
}


