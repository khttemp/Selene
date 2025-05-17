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
	class CTexture : public CBaseTexture, public CTextureInterface
	{
	protected:
		IDirect3DTexture9 *m_pTexture;

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
		CTexture( CRenderObjectMgr *pMgr );
		virtual ~CTexture();

		virtual Math::Point2DF GetPixelToTexelTransform( void );

		virtual Bool SaveToTGA( const char *pFileName );
		virtual Bool SaveToPNG( const char *pFileName );

		virtual Bool CreateFromFile( const char *pFileName, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize );
		virtual Bool CreateFromMemory( const void *pData, Sint32 Size, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize );

		virtual Math::Point2DI GetSize( void );
		virtual Math::Point2DI GetOriginalSize( void );
		virtual Bool BackupTargetBuffer( void );
	};
}
}
