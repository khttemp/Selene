

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Math/Quaternion.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Math;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Quaternion::Quaternion()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Quaternion::Quaternion( Float x, Float y, Float z, Float w )
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Quaternion::Quaternion( const Quaternion &In )
{
	this->x = In.x;
	this->y = In.y;
	this->z = In.z;
	this->w = In.w;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Quaternion::Quaternion( const Matrix &In )
{
	D3DXQuaternionRotationMatrix( (D3DXQUATERNION*)this, (D3DXMATRIX*)&In );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Quaternion& Quaternion::Identity( void )
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 1.0f;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float Quaternion::LengthSq( void ) const
{
	return (x * x) + (y * y) + (z * z) + (w * w);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float Quaternion::Length( void ) const
{
	return FastSqrt( LengthSq() );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float Quaternion::Dot( const Quaternion &qIn ) const
{
	return (x * qIn.x) + (y * qIn.y) + (z * qIn.z) + (w * qIn.w);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Quaternion& Quaternion::Conjugate( void )
{
    x = -x;
    y = -y;
    z = -z;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Quaternion& Quaternion::Conjugate( const Quaternion &In )
{
    x = -In.x;
    y = -In.y;
    z = -In.z;
    w =  In.w;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Quaternion& Quaternion::Add( const Quaternion &In1, const Quaternion &In2 )
{
	x = In1.x + In2.x;
	y = In1.y + In2.y;
	z = In1.z + In2.z;
	w = In1.w + In2.w;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Quaternion& Quaternion::Sub( const Quaternion &In1, const Quaternion &In2 )
{
	x = In1.x - In2.x;
	y = In1.y - In2.y;
	z = In1.z - In2.z;
	w = In1.w - In2.w;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Quaternion& Quaternion::Mul( const Quaternion &In1, const Quaternion &In2 )
{
	x = (In1.w * In2.x) + (In2.w * In1.x) + (In1.y * In2.z) - (In1.z * In2.y);
	y = (In1.w * In2.y) + (In2.w * In1.y) + (In1.z * In2.x) - (In1.x * In2.z);
	z = (In1.w * In2.z) + (In2.w * In1.z) + (In1.x * In2.y) - (In1.y * In2.x);
	w = (In1.w * In2.w) - (In1.x * In2.x) - (In1.y * In2.y) - (In1.z * In2.z);

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Quaternion& Quaternion::Lerp( const Quaternion &In1, const Quaternion &In2, Float fRate )
{
    x = In1.x + (fRate * (In2.x - In1.x));
    y = In1.y + (fRate * (In2.y - In1.y));
    z = In1.z + (fRate * (In2.z - In1.z));
    w = In1.w + (fRate * (In2.w - In1.w));

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Quaternion& Quaternion::Slerp( const Quaternion &In1, const Quaternion &In2, Float fRate )
{
    Quaternion qTemp;
    Float fDot;

	if ( fRate == 0.0f )
	{
		*this = In1;
		return *this;
	}
	ef ( fRate == 1.0f )
	{
		*this = In2;
		return *this;
	}

	// 2つのクォータニオンの内積
    fDot = In1.Dot( In2 );

    // fDot < 0.0f の時反転する
    if ( fDot < 0.0f )
	{
        fDot = -fDot;
        qTemp.x = -In2.x;
        qTemp.y = -In2.y;
        qTemp.z = -In2.z;
        qTemp.w = -In2.w;
    }
    else
	{
		qTemp.x = In2.x;
		qTemp.y = In2.y;
		qTemp.z = In2.z;
		qTemp.w = In2.w;
	}

	// 球面線形補間
    if ( fDot < 0.95f )
	{
        if ( fDot > +1.0f ) fDot = +1.0f;
        if ( fDot < -1.0f ) fDot = -1.0f;

        Float angle = acosf( fDot );

        Float sin1 = sinf(angle              );
        Float sin2 = sinf(angle *      fRate );
        Float sin3 = sinf(angle * (1 - fRate));

        x = ((In1.x * sin3) + (qTemp.x * sin2)) / sin1;
        y = ((In1.y * sin3) + (qTemp.y * sin2)) / sin1;
        z = ((In1.z * sin3) + (qTemp.z * sin2)) / sin1;
        w = ((In1.w * sin3) + (qTemp.w * sin2)) / sin1;
    }
    // 角度が小さい時は線形補間
    else
	{
		Lerp( In1, qTemp, fRate );
	}

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Quaternion& Quaternion::Add( const Quaternion &In )
{
	x += In.x;
	y += In.y;
	z += In.z;
	w += In.w;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Quaternion& Quaternion::Sub( const Quaternion &In )
{
	x -= In.x;
	y -= In.y;
	z -= In.z;
	w -= In.w;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Quaternion& Quaternion::Mul( const Quaternion &In )
{
	Quaternion qTemp = *this;
	x = (qTemp.w * In.x) + (In.w * qTemp.x) + (qTemp.y * In.z) - (qTemp.z * In.y);
	y = (qTemp.w * In.y) + (In.w * qTemp.y) + (qTemp.z * In.x) - (qTemp.x * In.z);
	z = (qTemp.w * In.z) + (In.w * qTemp.z) + (qTemp.x * In.y) - (qTemp.y * In.x);
	w = (qTemp.w * In.w) - (qTemp.x * In.x) - (qTemp.y * In.y) - (qTemp.z * In.z);

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Quaternion& Quaternion::Lerp( const Quaternion &In, Float fRate )
{
    x += fRate * (In.x - x);
    y += fRate * (In.y - y);
    z += fRate * (In.z - z);
    w += fRate * (In.w - w);

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Quaternion& Quaternion::Slerp( const Quaternion &In, Float fRate )
{
    Quaternion In1 = *this;
    Quaternion qTemp;
    Float fDot;

	// 2つのクォータニオンの内積
    fDot = In1.Dot( In );

    // fDot < 0.0f の時反転する
    if ( fDot < 0.0f )
	{
        fDot = -fDot;
        qTemp.x = -In.x;
        qTemp.y = -In.y;
        qTemp.z = -In.z;
        qTemp.w = -In.w;
    }
    else
	{
		qTemp.x = In.x;
		qTemp.y = In.y;
		qTemp.z = In.z;
        qTemp.w = In.w;
	}

	// 球面線形補間
    if ( fDot < 0.95f )
	{
        if ( fDot > +1.0f ) fDot = +1.0f;
        if ( fDot < -1.0f ) fDot = -1.0f;

        Float angle = acosf( fDot );

        Float sin1 = sinf(angle              );
        Float sin2 = sinf(angle *      fRate );
        Float sin3 = sinf(angle * (1 - fRate));

        x = ((In1.x * sin3) + (qTemp.x * sin2)) / sin1;
        y = ((In1.y * sin3) + (qTemp.y * sin2)) / sin1;
        z = ((In1.z * sin3) + (qTemp.z * sin2)) / sin1;
        w = ((In1.w * sin3) + (qTemp.w * sin2)) / sin1;
    }
    // 角度が小さい時は線形補間
    else
	{
		Lerp( In, qTemp, fRate );
	}

	return *this;
}

