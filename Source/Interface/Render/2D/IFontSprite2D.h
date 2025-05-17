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
		@brief フォントスプライト管理インターフェイス
		@author 葉迩倭

		2Dフォント描画用のインターフェイスです。
	*/
	class IFontSprite2D
	{
	public:
		virtual ~IFontSprite2D() {}

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
			@param Space	[in] 行間補正値

			内部バッファへのデータの追加を行うことを通知します。<BR>
			この関数を呼ばずにPush*系の関数を呼ばないようにしてください。
		*/
		virtual void Begin( Sint32 Space = 0 ) = 0;

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
			@brief 装飾用テクスチャの設定
			@author 葉迩倭

			@param pTex		[in] テクスチャインターフェイス

			装飾用のテクスチャを設定します。
		*/
		virtual void SetDecoration( ITexture *pTex ) = 0;

		/**
			@brief サイズ取得
			@author 葉迩倭

			文字サイズを取得
		*/
		virtual Sint32 GetSize( void ) = 0;

		/**
			@brief 文字列描画
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@param Pos		[in] 描画座標
			@param Color	[in] 描画色
			@param Length	[in] 描画文字数(-1で全て)

			等幅フォントで文字列の描画を行います。<BR>
			生成時の書体が等幅フォントでない場合は正しく描画されない事があります。
		*/
		virtual void DrawString( const char *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length = -1 ) = 0;

		/**
			@brief 文字列描画
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@param Pos		[in] 描画座標
			@param Color	[in] 描画色
			@param Length	[in] 描画文字数(-1で全て)

			プロポーショナルフォントで文字列の描画を行います。<BR>
			生成時の書体がプロポーショナルフォントでなくても正しく描画されます。
		*/
		virtual void DrawStringP( const char *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length = -1 ) = 0;

		/**
			@brief 文字描画
			@author 葉迩倭
			@param pChara	[in] 描画文字
			@param Dst		[in] 描画矩形
			@param Color	[in] 描画色

			指定位置に文字を描画します。<BR>
			この関数では文字の拡大縮小をサポートします。
		*/
		virtual Sint32 DrawChara( const char *pChara, Math::Rect2DF &Dst, CColor Color ) = 0;

		/**
			@brief 回転付き文字描画
			@author 葉迩倭
			@param pChara	[in] 描画文字
			@param Dst		[in] 描画矩形
			@param Color	[in] 描画色
			@param Angle	[in] 1周を65536とした回転角度

			指定位置に文字を回転付きで描画します。<BR>
			この関数では文字の拡大縮小をサポートします。
		*/
		virtual Sint32 DrawCharaRotate( const char *pChara, Math::Rect2DF &Dst, CColor Color, Sint32 Angle ) = 0;

		/**
			@brief 文字列描画完了位置取得
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@param Pos		[in] 描画座標
			@param Length	[in] 描画文字数(-1で全て)
			@return		描画完了時の座標

			等幅フォントで文字列の描画を行った場合の最終的な描画終了位置を取得します。<BR>
			改行が含まれる場合は改行を考慮した最終位置を返すので、<BR>
			文字列の最大幅を取得したい場合は注意してください。
		*/
		virtual Math::Point2DF GetStringLastPos( const char *pStr, Math::Point2DF Pos, Sint32 Length = -1 ) = 0;

		/**
			@brief 文字列描画完了位置取得
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@param Pos		[in] 描画座標
			@param Length	[in] 描画文字数(-1で全て)
			@return		描画完了時の座標

			プロポーショナルフォントで文字列の描画を行った場合の最終的な描画終了位置を取得します。<BR>
			改行が含まれる場合は改行を考慮した最終位置を返すので、<BR>
			文字列の最大幅を取得したい場合は注意してください。
		*/
		virtual Math::Point2DF GetStringLastPosP( const char *pStr, Math::Point2DF Pos, Sint32 Length = -1 ) = 0;

		/**
			@brief 文字列描画サイズ取得
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@return		描画サイズ

			等幅フォントで文字列の描画を行った場合の縦横のサイズを取得します。<BR>
			改行が含まれる場合でも最大の横幅を取得できます。
		*/
		virtual Math::Point2DF GetStringSize( const char *pStr ) = 0;

		/**
			@brief 文字列描画サイズ取得
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@return		描画サイズ

			プロポーショナルフォントで文字列の描画を行った場合の縦横のサイズを取得します。<BR>
			改行が含まれる場合でも最大の横幅を取得できます。
		*/
		virtual Math::Point2DF GetStringSizeP( const char *pStr ) = 0;

		/**
			@brief 文字列描画
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@param Pos		[in] 描画座標
			@param Color	[in] 描画色
			@param Length	[in] 描画文字数(-1で全て)

			等幅フォントで文字列の描画を行います。<BR>
			生成時の書体が等幅フォントでない場合は正しく描画されない事があります。
		*/
		virtual void DrawString( const wchar_t *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length = -1 ) = 0;

		/**
			@brief 文字列描画
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@param Pos		[in] 描画座標
			@param Color	[in] 描画色
			@param Length	[in] 描画文字数(-1で全て)

			プロポーショナルフォントで文字列の描画を行います。<BR>
			生成時の書体がプロポーショナルフォントでなくても正しく描画されます。
		*/
		virtual void DrawStringP( const wchar_t *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length = -1 ) = 0;

		/**
			@brief 文字描画
			@author 葉迩倭
			@param pChara	[in] 描画文字
			@param Dst		[in] 描画矩形
			@param Color	[in] 描画色

			指定位置に文字を描画します。<BR>
			この関数では文字の拡大縮小をサポートします。
		*/
		virtual Sint32 DrawChara( const wchar_t *pChara, Math::Rect2DF &Dst, CColor Color ) = 0;

		/**
			@brief 回転付き文字描画
			@author 葉迩倭
			@param pChara	[in] 描画文字
			@param Dst		[in] 描画矩形
			@param Color	[in] 描画色
			@param Angle	[in] 1周を65536とした回転角度

			指定位置に文字を回転付きで描画します。<BR>
			この関数では文字の拡大縮小をサポートします。
		*/
		virtual Sint32 DrawCharaRotate( const wchar_t *pChara, Math::Rect2DF &Dst, CColor Color, Sint32 Angle ) = 0;

		/**
			@brief 文字列描画完了位置取得
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@param Pos		[in] 描画座標
			@param Length	[in] 描画文字数(-1で全て)
			@return		描画完了時の座標

			等幅フォントで文字列の描画を行った場合の最終的な描画終了位置を取得します。<BR>
			改行が含まれる場合は改行を考慮した最終位置を返すので、<BR>
			文字列の最大幅を取得したい場合は注意してください。
		*/
		virtual Math::Point2DF GetStringLastPos( const wchar_t *pStr, Math::Point2DF Pos, Sint32 Length = -1 ) = 0;

		/**
			@brief 文字列描画完了位置取得
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@param Pos		[in] 描画座標
			@param Length	[in] 描画文字数(-1で全て)
			@return		描画完了時の座標

			プロポーショナルフォントで文字列の描画を行った場合の最終的な描画終了位置を取得します。<BR>
			改行が含まれる場合は改行を考慮した最終位置を返すので、<BR>
			文字列の最大幅を取得したい場合は注意してください。
		*/
		virtual Math::Point2DF GetStringLastPosP( const wchar_t *pStr, Math::Point2DF Pos, Sint32 Length = -1 ) = 0;

		/**
			@brief 文字列描画サイズ取得
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@return		描画サイズ

			等幅フォントで文字列の描画を行った場合の縦横のサイズを取得します。<BR>
			改行が含まれる場合でも最大の横幅を取得できます。
		*/
		virtual Math::Point2DF GetStringSize( const wchar_t *pStr ) = 0;

		/**
			@brief 文字列描画サイズ取得
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@return		描画サイズ

			プロポーショナルフォントで文字列の描画を行った場合の縦横のサイズを取得します。<BR>
			改行が含まれる場合でも最大の横幅を取得できます。
		*/
		virtual Math::Point2DF GetStringSizeP( const wchar_t *pStr ) = 0;
	};
}
}
}
