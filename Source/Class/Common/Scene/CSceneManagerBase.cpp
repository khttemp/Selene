

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "System.h"
#include "Class/Platform/Render/Shader/CShader.h"
#include "Class/Platform/Render/COcclusion.h"
#include "Class/Platform/Render/CPostEffect.h"
#include "Class/Platform/Surface/CTexture.h"
#include "Class/Platform/Surface/CDepthTexture.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Scene/CCustomizedSceneRenderObject.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Class/Common/Scene/CSceneInstanceModelActor.h"
#include "Class/Common/Scene/CSceneModelActor.h"
#include "Class/Common/Scene/CSceneMapActor.h"
#include "Class/Common/Scene/CScenePointPrimitiveActor.h"
#include "Class/Common/Scene/CSceneLinePrimitiveActor.h"
#include "Class/Common/Scene/CScenePrimitiveActor.h"
#include "Class/Common/Scene/CSceneSpriteActor.h"
#include "Class/Common/Scene/CSceneParticleActor.h"
#include "Class/Common/Scene/CSceneFontSpriteActor.h"
#include "Class/Common/Render/3D/CPointPrimitive3D.h"
#include "Class/Common/Render/3D/CLinePrimitive3D.h"
#include "Class/Common/Render/3D/CPrimitive3D.h"
#include "Class/Common/Render/3D/CSprite3D.h"
#include "Class/Common/Render/3D/CParticle.h"
#include "Class/Common/Render/3D/CFontSprite3D.h"
#include "Class/Common/Render/Model/CModel.h"
#include "Class/Common/Render/Model/CMesh.h"
#include "Class/Common/Render/Map/CMapModel.h"
#include "NullDevice/Scene/NullSceneActor.h"
#include "NullDevice/Surface/NullTexture.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
static const Uint8 g_Shadow[] = {
#include "Resource/Shadow.dds.inc"
};


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SceneConstructionFunc( void *pData )
{
	CSceneManagerBase *pSceneMgr = (CSceneManagerBase*)pData;

	pSceneMgr->SceneConstruction();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSceneManagerBase::CSceneManagerBase( Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr, Sint32 QueMax ) : Renderer::CRenderObject( pRender, pMgr )
	, m_SceneState						( SCENE_STATE_READY )
	, m_pDS_Normal						( NULL )
	, m_pRT_Temp						( NULL )
	, m_pRenderTarget					( NULL )
	, m_vLightDirection					( 0.0f, 0.0f, 0.0f )
	, m_PointLightCount					( 0 )
	, m_IsHardwareShadowmap				( false )
	, m_IsSoftShadow					( false )
	, m_IsSort							( false )
	, m_IsSkydoom						( false )
	, m_IsToonBold						( false )
	, m_Event							( false, 1 )
	, m_EventExit						( false, 1 )
	, m_EventSceneConstruct				( true, 1 )
	, m_IsEndSceneConstruct				( true )
	, m_QueMax							( QueMax )
	, m_QueCount						( 0 )
	, m_ShadowType						( SHADOW_TYPE_DISABLE )
	, m_ShadowQuarity					( SHADOW_QUARITY_LOW )
	, m_HdrEffect						( HDR_EFFECT_BLOOM )
	, m_MotionBlurType					( MOTION_BLUR_TYPE_DISABLE )
	, m_MotionBlurQuarity				( MOTION_BLUR_LIGHT )
	, m_DofType							( DOF_TYPE_DISABLE )
	, m_FogType							( FOG_TYPE_DISABLE )
	, m_FogEffect						( FOG_EFFECT_LINEAR )
	, m_HdrType							( HDR_TYPE_DISABLE )
	, m_ShadingType						( SHADING_TYPE_NORMAL )
	, m_AntiAliasType					( AA_TYPE_DISABLE )
	, m_HardwareShadowType				( HW_SHADOW_NONE )
	, m_fAntiAliasPower					( 0.0f )
	, m_fFocusDepth						( 0.0f )
	, m_fFocusPower						( 0.0f )
	, m_RenderRequestCount				( 0 )
	, m_RenderCount						( 0 )
	, m_vSkydoomCloudOffset				( 0.0f, 0.0f )
	, m_pModelSkydoom					( NULL )
	, m_pActorSkydoom					( NULL )
	, m_pMapModel						( NULL )
	, m_pTextureBG						( NULL )
	, m_RenderRect						( 0, 0, 0, 0 )
	, m_ClearColor						( 0.0f, 0.0f, 0.0f, 0.0f )
	, m_IsClear							( true )
	, m_fHDRPower						( 1.0f )
	, m_fHDRBoundary					( 1.0f )
	, m_fEdgeNormalPower				( 3.0f )
	, m_fEdgeDepthPower					( 5.0f )
	, m_vBrightness						( 1.0f, 1.0f, 1.0f )
	, m_vToonRenderParameter			( 0.3f, 0.3f, 0.3f, 0.3f )
	, m_SceneConstructTime				( 0 )
	, m_SceneRenderingTime				( 0 )
	, m_fSoftParticleScale				( 10.0f )
{
	m_pRender = pRender;
	pRender->AddRef();

	m_pActorMgr = new Renderer::CRenderObjectMgr( m_pRender, "アクター" );

	for ( Sint32 i = 0; i < PROJECTION_SHADOW_PRIORITY_MAX; i++ )
	{
		m_pParticleShadow[i] = NULL;
		m_pActorShadow[i]  = NULL;
	}

	for ( Sint32 i = 0; i < ID_MAX; i++ )
	{
		m_pObjectList[i] = NULL;
	}

	for ( Sint32 i = 0; i < LIGHT_MAX; i++ )
	{
		m_vLightColor[i].Set( 0.0f, 0.0f, 0.0f );
	}

	for ( Sint32 i = 0; i < LIGHT_POINT_MAX; i++ )
	{
		m_vLightPosition[i].Set( 0.0f, 0.0f, 0.0f );
	}

	m_pQueTbl = new CCustomizedSceneRenderObject [ QueMax ];

	m_pCameraBackup = new CCamera;
	m_Camera.Reset();

	m_mShadowView.Identity();

	m_mViewPrev.Identity();
	m_mView.Identity();
	m_mProjection.Identity();
	m_mViewProjection.Identity();

	m_TargetSize = Math::Point2DI( 0, 0 );

	// 投影シャドウ
	Renderer::CTextureConfig Conf = m_pRender->GetTextureConfig();
	Renderer::CTextureConfig ConfNew;
	ConfNew.SetColorKey( CColor(0,0,0,0) );
	ConfNew.SetFormat( FORMAT_TEXTURE_DXT );
	ConfNew.SetMipmapEnable( true );
	m_pRender->SetTextureConfig( ConfNew );
	m_pTextureShadowProjection	= m_pRender->CreateTextureFromMemory( g_Shadow, sizeof(g_Shadow) );
	m_pRender->SetTextureConfig( Conf );

	// シーン用スレッド
	m_Thread.Create( SceneConstructionFunc, this );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSceneManagerBase::~CSceneManagerBase()
{
	// キュー処理スレッド終了
	WaitForSceneConstruct();
	m_EventExit.Set();
	m_Event.Set();
	while ( !m_Thread.WaitForExit() )
	{
		::SleepEx( 100, true );
	}

	// 所有オブジェクト解放
	SAFE_RELEASE( m_pModelSkydoom );
	SAFE_RELEASE( m_pMapModel );
	SAFE_RELEASE( m_pCameraBackup );

	SAFE_RELEASE( m_pTextureShadowProjection );

	for ( Sint32 i = 0; i < PROJECTION_SHADOW_PRIORITY_MAX; i++ )
	{
		SAFE_RELEASE( m_pParticleShadow[i] );
		SAFE_RELEASE( m_pActorShadow[i] );
	}

	SAFE_RELEASE( m_pActorSkydoom );
	SAFE_RELEASE( m_pRender );

	SAFE_DELETE( m_pActorMgr );

	SAFE_DELETE_ARRAY( m_pQueTbl );

	SAFE_RELEASE( m_pTextureBG );
	SAFE_RELEASE( m_pRenderTarget );
	SAFE_RELEASE( m_pRT_Temp );
	SAFE_RELEASE( m_pDS_Normal );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::OnLostDevice( void )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::OnResetDevice( void )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eSceneShadowType CSceneManagerBase::GetShadowType( void )
{
	return m_ShadowType;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eSceneHighDynamicRangeType CSceneManagerBase::GetHdrType( void )
{
	return m_HdrType;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eSceneShadingType CSceneManagerBase::GetShadingType( void )
{
	return m_ShadingType;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eSceneAntiAliasType CSceneManagerBase::GetAntiAliasType( void )
{
	return m_AntiAliasType;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eSceneFogType CSceneManagerBase::GetFogType( void )
{
	return m_FogType;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eHardwareShadowType CSceneManagerBase::GetHardwareShadowType( void )
{
	return m_HardwareShadowType;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CSceneManagerBase::GetNewRenderActorID( void )
{
	Sint32 Max = m_QueMax;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		if ( !m_pQueTbl[i].IsActive )
		{
			m_pQueTbl[i].IsActive = true;
			return i;
		}
	}

	return -1;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::ReleaseRenderActorID( Sint32 RenderActorID )
{
	if ( RenderActorID != -1 )
	{
		m_pQueTbl[RenderActorID].IsActive = false;
		m_pQueTbl[RenderActorID].pActor = NULL;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IModelActor *CSceneManagerBase::CreateActor( Renderer::Object::IModel *pObject )
{
	if ( (m_SceneState == SCENE_STATE_STANDBY) || (m_SceneState == SCENE_STATE_RESET))
	{
		if ( (pObject != NULL) && !pObject->IsInvalid() )
		{
			return new CModelActor( this, pObject, m_pRender, m_pActorMgr );
		}
	}

	static NullSceneActor Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IInstanceModelActor *CSceneManagerBase::CreateActor( Renderer::Object::IModel *pObject, Sint32 InstanceCount )
{
	if ( (m_SceneState == SCENE_STATE_STANDBY) || (m_SceneState == SCENE_STATE_RESET))
	{
		if ( (pObject != NULL) && !pObject->IsInvalid() )
		{
			return new CInstanceModelActor( InstanceCount, this, pObject, m_pRender, m_pActorMgr );
		}
	}

	static NullSceneActor Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IMapActor *CSceneManagerBase::CreateActor( Renderer::Object::IMapModel *pObject )
{
	if ( (m_SceneState == SCENE_STATE_STANDBY) || (m_SceneState == SCENE_STATE_RESET))
	{
		if ( (pObject != NULL) && !pObject->IsInvalid() )
		{
			return new CMapActor( this, pObject, m_pRender, m_pActorMgr );
		}
	}

	static NullSceneActor Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IPrimitiveActor *CSceneManagerBase::CreateActor( Renderer::Object::IPoint3D *pObject )
{
	if ( (m_SceneState == SCENE_STATE_STANDBY) || (m_SceneState == SCENE_STATE_RESET))
	{
		if ( (pObject != NULL) && !pObject->IsInvalid() )
		{
			return new CScenePointActor( this, pObject, m_pRender, m_pActorMgr );
		}
	}

	static NullSceneActor Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IPrimitiveActor *CSceneManagerBase::CreateActor( Renderer::Object::ILine3D *pObject )
{
	if ( (m_SceneState == SCENE_STATE_STANDBY) || (m_SceneState == SCENE_STATE_RESET))
	{
		if ( (pObject != NULL) && !pObject->IsInvalid() )
		{
			return new CSceneLineActor( this, pObject, m_pRender, m_pActorMgr );
		}
	}

	static NullSceneActor Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IPrimitiveActor *CSceneManagerBase::CreateActor( Renderer::Object::IPrimitive3D *pObject, Bool IsLightmap, Bool IsNormalmap, Bool IsSpecularmap, Bool IsEnvironmentmap )
{
	if ( (m_SceneState == SCENE_STATE_STANDBY) || (m_SceneState == SCENE_STATE_RESET))
	{
		if ( (pObject != NULL) && !pObject->IsInvalid() )
		{
			return new CPrimitiveActor( this, pObject, m_pRender, m_pActorMgr, IsLightmap, IsNormalmap, IsSpecularmap, IsEnvironmentmap );
		}
	}

	static NullSceneActor Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ISpriteActor *CSceneManagerBase::CreateActor( Renderer::Object::ISprite3D *pObject )
{
	if ( (m_SceneState == SCENE_STATE_STANDBY) || (m_SceneState == SCENE_STATE_RESET))
	{
		if ( (pObject != NULL) && !pObject->IsInvalid() )
		{
			return new CSpriteActor( this, pObject, m_pRender, m_pActorMgr );
		}
	}

	static NullSceneActor Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IParticleActor *CSceneManagerBase::CreateActor( Renderer::Object::IParticle *pObject )
{
	if ( (m_SceneState == SCENE_STATE_STANDBY) || (m_SceneState == SCENE_STATE_RESET))
	{
		if ( (pObject != NULL) && !pObject->IsInvalid() )
		{
			return new CParticleActor( this, pObject, m_pRender, m_pActorMgr );
		}
	}

	static NullSceneActor Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IParticleActor *CSceneManagerBase::CreateActor( Renderer::Object::IFontSprite3D *pObject )
{
	if ( (m_SceneState == SCENE_STATE_STANDBY) || (m_SceneState == SCENE_STATE_RESET))
	{
		if ( (pObject != NULL) && !pObject->IsInvalid() )
		{
			return new CSceneFontSpriteActor( this, pObject, m_pRender, m_pActorMgr );
		}
	}

	static NullSceneActor Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ICamera *CSceneManagerBase::GetCamera( void )
{
	SAFE_ADDREF( m_pCameraBackup );

	return m_pCameraBackup;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::Abort( void )
{
	if ( m_SceneState == SCENE_STATE_END )
	{
		// レンダリング呼びましたよ的解放処理
		WaitForSceneConstruct();
		ReleaseObjectList();
		m_SceneState = SCENE_STATE_STANDBY;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::Reset( void )
{
	//------------------------------------------------------------------
	// シーンの終了を待つ（Renderingしていない場合対策）
	//------------------------------------------------------------------
	Abort();

	//------------------------------------------------------------------
	// スタンバイ状態？
	//------------------------------------------------------------------
	if ( m_SceneState != SCENE_STATE_STANDBY )
	{
		return;
	}

	//------------------------------------------------------------------
	// リセット完了
	//------------------------------------------------------------------
	m_SceneState = SCENE_STATE_RESET;

	//------------------------------------------------------------------
	// シーン情報の初期化
	//------------------------------------------------------------------
	m_PointLightCount = 0;

	Sint32 Max = m_QueMax;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pQueTbl[i].IsRender = false;
	}

	for ( Sint32 i = 0; i < ID_MAX; i++ )
	{
		CCustomizedSceneRenderObject *pObj = m_pObjectList[i];
		while ( pObj != NULL )
		{
			pObj->IsRender = false;
			pObj = pObj->pNext;
		}
		m_pObjectList[i] = NULL;
	}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::Begin( Bool IsSort )
{
	//------------------------------------------------------------------
	// Reset完了状態？
	//------------------------------------------------------------------
	if ( m_SceneState != SCENE_STATE_RESET )
	{
		return;
	}

	//------------------------------------------------------------------
	// シーン開始？
	//------------------------------------------------------------------
	if ( !m_pRender->ActivateScene( this ) ) return;

	//------------------------------------------------------------------
	// 開始
	//------------------------------------------------------------------
	m_SceneState = SCENE_STATE_BEGIN;

	//------------------------------------------------------------------
	// 設定初期化
	//------------------------------------------------------------------
	m_IsSort					= IsSort;
	m_fProjectionShadowRadius	= 1.0f;
	m_ProjectionShadowType		= PROJECTION_SHADOW_DISABLE;
	m_ProjectionShadowPriority	= PROJECTION_SHADOW_PRIORITY_0;
	m_QueCount					= 0;
	m_Camera					= *m_pCameraBackup;
	m_mViewPrev					= m_mView;
	m_mView						= m_Camera.WorldToView();
	m_mProjection				= m_Camera.ViewToScreen();
	m_mViewProjection			= m_Camera.WorldToScreen();
	m_RenderRequestCount		= 0;
	m_RenderCount				= 0;

	for ( Sint32 i = 0; i < ID_MAX; i++ )
	{
		m_pObjectList[i] = NULL;
	}

	m_DepthParameter.Set(
		-1.0f                 / (m_Camera.GetFarClip() - m_Camera.GetNearClip()),
		m_Camera.GetFarClip() / (m_Camera.GetFarClip() - m_Camera.GetNearClip()),
		0.0f,
		1.0f );

	m_FogParameter.Set(
		-1.0f     / (m_fFogFar - m_fFogNear),
		m_fFogFar / (m_fFogFar - m_fFogNear),
		0.0f,
		1.0f );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::End( void )
{
	//------------------------------------------------------------------
	// 開始状態？
	//------------------------------------------------------------------
	if ( m_SceneState != SCENE_STATE_BEGIN )
	{
		return;
	}

	//------------------------------------------------------------------
	// 開始？
	//------------------------------------------------------------------
	if ( !m_pRender->DeActivateScene( this ) ) return;

	//------------------------------------------------------------------
	// 終了
	//------------------------------------------------------------------
	m_SceneState = SCENE_STATE_END;

	//------------------------------------------------------------------
	// 設定初期化
	//------------------------------------------------------------------
	m_RenderRequestCount = m_QueCount;
	m_RenderCount        = 0;

	//------------------------------------------------------------------
	// キューにデータがあるとき
	//------------------------------------------------------------------
	if ( m_QueCount > 0 )
	{
		// シーン構築開始
		SetSceneConstruct( false );

		// キュー追加イベント発行
		m_Event.Set();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::ReleaseObjectList( void )
{
	Sint32 Max = m_QueMax;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pQueTbl[i].IsRender = false;
		if ( m_pQueTbl[i].pActor != NULL )
		{
			m_pQueTbl[i].pActor->Flip();
		}
	}

	for ( Sint32 i = 0; i < ID_MAX; i++ )
	{
		m_pObjectList[i] = NULL;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SceneSkydoom_Rendering( void )
{
	if ( m_SceneState == SCENE_STATE_BEGIN )
	{
		if ( m_pActorSkydoom != NULL )
		{
			m_IsSkydoom = true;

			// レンダリング
			m_pActorSkydoom->TransformReset();
			m_pActorSkydoom->Translation( m_Camera.Position().x, m_Camera.Position().y, m_Camera.Position().z );
			m_pActorSkydoom->TransformUpdate();
			m_pActorSkydoom->RenderingRequest();

			m_IsSkydoom = false;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::ClearDepthBuffer( void )
{
	m_pRender->ClearDepthStencil();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SetParameter_BGColor( Math::Vector4D &ClearColor, Bool IsClear )
{
	m_IsClear		= IsClear;
	m_ClearColor	= ClearColor;
	m_ClearColor.w	= 0.0f;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SetParameter_BGTexture( Renderer::ITexture *pTex )
{
	SAFE_RELEASE( m_pTextureBG );
	if ( (pTex != NULL) && !pTex->IsInvalid() )
	{
		m_pTextureBG = pTex;
		SAFE_ADDREF( m_pTextureBG );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SetParameter_BGColor( CColor ClearColor, Bool IsClear )
{
	m_IsClear		= IsClear;
	m_ClearColor.x	= toF(ClearColor.r) / 255.0f;
	m_ClearColor.y	= toF(ClearColor.g) / 255.0f;
	m_ClearColor.z	= toF(ClearColor.b) / 255.0f;
	m_ClearColor.w	= 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SetLightParameter_Ambient( const Math::Vector3D &vColorSky, const Math::Vector3D &vColorEarth )
{
	if ( m_SceneState == SCENE_STATE_RESET )
	{
		m_vLightColor[LIGHT_AMBIENT_SKY]   = vColorSky;
		m_vLightColor[LIGHT_AMBIENT_EARTH] = vColorEarth;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SetLightParameter_Directional( const Math::Vector3D &vDirect, const Math::Vector3D &vColor )
{
	if ( m_SceneState == SCENE_STATE_RESET )
	{
		if ( !IsShadowEnable() )
		{
			if ( vDirect.LengthSq() <= 0.001f )
			{
				m_vLightDirection.Set( 0.0f, 0.0f, 0.0f, 1.0f );
			}
			else
			{
				Math::Vector4D vTemp = -vDirect;
				m_vLightDirection.NormalizeFast( vTemp );
			}
		}

		m_vLightColor[LIGHT_DIRECTION] = vColor;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SetLightParameter_AddPoint( const Math::Vector3D &vPosition, const Math::Vector3D &vColor, Float fDistance )
{
	if ( m_SceneState == SCENE_STATE_RESET )
	{
		if ( m_PointLightCount < LIGHT_POINT_MAX )
		{
			m_vLightPosition[m_PointLightCount]	= vPosition;
			m_vLightColor[m_PointLightCount]	= vColor;
			m_fLightDistance[m_PointLightCount]	= fDistance;

			m_PointLightCount++;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SetActorParameter_MotionBlur( eSceneMotionBlurQuarity MotionBlurQuarity )
{
	if ( m_SceneState == SCENE_STATE_BEGIN )
	{
//		m_MotionBlurQuarity = MotionBlurQuarity;
		m_MotionBlurQuarity = MOTION_BLUR_LIGHT;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SetActorParameter_ProjectionShadow( eProjectionShadowType Type, eProjectionShadowPriority Priority, Float fRadius )
{
	if ( m_SceneState == SCENE_STATE_BEGIN )
	{
		if ( m_ShadowType == SHADOW_TYPE_PROJECTION )
		{
			m_fProjectionShadowRadius = fRadius;
			m_ProjectionShadowType = Type;
			m_ProjectionShadowPriority = Priority;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SetParameter_HighDynamicRange( Float fHDRPower, Float fHDRBoundary )
{
	if ( m_SceneState == SCENE_STATE_RESET )
	{
		m_fHDRPower		= fHDRPower;
		m_fHDRBoundary	= fHDRBoundary;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SetParameter_ToonEdge( Float fEdgeNormalPower, Float fEdgeDepthPower, Bool IsToonBold )
{
	if ( m_SceneState == SCENE_STATE_RESET )
	{
		m_fEdgeNormalPower	= fEdgeNormalPower;
		m_fEdgeDepthPower	= fEdgeDepthPower;
		m_IsToonBold		= IsToonBold;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SetParameter_Shadow( Math::Vector3D &vPosition, Math::Vector3D &vTarget, Float fSize, Float fNear, Float fFar, Float fBias, Float fPower )
{
	if ( m_SceneState == SCENE_STATE_RESET )
	{
		if ( !IsShadowEnable() ) return;

		// ビュー行列
		m_mShadowView.LookAt( vPosition, vTarget, Math::Vector3D(0.0f,1.0f,0.0f) );

		// プロジェクション行列
		Math::Matrix mProject;
		mProject.Ortho( fSize, fSize, fNear, fFar );

		// ビューｘプロジェクション
		m_mShadowViewProj = m_mShadowView * mProject;

		// バイアス
		m_fShadowMapNear	= fNear;
		m_fShadowMapFar		= fFar;
		m_fShadowMapBias	= fBias;
		m_fShadowMapPower	= MIN( 1.0f, MAX( 0.0f, fPower ) );

		// 平行光源
		Math::Vector3D vDirect = vTarget - vPosition;
		if ( vDirect.LengthSq() <= 0.001f )
		{
			m_vLightDirection.Set( 0.0f, 0.0f, 0.0f, 0.0f );
		}
		else
		{
			Math::Vector4D vTemp = -vDirect;
			m_vLightDirection.NormalizeFast( vTemp );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SetParameter_Toon( Math::Vector3D &vHatchingColor, Float fToonPower )
{
	if ( m_SceneState == SCENE_STATE_RESET )
	{
		m_vToonRenderParameter.x = vHatchingColor.x;
		m_vToonRenderParameter.y = vHatchingColor.y;
		m_vToonRenderParameter.z = vHatchingColor.z;
		m_vToonRenderParameter.w = fToonPower;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SetParameter_Fog( Math::Vector3D &vColor, Float fNear, Float fFar )
{
	if ( m_SceneState == SCENE_STATE_RESET )
	{
		m_FogColor	= vColor;
		m_fFogFar	= fFar;
		m_fFogNear	= fNear;

		if ( m_FogColor.x < 0.0f ) m_FogColor.x = 0.0f;
		if ( m_FogColor.y < 0.0f ) m_FogColor.y = 0.0f;
		if ( m_FogColor.z < 0.0f ) m_FogColor.z = 0.0f;
		if ( m_FogColor.x > 1.0f ) m_FogColor.x = 1.0f;
		if ( m_FogColor.y > 1.0f ) m_FogColor.y = 1.0f;
		if ( m_FogColor.z > 1.0f ) m_FogColor.z = 1.0f;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SetParameter_DepthOfField( Float fForcusZ, Float fPower )
{
	if ( m_SceneState == SCENE_STATE_RESET )
	{
		m_fFocusDepth = (fForcusZ - m_Camera.GetNearClip()) / (m_Camera.GetFarClip() - m_Camera.GetNearClip());
		m_fFocusDepth = 1.0f - m_fFocusDepth;
		m_fFocusPower = fPower;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SetParameter_SoftParticleScale( Float fSoftParticleScale )
{
	if ( m_SceneState == SCENE_STATE_RESET )
	{
		m_fSoftParticleScale = fSoftParticleScale;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneManagerBase::InitParameter_Update( void )
{
	//------------------------------------------------------------------
	// シーン待機状態？
	//------------------------------------------------------------------
	if ( m_SceneState != SCENE_STATE_READY )
	{
		return false;
	}

	//------------------------------------------------------------------
	// シーンをスタンバイにする
	//------------------------------------------------------------------
	m_SceneState = SCENE_STATE_STANDBY;

	//------------------------------------------------------------------
	// チェック
	//------------------------------------------------------------------
	if ( m_ShadingType != SHADING_TYPE_NORMAL )
	{
		m_IsSoftShadow = false;
	}

	//------------------------------------------------------------------
	// シーン情報を元に描画バッファの構築
	//------------------------------------------------------------------
	return CreateRenderTargetBuffer();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::InitParameter_RenderTargetData( Renderer::ITexture *pTarget, Math::Point2DI Size, Bool IsTextureSizePow2 )
{
	if ( m_SceneState == SCENE_STATE_READY )
	{
		//-----------------------------------------------------------------------
		// レンダリングターゲット
		//-----------------------------------------------------------------------
		if ( (pTarget != NULL) && !pTarget->IsInvalid() )
		{
			m_pRenderTarget = pTarget;
			SAFE_ADDREF( m_pRenderTarget );

			Size = m_pRenderTarget->GetSize();
		}
		else
		{
			m_pRenderTarget = NULL;
		}

		//-----------------------------------------------------------------------
		// サイズチェック
		//-----------------------------------------------------------------------
		m_TargetSize = m_pGraphicCard->GetTextureSize( Size, FORMAT_INVALID, IsTextureSizePow2 );
		m_RenderRect.Set( 0, 0, Size.x, Size.y );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::InitParameter_Shading( eSceneShadingType ShadingType )
{
	if ( (m_SceneState == SCENE_STATE_READY) && (GetShaderVersion() == SHADER_MODEL_2_0) )
	{
		m_ShadingType = ShadingType;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::InitParameter_AntiAliasType( eSceneAntiAliasType AntiAliasType, Float fPower )
{
	if ( (m_SceneState == SCENE_STATE_READY) && (GetShaderVersion() == SHADER_MODEL_2_0) )
	{
		m_AntiAliasType = AntiAliasType;
		m_fAntiAliasPower = MIN( 1.0f, MAX( 0.0f, fPower ) );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::InitParameter_Shadow( eSceneShadowType ShadowType, eSceneShadowQuarity ShadowQuarity, Bool IsSoftShadow, Bool IsHardwareShadowmap )
{
	if ( (m_SceneState == SCENE_STATE_READY) && (GetShaderVersion() == SHADER_MODEL_2_0) )
	{
		m_ShadowType = ShadowType;
		m_ShadowQuarity = ShadowQuarity;
		m_IsSoftShadow = IsSoftShadow;
		m_IsHardwareShadowmap = IsHardwareShadowmap;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::InitParameter_MotionBlur( eSceneMotionBlurType MotionBlurType )
{
	if ( (m_SceneState == SCENE_STATE_READY) && (GetShaderVersion() == SHADER_MODEL_2_0) )
	{
		m_MotionBlurType = MotionBlurType;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::InitParameter_DepthOfField( eSceneDepthOfFieldType DofType )
{
	if ( (m_SceneState == SCENE_STATE_READY) && (GetShaderVersion() == SHADER_MODEL_2_0) )
	{
		m_DofType = DofType;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::InitParameter_HighDynamicRange( eSceneHighDynamicRangeType HdrType, eSceneHighDynamicRangeEffect HdrEffect )
{
	if ( (m_SceneState == SCENE_STATE_READY) && (GetShaderVersion() == SHADER_MODEL_2_0) )
	{
		m_HdrType = HdrType;
		m_HdrEffect = HdrEffect;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::InitParameter_Fog( eSceneFogType FogType, eSceneFogEffect FogEffect )
{
	if ( m_SceneState == SCENE_STATE_READY )
	{
		m_FogType = FogType;
		m_FogEffect = FogEffect;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SetParameter_SceneBrightness( const Math::Vector3D &vBrightness )
{
	if ( m_SceneState == SCENE_STATE_RESET )
	{
		m_vBrightness = vBrightness;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneManagerBase::GetSceneConstruct( void )
{
	Thread::CAutoLock Lock( m_CS );
	return m_IsEndSceneConstruct;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SetSceneConstruct( Bool IsEnd )
{
	if ( IsEnd )
	{
		// フラグ
		Thread::CAutoLock Lock( m_CS );
		m_IsEndSceneConstruct = true;
		// 描画完了イベント
		m_EventSceneConstruct.Set();
	}
	else
	{
		// 描画完了イベント
		m_EventSceneConstruct.Reset();
		// フラグ
		Thread::CAutoLock Lock( m_CS );
		m_IsEndSceneConstruct = false;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::WaitForSceneConstruct( void )
{
	if ( !GetSceneConstruct() )
	{
		m_EventSceneConstruct.Wait();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::AddObject( CActorObject *pActor )
{
	// 書き込み可能？
	Sint32 Id = pActor->GetRenderActorID();
	if ( Id != -1 )
	{
		CCustomizedSceneRenderObject &Que = m_pQueTbl[Id];
		m_QueCount++;

		// キューに追加
		Que.IsRender					= true;
		Que.vBrightness					= m_vBrightness;
		Que.fShadowRadius				= m_fProjectionShadowRadius;
		Que.ProjectionShadowType		= m_ProjectionShadowType;
		Que.ProjectionShadowPriority	= m_ProjectionShadowPriority;
		Que.MotionBlurLevel				= pActor->IsSupportVertexNormal() ? m_MotionBlurQuarity : MOTION_BLUR_LIGHT;
		Que.IsSkydoom					= m_IsSkydoom;
		Que.pActor						= pActor;
		Que.fKey						= 0.0f;
		Que.pNext						= NULL;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::InsertList( Scene::CCustomizedSceneRenderObject &Obj )
{
	Bool IsAlpha = Obj.pActor->IsAlphaEnable();

	//-------------------------------------------------------------
	// オブジェクトのカメラからの距離
	//-------------------------------------------------------------
	Math::Vector3D vDistance = m_Camera.Position() - Obj.pActor->GetCenter();
	Obj.fKey = vDistance.LengthSq();

	//-------------------------------------------------------------
	// リストに追加
	//-------------------------------------------------------------
	// スカイドーム？
	if ( Obj.IsSkydoom )
	{
		Sint32 Id = ID_SKYDOOM;
		Obj.pNext = m_pObjectList[Id];
		m_pObjectList[Id] = &Obj;
	}
	// 通常外の描画
	ef ( IsAlpha )
	{
		Sint32 Id = ID_ALPHA_ENABLE;
		// １つ目orソートなしor先頭
		if ( (m_pObjectList[Id] == NULL) || !m_IsSort || (Obj.fKey >= m_pObjectList[Id]->fKey) )
		{
			Obj.pNext = m_pObjectList[Id];
			m_pObjectList[Id] = &Obj;
		}
		// ２つ目以降でソートする
		else
		{
			// 該当箇所へ挿入
			CCustomizedSceneRenderObject *pSrc = m_pObjectList[Id];
			while ( (pSrc->pNext != NULL) && (Obj.fKey < pSrc->pNext->fKey) )
			{
				pSrc = pSrc->pNext;
			}
			Obj.pNext = pSrc->pNext;
			pSrc->pNext = &Obj;
		}
	}
	// 通常の描画
	else
	{
		Sint32 Id = ID_ALPHA_DISABLE;

		Obj.pNext = m_pObjectList[Id];
		m_pObjectList[Id] = &Obj;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CSceneManagerBase::SearchPointLight( Sint32 NoTbl[], Math::Vector3D vPosition )
{
	Sint32 LightCount = m_PointLightCount;

	//--------------------------------------------------------
	// この時点でライト数が規定数に収まってる？
	//--------------------------------------------------------
	if ( LightCount <= POINT_LIGHT_VALID_MAX )
	{
		for ( Sint32 i = 0; i < LightCount; i++ )
		{
			NoTbl[i] = i;
		}
		return LightCount;
	}

	//--------------------------------------------------------
	// ライトの中から距離の近い順にソート
	//--------------------------------------------------------
	Float fRangeTbl[] = { FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX };
	for ( Sint32 i = 0; i < LightCount; i++ )
	{
		Math::Vector3D vDistance = vPosition - m_vLightPosition[i];
		Float fRange = vDistance.LengthSq();

		// ４つのリストから最も距離の遠いライトを検索
		Sint32 FarNo = 0;
		for ( Sint32 j = 1; j < POINT_LIGHT_VALID_MAX; j++ )
		{
			// より遠いものが見つかったら更新
			if ( fRangeTbl[FarNo] < fRangeTbl[j] )
			{
				FarNo = j;
			}
		}

		// リスト中の最も遠いものが現在のライトより遠ければ入れ替える
		if ( fRangeTbl[FarNo] > fRange )
		{
			fRangeTbl[FarNo] = fRange;
			NoTbl[FarNo] = i;
		}
	}

	return POINT_LIGHT_VALID_MAX;
}

//-----------------------------------------------------------------------------------
/**。
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::ComputeRenderData( Scene::CCustomizedSceneRenderObject &Obj )
{
	Math::Vector4D vPositionTbl[POINT_LIGHT_VALID_MAX];
	Math::Vector4D vColorTbl[POINT_LIGHT_VALID_MAX];

	const Math::Matrix &mWorld = Obj.pActor->GetWorldMatrix();
	const Math::Matrix &mWorldPrev = Obj.pActor->GetWorldMatrixPrev();
	const Math::Matrix &mWorldInverse = Obj.pActor->GetWorldInverseMatrix();

	//--------------------------------------------------------------------------------
	// カスタムシェーダー
	//--------------------------------------------------------------------------------
	if ( GetShaderVersion() == SHADER_MODEL_CUSTOM )
	{
		//----------------------------------------------------------------
		// 変換行列
		//----------------------------------------------------------------
		// WorldView
		Obj.mWorldView.Multiply( mWorld, m_mView );
		// WorldViewProjection
		Obj.mWorldViewProjection.Multiply( mWorld, m_mViewProjection );

		// WorldViewPrev
		Obj.mWorldViewPrev.Multiply( mWorldPrev, m_mViewPrev );
		// WorldViewProjectionPrev
		Obj.mWorldViewProjectionPrev.Multiply( Obj.mWorldViewPrev, m_mProjection );
	}
	//--------------------------------------------------------------------------------
	// 内蔵シェーダー
	//--------------------------------------------------------------------------------
	else
	{
		//----------------------------------------------------------------
		// 変換行列
		//----------------------------------------------------------------
		// WorldView
		Obj.mWorldView.Multiply( mWorld, m_mView );
		// WorldViewProjection
		Obj.mWorldViewProjection.Multiply( mWorld, m_mViewProjection );

		// モーションブラーある？
		if ( m_MotionBlurType != MOTION_BLUR_TYPE_DISABLE )
		{
			// WorldViewPrev
			Obj.mWorldViewPrev.Multiply( mWorldPrev, m_mViewPrev );
			// WorldViewProjectionPrev
			Obj.mWorldViewProjectionPrev.Multiply( Obj.mWorldViewPrev, m_mProjection );
		}

		//----------------------------------------------------------------
		// ライト
		//----------------------------------------------------------------
		// ライトあり？
		if ( Obj.pActor->IsSupportVertexNormal() )
		{
			// PointLightPosition & PointLightColor
			for ( Sint32 i = 0; i < POINT_LIGHT_VALID_MAX; i++ )
			{
				Obj.vPointLightPositionTbl[i] = Math::Vector4D( 0.0f, 0.0f, 0.0f, 0.0f );
				Obj.vPointLightColorTbl[i]    = Math::Vector4D( 0.0f, 0.0f, 0.0f, 0.0f );
			}

			Sint32 NoTbl[POINT_LIGHT_VALID_MAX];
			Sint32 NoMax = SearchPointLight( NoTbl, Obj.pActor->GetCenter() );
			if ( NoMax > 0 )
			{
				for ( Sint32 i = 0; i < NoMax; i++ )
				{
					// 位置
					Math::Vector4D vPos = m_vLightPosition[NoTbl[i]];
					Obj.vPointLightPositionTbl[i].TransformCoord( vPos, mWorldInverse );
					// 影響距離
					Obj.vPointLightPositionTbl[i].w = m_fLightDistance[NoTbl[i]];

					// 色
					Obj.vPointLightColorTbl[i].x = m_vLightColor[NoTbl[i]].x;
					Obj.vPointLightColorTbl[i].y = m_vLightColor[NoTbl[i]].y;
					Obj.vPointLightColorTbl[i].z = m_vLightColor[NoTbl[i]].z;
				}
			}
			Obj.PointLightCount = NoMax;
		}
		else
		{
			Obj.PointLightCount = 0;
		}

		// DirectionalLightDirection
		Obj.vLightDiection.TransformNormal( m_vLightDirection, mWorldInverse );
		Obj.vLightDiection.NormalizeFast();

		//----------------------------------------------------------------
		// 影あり
		//----------------------------------------------------------------
		if ( IsShadowEnable() )
		{
			Obj.mShadowWorldViewProjection.Multiply( mWorld, m_mShadowViewProj );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SetParameter_RenderRect( Math::Rect2DF &Dst )
{
	m_RenderRect = Dst;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CSceneManagerBase::GetResult_RenderingRequestActorCount( void )
{
	return m_RenderRequestCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CSceneManagerBase::GetResult_RenderingActorCount( void )
{
	return m_RenderCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneManagerBase::IsFogEnable( void )
{
	switch ( m_FogType )
	{
	case FOG_TYPE_ENABLE:
		return true;

	default:
		return false;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneManagerBase::IsVelocityEnable( void )
{
	switch ( m_MotionBlurType )
	{
	case MOTION_BLUR_TYPE_LOW:
	case MOTION_BLUR_TYPE_HIGH:
		return true;

	default:
		return false;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneManagerBase::IsAntiAliasEnable( void )
{
	switch ( m_AntiAliasType )
	{
	case AA_TYPE_ENABLE:
		return true;

	default:
		return false;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneManagerBase::IsHDREnable( void )
{
	switch ( m_HdrType )
	{
	case HDR_TYPE_ENABLE:
		return true;

	default:
		return false;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneManagerBase::IsDepthOfFieldEnable( void )
{
	switch ( m_DofType )
	{
	case DOF_TYPE_ENABLE:
		return true;

	default:
		return false;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneManagerBase::IsToonEnable( void )
{
	switch ( m_ShadingType )
	{
	case SHADING_TYPE_TOON:
	case SHADING_TYPE_HATCHING:
		return true;

	default:
		return false;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneManagerBase::IsShadowEnable( void )
{
	switch ( m_ShadowType )
	{
	case SHADOW_TYPE_PROJECTION:
	case SHADOW_TYPE_SHADOWMAP:
		return true;

	default:
		return false;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneManagerBase::IsSoftShadowEnable( void )
{
	return m_IsSoftShadow;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Vector3D CSceneManagerBase::TransformToScreen( const Math::Vector3D &vPosition )
{
	Math::Vector3D vPos = vPosition;

	vPos.TransformProjection( m_mViewProjection );

	Float w = toF(m_RenderRect.w / 2);
	Float h = toF(m_RenderRect.h / 2);
	Float x = toF(m_RenderRect.x + w);
	Float y = toF(m_RenderRect.y + h);

	vPos.x = x + (+vPos.x * w);
	vPos.y = y + (-vPos.y * h);

	return vPos;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Vector3D CSceneManagerBase::TransformFromScreen( const Math::Vector3D &vPosition )
{
	Math::Vector3D vPos = vPosition;

	Float w = toF(m_RenderRect.w / 2);
	Float h = toF(m_RenderRect.h / 2);
	Float x = toF(m_RenderRect.x + w);
	Float y = toF(m_RenderRect.y + h);

	vPos.x = +(vPos.x - x) / w;
	vPos.y = -(vPos.y - y) / h;

	Math::Matrix mTemp;
	mTemp.Inverse( m_mViewProjection );
	vPos.TransformProjection( mTemp );

	return vPos;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneManagerBase::SceneSkydoom_Create( Float fRadius, CColor TopColor, CColor BottomColor, Renderer::ITexture *pTexCloud )
{
	//-----------------------------------------------------------------------
	// スカイドーム生成
	//-----------------------------------------------------------------------
	SAFE_RELEASE( m_pActorSkydoom );
	SAFE_RELEASE( m_pModelSkydoom );

	m_pModelSkydoom = m_pRender->CreateModelSkydoom( fRadius, TopColor, BottomColor, pTexCloud );
	if ( m_pModelSkydoom->IsInvalid() )
	{
		SAFE_RELEASE( m_pModelSkydoom );
		return false;
	}

	m_pActorSkydoom = CreateActor( m_pModelSkydoom );
	if ( m_pActorSkydoom->IsInvalid() )
	{
		SAFE_RELEASE( m_pActorSkydoom );
		SAFE_RELEASE( m_pModelSkydoom );
		return false;
	}

	Sint32 Count = m_pActorSkydoom->GetMeshCount();
	for ( Sint32 i = 0; i < Count; i++ )
	{
		m_pActorSkydoom->SetCullTestEnable( false );
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCamera &CSceneManagerBase::GetActiveCamera( void )
{
	return m_Camera;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SceneSkydoom_SetCloudOffset( const Math::Vector2D &vOffset )
{
	m_vSkydoomCloudOffset.x += vOffset.x;
	m_vSkydoomCloudOffset.y += vOffset.y;
	while ( m_vSkydoomCloudOffset.x > +1.0f ) m_vSkydoomCloudOffset.x -= 1.0f;
	while ( m_vSkydoomCloudOffset.y > +1.0f ) m_vSkydoomCloudOffset.y -= 1.0f;
	while ( m_vSkydoomCloudOffset.x < -1.0f ) m_vSkydoomCloudOffset.x += 1.0f;
	while ( m_vSkydoomCloudOffset.y < -1.0f ) m_vSkydoomCloudOffset.y += 1.0f;

	if ( m_pActorSkydoom != NULL )
	{
		m_pActorSkydoom->MeshMaterial_SetTextureOffset( 0, 0, m_vSkydoomCloudOffset );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SceneSkydoom_SetCloudColor( const CColor &Color )
{
	if ( m_pActorSkydoom != NULL )
	{
		Math::Vector4D vColor(
			toF(Color.r) / 255.0f,
			toF(Color.g) / 255.0f,
			toF(Color.b) / 255.0f,
			toF(Color.a) / 255.0f );
		m_pActorSkydoom->MeshMaterial_SetMaterialColor( 0, 0, vColor );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CSceneManagerBase::GetResult_BackgroundThreadTime( void )
{
	return (Sint32)m_SceneConstructTime;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CSceneManagerBase::GetResult_RenderingTme( void )
{
	return (Sint32)m_SceneRenderingTime;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneManagerBase::CreateInstnaceModel( CActorObject *pActor )
{
	Sint32 RenderCount = 0;

	CSceneInstanceModelActorObject *pObject = (CSceneInstanceModelActorObject*)pActor;

	// 書き込み開始
	pObject->BeginInstance();

	// インスタンス分の処理
	Sint32 InstanceCount = pObject->GetControllerCount();
	for ( Sint32 i = 0; i < InstanceCount; i++ )
	{
		// 関連するコントローラーを取得
		CInstanceModelControllerObject *pController = pObject->GetControllerObject( i );

		// 描画フラグON？
		if ( !pController->GetDrawEnable() )
		{
			continue;
		}

		// フラグOFF
		pController->SetDrawEnable( false );

		// カリングする？
		if ( pController->GetCullTestEnable() )
		{
			// カリング
			if ( !m_Camera.ViewfrustumCulling( pController->GetCullBox() ) )
			{
				continue;
			}
		}

		// 描画データの生成
		pObject->UpdateInsntaceVertex( i, RenderCount );

		// 描画数＋１
		RenderCount++;
	}

	// 書き込み終了
	pObject->EndInstance();

	// 描画数設定
	pObject->SetRenderInstanceCount( RenderCount );

	return RenderCount > 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManagerBase::SceneConstruction( void )
{
	Uint64 TimeStart, TimeEnd, TimeSecond;

	// スレッド指定
	System::SetThreadCPUNo( 1 );

	// １秒間のカウント数
	::QueryPerformanceFrequency( (LARGE_INTEGER*)&TimeSecond );

	// イベントループ
	for ( ; ; )
	{
		// イベント待ち
		m_Event.Wait();
		m_Event.Reset();

		// 終了
		if ( m_EventExit.Wait( 0 ) != -1 ) break;

		// 開始時間
		::QueryPerformanceCounter( (LARGE_INTEGER*)&TimeStart );

		// キューからデータを取り出す
		Sint32 Max = m_QueMax;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			CCustomizedSceneRenderObject &Que = m_pQueTbl[i];
			if ( Que.IsRender )
			{
				// インスタンスモデル
				if ( Que.pActor->IsInstanceModel() )
				{
					// モデルデータ生成
					if ( !CreateInstnaceModel( Que.pActor ) )
					{
						continue;
					}
				}
				// 通常モデル
				else
				{
					// ビューフラスタムカリングする？
					if ( Que.pActor->GetCullTestEnable() )
					{
						// カリング
						if ( !m_Camera.ViewfrustumCulling( Que.pActor->GetCullBox() ) )
						{
							continue;
						}
					}
				}

				// 描画数
				m_RenderCount++;

				// リストに追加
				InsertList( Que );

				// 各種レンダリング用データの事前生成
				ComputeRenderData( Que );
			}
		}

		// 終了時間
		::QueryPerformanceCounter( (LARGE_INTEGER*)&TimeEnd );

		// シーン構築時間
		m_SceneConstructTime = (100 * 60 * (TimeEnd - TimeStart)) / TimeSecond;

		// シーン構築終わった
		SetSceneConstruct( true );
	}
}

