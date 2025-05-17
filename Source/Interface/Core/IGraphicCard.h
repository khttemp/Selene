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
	/**
		@brief ビデオカード管理インターフェイス
		@author 葉迩倭
	*/
	class IGraphicCard
	{
	public:
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
			@brief 16Bitカラーモードを使用
			@author 葉迩倭

			フルスクリーン時の画面カラーを32Bitではなく16Bitにします。<BR>
			フィルレートの厳しい環境で速度の向上が望めますが、<BR>
			マッハバンドなどの画質的な問題も出ます。
		*/
		virtual void EnableHighlColorScreen( void ) = 0;

		/**
			@brief ピクセルシェーダーがサポートされているか取得
			@author 葉迩倭
			@param Major	[in] メジャーバージョン
			@param Minor	[in] マイナーバージョン

			現在のデバイスで指定したピクセルシェーダーをサポート<BR>
			しているかどうかを取得します。
		*/
		virtual Bool GetPixelShaderSupport( Uint16 Major, Uint16 Minor ) = 0;

		/**
			@brief 画面解像度数取得
			@author 葉迩倭
			@param IsFullColor	[in] フルカラー(32Bit)の画面解像度か否か
			@return 画面解像度数

			使用可能な画面解像度の数を取得できます。<BR>
			IsFullColorフラグに応じて、16Bit/32Bitカラーの画面解像度数が取得出来ます。
		*/
		virtual Sint32 GetScreenModeCount( Bool IsFullColor ) = 0;

		/**
			@brief 画面解像度
			@author 葉迩倭
			@param IsFullColor	[in] フルカラー(32Bit)の画面解像度か否か
			@param No			[in] 画面解像度のインデックス（最大数はGetScreenModeCount()で取得）
			@param Width		[out] 画面横幅格納先
			@param Height		[out] 画面縦幅格納先

			使用可能な画面解像度を取得します。
		*/
		virtual void GetScreenMode( Bool IsFullColor, Sint32 No, Sint32 &Width, Sint32 &Height ) = 0;

		/**
			@brief レンダリングターゲットテクスチャサイズ数取得
			@author 葉迩倭
			@return レンダリングターゲットテクスチャサイズ数

			使用可能なレンダリングターゲットテクスチャサイズの数を取得できます。
		*/
		virtual Sint32 CreateRenderTargetTextureSizeCount( void ) = 0;

		/**
			@brief レンダリングターゲットテクスチャサイズ
			@author 葉迩倭
			@param No			[in] レンダリングターゲットテクスチャサイズのインデックス（最大数はCreateRenderTargetTextureSizeCount()で取得）
			@param pWidth		[out] 画面横幅格納先
			@param pHeight		[out] 画面縦幅格納先

			使用可能なレンダリングターゲットテクスチャサイズを取得します。
		*/
		virtual void CreateRenderTargetTextureSize( Sint32 No, Sint32 *pWidth, Sint32 *pHeight ) = 0;

		/**
			@brief グラフィックカード名称取得
			@author 葉迩倭
			@param pName		[out] 名称格納先
			@param NameSize		[in] pNameのバッファサイズ

			接続されているグラフィックカードの名称を取得します。
		*/
		virtual void GetGraphicCardName( char *pName, Sint32 NameSize ) = 0;

		/**
			@brief 頂点シェーダーのバージョンを取得
			@author 葉迩倭
			@param pName		[out] バージョン格納先
			@param NameSize		[in] pNameのバッファサイズ

			接続されているグラフィックカードの頂点シェーダーのバージョンを取得します。
		*/
		virtual void GetVertexShaderVersion( char *pName, Sint32 NameSize ) = 0;

		/**
			@brief ピクセルシェーダーのバージョンを取得
			@author 葉迩倭
			@param pName		[out] バージョン格納先
			@param NameSize		[in] pNameのバッファサイズ

			接続されているグラフィックカードのピクセルシェーダーのバージョンを取得します。
		*/
		virtual void GetPixelShaderVersion( char *pName, Sint32 NameSize ) = 0;

		/**
			@brief IRenderインターフェイス生成
			@author 葉迩倭
			@param IsLockEnableBackBuffer	[in] バックバッファのロック有無
			@param IsWaitVSync				[in] 画面更新時にVSYNCを待つ
			@return IRenderインターフェイス

			グラフィックカード上のレンダラー制御用のIRenderインターフェイスを取得します。<BR>
			IRenderインターフェイスは１つのIGraphicCardに対して１つしか存在しません。
		*/
		virtual Renderer::IRender *CreateRender( Bool IsLockEnableBackBuffer = false, Bool IsWaitVSync = true ) = 0;
	};
}

