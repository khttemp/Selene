#pragma once


/**
	@file
	@brief 算術演算
	@author 葉迩倭
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
@brief sin取得
@author 葉迩倭
@param Angle	[in] 1周65536とした角度
@return sin値

@note
sin値を取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // 90度の時のsin値を取得
  Float fRet = Math::Sin( DEG_TO_ANGLE(90) );

  return 0;
}
@endcode
*/
SELENE_DLL_API Float Sin( Sint32 Angle );

/**
@brief cos取得
@author 葉迩倭
@param Angle	[in] 1周65536とした角度
@return cos値

@note
cos値を取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // 90度の時のcos値を取得
  Float fRet = Math::Cos( DEG_TO_ANGLE(90) );

  return 0;
}
@endcode
*/
SELENE_DLL_API Float Cos( Sint32 Angle );

/**
@brief ベクトル取得
@author 葉迩倭
@param Angle	[in] 1周65536とした角度
@return 2Dベクトル

@note
正規化された2Dベクトルを取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // 90度の方向を向く単位ベクトルを取得
  Vector2D vDir = Math::GetVector( DEG_TO_ANGLE(90) );

  return 0;
}
@endcode
*/
SELENE_DLL_API Vector2D GetVector( Sint32 Angle );

/**
@brief atan2取得
@author 葉迩倭
@param Dx	[in] Ｘ距離
@param Dy	[in] Ｙ距離
@return X-Yの成す角度

@note
X,Yから求められるatan2の値をSeleneの角度単位に<BR>
あわせた値で取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // (x,y)=(100.0f,50.0f)における原点基準の角度を求める
  Sint32 Angle = Math::ATan2( 100.0f, 50.0f );

  return 0;
}
@endcode
*/
SELENE_DLL_API Sint32 ATan2( Float Dx, Float Dy );

	/**
		@brief 矩形データ
		@author 葉迩倭
	*/
	template <typename Type>
	class Rect2D
	{
	public:
		Type x;					///< Ｘ始点座標
		Type y;					///< Ｙ始点座標
		Type w;					///< Ｘサイズ
		Type h;					///< Ｙサイズ

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		Rect2D()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭
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
			@brief コンストラクタ
			@author 葉迩倭

			@param x		[in] Ｘ始点座標
			@param y		[in] Ｙ始点座標
			@param w		[in] Ｘサイズ
			@param h		[in] Ｙサイズ
		*/
		Rect2D( Type x, Type y, Type w, Type h )
		{
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}

		/**
			@brief 値設定
			@author 葉迩倭

			@param x		[in] Ｘ中心座標
			@param y		[in] Ｙ中心座標
			@param w		[in] Ｘサイズ
			@param h		[in] Ｙサイズ
		*/
		void Set( Type x, Type y, Type w, Type h )
		{
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}

		/**
			@brief 値設定
			@author 葉迩倭

			@param x		[in] Ｘ中心座標
			@param y		[in] Ｙ中心座標
			@param w		[in] Ｘサイズ
			@param h		[in] Ｙサイズ
			@param Scale	[in] 拡大縮小率
		*/
		void SetCenter( Type x, Type y, Type w, Type h, Float Scale = 1.0f )
		{
			this->w = (Type)(w * Scale);
			this->h = (Type)(h * Scale);
			this->x = x - (Type)(toF(this->w) * 0.5f);
			this->y = y - (Type)(toF(this->h) * 0.5f);
		}

		/**
			@brief オペレーター
			@author 葉迩倭
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
		@brief ２次元の点
		@author 葉迩倭
	*/
	template <typename Type>
	class Point2D
	{
	public:
		Type x;					///< Ｘ座標
		Type y;					///< Ｙ座標

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		Point2D()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		template <typename TypeT>
		Point2D( const Point2D<TypeT> &Src )
		{
			this->x = (Type)Src.x;
			this->y = (Type)Src.y;
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x		[in] Ｘ座標
			@param y		[in] Ｙ座標
		*/
		Point2D( Type x, Type y )
		{
			this->x = x;
			this->y = y;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Point2D<Type> operator + ( Point2D<Type> &Pt )
		{
			return Point2D<Type>( this->x + Pt.x, this->y + Pt.y );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Point2D<Type> operator - ( Point2D<Type> &Pt )
		{
			return Point2D<Type>( this->x - Pt.x, this->y - Pt.y );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Point2D<Type> operator * ( Type Mul )
		{
			return Point2D<Type>( this->x * Mul, this->y * Mul );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Point2D<Type> operator / ( Type Div )
		{
			return Point2D<Type>( this->x / Div, this->y / Div );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Point2D<Type> &operator += ( Point2D<Type> &Pt )
		{
			this->x += Pt.x;
			this->y += Pt.y;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Point2D<Type> &operator -= ( Point2D<Type> &Pt )
		{
			this->x -= Pt.x;
			this->y -= Pt.y;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Point2D<Type> &operator *= ( Type Mul )
		{
			this->x *= Mul;
			this->y *= Mul;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Point2D<Type> &operator /= ( Type Div )
		{
			this->x /= Div;
			this->y /= Div;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
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
		@brief ３次元の点
	*/
	template <typename Type>
	struct Point3D
	{
		Type x;							///< Ｘ位置
		Type y;							///< Ｙ位置
		Type z;							///< Ｚ位置

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		Point3D()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		template <typename TypeT>
		Point3D( const Point3D<TypeT> &Src )
		{
			this->x = (Type)Src.x;
			this->y = (Type)Src.y;
			this->z = (Type)Src.z;
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x		[in] Ｘ座標
			@param y		[in] Ｙ座標
			@param z		[in] Ｚ座標
		*/
		Point3D( Type x, Type y, Type z )
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Point3D<Type> operator + ( Point3D<Type> &Pt )
		{
			return Point3D<Type>( this->x + Pt.x, this->y + Pt.y, this->z + Pt.z );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Point3D<Type> operator - ( Point3D<Type> &Pt )
		{
			return Point3D<Type>( this->x - Pt.x, this->y - Pt.y, this->z - Pt.z );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Point3D<Type> operator * ( Type Mul )
		{
			return Point3D<Type>( this->x * Mul, this->y * Mul, this->z * Mul );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Point3D<Type> operator / ( Type Div )
		{
			return Point3D<Type>( this->x / Div, this->y / Div, this->z / Div );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Point3D<Type> &operator += ( Point3D<Type> &Pt )
		{
			this->x += Pt.x;
			this->y += Pt.y;
			this->z += Pt.z;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Point3D<Type> &operator -= ( Point3D<Type> &Pt )
		{
			this->x -= Pt.x;
			this->y -= Pt.y;
			this->z -= Pt.z;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Point3D<Type> &operator *= ( Type Mul )
		{
			this->x *= Mul;
			this->y *= Mul;
			this->z *= Mul;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Point3D<Type> &operator /= ( Type Div )
		{
			this->x /= Div;
			this->y /= Div;
			this->z /= Div;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
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

	typedef Point3D<Float>		Point3DF;	///< Point3D<Float>の略称
	typedef Point3D<Sint32>		Point3DI;	///< Point3D<Sint32>の略称
	typedef Point2D<Float>		Point2DF;	///< Point2D<Float>の略称
	typedef Point2D<Sint32>		Point2DI;	///< Point2D<Sint32>の略称
	typedef Rect2D<Float>		Rect2DF;	///< Rect2D<Float>の略称
	typedef Rect2D<Sint32>		Rect2DI;	///< Rect2D<Sint32>の略称
}
}

