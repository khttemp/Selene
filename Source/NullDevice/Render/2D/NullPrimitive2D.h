#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
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
	class NullPrimitive2D : public IPrimitive2D
	{
	public:
		virtual Bool IsInvalid( void )
		{
			return true;
		}

		virtual Sint32 Release( void )
		{
			return 0;
		}

		virtual Sint32 AddRef( void )
		{
			return 0;
		}

		virtual void Begin( void )
		{
		}

		virtual void End( void )
		{
		}

		virtual Bool Push( SPrimitiveVertex2D *pPrimitive, Sint32 Count )
		{
			return false;
		}

		virtual Sint32 GetRequestedVertexCount( void )
		{
			return 0;
		}

		virtual Sint32 GetRequestedVertexCountMax( void )
		{
			return 0;
		}

		virtual void Rendering( void )
		{
		}

		virtual void Square( Math::Rect2DI &DstRect, CColor Color )
		{
		}

		virtual void SquareRotate( Math::Rect2DI &DstRect, CColor Color, Sint32 Angle )
		{
		}

		virtual void Polygon( Math::Point2DI Pos, Float fRadius, CColor Color, Sint32 Num )
		{
		}

		virtual void PolygonRotate( Math::Point2DI Pos, Float fRadius, CColor Color, Sint32 Num, Sint32 Angle )
		{
		}

		virtual void Ring( Math::Point2DI Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num )
		{
		}

		virtual void RingRotate( Math::Point2DI Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num, Sint32 Angle )
		{
		}
	};
}
}
}
