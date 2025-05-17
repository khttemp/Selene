#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Network
{
	/**
		@brief TCP�ڑ��N���C�A���g�N���X
		@author �t���`

		@note
		Selene�Ŏg�p����l�b�g���[�N�������s���܂��B
	*/
	class ISocketTCP : public IInterface
	{
	public:
		virtual ~ISocketTCP() {}

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

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Network::INetworkManager	*pNetworkMgr	= NULL;
  Network::ISocketTCP		*pTCP			= NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �T�[�o�[��TCP���g���Đڑ�����
  pTCP = pNetworkMgr->ConnectByTCP( "127.0.0.1", 80 );
  if ( pTCP == NULL )
  {
    // �G���[���b�Z�[�W
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  const Uint32 MAX_PACKET_SIZE = 256;
  Sint8 PacketBuffer[MAX_PACKET_SIZE];

  // �f�[�^���M
  if ( !pTCP->Send( PacketBuffer, sizeof(PacketBuffer) ) )
  {
    // �G���[���b�Z�[�W
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // TCP�ڑ������
  SAFE_RELEASE( pTCP );

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
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

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Network::INetworkManager	*pNetworkMgr	= NULL;
  Network::ISocketTCP		*pTCP			= NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �T�[�o�[��TCP���g���Đڑ�����
  pTCP = pNetworkMgr->ConnectByTCP( "127.0.0.1", 80 );
  if ( pTCP == NULL )
  {
    // �G���[���b�Z�[�W
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  const Uint32 MAX_PACKET_SIZE = 256;
  Sint8 PacketBuffer[MAX_PACKET_SIZE];

  // �f�[�^��M
  if ( !pTCP->Recv( PacketBuffer, sizeof(PacketBuffer) ) )
  {
    // �G���[���b�Z�[�W
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // TCP�ڑ������
  SAFE_RELEASE( pTCP );

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Bool Recv( void *pData, Sint32 Size ) = 0;
	};
}
}

