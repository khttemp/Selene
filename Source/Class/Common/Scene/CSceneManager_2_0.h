#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CSceneManagerBase.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class CSceneManager_2_0 : public CSceneManagerBase
	{
	private:
		Renderer::ITexture *m_pRT_Temp;
		Renderer::CDepthTexture *m_pDS_Shadow;
		Renderer::ITexture *m_pRT_Small;
		Renderer::ITexture *m_pRT_Blur;
		Renderer::ITexture *m_pRT_HDR;
		Renderer::ITexture *m_pRT_HDR1;
		Renderer::ITexture *m_pRT_HDR1_GausA;
		Renderer::ITexture *m_pRT_HDR1_GausB;
		Renderer::ITexture *m_pRT_HDR2;
		Renderer::ITexture *m_pRT_HDR2_GausA;
		Renderer::ITexture *m_pRT_HDR2_GausB;
		Renderer::ITexture *m_pRT_HDR3;
		Renderer::ITexture *m_pRT_HDR3_GausA;
		Renderer::ITexture *m_pRT_HDR3_GausB;
		Renderer::ITexture *m_pRT_Shadow;
		Renderer::ITexture *m_pRT_ShadowSoft;
		Renderer::ITexture *m_pRT_Velocity;
		Renderer::ITexture *m_pRT_NormalDepth;

	private:
		virtual void Rendering( void );
		virtual void Rendering_DebugBuffer( void );
		virtual void Rendering_AlphaDisable( void );
		virtual void Rendering_AlphaEnable( void );
		virtual void Rendering_Shadowmap( Math::Point2DI Size );
		virtual void Rendering_ShadowProjection( Math::Point2DI Size );
		virtual void Rendering_Velocity( void );
		virtual void Rendering_NormalDepth( void );

		virtual void PostEffectEDGE( void );
		virtual void PostEffectDOF( void );
		virtual void PostEffectHDR( void );

		virtual void CreateShadowmap( void );

		virtual void ClearBackground( void );

	protected:
		virtual void CreateRenderTargetBuffer( void );

	public:
		CSceneManager_2_0( Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr, Sint32 QueMax );
		virtual ~CSceneManager_2_0();

		virtual void Rendering( Bool IsDrawBuffer );
		virtual eShaderVersion GetShaderVersion( void ) { return SHADER_MODEL_2_0; }
	};
}
}
