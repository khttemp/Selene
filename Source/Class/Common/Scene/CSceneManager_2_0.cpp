

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Scene/CSceneManager_2_0.h"
#include "Class/Common/Scene/CSceneParticleActor.h"
#include "Class/Common/Scene/CCustomizedSceneRenderObject.h"
#include "Class/Platform/DirectX9/Render/COcclusion.h"
#include "Class/Platform/DirectX9/Render/CRender.h"
#include "Class/Platform/DirectX9/Render/CPostEffect.h"
#include "Class/Platform/DirectX9/Surface/CDepthTexture.h"
#include "Class/Platform/DirectX9/Surface/CTexture.h"
#include "Common/SMF.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
// TABLE
//-----------------------------------------------------------------------------------
static const Math::Vector4D g_vProjectionReadMaskTbl[] = {
	Math::Vector4D( 0.0f, 0.0f, 0.0f, 1.0f ),	// PROJECTION_SHADOW_PRIORITY_0
	Math::Vector4D( 0.0f, 0.0f, 1.0f, 0.0f ),	// PROJECTION_SHADOW_PRIORITY_1
	Math::Vector4D( 0.0f, 1.0f, 0.0f, 0.0f ),	// PROJECTION_SHADOW_PRIORITY_2
	Math::Vector4D( 1.0f, 0.0f, 0.0f, 0.0f ),	// PROJECTION_SHADOW_PRIORITY_3
	Math::Vector4D( 0.0f, 0.0f, 0.0f, 0.0f ),	// PROJECTION_SHADOW_PRIORITY_4
};

