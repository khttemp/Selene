#pragma once


/**
	@file
	@brief �Q�����~
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
		@brief �Q������̉~
		@author �t���`
	*/
	class SELENE_DLL_API CCircle
	{
	public:
		Math::Vector2D vCenter;			///< �~�̒��S
		Float fRadius;					///< �~�̔��a

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CCircle( void );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w���W
			@param y		[in] �x���W
			@param r		[in] ���a
		*/
		CCircle( Float x, Float y, Float r );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param c		[in] ���S���W
			@param r		[in] ���a
		*/
		CCircle( Math::Vector2D &c, Float r );
	};
}
}

