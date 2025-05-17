#pragma once


/**
	@file
	@brief クリティカルセクション操作
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
		@brief クリティカルセクション管理クラス
		@author 葉迩倭
	*/
	class SELENE_DLL_API CCriticalSection
	{
	private:
		CRITICAL_SECTION m_CriticalSection;		///< クリティカルセクション

	public:
/**
@brief コンストラクタ
@author 葉迩倭
*/
		CCriticalSection();

/**
@brief デストラクタ
@author 葉迩倭
*/
		virtual ~CCriticalSection();

/**
@brief クリティカルセクションに入る
@author 葉迩倭

@note
クリティカルセクションに入ります。

@code
#include "Selene.h"

using namespace Selene;

CriticalSection cs;
Sint32 g_Result = 0;

void CThreadProc( void *pData )
{
  // 変数にアクセス前にロック
  cs.Enter();

  // 適当
  for ( Sint32 i = 0; i < 100000; )
  {
    g_Result += i * i;
  }

  // 変数使い終わったのでアクセスロック解除
  cs.Leave();
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // スレッド生成
  CThread.Create( CThreadProc, NULL );

  // 適当に待ってる
  Sleep( 1000 );

  // 変数にアクセス前にロック
  cs.Enter();

  // 結果をゲット
  Sint32 ret = g_Result;

  // 変数使い終わったのでアクセスロック解除
  cs.Leave();

  // スレッド終わってる？
  while ( !CThread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		void Enter( void ) const;

/**
@brief クリティカルセクションから抜ける
@author 葉迩倭

@note
クリティカルセクションから抜けます。

@code
#include "Selene.h"

using namespace Selene;

CriticalSection cs;
Sint32 g_Result = 0;

void CThreadProc( void *pData )
{
  // 変数にアクセス前にロック
  cs.Enter();

  // 適当
  for ( Sint32 i = 0; i < 100000; )
  {
    g_Result += i * i;
  }

  // 変数使い終わったのでアクセスロック解除
  cs.Leave();
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // スレッド生成
  CThread.Create( CThreadProc, NULL );

  // 適当に待ってる
  Sleep( 1000 );

  // 変数にアクセス前にロック
  cs.Enter();

  // 結果をゲット
  Sint32 ret = g_Result;

  // 変数使い終わったのでアクセスロック解除
  cs.Leave();

  // スレッド終わってる？
  while ( !CThread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		void Leave( void ) const;
	};

	/**
		@brief 自動クリティカルセクション管理クラス
		@author 葉迩倭
	*/
	class CAutoLock
	{
	private:
		const CCriticalSection	&m_cs;			///< 使用するクリティカルセクション

	private:
/**
@brief = オペレーター
@author 葉迩倭
@param	Lock [in] 入力
@return	入力と同じもの

コンパイルを通すためのダミー用。
*/
		CAutoLock & operator = ( CAutoLock &Lock ) {
			return Lock;
		}

	public:
/**
@brief コンストラクタ
@author 葉迩倭
@param cs	[in] クリティカルセクション

@note
コンストラクタ内で自動的にクリティカルセクションに入ります。

@code
#include "Selene.h"

using namespace Selene;

CriticalSection cs;
Sint32 g_Result = 0;

void CThreadProc( void *pData )
{
  // Lockのコンストラクタ内で
  // csがクリティカルセクションに入る
  CAutoLock Lock( cs );

  // 適当
  for ( Sint32 i = 0; i < 100000; )
  {
    g_Result += i * i;
  }

  // スコープから抜けるときにLockのデストラクタがコールされ
  // csがクリティカルセクションから抜ける
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // スレッド生成
  CThread.Create( CThreadProc, NULL );

  // 適当に待ってる
  Sleep( 1000 );

  // 変数にアクセス前にロック
  cs.Enter();

  // 結果をゲット
  Sint32 ret = g_Result;

  // 変数使い終わったのでアクセスロック解除
  cs.Leave();

  // スレッド終わってる？
  while ( !CThread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		CAutoLock( const CCriticalSection &cs )
			: m_cs	( cs )
		{
			m_cs.Enter();
		}

/**
@brief コンストラクタ
@author 葉迩倭
@param cs	[in] クリティカルセクション

@note
コンストラクタ内で自動的にクリティカルセクションに入ります。

@code
#include "Selene.h"

using namespace Selene;

CriticalSection cs;
Sint32 g_Result = 0;

void CThreadProc( void *pData )
{
  // Lockのコンストラクタ内で
  // csがクリティカルセクションに入る
  CAutoLock Lock( &cs );

  // 適当
  for ( Sint32 i = 0; i < 100000; )
  {
    g_Result += i * i;
  }

  // スコープから抜けるときにLockのデストラクタがコールされ
  // csがクリティカルセクションから抜ける
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // スレッド生成
  CThread.Create( CThreadProc, NULL );

  // 適当に待ってる
  Sleep( 1000 );

  // 変数にアクセス前にロック
  cs.Enter();

  // 結果をゲット
  Sint32 ret = g_Result;

  // 変数使い終わったのでアクセスロック解除
  cs.Leave();

  // スレッド終わってる？
  while ( !CThread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		CAutoLock( const CCriticalSection *cs )
			: m_cs	( *cs )
		{
			m_cs.Enter();
		}

/**
@brief デストラクタ
@author 葉迩倭

@note
デストラクタが呼ばれる時に自動的にクリティカルセクションから出ます。

@code
#include "Selene.h"

using namespace Selene;

CriticalSection cs;
Sint32 g_Result = 0;

void CThreadProc( void *pData )
{
  // Lockのコンストラクタ内で
  // csがクリティカルセクションに入る
  CAutoLock Lock( &cs );

  // 適当
  for ( Sint32 i = 0; i < 100000; )
  {
    g_Result += i * i;
  }

  // スコープから抜けるときにLockのデストラクタがコールされ
  // csがクリティカルセクションから抜ける
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // スレッド生成
  CThread.Create( CThreadProc, NULL );

  // 適当に待ってる
  Sleep( 1000 );

  // 変数にアクセス前にロック
  cs.Enter();

  // 結果をゲット
  Sint32 ret = g_Result;

  // 変数使い終わったのでアクセスロック解除
  cs.Leave();

  // スレッド終わってる？
  while ( !CThread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		~CAutoLock()
		{
			m_cs.Leave();
		}
	};
}
}

