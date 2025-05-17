#pragma once


/**
	@file
	@brief �X�g���[���T�E���h�C���^�[�t�F�C�X
	@author �t���`
*/


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
namespace Sound
{
	static const Float PLAY_TIME_AUTO = -1.0f;

	/**
		@brief �X�g���[���T�E���h�Đ��p�����[�^�[
		@author �t���`

		@note
		�X�g���[���T�E���h�̍Đ����s�����߂̃e�[�u���f�[�^�ł��B
	*/
	struct SPlayBlock
	{
		Sint32 LoopCount;		// ���̃e�[�u���̃��[�v���i-1�Ŗ������[�v�j
		Float fStartTime;		// �Đ��J�n�ʒu�i�b�w��j�iPLAY_TIME_AUTO�w��ōŏ�����j
		Float fEndTime;			// �Đ��I���ʒu�i�b�w��j�iPLAY_TIME_AUTO�w��ōŌ�܂Łj
	};

	/**
		@brief �X�g���[���T�E���h�Ǘ��N���X
		@author �t���`

		@note
		�X�g���[���T�E���h�̏������s���N���X�ł��B<BR>
		�����kWave/���kWave/OggVorbis�̍Đ��ɑΉ����Ă��܂��B<BR>
		BGM�≹���̍Đ��p�r��z�肵�Ă��܂��B
	*/
	class IStreamSound : public IInterface
	{
	public:
		virtual ~IStreamSound() {}

/**
@brief �Đ�
@author �t���`
@param pTbl			[in] �Đ��e�[�u��
@param Count		[in] �Đ��e�[�u����
@retval false		�����Ɏ��s
@retval true		�����ɐ���

@note
�ǂݍ��񂾃T�E���h�f�[�^�̍Đ����J�n���܂��B<BR>
�Đ��e�[�u���̒�`�ɂ����čĐ�����Ă����܂��B

@code
IStreamSound *pSnd;
// �Đ��e�[�u��
Sound::SPlayBlock Tbl[] = {
  {
    3,				// 3��
    0.0f,			// 0.0�b����
    5.0f,			// 5.0�b�܂�
  },
};
pSnd->Play( Tbl, sizeof(Tbl) / sizeof(Sound::SPlayBlock) );
@endcode
*/
		virtual Bool Play( SPlayBlock *pTbl, Sint32 Count ) = 0;

/**
@brief �Đ�
@author �t���`
@param LoopCount	[in] ���[�v��(-1�Ŗ���)
@retval false		�����Ɏ��s
@retval true		�����ɐ���

@note
�ǂݍ��񂾃T�E���h�f�[�^�̍Đ����J�n���܂��B

@code
IStreamSound *pSnd;
// ���ʂ�1��Đ�
pSnd->Play();
@endcode
*/
		virtual Bool Play( Sint32 LoopCount = 0 ) = 0;

/**
@brief ��~
@author �t���`

@retval false		�����Ɏ��s
@retval true		�����ɐ���

@note
�Đ����̃T�E���h���~���܂��B

@code
IStreamSound *pSnd;
// �Đ���~
pSnd->Stop();
@endcode
*/
		virtual Bool Stop( void ) = 0;

/**
@brief �ꎞ��~/����
@author �t���`

@retval false		�����Ɏ��s
@retval true		�����ɐ���

@note
�Đ����̃T�E���h���ꎞ��~�A<BR>
�ꎞ��~���̃T�E���h���Đ����܂��B

@code
IStreamSound *pSnd;
// �ꎞ��~
pSnd->Pause();
@endcode
*/
		virtual Bool Pause( void ) = 0;

/**
@brief �{�����[���ύX
@author �t���`
@param fVolume	[in] �{�����[���i0�`100�j
@retval false		�����Ɏ��s
@retval true		�����ɐ���

@note
�{�����[���̕ύX���s���܂��B

@code
IStreamSound *pSnd;
// �{�����[���ő��
pSnd->SetVolume( 100.0f );
@endcode
*/
		virtual Bool SetVolume( Float fVolume ) = 0;

/**
@brief �p���ړ�
@author �t���`
@param fPan	[in] �p���i-100�`+100�j
@retval false		�����Ɏ��s
@retval true		�����ɐ���

@note
�p���̈ړ����s���܂��B

@code
IStreamSound *pSnd;
// �E���炾������炷
pSnd->SetPan( +100.0f );
@endcode
*/
		virtual Bool SetPan( Float fPan ) = 0;

/**
@brief �Đ��`�F�b�N
@author �t���`
@retval false	�Đ����Ă��Ȃ�
@retval true	�Đ����Ă���

@note
���ݍĐ����̃T�E���h���ǂ������ׂ܂��B

@code
IStreamSound *pSnd;
// �Đ��������ׂ�
if ( !pSnd->IsPlay() )
{
	// �Đ��I��
}
@endcode
*/
		virtual Bool IsPlay( void ) = 0;
	};
}
}

