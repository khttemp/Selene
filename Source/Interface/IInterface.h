#pragma once


/**
	@file
	@brief �C���^�[�t�F�C�X���N���X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �C���^�[�t�F�[�X���N���X
		@author �t���`
	*/
	class IInterface
	{
	public:
		virtual ~IInterface() {}

/**
@brief �L�����`�F�b�N
@author �t���`
@retval true ����
@retval false �L��

@note
�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B

@code
// �L�����`�F�b�N
if ( this->IsInvalid() )
{
	// �����ȃC���^�[�t�F�C�X
	reutrn false;
}
*/
		virtual Bool IsInvalid( void ) = 0;

/**
@brief �Q�ƃJ�E���^�f�N�������g
@author �t���`
@return �f�N�������g��̎Q�ƃJ�E���g

@note
�Q�ƃJ�E���^���f�N�������g���A<BR>
�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B

@code
// ����i�Q�ƃJ�E���^��-1���邾���B���ۂɂ͎Q�ƃJ�E���g��0�ɂȂ�ƃ���������������j
this->Release();
@endcode
*/
		virtual Sint32 Release( void ) = 0;

/**
@brief �Q�ƃJ�E���^�C���N�������g
@author �t���`
@return �C���N�������g��̎Q�ƃJ�E���g

@note
�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B

@code
IInterface *pCopy = this;
// ���ł��Q�Ƃ���̂ŎQ�Ɛ�+1
this->AddRef();
@endcode
*/
		virtual Sint32 AddRef( void ) = 0;
	};
}

