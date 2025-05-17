#pragma once


/**
	@file
	@brief �e�N�X�`���C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Math.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	/**
		@brief �[�x�o�b�t�@�^�C�v
		@author �t���`
	*/
	enum eDepthBufferType
	{
		DEPTH_BUFFER_SURFACE,			///< �[�x�o�b�t�@�̓T�[�t�F�C�X
		DEPTH_BUFFER_TEXTURE_NVIDIA,	///< �[�x�o�b�t�@�̓e�N�X�`���iNVIDIA�d�l�j
		DEPTH_BUFFER_TEXTURE_ATI,		///< �[�x�o�b�t�@�̓e�N�X�`���iATI�d�l�j
	};

	/**
		@brief �e�N�X�`���^�C�v
		@author �t���`
	*/
	enum eTextureType
	{
		TEXTURE_TYPE_DEFAULT,		///< �ʏ�̕`��p�e�N�X�`��
		TEXTURE_TYPE_TARGET,		///< �`��^�[�Q�b�g�p�e�N�X�`��
		TEXTURE_TYPE_DEPTH,			///< �[�x�o�b�t�@�p�e�N�X�`��
		TEXTURE_TYPE_NONE,			///< ���ɂȂ�
	};

	/**
		@brief �e�N�X�`���C���^�[�t�F�C�X
		@author �t���`

		@note
		�e�N�X�`���𑀍삷�邽�߂̃C���^�[�t�F�C�X�ł��B<BR>
		IRender�C���^�[�t�F�C�X����擾�ł��܂��B
	*/
	class ITexture : public IInterface
	{
	public:
		virtual ~ITexture() {}

/**
@brief �摜�t�@�C���Ƃ��ĕۑ�
@author �t���`
@param pFileName	[in] �e�N�X�`���t�@�C����
@retval false	���s
@retval true	����

@note
�e�N�X�`���̓��e��TGA�摜�t�@�C���Ƃ��ĕۑ����܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;
  IGraphicCard *pGraphicCard = NULL;
  IRender      *pRender      = NULL;
  ITexture     *pTex         = NULL;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // �r�f�I�J�[�h������
    IGraphicCard *pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
    if ( pGraphicCard == NULL ) goto EXIT;      // IGraphicCard�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �����_���[�̐���
    IRender *pRender = pGraphicCard->CreateRender();
    if ( pRender == NULL ) goto EXIT;           // IRender�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �e�N�X�`���̐���
    pTex = pRender->CreateTextureFromFile( "sample.bmp" );

    // �e�N�X�`�����摜�Ƃ��ĕۑ�
    pTex->SaveToTGA( "hogehoge.tga" );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

EXIT:
  SAFE_RELEASE( pTex );                // �e�N�X�`���̉��
  SAFE_RELEASE( pRender );             // �����_���[�̉��
  SAFE_RELEASE( pGraphicCard );        // �r�f�I�J�[�h�̉��
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
		virtual Bool SaveToTGA( const char *pFileName ) = 0;

/**
@brief �摜�t�@�C���Ƃ��ĕۑ�
@author �t���`
@param pFileName	[in] �e�N�X�`���t�@�C����
@retval false	���s
@retval true	����

@note
�e�N�X�`���̓��e��PNG�摜�t�@�C���Ƃ��ĕۑ����܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;
  IGraphicCard *pGraphicCard = NULL;
  IRender      *pRender      = NULL;
  ITexture     *pTex         = NULL;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // �r�f�I�J�[�h������
    IGraphicCard *pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
    if ( pGraphicCard == NULL ) goto EXIT;      // IGraphicCard�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �����_���[�̐���
    IRender *pRender = pGraphicCard->CreateRender();
    if ( pRender == NULL ) goto EXIT;           // IRender�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �e�N�X�`���̐���
    pTex = pRender->CreateTextureFromFile( "sample.bmp" );

    // �e�N�X�`�����摜�Ƃ��ĕۑ�
    pTex->SaveToPNG( "hogehoge.png" );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

EXIT:
  SAFE_RELEASE( pTex );                // �e�N�X�`���̉��
  SAFE_RELEASE( pRender );             // �����_���[�̉��
  SAFE_RELEASE( pGraphicCard );        // �r�f�I�J�[�h�̉��
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
		virtual Bool SaveToPNG( const char *pFileName ) = 0;

/**
@brief ���e�N�X�`���T�C�Y�擾
@author �t���`
@return �e�N�X�`���̎��T�C�Y

@note
�e�N�X�`���̃T�C�Y���擾���܂��B<BR>
�Q�̗ݏ�łȂ��e�N�X�`�����쐬�����ۂ�<BR>
�f�o�C�X�����̃T�C�Y���T�|�[�g���Ă��Ȃ��Ƃ���<BR>
����ł���傫���̂Q�̗ݏ�̃T�C�Y�ɂȂ��Ă��܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;
  IGraphicCard *pGraphicCard = NULL;
  IRender      *pRender      = NULL;
  ITexture     *pTex         = NULL;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // �r�f�I�J�[�h������
    IGraphicCard *pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
    if ( pGraphicCard == NULL ) goto EXIT;      // IGraphicCard�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �����_���[�̐���
    IRender *pRender = pGraphicCard->CreateRender();
    if ( pRender == NULL ) goto EXIT;           // IRender�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �e�N�X�`���̐���
    pTex = pRender->CreateTextureFromFile( "sample.bmp" );

    // �e�N�X�`���̃T�C�Y���擾
    // �e�N�X�`���̎��T�C�Y
    // �f�o�C�X�ɂ���Ă͐������ɗv���ʂ�ɃT�C�Y�͂Ȃ�Ȃ�
    Math::Point2DI Size = pTex->GetSize();

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

EXIT:
  SAFE_RELEASE( pTex );                // �e�N�X�`���̉��
  SAFE_RELEASE( pRender );             // �����_���[�̉��
  SAFE_RELEASE( pGraphicCard );        // �r�f�I�J�[�h�̉��
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
		virtual Math::Point2DI GetSize( void ) = 0;

/**
@brief �v���e�N�X�`���T�C�Y�擾
@author �t���`
@return �e�N�X�`���̃T�C�Y

@note
�e�N�X�`���̌��T�C�Y���擾���܂��B<BR>
�쐬���Ɏw�肵���傫�����擾���܂��B<BR>
���̑傫���͎��ۂ̃e�N�X�`���T�C�Y�Ƃ͈Ⴄ�ꍇ������܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;
  IGraphicCard *pGraphicCard = NULL;
  IRender      *pRender      = NULL;
  ITexture     *pTex         = NULL;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // �r�f�I�J�[�h������
    IGraphicCard *pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
    if ( pGraphicCard == NULL ) goto EXIT;      // IGraphicCard�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �����_���[�̐���
    IRender *pRender = pGraphicCard->CreateRender();
    if ( pRender == NULL ) goto EXIT;           // IRender�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �e�N�X�`���̐���
    pTex = pRender->CreateTextureFromFile( "sample.bmp" );

    // �������Ƀ��N�G�X�g�����e�N�X�`���̃T�C�Y
    // �t�@�C���ǂݍ��݂̏ꍇ�t�@�C����̂ŉ摜�̃T�C�Y
    Math::Point2DI Size = pTex->GetOriginalSize();

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

EXIT:
  SAFE_RELEASE( pTex );                // �e�N�X�`���̉��
  SAFE_RELEASE( pRender );             // �����_���[�̉��
  SAFE_RELEASE( pGraphicCard );        // �r�f�I�J�[�h�̉��
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
		virtual Math::Point2DI GetOriginalSize( void ) = 0;

/**
@brief �e�N�X�`���ϊ��p�p�����[�^�[�擾
@author �t���`
@return �ϊ��p�̒l

@note
�e�N�X�`���̌��摜�̍��W����e�N�X�`���̒l���擾���邽�߂̕ϊ��p�̒l���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;
  IGraphicCard *pGraphicCard = NULL;
  IRender      *pRender      = NULL;
  ITexture     *pTex         = NULL;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // �r�f�I�J�[�h������
    IGraphicCard *pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
    if ( pGraphicCard == NULL ) goto EXIT;      // IGraphicCard�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �����_���[�̐���
    IRender *pRender = pGraphicCard->CreateRender();
    if ( pRender == NULL ) goto EXIT;           // IRender�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �e�N�X�`���̐���
    pTex = pRender->CreateTextureFromFile( "sample.bmp" );

    // ���摜��(100,50)���W��UV�֕ϊ�
    Math::Point2DF Trans = pTex->GetPixelToTexelTransform();
    Float u = 100.0f * Trans.x;
    Float v =  50.0f * Trans.y;

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

EXIT:
  SAFE_RELEASE( pTex );                // �e�N�X�`���̉��
  SAFE_RELEASE( pRender );             // �����_���[�̉��
  SAFE_RELEASE( pGraphicCard );        // �r�f�I�J�[�h�̉��
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
		virtual Math::Point2DF GetPixelToTexelTransform( void ) = 0;

/**
@brief �����_�����O�^�[�Q�b�g���e��ۑ�
@author �t���`
@retval true	����
@retval false	���s

@note
�����_�����O�^�[�Q�b�g�̌��݂̓��e���o�b�N�A�b�v���܂��B<BR>
�o�b�N�A�b�v���ꂽ���e�̓f�o�C�X�̃��X�g���Ɏ����I�ɕ�������܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;
  IGraphicCard *pGraphicCard = NULL;
  IRender      *pRender      = NULL;
  ITexture     *pTex         = NULL;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // �r�f�I�J�[�h������
    IGraphicCard *pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
    if ( pGraphicCard == NULL ) goto EXIT;      // IGraphicCard�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �����_���[�̐���
    IRender *pRender = pGraphicCard->CreateRender();
    if ( pRender == NULL ) goto EXIT;           // IRender�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �e�N�X�`���̐���
    pTex = pRender->CreateTextureRenderTarget( 256, 256 );

    // �f�o�C�X���X�g���ɓ��e�������ł���悤��
    // ���݂̏�Ԃ��o�b�N�A�b�v���Ă����B
    //   �ʏ�͉��炩�̃����_�����O���s�������ɁA
    //   ���̓��e��ۑ����Ă��������ꍇ�Ɏg���B
    pTex->BackupTargetBuffer();

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

EXIT:
  SAFE_RELEASE( pTex );                // �e�N�X�`���̉��
  SAFE_RELEASE( pRender );             // �����_���[�̉��
  SAFE_RELEASE( pGraphicCard );        // �r�f�I�J�[�h�̉��
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
		virtual Bool BackupTargetBuffer( void ) = 0;

/**
@brief ��ނ��擾
@author �t���`
@return	�e�N�X�`�����ǂ̎�ނɑ����邩���擾���܂��B

@note
�e�N�X�`���̎�ނ��擾���܂��B<BR>
IRender::SetRenderTarget()�Ɏg����̂�TEXTURE_TYPE_TARGET������<BR>
IRender::SetDepthBuffer()�Ɏg����̂�TEXTURE_TYPE_DEPTH�����ł��B
*/
		virtual eTextureType GetType( void ) = 0;

/**
@brief �[�x�o�b�t�@�̎�ނ��擾
@author �t���`
@return	�[�x�o�b�t�@�̎��

@note
�[�x�o�b�t�@�̎�ނ��擾���܂��B<BR>
�Ԃ�l��DEPTH_BUFFER_TEXTURE�̏ꍇ�̓e�N�X�`���Ƃ��Đ[�x�o�b�t�@������Ă��܂��B
*/
		virtual eDepthBufferType GetDepthBufferType( void ) = 0;

/**
@brief �t�B���^�����O�����̐�����擾
@author �t���`
@retval false	�t�B���^�����O���A���t�@�u�����h�o���Ȃ�
@retval true	�t�B���^�����O���A���t�@�u�����h�o����

@note
�t�B���^�����O�\�ȃt�H�[�}�b�g�����擾���܂��B
*/
		virtual Bool IsFilterEnable( void ) = 0;
	};
}
}

