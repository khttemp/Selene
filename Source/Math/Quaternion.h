#pragma once


/**
	@file
	@brief 四元数管理
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Math
{
	/**
		@brief 四元数クラス
	*/
	class SELENE_DLL_API Quaternion
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
		Quaternion();
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param x	[in] X要素
			@param y	[in] Y要素
			@param z	[in] Z要素
			@param w	[in] W要素
		*/
		Quaternion( Float x, Float y, Float z, Float w );
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param In	[in] クォータニオン
		*/
		Quaternion( const Quaternion &In );
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param mIn	[in] マトリックス
		*/
		Quaternion( const Matrix &mIn );
		/**
			@brief 加算
			@author 葉迩倭
			@param In1	[in] 入力クォータニオン１
			@param In2	[in] 入力クォータニオン２
			@return 計算結果後の*this
			@note
			二つのクォータニオンを加算します。
		*/
		Quaternion& Add( const Quaternion &In1, const Quaternion &In2 );
		/**
			@brief 減算
			@author 葉迩倭
			@param In1	[in] 入力クォータニオン１
			@param In2	[in] 入力クォータニオン２
			@return 計算結果後の*this
			@note
			二つのクォータニオンを減算します。
		*/
		Quaternion& Sub( const Quaternion &In1, const Quaternion &In2 );
		/**
			@brief 乗算
			@author 葉迩倭
			@param In1	[in] 入力クォータニオン１
			@param In2	[in] 入力クォータニオン２
			@return 計算結果後の*this
			@note
			二つのクォータニオンを乗算します。
		*/
		Quaternion& Mul( const Quaternion &In1, const Quaternion &In2 );
		/**
			@brief 線形補間
			@author 葉迩倭
			@param In0		[in] 入力クォータニオン１
			@param In1		[in] 入力クォータニオン２
			@param fRate	[in] ブレンド率(0.0～1.0f)
			@return 計算結果後の*this
			@note
			二つのクォータニオンを線形補間します
		*/
		Quaternion& Lerp( const Quaternion &In0, const Quaternion &In1, Float fRate );
		/**
			@brief 球面線形補間
			@author 葉迩倭
			@param In0		[in] 入力クォータニオン１
			@param In1		[in] 入力クォータニオン２
			@param fRate	[in] ブレンド率(0.0～1.0f)
			@return 計算結果後の*this
			@note
			二つのクォータニオンを球面線形補間します
		*/
		Quaternion& Slerp( const Quaternion &In0, const Quaternion &In1, Float fRate );
		/**
			@brief 加算
			@author 葉迩倭
			@param In	[in] 入力クォータニオン
			@note
			二つのクォータニオンを加算します。
		*/
		Quaternion& Add( const Quaternion &In );
		/**
			@brief 減算
			@author 葉迩倭
			@param In	[in] 入力クォータニオン
			@return 計算結果後の*this
			@note
			二つのクォータニオンを減算します。
		*/
		Quaternion& Sub( const Quaternion &In );
		/**
			@brief 乗算
			@author 葉迩倭
			@param In	[in] 入力クォータニオン
			@return 計算結果後の*this
			@note
			二つのクォータニオンを乗算します。
		*/
		Quaternion& Mul( const Quaternion &In );
		/**
			@brief 線形補間
			@author 葉迩倭
			@param In		[in] 入力クォータニオン
			@param fRate	[in] ブレンド率(0.0～1.0f)
			@return 計算結果後の*this
			@note
			二つのクォータニオンを線形補間します
		*/
		Quaternion& Lerp( const Quaternion &In, Float fRate );
		/**
			@brief 球面線形補間
			@author 葉迩倭
			@param In		[in] 入力クォータニオン
			@param fRate	[in] ブレンド率(0.0～1.0f)
			@return 計算結果後の*this
			@note
			二つのクォータニオンを球面線形補間します
		*/
		Quaternion& Slerp( const Quaternion &In, Float fRate );
		/**
			@brief 初期化
			@author 葉迩倭
			@return 計算結果後の*this
			@note
			xyz=0.0、w=1.0に初期化します。
		*/
		Quaternion& Identity( void );
		/**
			@brief 長さの二乗を取得
			@author 葉迩倭
			@return 長さの二乗
			@note
			長さの二乗を取得します。
		*/
		Float LengthSq( void ) const;
		/**
			@brief 長さを取得
			@author 葉迩倭
			@return 長さ
			@note
			長さを取得します。
		*/
		Float Length( void ) const;
		/**
			@brief 内積を取得
			@author 葉迩倭
			@return 内積
			@note
			内積を取得します
		*/
		Float Dot( const Quaternion &In ) const;
		/**
			@brief 共役
			@author 葉迩倭
			@return 計算結果後の*this
			@note
			クォータニオンを共役します。
		*/
		Quaternion& Conjugate( void );
		/**
			@brief 共役
			@author 葉迩倭
			@return 計算結果後の*this
			@note
			クォータニオンを共役して格納します。
		*/
		Quaternion& Conjugate( const Quaternion &In );
	};
}
}

