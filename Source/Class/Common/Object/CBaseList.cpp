

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Object/CBaseList.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseList::CBaseList()
{
	m_pTop	= NULL;
	m_pEnd	= NULL;
	m_Count	= 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseList::~CBaseList()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CBaseList::Init( void )
{
	m_pTop	= NULL;
	m_pEnd	= NULL;
	m_Count	= 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CBaseList::InsertTop( CBaseObject *pObj )
{
	if ( m_pTop != NULL )
	{
		pObj->SetPrev( NULL );
		pObj->SetNext( m_pTop );
		m_pTop = pObj;
		if ( m_pTop->GetNext() != NULL )
		{
			m_pTop->GetNext()->SetPrev( m_pTop );
		}
	}
	else
	{
		m_pTop = pObj;
		m_pEnd = pObj;
		pObj->SetPrev( NULL );
		pObj->SetNext( NULL );
	}
	m_Count++;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CBaseList::InsertEnd( CBaseObject *pObj )
{
	if ( m_pEnd != NULL )
	{
		pObj->SetPrev( m_pEnd );
		pObj->SetNext( NULL );
		m_pEnd->SetNext( pObj );
		m_pEnd = pObj;
	}
	else
	{
		m_pTop = pObj;
		m_pEnd = pObj;
		pObj->SetPrev( NULL );
		pObj->SetNext( NULL );
	}
	m_Count++;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CBaseList::Erase( CBaseObject *pObj )
{
	if ( pObj->GetPrev() == NULL )
	{
		if ( pObj->GetNext() == NULL )
		{
			m_pTop = NULL;
			m_pEnd = NULL;
		}
		else
		{
			m_pTop = pObj->GetNext();
			pObj->GetNext()->SetPrev( NULL );
		}
	}
	else
	{
		if ( pObj->GetNext() == NULL )
		{
			m_pEnd = m_pEnd->GetPrev();
			m_pEnd->SetNext( NULL );
		}
		else
		{
			pObj->GetNext()->SetPrev( pObj->GetPrev() );
			pObj->GetPrev()->SetNext( pObj->GetNext() );
		}
	}
	m_Count--;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseList::GetTop( void )
{
	return m_pTop;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseList::GetEnd( void )
{
	return m_pEnd;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseList::GetByIndex( Sint32 Index )
{
	CBaseObject *pObj = m_pTop;
	while ( pObj != NULL )
	{
		if ( Index == 0 )
		{
			return pObj;
		}
		pObj = pObj->GetNext();
		Index--;
	}

	return NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CBaseList::GetCount( void )
{
	return m_Count;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseObject *CBaseList::SearchFromName( const char *pName )
{
	CBaseObject *pObj = m_pTop;
	while ( pObj != NULL )
	{
		if ( pObj->IsSame( pName ) )
		{
			return pObj;
		}

		pObj = pObj->GetNext();
	}

	return NULL;
}

