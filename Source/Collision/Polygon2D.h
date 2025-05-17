#pragma once


/**
	@file
	@brief �Q�������p�`
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Vector2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
	/**
		@brief �Q�����̑��p�`
		@author �t���`
	*/
	class SELENE_DLL_API CPolygon2D
	{
	public:
		Sint32 Count;					///< �|�C���g�z��̃|�C���g��
		Math::Vector2D *pPts;			///< �|���S����\�����߂̃|�C���g�z��̃|�C���^

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CPolygon2D( void );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param Cnt		[in] ���_��
			@param pPt		[in] ���_�̔z��̃A�h���X(���ŃR�s�[�͂���܂���̂ŁA�Q�ƌ��̃������͕ێ����Ă����K�v������܂�)

			@note
			Collision�N���X�Ŕ�����s���ꍇ�ACnt�̒l��4�ȏ��pPt[0]==pPt[Cnt-1]�ɂȂ��Ă���A<BR>
			pPt�̓��e�͎��v���A���邢�͔����v���̓ʌ`������Ă���K�v������܂��B
		*/
		CPolygon2D( Sint32 Cnt, Math::Vector2D *pPt );
	};
}
}

