#pragma once


/**
	@file
	@brief �A�j���[�V��������
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CBaseObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �A�j���[�V�����^�C�v��`
		@author �t���`
	*/
	enum eAnimationType
	{
		ANIMATION_TYPE_STEP,					///< �X�e�b�v���
		ANIMATION_TYPE_LINEAR,					///< ���`���
		ANIMATION_TYPE_TCB,						///< �s�b�a�X�v���C�����
	};

	/**
		@brief �L�[�t���[���f�[�^
		@author �t���`
	*/
	struct SKeyFrame
	{
		Bool IsIn;								///< �X�v���C������IN�W����萔�ɂ��邩�ǂ���
		Bool IsOut;								///< �X�v���C������OUT�W����萔�ɂ��邩�ǂ���
		Float fTime;							///< �L�[����
		Float fParam;							///< �L�[�l
		Float fIn;								///< IN�W���̒萔
		Float fOut;								///< OUT�W���̒萔

		SKeyFrame *pPrev;						///< �O���L�[�t���[���f�[�^�|�C���^
		SKeyFrame *pNext;						///< ����L�[�t���[���f�[�^�|�C���^
	};

namespace Math
{
	/**
		@brief �A�j���[�V�����N���X
		@author �t���`
	*/
	class SELENE_DLL_API Animation
	{
	private:
		Float m_fTimeFirst;						///< �J�n����
		Float m_fTimeLast;						///< �I������
		SKeyFrame *m_pKeys;						///< �L�[�t���[���f�[�^�|�C���^
		Sint32 m_KeyMax;						///< �L�[�t���[����

	private:
/**
@brief �w�莞�Ԃ���ł��߂��L�[�f�[�^���擾���܂�
@author �t���`
@param pKeys		[in] �L�[�t���[���f�[�^
@param fTime		[in] ��������
@param KeyMax		[in] �L�[�ő吔
@return �L�[�t���[���f�[�^�|�C���^

@note
�w�莞�Ԃ�������Ƃ��߂��L�[�����A<BR>
�o�C�i���T�[�`�Ō������܂��B
*/
		SKeyFrame *GetKeyData( SKeyFrame *pKeys, Float fTime, Sint32 KeyMax );

/**
@brief �G���~�[�g��Ԋ֐����������܂�
@author �t���`
@param fTime	[in] ����
@param pH1		[out] �p�����[�^�[�i�[��P
@param pH2		[out] �p�����[�^�[�i�[��Q
@param pH3		[out] �p�����[�^�[�i�[��R
@param pH4		[out] �p�����[�^�[�i�[��S

@note
�G���~�[�g��Ԋ֐����g���ė^����ꂽ�p�����[�^�[���猋�ʂ��Z�o���܂��B
*/
		void Hermite( Float fTime, Float *pH1, Float *pH2, Float *pH3, Float *pH4 );

/**
@brief �O���̃L�[�̏o�͐�̃p�����[�^�����߂܂�
@author �t���`
@param pKey0	[in] �O���L�[�f�[�^
@param pKey1	[in] ����L�[�f�[�^
@return �Z�o���ꂽ�p�����[�^�[

@note
�w�莞�Ԃɑ΂��Ă̒��O�̃L�[�̋������v�Z���܂��B
*/
		Float InComing( SKeyFrame *pKey0, SKeyFrame *pKey1 );

/**
@brief ����̃L�[�̏o�͐�̃p�����[�^�����߂܂�
@author �t���`
@param pKey0	[in] �O���L�[�f�[�^
@param pKey1	[in] ����L�[�f�[�^
@return �Z�o���ꂽ�p�����[�^�[

@note
�w�莞�Ԃɑ΂��Ă̒���̃L�[�̋������v�Z���܂��B
*/
		Float OutGoing( SKeyFrame *pKey0, SKeyFrame *pKey1 );

	public:
/**
@brief �R���X�g���N�^
@author �t���`
@param KeyMax		[in] �L�[�ő吔
*/
		Animation( Sint32 KeyMax );

/**
@brief �f�X�g���N�^
@author �t���`
*/
		virtual ~Animation();

/**
@brief �L�[�t���[���f�[�^�ɃL�[��ݒ肵�܂�
@author �t���`
@param KeyNo		[in] �ݒ��L�[�ԍ�
@param fTime		[in] �ݒ莞��
@param fParam		[in] �ݒ�p�����[�^
@param IsIn			[in] ���̓p�����[�^�[�w��L��
@param IsOut		[in] �o�̓p�����[�^�[�w��L��
@param fIn			[in] ���̓p�����[�^�[
@param fOut			[in] �o�̓p�����[�^�[
@return ��������true

@note
�w��̃L�[�ɑ΂��āA��ԗp�̃p�����[�^�[��ݒ肵�܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;

  Math::Animation Anim( 3 );	// �L�[�R�ō쐬
  Anim.SetKey( 0,  0.0f,   0.0f );	// �L�[�P
  Anim.SetKey( 1,  5.0f,  40.0f );	// �L�[�Q
  Anim.SetKey( 2, 10.0f, 100.0f );	// �L�[�R

  Float fTime = 0.0f;

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

    // ���C�����[�v
    while ( pCore->Run() )
    {
      fTime += 0.1f;

      // ����fTime�ɂ�����l���擾
      // ��ԕ��@��TCB�X�v���C��
      Float fNow = Anim.GetParameter( fTime, ANIMATION_TYPE_TCB, 0.0f );
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
		virtual Bool SetKey( Sint32 KeyNo, Float fTime, Float fParam, Bool IsIn = false, Bool IsOut = false, Float fIn = 0.0f, Float fOut = 0.0f );

/**
@brief �w��^�C�v�̃A�j���[�V�����Ŏw�莞�Ԃɂ�����l���擾���܂�
@author �t���`
@param fTime		[in] ����
@param Type			[in] ��ԃ^�C�v
@param fDefault		[in] �f�t�H���g�l
@return		��Ԍ��ʒl

@note
�w��̎��Ԃɑ΂��āA��Ԃ��ꂽ�p�����[�^�[���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;

  Math::Animation Anim( 3 );	// �L�[�R�ō쐬
  Anim.SetKey( 0,  0.0f,   0.0f );	// �L�[�P
  Anim.SetKey( 1,  5.0f,  40.0f );	// �L�[�Q
  Anim.SetKey( 2, 10.0f, 100.0f );	// �L�[�R

  Float fTime = 0.0f;

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

    // ���C�����[�v
    while ( pCore->Run() )
    {
      fTime += 0.1f;

      // ����fTime�ɂ�����l���擾
      // ��ԕ��@��TCB�X�v���C��
      Float fNow = Anim.GetParameter( fTime, ANIMATION_TYPE_TCB, 0.0f );
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
		virtual Float GetParameter( Float fTime, eAnimationType Type, Float fDefault );
	};
}
}

