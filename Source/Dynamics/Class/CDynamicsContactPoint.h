#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Dynamics/IDynamicsContactPoint.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Dynamics
{
	class CContactPoint : public IContactPoint
	{
	protected:
		Sint32		m_Count;
		Sint32		m_MaxCount;
		dContact	*m_pContactPoint;

	public:
		CContactPoint( Sint32 Max );
		virtual ~CContactPoint( void );

		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return 1; }
		virtual Sint32 AddRef( void )  { return 1; }

	public:
		dContact *GetContactPointTbl( void );

		Sint32 GetMaxCount( void );
		void SetCount( Sint32 Count );

	public:
		virtual Sint32 GetCount( void );
		virtual void SetSurfaceParameter( Sint32 Index, SSurfaceParameter &Param );
	};
}
}