static const Bool g_vProjectionWriteMaskTbl[][4] = {
	{ false, false, false, false },				// PROJECTION_SHADOW_PRIORITY_0
	{ false, false, false,  true },				// PROJECTION_SHADOW_PRIORITY_1
	{ false, false,  true,  true },				// PROJECTION_SHADOW_PRIORITY_2
	{ false,  true,  true,  true },				// PROJECTION_SHADOW_PRIORITY_3
	{  true,  true,  true,  true },				// PROJECTION_SHADOW_PRIORITY_4
};


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSceneManager_2_0::CSceneManager_2_0( Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr, Sint32 QueMax ) : CSceneManagerBase( pRender, pMgr, QueMax )
	, m_pRT_Temp		( NULL )
	, m_pDS_Shadow		( NULL )
	, m_pRT_Small		( NULL )
	, m_pRT_Blur		( NULL )
	, m_pRT_HDR			( NULL )
	, m_pRT_HDR1		( NULL )
	, m_pRT_HDR2		( NULL )
	, m_pRT_HDR3		( NULL )
	, m_pRT_HDR1_GausA	( NULL )
	, m_pRT_HDR1_GausB	( NULL )
	, m_pRT_HDR2_GausA	( NULL )
	, m_pRT_HDR2_GausB	( NULL )
	, m_pRT_HDR3_GausA	( NULL )
	, m_pRT_HDR3_GausB	( NULL )
	, m_pRT_Shadow		( NULL )
	, m_pRT_ShadowSoft	( NULL )
	, m_pRT_Velocity	( NULL )
	, m_pRT_NormalDepth	( NULL )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSceneManager_2_0::~CSceneManager_2_0()
{
	SAFE_RELEASE( m_pRT_Temp );
	SAFE_RELEASE( m_pDS_Shadow );
	SAFE_RELEASE( m_pRT_Small );
	SAFE_RELEASE( m_pRT_Blur );
	SAFE_RELEASE( m_pRT_HDR );
	SAFE_RELEASE( m_pRT_HDR1 );
	SAFE_RELEASE( m_pRT_HDR2 );
	SAFE_RELEASE( m_pRT_HDR3 );
	SAFE_RELEASE( m_pRT_HDR1_GausA );
	SAFE_RELEASE( m_pRT_HDR1_GausB );
	SAFE_RELEASE( m_pRT_HDR2_GausA );
	SAFE_RELEASE( m_pRT_HDR2_GausB );
	SAFE_RELEASE( m_pRT_HDR3_GausA );
	SAFE_RELEASE( m_pRT_HDR3_GausB );
	SAFE_RELEASE( m_pRT_Shadow );
	SAFE_RELEASE( m_pRT_ShadowSoft );
	SAFE_RELEASE( m_pRT_Velocity );
	SAFE_RELEASE( m_pRT_NormalDepth );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_2_0::Rendering( Bool IsDrawBuffer )
{
	m_SceneRenderingTime = 0;

	//==============================================================
	// 開始してない
	//==============================================================
	if ( m_SceneState != SCENE_STATE_END )
	{
		return;
	}

	m_SceneState = SCENE_STATE_STANDBY;

	//==============================================================
	// シーン構築が終わるまでブロック
	//==============================================================
	WaitForSceneConstruct();

	//==============================================================
	// 現在時刻
	//==============================================================
	Uint64 TimeStart = m_pCore->GetSystemTimer();

	//==============================================================
	// ステート
	//==============================================================
	m_pRender->StatePush();

	//==============================================================
	// シャドウマップ生成
	//==============================================================
	CreateShadowmap();

	//==============================================================
	// 内部管理レンダリング
	//==============================================================
	Rendering();

	//==============================================================
	// デバッグ用
	//==============================================================
	if ( IsDrawBuffer )
	{
		Rendering_DebugBuffer();
	}

	//==============================================================
	// ステート
	//==============================================================
	m_pRender->StatePop();

	//==============================================================
	// シーンオブジェクト解放
	//==============================================================
	ReleaseObjectList();

	//==============================================================
	// 終了時刻
	//==============================================================
	Uint64 TimeEnd = m_pCore->GetSystemTimer();

	// 経過時間
	m_SceneRenderingTime = (100 * 60 * (TimeEnd - TimeStart)) / m_pCore->GetSystemTimerBySec();

	//==============================================================
	// 一応戻す
	//==============================================================
	m_pRender->SetColorWriteEnable( true, true, true, true );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_2_0::Rendering_DebugBuffer( void )
{
	Math::Rect2DF Dst, Src;

	// ステート
	m_pRender->SetCullType( CULL_FRONT );
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
	m_pRender->SetAlphaTestEnable( false );

	// 描画先
	Dst = Math::Rect2DF( 0.0f, 0.0f, 128.0f, 128.0f );

	// レンダリングターゲットのアルファ（深度）
	Renderer::Shader::ShaderManager::GetPostEffect()->AlphaRendering( Dst, m_pRT_NormalDepth );
	Dst.y += 128.0f;

	// 被写界深度用深度マップ
	if ( IsDepthOfFieldEnable() )
	{
		Renderer::Shader::ShaderManager::GetPostEffect()->AlphaRendering( Dst, m_pRT_Small );
		Dst.y += 128.0f;
	}

	// 速度マップ
	if ( m_MotionBlurType != MOTION_BLUR_TYPE_DISABLE )
	{
		Src.Set( 0.0f, 0.0f, toF(m_pRT_Velocity->GetOriginalSize().x), toF(m_pRT_Velocity->GetOriginalSize().y) );
		m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_Velocity );
		Dst.y += 128.0f;
	}

	// 法線マップ
	if ( m_ShadingType != SHADING_TYPE_NORMAL )
	{
		Src.Set( 0.0f, 0.0f, toF(m_pRT_NormalDepth->GetOriginalSize().x), toF(m_pRT_NormalDepth->GetOriginalSize().y) );
		m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_NormalDepth );
		Dst.y += 128.0f;
	}

	// シャドウマップ
	if ( IsShadowEnable() )
	{
		Src.Set( 0.0f, 0.0f, toF(m_pRT_Shadow->GetOriginalSize().x), toF(m_pRT_Shadow->GetOriginalSize().y) );
		m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_Shadow );
		Dst.y += 128.0f;
	}

	// HDR
	if ( m_HdrType != HDR_TYPE_DISABLE )
	{
		switch ( m_HdrEffect )
		{
		case HDR_EFFECT_BLOOM:
			Dst.Set( 128.0f, 0.0f, 64.0f, 64.0f );
			Src.Set( 0.0f, 0.0f, toF(m_pRT_HDR->GetOriginalSize().x), toF(m_pRT_HDR->GetOriginalSize().y) );
			m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_HDR );
			Dst.Set( 128.0f, 64.0f, 64.0f, 64.0f );
			Src.Set( 0.0f, 0.0f, toF(m_pRT_HDR1_GausB->GetOriginalSize().x), toF(m_pRT_HDR1_GausB->GetOriginalSize().y) );
			m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_HDR1_GausB );
			Dst.Set( 192.0f, 0.0f, 64.0f, 64.0f );
			Src.Set( 0.0f, 0.0f, toF(m_pRT_HDR2_GausB->GetOriginalSize().x), toF(m_pRT_HDR2_GausB->GetOriginalSize().y) );
			m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_HDR2_GausB );
			Dst.Set( 192.0f, 64.0f, 64.0f, 64.0f );
			Src.Set( 0.0f, 0.0f, toF(m_pRT_HDR3_GausB->GetOriginalSize().x), toF(m_pRT_HDR3_GausB->GetOriginalSize().y) );
			m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_HDR3_GausB );
			break;
		case HDR_EFFECT_CROSS:
			Dst.Set( 128.0f, 0.0f, 64.0f, 64.0f );
			Src.Set( 0.0f, 0.0f, toF(m_pRT_HDR->GetOriginalSize().x), toF(m_pRT_HDR->GetOriginalSize().y) );
			m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_HDR );
			Dst.Set( 128.0f, 64.0f, 64.0f, 64.0f );
			Src.Set( 0.0f, 0.0f, toF(m_pRT_HDR2_GausA->GetOriginalSize().x), toF(m_pRT_HDR2_GausA->GetOriginalSize().y) );
			m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_HDR2_GausA );
			Dst.Set( 192.0f, 64.0f, 64.0f, 64.0f );
			Src.Set( 0.0f, 0.0f, toF(m_pRT_HDR2_GausB->GetOriginalSize().x), toF(m_pRT_HDR2_GausB->GetOriginalSize().y) );
			m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_HDR2_GausB );
			Dst.Set( 128.0f, 128.0f, 64.0f, 64.0f );
			Src.Set( 0.0f, 0.0f, toF(m_pRT_HDR3_GausA->GetOriginalSize().x), toF(m_pRT_HDR3_GausA->GetOriginalSize().y) );
			m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_HDR3_GausA );
			Dst.Set( 192.0f, 128.0f, 64.0f, 64.0f );
			Src.Set( 0.0f, 0.0f, toF(m_pRT_HDR3_GausB->GetOriginalSize().x), toF(m_pRT_HDR3_GausB->GetOriginalSize().y) );
			m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_HDR3_GausB );
			break;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_2_0::ClearBackground( void )
{
	if ( m_IsClear )
	{
		CColor Color( 0, 0, 0, 0 );
		if ( IsHDREnable() )
		{
			Color.r = (Uint8)(m_ClearColor.x * 127.0f);
			Color.g = (Uint8)(m_ClearColor.y * 127.0f);
			Color.b = (Uint8)(m_ClearColor.z * 127.0f);
		}
		else
		{
			Color.r = (Uint8)(m_ClearColor.x * 255.0f);
			Color.g = (Uint8)(m_ClearColor.y * 255.0f);
			Color.b = (Uint8)(m_ClearColor.z * 255.0f);
		}
		m_pRender->Clear( Color );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_2_0::CreateShadowmap( void )
{
	switch ( m_ShadowType )
	{
	case SHADOW_TYPE_PROJECTION:
		{
			m_pRender->SetDepthBuffer( NULL );

			//------------------------------------------------------------------------
			// PASS 1
			//------------------------------------------------------------------------
			// ターゲット
			m_pRender->SetRenderTarget( m_pRT_Shadow );
			m_pRender->SetDepthBuffer( NULL );
			m_pRender->Clear( 0x00000000 );

			// レンダリング
			Rendering_ShadowProjection( m_pRT_Shadow->GetSize() );

			//------------------------------------------------------------------------
			// PASS 1
			//------------------------------------------------------------------------
			m_pRender->SetRenderTarget( m_pRT_ShadowSoft );
			m_pRender->Clear( 0x00000000 );

			Math::Rect2DI Rc( 1, 1, m_pRT_ShadowSoft->GetSize().x - 2, m_pRT_ShadowSoft->GetSize().y - 2 );
			m_pRender->SetScissorRect( &Rc );

			Math::Rect2DF Dst( 0.0f, 0.0f, toF(m_pRT_ShadowSoft->GetSize().x), toF(m_pRT_ShadowSoft->GetSize().y) );
			Renderer::Shader::ShaderManager::GetPostEffect()->DOF_Blur( Dst, m_pRT_Shadow );

			m_pRender->SetScissorRect( NULL );

			//------------------------------------------------------------------------
			// シャドウマップ
			//------------------------------------------------------------------------
			m_pRender->SetTexture( TEXTURE_STAGE_SHADOW, m_pRT_ShadowSoft );
			m_pRender->SetTextureFilterType( TEXTURE_STAGE_SHADOW, TEXTURE_FILTER_3D_LOW );
		}
		break;

	case SHADOW_TYPE_SHADOWMAP:
		{
			//------------------------------------------------------------------------
			// PASS 1
			//------------------------------------------------------------------------
			// ターゲット
			m_pRender->SetRenderTarget( m_pRT_Shadow );
			m_pRender->SetDepthBuffer( m_pDS_Shadow );
			// レンダリング
			Rendering_Shadowmap( m_pRT_Shadow->GetSize() );

			//------------------------------------------------------------------------
			// シャドウマップ
			//------------------------------------------------------------------------
			m_pRender->SetTexture( TEXTURE_STAGE_SHADOW, m_pRT_Shadow );
			m_pRender->SetTextureFilterType( TEXTURE_STAGE_SHADOW, TEXTURE_FILTER_DISABLE );
		}
		break;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_2_0::Rendering( void )
{
	//------------------------------------------------------------------------
	// 速度マップ
	//------------------------------------------------------------------------
	if ( IsVelocityEnable() )
	{
		// ターゲット
		m_pRender->SetRenderTarget( m_pRT_Velocity );
		m_pRender->SetDepthBuffer( m_pDS_Normal );
		// クリア
		m_pRender->Clear( 0x00000000 );
		ClearDepthBuffer();
		// レンダリング
		Rendering_Velocity();
	}

	//------------------------------------------------------------------------
	// 深度・法線マップ
	//------------------------------------------------------------------------
	// ターゲット
	m_pRender->SetRenderTarget( m_pRT_NormalDepth );
	m_pRender->SetDepthBuffer( m_pDS_Normal );
	// クリア
	m_pRender->Clear( 0x00000000 );
	ClearDepthBuffer();
	// レンダリング
	Rendering_NormalDepth();

	//------------------------------------------------------------------------
	// 基本モデル
	//------------------------------------------------------------------------
	// ターゲット
	m_pRender->SetRenderTarget( IsVelocityEnable() ? m_pRT_Final : m_pRT_Temp );
	// クリア
	ClearBackground();

	// 不透明モデルのレンダリング
	Rendering_AlphaDisable();

	//------------------------------------------------------------------------
	// エッジの描画
	//------------------------------------------------------------------------
	if ( IsEdgeDrawEnable() )
	{
		PostEffectEDGE();
	}

	//------------------------------------------------------------------------
	// モーションブラー
	//------------------------------------------------------------------------
	if ( IsVelocityEnable() )
	{
		// ターゲット
		m_pRender->SetRenderTarget( m_pRT_Temp );
	
		// ブラー
		m_pRender->SetDepthTestEnable( false );
		m_pRender->SetDepthWriteEnable( false );
		m_pRender->SetAlphaTestEnable( false );
		m_pRender->SetDrawType( DRAW_TYPE_NORMAL );

		switch ( m_MotionBlurType )
		{
		case MOTION_BLUR_TYPE_LOW:
			Renderer::Shader::ShaderManager::GetPostEffect()->Velocity_Low( m_pRender->GetViewport(), m_pRT_Final, m_pRT_Velocity );
			break;
		case MOTION_BLUR_TYPE_HIGH:
			Renderer::Shader::ShaderManager::GetPostEffect()->Velocity_High( m_pRender->GetViewport(), m_pRT_Final, m_pRT_Velocity );
			break;
		}
	}

	//------------------------------------------------------------------------
	// 半透明モデルのレンダリング
	//------------------------------------------------------------------------
	Rendering_AlphaEnable();

	//------------------------------------------------------------------------
	// DOF
	//------------------------------------------------------------------------
	PostEffectDOF();

	//------------------------------------------------------------------------
	// HDR
	//------------------------------------------------------------------------
	PostEffectHDR();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_2_0::Rendering_ShadowProjection( Math::Point2DI Size )
{
	Renderer::Shader::ShaderVariable *pVariable = Renderer::Shader::ShaderManager::GetShaderVariable();
	Renderer::Shader::ShaderEffect *pEffect = Renderer::Shader::ShaderManager::GetShaderEffect();
	CCustomizedSceneRenderObject *pObj;

	Sint32 Polygon = 0;

	// カメラの逆変換
	Math::Matrix mViewInverse;
	mViewInverse.Transpose( m_mShadowView );
	pVariable->SetViewInverse( &mViewInverse );

	//================================================================================================
	// スプライト更新
	//================================================================================================
	for ( Sint32 i = 0; i < PROJECTION_SHADOW_PRIORITY_MAX; i++ )
	{
		m_pParticleShadow[i]->Begin();
	}

	// UV
	Math::Rect2DF Src( 0.0f, 0.0f, toF(m_pTextureShadowProjection->GetOriginalSize().x), toF(m_pTextureShadowProjection->GetOriginalSize().y) );

	// 影を落とすオブジェクトを描画
	pObj = m_pObjectList[ID_ALPHA_DISABLE];
	while ( pObj != NULL )
	{
		if ( pObj->ProjectionShadowType == PROJECTION_SHADOW_DROP_SIMPLE )
		{
			Math::Point2DF fSize( pObj->fShadowRadius, pObj->fShadowRadius );
			m_pParticleShadow[pObj->ProjectionShadowPriority]->Draw( pObj->pActor->GetCenter(), fSize, Src, CColor(255,255,255,255) );
		}

		// 次
		pObj = pObj->pNext;
	}

	for ( Sint32 i = 0; i < PROJECTION_SHADOW_PRIORITY_MAX; i++ )
	{
		m_pParticleShadow[i]->End();
	}

	//--------------------------------------------------
	// レンダリングステート更新
	//--------------------------------------------------
	m_pRender->SetDepthWriteEnable( false );
	m_pRender->SetDepthTestEnable( false );

	// 描画モード
	m_pRender->SetDrawType( DRAW_TYPE_ADD );

	// アルファテスト
	m_pRender->SetAlphaTestEnable( true );
	m_pRender->SetAlphaBoundary( 0 );

	// カリング
	m_pRender->SetCullType( CULL_NONE );

	//--------------------------------------------------
	// グローバルライト
	//--------------------------------------------------
	if ( m_pProjectionShadowGlobalTexture != NULL )
	{
		Uint32 Pri = PROJECTION_SHADOW_PRIORITY_MAX - 1;
		// ピクセルマスク
		m_pRender->SetColorWriteEnable(
			g_vProjectionWriteMaskTbl[Pri][3],
			g_vProjectionWriteMaskTbl[Pri][0],
			g_vProjectionWriteMaskTbl[Pri][1],
			g_vProjectionWriteMaskTbl[Pri][2] );

		Float fSizeX = toF(m_pProjectionShadowGlobalTexture->GetOriginalSize().x);
		Float fSizeY = toF(m_pProjectionShadowGlobalTexture->GetOriginalSize().y);

		Math::Rect2DF Src(
			fSizeX * m_vProjectionShadowGlobalTextureOffset.x,
			fSizeY * m_vProjectionShadowGlobalTextureOffset.y,
			fSizeX * m_vProjectionShadowGlobalTextureScale.x,
			fSizeY * m_vProjectionShadowGlobalTextureScale.y );

		m_pRender->SetTextureFilterType( TEXTURE_STAGE_COLOR, TEXTURE_FILTER_2D );

		m_pRender->DrawTexture( m_pRender->GetViewport(), CColor(255,255,255), Src, m_pProjectionShadowGlobalTexture );
	}

	//================================================================================================
	// 丸影を描画
	//================================================================================================
	// テクニック
	pEffect->SetTechnique( TECHNIQUE_EFFECT_SHADOW_PROJECTION, false );

	// WorldViewProjection
	pVariable->SetWorldViewProjection( &m_mShadowViewProj );

	// パラメーター更新
	pVariable->Update();

	// パス開始
	pEffect->Begin();

	// レンダリング
	for ( Sint32 i = 0; i < PROJECTION_SHADOW_PRIORITY_MAX; i++ )
	{
		// ピクセルマスク
		const Bool *pTbl = g_vProjectionWriteMaskTbl[i];
		m_pRender->SetColorWriteEnable( pTbl[3], pTbl[0], pTbl[1], pTbl[2] );
		// レンダリング
		m_pRender->SetTexture( TEXTURE_STAGE_COLOR, m_pTextureShadowProjection );
		((CParticleActor*)m_pActorShadow[i])->RenderingDirect();
	}

	// パス終了
	pEffect->End();

	//================================================================================================
	// モデル形状の影を落とすオブジェクトを描画
	//================================================================================================

	// テクスチャ
	m_pRender->SetTexture( TEXTURE_STAGE_LIGHT, NULL );

	// 描画
	for ( Sint32 i = ID_ALPHA_DISABLE; i <= ID_ALPHA_ENABLE; i++ )
	{
		pObj = m_pObjectList[i];
		while ( pObj != NULL )
		{
			if ( pObj->ProjectionShadowType == PROJECTION_SHADOW_DROP_SHAPE )
			{
				if ( pObj->ProjectionShadowPriority != PROJECTION_SHADOW_PRIORITY_0 )
				{
					// ShadowWorldViewProjection
					pVariable->SetShadowWorldViewProjection( &pObj->mShadowWorldViewProjection );

					// ボーンあり？
					Sint32 BoneCnt = pObj->pActor->GetBoneCount();
					if ( BoneCnt > 0 )
					{
						// BoneMatrixArray
						pVariable->SetBoneMatrixArray( pObj->pActor->GetBoneMatrixArray(), BoneCnt );
					}

					// パラメーター更新
					pVariable->Update();

					// テクニック
					switch ( pObj->pActor->GetTransformType() )
					{
					case TRANSFORM_TYPE_MODEL:
						pEffect->SetTechnique( pObj->pActor->IsSupportVertexTexture() ? TECHNIQUE_EFFECT_SHADOW_PROJECTION_SHAPE_TEXTURE : TECHNIQUE_EFFECT_SHADOW_PROJECTION_SHAPE, pObj->pActor->IsSupportVertexBone() );
						break;
					case TRANSFORM_TYPE_BILLBOARD:
						pEffect->SetTechnique( TECHNIQUE_EFFECT_SHADOW_PROJECTION, false );
						break;
					}

					// パス開始
					pEffect->Begin();

					// ピクセルマスク
					const Bool *pTbl = g_vProjectionWriteMaskTbl[pObj->ProjectionShadowPriority];
					m_pRender->SetColorWriteEnable( pTbl[3], pTbl[0], pTbl[1], pTbl[2] );

					// ストリーム
					pObj->pActor->SetStreamSource( m_pRender );

					// レンダリング
					Sint32 MtrlCnt = pObj->pActor->GetMaterialCount();
					for ( Sint32 j = 0; j < MtrlCnt; j++ )
					{
						CSceneActorMaterial &Mtrl = pObj->pActor->GetSceneRenderMaterial( j );

						// テクスチャ
						m_pRender->SetTexture( TEXTURE_STAGE_COLOR, Mtrl.GetTexture( TEXTURE_STAGE_COLOR ) );

						// MaterialColor
						pVariable->SetMaterialColor( Mtrl.GetDiffuseColor() );

						// Texture Offset
						pVariable->SetTextureOffset( Mtrl.GetTextureOffset() );

						// レンダリングステート更新
						m_pRender->SetDepthWriteEnable( Mtrl.GetZWriteEnable() );
						m_pRender->SetDepthTestEnable( Mtrl.GetZTestEnable() );

						// アルファテスト
						m_pRender->SetAlphaTestEnable( Mtrl.GetAlphaTestEnable() );
						m_pRender->SetAlphaBoundary( Mtrl.GetAlphaBoundary() );

						// カリング
						m_pRender->SetCullType( Mtrl.GetCullType() );

						Polygon += pObj->pActor->Rendering( j, m_pRender );
					}

					// パス終了
					pEffect->End();
				}
			}

			// 次
			pObj = pObj->pNext;
		}
	}

	//--------------------------------------------------
	// 描画数
	//--------------------------------------------------
	m_pCore->DrawPolygon( Polygon );

	//--------------------------------------------------
	// アルファライトON
	//--------------------------------------------------
	m_pRender->SetColorWriteEnable( true, true, true, true );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_2_0::Rendering_Shadowmap( Math::Point2DI Size )
{
	Sint32 Polygon = 0;

	//--------------------------------------------------
	// クリア
	//--------------------------------------------------
	m_pRender->Clear( 0x00000000 );
	ClearDepthBuffer();

	//--------------------------------------------------
	// シザリング
	//--------------------------------------------------
	Math::Rect2DI Rc( 1, 1, Size.x - 2, Size.y - 2 );
	m_pRender->SetScissorRect( &Rc );

	//--------------------------------------------------
	// ステート
	//--------------------------------------------------
	// レンダリングステート更新
	m_pRender->SetDepthWriteEnable( true );
	m_pRender->SetDepthTestEnable( true );

	// 描画モード
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );

	// アルファテスト
	m_pRender->SetAlphaTestEnable( true );
	m_pRender->SetAlphaBoundary( 0 );

	//================================================================================================
	// 共通変数用
	//================================================================================================
	Renderer::Shader::ShaderVariable *pVariable = Renderer::Shader::ShaderManager::GetShaderVariable();

	// ShadowMapParameter
	pVariable->SetShadowMapParameter( m_ShadowParameter );

	//================================================================================================
	// オブジェクトレンダリング
	//================================================================================================
	CCustomizedSceneRenderObject *pObj = m_pObjectList[ID_ALPHA_DISABLE];
	while ( pObj != NULL )
	{
		Renderer::Shader::ShaderEffect *pEffect = Renderer::Shader::ShaderManager::GetShaderEffect();

		// テクニック
		pEffect->SetTechnique( TECHNIQUE_EFFECT_SHADOWMAP, pObj->pActor->IsSupportVertexBone() );

		// WorldViewProjection
		pVariable->SetWorldViewProjection( &pObj->mWorldViewProjection );
		// ShadowMapTransform
		pVariable->SetShadowMapTransform( pObj->vShadowMapTransform );
		// ShadowWorldViewProjection
		pVariable->SetShadowWorldViewProjection( &pObj->mShadowWorldViewProjection );
		// ボーンあり？
		Sint32 BoneCnt = pObj->pActor->GetBoneCount();
		if ( BoneCnt > 0 )
		{
			// BoneMatrixArray
			pVariable->SetBoneMatrixArray( pObj->pActor->GetBoneMatrixArray(), BoneCnt );
		}

		// パラメーター更新
		pVariable->Update();

		// パス開始
		pEffect->Begin();

		// ストリーム
		pObj->pActor->SetStreamSource( m_pRender );

		// マテリアル単位で
		Sint32 MtrlCnt = pObj->pActor->GetMaterialCount();
		for ( Sint32 i = 0; i < MtrlCnt; i++ )
		{
			CSceneActorMaterial &Mtrl = pObj->pActor->GetSceneRenderMaterial( i );

			// カリング
			if ( Mtrl.GetCullType() == CULL_FRONT )
			{
				m_pRender->SetCullType( CULL_BACK );
			}
			ef ( Mtrl.GetCullType() == CULL_BACK )
			{
				m_pRender->SetCullType( CULL_FRONT );
			}
			else
			{
				m_pRender->SetCullType( CULL_NONE );
			}

			// レンダリング
			Polygon += pObj->pActor->Rendering( i, m_pRender );
		}

		// パス終了
		pEffect->End();

		// 次
		pObj = pObj->pNext;
	}

	//--------------------------------------------------
	// 描画数
	//--------------------------------------------------
	m_pCore->DrawPolygon( Polygon );

	//--------------------------------------------------
	// シザリング
	//--------------------------------------------------
	m_pRender->SetScissorRect( NULL );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_2_0::Rendering_Velocity( void )
{
	if ( m_pObjectList[ID_ALPHA_DISABLE] == NULL ) return;

	Sint32 Polygon = 0;

	//--------------------------------------------------
	// レンダリングステート
	//--------------------------------------------------
	// アルファテスト
	m_pRender->SetAlphaTestEnable( false );

	// レンダリングステート更新
	m_pRender->SetDepthWriteEnable( true );
	m_pRender->SetDepthTestEnable( true );

	// 描画モード
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );

	// カリング
	m_pRender->SetCullType( CULL_NONE );

	// 共通
	m_pRender->Start3D();

	//================================================================================================
	// 共通変数用
	//================================================================================================
	Renderer::Shader::ShaderVariable *pVariable = Renderer::Shader::ShaderManager::GetShaderVariable();

	// Projection
	pVariable->SetProjection( &m_mProjection );

	//================================================================================================
	// オブジェクトレンダリング
	//================================================================================================
	CCustomizedSceneRenderObject *pObj = m_pObjectList[ID_ALPHA_DISABLE];
	while ( pObj != NULL )
	{
		// ブラー
		Bool IsLight = (pObj->MotionBlurLevel == MOTION_BLUR_LIGHT) || !pObj->pActor->IsSupportVertexNormal();

		// シェーダー
		Renderer::Shader::ShaderEffect *pEffect = Renderer::Shader::ShaderManager::GetShaderEffect();

		// テクニック
		pEffect->SetTechnique( IsLight ? TECHNIQUE_EFFECT_VELOCITY_SIMPLE : TECHNIQUE_EFFECT_VELOCITY, pObj->pActor->IsSupportVertexBone() );

		if ( IsLight )
		{
			// WorldViewProjection
			pVariable->SetWorldViewProjection( &pObj->mWorldViewProjection );

			// WorldViewProjectionPrev
			pVariable->SetWorldViewProjectionPrev( &pObj->mWorldViewProjectionPrev );
		}
		else
		{
			// WorldView
			pVariable->SetWorldView( &pObj->mWorldView );

			// WorldViewPrev
			pVariable->SetWorldViewPrev( &pObj->mWorldViewPrev );
		}

		// ボーンあり？
		Sint32 BoneCnt = pObj->pActor->GetBoneCount();
		if ( BoneCnt > 0 )
		{
			// BoneMatrixArray
			pVariable->SetBoneMatrixArray( pObj->pActor->GetBoneMatrixArray(), BoneCnt );
			// BoneMatrixArray
			pVariable->SetBoneMatrixArrayPrev( pObj->pActor->GetBoneMatrixArrayPrev(), BoneCnt );
		}

		// パラメーター更新
		pVariable->Update();

		// パス開始
		pEffect->Begin();

		// ストリーム
		pObj->pActor->SetStreamSource( m_pRender );

		// レンダリング
		Polygon += pObj->pActor->Rendering_Velocity( m_pRender );

		// パス終了
		pEffect->End();

		// 次
		pObj = pObj->pNext;
	}

	//--------------------------------------------------
	// 描画数
	//--------------------------------------------------
	m_pCore->DrawPolygon( Polygon );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_2_0::Rendering_NormalDepth( void )
{
	if ( m_pObjectList[ID_ALPHA_DISABLE] == NULL ) return;

	Sint32 Polygon = 0;
	Math::Vector4D vPositionTbl[4];
	Math::Vector4D vColorTbl[4];
	Math::Matrix mTemp;
	Math::Vector4D vTemp;

	//--------------------------------------------------
	// ステート
	//--------------------------------------------------
	// アルファテスト
	m_pRender->SetAlphaTestEnable( true );
	m_pRender->SetAlphaBoundary( 0 );

	// 描画モード
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );

	// 共通
	m_pRender->Start3D();

	//================================================================================================
	// 共通変数用
	//================================================================================================
	Renderer::Shader::ShaderVariable *pVariable = Renderer::Shader::ShaderManager::GetShaderVariable();

	// DepthParameter
	pVariable->SetDepthParameter( m_DepthParameter );

	//================================================================================================
	// オブジェクトレンダリング
	//================================================================================================
	CCustomizedSceneRenderObject *pObj = m_pObjectList[ID_ALPHA_DISABLE];
	while ( pObj != NULL )
	{
		Renderer::Shader::ShaderEffect *pEffect = Renderer::Shader::ShaderManager::GetShaderEffect();

		// テクニック
		pEffect->SetTechnique( TECHNIQUE_EFFECT_NORMAL_DEPTH, pObj->pActor->IsSupportVertexBone() );

		// World
		pVariable->SetWorld( &pObj->pActor->GetWorldMatrix() );

		// WorldViewProjection
		pVariable->SetWorldViewProjection( &pObj->mWorldViewProjection );

		// ボーンあり？
		Sint32 BoneCnt = pObj->pActor->GetBoneCount();
		if ( BoneCnt > 0 )
		{
			// BoneMatrixArray
			pVariable->SetBoneMatrixArray( pObj->pActor->GetBoneMatrixArray(), BoneCnt );
		}

		// パラメーター更新
		pVariable->Update();

		// データストリーム
		pObj->pActor->SetStreamSource( m_pRender );

		// マテリアル単位で
		Sint32 MtrlCnt = pObj->pActor->GetMaterialCount();
		for ( Sint32 j = 0; j < MtrlCnt; j++ )
		{
			CSceneActorMaterial &Mtrl = pObj->pActor->GetSceneRenderMaterial( j );

			// レンダリングステート更新
			m_pRender->SetDepthWriteEnable( Mtrl.GetZWriteEnable() );
			m_pRender->SetDepthTestEnable( Mtrl.GetZTestEnable() );

			// カリング
			m_pRender->SetCullType( Mtrl.GetCullType() );

			// パス開始
			pEffect->Begin();

			// レンダリング
			Polygon += pObj->pActor->Rendering( j, m_pRender );

			// パス終了
			pEffect->End();
		}

		// 次
		pObj = pObj->pNext;
	}

	//--------------------------------------------------
	// 描画数
	//--------------------------------------------------
	m_pCore->DrawPolygon( Polygon );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_2_0::Rendering_AlphaDisable( void )
{
	if ( (m_pObjectList[ID_SKYDOOM] == NULL) && (m_pObjectList[ID_ALPHA_DISABLE] == NULL) ) return;

	Renderer::Shader::ShaderVariable *pVariable = Renderer::Shader::ShaderManager::GetShaderVariable();

	Uint32 ActiveShaderID = 0xFFFFFFFF;
	Renderer::Shader::CShader *pActiveShader = NULL;
	Sint32 Polygon = 0;
	Math::Vector4D vPositionTbl[4];
	Math::Vector4D vColorTbl[4];
	Math::Matrix mTemp;
	Math::Vector4D vTemp;
	Renderer::ITexture *pTex;

	//--------------------------------------------------
	// シャドウマップON/OFF
	//--------------------------------------------------
	Bool IsShadow = IsShadowEnable();

	//--------------------------------------------------
	// Toon ON/OFF
	//--------------------------------------------------
	Bool IsToon = m_ShadingType != SHADING_TYPE_NORMAL;

	// 共通
	m_pRender->Start3D();

	//================================================================================================
	// 共通変数用
	//================================================================================================

	// FogParameter
	if ( IsFogEnable() )
	{
		pVariable->SetFogParameter( m_FogParameter );
		pVariable->SetFogColor( m_FogColor );
	}

	// ShadowMapParameter
	if ( IsShadow )
	{
		pVariable->SetShadowMapParameter( m_ShadowParameter );
	}

	// ToonParameter
	if ( IsToon )
	{
		pVariable->SetToonParameter( m_vToonRenderParameter );
	}

	// DepthParameter
	pVariable->SetDepthParameter( m_DepthParameter );

	//--------------------------------------------------
	// ライト
	//--------------------------------------------------
	// AmbientLightColorSky
	pVariable->SetLightParameter_AmbientColorSky( m_vLightColor[LIGHT_AMBIENT_SKY] );

	// AmbientLightColorEarth
	pVariable->SetLightParameter_AmbientColorEarth( m_vLightColor[LIGHT_AMBIENT_EARTH] );

	// DirectionalLightColor
	pVariable->SetDirectionalLightColor( m_vLightColor[LIGHT_DIRECTION] );

	//================================================================================================
	// オブジェクトレンダリング
	//================================================================================================
	for ( Sint32 i = 0; i <= ID_ALPHA_DISABLE; i++ )
	{
		CCustomizedSceneRenderObject *pObj = m_pObjectList[i];
		while ( pObj != NULL )
		{
			// WorldViewProjection
			pVariable->SetWorldViewProjection( &pObj->mWorldViewProjection );

			// シャドウマップあり？
			if ( IsShadow )
			{
				// ShadowMapTransform
				pVariable->SetShadowMapTransform( pObj->vShadowMapTransform );
				// ShadowWorldViewProjection
				pVariable->SetShadowWorldViewProjection( &pObj->mShadowWorldViewProjection );
				// パラメーター
				if ( pObj->ProjectionShadowType != PROJECTION_SHADOW_DISABLE )
				{
					pVariable->SetShadowMapParameter( g_vProjectionReadMaskTbl[pObj->ProjectionShadowPriority] );
				}
			}

			// CameraPosition
			if ( pObj->pActor->GetParallaxEnable() || pObj->pActor->GetSpecularEnable() || pObj->pActor->GetEnvironmentEnable() )
			{
				vTemp.TransformCoord( m_Camera.Position(), pObj->pActor->GetWorldInverseMatrix() );
				pVariable->SetCameraPosition( vTemp );
			}

			// World
			if ( pObj->pActor->GetEnvironmentEnable() )
			{
				pVariable->SetWorld( &pObj->pActor->GetWorldMatrix() );
			}

			// ライトあり？
			if ( pObj->pActor->IsSupportVertexNormal() )
			{
				// DirectionalLightDirection
				pVariable->SetDirectionalLightDirection( pObj->vLightDiection );
				// PointLight Count
				pVariable->SetPointLightCount( pObj->PointLightCount );
				// ポイントライトあり？
				if ( pObj->PointLightCount > 0 )
				{
					// PointLightPosition
					pVariable->SetPointLightPosition( pObj->vPointLightPositionTbl, pObj->PointLightCount );
					pVariable->SetPointLightColor( pObj->vPointLightColorTbl, pObj->PointLightCount );
				}
			}

			// ボーンあり？
			Sint32 BoneCnt = pObj->pActor->GetBoneCount();
			if ( BoneCnt > 0 )
			{
				// BoneMatrixArray
				pVariable->SetBoneMatrixArray( pObj->pActor->GetBoneMatrixArray(), BoneCnt );
			}

			// データストリーム
			pObj->pActor->SetStreamSource( m_pRender );

			// マテリアル単位で
			Sint32 MtrlCnt = pObj->pActor->GetMaterialCount();
			for ( Sint32 j = 0; j < MtrlCnt; j++ )
			{
				CSceneActorMaterial &Mtrl = pObj->pActor->GetSceneRenderMaterial( j );
				Renderer::Shader::CShader *pShader = (Renderer::Shader::CShader*)Mtrl.GetShader();

				if ( pShader == NULL ) continue;

				// シェーダー変更
				if ( ActiveShaderID != pShader->GetID() )
				{
					ActiveShaderID = pShader->GetID();
					// 古いの終了
					if ( pActiveShader != NULL )
					{
						pActiveShader->SimpleEnd();
					}
					// 新しいの開始
					pActiveShader = pShader;
					pActiveShader->SimpleBegin();
				}

				Math::Vector3D vBrightness = pObj->vBrightness;

				// カラーテクスチャ
				pTex = Mtrl.GetTexture( TEXTURE_STAGE_COLOR );
				m_pRender->SetTexture( TEXTURE_STAGE_COLOR, pTex );

				// ライトマップ
				if ( !IsToon )
				{
					pTex = Mtrl.GetTexture( TEXTURE_STAGE_LIGHT );
					m_pRender->SetTexture( TEXTURE_STAGE_LIGHT, pTex );
					if ( pTex != NULL )
					{
						vBrightness *= 2.0f;
					}
				}

				// 環境マップ
				if ( !IsToon )
				{
					pTex = Mtrl.GetTexture( TEXTURE_STAGE_ENVIRONMENT );
					m_pRender->SetTexture( TEXTURE_STAGE_ENVIRONMENT, pTex );
					if ( pTex != NULL )
					{
						vBrightness *= 2.0f;
					}
				}

				// バンプマップ
				if ( Mtrl.GetBumpType() != BUMP_TYPE_NONE )
				{
					pTex = Mtrl.GetTexture( TEXTURE_STAGE_NORMAL );
					m_pRender->SetTexture( TEXTURE_STAGE_NORMAL, pTex );

					// ParallaxDepth
					pVariable->SetParallaxDepth( Mtrl.GetParallaxDepth() );
				}

				// スペキュラマップ
				if ( Mtrl.GetSpecularType() != SPECULAR_TYPE_NONE )
				{
					pTex = Mtrl.GetTexture( TEXTURE_STAGE_SPECULAR );
					m_pRender->SetTexture( TEXTURE_STAGE_SPECULAR, pTex );

					// SpecularColor
					pVariable->SetSpecularColor( Mtrl.GetSpecularColor() );
					// Specular Refractive
					pVariable->SetRefractive( Mtrl.GetSpecularRefractive() );
					// Specular Roughly
					pVariable->SetRoughly( Mtrl.GetSpecularRoughly() );
				}

				// MaterialColor
				vTemp.x = Mtrl.GetDiffuseColor().x * vBrightness.x;
				vTemp.y = Mtrl.GetDiffuseColor().y * vBrightness.y;
				vTemp.z = Mtrl.GetDiffuseColor().z * vBrightness.z;
				vTemp.w = Mtrl.GetDiffuseColor().w;
				pVariable->SetMaterialColor( vTemp );

				// EmissiveColor
				pVariable->SetEmissiveColor( Mtrl.GetEmissiveColor() );

				// Texture Offset
				pVariable->SetTextureOffset( Mtrl.GetTextureOffset() );

				// パラメーター更新
				pVariable->Update();

				// レンダリングステート更新
				m_pRender->SetDepthWriteEnable( Mtrl.GetZWriteEnable() );
				m_pRender->SetDepthTestEnable( Mtrl.GetZTestEnable() );

				// アルファテスト
				m_pRender->SetAlphaTestEnable( Mtrl.GetAlphaTestEnable() );
				m_pRender->SetAlphaBoundary( Mtrl.GetAlphaBoundary() );

				// カリング
				m_pRender->SetCullType( Mtrl.GetCullType() );

				// 描画モード
				m_pRender->SetDrawType( Mtrl.GetDrawType() );

				// パス開始
				pActiveShader->BeginPass( 0 );
				Polygon += pObj->pActor->Rendering( j, m_pRender );
				pActiveShader->EndPass();
			}
		
			// 次
			pObj = pObj->pNext;
		}
	}

	// 終わり
	if ( pActiveShader != NULL )
	{
		pActiveShader->SimpleEnd();
	}

	//--------------------------------------------------
	// 描画数
	//--------------------------------------------------
	m_pCore->DrawPolygon( Polygon );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_2_0::Rendering_AlphaEnable( void )
{
	if ( m_pObjectList[ID_ALPHA_ENABLE] == NULL ) return;

	Renderer::Shader::ShaderVariable *pVariable = Renderer::Shader::ShaderManager::GetShaderVariable();

	Uint32 ActiveShaderID = 0xFFFFFFFF;
	Renderer::Shader::CShader *pActiveShader = NULL;
	Sint32 Polygon = 0;
	Math::Vector4D vPositionTbl[4];
	Math::Vector4D vColorTbl[4];
	Math::Matrix mTemp;
	Math::Vector4D vTemp;
	Renderer::ITexture *pTex;

	//--------------------------------------------------
	// 共通パラメーター
	//--------------------------------------------------
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_TOON, TEXTURE_FILTER_2D );
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_DEPTH, TEXTURE_FILTER_2D );
	m_pRender->SetTexture( TEXTURE_STAGE_DEPTH, m_pRT_NormalDepth );

	//--------------------------------------------------
	// シャドウマップON/OFF
	//--------------------------------------------------
	Bool IsShadow = IsShadowEnable();

	//--------------------------------------------------
	// Toon ON/OFF
	//--------------------------------------------------
	Bool IsToon = m_ShadingType != SHADING_TYPE_NORMAL;

	// 共通
	m_pRender->Start3D();

	//--------------------------------------------------
	// アルファ書き込みOFF
	//--------------------------------------------------
	m_pRender->SetColorWriteEnable( false, true, true, true );

	//================================================================================================
	// 共通変数用
	//================================================================================================

	// ShadowMapParameter
	if ( IsShadow )
	{
		pVariable->SetShadowMapParameter( m_ShadowParameter );
	}

	// ToonParameter
	if ( IsToon )
	{
		pVariable->SetToonParameter( m_vToonRenderParameter );
	}

	// DepthParameter
	pVariable->SetDepthParameter( m_DepthParameter );

	// カメラの逆変換
	Math::Matrix mViewInverse;
	mViewInverse.Transpose( m_Camera.WorldToView() );
	pVariable->SetViewInverse( &mViewInverse );

	//--------------------------------------------------
	// ライト
	//--------------------------------------------------
	// AmbientLightColorSky
	pVariable->SetLightParameter_AmbientColorSky( m_vLightColor[LIGHT_AMBIENT_SKY] );

	// AmbientLightColorEarth
	pVariable->SetLightParameter_AmbientColorEarth( m_vLightColor[LIGHT_AMBIENT_EARTH] );

	// DirectionalLightColor
	pVariable->SetDirectionalLightColor( m_vLightColor[LIGHT_DIRECTION] );

	//================================================================================================
	// オブジェクトレンダリング
	//================================================================================================
	CCustomizedSceneRenderObject *pObj = m_pObjectList[ID_ALPHA_ENABLE];
	while ( pObj != NULL )
	{
		// PointLight Count
		pVariable->SetPointLightCount( pObj->PointLightCount );

		// WorldViewProjection
		pVariable->SetWorldViewProjection( &pObj->mWorldViewProjection );

		// シャドウマップあり？
		if ( IsShadow )
		{
			// ShadowMapTransform
			pVariable->SetShadowMapTransform( pObj->vShadowMapTransform );
			// ShadowWorldViewProjection
			pVariable->SetShadowWorldViewProjection( &pObj->mShadowWorldViewProjection );
			// パラメーター
			if ( pObj->ProjectionShadowType != PROJECTION_SHADOW_DISABLE )
			{
				pVariable->SetShadowMapParameter( g_vProjectionReadMaskTbl[pObj->ProjectionShadowPriority] );
			}
		}

		// CameraPosition
		if ( pObj->pActor->GetParallaxEnable() || pObj->pActor->GetSpecularEnable() || pObj->pActor->GetEnvironmentEnable() )
		{
			vTemp.TransformCoord( m_Camera.Position(), pObj->pActor->GetWorldInverseMatrix() );
			pVariable->SetCameraPosition( vTemp );
		}

		// World
		if ( pObj->pActor->GetEnvironmentEnable() )
		{
			pVariable->SetWorld( &pObj->pActor->GetWorldMatrix() );
		}

		// ライトあり？
		if ( pObj->pActor->IsSupportVertexNormal() )
		{
			// DirectionalLightDirection
			pVariable->SetDirectionalLightDirection( pObj->vLightDiection );
			// ポイントライトあり？
			if ( pObj->PointLightCount > 0 )
			{
				// PointLightPosition & PointLightColor
				pVariable->SetPointLightPosition( pObj->vPointLightPositionTbl, pObj->PointLightCount );
				pVariable->SetPointLightColor( pObj->vPointLightColorTbl, pObj->PointLightCount );
			}
		}

		// ボーンあり？
		Sint32 BoneCnt = pObj->pActor->GetBoneCount();
		if ( BoneCnt > 0 )
		{
			// BoneMatrixArray
			pVariable->SetBoneMatrixArray( pObj->pActor->GetBoneMatrixArray(), BoneCnt );
		}

		// データストリーム
		pObj->pActor->SetStreamSource( m_pRender );

		// マテリアル単位で
		Sint32 MtrlCnt = pObj->pActor->GetMaterialCount();
		for ( Sint32 j = 0; j < MtrlCnt; j++ )
		{
			CSceneActorMaterial &Mtrl = pObj->pActor->GetSceneRenderMaterial( j );
			Renderer::Shader::CShader *pShader = (Renderer::Shader::CShader*)Mtrl.GetShader();

			if ( pShader == NULL ) continue;

			// シェーダー変更
			if ( ActiveShaderID != pShader->GetID() )
			{
				ActiveShaderID = pShader->GetID();
				// 古いの終了
				if ( pActiveShader != NULL )
				{
					pActiveShader->SimpleEnd();
				}
				// 新しいの開始
				pActiveShader = pShader;
				pActiveShader->SimpleBegin();
			}

			Math::Vector3D vBrightness = pObj->vBrightness;

			// カラーテクスチャ
			pTex = Mtrl.GetTexture( TEXTURE_STAGE_COLOR );
			m_pRender->SetTexture( TEXTURE_STAGE_COLOR, pTex );

			// ライトマップ
			if ( !IsToon )
			{
				pTex = Mtrl.GetTexture( TEXTURE_STAGE_LIGHT );
				m_pRender->SetTexture( TEXTURE_STAGE_LIGHT, pTex );
				if ( pTex != NULL )
				{
					vBrightness *= 2.0f;
				}
			}

			// 環境マップ
			if ( !IsToon )
			{
				pTex = Mtrl.GetTexture( TEXTURE_STAGE_ENVIRONMENT );
				m_pRender->SetTexture( TEXTURE_STAGE_ENVIRONMENT, pTex );
				if ( pTex != NULL )
				{
					vBrightness *= 2.0f;
				}
			}

			// バンプマップ
			if ( Mtrl.GetBumpType() != BUMP_TYPE_NONE )
			{
				pTex = Mtrl.GetTexture( TEXTURE_STAGE_NORMAL );
				m_pRender->SetTexture( TEXTURE_STAGE_NORMAL, pTex );

				// ParallaxDepth
				pVariable->SetParallaxDepth( Mtrl.GetParallaxDepth() );
			}

			// スペキュラマップ
			if ( Mtrl.GetSpecularType() != SPECULAR_TYPE_NONE )
			{
				pTex = Mtrl.GetTexture( TEXTURE_STAGE_SPECULAR );
				m_pRender->SetTexture( TEXTURE_STAGE_SPECULAR, pTex );

				// SpecularColor
				pVariable->SetSpecularColor( Mtrl.GetSpecularColor() );
				// Specular Refractive
				pVariable->SetRefractive( Mtrl.GetSpecularRefractive() );
				// Specular Roughly
				pVariable->SetRoughly( Mtrl.GetSpecularRoughly() );
			}

			// MaterialColor
			vTemp.x = Mtrl.GetDiffuseColor().x * vBrightness.x;
			vTemp.y = Mtrl.GetDiffuseColor().y * vBrightness.y;
			vTemp.z = Mtrl.GetDiffuseColor().z * vBrightness.z;
			vTemp.w = Mtrl.GetDiffuseColor().w;
			pVariable->SetMaterialColor( vTemp );

			// EmissiveColor
			pVariable->SetEmissiveColor( Mtrl.GetEmissiveColor() );

			// Texture Offset
			pVariable->SetTextureOffset( Mtrl.GetTextureOffset() );

			// パラメーター更新
			pVariable->Update();

			// レンダリングステート更新
			m_pRender->SetDepthWriteEnable( Mtrl.GetZWriteEnable() );
			m_pRender->SetDepthTestEnable( Mtrl.GetZTestEnable() );

			// アルファテスト
			m_pRender->SetAlphaTestEnable( Mtrl.GetAlphaTestEnable() );
			m_pRender->SetAlphaBoundary( Mtrl.GetAlphaBoundary() );

			// カリング
			m_pRender->SetCullType( Mtrl.GetCullType() );

			// 描画モード
			m_pRender->SetDrawType( Mtrl.GetDrawType() );

			// レンダリング
			pActiveShader->BeginPass( 0 );
			Polygon += pObj->pActor->Rendering( j, m_pRender );
			pActiveShader->EndPass();
		}

		// 次
		pObj = pObj->pNext;
	}

	// 終わり
	if ( pActiveShader != NULL )
	{
		pActiveShader->SimpleEnd();
	}

	//--------------------------------------------------
	// アルファ書き込みする
	//--------------------------------------------------
	m_pRender->SetColorWriteEnable( true, true, true, true );

	//--------------------------------------------------
	// 描画数
	//--------------------------------------------------
	m_pCore->DrawPolygon( Polygon );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_2_0::PostEffectEDGE( void )
{
	m_pRender->SetDrawType( DRAW_TYPE_SUB );
	m_pRender->SetColorWriteEnable( false, true, true, true );
	Renderer::Shader::ShaderManager::GetPostEffect()->NormalDepthEdge( m_pRender->GetViewport(), m_pRT_NormalDepth, m_fEdgeNormalPower, m_fEdgeDepthPower, m_IsToonBold );
	m_pRender->SetColorWriteEnable( true, true, true, true );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_2_0::PostEffectDOF( void )
{
	if ( !IsDepthOfFieldEnable() ) return;

	Math::Rect2DF Dst, Src;

	//------------------------------------------------------------------------
	// 縮小画像生成
	//------------------------------------------------------------------------
	m_pRender->SetRenderTarget( m_pRT_Small );
	m_pRender->SetDepthBuffer( NULL );

	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
	Renderer::Shader::ShaderManager::GetPostEffect()->DOF_DownSample( m_pRender->GetViewport(), m_pRT_Temp, m_pRT_NormalDepth, m_fFocusDepth, m_fFocusPower );

	//------------------------------------------------------------------------
	// 4x4フィルタ画像生成
	//------------------------------------------------------------------------
	m_pRender->SetRenderTarget( m_pRT_Blur );
	m_pRender->SetDepthBuffer( NULL );

	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
	Renderer::Shader::ShaderManager::GetPostEffect()->DOF_Blur( m_pRender->GetViewport(), m_pRT_Small );

	//------------------------------------------------------------------------
	// ターゲット
	//------------------------------------------------------------------------
	m_pRender->SetRenderTarget( m_pRT_Temp );
	m_pRender->SetDepthBuffer( NULL );
	m_pRender->SetDrawType( DRAW_TYPE_BLEND );
	m_pRender->SetColorWriteEnable( false, true, true, true );

	//------------------------------------------------------------------------
	// 被写界深度処理
	//------------------------------------------------------------------------
	switch ( m_DofType )
	{
	case DOF_TYPE_LOW:
		//------------------------------------------------------------------------
		// 描画
		//------------------------------------------------------------------------
		Renderer::Shader::ShaderManager::GetPostEffect()->DOF_UpSample( m_pRender->GetViewport(), m_pRT_Blur );
		break;

	case DOF_TYPE_HIGH:
		//------------------------------------------------------------------------
		// 描画
		//------------------------------------------------------------------------
		Renderer::ITexture *pTexTbl[] = {
			m_pRT_Small,
			m_pRT_Blur,
		};
		Renderer::Shader::ShaderManager::GetPostEffect()->DOF_Effect( m_pRender->GetViewport(), pTexTbl );
		break;
	}

	//------------------------------------------------------------------------
	// ステート
	//------------------------------------------------------------------------
	m_pRender->SetColorWriteEnable( true, true, true, true );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_2_0::PostEffectHDR( void )
{
	Math::Rect2DF Dst, Src;

	//------------------------------------------------------------------------
	// 描画
	//------------------------------------------------------------------------
	switch ( m_HdrType )
	{
	case HDR_TYPE_DISABLE:
		//------------------------------------------------------------------------
		// ターゲット
		//------------------------------------------------------------------------
		m_pRender->SetRenderTarget( m_pRenderTarget );
		m_pRender->SetDepthBuffer( NULL );

		//------------------------------------------------------------------------
		// ターゲットに描画(-> Target)
		//------------------------------------------------------------------------
		m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
		Renderer::Shader::ShaderManager::GetPostEffect()->Simple( m_pRender->GetViewport(), m_pRT_Temp );
		break;

	case HDR_TYPE_ENABLE:
		switch ( m_HdrEffect )
		{
		case HDR_EFFECT_BLOOM:
			// 高輝度部分抽出(Target -> HDR)
			m_pRender->SetRenderTarget( m_pRT_HDR );
			Renderer::Shader::ShaderManager::GetPostEffect()->HDR_DownSample( m_pRender->GetViewport(), m_pRT_Temp, m_fHDRPower, m_fHDRBoundary );

			// 縮小バッファ
			m_pRender->SetRenderTarget( m_pRT_HDR1 );
			Renderer::Shader::ShaderManager::GetPostEffect()->DownSample( m_pRender->GetViewport(), m_pRT_HDR );
			// ガウス(HDR -> A)
			m_pRender->SetRenderTarget( m_pRT_HDR1_GausA );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR1, DEG_TO_ANGLE(0) );
			// ガウス(A -> B)
			m_pRender->SetRenderTarget( m_pRT_HDR1_GausB );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR1_GausA, DEG_TO_ANGLE(90) );

			// 縮小バッファ
			m_pRender->SetRenderTarget( m_pRT_HDR2 );
			Renderer::Shader::ShaderManager::GetPostEffect()->DownSample( m_pRender->GetViewport(), m_pRT_HDR1_GausB );
			// ガウス(HDR -> A)
			m_pRender->SetRenderTarget( m_pRT_HDR2_GausA );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR2, DEG_TO_ANGLE(-45) );
			// ガウス(A -> B)
			m_pRender->SetRenderTarget( m_pRT_HDR2_GausB );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR2_GausA, DEG_TO_ANGLE(+45) );

			// 縮小バッファ
			m_pRender->SetRenderTarget( m_pRT_HDR3 );
			Renderer::Shader::ShaderManager::GetPostEffect()->DownSample( m_pRender->GetViewport(), m_pRT_HDR2_GausB );
			// ガウス(HDR -> A)
			m_pRender->SetRenderTarget( m_pRT_HDR3_GausA );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR3, DEG_TO_ANGLE(0) );
			// ガウス(A -> B)
			m_pRender->SetRenderTarget( m_pRT_HDR3_GausB );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR3_GausA, DEG_TO_ANGLE(90) );

			//------------------------------------------------------------------------
			// ターゲット
			//------------------------------------------------------------------------
			m_pRender->SetRenderTarget( m_pRenderTarget );
			m_pRender->SetDepthBuffer( NULL );

			//------------------------------------------------------------------------
			// ターゲットに描画(-> Target)
			//------------------------------------------------------------------------
			{
				Renderer::ITexture *pTexTbl[] = {
					m_pRT_Temp,
					m_pRT_HDR1_GausB,
					m_pRT_HDR2_GausB,
					m_pRT_HDR3_GausB,
				};

				m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
				Renderer::Shader::ShaderManager::GetPostEffect()->HDR_BloomFx( m_pRender->GetViewport(), pTexTbl );
			}
			break;

		case HDR_EFFECT_CROSS:
			// 高輝度部分抽出(Target -> HDR)
			m_pRender->SetRenderTarget( m_pRT_HDR );
			Renderer::Shader::ShaderManager::GetPostEffect()->HDR_DownSample( m_pRender->GetViewport(), m_pRT_Temp, m_fHDRPower, m_fHDRBoundary );

			// 縮小バッファ
			m_pRender->SetRenderTarget( m_pRT_HDR1 );
			Renderer::Shader::ShaderManager::GetPostEffect()->DownSample( m_pRender->GetViewport(), m_pRT_HDR );
			// ガウス(HDR -> A)
			m_pRender->SetRenderTarget( m_pRT_HDR1_GausA );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR1, DEG_TO_ANGLE(-45) );
			// 縮小バッファ
			m_pRender->SetRenderTarget( m_pRT_HDR2 );
			Renderer::Shader::ShaderManager::GetPostEffect()->DownSample( m_pRender->GetViewport(), m_pRT_HDR1_GausA );
			// ガウス(HDR -> A)
			m_pRender->SetRenderTarget( m_pRT_HDR2_GausA );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR2, DEG_TO_ANGLE(-45) );
			// 縮小バッファ
			m_pRender->SetRenderTarget( m_pRT_HDR3 );
			Renderer::Shader::ShaderManager::GetPostEffect()->DownSample( m_pRender->GetViewport(), m_pRT_HDR2_GausA );
			// ガウス(HDR -> A)
			m_pRender->SetRenderTarget( m_pRT_HDR3_GausA );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR3, DEG_TO_ANGLE(-45) );

			// 縮小バッファ
			m_pRender->SetRenderTarget( m_pRT_HDR1 );
			Renderer::Shader::ShaderManager::GetPostEffect()->DownSample( m_pRender->GetViewport(), m_pRT_HDR );
			// ガウス(A -> B)
			m_pRender->SetRenderTarget( m_pRT_HDR1_GausB );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR1, DEG_TO_ANGLE(+45) );
			// 縮小バッファ
			m_pRender->SetRenderTarget( m_pRT_HDR2 );
			Renderer::Shader::ShaderManager::GetPostEffect()->DownSample( m_pRender->GetViewport(), m_pRT_HDR1_GausB );
			// ガウス(A -> B)
			m_pRender->SetRenderTarget( m_pRT_HDR2_GausB );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR2, DEG_TO_ANGLE(+45) );
			// 縮小バッファ
			m_pRender->SetRenderTarget( m_pRT_HDR3 );
			Renderer::Shader::ShaderManager::GetPostEffect()->DownSample( m_pRender->GetViewport(), m_pRT_HDR2_GausB );
			// ガウス(A -> B)
			m_pRender->SetRenderTarget( m_pRT_HDR3_GausB );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR3, DEG_TO_ANGLE(+45) );

			//------------------------------------------------------------------------
			// ターゲット
			//------------------------------------------------------------------------
			m_pRender->SetRenderTarget( m_pRenderTarget );
			m_pRender->SetDepthBuffer( NULL );

			//------------------------------------------------------------------------
			// ターゲットに描画(-> Target)
			//------------------------------------------------------------------------
			{
				Renderer::ITexture *pTexTbl[] = {
					m_pRT_Temp,
					m_pRT_HDR2_GausA,
					m_pRT_HDR2_GausB,
					m_pRT_HDR3_GausA,
					m_pRT_HDR3_GausB,
				};

				m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
				Renderer::Shader::ShaderManager::GetPostEffect()->HDR_CrossFx( m_pRender->GetViewport(), pTexTbl );
			}
			break;
		}
		break;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_2_0::CreateRenderTargetBuffer( void )
{
	//-----------------------------------------------------------------------
	// 深度バッファ
	//-----------------------------------------------------------------------
	m_pDS_Normal = (Renderer::CDepthTexture*)m_pRender->CreateTextureDepthBuffer( m_TargetSize.x, m_TargetSize.y );

	//-----------------------------------------------------------------------
	// 基本描画ターゲット
	//-----------------------------------------------------------------------
	// ターゲット
	m_pRT_Final			= m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y, FORMAT_TARGET_UCHAR4 );
	m_pRT_Temp			= m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y, FORMAT_TARGET_UCHAR4 );
	m_pRT_NormalDepth	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y, FORMAT_TARGET_UCHAR4 );

	//-----------------------------------------------------------------------
	// HDR画像
	//-----------------------------------------------------------------------
	if ( m_HdrType != HDR_TYPE_DISABLE )
	{
		m_pRT_HDR			= m_pRender->CreateTextureRenderTarget( m_TargetSize.x /  2, m_TargetSize.y /  2, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR1			= m_pRender->CreateTextureRenderTarget( m_TargetSize.x /  4, m_TargetSize.y /  4, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR1_GausA	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x /  4, m_TargetSize.y /  4, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR1_GausB	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x /  4, m_TargetSize.y /  4, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR2			= m_pRender->CreateTextureRenderTarget( m_TargetSize.x /  8, m_TargetSize.y /  8, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR2_GausA	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x /  8, m_TargetSize.y /  8, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR2_GausB	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x /  8, m_TargetSize.y /  8, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR3			= m_pRender->CreateTextureRenderTarget( m_TargetSize.x / 16, m_TargetSize.y / 16, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR3_GausA	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x / 16, m_TargetSize.y / 16, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR3_GausB	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x / 16, m_TargetSize.y / 16, FORMAT_TARGET_UCHAR4 );
		if ( m_pRT_HDR->IsInvalid() ||
			m_pRT_HDR1->IsInvalid() || m_pRT_HDR2->IsInvalid() || m_pRT_HDR3->IsInvalid() ||
			m_pRT_HDR1_GausA->IsInvalid() || m_pRT_HDR1_GausB->IsInvalid() ||
			m_pRT_HDR2_GausA->IsInvalid() || m_pRT_HDR2_GausB->IsInvalid() ||
			m_pRT_HDR3_GausA->IsInvalid() || m_pRT_HDR3_GausB->IsInvalid() )
		{
			m_HdrType = HDR_TYPE_DISABLE;
			SAFE_RELEASE( m_pRT_HDR );
			SAFE_RELEASE( m_pRT_HDR1 );
			SAFE_RELEASE( m_pRT_HDR2 );
			SAFE_RELEASE( m_pRT_HDR3 );
			SAFE_RELEASE( m_pRT_HDR1_GausA );
			SAFE_RELEASE( m_pRT_HDR1_GausB );
			SAFE_RELEASE( m_pRT_HDR2_GausA );
			SAFE_RELEASE( m_pRT_HDR2_GausB );
			SAFE_RELEASE( m_pRT_HDR3_GausA );
			SAFE_RELEASE( m_pRT_HDR3_GausB );
		}
	}

	//-----------------------------------------------------------------------
	// 速度マップ
	//-----------------------------------------------------------------------
	if ( m_MotionBlurType != MOTION_BLUR_TYPE_DISABLE )
	{
		m_pRT_Velocity = m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y, FORMAT_TARGET_FLOAT4 );
		if ( m_pRT_Velocity->IsInvalid() )
		{
			SAFE_RELEASE( m_pRT_Velocity );
			m_MotionBlurType = MOTION_BLUR_TYPE_DISABLE;
		}
	}

	//-----------------------------------------------------------------------
	// 被写界深度
	//-----------------------------------------------------------------------
	switch ( m_DofType )
	{
	case DOF_TYPE_LOW:
	case DOF_TYPE_HIGH:
		// ターゲット
		m_pRT_Small	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x / 2, m_TargetSize.y / 2, FORMAT_TARGET_UCHAR4 );
		m_pRT_Blur	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x / 2, m_TargetSize.y / 2, FORMAT_TARGET_UCHAR4 );
		// 失敗？
		if ( m_pRT_Blur->IsInvalid() || m_pRT_Small->IsInvalid() )
		{
			SAFE_RELEASE( m_pRT_Blur );
			SAFE_RELEASE( m_pRT_Small );
			m_DofType = DOF_TYPE_DISABLE;
		}
		break;
	}

	//-----------------------------------------------------------------------
	// シャドウマップ用
	//-----------------------------------------------------------------------
	const Sint32 ShadowSizeTbl[] = { 512, 1024, 2048, 4096 };
	switch ( m_ShadowType )
	{
	case SHADOW_TYPE_SHADOWMAP:
		{
			Sint32 w = ShadowSizeTbl[m_ShadowQuarity];
			Sint32 h = ShadowSizeTbl[m_ShadowQuarity];

			// 深度バッファ
			m_pDS_Shadow = (Renderer::CDepthTexture*)m_pRender->CreateTextureDepthBuffer( w, h );

			// レンダリンシャドウマップ
			m_pRT_Shadow = m_pRender->CreateTextureRenderTarget( w, h, FORMAT_TARGET_FLOAT1 );

			// 失敗？
			if ( (m_pDS_Shadow == NULL) || m_pRT_Shadow->IsInvalid() )
			{
				SAFE_RELEASE( m_pDS_Shadow );
				SAFE_RELEASE( m_pRT_Shadow );
				// 影OFF
				m_ShadowType = SHADOW_TYPE_DISABLE;
			}

			m_pRender->SetRenderTarget( m_pRT_Shadow );
			m_pRender->Clear( CColor( 0, 0, 0, 0 ) );
			m_pRender->SetRenderTarget( NULL );
		}
		break;

	case SHADOW_TYPE_PROJECTION:
		{
			Sint32 w = ShadowSizeTbl[m_ShadowQuarity];
			Sint32 h = ShadowSizeTbl[m_ShadowQuarity];

			// レンダリンシャドウマップ
			m_pRT_Shadow     = m_pRender->CreateTextureRenderTarget( w, h, FORMAT_TARGET_UCHAR4 );
			m_pRT_ShadowSoft = m_pRender->CreateTextureRenderTarget( w / 2, h / 2, FORMAT_TARGET_UCHAR4 );

			// 失敗？
			if ( m_pRT_Shadow->IsInvalid() || m_pRT_ShadowSoft->IsInvalid() )
			{
				SAFE_RELEASE( m_pRT_ShadowSoft );
				SAFE_RELEASE( m_pRT_Shadow );
				// 影OFF
				m_ShadowType = SHADOW_TYPE_DISABLE;
			}

			// 影レンダリング用
			for ( Sint32 i = 0; i < PROJECTION_SHADOW_PRIORITY_MAX; i++ )
			{
				m_pParticleShadow[i] = m_pRender->CreateParticle( m_QueMax * MAX_BONE_COUNT, m_pTextureShadowProjection, PARTICLE_TYPE_NORMAL, false );
				m_pActorShadow[i] = CreateActor( m_pParticleShadow[i] );
			}

			m_pRender->SetRenderTarget( m_pRT_ShadowSoft );
			m_pRender->Clear( CColor( 0, 0, 0, 0 ) );
			m_pRender->SetRenderTarget( m_pRT_Shadow );
			m_pRender->Clear( CColor( 0, 0, 0, 0 ) );
			m_pRender->SetRenderTarget( NULL );
		}
		break;
	}
}

