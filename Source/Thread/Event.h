#pragma once


/**
	@file
	@brief イベント操作
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Thread
{
	/**
		@brief スレッド用イベントオブジェクト
		@author 葉迩倭
	*/
	class SELENE_DLL_API CEvent
	{
	private:
		HANDLE m_EventHandle[MAXIMUM_WAIT_OBJECTS];		///< イベントハンドル
		Sint32 m_HandleCount;							///< イベント数

	public:
/**
@brief コンストラクタ
@author 葉迩倭
@param IsSignal		[in] シグナル状態で初期化する場合はtrue
@param Count		[in] イベントのカウント（MAXIMUM_WAIT_OBJECTS以下）
*/
		CEvent( Bool IsSignal = false, Sint32 Count = 1 );

/**
@brief デストラクタ
@author 葉迩倭
*/
		virtual ~CEvent();

/**
@brief 指定されたイベントをシグナル状態に設定
@author 葉迩倭
@param No	[in] シグナル状態するイベントの番号

@note
指定した番号のイベントをシグナル状態に設定します。

@code
#include "Selene.h"

using namespace Selene;

// 5個のイベント生成
Event Event( false, 5 );

void ThreadProc( void *pData )
{
  // No=3のイベントがシグナル？
  while ( !Event.IsSignal( 3 ) )
  {
    // しばし待つ
    Sleep( 1000 );
  }

  // No=3のイベントを非シグナルにする
  Event.Reset( 3 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Thread Thread;

  // スレッド生成
  Thread.Create( ThreadProc, NULL );

  // 適当に待ってるふり
  Sleep( 1000 );

  // No=3のイベントをシグナルにする
  Event.Set( 3 );

  // スレッド終わってる？
  while ( !Thread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		virtual void Set( Sint32 No = 0 );

/**
@brief 指定されたイベントを非シグナル状態に設定
@author 葉迩倭
@param No	[in] 非シグナル状態するイベントの番号

@note
指定した番号のイベンとぉ非シグナル状態に設定します。

@code
#include "Selene.h"

using namespace Selene;

// 5個のイベント生成
Event Event( false, 5 );

void ThreadProc( void *pData )
{
  // No=3のイベントがシグナル？
  while ( !Event.IsSignal( 3 ) )
  {
    // しばし待つ
    Sleep( 1000 );
  }

  // No=3のイベントを非シグナルにする
  Event.Reset( 3 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Thread Thread;

  // スレッド生成
  Thread.Create( ThreadProc, NULL );

  // 適当に待ってるふり
  Sleep( 1000 );

  // No=3のイベントをシグナルにする
  Event.Set( 3 );

  // スレッド終わってる？
  while ( !Thread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		virtual void Reset( Sint32 No = 0 );

/**
@brief 指定したイベントがシグナル状態かチェック
@author 葉迩倭
@param No	[in] チェックするイベントの番号
@retval false	非シグナル状態
@retval true	シグナル状態

@note
指定したイベントがシグナル状態になっているかをチェックします。

@code
#include "Selene.h"

using namespace Selene;

// 5個のイベント生成
Event Event( false, 5 );

void ThreadProc( void *pData )
{
  // No=3のイベントがシグナル？
  while ( !Event.IsSignal( 3 ) )
  {
    // しばし待つ
    Sleep( 1000 );
  }

  // No=3のイベントを非シグナルにする
  Event.Reset( 3 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Thread Thread;

  // スレッド生成
  Thread.Create( ThreadProc, NULL );

  // 適当に待ってるふり
  Sleep( 1000 );

  // No=3のイベントをシグナルにする
  Event.Set( 3 );

  // スレッド終わってる？
  while ( !Thread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		virtual Bool IsSignal( Sint32 No = 0 );

/**
@brief 全てのイベントがシグナル状態かチェック
@author 葉迩倭
@retval false	非シグナル状態
@retval true	シグナル状態

@note
全てのイベントがシグナル状態になっているかをチェックします。

@code
#include "Selene.h"

using namespace Selene;

// 3個のイベント生成
Event Event( false, 3 );

void ThreadProc( void *pData )
{
  // 全部シグナルになるまで待つ
  while ( !Event.IsSignalAll() )
  {
    // まだなのでしばし待つ
    Sleep( 1000 );
  }
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Thread Thread;

  // スレッド生成
  Thread.Create( ThreadProc, NULL );

  // 適当に待ってるふり
  Sleep( 1000 );

  // イベントをシグナルにする
  Event.Set( 0 );
  Event.Set( 1 );
  Event.Set( 2 );

  // スレッド終わってる？
  while ( !Thread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		virtual Bool IsSignalAll( void );

/**
@brief シグナル状態になったイベントを取得
@author 葉迩倭
@param TimeOut		[in] タイムアウトms時間（-1で無限）
@retval -1		タイムアウト
@retval 0以上	シグナル状態になったイベント番号

@note
指定時間待機し１つでもシグナル状態になったらその瞬間にそのイベントの番号を返します。<BR>
指定時間経過してもシグナル状態になったイベントがなければ-1を返します。

@code
#include "Selene.h"

using namespace Selene;

// 3個のイベント生成
Event Event( false, 3 );

void ThreadProc( void *pData )
{
  // 何かがシグナルになるまで1秒ほど待つ
  Sint32 No = Event.Wait( 1000 );
  switch ( No )
  {
  case 0:
  case 1:
  case 2:
    break;
  default:
    break;
  }
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Thread Thread;

  // スレッド生成
  Thread.Create( ThreadProc, NULL );

  // 適当に待ってるふり
  Sleep( 1000 );

  // イベントをシグナルにする
  Event.Set( 1 );

  // スレッド終わってる？
  while ( !Thread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		virtual Sint32 Wait( Sint32 TimeOut = -1 );

/**
@brief シグナル状態になったイベントを取得
@author 葉迩倭
@param No		[in] ハンドル番号
@return		ハンドル

@note
指定番号のハンドルを取得します。
*/
		virtual HANDLE GetHandle( Sint32 No );
	};
}
}

