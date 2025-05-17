

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "System.h"
#include "Network/Class/CServerClientTCP.h"
#include "Network/Class/CServerTCP.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Network;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CServerClientTCP::CallbackRecieve( void *pData )
{
	((CServerClientTCP*)pData)->Recieve();
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CServerClientTCP::CServerClientTCP( CServerTCP *pServer, SOCKET &Socket, SOCKADDR_IN &SocketAddrIn, SHostInfo &HostInfo, ClientControlCallback pCallback )
	: m_pServer				( pServer )
	, m_Socket				( Socket )
	, m_SocketAddrIn		( SocketAddrIn )
	, m_HostInfo			( HostInfo )
	, m_pCallbackRecieve	( pCallback )
{
	m_pServer->AddClient( this );

	// IP取得
	MemoryClear( m_StrIP, sizeof(m_StrIP) );
	StringCbCopy( m_StrIP, sizeof(m_StrIP), ::inet_ntoa( m_SocketAddrIn.sin_addr ) );

	m_Thread.Create( CallbackRecieve, this );
	m_Thread.SetPriority( Thread::THREAD_PRIORITY_LOW );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CServerClientTCP::~CServerClientTCP()
{
	m_pServer->SubClient( this );

	//-------------------------------------------------------
	// ソケット切断
	//-------------------------------------------------------
	// シャットダウン
	::shutdown( m_Socket, SD_BOTH );
	::closesocket( m_Socket );

	//-------------------------------------------------------
	// Acceptスレッドの終了待ち
	//-------------------------------------------------------
	while ( !m_Thread.WaitForExit() )
	{
		::SleepEx( 100, true );
	}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CServerClientTCP::Recieve( void )
{
	m_pCallbackRecieve( this );

	Release();
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CServerClientTCP::Send( const void *pData, Sint32 Size )
{
	Thread::CAutoLock Lock( m_CS );

	Sint8 *pSrcBuff = (Sint8*)pData;
	Bool bRet = true;

	Sint32 RestByte = Size;
	while ( RestByte > 0 )
	{
		// 送信
		Sint32 Send = ::send( m_Socket, pSrcBuff, RestByte, 0 );
		if ( Send > 0 )
		{
			RestByte -= Send;
			pSrcBuff += Send;
		}
		else
		{
			m_pServer->GetMakeError( ::WSAGetLastError() );
			bRet = false;
			break;
		}
	}

	return bRet;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CServerClientTCP::Recv( void *pData, Sint32 Size )
{
	Sint8 *pDstBuff = (Sint8*)pData;
	Bool bRet = true;

	Sint32 RestByte = Size;
	while ( RestByte > 0 )
	{
		// 送信
		Sint32 Recv = ::recv( m_Socket, pDstBuff, RestByte, 0 );
		if ( Recv > 0 )
		{
			RestByte -= Recv;
			pDstBuff += Recv;
		}
		else
		{
			m_pServer->GetMakeError( ::WSAGetLastError() );
			bRet = false;
			break;
		}
	}

	return bRet;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CServerClientTCP::GetHostInfo( SHostInfo &Info )
{
	Info = m_HostInfo;
}

