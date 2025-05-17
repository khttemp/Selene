#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Style.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief シーンプリミティブアクター用インターフェイス
		@author 葉迩倭

		シーン管理されたプリミティブアクターを扱う為のインターフェイスです。
	*/
	class IPrimitiveActor : public Math::Style
	{
	public:
		virtual ~IPrimitiveActor() {}

		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief 描画リクエスト
			@author 葉迩倭

			ISceneManagerに対してレンダリングリクエストを発行します。<BR>
			取得元のISceneManagerがBegin()/End()中でない場合この関数は失敗します。
		*/
		virtual void RenderingRequest( void ) = 0;

		/**
			@brief 座標変換初期化
			@author 葉迩倭

			アクターの座標変換を初期化します。<BR>
			アニメーションの情報などもこの関数内ですべて初期化されます。
		*/
		virtual void TransformReset( void )	 = 0;

		/**
			@brief 座標変換更新
			@author 葉迩倭

			アクターの座標変換を更新します。<BR>
			アニメーションの情報などもこの関数内ですべて更新されます。
		*/
		virtual void TransformUpdate( void ) = 0;

		/**
			@brief ボーン変換行列を設定
			@author 葉迩倭
			@param pMatrix	[in] ボーン行列の配列
			@param Count	[in] ボーン行列の数

			アクターに対してボーンの変換行列を設定します。<BR>
			ボーンデータをもつIPrimitive3Dに対してのみ有効です。
		*/
		virtual void SetBoneMatrixArray( Math::Matrix *pMatrix, Sint32 Count ) = 0;

		/**
			@brief シェーダーを設定
			@author 葉迩倭
			@param pShader	[in] シェーダーインターフェイス

			アクターに対して任意のシェーダーを設定します。
		*/
		virtual void SetShader( Renderer::Shader::IShader *pShader ) = 0;

		/**
			@brief マテリアルの拡散反射色設定
			@author 葉迩倭
			@param vColor			[in] 色

			メッシュ内のマテリアルの拡散反射色を設定します。
		*/
		virtual void SetMaterialColor( Math::Vector4D &vColor ) = 0;

		/**
			@brief マテリアルの自己発光色設定
			@author 葉迩倭
			@param vColor			[in] 色

			メッシュ内のマテリアルの自己発光色を設定します。
		*/
		virtual void SetEmissiveColor( Math::Vector4D &vColor )										= 0;

		/**
			@brief マテリアルの鏡面反射色設定
			@author 葉迩倭
			@param vColor			[in] 色

			メッシュ内のマテリアルの鏡面反射色を設定します。
		*/
		virtual void SetSpecularColor( Math::Vector4D &vColor )										= 0;

		/**
			@brief マテリアルの鏡面反射の強さ設定
			@author 葉迩倭
			@param fParam			[in] 強さ

			メッシュ内のマテリアルの鏡面反射の強さを設定します。
		*/
		virtual void SetSpecularRefractive( Float fParam )									= 0;

		/**
			@brief マテリアルの鏡面反射の荒さ設定
			@author 葉迩倭
			@param fParam			[in] 荒さ

			メッシュ内のマテリアルの鏡面反射の荒さを設定します。
		*/
		virtual void SetSpecularRoughly( Float fParam )									= 0;
	};
}
}

