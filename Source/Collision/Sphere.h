#pragma once


/**
	@file
	@brief �R���W�����p��
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Vector3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
	/**
		@brief �R������̋�
		@author �t���`
	*/
	class SELENE_DLL_API CSphere
	{
	public:
		Math::Vector3D vCenter;				///< ���̒��S
		Float fRadius;						///< ���̔��a

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CSphere( void );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w���W
			@param y		[in] �x���W
			@param z		[in] �y���W
			@param r		[in] ���a
		*/
		CSphere( Float x, Float y, Float z, Float r );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param c		[in] ���S���W
			@param r		[in] ���a
		*/
		CSphere( const Math::Vector3D &c, Float r );
	};
}
}

