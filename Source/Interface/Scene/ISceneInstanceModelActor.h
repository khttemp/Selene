#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief シーンモデルアクター用インターフェイス
		@author 葉迩倭

		シーン管理されたモデルアクターを扱う為のインターフェイスです。
	*/
	class IInstanceModelActor : public IInterface
	{
	public:
		virtual ~IInstanceModelActor() {}

		/**
			@brief インスタンスモデル制御用インターフェイス取得
			@author 葉迩倭

			インスタンス登録された個々のモデルを制御するためのインターフェイスを取得します。<BR>
			ボーンやワールド変換の処理はこのインターフェイスを経由して行います。
		*/
		virtual IInstanceModelController *GetController( Sint32 Index ) = 0;

		/**
			@brief 描画リクエスト開始
			@author 葉迩倭

			IInstanceModelControllerのレンダリング処理の開始を宣言します。
			IInstanceModelControllerのRenderingRequest()はBegin-End間で呼んで下さい。
		*/
		virtual void Begin( void ) = 0;

		/**
			@brief 描画リクエスト終了
			@author 葉迩倭

			IInstanceModelControllerのレンダリング処理の終了を宣言します。
			IInstanceModelControllerのRenderingRequest()はBegin-End間で呼んで下さい。
		*/
		virtual void End( void ) = 0;
	};
}
}

