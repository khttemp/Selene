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
		@brief 3Dプリミティブ描画用インターフェイス
		@author 葉迩倭

		3Dプリミティブ描画を保持するためのインターフェイスです。
	*/
	class IPrimitive3D
	{
	public:
		virtual ~IPrimitive3D() {}

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
			@param pVtx		[in] 頂点データ
			@param Count	[in] 頂点数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			適合した頂点データを設定してください。
		*/
		virtual Bool Push( const SVertex3DBase *pVtx, Sint32 Count ) = 0;

		/**
			@brief 頂点データを追加
			@author 葉迩倭
			@param pVtx		[in] 頂点データ
			@param Count	[in] 頂点数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			適合した頂点データを設定してください。
		*/
		virtual Bool Push( const SVertex3DTexture *pVtx, Sint32 Count ) = 0;

		/**
			@brief 頂点データを追加
			@author 葉迩倭
			@param pVtx		[in] 頂点データ
			@param Count	[in] 頂点数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			適合した頂点データを設定してください。
		*/
		virtual Bool Push( const SVertex3DLight *pVtx, Sint32 Count ) = 0;

		/**
			@brief 頂点データを追加
			@author 葉迩倭
			@param pVtx		[in] 頂点データ
			@param Count	[in] 頂点数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			適合した頂点データを設定してください。
		*/
		virtual Bool Push( const SVertex3DBump *pVtx, Sint32 Count ) = 0;

		/**
			@brief 頂点データを追加
			@author 葉迩倭
			@param pVtx		[in] 頂点データ
			@param Count	[in] 頂点数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			適合した頂点データを設定してください。
		*/
		virtual Bool Push( const SVertex3DAnimation *pVtx, Sint32 Count ) = 0;

		/**
			@brief インデックスデータを追加
			@author 葉迩倭
			@param pIndex		[in] インデックスデータ
			@param IndexCount	[in] インデックス数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへインデックスデータを追加します。<BR>
			生成時に指定したインデックスフォーマットに適合したインデックスデータを設定してください。
		*/
		virtual Bool Push( const void *pIndex, Sint32 IndexCount ) = 0;

		/**
			@brief 頂点数取得
			@author 葉迩倭
			@return 追加要求をした頂点の数

			追加要求を行ったSVertex3DBase頂点の数を取得します。<BR>
			この値は実際に追加された数ではなく、Pushを行って追加された数を<BR>
			取得するので、実際に持てる最大数以上の数を返す場合があります。
		*/
		virtual Sint32 GetVertexCount( void ) = 0;

		/**
			@brief インデックス数取得
			@author 葉迩倭
			@return 追加要求をしたインデックスの数

			追加要求を行ったインデックスの数を取得します。<BR>
			この値は実際に追加された数ではなく、Pushを行って追加された数を<BR>
			取得するので、実際に持てる最大数以上の数を返す場合があります。
		*/
		virtual Sint32 GetIndexCount( void ) = 0;

		/**
			@brief データ追加開始宣言
			@author 葉迩倭
			@param IsVertex		[in] 頂点書き込み行う
			@param IsIndex		[in] インデックス書き込み行う
			@param IsDirect		[in] バッファ直接書き込み

			内部バッファへのデータの追加を行うことを通知します。<BR>
			この関数を呼ばずにPush*系の関数を呼ばないようにしてください。
		*/
		virtual void Begin( Bool IsVertex = true, Bool IsIndex = true, Bool IsDirect = true ) = 0;

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
