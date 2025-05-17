

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Surface/CBaseTexture.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseTexture::CBaseTexture( CRenderObjectMgr *pMgr ) : CRenderObject( pMgr->GetRenderPointer(), pMgr )
	, m_Pool			( D3DPOOL_DEFAULT )
	, m_PixelToTexel	( 1.0f, 1.0f )
	, m_Format			( D3DFMT_UNKNOWN )
	, m_Size			( 0, 0 )
	, m_SurfaceType		( SURFACE_TYPE_INVALID )
	, m_IsAutoRecover	( false )
{
	MemoryClear( &m_ImageInfo, sizeof(m_ImageInfo) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseTexture::~CBaseTexture()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CBaseTexture::LoadImageToBaseSurface( IDirect3DSurface9 *pSurface, const void *pData, Sint32 Size, Sint32 Width, Sint32 Height, CColor KeyColor )
{
	HRESULT hr;
	RECT Dst = { 0, 0, Width, Height };
	RECT Src = { 0, 0, m_ImageInfo.Width, m_ImageInfo.Height };

	//------------------------------------------------------
	// オフスクリーンサーフェイスに画像データをロード
	//------------------------------------------------------
	hr = ::D3DXLoadSurfaceFromFileInMemory(
				pSurface,
				NULL,
				&Dst,
				pData,
				Size,
				&Src,
				D3DX_FILTER_TRIANGLE,
				(D3DCOLOR)KeyColor,
				NULL );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, "データが開けません　[ %s ]", m_pGraphicCard->GetD3DError(hr) );
		return false;
	}

	return hr;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CBaseTexture::GetImageInfoFromMemory( const void *pData, Sint32 Size )
{
	HRESULT hr;

	//--------------------------------------------------------------
	// ファイル情報取得
	//--------------------------------------------------------------
	hr = ::D3DXGetImageInfoFromFileInMemory( pData, Size, &m_ImageInfo );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF00000, "ファイルが開けません　[ %s ]", m_pGraphicCard->GetD3DError(hr) );
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
D3DFORMAT CBaseTexture::GetFormat( void )
{
	return m_Format;
}

