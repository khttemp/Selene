#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/3D/ILinePrimitive3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class NullLine3D : public ILine3D
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

		virtual Sint32 Rendering( void )
		{
			return -1;
		}

		virtual void PushBox( Collision::CBox &Box, CColor Color )
		{
		}

		virtual Bool Push( SLineVertex3D *pLine, Sint32 LineCount )
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
