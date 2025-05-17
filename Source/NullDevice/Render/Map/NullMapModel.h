#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/Map/IMapModel.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class NullMapModel : public IMapModel
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
	};
}
}
}

