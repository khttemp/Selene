#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Matrix.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief カスタムシーン描画オブジェクトインターフェイス
		@author 葉迩倭

		@note
		カスタムシーンの描画オブジェクトを扱うためのインターフェイスです。
	*/
	class ICustomizedSceneRenderObject : public IInterface
	{
	protected:
		virtual ~ICustomizedSceneRenderObject() {}

	public:
		/**
			@brief ボーン用頂点の有無を取得
			@author 葉迩倭
			@retval false	無い
			@retval true	有る

			@note
			描画オブジェクトがボーン用頂点を持っているかを取得します。
		*/
		virtual Bool IsSupportVertexBone( void ) = 0;

		/**
			@brief テクスチャ用頂点の有無を取得
			@author 葉迩倭
			@retval false	無い
			@retval true	有る

			@note
			描画オブジェクトがテクスチャ用頂点を持っているかを取得します。
		*/
		virtual Bool IsSupportVertexTexture( void ) = 0;

		/**
			@brief 法線用頂点の有無を取得
			@author 葉迩倭
			@retval false	無い
			@retval true	有る

			@note
			描画オブジェクトが法線用頂点を持っているかを取得します。
		*/
		virtual Bool IsSupportVertexNormal( void ) = 0;

		/**
			@brief バンプ用接線用頂点の有無を取得
			@author 葉迩倭
			@retval false	無い
			@retval true	有る

			@note
			描画オブジェクトがバンプ用接線用頂点を持っているかを取得します。
		*/
		virtual Bool IsSupportVertexBump( void ) = 0;

		/**
			@brief マテリアル数取得
			@author 葉迩倭
			@return マテリアル数

			@note
			描画オブジェクトが所有するマテリアル数を取得します。
		*/
		virtual Sint32 GetMaterialCount( void ) = 0;

		/**
			@brief 描画マテリアル取得
			@author 葉迩倭
			@param Index	[in] マテリアル番号

			@note
			描画オブジェクトが所有するマテリアルデータを取得します。
		*/
		virtual ICustomizedSceneRenderMaterial *GetMaterialPointer( Sint32 Index ) = 0;

		/**
			@brief ボーン数を取得
			@author 葉迩倭
			@return ボーン数

			@note
			描画オブジェクトが所持しているボーン数を取得します。
		*/
		virtual Sint32 GetBoneCount( void ) = 0;

		/**
			@brief ワールド行列取得
			@author 葉迩倭
			@return ワールド行列

			@note
			描画オブジェクトの行列データを取得します。
		*/
		virtual const Math::Matrix &GetWorldMatrix( void ) = 0;


		/**
			@brief 前フレームのワールド行列取得
			@author 葉迩倭
			@return ワールド行列

			@note
			描画オブジェクトの行列データを取得します。
		*/
		virtual const Math::Matrix &GetWorldMatrixPrev( void ) = 0;

		/**
			@brief ワールド＞ビュー行列取得
			@author 葉迩倭
			@return ワールド＞ビュー行列

			@note
			描画オブジェクトの行列データを取得します。
		*/
		virtual const Math::Matrix &GetWorldViewMatrix( void ) = 0;

		/**
			@brief 前フレームのワールド＞ビュー行列取得
			@author 葉迩倭
			@return ワールド＞ビュー行列

			@note
			描画オブジェクトの行列データを取得します。
		*/
		virtual const Math::Matrix &GetWorldViewPrevMatrix( void ) = 0;

		/**
			@brief ワールド＞ビュー＞プロジェクション行列取得
			@author 葉迩倭
			@return ワールド＞ビュー＞プロジェクション行列

			@note
			描画オブジェクトの行列データを取得します。
		*/
		virtual const Math::Matrix &GetWorldViewProjectionMatrix( void ) = 0;

		/**
			@brief 前フレームのワールド＞ビュー＞プロジェクション行列取得
			@author 葉迩倭
			@return ワールド＞ビュー＞プロジェクション行列

			@note
			描画オブジェクトの行列データを取得します。
		*/
		virtual const Math::Matrix &GetWorldViewProjectionPrevMatrix( void ) = 0;

		/**
			@brief ワールド逆行列取得
			@author 葉迩倭
			@return ワールド逆行列

			@note
			描画オブジェクトの行列データを取得します。
		*/
		virtual const Math::Matrix &GetWorldInverseMatrix( void ) = 0;

		/**
			@brief 前フレームのワールド逆行列取得
			@author 葉迩倭
			@return ワールド逆行列

			@note
			描画オブジェクトの行列データを取得します。
		*/
		virtual const Math::Matrix &GetWorldInverseMatrixPrev( void ) = 0;

		/**
			@brief ボーン用変換行列取得
			@author 葉迩倭
			@return ボーン変換行列

			@note
			描画オブジェクトのボーン用の行列データを取得します。
		*/
		virtual const Math::SMatrix4x4 *GetBoneMatrixArray( void ) = 0;

		/**
			@brief 前フレームのボーン用変換行列取得
			@author 葉迩倭
			@return ボーン変換行列

			@note
			描画オブジェクトのボーン用の行列データを取得します。
		*/
		virtual const Math::SMatrix4x4 *GetBoneMatrixArrayPrev( void ) = 0;

		/**
			@brief レンダリング用頂点データ設定
			@author 葉迩倭
			@param pRender		[in] 関連するIRenderインターフェイス

			@note
			レンダリングを行うための頂点ストリームの設定を行います。
		*/
		virtual void SetStreamSource( Renderer::IRender *pRender ) = 0;

		/**
			@brief 通常レンダリング
			@author 葉迩倭
			@param MaterialNo	[in] 描画するマテリアル番号
			@param pRender		[in] 関連するIRenderインターフェイス

			@note
			通常のレンダリング処理を行います。
		*/
		virtual Sint32 Rendering( Sint32 MaterialNo, Renderer::IRender *pRender ) = 0;

		/**
			@brief 速度マップ用縮退ポリゴン入りレンダリング
			@author 葉迩倭
			@param pRender	[in] 関連するIRenderインターフェイス

			@note
			速度マップ描画用の縮退ポリゴン入りのレンダリングを行います。
		*/
		virtual Sint32 Rendering_Velocity( Renderer::IRender *pRender ) = 0;

		/**
			@brief 頂点変換タイプを取得
			@author 葉迩倭
			@retval false	無い
			@retval true	有る

			@note
			描画オブジェクトの頂点変換タイプを取得します。
		*/
		virtual eTransformType GetTransformType( void ) = 0;

		/**
			@brief ソフトパーティクルの有無を取得
			@author 葉迩倭
			@retval false	ソフトパーティクルではない
			@retval true	ソフトパーティクル

			@note
			描画オブジェクトがソフトパーティクルかどうかを取得します。
		*/
		virtual Bool GetSoftBillboardEnable( void ) = 0;

		/**
			@brief 視差バンプマップの有無を取得
			@author 葉迩倭
			@retval false	無い
			@retval true	有る

			@note
			描画オブジェクトが視差バンプマップを持っているかを取得します。
		*/
		virtual Bool GetParallaxEnable( void ) = 0;

		/**
			@brief スペキュラー設定のの有無を取得
			@author 葉迩倭
			@retval false	無い
			@retval true	有る

			@note
			描画オブジェクトがスペキュラー設定のを持っているかを取得します。
		*/
		virtual Bool GetSpecularEnable( void ) = 0;

		/**
			@brief 環境マップ設定のの有無を取得
			@author 葉迩倭
			@retval false	無い
			@retval true	有る

			@note
			描画オブジェクトが環境マップ設定のを持っているかを取得します。
		*/
		virtual Bool GetEnvironmentEnable( void ) = 0;

		/**
			@brief リストにつながれている次の描画オブジェクトを取得
			@author 葉迩倭
			@return 描画オブジェクトインターフェイス

			@note
			リストにつながれている描画オブジェクトの自分の次の描画オブジェクトを取得します。
		*/
		virtual ICustomizedSceneRenderObject *GetNextObject( void ) = 0;
	};
}
}

