#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CBaseObject.h"
#include "Class/ClassReference.h"
#include "Interface/Dynamics/IDynamicsRigidBody.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Dynamics
{
	struct SRigidVertex
	{
		Float Position[4];
	};

	struct SRigidIndex
	{
		Sint32 Index[3];
	};

	class CRigidBody : public CBaseObject, public IRigidBody
	{
	protected:
		CSimulationWorld		*m_pParentWorld;
		dWorldID				m_World;
		dBodyID					m_BodyId;
		dGeomID					m_GeomId;
		dTriMeshDataID			m_DataId;
		Math::Matrix			m_Matrix;
		Scene::IPrimitiveActor	*m_pActor;
		Bool					m_IsMap;
		void					*m_pUserData;

		SRigidVertex			*m_pVertex;
		SRigidIndex				*m_pIndex;

		eBodyType				m_Type;

	public:
		CRigidBody( CSimulationWorld *pWorld, dWorldID World, dBodyID Body, dGeomID Geom, dTriMeshDataID Data, Scene::IPrimitiveActor *pActor );
		virtual ~CRigidBody( void );

		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

		virtual void SetGeometry( SRigidVertex *pVtx, SRigidIndex *pIdx );

		virtual void SetType( eBodyType Type ) { m_Type = Type; }
		virtual eBodyType GetType( void ) { return m_Type; }

	public:
		virtual void SetUserData( void *pUser );
		virtual void *GetUserData( void );

		virtual void SetPosition( Math::Vector3D &vPos );
		virtual void SetRotation( Math::Matrix &mRot );
		virtual void SetLinearSpeed( Math::Vector3D &vDir );
		virtual void SetAngularSpeed( Math::Vector3D &vDir );

		virtual Math::Matrix &GetMatrix( void );
		virtual void GetPosition( Math::Vector3D &vPos );

		virtual void SetFixed( void );

		virtual void RenderingRequest( void );
	};
}
}

