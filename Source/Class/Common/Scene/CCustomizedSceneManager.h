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
	class CCustomizedSceneManager : public CSceneManagerBase
	{
	private:
		Uint64 m_TimeStart;

	protected:
		virtual Bool CreateRenderTargetBuffer( void ) { return true; }

	public:
		CCustomizedSceneManager( Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr, Sint32 QueMax );
		virtual ~CCustomizedSceneManager();

		virtual Bool RenderingStart( void );
		virtual void RenderingExit( void );
		virtual Sint32 GetRenderObjectLayerCount( void );
		virtual ICustomizedSceneRenderObject *GetRenderObject( Sint32 Layer );

		virtual void Rendering( Bool IsDeugBuffer ) {}
		virtual Bool InitParameter_Update( void ) { return true; }
		virtual void InitParameter_RenderTargetData( Renderer::ITexture *pTarget, Math::Point2DI Size, Bool IsTextureSizePow2 ) {}
		virtual eShaderVersion GetShaderVersion( void ) { return SHADER_MODEL_CUSTOM; }
		virtual eSceneShadingType GetShadingType( void ) { return SHADING_TYPE_NORMAL; }
	};
}
}
