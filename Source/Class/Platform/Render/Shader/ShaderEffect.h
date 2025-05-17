#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Platform/Render/Shader/ShaderBase.h"
#include "Class/Platform/Render/Shader/CShader.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Shader
{
	struct ShaderEffect
	{
	private:
		FX_HANDLE m_hTechnique[TECHNIQUE_EFFECT_MAX][2];
		IShader *m_pShader;

	public:
		ShaderEffect();
		~ShaderEffect();

		void UpdateTechniqueHandle( void );

	public:
		void SetShader( IShader *pShader );
		void SetTechnique( eTechniqueEffectType TechType, Bool IsBoneEnable );

		void Begin( void );
		void End( void );
	};
}
}
}
