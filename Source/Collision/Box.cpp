

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Collision/Box.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Collision;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBox::CBox( void )
{
}
		
//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CBox::UpdateBox( void )
{
	// �{�b�N�X���\�����镽�ʃf�[�^
	Planes[0].FromPoint( Points[0], Points[3], Points[1] );		// ��
	Planes[1].FromPoint( Points[4], Points[5], Points[7] );		// �E
	Planes[2].FromPoint( Points[1], Points[2], Points[5] );		// ��
	Planes[3].FromPoint( Points[0], Points[4], Points[3] );		// ��
	Planes[4].FromPoint( Points[1], Points[5], Points[0] );		// �O
	Planes[5].FromPoint( Points[2], Points[3], Points[6] );		// ��

	// AABB�̍\�z
	vMin = Points[0];
	vMax = Points[0];
	for ( Sint32 i = 1; i < 8; i++ )
	{
		if ( vMin.x > Points[i].x ) vMin.x = Points[i].x;
		if ( vMin.y > Points[i].y ) vMin.y = Points[i].y;
		if ( vMin.z > Points[i].z ) vMin.z = Points[i].z;
		if ( vMax.x < Points[i].x ) vMax.x = Points[i].x;
		if ( vMax.y < Points[i].y ) vMax.y = Points[i].y;
		if ( vMax.z < Points[i].z ) vMax.z = Points[i].z;
	}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CBox::SetPoints( const Math::Vector3D vPoints[] )
{
	for ( Sint32 i = 0; i < 8; i++ )
	{
		Points[i] = vPoints[i];
	}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CBox::UpdatePoints( const Math::Vector3D &vCenter, const Math::Vector3D vAxis[], const Float fLength[] )
{
	Math::Vector3D Axis[3] = {
		vAxis[0] * fLength[0] * 0.5f,
		vAxis[1] * fLength[1] * 0.5f,
		vAxis[2] * fLength[2] * 0.5f,
	};

	// �{�b�N�X���\�����钸�_�f�[�^
	Points[0] = vCenter - Axis[0] - Axis[1] - Axis[2];
	Points[1] = vCenter - Axis[0] + Axis[1] - Axis[2];
	Points[2] = vCenter - Axis[0] + Axis[1] + Axis[2];
	Points[3] = vCenter - Axis[0] - Axis[1] + Axis[2];
	Points[4] = vCenter + Axis[0] - Axis[1] - Axis[2];
	Points[5] = vCenter + Axis[0] + Axis[1] - Axis[2];
	Points[6] = vCenter + Axis[0] + Axis[1] + Axis[2];
	Points[7] = vCenter + Axis[0] - Axis[1] + Axis[2];

	// �{�b�N�X�f�[�^�X�V
	UpdateBox();
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CBox::Transform( const Math::Matrix &Matrix )
{
	// �{�b�N�X���\�����钸�_�f�[�^
	for ( Sint32 i = 0; i < 8; i++ )
	{
		Points[i].TransformCoord( Matrix );
	}

	// �{�b�N�X�f�[�^�X�V
	UpdateBox();
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CBox::Transform( const Math::Vector3D vPoints[], const Math::Matrix &Matrix )
{
	// �{�b�N�X���\�����钸�_�f�[�^
	for ( Sint32 i = 0; i < 8; i++ )
	{
		Points[i].TransformCoord( vPoints[i], Matrix );
	}

	// �{�b�N�X�f�[�^�X�V
	UpdateBox();
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CBox::TransformProjection( const Math::Matrix &Matrix )
{
	// �{�b�N�X���\�����钸�_�f�[�^
	for ( Sint32 i = 0; i < 8; i++ )
	{
		Points[i].TransformProjection( Matrix );
	}

	// �{�b�N�X�f�[�^�X�V
	UpdateBox();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CBox::TransformProjection( const Math::Vector3D vPoints[], const Math::Matrix &Matrix )
{
	// �{�b�N�X���\�����钸�_�f�[�^
	for ( Sint32 i = 0; i < 8; i++ )
	{
		Points[i].TransformProjection( vPoints[i], Matrix );
	}

	// �{�b�N�X�f�[�^�X�V
	UpdateBox();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CBox::CreateBox( const Math::Vector3D &MinPt, const Math::Vector3D &MaxPt, const Math::Matrix &Matrix )
{
	Math::Vector3D LocalBB[] = {
		Math::Vector3D( MinPt.x, MinPt.y, MinPt.z ), // xyz
		Math::Vector3D( MinPt.x, MaxPt.y, MinPt.z ), // xYz
		Math::Vector3D( MinPt.x, MaxPt.y, MaxPt.z ), // xYZ
		Math::Vector3D( MinPt.x, MinPt.y, MaxPt.z ), // xyZ
		Math::Vector3D( MaxPt.x, MinPt.y, MinPt.z ), // Xyz
		Math::Vector3D( MaxPt.x, MaxPt.y, MinPt.z ), // XYz
		Math::Vector3D( MaxPt.x, MaxPt.y, MaxPt.z ), // XYZ
		Math::Vector3D( MaxPt.x, MinPt.y, MaxPt.z ), // XyZ
	};

	Transform( LocalBB, Matrix );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CBox::CreateBoxProjection( const Math::Vector3D &MinPt, const Math::Vector3D &MaxPt, const Math::Matrix &Matrix )
{
	Math::Vector3D LocalBB[] = {
		Math::Vector3D( MinPt.x, MinPt.y, MinPt.z ), // xyz
		Math::Vector3D( MinPt.x, MaxPt.y, MinPt.z ), // xYz
		Math::Vector3D( MinPt.x, MaxPt.y, MaxPt.z ), // xYZ
		Math::Vector3D( MinPt.x, MinPt.y, MaxPt.z ), // xyZ
		Math::Vector3D( MaxPt.x, MinPt.y, MinPt.z ), // Xyz
		Math::Vector3D( MaxPt.x, MaxPt.y, MinPt.z ), // XYz
		Math::Vector3D( MaxPt.x, MaxPt.y, MaxPt.z ), // XYZ
		Math::Vector3D( MaxPt.x, MinPt.y, MaxPt.z ), // XyZ
	};

	TransformProjection( LocalBB, Matrix );
}
