

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "System.h"
#include "Network/Class/CNetworkManager.h"
#include "Network/Class/CServerTCP.h"
#include "Network/Class/CServerClientTCP.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Network;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CServerTCP::AcceptFunc( void *pData )
{
	((CServerTCP*)pData)->AcceptThread();
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CServerTCP::CServerTCP( CNetworkManager *pMgr, SOCKET Socket, Uint16 Port )
	: m_pManager			( pMgr )
	, m_Socket				( Socket )
	, m_pCallbackRecieve	( NULL )
{
	m_pManager->AddServer( this );

	m_Port = Port;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CServerTCP::~CServerTCP()
{
	m_pManager->SubServer( this );

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
Uint16 CServerTCP::GetPort( void )
{
	return m_Port;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CServerTCP::GetMakeError( Sint32 ErrorCode )
{
	m_pManager->GetMakeError( ErrorCode );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CServerTCP::Start( ClientControlCallback pCallback )
{
	if ( m_pCallbackRecieve != NULL )
	{
		return false;
	}

	m_pCallbackRecieve = pCallback;

	m_Thread.Create( AcceptFunc, this );
	m_Thread.SetPriority( Thread::THREAD_PRIORITY_LOW );

	return true;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CServerTCP::AddClient( CServerClientTCP *pClient )
{
	Thread::CAutoLock Lock( m_CS );

	m_ClientList.InsertEnd( pClient );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CServerTCP::SubClient( CServerClientTCP *pClient )
{
	Thread::CAutoLock Lock( m_CS );

	m_ClientList.Erase( pClient );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CServerTCP::AcceptThread( void )
{
	SOCKADDR_IN SocketAddrIn;
	SOCKET Socket;
	HOSTENT *pEntry;
	SHostInfo HostInfo;
	Sint32 Size;

	for ( ; ; )
	{
		Size = sizeof(SOCKADDR_IN);
		Socket = ::accept( m_Socket, (SOCKADDR*)&SocketAddrIn, (int*)&Size );
		if ( Socket == INVALID_SOCKET )
		{
			return;
		}

		if ( m_Socket == INVALID_SOCKET )
		{
			return;
		}

		pEntry = m_pManager->GetHostEntry( ::inet_ntoa( SocketAddrIn.sin_addr ) );
		m_pManager->GetHostInfo( pEntry, &HostInfo );

		m_ClientList.InsertEnd( new CServerClientTCP( this, Socket, SocketAddrIn, HostInfo, m_pCallbackRecieve ) );
	}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CServerTCP::SendAllClient( const void *pData, Sint32 Size )
{
	Thread::CAutoLock Lock( m_CS );

	Bool bRet = true;

	CServerClientTCP *pClient = (CServerClientTCP*)m_ClientList.GetTop();
	while ( pClient != NULL )
	{
		if ( !pClient->Send( pData, Size ) )
		{
			bRet = false;
		}

		pClient = (CServerClientTCP*)pClient->GetNext();
	}

	return bRet;
}

