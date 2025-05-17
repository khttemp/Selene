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
	class CSceneManager_Fixed : public CSceneManagerBase
	{
	private:
		virtual void Rendering_NoPS( void );
		virtual void Rendering_All( void );

	protected:
		virtual Bool CreateRenderTargetBuffer( void );
		virtual void SceneClear( void );

	public:
		CSceneManager_Fixed( Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr, Sint32 QueMax );
		virtual ~CSceneManager_Fixed();

		virtual void Rendering( Bool IsDrawBuffer );
		virtual eShaderVersion GetShaderVersion( void ) { return SHADER_MODEL_0_0; }
	};
}
}
