#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Common/Render/2D/CPrimitive2DBase.h"
#include "Interface/Render/2D/IPrimitive2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CPrimitive2D : public CPrimitive2DBase, public IPrimitive2D
	{
		enum { PRIMITIVE_POINT_COUNT = 3 };

	protected:
		virtual Sint32 ScissorPolygon( SVertex2DTex *pDst, SVertex2DTex *pSrc );
		virtual Sint32 ScissorPolygonLeft( SVertex2DTex *pPtIn, SVertex2DTex *pPtOut, Sint32 VxNum );
		virtual Sint32 ScissorPolygonTop( SVertex2DTex *pPtIn, SVertex2DTex *pPtOut, Sint32 VxNum );
		virtual Sint32 ScissorPolygonRight( SVertex2DTex *pPtIn, SVertex2DTex *pPtOut, Sint32 VxNum );
		virtual Sint32 ScissorPolygonBottom( SVertex2DTex *pPtIn, SVertex2DTex *pPtOut, Sint32 VxNum );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CPrimitive2D( CRender *pRender, CRenderObjectMgr *pMgr );
		virtual ~CPrimitive2D();

		virtual Bool Create( Sint32 PrimitiveMax, Bool IsAutoResize, Sint32 ResizeStep );

		virtual Sint32 GetRequestedVertexCount( void );
		virtual Sint32 GetRequestedVertexCountMax( void );

		virtual Bool Push( SPrimitiveVertex2D *pPrimitive, Sint32 Count );
		virtual void Begin( void );
		virtual void End( void );
		virtual void Rendering( void );
		virtual void RenderingNoStateChange( void );

		virtual void Square( Math::Rect2DI &DstRect, CColor Color );
		virtual void SquareRotate( Math::Rect2DI &DstRect, CColor Color, Sint32 Angle );

		virtual void Polygon( Math::Point2DI Pos, Float fRadius, CColor Color, Sint32 Num );
		virtual void PolygonRotate( Math::Point2DI Pos, Float fRadius, CColor Color, Sint32 Num, Sint32 Angle );

		virtual void Ring( Math::Point2DI Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num );
		virtual void RingRotate( Math::Point2DI Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num, Sint32 Angle );
	};
}
}
}
