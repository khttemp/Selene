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
	class CPrimitive3DBaseMgr : public CRenderObjectMgr
	{
	public:
		CPrimitive3DBaseMgr( CRender *pRender );
		virtual ~CPrimitive3DBaseMgr();
	};
}
}
}
