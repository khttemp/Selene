#pragma once


/**
	@file
	@brief �p���Ǘ�
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Math/Vector3D.h"
#include "Math/Matrix.h"
#include "Math/Quaternion.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Math
{
	/**
		@brief �p������N���X
	*/
	class SELENE_DLL_API Style
	{
	private:
		Vector3D m_vUp;					///< ������x�N�g��
		Vector3D m_vRight;				///< �E�����x�N�g��
		Vector3D m_vFront;				///< �O�����x�N�g��
		Vector3D m_vPosition;			///< �ʒu�x�N�g��
		Vector3D m_vLocalPosition;		///< �ʒu�x�N�g��
		Vector3D m_vScale;				///< �g��k���x�N�g��

		Bool m_IsScale;					///< �g��k��
		Bool m_IsLocal;					///< ���[�J���ړ�

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Style();
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param Style	[in] �R�s�[��
		*/
		Style( const Style &Style );
		/**
			@brief �ϊ�������
			@author �t���`

			@note
			�ϊ������������ď����l�ɖ߂��܂��B
		*/
		virtual void TransformReset( void );
		/**
			@brief X����]
			@author �t���`
			@param Rot		[in] �p�x

			@note
			���[���h���W�����X������ɉ�]�����܂��B
		*/
		virtual void RotationX( Sint32 Rot );
		/**
			@brief Y����]
			@author �t���`
			@param Rot		[in] �p�x

			@note
			���[���h���W�����Y������ɉ�]�����܂��B
		*/
		virtual void RotationY( Sint32 Rot );
		/**
			@brief Z����]
			@author �t���`
			@param Rot		[in] �p�x

			@note
			���[���h���W�����Z������ɉ�]�����܂��B
		*/
		virtual void RotationZ( Sint32 Rot );
		/**
			@brief �s�b�`���O
			@author �t���`
			@param Rot		[in] �p�x

			@note
			���[�J�����W�����X������ɉ�]�����܂��B
		*/
		virtual void LocalRotationX( Sint32 Rot );
		/**
			@brief �w�b�f�B���O
			@author �t���`
			@param Rot		[in] �p�x

			@note
			���[�J�����W�����Y������ɉ�]�����܂��B
		*/
		virtual void LocalRotationY( Sint32 Rot );
		/**
			@brief ���[�����O
			@author �t���`
			@param Rot		[in] �p�x

			@note
			���[�J�����W�����Z������ɉ�]�����܂��B
		*/
		virtual void LocalRotationZ( Sint32 Rot );
		/**
			@brief �N�H�[�^�j�I���ŉ�]
			@author �t���`
			@param Quat		[in] �N�H�[�^�j�I��

			@note
			�N�H�[�^�j�I�����g���ĉ�]�����܂��B
		*/
		virtual void RotationQuaternion( const Quaternion &Quat );
		/**
			@brief �ړ�
			@author �t���`
			@param fPx		[in] X���W
			@param fPy		[in] Y���W
			@param fPz		[in] Z���W

			@note
			�w����W�ֈړ������܂��B
		*/
		virtual void Translation( Float fPx, Float fPy, Float fPz );
		/**
			@brief �ړ�
			@author �t���`
			@param vPos		[in] ���W

			@note
			�w����W�ֈړ������܂��B
		*/
		virtual void Translation( const Vector3D &vPos );
		/**
			@brief �ړ�
			@author �t���`
			@param fPx		[in] X���W
			@param fPy		[in] Y���W
			@param fPz		[in] Z���W

			@note
			�w����W�ֈړ������܂��B
		*/
		virtual void LocalTranslation( Float fPx, Float fPy, Float fPz );
		/**
			@brief �ړ�
			@author �t���`
			@param vPos		[in] ���W

			@note
			�w����W�ֈړ������܂��B
		*/
		virtual void LocalTranslation( const Vector3D &vPos );
		/**
			@brief �g��k��
			@author �t���`
			@param fSx		[in] X���g��k����
			@param fSy		[in] Y���g��k����
			@param fSz		[in] Z���g��k����

			@note
			�w��{���Ŋg��k���������܂��B
		*/
		virtual void Scaling( Float fSx, Float fSy, Float fSz );
		/**
			@brief �C�ӕ����֎p��
			@author �t���`
			@param vEye		[in] ���_�ʒu
			@param vAt		[in] �ڕW�ʒu
			@param vUp		[in] �����

			@note
			�C�ӂ̏ꏊ����w��̏ꏊ�������ꍇ�̎p�����쐬���܂��B
		*/
		virtual void LookAt( const Vector3D &vEye, const Vector3D &vAt, const Vector3D &vUp );
		/**
			@brief �s�񂩂�ϊ�
			@author �t���`
			@param Mat		[in] �ϊ��}�g���b�N�X

			@note
			�w��̃}�g���b�N�X�ɂȂ�悤�Ȏp���f�[�^�𐶐����܂��B
		*/
		virtual void FromMatrix( const Matrix &Mat );
		/**
			@brief X����]�p�x�擾
			@author �t���`
			@return X���ɂ������]�p�x

			@note
			X���ɂ������]�p�x���擾���܂��B
		*/
		virtual Sint32 GetAngleX( void ) const;
		/**
			@brief Y����]�p�x�擾
			@author �t���`
			@return Y���ɂ������]�p�x

			@note
			Y���ɂ������]�p�x���擾���܂��B
		*/
		virtual Sint32 GetAngleY( void ) const;
		/**
			@brief Z����]�p�x�擾
			@author �t���`
			@return Z���ɂ������]�p�x

			@note
			Z���ɂ������]�p�x���擾���܂��B
		*/
		virtual Sint32 GetAngleZ( void ) const;
		/**
			@brief �ʒu�ݒ�
			@author �t���`
			@param Pos	[in] �ʒu

			@note
			�w��ʒu�Ɉړ����܂��B
		*/
		virtual void SetPosition( const Vector3D &Pos );
		/**
			@brief �O���ݒ�
			@author �t���`
			@param Vec	[in] �O���x�N�g��

			@note
			�p���̐��ʕ�����ݒ肵�܂��B
		*/
		virtual void SetFront( const Vector3D &Vec );
		/**
			@brief �E���ݒ�
			@author �t���`
			@param Vec	[in] �E���x�N�g��

			@note
			�p���̉E�������ݒ肵�܂��B
		*/
		virtual void SetRight( const Vector3D &Vec );
		/**
			@brief ����ݒ�
			@author �t���`
			@param Vec	[in] ����x�N�g��

			@note
			�p���̏�������ݒ肵�܂��B
		*/
		virtual void SetUp( const Vector3D &Vec );
		/**
			@brief �ʒu�擾
			@author �t���`
			@param Pos	[out] �i�[��

			@note
			�w��ʒu�Ɉړ����܂��B
		*/
		virtual void GetPosition( Vector3D &Pos ) const;
		/**
			@brief �O���擾
			@author �t���`
			@param Vec	[out] �i�[��

			@note
			�p���̐��ʕ������擾���܂��B
		*/
		virtual void GetFront( Vector3D &Vec ) const;
		/**
			@brief �E���擾
			@author �t���`
			@param Vec	[out] �i�[��

			@note
			�p���̉E��������擾���܂��B
		*/
		virtual void GetRight( Vector3D &Vec ) const;
		/**
			@brief ����擾
			@author �t���`
			@param Vec	[out] �i�[��

			@note
			�p���̏��������擾���܂��B
		*/
		virtual void GetUp( Vector3D &Vec ) const;
		/**
			@brief �p���s����擾
			@author �t���`
			@param Mat	[out] �i�[��

			@note
			�p���s����擾���܂��B<BR>
			���̍s��ɂ͉�]�v�f�����܂݂܂���B
		*/
		virtual void GetStyle( Matrix &Mat ) const;
		/**
			@brief �t�p���s����擾
			@author �t���`
			@param Mat	[out] �i�[��

			@note
			�t�p���s����擾���܂��B<BR>
			���̍s��ɂ͉�]�v�f�����܂݂܂���B
		*/
		virtual void GetStyleInverse( Matrix &Mat ) const;
		/**
			@brief �ϊ��s����擾
			@author �t���`
			@param Mat	[out] �i�[��

			@note
			�ϊ��s����擾���܂��B<BR>
			���̍s��ɂ͉�]�ƈʒu�v�f�����܂݂܂���B
		*/
		virtual void GetTransform( Matrix &Mat ) const;
		/**
			@brief �t�ϊ��s����擾
			@author �t���`
			@param Mat	[out] �i�[��

			@note
			�t�ϊ��s����擾���܂��B<BR>
			���̍s��ɂ͉�]�ƈʒu�v�f�����܂݂܂���B
		*/
		virtual void GetTransformInverse( Matrix &Mat ) const;
		/**
			@brief �ϊ��s����擾
			@author �t���`
			@param Mat	[out] �i�[��

			@note
			�ϊ��s����擾���܂��B<BR>
			���̍s��ɂ͉�]�ƈʒu�Ɗg��k���̑S�v�f���܂݂܂��B
		*/
		virtual void GetTransformWithScale( Matrix &Mat ) const;
		/**
			@brief �t�ϊ��s����擾
			@author �t���`
			@param Mat	[out] �i�[��

			@note
			�t�ϊ��s����擾���܂��B<BR>
			���̍s��ɂ͉�]�ƈʒu�Ɗg��k���̑S�v�f���܂݂܂��B
		*/
		virtual void GetTransformInverseWithScale( Matrix &Mat ) const;
	};
}
}

