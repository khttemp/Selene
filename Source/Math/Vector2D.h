#pragma once


/**
	@file
	@brief 2�����x�N�g��
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
		@brief 2�����x�N�g�����Z�N���X
	*/
	class SELENE_DLL_API Vector2D
	{
	public:
		Float x;
		Float y;

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Vector2D();
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param v	[in] ����
		*/
		Vector2D( const Vector2D &v );
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param fPx	[in] x�����l
			@param fPy	[in] y�����l
		*/
		Vector2D( Float fPx, Float fPy );
		/**
			@brief ���Z
			@author �t���`
			@param In1	[in] ���Z�p���̓x�N�g��
			@param In2	[in] ���Z�p���̓x�N�g��
			@return �v�Z���ʌ��*this

			@note
			this = In + In2
		*/
		Vector2D& Add( const Vector2D &In1, const Vector2D &In2 );
		/**
			@brief ���Z
			@author �t���`
			@param In1	[in] ���Z�p���̓x�N�g��
			@param In2	[in] ���Z�p���̓x�N�g��
			@return �v�Z���ʌ��*this

			@note
			this = In - In2
		*/
		Vector2D& Sub( const Vector2D &In1, const Vector2D &In2 );
		/**
			@brief �l�ݒ�
			@author �t���`
			@param fPx	[in] x�ݒ�l
			@param fPy	[in] y�ݒ�l
			@return �v�Z���ʌ��*this
		*/
		Vector2D& Set( Float fPx, Float fPy );
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
		Float Dot( const Vector2D &In ) const;
		/**
			@brief ���K��
			@author �t���`
			@return �v�Z���ʌ��*this

			@note
			������1.0�ɐ��K�����܂��B
		*/
		Vector2D& Normalize( void );
		/**
			@brief ���K��
			@author �t���`
			@return �v�Z���ʌ��*this

			@note
			������1.0�ɐ��K�����܂��B
		*/
		Vector2D& NormalizeFast( void );
		/**
			@brief ���˃x�N�g���̎擾
			@author �t���`
			@param In1	[in] ���ˑΏۂ̖@��
			@param In2	[in] ���˃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector2D& Reflect( const Vector2D &In1, const Vector2D &In2 );
		/**
			@brief ���K��
			@author �t���`
			@param In	[in] ���K�����̃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector2D& Normalize( const Vector2D &In );
		/**
			@brief ���K��
			@author �t���`
			@param In	[in] ���K�����̃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector2D& NormalizeFast( const Vector2D &In );
		/**
			@brief �O��
			@author �t���`
			@param In	[in] �O�ϗp�̃x�N�g��
			@return z=0.0�Ƃ��Čv�Z�����x�N�g���̊O��
		*/
		Float Cross( const Vector2D &In ) const;
		/**
			@brief ����
			@author �t���`
			@param In	[in] ���˗p�@��
			@return �v�Z���ʌ��*this
		*/
		Vector2D& Reflect( const Vector2D &In );
		/**
			@brief Z����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return �v�Z���ʌ��*this
		*/
		Vector2D& RotationZ( Sint32 Angle );
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator + () const
		{
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator - () const
		{
			return Vector2D(-x, -y);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Bool operator == ( const Vector2D &v )
		{
			return (x == v.x) && (y == v.y);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Bool operator != ( const Vector2D &v )
		{
			return (x != v.x) || (y != v.y);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D& operator += ( Float f )
		{
			x += f;
			y += f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D& operator -= ( Float f )
		{
			x -= f;
			y -= f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D& operator *= ( Float f )
		{
			x *= f;
			y *= f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D& operator /= ( Float f )
		{
			x /= f;
			y /= f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D& operator += ( const Vector2D &v )
		{
			x += v.x;
			y += v.y;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D& operator -= ( const Vector2D &v )
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D& operator *= ( const Vector2D &v )
		{
			x *= v.x;
			y *= v.y;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D& operator /= ( const Vector2D &v )
		{
			x /= v.x;
			y /= v.y;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator + ( Float f ) const
		{
		    return Vector2D(x + f, y + f);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator - ( Float f ) const
		{
			f = 1.0f / f;
			return Vector2D(x - f, y - f);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator * ( Float f ) const
		{
		    return Vector2D(x * f, y * f);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator / ( Float f ) const
		{
			return Vector2D(x / f, y / f);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator + ( const Vector2D &v ) const
		{
			return Vector2D(x + v.x, y + v.y);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator - ( const Vector2D &v ) const
		{
			return Vector2D(x - v.x, y - v.y);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator * ( const Vector2D &v ) const
		{
			return Vector2D(x * v.x, y * v.y);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator / ( const Vector2D &v ) const
		{
			return Vector2D(x / v.x, y / v.y);
		}
	};
}
}

