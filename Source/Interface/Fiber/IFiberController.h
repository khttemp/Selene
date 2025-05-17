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
namespace Fiber
{
	/**
		@brief �t�@�C�o�[�R���g���[���[�C���^�[�t�F�C�X
		@author �t���`

		@note
		�t�@�C�o�[�̐�����s�����߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IFiberController : public IInterface
	{
	public:
		virtual ~IFiberController() {}

/**
@brief �t�@�C�o�[�V�X�e���J�n
@author �t���`
@note
�t�@�C�o�[�̏������J�n���܂��B
*/
		virtual void Start( void ) = 0;

/**
@brief �t�@�C�o�[�V�X�e���I��
@author �t���`
@note
�t�@�C�o�[�̏������I�����܂��B
*/
		virtual void Exit( void ) = 0;

/**
@brief �t�@�C�o�[�؂�ւ�
@author �t���`
@retval false	�A�v���P�[�V�����͏I�����Ă���
@retval true	�A�v���P�[�V�����͌p�����ł���
@note
�t�@�C�o�[�̐؂�ւ����s���܂��B
*/
		virtual Bool Switch( void ) = 0;

/**
@brief �t�@�C�o�[����
@author �t���`
@param FiberId	[in] �t�@�C�o�[ID
@param pFiber	[in] �t�@�C�o�[�C���^�[�t�F�C�X
@retval false	�w���FiberId�ɂ��łɃt�@�C�o�[������
@retval true	����
@note
�t�@�C�o�[�̐������s���܂��B
*/
		virtual Bool Create( Sint32 FiberId, IFiber *pFiber ) = 0;
	};
}
}


