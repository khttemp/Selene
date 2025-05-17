

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CSceneCamera.h"
#include "Class/Common/Render/3D/CLinePrimitive3D.h"
#include "Collision/Collision.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCamera::CCamera()
	: m_fNearClip ( 0.0f )
	, m_fFarClip  ( 0.0f )
	, m_FovAngle  ( 0 )
{
	m_mCamera.Identity();
	m_mProjection.Identity();
	m_mView.Identity();
	m_mCameraInverse.Identity();
	m_mProjectionInverse.Identity();
	m_mViewInverse.Identity();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCamera::~CCamera()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CCamera::ViewToScreen( void )
{
	return m_mProjection;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CCamera::WorldToScreen( void )
{
	return m_mCamera;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CCamera::WorldToView( void )
{
	return m_mView;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CCamera::ScreenToWorld( void )
{
	return m_mCameraInverse;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CCamera::ViewToWorld( void )
{
	return m_mViewInverse;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Vector3D &CCamera::Position( void )
{
	return m_vPosition;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CCamera::GetNearClip( void )
{
	return m_fNearClip;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CCamera::GetFarClip( void )
{
	return m_fFarClip;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCamera::UpdateProjection( Float fNearClip, Float fFarClip, Sint32 FovAngle, Sint32 Width, Sint32 Height )
{
	m_fNearClip = fNearClip;
	m_fFarClip  = fFarClip;
	m_FovAngle  = FovAngle;

	// •½s“Š‰e
	if ( FovAngle == 0 )
	{
		m_mProjection.Ortho( toF(Width), toF(Height), fNearClip, fFarClip );
	}
	// “§Ž‹“Š‰e
	else
	{
		m_mProjection.Perspective( FovAngle, fNearClip, fFarClip, toF(Width) / toF(Height) );
	}

	// ‹ts—ñ
	m_mProjectionInverse.Inverse( m_mProjection );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCamera::Reset( void )
{
	// Matrix
	m_mCamera.Identity();
	m_mCameraInverse.Identity();
	m_mView.Identity();
	m_mViewInverse.Identity();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCamera::Update( void )
{
	// Matrix
	m_mCamera.Multiply( m_mView, m_mProjection );
	m_mCameraInverse.Multiply( m_mProjectionInverse, m_mViewInverse );

	// Update Bounding
	Math::Vector3D vMin( -1.0f, -1.0f,  0.0f );
	Math::Vector3D vMax( +1.0f, +1.0f, +1.0f );
	m_BoxOBB.CreateBoxProjection( vMin, vMax, m_mCameraInverse );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCamera::SetTransformSimple( Math::Vector3D &vPosition, Math::Vector3D &vTarget, Sint32 Bank )
{
	Math::Style Style;
	Math::Vector3D vUp( 0.0f, 1.0f, 0.0f );

	Style.TransformReset();
	Style.LookAt( vPosition, vTarget, vUp );
	Style.LocalRotationZ( Bank );

	SetTransform( Style );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCamera::SetTransform( Math::Style &Style )
{
	Style.GetTransformInverse( m_mView );
	Style.GetTransform( m_mViewInverse );

	Style.GetPosition( m_vPosition );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCamera::ViewfrustumCulling( const Collision::CBox &Box )
{
	return Collision::Box_Box_3D( m_BoxOBB, Box );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCamera::RenderingBounding( Renderer::Object::ILine3D *pLine )
{
	Collision::CBox Dummy;
	Math::Vector3D vMin( -1.0f, -1.0f,  0.0f );
	Math::Vector3D vMax( +1.0f, +1.0f, +1.0f );
	Dummy.CreateBoxProjection( vMin, vMax, Math::Matrix::GetScaling( 0.97f, 0.97f, 0.97f ) * m_mCameraInverse );

	pLine->PushBox( Dummy, CColor(64,64,255) );
}
