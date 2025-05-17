

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "System.h"
#include "Network/Class/CNetworkManager.h"
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
CSocketTCP::CSocketTCP( CNetworkManager *pMgr, SOCKET Socket, const char *pTargetHost, Uint16 TargetPort )
	: m_pManager	( pMgr )
	, m_Socket		( Socket )
{
	m_pManager->AddClient( this );

	MemoryClear( m_HostName, sizeof(m_HostName) );
	StringCbCopy( m_HostName, sizeof(m_HostName), pTargetHost );
	m_Port = TargetPort;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSocketTCP::~CSocketTCP()
{
	m_pManager->SubClient( this );

	//-------------------------------------------------------
	// ソケット切断
	//-------------------------------------------------------
	// シャットダウン
	::shutdown( m_Socket, SD_BOTH );
	::closesocket( m_Socket );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSocketTCP::Send( const void *pData, Sint32 Size )
{
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
			m_pManager->GetMakeError( ::WSAGetLastError() );
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
Bool CSocketTCP::Recv( void *pData, Sint32 Size )
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
			m_pManager->GetMakeError( ::WSAGetLastError() );
			bRet = false;
			break;
		}
	}

	return bRet;
}

