

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Render/Map/CMapMaterial.h"
#include "Interface/Surface/ITexture.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;
using namespace Object;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapMaterial::CMapMaterial()
	: m_vDiffuseColor	( 1.0f, 1.0f, 1.0f, 1.0f )
	, m_vEmissiveColor	( 0.0f, 0.0f, 0.0f, 0.0f )
	, m_vSpecularColor	( 1.0f, 1.0f, 1.0f, 0.0f )
	, m_vTextureOffset	( 0.0f, 0.0f )
	, m_fRefractive		( 20.0f * 20.0f )
	, m_fRoughly		( 0.5f * 0.5f )
	, m_fParallaxDepth	( 0.0f )
	, m_DrawType		( DRAW_TYPE_NORMAL )
	, m_CullType		( CULL_FRONT )
	, m_IsAlphaTest		( true )
	, m_IsZTest			( true )
	, m_IsZWrite		( true )
	, m_IsLight			( true )
	, m_AlphaBoundary	( 0 )
	, m_SpecularType	( SPECULAR_TYPE_NONE )
	, m_BumpType	( BUMP_TYPE_NONE )
{
	for ( Sint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		m_pTexture[i] = NULL;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapMaterial::~CMapMaterial()
{
	Log_TableBegin();
	Log_PrintCellTitle( 0xFF0000, "‰ð•ú" );
	Log_PrintCellKind( "ƒ}ƒeƒŠƒAƒ‹" );
	Log_CellBegin( 0 );

	for ( Sint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		SAFE_RELEASE( m_pTexture[i] );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapMaterial::SetTexture( eTextureStage Stage, ITexture *pTexture ) 
{
	SAFE_RELEASE( m_pTexture[Stage] );
	m_pTexture[Stage] = pTexture;
	if ( pTexture != NULL )
	{
		pTexture->AddRef();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ITexture *CMapMaterial::GetTexturePointer( Sint32 Stage ) const
{
	return m_pTexture[Stage];
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapMaterial::SetTextureOffset( const Math::Vector2D &Offset )
{
	m_vTextureOffset = Offset;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Vector2D CMapMaterial::GetTextureOffset( void ) const
{
	return m_vTextureOffset;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapMaterial::SetDiffuseColor( const Math::Vector4D &Color )
{
	m_vDiffuseColor = Color;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Vector4D &CMapMaterial::GetDiffuseColor( void )const
{
	return m_vDiffuseColor;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapMaterial::SetEmissiveColor( const Math::Vector4D &Color )
{
	m_vEmissiveColor = Color;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Vector4D &CMapMaterial::GetEmissiveColor( void ) const
{
	return m_vEmissiveColor;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapMaterial::SetSpecularColor( const Math::Vector4D &Color )
{
	m_vSpecularColor = Color;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Vector4D &CMapMaterial::GetSpecularColor( void ) const
{
	return m_vSpecularColor;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapMaterial::SetSpecularRefractive( Float fRefractive )
{
	m_fRefractive = fRefractive * fRefractive;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CMapMaterial::GetSpecularRefractive( void )
{
	return m_fRefractive;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapMaterial::SetSpecularRoughly( Float fRoughly )
{
	m_fRoughly = fRoughly * fRoughly;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CMapMaterial::GetSpecularRoughly( void )
{
	return m_fRoughly;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapMaterial::SetParallaxDepth( Float fParallaxDepth )
{
	m_fParallaxDepth = fParallaxDepth;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CMapMaterial::GetParallaxDepth( void )
{
	return m_fParallaxDepth;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapMaterial& CMapMaterial::operator = ( CMapMaterial &Src )
{
	for ( Sint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		SAFE_RELEASE( m_pTexture[i] );
		m_pTexture[i] = Src.m_pTexture[i];
		SAFE_ADDREF( m_pTexture[i] );
	}

	m_vDiffuseColor		= Src.m_vDiffuseColor;
	m_vEmissiveColor	= Src.m_vEmissiveColor;
	m_vSpecularColor	= Src.m_vSpecularColor;
	m_vTextureOffset	= Src.m_vTextureOffset;
	m_fRefractive		= Src.m_fRefractive;
	m_fRoughly			= Src.m_fRoughly;

	m_DrawType			= Src.m_DrawType;
	m_CullType			= Src.m_CullType;
	m_IsAlphaTest		= Src.m_IsAlphaTest;
	m_IsZTest			= Src.m_IsZTest;
	m_IsZWrite			= Src.m_IsZWrite;
	m_IsLight			= Src.m_IsLight;

	m_SpecularType		= Src.m_SpecularType;
	m_BumpType			= Src.m_BumpType;

	return *this;
}

