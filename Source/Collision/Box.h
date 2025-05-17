#pragma once


/**
	@file
	@brief �R�����{�b�N�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Vector3D.h"
#include "Math/Matrix.h"
#include "Collision/Plane.h"
#include "Collision/Sphere.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
	/**
		@brief �R������̔�
		@author �t���`
	*/
	class SELENE_DLL_API CBox
	{
	public:
		Math::Vector3D Points[8];		///< �����\������8���_
		CPlane Planes[6];				///< �����\������6����
		Math::Vector3D vMin;			///< AABB�̍ŏ��_
		Math::Vector3D vMax;			///< AABB�̍ő�_

	private:
		/**
			@brief �|�C���g�f�[�^�����Ƀ{�b�N�X�̊e�ʁA���E���̍Čv�Z
			@author �t���`
		*/
		void UpdateBox( void );

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CBox( void );

		/**
			@brief �o�E���f�B���O�{�b�N�X���\������W���_���w��
			@author �t���`
			@param vPoints	[in] �|�C���g

			@note
			�ȉ��̏��Ԃɕ���ł���K�v������܂��B<BR>
			(min.x,min.y,min.z)-(min.x,max.y,min.z)-(min.x,max.y,max.z)-(min.x,min.y,max.z)-<BR>
			(max.x,min.y,min.z)-(max.x,max.y,min.z)-(max.x,max.y,max.z)-(max.x,min.y,max.z)
		*/
		void SetPoints( const Math::Vector3D vPoints[] );

		/**
			@brief �R���w��Ńo�E���f�B���O�{�b�N�X���\������W���_���X�V
			@author �t���`
			@param vCenter	[in] ���S
			@param vAxis	[in] ��(X,Y,Z)
			@param fLength	[in] ���̒���(X,Y,Z)
		*/
		void UpdatePoints( const Math::Vector3D &vCenter, const Math::Vector3D vAxis[], const Float fLength[] );

		/**
			@brief �o�E���f�B���O�{�b�N�X���w�肵���s��ŕϊ����܂��B
			@author �t���`
			@param Matrix	[in] �|�C���g��ϊ����邽�߂̍s��
		*/
		void Transform( const Math::Matrix &Matrix );

		/**
			@brief �o�E���f�B���O�{�b�N�X���w�肵���s��ŕϊ����܂��B
			@author �t���`
			@param vPoints	[in] �|�C���g�̔z��
			@param Matrix	[in] �|�C���g��ϊ����邽�߂̍s��
		*/
		void Transform( const Math::Vector3D vPoints[], const Math::Matrix &Matrix );

		/**
			@brief �o�E���f�B���O�{�b�N�X���w�肵���s��œ����ϊ����܂��B
			@author �t���`
			@param Matrix	[in] �|�C���g�𓧎��ϊ����邽�߂̍s��
		*/
		void TransformProjection( const Math::Matrix &Matrix );

		/**
			@brief �o�E���f�B���O�{�b�N�X���w�肵���s��œ����ϊ����܂��B
			@author �t���`
			@param vPoints	[in] �|�C���g�̔z��
			@param Matrix	[in] �|�C���g�𓧎��ϊ����邽�߂̍s��
		*/
		void TransformProjection( const Math::Vector3D vPoints[], const Math::Matrix &Matrix );

		/**
			@brief �o�E���f�B���O�{�b�N�X�𐶐�
			@author �t���`
			@param MinPt	[in] AABB�̍ŏ��l
			@param MaxPt	[in] AABB�̍ő�l
			@param Matrix	[in] �|�C���g��ϊ����邽�߂̍s��
		*/
		void CreateBox( const Math::Vector3D &MinPt, const Math::Vector3D &MaxPt, const Math::Matrix &Matrix );

		/**
			@brief �o�E���f�B���O�{�b�N�X�𐶐�
			@author �t���`
			@param MinPt	[in] AABB�̍ŏ��l
			@param MaxPt	[in] AABB�̍ő�l
			@param Matrix	[in] �|�C���g�𓧎��ϊ����邽�߂̍s��
		*/
		void CreateBoxProjection( const Math::Vector3D &MinPt, const Math::Vector3D &MaxPt, const Math::Matrix &Matrix );
	};
}
}

