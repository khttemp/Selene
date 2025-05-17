#pragma once


/**
	@file
	@brief �N���e�B�J���Z�N�V��������
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
		@brief �N���e�B�J���Z�N�V�����Ǘ��N���X
		@author �t���`
	*/
	class SELENE_DLL_API CCriticalSection
	{
	private:
		CRITICAL_SECTION m_CriticalSection;		///< �N���e�B�J���Z�N�V����

	public:
/**
@brief �R���X�g���N�^
@author �t���`
*/
		CCriticalSection();

/**
@brief �f�X�g���N�^
@author �t���`
*/
		virtual ~CCriticalSection();

/**
@brief �N���e�B�J���Z�N�V�����ɓ���
@author �t���`

@note
�N���e�B�J���Z�N�V�����ɓ���܂��B

@code
#include "Selene.h"

using namespace Selene;

CriticalSection cs;
Sint32 g_Result = 0;

void CThreadProc( void *pData )
{
  // �ϐ��ɃA�N�Z�X�O�Ƀ��b�N
  cs.Enter();

  // �K��
  for ( Sint32 i = 0; i < 100000; )
  {
    g_Result += i * i;
  }

  // �ϐ��g���I������̂ŃA�N�Z�X���b�N����
  cs.Leave();
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // �X���b�h����
  CThread.Create( CThreadProc, NULL );

  // �K���ɑ҂��Ă�
  Sleep( 1000 );

  // �ϐ��ɃA�N�Z�X�O�Ƀ��b�N
  cs.Enter();

  // ���ʂ��Q�b�g
  Sint32 ret = g_Result;

  // �ϐ��g���I������̂ŃA�N�Z�X���b�N����
  cs.Leave();

  // �X���b�h�I����Ă�H
  while ( !CThread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		void Enter( void ) const;

/**
@brief �N���e�B�J���Z�N�V�������甲����
@author �t���`

@note
�N���e�B�J���Z�N�V�������甲���܂��B

@code
#include "Selene.h"

using namespace Selene;

CriticalSection cs;
Sint32 g_Result = 0;

void CThreadProc( void *pData )
{
  // �ϐ��ɃA�N�Z�X�O�Ƀ��b�N
  cs.Enter();

  // �K��
  for ( Sint32 i = 0; i < 100000; )
  {
    g_Result += i * i;
  }

  // �ϐ��g���I������̂ŃA�N�Z�X���b�N����
  cs.Leave();
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // �X���b�h����
  CThread.Create( CThreadProc, NULL );

  // �K���ɑ҂��Ă�
  Sleep( 1000 );

  // �ϐ��ɃA�N�Z�X�O�Ƀ��b�N
  cs.Enter();

  // ���ʂ��Q�b�g
  Sint32 ret = g_Result;

  // �ϐ��g���I������̂ŃA�N�Z�X���b�N����
  cs.Leave();

  // �X���b�h�I����Ă�H
  while ( !CThread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		void Leave( void ) const;
	};

	/**
		@brief �����N���e�B�J���Z�N�V�����Ǘ��N���X
		@author �t���`
	*/
	class CAutoLock
	{
	private:
		const CCriticalSection	&m_cs;			///< �g�p����N���e�B�J���Z�N�V����

	private:
/**
@brief = �I�y���[�^�[
@author �t���`
@param	Lock [in] ����
@return	���͂Ɠ�������

�R���p�C����ʂ����߂̃_�~�[�p�B
*/
		CAutoLock & operator = ( CAutoLock &Lock ) {
			return Lock;
		}

	public:
/**
@brief �R���X�g���N�^
@author �t���`
@param cs	[in] �N���e�B�J���Z�N�V����

@note
�R���X�g���N�^���Ŏ����I�ɃN���e�B�J���Z�N�V�����ɓ���܂��B

@code
#include "Selene.h"

using namespace Selene;

CriticalSection cs;
Sint32 g_Result = 0;

void CThreadProc( void *pData )
{
  // Lock�̃R���X�g���N�^����
  // cs���N���e�B�J���Z�N�V�����ɓ���
  CAutoLock Lock( cs );

  // �K��
  for ( Sint32 i = 0; i < 100000; )
  {
    g_Result += i * i;
  }

  // �X�R�[�v���甲����Ƃ���Lock�̃f�X�g���N�^���R�[������
  // cs���N���e�B�J���Z�N�V�������甲����
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // �X���b�h����
  CThread.Create( CThreadProc, NULL );

  // �K���ɑ҂��Ă�
  Sleep( 1000 );

  // �ϐ��ɃA�N�Z�X�O�Ƀ��b�N
  cs.Enter();

  // ���ʂ��Q�b�g
  Sint32 ret = g_Result;

  // �ϐ��g���I������̂ŃA�N�Z�X���b�N����
  cs.Leave();

  // �X���b�h�I����Ă�H
  while ( !CThread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		CAutoLock( const CCriticalSection &cs )
			: m_cs	( cs )
		{
			m_cs.Enter();
		}

/**
@brief �R���X�g���N�^
@author �t���`
@param cs	[in] �N���e�B�J���Z�N�V����

@note
�R���X�g���N�^���Ŏ����I�ɃN���e�B�J���Z�N�V�����ɓ���܂��B

@code
#include "Selene.h"

using namespace Selene;

CriticalSection cs;
Sint32 g_Result = 0;

void CThreadProc( void *pData )
{
  // Lock�̃R���X�g���N�^����
  // cs���N���e�B�J���Z�N�V�����ɓ���
  CAutoLock Lock( &cs );

  // �K��
  for ( Sint32 i = 0; i < 100000; )
  {
    g_Result += i * i;
  }

  // �X�R�[�v���甲����Ƃ���Lock�̃f�X�g���N�^���R�[������
  // cs���N���e�B�J���Z�N�V�������甲����
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // �X���b�h����
  CThread.Create( CThreadProc, NULL );

  // �K���ɑ҂��Ă�
  Sleep( 1000 );

  // �ϐ��ɃA�N�Z�X�O�Ƀ��b�N
  cs.Enter();

  // ���ʂ��Q�b�g
  Sint32 ret = g_Result;

  // �ϐ��g���I������̂ŃA�N�Z�X���b�N����
  cs.Leave();

  // �X���b�h�I����Ă�H
  while ( !CThread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		CAutoLock( const CCriticalSection *cs )
			: m_cs	( *cs )
		{
			m_cs.Enter();
		}

/**
@brief �f�X�g���N�^
@author �t���`

@note
�f�X�g���N�^���Ă΂�鎞�Ɏ����I�ɃN���e�B�J���Z�N�V��������o�܂��B

@code
#include "Selene.h"

using namespace Selene;

CriticalSection cs;
Sint32 g_Result = 0;

void CThreadProc( void *pData )
{
  // Lock�̃R���X�g���N�^����
  // cs���N���e�B�J���Z�N�V�����ɓ���
  CAutoLock Lock( &cs );

  // �K��
  for ( Sint32 i = 0; i < 100000; )
  {
    g_Result += i * i;
  }

  // �X�R�[�v���甲����Ƃ���Lock�̃f�X�g���N�^���R�[������
  // cs���N���e�B�J���Z�N�V�������甲����
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // �X���b�h����
  CThread.Create( CThreadProc, NULL );

  // �K���ɑ҂��Ă�
  Sleep( 1000 );

  // �ϐ��ɃA�N�Z�X�O�Ƀ��b�N
  cs.Enter();

  // ���ʂ��Q�b�g
  Sint32 ret = g_Result;

  // �ϐ��g���I������̂ŃA�N�Z�X���b�N����
  cs.Leave();

  // �X���b�h�I����Ă�H
  while ( !CThread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		~CAutoLock()
		{
			m_cs.Leave();
		}
	};
}
}

