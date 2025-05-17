

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Math/Math.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/File/CFileManager.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Surface/CTexture.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CTexture::CTexture( CRenderObjectMgr *pMgr ) : CBaseTexture( pMgr )
	, m_pTexture	( NULL )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CTexture::~CTexture()
{
	Log_PrintTable( 0xFF0000, 0x000000, "解放", "テクスチャ", m_Name );
	Log_TableLine( 1 );

	m_pRender->ReleaseTexture( this );

	SAFE_RELEASE( m_pTexture );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CTexture::CreateTextureFromImageInfo( const void *pData, Sint32 Size, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize )
{
	HRESULT hr;
	IDirect3DSurface9 *pSurface;
	D3DSURFACE_DESC Desc;

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

	m_PixelToTexel.x = 1.0f / toF(m_ImageInfo.Width);
	m_PixelToTexel.y = 1.0f / toF(m_ImageInfo.Height);

	//------------------------------------------------------------
	// テクスチャの生成
	//------------------------------------------------------------
	hr = m_pRender->CreateTexture(
						m_Size.x,
						m_Size.y,
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

	//------------------------------------------------------------
	// サーフェイスに画像読み込み
	//------------------------------------------------------------
	Sint32 Max = m_pTexture->GetLevelCount();
	for ( Sint32 i = 0; i < Max; i++ )
	{
		// サーフェイス取得
		hr = m_pTexture->GetSurfaceLevel( i, &pSurface );
		if FAILED( hr )
		{
			Log_PrintLine( 0xFF00000, "サーフェイスの取得に失敗しました [%dx%d] [%s]", m_Size.x, m_Size.y, m_pGraphicCard->GetPixelFormat(m_Format) );
			Log_PrintLine( 0xFF00000, "%s", m_pGraphicCard->GetD3DError(hr) );
			SAFE_RELEASE( m_pTexture );
			return false;
		}

		// サーフェイス情報取得
		pSurface->GetDesc( &Desc );

		// サーフェイスに画像データ読み込み
		hr = LoadImageToBaseSurface( pSurface, pData, Size, Desc.Width, Desc.Height, KeyColor );
		if FAILED( hr )
		{
			Log_PrintLine( 0xFF00000, "画像の読み込みに失敗しました [%dx%d] [%s]", m_Size.x, m_Size.y, m_pGraphicCard->GetPixelFormat(m_Format) );
			Log_PrintLine( 0xFF00000, "%s", m_pGraphicCard->GetD3DError(hr) );
			SAFE_RELEASE( pSurface );
			SAFE_RELEASE( m_pTexture );
			return false;
		}

		SAFE_RELEASE( pSurface );
	}

	// ログ
	Log_PrintLine( 0x0000000, "サイズ [%dx%d] フォーマット [%s] ミップマップ [%d]", m_Size.x, m_Size.y, m_pGraphicCard->GetPixelFormat(m_Format), Max );
	Log_PrintLine( 0x0000000, "残VRAM容量 %.3lfMB", m_pRender->GetRestVRAM() );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CTexture::CreateFromFile( const char *pFileName, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize )
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
Bool CTexture::CreateFromMemory( const void *pData, Sint32 Size, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize )
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
void CTexture::OnLostDevice( void )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CTexture::OnResetDevice( void )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CTexture::GetTexture( IDirect3DBaseTexture9 *&pTexture, eCubemapFaceType FaceType )
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
Bool CTexture::GetSurface( IDirect3DSurface9 *&pSurface, eCubemapFaceType FaceType )
{
	if ( m_pTexture != NULL )
	{
		m_pTexture->GetSurfaceLevel( 0, &pSurface );
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
Math::Point2DF CTexture::GetPixelToTexelTransform( void )
{
	return m_PixelToTexel;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CTexture::SaveToTGA( const char *pFileName )
{
	if ( m_pTexture != NULL )
	{
		// 保存
		HRESULT hr;
		hr = ::D3DXSaveTextureToFile(
					pFileName,
					D3DXIFF_TGA,
					m_pTexture,
					NULL );
		return SUCCEEDED( hr );
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CTexture::SaveToPNG( const char *pFileName )
{
	if ( m_pTexture != NULL )
	{
		// 保存
		HRESULT hr;
		hr = ::D3DXSaveTextureToFile(
					pFileName,
					D3DXIFF_PNG,
					m_pTexture,
					NULL );
		return SUCCEEDED( hr );
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CTexture::BackupTargetBuffer( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DI CTexture::GetSize( void )
{
	return m_Size;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DI CTexture::GetOriginalSize( void )
{
	return Math::Point2DI( m_ImageInfo.Width, m_ImageInfo.Height );
}

