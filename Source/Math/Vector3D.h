#pragma once


/**
	@file
	@brief 3次元ベクトル
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
		@brief 3次元ベクトル演算クラス
	*/
	class SELENE_DLL_API Vector3D
	{
	public:
		Float x;
		Float y;
		Float z;

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		Vector3D();
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param v	[in] 入力
		*/
		Vector3D( const Vector3D &v );
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param fPx	[in] x初期値
			@param fPy	[in] y初期値
			@param fPz	[in] z初期値
		*/
		Vector3D( Float fPx, Float fPy, Float fPz );
		/**
			@brief 加算
			@author 葉迩倭
			@param In1	[in] 加算用入力ベクトル
			@param In2	[in] 加算用入力ベクトル
			@return 計算結果後の*this

			@note
			this = In + In2
		*/
		Vector3D& Add( const Vector3D &In1, const Vector3D &In2 );
		/**
			@brief 減算
			@author 葉迩倭
			@param In1	[in] 加算用入力ベクトル
			@param In2	[in] 加算用入力ベクトル
			@return 計算結果後の*this

			@note
			this = In - In2
		*/
		Vector3D& Sub( const Vector3D &In1, const Vector3D &In2 );
		/**
			@brief 値設定
			@author 葉迩倭
			@param fPx	[in] x設定値
			@param fPy	[in] y設定値
			@param fPz	[in] z設定値
			@return 計算結果後の*this
		*/
		Vector3D& Set( Float fPx, Float fPy, Float fPz );
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
		Float Dot( const Vector3D &In ) const;
		/**
			@brief 正規化
			@author 葉迩倭
			@return 計算結果後の*this

			@note
			長さを1.0に正規化します。
		*/
		Vector3D &Normalize( void );
		/**
			@brief 正規化
			@author 葉迩倭
			@return 計算結果後の*this

			@note
			長さを1.0に正規化します。
		*/
		Vector3D &NormalizeFast( void );
		/**
			@brief 外積
			@author 葉迩倭
			@param In1	[in] 外積算出用入力ベクトル
			@param In2	[in] 外積算出用入力ベクトル
			@return 計算結果後の*this
		*/
		Vector3D& Cross( const Vector3D &In1, const Vector3D &In2 );
		/**
			@brief 反射ベクトルの取得
			@author 葉迩倭
			@param In1	[in] 反射対象の法線
			@param In2	[in] 入射ベクトル
			@return 計算結果後の*this
		*/
		Vector3D& Reflect( const Vector3D &In1, const Vector3D &In2 );
		/**
			@brief 拡大縮小＋回転変換
			@author 葉迩倭
			@param In1	[in] 変換元ベクトル
			@param In2	[in] 変換用マトリックス
			@return 計算結果後の*this
		*/
		Vector3D& TransformNormal( const Vector3D &In1, const Matrix &In2 );
		/**
			@brief 拡大縮小＋回転＋移動変換
			@author 葉迩倭
			@param In1	[in] 変換元ベクトル
			@param In2	[in] 変換用マトリックス
			@return 計算結果後の*this
		*/
		Vector3D& TransformCoord( const Vector3D &In1, const Matrix &In2 );
		/**
			@brief 透視変換
			@author 葉迩倭
			@param In1	[in] 変換元ベクトル
			@param In2	[in] 変換用マトリックス
			@return 計算結果後の*this
		*/
		Vector3D& TransformProjection( const Vector3D &In1, const Matrix &In2 );
		/**
			@brief 正規化
			@author 葉迩倭
			@param In	[in] 正規化元のベクトル
			@return 計算結果後の*this
		*/
		Vector3D &Normalize( const Vector3D &In );
		/**
			@brief 正規化
			@author 葉迩倭
			@param In	[in] 正規化元のベクトル
			@return 計算結果後の*this
		*/
		Vector3D &NormalizeFast( const Vector3D &In );
		/**
			@brief 外積
			@author 葉迩倭
			@param In	[in] 外積用のベクトル
			@return 計算結果後の*this
		*/
		Vector3D& Cross( const Vector3D &In );
		/**
			@brief 反射
			@author 葉迩倭
			@param In	[in] 反射用法線
			@return 計算結果後の*this
		*/
		Vector3D& Reflect( const Vector3D &In );
		/**
			@brief 拡大縮小＋回転変換
			@author 葉迩倭
			@param In	[in] 変換用マトリックス
			@return 計算結果後の*this
		*/
		Vector3D& TransformNormal( const Matrix &In );
		/**
			@brief 拡大縮小＋回転＋移動変換
			@author 葉迩倭
			@param In	[in] 変換用マトリックス
			@return 計算結果後の*this
		*/
		Vector3D& TransformCoord( const Matrix &In );
		/**
			@brief 透視変換
			@author 葉迩倭
			@param In	[in] 変換用マトリックス
			@return 計算結果後の*this
		*/
		Vector3D& TransformProjection( const Matrix &In );
		/**
			@brief X軸回転
			@author 葉迩倭
			@param Angle	[in] 回転角度
			@return 計算結果後の*this
		*/
		Vector3D& RotationX( Sint32 Angle );
		/**
			@brief Y軸回転
			@author 葉迩倭
			@param Angle	[in] 回転角度
			@return 計算結果後の*this
		*/
		Vector3D& RotationY( Sint32 Angle );
		/**
			@brief Z軸回転
			@author 葉迩倭
			@param Angle	[in] 回転角度
			@return 計算結果後の*this
		*/
		Vector3D& RotationZ( Sint32 Angle );
		/**
			@brief ベクトルを軸に回転
			@author 葉迩倭
			@param Angle	[in] 回転角度
			@param Axis		[in] 回転軸
			@return 計算結果後の*this
		*/
		Vector3D& RotationAxis( Sint32 Angle, const Vector3D &Axis );
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector3D operator + () const
		{
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector3D operator - () const
		{
			return Vector3D(-x, -y, -z);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Bool operator == ( const Vector3D &v )
		{
			return (x == v.x) && (y == v.y) && (z == v.z);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Bool operator != ( const Vector3D &v )
		{
			return (x != v.x) || (y != v.y) || (z != v.z);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector3D& operator += ( Float f )
		{
			x += f;
			y += f;
			z += f;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector3D& operator -= ( Float f )
		{
			x -= f;
			y -= f;
			z -= f;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector3D& operator *= ( Float f )
		{
			x *= f;
			y *= f;
			z *= f;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector3D& operator /= ( Float f )
		{
			x /= f;
			y /= f;
			z /= f;
			return *this;
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector3D& operator += ( const Vector3D &v )
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
		Vector3D& operator -= ( const Vector3D &v )
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
		Vector3D& operator *= ( const Vector3D &v )
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
		Vector3D& operator /= ( const Vector3D &v )
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
		Vector3D operator + ( Float f ) const
		{
			return Vector3D(x + f, y + f, z + f);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector3D operator - ( Float f ) const
		{
			return Vector3D(x - f, y - f, z - f);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector3D operator * ( Float f ) const
		{
			return Vector3D(x * f, y * f, z * f);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector3D operator / ( Float f ) const
		{
			return Vector3D(x / f, y / f, z / f);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector3D operator + ( const Vector3D &v ) const
		{
			return Vector3D(x + v.x, y + v.y, z + v.z);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector3D operator - ( const Vector3D &v ) const
		{
			return Vector3D(x - v.x, y - v.y, z - v.z);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector3D operator * ( const Vector3D &v ) const
		{
			return Vector3D(x * v.x, y * v.y, z * v.z);
		}
		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		Vector3D operator / ( const Vector3D &v ) const
		{
			return Vector3D(x - v.x, y - v.y, z - v.z);
		}
	};
}
}

