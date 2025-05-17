

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Math/Math.h"
#include "Math/Style.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Math;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Style::Style()
{
	TransformReset();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Style::Style( const Style &Style )
{
	*this = Style;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::TransformReset( void )
{
	// 上
	m_vUp.Set( 0.0f, 1.0f, 0.0f );
	// 右
	m_vRight.Set( 1.0f, 0.0f, 0.0f );
	// 前
	m_vFront.Set( 0.0f, 0.0f, 1.0f );
	// 位置
	m_vPosition.Set( 0.0f, 0.0f, 0.0f );
	m_vLocalPosition.Set( 0.0f, 0.0f, 0.0f );
	// 拡大縮小
	m_vScale.Set( 1.0f, 1.0f, 1.0f );

	m_IsScale = false;
	m_IsLocal = false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::FromMatrix( const Matrix &Mat )
{
	Matrix mTemp = Mat;
	Matrix mScale;

	// 位置
	m_vPosition.x = mTemp.w.x;
	m_vPosition.y = mTemp.w.y;
	m_vPosition.z = mTemp.w.z;
	mTemp.w = Vector4D( 0.0f, 0.0f, 0.0f, 1.0f );

	// 拡大縮小
	Vector3D vScaleX( 1.0f, 0.0f, 0.0f );
	Vector3D vScaleY( 0.0f, 1.0f, 0.0f );
	Vector3D vScaleZ( 0.0f, 0.0f, 1.0f );
	vScaleX.TransformNormal( mTemp );
	vScaleY.TransformNormal( mTemp );
	vScaleZ.TransformNormal( mTemp );
	m_vScale.Set( vScaleX.Length(), vScaleY.Length(), vScaleZ.Length() );

	mScale.Scaling( 1.0f / m_vScale.x, 1.0f / m_vScale.y, 1.0f / m_vScale.z );
	mTemp = mScale * mTemp;

	// 回転
	m_vRight	= Vector3D( mTemp.x.x, mTemp.x.y, mTemp.x.z );
	m_vUp		= Vector3D( mTemp.y.x, mTemp.y.y, mTemp.y.z );
	m_vFront	= Vector3D( mTemp.z.x, mTemp.z.y, mTemp.z.z );
	m_vPosition = Vector3D( Mat.w.x, Mat.w.y, Mat.w.z );
	m_vLocalPosition.Set( 0.0f, 0.0f, 0.0f );

	m_IsScale = true;
	m_IsLocal = false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 Style::GetAngleX( void ) const
{
	return PI_TO_ANGLE( asinf( m_vFront.y ) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 Style::GetAngleY( void ) const
{
	if ( (m_vFront.y == -1.0f) || (m_vFront.y == +1.0f) )
	{
		return PI_TO_ANGLE( atan2f( m_vUp.z, m_vUp.x ) );
	}
	else
	{
		return PI_TO_ANGLE( atan2f( m_vFront.z, m_vFront.x ) );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 Style::GetAngleZ( void ) const
{
	Float fTemp = asinf( m_vRight.y / FastSqrt( 1.0f - m_vFront.y * m_vFront.y ) );

	if ( m_vUp.y < 0 )
	{
		return PI_TO_ANGLE( PI - fTemp );
	}
	else
	{
		return PI_TO_ANGLE( fTemp );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::RotationX( Sint32 Rot )
{
	Matrix Mt[2];
	Matrix *pMt[2] = { &Mt[0], &Mt[1] };

	Float fCos = Math::Cos( Rot );
	Float fSin = Math::Sin( Rot );

	pMt[0]->x.x = m_vRight.x;  pMt[0]->x.y = m_vRight.y;  pMt[0]->x.z = m_vRight.z;  pMt[0]->x.w = 0;
	pMt[0]->y.x = m_vUp.x;     pMt[0]->y.y = m_vUp.y;     pMt[0]->y.z = m_vUp.z;     pMt[0]->y.w = 0;
	pMt[0]->z.x = m_vFront.x;  pMt[0]->z.y = m_vFront.y;  pMt[0]->z.z = m_vFront.z;  pMt[0]->z.w = 0;
	pMt[0]->w.x = 0;           pMt[0]->w.y = 0;           pMt[0]->w.z = 0;           pMt[0]->w.w = 1;

	pMt[1]->x.x = 1;  pMt[1]->x.y =     0;  pMt[1]->x.z =    0;  pMt[1]->x.w = 0;
	pMt[1]->y.x = 0;  pMt[1]->y.y =  fCos;  pMt[1]->y.z = fSin;  pMt[1]->y.w = 0;
	pMt[1]->z.x = 0;  pMt[1]->z.y = -fSin;  pMt[1]->z.z = fCos;  pMt[1]->z.w = 0;
	pMt[1]->w.x = 0;  pMt[1]->w.y =     0;  pMt[1]->w.z =    0;  pMt[1]->w.w = 1;

	Mt[0] *= Mt[1];

	m_vRight.x = pMt[0]->x.x;
	m_vRight.y = pMt[0]->x.y;
	m_vRight.z = pMt[0]->x.z;
	m_vUp.x    = pMt[0]->y.x;
	m_vUp.y    = pMt[0]->y.y;
	m_vUp.z    = pMt[0]->y.z;
	m_vFront.x = pMt[0]->z.x;
	m_vFront.y = pMt[0]->z.y;
	m_vFront.z = pMt[0]->z.z;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::RotationY( Sint32 Rot )
{
	Matrix Mt[2];
	Matrix *pMt[2] = { &Mt[0], &Mt[1] };

	Float fCos = Math::Cos( Rot );
	Float fSin = Math::Sin( Rot );

	pMt[0]->x.x = m_vRight.x;  pMt[0]->x.y = m_vRight.y;  pMt[0]->x.z = m_vRight.z;  pMt[0]->x.w = 0;
	pMt[0]->y.x = m_vUp.x;     pMt[0]->y.y = m_vUp.y;     pMt[0]->y.z = m_vUp.z;     pMt[0]->y.w = 0;
	pMt[0]->z.x = m_vFront.x;  pMt[0]->z.y = m_vFront.y;  pMt[0]->z.z = m_vFront.z;  pMt[0]->z.w = 0;
	pMt[0]->w.x = 0;           pMt[0]->w.y = 0;           pMt[0]->w.z = 0;           pMt[0]->w.w = 1;

	pMt[1]->x.x = fCos;  pMt[1]->x.y = 0;  pMt[1]->x.z = -fSin;  pMt[1]->x.w = 0;
	pMt[1]->y.x =    0;  pMt[1]->y.y = 1;  pMt[1]->y.z =     0;  pMt[1]->y.w = 0;
	pMt[1]->z.x = fSin;  pMt[1]->z.y = 0;  pMt[1]->z.z =  fCos;  pMt[1]->z.w = 0;
	pMt[1]->w.x =    0;  pMt[1]->w.y = 0;  pMt[1]->w.z =     0;  pMt[1]->w.w = 1;

	Mt[0] *= Mt[1];

	m_vRight.x = pMt[0]->x.x;
	m_vRight.y = pMt[0]->x.y;
	m_vRight.z = pMt[0]->x.z;
	m_vUp.x    = pMt[0]->y.x;
	m_vUp.y    = pMt[0]->y.y;
	m_vUp.z    = pMt[0]->y.z;
	m_vFront.x = pMt[0]->z.x;
	m_vFront.y = pMt[0]->z.y;
	m_vFront.z = pMt[0]->z.z;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::RotationZ( Sint32 Rot )
{
	Matrix Mt[2];
	Matrix *pMt[2] = { &Mt[0], &Mt[1] };

	Float fCos = Math::Cos( Rot );
	Float fSin = Math::Sin( Rot );

	pMt[0]->x.x = m_vRight.x;  pMt[0]->x.y = m_vRight.y;  pMt[0]->x.z = m_vRight.z;  pMt[0]->x.w = 0;
	pMt[0]->y.x = m_vUp.x;     pMt[0]->y.y = m_vUp.y;     pMt[0]->y.z = m_vUp.z;     pMt[0]->y.w = 0;
	pMt[0]->z.x = m_vFront.x;  pMt[0]->z.y = m_vFront.y;  pMt[0]->z.z = m_vFront.z;  pMt[0]->z.w = 0;
	pMt[0]->w.x = 0;           pMt[0]->w.y = 0;           pMt[0]->w.z = 0;           pMt[0]->w.w = 1;

	pMt[1]->x.x =  fCos;  pMt[1]->x.y = fSin;  pMt[1]->x.z = 0;  pMt[1]->x.w = 0;
	pMt[1]->y.x = -fSin;  pMt[1]->y.y = fCos;  pMt[1]->y.z = 0;  pMt[1]->y.w = 0;
	pMt[1]->z.x =     0;  pMt[1]->z.y =    0;  pMt[1]->z.z = 1;  pMt[1]->z.w = 0;
	pMt[1]->w.x =     0;  pMt[1]->w.y =    0;  pMt[1]->w.z = 0;  pMt[1]->w.w = 1;

	Mt[0] *= Mt[1];

	m_vRight.x = pMt[0]->x.x;
	m_vRight.y = pMt[0]->x.y;
	m_vRight.z = pMt[0]->x.z;
	m_vUp.x    = pMt[0]->y.x;
	m_vUp.y    = pMt[0]->y.y;
	m_vUp.z    = pMt[0]->y.z;
	m_vFront.x = pMt[0]->z.x;
	m_vFront.y = pMt[0]->z.y;
	m_vFront.z = pMt[0]->z.z;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::LocalRotationX( Sint32 Rot )
{
	Vector3D vTemp[3];
	vTemp[0] = m_vRight;
	vTemp[1] = m_vUp;
	vTemp[2] = m_vFront;

	Float fCos = Math::Cos( Rot );
	Float fSin = Math::Sin( Rot );

	m_vUp.x		= (+fCos * vTemp[1].x) + (+fSin * vTemp[2].x);
	m_vUp.y		= (+fCos * vTemp[1].y) + (+fSin * vTemp[2].y);
	m_vUp.z		= (+fCos * vTemp[1].z) + (+fSin * vTemp[2].z);

	m_vFront.x	= (-fSin * vTemp[1].x) + (+fCos * vTemp[2].x);
	m_vFront.y	= (-fSin * vTemp[1].y) + (+fCos * vTemp[2].y);
	m_vFront.z	= (-fSin * vTemp[1].z) + (+fCos * vTemp[2].z);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::LocalRotationY( Sint32 Rot )
{
	Vector3D vTemp[3];
	vTemp[0] = m_vRight;
	vTemp[1] = m_vUp;
	vTemp[2] = m_vFront;

	Float fCos = Math::Cos( Rot );
	Float fSin = Math::Sin( Rot );

	m_vRight.x	= (+fCos * vTemp[0].x) + (-fSin * vTemp[2].x);
	m_vRight.y	= (+fCos * vTemp[0].y) + (-fSin * vTemp[2].y);
	m_vRight.z	= (+fCos * vTemp[0].z) + (-fSin * vTemp[2].z);

	m_vFront.x	= (+fSin * vTemp[0].x) + (+fCos * vTemp[2].x);
	m_vFront.y	= (+fSin * vTemp[0].y) + (+fCos * vTemp[2].y);
	m_vFront.z	= (+fSin * vTemp[0].z) + (+fCos * vTemp[2].z);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::LocalRotationZ( Sint32 Rot )
{
	Vector3D vTemp[3];
	vTemp[0] = m_vRight;
	vTemp[1] = m_vUp;
	vTemp[2] = m_vFront;

	Float fCos = Math::Cos( Rot );
	Float fSin = Math::Sin( Rot );

	m_vRight.x	= (+fCos * vTemp[0].x) + (+fSin * vTemp[1].x);
	m_vRight.y	= (+fCos * vTemp[0].y) + (+fSin * vTemp[1].y);
	m_vRight.z	= (+fCos * vTemp[0].z) + (+fSin * vTemp[1].z);

	m_vUp.x		= (-fSin * vTemp[0].x) + (+fCos * vTemp[1].x);
	m_vUp.y		= (-fSin * vTemp[0].y) + (+fCos * vTemp[1].y);
	m_vUp.z		= (-fSin * vTemp[0].z) + (+fCos * vTemp[1].z);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::RotationQuaternion( const Quaternion &Quat )
{
	Matrix Mat = Quat;

	m_vRight.x	= Mat.x.x;
	m_vRight.y	= Mat.x.y;
	m_vRight.z	= Mat.x.z;

	m_vUp.x		= Mat.y.x;
	m_vUp.y		= Mat.y.y;
	m_vUp.z		= Mat.y.z;

	m_vFront.x	= Mat.z.x;
	m_vFront.y	= Mat.z.y;
	m_vFront.z	= Mat.z.z;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::Translation( Float fPx, Float fPy, Float fPz )
{
	m_vPosition.Set( fPx, fPy, fPz );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::Translation( const Vector3D &vPos )
{
	m_vPosition = vPos;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::LocalTranslation( Float fPx, Float fPy, Float fPz )
{
	m_vLocalPosition.Set( fPx, fPy, fPz );
	m_IsLocal = true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::LocalTranslation( const Vector3D &vPos )
{
	m_vLocalPosition = vPos;
	m_IsLocal = true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::Scaling( Float fSx, Float fSy, Float fSz )
{
	m_vScale.Set( fSx, fSy, fSz );
	m_IsScale = true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::LookAt( const Vector3D &vEye, const Vector3D &vAt, const Vector3D &vUp )
{
	Vector3D vFrontDir, vRightDir, vUpDir;
	vUpDir = vUp;

	//--------------------------------------------------------
	// カメラ視線
	//--------------------------------------------------------
	vFrontDir.Sub( vAt, vEye );
	vFrontDir.NormalizeFast();

	//--------------------------------------------------------
	// 前方向が完全に真上か真下の時
	//--------------------------------------------------------
	if ( (-0.0001f < vFrontDir.x) && (vFrontDir.x < +0.0001f) )
	{
		if ( (-0.0001f < vFrontDir.z) && (vFrontDir.z < +0.0001f) )
		{
			// ＵＰベクトルを変えておく
			vUpDir.Set( 0, 0, -vFrontDir.y );
		}
	}

	//--------------------------------------------------------
	// カメラ右方向
	//--------------------------------------------------------
	vRightDir.Cross( vFrontDir, vUpDir );
	vRightDir.NormalizeFast();
	vRightDir.x = -vRightDir.x;
	vRightDir.y = -vRightDir.y;
	vRightDir.z = -vRightDir.z;

	//--------------------------------------------------------
	// 上方向
	//--------------------------------------------------------
	vUpDir.Cross( vFrontDir, vRightDir );
	vUpDir.NormalizeFast();

	//--------------------------------------------------------
	// コピー
	//--------------------------------------------------------
	m_vFront	= vFrontDir;
	m_vUp		= vUpDir;
	m_vRight	= vRightDir;
	m_vPosition	= vEye;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::SetPosition( const Vector3D &Pos )
{
	m_vPosition = Pos;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::SetFront( const Vector3D &Vec )
{
	m_vFront = Vec;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::SetRight( const Vector3D &Vec )
{
	m_vRight = Vec;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::SetUp( const Vector3D &Vec )
{
	m_vUp = Vec;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::GetPosition( Vector3D &vPos ) const
{
	vPos = m_vPosition;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::GetFront( Vector3D &Vec ) const
{
	Vec = m_vFront;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::GetRight( Vector3D &Vec ) const
{
	Vec = m_vRight;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::GetUp( Vector3D &Vec ) const
{
	Vec = m_vUp;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::GetStyle( Matrix &Mat ) const
{
	Mat.x.x = m_vRight.x; Mat.x.y = m_vRight.y; Mat.x.z = m_vRight.z; Mat.x.w = 0.0f;
	Mat.y.x = m_vUp.x;    Mat.y.y = m_vUp.y;    Mat.y.z = m_vUp.z;    Mat.y.w = 0.0f;
	Mat.z.x = m_vFront.x; Mat.z.y = m_vFront.y; Mat.z.z = m_vFront.z; Mat.z.w = 0.0f;
	Mat.w.x = 0.0f;       Mat.w.y = 0.0f;       Mat.w.z = 0.0f;       Mat.w.w = 1.0f;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::GetStyleInverse( Matrix &Mat ) const
{
	Mat.x.x = m_vRight.x; Mat.x.y = m_vUp.x; Mat.x.z = m_vFront.x; Mat.x.w = 0.0f;
	Mat.y.x = m_vRight.y; Mat.y.y = m_vUp.y; Mat.y.z = m_vFront.y; Mat.y.w = 0.0f;
	Mat.z.x = m_vRight.z; Mat.z.y = m_vUp.z; Mat.z.z = m_vFront.z; Mat.z.w = 0.0f;
	Mat.w.x = 0.0f;       Mat.w.y = 0.0f;    Mat.w.z = 0.0f;       Mat.w.w = 1.0f;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::GetTransform( Matrix &Mat ) const
{
	Mat.x.x = m_vRight.x; Mat.x.y = m_vRight.y; Mat.x.z = m_vRight.z; Mat.x.w = 0.0f;
	Mat.y.x = m_vUp.x;    Mat.y.y = m_vUp.y;    Mat.y.z = m_vUp.z;    Mat.y.w = 0.0f;
	Mat.z.x = m_vFront.x; Mat.z.y = m_vFront.y; Mat.z.z = m_vFront.z; Mat.z.w = 0.0f;

	Mat.w.x = m_vPosition.x;
	Mat.w.y = m_vPosition.y;
	Mat.w.z = m_vPosition.z;
	Mat.w.w = 1.0f;

	if ( m_IsLocal )
	{
		Mat = Math::Matrix::GetTranslation( m_vLocalPosition.x, m_vLocalPosition.y, m_vLocalPosition.z ) * Mat;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::GetTransformInverse( Matrix &Mat ) const
{
	Mat.x.x = m_vRight.x; Mat.x.y = m_vUp.x; Mat.x.z = m_vFront.x; Mat.x.w = 0.0f;
	Mat.y.x = m_vRight.y; Mat.y.y = m_vUp.y; Mat.y.z = m_vFront.y; Mat.y.w = 0.0f;
	Mat.z.x = m_vRight.z; Mat.z.y = m_vUp.z; Mat.z.z = m_vFront.z; Mat.z.w = 0.0f;

	Mat.w.x = -m_vPosition.Dot( m_vRight );
	Mat.w.y = -m_vPosition.Dot( m_vUp );
	Mat.w.z = -m_vPosition.Dot( m_vFront );
	Mat.w.w = 1.0f;

	if ( m_IsLocal )
	{
		Mat = Mat * Math::Matrix::GetTranslation( -m_vLocalPosition.x, -m_vLocalPosition.y, -m_vLocalPosition.z );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::GetTransformWithScale( Matrix &Mat ) const
{
	Matrix mTemp;

	if ( m_IsScale )
	{
		mTemp.x.x = m_vRight.x;	mTemp.x.y = m_vRight.y;	mTemp.x.z = m_vRight.z;	mTemp.x.w = 0.0f;
		mTemp.y.x = m_vUp.x;	mTemp.y.y = m_vUp.y;	mTemp.y.z = m_vUp.z;	mTemp.y.w = 0.0f;
		mTemp.z.x = m_vFront.x;	mTemp.z.y = m_vFront.y;	mTemp.z.z = m_vFront.z;	mTemp.z.w = 0.0f;
		mTemp.w.x = 0.0f;		mTemp.w.y = 0.0f;		mTemp.w.z = 0.0f;		mTemp.w.w = 1.0f;

		Mat.Scaling( m_vScale.x, m_vScale.y, m_vScale.z );
		Mat *= mTemp;
	}
	else
	{
		Mat.x.x = m_vRight.x;	Mat.x.y = m_vRight.y;	Mat.x.z = m_vRight.z;	Mat.x.w = 0.0f;
		Mat.y.x = m_vUp.x;		Mat.y.y = m_vUp.y;		Mat.y.z = m_vUp.z;		Mat.y.w = 0.0f;
		Mat.z.x = m_vFront.x;	Mat.z.y = m_vFront.y;	Mat.z.z = m_vFront.z;	Mat.z.w = 0.0f;
	}

	Mat.w = m_vPosition;

	if ( m_IsLocal )
	{
		mTemp.Translation( m_vLocalPosition.x, m_vLocalPosition.y, m_vLocalPosition.z );
		Mat = mTemp * Mat;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Style::GetTransformInverseWithScale( Matrix &Mat ) const
{
	Matrix mTemp;

	if ( m_IsScale )
	{
		mTemp.x.x = m_vRight.x;	mTemp.x.y = m_vUp.x;	mTemp.x.z = m_vFront.x;	mTemp.x.w = 0.0f;
		mTemp.y.x = m_vRight.y;	mTemp.y.y = m_vUp.y;	mTemp.y.z = m_vFront.y;	mTemp.y.w = 0.0f;
		mTemp.z.x = m_vRight.z;	mTemp.z.y = m_vUp.z;	mTemp.z.z = m_vFront.z;	mTemp.z.w = 0.0f;

		Mat.Scaling( 1.0f/m_vScale.x, 1.0f/m_vScale.y, 1.0f/m_vScale.z );
		Mat *= mTemp;
	}
	else
	{
		Mat.x.x = m_vRight.x;	Mat.x.y = m_vUp.x;	Mat.x.z = m_vFront.x;	Mat.x.w = 0.0f;
		Mat.y.x = m_vRight.y;	Mat.y.y = m_vUp.y;	Mat.y.z = m_vFront.y;	Mat.y.w = 0.0f;
		Mat.z.x = m_vRight.z;	Mat.z.y = m_vUp.z;	Mat.z.z = m_vFront.z;	Mat.z.w = 0.0f;
	}

	Mat.w.x = -m_vPosition.Dot( m_vRight );
	Mat.w.y = -m_vPosition.Dot( m_vUp );
	Mat.w.z = -m_vPosition.Dot( m_vFront );
	Mat.w.w = 1.0f;

	if ( m_IsLocal )
	{
		mTemp.Translation( -m_vLocalPosition.x, -m_vLocalPosition.y, -m_vLocalPosition.z );
		Mat = Mat * mTemp;
	}
}

