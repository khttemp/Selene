#pragma once


/**
	@file
	@brief 2次元ベクトル
	@author 葉迩倭
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
		@brief 2次元ベクトル演算クラス
	*/
	class SELENE_DLL_API Vector2D
	{
	public:
		Float x;
		Float y;

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		Vector2D();
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param v	[in] 入力
		*/
		Vector2D( const Vector2D &v );
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param fPx	[in] x初期値
			@param fPy	[in] y初期値
		*/
		Vector2D( Float fPx, Float fPy );
		/**
			@brief 加算
			@author 葉迩倭
			@param In1	[in] 加算用入力ベクトル
			@param In2	[in] 加算用入力ベクトル
			@return 計算結果後の*this

			@note
			this = In + In2
		*/
		Vector2D& Add( const Vector2D &In1, const Vector2D &In2 );
		/**
			@brief 減算
			@author 葉迩倭
			@param In1	[in] 加算用入力ベクトル
			@param In2	[in] 加算用入力ベクトル
			@return 計算結果後の*this

			@note
			this = In - In2
		*/
		Vector2D& Sub( const Vector2D &In1, const Vector2D &In2 );
		/**
			@brief 値設定
			@author 葉迩倭
			@param fPx	[in] x設定値
			@param fPy	[in] y設定値
			@return 計算結果後の*this
		*/
		Vector2D& Set( Float fPx, Float fPy );
		/**
			@brief 長さの二乗取得
			@author 葉迩倭
			@return 長さの二乗
		*/
		Float LengthSq( void ) const;
		/**
			@brief 長さ取得
			@author 葉迩倭
			@return 長さ
		*/
		Float Length( void ) const;
		/**
			@brief 長さ取得
			@author 葉迩倭
			@return 長さ
		*/
		Float LengthFast( void ) const;
		/**
			@brief 内積
			@author 葉迩倭
			@param In	[in] 内積算出用入力ベクトル
			@return 内積
		*/
		Float Dot( const Vector2D &In ) const;
		/**
			@brief 正規化
			@author 葉迩倭
			@return 計算結果後の*this

			@note
			長さを1.0に正規化します。
		*/
		Vector2D& Normalize( void );
		/**
			@brief 正規化
			@author 葉迩倭
			@return 計算結果後の*this

			@note
			長さを1.0に正規化します。
		*/
		Vector2D& NormalizeFast( void );
		/**
			@brief 反射ベクトルの取得
			@author 葉迩倭
			@param In1	[in] 反射対象の法線
			@param In2	[in] 入射ベクトル
			@return 計算結果後の*this
		*/
		Vector2D& Reflect( const Vector2D &In1, const Vector2D &In2 );
		/**
			@brief 正規化
			@author 葉迩倭
			@param In	[in] 正規化元のベクトル
			@return 計算結果後の*this
		*/
		Vector2D& Normalize( const Vector2D &In );
		/**
			@brief 正規化
			@author 葉迩倭
			@param In	[in] 正規化元のベクトル
			@return 計算結果後の*this
		*/
		Vector2D& NormalizeFast( const Vector2D &In );
		/**
			@brief 外積
			@author 葉迩倭
			@param In	[in] 外積用のベクトル
			@return z=0.0として計算したベクトルの外積
		*/
		Float Cross( const Vector2D &In ) const;
		/**
			@brief 反射
			@author 葉迩倭
			@param In	[in] 反射用法線
			@return 計算結果後の*this
		*/
		Vector2D& Reflect( const Vector2D &In );
		/**
			@brief Z軸回転
			@author 葉迩倭
			@param Angle	[in] 回転角度
			@return 計算結果後の*this
		*/
		Vector2D& RotationZ( Sint32 Angle );
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector2D operator + () const
		{
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector2D operator - () const
		{
			return Vector2D(-x, -y);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Bool operator == ( const Vector2D &v )
		{
			return (x == v.x) && (y == v.y);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Bool operator != ( const Vector2D &v )
		{
			return (x != v.x) || (y != v.y);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector2D& operator += ( Float f )
		{
			x += f;
			y += f;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector2D& operator -= ( Float f )
		{
			x -= f;
			y -= f;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector2D& operator *= ( Float f )
		{
			x *= f;
			y *= f;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector2D& operator /= ( Float f )
		{
			x /= f;
			y /= f;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector2D& operator += ( const Vector2D &v )
		{
			x += v.x;
			y += v.y;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector2D& operator -= ( const Vector2D &v )
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector2D& operator *= ( const Vector2D &v )
		{
			x *= v.x;
			y *= v.y;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector2D& operator /= ( const Vector2D &v )
		{
			x /= v.x;
			y /= v.y;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector2D operator + ( Float f ) const
		{
		    return Vector2D(x + f, y + f);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector2D operator - ( Float f ) const
		{
			f = 1.0f / f;
			return Vector2D(x - f, y - f);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector2D operator * ( Float f ) const
		{
		    return Vector2D(x * f, y * f);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector2D operator / ( Float f ) const
		{
			return Vector2D(x / f, y / f);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector2D operator + ( const Vector2D &v ) const
		{
			return Vector2D(x + v.x, y + v.y);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector2D operator - ( const Vector2D &v ) const
		{
			return Vector2D(x - v.x, y - v.y);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector2D operator * ( const Vector2D &v ) const
		{
			return Vector2D(x * v.x, y * v.y);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector2D operator / ( const Vector2D &v ) const
		{
			return Vector2D(x / v.x, y / v.y);
		}
	};
}
}

