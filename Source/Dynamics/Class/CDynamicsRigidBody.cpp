

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Dynamics/Class/CDynamicsRigidBody.h"
#include "Class/Common/Scene/CScenePrimitiveActor.h"
#include "Dynamics/Class/CDynamicsSimulationWorld.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Dynamics;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRigidBody::CRigidBody( CSimulationWorld *pWorld, dWorldID World, dBodyID Body, dGeomID Geom, dTriMeshDataID Data, Scene::IPrimitiveActor *pActor )
	: m_pParentWorld	( pWorld )
	, m_World			( World )
	, m_BodyId			( Body )
	, m_GeomId			( Geom )
	, m_DataId			( Data )
	, m_pActor			( pActor )
	, m_pUserData		( NULL )
	, m_pVertex			( NULL )
	, m_pIndex			( NULL )
	, m_IsMap			( false )
	, m_Type			( BODY_TYPE_GEOMETRY )
{
	if ( m_BodyId != 0 ) dBodySetData( m_BodyId, this );
	if ( m_GeomId != 0 ) dGeomSetData( m_GeomId, this );

	m_Matrix.Identity();

	m_pParentWorld->AddBody( this );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRigidBody::~CRigidBody( void )
{
	m_pParentWorld->DelBody( this );

	if ( m_BodyId != 0 ) dBodyDestroy( m_BodyId );
	if ( m_GeomId != 0 ) dGeomDestroy( m_GeomId );
	if ( m_DataId != 0 ) dGeomTriMeshDataDestroy( m_DataId );

	SAFE_RELEASE( m_pActor );

	SAFE_DELETE_ARRAY( m_pVertex );
	SAFE_DELETE_ARRAY( m_pIndex );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRigidBody::SetGeometry( SRigidVertex *pVtx, SRigidIndex *pIdx )
{
	m_pVertex = pVtx;
	m_pIndex = pIdx;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRigidBody::SetUserData( void *pUser )
{
	m_pUserData = pUser;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void *CRigidBody::GetUserData( void )
{
	return m_pUserData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRigidBody::SetPosition( Math::Vector3D &vPos )
{
	dGeomSetPosition( m_GeomId, vPos.x, vPos.y, vPos.z );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRigidBody::SetRotation( Math::Matrix &mRot )
{
	dGeomSetRotation( m_GeomId, (Float*)mRot.m );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRigidBody::SetLinearSpeed( Math::Vector3D &vDir )
{
	if ( m_BodyId != 0 )
	{
		dBodySetLinearVel( m_BodyId, vDir.x, vDir.y, vDir.z );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRigidBody::SetAngularSpeed( Math::Vector3D &vDir )
{
	if ( m_BodyId != 0 )
	{
		dBodySetAngularVel( m_BodyId, vDir.x, vDir.y, vDir.z );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Matrix &CRigidBody::GetMatrix( void )
{
	 const dReal *pPos = dGeomGetPosition( m_GeomId );
	 const dReal *pRot = dGeomGetRotation( m_GeomId );

	 m_Matrix = Math::Matrix(
					 pRot[ 0], pRot[ 4], pRot[ 8], 0.0f,
					 pRot[ 1], pRot[ 5], pRot[ 9], 0.0f,
					 pRot[ 2], pRot[ 6], pRot[10], 0.0f,
					 pPos[ 0], pPos[ 1], pPos[ 2], 1.0f );

	 return m_Matrix;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRigidBody::GetPosition( Math::Vector3D &vPos )
{
	 const dReal *pPos = dGeomGetPosition( m_GeomId );
	 vPos.x = pPos[0];
	 vPos.y = pPos[1];
	 vPos.z = pPos[2];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRigidBody::SetFixed( void )
{
	if ( m_BodyId != 0 )
	{
		dJointID FixedJoint = dJointCreateFixed( m_World, 0 );
		dJointAttach( FixedJoint, m_BodyId, 0 );
		dJointSetFixed( FixedJoint );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRigidBody::RenderingRequest( void )
{
	if ( (m_pActor != NULL) && !m_pActor->IsInvalid() )
	{
		m_pActor->TransformReset();
		m_pActor->FromMatrix( GetMatrix() );
		m_pActor->TransformUpdate();

		m_pActor->RenderingRequest();
	}
}
