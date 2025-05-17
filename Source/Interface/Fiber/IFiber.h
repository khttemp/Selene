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
namespace Fiber
{
	/**
		@brief �t�@�C�o�[�C���^�[�t�F�C�X
		@author �t���`

		@note
		�t�@�C�o�[���������邽�߂̊��N���X�ł��B
	*/
	class IFiber
	{
	private:
		Sint32 m_RefCount;
		IFiberController *m_pFiberCtrl;

	protected:
/**
@brief �t�@�C�o�[�؂�ւ�
@author �t���`
@retval true	�A�v���P�[�V�����͌p����
@retval false	�A�v���P�[�V�������I�����Ă���

@note
�o�^����Ă��鎟��ID�̃t�@�C�o�[�ɏ�����؂�ւ��܂��B<BR>
�Ԃ�l��false�̏ꍇ�A�v���P�[�V�������I���������s���Ă���̂�<BR>
Controller()���\�b�h���璼���ɔ�����悤�ɑg��ŉ������B
*/
		Bool Switch( void )
		{
			return m_pFiberCtrl->Switch();
		}

	public:
/**
@brief �R���X�g���N�^
@author �t���`
*/
		IFiber( void )
			: m_pFiberCtrl	( NULL )
			, m_RefCount	( 1 )
		{
		}

/**
@brief �f�X�g���N�^
@author �t���`
*/
		virtual ~IFiber()
		{
			if ( m_pFiberCtrl != NULL )
			{
				m_pFiberCtrl->Release();
			}
		}

/**
@brief �Q�ƃJ�E���^�f�N�������g
@author �t���`
@return �f�N�������g��̎Q�ƃJ�E���g

@note
�Q�ƃJ�E���^���f�N�������g���A<BR>
�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
*/
		Sint32 Release( void )
		{
			Sint32 Cnt = --m_RefCount;
			if ( Cnt == 0 )
			{
				delete this;
			}
			return Cnt;
		}

/**
@brief �Q�ƃJ�E���^�C���N�������g
@author �t���`
@return �C���N�������g��̎Q�ƃJ�E���g

@note
�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
*/
		Sint32 AddRef( void )
		{
			return ++m_RefCount;
		}

/**
@brief �R���g���[���[�ݒ�
@author �t���`
@param pCtrl	[in] �R���g���[���[
*/
		void SetController( IFiberController *pCtrl )
		{
			m_pFiberCtrl = pCtrl;
			m_pFiberCtrl->AddRef();
		}

	public:
/**
@brief �t�@�C�o�[�p����֐�
@author �t���`

@note
�t�@�C�o�[�����ۂɑ��삷�邽�߂̏������z�֐��ł��B<BR>
���̊֐����甲���邱�Ƃł��̃t�@�C�o�[�̏�������~���܂��B<BR>
Switch()���\�b�h�ł̐؂�ւ�����false���A���Ă����炽������<BR>
�֐����甲����悤�ɂ��ĉ������B
*/
		virtual void Control( void ) = 0;
	};
}
}

