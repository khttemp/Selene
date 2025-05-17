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
		@brief �L�[�{�[�h�Ǘ��C���^�[�t�F�C�X
		@author �t���`

		�L�[�{�[�h���������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IKeyboard
	{
	public:
		virtual ~IKeyboard() {}

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
			@brief �L�[���̓o�b�t�@�t���b�V��
			@author �t���`

			�L�[���̓o�b�t�@�ɒ~�ς������̓o�b�t�@���N���A���܂��B
		*/
		virtual void ClearKeyBuffer( void ) = 0;

		/**
			@brief �L�[���̓o�b�t�@����f�[�^�擾
			@author �t���`
			@return ���͂��ꂽ�L�[�̃L�[�R�[�h

			�L�[���̓o�b�t�@�ɒ~�ς��ꂽ�f�[�^�����o���܂��B<BR>
			�����ꂽ�L�[��S�Ď��o������while()�����ŏ������Ă��������B
		*/
		virtual eVirtualKeyCode GetKeyBuffer( void ) = 0;

		/**
			@brief �L�[��������Ă��邩�`�F�b�N����
			@author �t���`
			@retval false	������Ă��Ȃ�
			@retval true	������Ă���

			�w�肳�ꂽ�L�[�����݉�����Ă��邩�`�F�b�N���܂��B<BR>
			�����ɃL�[��ON/OFF�̂ݎ擾�ł��܂��B
		*/
		virtual Bool GetKeyData( eVirtualKeyCode Key ) = 0;
	};
}
}

