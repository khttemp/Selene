#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Peripheral/IKeyboard.h"
#include "Interface/Peripheral/IJoystick.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Peripheral
{
	/**
		@brief ���̓f�o�C�X�Ǘ��N���X
		@author �t���`

		�L�[�{�[�h�ƃp�b�h�𓝈ꂵ�Ĉ������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IInputController
	{
	public:
		virtual ~IInputController() {}

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
			@brief ���͏��X�V
			@author �t���`

			���͏�񂩂�ŐV�̏�Ԃ֍X�V���܂��B<BR>
			�K���P�t���[���ɂP��ĂԂ悤�ɂ��ĉ������B
		*/
		virtual void Refresh( void ) = 0;

		/**
			@brief X�����͐ݒ�
			@author �t���`
			@param Type		[in] ���͊Ǘ��p�̎��^�C�v
			@param AxisX	[in] �K�p����W���C�X�e�B�b�N�̎�
			@param AxisDirX	[in] �K�p����W���C�X�e�B�b�N�̎�����

			�W���C�X�e�B�b�N�̎��f�[�^����͊Ǘ��p��X���փ}�b�s���O���܂��B
		*/
		virtual void SetAxisX( eInputAxisType Type, ePadAxisType AxisX, ePadAxisDirection AxisDirX ) = 0;

		/**
			@brief Y�����͐ݒ�
			@author �t���`
			@param Type		[in] ���͊Ǘ��p�̎��^�C�v
			@param AxisY	[in] �K�p����W���C�X�e�B�b�N�̎�
			@param AxisDirY	[in] �K�p����W���C�X�e�B�b�N�̎�����

			�W���C�X�e�B�b�N�̎��f�[�^����͊Ǘ��p��Y���փ}�b�s���O���܂��B
		*/
		virtual void SetAxisY( eInputAxisType Type, ePadAxisType AxisY, ePadAxisDirection AxisDirY ) = 0;

		/**
			@brief �{�^�����͐ݒ�
			@author �t���`
			@param Type		[in] ���͊Ǘ��p�̃{�^���^�C�v
			@param Button	[in] �K�p����W���C�X�e�B�b�N�̃{�^��

			�W���C�X�e�B�b�N�̃{�^���f�[�^����͊Ǘ��p�̃{�^���փ}�b�s���O���܂��B
		*/
		virtual void SetButton( eInputButtonType Type, ePadButtonType Button ) = 0;

		/**
			@brief �L�[�{�[�h�o�R���͐ݒ�
			@author �t���`
			@param Type		[in] ���͊Ǘ��p�̃{�^���^�C�v
			@param Key		[in] �K�p����L�[�{�[�h�̃L�[

			�L�[�{�[�h�̃L�[���W���C�X�e�B�b�N�̕ʖ��Ƃ��ē��͊Ǘ��p�̃{�^���փ}�b�s���O���܂��B
		*/
		virtual void SetAlias( eInputButtonType Type, eVirtualKeyCode Key ) = 0;

		/**
			@brief �ǂꂩ�P�ł��{�^����������Ă��邩�`�F�b�N
			@author �t���`
			@retval false	�{�^���͂P��������Ă��Ȃ�
			@retval true	�{�^���͂P�ȏ㉟����Ă���

			�Ȃ�炩�̃{�^����������Ă��邩�ǂ������`�F�b�N���܂��B
		*/
		virtual Bool IsPushAnyKey( void ) = 0;

		/**
			@brief �{�^���̏�Ԃ�������
			@author �t���`

			���ׂẴX�e�[�g��OFF��Ԃɂ��܂��B
		*/
		virtual void ClearState( void ) = 0;

		/**
			@brief �{�^���̏�Ԃ��擾
			@author �t���`
			@param PadState	[in] �擾������
			@param Type		[in] �擾����{�^��
			@retval false	�{�^���͏����𖞂����Ă��Ȃ�
			@retval true	�{�^���͏����𖞂����Ă���

			�{�^��Type�����PadState�̂Ƃ���true���Ԃ�܂��B<BR>
			�L�[���s�[�g��ݒ肵�Ă���ꍇ�́A�w��Ԋu����BUTTON_STATE_PUSH<BR>
			��ԂɎ����I�ɂȂ�܂��B
		*/
		virtual Bool GetState( eInputButtonState PadState, eInputButtonType Type ) = 0;

		/**
			@brief �{�^���̏�Ԃ�ݒ�
			@author �t���`
			@param PadState	[in] �ݒ肷����
			@param Type		[in] �ݒ肷��{�^��

			�{�^��Type�����PadState�ɐݒ肵�܂��B<BR>
			�O������L�[�𑀍삵�A�����i�s�Ȃǂ��s�킹�邱�Ƃ��\�ł��B
		*/
		virtual void SetState( eInputButtonState PadState, eInputButtonType Type ) = 0;

		/**
			@brief �J�[�\���㉺�ړ�
			@author �t���`
			@param AxisNo		[in] �g�p���鎲�ԍ�
			@param Cursor		[in,out] �J�[�\��
			@param Max			[in] �J�[�\���̂Ƃ肤��ő�l
			@retval BUTTON_DISABLE			�{�^���͉�����Ă��Ȃ�
			@retval BUTTON_DISABLE�ȊO		�{�^���͏�or����������Ă���

			�w�肵�����ɑ΂��ăJ�[�\�����㉺�ɓ������܂��B<BR>
			�܂����̎��ɃJ�[�\���̓��s�[�g����܂��B
		*/
		virtual eInputButtonType CursorRepeatUpDown( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max ) = 0;

		/**
			@brief �J�[�\�����E�ړ�
			@author �t���`
			@param AxisNo		[in] �g�p���鎲�ԍ�
			@param Cursor		[in,out] �J�[�\��
			@param Max			[in] �J�[�\���̂Ƃ肤��ő�l
			@retval BUTTON_DISABLE			�{�^���͉�����Ă��Ȃ�
			@retval BUTTON_DISABLE�ȊO		�{�^���͍�or�E��������Ă���

			�w�肵�����ɑ΂��ăJ�[�\�������E�ɓ������܂��B<BR>
			�܂����̎��ɃJ�[�\���̓��s�[�g����܂��B
		*/
		virtual eInputButtonType CursorRepeatLeftRight( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max ) = 0;

		/**
			@brief �J�[�\���㉺�ړ�
			@author �t���`
			@param AxisNo		[in] �g�p���鎲�ԍ�
			@param Cursor		[in,out] �J�[�\��
			@param Max			[in] �J�[�\���̂Ƃ肤��ő�l
			@retval BUTTON_DISABLE			�{�^���͉�����Ă��Ȃ�
			@retval BUTTON_DISABLE�ȊO		�{�^���͏�or����������Ă���

			�w�肵�����ɑ΂��ăJ�[�\�����㉺�ɓ������܂��B<BR>
			�܂����̎��ɃJ�[�\���̓N�����v����܂��B
		*/
		virtual eInputButtonType CursorClampUpDown( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max ) = 0;

		/**
			@brief �J�[�\�����E�ړ�
			@author �t���`
			@param AxisNo		[in] �g�p���鎲�ԍ�
			@param Cursor		[in,out] �J�[�\��
			@param Max			[in] �J�[�\���̂Ƃ肤��ő�l
			@retval BUTTON_DISABLE			�{�^���͉�����Ă��Ȃ�
			@retval BUTTON_DISABLE�ȊO		�{�^���͍�or�E��������Ă���

			�w�肵�����ɑ΂��ăJ�[�\�������E�ɓ������܂��B<BR>
			�܂����̎��ɃJ�[�\���̓N�����v����܂��B
		*/
		virtual eInputButtonType CursorClampLeftRight( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max ) = 0;
	};
}
}

