#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief カスタムシーンマテリアルインターフェイス
		@author 葉迩倭

		@note
		カスタムシーンのアクターのマテリアルを扱うためのインターフェイスです。
	*/
	class ICustomizedSceneRenderMaterial
	{
	protected:
		virtual ~ICustomizedSceneRenderMaterial() {}

	public:
		/**
			@brief シェーダーインターフェイス取得
			@author 葉迩倭
			@return シェーダーインターフェイス

			@note
			マテリアルに関連付けられているシェーダーを取得します。
		*/
		virtual Renderer::Shader::IShader *GetShader( void ) = 0;

		/**
			@brief テクスチャインターフェイス取得
			@author 葉迩倭
			@return テクスチャインターフェイス

			@note
			マテリアルに関連付けられているテクスチャを取得します。
		*/
		virtual Renderer::ITexture *GetTexture( Sint32 Stage ) = 0;

		/**
			@brief 拡散反射色取得
			@author 葉迩倭
			@return 拡散反射色

			@note
			マテリアルに関連付けられている拡散反射色を取得します。
		*/
		virtual Math::Vector4D &GetDiffuseColor( void ) = 0;

		/**
			@brief 自己発光色取得
			@author 葉迩倭
			@return 自己発光色

			@note
			マテリアルに関連付けられている自己発光色を取得します。
		*/
		virtual Math::Vector4D &GetEmissiveColor( void ) = 0;

		/**
			@brief 鏡面反射色取得
			@author 葉迩倭
			@return 鏡面反射色

			@note
			マテリアルに関連付けられている鏡面反射色を取得します。
		*/
		virtual Math::Vector4D &GetSpecularColor( void ) = 0;

		/**
			@brief テクスチャUVオフセット取得
			@author 葉迩倭
			@return テクスチャUVオフセット

			@note
			マテリアルに関連付けられているテクスチャUVオフセットを取得します。
		*/
		virtual Math::Vector2D &GetTextureOffset( void ) = 0;

		/**
			@brief 鏡面反射反射率取得
			@author 葉迩倭
			@return 鏡面反射反射率

			@note
			マテリアルに関連付けられている鏡面反射反射率を取得します。
		*/
		virtual Float GetSpecularRefractive( void ) = 0;

		/**
			@brief 鏡面反射荒さ取得
			@author 葉迩倭
			@return 鏡面反射荒さ

			@note
			マテリアルに関連付けられている鏡面反射荒さを取得します。
		*/
		virtual Float GetSpecularRoughly( void ) = 0;

		/**
			@brief 視差マップ深度取得
			@author 葉迩倭
			@return 視差マップ深度

			@note
			マテリアルに関連付けられている視差マップ深度を取得します。
		*/
		virtual Float GetParallaxDepth( void ) = 0;

		/**
			@brief 鏡面反射タイプ取得
			@author 葉迩倭
			@return 鏡面反射タイプ

			@note
			マテリアルに関連付けられている鏡面反射タイプを取得します。
		*/
		virtual eSpecularType GetSpecularType( void ) = 0;

		/**
			@brief 鏡面反射反射率取得
			@author 葉迩倭
			@return 鏡面反射反射率

			@note
			マテリアルに関連付けられている鏡面反射反射率を取得します。
		*/
		virtual eBumpType GetBumpType( void ) = 0;

		/**
			@brief 鏡面反射反射率取得
			@author 葉迩倭
			@return 鏡面反射反射率

			@note
			マテリアルに関連付けられている鏡面反射反射率を取得します。
		*/
		virtual eDrawType GetDrawType( void ) = 0;

		/**
			@brief 鏡面反射反射率取得
			@author 葉迩倭
			@return 鏡面反射反射率

			@note
			マテリアルに関連付けられている鏡面反射反射率を取得します。
		*/
		virtual eCullType GetCullType( void ) = 0;

		/**
			@brief 鏡面反射反射率取得
			@author 葉迩倭
			@return 鏡面反射反射率

			@note
			マテリアルに関連付けられている鏡面反射反射率を取得します。
		*/
		virtual Sint32 GetAlphaBoundary( void ) = 0;

		/**
			@brief 鏡面反射反射率取得
			@author 葉迩倭
			@return 鏡面反射反射率

			@note
			マテリアルに関連付けられている鏡面反射反射率を取得します。
		*/
		virtual Bool GetAlphaTestEnable( void ) = 0;

		/**
			@brief 鏡面反射反射率取得
			@author 葉迩倭
			@return 鏡面反射反射率

			@note
			マテリアルに関連付けられている鏡面反射反射率を取得します。
		*/
		virtual Bool GetZTestEnable( void ) = 0;

		/**
			@brief 鏡面反射反射率取得
			@author 葉迩倭
			@return 鏡面反射反射率

			@note
			マテリアルに関連付けられている鏡面反射反射率を取得します。
		*/
		virtual Bool GetZWriteEnable( void ) = 0;

		/**
			@brief 鏡面反射反射率取得
			@author 葉迩倭
			@return 鏡面反射反射率

			@note
			マテリアルに関連付けられている鏡面反射反射率を取得します。
		*/
		virtual Bool GetLightEnable( void ) = 0;
	};
}
}

