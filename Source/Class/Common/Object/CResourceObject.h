#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Math.h"
#include "Class/Common/Object/CBaseObject.h"
#include "Class/Common/Object/CResourceObjectMgr.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CResourceObject : public CBaseObject
	{
	protected:
		CResourceObjectMgr *m_pManager;

	public:
		CResourceObject( CResourceObjectMgr *pMgr );
		virtual ~CResourceObject();
	};
}

