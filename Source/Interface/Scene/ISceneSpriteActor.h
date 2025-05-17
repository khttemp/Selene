#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Style.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �V�[���v���~�e�B�u�A�N�^�[�p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���Ǘ����ꂽ�v���~�e�B�u�A�N�^�[�������ׂ̃C���^�[�t�F�C�X�ł��B
	*/
	class ISpriteActor : public Math::Style
	{
	public:
		virtual ~ISpriteActor() {}

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
			@brief �`�惊�N�G�X�g
			@author �t���`

			ISceneManager�ɑ΂��ă����_�����O���N�G�X�g�𔭍s���܂��B<BR>
			�擾����ISceneManager��Begin()/End()���łȂ��ꍇ���̊֐��͎��s���܂��B
		*/
		virtual void RenderingRequest( void ) = 0;

		/**
			@brief ���W�ϊ�������
			@author �t���`

			�A�N�^�[�̍��W�ϊ������������܂��B<BR>
			�A�j���[�V�����̏��Ȃǂ����̊֐����ł��ׂď���������܂��B
		*/
		virtual void TransformReset( void )	 = 0;

		/**
			@brief ���W�ϊ��X�V
			@author �t���`

			�A�N�^�[�̍��W�ϊ����X�V���܂��B<BR>
			�A�j���[�V�����̏��Ȃǂ����̊֐����ł��ׂčX�V����܂��B
		*/
		virtual void TransformUpdate( void ) = 0;
	};
}
}

