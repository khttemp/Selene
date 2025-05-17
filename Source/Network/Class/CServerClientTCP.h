#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/ClassReference.h"
#include "Class/Common/Object/CBaseObject.h"
#include "Thread/Thread.h"
#include "Interface/Network/IServerTCP.h"
#include "Interface/Network/IServerClientTCP.h"
#include "Interface/Network/INetworkManager.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Network
{
	class CServerClientTCP : public CBaseObject, public IServerClientTCP
	{
	protected:
		static void CallbackRecieve( void *pData );

	protected:
		CServerTCP					*m_pServer;
		SOCKET						m_Socket;
		ClientControlCallback		m_pCallbackRecieve;
		SOCKADDR_IN					m_SocketAddrIn;
		SHostInfo					m_HostInfo;
		char						m_StrIP[64];

		Thread::CThread				m_Thread;
		Thread::CCriticalSection	m_CS;

	protected:
		void Recieve( void );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CServerClientTCP( CServerTCP *pServer, SOCKET &Socket, SOCKADDR_IN &SocketAddrIn, SHostInfo &HostInfo, ClientControlCallback pCallback );
		~CServerClientTCP();

		virtual Bool Send( const void *pData, Sint32 Size );
		virtual Bool Recv( void *pData, Sint32 Size );

		virtual void GetHostInfo( SHostInfo &Info );
	};
}
}

