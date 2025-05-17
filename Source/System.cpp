

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "System.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/File/CFileHtmlLog.h"
#include "Thread/CriticalSection.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// VARIABLE
//-----------------------------------------------------------------------------------
static Bool g_IsInitialize					= false;
static Bool g_IsSuportSSE					= false;
static Sint32 g_NumberOfProcessors			= 0;
static HANDLE g_hMutex						= NULL;
static ICore *g_pCore						= NULL;
static char g_CurrentDirectry[MAX_PATH]		= "";


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::System::Initialize( Bool IsSetExePath, Bool IsCreateLogFile, Bool IsSSE )
{
	if ( !g_IsInitialize )
	{
		g_IsInitialize = true;

		//------------------------------------------------------
		// 優先度アップ
		//------------------------------------------------------
		::SetPriorityClass( ::GetCurrentProcess(), HIGH_PRIORITY_CLASS );

		//------------------------------------------------------
		// SSE2
		//------------------------------------------------------
		if ( IsSSE )
		{
			Uint32 Flag = 0x00000000;
			_asm
			{
				push	eax
				push	ebx
				push	ecx
				push	edx

				mov		eax,	0x00000001
				_emit	0x0F
				_emit	0xA2
				mov		Flag,	edx

				pop		edx
				pop		ecx
				pop		ebx
				pop		eax
			}
			g_IsSuportSSE = (Flag & (1 << 25)) != 0;
		}

		//------------------------------------------------------
		// COMの初期化
		//------------------------------------------------------
		::CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );

		//------------------------------------------------------
		// カレントディレクトリ
		//------------------------------------------------------
		// 実行ファイルの場所へ変更する？
		if ( IsSetExePath )
		{
			GetExePath( g_CurrentDirectry, sizeof(g_CurrentDirectry) );
			::SetCurrentDirectory( g_CurrentDirectry );
		}
		else
		{
			::GetCurrentDirectory( sizeof(g_CurrentDirectry), g_CurrentDirectry );
			StringCbCat( g_CurrentDirectry, sizeof(g_CurrentDirectry), "\\" );
		}

		//------------------------------------------------------
		// ログファイル
		//------------------------------------------------------
		if ( IsCreateLogFile )
		{
			Log_Initialize( g_CurrentDirectry );
		}

		//------------------------------------------------------
		// タイマー精度設定
		//------------------------------------------------------
		::timeBeginPeriod( 1 );

		//------------------------------------------------------
		// プロセッサ数
		//------------------------------------------------------
		SYSTEM_INFO Info;
		::GetSystemInfo( &Info );
		g_NumberOfProcessors = Info.dwNumberOfProcessors;

		//------------------------------------------------------
		// ログ
		//------------------------------------------------------
		Log_TableBegin();
		Log_PrintCellTitle( 0x008000, "調査" );
		Log_PrintCellKind( "システム情報" );
		Log_CellBegin( 0 );

		Log_PrintTable( 256, "プロセッサ数", "[ %d ]", g_NumberOfProcessors );
		Log_PrintTable( 256, "SSEのサポート", "[ %s ]", g_IsSuportSSE ? "○" : "×" );

		Log_CellEnd();
		Log_TableEnd();
		Log_TableLine( 1 );

		//------------------------------------------------------
		// ODE初期化
		//------------------------------------------------------
		dInitODE();
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::System::Finalize( void )
{
	if ( g_IsInitialize )
	{
		g_IsInitialize = false;

		//------------------------------------------------------
		// ODE解放
		//------------------------------------------------------
		dCloseODE();

		//------------------------------------------------------
		// ミューテックス
		//------------------------------------------------------
		if ( g_hMutex != NULL )
		{
			::CloseHandle( g_hMutex );
		}

		//------------------------------------------------------
		// ログ用
		//------------------------------------------------------
		Log_Finalize();

		//------------------------------------------------------
		// タイマー精度復元
		//------------------------------------------------------
		::timeEndPeriod( 1 );

		//------------------------------------------------------
		// COMの解放
		//------------------------------------------------------
		::CoUninitialize();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::System::BlockDualBoot( const char *pApplicationName )
{
	if ( g_hMutex == NULL )
	{
		// 二重起動確認
		g_hMutex = ::CreateMutex( NULL, false, pApplicationName );
		if ( ::WaitForSingleObject( g_hMutex, 0 ) != WAIT_OBJECT_0 )
		{
			// すでにある
			::CloseHandle( g_hMutex );
			g_hMutex = NULL;

			return false;
		}
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ICore *Selene::System::CreateCore( void )
{
	if ( g_pCore == NULL )
	{
		g_pCore = CCore::CreateCore();
	}
	else
	{
		g_pCore->AddRef();
	}

	return g_pCore;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::System::ResetCurrentDirectory( void )
{
	::SetCurrentDirectory( g_CurrentDirectry );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::System::DirectoryCreate( const char *pPath )
{
	ResetCurrentDirectory();

	SECURITY_ATTRIBUTES Attr = { sizeof(SECURITY_ATTRIBUTES) };
	char Work[MAX_PATH] = "";
	Sint32 Pos = 0;
	Sint32 Len = (Sint32)strlen(pPath);

	while ( Pos < Len )
	{
		// フォルダ名取得
		while ( (Pos < Len) && ((pPath[Pos] != '/') && (pPath[Pos] != '\\')) )
		{
			Work[Pos] = pPath[Pos];
			Pos++;
		}

		Work[Pos] = '\0';

		::CreateDirectory( Work, &Attr );

		Work[Pos] = '\\';
		Pos++;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::System::SetThreadCPUNo( Sint32 No )
{
	// プロセッサ番号チェック
	if ( g_NumberOfProcessors == 0 )
	{
		No = 0;
	}
	else
	{
		No %= g_NumberOfProcessors;
	}

	// 設定
	HANDLE hThread = ::GetCurrentThread();
	::SetThreadIdealProcessor( hThread, No );
	::SetThreadAffinityMask( hThread, 1 << No );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::System::IsSupportSSE( void )
{
	return g_IsSuportSSE;
}

