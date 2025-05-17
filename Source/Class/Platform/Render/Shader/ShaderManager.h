#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Platform/Render/Shader/ShaderVariable.h"
#include "Class/Platform/Render/Shader/ShaderEffect.h"
#include "Class/Platform/Render/Shader/CShader.h"
#include "Class/Platform/Render/CRender.h"
#include "Math/Vector4D.h"
#include "Math/Matrix.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	enum eShaderVersion
	{
		SHADER_MODEL_2_0,
		SHADER_MODEL_0_0,
		SHADER_MODEL_CUSTOM,
		SHADER_MODEL_MAX,
	};

namespace Renderer
{
namespace Shader
{
	struct SShaderMaterialData
	{
		Math::Vector4D vMaterialColor;
		Math::Vector4D vEmissiveColor;
		Math::Vector4D vSpecularColor;
		Math::Vector2D vTextureOffset;
		SRenderState RenderState;
		Float fParallaxDepth;
		Float fRefractive;
		Float fRoughly;
		eSpecularType SpecularType;
		eBumpType BumpType;
	};

	struct SModelCacheParameter
	{
		Plugin::Shader::SModelParameter Param;
		eShaderVersion ShaderVersion;
		eSceneShadingType ShadingType;
		eSceneFogType FogType;
		eSceneHighDynamicRangeType HdrType;
		eSceneShadowType ShadowType;
	};

	class CModelShaderCache : public CBaseObject
	{
	private:
		SModelCacheParameter m_Param;
		CShader *m_pShader;

	public:
		CModelShaderCache( CShader *pShader, const SModelCacheParameter &Param )
			: m_pShader	( pShader )
			, m_Param	( Param )
		{
			m_pShader->AddRef();
		}

		~CModelShaderCache()
		{
			SAFE_RELEASE( m_pShader );
		}

		Bool IsSameParameter( const SModelCacheParameter &Param )
		{
			return memcmp( &m_Param, &Param, sizeof(SModelCacheParameter) ) == 0;
		}

		void GetShader( CShader *&pShader )
		{
			m_pShader->AddRef();
			pShader = m_pShader;
		}
	};

	struct SBillboardCacheParameter
	{
		Plugin::Shader::SBillboardParameter Param;
		eShaderVersion ShaderVersion;
		eSceneShadingType ShadingType;
		eSceneFogType FogType;
		eSceneHighDynamicRangeType HdrType;
	};

	class CBillboardShaderCache : public CBaseObject
	{
	private:
		SBillboardCacheParameter m_Param;
		CShader *m_pShader;

	public:
		CBillboardShaderCache( CShader *pShader, const SBillboardCacheParameter &Param )
			: m_pShader	( pShader )
			, m_Param	( Param )
		{
			m_pShader->AddRef();
		}

		~CBillboardShaderCache()
		{
			SAFE_RELEASE( m_pShader );
		}

		Bool IsSameParameter( const SBillboardCacheParameter &Param )
		{
			return memcmp( &m_Param, &Param, sizeof(SBillboardCacheParameter) ) == 0;
		}

		void GetShader( CShader *&pShader )
		{
			m_pShader->AddRef();
			pShader = m_pShader;
		}
	};

	class ShaderManager
	{
	public:
		static Bool m_IsDfaulteShaderEnable;
		static CRender *m_pRender;
		static CPostEffect *m_pPostEffect;
		static ShaderVariable *m_pShaderVariable;
		static ShaderEffect *m_pShaderEffect;
		static char m_PluginDirectory[MAX_PATH];

		static CBaseList m_ModelChacheList;
		static CBaseList m_BillboardChacheList;

	private:
		static Bool SearchSameShader( CShader *&pShader, const SModelCacheParameter &Param );
		static Bool SearchSameShader( CShader *&pShader, const SBillboardCacheParameter &Param );

		static void AddCahcheShader( CShader *pShader, const SModelCacheParameter &Param );
		static void AddCahcheShader( CShader *pShader, const SBillboardCacheParameter &Param );

	public:
		static Bool Initialize( CRender *pRender, const char *pPluginDirectory );
		static void Finalize( void );

		static Bool IsDfaulteShaderEnable( void );
		static ShaderVariable *GetShaderVariable( void );
		static ShaderEffect *GetShaderEffect( void );
		static CShader *GetShader( eShaderVersion ShaderVersion, const Plugin::Shader::SModelParameter &Param, eSceneShadingType ShadingType, eSceneFogType FogType, eSceneHighDynamicRangeType HdrType, eSceneShadowType ShadowType, eHardwareShadowType HardareShadowType, Bool IsSoftShadow );
		static CShader *GetShader( eShaderVersion ShaderVersion, const Plugin::Shader::SBillboardParameter &Param, eSceneShadingType ShadingType, eSceneFogType FogType, eSceneHighDynamicRangeType HdrType );
		static CPostEffect *GetPostEffect( void );
	};
}
}
}

