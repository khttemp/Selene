#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Math.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Peripheral
{
	/**
		@brief マウス管理インターフェイス
		@author 葉迩倭

		マウスを扱うためのインターフェイスです。
	*/
	class IMouse
	{
	public:
		virtual ~IMouse() {}

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
			@brief マウスのX座標取得
			@author 葉迩倭
			@return X座標

			マウスポインターのスクリーン座標上のX座標を取得します。
		*/
		virtual Sint32 GetPosX( void ) = 0;

		/**
			@brief マウスのY座標取得
			@author 葉迩倭
			@return Y座標

			マウスポインターのスクリーン座標上のY座標を取得します。
		*/
		virtual Sint32 GetPosY( void ) = 0;

		/**
			@brief マウスのホイール回転量取得
			@author 葉迩倭
			@return ホイール回転量

			マウスホイールの回転量を取得します。
		*/
		virtual Sint32 GetPosW( void ) = 0;

		/**
			@brief マウスのX移動量取得
			@author 葉迩倭
			@return X移動量

			マウスポインターのスクリーン上のX移動量を取得します。
		*/
		virtual Sint32 GetMoveX( void ) = 0;

		/**
			@brief マウスのY移動量取得
			@author 葉迩倭
			@return Y移動量

			マウスポインターのスクリーン上のY移動量を取得します。
		*/
		virtual Sint32 GetMoveY( void ) = 0;

		/**
			@brief マウスのホイール移動量取得
			@author 葉迩倭
			@return ホイール移動量

			マウスポインターのホイール移動量を取得します。
		*/
		virtual Sint32 GetMoveW( void ) = 0;

		/**
			@brief マウスの左クリック状態取得
			@author 葉迩倭
			@retval false	左ボタンは押されていない
			@retval true	左ボタンは押されている

			マウスの左ボタンの状態を取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual Bool GetClickL( void ) = 0;

		/**
			@brief マウスの右クリック状態取得
			@author 葉迩倭
			@retval false	右ボタンは押されていない
			@retval true	右ボタンは押されている

			マウスの右ボタンの状態を取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual Bool GetClickR( void ) = 0;

		/**
			@brief マウスのホイールクリック状態取得
			@author 葉迩倭
			@retval false	ホイールボタンは押されていない
			@retval true	ホイールボタンは押されている

			マウスのホイールボタンの状態を取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual Bool GetClickW( void ) = 0;

		/**
			@brief マウスの左ダブルクリック状態取得
			@author 葉迩倭
			@retval false	左ボタンはダブルクリックされていない
			@retval true	左ボタンはダブルクリックされた

			マウスの左ボタンがダブルクリックされたかを取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual Bool GetDoubleClickL( void ) = 0;

		/**
			@brief マウスの右ダブルクリック状態取得
			@author 葉迩倭
			@retval false	右ボタンはダブルクリックされていない
			@retval true	右ボタンはダブルクリックされた

			マウスの右ボタンがダブルクリックされたかを取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual Bool GetDoubleClickR( void ) = 0;

		/**
			@brief マウスのホイールダブルクリック状態取得
			@author 葉迩倭
			@retval false	ホイールボタンはダブルクリックされていない
			@retval true	ホイールボタンはダブルクリックされた

			マウスのホイールボタンがダブルクリックされたかを取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual Bool GetDoubleClickW( void ) = 0;

		/**
			@brief マウスの左ボタン状態取得
			@author 葉迩倭
			@return		左ボタンの状態

			マウスの左ボタンの詳細な情報を取得します。
		*/
		virtual eMouseState GetStateL( void ) = 0;

		/**
			@brief マウスの右ボタン状態取得
			@author 葉迩倭
			@return		右ボタンの状態

			マウスの右ボタンの詳細な情報を取得します。
		*/
		virtual eMouseState	GetStateR( void ) = 0;

		/**
			@brief マウスのホイールボタン状態取得
			@author 葉迩倭
			@return		ホイールボタンの状態

			マウスのホイールボタンの詳細な情報を取得します。
		*/
		virtual eMouseState	GetStateW( void ) = 0;

		/**
			@brief マウスの位置を設定
			@author 葉迩倭
			@param Pos	[in] スクリーン座標

			マウスの位置を任意の場所に設定します。
		*/
		virtual void SetPosition( Math::Point2DI &Pos ) = 0;
	};
}
}

