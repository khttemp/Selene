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
		@brief 3Dライン描画用インターフェイス
		@author 葉迩倭

		3Dライン描画を保持するためのインターフェイスです。
	*/
	class ILine3D
	{
	public:
		virtual ~ILine3D() {}

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
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief 頂点データを追加
			@author 葉迩倭
			@param pLine		[in] ラインデータ
			@param LineCount	[in] ライン数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			生成時に指定した頂点フォーマットに適合した頂点データを設定してください。
		*/
		virtual Bool Push( SLineVertex3D *pLine, Sint32 LineCount ) = 0;

		/**
			@brief バウンディングボックス描画リクエスト
			@author 葉迩倭
			@param Box		[in] コリジョン用のボックス
			@param Color	[in] 色

			コリジョン用のボックスデータの描画を行います。
		*/
		virtual void PushBox( Collision::CBox &Box, CColor Color ) = 0;

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
	};
}
}
}
