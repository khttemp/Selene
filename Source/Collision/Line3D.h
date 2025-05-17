#pragma once


/**
	@file
	@brief ３次元線分
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
		@brief ３次元の線分
		@author 葉迩倭
	*/
	class SELENE_DLL_API CLine3D
	{
	public:
		Math::Vector3D vStart;				///< 線分始点位置
		Math::Vector3D vEnd;				///< 線分終点位置

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CLine3D( void );

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x0		[in] Ｘ座標
			@param y0		[in] Ｙ座標
			@param z0		[in] Ｚ座標
			@param x1		[in] Ｘ座標
			@param y1		[in] Ｙ座標
			@param z1		[in] Ｚ座標
		*/
		CLine3D( Float x0, Float y0, Float z0, Float x1, Float y1, Float z1 );

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param pt0	[in] 線分の頂点１
			@param pt1	[in] 線分の頂点２
		*/
		CLine3D( const Math::Vector3D &pt0, const Math::Vector3D &pt1 );
	};
}
}

