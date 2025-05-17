#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/ClassReference.h"
#include "Class/Common/Object/CBaseObject.h"
#include "Interface/Network/ISocketTCP.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Network
{
	class CSocketTCP : public CBaseObject, public ISocketTCP
	{
	protected:
		CNetworkManager	*m_pManager;
		SOCKET			m_Socket;
		char			m_HostName[64];
		Uint16			m_Port;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CSocketTCP( CNetworkManager *pMgr, SOCKET Socket, const char *pTargetHost, Uint16 TargetPort );
		virtual ~CSocketTCP();

		virtual Bool Send( const void *pData, Sint32 Size );
		virtual Bool Recv( void *pData, Sint32 Size );
	};
}
}

