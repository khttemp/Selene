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
		@brief	�z�X�g���
		@author �t���`
	*/
	struct SHostInfo
	{
		char Name[64];						///< �z�X�g��
		char Alias[16][64];					///< �z�X�g�ʖ��e�[�u��
		char Address[16][64];				///< IP�A�h���X�e�[�u��
		Sint32 Type;						///< �f�[�^�^�C�v
		Sint32 Length;						///< �f�[�^�T�C�Y
		Sint32 AliasCount;					///< �G�C���A�X��
		Sint32 AddressCount;				///< IP�A�h���X��
	};

	/**
		@brief �l�b�g���[�N�Ǘ��N���X
		@author �t���`

		@note
		Selene�Ŏg�p����l�b�g���[�N�̊Ǘ����s���܂��B
	*/
	class INetworkManager : public IInterface
	{
	public:
		virtual ~INetworkManager() {}

/**
@brief �G���[������擾
@author �t���`
@return	������̃|�C���^

@note
��A�̃l�b�g���[�N�������������G���[���b�Z�[�W���擾���܂��B

@code
#include "Selene.h"
#include <stdio.h>

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Network::INetworkManager	*pNetworkMgr	= NULL;

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

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual const char *GetLastErrorString( void ) = 0;

/**
@brief �N���C�A���g����
@author �t���`
@param pTargetHost	[in] �ڑ���̃z�X�g���iIP�A�h���X�j
@param TargetPort	[in] �ڑ���̃|�[�g
@retval	NULL		���s
@retval	NULL�ȊO	�N���C�A���g�̃C���^�[�t�F�C�X

@note
�w�肵���z�X�g�ւ�TCP�ڑ������݂܂��B<BR>
�ڑ��ł����ꍇ��TCP����p�̃C���^�[�t�F�C�X���Ԃ�܂��B

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
		virtual ISocketTCP *ConnectByTCP( const char *pTargetHost, Uint16 TargetPort ) = 0;

/**
@brief �T�[�o�[�@�\�𐶐����܂�
@author �t���`
@param Port			[in] �|�[�g�ԍ�
@param ConnectMax	[in] �ڑ��ő吔
@retval	NULL		���s
@retval	NULL�ȊO	�T�[�o�[�̃C���^�[�t�F�C�X

@note
�T�[�o�[�@�\�𐶐����A���̃C���^�[�t�F�C�X���擾���܂��B<BR>
�ڑ��ł����ꍇ��TCP����p�̃C���^�[�t�F�C�X���Ԃ�܂��B

@code
#include "Selene.h"
#include <stdio.h>

using namespace Selene;

int main()
{
  Network::INetworkManager  *pNetworkMgr  = NULL;
  Network::IServerTCP      *pServer    = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �T�[�o�[�𐶐�����
  pServer = pNetworkMgr->CreateServer( HOST_PORT, 16 );
  if ( pServer == NULL )
  {
    // ���s
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

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
@endcode
*/
	virtual IServerTCP *CreateServer( Uint16 Port, Uint32 ConnectMax = 32 ) = 0;

/**
@brief �z�X�g���擾
@author �t���`
@param Info		[out] �z�X�g���

@note
��A�̃l�b�g���[�N�������������G���[���b�Z�[�W���擾���܂��B

@code
#include "Selene.h"
#include <stdio.h>

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Network::INetworkManager	*pNetworkMgr	= NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �A�v���P�[�V���������삵�Ă���PC�̃z�X�g�����擾
  SHostInfo Info;
  pNetworkMgr->GetHostInfo( Info );

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void GetHostInfo( SHostInfo &Info ) = 0;
	};
}
}

