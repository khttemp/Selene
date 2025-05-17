#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CBaseList.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CResourceObjectMgr : public CBaseList
	{
	protected:
		char	m_Name[64];

	public:
		CResourceObjectMgr( const char *pName );
		virtual ~CResourceObjectMgr();
	};
}

