#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/3D/IPointPrimitive3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class NullPoint3D : public IPoint3D
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

		virtual Sint32 AddRef( void	)
		{
			return 0;
		}

		virtual Bool Push( const SVertex3DBase *pPoint, Sint32 PointCount )
		{
			return false;
		}

		virtual void Begin( void )
		{
		}

		virtual void End( void )
		{
		}

		virtual void SetTransform( Math::Style &Style )
		{
		}
	};
}
}
}
