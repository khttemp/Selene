#pragma once


/**
	@file
	@brief �s�񉉎Z
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Vector4D.h"
#include "Quaternion.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Math
{
	/**
		@brief �s��\����
	*/
	struct SELENE_DLL_API SMatrix4x4
	{
		union {
			struct {
				Vector4D x;
				Vector4D y;
				Vector4D z;
				Vector4D w;
			};
			Float m[4][4];
		};
	};

	/**
		@brief �s��N���X
	*/
	class SELENE_DLL_API Matrix : public SMatrix4x4
	{
	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Matrix();

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Matrix( const Matrix &Mat );

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Matrix( const SMatrix4x4 &Mat );

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Matrix( const Quaternion &In );

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Matrix(
			Float _11, Float _12, Float _13, Float _14,
			Float _21, Float _22, Float _23, Float _24,
			Float _31, Float _32, Float _33, Float _34,
			Float _41, Float _42, Float _43, Float _44 );

		/**
			@brief �s��̒P�ʉ�
			@author �t���`
		*/
		void Identity( void );

		/**
			@brief �s��̓]�u��
			@author �t���`
			@param In	[in] �������s��
		*/
		Matrix &Transpose( const Matrix &In );

		/**
			@brief �s��̋t�s��
			@author �t���`
			@param In	[in] �������s��
		*/
		Matrix &Inverse( const Matrix &In );

		/**
			@brief �s��̍���
			@author �t���`
			@param In1		[in] �������s��P
			@param In2		[in] �������s��Q
		*/
		Matrix &Multiply( const Matrix &In1, const Matrix &In2 );

		/**
			@brief �s��̓]�u�s��
			@author �t���`
		*/
		Matrix &Transpose( void );

		/**
			@brief �s��̋t�s��
			@author �t���`
		*/
		Matrix &Inverse( void );

		/**
			@brief �s��̍���
			@author �t���`
			@param In	[in] �������s��
		*/
		Matrix &Multiply( const Matrix &In );

		/**
			@brief �w����]
			@author �t���`
			@param Angle	[in] ��]�p�x
		*/
		Matrix &RotationX( Sint32 Angle );

		/**
			@brief �x����]
			@author �t���`
			@param Angle	[in] ��]�p�x
		*/
		Matrix &RotationY( Sint32 Angle );

		/**
			@brief �y����]
			@author �t���`
			@param Angle	[in] ��]�p�x
		*/
		Matrix &RotationZ( Sint32 Angle );

		/**
			@brief �y�w�x��]�s��𐶐�
			@author �t���`
			@param AngleX	[in] �w����]�p�x
			@param AngleY	[in] �x����]�p�x
			@param AngleZ	[in] �y����]�p�x
		*/
		Matrix &RotationZXY( Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ );

		/**
			@brief �C�ӎ���]
			@author �t���`
			@param Angle	[in] �p�x
			@param Axis		[in] ��]��
		*/
		Matrix &RotationAxis( Sint32 Angle, const Vector3D &Axis );

		/**
			@brief �g��k���s�񐶐�
			@author �t���`
			@param sx	[in] �w�����g�嗦
			@param sy	[in] �x�����g�嗦
			@param sz	[in] �y�����g�嗦
		*/
		Matrix &Scaling( Float sx, Float sy, Float sz );

		/**
			@brief �ړ��s�񐶐�
			@author �t���`
			@param px	[in] �w�ʒu
			@param py	[in] �x�ʒu
			@param pz	[in] �y�ʒu
		*/
		Matrix &Translation( Float px, Float py, Float pz );

		/**
			@brief �����ϊ��p�s�񐶐�
			@author �t���`
			@param Fov		[in] ��p
			@param NearZ	[in] �ߐڃN���b�v��
			@param FarZ		[in] �����N���b�v��
			@param Aspect	[in] �A�X�y�N�g��i���`��G���A�������`��G���A�c���j
		*/
		Matrix &Perspective( Sint32 Fov, Float NearZ, Float FarZ, Float Aspect );

		/**
			@brief ���s���e�p�s�񐶐�
			@author �t���`
			@param Width	[in] ����
			@param Height	[in] �c��
			@param NearZ	[in] �ߐڃN���b�v��
			@param FarZ		[in] �����N���b�v��
		*/
		Matrix &Ortho( Float Width, Float Height, Float NearZ, Float FarZ );

		/**
			@brief �C�ӓ_�����s��쐬
			@author �t���`
			@param Eye	[in] ���_
			@param At	[in] �����_
			@param Up	[in] �����
		*/
		Matrix &LookAt( const Vector3D &Eye, const Vector3D &At, const Vector3D &Up );

		/**
			@brief �s��̕���
			@author �t���`
			@param vTranslate	[in] �ړ�
			@param vScale		[in] �g��k��
			@param qRotate		[in] ��]
		*/
		void Resolution( Vector3D &vTranslate, Vector3D &vScale, Quaternion &qRotate );

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Matrix &operator = ( const Quaternion &q )
		{
			Float xx = q.x * q.x;
			Float yy = q.y * q.y;
			Float zz = q.z * q.z;
			Float xy = q.x * q.y;
			Float xz = q.x * q.z;
			Float yz = q.y * q.z;
			Float wx = q.w * q.x;
			Float wy = q.w * q.y;
			Float wz = q.w * q.z;

			x.x = 1.0f - 2.0f * (yy + zz);
			x.y =        2.0f * (xy - wz);
			x.z =        2.0f * (xz + wy);
			x.w = 0.0f;

			y.x =        2.0f * (xy + wz);
			y.y = 1.0f - 2.0f * (xx + zz);
			y.z =        2.0f * (yz - wx);
			y.w = 0.0f;

			z.x =        2.0f * (xz - wy);
			z.y =        2.0f * (yz + wx);
			z.z = 1.0f - 2.0f * (xx + yy);
			z.w = 0.0f;

			w.x = 0.0f;
			w.y = 0.0f;
			w.z = 0.0f;
			w.w = 1.0f;

			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Matrix &operator = ( const Matrix &m )
		{
			MemoryCopy( this->m, m.m, sizeof(Float[4][4]) );
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Matrix &operator = ( const SMatrix4x4 &m )
		{
			MemoryCopy( this->m, m.m, sizeof(Float[4][4]) );
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Matrix operator * ( const Matrix &m )
		{
			Matrix mTemp;
			return mTemp.Multiply( *this, m );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Matrix &operator *= ( const Matrix &m )
		{
			return Multiply( m );
		}

		/**
			@brief �P�ʍs��
			@author �t���`
			@return �P�ʍs��
		*/
		static Matrix GetIdentity( void )
		{
			Matrix mTemp;
			mTemp.Identity();
			return mTemp;
		}

		/**
			@brief �ړ��s�񐶐�
			@author �t���`
			@param px	[in] �w�ʒu
			@param py	[in] �x�ʒu
			@param pz	[in] �y�ʒu
			@return �ړ��s��
		*/
		static Matrix GetTranslation( Float px, Float py, Float pz )
		{
			Matrix mTemp;
			mTemp.Translation( px, py, pz );
			return mTemp;
		}

		/**
			@brief �w����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return ��]�s��
		*/
		static Matrix GetRotationX( Sint32 Angle )
		{
			Matrix mTemp;
			mTemp.RotationX( Angle );
			return mTemp;
		}

		/**
			@brief �x����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return ��]�s��
		*/
		static Matrix GetRotationY( Sint32 Angle )
		{
			Matrix mTemp;
			mTemp.RotationY( Angle );
			return mTemp;
		}

		/**
			@brief �y����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return ��]�s��
		*/
		static Matrix GetRotationZ( Sint32 Angle )
		{
			Matrix mTemp;
			mTemp.RotationZ( Angle );
			return mTemp;
		}
		
		/**
			@brief �g��k���s��
			@author �t���`
			@param sx	[in] �w�����g�嗦
			@param sy	[in] �x�����g�嗦
			@param sz	[in] �y�����g�嗦
			@return �g��k���s��
		*/
		static Matrix GetScaling( Float sx, Float sy, Float sz )
		{
			Matrix mTemp;
			mTemp.Scaling( sx, sy, sz );
			return mTemp;
		}
	};
}
}

