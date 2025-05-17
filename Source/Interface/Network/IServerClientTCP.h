#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Network/INetworkManager.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Network
{
	/**
		@brief TCP�ڑ��T�[�o�[�ɐڑ����ꂽ�N���C�A���g�N���X
		@author �t���`

		@note
		Selene�Ŏg�p����l�b�g���[�N�������s���܂��B
	*/
	class IServerClientTCP : public IInterface
	{
	public:
		virtual ~IServerClientTCP() {}

/**
@brief �f�[�^���M
@author �t���`
@param pData	[in] �f�[�^�i�[�o�b�t�@
@param Size		[in] ���M�T�C�Y
@retval false	���s
@retval true	����

@note
�f�[�^�̑��M���s���܂��B<BR>
�w��T�C�Y�̑��M����������܂Ŋ֐����甲���Ă��܂���B

@code
#include "Selene.h"
#include <stdio.h>

using namespace Selene;

static void ClientRecieve( Network::IServerClientTCP *pClient );

int main()
{
  Network::INetworkManager  *pNetworkMgr  = NULL;
  Network::IServerTCP      *pServer    = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �T�[�o�[�𐶐�����
  pServer = pNetworkMgr->CreateServer( 80, 16 );
  if ( pServer == NULL )
  {
    // ���s
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // �T�[�o�[�����J�n
  pServer->Start( ClientRecieve );

  // �L�[���͂ŏI��
  getchar();

  // �T�[�o�[�����
  SAFE_RELEASE( pServer );

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}

void ClientRecieve( Network::IServerClientTCP *pClient )
{
  // �ڑ����N���C�A���g���
  Network::SHostInfo HostInfo;
  pClient->GetHostInfo( HostInfo );

  // �N���C�A���g�p���C���ʐM���[�v
  for ( ; ; )
  {
    const Uint32 MAX_PACKET_SIZE = 256;
    Sint8 PacketBuffer[MAX_PACKET_SIZE];

    // �N���C�A���g�փp�P�b�g�𑗂�
    if ( !pClient->Send( PacketBuffer, sizeof(PacketBuffer) ) )
    {
      // �G���[or�ؒf
      return;
    }
  }
}
@endcode
*/
		virtual Bool Send( const void *pData, Sint32 Size ) = 0;

/**
@brief �f�[�^��M
@author �t���`
@param pData	[in] �f�[�^�i�[�o�b�t�@
@param Size		[in] ��M�T�C�Y
@retval false	���s
@retval true	����

@note
�f�[�^�̎�M���s���܂��B<BR>
�w��T�C�Y�̎�M����������܂Ŋ֐����甲���Ă��܂���B

@code
#include "Selene.h"
#include <stdio.h>

using namespace Selene;

static void ClientRecieve( Network::IServerClientTCP *pClient );

int main()
{
  Network::INetworkManager  *pNetworkMgr  = NULL;
  Network::IServerTCP      *pServer    = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �T�[�o�[�𐶐�����
  pServer = pNetworkMgr->CreateServer( 80, 16 );
  if ( pServer == NULL )
  {
    // ���s
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // �T�[�o�[�����J�n
  pServer->Start( ClientRecieve );

  // �L�[���͂ŏI��
  getchar();

  // �T�[�o�[�����
  SAFE_RELEASE( pServer );

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}

void ClientRecieve( Network::IServerClientTCP *pClient )
{
  // �ڑ����N���C�A���g���
  Network::SHostInfo HostInfo;
  pClient->GetHostInfo( HostInfo );

  // �N���C�A���g�p���C���ʐM���[�v
  for ( ; ; )
  {
    const Uint32 MAX_PACKET_SIZE = 256;
    Sint8 PacketBuffer[MAX_PACKET_SIZE];

    // �N���C�A���g����̃p�P�b�g��҂�
    if ( !pClient->Recv( PacketBuffer, sizeof(PacketBuffer) ) )
    {
      // �G���[or�ؒf
      return;
    }
  }
}
@endcode
*/
		virtual Bool Recv( void *pData, Sint32 Size ) = 0;

/**
@brief �ڑ����ꂽ�N���C�A���g�̏��擾
@author �t���`
@param Info	[in] �N���C�A���g���

@note
�ڑ����ꂽ�N���C�A���g�̏����擾���܂��B

@code
#include "Selene.h"
#include <stdio.h>

using namespace Selene;

static void ClientRecieve( Network::IServerClientTCP *pClient );

int main()
{
  Network::INetworkManager  *pNetworkMgr  = NULL;
  Network::IServerTCP      *pServer    = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �T�[�o�[�𐶐�����
  pServer = pNetworkMgr->CreateServer( 80, 16 );
  if ( pServer == NULL )
  {
    // ���s
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // �T�[�o�[�����J�n
  pServer->Start( ClientRecieve );

  // �L�[���͂ŏI��
  getchar();

  // �T�[�o�[�����
  SAFE_RELEASE( pServer );

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}

void ClientRecieve( Network::IServerClientTCP *pClient )
{
  // �ڑ����N���C�A���g���
  Network::SHostInfo HostInfo;
  pClient->GetHostInfo( HostInfo );

  // �N���C�A���g�p���C���ʐM���[�v
  for ( ; ; )
  {
    const Uint32 MAX_PACKET_SIZE = 256;
    Sint8 PacketBuffer[MAX_PACKET_SIZE];

    // �N���C�A���g����̃p�P�b�g��҂�
    if ( !pClient->Recv( PacketBuffer, sizeof(PacketBuffer) ) )
    {
      // �G���[or�ؒf
      return;
    }
  }
}
@endcode
*/
		virtual void GetHostInfo( SHostInfo &Info ) = 0;
	};
}
}

