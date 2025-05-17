

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Math/Math.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/File/CFileManager.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Surface/CCubeTexture.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCubeTexture::CCubeTexture( CRenderObjectMgr *pMgr ) : CBaseTexture( pMgr )
	, m_pTexture		( NULL )
	, m_pBaseTexture	( NULL )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCubeTexture::~CCubeTexture()
{
	Log_PrintTable( 0xFF0000, 0x000000, "解放", "キューブテクスチャ", m_Name );
	Log_TableLine( 1 );

	m_pRender->ReleaseTexture( this );

	SAFE_RELEASE( m_pBaseTexture );
	SAFE_RELEASE( m_pTexture );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCubeTexture::CreateTextureFromImageInfo( const void *pData, Sint32 Size, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize )
{
	HRESULT hr;

	//------------------------------------------------------------
	// テクスチャ
	//------------------------------------------------------------
	m_Format		= m_pGraphicCard->GetFormat( Format );
	m_Size			= m_pGraphicCard->GetTextureSize( Math::Point2DI( m_ImageInfo.Width, m_ImageInfo.Height ), Format, IsMipmap );
	m_Pool			= D3DPOOL_MANAGED;
	m_SurfaceType	= SURFACE_TYPE_OFFSCREEN;

	// サイズ半分？
	if ( IsHalfSize && (m_Size.x >= 2) && (m_Size.y >= 2) )
	{
		m_Size.x /= 2;
		m_Size.y /= 2;
	}

	if ( m_Size.x < m_Size.y ) m_Size.x = m_Size.y;
	if ( m_Size.y < m_Size.x ) m_Size.y = m_Size.x;

	m_PixelToTexel.x = 1.0f / toF(m_ImageInfo.Width);
	m_PixelToTexel.y = 1.0f / toF(m_ImageInfo.Height);

	//------------------------------------------------------------
	// テクスチャの生成
	//------------------------------------------------------------
	hr = m_pRender->CreateCubeTextureFromInMemory(
						pData,
						Size,
						m_Size.x,
						IsMipmap ? 0 : 1,
						0,
						m_Format,
						m_Pool,
						&m_pTexture );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, "テクスチャの生成に失敗しました [%dx%d] [%s]", m_Size.x, m_Size.y, m_pGraphicCard->GetPixelFormat(m_Format) );
		Log_PrintLine( 0xFF00000, "%s", m_pGraphicCard->GetD3DError(hr) );
		SAFE_RELEASE( m_pTexture );
		return false;
	}

	// ログ
	Log_PrintLine( 0x0000000, "サイズ [%dx%d] フォーマット [%s] ミップマップ [%d]", m_Size.x, m_Size.y, m_pGraphicCard->GetPixelFormat(m_Format), m_pTexture->GetLevelCount() );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCubeTexture::CreateRenderTarget( Sint32 Size, eSurfaceFormat Format )
{
	HRESULT hr;

	//------------------------------------------------------------
	// イメージ情報
	//------------------------------------------------------------
	m_ImageInfo.Format		= m_pGraphicCard->GetFormat( Format );
	m_ImageInfo.Width		= Size;
	m_ImageInfo.Height		= Size;
	m_SurfaceType			= SURFACE_TYPE_RENDERTARGET;
	m_Pool					= D3DPOOL_DEFAULT;
	m_Format				= m_pGraphicCard->GetFormat( Format );
	m_Size					= m_pGraphicCard->GetTextureSize( Math::Point2DI( m_ImageInfo.Width, m_ImageInfo.Height ), Format, false );

	m_PixelToTexel.x		= 1.0f / toF(m_ImageInfo.Width);
	m_PixelToTexel.y		= 1.0f / toF(m_ImageInfo.Height);

	//------------------------------------------------------------
	// ベーステクスチャ生成
	//------------------------------------------------------------
	hr = m_pRender->CreateCubeTexture(
					m_Size.x,
					1,
					0,
					m_Format,
					D3DPOOL_SYSTEMMEM,
					&m_pBaseTexture );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, "ベーステクスチャの生成に失敗しました [%dx%d] [%s]", m_Size.x, m_Size.y, m_pGraphicCard->GetPixelFormat(m_Format) );
		Log_PrintLine( 0xFF00000, "%s", m_pGraphicCard->GetD3DError(hr) );
		return false;
	}

	//------------------------------------------------------------
	// テクスチャの生成
	//------------------------------------------------------------
	hr = m_pRender->CreateCubeTexture(
					m_Size.x,
					1,
					D3DUSAGE_RENDERTARGET,
					m_Format,
					m_Pool,
					&m_pTexture );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, "テクスチャの生成に失敗しました [%dx%d] [%s]", m_Size.x, m_Size.y, m_pGraphicCard->GetPixelFormat(m_Format) );
		Log_PrintLine( 0xFF00000, "%s", m_pGraphicCard->GetD3DError(hr) );
		return false;
	}

	// ログ
	Log_PrintLine( 0x0000000, "サイズ [%dx%d] フォーマット [%s]", m_Size.x, m_Size.y, m_pGraphicCard->GetPixelFormat(m_Format) );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCubeTexture::CreateFromFile( const char *pFileName, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize )
{
	void *pData = NULL;
	Sint32 Size;

	//--------------------------------------------------------
	// ファイルから読み込み
	//--------------------------------------------------------
	if ( !m_pCore->GetFileMgrPointer()->Load( pFileName, &pData, &Size ) )
	{
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintLine( 0xFF00000, "ファイルが開けません" );

		return false;
	}

	//--------------------------------------------------------
	// メモリから読み込み
	//--------------------------------------------------------
	if ( !CreateFromMemory( pData, Size, Format, KeyColor, IsMipmap, IsHalfSize ) )
	{
		m_pCore->GetFileMgrPointer()->Free( pData );
		return false;
	}

	m_pCore->GetFileMgrPointer()->Free( pData );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCubeTexture::CreateFromMemory( const void *pData, Sint32 Size, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize )
{
	SAFE_RELEASE( m_pTexture );

	//--------------------------------------------------------
	// 画像情報を取得
	//--------------------------------------------------------
	if ( !GetImageInfoFromMemory( pData, Size ) )
	{
		SAFE_RELEASE( m_pTexture );
		return false;
	}

	//--------------------------------------------------------
	// テクスチャを生成
	//--------------------------------------------------------
	if ( !CreateTextureFromImageInfo( pData, Size, Format, KeyColor, IsMipmap, IsHalfSize ) )
	{
		SAFE_RELEASE( m_pTexture );
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCubeTexture::OnLostDevice( void )
{
	switch ( m_SurfaceType )
	{
	case SURFACE_TYPE_RENDERTARGET:
		SAFE_RELEASE( m_pTexture );
		break;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCubeTexture::OnResetDevice( void )
{
	HRESULT hr = S_OK;

	switch ( m_SurfaceType )
	{
	case SURFACE_TYPE_RENDERTARGET:
		hr = m_pRender->CreateCubeTexture(
					m_Size.x,
					1,
					D3DUSAGE_RENDERTARGET,
					m_Format,
					D3DPOOL_DEFAULT,
					&m_pTexture );
		break;
	}

	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, "テクスチャの生成に失敗しました [ %s ]", m_pGraphicCard->GetD3DError(hr) );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCubeTexture::GetTexture( IDirect3DBaseTexture9 *&pTexture, eCubemapFaceType FaceType )
{
	if ( m_pTexture != NULL )
	{
		pTexture = m_pTexture;
		m_pTexture->AddRef();
	}
	else
	{
		pTexture = NULL;
	}

	return pTexture != NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCubeTexture::GetSurface( IDirect3DSurface9 *&pSurface, eCubemapFaceType FaceType )
{
	if ( m_pTexture != NULL )
	{
		m_pTexture->GetCubeMapSurface( (D3DCUBEMAP_FACES)FaceType, 0, &pSurface );
	}
	else
	{
		pSurface = NULL;
	}

	return pSurface != NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DF CCubeTexture::GetPixelToTexelTransform( void )
{
	return m_PixelToTexel;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DI CCubeTexture::GetSize( void )
{
	return m_Size;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DI CCubeTexture::GetOriginalSize( void )
{
	return Math::Point2DI( m_ImageInfo.Width, m_ImageInfo.Height );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCubeTexture::BackupTargetBuffer( void )
{
	return false;
}

