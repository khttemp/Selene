#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/2D/IPrimitive2D.h"


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
		@brief DrawList用構造体
		@author 葉迩倭

		@note
		DrawListで利用する構造体です。
	*/
	struct SSpriteListData2D
	{
		Math::Vector2D Pos;
		Float Width;
		Sint32 Angle;
		CColor Color;
	};

	/**
		@brief 2Dスプライト管理インターフェイス
		@author 葉迩倭

		2Dスプライト描画用のインターフェイスです。
	*/
	class ISprite2D
	{
	public:
		virtual ~ISprite2D() {}

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
			@brief レンダリング
			@author 葉迩倭

			内部バッファの内容のレンダリングを行います。
		*/
		virtual void Rendering( void ) = 0;

		/**
			@brief 頂点リクエスト数取得
			@author 葉迩倭
			@return リクエストした頂点数

			Pushした最大頂点数を取得します。
		*/
		virtual Sint32 GetRequestedVertexCount( void ) = 0;

		/**
			@brief 頂点リクエスト数取得
			@author 葉迩倭
			@return リクエストした頂点数

			Pushした最大頂点数を取得します。
		*/
		virtual Sint32 GetRequestedVertexCountMax( void ) = 0;

		/**
			@brief 内部バッファへデータ追加
			@author 葉迩倭
			@param pPrimitive	[in] プリミティブデータ
			@param Count		[in] 追加数

			内部バッファのデータの追加を行います。<BR>
			この関数を呼び出す前に必ずBeing関数でデータ追加の開始を宣言して下さい。
		*/
		virtual Bool Push( SPrimitiveVertex2D *pPrimitive, Sint32 Count ) = 0;

		/**
			@brief 装飾用テクスチャの設定
			@author 葉迩倭

			@param pTex		[in] テクスチャインターフェイス

			装飾用のテクスチャを設定します。
		*/
		virtual void SetDecoration( ITexture *pTex ) = 0;

		/**
			@brief 四角形描画
			@author 葉迩倭

			@param DstRect		[in] 転送先スクリーンの矩形
			@param SrcRect		[in] 転送元テクスチャの矩形
			@param Color		[in] 頂点色

			最も単純なスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawSquare( Math::Rect2DF &DstRect, Math::Rect2DF &SrcRect, CColor Color ) = 0;

		/**
			@brief 回転付き四角形描画
			@author 葉迩倭

			@param DstRect		[in] 転送先スクリーンの矩形
			@param SrcRect		[in] 転送元テクスチャの矩形
			@param Color		[in] 頂点色
			@param Angle		[in] 1周65536とした回転角度

			回転付きスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawSquareRotate( Math::Rect2DF &DstRect, Math::Rect2DF &SrcRect, CColor Color, Sint32 Angle ) = 0;

		/**
			@brief 回転付き四角形描画
			@author 葉迩倭

			@param DstRect		[in] 転送先スクリーンの矩形
			@param SrcRect		[in] 転送元テクスチャの矩形
			@param Color		[in] 頂点色
			@param AngleX		[in] 1周65536とした回転角度
			@param AngleY		[in] 1周65536とした回転角度
			@param AngleZ		[in] 1周65536とした回転角度

			回転付きスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawSquareRotateXYZ( Math::Rect2DF &DstRect, Math::Rect2DF &SrcRect, CColor Color, Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ ) = 0;

		/**
			@brief 行列変換四角形描画
			@author 葉迩倭

			@param mWorld		[in] 変換行列
			@param SrcRect		[in] 転送元テクスチャの矩形
			@param Color		[in] 頂点色

			行列変換付きスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawSquareMatrix( Math::Matrix &mWorld, Math::Rect2DF &SrcRect, CColor Color ) = 0;

		/**
			@brief 帯状四角形描画
			@author 葉迩倭

			@param Pos		[in] 描画位置の配列
			@param Angle	[in] 1周65536とした回転角度の配列
			@param Color	[in] 描画色の配列
			@param Count	[in] 各要素の配列数
			@param Width	[in] 頂点ごとの幅
			@param Src		[in] 転送元テクスチャの矩形

			帯状に連結したスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawList( Math::Point2DF Pos[], Sint32 Angle[], CColor Color[], Sint32 Count, Float Width, Math::Rect2DF &Src ) = 0;

		/**
			@brief 帯状四角形描画
			@author 葉迩倭

			@param Pos		[in] 描画位置の配列
			@param Width	[in] 頂点ごとの幅の配列
			@param Angle	[in] 1周65536とした回転角度の配列
			@param Color	[in] 描画色の配列
			@param Count	[in] 各要素の配列数
			@param Src		[in] 転送元テクスチャの矩形

			帯状に連結したスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawList( Math::Point2DF Pos[], Float Width[], Sint32 Angle[], CColor Color[], Sint32 Count, Math::Rect2DF &Src ) = 0;

		/**
			@brief 帯状四角形描画
			@author 葉迩倭

			@param Pos		[in] 描画位置の配列
			@param List		[in] リスト情報の配列
			@param Count	[in] 各要素の配列数
			@param Src		[in] 転送元テクスチャの矩形

			帯状に連結したスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawList( SSpriteListData2D List[], Sint32 Count, Math::Rect2DF &Src ) = 0;

		/**
			@brief 放射状フェード
			@author 葉迩倭

			@param SrcRect		[in] 転送元テクスチャの矩形
			@param Divide		[in] 円周のポリゴンの分割数
			@param Side			[in] １辺あたりのポリゴンの分割数
			@param Alpha		[in] 透明度

			中心に向かってフェードするエフェクトです。<BR>
			画面の切り替え時などに利用できると思います。
		*/
		virtual void CircleFade( Math::Rect2DF &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha ) = 0;

		/**
			@brief 円状回転フェード
			@author 葉迩倭

			@param SrcRect		[in] 転送元テクスチャの矩形
			@param Divide		[in] 円周のポリゴンの分割数
			@param Side			[in] １辺あたりのポリゴンの分割数
			@param Alpha		[in] 透明度

			時計回りにフェードするエフェクトです。<BR>
			画面の切り替え時などに利用できると思います。
		*/
		virtual void CircleRoundFade( Math::Rect2DF &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha ) = 0;
	};
}
}
}
