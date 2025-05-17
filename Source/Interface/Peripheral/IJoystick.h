#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Peripheral
{
	/**
		@brief ジョイスティック管理インターフェイス
		@author 葉迩倭

		ジョイスティックを扱うためのインターフェイスです。
	*/
	class IJoystick
	{
	public:
		virtual ~IJoystick() {}

		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Sint32 AddRef( void ) = 0;

		/**
			@brief 軸情報を取得
			@author 葉迩倭
			@param Type		[in] 軸の種類
			@param Dir		[in] 軸の方向
			@return 軸の現在値

			指定された種類、方向の軸の状態を取得します。<BR>
			アナログスティックの場合は-4096～+4096の値が返り、<BR>
			デジタルスティックの場合は-4096か+4096の値が返ります。
		*/
		virtual Sint32 GetAxis( ePadAxisType Type, ePadAxisDirection Dir ) = 0;

		/**
			@brief スライダー情報を取得
			@author 葉迩倭
			@param Type		[in] スライダーのタイプ
			@return スライダーの現在値

			指定された種類のスライダーの状態を取得します。<BR>
			-4096～+4096の値が返ります。
		*/
		virtual Sint32 GetSlider( ePadSliderType Type ) = 0;

		/**
			@brief ボタン情報を取得
			@author 葉迩倭
			@param Type		[in] ボタンのタイプ
			@retval false	押されてない
			@retval true	押されている

			指定された種類のボタンの状態を取得します。
		*/
		virtual Bool GetButton( ePadButtonType Type ) = 0;
	};
}
}

