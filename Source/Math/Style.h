#pragma once


/**
	@file
	@brief 姿勢管理
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Math/Vector3D.h"
#include "Math/Matrix.h"
#include "Math/Quaternion.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Math
{
	/**
		@brief 姿勢制御クラス
	*/
	class SELENE_DLL_API Style
	{
	private:
		Vector3D m_vUp;					///< 上方向ベクトル
		Vector3D m_vRight;				///< 右方向ベクトル
		Vector3D m_vFront;				///< 前方向ベクトル
		Vector3D m_vPosition;			///< 位置ベクトル
		Vector3D m_vLocalPosition;		///< 位置ベクトル
		Vector3D m_vScale;				///< 拡大縮小ベクトル

		Bool m_IsScale;					///< 拡大縮小
		Bool m_IsLocal;					///< ローカル移動

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		Style();
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param Style	[in] コピー元
		*/
		Style( const Style &Style );
		/**
			@brief 変換初期化
			@author 葉迩倭

			@note
			変換を初期化して初期値に戻します。
		*/
		virtual void TransformReset( void );
		/**
			@brief X軸回転
			@author 葉迩倭
			@param Rot		[in] 角度

			@note
			ワールド座標を基準にX軸周りに回転させます。
		*/
		virtual void RotationX( Sint32 Rot );
		/**
			@brief Y軸回転
			@author 葉迩倭
			@param Rot		[in] 角度

			@note
			ワールド座標を基準にY軸周りに回転させます。
		*/
		virtual void RotationY( Sint32 Rot );
		/**
			@brief Z軸回転
			@author 葉迩倭
			@param Rot		[in] 角度

			@note
			ワールド座標を基準にZ軸周りに回転させます。
		*/
		virtual void RotationZ( Sint32 Rot );
		/**
			@brief ピッチング
			@author 葉迩倭
			@param Rot		[in] 角度

			@note
			ローカル座標を基準にX軸周りに回転させます。
		*/
		virtual void LocalRotationX( Sint32 Rot );
		/**
			@brief ヘッディング
			@author 葉迩倭
			@param Rot		[in] 角度

			@note
			ローカル座標を基準にY軸周りに回転させます。
		*/
		virtual void LocalRotationY( Sint32 Rot );
		/**
			@brief ローリング
			@author 葉迩倭
			@param Rot		[in] 角度

			@note
			ローカル座標を基準にZ軸周りに回転させます。
		*/
		virtual void LocalRotationZ( Sint32 Rot );
		/**
			@brief クォータニオンで回転
			@author 葉迩倭
			@param Quat		[in] クォータニオン

			@note
			クォータニオンを使って回転させます。
		*/
		virtual void RotationQuaternion( const Quaternion &Quat );
		/**
			@brief 移動
			@author 葉迩倭
			@param fPx		[in] X座標
			@param fPy		[in] Y座標
			@param fPz		[in] Z座標

			@note
			指定座標へ移動させます。
		*/
		virtual void Translation( Float fPx, Float fPy, Float fPz );
		/**
			@brief 移動
			@author 葉迩倭
			@param vPos		[in] 座標

			@note
			指定座標へ移動させます。
		*/
		virtual void Translation( const Vector3D &vPos );
		/**
			@brief 移動
			@author 葉迩倭
			@param fPx		[in] X座標
			@param fPy		[in] Y座標
			@param fPz		[in] Z座標

			@note
			指定座標へ移動させます。
		*/
		virtual void LocalTranslation( Float fPx, Float fPy, Float fPz );
		/**
			@brief 移動
			@author 葉迩倭
			@param vPos		[in] 座標

			@note
			指定座標へ移動させます。
		*/
		virtual void LocalTranslation( const Vector3D &vPos );
		/**
			@brief 拡大縮小
			@author 葉迩倭
			@param fSx		[in] X軸拡大縮小率
			@param fSy		[in] Y軸拡大縮小率
			@param fSz		[in] Z軸拡大縮小率

			@note
			指定倍率で拡大縮小をさせます。
		*/
		virtual void Scaling( Float fSx, Float fSy, Float fSz );
		/**
			@brief 任意方向へ姿勢
			@author 葉迩倭
			@param vEye		[in] 視点位置
			@param vAt		[in] 目標位置
			@param vUp		[in] 上方向

			@note
			任意の場所から指定の場所を見た場合の姿勢を作成します。
		*/
		virtual void LookAt( const Vector3D &vEye, const Vector3D &vAt, const Vector3D &vUp );
		/**
			@brief 行列から変換
			@author 葉迩倭
			@param Mat		[in] 変換マトリックス

			@note
			指定のマトリックスになるような姿勢データを生成します。
		*/
		virtual void FromMatrix( const Matrix &Mat );
		/**
			@brief X軸回転角度取得
			@author 葉迩倭
			@return X軸における回転角度

			@note
			X軸における回転角度を取得します。
		*/
		virtual Sint32 GetAngleX( void ) const;
		/**
			@brief Y軸回転角度取得
			@author 葉迩倭
			@return Y軸における回転角度

			@note
			Y軸における回転角度を取得します。
		*/
		virtual Sint32 GetAngleY( void ) const;
		/**
			@brief Z軸回転角度取得
			@author 葉迩倭
			@return Z軸における回転角度

			@note
			Z軸における回転角度を取得します。
		*/
		virtual Sint32 GetAngleZ( void ) const;
		/**
			@brief 位置設定
			@author 葉迩倭
			@param Pos	[in] 位置

			@note
			指定位置に移動します。
		*/
		virtual void SetPosition( const Vector3D &Pos );
		/**
			@brief 前方設定
			@author 葉迩倭
			@param Vec	[in] 前方ベクトル

			@note
			姿勢の正面方向を設定します。
		*/
		virtual void SetFront( const Vector3D &Vec );
		/**
			@brief 右方設定
			@author 葉迩倭
			@param Vec	[in] 右方ベクトル

			@note
			姿勢の右手方向を設定します。
		*/
		virtual void SetRight( const Vector3D &Vec );
		/**
			@brief 上方設定
			@author 葉迩倭
			@param Vec	[in] 上方ベクトル

			@note
			姿勢の上手方向を設定します。
		*/
		virtual void SetUp( const Vector3D &Vec );
		/**
			@brief 位置取得
			@author 葉迩倭
			@param Pos	[out] 格納先

			@note
			指定位置に移動します。
		*/
		virtual void GetPosition( Vector3D &Pos ) const;
		/**
			@brief 前方取得
			@author 葉迩倭
			@param Vec	[out] 格納先

			@note
			姿勢の正面方向を取得します。
		*/
		virtual void GetFront( Vector3D &Vec ) const;
		/**
			@brief 右方取得
			@author 葉迩倭
			@param Vec	[out] 格納先

			@note
			姿勢の右手方向を取得します。
		*/
		virtual void GetRight( Vector3D &Vec ) const;
		/**
			@brief 上方取得
			@author 葉迩倭
			@param Vec	[out] 格納先

			@note
			姿勢の上手方向を取得します。
		*/
		virtual void GetUp( Vector3D &Vec ) const;
		/**
			@brief 姿勢行列を取得
			@author 葉迩倭
			@param Mat	[out] 格納先

			@note
			姿勢行列を取得します。<BR>
			この行列には回転要素しか含みません。
		*/
		virtual void GetStyle( Matrix &Mat ) const;
		/**
			@brief 逆姿勢行列を取得
			@author 葉迩倭
			@param Mat	[out] 格納先

			@note
			逆姿勢行列を取得します。<BR>
			この行列には回転要素しか含みません。
		*/
		virtual void GetStyleInverse( Matrix &Mat ) const;
		/**
			@brief 変換行列を取得
			@author 葉迩倭
			@param Mat	[out] 格納先

			@note
			変換行列を取得します。<BR>
			この行列には回転と位置要素しか含みません。
		*/
		virtual void GetTransform( Matrix &Mat ) const;
		/**
			@brief 逆変換行列を取得
			@author 葉迩倭
			@param Mat	[out] 格納先

			@note
			逆変換行列を取得します。<BR>
			この行列には回転と位置要素しか含みません。
		*/
		virtual void GetTransformInverse( Matrix &Mat ) const;
		/**
			@brief 変換行列を取得
			@author 葉迩倭
			@param Mat	[out] 格納先

			@note
			変換行列を取得します。<BR>
			この行列には回転と位置と拡大縮小の全要素を含みます。
		*/
		virtual void GetTransformWithScale( Matrix &Mat ) const;
		/**
			@brief 逆変換行列を取得
			@author 葉迩倭
			@param Mat	[out] 格納先

			@note
			逆変換行列を取得します。<BR>
			この行列には回転と位置と拡大縮小の全要素を含みます。
		*/
		virtual void GetTransformInverseWithScale( Matrix &Mat ) const;
	};
}
}

