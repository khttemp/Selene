#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/ClassReference.h"
#include "Class/Common/Object/CBaseObject.h"
#include "Class/Common/Object/CBaseList.h"
#include "Interface/Network/INetworkManager.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Network
{
	class CNetworkManager : public CBaseObject, public INetworkManager
	{
	protected:
		WSADATA			m_WsaData;
		SHostInfo		m_LocalHost;
		char			m_LastError[1024];
		CBaseList		m_ClientList;
		CBaseList		m_ServerList;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CNetworkManager( void );
		virtual ~CNetworkManager();

		virtual const char *GetLastErrorString( void );
		virtual void GetMakeError( Sint32 ErrorCode );
		virtual HOSTENT *GetHostEntry( const char *pServerString );
		virtual Bool GetHostInfo( const HOSTENT *pEntry, SHostInfo *pHost );

		virtual void GetHostInfo( SHostInfo &Info );

		virtual ISocketTCP *ConnectByTCP( const char *pTargetHost, Uint16 TargetPort );
		virtual void AddClient( ISocketTCP *pTCP );
		virtual void SubClient( ISocketTCP *pTCP );

		virtual IServerTCP *CreateServer( Uint16 Port, Uint32 ConnectMax );
		virtual void AddServer( IServerTCP *pTCP );
		virtual void SubServer( IServerTCP *pTCP );
	};
}
}

