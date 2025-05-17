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
		@brief �R�����̕���
		@author �t���`
	*/
	class SELENE_DLL_API CPlane
	{
	public:
		Math::Vector3D n;		///< ��ʕ��ʕ������ɂ�����N���b�v�ʂ� a b c �W��
		Float d;				///< ��ʕ��ʕ������ɂ�����N���b�v�ʂ� d �W��

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CPlane( void );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param a	[in] ��ʕ��ʕ������ɂ�����N���b�v�ʂ� a �W��
			@param b	[in] ��ʕ��ʕ������ɂ�����N���b�v�ʂ� b �W��
			@param c	[in] ��ʕ��ʕ������ɂ�����N���b�v�ʂ� c �W��
			@param d	[in] ��ʕ��ʕ������ɂ�����N���b�v�ʂ� d �W��
		*/
		CPlane( Float a, Float b, Float c, Float d );

		/**
			@brief �@���f�[�^���琶��
			@author �t���`

			@param Pt		[in] ���ʏ��1�_
			@param vNormal	[in] ���ʂ̖@��
		*/
		void FromNormal( const Math::Vector3D &Pt, const Math::Vector3D &vNormal );

		/**
			@brief ���ʏ�̂R�_���琶��
			@author �t���`

			@param vPt0		[in] ���ʏ��1�_
			@param vPt1		[in] ���ʏ��1�_
			@param vPt2		[in] ���ʏ��1�_
		*/
		void FromPoint( const Math::Vector3D &vPt0, const Math::Vector3D &vPt1, const Math::Vector3D &vPt2 );

		/**
			@brief ����
			@author �t���`

			@param Pt	[in] �C�ӂ̓_

			@note
			���ʂƔC�ӂ̓_�̓��ς��Ƃ�܂��B
		*/
		Float Dot( const Math::Vector3D &Pt ) const;
	};
}
}

