#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Platform/Surface/CTextureInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	class NullTexture : public CTextureInterface
	{
	public:
		virtual Bool IsInvalid( void )
		{
			return true;
		}

		virtual Sint32 Release( void )
		{
			return 0;
		}

		virtual Sint32 AddRef( void )
		{
			return 0;
		}

		virtual Bool SaveToTGA( const char *pFileName )
		{
			return false;
		}

		virtual Bool SaveToPNG( const char *pFileName )
		{
			return false;
		}

		virtual Math::Point2DI GetSize( void )
		{
			return Math::Point2DI( 1, 1 );
		}

		virtual Math::Point2DI GetOriginalSize( void )
		{
			return Math::Point2DI( 1, 1 );
		}

		virtual Math::Point2DF GetPixelToTexelTransform( void )
		{
			return Math::Point2DF( 0.0f, 0.0f );
		}

		virtual Bool BackupTargetBuffer( void )
		{
			return false;
		}

		virtual Bool GetTexture( IDirect3DBaseTexture9 *&pTexture, eCubemapFaceType FaceType )
		{
			return false;
		}

		virtual Bool GetSurface( IDirect3DSurface9 *&pSurface, eCubemapFaceType FaceType )
		{
			return false;
		}

		virtual eTextureType GetType( void )
		{
			return TEXTURE_TYPE_NONE;
		}

		virtual eDepthBufferType GetDepthBufferType( void )
		{
			return DEPTH_BUFFER_SURFACE;
		}
	};
}
}
