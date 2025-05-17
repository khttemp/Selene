#pragma once


/**
	@file
	@brief コリジョン用球
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
		@brief ３次元上の球
		@author 葉迩倭
	*/
	class SELENE_DLL_API CSphere
	{
	public:
		Math::Vector3D vCenter;				///< 球の中心
		Float fRadius;						///< 球の半径

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CSphere( void );

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x		[in] Ｘ座標
			@param y		[in] Ｙ座標
			@param z		[in] Ｚ座標
			@param r		[in] 半径
		*/
		CSphere( Float x, Float y, Float z, Float r );

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param c		[in] 中心座標
			@param r		[in] 半径
		*/
		CSphere( const Math::Vector3D &c, Float r );
	};
}
}

