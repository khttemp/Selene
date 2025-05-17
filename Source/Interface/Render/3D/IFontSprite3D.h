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
		@brief 3D文字描画用インターフェイス
		@author 葉迩倭

		3D文字描画を保持するためのインターフェイスです。
	*/
	class IFontSprite3D
	{
	public:
		virtual ~IFontSprite3D() {}

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
			@brief 文字列描画
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@param vPos		[in] 描画座標
			@param fSize	[in] 描画サイズ
			@param Color	[in] 描画色

			等幅フォントで文字列の描画を行います。<BR>
			生成時の書体が等幅フォントでない場合は正しく描画されない事があります。
		*/
		virtual void DrawString( const char *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color ) = 0;

		/**
			@brief 文字列描画
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@param vPos		[in] 描画座標
			@param fSize	[in] 描画サイズ
			@param Color	[in] 描画色

			プロポーショナルフォントで文字列の描画を行います。<BR>
			生成時の書体がプロポーショナルフォントでなくても正しく描画されます。
		*/
		virtual void DrawStringP( const char *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color ) = 0;

		/**
			@brief 文字列描画
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@param vPos		[in] 描画座標
			@param fSize	[in] 描画サイズ
			@param Color	[in] 描画色

			等幅フォントで文字列の描画を行います。<BR>
			生成時の書体が等幅フォントでない場合は正しく描画されない事があります。
		*/
		virtual void DrawString( const wchar_t *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color ) = 0;

		/**
			@brief 文字列描画
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@param vPos		[in] 描画座標
			@param fSize	[in] 描画サイズ
			@param Color	[in] 描画色

			プロポーショナルフォントで文字列の描画を行います。<BR>
			生成時の書体がプロポーショナルフォントでなくても正しく描画されます。
		*/
		virtual void DrawStringP( const wchar_t *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color ) = 0;
	};
}
}
}
