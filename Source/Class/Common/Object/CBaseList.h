#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Thread/CriticalSection.h"
#include "Class/Common/Object/CBaseObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CBaseList : public CBaseObject
	{
	protected:
		CBaseObject	*m_pTop;
		CBaseObject	*m_pEnd;
		Sint32		m_Count;

	public:
		CBaseList();
		virtual ~CBaseList();

		void Init( void );
		void InsertTop( CBaseObject *pObj );
		void InsertEnd( CBaseObject *pObj );
		void Erase( CBaseObject *pObj );
		CBaseObject *GetTop( void );
		CBaseObject *GetEnd( void );
		CBaseObject *GetByIndex( Sint32 Index );
		Sint32 GetCount( void );
		CBaseObject *SearchFromName( const char *pName );
	};
}

