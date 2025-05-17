#pragma once


/**
	@file
	@brief ２次元線分
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
		@brief ２次元の線分
		@author 葉迩倭
	*/
	class SELENE_DLL_API CLine2D
	{
	public:
		Math::Vector2D vStart;				///< 線分始点位置
		Math::Vector2D vEnd;				///< 線分終点位置

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CLine2D( void );

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x0		[in] Ｘ座標
			@param y0		[in] Ｙ座標
			@param x1		[in] Ｘ座標
			@param y1		[in] Ｙ座標
		*/
		CLine2D( Float x0, Float y0, Float x1, Float y1 );

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param pt0		[in] 線分の頂点１
			@param pt1		[in] 線分の頂点２
		*/
		CLine2D( Math::Vector2D &pt0, Math::Vector2D &pt1 );
	};
}
}


