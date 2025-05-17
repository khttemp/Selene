#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Common/Render/2D/CPrimitive2DBase.h"
#include "Interface/Render/2D/IPointPrimitive2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CPoint2D : public CPrimitive2DBase, public IPoint2D
	{
	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CPoint2D( CRender *pRender, CRenderObjectMgr *pMgr );
		virtual ~CPoint2D();

		virtual Bool Create( Sint32 PointMax, Bool IsAutoResize, Sint32 ResizeStep );

		virtual Bool Push( SVertex2D *pPoint, Sint32 Count );
		virtual void Rendering( void );
		virtual void Begin( void );
		virtual void End( void );
	};
}
}
}
