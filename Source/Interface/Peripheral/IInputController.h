#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Peripheral/IKeyboard.h"
#include "Interface/Peripheral/IJoystick.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Peripheral
{
	/**
		@brief 入力デバイス管理クラス
		@author 葉迩倭

		キーボードとパッドを統一して扱うためのインターフェイスです。
	*/
	class IInputController
	{
	public:
		virtual ~IInputController() {}

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
			@brief 入力情報更新
			@author 葉迩倭

			入力情報から最新の状態へ更新します。<BR>
			必ず１フレームに１回呼ぶようにして下さい。
		*/
		virtual void Refresh( void ) = 0;

		/**
			@brief X軸入力設定
			@author 葉迩倭
			@param Type		[in] 入力管理用の軸タイプ
			@param AxisX	[in] 適用するジョイスティックの軸
			@param AxisDirX	[in] 適用するジョイスティックの軸方向

			ジョイスティックの軸データを入力管理用のX軸へマッピングします。
		*/
		virtual void SetAxisX( eInputAxisType Type, ePadAxisType AxisX, ePadAxisDirection AxisDirX ) = 0;

		/**
			@brief Y軸入力設定
			@author 葉迩倭
			@param Type		[in] 入力管理用の軸タイプ
			@param AxisY	[in] 適用するジョイスティックの軸
			@param AxisDirY	[in] 適用するジョイスティックの軸方向

			ジョイスティックの軸データを入力管理用のY軸へマッピングします。
		*/
		virtual void SetAxisY( eInputAxisType Type, ePadAxisType AxisY, ePadAxisDirection AxisDirY ) = 0;

		/**
			@brief ボタン入力設定
			@author 葉迩倭
			@param Type		[in] 入力管理用のボタンタイプ
			@param Button	[in] 適用するジョイスティックのボタン

			ジョイスティックのボタンデータを入力管理用のボタンへマッピングします。
		*/
		virtual void SetButton( eInputButtonType Type, ePadButtonType Button ) = 0;

		/**
			@brief キーボード経由入力設定
			@author 葉迩倭
			@param Type		[in] 入力管理用のボタンタイプ
			@param Key		[in] 適用するキーボードのキー

			キーボードのキーをジョイスティックの別名として入力管理用のボタンへマッピングします。
		*/
		virtual void SetAlias( eInputButtonType Type, eVirtualKeyCode Key ) = 0;

		/**
			@brief どれか１つでもボタンが押されているかチェック
			@author 葉迩倭
			@retval false	ボタンは１つも押されていない
			@retval true	ボタンは１つ以上押されている

			なんらかのボタンが押されているかどうかをチェックします。
		*/
		virtual Bool IsPushAnyKey( void ) = 0;

		/**
			@brief ボタンの状態を初期化
			@author 葉迩倭

			すべてのステートをOFF状態にします。
		*/
		virtual void ClearState( void ) = 0;

		/**
			@brief ボタンの状態を取得
			@author 葉迩倭
			@param PadState	[in] 取得する状態
			@param Type		[in] 取得するボタン
			@retval false	ボタンは条件を満たしていない
			@retval true	ボタンは条件を満たしている

			ボタンTypeが状態PadStateのときにtrueが返ります。<BR>
			キーリピートを設定している場合は、指定間隔毎にBUTTON_STATE_PUSH<BR>
			状態に自動的になります。
		*/
		virtual Bool GetState( eInputButtonState PadState, eInputButtonType Type ) = 0;

		/**
			@brief ボタンの状態を設定
			@author 葉迩倭
			@param PadState	[in] 設定する状態
			@param Type		[in] 設定するボタン

			ボタンTypeを状態PadStateに設定します。<BR>
			外部からキーを操作し、自動進行などを行わせることが可能です。
		*/
		virtual void SetState( eInputButtonState PadState, eInputButtonType Type ) = 0;

		/**
			@brief カーソル上下移動
			@author 葉迩倭
			@param AxisNo		[in] 使用する軸番号
			@param Cursor		[in,out] カーソル
			@param Max			[in] カーソルのとりうる最大値
			@retval BUTTON_DISABLE			ボタンは押されていない
			@retval BUTTON_DISABLE以外		ボタンは上or下が押されている

			指定した軸に対してカーソルを上下に動かします。<BR>
			またこの時にカーソルはリピートされます。
		*/
		virtual eInputButtonType CursorRepeatUpDown( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max ) = 0;

		/**
			@brief カーソル左右移動
			@author 葉迩倭
			@param AxisNo		[in] 使用する軸番号
			@param Cursor		[in,out] カーソル
			@param Max			[in] カーソルのとりうる最大値
			@retval BUTTON_DISABLE			ボタンは押されていない
			@retval BUTTON_DISABLE以外		ボタンは左or右が押されている

			指定した軸に対してカーソルを左右に動かします。<BR>
			またこの時にカーソルはリピートされます。
		*/
		virtual eInputButtonType CursorRepeatLeftRight( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max ) = 0;

		/**
			@brief カーソル上下移動
			@author 葉迩倭
			@param AxisNo		[in] 使用する軸番号
			@param Cursor		[in,out] カーソル
			@param Max			[in] カーソルのとりうる最大値
			@retval BUTTON_DISABLE			ボタンは押されていない
			@retval BUTTON_DISABLE以外		ボタンは上or下が押されている

			指定した軸に対してカーソルを上下に動かします。<BR>
			またこの時にカーソルはクランプされます。
		*/
		virtual eInputButtonType CursorClampUpDown( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max ) = 0;

		/**
			@brief カーソル左右移動
			@author 葉迩倭
			@param AxisNo		[in] 使用する軸番号
			@param Cursor		[in,out] カーソル
			@param Max			[in] カーソルのとりうる最大値
			@retval BUTTON_DISABLE			ボタンは押されていない
			@retval BUTTON_DISABLE以外		ボタンは左or右が押されている

			指定した軸に対してカーソルを左右に動かします。<BR>
			またこの時にカーソルはクランプされます。
		*/
		virtual eInputButtonType CursorClampLeftRight( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max ) = 0;
	};
}
}

