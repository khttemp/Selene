#pragma once


/**
	@file
	@brief テクスチャインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Math.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	/**
		@brief 深度バッファタイプ
		@author 葉迩倭
	*/
	enum eDepthBufferType
	{
		DEPTH_BUFFER_SURFACE,			///< 深度バッファはサーフェイス
		DEPTH_BUFFER_TEXTURE_NVIDIA,	///< 深度バッファはテクスチャ（NVIDIA仕様）
		DEPTH_BUFFER_TEXTURE_ATI,		///< 深度バッファはテクスチャ（ATI仕様）
	};

	/**
		@brief テクスチャタイプ
		@author 葉迩倭
	*/
	enum eTextureType
	{
		TEXTURE_TYPE_DEFAULT,		///< 通常の描画用テクスチャ
		TEXTURE_TYPE_TARGET,		///< 描画ターゲット用テクスチャ
		TEXTURE_TYPE_DEPTH,			///< 深度バッファ用テクスチャ
		TEXTURE_TYPE_NONE,			///< 特になし
	};

	/**
		@brief テクスチャインターフェイス
		@author 葉迩倭

		@note
		テクスチャを操作するためのインターフェイスです。<BR>
		IRenderインターフェイスから取得できます。
	*/
	class ITexture : public IInterface
	{
	public:
		virtual ~ITexture() {}

/**
@brief 画像ファイルとして保存
@author 葉迩倭
@param pFileName	[in] テクスチャファイル名
@retval false	失敗
@retval true	成功

@note
テクスチャの内容をTGA画像ファイルとして保存します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;
  IGraphicCard *pGraphicCard = NULL;
  IRender      *pRender      = NULL;
  ITexture     *pTex         = NULL;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // ビデオカード初期化
    IGraphicCard *pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
    if ( pGraphicCard == NULL ) goto EXIT;      // IGraphicCardにはNullDeviceがないので失敗するとNULLが返る

    // レンダラーの生成
    IRender *pRender = pGraphicCard->CreateRender();
    if ( pRender == NULL ) goto EXIT;           // IRenderにはNullDeviceがないので失敗するとNULLが返る

    // テクスチャの生成
    pTex = pRender->CreateTextureFromFile( "sample.bmp" );

    // テクスチャを画像として保存
    pTex->SaveToTGA( "hogehoge.tga" );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

EXIT:
  SAFE_RELEASE( pTex );                // テクスチャの解放
  SAFE_RELEASE( pRender );             // レンダラーの解放
  SAFE_RELEASE( pGraphicCard );        // ビデオカードの解放
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
		virtual Bool SaveToTGA( const char *pFileName ) = 0;

/**
@brief 画像ファイルとして保存
@author 葉迩倭
@param pFileName	[in] テクスチャファイル名
@retval false	失敗
@retval true	成功

@note
テクスチャの内容をPNG画像ファイルとして保存します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;
  IGraphicCard *pGraphicCard = NULL;
  IRender      *pRender      = NULL;
  ITexture     *pTex         = NULL;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // ビデオカード初期化
    IGraphicCard *pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
    if ( pGraphicCard == NULL ) goto EXIT;      // IGraphicCardにはNullDeviceがないので失敗するとNULLが返る

    // レンダラーの生成
    IRender *pRender = pGraphicCard->CreateRender();
    if ( pRender == NULL ) goto EXIT;           // IRenderにはNullDeviceがないので失敗するとNULLが返る

    // テクスチャの生成
    pTex = pRender->CreateTextureFromFile( "sample.bmp" );

    // テクスチャを画像として保存
    pTex->SaveToPNG( "hogehoge.png" );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

EXIT:
  SAFE_RELEASE( pTex );                // テクスチャの解放
  SAFE_RELEASE( pRender );             // レンダラーの解放
  SAFE_RELEASE( pGraphicCard );        // ビデオカードの解放
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
		virtual Bool SaveToPNG( const char *pFileName ) = 0;

/**
@brief 実テクスチャサイズ取得
@author 葉迩倭
@return テクスチャの実サイズ

@note
テクスチャのサイズを取得します。<BR>
２の累乗でないテクスチャを作成した際に<BR>
デバイスがそのサイズをサポートしていないときは<BR>
内包できる大きさの２の累乗のサイズになっています。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;
  IGraphicCard *pGraphicCard = NULL;
  IRender      *pRender      = NULL;
  ITexture     *pTex         = NULL;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // ビデオカード初期化
    IGraphicCard *pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
    if ( pGraphicCard == NULL ) goto EXIT;      // IGraphicCardにはNullDeviceがないので失敗するとNULLが返る

    // レンダラーの生成
    IRender *pRender = pGraphicCard->CreateRender();
    if ( pRender == NULL ) goto EXIT;           // IRenderにはNullDeviceがないので失敗するとNULLが返る

    // テクスチャの生成
    pTex = pRender->CreateTextureFromFile( "sample.bmp" );

    // テクスチャのサイズを取得
    // テクスチャの実サイズ
    // デバイスによっては生成時に要求通りにサイズはならない
    Math::Point2DI Size = pTex->GetSize();

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

EXIT:
  SAFE_RELEASE( pTex );                // テクスチャの解放
  SAFE_RELEASE( pRender );             // レンダラーの解放
  SAFE_RELEASE( pGraphicCard );        // ビデオカードの解放
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
		virtual Math::Point2DI GetSize( void ) = 0;

/**
@brief 要求テクスチャサイズ取得
@author 葉迩倭
@return テクスチャのサイズ

@note
テクスチャの元サイズを取得します。<BR>
作成時に指定した大きさを取得します。<BR>
この大きさは実際のテクスチャサイズとは違う場合があります。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;
  IGraphicCard *pGraphicCard = NULL;
  IRender      *pRender      = NULL;
  ITexture     *pTex         = NULL;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // ビデオカード初期化
    IGraphicCard *pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
    if ( pGraphicCard == NULL ) goto EXIT;      // IGraphicCardにはNullDeviceがないので失敗するとNULLが返る

    // レンダラーの生成
    IRender *pRender = pGraphicCard->CreateRender();
    if ( pRender == NULL ) goto EXIT;           // IRenderにはNullDeviceがないので失敗するとNULLが返る

    // テクスチャの生成
    pTex = pRender->CreateTextureFromFile( "sample.bmp" );

    // 生成時にリクエストしたテクスチャのサイズ
    // ファイル読み込みの場合ファイル上ので画像のサイズ
    Math::Point2DI Size = pTex->GetOriginalSize();

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

EXIT:
  SAFE_RELEASE( pTex );                // テクスチャの解放
  SAFE_RELEASE( pRender );             // レンダラーの解放
  SAFE_RELEASE( pGraphicCard );        // ビデオカードの解放
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
		virtual Math::Point2DI GetOriginalSize( void ) = 0;

/**
@brief テクスチャ変換用パラメーター取得
@author 葉迩倭
@return 変換用の値

@note
テクスチャの元画像の座標からテクスチャの値を取得するための変換用の値を取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;
  IGraphicCard *pGraphicCard = NULL;
  IRender      *pRender      = NULL;
  ITexture     *pTex         = NULL;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // ビデオカード初期化
    IGraphicCard *pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
    if ( pGraphicCard == NULL ) goto EXIT;      // IGraphicCardにはNullDeviceがないので失敗するとNULLが返る

    // レンダラーの生成
    IRender *pRender = pGraphicCard->CreateRender();
    if ( pRender == NULL ) goto EXIT;           // IRenderにはNullDeviceがないので失敗するとNULLが返る

    // テクスチャの生成
    pTex = pRender->CreateTextureFromFile( "sample.bmp" );

    // 元画像の(100,50)座標をUVへ変換
    Math::Point2DF Trans = pTex->GetPixelToTexelTransform();
    Float u = 100.0f * Trans.x;
    Float v =  50.0f * Trans.y;

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

EXIT:
  SAFE_RELEASE( pTex );                // テクスチャの解放
  SAFE_RELEASE( pRender );             // レンダラーの解放
  SAFE_RELEASE( pGraphicCard );        // ビデオカードの解放
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
		virtual Math::Point2DF GetPixelToTexelTransform( void ) = 0;

/**
@brief レンダリングターゲット内容を保存
@author 葉迩倭
@retval true	成功
@retval false	失敗

@note
レンダリングターゲットの現在の内容をバックアップします。<BR>
バックアップされた内容はデバイスのロスト時に自動的に復元されます。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;
  IGraphicCard *pGraphicCard = NULL;
  IRender      *pRender      = NULL;
  ITexture     *pTex         = NULL;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // ビデオカード初期化
    IGraphicCard *pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
    if ( pGraphicCard == NULL ) goto EXIT;      // IGraphicCardにはNullDeviceがないので失敗するとNULLが返る

    // レンダラーの生成
    IRender *pRender = pGraphicCard->CreateRender();
    if ( pRender == NULL ) goto EXIT;           // IRenderにはNullDeviceがないので失敗するとNULLが返る

    // テクスチャの生成
    pTex = pRender->CreateTextureRenderTarget( 256, 256 );

    // デバイスロスト時に内容が復元できるように
    // 現在の状態をバックアップしておく。
    //   通常は何らかのレンダリングを行った時に、
    //   その内容を保存しておきたい場合に使う。
    pTex->BackupTargetBuffer();

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

EXIT:
  SAFE_RELEASE( pTex );                // テクスチャの解放
  SAFE_RELEASE( pRender );             // レンダラーの解放
  SAFE_RELEASE( pGraphicCard );        // ビデオカードの解放
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
		virtual Bool BackupTargetBuffer( void ) = 0;

/**
@brief 種類を取得
@author 葉迩倭
@return	テクスチャがどの種類に属するかを取得します。

@note
テクスチャの種類を取得します。<BR>
IRender::SetRenderTarget()に使えるのはTEXTURE_TYPE_TARGETだけで<BR>
IRender::SetDepthBuffer()に使えるのはTEXTURE_TYPE_DEPTHだけです。
*/
		virtual eTextureType GetType( void ) = 0;

/**
@brief 深度バッファの種類を取得
@author 葉迩倭
@return	深度バッファの種類

@note
深度バッファの種類を取得します。<BR>
返り値がDEPTH_BUFFER_TEXTUREの場合はテクスチャとして深度バッファが作られています。
*/
		virtual eDepthBufferType GetDepthBufferType( void ) = 0;

/**
@brief フィルタリング処理の是非を取得
@author 葉迩倭
@retval false	フィルタリング＆アルファブレンド出来ない
@retval true	フィルタリング＆アルファブレンド出来る

@note
フィルタリング可能なフォーマットかを取得します。
*/
		virtual Bool IsFilterEnable( void ) = 0;
	};
}
}

