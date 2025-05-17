#pragma once


/**
	@file
	@brief ３次元ボックス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Vector3D.h"
#include "Math/Matrix.h"
#include "Collision/Plane.h"
#include "Collision/Sphere.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
	/**
		@brief ３次元上の箱
		@author 葉迩倭
	*/
	class SELENE_DLL_API CBox
	{
	public:
		Math::Vector3D Points[8];		///< 箱を構成する8頂点
		CPlane Planes[6];				///< 箱を構成する6平面
		Math::Vector3D vMin;			///< AABBの最少点
		Math::Vector3D vMax;			///< AABBの最大点

	private:
		/**
			@brief ポイントデータを元にボックスの各面、境界球の再計算
			@author 葉迩倭
		*/
		void UpdateBox( void );

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CBox( void );

		/**
			@brief バウンディングボックスを構成する８頂点を指定
			@author 葉迩倭
			@param vPoints	[in] ポイント

			@note
			以下の順番に並んでいる必要があります。<BR>
			(min.x,min.y,min.z)-(min.x,max.y,min.z)-(min.x,max.y,max.z)-(min.x,min.y,max.z)-<BR>
			(max.x,min.y,min.z)-(max.x,max.y,min.z)-(max.x,max.y,max.z)-(max.x,min.y,max.z)
		*/
		void SetPoints( const Math::Vector3D vPoints[] );

		/**
			@brief ３軸指定でバウンディングボックスを構成する８頂点を更新
			@author 葉迩倭
			@param vCenter	[in] 中心
			@param vAxis	[in] 軸(X,Y,Z)
			@param fLength	[in] 軸の長さ(X,Y,Z)
		*/
		void UpdatePoints( const Math::Vector3D &vCenter, const Math::Vector3D vAxis[], const Float fLength[] );

		/**
			@brief バウンディングボックスを指定した行列で変換します。
			@author 葉迩倭
			@param Matrix	[in] ポイントを変換するための行列
		*/
		void Transform( const Math::Matrix &Matrix );

		/**
			@brief バウンディングボックスを指定した行列で変換します。
			@author 葉迩倭
			@param vPoints	[in] ポイントの配列
			@param Matrix	[in] ポイントを変換するための行列
		*/
		void Transform( const Math::Vector3D vPoints[], const Math::Matrix &Matrix );

		/**
			@brief バウンディングボックスを指定した行列で透視変換します。
			@author 葉迩倭
			@param Matrix	[in] ポイントを透視変換するための行列
		*/
		void TransformProjection( const Math::Matrix &Matrix );

		/**
			@brief バウンディングボックスを指定した行列で透視変換します。
			@author 葉迩倭
			@param vPoints	[in] ポイントの配列
			@param Matrix	[in] ポイントを透視変換するための行列
		*/
		void TransformProjection( const Math::Vector3D vPoints[], const Math::Matrix &Matrix );

		/**
			@brief バウンディングボックスを生成
			@author 葉迩倭
			@param MinPt	[in] AABBの最小値
			@param MaxPt	[in] AABBの最大値
			@param Matrix	[in] ポイントを変換するための行列
		*/
		void CreateBox( const Math::Vector3D &MinPt, const Math::Vector3D &MaxPt, const Math::Matrix &Matrix );

		/**
			@brief バウンディングボックスを生成
			@author 葉迩倭
			@param MinPt	[in] AABBの最小値
			@param MaxPt	[in] AABBの最大値
			@param Matrix	[in] ポイントを透視変換するための行列
		*/
		void CreateBoxProjection( const Math::Vector3D &MinPt, const Math::Vector3D &MaxPt, const Math::Matrix &Matrix );
	};
}
}

