#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Platform/Render/Shader/ShaderManager.h"
#include "Interface/Render/IRender.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CMapMaterial
	{
	private:
		ITexture *m_pTexture[TEXTURE_STAGE_MAX];
		Math::Vector4D m_vDiffuseColor;
		Math::Vector4D m_vEmissiveColor;
		Math::Vector4D m_vSpecularColor;
		Math::Vector2D m_vTextureOffset;
		Float m_fRefractive;
		Float m_fRoughly;
		Float m_fParallaxDepth;

		eDrawType m_DrawType;
		eCullType m_CullType;
		Sint32 m_AlphaBoundary;
		Bool m_IsAlphaTest;
		Bool m_IsZTest;
		Bool m_IsZWrite;
		Bool m_IsLight;

		eSpecularType m_SpecularType;
		eBumpType m_BumpType;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return 0; }
		virtual Sint32 AddRef( void )  { return 0; }

	public:
		CMapMaterial();
		virtual ~CMapMaterial();

		virtual void SetTexture( eTextureStage Stage, ITexture *pTexture );
		virtual ITexture *GetTexturePointer( Sint32 Stage ) const;

		virtual void SetTextureOffset( const Math::Vector2D &Offset );
		virtual const Math::Vector2D GetTextureOffset( void ) const;

		virtual void SetDiffuseColor( const Math::Vector4D &Color );
		virtual const Math::Vector4D &GetDiffuseColor( void ) const;

		virtual void SetEmissiveColor( const Math::Vector4D &Color );
		virtual const Math::Vector4D &GetEmissiveColor( void ) const;

		virtual void SetSpecularColor( const Math::Vector4D &Color );
		virtual const Math::Vector4D &GetSpecularColor( void ) const;

		virtual void SetSpecularRefractive( Float fRefractive );
		virtual Float GetSpecularRefractive( void );

		virtual void SetSpecularRoughly( Float fRoughly );
		virtual Float GetSpecularRoughly( void );

		virtual void SetParallaxDepth( Float fParallaxDepth );
		virtual Float GetParallaxDepth( void );

		virtual void SetSpecularType( eSpecularType Mode ) { m_SpecularType = Mode; }
		virtual eSpecularType GetSpecularType( void ) { return m_SpecularType; }

		virtual void SetBumpmapMode( eBumpType Mode ) { m_BumpType = Mode; }
		virtual eBumpType GetBumpmapMode( void )  { return m_BumpType; }

		virtual eDrawType GetDrawType( void )    { return m_DrawType;      }
		virtual eCullType GetCullType( void )    { return m_CullType;      }
		virtual Sint32 GetAlphaBoundary( void )  { return m_AlphaBoundary; }
		virtual Bool GetAlphaTestEnable( void )  { return m_IsAlphaTest;   }
		virtual Bool GetDepthTestEnable( void )  { return m_IsZTest;       }
		virtual Bool GetDepthWriteEnable( void ) { return m_IsZWrite;      }
		virtual Bool GetLightEnable( void )      { return m_IsLight;       }

		virtual void SetDrawType( eDrawType DrawType )      { m_DrawType    = DrawType;      }
		virtual void SetCullType( eCullType CullType )      { m_CullType    = CullType;      }
		virtual void SetAlphaBoundary( Sint32 Bound )       { m_AlphaBoundary = Bound;       }
		virtual void SetAlphaTestEnable( Bool IsAlphaTest ) { m_IsAlphaTest = IsAlphaTest;   }
		virtual void SetDepthTestEnable( Bool IsZTest )     { m_IsZTest     = IsZTest;       }
		virtual void SetDepthWriteEnable( Bool IsZWrite )   { m_IsZWrite    = IsZWrite;      }
		virtual void SetLightEnable( Bool IsLight )         { m_IsLight     = IsLight;     }

		CMapMaterial& operator = ( CMapMaterial &Src );
	};
}
}
}
