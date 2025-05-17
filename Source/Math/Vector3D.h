#pragma once


/**
	@file
	@brief 3�����x�N�g��
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
namespace Math
{
	/**
		@brief 3�����x�N�g�����Z�N���X
	*/
	class SELENE_DLL_API Vector3D
	{
	public:
		Float x;
		Float y;
		Float z;

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Vector3D();
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param v	[in] ����
		*/
		Vector3D( const Vector3D &v );
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param fPx	[in] x�����l
			@param fPy	[in] y�����l
			@param fPz	[in] z�����l
		*/
		Vector3D( Float fPx, Float fPy, Float fPz );
		/**
			@brief ���Z
			@author �t���`
			@param In1	[in] ���Z�p���̓x�N�g��
			@param In2	[in] ���Z�p���̓x�N�g��
			@return �v�Z���ʌ��*this

			@note
			this = In + In2
		*/
		Vector3D& Add( const Vector3D &In1, const Vector3D &In2 );
		/**
			@brief ���Z
			@author �t���`
			@param In1	[in] ���Z�p���̓x�N�g��
			@param In2	[in] ���Z�p���̓x�N�g��
			@return �v�Z���ʌ��*this

			@note
			this = In - In2
		*/
		Vector3D& Sub( const Vector3D &In1, const Vector3D &In2 );
		/**
			@brief �l�ݒ�
			@author �t���`
			@param fPx	[in] x�ݒ�l
			@param fPy	[in] y�ݒ�l
			@param fPz	[in] z�ݒ�l
			@return �v�Z���ʌ��*this
		*/
		Vector3D& Set( Float fPx, Float fPy, Float fPz );
		/**
			@brief �����̓��擾
			@author �t���`
			@return �����̓��
		*/
		Float LengthSq( void ) const;
		/**
			@brief �����擾
			@author �t���`
			@return ����
		*/
		Float Length( void ) const;
		/**
			@brief �����擾
			@author �t���`
			@return ����
		*/
		Float LengthFast( void ) const;
		/**
			@brief ����
			@author �t���`
			@param In	[in] ���ώZ�o�p���̓x�N�g��
			@return ����
		*/
		Float Dot( const Vector3D &In ) const;
		/**
			@brief ���K��
			@author �t���`
			@return �v�Z���ʌ��*this

			@note
			������1.0�ɐ��K�����܂��B
		*/
		Vector3D &Normalize( void );
		/**
			@brief ���K��
			@author �t���`
			@return �v�Z���ʌ��*this

			@note
			������1.0�ɐ��K�����܂��B
		*/
		Vector3D &NormalizeFast( void );
		/**
			@brief �O��
			@author �t���`
			@param In1	[in] �O�ώZ�o�p���̓x�N�g��
			@param In2	[in] �O�ώZ�o�p���̓x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector3D& Cross( const Vector3D &In1, const Vector3D &In2 );
		/**
			@brief ���˃x�N�g���̎擾
			@author �t���`
			@param In1	[in] ���ˑΏۂ̖@��
			@param In2	[in] ���˃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector3D& Reflect( const Vector3D &In1, const Vector3D &In2 );
		/**
			@brief �g��k���{��]�ϊ�
			@author �t���`
			@param In1	[in] �ϊ����x�N�g��
			@param In2	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector3D& TransformNormal( const Vector3D &In1, const Matrix &In2 );
		/**
			@brief �g��k���{��]�{�ړ��ϊ�
			@author �t���`
			@param In1	[in] �ϊ����x�N�g��
			@param In2	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector3D& TransformCoord( const Vector3D &In1, const Matrix &In2 );
		/**
			@brief �����ϊ�
			@author �t���`
			@param In1	[in] �ϊ����x�N�g��
			@param In2	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector3D& TransformProjection( const Vector3D &In1, const Matrix &In2 );
		/**
			@brief ���K��
			@author �t���`
			@param In	[in] ���K�����̃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector3D &Normalize( const Vector3D &In );
		/**
			@brief ���K��
			@author �t���`
			@param In	[in] ���K�����̃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector3D &NormalizeFast( const Vector3D &In );
		/**
			@brief �O��
			@author �t���`
			@param In	[in] �O�ϗp�̃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector3D& Cross( const Vector3D &In );
		/**
			@brief ����
			@author �t���`
			@param In	[in] ���˗p�@��
			@return �v�Z���ʌ��*this
		*/
		Vector3D& Reflect( const Vector3D &In );
		/**
			@brief �g��k���{��]�ϊ�
			@author �t���`
			@param In	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector3D& TransformNormal( const Matrix &In );
		/**
			@brief �g��k���{��]�{�ړ��ϊ�
			@author �t���`
			@param In	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector3D& TransformCoord( const Matrix &In );
		/**
			@brief �����ϊ�
			@author �t���`
			@param In	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector3D& TransformProjection( const Matrix &In );
		/**
			@brief X����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return �v�Z���ʌ��*this
		*/
		Vector3D& RotationX( Sint32 Angle );
		/**
			@brief Y����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return �v�Z���ʌ��*this
		*/
		Vector3D& RotationY( Sint32 Angle );
		/**
			@brief Z����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return �v�Z���ʌ��*this
		*/
		Vector3D& RotationZ( Sint32 Angle );
		/**
			@brief �x�N�g�������ɉ�]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@param Axis		[in] ��]��
			@return �v�Z���ʌ��*this
		*/
		Vector3D& RotationAxis( Sint32 Angle, const Vector3D &Axis );
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator + () const
		{
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator - () const
		{
			return Vector3D(-x, -y, -z);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Bool operator == ( const Vector3D &v )
		{
			return (x == v.x) && (y == v.y) && (z == v.z);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Bool operator != ( const Vector3D &v )
		{
			return (x != v.x) || (y != v.y) || (z != v.z);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D& operator += ( Float f )
		{
			x += f;
			y += f;
			z += f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D& operator -= ( Float f )
		{
			x -= f;
			y -= f;
			z -= f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D& operator *= ( Float f )
		{
			x *= f;
			y *= f;
			z *= f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D& operator /= ( Float f )
		{
			x /= f;
			y /= f;
			z /= f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D& operator += ( const Vector3D &v )
		{
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D& operator -= ( const Vector3D &v )
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D& operator *= ( const Vector3D &v )
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D& operator /= ( const Vector3D &v )
		{
			x /= v.x;
			y /= v.y;
			z /= v.z;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator + ( Float f ) const
		{
			return Vector3D(x + f, y + f, z + f);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator - ( Float f ) const
		{
			return Vector3D(x - f, y - f, z - f);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator * ( Float f ) const
		{
			return Vector3D(x * f, y * f, z * f);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator / ( Float f ) const
		{
			return Vector3D(x / f, y / f, z / f);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator + ( const Vector3D &v ) const
		{
			return Vector3D(x + v.x, y + v.y, z + v.z);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator - ( const Vector3D &v ) const
		{
			return Vector3D(x - v.x, y - v.y, z - v.z);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator * ( const Vector3D &v ) const
		{
			return Vector3D(x * v.x, y * v.y, z * v.z);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator / ( const Vector3D &v ) const
		{
			return Vector3D(x - v.x, y - v.y, z - v.z);
		}
	};
}
}

