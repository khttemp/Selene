#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Peripheral/IKeyboard.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Peripheral
{
	class NullKeyboard : public IKeyboard
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

		virtual void ClearKeyBuffer( void )
		{
		}

		virtual eVirtualKeyCode GetKeyBuffer( void )
		{
			return SELENE_VK_DISABLE;
		}

		virtual Bool GetKeyData( eVirtualKeyCode Key )
		{
			return false;
		}
	};
}
}

