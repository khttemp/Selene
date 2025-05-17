#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Platform/Render/CRender.h"
#include "Class/Common/Object/CRenderObjectMgr.h"
#include "Class/Platform/Surface/CBaseTexture.h"
#include "Class/Platform/Surface/CTextureInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	class CCubeTexture : public CBaseTexture, public CTextureInterface
	{
	protected:
		IDirect3DCubeTexture9	*m_pTexture;
		IDirect3DCubeTexture9	*m_pBaseTexture;

	protected:
		virtual Bool CreateTextureFromImageInfo( const void *pData, Sint32 Size, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize );

		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual Bool GetTexture( IDirect3DBaseTexture9 *&pTexture, eCubemapFaceType FaceType );
		virtual Bool GetSurface( IDirect3DSurface9 *&pSurface, eCubemapFaceType FaceType );
		virtual eTextureType GetType( void ) { return TEXTURE_TYPE_DEFAULT; }
		virtual eDepthBufferType GetDepthBufferType( void ) { return DEPTH_BUFFER_SURFACE; }

	public:
		CCubeTexture( CRenderObjectMgr *pMgr );
		virtual ~CCubeTexture();

		virtual Math::Point2DF GetPixelToTexelTransform( void );

		virtual Bool CreateRenderTarget( Sint32 Size, eSurfaceFormat Format );
		virtual Bool CreateFromFile( const char *pFileName, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize );
		virtual Bool CreateFromMemory( const void *pData, Sint32 Size, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize );

		virtual Math::Point2DI GetSize( void );
		virtual Math::Point2DI GetOriginalSize( void );

		virtual Bool SaveToTGA( const char *pFileName ) { return false; }
		virtual Bool SaveToPNG( const char *pFileName ) { return false; }

		virtual Bool BackupTargetBuffer( void );
	};
}
}
