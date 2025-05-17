#pragma once


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
namespace Scene
{
	/**
		@brief �V�[�����f���A�N�^�[�p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���Ǘ����ꂽ���f���A�N�^�[�������ׂ̃C���^�[�t�F�C�X�ł��B
	*/
	class IInstanceModelActor : public IInterface
	{
	public:
		virtual ~IInstanceModelActor() {}

		/**
			@brief �C���X�^���X���f������p�C���^�[�t�F�C�X�擾
			@author �t���`

			�C���X�^���X�o�^���ꂽ�X�̃��f���𐧌䂷�邽�߂̃C���^�[�t�F�C�X���擾���܂��B<BR>
			�{�[���⃏�[���h�ϊ��̏����͂��̃C���^�[�t�F�C�X���o�R���čs���܂��B
		*/
		virtual IInstanceModelController *GetController( Sint32 Index ) = 0;

		/**
			@brief �`�惊�N�G�X�g�J�n
			@author �t���`

			IInstanceModelController�̃����_�����O�����̊J�n��錾���܂��B
			IInstanceModelController��RenderingRequest()��Begin-End�ԂŌĂ�ŉ������B
		*/
		virtual void Begin( void ) = 0;

		/**
			@brief �`�惊�N�G�X�g�I��
			@author �t���`

			IInstanceModelController�̃����_�����O�����̏I����錾���܂��B
			IInstanceModelController��RenderingRequest()��Begin-End�ԂŌĂ�ŉ������B
		*/
		virtual void End( void ) = 0;
	};
}
}

