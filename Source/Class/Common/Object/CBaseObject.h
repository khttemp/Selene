#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/ClassReference.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CBaseObject
	{
	protected:
		CBaseObject		*m_pPrev;
		CBaseObject		*m_pNext;
		CBaseObject		*m_pParent;
		CBaseObject		*m_pChild;
		CBaseObject		*m_pSibling;

		Sint32			m_RefCount;
		Sint32			m_ChildCount;

		char			m_Name[MAX_PATH];

	public:
		CBaseObject();
		virtual ~CBaseObject();

		Sint32 AddRef( void );
		Sint32 Release( void );

		Sint32 GetRefCount( void );
		Sint32 GetChildCount( void );

		CBaseObject *GetPrev( void );
		CBaseObject *GetNext( void );
		CBaseObject *GetChild( void );
		CBaseObject *GetParent( void );
		CBaseObject *GetSibling( void );

		void SetPrev( CBaseObject *pObj );
		void SetNext( CBaseObject *pObj );
		void SetChild( CBaseObject *pObj );
		void SetParent( CBaseObject *pObj );
		void SetSibling( CBaseObject *pObj );

		void AddChild( CBaseObject *pChild );

		void SetName( const char *pName );
		void GetName( char *pName, Sint32 NameSize );
		const char *GetNamePointer( void ) const;

		Bool IsSame( const char *pName );
	};
}

