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
namespace Renderer
{
namespace Object
{
	/**
		@brief 3D���C���`��p�C���^�[�t�F�C�X
		@author �t���`

		3D���C���`���ێ����邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class ILine3D
	{
	public:
		virtual ~ILine3D() {}

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
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pLine		[in] ���C���f�[�^
			@param LineCount	[in] ���C����
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�������Ɏw�肵�����_�t�H�[�}�b�g�ɓK���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( SLineVertex3D *pLine, Sint32 LineCount ) = 0;

		/**
			@brief �o�E���f�B���O�{�b�N�X�`�惊�N�G�X�g
			@author �t���`
			@param Box		[in] �R���W�����p�̃{�b�N�X
			@param Color	[in] �F

			�R���W�����p�̃{�b�N�X�f�[�^�̕`����s���܂��B
		*/
		virtual void PushBox( Collision::CBox &Box, CColor Color ) = 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void ) = 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void ) = 0;
	};
}
}
}
