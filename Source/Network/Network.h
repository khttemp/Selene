#pragma once


/**
	@file
	@brief �V�X�e���n�֐��Q
	@author �t���`
*/

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CBaseList.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Network
{
/**
@brief �l�b�g���[�N�}�l�[�W���[�C���^�[�t�F�C�X����
@author �t���`
@return �l�b�g���[�N�}�l�[�W���[�C���^�[�t�F�C�X

@note
�V�K�̃l�b�g���[�N�}�l�[�W���[�C���^�[�t�F�C�X�𐶐����܂��B<BR>
�l�b�g���[�N�̃p�X�Ȃǂ̐ݒ�͑S��INetworkManager���o�R���čs���܂��B
�擾�����l�b�g���[�N�}�l�[�W���[�C���^�[�t�F�C�X�͎g�p�I����ɂ͕K��Release()���ĉ������B�B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Network::INetworkManager *pNetworkMgr = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
SELENE_DLL_API INetworkManager *CreateManager( void );
}
}

