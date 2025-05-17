

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Math/Vector2D.h"
#include "Math/Math.h"
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
Vector2D::Vector2D()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector2D::Vector2D( const Vector2D &v )
{
	*this = v;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector2D::Vector2D( Float fPx, Float fPy )
{
	x = fPx;
	y = fPy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float Vector2D::LengthSq( void ) const
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float vIn[] = { x, y, 0.0f, 0.0f };
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
		return (x * x) + (y * y);
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float Vector2D::Length( void ) const
{
	SSE_ALIGN Float vIn[] = { x, y, 0.0f, 0.0f };
	Float fOut;

	if ( System::IsSupportSSE() )
	{
		__asm
		{
			MOVAPS	xmm0,	vIn
			MOVAPS	xmm1,	xmm0

			MULPS	xmm0,	xmm1
			MOVAPS	xmm1,	xmm0
			SHUFPS	xmm0,	xmm1,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm0,	xmm1
			MOVHLPS	xmm1,	xmm0
			ADDPS	xmm0,	xmm1

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
Float Vector2D::LengthFast( void ) const
{
	SSE_ALIGN Float vIn[] = { x, y, 0.0f, 0.0f };
	Float fOut;

	if ( System::IsSupportSSE() )
	{
		__asm
		{
			MOVAPS	xmm0,	vIn
			MOVAPS	xmm1,	xmm0

			MULPS	xmm0,	xmm1
			MOVAPS	xmm1,	xmm0
			SHUFPS	xmm0,	xmm1,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm0,	xmm1
			MOVHLPS	xmm1,	xmm0
			ADDPS	xmm0,	xmm1

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
Float Vector2D::Dot( const Vector2D &In ) const
{
	SSE_ALIGN Float fIn1[] = { x, y, 0.0f, 0.0f };
	SSE_ALIGN Float fIn2[] = { In.x, In.y, 0.0f, 0.0f };
	Float fOut;

	if ( System::IsSupportSSE() )
	{
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
		return (x * x) + (y * y);
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector2D& Vector2D::Normalize( const Vector2D &In )
{
	SSE_ALIGN Float vIn[] = { In.x, In.y, 0.0f, 0.0f };
	SSE_ALIGN Float vOut[4];

	if ( System::IsSupportSSE() )
	{
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

		Set( vOut[0], vOut[1] );
	}
	else
	{
		Float fInvLen = 1.0f / In.Length();
		x = In.x * fInvLen;
		y = In.y * fInvLen;
	}

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector2D& Vector2D::NormalizeFast( const Vector2D &In )
{
	SSE_ALIGN Float vIn[] = { In.x, In.y, 0.0f, 0.0f };
	SSE_ALIGN Float vOut[4];

	if ( System::IsSupportSSE() )
	{
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

		Set( vOut[0], vOut[1] );
	}
	else
	{
		Float fInvLen = 1.0f / In.LengthFast();
		x = In.x * fInvLen;
		y = In.y * fInvLen;
	}

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector2D& Vector2D::Reflect( const Vector2D &In1, const Vector2D &In2 )
{
	Float dot = In1.Dot( In2 );

	x = In1.x - (2 * dot * In2.x);
	y = In1.y - (2 * dot * In2.y);

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector2D& Vector2D::Normalize( void )
{
	SSE_ALIGN Float vIn[] = { x, y, 0.0f, 0.0f };
	SSE_ALIGN Float vOut[4];

	if ( System::IsSupportSSE() )
	{
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

		Set( vOut[0], vOut[1] );
	}
	else
	{
		Float fInvLen = 1.0f / Length();
		x = x * fInvLen;
		y = y * fInvLen;
	}

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector2D& Vector2D::NormalizeFast( void )
{
	SSE_ALIGN Float vIn[] = { x, y, 0.0f, 0.0f };
	SSE_ALIGN Float vOut[4];

	if ( System::IsSupportSSE() )
	{
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

		Set( vOut[0], vOut[1] );
	}
	else
	{
		Float fInvLen = 1.0f / LengthFast();
		x = x * fInvLen;
		y = y * fInvLen;
	}

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float Vector2D::Cross( const Vector2D &In ) const
{
	return (x * In.y) - (y * In.x);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector2D& Vector2D::Reflect( const Vector2D &In )
{
	Vector2D vTemp = *this;
	Float dot = In.Dot( vTemp );

	x = In.x - (2 * dot * vTemp.x);
	y = In.y - (2 * dot * vTemp.y);

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector2D& Vector2D::Add( const Vector2D &In1, const Vector2D &In2 )
{
	x = In1.x + In2.x;
	y = In1.y + In2.y;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector2D& Vector2D::Sub( const Vector2D &In1, const Vector2D &In2 )
{
	x = In1.x - In2.x;
	y = In1.y - In2.y;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector2D& Vector2D::Set( Float fPx, Float fPy )
{
	x = fPx;
	y = fPy;

	return *this;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Vector2D& Vector2D::RotationZ( Sint32 Angle )
{
	Float fSin = Math::Sin( Angle );
	Float fCos = Math::Cos( Angle );

	Float fPx = (fCos * x) - (fSin * y);
	Float fPy = (fSin * x) + (fCos * y);

	x = fPx;
	y = fPy;

	return *this;
}

