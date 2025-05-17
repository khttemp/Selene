#pragma once


/**
	@file
	@brief アプリケーション管理インターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Color.h"
#include "Class/Common/Peripheral/CInput.h"
#include "Interface/Core/IGraphicCard.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief アプリケーション管理インターフェイス
		@author 葉迩倭

		@note
		ウィンドウを管理するアプリケーションのコアのインターフェイスです。
	*/
	class ICore : public IInterface
	{
	public:
		virtual ~ICore() {}

/**
@brief コアの初期化
@author 葉迩倭
@param pAppName		[in] アプリケーション名
@param FrameRate	[in] フレームレート
@retval false	失敗
@retval true	成功

@note
アプリケーションに関する初期化を行います。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Bool Initialize( const char *pAppName, eFrameRate FrameRate ) = 0;

/**
@brief ウィンドウ生成
@author 葉迩倭
@param ScreenWidth	[in] 画面横幅
@param ScreenHeight	[in] 画面縦幅
@param IsWindow		[in] ウィンドウモードで起動する場合true

@note
ウィンドウを作成し、アプリケーションを起動します。<BR>
ここでの設定で起動後変更可能なものは画面モードだけです。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void Start( Sint32 ScreenWidth, Sint32 ScreenHeight, Bool IsWindow ) = 0;

/**
@brief ウィンドウの終了
@author 葉迩倭

@note
ウィンドウを解体し、アプリケーションを終了します。<BR>
この関数は終了を通知するだけで、実際にはメインループ後に<BR>
終了処理が行われます。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      // 終了
      pCore->Exit();
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void Exit( void ) = 0;

/**
@brief アプリケーションメイン処理
@author 葉迩倭
@param IsFullActive	[in] 常時動作フラグ
@retval false	アプリケーションは終了した
@retval true	アプリケーションは稼働中

@note
IsFullActiveにtrueを指定すると、<BR>
ウィンドウがフォーカスを失っている状態でも動作し続けます。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Bool Run( Bool IsFullActive = false ) = 0;

/**
@brief ウィンドウハンドル取得
@author 葉迩倭
@return ウィンドウのウィンドウハンドル

@note
ICoreの所有するウィンドウのウィンドウハンドルを取得します。


@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // ウィンドウハンドルを取得
    HWND hWnd = pCore->GetWindowHandle();

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual HWND GetWindowHandle( void ) = 0;

/**
@brief ベンチマーク用モード設定
@author 葉迩倭
@param IsEnable	[in] trueにするとすべてのウェイト処理を省きます

@note
ベンチマークのような速度チェックをする場合に使います。<BR>
このフラグをtrueにするとVSYNCやタイマーなどの処理がすべて省かれ、<BR>
出せる最高の速度で処理が回ります。<BR>
<BR>
デフォルトはfalseです。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // ベンチマーク用に各種ウェイトをOFF
    pCore->SetBenchMode( true );

    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void SetBenchMode( Bool IsEnable ) = 0;

/**
@brief Sleep使用有無設定
@author 葉迩倭
@param IsEnable	[in] trueにするとSleepを使用します

@note
フレームレートの調整にSleepを使うかどうかを設定します。<BR>
環境によっては誤差が大きくフレームレートが一定にならないことがあるので、<BR>
そのような条件ではfalseを設定して下さい。<BR>
Sleepを使わない場合は当然CPUを常に占有するようになります。<BR>
<BR>
デフォルトはtrueです。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // より厳密に時間計測をする（CPU使用率が跳ね上がるので注意）
    pCore->SetSleepUse( false );

    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void SetSleepUse( Bool IsEnable ) = 0;

/**
@brief 仮想画面処理のON/OFF
@author 葉迩倭
@param IsEnable		[in] true 有効 / false 無効

@note
2D描画時の仮想画面処理の有無のON/OFFを設定します。<BR>
trueにする事で2Dの描画が仮想画面に行われるようになり、<BR>
画面解像度に関係なく画面に対する同じ割合で描画されるようになります。<BR>
<BR>
デフォルトはfalseです。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // 画面サイズが返られてもいいように2Dがを仮想画面に描画
    pCore->SetVirtualScreenEnable( true );

    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void SetVirtualScreenEnable( Bool IsEnable ) = 0;

/**
@brief 仮想画面設定
@author 葉迩倭
@param RealWidth		[in] 実画面の横幅
@param RealHeight		[in] 実画面の縦幅
@param VirtualWidth		[in] 仮想画面の横幅
@param VirtualHeight	[in] 仮想画面の縦幅

@note
可変画面サイズ用の設定を行います。<BR>
3D用に画面のサイズを自由に変えられるように作られている場合でも<BR>
2Dの描画は仮想画面に設定された画面サイズと見立てて描画を行います。<BR>
つまり仮想画面が(640x480)の時に(0,0)-(640,480)への全画面の2D描画を行った場合、<BR>
実際の画面のサイズが(320x240)や(1280x960)等のサイズであっても<BR>
全画面に自動的に拡大縮小して描画されるということです。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // 画面サイズが返られてもいいように2Dがを仮想画面に描画
    pCore->SetVirtualScreenEnable( true );

    // 仮想画面サイズ
    pCore->SetVirtualScreenSize( 640, 480, 800, 600 );

    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void SetVirtualScreenSize( Sint32 RealWidth, Sint32 RealHeight, Sint32 VirtualWidth, Sint32 VirtualHeight ) = 0;

/**
@brief GPU負荷を取得します。
@author 葉迩倭
@return GPU負荷（％）

@note
おおまかなGPUの負荷を取得します。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      // CPU使用率
      Float fCPU = pCore->GetCPU();
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Float GetCPU( void ) = 0;

/**
@brief FPSを取得します。
@author 葉迩倭
@return FPS

@note
秒間のフレーム数を取得します。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      // FPS
      Float fFPS = pCore->GetFPS();
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Float GetFPS( void ) = 0;

/**
@brief 1フレームのポリゴン数を取得します。
@author 葉迩倭
@return PPS

@note
秒間のポリゴン数を取得します。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      // ポリゴン数取得
	  Float fPPF = pCore->GetPPF();
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Float GetPPF( void ) = 0;

/**
@brief OS起動からの時間取得
@author 葉迩倭
@return 1/1000秒単位の時間

@note
OSが起動してからの時間を取得します。<BR>
32Bit変数なので約48日で1周して0に戻ります。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      // 時間取得
      Uint32 Time = pCore->GetMultiMediaTime();
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Uint32 GetMultiMediaTime( void ) = 0;

/**
@brief CPUタイマーのカウント値取得
@author 葉迩倭
@return 1/GetSystemTimerBySec秒単位の時間

@note
CPUタイマーの現在の時間を取得します。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      // 時間取得
      Uint64 Time = pCore->GetSystemTimer();

      // なんか処理する
 
      // 経過時間取得
      Time = pCore->GetSystemTimer() - Time;

      // 経過時間を1秒あたりの％に
      Float fTime = 100.0 * (double)Time / (double)pCore->GetSystemTimerBySec();
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Uint64 GetSystemTimer( void ) = 0;

/**
@brief CPUタイマーの1秒のカウント値取得
@author 葉迩倭
@return GetSystemTimerの1秒のカウント値

@note
CPUタイマーの1秒の時間を取得します。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      // 時間取得
      Uint64 Time = pCore->GetSystemTimer();

      // なんか処理する
 
      // 経過時間取得
      Time = pCore->GetSystemTimer() - Time;

      // 経過時間を1秒あたりの％に
      Float fTime = 100.0 * (double)Time / (double)pCore->GetSystemTimerBySec();
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Uint64 GetSystemTimerBySec( void ) = 0;

/**
@brief 画面サイズ変更
@author 葉迩倭
@param Size		[in] 画面サイズ

@note
画面サイズを変更します。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // 画面サイズ変更
    pCore->ResizeWindowSize( Math::Point2DI(320,240) );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void ResizeWindowSize( Math::Point2DI Size ) = 0;

/**
@brief 画面モードを変更します
@author 葉迩倭

@note
画面モードを変更します。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // 画面モード変更
    pCore->ChangeScreenMode();

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void ChangeScreenMode( void ) = 0;

/**
@brief ウィンドウモードチェック
@author 葉迩倭

@note
現在の画面モードがウィンドウモードかどうかを調べます

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // 画面モード取得
    if ( pCore->IsWindowMode() )
    {
    }

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Bool IsWindowMode( void ) = 0;

/**
@brief ムービー再生
@author 葉迩倭
@param pFileName	[in] ファイル名
@param IsLoop		[in] ループON/OFF
@param pCallback	[in] 強制終了用コールバック関数

@note
フル画面でムービーの再生を行います。<BR>
ムービーが終了するか、pCallback関数内でfalseを返すまで処理は戻ってきません。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // ムービー再生
    if ( pCore->PlayMovie( "Sample.mpg", false, NULL ) )
    {
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Bool PlayMovie( const char *pFileName, Bool IsLoop, Bool (__stdcall *pCallback)( void ) ) = 0;

/**
@brief フレームカウントを取得します。
@author 葉迩倭
@return フレーム数

@note
起動時からの総フレーム数を取得します。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      // 起動からのフレーム数
      Sint32 Cnt = pCore->GetSyncCount();
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Sint32 GetSyncCount( void ) = 0;

/**
@brief タイトルバーの情報表示ON/OFF
@author 葉迩倭
@param IsEnable		[in] 表示のON/OFF

@note
タイトルバーに現在の情報の表示を行うか設定します。<BR>
<BR>
デフォルトはfalseです。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // タイトルバーに情報表示
    pCore->EnableDrawTitleInformation( true );

    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void EnableDrawTitleInformation( Bool IsEnable ) = 0;

/**
@brief マウスカーソルの表示ON/OFF
@author 葉迩倭
@param IsEnable		[in] 表示のON/OFF

@note
マウスカーソルの表示を行うか設定します。<BR>
<BR>
デフォルトはfalseです。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // マウスカーソル消去
    pCore->EnableDrawMouseCursor( false );

    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void EnableDrawMouseCursor( Bool IsEnable ) = 0;

/**
@brief グラフィックカードインターフェイスを取得
@author 葉迩倭
@param GraphicCardNo	[in] グラフィックカード番号
@return グラフィックカードインターフェイス

@note
グラフィックカードに関しての初期化を行い、<BR>
そのインターフェイスを取得します。<BR>
通常GraphicCardNoにはGRAPHIC_CARD_DEFAULT_NOを指定します。<BR>
「NV PerfHUD」のインストールされた環境では、<BR>
GRAPHIC_CARD_NV_PERF_HUDを指定することでそれを有効に出来ます。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  IGraphicCard *pGraphicCard = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // グラフィックカードインターフェイスを生成
    pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // グラフィックカードの解放
  SAFE_RELEASE( pGraphicCard );

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual IGraphicCard *CreateGraphicCard( eGraphicCardNo GraphicCardNo ) = 0;

/**
@brief ジョイスティックの数を取得
@author 葉迩倭
@return 有効なジョイスティックの数

@note
初期化に成功した有効なジョイスティックなの数を取得します。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // ジョイスティック数を取得
    Sint32 Count = pCore->GetJoystickCount();

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Sint32 GetJoystickCount( void ) = 0;

/**
@brief マウスインターフェイスを取得
@author 葉迩倭
@return マウスインターフェイス

@note
ICoreの所有するウィンドウに関連付けられたマウスの初期化を行い、<BR>
そのインターフェイスを取得します。<BR>
マウスに関しての情報はこのインターフェイス経由で取得して下さい。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Peripheral::IMouse *pMouse = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // マウスの取得
    pMouse = pCore->GetMouse();

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // マウスの解放
  SAFE_RELEASE( pMouse );

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Peripheral::IMouse *GetMouse( void ) = 0;

/**
@brief キーボードインターフェイスを取得
@author 葉迩倭
@return キーボードインターフェイス

@note
ICoreの所有するウィンドウに関連付けられたキーボードの初期化を行い、<BR>
そのインターフェイスを取得します。<BR>
キーボードに関しての情報はこのインターフェイス経由で取得して下さい。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Peripheral::IKeyboard *pKeyboard = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // キーボードの取得
    pKeyboard = pCore->GetKeyboard();

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // キーボードの解放
  SAFE_RELEASE( pKeyboard );

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Peripheral::IKeyboard *GetKeyboard( void ) = 0;

/**
@brief ジョイスティックインターフェイスを取得
@author 葉迩倭
@param No	[in] ジョイスティック番号(0～15)
@return ジョイスティックインターフェイス

@note
ICoreの所有するウィンドウに関連付けられたジョイスティックの初期化を行い、<BR>
そのインターフェイスを取得します。<BR>
ジョイスティックに関しての情報はこのインターフェイス経由で取得して下さい。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Peripheral::IJoystick *pJoystick = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // ジョイスティックの取得
    pJoystick = pCore->GetJoystick( 0 );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // ジョイスティックの解放
  SAFE_RELEASE( pJoystick );

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Peripheral::IJoystick *GetJoystick( Sint32 No ) = 0;

/**
@brief 入力統合インターフェイスを取得
@author 葉迩倭
@param No					[in] 適用するジョイスティック番号
@param KeyRepeatStartTime	[in] キーリピート開始フレーム
@param KeyRepeatInterval	[in] キーリピート間隔フレーム
@return 入力統合インターフェイス

@note
ICoreの所有するウィンドウに関連付けられたジョイスティック＆キーボードの初期化を行い、<BR>
そのインターフェイスを取得します。<BR>
ジョイスティックとキーボードを統合して扱うことのできるインターフェイスです。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Peripheral::IInputController *pInputController = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // 入力コントローラーの取得
    pInputController = pCore->GetInputController( 0, 30, 5 );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // 入力コントローラーの解放
  SAFE_RELEASE( pInputController );

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Peripheral::IInputController *GetInputController( Sint32 No, Sint32 KeyRepeatStartTime, Sint32 KeyRepeatInterval ) = 0;

/**
@brief ファイルマネージャーインターフェイス生成
@author 葉迩倭
@return ファイルマネージャーインターフェイス

@note
新規のファイルマネージャーインターフェイスを生成します。<BR>
ファイルのパスなどの設定は全てIFileManagerを経由して行います。
取得したファイルマネージャーインターフェイスは使用終了後には必ずRelease()して下さい。。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  File::IFileManager *pFileMgr = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // ファイルマネージャーの生成
    pFileMgr = pCore->CreateFileManager();

    // ファイルマネージャーを設定
    pCore->SetFileManager( pFileMgr );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // ファイルマネージャーの解放
  SAFE_RELEASE( pFileMgr );

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual File::IFileManager *CreateFileManager( void ) = 0;

/**
@brief ファイルマネージャーインターフェイス取得
@author 葉迩倭
@return ファイルマネージャーインターフェイス

@note
現在設定されているファイルマネージャーインターフェイスを取得します。<BR>
設定済みのファイルマネージャーインターフェイスへのアクセスを行う場合に使用してください。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  File::IFileManager *pFileMgr = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // ファイルマネージャーの生成
    pFileMgr = pCore->CreateFileManager();

    // ファイルマネージャーを設定
    pCore->SetFileManager( pFileMgr );

    // ファイルパス設定
    pCore->GetFileMgrPointer()->SetCurrentPath( "Data\\Texture" );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // ファイルマネージャーの解放
  SAFE_RELEASE( pFileMgr );

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual File::IFileManager *GetFileMgrPointer( void ) = 0;

/**
@brief ファイルマネージャーインターフェイス設定
@author 葉迩倭
@param pMgr	[in] ファイルマネージャーインターフェイス

@note
ファイルの読み込みに使われるファイルマネージャーインターフェイスを設定します。<BR>
ファイルの読み込みはこのマネージャーを経由して行うので、<BR>
ファイルの読み込みを行う場合は必ず設定してください。<BR>
既に設定されているマネージャーは内部で解放されます。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  File::IFileManager *pFileMgr = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // ファイルマネージャーの生成
    pFileMgr = pCore->CreateFileManager();

    // ファイルマネージャーを設定
    pCore->SetFileManager( pFileMgr );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // ファイルマネージャーの解放
  SAFE_RELEASE( pFileMgr );

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void SetFileManager( File::IFileManager *pMgr ) = 0;

/**
@brief サウンドファイル読み込み
@author 葉迩倭
@param pFileName		[in] サウンドファイル名(wav)
@param LayerCount		[in] レイヤー数（同時発音可能数）
@param IsGlobalScope	[in] サウンドのスコープ
@retval	サウンドインターフェイス

@note
ICoreの所有するウィンドウに関連付けられたサウンドを取得します。<BR>
IsGlobalScopeにtrueを渡すと、ウィンドウのフォーカスに関係なく再生されます。<BR>
LayerCountで指定した数分のレイヤーを内部で持ちます。<BR>
これは同一のバッファを別々のタイミングで再生・停止等の<BR>
操作を行うための機能ですが、１つのバッファを使いまわすので<BR>
メモリ使用量は１つの場合と同じです。<BR>
使用の終了したサウンドは必ずRelease()して下さい。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Sound::ISound *pSound = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // サウンドの生成
    pSound = CreateSoundFromFile( "Sample.wav", 4, false );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // サウンドの解放
  SAFE_RELEASE( pSound );

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Sound::ISound *CreateSoundFromFile( const char *pFileName, Sint32 LayerCount, Bool IsGlobalScope ) = 0;

/**
@brief サウンドファイル読み込み
@author 葉迩倭
@param pFileName		[in] サウンドファイル名
@param IsGlobalScope	[in] サウンドのスコープ
@param pPluginName		[in] プラグイン名
@retval		サウンドインターフェイス

@note
ICoreの所有するウィンドウに関連付けられたサウンドを取得します。<BR>
IsGlobalScopeにtrueを渡すと、ウィンドウのフォーカスに関係なく再生されます。<BR>
使用の終了したサウンドは必ずRelease()して下さい。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Sound::IStreamSound *pSound = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // サウンドの生成
    pSound = CreateStreamSoundFromFile( "Sample.ogg", false, "OggVorbis" );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // サウンドの解放
  SAFE_RELEASE( pSound );

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Sound::IStreamSound *CreateStreamSoundFromFile( const char *pFileName, Bool IsGlobalScope, const char *pPluginName ) = 0;

/**
@brief ファイバーコントローラー生成
@author 葉迩倭
@param Max	[in] ファイバー最大数
@return ファイバーコントローラーインターフェイス

@note
ファイバーコントローラーを取得します。<BR>
ICoreに１つしか存在せず2回目以降は既存のインターフェイスを返します。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Fiber::IFiberController *pFiber = NULL;

  // システムの初期化
  System::Initialize();

  // コアの生成
  pCore = System::CreateCore();

  // 初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーション開始
    pCore->Start( 640, 480, true );

    // ファイバーコントローラーの生成
    pFiber = pCore->CreateFiberController( 8 );

    // メインループ
    while ( pCore->Run() )
    {
    }
  }

  // ファイバーの解放
  SAFE_RELEASE( pFiber );

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Fiber::IFiberController *CreateFiberController( Sint32 Max ) = 0;
	};
}

