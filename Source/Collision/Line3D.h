#pragma once


/**
	@file
	@brief �R��������
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
		@brief �R�����̐���
		@author �t���`
	*/
	class SELENE_DLL_API CLine3D
	{
	public:
		Math::Vector3D vStart;				///< �����n�_�ʒu
		Math::Vector3D vEnd;				///< �����I�_�ʒu

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CLine3D( void );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x0		[in] �w���W
			@param y0		[in] �x���W
			@param z0		[in] �y���W
			@param x1		[in] �w���W
			@param y1		[in] �x���W
			@param z1		[in] �y���W
		*/
		CLine3D( Float x0, Float y0, Float z0, Float x1, Float y1, Float z1 );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param pt0	[in] �����̒��_�P
			@param pt1	[in] �����̒��_�Q
		*/
		CLine3D( const Math::Vector3D &pt0, const Math::Vector3D &pt1 );
	};
}
}

