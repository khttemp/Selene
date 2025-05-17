#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/IRender.h"


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
		@brief 2Dプリミティブ管理インターフェイス
		@author 葉迩倭

		2Dプリミティブ描画用のインターフェイスです。
	*/
	class IPrimitive2D
	{
	public:
		virtual ~IPrimitive2D() {}

		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )																													= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Sint32 Release( void )																													= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Sint32 AddRef( void )																													= 0;

		/**
			@brief データ追加開始宣言
			@author 葉迩倭

			内部バッファへのデータの追加を行うことを通知します。<BR>
			この関数を呼ばずにPush*系の関数を呼ばないようにしてください。
		*/
		virtual void Begin( void )																														= 0;

		/**
			@brief データ追加終了宣言
			@author 葉迩倭

			内部バッファへのデータの追加を完了したことを通知します。<BR>
			この関数を呼ぶ前に必ずBegin関数を呼ぶようにしてください。
		*/
		virtual void End( void )																														= 0;

		/**
			@brief 頂点リクエスト数取得
			@author 葉迩倭
			@return リクエストした頂点数

			Pushした最大頂点数を取得します。
		*/
		virtual Sint32 GetRequestedVertexCount( void )																									= 0;

		/**
			@brief 頂点リクエスト数取得
			@author 葉迩倭
			@return リクエストした頂点数

			Pushした最大頂点数を取得します。
		*/
		virtual Sint32 GetRequestedVertexCountMax( void )																								= 0;

		/**
			@brief 内部バッファへデータ追加
			@author 葉迩倭
			@param pPrimitive	[in] プリミティブデータ
			@param Count		[in] 追加数

			内部バッファのデータの追加を行います。<BR>
			この関数を呼び出す前に必ずBeing関数でデータ追加の開始を宣言して下さい。
		*/
		virtual Bool Push( SPrimitiveVertex2D *pPrimitive, Sint32 Count )																				= 0;

		/**
			@brief レンダリング
			@author 葉迩倭

			内部バッファの内容のレンダリングを行います。
		*/
		virtual void Rendering( void )																													= 0;

		/**
			@brief 四角形描画
			@author 葉迩倭
			@param DstRect	[in] 描画矩形データ
			@param Color	[in] 描画色

			単純な四角形を描画します。
		*/
		virtual void Square( Math::Rect2DI &DstRect, CColor Color )																					= 0;

		/**
			@brief 回転付き四角形描画
			@author 葉迩倭
			@param DstRect	[in] 描画矩形データ
			@param Color	[in] 描画色
			@param Angle	[in] 1周を65536とした回転角度

			回転付きの四角形を描画します。
		*/
		virtual void SquareRotate( Math::Rect2DI &DstRect, CColor Color, Sint32 Angle )																= 0;

		/**
			@brief 多角形描画
			@author 葉迩倭
			@param Pos		[in] 中心位置
			@param fRadius	[in] 描画半径
			@param Color	[in] 描画色
			@param Num		[in] 角数

			単純な多角形を描画します。
		*/
		virtual void Polygon( Math::Point2DI Pos, Float fRadius, CColor Color, Sint32 Num )															= 0;

		/**
			@brief 回転付き多角形描画
			@author 葉迩倭
			@param Pos		[in] 中心位置
			@param fRadius	[in] 描画半径
			@param Color	[in] 描画色
			@param Num		[in] 角数
			@param Angle	[in] 1周を65536とした回転角度

			回転付き多角形を描画します。
		*/
		virtual void PolygonRotate( Math::Point2DI Pos, Float fRadius, CColor Color, Sint32 Num, Sint32 Angle )										= 0;

		/**
			@brief リング状描画
			@author 葉迩倭
			@param Pos			[in] 中心位置
			@param fInRadius	[in] 内周半径
			@param fOutRadius	[in] 外周半径
			@param InColor		[in] 内周描画色
			@param OutColor		[in] 外周描画色
			@param Num			[in] 角数

			リング状ポリゴンを描画します。
		*/
		virtual void Ring( Math::Point2DI Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num )						= 0;

		/**
			@brief 回転付きリング状描画
			@author 葉迩倭
			@param Pos			[in] 中心位置
			@param fInRadius	[in] 内周半径
			@param fOutRadius	[in] 外周半径
			@param InColor		[in] 内周描画色
			@param OutColor		[in] 外周描画色
			@param Num			[in] 角数
			@param Angle	[in] 1周を65536とした回転角度

			回転付きリング状ポリゴンを描画します。
		*/
		virtual void RingRotate( Math::Point2DI Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num, Sint32 Angle )	= 0;
	};
}
}
}
