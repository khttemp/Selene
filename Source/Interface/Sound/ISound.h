#pragma once


/**
	@file
	@brief �T�E���h�C���^�[�t�F�C�X
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
	/**
		@brief �T�E���h�Ǘ��N���X
		@author �t���`

		@note
		�T�E���h�̏������s���N���X�ł��B<BR>
		�����kWave�݂̂̃I�����������d�Đ��ɑΉ����Ă��܂��B<BR>
		SE�̍Đ��p�r��z�肵�Ă��܂��B
	*/
	class ISound : public IInterface
	{
	public:
		virtual ~ISound() {}

/**
@brief �Đ�
@author �t���`
@param Layer	[in] ���C���[�ԍ��i-1�w��őS���C���[�ɑ΂��āj
@param IsLoop	[in] ���[�v�L���t���O

@note
�ǂݍ��񂾃T�E���h�f�[�^�̍Đ����J�n���܂��B<BR>
���[�v�̗L�����w��ł��܂��B

@code
ISound *pSnd;
// ����T�E���h�ł����Ă�Layer���Ⴄ���̂͑��d�Đ����o����B
// ���̂R��10ms���ɑ��d�Đ������B
pSnd->Play( 0, false );
Sleep( 10 );
pSnd->Play( 1, false );
Sleep( 10 );
pSnd->Play( 2, false );
@endcode
*/
		virtual void Play( Sint32 Layer, Bool IsLoop = false ) = 0;

/**
@brief ��~
@author �t���`
@param Layer	[in] ���C���[�ԍ��i-1�w��őS���C���[�ɑ΂��āj

@note
�Đ����̃T�E���h���~���܂��B

@code
ISound *pSnd;
// ����t�@�C��=�T�E���h�ł����Ă�Layer���Ⴆ�Εʂ̂��̂Ƃ��Ĉ�����
pSnd->Play( 0, false );
Sleep( 10 );
pSnd->Play( 1, false );
Sleep( 10 );
// ���̏ꍇLayer=0�̃T�E���h�͒�~���邪�ALayer=1�̃T�E���h�͍Đ����ꂽ�܂܂ɂȂ�
pSnd->Stop( 0, false );
@endcode
*/
		virtual void Stop( Sint32 Layer ) = 0;

/**
@brief �ꎞ��~/����
@author �t���`
@param Layer	[in] ���C���[�ԍ��i-1�w��őS���C���[�ɑ΂��āj

@note
�Đ����̃T�E���h���ꎞ��~�A<BR>
�ꎞ��~���̃T�E���h���Đ����܂��B

@code
ISound *pSnd;
// ����t�@�C��=�T�E���h�ł����Ă�Layer���Ⴆ�Εʂ̂��̂Ƃ��Ĉ�����
pSnd->Play( 0, false );
Sleep( 10 );
pSnd->Play( 1, false );
Sleep( 10 );
// ���̏ꍇLayer=0�̃T�E���h�͈ꎞ��~���邪�ALayer=1�̃T�E���h�͍Đ����ꂽ�܂܂ɂȂ�
pSnd->Pause( 0, false );
@endcode
*/
		virtual void Pause( Sint32 Layer ) = 0;

/**
@brief �{�����[���ύX
@author �t���`
@param Layer	[in] ���C���[�ԍ��i-1�w��őS���C���[�ɑ΂��āj
@param fVolume	[in] �{�����[���i0�`100%�j

@note
�{�����[���̕ύX���s���܂��B

@code
ISound *pSnd;
// ����t�@�C��=�T�E���h�ł����Ă�Layer���Ⴆ�Εʂ̂��̂Ƃ��Ĉ�����
pSnd->Play( 0, false );
Sleep( 10 );
pSnd->Play( 1, false );
Sleep( 10 );
// ���̏ꍇLayer=0�̃T�E���h�͉��ʂ������ɂȂ邪�ALayer=1�̃T�E���h�͂��̂܂܂ɂȂ�
pSnd->SetVolume( 0, 50.0f );
@endcode
*/
		virtual void SetVolume( Sint32 Layer, Float fVolume ) = 0;

/**
@brief �p���ړ�
@author �t���`
@param Layer	[in] ���C���[�ԍ��i-1�w��őS���C���[�ɑ΂��āj
@param fPan	[in] �p���i��:-100�`�E:+100�j

@note
�p���̈ړ����s���܂��B

@code
ISound *pSnd;
// ����t�@�C��=�T�E���h�ł����Ă�Layer���Ⴆ�Εʂ̂��̂Ƃ��Ĉ�����
pSnd->Play( 0, false );
Sleep( 10 );
pSnd->Play( 1, false );
Sleep( 10 );
// ���̏ꍇLayer=0�̃T�E���h�͍�����̂ݖ邪�ALayer=1�̃T�E���h�͂��̂܂܂ɂȂ�
pSnd->SetPan( 0, -100.0f );
@endcode
*/
		virtual void SetPan( Sint32 Layer, Float fPan ) = 0;

/**
@brief �Đ��`�F�b�N
@author �t���`
@param Layer	[in] ���C���[�ԍ�
@retval false	�Đ����Ă��Ȃ�
@retval true	�Đ����Ă���

@note
���ݍĐ����̃T�E���h���ǂ������ׂ܂��B

@code
ISound *pSnd;
// �T�E���h��Layer=1���Đ��������ׂ�
if ( pSnd->IsPlay( 1 ) )
{
	// �Đ���
}
@endcode
*/
		virtual Bool IsPlay( Sint32 Layer ) = 0;
	};
}
}
