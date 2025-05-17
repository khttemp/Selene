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
#include "Class/Common/Core/CCore.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace System
{
/**
@brief �V�X�e��������
@author �t���`
@param IsSetExePath		[in] �J�����g�f�B���N�g�������s�t�@�C���̏ꏊ�ɋ����I�ɕύX���邩�̗L��
@param IsCreateLogFile	[in] ���O�t�@�C���𐶐����邩�ǂ���
@param IsSSE			[in] SSE�̎g�p�L��
@retval true	����
@retval false	���s

@note
Selene�V�X�e���̏��������s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // �V�X�e���̋N��
  if ( System::Initialize() )
  {  
  }

  System::Finalize();            // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
SELENE_DLL_API Bool Initialize( Bool IsSetExePath = true, Bool IsCreateLogFile = true, Bool IsSSE = true );

/**
@brief �V�X�e���I��
@author �t���`

@note
Selene�V�X�e���̏I�������܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // �V�X�e���̋N��
  if ( System::Initialize() )
  {  
  }

  System::Finalize();            // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
SELENE_DLL_API void Finalize( void );

/**
@brief ���d�N���u���b�N
@author �t���`
@param pApplicationName	[in] �A�v���P�[�V������
@retval false	���ɓ����̃A�v���P�[�V�������N�����Ă���
@retval true	�����̃A�v���P�[�V�����͑��݂��Ȃ�

@note
�Ԃ�lfalse���ɃA�v���P�[�V�������I�������邱�Ƃ�<BR>
���d�N����h�~���邱�Ƃ��ł��܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // �V�X�e���̋N��
  if ( System::Initialize() )
  {  
    // ���d�N���`�F�b�N
    if ( System::BlockDualBoot( "Application Name" ) )
    {
    }
  }

  System::Finalize();            // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
SELENE_DLL_API Bool BlockDualBoot( const char *pApplicationName );

/**
@brief �J�����g�f�B���N�g�����Z�b�g
@author �t���`

@note
�J�����g�f�B���N�g�����A�v���P�[�V�����̎��s�t�H���_�ɐݒ肵�܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // �V�X�e���̋N��
  if ( System::Initialize() )
  {  
    // �J�����g�f�B���N�g�������s�t�@�C���̃t�H���_�ɂ���
    System::ResetCurrentDirectory();
  }

  System::Finalize();            // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
SELENE_DLL_API void ResetCurrentDirectory( void );

/**
@brief �f�B���N�g������
@author �t���`
@param pPath	[in] �t�H���_�p�X

@note
�w��p�X�փf�B���N�g���𐶐����܂��B<BR>
�r���̃t�H���_�����݂��Ȃ��ꍇ�A�S�Ă̊K�w�ɑ΂��ăt�H���_���쐬���Ă����܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // �V�X�e���̋N��
  if ( System::Initialize() )
  {  
    // �J�����g�f�B���N�g�������s�t�@�C���̃t�H���_�ɂ���
    System::ResetCurrentDirectory();

    // �J�����g�f�B���N�g���̏ꏊ�ȉ��Ƀt�H���_����
    // �����s�t�@�C���̏ꏊ�Ƀt�H���_���@��
    System::DirectoryCreate( "Save\\Config" );
  }

  System::Finalize();            // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
SELENE_DLL_API void DirectoryCreate( const char *pPath );

/**
@brief Core�̎擾
@author �t���`
@return ICore�C���^�[�t�F�C�X

@note
�E�B���h�E���Ǘ�����ICore�N���X�𐶐�/�擾���܂��B<BR>
���݁A�P��ICore���������ł��܂���B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore      *pCore      = NULL;

  // �V�X�e���̋N��
  if ( System::Initialize() )
  {
    // ICore�̐���
    ICore *pCore = System::CreateCore();
    if ( pCore == NULL ) goto EXIT;      // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�  
  }

EXIT:
  SAFE_RELEASE( pCore );            // �R�A�̉��

  System::Finalize();              // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
SELENE_DLL_API ICore *CreateCore( void );

/**
@brief SSE�̃T�|�[�g�̗L��
@author �t���`
@return	SSE�̃T�|�[�g�̗L��

@note
�g�p���Ă���CPU��SSE���T�|�[�g���Ă��邩�𒲂ׂ܂��B<BR>
���̊֐���Initialize()��IsSSE��false���w�肷��Ƃ��Ȃ炸false��Ԃ��܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // �V�X�e���̋N��
  if ( System::Initialize() )
  {  
    // SSE�T�|�[�g���Ă�H
    if ( System::IsSupportSSE() )
    {
      // SSE��SIMD���Z
    }
    else
    {
      // FPU�ŕ��ʂɉ��Z
    }
  }

  System::Finalize();        // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
SELENE_DLL_API Bool IsSupportSSE( void );

/**
@brief �g�p����CPU�ԍ���ݒ�
@author �t���`
@param No	[in] CPU�ԍ�

@note
���݂̃X���b�h�Ŏg�p����CPU�̔ԍ���ݒ肵�܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // �V�X�e���̋N��
  if ( System::Initialize() )
  {  
    // ���݂̃X���b�h��CPU1�œ�����
    System::SetThreadCPUNo( 1 );
  }

  System::Finalize();        // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
SELENE_DLL_API void SetThreadCPUNo( Sint32 No );
}
}
