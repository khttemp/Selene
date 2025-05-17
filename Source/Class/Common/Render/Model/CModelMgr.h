#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CRenderObjectMgr.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CModelMgr : public CRenderObjectMgr
	{
	public:
		CModelMgr( CRender *pRender );
		virtual ~CModelMgr();

		CModel *SearchInstance( const char *pFileName );

		virtual CModel *CreateFromFile( const char *pFileName, CRender *pRender );
		virtual CModel *CreateFromMemory( const void *pData, Sint32 Size, CRender *pRender );
		virtual CModel *SceneSkydoom_Create( Float fRadius, CColor TopColor, CColor BottomColor, ITexture *pTexCloud, CRender *pRender );
	};
}
}
}
