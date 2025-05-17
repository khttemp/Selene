#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Common/Object/CRenderObjectMgr.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	class CTextureMgr : public CRenderObjectMgr
	{
	public:
		CTextureMgr( CRender *pRender );
		virtual ~CTextureMgr();

		CTexture *SearchInstance( const char *pFileName );

		virtual CDepthTexture *CreateTextureDepthBuffer( Sint32 Width, Sint32 Height );
		virtual CTargetTexture *CreateRenderTarget( Sint32 Width, Sint32 Height, eSurfaceFormat Format );

		virtual CTexture *CreateFromFile( const char *pFileName, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize );
		virtual CTexture *CreateFromMemory( const void *pData, Sint32 Size, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize );

		virtual CCubeTexture *CubeCreateRenderTarget( Sint32 Size, eSurfaceFormat Format, Bool IsHalfSize );
		virtual CCubeTexture *CubeCreateFromFile( const char *pFileName, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize );
		virtual CCubeTexture *CubeCreateFromMemory( const void *pData, Sint32 Size, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize );
	};
}
}

