#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Scene/ISceneCamera.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class NullCamera : public ICamera
	{
	public:
		virtual Bool IsInvalid( void )
		{
			return true;
		}

		virtual Sint32 Release( void )
		{
			return 0;
		}

		virtual Sint32 AddRef( void	)
		{
			return 0;
		}

		virtual const Math::Matrix &WorldToScreen( void )
		{
			static Math::Matrix Dummy;
			Dummy.Identity();
			return Dummy;
		}

		virtual const Math::Matrix &WorldToView( void )
		{
			static Math::Matrix Dummy;
			Dummy.Identity();
			return Dummy;
		}

		virtual const Math::Matrix &ScreenToWorld( void )
		{
			static Math::Matrix Dummy;
			Dummy.Identity();
			return Dummy;
		}

		virtual const Math::Matrix &ViewToWorld( void )
		{
			static Math::Matrix Dummy;
			Dummy.Identity();
			return Dummy;
		}

		virtual const Math::Vector3D &Position( void )
		{
			static Math::Vector3D Dummy( 0.0f, 0.0f, 0.0f );
			return Dummy;
		}

		virtual Float GetNearClip( void )
		{
			return 1.0f;
		}

		virtual Float GetFarClip( void )
		{
			return 100.0f;
		}

		virtual void UpdateProjection( Float fNearClip, Float fFarClip, Sint32 FovAngle, Sint32 Width, Sint32 Height )
		{
		}

		virtual void Reset( void )
		{
		}

		virtual void Update( void )
		{
		}

		virtual void SetTransformSimple( Math::Vector3D &vPosition, Math::Vector3D &vTarget, Sint32 Bank )
		{
		}

		virtual void SetTransform( Math::Style &Style )
		{
		}

		virtual void RenderingBounding( Renderer::Object::ILine3D *pLine )
		{
		}
	};
}
}
