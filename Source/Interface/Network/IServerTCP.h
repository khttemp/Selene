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
	typedef void (*ClientControlCallback)( IServerClientTCP *pClient );		///< �N���C�A���g����p

	/**
		@brief TCP�ڑ��T�[�o�[�N���X
		@author �t���`

		@note
		Selene�Ŏg�p����l�b�g���[�N�������s���܂��B
	*/
	class IServerTCP : public IInterface
	{
	public:
		virtual ~IServerTCP() {}

/**
@brief �T�[�o�[�@�\���J�n
@author �t���`
@param pCallback	[in] �N���C�A���g�����p�R�[���o�b�N�֐�

@note
�T�[�o�[�@�\���J�n���A�N���C�A���g����̐ڑ���҂��܂��B<BR>
�N���C�A���g���ڑ�����邽�тɃX���b�h������A���̒�����pCallback��<BR>
�w�肵���֐��ɏ��������܂��B

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
  }
}
@endcode
*/
		virtual Bool Start( ClientControlCallback pCallback ) = 0;

/**
@brief �f�[�^���M
@author �t���`
@param pData	[in] �f�[�^�i�[�o�b�t�@
@param Size		[in] ���M�T�C�Y
@retval false	���s
@retval true	����

@note
�ڑ�����Ă���S�ẴN���C�A���g�Ƀf�[�^�̑��M���s���܂��B<BR>
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

  // �S�ẴN���C�A���g�ɑ��M
  pServer->SendAllClient( "�߂����[��", strlen("�߂����[��") + 1 );

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
  }
}
@endcode
*/
		virtual Bool SendAllClient( const void *pData, Sint32 Size ) = 0;
	};
}
}

