#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Platform/Render/Shader/ShaderManager.h"
#include "Interface/Surface/ITexture.h"
#include "Interface/Scene/ICustomizedSceneRenderMaterial.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class CSceneActorMaterial : public ICustomizedSceneRenderMaterial
	{
	private:
		Renderer::Shader::IShader *m_pShader;

		Sint32 m_IndexStart;
		Sint32 m_IndexCount;
		Sint32 m_VertexStart;
		Sint32 m_VertexCount;
		Renderer::ITexture *m_pTextureTbl[TEXTURE_STAGE_MAX];

		Math::Vector4D m_vDiffuseColor;
		Math::Vector4D m_vEmissiveColor;
		Math::Vector4D m_vSpecularColor;
		Math::Vector2D m_vTextureOffset;
		Float m_fRefractive;
		Float m_fRoughly;
		Float m_fParallaxDepth;

		eSpecularType m_SpecularType;
		eBumpType m_BumpType;

		eDrawType m_DrawType;
		eCullType m_CullType;
		Sint32 m_AlphaBoundary;
		Bool m_IsAlphaTest;
		Bool m_IsZTest;
		Bool m_IsZWrite;
		Bool m_IsLight;

	public:
		CSceneActorMaterial();
		virtual ~CSceneActorMaterial();
		virtual void SetShader( Renderer::Shader::IShader *pShader );
		virtual void SetIndexStart( Sint32 Cnt );
		virtual void SetIndexCount( Sint32 Cnt );
		virtual void SetVertexStart( Sint32 Cnt );
		virtual void SetVertexCount( Sint32 Cnt );
		virtual void SetTexture( eTextureStage Stage, Renderer::ITexture *pTex );
		virtual void SetDiffuseColor( const Math::Vector4D &Color );
		virtual void SetEmissiveColor( const Math::Vector4D &Color );
		virtual void SetSpecularColor( const Math::Vector4D &Color );
		virtual void SetTextureOffset( const Math::Vector2D &Offset );
		virtual void SetSpecularRefractive( Float fRefractive );
		virtual void SetSpecularRoughly( Float fRoughly );
		virtual void SetParallaxDepth( Float fDepth );
		virtual void SetSpecularType( eSpecularType Mode );
		virtual void SetBumpType( eBumpType Mode );
		virtual void SetDrawType( eDrawType Type );
		virtual void SetCullType( eCullType Type );
		virtual void SetAlphaBoundary( Sint32 Bound );
		virtual void SetAlphaTestEnable( Bool IsEnable );
		virtual void SetZTestEnable( Bool IsEnable );
		virtual void SetZWriteEnable( Bool IsEnable );
		virtual void SetLightEnable( Bool IsEnable );
		virtual Renderer::Shader::IShader *GetShader( void );
		virtual Sint32 GetIndexStart( void );
		virtual Sint32 GetIndexCount( void );
		virtual Sint32 GetVertexStart( void );
		virtual Sint32 GetVertexCount( void );
		virtual Renderer::ITexture *GetTexture( Sint32 Stage );
		virtual Math::Vector4D &GetDiffuseColor( void );
		virtual Math::Vector4D &GetEmissiveColor( void );
		virtual Math::Vector4D &GetSpecularColor( void );
		virtual Math::Vector2D &GetTextureOffset( void );
		virtual Float GetSpecularRefractive( void );
		virtual Float GetSpecularRoughly( void );
		virtual Float GetParallaxDepth( void );
		virtual eSpecularType GetSpecularType( void );
		virtual eBumpType GetBumpType( void );
		virtual eDrawType GetDrawType( void );
		virtual eCullType GetCullType( void );
		virtual Sint32 GetAlphaBoundary( void );
		virtual Bool GetAlphaTestEnable( void );
		virtual Bool GetZTestEnable( void );
		virtual Bool GetZWriteEnable( void );
		virtual Bool GetLightEnable( void );
	};
}
}
