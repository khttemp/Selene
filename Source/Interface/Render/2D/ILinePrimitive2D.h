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
namespace Renderer
{
namespace Object
{
	/**
		@brief 2Dラインプリミティブ管理インターフェイス
		@author 葉迩倭

		2Dライン描画用のインターフェイスです。
	*/
	class ILine2D
	{
	public:
		virtual ~ILine2D() {}
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
			@brief データ追加開始宣言
			@author 葉迩倭

			内部バッファへのデータの追加を行うことを通知します。<BR>
			この関数を呼ばずにPush*系の関数を呼ばないようにしてください。
		*/
		virtual void Begin( void ) = 0;

		/**
			@brief データ追加終了宣言
			@author 葉迩倭

			内部バッファへのデータの追加を完了したことを通知します。<BR>
			この関数を呼ぶ前に必ずBegin関数を呼ぶようにしてください。
		*/
		virtual void End( void ) = 0;

		/**
			@brief 内部バッファへデータ追加
			@author 葉迩倭
			@param pLine	[in] ラインデータ
			@param Count	[in] 追加数

			内部バッファのデータの追加を行います。<BR>
			この関数を呼び出す前に必ずBeing関数でデータ追加の開始を宣言して下さい。
		*/
		virtual Bool Push( SLineVertex2D *pLine, Sint32 Count ) = 0;

		/**
			@brief レンダリング
			@author 葉迩倭

			内部バッファの内容のレンダリングを行います。
		*/
		virtual void Rendering( void ) = 0;
	};
}
}
}
