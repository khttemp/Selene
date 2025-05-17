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
	class CDepthTexture : public CBaseTexture, public CTextureInterface
	{
	protected:
		eDepthBufferType	m_DepthBufferType;
		IDirect3DTexture9	*m_pTexture;
		IDirect3DSurface9	*m_pSurface;

	protected:
		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual Bool GetTexture( IDirect3DBaseTexture9 *&pTexture, eCubemapFaceType FaceType );
		virtual Bool GetSurface( IDirect3DSurface9 *&pSurface, eCubemapFaceType FaceType );
		virtual Bool IsStencilFormat( void );

	public:
		CDepthTexture( CRenderObjectMgr *pMgr );
		virtual ~CDepthTexture();

		virtual Bool SaveToTGA( const char *pFileName );
		virtual Bool SaveToPNG( const char *pFileName );

		virtual Bool CreateTextureDepthBuffer( Sint32 Width, Sint32 Height );

		virtual Bool BackupTargetBuffer( void );

		virtual Math::Point2DI GetSize( void );
		virtual Math::Point2DI GetOriginalSize( void );
		virtual Math::Point2DF GetPixelToTexelTransform( void );

		virtual eTextureType GetType( void ) { return TEXTURE_TYPE_DEPTH; }
		virtual eDepthBufferType GetDepthBufferType( void ) { return m_DepthBufferType; }
	};
}
}
