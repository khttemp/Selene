#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Collision/Box.h"
#include "Interface/Scene/ISceneManager.h"
#include "Interface/Scene/ICustomizedSceneManager.h"
#include "NullDevice/Scene/NullSceneCamera.h"
#include "NullDevice/Scene/NullSceneActor.h"
#include "NullDevice/Surface/NullTexture.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class NullManager : public ISceneManager, public ICustomizedSceneManager
	{
	public:
		virtual Bool IsInvalid( void )
		{
			return true;
		}

		virtual Sint32 Release( void )
		{
			return 0;
		}

		virtual Sint32 AddRef( void	)
		{
			return 0;
		}

		virtual void Abort( void )
		{
		}

		virtual ICamera *GetCamera( void )
		{
			static NullCamera Dummy;
			return &Dummy;
		}

		virtual void Reset( void )
		{
		}

		virtual void Begin( Bool IsSort )
		{
		}

		virtual void End( void )
		{
		}

		virtual void Rendering( Bool IsDrawBuffer )
		{
		}

		virtual IInstanceModelActor *CreateActor( Renderer::Object::IModel *pObject, Sint32 InstanceCount )
		{
			static NullSceneActor Dummy;
			return &Dummy;
		}

		virtual IModelActor *CreateActor( Renderer::Object::IModel *pObject )
		{
			static NullSceneActor Dummy;
			return &Dummy;
		}

		virtual IMapActor *CreateActor( Renderer::Object::IMapModel *pObject )
		{
			static NullSceneActor Dummy;
			return &Dummy;
		}

		virtual IPrimitiveActor *CreateActor( Renderer::Object::IPoint3D *pObject )
		{
			static NullSceneActor Dummy;
			return &Dummy;
		}

		virtual IPrimitiveActor *CreateActor( Renderer::Object::ILine3D *pObject )
		{
			static NullSceneActor Dummy;
			return &Dummy;
		}

		virtual IPrimitiveActor *CreateActor( Renderer::Object::IPrimitive3D *pObject, Bool IsLightmap, Bool IsNormalmap, Bool IsSpecularmap, Bool IsEnvironmentmap )
		{
			static NullSceneActor Dummy;
			return &Dummy;
		}

		virtual ISpriteActor *CreateActor( Renderer::Object::ISprite3D *pObject )
		{
			static NullSceneActor Dummy;
			return &Dummy;
		}

		virtual IParticleActor *CreateActor( Renderer::Object::IParticle *pObject )
		{
			static NullSceneActor Dummy;
			return &Dummy;
		}

		virtual IParticleActor *CreateActor( Renderer::Object::IFontSprite3D *pObject )
		{
			static NullSceneActor Dummy;
			return &Dummy;
		}

		virtual void SetParameter_BGColor( Math::Vector4D &ClearColor, Bool IsClear )
		{
		}

		virtual void SetParameter_BGColor( CColor ClearColor, Bool IsClear )
		{
		}

		virtual void SetParameter_BGTexture( Renderer::ITexture *pTex )
		{
		}

		virtual void SetParameter_SceneBrightness( const Math::Vector3D &vBrightness )
		{
		}

		virtual void SetLightParameter_Ambient( const Math::Vector3D &vColorSky, const Math::Vector3D &vColorEarth )
		{
		}

		virtual void SetLightParameter_Directional( const Math::Vector3D &vDirect, const Math::Vector3D &vColor )
		{
		}

		virtual void SetLightParameter_AddPoint( const Math::Vector3D &vPosition, const Math::Vector3D &vColor, Float fDistance )
		{
		}

		virtual Bool RenderingStart( void )
		{
			return false;
		}

		virtual void RenderingExit( void )
		{
		}

		virtual Sint32 GetRenderObjectLayerCount( void )
		{
			return 0;
		}

		virtual ICustomizedSceneRenderObject *GetRenderObject( Sint32 Layer )
		{
			return NULL;
		}

		virtual Sint32 GetResult_RenderingRequestActorCount( void )
		{
			return 0;
		}

		virtual Sint32 GetResult_RenderingActorCount( void )
		{
			return 0;
		}

		virtual Sint32 GetResult_BackgroundThreadTime( void )
		{
			return 0;
		}

		virtual Sint32 GetResult_RenderingTme( void )
		{
			return 0;
		}

		virtual void SetActorParameter_ProjectionShadow( eProjectionShadowType ProjectionShadowType, eProjectionShadowPriority Priority, Float fRadius )
		{
		}

		virtual void SetActorParameter_MotionBlur( eSceneMotionBlurQuarity MotionBlurQuarity )
		{
		}

		virtual void SetParameter_Toon( Math::Vector3D &vHatchingColor, Float fToonPower )
		{
		}

		virtual void SetParameter_HighDynamicRange( Float fHDRPower, Float fHDRBoundary )
		{
		}

		virtual void SetParameter_ToonEdge( Float fEdgeNormalPower, Float fEdgeDepthPower, Bool IsToonBold )
		{
		}

		virtual void SetParameter_Shadow( Math::Vector3D &vPosition, Math::Vector3D &vTarget, Float fSize, Float fNear, Float fFar, Float fBias, Float fPower )
		{
		}

		virtual void SetParameter_Fog( Math::Vector3D &vColor, Float fNear, Float fFar )
		{
		}

		virtual void SetParameter_DepthOfField( Float fForcusZ, Float fPower )
		{
		}

		virtual void SetParameter_SoftParticleScale( Float fSoftParticleScale )
		{
		}

		virtual void SetParameter_RenderRect( Math::Rect2DF &Dst )
		{
		}

		virtual Bool InitParameter_Update( void )
		{
			return false;
		}

		virtual void InitParameter_RenderTargetData( Renderer::ITexture *pTarget, Math::Point2DI Size, Bool IsTextureSizePow2 )
		{
		}

		virtual void InitParameter_Shading( eSceneShadingType ShadingType )
		{
		}

		virtual void InitParameter_AntiAliasType( eSceneAntiAliasType AntiAliasType, Float fPower )
		{
		}

		virtual void InitParameter_Shadow( eSceneShadowType ShadowType, eSceneShadowQuarity ShadowQuarity, Bool IsSoftShadow, Bool IsHardwareShadowmap )
		{
		}

		virtual void InitParameter_MotionBlur( eSceneMotionBlurType MotionBlurType )
		{
		}

		virtual void InitParameter_DepthOfField( eSceneDepthOfFieldType DofType )
		{
		}

		virtual void InitParameter_Fog( eSceneFogType FogType, eSceneFogEffect FogEffect )
		{
		}

		virtual void InitParameter_HighDynamicRange( eSceneHighDynamicRangeType HdrType, eSceneHighDynamicRangeEffect HdrEffect )
		{
		}

		virtual void SceneSkydoom_SetCloudOffset( const Math::Vector2D &vOffset )
		{
		}

		virtual void SceneSkydoom_SetCloudColor( const CColor &Color )
		{
		}

		virtual void SceneSkydoom_Rendering( void )
		{
		}

		virtual Bool SceneSkydoom_Create( Float fRadius, CColor TopColor, CColor BottomColor, Renderer::ITexture *pTexCloud )
		{
			return false;
		}

		virtual Math::Vector3D TransformToScreen( const Math::Vector3D &vPosition )
		{
			return Math::Vector3D( 0.0f, 0.0f, 0.0f );
		}

		virtual Math::Vector3D TransformFromScreen( const Math::Vector3D &vPosition )
		{
			return Math::Vector3D( 0.0f, 0.0f, 0.0f );
		}
	};
}
}
