#pragma once


/**
	@file
	@brief ３次元平面
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Vector3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
	/**
		@brief ３次元の平面
		@author 葉迩倭
	*/
	class SELENE_DLL_API CPlane
	{
	public:
		Math::Vector3D n;		///< 一般平面方程式におけるクリップ面の a b c 係数
		Float d;				///< 一般平面方程式におけるクリップ面の d 係数

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CPlane( void );

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param a	[in] 一般平面方程式におけるクリップ面の a 係数
			@param b	[in] 一般平面方程式におけるクリップ面の b 係数
			@param c	[in] 一般平面方程式におけるクリップ面の c 係数
			@param d	[in] 一般平面方程式におけるクリップ面の d 係数
		*/
		CPlane( Float a, Float b, Float c, Float d );

		/**
			@brief 法線データから生成
			@author 葉迩倭

			@param Pt		[in] 平面上の1点
			@param vNormal	[in] 平面の法線
		*/
		void FromNormal( const Math::Vector3D &Pt, const Math::Vector3D &vNormal );

		/**
			@brief 平面上の３点から生成
			@author 葉迩倭

			@param vPt0		[in] 平面上の1点
			@param vPt1		[in] 平面上の1点
			@param vPt2		[in] 平面上の1点
		*/
		void FromPoint( const Math::Vector3D &vPt0, const Math::Vector3D &vPt1, const Math::Vector3D &vPt2 );

		/**
			@brief 内積
			@author 葉迩倭

			@param Pt	[in] 任意の点

			@note
			平面と任意の点の内積をとります。
		*/
		Float Dot( const Math::Vector3D &Pt ) const;
	};
}
}

