#pragma once


/**
	@file
	@brief 4次元ベクトル
	@author 葉迩倭
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
		@brief 4次元ベクトル演算クラス
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
			@brief コンストラクタ
			@author 葉迩倭
		*/
		Vector4D();
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param v	[in] 入力（x, y, 0, 1)に展開
		*/
		Vector4D( const Vector2D &v );
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param v	[in] 入力（x, y, z, 1)に展開
		*/
		Vector4D( const Vector3D &v );
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param v	[in] 入力
		*/
		Vector4D( const Vector4D &v );
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param fPx	[in] x初期値
			@param fPy	[in] y初期値
			@param fPz	[in] z初期値
			@param fPw	[in] w初期値
		*/
		Vector4D( Float fPx, Float fPy = 0.0f, Float fPz = 0.0f, Float fPw = 1.0f );
		/**
			@brief 加算
			@author 葉迩倭
			@param In1	[in] 加算用入力ベクトル
			@param In2	[in] 加算用入力ベクトル
			@return 計算結果後の*this

			@note
			this = In + In2
		*/
		Vector4D& Add( const Vector4D &In1, const Vector4D &In2 );
		/**
			@brief 減算
			@author 葉迩倭
			@param In1	[in] 加算用入力ベクトル
			@param In2	[in] 加算用入力ベクトル
			@return 計算結果後の*this

			@note
			this = In - In2
		*/
		Vector4D& Sub( const Vector4D &In1, const Vector4D &In2 );
		/**
			@brief 値設定
			@author 葉迩倭
			@param fPx	[in] x設定値
			@param fPy	[in] y設定値
			@param fPz	[in] z設定値
			@param fPw	[in] w設定値
			@return 計算結果後の*this
		*/
		Vector4D& Set( Float fPx, Float fPy, Float fPz, Float fPw = 1.0f );
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
		Float Dot( const Vector4D &In ) const;
		/**
			@brief 正規化
			@author 葉迩倭
			@return 計算結果後の*this

			@note
			長さを1.0に正規化します。
		*/
		Vector4D& Normalize( void );
		/**
			@brief 正規化
			@author 葉迩倭
			@return 計算結果後の*this

			@note
			長さを1.0に正規化します。
		*/
		Vector4D& NormalizeFast( void );
		/**
			@brief 外積
			@author 葉迩倭
			@param In1	[in] 外積算出用入力ベクトル
			@param In2	[in] 外積算出用入力ベクトル
			@return 計算結果後の*this
		*/
		Vector4D& Cross( const Vector4D &In1, const Vector4D &In2 );
		/**
			@brief 反射ベクトルの取得
			@author 葉迩倭
			@param In1	[in] 反射対象の法線
			@param In2	[in] 入射ベクトル
			@return 計算結果後の*this
		*/
		Vector4D& Reflect( const Vector4D &In1, const Vector4D &In2 );
		/**
			@brief 拡大縮小＋回転変換
			@author 葉迩倭
			@param In1	[in] 変換元ベクトル
			@param In2	[in] 変換用マトリックス
			@return 計算結果後の*this
		*/
		Vector4D& TransformNormal( const Vector4D &In1, const Matrix &In2 );
		/**
			@brief 拡大縮小＋回転＋移動変換
			@author 葉迩倭
			@param In1	[in] 変換元ベクトル
			@param In2	[in] 変換用マトリックス
			@return 計算結果後の*this
		*/
		Vector4D& TransformCoord( const Vector4D &In1, const Matrix &In2 );
		/**
			@brief 透視変換
			@author 葉迩倭
			@param In1	[in] 変換元ベクトル
			@param In2	[in] 変換用マトリックス
			@return 計算結果後の*this
		*/
		Vector4D& TransformProjection( const Vector4D &In1, const Matrix &In2 );
		/**
			@brief 正規化
			@author 葉迩倭
			@param In	[in] 正規化元のベクトル
			@return 計算結果後の*this
		*/
		Vector4D& Normalize( const Vector4D &In );
		/**
			@brief 正規化
			@author 葉迩倭
			@param In	[in] 正規化元のベクトル
			@return 計算結果後の*this
		*/
		Vector4D& NormalizeFast( const Vector4D &In );
		/**
			@brief 外積
			@author 葉迩倭
			@param In	[in] 外積用のベクトル
			@return 計算結果後の*this
		*/
		Vector4D& Cross( const Vector4D &In );
		/**
			@brief 反射
			@author 葉迩倭
			@param In	[in] 反射用法線
			@return 計算結果後の*this
		*/
		Vector4D& Reflect( const Vector4D &In );
		/**
			@brief 拡大縮小＋回転変換
			@author 葉迩倭
			@param In	[in] 変換用マトリックス
			@return 計算結果後の*this
		*/
		Vector4D& TransformNormal( const Matrix &In );
		/**
			@brief 拡大縮小＋回転＋移動変換
			@author 葉迩倭
			@param In	[in] 変換用マトリックス
			@return 計算結果後の*this
		*/
		Vector4D& TransformCoord( const Matrix &In );
		/**
			@brief 透視変換
			@author 葉迩倭
			@param In	[in] 変換用マトリックス
			@return 計算結果後の*this
		*/
		Vector4D& TransformProjection( const Matrix &In );
		/**
			@brief X軸回転
			@author 葉迩倭
			@param Angle	[in] 回転角度
			@return 計算結果後の*this
		*/
		Vector4D& RotationX( Sint32 Angle );
		/**
			@brief Y軸回転
			@author 葉迩倭
			@param Angle	[in] 回転角度
			@return 計算結果後の*this
		*/
		Vector4D& RotationY( Sint32 Angle );
		/**
			@brief Z軸回転
			@author 葉迩倭
			@param Angle	[in] 回転角度
			@return 計算結果後の*this
		*/
		Vector4D& RotationZ( Sint32 Angle );
		/**
			@brief ベクトルを軸に回転
			@author 葉迩倭
			@param Angle	[in] 回転角度
			@param Axis		[in] 回転軸
			@return 計算結果後の*this
		*/
		Vector4D& RotationAxis( Sint32 Angle, const Vector3D &Axis );
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Bool operator == ( const Vector4D &v )
		{
			return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Bool operator != ( const Vector4D &v )
		{
			return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator + () const
		{
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator - () const
		{
			return Vector4D(-x, -y, -z, 1.0);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D& operator += ( const Vector2D &v )
		{
			x += v.x;
			y += v.y;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D& operator -= ( const Vector2D &v )
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D& operator *= ( const Vector2D &v )
		{
			x *= v.x;
			y *= v.y;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D& operator /= ( const Vector2D &v )
		{
			x /= v.x;
			y /= v.y;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D& operator += ( const Vector3D &v )
		{
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D& operator -= ( const Vector3D &v )
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D& operator *= ( const Vector3D &v )
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D& operator /= ( const Vector3D &v )
		{
			x /= v.x;
			y /= v.y;
			z /= v.z;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
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
			@brief オペレーター
			@author 葉迩倭
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
			@brief オペレーター
			@author 葉迩倭
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
			@brief オペレーター
			@author 葉迩倭
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
			@brief オペレーター
			@author 葉迩倭
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
			@brief オペレーター
			@author 葉迩倭
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
			@brief オペレーター
			@author 葉迩倭
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
			@brief オペレーター
			@author 葉迩倭
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
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D& operator *= ( Matrix &m )
		{
			return TransformCoord( m );
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator + ( Float f ) const
		{
			return Vector4D(x + f, y + f, z + f, w + f );
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator - ( Float f ) const
		{
			return Vector4D(x - f, y - f, z - f, w - f );
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator * ( Float f ) const
		{
			return Vector4D(x * f, y * f, z * f, w * f );
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator / ( Float f ) const
		{
			return Vector4D(x / f, y / f, z / f, w / f );
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator + ( const Vector2D &v ) const
		{
			return Vector4D(x + v.x, y + v.y, z, w );
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator - ( const Vector2D &v ) const
		{
			return Vector4D(x - v.x, y - v.y, z, w );
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator * ( const Vector2D &v ) const
		{
			return Vector4D(x * v.x, y * v.y, z, w );
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator / ( const Vector2D &v ) const
		{
			return Vector4D(x / v.x, y / v.y, z, w );
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator + ( const Vector3D &v ) const
		{
			return Vector4D(x + v.x, y + v.y, z + v.z, w );
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator - ( const Vector3D &v ) const
		{
			return Vector4D(x - v.x, y - v.y, z - v.z, w );
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator * ( const Vector3D &v ) const
		{
			return Vector4D(x * v.x, y * v.y, z * v.z, w );
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator / ( const Vector3D &v ) const
		{
			return Vector4D(x / v.x, y / v.y, z / v.z, w );
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator + ( const Vector4D &v ) const
		{
			return Vector4D(x + v.x, y + v.y, z + v.z, w + v.w );
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator - ( const Vector4D &v ) const
		{
			return Vector4D(x - v.x, y - v.y, z - v.z, w - v.w );
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator * ( const Vector4D &v ) const
		{
			return Vector4D(x * v.x, y * v.y, z * v.z, w * v.w );
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator / ( const Vector4D &v ) const
		{
			return Vector4D(x / v.x, y / v.y, z / v.z, w / v.w );
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector4D operator * ( Matrix &m ) const
		{
			Vector4D vTemp;
			return vTemp.TransformCoord( *this, m );
		}
	};
}
}

