#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Style.h"
#include "Collision/Line3D.h"
#include "Collision/Box.h"
#include "Interface/Render/IRender.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief シーンモデルアクター用インターフェイス
		@author 葉迩倭

		シーン管理されたモデルアクターを扱う為のインターフェイスです。
	*/
	class IModelActor : public Math::Style
	{
	public:
		virtual ~IModelActor() {}

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
			@brief 座標変換初期化
			@author 葉迩倭

			アクターの座標変換を初期化します。<BR>
			アニメーションの情報などもこの関数内ですべて初期化されます。
		*/
		virtual void TransformReset( void ) = 0;

		/**
			@brief 座標変換更新
			@author 葉迩倭

			アクターの座標変換を更新します。<BR>
			アニメーションの情報などもこの関数内ですべて更新されます。<BR>
			処理的には　TransformUpdateCollisionOnly() と TransformUpdateActorOnly() を呼び出しています。
		*/
		virtual void TransformUpdate( void ) = 0;

		/**
			@brief 座標変換更新
			@author 葉迩倭

			アクターのコリジョンの座標変換を更新します。<BR>
			コリジョンに関係するデータがここで更新されます。
		*/
		virtual void TransformUpdateCollisionOnly( void ) = 0;

		/**
			@brief 座標変換更新
			@author 葉迩倭

			アクターの座標変換を更新します。<BR>
			描画用のアクターだけが更新されます。
		*/
		virtual void TransformUpdateActorOnly( void ) = 0;

		/**
			@brief モデルに対してアニメーションデータ数を取得
			@author 葉迩倭
			@return	アニメーション数

			アクターの所持するアニメーションの数を取得します。
		*/
		virtual Sint32 GetAnimationCount( void ) = 0;

		/**
			@brief アニメーションデータの最終時間を取得
			@author 葉迩倭
			@param AnimationNo		[in] 適用するアニメーション番号
			@return	アニメーションの最終時間

			アニメーションの最終フレームを取得します。
		*/
		virtual Float GetAnimationLastTime( Sint32 AnimationNo ) = 0;

		/**
			@brief モデルに対してアニメーションデータを更新
			@author 葉迩倭
			@param AnimationNo		[in] 適用するアニメーション番号
			@param fAnimationTime	[in] アニメーションの時間（単位は作成したツールによる）

			単一のアニメーションデータの更新をします。
		*/
		virtual void UpdateAnimation( Sint32 AnimationNo, Float fAnimationTime ) = 0;

		/**
			@brief モデルに対してアニメーションデータを更新
			@author 葉迩倭
			@param AnimationNo1		[in] 適用するアニメーション番号
			@param fAnimationTime1	[in] アニメーションの時間（単位は作成したツールによる）
			@param AnimationNo2		[in] 適用するアニメーション番号
			@param fAnimationTime2	[in] アニメーションの時間（単位は作成したツールによる）
			@param fWeight			[in] ブレンド割合（0.0fの時AnimationNo0、1.0の時AnimationNo1)

			２つのアニメーションをブレンドしてアニメーションデータを更新します。
		*/
		virtual void UpdateAnimation( Sint32 AnimationNo1, Float fAnimationTime1, Sint32 AnimationNo2, Float fAnimationTime2, Float fWeight ) = 0;

		/**
			@brief カリング処理に有無設定
			@author 葉迩倭
			@param IsEnable	[in] カリングの有無

			モデル内の各アクターに対してビューフラスタムカリングを行うかを設定します。<BR>
			ビューフラスタムカリングとはカメラの描画領域内にないアクターを描画に関する一連の処理から<BR>
			省くための処理で、行う事でCPU負荷は増えますが画面外に出るアクターに対しての描画負荷を軽減できます。
		*/
		virtual void SetCullTestEnable( Bool IsEnable ) = 0;

		/**
			@brief モデル内のフレーム数取得
			@author 葉迩倭
			@return	モデル内のフレームの数

			モデル内のフレームの数を取得します。<BR>
			スキンメッシュに関連付けられているフレームは<BR>
			扱い的にはボーンになります。
		*/
		virtual Sint32 GetFrameCount( void ) = 0;

		/**
			@brief モデル内のフレーム数取得
			@author 葉迩倭
			@return	モデル内のフレームの数

			モデル内のフレームの数を取得します。
		*/
		virtual Sint32 Frame_GetIndex( const char *pName ) = 0;

		/**
			@brief フレームの変換行列を取得
			@author 葉迩倭
			@param Index	[in] フレームの番号
			@return	フレームの変換行列

			フレームの変換行列を取得します。
		*/
		virtual Math::Matrix &Frame_GetTransformLocal( Sint32 Index ) = 0;

		/**
			@brief フレームの変換行列を取得
			@author 葉迩倭
			@param Index	[in] フレームの番号
			@return	フレームの変換行列

			フレームの変換行列を取得します。
		*/
		virtual Math::Matrix &Frame_GetTransformWorld( Sint32 Index ) = 0;

		/**
			@brief モデル内のメッシュ数取得
			@author 葉迩倭
			@return	モデル内のメッシュの数

			モデル内のメッシュの数を取得します。<BR>
			メッシュの数＝描画アクターの数になります。
		*/
		virtual Sint32 GetMeshCount( void ) = 0;

		/**
			@brief モデル内のメッシュ描画ON/OFF
			@author 葉迩倭
			@param Index		[in] メッシュ番号
			@param IsDrawEnable	[in] 描画するか否か

			モデル内のメッシュを描画するかどうかを設定します。
		*/
		virtual void GetMesh_DrawEnable( Sint32 Index, Bool IsDrawEnable ) = 0;

		/**
			@brief メッシュ内のマテリアル数取得
			@author 葉迩倭
			@param MeshIndex	[in] メッシュ番号
			@return	メッシュ内のマテリアル数

			メッシュ内のマテリアル数を取得します。
		*/
		virtual Sint32 GetMeshMaterialCount( Sint32 MeshIndex ) = 0;

		/**
			@brief マテリアルのシェーダー設定
			@author 葉迩倭
			@param MeshIndex		[in] メッシュ番号
			@param MaterialIndex	[in] マテリアル番号
			@param pShader			[in] シェーダー

			メッシュ内のマテリアルのシェーダーを設定します。
		*/
		virtual void MeshMaterial_SetShader( Sint32 MeshIndex, Sint32 MaterialIndex, Renderer::Shader::IShader *pShader ) = 0;

		/**
			@brief マテリアルの拡散反射色設定
			@author 葉迩倭
			@param MeshIndex		[in] メッシュ番号
			@param MaterialIndex	[in] マテリアル番号
			@param vColor			[in] 色

			メッシュ内のマテリアルの拡散反射色を設定します。
		*/
		virtual void MeshMaterial_SetMaterialColor( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector4D &vColor ) = 0;

		/**
			@brief マテリアルの自己発光色設定
			@author 葉迩倭
			@param MeshIndex		[in] メッシュ番号
			@param MaterialIndex	[in] マテリアル番号
			@param vColor			[in] 色

			メッシュ内のマテリアルの自己発光色を設定します。
		*/
		virtual void MeshMaterial_SetEmissiveColor( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector4D &vColor )										= 0;

		/**
			@brief マテリアルの鏡面反射色設定
			@author 葉迩倭
			@param MeshIndex		[in] メッシュ番号
			@param MaterialIndex	[in] マテリアル番号
			@param vColor			[in] 色

			メッシュ内のマテリアルの鏡面反射色を設定します。
		*/
		virtual void MeshMaterial_SetSpecularColor( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector4D &vColor )										= 0;

		/**
			@brief マテリアルの鏡面反射の強さ設定
			@author 葉迩倭
			@param MeshIndex		[in] メッシュ番号
			@param MaterialIndex	[in] マテリアル番号
			@param fParam			[in] 強さ

			メッシュ内のマテリアルの鏡面反射の強さを設定します。
		*/
		virtual void MeshMaterial_SetSpecularRefractive( Sint32 MeshIndex, Sint32 MaterialIndex, Float fParam )									= 0;

		/**
			@brief マテリアルの鏡面反射の荒さ設定
			@author 葉迩倭
			@param MeshIndex		[in] メッシュ番号
			@param MaterialIndex	[in] マテリアル番号
			@param fParam			[in] 荒さ

			メッシュ内のマテリアルの鏡面反射の荒さを設定します。
		*/
		virtual void MeshMaterial_SetSpecularRoughly( Sint32 MeshIndex, Sint32 MaterialIndex, Float fParam )									= 0;

		/**
			@brief マテリアルの描画タイプ設定
			@author 葉迩倭
			@param MeshIndex		[in] メッシュ番号
			@param MaterialIndex	[in] マテリアル番号
			@param Type				[in] 描画タイプ

			メッシュ内のマテリアルの描画タイプを設定します。
		*/
		virtual void MeshMaterial_SetDrawType( Sint32 MeshIndex, Sint32 MaterialIndex, eDrawType Type )											= 0;

		/**
			@brief マテリアルのテクスチャ設定
			@author 葉迩倭
			@param MeshIndex		[in] メッシュ番号
			@param MaterialIndex	[in] マテリアル番号
			@param pTexture			[in] テクスチャ

			メッシュ内のマテリアルのテクスチャを設定します。
		*/
		virtual void MeshMaterial_SetTexture( Sint32 MeshIndex, Sint32 MaterialIndex, Renderer::ITexture *pTexture )										= 0;

		/**
			@brief マテリアルのテクスチャUVのオフセット設定
			@author 葉迩倭
			@param MeshIndex		[in] メッシュ番号
			@param MaterialIndex	[in] マテリアル番号
			@param vOffset			[in] オフセット（0.0->1.0)

			メッシュ内のマテリアルのテクスチャUVのオフセットを設定します。
		*/
		virtual void MeshMaterial_SetTextureOffset( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector2D &vOffset )									= 0;

		/**
			@brief コリジョン生成
			@author 葉迩倭

			アクターに対してのコリジョン操作用のインターフェイスを生成します。<BR>
			これを行うとCollision_***()系の関数が有効になります。
		*/
		virtual void Collision_Create( void ) = 0;

		/**
			@brief コリジョン有無設定
			@author 葉迩倭
			@param Index	[in] フレーム番号
			@param IsEnable	[in] trueの時コリジョンON（デフォルトはON）

			指定番号のフレームのコリジョンをON/OFFします。
		*/
		virtual void Collision_SetEnable( Sint32 Index, Bool IsEnable ) = 0;

		/**
			@brief コリジョン有無設定
			@author 葉迩倭
			@param pName	[in] 名称
			@param IsEnable	[in] trueの時コリジョンON（デフォルトはON）

			指定名のフレームのコリジョンをON/OFFします。
		*/
		virtual void Collision_SetEnable( const char *pName, Bool IsEnable ) = 0;

		/**
			@brief コリジョンデータ描画
			@author 葉迩倭
			@param pLine	[in] 描画用ラインプリミティブインターフェイス

			当たり判定データをレンダリングするための関数です。
		*/
		virtual void Collision_Rendering( Renderer::Object::ILine3D *pLine ) = 0;

		/**
			@brief コリジョンの結果取得
			@author 葉迩倭
			@param FrameNo	[in,out] 衝突したフレーム番号格納先
			@param vPos		[in,out] 衝突した位置格納先

			当たり判定データを取得します。<BR>
			現時点では衝突した大まかな位置と衝突した<BR>
			フレーム番号しか取得することはできません。
		*/
		virtual void Collision_GetResult( Sint32 &FrameNo, Math::Vector3D &vPos ) = 0;

		/**
			@brief コリジョンチェック
			@author 葉迩倭
			@param pSrc	[in] チェックするIModelActor

			指定されたデータとの衝突検出を行います。<BR>
			衝突の結果はCollision_GetResult()で取得できます。
		*/
		virtual Bool Collision_Check( IModelActor *pSrc ) = 0;

		/**
			@brief コリジョンチェック
			@author 葉迩倭
			@param Src	[in] チェックするボックスデータ

			指定されたデータとの衝突検出を行います。<BR>
			衝突の結果はCollision_GetResult()で取得できます。
		*/
		virtual Bool Collision_Check( Collision::CBox &Src ) = 0;

		/**
			@brief コリジョンチェック
			@author 葉迩倭
			@param Src	[in] チェックするラインデータ

			指定されたデータとの衝突検出を行います。<BR>
			衝突の結果はCollision_GetResult()で取得できます。
		*/
		virtual Bool Collision_Check( Collision::CLine3D &Src ) = 0;

		/**
			@brief コリジョンチェック
			@author 葉迩倭
			@param Src	[in] チェックする点データ

			指定されたデータとの衝突検出を行います。<BR>
			衝突の結果はCollision_GetResult()で取得できます。
		*/
		virtual Bool Collision_Check( Math::Vector3D &Src ) = 0;

		/**
			@brief コリジョンチェック
			@author 葉迩倭
			@param Src			[in] チェックする点データ
			@param pSceneMgr	[in] レンダリングを行ったシーンのインターフェイス

			スクリーン座標との衝突検出を行います。<BR>
			衝突の結果はCollision_GetResult()で取得できます。
		*/
		virtual Bool Collision_CheckOnScreen( Math::Vector2D &Src, ISceneManager *pSceneMgr ) = 0;

		/**
			@brief 衝突判定
			@author 葉迩倭
			@param Ray			[in] 始点から終点を結ぶ線分
			@retval false	衝突しない
			@retval true	衝突する

			マップモデルが持つコリジョンデータに対して、
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

			マップモデルが持つコリジョンデータに対して、
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

			マップモデルが持つコリジョンデータに対して、
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

			マップモデルが持つコリジョンデータに対して、
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

			マップモデルが持つコリジョンデータに対して、
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

			マップモデルが持つコリジョンデータに対して、
			点がRayで示す移動をした場合のコリジョンを処理します。
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out, Collision::CBox &Box ) = 0;

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

