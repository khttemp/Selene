#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Math.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Peripheral
{
	/**
		@brief �}�E�X�Ǘ��C���^�[�t�F�C�X
		@author �t���`

		�}�E�X���������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IMouse
	{
	public:
		virtual ~IMouse() {}

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
			@brief �}�E�X��X���W�擾
			@author �t���`
			@return X���W

			�}�E�X�|�C���^�[�̃X�N���[�����W���X���W���擾���܂��B
		*/
		virtual Sint32 GetPosX( void ) = 0;

		/**
			@brief �}�E�X��Y���W�擾
			@author �t���`
			@return Y���W

			�}�E�X�|�C���^�[�̃X�N���[�����W���Y���W���擾���܂��B
		*/
		virtual Sint32 GetPosY( void ) = 0;

		/**
			@brief �}�E�X�̃z�C�[����]�ʎ擾
			@author �t���`
			@return �z�C�[����]��

			�}�E�X�z�C�[���̉�]�ʂ��擾���܂��B
		*/
		virtual Sint32 GetPosW( void ) = 0;

		/**
			@brief �}�E�X��X�ړ��ʎ擾
			@author �t���`
			@return X�ړ���

			�}�E�X�|�C���^�[�̃X�N���[�����X�ړ��ʂ��擾���܂��B
		*/
		virtual Sint32 GetMoveX( void ) = 0;

		/**
			@brief �}�E�X��Y�ړ��ʎ擾
			@author �t���`
			@return Y�ړ���

			�}�E�X�|�C���^�[�̃X�N���[�����Y�ړ��ʂ��擾���܂��B
		*/
		virtual Sint32 GetMoveY( void ) = 0;

		/**
			@brief �}�E�X�̃z�C�[���ړ��ʎ擾
			@author �t���`
			@return �z�C�[���ړ���

			�}�E�X�|�C���^�[�̃z�C�[���ړ��ʂ��擾���܂��B
		*/
		virtual Sint32 GetMoveW( void ) = 0;

		/**
			@brief �}�E�X�̍��N���b�N��Ԏ擾
			@author �t���`
			@retval false	���{�^���͉�����Ă��Ȃ�
			@retval true	���{�^���͉�����Ă���

			�}�E�X�̍��{�^���̏�Ԃ��擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual Bool GetClickL( void ) = 0;

		/**
			@brief �}�E�X�̉E�N���b�N��Ԏ擾
			@author �t���`
			@retval false	�E�{�^���͉�����Ă��Ȃ�
			@retval true	�E�{�^���͉�����Ă���

			�}�E�X�̉E�{�^���̏�Ԃ��擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual Bool GetClickR( void ) = 0;

		/**
			@brief �}�E�X�̃z�C�[���N���b�N��Ԏ擾
			@author �t���`
			@retval false	�z�C�[���{�^���͉�����Ă��Ȃ�
			@retval true	�z�C�[���{�^���͉�����Ă���

			�}�E�X�̃z�C�[���{�^���̏�Ԃ��擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual Bool GetClickW( void ) = 0;

		/**
			@brief �}�E�X�̍��_�u���N���b�N��Ԏ擾
			@author �t���`
			@retval false	���{�^���̓_�u���N���b�N����Ă��Ȃ�
			@retval true	���{�^���̓_�u���N���b�N���ꂽ

			�}�E�X�̍��{�^�����_�u���N���b�N���ꂽ�����擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual Bool GetDoubleClickL( void ) = 0;

		/**
			@brief �}�E�X�̉E�_�u���N���b�N��Ԏ擾
			@author �t���`
			@retval false	�E�{�^���̓_�u���N���b�N����Ă��Ȃ�
			@retval true	�E�{�^���̓_�u���N���b�N���ꂽ

			�}�E�X�̉E�{�^�����_�u���N���b�N���ꂽ�����擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual Bool GetDoubleClickR( void ) = 0;

		/**
			@brief �}�E�X�̃z�C�[���_�u���N���b�N��Ԏ擾
			@author �t���`
			@retval false	�z�C�[���{�^���̓_�u���N���b�N����Ă��Ȃ�
			@retval true	�z�C�[���{�^���̓_�u���N���b�N���ꂽ

			�}�E�X�̃z�C�[���{�^�����_�u���N���b�N���ꂽ�����擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual Bool GetDoubleClickW( void ) = 0;

		/**
			@brief �}�E�X�̍��{�^����Ԏ擾
			@author �t���`
			@return		���{�^���̏��

			�}�E�X�̍��{�^���̏ڍׂȏ����擾���܂��B
		*/
		virtual eMouseState GetStateL( void ) = 0;

		/**
			@brief �}�E�X�̉E�{�^����Ԏ擾
			@author �t���`
			@return		�E�{�^���̏��

			�}�E�X�̉E�{�^���̏ڍׂȏ����擾���܂��B
		*/
		virtual eMouseState	GetStateR( void ) = 0;

		/**
			@brief �}�E�X�̃z�C�[���{�^����Ԏ擾
			@author �t���`
			@return		�z�C�[���{�^���̏��

			�}�E�X�̃z�C�[���{�^���̏ڍׂȏ����擾���܂��B
		*/
		virtual eMouseState	GetStateW( void ) = 0;

		/**
			@brief �}�E�X�̈ʒu��ݒ�
			@author �t���`
			@param Pos	[in] �X�N���[�����W

			�}�E�X�̈ʒu��C�ӂ̏ꏊ�ɐݒ肵�܂��B
		*/
		virtual void SetPosition( Math::Point2DI &Pos ) = 0;
	};
}
}

