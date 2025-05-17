#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "CriticalSection.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Thread
{
	/**
		@brief �X���b�h���s�D��x
		@author �t���`
	*/
	enum eCThreadPriority
	{
		THREAD_PRIORITY_LOW		= -2,		/// �Ⴂ
		THREAD_PRIORITY_MIDDLE	= -1,		/// ���Ⴂ
		THREAD_PRIORITY_DEFAULT	=  0,		/// �ʏ�
		THREAD_PRIORITY_HIGH	= +1,		/// ����
	};

	/**
		@brief �X���b�h�Ǘ�����N���X
		@author �t���`
	*/
	class SELENE_DLL_API CThread
	{
	private:
/**
@brief �X���b�h�p�֐�
@author �t���`
@param pArguments	[in] CThread�̃|�C���^

@note
�N���X�̊֐��𒼐ڂ͎w��ł��Ȃ��̂�<BR>
static�Ȋ֐����o�R���ČĂяo���B
*/
		static Uint32 __stdcall CThreadFunc( void* pArguments );

	private:
		HANDLE m_hThread;					///< �X���b�h�n���h��
		Uint32 m_ThreadId;					///< �X���b�hID
		void *m_pData;						///< �X���b�h�f�[�^�`�B�p�|�C���^
		void (*m_pMainProc)( void* );		///< �X���b�h�֐�
		CCriticalSection m_cs;				///< �N���e�B�J���Z�N�V����

	public:
/**
@brief �R���X�g���N�^
@author �t���`
*/
		CThread();

/**
@brief �f�X�g���N�^
@author �t���`
*/
		virtual ~CThread();

	public:
/**
@brief �X���b�h����
@author �t���`
@param pCThreadFunc	[in] �X���b�h�֐�
@param pData		[in] �X���b�h�Ɉ����n���f�[�^�|�C���^
@retval false	�������sor���ɃX���b�h����������Ă���
@retval true	��������

@note
�X���b�h�̐������s���܂��B

@code
#include "Selene.h"

using namespace Selene;

void CThreadProc( void *pData )
{
  // 10�b�ҋ@
  Sleep( 10 * 1000 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // �X���b�h����
  CThread.Create( CThreadProc, NULL );

  // �X���b�h�I���܂ő҂�
  while ( !CThread.WaitForExit() )
  {
    // �K��
    Sleep( 100 );
  }
  return 0;
}
@endcode
*/
		virtual Bool Create( void (*pCThreadFunc)( void* ), void *pData );

/**
@brief �X���b�h�I���҂�
@author �t���`
@retval false	�X���b�h�͏I�����Ă��Ȃ�
@retval true	�X���b�h�͏I������

@note
�X���b�h���I������̂�҂��܂�

@code
void CThreadProc( void *pData )
{
  // 10�b�ҋ@
  Sleep( 10 * 1000 );
}

void hogehoge( void )
{
	CThread CThread;

	// �X���b�h����
	CThread.Create( CThreadProc, NULL );

	// �X���b�h�I���܂ő҂�
	while ( !CThread.WaitForExit() )
	{
		// �K��
		Sleep( 100 );
	}
}
@endcode
*/
		virtual Bool WaitForExit( void );

/**
@brief �X���b�h�̗D��x�ύX
@author �t���`
@param Priority		[in] �X���b�h�����̗D��x

@note
�X���b�h�̗D��x��ύX���܂��B<BR>
�f�t�H���g�̗D��x��THREAD_PRIORITY_DEFAULT�ł��B

@code
#include "Selene.h"

using namespace Selene;

void CThreadProc( void *pData )
{
  // 10�b�ҋ@
  Sleep( 10 * 1000 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // �X���b�h����
  CThread.Create( CThreadProc, NULL );

  // �X���b�h�̗D��x��1�����N������
  CThread.SetPriority( THREAD_PRIORITY_MIDDLE );

  // �X���b�h�I���܂ő҂�
  while ( !CThread.WaitForExit() )
  {
    // �K��
    Sleep( 100 );
  }
  return 0;
}
@endcode
*/
		virtual Bool SetPriority( Sint32 Priority );

/**
@brief �X���b�h�̒��f������
@author �t���`

@note
�X���b�h�̃T�X�y���h�J�E���g�� 1 ����܂��B<BR>
�J�E���g�� 0 �ɂȂ������_�ŃX���b�h�̒��f����������܂��B

@code
#include "Selene.h"

using namespace Selene;

void CThreadProc( void *pData )
{
  // 10�b�ҋ@
  Sleep( 10 * 1000 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // �X���b�h����
  CThread.Create( CThreadProc, NULL );

  // �X���b�h�ꎞ��~
  CThread.Suspend();

  // �K���ɑ҂��Ă�ӂ�
  Sleep( 1000 );

  // �X���b�h�ĊJ
  CThread.Resume();

  // �X���b�h�I���܂ő҂�
  while ( !CThread.WaitForExit() )
  {
    // �K��
    Sleep( 100 );
  }
  return 0;
}
@endcode
*/
		virtual void Resume( void );

/**
@brief �X���b�h�̎��s�𒆒f
@author �t���`

@note
�w�肳�ꂽ�X���b�h�̎��s�����f����A<BR>
���̃X���b�h�̃T�X�y���h�J�E���g�� 1 �����܂��B

@code
void CThreadProc( void *pData  )
{
}

void hogehoge( void )
{
	Selene::CThread CThread;

	// �X���b�h����
	CThread.Create( CThreadProc );

	// �X���b�h�ꎞ��~
	CThread.Suspend();

	// ��
	�c

	// �X���b�h�ĊJ
	CThread.Resume();

	// ��
	�c
}
@endcode
*/
		virtual void Suspend( void );

/**
@brief �X���b�h�̎��s���I��
@author �t���`

@note
�w�肳�ꂽ�X���b�h�̎��s�������I�����܂��B<BR>
���̊֐��ŏI��������ꍇ�̓X�^�b�N�̉���Ȃǂ��s���Ȃ��̂�<BR>
�ʏ�͎g�p���Ȃ��ł��������B<BR>
�����I�����s�킴��𓾂Ȃ��󋵂ł̂ݎg�p���ĉ������B

@code
#include "Selene.h"

using namespace Selene;

void CThreadProc( void *pData )
{
  // 10�b�ҋ@
  Sleep( 10 * 1000 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // �X���b�h����
  CThread.Create( CThreadProc, NULL );

  // �K���ɑ҂��Ă�ӂ�
  Sleep( 1000 );

  // �X���b�h�I����Ă�H
  if ( !CThread.WaitForExit() )
  {
    // �����I��
    CThread.Terminate();
  }
  return 0;
}
@endcode
*/
		virtual void Terminate( void );
	};
}
}

