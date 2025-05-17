#pragma once


/**
	@file
	@brief �Z�p���Z
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Vector2D.h"
#include "Math/Vector3D.h"
#include "Math/Matrix.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Math
{
/**
@brief sin�擾
@author �t���`
@param Angle	[in] 1��65536�Ƃ����p�x
@return sin�l

@note
sin�l���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // 90�x�̎���sin�l���擾
  Float fRet = Math::Sin( DEG_TO_ANGLE(90) );

  return 0;
}
@endcode
*/
SELENE_DLL_API Float Sin( Sint32 Angle );

/**
@brief cos�擾
@author �t���`
@param Angle	[in] 1��65536�Ƃ����p�x
@return cos�l

@note
cos�l���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // 90�x�̎���cos�l���擾
  Float fRet = Math::Cos( DEG_TO_ANGLE(90) );

  return 0;
}
@endcode
*/
SELENE_DLL_API Float Cos( Sint32 Angle );

/**
@brief �x�N�g���擾
@author �t���`
@param Angle	[in] 1��65536�Ƃ����p�x
@return 2D�x�N�g��

@note
���K�����ꂽ2D�x�N�g�����擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // 90�x�̕����������P�ʃx�N�g�����擾
  Vector2D vDir = Math::GetVector( DEG_TO_ANGLE(90) );

  return 0;
}
@endcode
*/
SELENE_DLL_API Vector2D GetVector( Sint32 Angle );

