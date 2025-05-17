

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Math/Math.h"
#include "Math/Vector3D.h"
#include "Math/Matrix.h"
#include "System.h"
#include "SSE.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Math;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D::Vector3D()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D::Vector3D( const Vector3D &v )
{
	*this = v;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D::Vector3D( Float fPx, Float fPy, Float fPz )
{
	this->x = fPx;
	this->y = fPy;
	this->z = fPz;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float Vector3D::LengthSq( void ) const
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float vIn[] = { x, y, z, 0.0f };
		Float fOut;

		__asm
		{
			MOVAPS	xmm0,	vIn
			MOVAPS	xmm1,	xmm0

			MULPS	xmm0,	xmm1
			MOVAPS	xmm1,	xmm0
			SHUFPS	xmm0,	xmm1,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm0,	xmm1
			MOVHLPS	xmm1,	xmm0
			ADDSS	xmm0,	xmm1

			MOVSS	fOut,	xmm0
		}

		return fOut;
	}
	else
	{
		return (x * x) + (y * y) + (z * z);
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float Vector3D::Length( void ) const
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float vIn[] = { x, y, z, 0.0f };
		Float fOut;

		__asm
		{
			MOVAPS	xmm0,	vIn
			MOVAPS	xmm1,	xmm0

			MULPS	xmm0,	xmm1
			MOVAPS	xmm1,	xmm0
			SHUFPS	xmm0,	xmm1,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm0,	xmm1
			MOVHLPS	xmm1,	xmm0
			ADDSS	xmm0,	xmm1

			RSQRTSS	xmm1,	xmm0
			MULSS	xmm0,	xmm1

			MOVSS	fOut,	xmm0
		}

		return fOut;
	}
	else
	{
		return sqrtf( LengthSq() );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float Vector3D::LengthFast( void ) const
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float vIn[] = { x, y, z, 0.0f };
		Float fOut;

		__asm
		{
			MOVAPS	xmm0,	vIn
			MOVAPS	xmm1,	xmm0

			MULPS	xmm0,	xmm1
			MOVAPS	xmm1,	xmm0
			SHUFPS	xmm0,	xmm1,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm0,	xmm1
			MOVHLPS	xmm1,	xmm0
			ADDSS	xmm0,	xmm1

			RSQRTSS	xmm1,	xmm0
			MULSS	xmm0,	xmm1

			MOVSS	fOut,	xmm0
		}

		return fOut;
	}
	else
	{
		return FastSqrt( LengthSq() );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float Vector3D::Dot( const Vector3D &In ) const
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float fIn1[] = { x, y, z, 0.0f };
		SSE_ALIGN Float fIn2[] = { In.x, In.y, In.z, 0.0f };
		Float fOut;

		__asm
		{
			MOVAPS	xmm0,	fIn1
			MOVAPS	xmm1,	fIn2

			MULPS	xmm0,	xmm1
			MOVAPS	xmm1,	xmm0
			SHUFPS	xmm0,	xmm1,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm0,	xmm1
			MOVHLPS	xmm1,	xmm0
			ADDSS	xmm0,	xmm1

			MOVSS	fOut,	xmm0
		}

		return fOut;
	}
	else
	{
		return (x * In.x) + (y * In.y) + (z * In.z);
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D &Vector3D::Normalize( const Vector3D &In )
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float vIn[] = { In.x, In.y, In.z, 0.0f };
		SSE_ALIGN Float vOut[4];

		__asm
		{
			MOVAPS	xmm0,	vIn
			MOVAPS	xmm1,	xmm0
			MOVAPS	xmm7,	xmm0

			MULPS	xmm0,	xmm1
			MOVAPS	xmm1,	xmm0
			SHUFPS	xmm0,	xmm1,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm0,	xmm1
			MOVAPS	xmm1,	xmm0
			SHUFPS	xmm0,	xmm1,	SSE_PACK(SSE_W,SSE_Z,SSE_Y,SSE_X)
			ADDPS	xmm0,	xmm1

			RSQRTPS	xmm1,	xmm0
			MULPS	xmm0,	xmm1

			RCPPS	xmm1,	xmm0
			MULPS	xmm1,	xmm7

			MOVAPS	vOut,	xmm1
		}

		Set( vOut[0], vOut[1], vOut[2] );
	}
	else
	{
		Float fInvLen = 1.0f / In.Length();
		x = In.x * fInvLen;
		y = In.y * fInvLen;
		z = In.z * fInvLen;
	}

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D &Vector3D::NormalizeFast( const Vector3D &In )
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float vIn[] = { In.x, In.y, In.z, 0.0f };
		SSE_ALIGN Float vOut[4];

		__asm
		{
			MOVAPS	xmm0,	vIn
			MOVAPS	xmm1,	xmm0
			MOVAPS	xmm7,	xmm0

			MULPS	xmm0,	xmm1
			MOVAPS	xmm1,	xmm0
			SHUFPS	xmm0,	xmm1,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm0,	xmm1
			MOVAPS	xmm1,	xmm0
			SHUFPS	xmm0,	xmm1,	SSE_PACK(SSE_W,SSE_Z,SSE_Y,SSE_X)
			ADDPS	xmm0,	xmm1

			RSQRTPS	xmm1,	xmm0
			MULPS	xmm0,	xmm1

			RCPPS	xmm1,	xmm0
			MULPS	xmm1,	xmm7

			MOVAPS	vOut,	xmm1
		}

		Set( vOut[0], vOut[1], vOut[2] );
	}
	else
	{
		Float fInvLen = 1.0f / In.LengthFast();
		x = In.x * fInvLen;
		y = In.y * fInvLen;
		z = In.z * fInvLen;
	}

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D& Vector3D::Cross( const Vector3D &In1, const Vector3D &In2 )
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float vIn1[] = { In1.x, In1.y, In1.z, 0.0f };
		SSE_ALIGN Float vIn2[] = { In2.x, In2.y, In2.z, 0.0f };
		SSE_ALIGN Float vOut[4];

		__asm
		{
			MOVAPS	xmm0,	vIn1
			MOVAPS	xmm1,	vIn2

			MOVAPS	xmm2,	xmm0
			MOVAPS	xmm3,	xmm1
			SHUFPS	xmm2,	xmm2,	SSE_PACK(SSE_X,SSE_W,SSE_Y,SSE_Z)
			SHUFPS	xmm3,	xmm3,	SSE_PACK(SSE_X,SSE_Z,SSE_W,SSE_Y)
			MULPS	xmm2,	xmm3
			SHUFPS	xmm0,	xmm0,	SSE_PACK(SSE_X,SSE_Z,SSE_W,SSE_Y)
			SHUFPS	xmm1,	xmm1,	SSE_PACK(SSE_X,SSE_W,SSE_Y,SSE_Z)
			MULPS	xmm0,	xmm1
			SUBPS	xmm2,	xmm0

			MOVAPS	vOut,	xmm2
		}

		Set( vOut[0], vOut[1], vOut[2] );
	}
	else
	{
		x = (In1.y * In2.z) - (In1.z * In2.y);
		y = (In1.z * In2.x) - (In1.x * In2.z);
		z = (In1.x * In2.y) - (In1.y * In2.x);
	}

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D& Vector3D::Reflect( const Vector3D &In1, const Vector3D &In2 )
{
	Float dot = In1.Dot( In2 );

	x = In1.x - (2 * dot * In2.x);
	y = In1.y - (2 * dot * In2.y);
	z = In1.z - (2 * dot * In2.z);

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D& Vector3D::TransformNormal( const Vector3D &In1, const Matrix &In2 )
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float Mtx0[4] = { In2.x.x, In2.y.x, In2.z.x, 0.0f };
		SSE_ALIGN Float Mtx1[4] = { In2.x.y, In2.y.y, In2.z.y, 0.0f };
		SSE_ALIGN Float Mtx2[4] = { In2.x.z, In2.y.z, In2.z.z, 0.0f };
		SSE_ALIGN Float vIn[4] = { In1.x, In1.y, In1.z, 0.0f };
		Float vOut0, vOut1, vOut2;

		__asm
		{
			MOVAPS	xmm0,	Mtx0
			MOVAPS	xmm1,	Mtx1
			MOVAPS	xmm2,	Mtx2

			MULPS	xmm0,	vIn
			MULPS	xmm1,	vIn
			MULPS	xmm2,	vIn

			MOVAPS	xmm4,	xmm0
			SHUFPS	xmm0,	xmm4,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm4,	xmm0
			MOVHLPS	xmm0,	xmm4
			ADDSS	xmm4,	xmm0

			MOVAPS	xmm5,	xmm1
			SHUFPS	xmm1,	xmm5,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm5,	xmm1
			MOVHLPS	xmm1,	xmm5
			ADDSS	xmm5,	xmm1

			MOVAPS	xmm6,	xmm2
			SHUFPS	xmm2,	xmm6,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm6,	xmm2
			MOVHLPS	xmm2,	xmm6
			ADDSS	xmm6,	xmm2

			MOVSS	vOut0,	xmm4
			MOVSS	vOut1,	xmm5
			MOVSS	vOut2,	xmm6
		}

		Set( vOut0, vOut1, vOut2 );
	}
	else
	{
		x = (In1.x * In2.x.x) + (In1.y * In2.y.x) + (In1.z * In2.z.x);
		y = (In1.x * In2.x.y) + (In1.y * In2.y.y) + (In1.z * In2.z.y);
		z = (In1.x * In2.x.z) + (In1.y * In2.y.z) + (In1.z * In2.z.z);
	}

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D& Vector3D::TransformCoord( const Vector3D &In1, const Matrix &In2 )
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float Mtx0[4] = { In2.x.x, In2.y.x, In2.z.x, In2.w.x };
		SSE_ALIGN Float Mtx1[4] = { In2.x.y, In2.y.y, In2.z.y, In2.w.y };
		SSE_ALIGN Float Mtx2[4] = { In2.x.z, In2.y.z, In2.z.z, In2.w.z };
		SSE_ALIGN Float vIn[4] = { In1.x, In1.y, In1.z, 1.0f };
		Float vOut0, vOut1, vOut2;

		__asm
		{
			MOVAPS	xmm0,	Mtx0
			MOVAPS	xmm1,	Mtx1
			MOVAPS	xmm2,	Mtx2

			MULPS	xmm0,	vIn
			MULPS	xmm1,	vIn
			MULPS	xmm2,	vIn

			MOVAPS	xmm4,	xmm0
			SHUFPS	xmm0,	xmm4,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm4,	xmm0
			MOVHLPS	xmm0,	xmm4
			ADDSS	xmm4,	xmm0

			MOVAPS	xmm5,	xmm1
			SHUFPS	xmm1,	xmm5,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm5,	xmm1
			MOVHLPS	xmm1,	xmm5
			ADDSS	xmm5,	xmm1

			MOVAPS	xmm6,	xmm2
			SHUFPS	xmm2,	xmm6,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm6,	xmm2
			MOVHLPS	xmm2,	xmm6
			ADDSS	xmm6,	xmm2

			MOVSS	vOut0,	xmm4
			MOVSS	vOut1,	xmm5
			MOVSS	vOut2,	xmm6
		}

		Set( vOut0, vOut1, vOut2 );
	}
	else
	{
		x = (In1.x * In2.x.x) + (In1.y * In2.y.x) + (In1.z * In2.z.x) + In2.w.x;
		y = (In1.x * In2.x.y) + (In1.y * In2.y.y) + (In1.z * In2.z.y) + In2.w.y;
		z = (In1.x * In2.x.z) + (In1.y * In2.y.z) + (In1.z * In2.z.z) + In2.w.z;
	}

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D& Vector3D::TransformProjection( const Vector3D &In1, const Matrix &In2 )
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float Mtx0[4] = { In2.x.x, In2.y.x, In2.z.x, In2.w.x };
		SSE_ALIGN Float Mtx1[4] = { In2.x.y, In2.y.y, In2.z.y, In2.w.y };
		SSE_ALIGN Float Mtx2[4] = { In2.x.z, In2.y.z, In2.z.z, In2.w.z };
		SSE_ALIGN Float Mtx3[4] = { In2.x.w, In2.y.w, In2.z.w, In2.w.w };
		SSE_ALIGN Float vIn[4] = { In1.x, In1.y, In1.z, 1.0f };
		Float vOut0, vOut1, vOut2, vOut3;

		__asm
		{
			MOVAPS	xmm0,	Mtx0
			MOVAPS	xmm1,	Mtx1
			MOVAPS	xmm2,	Mtx2
			MOVAPS	xmm3,	Mtx3

			MULPS	xmm0,	vIn
			MULPS	xmm1,	vIn
			MULPS	xmm2,	vIn
			MULPS	xmm3,	vIn

			MOVAPS	xmm4,	xmm0
			SHUFPS	xmm0,	xmm4,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm4,	xmm0
			MOVHLPS	xmm0,	xmm4
			ADDSS	xmm4,	xmm0

			MOVAPS	xmm5,	xmm1
			SHUFPS	xmm1,	xmm5,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm5,	xmm1
			MOVHLPS	xmm1,	xmm5
			ADDSS	xmm5,	xmm1

			MOVAPS	xmm6,	xmm2
			SHUFPS	xmm2,	xmm6,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm6,	xmm2
			MOVHLPS	xmm2,	xmm6
			ADDSS	xmm6,	xmm2

			MOVAPS	xmm7,	xmm3
			SHUFPS	xmm3,	xmm7,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm7,	xmm3
			MOVHLPS	xmm3,	xmm7
			ADDSS	xmm7,	xmm3

			MOVSS	vOut0,	xmm4
			MOVSS	vOut1,	xmm5
			MOVSS	vOut2,	xmm6
			MOVSS	vOut3,	xmm7
		}

		Float fInvW = 1.0f / vOut3;
		Set( vOut0 * fInvW, vOut1 * fInvW, vOut2 * fInvW );
	}
	else
	{
		Float vOut0 = (In1.x * In2.x.x) + (In1.y * In2.y.x) + (In1.z * In2.z.x) + In2.w.x;
		Float vOut1 = (In1.x * In2.x.y) + (In1.y * In2.y.y) + (In1.z * In2.z.y) + In2.w.y;
		Float vOut2 = (In1.x * In2.x.z) + (In1.y * In2.y.z) + (In1.z * In2.z.z) + In2.w.z;
		Float vOut3 = (In1.x * In2.x.w) + (In1.y * In2.y.w) + (In1.z * In2.z.w) + In2.w.w;

		Float fInvW = 1.0f / vOut3;
		Set( vOut0 * fInvW, vOut1 * fInvW, vOut2 * fInvW );
	}

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D &Vector3D::Normalize( void )
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float vIn[] = { x, y, z, 0.0f };
		SSE_ALIGN Float vOut[4];

		__asm
		{
			MOVAPS	xmm0,	vIn
			MOVAPS	xmm1,	xmm0
			MOVAPS	xmm7,	xmm0

			MULPS	xmm0,	xmm1
			MOVAPS	xmm1,	xmm0
			SHUFPS	xmm0,	xmm1,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm0,	xmm1
			MOVAPS	xmm1,	xmm0
			SHUFPS	xmm0,	xmm1,	SSE_PACK(SSE_W,SSE_Z,SSE_Y,SSE_X)
			ADDPS	xmm0,	xmm1

			RSQRTPS	xmm1,	xmm0
			MULPS	xmm0,	xmm1

			RCPPS	xmm1,	xmm0
			MULPS	xmm1,	xmm7

			MOVAPS	vOut,	xmm1
		}

		Set( vOut[0], vOut[1], vOut[2] );
	}
	else
	{
		Float fInvLen = 1.0f / Length();
		x = x * fInvLen;
		y = y * fInvLen;
		z = z * fInvLen;
	}

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D &Vector3D::NormalizeFast( void )
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float vIn[] = { x, y, z, 0.0f };
		SSE_ALIGN Float vOut[4];

		__asm
		{
			MOVAPS	xmm0,	vIn
			MOVAPS	xmm1,	xmm0
			MOVAPS	xmm7,	xmm0

			MULPS	xmm0,	xmm1
			MOVAPS	xmm1,	xmm0
			SHUFPS	xmm0,	xmm1,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm0,	xmm1
			MOVAPS	xmm1,	xmm0
			SHUFPS	xmm0,	xmm1,	SSE_PACK(SSE_W,SSE_Z,SSE_Y,SSE_X)
			ADDPS	xmm0,	xmm1

			RSQRTPS	xmm1,	xmm0
			MULPS	xmm0,	xmm1

			RCPPS	xmm1,	xmm0
			MULPS	xmm1,	xmm7

			MOVAPS	vOut,	xmm1
		}

		Set( vOut[0], vOut[1], vOut[2] );
	}
	else
	{
		Float fInvLen = 1.0f / LengthFast();
		x = x * fInvLen;
		y = y * fInvLen;
		z = z * fInvLen;
	}

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D& Vector3D::Cross( const Vector3D &In )
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float vIn1[] = { x, y, z, 0.0f };
		SSE_ALIGN Float vIn2[] = { In.x, In.y, In.z, 0.0f };
		SSE_ALIGN Float vOut[4];

		__asm
		{
			MOVAPS	xmm0,	vIn1
			MOVAPS	xmm1,	vIn2

			MOVAPS	xmm2,	xmm0
			MOVAPS	xmm3,	xmm1
			SHUFPS	xmm2,	xmm2,	SSE_PACK(SSE_X,SSE_W,SSE_Y,SSE_Z)
			SHUFPS	xmm3,	xmm3,	SSE_PACK(SSE_X,SSE_Z,SSE_W,SSE_Y)
			MULPS	xmm2,	xmm3
			SHUFPS	xmm0,	xmm0,	SSE_PACK(SSE_X,SSE_Z,SSE_W,SSE_Y)
			SHUFPS	xmm1,	xmm1,	SSE_PACK(SSE_X,SSE_W,SSE_Y,SSE_Z)
			MULPS	xmm0,	xmm1
			SUBPS	xmm2,	xmm0

			MOVAPS	vOut,	xmm2
		}

		Set( vOut[0], vOut[1], vOut[2] );
	}
	else
	{
		Vector3D vTemp = *this;
		x = (vTemp.y * In.z) - (vTemp.z * In.y);
		y = (vTemp.z * In.x) - (vTemp.x * In.z);
		z = (vTemp.x * In.y) - (vTemp.y * In.x);
	}

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D& Vector3D::Reflect( const Vector3D &In )
{
	Vector3D vTemp = *this;
	Float dot = In.Dot( vTemp );

	x = In.x - (2 * dot * vTemp.x);
	y = In.y - (2 * dot * vTemp.y);
	z = In.z - (2 * dot * vTemp.z);

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D& Vector3D::TransformNormal( const Matrix &In )
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float Mtx0[4] = { In.x.x, In.y.x, In.z.x, 0.0f };
		SSE_ALIGN Float Mtx1[4] = { In.x.y, In.y.y, In.z.y, 0.0f };
		SSE_ALIGN Float Mtx2[4] = { In.x.z, In.y.z, In.z.z, 0.0f };
		SSE_ALIGN Float vIn[4] = { x, y, z, 0.0f };
		Float vOut0, vOut1, vOut2;

		__asm
		{
			MOVAPS	xmm0,	Mtx0
			MOVAPS	xmm1,	Mtx1
			MOVAPS	xmm2,	Mtx2

			MULPS	xmm0,	vIn
			MULPS	xmm1,	vIn
			MULPS	xmm2,	vIn

			MOVAPS	xmm4,	xmm0
			SHUFPS	xmm0,	xmm4,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm4,	xmm0
			MOVHLPS	xmm0,	xmm4
			ADDSS	xmm4,	xmm0

			MOVAPS	xmm5,	xmm1
			SHUFPS	xmm1,	xmm5,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm5,	xmm1
			MOVHLPS	xmm1,	xmm5
			ADDSS	xmm5,	xmm1

			MOVAPS	xmm6,	xmm2
			SHUFPS	xmm2,	xmm6,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm6,	xmm2
			MOVHLPS	xmm2,	xmm6
			ADDSS	xmm6,	xmm2

			MOVSS	vOut0,	xmm4
			MOVSS	vOut1,	xmm5
			MOVSS	vOut2,	xmm6
		}

		Set( vOut0, vOut1, vOut2 );
	}
	else
	{
		Vector3D vTemp = *this;
		x = (vTemp.x * In.x.x) + (vTemp.y * In.y.x) + (vTemp.z * In.z.x);
		y = (vTemp.x * In.x.y) + (vTemp.y * In.y.y) + (vTemp.z * In.z.y);
		z = (vTemp.x * In.x.z) + (vTemp.y * In.y.z) + (vTemp.z * In.z.z);
	}

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D& Vector3D::TransformCoord( const Matrix &In )
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float Mtx0[4] = { In.x.x, In.y.x, In.z.x, In.w.x };
		SSE_ALIGN Float Mtx1[4] = { In.x.y, In.y.y, In.z.y, In.w.y };
		SSE_ALIGN Float Mtx2[4] = { In.x.z, In.y.z, In.z.z, In.w.z };
		SSE_ALIGN Float vIn[4] = { x, y, z, 1.0f };
		Float vOut0, vOut1, vOut2;

		__asm
		{
			MOVAPS	xmm0,	Mtx0
			MOVAPS	xmm1,	Mtx1
			MOVAPS	xmm2,	Mtx2

			MULPS	xmm0,	vIn
			MULPS	xmm1,	vIn
			MULPS	xmm2,	vIn

			MOVAPS	xmm4,	xmm0
			SHUFPS	xmm0,	xmm4,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm4,	xmm0
			MOVHLPS	xmm0,	xmm4
			ADDSS	xmm4,	xmm0

			MOVAPS	xmm5,	xmm1
			SHUFPS	xmm1,	xmm5,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm5,	xmm1
			MOVHLPS	xmm1,	xmm5
			ADDSS	xmm5,	xmm1

			MOVAPS	xmm6,	xmm2
			SHUFPS	xmm2,	xmm6,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm6,	xmm2
			MOVHLPS	xmm2,	xmm6
			ADDSS	xmm6,	xmm2

			MOVSS	vOut0,	xmm4
			MOVSS	vOut1,	xmm5
			MOVSS	vOut2,	xmm6
		}

		Set( vOut0, vOut1, vOut2 );
	}
	else
	{
		Vector3D vTemp = *this;
		x = (vTemp.x * In.x.x) + (vTemp.y * In.y.x) + (vTemp.z * In.z.x) + In.w.x;
		y = (vTemp.x * In.x.y) + (vTemp.y * In.y.y) + (vTemp.z * In.z.y) + In.w.y;
		z = (vTemp.x * In.x.z) + (vTemp.y * In.y.z) + (vTemp.z * In.z.z) + In.w.z;
	}

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D& Vector3D::TransformProjection( const Matrix &In )
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float Mtx0[4] = { In.x.x, In.y.x, In.z.x, In.w.x };
		SSE_ALIGN Float Mtx1[4] = { In.x.y, In.y.y, In.z.y, In.w.y };
		SSE_ALIGN Float Mtx2[4] = { In.x.z, In.y.z, In.z.z, In.w.z };
		SSE_ALIGN Float Mtx3[4] = { In.x.w, In.y.w, In.z.w, In.w.w };
		SSE_ALIGN Float vIn[4] = { x, y, z, 1.0f };
		Float vOut0, vOut1, vOut2, vOut3;

		__asm
		{
			MOVAPS	xmm0,	Mtx0
			MOVAPS	xmm1,	Mtx1
			MOVAPS	xmm2,	Mtx2
			MOVAPS	xmm3,	Mtx3

			MULPS	xmm0,	vIn
			MULPS	xmm1,	vIn
			MULPS	xmm2,	vIn
			MULPS	xmm3,	vIn

			MOVAPS	xmm4,	xmm0
			SHUFPS	xmm0,	xmm4,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm4,	xmm0
			MOVHLPS	xmm0,	xmm4
			ADDSS	xmm4,	xmm0

			MOVAPS	xmm5,	xmm1
			SHUFPS	xmm1,	xmm5,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm5,	xmm1
			MOVHLPS	xmm1,	xmm5
			ADDSS	xmm5,	xmm1

			MOVAPS	xmm6,	xmm2
			SHUFPS	xmm2,	xmm6,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm6,	xmm2
			MOVHLPS	xmm2,	xmm6
			ADDSS	xmm6,	xmm2

			MOVAPS	xmm7,	xmm3
			SHUFPS	xmm3,	xmm7,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm7,	xmm3
			MOVHLPS	xmm3,	xmm7
			ADDSS	xmm7,	xmm3

			MOVSS	vOut0,	xmm4
			MOVSS	vOut1,	xmm5
			MOVSS	vOut2,	xmm6
			MOVSS	vOut3,	xmm7
		}

		Float fInvW = 1.0f / vOut3;
		Set( vOut0 * fInvW, vOut1 * fInvW, vOut2 * fInvW );
	}
	else
	{
		Vector3D vTemp = *this;
		Float _x = (vTemp.x * In.x.x) + (vTemp.y * In.y.x) + (vTemp.z * In.z.x) + In.w.x;
		Float _y = (vTemp.x * In.x.y) + (vTemp.y * In.y.y) + (vTemp.z * In.z.y) + In.w.y;
		Float _z = (vTemp.x * In.x.z) + (vTemp.y * In.y.z) + (vTemp.z * In.z.z) + In.w.z;
		Float _w = (vTemp.x * In.x.w) + (vTemp.y * In.y.w) + (vTemp.z * In.z.w) + In.w.w;

		_w = 1.0f / _w;

		x = _x * _w;
		y = _y * _w;
		z = _z * _w;
	}

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D& Vector3D::RotationX( Sint32 Angle )
{
	Vector3D vTemp = *this;
	Float s = Math::Sin( Angle );
	Float c = Math::Cos( Angle );

	x = vTemp.x;
	y = (vTemp.y * +c) + (vTemp.z * -s);
	z = (vTemp.y * +s) + (vTemp.z * +c);

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D& Vector3D::RotationY( Sint32 Angle )
{
	Vector3D vTemp = *this;
	Float s = Math::Sin( Angle );
	Float c = Math::Cos( Angle );

	x = (vTemp.x * +c) + (vTemp.z * +s);
	y = vTemp.y;
	z = (vTemp.x * -s) + (vTemp.z * +c);

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D& Vector3D::RotationZ( Sint32 Angle )
{
	Vector3D vTemp = *this;
	Float s = Math::Sin( Angle );
	Float c = Math::Cos( Angle );

	x = (vTemp.x * +c) + (vTemp.y * -s);
	y = (vTemp.x * +s) + (vTemp.y * +c);
	z = vTemp.z;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D& Vector3D::RotationAxis( Sint32 Angle, const Vector3D &Axis )
{
	Matrix Mat;
	Mat.RotationAxis( Angle, Axis );
	TransformNormal( Mat );

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D& Vector3D::Add( const Vector3D &In1, const Vector3D &In2 )
{
	x = In1.x + In2.x;
	y = In1.y + In2.y;
	z = In1.z + In2.z;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D& Vector3D::Sub( const Vector3D &In1, const Vector3D &In2 )
{
	x = In1.x - In2.x;
	y = In1.y - In2.y;
	z = In1.z - In2.z;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector3D& Vector3D::Set( Float fPx, Float fPy, Float fPz )
{
	x = fPx;
	y = fPy;
	z = fPz;

	return *this;
}

