#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CRenderObject.h"
#include "Interface/Surface/ITexture.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	enum eCubemapFaceType
	{
		CUBEMAP_FACE_POSITIVE_X,
		CUBEMAP_FACE_NEGATIVE_X,
		CUBEMAP_FACE_POSITIVE_Y,
		CUBEMAP_FACE_NEGATIVE_Y,
		CUBEMAP_FACE_POSITIVE_Z,
		CUBEMAP_FACE_NEGATIVE_Z,
		CUBEMAP_FACE_NONE,
	};

	class CTextureInterface : public ITexture
	{
	public:
		virtual ~CTextureInterface() {}

	public:
		virtual Bool GetTexture( IDirect3DBaseTexture9 *&pTexture, eCubemapFaceType FaceType = CUBEMAP_FACE_NONE ) = 0;
		virtual Bool GetSurface( IDirect3DSurface9 *&pSurface, eCubemapFaceType FaceType = CUBEMAP_FACE_NONE ) = 0;
		virtual eTextureType GetType( void ) = 0;

	public:
		virtual Bool IsStencilFormat( void ) { return false; }
		virtual Bool IsFilterEnable( void ) { return false; }
	};
}
}
