#pragma once


/**
	@file
	@brief �A�v���P�[�V�����Ǘ��C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Color.h"
#include "Class/Common/Peripheral/CInput.h"
#include "Interface/Core/IGraphicCard.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �A�v���P�[�V�����Ǘ��C���^�[�t�F�C�X
		@author �t���`

		@note
		�E�B���h�E���Ǘ�����A�v���P�[�V�����̃R�A�̃C���^�[�t�F�C�X�ł��B
	*/
	class ICore : public IInterface
	{
	public:
		virtual ~ICore() {}

/**
@brief �R�A�̏�����
@author �t���`
@param pAppName		[in] �A�v���P�[�V������
@param FrameRate	[in] �t���[�����[�g
@retval false	���s
@retval true	����

@note
�A�v���P�[�V�����Ɋւ��鏉�������s���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Bool Initialize( const char *pAppName, eFrameRate FrameRate ) = 0;

/**
@brief �E�B���h�E����
@author �t���`
@param ScreenWidth	[in] ��ʉ���
@param ScreenHeight	[in] ��ʏc��
@param IsWindow		[in] �E�B���h�E���[�h�ŋN������ꍇtrue

@note
�E�B���h�E���쐬���A�A�v���P�[�V�������N�����܂��B<BR>
�����ł̐ݒ�ŋN����ύX�\�Ȃ��͉̂�ʃ��[�h�����ł��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void Start( Sint32 ScreenWidth, Sint32 ScreenHeight, Bool IsWindow ) = 0;

/**
@brief �E�B���h�E�̏I��
@author �t���`

@note
�E�B���h�E����̂��A�A�v���P�[�V�������I�����܂��B<BR>
���̊֐��͏I����ʒm���邾���ŁA���ۂɂ̓��C�����[�v���<BR>
�I���������s���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      // �I��
      pCore->Exit();
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void Exit( void ) = 0;

/**
@brief �A�v���P�[�V�������C������
@author �t���`
@param IsFullActive	[in] �펞����t���O
@retval false	�A�v���P�[�V�����͏I������
@retval true	�A�v���P�[�V�����͉ғ���

@note
IsFullActive��true���w�肷��ƁA<BR>
�E�B���h�E���t�H�[�J�X�������Ă����Ԃł����삵�����܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Bool Run( Bool IsFullActive = false ) = 0;

/**
@brief �E�B���h�E�n���h���擾
@author �t���`
@return �E�B���h�E�̃E�B���h�E�n���h��

@note
ICore�̏��L����E�B���h�E�̃E�B���h�E�n���h�����擾���܂��B


@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �E�B���h�E�n���h�����擾
    HWND hWnd = pCore->GetWindowHandle();

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual HWND GetWindowHandle( void ) = 0;

/**
@brief �x���`�}�[�N�p���[�h�ݒ�
@author �t���`
@param IsEnable	[in] true�ɂ���Ƃ��ׂẴE�F�C�g�������Ȃ��܂�

@note
�x���`�}�[�N�̂悤�ȑ��x�`�F�b�N������ꍇ�Ɏg���܂��B<BR>
���̃t���O��true�ɂ����VSYNC��^�C�}�[�Ȃǂ̏��������ׂďȂ���A<BR>
�o����ō��̑��x�ŏ��������܂��B<BR>
<BR>
�f�t�H���g��false�ł��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �x���`�}�[�N�p�Ɋe��E�F�C�g��OFF
    pCore->SetBenchMode( true );

    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void SetBenchMode( Bool IsEnable ) = 0;

/**
@brief Sleep�g�p�L���ݒ�
@author �t���`
@param IsEnable	[in] true�ɂ����Sleep���g�p���܂�

@note
�t���[�����[�g�̒�����Sleep���g�����ǂ�����ݒ肵�܂��B<BR>
���ɂ���Ă͌덷���傫���t���[�����[�g�����ɂȂ�Ȃ����Ƃ�����̂ŁA<BR>
���̂悤�ȏ����ł�false��ݒ肵�ĉ������B<BR>
Sleep���g��Ȃ��ꍇ�͓��RCPU����ɐ�L����悤�ɂȂ�܂��B<BR>
<BR>
�f�t�H���g��true�ł��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // ��茵���Ɏ��Ԍv��������iCPU�g�p�������ˏオ��̂Œ��Ӂj
    pCore->SetSleepUse( false );

    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void SetSleepUse( Bool IsEnable ) = 0;

/**
@brief ���z��ʏ�����ON/OFF
@author �t���`
@param IsEnable		[in] true �L�� / false ����

@note
2D�`�掞�̉��z��ʏ����̗L����ON/OFF��ݒ肵�܂��B<BR>
true�ɂ��鎖��2D�̕`�悪���z��ʂɍs����悤�ɂȂ�A<BR>
��ʉ𑜓x�Ɋ֌W�Ȃ���ʂɑ΂��铯�������ŕ`�悳���悤�ɂȂ�܂��B<BR>
<BR>
�f�t�H���g��false�ł��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // ��ʃT�C�Y���Ԃ��Ă������悤��2D�������z��ʂɕ`��
    pCore->SetVirtualScreenEnable( true );

    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void SetVirtualScreenEnable( Bool IsEnable ) = 0;

/**
@brief ���z��ʐݒ�
@author �t���`
@param RealWidth		[in] ����ʂ̉���
@param RealHeight		[in] ����ʂ̏c��
@param VirtualWidth		[in] ���z��ʂ̉���
@param VirtualHeight	[in] ���z��ʂ̏c��

@note
�ω�ʃT�C�Y�p�̐ݒ���s���܂��B<BR>
3D�p�ɉ�ʂ̃T�C�Y�����R�ɕς�����悤�ɍ���Ă���ꍇ�ł�<BR>
2D�̕`��͉��z��ʂɐݒ肳�ꂽ��ʃT�C�Y�ƌ����Ăĕ`����s���܂��B<BR>
�܂艼�z��ʂ�(640x480)�̎���(0,0)-(640,480)�ւ̑S��ʂ�2D�`����s�����ꍇ�A<BR>
���ۂ̉�ʂ̃T�C�Y��(320x240)��(1280x960)���̃T�C�Y�ł����Ă�<BR>
�S��ʂɎ����I�Ɋg��k�����ĕ`�悳���Ƃ������Ƃł��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // ��ʃT�C�Y���Ԃ��Ă������悤��2D�������z��ʂɕ`��
    pCore->SetVirtualScreenEnable( true );

    // ���z��ʃT�C�Y
    pCore->SetVirtualScreenSize( 640, 480, 800, 600 );

    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void SetVirtualScreenSize( Sint32 RealWidth, Sint32 RealHeight, Sint32 VirtualWidth, Sint32 VirtualHeight ) = 0;

/**
@brief GPU���ׂ��擾���܂��B
@author �t���`
@return GPU���ׁi���j

@note
�����܂���GPU�̕��ׂ��擾���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      // CPU�g�p��
      Float fCPU = pCore->GetCPU();
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Float GetCPU( void ) = 0;

/**
@brief FPS���擾���܂��B
@author �t���`
@return FPS

@note
�b�Ԃ̃t���[�������擾���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      // FPS
      Float fFPS = pCore->GetFPS();
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Float GetFPS( void ) = 0;

/**
@brief 1�t���[���̃|���S�������擾���܂��B
@author �t���`
@return PPS

@note
�b�Ԃ̃|���S�������擾���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      // �|���S�����擾
	  Float fPPF = pCore->GetPPF();
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Float GetPPF( void ) = 0;

/**
@brief OS�N������̎��Ԏ擾
@author �t���`
@return 1/1000�b�P�ʂ̎���

@note
OS���N�����Ă���̎��Ԃ��擾���܂��B<BR>
32Bit�ϐ��Ȃ̂Ŗ�48����1������0�ɖ߂�܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      // ���Ԏ擾
      Uint32 Time = pCore->GetMultiMediaTime();
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Uint32 GetMultiMediaTime( void ) = 0;

/**
@brief CPU�^�C�}�[�̃J�E���g�l�擾
@author �t���`
@return 1/GetSystemTimerBySec�b�P�ʂ̎���

@note
CPU�^�C�}�[�̌��݂̎��Ԃ��擾���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      // ���Ԏ擾
      Uint64 Time = pCore->GetSystemTimer();

      // �Ȃ񂩏�������
 
      // �o�ߎ��Ԏ擾
      Time = pCore->GetSystemTimer() - Time;

      // �o�ߎ��Ԃ�1�b������́���
      Float fTime = 100.0 * (double)Time / (double)pCore->GetSystemTimerBySec();
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Uint64 GetSystemTimer( void ) = 0;

/**
@brief CPU�^�C�}�[��1�b�̃J�E���g�l�擾
@author �t���`
@return GetSystemTimer��1�b�̃J�E���g�l

@note
CPU�^�C�}�[��1�b�̎��Ԃ��擾���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      // ���Ԏ擾
      Uint64 Time = pCore->GetSystemTimer();

      // �Ȃ񂩏�������
 
      // �o�ߎ��Ԏ擾
      Time = pCore->GetSystemTimer() - Time;

      // �o�ߎ��Ԃ�1�b������́���
      Float fTime = 100.0 * (double)Time / (double)pCore->GetSystemTimerBySec();
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Uint64 GetSystemTimerBySec( void ) = 0;

/**
@brief ��ʃT�C�Y�ύX
@author �t���`
@param Size		[in] ��ʃT�C�Y

@note
��ʃT�C�Y��ύX���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ��ʃT�C�Y�ύX
    pCore->ResizeWindowSize( Math::Point2DI(320,240) );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void ResizeWindowSize( Math::Point2DI Size ) = 0;

/**
@brief ��ʃ��[�h��ύX���܂�
@author �t���`

@note
��ʃ��[�h��ύX���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ��ʃ��[�h�ύX
    pCore->ChangeScreenMode();

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void ChangeScreenMode( void ) = 0;

/**
@brief �E�B���h�E���[�h�`�F�b�N
@author �t���`

@note
���݂̉�ʃ��[�h���E�B���h�E���[�h���ǂ����𒲂ׂ܂�

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ��ʃ��[�h�擾
    if ( pCore->IsWindowMode() )
    {
    }

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Bool IsWindowMode( void ) = 0;

/**
@brief ���[�r�[�Đ�
@author �t���`
@param pFileName	[in] �t�@�C����
@param IsLoop		[in] ���[�vON/OFF
@param pCallback	[in] �����I���p�R�[���o�b�N�֐�

@note
�t����ʂŃ��[�r�[�̍Đ����s���܂��B<BR>
���[�r�[���I�����邩�ApCallback�֐�����false��Ԃ��܂ŏ����͖߂��Ă��܂���B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���[�r�[�Đ�
    if ( pCore->PlayMovie( "Sample.mpg", false, NULL ) )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Bool PlayMovie( const char *pFileName, Bool IsLoop, Bool (__stdcall *pCallback)( void ) ) = 0;

/**
@brief �t���[���J�E���g���擾���܂��B
@author �t���`
@return �t���[����

@note
�N��������̑��t���[�������擾���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      // �N������̃t���[����
      Sint32 Cnt = pCore->GetSyncCount();
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Sint32 GetSyncCount( void ) = 0;

/**
@brief �^�C�g���o�[�̏��\��ON/OFF
@author �t���`
@param IsEnable		[in] �\����ON/OFF

@note
�^�C�g���o�[�Ɍ��݂̏��̕\�����s�����ݒ肵�܂��B<BR>
<BR>
�f�t�H���g��false�ł��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �^�C�g���o�[�ɏ��\��
    pCore->EnableDrawTitleInformation( true );

    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void EnableDrawTitleInformation( Bool IsEnable ) = 0;

/**
@brief �}�E�X�J�[�\���̕\��ON/OFF
@author �t���`
@param IsEnable		[in] �\����ON/OFF

@note
�}�E�X�J�[�\���̕\�����s�����ݒ肵�܂��B<BR>
<BR>
�f�t�H���g��false�ł��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �}�E�X�J�[�\������
    pCore->EnableDrawMouseCursor( false );

    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void EnableDrawMouseCursor( Bool IsEnable ) = 0;

/**
@brief �O���t�B�b�N�J�[�h�C���^�[�t�F�C�X���擾
@author �t���`
@param GraphicCardNo	[in] �O���t�B�b�N�J�[�h�ԍ�
@return �O���t�B�b�N�J�[�h�C���^�[�t�F�C�X

@note
�O���t�B�b�N�J�[�h�Ɋւ��Ă̏��������s���A<BR>
���̃C���^�[�t�F�C�X���擾���܂��B<BR>
�ʏ�GraphicCardNo�ɂ�GRAPHIC_CARD_DEFAULT_NO���w�肵�܂��B<BR>
�uNV PerfHUD�v�̃C���X�g�[�����ꂽ���ł́A<BR>
GRAPHIC_CARD_NV_PERF_HUD���w�肷�邱�Ƃł����L���ɏo���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  IGraphicCard *pGraphicCard = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �O���t�B�b�N�J�[�h�C���^�[�t�F�C�X�𐶐�
    pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �O���t�B�b�N�J�[�h�̉��
  SAFE_RELEASE( pGraphicCard );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual IGraphicCard *CreateGraphicCard( eGraphicCardNo GraphicCardNo ) = 0;

/**
@brief �W���C�X�e�B�b�N�̐����擾
@author �t���`
@return �L���ȃW���C�X�e�B�b�N�̐�

@note
�������ɐ��������L���ȃW���C�X�e�B�b�N�Ȃ̐����擾���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �W���C�X�e�B�b�N�����擾
    Sint32 Count = pCore->GetJoystickCount();

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Sint32 GetJoystickCount( void ) = 0;

/**
@brief �}�E�X�C���^�[�t�F�C�X���擾
@author �t���`
@return �}�E�X�C���^�[�t�F�C�X

@note
ICore�̏��L����E�B���h�E�Ɋ֘A�t����ꂽ�}�E�X�̏��������s���A<BR>
���̃C���^�[�t�F�C�X���擾���܂��B<BR>
�}�E�X�Ɋւ��Ă̏��͂��̃C���^�[�t�F�C�X�o�R�Ŏ擾���ĉ������B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Peripheral::IMouse *pMouse = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �}�E�X�̎擾
    pMouse = pCore->GetMouse();

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �}�E�X�̉��
  SAFE_RELEASE( pMouse );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Peripheral::IMouse *GetMouse( void ) = 0;

/**
@brief �L�[�{�[�h�C���^�[�t�F�C�X���擾
@author �t���`
@return �L�[�{�[�h�C���^�[�t�F�C�X

@note
ICore�̏��L����E�B���h�E�Ɋ֘A�t����ꂽ�L�[�{�[�h�̏��������s���A<BR>
���̃C���^�[�t�F�C�X���擾���܂��B<BR>
�L�[�{�[�h�Ɋւ��Ă̏��͂��̃C���^�[�t�F�C�X�o�R�Ŏ擾���ĉ������B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Peripheral::IKeyboard *pKeyboard = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �L�[�{�[�h�̎擾
    pKeyboard = pCore->GetKeyboard();

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �L�[�{�[�h�̉��
  SAFE_RELEASE( pKeyboard );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Peripheral::IKeyboard *GetKeyboard( void ) = 0;

/**
@brief �W���C�X�e�B�b�N�C���^�[�t�F�C�X���擾
@author �t���`
@param No	[in] �W���C�X�e�B�b�N�ԍ�(0�`15)
@return �W���C�X�e�B�b�N�C���^�[�t�F�C�X

@note
ICore�̏��L����E�B���h�E�Ɋ֘A�t����ꂽ�W���C�X�e�B�b�N�̏��������s���A<BR>
���̃C���^�[�t�F�C�X���擾���܂��B<BR>
�W���C�X�e�B�b�N�Ɋւ��Ă̏��͂��̃C���^�[�t�F�C�X�o�R�Ŏ擾���ĉ������B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Peripheral::IJoystick *pJoystick = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �W���C�X�e�B�b�N�̎擾
    pJoystick = pCore->GetJoystick( 0 );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �W���C�X�e�B�b�N�̉��
  SAFE_RELEASE( pJoystick );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Peripheral::IJoystick *GetJoystick( Sint32 No ) = 0;

/**
@brief ���͓����C���^�[�t�F�C�X���擾
@author �t���`
@param No					[in] �K�p����W���C�X�e�B�b�N�ԍ�
@param KeyRepeatStartTime	[in] �L�[���s�[�g�J�n�t���[��
@param KeyRepeatInterval	[in] �L�[���s�[�g�Ԋu�t���[��
@return ���͓����C���^�[�t�F�C�X

@note
ICore�̏��L����E�B���h�E�Ɋ֘A�t����ꂽ�W���C�X�e�B�b�N���L�[�{�[�h�̏��������s���A<BR>
���̃C���^�[�t�F�C�X���擾���܂��B<BR>
�W���C�X�e�B�b�N�ƃL�[�{�[�h�𓝍����Ĉ������Ƃ̂ł���C���^�[�t�F�C�X�ł��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Peripheral::IInputController *pInputController = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���̓R���g���[���[�̎擾
    pInputController = pCore->GetInputController( 0, 30, 5 );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // ���̓R���g���[���[�̉��
  SAFE_RELEASE( pInputController );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Peripheral::IInputController *GetInputController( Sint32 No, Sint32 KeyRepeatStartTime, Sint32 KeyRepeatInterval ) = 0;

/**
@brief �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X����
@author �t���`
@return �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X

@note
�V�K�̃t�@�C���}�l�[�W���[�C���^�[�t�F�C�X�𐶐����܂��B<BR>
�t�@�C���̃p�X�Ȃǂ̐ݒ�͑S��IFileManager���o�R���čs���܂��B
�擾�����t�@�C���}�l�[�W���[�C���^�[�t�F�C�X�͎g�p�I����ɂ͕K��Release()���ĉ������B�B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  File::IFileManager *pFileMgr = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �t�@�C���}�l�[�W���[�̐���
    pFileMgr = pCore->CreateFileManager();

    // �t�@�C���}�l�[�W���[��ݒ�
    pCore->SetFileManager( pFileMgr );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �t�@�C���}�l�[�W���[�̉��
  SAFE_RELEASE( pFileMgr );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual File::IFileManager *CreateFileManager( void ) = 0;

/**
@brief �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X�擾
@author �t���`
@return �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X

@note
���ݐݒ肳��Ă���t�@�C���}�l�[�W���[�C���^�[�t�F�C�X���擾���܂��B<BR>
�ݒ�ς݂̃t�@�C���}�l�[�W���[�C���^�[�t�F�C�X�ւ̃A�N�Z�X���s���ꍇ�Ɏg�p���Ă��������B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  File::IFileManager *pFileMgr = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �t�@�C���}�l�[�W���[�̐���
    pFileMgr = pCore->CreateFileManager();

    // �t�@�C���}�l�[�W���[��ݒ�
    pCore->SetFileManager( pFileMgr );

    // �t�@�C���p�X�ݒ�
    pCore->GetFileMgrPointer()->SetCurrentPath( "Data\\Texture" );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �t�@�C���}�l�[�W���[�̉��
  SAFE_RELEASE( pFileMgr );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual File::IFileManager *GetFileMgrPointer( void ) = 0;

/**
@brief �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X�ݒ�
@author �t���`
@param pMgr	[in] �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X

@note
�t�@�C���̓ǂݍ��݂Ɏg����t�@�C���}�l�[�W���[�C���^�[�t�F�C�X��ݒ肵�܂��B<BR>
�t�@�C���̓ǂݍ��݂͂��̃}�l�[�W���[���o�R���čs���̂ŁA<BR>
�t�@�C���̓ǂݍ��݂��s���ꍇ�͕K���ݒ肵�Ă��������B<BR>
���ɐݒ肳��Ă���}�l�[�W���[�͓����ŉ������܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  File::IFileManager *pFileMgr = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �t�@�C���}�l�[�W���[�̐���
    pFileMgr = pCore->CreateFileManager();

    // �t�@�C���}�l�[�W���[��ݒ�
    pCore->SetFileManager( pFileMgr );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �t�@�C���}�l�[�W���[�̉��
  SAFE_RELEASE( pFileMgr );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void SetFileManager( File::IFileManager *pMgr ) = 0;

/**
@brief �T�E���h�t�@�C���ǂݍ���
@author �t���`
@param pFileName		[in] �T�E���h�t�@�C����(wav)
@param LayerCount		[in] ���C���[���i���������\���j
@param IsGlobalScope	[in] �T�E���h�̃X�R�[�v
@retval	�T�E���h�C���^�[�t�F�C�X

@note
ICore�̏��L����E�B���h�E�Ɋ֘A�t����ꂽ�T�E���h���擾���܂��B<BR>
IsGlobalScope��true��n���ƁA�E�B���h�E�̃t�H�[�J�X�Ɋ֌W�Ȃ��Đ�����܂��B<BR>
LayerCount�Ŏw�肵�������̃��C���[������Ŏ����܂��B<BR>
����͓���̃o�b�t�@��ʁX�̃^�C�~���O�ōĐ��E��~����<BR>
������s�����߂̋@�\�ł����A�P�̃o�b�t�@���g���܂킷�̂�<BR>
�������g�p�ʂ͂P�̏ꍇ�Ɠ����ł��B<BR>
�g�p�̏I�������T�E���h�͕K��Release()���ĉ������B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Sound::ISound *pSound = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �T�E���h�̐���
    pSound = CreateSoundFromFile( "Sample.wav", 4, false );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �T�E���h�̉��
  SAFE_RELEASE( pSound );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Sound::ISound *CreateSoundFromFile( const char *pFileName, Sint32 LayerCount, Bool IsGlobalScope ) = 0;

/**
@brief �T�E���h�t�@�C���ǂݍ���
@author �t���`
@param pFileName		[in] �T�E���h�t�@�C����
@param IsGlobalScope	[in] �T�E���h�̃X�R�[�v
@param pPluginName		[in] �v���O�C����
@retval		�T�E���h�C���^�[�t�F�C�X

@note
ICore�̏��L����E�B���h�E�Ɋ֘A�t����ꂽ�T�E���h���擾���܂��B<BR>
IsGlobalScope��true��n���ƁA�E�B���h�E�̃t�H�[�J�X�Ɋ֌W�Ȃ��Đ�����܂��B<BR>
�g�p�̏I�������T�E���h�͕K��Release()���ĉ������B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Sound::IStreamSound *pSound = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �T�E���h�̐���
    pSound = CreateStreamSoundFromFile( "Sample.ogg", false, "OggVorbis" );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �T�E���h�̉��
  SAFE_RELEASE( pSound );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Sound::IStreamSound *CreateStreamSoundFromFile( const char *pFileName, Bool IsGlobalScope, const char *pPluginName ) = 0;

/**
@brief �t�@�C�o�[�R���g���[���[����
@author �t���`
@param Max	[in] �t�@�C�o�[�ő吔
@return �t�@�C�o�[�R���g���[���[�C���^�[�t�F�C�X

@note
�t�@�C�o�[�R���g���[���[���擾���܂��B<BR>
ICore�ɂP�������݂���2��ڈȍ~�͊����̃C���^�[�t�F�C�X��Ԃ��܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Fiber::IFiberController *pFiber = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �t�@�C�o�[�R���g���[���[�̐���
    pFiber = pCore->CreateFiberController( 8 );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �t�@�C�o�[�̉��
  SAFE_RELEASE( pFiber );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Fiber::IFiberController *CreateFiberController( Sint32 Max ) = 0;
	};
}

