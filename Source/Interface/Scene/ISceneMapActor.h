#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/Map/IMapModel.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief シーンアクター用インターフェイス
		@author 葉迩倭

		シーン管理されたオブジェクトを扱う為のインターフェイスです。
	*/
	class IMapActor
	{
	public:
		virtual ~IMapActor() {}

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
			@brief カリング用バウンディングレンダリング
			@author 葉迩倭
			@param pLine	[in] ラインプリミティブインターフェイス

			バウンディングボックスを指定したラインデータに対して追加します。
		*/
		virtual void RenderingBounding( Renderer::Object::ILine3D *pLine ) = 0;

		/**
			@brief セルの全体数取得
			@author 葉迩倭
			@return セルの全体数

			マップ内のセルの数を取得します。
		*/
		virtual Sint32 GetCellCount( void ) = 0;

		/**
			@brief セルの描画数取得
			@author 葉迩倭
			@return セルの描画数

			マップ内の描画されたセルの数を取得します。
		*/
		virtual Sint32 GetRenderingCellCount( void ) = 0;

		/**
			@brief 衝突判定
			@author 葉迩倭
			@param Ray			[in] 始点から終点を結ぶ線分
			@retval false	衝突しない
			@retval true	衝突する

			マップモデルが持つコリジョンデータに対して、<BR>
			点がRayで示す移動をした場合のコリジョンを処理します。
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray ) = 0;

		/**
			@brief 衝突判定
			@author 葉迩倭
			@param Ray			[in] 始点から終点を結ぶ線分
			@param Box			[out] 衝突したメッシュのOBB
			@retval false	衝突しない
			@retval true	衝突する

			マップモデルが持つコリジョンデータに対して、<BR>
			点がRayで示す移動をした場合のコリジョンを処理します。
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box ) = 0;

		/**
			@brief 衝突判定
			@author 葉迩倭
			@param Ray			[in] 始点から終点を結ぶ線分
			@param Out			[out] 衝突結果
			@retval false	衝突しない
			@retval true	衝突する

			マップモデルが持つコリジョンデータに対して、<BR>
			点がRayで示す移動をした場合のコリジョンを処理します。
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out ) = 0;

		/**
			@brief 衝突判定
			@author 葉迩倭
			@param Ray			[in] 始点から終点を結ぶ線分
			@param Out			[out] 衝突結果
			@param Box			[out] 衝突したメッシュのOBB
			@retval false	衝突しない
			@retval true	衝突する

			マップモデルが持つコリジョンデータに対して、<BR>
			点がRayで示す移動をした場合のコリジョンを処理します。
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out, Collision::CBox &Box ) = 0;

		/**
			@brief 衝突判定
			@author 葉迩倭
			@param Ray			[in] 始点から終点を結ぶ線分
			@param Out			[out] 衝突結果
			@retval false	衝突しない
			@retval true	衝突する

			マップモデルが持つコリジョンデータに対して、<BR>
			点がRayで示す移動をした場合のコリジョンを処理します。
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out ) = 0;

		/**
			@brief 衝突判定
			@author 葉迩倭
			@param Ray			[in] 始点から終点を結ぶ線分
			@param Out			[out] 衝突結果
			@param Box			[out] 衝突したメッシュのOBB
			@retval false	衝突しない
			@retval true	衝突する

			マップモデルが持つコリジョンデータに対して、<BR>
			点がRayで示す移動をした場合のコリジョンを処理します。
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out, Collision::CBox &Box ) = 0;

		/**
			@brief 衝突判定
			@author 葉迩倭
			@param Ray			[in] 始点から終点を結ぶ線分
			@param fRadius		[in] 衝突半径
			@retval false	衝突しない
			@retval true	衝突する

			マップモデルが持つコリジョンデータに対して、<BR>
			点がRayで示す移動をした場合のコリジョンを処理します。
		*/
//		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius ) = 0;

		/**
			@brief 衝突判定
			@author 葉迩倭
			@param Ray			[in] 始点から終点を結ぶ線分
			@param fRadius		[in] 衝突半径
			@param Box			[out] 衝突したメッシュのOBB
			@retval false	衝突しない
			@retval true	衝突する

			マップモデルが持つコリジョンデータに対して、<BR>
			点がRayで示す移動をした場合のコリジョンを処理します。
		*/
//		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Collision::CBox &Box ) = 0;

		/**
			@brief 衝突判定
			@author 葉迩倭
			@param Ray			[in] 始点から終点を結ぶ線分
			@param fRadius		[in] 衝突半径
			@param Out			[out] 衝突結果
			@retval false	衝突しない
			@retval true	衝突する

			マップモデルが持つコリジョンデータに対して、<BR>
			点がRayで示す移動をした場合のコリジョンを処理します。
		*/
//		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphere &Out ) = 0;

		/**
			@brief 衝突判定
			@author 葉迩倭
			@param Ray			[in] 始点から終点を結ぶ線分
			@param fRadius		[in] 衝突半径
			@param Out			[out] 衝突結果
			@param Box			[out] 衝突したメッシュのOBB
			@retval false	衝突しない
			@retval true	衝突する

			マップモデルが持つコリジョンデータに対して、<BR>
			点がRayで示す移動をした場合のコリジョンを処理します。
		*/
//		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphere &Out, Collision::CBox &Box ) = 0;

		/**
			@brief 衝突判定
			@author 葉迩倭
			@param Ray			[in] 始点から終点を結ぶ線分
			@param fRadius		[in] 衝突半径
			@param Out			[out] 衝突結果
			@retval false	衝突しない
			@retval true	衝突する

			マップモデルが持つコリジョンデータに対して、<BR>
			点がRayで示す移動をした場合のコリジョンを処理します。
		*/
//		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphereExtend &Out ) = 0;

		/**
			@brief 衝突判定
			@author 葉迩倭
			@param Ray			[in] 始点から終点を結ぶ線分
			@param fRadius		[in] 衝突半径
			@param Out			[out] 衝突結果
			@param Box			[out] 衝突したメッシュのOBB
			@retval false	衝突しない
			@retval true	衝突する

			マップモデルが持つコリジョンデータに対して、<BR>
			点がRayで示す移動をした場合のコリジョンを処理します。
		*/
//		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphereExtend &Out, Collision::CBox &Box ) = 0;

		/**
			@brief コリジョンモデル表示
			@author 葉迩倭
			@param pLine		[in] ラインプリミティブインターフェイス

			マップモデルが持つコリジョンデータをRenderer::Object::ILine3Dを使って<BR>
			可視出来るように描画します。
		*/
		virtual void CreateCollisionDrawPrimitive( Renderer::Object::ILine3D *pLine ) = 0;
	};
}
}

