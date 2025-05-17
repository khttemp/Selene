#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CBaseObject.h"
#include "Class/Common/Object/CBaseList.h"
#include "Dynamics/Class/CDynamicsRigidBody.h"
#include "Dynamics/Class/CDynamicsContactPoint.h"
#include "Interface/Dynamics/IDynamicsSimulationWorld.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Dynamics
{
	class CSimulationWorld : public CBaseObject, public ISimulationWorld
	{
	private:
		static void GeometoryCallback( void *pData, dGeomID Obj1, dGeomID Obj2 );

	protected:
		dWorldID						m_World;
		dSpaceID						m_Space;
		dJointGroupID					m_JointGroup;
		CContactPoint					*m_pContactPoint;
		CBaseList						m_BodyList;

		Scene::ISceneManager			*m_pRenderScene;
		Scene::IPrimitiveActor			*m_pActorEarth;

	protected:
		CRigidBody *CreateMesh( Float fMass, SRigidVertex *pVtx, Sint32 VertexCount, SRigidIndex *pIdx, Sint32 IndexCount, Bool IsBody );

	public:
		CSimulationWorld( Scene::ISceneManager *pScene );
		virtual ~CSimulationWorld( void );

		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

		virtual void AddBody( CRigidBody *pBody );
		virtual void DelBody( CRigidBody *pBody );

	public:
		virtual void SetContactPointCount( Sint32 Count );
		virtual void SetStepNumIterations( Sint32 Count );

		virtual void CreateEarth( void );
		virtual void SetGravity( Math::Vector3D &vDir );
		virtual void Update( Float fTime, CollisionProc Proc );

		virtual void RenderingRequest( void );

		virtual IRigidBody *CreateSphere( Float fRadius, Float fMass, Bool IsBody );
		virtual IRigidBody *CreateCapsule( Float fRadius, Float fLength, Float fMass, Bool IsBody );
		virtual IRigidBody *CreateBox( Math::Point3DF &Size, Float fMass, Bool IsBody );
		virtual IRigidModel *CreateMap( Renderer::Object::IMapModel *pMap );
		virtual IRigidModel *CreateModel( Renderer::Object::IModel *pModel, Bool IsBody );
	};
}
}

