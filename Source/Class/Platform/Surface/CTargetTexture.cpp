

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Math/Math.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/File/CFileManager.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Surface/CTargetTexture.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CTargetTexture::CTargetTexture( CRenderObjectMgr *pMgr ) : CBaseTexture( pMgr )
	, m_pTexture		( NULL )
	, m_pBaseTexture	( NULL )
	, m_IsFilterEnable	( false )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CTargetTexture::~CTargetTexture()
{
	Log_PrintTable( 0xFF0000, 0x000000, "解放", "ターゲットテクスチャ", m_Name );
	Log_TableLine( 1 );

	m_pRender->ReleaseTexture( this );

	SAFE_RELEASE( m_pBaseTexture );
	SAFE_RELEASE( m_pTexture );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CTargetTexture::CreateRenderTarget( Sint32 Width, Sint32 Height, eSurfaceFormat Format )
{
	HRESULT hr;

	//------------------------------------------------------------
	// イメージ情報
	//------------------------------------------------------------
	m_ImageInfo.Format	= m_pGraphicCard->GetFormat( Format );
	m_ImageInfo.Width	= Width;
	m_ImageInfo.Height	= Height;
	m_SurfaceType		= SURFACE_TYPE_RENDERTARGET;
	m_Pool				= D3DPOOL_DEFAULT;
	m_Format			= m_pGraphicCard->GetFormat( Format );
	m_Size				= m_pGraphicCard->GetTextureSize( Math::Point2DI( m_ImageInfo.Width, m_ImageInfo.Height ), Format, false );

	m_PixelToTexel.x	= 1.0f / toF(m_ImageInfo.Width);
	m_PixelToTexel.y	= 1.0f / toF(m_ImageInfo.Height);

	m_IsFilterEnable	= GetGraphicCardPointer()->CheckAlphaBlending( m_Format );

	//------------------------------------------------------------
	// ベーステクスチャ生成
	//------------------------------------------------------------
	hr = m_pRender->CreateTexture(
					m_Size.x,
					m_Size.y,
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
	hr = m_pRender->CreateTexture(
					m_Size.x,
					m_Size.y,
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
	Log_PrintLine( 0x0000000, "残VRAM容量 %.3lfMB", m_pRender->GetRestVRAM() );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CTargetTexture::OnLostDevice( void )
{
	SAFE_RELEASE( m_pTexture );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CTargetTexture::OnResetDevice( void )
{
	HRESULT hr = m_pRender->CreateTexture(
					m_Size.x,
					m_Size.y,
					1,
					D3DUSAGE_RENDERTARGET,
					m_Format,
					D3DPOOL_DEFAULT,
					&m_pTexture );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, "テクスチャの生成に失敗しました [ %s ]", m_pGraphicCard->GetD3DError(hr) );
	}

	// 自動復元
	if ( m_IsAutoRecover )
	{
		if FAILED( UploadToVram() )
		{
			Log_PrintLine( 0xFF00000, "テクスチャの復旧に失敗しました [ %s ]", m_pGraphicCard->GetD3DError(hr) );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CTargetTexture::GetTexture( IDirect3DBaseTexture9 *&pTexture, eCubemapFaceType FaceType )
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
Bool CTargetTexture::GetSurface( IDirect3DSurface9 *&pSurface, eCubemapFaceType FaceType )
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
Math::Point2DF CTargetTexture::GetPixelToTexelTransform( void )
{
	return m_PixelToTexel;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CTargetTexture::SaveToTGA( const char *pFileName )
{
	if ( m_pTexture != NULL )
	{
		// レンダリングターゲットの場合はシステムにコピ－
		DownloadToSystem();

		// 保存
		HRESULT hr;
		hr = ::D3DXSaveTextureToFile(
					pFileName,
					D3DXIFF_TGA,
					m_pBaseTexture != NULL ? m_pBaseTexture : m_pTexture,
					NULL );
		return SUCCEEDED( hr );
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CTargetTexture::SaveToPNG( const char *pFileName )
{
	if ( m_pTexture != NULL )
	{
		// レンダリングターゲットの場合はシステムにコピ－
		DownloadToSystem();

		// 保存
		HRESULT hr;
		hr = ::D3DXSaveTextureToFile(
					pFileName,
					D3DXIFF_PNG,
					m_pBaseTexture != NULL ? m_pBaseTexture : m_pTexture,
					NULL );
		return SUCCEEDED( hr );
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CTargetTexture::DownloadToSystem( void )
{
	HRESULT hr;
	IDirect3DSurface9 *pSrcSurf;
	IDirect3DSurface9 *pDstSurf;

	if ( m_pBaseTexture == NULL ) return false;
	if ( m_pTexture     == NULL ) return false;

	Bool bRet = false;

	hr = m_pTexture->GetSurfaceLevel( 0, &pSrcSurf );
	if SUCCEEDED( hr )
	{
		hr = m_pBaseTexture->GetSurfaceLevel( 0, &pDstSurf );
		if SUCCEEDED( hr )
		{
			hr = m_pRender->GetRenderTargetData( pSrcSurf, pDstSurf );
			if SUCCEEDED( hr )
			{
				bRet = true;
			}

			SAFE_RELEASE( pDstSurf );
		}

		SAFE_RELEASE( pSrcSurf );
	}

	return bRet;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CTargetTexture::UploadToVram( void )
{	
	HRESULT hr;
	IDirect3DSurface9 *pSrcSurf;
	IDirect3DSurface9 *pDstSurf;

	if ( m_pBaseTexture == NULL ) return false;
	if ( m_pTexture     == NULL ) return false;

	Bool bRet = false;

	hr = m_pTexture->GetSurfaceLevel( 0, &pDstSurf );
	if SUCCEEDED( hr )
	{
		hr = m_pBaseTexture->GetSurfaceLevel( 0, &pSrcSurf );
		if SUCCEEDED( hr )
		{
			hr = m_pRender->UpdateSurface( pSrcSurf, pDstSurf );
			if SUCCEEDED( hr )
			{
				bRet = true;
			}

			SAFE_RELEASE( pSrcSurf );
		}

		SAFE_RELEASE( pDstSurf );
	}

	return bRet;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CTargetTexture::BackupTargetBuffer( void )
{
	if ( !DownloadToSystem() )
	{
		return false;
	}
	
	// 保存できたら「自動復旧」フラグを立てる
	m_IsAutoRecover = true;;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DI CTargetTexture::GetSize( void )
{
	return m_Size;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DI CTargetTexture::GetOriginalSize( void )
{
	return Math::Point2DI( m_ImageInfo.Width, m_ImageInfo.Height );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CTargetTexture::IsFilterEnable( void )
{
	return m_IsFilterEnable;
}

