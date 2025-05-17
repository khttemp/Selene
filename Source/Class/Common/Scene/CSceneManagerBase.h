#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Render/Shader/ShaderManager.h"
#include "Class/Platform/Render/COcclusion.h"
#include "Class/Common/Scene/CSceneCamera.h"
#include "Class/Common/Scene/CSceneActorObject.h"
#include "Class/Common/Object/CRenderObject.h"
#include "Class/Common/Object/CRenderObjectMgr.h"
#include "Class/ClassReference.h"
#include "Collision/Box.h"
#include "Thread/Thread.h"
#include "Thread/Event.h"
#include "Thread/CriticalSection.h"
#include "Interface/Scene/ISceneManager.h"
#include "Interface/Scene/ICustomizedSceneManager.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class CSceneManagerBase : public Renderer::CRenderObject, public ISceneManager, public ICustomizedSceneManager
	{
	protected:
		enum {
			LIGHT_POINT_MAX = 64,
			LIGHT_DIRECTION,
			LIGHT_AMBIENT_SKY,
			LIGHT_AMBIENT_EARTH,
			LIGHT_MAX,
			POINT_LIGHT_VALID_MAX = 4,
		};

		enum {
			ID_SKYDOOM,
			ID_ALPHA_DISABLE,
			ID_ALPHA_ENABLE,
			ID_MAX,
		};

		enum eSceneState
		{
			SCENE_STATE_READY,
			SCENE_STATE_STANDBY,
			SCENE_STATE_RESET,
			SCENE_STATE_BEGIN,
			SCENE_STATE_END,
		};

	protected:
		eSceneState m_SceneState;

		Renderer::ITexture *m_pRenderTarget;
		Renderer::ITexture *m_pRT_Temp;
		Renderer::ITexture *m_pDS_Normal;

		Bool m_IsSkydoom;
		Bool m_IsToonBold;
		Bool m_IsHardwareShadowmap;
		Bool m_IsSoftShadow;

		Float m_fProjectionShadowRadius;
		eProjectionShadowType m_ProjectionShadowType;
		eProjectionShadowPriority m_ProjectionShadowPriority;

		CCamera *m_pCameraBackup;
		CCamera m_Camera;
		Math::Matrix m_mView;
		Math::Matrix m_mViewPrev;
		Math::Matrix m_mProjection;
		Math::Matrix m_mViewProjection;

		Renderer::CRenderObjectMgr *m_pActorMgr;

		Math::Vector3D m_vBrightness;
		Math::Vector4D m_vLightColor[LIGHT_MAX];
		Math::Vector3D m_vLightPosition[LIGHT_POINT_MAX];
		Float m_fLightDistance[LIGHT_POINT_MAX];
		Float m_fLightAttenuation[LIGHT_POINT_MAX];
		Math::Vector4D m_vLightDirection;
		Sint32 m_PointLightCount;

		Float m_fShadowMapNear;
		Float m_fShadowMapFar;
		Float m_fShadowMapBias;
		Float m_fShadowMapPower;
		Math::Matrix m_mShadowView;
		Math::Matrix m_mShadowViewProj;

		Float m_fHDRPower;
		Float m_fHDRBoundary;
		Float m_fEdgeNormalPower;
		Float m_fEdgeDepthPower;

		Float m_fFogFar;
		Float m_fFogNear;
		Math::Vector4D m_FogColor;
		Math::Vector4D m_FogParameter;
		Math::Vector4D m_DepthParameter;
		Math::Vector4D m_ShadowParameter;

		CCustomizedSceneRenderObject *m_pObjectList[ID_MAX];
		Renderer::CRender *m_pRender;
		Math::Rect2DI m_RenderRect;

		Thread::CThread m_Thread;
		Thread::CEvent m_Event;
		Thread::CEvent m_EventExit;
		Thread::CEvent m_EventSceneConstruct;
		Thread::CCriticalSection m_CS;
		Bool m_IsEndSceneConstruct;

		Sint32 m_QueMax;
		Sint32 m_QueCount;
		CCustomizedSceneRenderObject *m_pQueTbl;
		Math::Vector2D m_vSkydoomCloudOffset;
		Math::Vector4D m_vToonRenderParameter;

		Bool m_IsSort;

		Renderer::Object::IModel *m_pModelSkydoom;
		IModelActor *m_pActorSkydoom;

		Renderer::Object::CMapModel *m_pMapModel;
		Renderer::ITexture *m_pTextureBG;

		eSceneShadingType m_ShadingType;

		eSceneHighDynamicRangeType m_HdrType;
		eSceneHighDynamicRangeEffect m_HdrEffect;

		eSceneMotionBlurType m_MotionBlurType;
		eSceneMotionBlurQuarity m_MotionBlurQuarity;

		eSceneShadowType m_ShadowType;
		eSceneShadowQuarity m_ShadowQuarity;

		eSceneDepthOfFieldType m_DofType;

		eSceneFogType m_FogType;
		eSceneFogEffect m_FogEffect;

		eSceneAntiAliasType m_AntiAliasType;
		Float m_fAntiAliasPower;

		eHardwareShadowType m_HardwareShadowType;

		Math::Point2DI m_TargetSize;

		Float m_fFocusDepth;
		Float m_fFocusPower;
		Sint32 m_RenderRequestCount;
		Sint32 m_RenderCount;

		Renderer::Object::IParticle *m_pParticleShadow[PROJECTION_SHADOW_PRIORITY_MAX];
		IParticleActor *m_pActorShadow[PROJECTION_SHADOW_PRIORITY_MAX];

		Renderer::ITexture *m_pTextureShadowProjection;

		Bool m_IsClear;
		Math::Vector4D m_ClearColor;

		Uint64 m_SceneConstructTime;
		Uint64 m_SceneRenderingTime;

		Float m_fSoftParticleScale;

	protected:
		static void SceneConstructionFunc( void *pData );

	protected:
		virtual void SceneConstruction( void );
		virtual Bool CreateInstnaceModel( CActorObject *pActor );
		virtual Sint32 SearchPointLight( Sint32 NoTbl[], Math::Vector3D vPosition );
		virtual void InsertList( CCustomizedSceneRenderObject &Obj );
		virtual void ComputeRenderData( CCustomizedSceneRenderObject &Obj );
		virtual void WaitForSceneConstruct( void );
		virtual void SetSceneConstruct( Bool IsEnd );
		virtual Bool GetSceneConstruct( void );
		virtual void ClearDepthBuffer( void );
		virtual void ReleaseObjectList( void );

	protected:
		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual Bool RenderingStart( void ) { return false; }
		virtual void RenderingExit( void ) {}
		virtual Sint32 GetRenderObjectLayerCount( void ) { return 0; }
		virtual ICustomizedSceneRenderObject *GetRenderObject( Sint32 Layer ) { return NULL; }

	public:
		virtual Bool CreateRenderTargetBuffer( void ) = 0;
		virtual eShaderVersion GetShaderVersion( void ) = 0;

	public:
		CSceneManagerBase( Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr, Sint32 QueMax );
		virtual ~CSceneManagerBase();

		virtual Bool IsToonEnable( void );
		virtual Bool IsShadowEnable( void );
		virtual Bool IsDepthOfFieldEnable( void );
		virtual Bool IsHDREnable( void );
		virtual Bool IsFogEnable( void );
		virtual Bool IsVelocityEnable( void );
		virtual Bool IsAntiAliasEnable( void );
		virtual Bool IsSoftShadowEnable( void );

		virtual eSceneShadingType GetShadingType( void );
		virtual eSceneShadowType GetShadowType( void );
		virtual eSceneFogType GetFogType( void );
		virtual eSceneHighDynamicRangeType GetHdrType( void );
		virtual eSceneAntiAliasType GetAntiAliasType( void );

		virtual eHardwareShadowType GetHardwareShadowType( void );

		virtual void AddObject( CActorObject *pActor );
		virtual Sint32 GetNewRenderActorID( void );
		virtual void ReleaseRenderActorID( Sint32 RenderActorID );
		virtual CCamera &GetActiveCamera( void );

	public:
		virtual IInstanceModelActor *CreateActor( Renderer::Object::IModel *pObject, Sint32 InstanceCount );
		virtual IModelActor *CreateActor( Renderer::Object::IModel *pObject );
		virtual IMapActor *CreateActor( Renderer::Object::IMapModel *pObject );
		virtual IPrimitiveActor *CreateActor( Renderer::Object::IPoint3D *pObject );
		virtual IPrimitiveActor *CreateActor( Renderer::Object::ILine3D *pObject );
		virtual IPrimitiveActor *CreateActor( Renderer::Object::IPrimitive3D *pObject, Bool IsLightmap, Bool IsNormalmap, Bool IsSpecularmap, Bool IsEnvironmentmap );
		virtual ISpriteActor *CreateActor( Renderer::Object::ISprite3D *pObject );
		virtual IParticleActor *CreateActor( Renderer::Object::IFontSprite3D *pObject );
		virtual IParticleActor *CreateActor( Renderer::Object::IParticle *pObject );

		virtual ICamera *GetCamera( void );

		virtual void Abort( void );
		virtual void Reset( void );
		virtual void Begin( Bool IsSort );
		virtual void End( void );

		virtual Sint32 GetResult_BackgroundThreadTime( void );
		virtual Sint32 GetResult_RenderingTme( void );

		virtual void SetParameter_BGColor( CColor ClearColor, Bool IsClear );
		virtual void SetParameter_BGColor( Math::Vector4D &ClearColor, Bool IsClear );
		virtual void SetParameter_BGTexture( Renderer::ITexture *pTex );
		virtual void SetParameter_RenderRect( Math::Rect2DF &Dst );

		virtual void SetLightParameter_Directional( const Math::Vector3D &vDirect, const Math::Vector3D &vColor );
		virtual void SetLightParameter_AddPoint( const Math::Vector3D &vPosition, const Math::Vector3D &vColor, Float fDistance );
		virtual void SetLightParameter_Ambient( const Math::Vector3D &vColorSky, const Math::Vector3D &vColorEarth );

		virtual Sint32 GetResult_RenderingRequestActorCount( void );
		virtual Sint32 GetResult_RenderingActorCount( void );

		virtual Bool SceneSkydoom_Create( Float fRadius, CColor TopColor, CColor BottomColor, Renderer::ITexture *pTexCloud );
		virtual void SceneSkydoom_Rendering( void );
		virtual void SceneSkydoom_SetCloudOffset( const Math::Vector2D &vOffset );
		virtual void SceneSkydoom_SetCloudColor( const CColor &Color );

		virtual Math::Vector3D TransformToScreen( const Math::Vector3D &vPosition );
		virtual Math::Vector3D TransformFromScreen( const Math::Vector3D &vPosition );

		virtual void SetParameter_SceneBrightness( const Math::Vector3D &vBrightness );

		virtual void SetActorParameter_ProjectionShadow( eProjectionShadowType Type, eProjectionShadowPriority Priority, Float fRadius );
		virtual void SetActorParameter_MotionBlur( eSceneMotionBlurQuarity MotionBlurQuarity );

		virtual void SetParameter_HighDynamicRange( Float fHDRPower, Float fHDRBoundary );
		virtual void SetParameter_ToonEdge( Float fEdgeNormalPower, Float fEdgeDepthPower, Bool IsToonBold );
		virtual void SetParameter_Shadow( Math::Vector3D &vPosition, Math::Vector3D &vTarget, Float fSize, Float fNear, Float fFar, Float fBias, Float fPower );
		virtual void SetParameter_Toon( Math::Vector3D &vHatchingColor, Float fToonPower );
		virtual void SetParameter_Fog( Math::Vector3D &vColor, Float fNear, Float fFar );
		virtual void SetParameter_DepthOfField( Float fForcusZ, Float fPower );
		virtual void SetParameter_SoftParticleScale( Float fSoftParticleScale );

		virtual void InitParameter_RenderTargetData( Renderer::ITexture *pTarget, Math::Point2DI Size, Bool IsTextureSizePow2 );
		virtual void InitParameter_Shading( eSceneShadingType ShadingType );
		virtual void InitParameter_AntiAliasType( eSceneAntiAliasType AntiAliasType, Float fPower );
		virtual void InitParameter_Shadow( eSceneShadowType ShadowType, eSceneShadowQuarity ShadowQuarity, Bool IsSoftShadow, Bool IsHardwareShadowmap );
		virtual void InitParameter_MotionBlur( eSceneMotionBlurType MotionBlurType );
		virtual void InitParameter_DepthOfField( eSceneDepthOfFieldType DofType );
		virtual void InitParameter_Fog( eSceneFogType FogType, eSceneFogEffect FogEffect );
		virtual void InitParameter_HighDynamicRange( eSceneHighDynamicRangeType HdrType, eSceneHighDynamicRangeEffect HdrEffect );
		virtual Bool InitParameter_Update( void );
	};
}
}
