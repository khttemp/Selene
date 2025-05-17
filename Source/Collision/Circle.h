#pragma once


/**
	@file
	@brief ２次元円
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Vector2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
	/**
		@brief ２次元上の円
		@author 葉迩倭
	*/
	class SELENE_DLL_API CCircle
	{
	public:
		Math::Vector2D vCenter;			///< 円の中心
		Float fRadius;					///< 円の半径

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CCircle( void );

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x		[in] Ｘ座標
			@param y		[in] Ｙ座標
			@param r		[in] 半径
		*/
		CCircle( Float x, Float y, Float r );

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param c		[in] 中心座標
			@param r		[in] 半径
		*/
		CCircle( Math::Vector2D &c, Float r );
	};
}
}

