

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "System.h"
#include "Network/Class/CNetworkManager.h"
#include "Network/Class/CServerTCP.h"
#include "Network/Class/CSocketTCP.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Network;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CNetworkManager::CNetworkManager( void )
{
	MemoryClear( m_LastError, sizeof(m_LastError) );

	// WinSock開始
	::WSAStartup( MAKEWORD(2,0), &m_WsaData );

	// ローカルホスト
	char LocalHostName[128] = "";
	::gethostname( LocalHostName, sizeof(LocalHostName) );
	GetHostInfo( GetHostEntry( LocalHostName ), &m_LocalHost );

	// ログ
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "初期化" );
	Log_PrintCellKind( "ネットワーク" );
	Log_CellBegin( 0 );

	Log_PrintTable( 128, "ローカルホスト名", "%s", LocalHostName );
	Log_PrintTable( 128, "ホスト名", "%s", m_LocalHost.Name );
	for ( Sint32 i = 0; i < m_LocalHost.AddressCount; i++ )
	{
		Log_PrintTable( 128, "IPアドレス", "%s", m_LocalHost.Address[i] );
	}
	for ( Sint32 i = 0; i < m_LocalHost.AliasCount; i++ )
	{
		Log_PrintTable( 128, "エイリアス", "%s", m_LocalHost.Alias[i] );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CNetworkManager::~CNetworkManager()
{
	// WinSock終了
	::WSACleanup();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CNetworkManager::GetMakeError( Sint32 ErrorCode )
{
	MemoryClear( m_LastError, sizeof(m_LastError) );
	GetSocketError( ErrorCode, m_LastError, sizeof(m_LastError) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const char *CNetworkManager::GetLastErrorString( void )
{
	if ( m_LastError[0] == '\0' )
	{
		return "エラーなし";
	}
	else
	{
		return m_LastError;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HOSTENT *CNetworkManager::GetHostEntry( const char *pServerString )
{
	HOSTENT *pHostEntry = NULL;
	IN_ADDR InAddrHost;

	//------------------------------------------------------------
	// 指定された文字列がホスト名かＩＰアドレスか調べる
	//------------------------------------------------------------
	InAddrHost.s_addr = ::inet_addr( pServerString );
	if ( InAddrHost.s_addr == INADDR_NONE )
	{
		// ＩＰではないのでホスト名として処理
		pHostEntry = ::gethostbyname( pServerString );
		if ( pHostEntry == NULL )
		{
			GetMakeError( ::WSAGetLastError() );
		}
	}
	else
	{
		// ＩＰアドレスのようでふ
		pHostEntry = ::gethostbyaddr( (const char *)&InAddrHost, sizeof(IN_ADDR), AF_INET );
		if ( pHostEntry == NULL )
		{
			GetMakeError( ::WSAGetLastError() );
		}
	}

	return pHostEntry;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CNetworkManager::GetHostInfo( const HOSTENT *pEntry, SHostInfo *pHost )
{
	if ( pEntry == NULL )
	{
		return false;
	}

	//------------------------------------------------------------
	// ホスト情報の保存
	//------------------------------------------------------------
	MemoryClear( pHost, sizeof(SHostInfo) );

	// ホスト公式名
	strcpy( pHost->Name, pEntry->h_name );

	// ホストの別名
	for ( Sint32 i = 0; pEntry->h_aliases[i] != NULL; i++ )
	{
		StringCbCopy( pHost->Alias[pHost->AliasCount], sizeof(pHost->Alias[pHost->AliasCount]), pEntry->h_aliases[i] );
		pHost->AliasCount++;
	}

	// アドレス
	for ( Sint32 i = 0; pEntry->h_addr_list[i] != NULL; i++ )
	{
		const char *pAddr = ::inet_ntoa( *((IN_ADDR*)pEntry->h_addr_list[i]));
		StringCbCopy( pHost->Address[pHost->AddressCount], sizeof(pHost->Address[pHost->AddressCount]), pAddr );
		pHost->AddressCount++;
	}

	// データサイズ
	pHost->Length = pEntry->h_length;

	// データタイプ
	pHost->Type = pEntry->h_addrtype;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CNetworkManager::GetHostInfo( SHostInfo &Info )
{
	Info = m_LocalHost;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ISocketTCP *CNetworkManager::ConnectByTCP( const char *pTargetHost, Uint16 TargetPort )
{
	SOCKET Socket;
	SOCKADDR_IN SockAddr;
	HOSTENT *pHostEntry;
	SHostInfo HostInfo;

	// ログ
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "接続" );
	Log_PrintCellKind( "ネットワーク" );
	Log_CellBegin( 0 );

	Log_PrintTable( 128, "接続先", "%s:%d", pTargetHost, TargetPort );

	//------------------------------------------------------------
	// ソケット生成
	//------------------------------------------------------------
	Socket = ::socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( Socket == INVALID_SOCKET )
	{
		GetMakeError( ::WSAGetLastError() );
		goto EXIT_ERROR;
	}

	//------------------------------------------------------------
	// ホスト情報取得
	//------------------------------------------------------------
	pHostEntry = GetHostEntry( pTargetHost );
	if ( pHostEntry == NULL )
	{
		goto EXIT_ERROR;
	}

	//------------------------------------------------------------
	// ホストデータ取得
	//------------------------------------------------------------
	if ( !GetHostInfo( pHostEntry, &HostInfo ) )
	{
		goto EXIT_ERROR;
	}

	//------------------------------------------------------------
	// 接続用データ生成
	//------------------------------------------------------------
	MemoryClear( &SockAddr, sizeof(SOCKADDR_IN) );
	SockAddr.sin_family	= AF_INET;
	SockAddr.sin_port	= ::htons( TargetPort );
	SockAddr.sin_addr	= *((IN_ADDR*)pHostEntry->h_addr_list[0]);

	//------------------------------------------------------------
	// 接続
	//------------------------------------------------------------
	Sint32 Ret = ::connect( Socket, (SOCKADDR*)&SockAddr, sizeof(SOCKADDR_IN) );
	if ( Ret == SOCKET_ERROR )
	{
		GetMakeError( ::WSAGetLastError() );
		goto EXIT_ERROR;
	}

	Log_PrintStrongLine( 0x008000, "完了" );

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	//------------------------------------------------------------
	// クラス生成
	//------------------------------------------------------------
	return new CSocketTCP( this, Socket, pTargetHost, TargetPort );

EXIT_ERROR:
	if ( Socket != INVALID_SOCKET )
	{
		::closesocket( Socket );
	}

	Log_PrintStrong( 0x000000, m_LastError );
	Log_PrintStrong( 0xFF0000, "接続できませんでした。");

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CNetworkManager::AddClient( ISocketTCP *pTCP )
{
	m_ClientList.InsertEnd( (CSocketTCP*)pTCP );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CNetworkManager::SubClient( ISocketTCP *pTCP )
{
	m_ClientList.Erase( (CSocketTCP*)pTCP );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IServerTCP *CNetworkManager::CreateServer( Uint16 Port, Uint32 ConnectMax )
{
	SOCKET Socket;
	Sint32 ReturnCode;
	SOCKADDR_IN SockAddr;

	//------------------------------------------------------------
	// 同一ポートのサーバーを検索
	//------------------------------------------------------------
	CServerTCP *pServer = (CServerTCP*)m_ServerList.GetTop();
	while ( pServer != NULL )
	{
		if ( pServer->GetPort() == Port )
		{
			MemoryClear( m_LastError, sizeof(m_LastError) );
			StringCbCopy( m_LastError, sizeof(m_LastError), "既に同一ポートのサーバーが起動しています。" );
			return NULL;
		}
		pServer = (CServerTCP*)pServer->GetNext();
	}

	//------------------------------------------------------------
	// ソケット生成
	//------------------------------------------------------------
	Socket = ::socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( Socket == INVALID_SOCKET )
	{
		GetMakeError( ::WSAGetLastError() );
		goto EXIT_ERROR;
	}

	//------------------------------------------------------------
	// 接続用データ生成
	//------------------------------------------------------------
	MemoryClear( &SockAddr, sizeof(SOCKADDR_IN) );
	SockAddr.sin_family	= AF_INET;
	SockAddr.sin_port	= ::htons( Port );

	//------------------------------------------------------------
	// ソケットにアドレスとポートを関連付ける
	//------------------------------------------------------------
	ReturnCode = ::bind( Socket, (SOCKADDR*)&SockAddr, sizeof(SOCKADDR_IN) );
	if ( ReturnCode == SOCKET_ERROR )
	{
		GetMakeError( ::WSAGetLastError() );
		goto EXIT_ERROR;
	}

	//------------------------------------------------------------
	// 接続
	//------------------------------------------------------------
	ReturnCode = ::listen( Socket, ConnectMax );
	if ( ReturnCode == SOCKET_ERROR )
	{
		GetMakeError( ::WSAGetLastError() );
		goto EXIT_ERROR;
	}

	//------------------------------------------------------------
	// クラス生成
	//------------------------------------------------------------
	return new CServerTCP( this, Socket, Port );

EXIT_ERROR:
	if ( Socket != INVALID_SOCKET )
	{
		::closesocket( Socket );
	}

	Log_PrintStrong( 0x000000, m_LastError );
	Log_PrintStrong( 0xFF0000, "作成できませんでした。");

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CNetworkManager::AddServer( IServerTCP *pTCP )
{
	m_ServerList.InsertEnd( (CServerTCP*)pTCP );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CNetworkManager::SubServer( IServerTCP *pTCP )
{
	m_ServerList.Erase( (CServerTCP*)pTCP );
}

