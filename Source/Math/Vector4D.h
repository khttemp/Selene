#pragma once


/**
	@file
	@brief 4�����x�N�g��
	@author �t���`
*/

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Vector2D.h"
#include "Vector3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Math
{
	/**
		@brief 4�����x�N�g�����Z�N���X
	*/
	class SELENE_DLL_API Vector4D
	{
	public:
		Float x;
		Float y;
		Float z;
		Float w;

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Vector4D();
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param v	[in] ���́ix, y, 0, 1)�ɓW�J
		*/
		Vector4D( const Vector2D &v );
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param v	[in] ���́ix, y, z, 1)�ɓW�J
		*/
		Vector4D( const Vector3D &v );
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param v	[in] ����
		*/
		Vector4D( const Vector4D &v );
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param fPx	[in] x�����l
			@param fPy	[in] y�����l
			@param fPz	[in] z�����l
			@param fPw	[in] w�����l
		*/
		Vector4D( Float fPx, Float fPy = 0.0f, Float fPz = 0.0f, Float fPw = 1.0f );
		/**
			@brief ���Z
			@author �t���`
			@param In1	[in] ���Z�p���̓x�N�g��
			@param In2	[in] ���Z�p���̓x�N�g��
			@return �v�Z���ʌ��*this

			@note
			this = In + In2
		*/
		Vector4D& Add( const Vector4D &In1, const Vector4D &In2 );
		/**
			@brief ���Z
			@author �t���`
			@param In1	[in] ���Z�p���̓x�N�g��
			@param In2	[in] ���Z�p���̓x�N�g��
			@return �v�Z���ʌ��*this

			@note
			this = In - In2
		*/
		Vector4D& Sub( const Vector4D &In1, const Vector4D &In2 );
		/**
			@brief �l�ݒ�
			@author �t���`
			@param fPx	[in] x�ݒ�l
			@param fPy	[in] y�ݒ�l
			@param fPz	[in] z�ݒ�l
			@param fPw	[in] w�ݒ�l
			@return �v�Z���ʌ��*this
		*/
		Vector4D& Set( Float fPx, Float fPy, Float fPz, Float fPw = 1.0f );
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
		Float Dot( const Vector4D &In ) const;
		/**
			@brief ���K��
			@author �t���`
			@return �v�Z���ʌ��*this

			@note
			������1.0�ɐ��K�����܂��B
		*/
		Vector4D& Normalize( void );
		/**
			@brief ���K��
			@author �t���`
			@return �v�Z���ʌ��*this

			@note
			������1.0�ɐ��K�����܂��B
		*/
		Vector4D& NormalizeFast( void );
		/**
			@brief �O��
			@author �t���`
			@param In1	[in] �O�ώZ�o�p���̓x�N�g��
			@param In2	[in] �O�ώZ�o�p���̓x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector4D& Cross( const Vector4D &In1, const Vector4D &In2 );
		/**
			@brief ���˃x�N�g���̎擾
			@author �t���`
			@param In1	[in] ���ˑΏۂ̖@��
			@param In2	[in] ���˃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector4D& Reflect( const Vector4D &In1, const Vector4D &In2 );
		/**
			@brief �g��k���{��]�ϊ�
			@author �t���`
			@param In1	[in] �ϊ����x�N�g��
			@param In2	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector4D& TransformNormal( const Vector4D &In1, const Matrix &In2 );
		/**
			@brief �g��k���{��]�{�ړ��ϊ�
			@author �t���`
			@param In1	[in] �ϊ����x�N�g��
			@param In2	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector4D& TransformCoord( const Vector4D &In1, const Matrix &In2 );
		/**
			@brief �����ϊ�
			@author �t���`
			@param In1	[in] �ϊ����x�N�g��
			@param In2	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector4D& TransformProjection( const Vector4D &In1, const Matrix &In2 );
		/**
			@brief ���K��
			@author �t���`
			@param In	[in] ���K�����̃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector4D& Normalize( const Vector4D &In );
		/**
			@brief ���K��
			@author �t���`
			@param In	[in] ���K�����̃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector4D& NormalizeFast( const Vector4D &In );
		/**
			@brief �O��
			@author �t���`
			@param In	[in] �O�ϗp�̃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector4D& Cross( const Vector4D &In );
		/**
			@brief ����
			@author �t���`
			@param In	[in] ���˗p�@��
			@return �v�Z���ʌ��*this
		*/
		Vector4D& Reflect( const Vector4D &In );
		/**
			@brief �g��k���{��]�ϊ�
			@author �t���`
			@param In	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector4D& TransformNormal( const Matrix &In );
		/**
			@brief �g��k���{��]�{�ړ��ϊ�
			@author �t���`
			@param In	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector4D& TransformCoord( const Matrix &In );
		/**
			@brief �����ϊ�
			@author �t���`
			@param In	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector4D& TransformProjection( const Matrix &In );
		/**
			@brief X����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return �v�Z���ʌ��*this
		*/
		Vector4D& RotationX( Sint32 Angle );
		/**
			@brief Y����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return �v�Z���ʌ��*this
		*/
		Vector4D& RotationY( Sint32 Angle );
		/**
			@brief Z����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return �v�Z���ʌ��*this
		*/
		Vector4D& RotationZ( Sint32 Angle );
		/**
			@brief �x�N�g�������ɉ�]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@param Axis		[in] ��]��
			@return �v�Z���ʌ��*this
		*/
		Vector4D& RotationAxis( Sint32 Angle, const Vector3D &Axis );
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Bool operator == ( const Vector4D &v )
		{
			return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Bool operator != ( const Vector4D &v )
		{
			return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator + () const
		{
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator - () const
		{
			return Vector4D(-x, -y, -z, 1.0);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator += ( const Vector2D &v )
		{
			x += v.x;
			y += v.y;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator -= ( const Vector2D &v )
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator *= ( const Vector2D &v )
		{
			x *= v.x;
			y *= v.y;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator /= ( const Vector2D &v )
		{
			x /= v.x;
			y /= v.y;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator += ( const Vector3D &v )
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
		Vector4D& operator -= ( const Vector3D &v )
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
		Vector4D& operator *= ( const Vector3D &v )
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
		Vector4D& operator /= ( const Vector3D &v )
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
		Vector4D& operator += ( Float f )
		{
			x += f;
			y += f;
			z += f;
			w += f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator -= ( Float f )
		{
			x -= f;
			y -= f;
			z -= f;
			w -= f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator *= ( Float f )
		{
			x *= f;
			y *= f;
			z *= f;
			w *= f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator /= ( Float f )
		{
			x /= f;
			y /= f;
			z /= f;
			w /= f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator += ( const Vector4D &v )
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator -= ( const Vector4D &v )
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator *= ( const Vector4D &v )
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;
			w *= v.w;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator /= ( const Vector4D &v )
		{
			x /= v.x;
			y /= v.y;
			z /= v.z;
			w /= v.w;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator *= ( Matrix &m )
		{
			return TransformCoord( m );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator + ( Float f ) const
		{
			return Vector4D(x + f, y + f, z + f, w + f );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator - ( Float f ) const
		{
			return Vector4D(x - f, y - f, z - f, w - f );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator * ( Float f ) const
		{
			return Vector4D(x * f, y * f, z * f, w * f );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator / ( Float f ) const
		{
			return Vector4D(x / f, y / f, z / f, w / f );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator + ( const Vector2D &v ) const
		{
			return Vector4D(x + v.x, y + v.y, z, w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator - ( const Vector2D &v ) const
		{
			return Vector4D(x - v.x, y - v.y, z, w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator * ( const Vector2D &v ) const
		{
			return Vector4D(x * v.x, y * v.y, z, w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator / ( const Vector2D &v ) const
		{
			return Vector4D(x / v.x, y / v.y, z, w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator + ( const Vector3D &v ) const
		{
			return Vector4D(x + v.x, y + v.y, z + v.z, w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator - ( const Vector3D &v ) const
		{
			return Vector4D(x - v.x, y - v.y, z - v.z, w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator * ( const Vector3D &v ) const
		{
			return Vector4D(x * v.x, y * v.y, z * v.z, w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator / ( const Vector3D &v ) const
		{
			return Vector4D(x / v.x, y / v.y, z / v.z, w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator + ( const Vector4D &v ) const
		{
			return Vector4D(x + v.x, y + v.y, z + v.z, w + v.w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator - ( const Vector4D &v ) const
		{
			return Vector4D(x - v.x, y - v.y, z - v.z, w - v.w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator * ( const Vector4D &v ) const
		{
			return Vector4D(x * v.x, y * v.y, z * v.z, w * v.w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator / ( const Vector4D &v ) const
		{
			return Vector4D(x / v.x, y / v.y, z / v.z, w / v.w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator * ( Matrix &m ) const
		{
			Vector4D vTemp;
			return vTemp.TransformCoord( *this, m );
		}
	};
}
}

