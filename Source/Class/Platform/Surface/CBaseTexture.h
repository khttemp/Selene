#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Color.h"
#include "Class/Common/Object/CRenderObject.h"
#include "Class/Common/Object/CRenderObjectMgr.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	enum eSurfaceType
	{
		SURFACE_TYPE_OFFSCREEN,
		SURFACE_TYPE_RENDERTARGET,
		SURFACE_TYPE_DEPTHSTENCIL,

		SURFACE_TYPE_INVALID,
	};

	class CBaseTexture : public CRenderObject
	{
	protected:
		D3DPOOL				m_Pool;
		D3DXIMAGE_INFO		m_ImageInfo;
		Math::Point2DF		m_PixelToTexel;
		D3DFORMAT			m_Format;
		Math::Point2DI		m_Size;
		eSurfaceType		m_SurfaceType;
		Bool				m_IsAutoRecover;

	protected:
		virtual HRESULT LoadImageToBaseSurface( IDirect3DSurface9 *pSurface, const void *pData, Sint32 Size, Sint32 Width, Sint32 Height, CColor KeyColor );
		virtual Bool GetImageInfoFromMemory( const void *pData, Sint32 Size );
		virtual D3DFORMAT GetFormat( void );

	public:
		CBaseTexture( CRenderObjectMgr *pMgr );
		virtual ~CBaseTexture();

	public:
		virtual void OnLostDevice( void ) = 0;
		virtual void OnResetDevice( void ) = 0;
	};
}
}
