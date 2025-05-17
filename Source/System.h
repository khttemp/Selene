#pragma once


/**
	@file
	@brief システム系関数群
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Core/CCore.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace System
{
/**
@brief システム初期化
@author 葉迩倭
@param IsSetExePath		[in] カレントディレクトリを実行ファイルの場所に強制的に変更するかの有無
@param IsCreateLogFile	[in] ログファイルを生成するかどうか
@param IsSSE			[in] SSEの使用有無
@retval true	成功
@retval false	失敗

@note
Seleneシステムの初期化を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // システムの起動
  if ( System::Initialize() )
  {  
  }

  System::Finalize();            // システムの終了処理を行う

  return 0;
}
@endcode
*/
SELENE_DLL_API Bool Initialize( Bool IsSetExePath = true, Bool IsCreateLogFile = true, Bool IsSSE = true );

/**
@brief システム終了
@author 葉迩倭

@note
Seleneシステムの終了をします。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // システムの起動
  if ( System::Initialize() )
  {  
  }

  System::Finalize();            // システムの終了処理を行う

  return 0;
}
@endcode
*/
SELENE_DLL_API void Finalize( void );

/**
@brief 多重起動ブロック
@author 葉迩倭
@param pApplicationName	[in] アプリケーション名
@retval false	既に同名のアプリケーションが起動している
@retval true	同名のアプリケーションは存在しない

@note
返り値false時にアプリケーションを終了させることで<BR>
多重起動を防止することができます。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // システムの起動
  if ( System::Initialize() )
  {  
    // 多重起動チェック
    if ( System::BlockDualBoot( "Application Name" ) )
    {
    }
  }

  System::Finalize();            // システムの終了処理を行う

  return 0;
}
@endcode
*/
SELENE_DLL_API Bool BlockDualBoot( const char *pApplicationName );

/**
@brief カレントディレクトリリセット
@author 葉迩倭

@note
カレントディレクトリをアプリケーションの実行フォルダに設定します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // システムの起動
  if ( System::Initialize() )
  {  
    // カレントディレクトリを実行ファイルのフォルダにする
    System::ResetCurrentDirectory();
  }

  System::Finalize();            // システムの終了処理を行う

  return 0;
}
@endcode
*/
SELENE_DLL_API void ResetCurrentDirectory( void );

/**
@brief ディレクトリ生成
@author 葉迩倭
@param pPath	[in] フォルダパス

@note
指定パスへディレクトリを生成します。<BR>
途中のフォルダが存在しない場合、全ての階層に対してフォルダを作成していきます。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // システムの起動
  if ( System::Initialize() )
  {  
    // カレントディレクトリを実行ファイルのフォルダにする
    System::ResetCurrentDirectory();

    // カレントディレクトリの場所以下にフォルダ生成
    // ※実行ファイルの場所にフォルダを掘る
    System::DirectoryCreate( "Save\\Config" );
  }

  System::Finalize();            // システムの終了処理を行う

  return 0;
}
@endcode
*/
SELENE_DLL_API void DirectoryCreate( const char *pPath );

/**
@brief Coreの取得
@author 葉迩倭
@return ICoreインターフェイス

@note
ウィンドウを管理するICoreクラスを生成/取得します。<BR>
現在、１つのICoreしか生成できません。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore      *pCore      = NULL;

  // システムの起動
  if ( System::Initialize() )
  {
    // ICoreの生成
    ICore *pCore = System::CreateCore();
    if ( pCore == NULL ) goto EXIT;      // ICoreにはNullDeviceがないので失敗するとNULLが返る  
  }

EXIT:
  SAFE_RELEASE( pCore );            // コアの解放

  System::Finalize();              // システムの終了処理を行う

  return 0;
}
@endcode
*/
SELENE_DLL_API ICore *CreateCore( void );

/**
@brief SSEのサポートの有無
@author 葉迩倭
@return	SSEのサポートの有無

@note
使用しているCPUがSSEをサポートしているかを調べます。<BR>
この関数はInitialize()のIsSSEにfalseを指定するとかならずfalseを返します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // システムの起動
  if ( System::Initialize() )
  {  
    // SSEサポートしてる？
    if ( System::IsSupportSSE() )
    {
      // SSEでSIMD演算
    }
    else
    {
      // FPUで普通に演算
    }
  }

  System::Finalize();        // システムの終了処理を行う

  return 0;
}
@endcode
*/
SELENE_DLL_API Bool IsSupportSSE( void );

/**
@brief 使用するCPU番号を設定
@author 葉迩倭
@param No	[in] CPU番号

@note
現在のスレッドで使用するCPUの番号を設定します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // システムの起動
  if ( System::Initialize() )
  {  
    // 現在のスレッドをCPU1で動かす
    System::SetThreadCPUNo( 1 );
  }

  System::Finalize();        // システムの終了処理を行う

  return 0;
}
@endcode
*/
SELENE_DLL_API void SetThreadCPUNo( Sint32 No );
}
}
