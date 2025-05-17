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
	class CMapModelMgr : public CRenderObjectMgr
	{
	public:
		CMapModelMgr( CRender *pRender );
		virtual ~CMapModelMgr();

		CMapModel *SearchInstance( const char *pFileName );

		virtual CMapModel *CreateFromFile( const char *pFileName, CRender *pRender );
		virtual CMapModel *CreateFromMemory( const void *pData, Sint32 Size, CRender *pRender );
	};
}
}
}
