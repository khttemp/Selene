#pragma once


/**
	@file
	@brief �Q��������
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
		@brief �Q�����̐���
		@author �t���`
	*/
	class SELENE_DLL_API CLine2D
	{
	public:
		Math::Vector2D vStart;				///< �����n�_�ʒu
		Math::Vector2D vEnd;				///< �����I�_�ʒu

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CLine2D( void );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x0		[in] �w���W
			@param y0		[in] �x���W
			@param x1		[in] �w���W
			@param y1		[in] �x���W
		*/
		CLine2D( Float x0, Float y0, Float x1, Float y1 );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param pt0		[in] �����̒��_�P
			@param pt1		[in] �����̒��_�Q
		*/
		CLine2D( Math::Vector2D &pt0, Math::Vector2D &pt1 );
	};
}
}


