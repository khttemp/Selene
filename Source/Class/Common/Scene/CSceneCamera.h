#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Math/Style.h"
#include "Collision/Box.h"
#include "Class/Common/Object/CBaseObject.h"
#include "Interface/Scene/ISceneCamera.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class CCamera : public CBaseObject, public ICamera
	{
	protected:
		Math::Matrix m_mCamera;
		Math::Matrix m_mCameraInverse;
		Math::Matrix m_mProjection;
		Math::Matrix m_mProjectionInverse;
		Math::Matrix m_mView;
		Math::Matrix m_mViewInverse;
		Math::Vector3D m_vPosition;

		Float m_fNearClip;
		Float m_fFarClip;
		Sint32 m_FovAngle;

		Collision::CBox m_BoxOBB;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CCamera();
		virtual ~CCamera();

		virtual const Math::Matrix &WorldToScreen( void );
		virtual const Math::Matrix &WorldToView( void );
		virtual const Math::Matrix &ScreenToWorld( void );
		virtual const Math::Matrix &ViewToWorld( void );
		virtual const Math::Matrix &ViewToScreen( void );
		virtual const Math::Vector3D &Position( void );

		virtual Float GetNearClip( void );
		virtual Float GetFarClip( void );

		virtual void UpdateProjection( Float fNearClip, Float fFarClip, Sint32 FovAngle, Sint32 Width, Sint32 Height );

		virtual void Reset( void );
		virtual void Update( void );

		virtual Bool ViewfrustumCulling( const Collision::CBox &Box );

		virtual void SetTransformSimple( Math::Vector3D &vPosition, Math::Vector3D &vTarget, Sint32 Bank );
		virtual void SetTransform( Math::Style &Style );

		virtual void RenderingBounding( Renderer::Object::ILine3D *pLine );
	};
}
}
