#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Peripheral/IJoystick.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Peripheral
{
	class NullJoystick : public IJoystick
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

		virtual Sint32 GetAxis( ePadAxisType Type, ePadAxisDirection Dir )
		{
			return 0;
		}

		virtual Sint32 GetSlider( ePadSliderType Type )
		{
			return 0;
		}

		virtual Bool GetButton( ePadButtonType Type )
		{
			return false;
		}
	};
}
}
