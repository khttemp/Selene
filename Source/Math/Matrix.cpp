

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Math/Math.h"
#include "Math/Matrix.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Math;


//-----------------------------------------------------------------------------------
// INLINE
//-----------------------------------------------------------------------------------
inline void Matrix_Multiply( Matrix &mOut, const Matrix &mIn1, const Matrix &mIn2 )
{
	if ( (&mOut == &mIn1) && (&mOut == &mIn2) )
	{
		Matrix mTemp1 = mIn1;
		Matrix mTemp2 = mIn2;
		mOut.x.TransformCoord( mTemp1.x, mTemp2 );
		mOut.y.TransformCoord( mTemp1.y, mTemp2 );
		mOut.z.TransformCoord( mTemp1.z, mTemp2 );
		mOut.w.TransformCoord( mTemp1.w, mTemp2 );
	}
	ef ( &mOut == &mIn1 )
	{
		Matrix mTemp = mIn1;
		mOut.x.TransformCoord( mTemp.x, mIn2 );
		mOut.y.TransformCoord( mTemp.y, mIn2 );
		mOut.z.TransformCoord( mTemp.z, mIn2 );
		mOut.w.TransformCoord( mTemp.w, mIn2 );
	}
	ef ( &mOut == &mIn2 )
	{
		Matrix mTemp = mIn2;
		mOut.x.TransformCoord( mIn1.x, mTemp );
		mOut.y.TransformCoord( mIn1.y, mTemp );
		mOut.z.TransformCoord( mIn1.z, mTemp );
		mOut.w.TransformCoord( mIn1.w, mTemp );
	}
	else
	{
		mOut.x.TransformCoord( mIn1.x, mIn2 );
		mOut.y.TransformCoord( mIn1.y, mIn2 );
		mOut.z.TransformCoord( mIn1.z, mIn2 );
		mOut.w.TransformCoord( mIn1.w, mIn2 );
	}
}

inline void Matrix_Transpose( Matrix &mOut, const Matrix &mIn )
{
	if ( &mOut == &mIn )
	{
		Matrix mTemp = mIn;
		mOut.x.x = mTemp.x.x;	mOut.x.y = mTemp.y.x;	mOut.x.z = mTemp.z.x;	mOut.x.w = mTemp.w.x;
		mOut.y.x = mTemp.x.y;	mOut.y.y = mTemp.y.y;	mOut.y.z = mTemp.z.y;	mOut.y.w = mTemp.w.y;
		mOut.z.x = mTemp.x.z;	mOut.z.y = mTemp.y.z;	mOut.z.z = mTemp.z.z;	mOut.z.w = mTemp.w.z;
		mOut.w.x = mTemp.x.w;	mOut.w.y = mTemp.y.w;	mOut.w.z = mTemp.z.w;	mOut.w.w = mTemp.w.w;
	}
	else
	{
		mOut.x.x = mIn.x.x;		mOut.x.y = mIn.y.x;		mOut.x.z = mIn.z.x;		mOut.x.w = mIn.w.x;
		mOut.y.x = mIn.x.y;		mOut.y.y = mIn.y.y;		mOut.y.z = mIn.z.y;		mOut.y.w = mIn.w.y;
		mOut.z.x = mIn.x.z;		mOut.z.y = mIn.y.z;		mOut.z.z = mIn.z.z;		mOut.z.w = mIn.w.z;
		mOut.w.x = mIn.x.w;		mOut.w.y = mIn.y.w;		mOut.w.z = mIn.z.w;		mOut.w.w = mIn.w.w;
	}
}

