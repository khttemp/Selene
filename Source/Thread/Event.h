#pragma once


/**
	@file
	@brief �C�x���g����
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Thread
{
	/**
		@brief �X���b�h�p�C�x���g�I�u�W�F�N�g
		@author �t���`
	*/
	class SELENE_DLL_API CEvent
	{
	private:
		HANDLE m_EventHandle[MAXIMUM_WAIT_OBJECTS];		///< �C�x���g�n���h��
		Sint32 m_HandleCount;							///< �C�x���g��

	public:
/**
@brief �R���X�g���N�^
@author �t���`
@param IsSignal		[in] �V�O�i����Ԃŏ���������ꍇ��true
@param Count		[in] �C�x���g�̃J�E���g�iMAXIMUM_WAIT_OBJECTS�ȉ��j
*/
		CEvent( Bool IsSignal = false, Sint32 Count = 1 );

/**
@brief �f�X�g���N�^
@author �t���`
*/
		virtual ~CEvent();

/**
@brief �w�肳�ꂽ�C�x���g���V�O�i����Ԃɐݒ�
@author �t���`
@param No	[in] �V�O�i����Ԃ���C�x���g�̔ԍ�

@note
�w�肵���ԍ��̃C�x���g���V�O�i����Ԃɐݒ肵�܂��B

@code
#include "Selene.h"

using namespace Selene;

// 5�̃C�x���g����
Event Event( false, 5 );

void ThreadProc( void *pData )
{
  // No=3�̃C�x���g���V�O�i���H
  while ( !Event.IsSignal( 3 ) )
  {
    // ���΂��҂�
    Sleep( 1000 );
  }

  // No=3�̃C�x���g���V�O�i���ɂ���
  Event.Reset( 3 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Thread Thread;

  // �X���b�h����
  Thread.Create( ThreadProc, NULL );

  // �K���ɑ҂��Ă�ӂ�
  Sleep( 1000 );

  // No=3�̃C�x���g���V�O�i���ɂ���
  Event.Set( 3 );

  // �X���b�h�I����Ă�H
  while ( !Thread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		virtual void Set( Sint32 No = 0 );

/**
@brief �w�肳�ꂽ�C�x���g���V�O�i����Ԃɐݒ�
@author �t���`
@param No	[in] ��V�O�i����Ԃ���C�x���g�̔ԍ�

@note
�w�肵���ԍ��̃C�x���Ƃ���V�O�i����Ԃɐݒ肵�܂��B

@code
#include "Selene.h"

using namespace Selene;

// 5�̃C�x���g����
Event Event( false, 5 );

void ThreadProc( void *pData )
{
  // No=3�̃C�x���g���V�O�i���H
  while ( !Event.IsSignal( 3 ) )
  {
    // ���΂��҂�
    Sleep( 1000 );
  }

  // No=3�̃C�x���g���V�O�i���ɂ���
  Event.Reset( 3 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Thread Thread;

  // �X���b�h����
  Thread.Create( ThreadProc, NULL );

  // �K���ɑ҂��Ă�ӂ�
  Sleep( 1000 );

  // No=3�̃C�x���g���V�O�i���ɂ���
  Event.Set( 3 );

  // �X���b�h�I����Ă�H
  while ( !Thread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		virtual void Reset( Sint32 No = 0 );

/**
@brief �w�肵���C�x���g���V�O�i����Ԃ��`�F�b�N
@author �t���`
@param No	[in] �`�F�b�N����C�x���g�̔ԍ�
@retval false	��V�O�i�����
@retval true	�V�O�i�����

@note
�w�肵���C�x���g���V�O�i����ԂɂȂ��Ă��邩���`�F�b�N���܂��B

@code
#include "Selene.h"

using namespace Selene;

// 5�̃C�x���g����
Event Event( false, 5 );

void ThreadProc( void *pData )
{
  // No=3�̃C�x���g���V�O�i���H
  while ( !Event.IsSignal( 3 ) )
  {
    // ���΂��҂�
    Sleep( 1000 );
  }

  // No=3�̃C�x���g���V�O�i���ɂ���
  Event.Reset( 3 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Thread Thread;

  // �X���b�h����
  Thread.Create( ThreadProc, NULL );

  // �K���ɑ҂��Ă�ӂ�
  Sleep( 1000 );

  // No=3�̃C�x���g���V�O�i���ɂ���
  Event.Set( 3 );

  // �X���b�h�I����Ă�H
  while ( !Thread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		virtual Bool IsSignal( Sint32 No = 0 );

/**
@brief �S�ẴC�x���g���V�O�i����Ԃ��`�F�b�N
@author �t���`
@retval false	��V�O�i�����
@retval true	�V�O�i�����

@note
�S�ẴC�x���g���V�O�i����ԂɂȂ��Ă��邩���`�F�b�N���܂��B

@code
#include "Selene.h"

using namespace Selene;

// 3�̃C�x���g����
Event Event( false, 3 );

void ThreadProc( void *pData )
{
  // �S���V�O�i���ɂȂ�܂ő҂�
  while ( !Event.IsSignalAll() )
  {
    // �܂��Ȃ̂ł��΂��҂�
    Sleep( 1000 );
  }
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Thread Thread;

  // �X���b�h����
  Thread.Create( ThreadProc, NULL );

  // �K���ɑ҂��Ă�ӂ�
  Sleep( 1000 );

  // �C�x���g���V�O�i���ɂ���
  Event.Set( 0 );
  Event.Set( 1 );
  Event.Set( 2 );

  // �X���b�h�I����Ă�H
  while ( !Thread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		virtual Bool IsSignalAll( void );

/**
@brief �V�O�i����ԂɂȂ����C�x���g���擾
@author �t���`
@param TimeOut		[in] �^�C���A�E�gms���ԁi-1�Ŗ����j
@retval -1		�^�C���A�E�g
@retval 0�ȏ�	�V�O�i����ԂɂȂ����C�x���g�ԍ�

@note
�w�莞�ԑҋ@���P�ł��V�O�i����ԂɂȂ����炻�̏u�Ԃɂ��̃C�x���g�̔ԍ���Ԃ��܂��B<BR>
�w�莞�Ԍo�߂��Ă��V�O�i����ԂɂȂ����C�x���g���Ȃ����-1��Ԃ��܂��B

@code
#include "Selene.h"

using namespace Selene;

// 3�̃C�x���g����
Event Event( false, 3 );

void ThreadProc( void *pData )
{
  // �������V�O�i���ɂȂ�܂�1�b�قǑ҂�
  Sint32 No = Event.Wait( 1000 );
  switch ( No )
  {
  case 0:
  case 1:
  case 2:
    break;
  default:
    break;
  }
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Thread Thread;

  // �X���b�h����
  Thread.Create( ThreadProc, NULL );

  // �K���ɑ҂��Ă�ӂ�
  Sleep( 1000 );

  // �C�x���g���V�O�i���ɂ���
  Event.Set( 1 );

  // �X���b�h�I����Ă�H
  while ( !Thread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		virtual Sint32 Wait( Sint32 TimeOut = -1 );

/**
@brief �V�O�i����ԂɂȂ����C�x���g���擾
@author �t���`
@param No		[in] �n���h���ԍ�
@return		�n���h��

@note
�w��ԍ��̃n���h�����擾���܂��B
*/
		virtual HANDLE GetHandle( Sint32 No );
	};
}
}

