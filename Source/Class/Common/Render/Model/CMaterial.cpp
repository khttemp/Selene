

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Render/Model/CMaterial.h"
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
CMaterial::CMaterial()
	: m_vDiffuseColor	( 1.0f, 1.0f, 1.0f, 1.0f )
	, m_vEmissiveColor	( 0.0f, 0.0f, 0.0f, 0.0f )
	, m_vSpecularColor	( 1.0f, 1.0f, 1.0f, 0.0f )
	, m_vTextureOffset	( 0.0f, 0.0f )
	, m_fRefractive		( 20.0f * 20.0f )
	, m_fRoughly		( 0.5f * 0.5f )
	, m_fParallaxDepth	( 0.0f )
	, m_VertexStart		( 0 )
	, m_VertexCount		( 0 )
	, m_IndexStart		( 0 )
	, m_IndexCount		( 0 )
	, m_DrawType		( DRAW_TYPE_NORMAL )
	, m_CullType		( CULL_FRONT )
	, m_AlphaBoundary	( 0 )
	, m_IsAlphaTest		( true )
	, m_IsZTest			( true )
	, m_IsZWrite		( true )
	, m_IsLight			( true )
	, m_SpecularType	( SPECULAR_TYPE_NONE )
	, m_BumpType		( BUMP_TYPE_NONE )
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
CMaterial::~CMaterial()
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
void CMaterial::SetTexture( eTextureStage Stage, ITexture *pTexture ) 
{
	SAFE_RELEASE( m_pTexture[Stage] );
	m_pTexture[Stage] = pTexture;
	SAFE_ADDREF( m_pTexture[Stage] );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ITexture *CMaterial::GetTexturePointer( eTextureStage Stage )
{
	return m_pTexture[Stage];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMaterial::SetTextureOffset( const Math::Vector2D &Offset )
{
	m_vTextureOffset = Offset;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Vector2D CMaterial::GetTextureOffset( void )
{
	return m_vTextureOffset;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMaterial::SetDiffuseColor( const Math::Vector4D &Color )
{
	m_vDiffuseColor = Color;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Vector4D &CMaterial::GetDiffuseColor( void )
{
	return m_vDiffuseColor;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMaterial::SetEmissiveColor( const Math::Vector4D &Color )
{
	m_vEmissiveColor = Color;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Vector4D &CMaterial::GetEmissiveColor( void )
{
	return m_vEmissiveColor;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMaterial::SetSpecularColor( const Math::Vector4D &Color )
{
	m_vSpecularColor = Color;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Vector4D &CMaterial::GetSpecularColor( void )
{
	return m_vSpecularColor;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMaterial::SetSpecularRefractive( Float fRefractive )
{
	m_fRefractive = fRefractive * fRefractive;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CMaterial::GetSpecularRefractive( void )
{
	return m_fRefractive;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMaterial::SetSpecularRoughly( Float fRoughly )
{
	m_fRoughly = fRoughly * fRoughly;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CMaterial::GetSpecularRoughly( void )
{
	return m_fRoughly;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMaterial::SetParallaxDepth( Float fParallaxDepth )
{
	m_fParallaxDepth = fParallaxDepth;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CMaterial::GetParallaxDepth( void )
{
	return m_fParallaxDepth;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMaterial::SetVertexStart( Sint32 Start )
{
	m_VertexStart = Start;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMaterial::SetVertexCount( Sint32 Count )
{
	m_VertexCount = Count;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMaterial::SetIndexStart( Sint32 Start )
{
	m_IndexStart = Start;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMaterial::SetIndexCount( Sint32 Count )
{
	m_IndexCount = Count;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CMaterial::GetVertexStart( void )
{
	return m_VertexStart;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CMaterial::GetVertexCount( void )
{
	return m_VertexCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CMaterial::GetIndexStart( void )
{
	return m_IndexStart;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CMaterial::GetIndexCount( void )
{
	return m_IndexCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMaterial& CMaterial::operator = ( CMaterial &Src )
{
	for ( Sint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		SAFE_RELEASE( m_pTexture[i] );
		m_pTexture[i] = Src.m_pTexture[i];
		if ( m_pTexture[i] != NULL )
		{
			m_pTexture[i]->AddRef();
		}
	}

	m_vDiffuseColor		= Src.m_vDiffuseColor;
	m_vEmissiveColor	= Src.m_vEmissiveColor;
	m_vSpecularColor	= Src.m_vSpecularColor;
	m_vTextureOffset	= Src.m_vTextureOffset;
	m_fRefractive		= Src.m_fRefractive;
	m_fRoughly			= Src.m_fRoughly;

	m_VertexStart		= Src.m_VertexStart;
	m_VertexCount		= Src.m_VertexCount;
	m_IndexStart		= Src.m_IndexStart;
	m_IndexCount		= Src.m_IndexCount;

	m_DrawType			= Src.m_DrawType;
	m_CullType			= Src.m_CullType;
	m_IsAlphaTest		= Src.m_IsAlphaTest;
	m_IsZTest			= Src.m_IsZTest;
	m_IsZWrite			= Src.m_IsZWrite;

	m_SpecularType		= m_SpecularType;
	m_BumpType		= m_BumpType;

	return *this;
}

