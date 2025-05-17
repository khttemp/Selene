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
		@brief キーボード管理インターフェイス
		@author 葉迩倭

		キーボードを扱うためのインターフェイスです。
	*/
	class IKeyboard
	{
	public:
		virtual ~IKeyboard() {}

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
			@brief キー入力バッファフラッシュ
			@author 葉迩倭

			キー入力バッファに蓄積した入力バッファをクリアします。
		*/
		virtual void ClearKeyBuffer( void ) = 0;

		/**
			@brief キー入力バッファからデータ取得
			@author 葉迩倭
			@return 入力されたキーのキーコード

			キー入力バッファに蓄積されたデータを取り出します。<BR>
			押されたキーを全て取り出す時はwhile()文等で処理してください。
		*/
		virtual eVirtualKeyCode GetKeyBuffer( void ) = 0;

		/**
			@brief キーが押されているかチェックする
			@author 葉迩倭
			@retval false	押されていない
			@retval true	押されている

			指定されたキーが現在押されているかチェックします。<BR>
			純粋にキーのON/OFFのみ取得できます。
		*/
		virtual Bool GetKeyData( eVirtualKeyCode Key ) = 0;
	};
}
}

