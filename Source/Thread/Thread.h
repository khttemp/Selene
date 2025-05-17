#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "CriticalSection.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Thread
{
	/**
		@brief スレッド実行優先度
		@author 葉迩倭
	*/
	enum eCThreadPriority
	{
		THREAD_PRIORITY_LOW		= -2,		/// 低い
		THREAD_PRIORITY_MIDDLE	= -1,		/// やや低い
		THREAD_PRIORITY_DEFAULT	=  0,		/// 通常
		THREAD_PRIORITY_HIGH	= +1,		/// 高い
	};

	/**
		@brief スレッド管理操作クラス
		@author 葉迩倭
	*/
	class SELENE_DLL_API CThread
	{
	private:
/**
@brief スレッド用関数
@author 葉迩倭
@param pArguments	[in] CThreadのポインタ

@note
クラスの関数を直接は指定できないので<BR>
staticな関数を経由して呼び出す。
*/
		static Uint32 __stdcall CThreadFunc( void* pArguments );

	private:
		HANDLE m_hThread;					///< スレッドハンドル
		Uint32 m_ThreadId;					///< スレッドID
		void *m_pData;						///< スレッドデータ伝達用ポインタ
		void (*m_pMainProc)( void* );		///< スレッド関数
		CCriticalSection m_cs;				///< クリティカルセクション

	public:
/**
@brief コンストラクタ
@author 葉迩倭
*/
		CThread();

/**
@brief デストラクタ
@author 葉迩倭
*/
		virtual ~CThread();

	public:
/**
@brief スレッド生成
@author 葉迩倭
@param pCThreadFunc	[in] スレッド関数
@param pData		[in] スレッドに引き渡すデータポインタ
@retval false	生成失敗or既にスレッドが生成されている
@retval true	生成完了

@note
スレッドの生成を行います。

@code
#include "Selene.h"

using namespace Selene;

void CThreadProc( void *pData )
{
  // 10秒待機
  Sleep( 10 * 1000 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // スレッド生成
  CThread.Create( CThreadProc, NULL );

  // スレッド終わるまで待つ
  while ( !CThread.WaitForExit() )
  {
    // 適当
    Sleep( 100 );
  }
  return 0;
}
@endcode
*/
		virtual Bool Create( void (*pCThreadFunc)( void* ), void *pData );

/**
@brief スレッド終了待ち
@author 葉迩倭
@retval false	スレッドは終了していない
@retval true	スレッドは終了した

@note
スレッドが終了するのを待ちます

@code
void CThreadProc( void *pData )
{
  // 10秒待機
  Sleep( 10 * 1000 );
}

void hogehoge( void )
{
	CThread CThread;

	// スレッド生成
	CThread.Create( CThreadProc, NULL );

	// スレッド終わるまで待つ
	while ( !CThread.WaitForExit() )
	{
		// 適当
		Sleep( 100 );
	}
}
@endcode
*/
		virtual Bool WaitForExit( void );

/**
@brief スレッドの優先度変更
@author 葉迩倭
@param Priority		[in] スレッド処理の優先度

@note
スレッドの優先度を変更します。<BR>
デフォルトの優先度はTHREAD_PRIORITY_DEFAULTです。

@code
#include "Selene.h"

using namespace Selene;

void CThreadProc( void *pData )
{
  // 10秒待機
  Sleep( 10 * 1000 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // スレッド生成
  CThread.Create( CThreadProc, NULL );

  // スレッドの優先度を1ランク下げる
  CThread.SetPriority( THREAD_PRIORITY_MIDDLE );

  // スレッド終わるまで待つ
  while ( !CThread.WaitForExit() )
  {
    // 適当
    Sleep( 100 );
  }
  return 0;
}
@endcode
*/
		virtual Bool SetPriority( Sint32 Priority );

/**
@brief スレッドの中断を解除
@author 葉迩倭

@note
スレッドのサスペンドカウントが 1 減ります。<BR>
カウントが 0 になった時点でスレッドの中断が解除されます。

@code
#include "Selene.h"

using namespace Selene;

void CThreadProc( void *pData )
{
  // 10秒待機
  Sleep( 10 * 1000 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // スレッド生成
  CThread.Create( CThreadProc, NULL );

  // スレッド一時停止
  CThread.Suspend();

  // 適当に待ってるふり
  Sleep( 1000 );

  // スレッド再開
  CThread.Resume();

  // スレッド終わるまで待つ
  while ( !CThread.WaitForExit() )
  {
    // 適当
    Sleep( 100 );
  }
  return 0;
}
@endcode
*/
		virtual void Resume( void );

/**
@brief スレッドの実行を中断
@author 葉迩倭

@note
指定されたスレッドの実行が中断され、<BR>
そのスレッドのサスペンドカウントが 1 増えます。

@code
void CThreadProc( void *pData  )
{
}

void hogehoge( void )
{
	Selene::CThread CThread;

	// スレッド生成
	CThread.Create( CThreadProc );

	// スレッド一時停止
	CThread.Suspend();

	// 略
	…

	// スレッド再開
	CThread.Resume();

	// 略
	…
}
@endcode
*/
		virtual void Suspend( void );

/**
@brief スレッドの実行を終了
@author 葉迩倭

@note
指定されたスレッドの実行を強制終了します。<BR>
この関数で終了させる場合はスタックの解放などが行われないので<BR>
通常は使用しないでください。<BR>
強制終了を行わざるを得ない状況でのみ使用して下さい。

@code
#include "Selene.h"

using namespace Selene;

void CThreadProc( void *pData )
{
  // 10秒待機
  Sleep( 10 * 1000 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // スレッド生成
  CThread.Create( CThreadProc, NULL );

  // 適当に待ってるふり
  Sleep( 1000 );

  // スレッド終わってる？
  if ( !CThread.WaitForExit() )
  {
    // 強制終了
    CThread.Terminate();
  }
  return 0;
}
@endcode
*/
		virtual void Terminate( void );
	};
}
}

