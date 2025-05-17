#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Platform/Render/Shader/ShaderManager.h"
#include "Class/Common/Scene/CSceneActorObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class CMapActorObject : public CActorObject
	{
	protected:
		Bool m_IsParallax;
		Bool m_IsSpecular;
		Bool m_IsEnvironment;

	public:
		CMapActorObject( CSceneManagerBase *pScene );
		~CMapActorObject();

		virtual void SetParallaxEnable( Bool IsEnable );
		virtual void SetSpecularEnable( Bool IsEnable );
		virtual void SetEnvironmentEnable( Bool IsEnable );

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
