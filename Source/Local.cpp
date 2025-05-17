

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/File/CFileHtmlLog.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
static const char VERSION_STRING[] = "Selene/Lue - Beta 1.0.3 - 2008.04.09";


//-----------------------------------------------------------------------------------
// VARIABLE
//-----------------------------------------------------------------------------------
static File::CFileHtmlLog *g_pHtmlLogFile;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::MBtoWC( const char In[], wchar_t Out[], Sint32 Size )
{
	::MultiByteToWideChar( CP_ACP, 0, In, -1, Out, Size );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::WCtoMB( const wchar_t In[], char Out[], Sint32 Size )
{
	::WideCharToMultiByte( CP_ACP, 0, In, -1, Out, Size, NULL, NULL );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::GetExePath( char *pPath, Sint32 Size )
{
	MemoryClear( pPath, Size );

	::GetModuleFileName( ::GetModuleHandle( NULL ), pPath, Size );
	Sint32 Len = (Sint32)strlen( pPath );

	while ( pPath[Len] != '\\' )
	{
		pPath[Len] = '\0';
		if ( --Len < 0 ) break;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint16 Selene::GetCharaCode( const char *pStr )
{
	const unsigned char *pSrc = (const unsigned char*)pStr;

	if ( Is2ByteChara( pSrc[0] ) )
	{
		return (pSrc[0] << 8) | pSrc[1];
	}
	else
	{
		return pSrc[0];
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
char *Selene::GetSocketError( Sint32 ErrorCode, char *pErrStr, Sint32 ErrStrSize )
{
	static char String[128] = "";

	switch ( ErrorCode )
	{
	case WSABASEERR:				StringCbCopy( String, sizeof(String), "エラーは発生していない" );								break;
	case WSAEINTR:					StringCbCopy( String, sizeof(String), "関数呼び出しが中断された" );								break;
	case WSAEBADF:					StringCbCopy( String, sizeof(String), "無効なファイルハンドル" );								break;
	case WSAEACCES:					StringCbCopy( String, sizeof(String), "アクセスが拒否された" );									break;
	case WSAEFAULT:					StringCbCopy( String, sizeof(String), "無効なバッファアドレス" );								break;
	case WSAEINVAL:					StringCbCopy( String, sizeof(String), "無効な引数が渡された" );									break;
	case WSAEMFILE:					StringCbCopy( String, sizeof(String), "使用中のソケットの数が多すぎる" );						break;
	case WSAEWOULDBLOCK:			StringCbCopy( String, sizeof(String), "操作はブロッキングされる" );								break;
	case WSAEINPROGRESS:			StringCbCopy( String, sizeof(String), "すでにブロッキング手続きが実行されている" );				break;
	case WSAEALREADY:				StringCbCopy( String, sizeof(String), "要求された操作は既に実行中、または実行済み" );			break;
	case WSAENOTSOCK:				StringCbCopy( String, sizeof(String), "指定されたソケットが無効である" );						break;
	case WSAEDESTADDRREQ:			StringCbCopy( String, sizeof(String), "操作の実行に送信先アドレスが必要" );						break;
	case WSAEMSGSIZE:				StringCbCopy( String, sizeof(String), "メッセージサイズが大きすぎる" );							break;
	case WSAEPROTOTYPE:				StringCbCopy( String, sizeof(String), "ソケットは要求されたプロトコルに適合していない" );		break;
	case WSAENOPROTOOPT:			StringCbCopy( String, sizeof(String), "不正なプロトコルオプション" );							break;
	case WSAEPROTONOSUPPORT:		StringCbCopy( String, sizeof(String), "プロトコルがサポートされていない" );						break;
	case WSAESOCKTNOSUPPORT:		StringCbCopy( String, sizeof(String), "指定されたソケットタイプはサポートされていない" );		break;
	case WSAEOPNOTSUPP:				StringCbCopy( String, sizeof(String), "要求された操作はサポートされていない" );					break;
	case WSAEPFNOSUPPORT:			StringCbCopy( String, sizeof(String), "プロトコルファミリがサポートされていない" );				break;
	case WSAEAFNOSUPPORT:			StringCbCopy( String, sizeof(String), "アドレスファミリがサポートされていない" );				break;
	case WSAEADDRINUSE:				StringCbCopy( String, sizeof(String), "アドレスは既に使用中である" );							break;
	case WSAEADDRNOTAVAIL:			StringCbCopy( String, sizeof(String), "無効なネットワークアドレス" );							break;
	case WSAENETDOWN:				StringCbCopy( String, sizeof(String), "ネットワークがダウンしている" );							break;
	case WSAENETUNREACH:			StringCbCopy( String, sizeof(String), "指定されたネットワークホストに到達できない" );			break;
	case WSAENETRESET:				StringCbCopy( String, sizeof(String), "ネットワーク接続が破棄された" );							break;
	case WSAECONNABORTED:			StringCbCopy( String, sizeof(String), "ネットワーク接続が破棄された" );							break;
	case WSAECONNRESET:				StringCbCopy( String, sizeof(String), "ネットワーク接続が相手によって破棄された" );				break;
	case WSAENOBUFS:				StringCbCopy( String, sizeof(String), "バッファが不足している" );								break;
	case WSAEISCONN:				StringCbCopy( String, sizeof(String), "ソケットは既に接続されている" );							break;
	case WSAENOTCONN:				StringCbCopy( String, sizeof(String), "ソケットは接続されていない" );							break;
	case WSAESHUTDOWN:				StringCbCopy( String, sizeof(String), "ソケットはシャットダウンされている" );					break;
	case WSAETOOMANYREFS:			StringCbCopy( String, sizeof(String), "参照の数が多すぎる" );									break;
	case WSAETIMEDOUT:				StringCbCopy( String, sizeof(String), "接続要求がタイムアウトした" );							break;
	case WSAECONNREFUSED:			StringCbCopy( String, sizeof(String), "接続が拒否された" );										break;
	case WSAELOOP:					StringCbCopy( String, sizeof(String), "ループ" );												break;
	case WSAENAMETOOLONG:			StringCbCopy( String, sizeof(String), "名前が長すぎる" );										break;
	case WSAEHOSTDOWN:				StringCbCopy( String, sizeof(String), "ホストがダウンしている" );								break;
	case WSAEHOSTUNREACH:			StringCbCopy( String, sizeof(String), "ホストへの経路がない" );									break;
	case WSAENOTEMPTY:				StringCbCopy( String, sizeof(String), "ディレクトリが空ではない" );								break;
	case WSAEPROCLIM:				StringCbCopy( String, sizeof(String), "プロセスの数が多すぎる" );								break;
	case WSAEUSERS:					StringCbCopy( String, sizeof(String), "ユーザの数が多すぎる" );									break;
	case WSAEDQUOT:					StringCbCopy( String, sizeof(String), "ディスククォータ" );										break;
	case WSAESTALE:					StringCbCopy( String, sizeof(String), "実行しようとした操作は廃止されている" );					break;
	case WSAEREMOTE:				StringCbCopy( String, sizeof(String), "リモート" );												break;
	case WSASYSNOTREADY:			StringCbCopy( String, sizeof(String), "ネットワークサブシステムが利用できない" );				break;
	case WSAVERNOTSUPPORTED:		StringCbCopy( String, sizeof(String), "Winsock.dllのバージョンが範囲外である" );				break;
	case WSANOTINITIALISED:			StringCbCopy( String, sizeof(String), "WinSockシステムが初期化されていない" );					break;
	case WSAEDISCON:				StringCbCopy( String, sizeof(String), "シャットダウン処理中" );									break;
	case WSAENOMORE:				StringCbCopy( String, sizeof(String), "データはこれ以上存在しない" );							break;
	case WSAECANCELLED:				StringCbCopy( String, sizeof(String), "操作は取り消された" );									break;
	case WSAEINVALIDPROCTABLE:		StringCbCopy( String, sizeof(String), "サービスプロバイダの関数テーブルが無効" );				break;
	case WSAEINVALIDPROVIDER:		StringCbCopy( String, sizeof(String), "サービスプロバイダが無効" );								break;
	case WSAEPROVIDERFAILEDINIT:	StringCbCopy( String, sizeof(String), "サービスプロバイダの初期化に失敗した" );					break;
	case WSASYSCALLFAILURE:			StringCbCopy( String, sizeof(String), "システムコールに失敗した" );								break;
	case WSASERVICE_NOT_FOUND:		StringCbCopy( String, sizeof(String), "サービスが見つからない" );								break;
	case WSATYPE_NOT_FOUND:			StringCbCopy( String, sizeof(String), "タイプが見つからない" );									break;
	case WSA_E_CANCELLED:			StringCbCopy( String, sizeof(String), "検索がキャンセルされた" );								break;
	case WSAEREFUSED:				StringCbCopy( String, sizeof(String), "操作は拒否された" );										break;
	case WSAHOST_NOT_FOUND:			StringCbCopy( String, sizeof(String), "ホストが見つからない" );									break;
	case WSATRY_AGAIN:				StringCbCopy( String, sizeof(String), "指定されたホストが見つからない、またはサービスの異常" );	break;
	case WSANO_RECOVERY:			StringCbCopy( String, sizeof(String), "回復不能なエラーが発生した" );							break;
	case WSANO_DATA:				StringCbCopy( String, sizeof(String), "要求されたタイプのデータレコードが見つからない" );		break;
	}

	if ( pErrStr != NULL ) StringCbCopy( pErrStr, ErrStrSize, String );

	return String;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void *Selene::MemoryAlloc( Sint32 Size )
{
	return ::HeapAlloc( ::GetProcessHeap(), HEAP_CREATE_ALIGN_16, Size );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void *Selene::MemoryClearAlloc( Sint32 Size )
{
	return ::HeapAlloc( ::GetProcessHeap(), HEAP_CREATE_ALIGN_16|HEAP_ZERO_MEMORY, Size );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::MemoryFree( void *pMem )
{
	if ( pMem != NULL )
	{
		::HeapFree( ::GetProcessHeap(), 0, pMem );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_Initialize( const char *pDir )
{
	char LogFile[MAX_PATH];
	StringCbPrintf( LogFile, sizeof(LogFile), "%sLog.html", pDir );

	g_pHtmlLogFile = new File::CFileHtmlLog( LogFile, VERSION_STRING );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_Finalize( void )
{
	SAFE_DELETE( g_pHtmlLogFile );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_Print( Sint32 Color, const char *pStr,... )
{
	if ( g_pHtmlLogFile == NULL ) return;

	char Buff[256] = "";
	StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );
	g_pHtmlLogFile->Print( Color, Buff );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintStrong( Sint32 Color, const char *pStr,... )
{
	if ( g_pHtmlLogFile == NULL ) return;

	char Buff[256] = "";
	StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );
	g_pHtmlLogFile->PrintStrong( Color, Buff );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintLine( Sint32 Color, const char *pStr,... )
{
	if ( g_pHtmlLogFile == NULL ) return;

	char Buff[256] = "";
	StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );
	g_pHtmlLogFile->PrintLine( Color, Buff );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintStrongLine( Sint32 Color, const char *pStr,... )
{
	if ( g_pHtmlLogFile == NULL ) return;

	char Buff[256] = "";
	StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );
	g_pHtmlLogFile->PrintStrongLine( Color, Buff );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintTable( Sint32 ColorTitle, Sint32 Color, const char *pTitle, const char *pKind, const char *pStr,... )
{
	char Buff[256] = "";
	StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );

	Log_TableBegin();
	Log_PrintCellTitle( ColorTitle, pTitle );
	Log_PrintCellKind( pKind );
	Log_CellBegin( 0 );
	Log_Print( Color, Buff );
	Log_CellEnd();
	Log_TableEnd();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintTable( Sint32 Width, const char *pTitle, const char *pStr,... )
{
	char Buff[256] = "";
	StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );

	Log_TableBegin();
	Log_CellBegin( Width );
	Log_PrintLine( 0x000000, pTitle );
	Log_CellEnd();
	Log_CellBegin( 0 );
	Log_PrintLine( 0x000000, Buff );
	Log_CellEnd();
	Log_TableEnd();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintCellTitle( Sint32 Color, const char *pTitle )
{
	Log_CellBegin( 64 );
	Log_PrintStrong( Color, pTitle );
	Log_CellEnd();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintCellKind( const char *pKind,... )
{
	char Buff[256] = "";
	StringCbPrintf( Buff, sizeof(Buff), pKind, (char*)(&pKind+ 1) );

	Log_CellBegin( 192 );
	Log_Print( 0x000000, Buff );
	Log_CellEnd();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_TableBegin( void )
{
	if ( g_pHtmlLogFile == NULL ) return;
	g_pHtmlLogFile->TableBegin();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_TableEnd( void )
{
	if ( g_pHtmlLogFile == NULL ) return;
	g_pHtmlLogFile->TableEnd();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_TableLine( Sint32 Bold )
{
	if ( g_pHtmlLogFile == NULL ) return;
	g_pHtmlLogFile->TableLine( Bold );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_CellBegin( Sint32 Width )
{
	if ( g_pHtmlLogFile == NULL ) return;
	g_pHtmlLogFile->CellBegin( Width );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_CellEnd( void )
{
	if ( g_pHtmlLogFile == NULL ) return;
	g_pHtmlLogFile->CellEnd();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::GetDesktopDirectory( char *pPath, Sint32 PathSize )
{
	pPath[0] = '\0';

	ITEMIDLIST *pidl = NULL;
	IMalloc *pMalloc = NULL;
	char Temp[MAX_PATH] = "";

	if FAILED( ::SHGetMalloc( &pMalloc ) ) return false;

	::SHGetSpecialFolderLocation( ::GetDesktopWindow(), CSIDL_DESKTOP, &pidl );
	::SHGetPathFromIDList( pidl, Temp );

	pMalloc->Free( pidl );
	SAFE_RELEASE( pMalloc );

	StringCbCopy( pPath, PathSize, Temp );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::GetLongFullPathName( const char *pSrcPath, char *pDstPath, Sint32 DstPathSize )
{
	pDstPath[0] = '\0';

	Sint32 Len = (Sint32)strlen( pSrcPath );
	while ( pSrcPath[Len] != '\\' ) if ( --Len < 0 ) break;
	if ( Len < 0 )
	{
		StringCbCat( pDstPath, DstPathSize, pSrcPath );
	}
	else
	{
		HANDLE hFind;
		WIN32_FIND_DATA FindData;
		char LongPath[MAX_PATH] = "";
		char Temp[MAX_PATH] = "";

		// 親ディレクトリを取得
		StringCbCopy( Temp, sizeof(Temp), pSrcPath );
		Temp[Len] = '\0';
		GetLongFullPathName( Temp, LongPath, sizeof(LongPath) );

		// ファイル名検索
		hFind = ::FindFirstFile( pSrcPath, &FindData );
		if ( hFind == INVALID_HANDLE_VALUE )
		{
			StringCbCat( pDstPath, DstPathSize, LongPath );
		}
		else
		{
			::FindClose( hFind );

			StringCbCat( pDstPath, DstPathSize, LongPath );
			StringCbCat( pDstPath, DstPathSize, "\\" );
			StringCbCat( pDstPath, DstPathSize, FindData.cFileName );
		}
	}
}