inline void Matrix_Inverse( Matrix &mOut, const Matrix &mIn )
{
	D3DXMatrixInverse( (D3DXMATRIX*)&mOut, NULL, (const D3DXMATRIX*)&mIn );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix::Matrix()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix::Matrix( const Matrix &Mat )
{
	this->x = Mat.x;
	this->y = Mat.y;
	this->z = Mat.z;
	this->w = Mat.w;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix::Matrix( const SMatrix4x4 &Mat )
{
	this->x = Mat.x;
	this->y = Mat.y;
	this->z = Mat.z;
	this->w = Mat.w;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix::Matrix( const Quaternion &In )
{
	Float xx = In.x * In.x;
	Float yy = In.y * In.y;
	Float zz = In.z * In.z;
	Float xy = In.x * In.y;
	Float xz = In.x * In.z;
	Float yz = In.y * In.z;
	Float wx = In.w * In.x;
	Float wy = In.w * In.y;
	Float wz = In.w * In.z;

	x.x = 1.0f - 2.0f * (yy + zz);
	x.y =        2.0f * (xy - wz);
	x.z =        2.0f * (xz + wy);
	x.w = 0.0f;

	y.x =        2.0f * (xy + wz);
	y.y = 1.0f - 2.0f * (xx + zz);
	y.z =        2.0f * (yz - wx);
	y.w = 0.0f;

	z.x =        2.0f * (xz - wy);
	z.y =        2.0f * (yz + wx);
	z.z = 1.0f - 2.0f * (xx + yy);
	z.w = 0.0f;

	w.x = 0.0f;
	w.y = 0.0f;
	w.z = 0.0f;
	w.w = 1.0f;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix::Matrix(
		Float _11, Float _12, Float _13, Float _14,
		Float _21, Float _22, Float _23, Float _24,
		Float _31, Float _32, Float _33, Float _34,
		Float _41, Float _42, Float _43, Float _44 )
{
	x.x = _11;  x.y = _12;  x.z = _13;  x.w = _14;
	y.x = _21;  y.y = _22;  y.z = _23;  y.w = _24;
	z.x = _31;  z.y = _32;  z.z = _33;  z.w = _34;
	w.x = _41;  w.y = _42;  w.z = _43;  w.w = _44;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Matrix::Identity( void )
{
	x.x = 1.0f;  x.y = 0.0f;  x.z = 0.0f;  x.w = 0.0f;
	y.x = 0.0f;  y.y = 1.0f;  y.z = 0.0f;  y.w = 0.0f;
	z.x = 0.0f;  z.y = 0.0f;  z.z = 1.0f;  z.w = 0.0f;
	w.x = 0.0f;  w.y = 0.0f;  w.z = 0.0f;  w.w = 1.0f;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix& Matrix::Transpose( const Matrix &In )
{
	Matrix_Transpose( *this, In );

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix& Matrix::Inverse( const Matrix &In )
{
	Matrix_Inverse( *this, In );

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix& Matrix::Multiply( const Matrix &In1, const Matrix &In2 )
{
	Matrix_Multiply( *this, In1, In2 );

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix& Matrix::Transpose( void )
{
	Matrix_Transpose( *this, *this );

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix& Matrix::Inverse( void )
{
	Matrix_Inverse( *this, *this );

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix& Matrix::Multiply( const Matrix &In )
{
	Matrix_Multiply( *this, *this, In );

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix& Matrix::RotationX( Sint32 Angle )
{
	Float c = Math::Cos( Angle );
	Float s = Math::Sin( Angle );

	x.x = 1.0f;  x.y =  0.0f;  x.z = 0.0f;  x.w = 0.0f;
	y.x = 0.0f;  y.y =     c;  y.z =    s;  y.w = 0.0f;
	z.x = 0.0f;  z.y =    -s;  z.z =    c;  z.w = 0.0f;
	w.x = 0.0f;  w.y =  0.0f;  w.z = 0.0f;  w.w = 1.0f;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix& Matrix::RotationY( Sint32 Angle )
{
	Float c = Math::Cos( Angle );
	Float s = Math::Sin( Angle );

	x.x =    c;  x.y = 0.0f;  x.z =   -s;  x.w = 0.0f;
	y.x = 0.0f;  y.y = 1.0f;  y.z = 0.0f;  y.w = 0.0f;
	z.x =    s;  z.y = 0.0f;  z.z =    c;  z.w = 0.0f;
	w.x = 0.0f;  w.y = 0.0f;  w.z = 0.0f;  w.w = 1.0f;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix& Matrix::RotationZ( Sint32 Angle )
{
	Float c = Math::Cos( Angle );
	Float s = Math::Sin( Angle );

	x.x =    c;  x.y =    s;  x.z = 0.0f;  x.w = 0.0f;
	y.x =   -s;  y.y =    c;  y.z = 0.0f;  y.w = 0.0f;
	z.x = 0.0f;  z.y = 0.0f;  z.z = 1.0f;  z.w = 0.0f;
	w.x = 0.0f;  w.y = 0.0f;  w.z = 0.0f;  w.w = 1.0f;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix& Matrix::RotationZXY( Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ )
{
	AngleX /= 2;
	AngleY /= 2;
	AngleZ /= 2;

	Float SinAx = Math::Sin( AngleX );
	Float SinAy = Math::Sin( AngleY );
	Float SinAz = Math::Sin( AngleZ );
	Float CosAx = Math::Cos( AngleX );
	Float CosAy = Math::Cos( AngleY );
	Float CosAz = Math::Cos( AngleZ ); 

	Float _x = (SinAx * CosAy * CosAz) - (CosAx * SinAy * SinAz);
	Float _y = (CosAx * SinAy * CosAz) + (SinAx * CosAy * SinAz);
	Float _z = (CosAx * CosAy * SinAz) - (SinAx * SinAy * CosAz);
	Float _w = (CosAx * CosAy * CosAz) + (SinAx * SinAy * SinAz);

	Float xx = _x * _x;
	Float yy = _y * _y;
	Float zz = _z * _z;
	Float xy = _x * _y;
	Float xz = _x * _z;
	Float yz = _y * _z;
	Float wx = _w * _x;
	Float wy = _w * _y;
	Float wz = _w * _z;

	x.x = 1.0f - (2.0f * (yy + zz));
	x.y =        (2.0f * (xy - wz));
	x.z =        (2.0f * (xz + wy));
	x.w = 0.0f;

	y.x =        (2.0f * (xy + wz));
	y.y = 1.0f - (2.0f * (xx + zz));
	y.z =        (2.0f * (yz - wx));
	y.w = 0.0f;

	z.x =        (2.0f * (xz - wy));
	z.y =        (2.0f * (yz + wx));
	z.z = 1.0f - (2.0f * (xx + yy));
	z.w = 0.0f;

	w.x = 0.0f;
	w.y = 0.0f;
	w.z = 0.0f;
	w.w = 1.0f;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix& Matrix::RotationAxis( Sint32 Angle, const Vector3D &vAxis )
{
	Float c = Math::Cos( Angle );
	Float s = Math::Sin( Angle );
	Float cc = 1.0f - c;

	x.x = cc * (vAxis.x * vAxis.x) + c;
	x.y = cc * (vAxis.x * vAxis.y) - (vAxis.z * s);
	x.z = cc * (vAxis.z * vAxis.x) + (vAxis.y * s);
	x.w = 0.0f;

	y.x = cc * (vAxis.x * vAxis.y) + (vAxis.z * s);
	y.y = cc * (vAxis.y * vAxis.y) + c;
	y.z = cc * (vAxis.y * vAxis.z) - (vAxis.x * s);
	y.w = 0.0f;

	z.x = cc * (vAxis.z * vAxis.x) - (vAxis.y * s);
	z.y = cc * (vAxis.y * vAxis.z) + (vAxis.x * s);
	z.z = cc * (vAxis.z * vAxis.z) + c;
	z.w = 0.0f;

	w.x = 0.0f;
	w.y = 0.0f;
	w.z = 0.0f;
	w.w = 1.0f;

	return *this;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix& Matrix::Scaling( Float sx, Float sy, Float sz )
{
	x.x =   sx;  x.y = 0.0f;  x.z = 0.0f;  x.w = 0.0f;
	y.x = 0.0f;  y.y =   sy;  y.z = 0.0f;  y.w = 0.0f;
	z.x = 0.0f;  z.y = 0.0f;  z.z =   sz;  z.w = 0.0f;
	w.x = 0.0f;  w.y = 0.0f;  w.z = 0.0f;  w.w = 1.0f;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix& Matrix::Translation( Float px, Float py, Float pz )
{
	x.x = 1.0f;  x.y = 0.0f;  x.z = 0.0f;  x.w = 0.0f;
	y.x = 0.0f;  y.y = 1.0f;  y.z = 0.0f;  y.w = 0.0f;
	z.x = 0.0f;  z.y = 0.0f;  z.z = 1.0f;  z.w = 0.0f;

	w.x = px;
	w.y = py;
	w.z = pz;
	w.w = 1.0f;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix& Matrix::Perspective( Sint32 Fov, Float NearZ, Float FarZ, Float Aspect )
{
	::D3DXMatrixPerspectiveFovLH(
		(D3DXMATRIX*)this,
		ANGLE_TO_PI(Fov),
		Aspect,
		NearZ,
		FarZ );
	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix& Matrix::Ortho( Float Width, Float Height, Float NearZ, Float FarZ )
{
	::D3DXMatrixOrthoLH(
		(D3DXMATRIX*)this,
		Width,
		Height,
		NearZ,
		FarZ );
	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Matrix& Matrix::LookAt( const Vector3D &Eye, const Vector3D &At, const Vector3D &Up )
{
	Vector3D vFront, vRight, vUp;

	vFront = At - Eye;
	if ( (Abs(vFront.x) < 0.0000001f) && (Abs(vFront.z) < 0.0000001f) )
	{
		if ( vFront.y < 0.0f )
		{
			vUp.Set( Up.x, Up.z, +Up.y );
		}
		else
		{
			vUp.Set( Up.x, Up.z, -Up.y );
		}
	}
	else
	{
		vUp.Set( Up.x, Up.y, Up.z );
	}

	vRight.Cross( vUp, vFront );
	vUp.Cross( vFront, vRight );

	vRight.NormalizeFast();
	vUp.NormalizeFast();
	vFront.NormalizeFast();

	x.x = vRight.x;		x.y = vUp.x;		x.z = vFront.x;		x.w = 0.0f;
	y.x = vRight.y;		y.y = vUp.y;		y.z = vFront.y;		y.w = 0.0f;
	z.x = vRight.z;		z.y = vUp.z;		z.z = vFront.z;		z.w = 0.0f;

	w.x = -Eye.Dot( vRight );
	w.y = -Eye.Dot( vUp );
	w.z = -Eye.Dot( vFront );
	w.w = 1.0f;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Matrix::Resolution( Vector3D &vTranslate, Vector3D &vScale, Quaternion &qRotate )
{
	Matrix mTemp(
		x.x, x.y, x.z, 0.0f,
		y.x, y.y, y.z, 0.0f,
		z.x, z.y, z.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f );

	// Šg‘åk¬
	Vector3D AxisX( 1.0f, 0.0f, 0.0f );
	Vector3D AxisY( 0.0f, 1.0f, 0.0f );
	Vector3D AxisZ( 0.0f, 0.0f, 1.0f );
	AxisX.TransformNormal( mTemp );
	AxisY.TransformNormal( mTemp );
	AxisZ.TransformNormal( mTemp );
	vScale.Set( AxisX.Length(), AxisY.Length(), AxisZ.Length() );

	// ‰ñ“]
	Matrix mScale;
	mScale.Scaling( vScale.x, vScale.y, vScale.z );
	qRotate = Quaternion( mScale * mTemp );

	// ˆÚ“®
	vTranslate.Set( w.x, w.y, w.z );
}

