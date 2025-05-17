#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Math.h"
#include "Math/Vector3D.h"
#include "Collision/Plane.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Dynamics
{
	typedef void (*CollisionProc)( ISimulationWorld *pWorld, IRigidBody *pIn1, IRigidBody *pIn2, IContactPoint *pContact );

	/**
		@brief �_�C�i�~�N�X�Ǘ��C���^�[�t�F�C�X
		@author �t���`

		�_�C�i�~�N�X���������郏�[���h���Ǘ�����C���^�[�t�F�C�X�ł��B
	*/
	class ISimulationWorld : public IInterface
	{
	public:
		virtual ~ISimulationWorld() {}

		virtual void SetContactPointCount( Sint32 Count ) = 0;
		virtual void SetStepNumIterations( Sint32 Count ) = 0;

		virtual void CreateEarth( void ) = 0;
		virtual void SetGravity( Math::Vector3D &vDir ) = 0;
		virtual void Update( Float fTime, CollisionProc Proc ) = 0;

		virtual void RenderingRequest( void ) = 0;

		virtual IRigidBody *CreateSphere( Float fRadius, Float fMass, Bool IsBody ) = 0;
		virtual IRigidBody *CreateCapsule( Float fRadius, Float fLength, Float fMass, Bool IsBody ) = 0;
		virtual IRigidBody *CreateBox( Math::Point3DF &Size, Float fMass, Bool IsBody ) = 0;
		virtual IRigidModel *CreateMap( Renderer::Object::IMapModel *pMap ) = 0;
		virtual IRigidModel *CreateModel( Renderer::Object::IModel *pModel, Bool IsBody ) = 0;
	};
}
}

