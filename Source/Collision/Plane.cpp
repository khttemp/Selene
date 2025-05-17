

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Collision/Plane.h"
#include "System.h"
#include "SSE.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Collision;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPlane::CPlane( void )
{
}


//-----------------------------------------------------------------------------------
/**
	@brief コンストラクタ
	@author 葉迩倭

	@param a	[in] 一般平面方程式におけるクリップ面の a 係数
	@param b	[in] 一般平面方程式におけるクリップ面の b 係数
	@param c	[in] 一般平面方程式におけるクリップ面の c 係数
	@param d	[in] 一般平面方程式におけるクリップ面の d 係数
*/
//-----------------------------------------------------------------------------------
CPlane::CPlane( Float a, Float b, Float c, Float d )
{
	this->n.x = a;
	this->n.y = b;
	this->n.z = c;
	this->d = d;
}


//-----------------------------------------------------------------------------------
/**
	@brief 法線データから生成
	@author 葉迩倭

	@param Pt		[in] 平面上の1点
	@param vNormal	[in] 平面の法線
*/
//-----------------------------------------------------------------------------------
void CPlane::FromNormal( const Math::Vector3D &Pt, const Math::Vector3D &vNormal )
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float vIn1[] = { vNormal.x, vNormal.y, vNormal.z, 0.0f };
		SSE_ALIGN Float vIn2[] = { Pt.x, Pt.y, Pt.z, 0.0f };
		SSE_ALIGN Float vOut[4];
		Float fDot;

		__asm
		{
			MOVAPS	xmm0,	vIn1
			MOVAPS	xmm1,	xmm0
			MOVAPS	xmm7,	xmm0

			// 正規化
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

			// 内積
			MOVAPS	xmm0,	vIn2

			MULPS	xmm0,	xmm1
			MOVAPS	xmm1,	xmm0
			SHUFPS	xmm0,	xmm1,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm0,	xmm1
			MOVHLPS	xmm1,	xmm0
			ADDSS	xmm0,	xmm1

			MOVSS	fDot,	xmm0
		}

		n.x = vOut[0];
		n.y = vOut[1];
		n.z = vOut[2];
		d = -fDot;
	}
	else
	{
		n.NormalizeFast( vNormal );
		d = -Pt.Dot( n );
	}
}


//-----------------------------------------------------------------------------------
/**
	@brief 平面上の３点から生成
	@author 葉迩倭

	@param vPt0		[in] 平面上の1点
	@param vPt1		[in] 平面上の1点
	@param vPt2		[in] 平面上の1点
*/
//-----------------------------------------------------------------------------------
void CPlane::FromPoint( const Math::Vector3D &vPt0, const Math::Vector3D &vPt1, const Math::Vector3D &vPt2 )
{
	if ( System::IsSupportSSE() )
	{
		SSE_ALIGN Float vIn0[] = { vPt0.x, vPt0.y, vPt0.z, 0.0f };
		SSE_ALIGN Float vIn1[] = { vPt1.x, vPt1.y, vPt1.z, 0.0f };
		SSE_ALIGN Float vIn2[] = { vPt2.x, vPt2.y, vPt2.z, 0.0f };
		SSE_ALIGN Float vOut[4];
		Float fDot;

		__asm
		{
			MOVAPS	xmm0,	vIn1
			MOVAPS	xmm1,	vIn2
			MOVAPS	xmm2,	vIn0

			MOVAPS	xmm7,	xmm2

			// 引き算
			SUBPS	xmm0,	xmm2
			SUBPS	xmm1,	xmm2

			// 外積
			MOVAPS	xmm2,	xmm0
			MOVAPS	xmm3,	xmm1
			SHUFPS	xmm2,	xmm2,	SSE_PACK(SSE_X,SSE_W,SSE_Y,SSE_Z)
			SHUFPS	xmm3,	xmm3,	SSE_PACK(SSE_X,SSE_Z,SSE_W,SSE_Y)
			MULPS	xmm2,	xmm3
			SHUFPS	xmm0,	xmm0,	SSE_PACK(SSE_X,SSE_Z,SSE_W,SSE_Y)
			SHUFPS	xmm1,	xmm1,	SSE_PACK(SSE_X,SSE_W,SSE_Y,SSE_Z)
			MULPS	xmm0,	xmm1
			SUBPS	xmm2,	xmm0

			// 正規化
			MOVAPS	xmm6,	xmm2
			MOVAPS	xmm1,	xmm2

			MULPS	xmm2,	xmm1
			MOVAPS	xmm1,	xmm2
			SHUFPS	xmm2,	xmm1,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm2,	xmm1
			MOVAPS	xmm1,	xmm2
			SHUFPS	xmm2,	xmm1,	SSE_PACK(SSE_W,SSE_Z,SSE_Y,SSE_X)
			ADDPS	xmm2,	xmm1

			RSQRTPS	xmm1,	xmm2
			MULPS	xmm2,	xmm1

			RCPPS	xmm1,	xmm2
			MULPS	xmm1,	xmm6

			MOVAPS	vOut,	xmm1

			// 内積
			MULPS	xmm7,	xmm1
			MOVAPS	xmm1,	xmm7
			SHUFPS	xmm7,	xmm1,	SSE_PACK(SSE_Y,SSE_X,SSE_W,SSE_Z)
			ADDPS	xmm7,	xmm1
			MOVHLPS	xmm1,	xmm7
			ADDSS	xmm7,	xmm1

			MOVSS	fDot,	xmm7
		}

		n.x = vOut[0];
		n.y = vOut[1];
		n.z = vOut[2];
		d = -fDot;
	}
	else
	{
		Math::Vector3D vTemp1 = vPt1 - vPt0;
		Math::Vector3D vTemp2 = vPt2 - vPt0;
		n.Cross( vTemp1, vTemp2 );
		n.NormalizeFast();
		d = -vPt0.Dot( n );
	}
}


//-----------------------------------------------------------------------------------
/**
	@brief 内積
	@author 葉迩倭

	@param Pt	[in] 任意の点
	@param w	[in] ベクトルの4要素目

	平面と任意の点の内積をとります。
*/
//-----------------------------------------------------------------------------------
Float CPlane::Dot( const Math::Vector3D &Pt ) const
{
	return n.Dot( Pt ) + d;
}