/**
@brief atan2�擾
@author �t���`
@param Dx	[in] �w����
@param Dy	[in] �x����
@return X-Y�̐����p�x

@note
X,Y���狁�߂���atan2�̒l��Selene�̊p�x�P�ʂ�<BR>
���킹���l�Ŏ擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // (x,y)=(100.0f,50.0f)�ɂ����錴�_��̊p�x�����߂�
  Sint32 Angle = Math::ATan2( 100.0f, 50.0f );

  return 0;
}
@endcode
*/
SELENE_DLL_API Sint32 ATan2( Float Dx, Float Dy );

	/**
		@brief ��`�f�[�^
		@author �t���`
	*/
	template <typename Type>
	class Rect2D
	{
	public:
		Type x;					///< �w�n�_���W
		Type y;					///< �x�n�_���W
		Type w;					///< �w�T�C�Y
		Type h;					///< �x�T�C�Y

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Rect2D()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		template <typename TypeT>
		Rect2D( const Rect2D<TypeT> &Src )
		{
			this->x = (Type)Src.x;
			this->y = (Type)Src.y;
			this->w = (Type)Src.w;
			this->h = (Type)Src.h;
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w�n�_���W
			@param y		[in] �x�n�_���W
			@param w		[in] �w�T�C�Y
			@param h		[in] �x�T�C�Y
		*/
		Rect2D( Type x, Type y, Type w, Type h )
		{
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}

		/**
			@brief �l�ݒ�
			@author �t���`

			@param x		[in] �w���S���W
			@param y		[in] �x���S���W
			@param w		[in] �w�T�C�Y
			@param h		[in] �x�T�C�Y
		*/
		void Set( Type x, Type y, Type w, Type h )
		{
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}

		/**
			@brief �l�ݒ�
			@author �t���`

			@param x		[in] �w���S���W
			@param y		[in] �x���S���W
			@param w		[in] �w�T�C�Y
			@param h		[in] �x�T�C�Y
			@param Scale	[in] �g��k����
		*/
		void SetCenter( Type x, Type y, Type w, Type h, Float Scale = 1.0f )
		{
			this->w = (Type)(w * Scale);
			this->h = (Type)(h * Scale);
			this->x = x - (Type)(toF(this->w) * 0.5f);
			this->y = y - (Type)(toF(this->h) * 0.5f);
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		template <typename TypeT>
		Rect2D<Type> & operator = ( const Rect2D<TypeT> &Src )
		{
			this->x = (Type)Src.x;
			this->y = (Type)Src.y;
			this->w = (Type)Src.w;
			this->h = (Type)Src.h;
			return *this;
		}
	};

	/**
		@brief �Q�����̓_
		@author �t���`
	*/
	template <typename Type>
	class Point2D
	{
	public:
		Type x;					///< �w���W
		Type y;					///< �x���W

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Point2D()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		template <typename TypeT>
		Point2D( const Point2D<TypeT> &Src )
		{
			this->x = (Type)Src.x;
			this->y = (Type)Src.y;
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w���W
			@param y		[in] �x���W
		*/
		Point2D( Type x, Type y )
		{
			this->x = x;
			this->y = y;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point2D<Type> operator + ( Point2D<Type> &Pt )
		{
			return Point2D<Type>( this->x + Pt.x, this->y + Pt.y );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point2D<Type> operator - ( Point2D<Type> &Pt )
		{
			return Point2D<Type>( this->x - Pt.x, this->y - Pt.y );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point2D<Type> operator * ( Type Mul )
		{
			return Point2D<Type>( this->x * Mul, this->y * Mul );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point2D<Type> operator / ( Type Div )
		{
			return Point2D<Type>( this->x / Div, this->y / Div );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point2D<Type> &operator += ( Point2D<Type> &Pt )
		{
			this->x += Pt.x;
			this->y += Pt.y;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point2D<Type> &operator -= ( Point2D<Type> &Pt )
		{
			this->x -= Pt.x;
			this->y -= Pt.y;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point2D<Type> &operator *= ( Type Mul )
		{
			this->x *= Mul;
			this->y *= Mul;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point2D<Type> &operator /= ( Type Div )
		{
			this->x /= Div;
			this->y /= Div;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		template <typename TypeT>
		Point2D<Type> & operator = ( const Point2D<TypeT> &Src )
		{
			this->x = (Type)Src.x;
			this->y = (Type)Src.y;
			return *this;
		}
	};

	/**
		@brief �R�����̓_
	*/
	template <typename Type>
	struct Point3D
	{
		Type x;							///< �w�ʒu
		Type y;							///< �x�ʒu
		Type z;							///< �y�ʒu

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Point3D()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		template <typename TypeT>
		Point3D( const Point3D<TypeT> &Src )
		{
			this->x = (Type)Src.x;
			this->y = (Type)Src.y;
			this->z = (Type)Src.z;
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w���W
			@param y		[in] �x���W
			@param z		[in] �y���W
		*/
		Point3D( Type x, Type y, Type z )
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point3D<Type> operator + ( Point3D<Type> &Pt )
		{
			return Point3D<Type>( this->x + Pt.x, this->y + Pt.y, this->z + Pt.z );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point3D<Type> operator - ( Point3D<Type> &Pt )
		{
			return Point3D<Type>( this->x - Pt.x, this->y - Pt.y, this->z - Pt.z );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point3D<Type> operator * ( Type Mul )
		{
			return Point3D<Type>( this->x * Mul, this->y * Mul, this->z * Mul );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point3D<Type> operator / ( Type Div )
		{
			return Point3D<Type>( this->x / Div, this->y / Div, this->z / Div );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point3D<Type> &operator += ( Point3D<Type> &Pt )
		{
			this->x += Pt.x;
			this->y += Pt.y;
			this->z += Pt.z;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point3D<Type> &operator -= ( Point3D<Type> &Pt )
		{
			this->x -= Pt.x;
			this->y -= Pt.y;
			this->z -= Pt.z;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point3D<Type> &operator *= ( Type Mul )
		{
			this->x *= Mul;
			this->y *= Mul;
			this->z *= Mul;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point3D<Type> &operator /= ( Type Div )
		{
			this->x /= Div;
			this->y /= Div;
			this->z /= Div;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		template <typename TypeT>
		Point3D<Type> & operator = ( const Point3D<TypeT> &Src )
		{
			this->x = (Type)Src.x;
			this->y = (Type)Src.y;
			this->z = (Type)Src.z;
			return *this;
		}
	};

	typedef Point3D<Float>		Point3DF;	///< Point3D<Float>�̗���
	typedef Point3D<Sint32>		Point3DI;	///< Point3D<Sint32>�̗���
	typedef Point2D<Float>		Point2DF;	///< Point2D<Float>�̗���
	typedef Point2D<Sint32>		Point2DI;	///< Point2D<Sint32>�̗���
	typedef Rect2D<Float>		Rect2DF;	///< Rect2D<Float>�̗���
	typedef Rect2D<Sint32>		Rect2DI;	///< Rect2D<Sint32>�̗���
}
}

