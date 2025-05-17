#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Math.h"
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
	class CPrimitive2DBaseMgr : public CRenderObjectMgr
	{
	public:
		CPrimitive2DBaseMgr( CRender *pRender );
		virtual ~CPrimitive2DBaseMgr();

		virtual void SetScissoring( Math::Rect2DF *pRect );
	};
}
}
}
