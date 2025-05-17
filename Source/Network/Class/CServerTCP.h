#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/ClassReference.h"
#include "Class/Common/Object/CBaseObject.h"
#include "Class/Common/Object/CBaseList.h"
#include "Thread/Thread.h"
#include "Interface/Network/IServerTCP.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Network
{
	class CServerTCP : public CBaseObject, public IServerTCP
	{
	protected:
		static void AcceptFunc( void *pData );

	protected:
		CNetworkManager				*m_pManager;
		SOCKET						m_Socket;
		Uint16						m_Port;
		CBaseList					m_ClientList;
		ClientControlCallback		m_pCallbackRecieve;

		Thread::CThread				m_Thread;
		Thread::CCriticalSection	m_CS;

	public:
		virtual void AcceptThread( void );
		virtual void GetMakeError( Sint32 ErrorCode );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual Uint16 GetPort( void );

	public:
		CServerTCP( CNetworkManager *pMgr, SOCKET Socket, Uint16 Port );
		virtual ~CServerTCP();

		virtual void AddClient( CServerClientTCP *pClient );
		virtual void SubClient( CServerClientTCP *pClient );

		virtual Bool Start( ClientControlCallback pCallback );
		virtual Bool SendAllClient( const void *pData, Sint32 Size );
	};
}
}

