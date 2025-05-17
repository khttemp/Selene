

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Platform/Render/Shader/ShaderEffect.h"
#include "Class/Platform/Render/Shader/CShader.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;
using namespace Shader;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ShaderEffect::ShaderEffect()
	: m_pShader		( NULL )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ShaderEffect::~ShaderEffect()
{
	SAFE_RELEASE( m_pShader );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void ShaderEffect::SetShader( IShader *pShader )
{
	m_pShader = pShader;
	UpdateTechniqueHandle();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void ShaderEffect::UpdateTechniqueHandle( void )
{
	if ( m_pShader != NULL )
	{
		const char *pTechniqueTbl[TECHNIQUE_EFFECT_MAX][2] = {
			{ "Technique_Depth",					"Technique_DepthB"						},
			{ "Technique_DepthNormal",				"Technique_DepthNormalB"				},
			{ "Technique_VelocitySimple",			"Technique_VelocitySimpleB"				},
			{ "Technique_Velocity",					"Technique_VelocityB"					},
			{ "Technique_ShadowMap",				"Technique_ShadowMapB"					},
			{ "Technique_ShadowProjection",			"Technique_ShadowProjectionB"			},
			{ "Technique_ShadowProjectionShape",	"Technique_ShadowProjectionShapeB"		},
			{ "Technique_ShadowProjectionShapeTex",	"Technique_ShadowProjectionShapeTexB"	},
		};

		for ( Sint32 i = 0; i < TECHNIQUE_EFFECT_MAX; i++ )
		{
			for ( Sint32 j = 0; j < 2; j++ )
			{
				m_hTechnique[i][j] = m_pShader->GetTechnique( pTechniqueTbl[i][j] );
			}
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void ShaderEffect::SetTechnique( eTechniqueEffectType TechType, Bool IsBoneEnable )
{
	m_pShader->SetTechnique( m_hTechnique[TechType][IsBoneEnable?1:0] );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void ShaderEffect::Begin( void )
{
	m_pShader->Begin( NULL );
	m_pShader->BeginPass( 0 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void ShaderEffect::End( void )
{
	m_pShader->EndPass();
	m_pShader->End();
}
