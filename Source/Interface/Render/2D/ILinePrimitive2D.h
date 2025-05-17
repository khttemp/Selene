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
		@brief 2D���C���v���~�e�B�u�Ǘ��C���^�[�t�F�C�X
		@author �t���`

		2D���C���`��p�̃C���^�[�t�F�C�X�ł��B
	*/
	class ILine2D
	{
	public:
		virtual ~ILine2D() {}
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

		/**
			@brief �����o�b�t�@�փf�[�^�ǉ�
			@author �t���`
			@param pLine	[in] ���C���f�[�^
			@param Count	[in] �ǉ���

			�����o�b�t�@�̃f�[�^�̒ǉ����s���܂��B<BR>
			���̊֐����Ăяo���O�ɕK��Being�֐��Ńf�[�^�ǉ��̊J�n��錾���ĉ������B
		*/
		virtual Bool Push( SLineVertex2D *pLine, Sint32 Count ) = 0;

		/**
			@brief �����_�����O
			@author �t���`

			�����o�b�t�@�̓��e�̃����_�����O���s���܂��B
		*/
		virtual void Rendering( void ) = 0;
	};
}
}
}
