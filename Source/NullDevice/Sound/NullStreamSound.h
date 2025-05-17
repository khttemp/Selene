#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Sound/IStreamSound.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Sound
{
	class NullStreamSound : public IStreamSound
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

		virtual Bool Play( SPlayBlock *pTbl, Sint32 Count )
		{
			return false;
		}

		virtual Bool Play( Sint32 LoopCount )
		{
			return false;
		}

		virtual Bool Stop( void )
		{
			return false;
		}

		virtual Bool Pause( void )
		{
			return false;
		}

		virtual Bool SetVolume( Float fVolume )
		{
			return false;
		}

		virtual Bool SetPan( Float fPan )
		{
			return false;
		}

		virtual Bool IsPlay( void )
		{
			return false;
		}
	};
}
}
