#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Common/SMF.h"
#include "Class/Platform/Render/Shader/ShaderManager.h"
#include "Class/Common/Scene/CSceneActorObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class CSpriteActorObject : public CActorObject
	{
	public:
		CSpriteActorObject( CSceneManagerBase *pScene );
		~CSpriteActorObject();

		virtual void Update( Math::Matrix &mWorld, Math::Matrix &mWorldInverse );
		virtual void UpdateMaterial( Renderer::CRender *pRender );

		virtual Sint32 GetBoneCount( void );

	public:
		virtual void SetStreamSource( Renderer::CRender *pRender );
		virtual Sint32 Rendering( Sint32 MaterialNo, Renderer::CRender *pRender );
		virtual Sint32 Rendering_Velocity( Renderer::CRender *pRender );
		virtual eTransformType GetTransformType( void );
		virtual Bool IsAlphaEnable( void );
		virtual Bool GetSoftBillboardEnable( void );
		virtual Bool GetCullTestEnable( void );
		virtual Bool GetParallaxEnable( void );
		virtual Bool GetSpecularEnable( void );
		virtual Bool GetEnvironmentEnable( void );
	};
}
}
