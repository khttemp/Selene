#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Peripheral
{
	/**
		@brief �W���C�X�e�B�b�N�Ǘ��C���^�[�t�F�C�X
		@author �t���`

		�W���C�X�e�B�b�N���������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IJoystick
	{
	public:
		virtual ~IJoystick() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void ) = 0;

		/**
			@brief �������擾
			@author �t���`
			@param Type		[in] ���̎��
			@param Dir		[in] ���̕���
			@return ���̌��ݒl

			�w�肳�ꂽ��ށA�����̎��̏�Ԃ��擾���܂��B<BR>
			�A�i���O�X�e�B�b�N�̏ꍇ��-4096�`+4096�̒l���Ԃ�A<BR>
			�f�W�^���X�e�B�b�N�̏ꍇ��-4096��+4096�̒l���Ԃ�܂��B
		*/
		virtual Sint32 GetAxis( ePadAxisType Type, ePadAxisDirection Dir ) = 0;

		/**
			@brief �X���C�_�[�����擾
			@author �t���`
			@param Type		[in] �X���C�_�[�̃^�C�v
			@return �X���C�_�[�̌��ݒl

			�w�肳�ꂽ��ނ̃X���C�_�[�̏�Ԃ��擾���܂��B<BR>
			-4096�`+4096�̒l���Ԃ�܂��B
		*/
		virtual Sint32 GetSlider( ePadSliderType Type ) = 0;

		/**
			@brief �{�^�������擾
			@author �t���`
			@param Type		[in] �{�^���̃^�C�v
			@retval false	������ĂȂ�
			@retval true	������Ă���

			�w�肳�ꂽ��ނ̃{�^���̏�Ԃ��擾���܂��B
		*/
		virtual Bool GetButton( ePadButtonType Type ) = 0;
	};
}
}

