#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CBaseObject.h"
#include "Dynamics/Class/CDynamicsRigidBody.h"
#include "Interface/Dynamics/IDynamicsRigidModel.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Dynamics
{
	class CRigidModel : public CBaseObject, public IRigidModel
	{
	protected:
		CRigidBody	**m_pRigidBodyTbl;
		Sint32		m_Count;

	public:
		CRigidModel( Sint32 Count );
		virtual ~CRigidModel( void );

		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual void Set( Sint32 Index, CRigidBody *pBody );
	};
}
}

