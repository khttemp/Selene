#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/ClassReference.h"
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
	struct ShaderVariable
	{
	private:
		IShader *m_pShader;

		FX_HANDLE m_hPointLightCount;

		FX_HANDLE m_hMaterialColor;
		FX_HANDLE m_hEmissiveColor;
		FX_HANDLE m_hSpecularColor;

		FX_HANDLE m_hTextureOffset;

		FX_HANDLE m_hToonParameter;

		FX_HANDLE m_hRefractive;
		FX_HANDLE m_hRoughly;

		FX_HANDLE m_hDirectionalLightDirection;
		FX_HANDLE m_hDirectionalLightColor;
		FX_HANDLE m_hPointLightPosition;
		FX_HANDLE m_hPointLightColor;
		FX_HANDLE m_hAmbientLightColorSky;
		FX_HANDLE m_hAmbientLightColorEarth;
		FX_HANDLE m_hCameraPosition;
		FX_HANDLE m_hParallaxDepth;

		FX_HANDLE m_hFogParameter;
		FX_HANDLE m_hFogColor;

		FX_HANDLE m_hDepthParameter;
		FX_HANDLE m_hDepthTransform;

		FX_HANDLE m_hShadowMapParameter;
		FX_HANDLE m_hShadowMapOffset;

		FX_HANDLE m_hBoneMatrixArray;
		FX_HANDLE m_hBoneMatrixArrayPrev;

		FX_HANDLE m_hProjection;

		FX_HANDLE m_hWorld;

		FX_HANDLE m_hWorldView;
		FX_HANDLE m_hWorldViewPrev;

		FX_HANDLE m_hWorldViewProjection;
		FX_HANDLE m_hWorldViewProjectionPrev;

		FX_HANDLE m_hViewInverse;
		FX_HANDLE m_hShadowWorldViewProjection;

		FX_HANDLE m_hSoftParticleScale;

	private:
		virtual void UpdateVariableHandle( void )
		{
			m_hPointLightCount				= m_pShader->GetParameterBySemantic( "PointLightCount" );
			m_hMaterialColor				= m_pShader->GetParameterBySemantic( "MaterialColor" );
			m_hEmissiveColor				= m_pShader->GetParameterBySemantic( "EmissiveColor" );
			m_hSpecularColor				= m_pShader->GetParameterBySemantic( "SpecularColor" );
			m_hToonParameter				= m_pShader->GetParameterBySemantic( "ToonParameter" );
			m_hRefractive					= m_pShader->GetParameterBySemantic( "Refractive" );
			m_hRoughly						= m_pShader->GetParameterBySemantic( "Roughly" );
			m_hTextureOffset				= m_pShader->GetParameterBySemantic( "TextureOffset" );
			m_hDirectionalLightDirection	= m_pShader->GetParameterBySemantic( "DirectionalLightDirection" );
			m_hDirectionalLightColor		= m_pShader->GetParameterBySemantic( "DirectionalLightColor" );
			m_hPointLightPosition			= m_pShader->GetParameterBySemantic( "PointLightPosition" );
			m_hPointLightColor				= m_pShader->GetParameterBySemantic( "PointLightColor" );
			m_hAmbientLightColorSky			= m_pShader->GetParameterBySemantic( "AmbientLightColorSky" );
			m_hAmbientLightColorEarth		= m_pShader->GetParameterBySemantic( "AmbientLightColorEarth" );
			m_hCameraPosition				= m_pShader->GetParameterBySemantic( "CameraPosition" );
			m_hParallaxDepth				= m_pShader->GetParameterBySemantic( "ParallaxDepth" );
			m_hFogParameter					= m_pShader->GetParameterBySemantic( "FogParameter" );
			m_hFogColor						= m_pShader->GetParameterBySemantic( "FogColor" );
			m_hShadowMapParameter			= m_pShader->GetParameterBySemantic( "ShadowMapParameter" );
			m_hShadowMapOffset				= m_pShader->GetParameterBySemantic( "ShadowMapOffset" );
			m_hDepthParameter				= m_pShader->GetParameterBySemantic( "DepthParameter" );
			m_hProjection					= m_pShader->GetParameterBySemantic( "Projection" );
			m_hWorld						= m_pShader->GetParameterBySemantic( "World" );
			m_hWorldView					= m_pShader->GetParameterBySemantic( "WorldView" );
			m_hWorldViewPrev				= m_pShader->GetParameterBySemantic( "WorldViewPrev" );
			m_hBoneMatrixArray				= m_pShader->GetParameterBySemantic( "BoneMatrixArray" );
			m_hBoneMatrixArrayPrev			= m_pShader->GetParameterBySemantic( "BoneMatrixArrayPrev" );
			m_hWorldViewProjection			= m_pShader->GetParameterBySemantic( "WorldViewProjection" );
			m_hWorldViewProjectionPrev		= m_pShader->GetParameterBySemantic( "WorldViewProjectionPrev" );
			m_hViewInverse					= m_pShader->GetParameterBySemantic( "ViewInverse" );
			m_hShadowWorldViewProjection	= m_pShader->GetParameterBySemantic( "ShadowWorldViewProjection" );
			m_hSoftParticleScale			= m_pShader->GetParameterBySemantic( "SoftParticleScale" );
		}

	public:
		ShaderVariable()
			: m_pShader	( NULL )
		{
		}

		~ShaderVariable()
		{
			SAFE_RELEASE( m_pShader );
		}

	public:
		virtual void SetShader( IShader *pShader )
		{
			m_pShader = pShader;
			UpdateVariableHandle();
		}

	public:
		void Update( void ) const 
		{
			m_pShader->UpdateParameter();
		}

		void SetPointLightCount( const Sint32 Param ) const 
		{
			m_pShader->SetInt( m_hPointLightCount, Param );
		}

		void SetMaterialColor( const Math::Vector4D &vParam ) const 
		{
			m_pShader->SetVector( m_hMaterialColor, &vParam );
		}

		void SetEmissiveColor( const Math::Vector4D &vParam ) const 
		{
			m_pShader->SetVector( m_hEmissiveColor, &vParam );
		}

		void SetSpecularColor( const Math::Vector4D &vParam ) const 
		{
			m_pShader->SetVector( m_hSpecularColor, &vParam );
		}

		void SetTextureOffset( const Math::Vector2D &vParam ) const 
		{
			Math::Vector4D vTemp( vParam.x, vParam.y, 0.0f, 0.0f );
			m_pShader->SetVector( m_hTextureOffset, &vTemp );
		}

		void SetToonParameter( const Math::Vector4D &vParam ) const 
		{
			m_pShader->SetVector( m_hToonParameter, &vParam );
		}

		void SetRefractive( const Float fParam ) const 
		{
			m_pShader->SetFloat( m_hRefractive, fParam );
		}

		void SetRoughly( const Float fParam ) const 
		{
			m_pShader->SetFloat( m_hRoughly, fParam );
		}

		void SetParallaxDepth( const Float fParam ) const 
		{
			m_pShader->SetFloat( m_hParallaxDepth, fParam );
		}

		void SetDirectionalLightDirection( const Math::Vector4D &vParam ) const 
		{
			m_pShader->SetVector( m_hDirectionalLightDirection, &vParam );
		}

		void SetDirectionalLightColor( const Math::Vector4D &vParam ) const 
		{
			m_pShader->SetVector( m_hDirectionalLightColor, &vParam );
		}

		void SetPointLightPosition( const Math::Vector4D *pParam, Sint32 Count ) const 
		{
			m_pShader->SetVectorArray( m_hPointLightPosition, pParam, Count );
		}

		void SetPointLightColor( const Math::Vector4D *pParam, Sint32 Count ) const 
		{
			m_pShader->SetVectorArray( m_hPointLightColor, pParam, Count );
		}

		void SetLightParameter_AmbientColorSky( const Math::Vector4D &vParam ) const 
		{
			m_pShader->SetVector( m_hAmbientLightColorSky, &vParam );
		}

		void SetLightParameter_AmbientColorEarth( const Math::Vector4D &vParam ) const 
		{
			m_pShader->SetVector( m_hAmbientLightColorEarth, &vParam );
		}

		void SetCameraPosition( const Math::Vector4D &vParam ) const 
		{
			m_pShader->SetVector( m_hCameraPosition, &vParam );
		}

		void SetFogParameter( const Math::Vector4D &vParam ) const 
		{
			m_pShader->SetVector( m_hFogParameter, &vParam );
		}

		void SetFogColor( const Math::Vector4D &vParam ) const 
		{
			m_pShader->SetVector( m_hFogColor, &vParam );
		}

		void SetDepthParameter( const Math::Vector4D &vParam ) const 
		{
			m_pShader->SetVector( m_hDepthParameter, &vParam );
		}

		void SetShadowMapParameter( const Math::Vector4D &vParam ) const 
		{
			m_pShader->SetVector( m_hShadowMapParameter, &vParam );
		}

		void SetShadowMapOffset( const Math::Vector4D *pParam ) const 
		{
			m_pShader->SetVectorArray( m_hShadowMapOffset, pParam, 4 );
		}

		void SetBoneMatrixArray( const Math::SMatrix4x4 *pParam, Sint32 Count ) const 
		{
			m_pShader->SetMatrixArray( m_hBoneMatrixArray, pParam, Count );
		}

		void SetBoneMatrixArrayPrev( const Math::SMatrix4x4 *pParam, Sint32 Count ) const 
		{
			m_pShader->SetMatrixArray( m_hBoneMatrixArrayPrev, pParam, Count );
		}

		void SetProjection( const Math::SMatrix4x4 *pParam ) const 
		{
			m_pShader->SetMatrix( m_hProjection, pParam );
		}

		void SetWorld( const Math::SMatrix4x4 *pParam ) const 
		{
			m_pShader->SetMatrix( m_hWorld, pParam );
		}

		void SetWorldView( const Math::SMatrix4x4 *pParam ) const 
		{
			m_pShader->SetMatrix( m_hWorldView, pParam );
		}

		void SetWorldViewPrev( const Math::SMatrix4x4 *pParam ) const 
		{
			m_pShader->SetMatrix( m_hWorldViewPrev, pParam );
		}

		void SetWorldViewProjection( const Math::SMatrix4x4 *pParam ) const 
		{
			m_pShader->SetMatrix( m_hWorldViewProjection, pParam );
		}

		void SetWorldViewProjectionPrev( const Math::SMatrix4x4 *pParam ) const 
		{
			m_pShader->SetMatrix( m_hWorldViewProjectionPrev, pParam );
		}

		void SetViewInverse( const Math::SMatrix4x4 *pParam ) const 
		{
			m_pShader->SetMatrix( m_hViewInverse, pParam );
		}

		void SetShadowWorldViewProjection( const Math::SMatrix4x4 *pParam ) const 
		{
			m_pShader->SetMatrix( m_hShadowWorldViewProjection, pParam );
		}

		void SetSoftParticleScale( Float fParam ) const 
		{
			m_pShader->SetFloat( m_hSoftParticleScale, fParam );
		}
	};
}
}
}

