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
		@brief DrawList用構造体
		@author 葉迩倭

		@note
		DrawListで利用する構造体です。
	*/
	struct SSpriteListData3D
	{
		Math::Vector3D Pos;
		Float Width;
		Sint32 Angle;
		CColor Color;
	};

	/**
		@brief 3Dスプライト描画用インターフェイス
		@author 葉迩倭

		3Dスプライト描画を保持するためのインターフェイスです。
	*/
	class ISprite3D
	{
	public:
		virtual ~ISprite3D() {}

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
			@brief 描画リクエスト
			@author 葉迩倭
			@param mWorld		[in] ワールドの変換行列
			@param Size			[in] 描画サイズ
			@param SrcRect		[in] テクスチャ矩形
			@param Color		[in] 色

			内部バッファへのデータの追加を行います。<BR>
			Sizeで指定した大きさの四角形ポリゴンをmWorldで変換します。
		*/
		virtual void Draw( const Math::Matrix &mWorld, const Math::Point2DF &Size, const Math::Rect2DI &SrcRect, CColor Color ) = 0;

		/**
			@brief 描画リクエスト
			@author 葉迩倭
			@param mWorld		[in] ワールドの変換行列
			@param PtTbl		[in] 描画用４頂点（左上－右上－左下－右下）
			@param SrcRect		[in] テクスチャ矩形
			@param Color		[in] 色

			内部バッファへのデータの追加を行います。<BR>
			vPositionを基準位置としてPtTblで指定した大きさの矩形を作りmWorldで変換します。
		*/
		virtual void Draw( const Math::Matrix &mWorld, const Math::Vector2D PtTbl[], const Math::Rect2DI &SrcRect, CColor Color ) = 0;

		/**
			@brief 帯状四角形描画
			@author 葉迩倭

			@param vCameraPosition	[in] カメラの位置
			@param Pos				[in] 描画位置の配列
			@param Color			[in] 描画色の配列
			@param Count			[in] 各要素の配列数
			@param Width			[in] 頂点ごとの幅
			@param Src				[in] 転送元テクスチャの矩形

			カメラの位置に応じて自動回転処理が行われた<BR>
			帯状に連結したスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawPolyLine( const Math::Vector3D &vCameraPosition, const Math::Vector3D Pos[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src ) = 0;

		/**
			@brief 帯状四角形描画
			@author 葉迩倭

			@param vCameraPosition	[in] カメラの位置
			@param Pos				[in] 描画位置の配列
			@param Color			[in] 描画色の配列
			@param Width			[in] 頂点ごとの幅
			@param Count			[in] 各要素の配列数
			@param Src				[in] 転送元テクスチャの矩形

			カメラの位置に応じて自動回転処理が行われた<BR>
			帯状に連結したスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawPolyLine( const Math::Vector3D &vCameraPosition, const Math::Vector3D Pos[], const CColor Color[], const Float Width[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

		/**
			@brief 帯状四角形描画
			@author 葉迩倭

			@param vCameraPosition	[in] カメラの位置
			@param List				[in] 頂点ごとの配列
			@param Count			[in] 各要素の配列数
			@param Src				[in] 転送元テクスチャの矩形

			カメラの位置に応じて自動回転処理が行われた<BR>
			帯状に連結したスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawPolyLine( const Math::Vector3D &vCameraPosition, const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

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
		virtual void DrawListXY( const Math::Vector3D Pos[], const Sint32 Angle[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src ) = 0;

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
		virtual void DrawListYZ( const Math::Vector3D Pos[], const Sint32 Angle[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src ) = 0;

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
		virtual void DrawListZX( const Math::Vector3D Pos[], const Sint32 Angle[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src ) = 0;

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
		virtual void DrawListXY( const Math::Vector3D Pos[], const Float Width[], const Sint32 Angle[], const CColor Color[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

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
		virtual void DrawListYZ( const Math::Vector3D Pos[], const Float Width[], const Sint32 Angle[], const CColor Color[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

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
		virtual void DrawListZX( const Math::Vector3D Pos[], const Float Width[], const Sint32 Angle[], const CColor Color[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

		/**
			@brief 帯状四角形描画
			@author 葉迩倭

			@param List		[in] 頂点ごとの配列
			@param Count	[in] 各要素の配列数
			@param Src		[in] 転送元テクスチャの矩形

			帯状に連結したスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawListXY( const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

		/**
			@brief 帯状四角形描画
			@author 葉迩倭

			@param List		[in] 頂点ごとの配列
			@param Count	[in] 各要素の配列数
			@param Src		[in] 転送元テクスチャの矩形

			帯状に連結したスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawListYZ( const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

		/**
			@brief 帯状四角形描画
			@author 葉迩倭

			@param List		[in] 頂点ごとの配列
			@param Count	[in] 各要素の配列数
			@param Src		[in] 転送元テクスチャの矩形

			帯状に連結したスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawListZX( const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src ) = 0;
	};
}
}
}
