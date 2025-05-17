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
	class CSceneManager_Shader : public CSceneManagerBase
	{
	private:
		// 影
		Renderer::ITexture *m_pRT_Shadow;
		Renderer::ITexture *m_pDS_Shadow;
		// テンポラリ
		Renderer::ITexture *m_pRT_Temp_HDR;
		Renderer::ITexture *m_pRT_Temp_DOF;
		Renderer::ITexture *m_pRT_Final;
		// HDR
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
		// モーションブラー
		Renderer::ITexture *m_pRT_Velocity;
		Renderer::ITexture *m_pRT_VelocityTemp;
		// 法線/深度
		Renderer::ITexture *m_pRT_DepthNormal;

		Math::Vector4D m_ShadowMapOffset[4];
		Math::Matrix m_mShadowOffset;

	private:
		virtual void Rendering( void );
		virtual void Rendering_DebugBuffer( void );
		virtual void Rendering_AlphaDisable( void );
		virtual void Rendering_AlphaEnable( void );
		virtual void Rendering_Shadowmap( Math::Point2DI Size );
		virtual void Rendering_ShadowProjection( Math::Point2DI Size );
		virtual void Rendering_Velocity( void );
		virtual void Rendering_DepthNormal( void );

		virtual void DrawToonEDGE( void );

		virtual void PostEffect( void );

		virtual void CreateShadowmap( void );

		virtual void ClearBackground( Bool IsRendering );

	protected:
		virtual Bool CreateRenderTargetBuffer( void );

	public:
		CSceneManager_Shader( Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr, Sint32 QueMax );
		virtual ~CSceneManager_Shader();

		virtual void Rendering( Bool IsDrawBuffer );
		virtual eShaderVersion GetShaderVersion( void ) { return SHADER_MODEL_2_0; }
	};
}
}
