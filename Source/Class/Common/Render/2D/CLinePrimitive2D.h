#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Common/Render/2D/CPrimitive2DBase.h"
#include "Interface/Render/2D/ILinePrimitive2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CLine2D : public CPrimitive2DBase, public ILine2D
	{
		enum { LINE_POINT_COUNT = 2 };

	protected:
		virtual Sint32 ScissorPolygon( SVertex2D *pDst, SVertex2D *pSrc );
		virtual Sint32 ScissorPolygonLeft( SVertex2D *pPtIn, SVertex2D *pPtOut, Sint32 VxNum );
		virtual Sint32 ScissorPolygonTop( SVertex2D *pPtIn, SVertex2D *pPtOut, Sint32 VxNum );
		virtual Sint32 ScissorPolygonRight( SVertex2D *pPtIn, SVertex2D *pPtOut, Sint32 VxNum );
		virtual Sint32 ScissorPolygonBottom( SVertex2D *pPtIn, SVertex2D *pPtOut, Sint32 VxNum );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CLine2D( CRender *pRender, CRenderObjectMgr *pMgr );
		virtual ~CLine2D();

		virtual Bool Create( Sint32 LineMax, Bool IsAutoResize, Sint32 ResizeStep );

		virtual Bool Push( SLineVertex2D *pLine, Sint32 Count );
		virtual void Rendering( void );
		virtual void Begin( void );
		virtual void End( void );
	};
}
}
}
