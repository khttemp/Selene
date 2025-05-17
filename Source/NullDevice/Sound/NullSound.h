#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Sound/ISound.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Sound
{
	class NullSound : public ISound
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

		virtual void Play( Sint32 Layer, Bool IsLoop )
		{
		}

		virtual void Stop( Sint32 Layer )
		{
		}

		virtual void Pause( Sint32 Layer )
		{
		}

		virtual void SetVolume( Sint32 Layer, Float fVolume )
		{
		}

		virtual void SetPan( Sint32 Layer, Float fPan )
		{
		}

		virtual Bool IsPlay( Sint32 Layer )
		{
			return false;
		}
	};
}
}
