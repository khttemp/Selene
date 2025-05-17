#pragma once


/**
	@file
	@brief 疑似乱数
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Math
{
	/**
		@brief 乱数処理クラス
		@author 葉迩倭
	*/
	class SELENE_DLL_API CRandom
	{
		enum { N = 624UL };

	private:
		Sint32 m_MersenneTwister[N];		///< 乱数生成用ワーク
		Sint32 m_MersenneTwisterCount;		///< 乱数生成用ワーク

	private:
		/**
			@brief 擬似乱数生成
			@author 葉迩倭
			@return 乱数値

			@note
			32Bit整数の擬似乱数を生成します。
		*/
		virtual Sint32 GenerateInt32( void );

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CRandom();

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CRandom( Sint32 Param );

		/**
			@brief 乱数用種設定
			@author 葉迩倭
			@param Param	[in] シード値

			@note
			乱数生成の種を設定します。
		*/
		virtual void Seed( Sint32 Param );

		/**
			@brief 32Bit整数乱数取得
			@author 葉迩倭
			@return 乱数値

			@note
			32Bit整数の乱数値を取得します。
		*/
		virtual Sint32 GetInt32( void );

		/**
			@brief 64Bit整数乱数取得
			@author 葉迩倭
			@return 乱数値

			@note
			64Bit整数の乱数値を取得します。
		*/
		virtual Uint64 GetInt64( void );

		/**
			@brief 32Bit浮動小数乱数取得
			@author 葉迩倭
			@return 乱数値

			@note
			32Bit浮動小数の乱数値を取得します。
		*/
		virtual Float GetFloat32( void );

		/**
			@brief 指定範囲乱数取得
			@author 葉迩倭
			@param Min [in] 最小値
			@param Max [in] 最大値
			@return 乱数値

			@note
			指定範囲内の整数乱数を取得します。
		*/
		virtual Sint32 GetInt( Sint32 Min, Sint32 Max );

		/**
			@brief 指定範囲乱数取得
			@author 葉迩倭
			@param Min [in] 最小値
			@param Max [in] 最大値
			@return 乱数値

			@note
			指定範囲内の浮動小数乱数を取得します。
		*/
		virtual Float GetFloat( Float Min, Float Max );
	};
}
}

