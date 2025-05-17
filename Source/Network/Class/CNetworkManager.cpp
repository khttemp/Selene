

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

	// WinSock�J�n
	::WSAStartup( MAKEWORD(2,0), &m_WsaData );

	// ���[�J���z�X�g
	char LocalHostName[128] = "";
	::gethostname( LocalHostName, sizeof(LocalHostName) );
	GetHostInfo( GetHostEntry( LocalHostName ), &m_LocalHost );

	// ���O
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "������" );
	Log_PrintCellKind( "�l�b�g���[�N" );
	Log_CellBegin( 0 );

	Log_PrintTable( 128, "���[�J���z�X�g��", "%s", LocalHostName );
	Log_PrintTable( 128, "�z�X�g��", "%s", m_LocalHost.Name );
	for ( Sint32 i = 0; i < m_LocalHost.AddressCount; i++ )
	{
		Log_PrintTable( 128, "IP�A�h���X", "%s", m_LocalHost.Address[i] );
	}
	for ( Sint32 i = 0; i < m_LocalHost.AliasCount; i++ )
	{
		Log_PrintTable( 128, "�G�C���A�X", "%s", m_LocalHost.Alias[i] );
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
	// WinSock�I��
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
		return "�G���[�Ȃ�";
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
	// �w�肳�ꂽ�����񂪃z�X�g�����h�o�A�h���X�����ׂ�
	//------------------------------------------------------------
	InAddrHost.s_addr = ::inet_addr( pServerString );
	if ( InAddrHost.s_addr == INADDR_NONE )
	{
		// �h�o�ł͂Ȃ��̂Ńz�X�g���Ƃ��ď���
		pHostEntry = ::gethostbyname( pServerString );
		if ( pHostEntry == NULL )
		{
			GetMakeError( ::WSAGetLastError() );
		}
	}
	else
	{
		// �h�o�A�h���X�̂悤�ł�
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
	// �z�X�g���̕ۑ�
	//------------------------------------------------------------
	MemoryClear( pHost, sizeof(SHostInfo) );

	// �z�X�g������
	strcpy( pHost->Name, pEntry->h_name );

	// �z�X�g�̕ʖ�
	for ( Sint32 i = 0; pEntry->h_aliases[i] != NULL; i++ )
	{
		StringCbCopy( pHost->Alias[pHost->AliasCount], sizeof(pHost->Alias[pHost->AliasCount]), pEntry->h_aliases[i] );
		pHost->AliasCount++;
	}

	// �A�h���X
	for ( Sint32 i = 0; pEntry->h_addr_list[i] != NULL; i++ )
	{
		const char *pAddr = ::inet_ntoa( *((IN_ADDR*)pEntry->h_addr_list[i]));
		StringCbCopy( pHost->Address[pHost->AddressCount], sizeof(pHost->Address[pHost->AddressCount]), pAddr );
		pHost->AddressCount++;
	}

	// �f�[�^�T�C�Y
	pHost->Length = pEntry->h_length;

	// �f�[�^�^�C�v
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

	// ���O
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "�ڑ�" );
	Log_PrintCellKind( "�l�b�g���[�N" );
	Log_CellBegin( 0 );

	Log_PrintTable( 128, "�ڑ���", "%s:%d", pTargetHost, TargetPort );

	//------------------------------------------------------------
	// �\�P�b�g����
	//------------------------------------------------------------
	Socket = ::socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( Socket == INVALID_SOCKET )
	{
		GetMakeError( ::WSAGetLastError() );
		goto EXIT_ERROR;
	}

	//------------------------------------------------------------
	// �z�X�g���擾
	//------------------------------------------------------------
	pHostEntry = GetHostEntry( pTargetHost );
	if ( pHostEntry == NULL )
	{
		goto EXIT_ERROR;
	}

	//------------------------------------------------------------
	// �z�X�g�f�[�^�擾
	//------------------------------------------------------------
	if ( !GetHostInfo( pHostEntry, &HostInfo ) )
	{
		goto EXIT_ERROR;
	}

	//------------------------------------------------------------
	// �ڑ��p�f�[�^����
	//------------------------------------------------------------
	MemoryClear( &SockAddr, sizeof(SOCKADDR_IN) );
	SockAddr.sin_family	= AF_INET;
	SockAddr.sin_port	= ::htons( TargetPort );
	SockAddr.sin_addr	= *((IN_ADDR*)pHostEntry->h_addr_list[0]);

	//------------------------------------------------------------
	// �ڑ�
	//------------------------------------------------------------
	Sint32 Ret = ::connect( Socket, (SOCKADDR*)&SockAddr, sizeof(SOCKADDR_IN) );
	if ( Ret == SOCKET_ERROR )
	{
		GetMakeError( ::WSAGetLastError() );
		goto EXIT_ERROR;
	}

	Log_PrintStrongLine( 0x008000, "����" );

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	//------------------------------------------------------------
	// �N���X����
	//------------------------------------------------------------
	return new CSocketTCP( this, Socket, pTargetHost, TargetPort );

EXIT_ERROR:
	if ( Socket != INVALID_SOCKET )
	{
		::closesocket( Socket );
	}

	Log_PrintStrong( 0x000000, m_LastError );
	Log_PrintStrong( 0xFF0000, "�ڑ��ł��܂���ł����B");

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
	// ����|�[�g�̃T�[�o�[������
	//------------------------------------------------------------
	CServerTCP *pServer = (CServerTCP*)m_ServerList.GetTop();
	while ( pServer != NULL )
	{
		if ( pServer->GetPort() == Port )
		{
			MemoryClear( m_LastError, sizeof(m_LastError) );
			StringCbCopy( m_LastError, sizeof(m_LastError), "���ɓ���|�[�g�̃T�[�o�[���N�����Ă��܂��B" );
			return NULL;
		}
		pServer = (CServerTCP*)pServer->GetNext();
	}

	//------------------------------------------------------------
	// �\�P�b�g����
	//------------------------------------------------------------
	Socket = ::socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( Socket == INVALID_SOCKET )
	{
		GetMakeError( ::WSAGetLastError() );
		goto EXIT_ERROR;
	}

	//------------------------------------------------------------
	// �ڑ��p�f�[�^����
	//------------------------------------------------------------
	MemoryClear( &SockAddr, sizeof(SOCKADDR_IN) );
	SockAddr.sin_family	= AF_INET;
	SockAddr.sin_port	= ::htons( Port );

	//------------------------------------------------------------
	// �\�P�b�g�ɃA�h���X�ƃ|�[�g���֘A�t����
	//------------------------------------------------------------
	ReturnCode = ::bind( Socket, (SOCKADDR*)&SockAddr, sizeof(SOCKADDR_IN) );
	if ( ReturnCode == SOCKET_ERROR )
	{
		GetMakeError( ::WSAGetLastError() );
		goto EXIT_ERROR;
	}

	//------------------------------------------------------------
	// �ڑ�
	//------------------------------------------------------------
	ReturnCode = ::listen( Socket, ConnectMax );
	if ( ReturnCode == SOCKET_ERROR )
	{
		GetMakeError( ::WSAGetLastError() );
		goto EXIT_ERROR;
	}

	//------------------------------------------------------------
	// �N���X����
	//------------------------------------------------------------
	return new CServerTCP( this, Socket, Port );

EXIT_ERROR:
	if ( Socket != INVALID_SOCKET )
	{
		::closesocket( Socket );
	}

	Log_PrintStrong( 0x000000, m_LastError );
	Log_PrintStrong( 0xFF0000, "�쐬�ł��܂���ł����B");

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

