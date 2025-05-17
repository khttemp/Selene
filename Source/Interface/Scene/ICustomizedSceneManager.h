#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/IRender.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief カスタムシーン管理用インターフェイス
		@author 葉迩倭

		@note
		カスタムシーン管理を行うためのインターフェイスです。
	*/
	class ICustomizedSceneManager : public IInterface
	{
	protected:
		virtual ~ICustomizedSceneManager() {}

	public:
		/**
			@brief 終了待機
			@author 葉迩倭

			ISceneManagerでレンダリング処理の完了を完全に待機します。<BR>
			Begin()-End()以降並列でデータの構築処理が行われますので、<BR>
			シーン、あるいはシーンで利用しているリソースを解放する前は<BR>
			この関数でシーンの構築処理の終了を待って下さい。<BR>
			なおアプリケーションの終了時(ICore::Run()=false)時には内部で全てのシーンの<BR>
			Abort()が自動的に呼ばれます。
		*/
		virtual void Abort( void ) = 0;

		/**
			@brief シーンアクター取得
			@author 葉迩倭
			@param pObject			[in] アクターに関連付ける描画インターフェイス
			@param InstanceCount	[in] インスタンス数
			@return	IInstanceModelActorインターフェイス

			ISceneManagerでレンダリングを行うためのアクターを取得します。<BR>
			ジオメトリインスタンシングを行うための特殊なアクターで、<BR>
			このアクターからさらに個別のコントローラーを取得し、ワールド変換やボーンの設定を行います。
		*/
		virtual IInstanceModelActor *CreateActor( Renderer::Object::IModel *pObject, Sint32 InstanceCount ) = 0;

		/**
			@brief シーンアクター取得
			@author 葉迩倭
			@param pObject	[in] アクターに関連付ける描画インターフェイス
			@return	IModelActorインターフェイス

			ISceneManagerでレンダリングを行うためのアクターを取得します。<BR>
			ワールド変換やレンダリングの操作はIModelActorを経由して行います。
		*/
		virtual IModelActor *CreateActor( Renderer::Object::IModel *pObject ) = 0;

		/**
			@brief シーンアクター取得
			@author 葉迩倭
			@param pObject	[in] アクターに関連付ける描画インターフェイス
			@return	IMapActorインターフェイス

			ISceneManagerでレンダリングを行うためのアクターを取得します。<BR>
			ワールド変換やレンダリングの操作はIMapActorを経由して行います。
		*/

		virtual IMapActor *CreateActor( Renderer::Object::IMapModel *pObject ) = 0;

		/**
			@brief シーンアクター取得
			@author 葉迩倭
			@param pObject	[in] アクターに関連付ける描画インターフェイス
			@return	IPrimitiveActorインターフェイス

			ISceneManagerでレンダリングを行うためのアクターを取得します。<BR>
			ワールド変換やレンダリングの操作はIPrimitiveActorを経由して行います。
		*/
		virtual IPrimitiveActor *CreateActor( Renderer::Object::IPoint3D *pObject ) = 0;

		/**
			@brief シーンアクター取得
			@author 葉迩倭
			@param pObject	[in] アクターに関連付ける描画インターフェイス
			@return	IPrimitiveActorインターフェイス

			ISceneManagerでレンダリングを行うためのアクターを取得します。<BR>
			ワールド変換やレンダリングの操作はIPrimitiveActorを経由して行います。
		*/
		virtual IPrimitiveActor *CreateActor( Renderer::Object::ILine3D *pObject ) = 0;

		/**
			@brief シーンアクター取得
			@author 葉迩倭
			@param pObject	[in] アクターに関連付ける描画インターフェイス
			@param IsLightmap		[in] 
			@pamra IsNormalmap		[in] 
			@param IsSpecularmap	[in] 
			@param IsEnvironmentmap	[in] 
			@return	IPrimitiveActorインターフェイス

			ISceneManagerでレンダリングを行うためのアクターを取得します。<BR>
			ワールド変換やレンダリングの操作はIPrimitiveActorを経由して行います。
		*/
		virtual IPrimitiveActor *CreateActor( Renderer::Object::IPrimitive3D *pObject, Bool IsLightmap = false, Bool IsNormalmap = false, Bool IsSpecularmap = false, Bool IsEnvironmentmap = false ) = 0;

		/**
			@brief シーンアクター取得
			@author 葉迩倭
			@param pObject	[in] アクターに関連付ける描画インターフェイス
			@return	ISpriteActorインターフェイス

			ISceneManagerでレンダリングを行うためのアクターを取得します。<BR>
			ワールド変換やレンダリングの操作はISpriteActorを経由して行います。
		*/
		virtual ISpriteActor *CreateActor( Renderer::Object::ISprite3D *pObject ) = 0;

		/**
			@brief シーンアクター取得
			@author 葉迩倭
			@param pObject	[in] アクターに関連付ける描画インターフェイス
			@return	IParticleActorインターフェイス

			ISceneManagerでレンダリングを行うためのアクターを取得します。<BR>
			ワールド変換やレンダリングの操作はIParticleActorを経由して行います。
		*/
		virtual IParticleActor *CreateActor( Renderer::Object::IFontSprite3D *pObject ) = 0;

		/**
			@brief シーンアクター取得
			@author 葉迩倭
			@param pObject	[in] アクターに関連付ける描画インターフェイス
			@return	IParticleActorインターフェイス

			ISceneManagerでレンダリングを行うためのアクターを取得します。<BR>
			ワールド変換やレンダリングの操作はIParticleActorを経由して行います。
		*/
		virtual IParticleActor *CreateActor( Renderer::Object::IParticle *pObject ) = 0;

		/**
			@brief シーンカメラ取得
			@author 葉迩倭
			@return カメラ

			シーンに関連付けられたカメラを取得します。
		*/
		virtual ICamera *GetCamera( void ) = 0;

		/**
			@brief シーン初期化
			@author 葉迩倭

			シーンのライトやフォグなどのデータをリセットします。<BR>
			この関数はBegin()-End()内で呼び出すと失敗します。
		*/
		virtual void Reset( void ) = 0;

		/**
			@brief シーン開始
			@author 葉迩倭
			@param IsSort	[in] シーン内のオブジェクトをソートするかどうか

			シーン管理を開始します。<BR>
			この時点でカメラのデータが確定しますので<BR>
			この関数を呼び出したあとのカメラの更新は全て無効です。
		*/
		virtual void Begin( Bool IsSort ) = 0;

		/**
			@brief シーン終了
			@author 葉迩倭

			シーンの管理を完了します。
		*/
		virtual void End( void ) = 0;

		/**
			@brief シーンレンダリング開始
			@author 葉迩倭
			@retval false	シーンにレンダリングするオブジェクトがない
			@retval	true	シーンにレンダリングするオブジェクトがある

			@note
			シーンのレンダリングを開始する事を宣言します。<BR>
			この関数がtrueを返した場合は必ずRedneringEnd()をコールして下さい。
		*/
		virtual Bool RenderingStart( void ) = 0;

		/**
			@brief シーンレンダリング終了
			@author 葉迩倭

			@note
			シーンのレンダリングを終了する事を宣言します。
		*/
		virtual void RenderingExit( void ) = 0;

		/**
			@brief スクリーン座標に変換
			@author 葉迩倭
			@param vPosition	[in] ワールド座標
			@return スクリーン座標

			ワールド空間の座標をスクリーン座標に変換します。
		*/
		virtual Math::Vector3D TransformToScreen( const Math::Vector3D &vPosition ) = 0;

		/**
			@brief スクリーン座標から変換
			@author 葉迩倭
			@param vPosition	[in] スクリーン座標
			@return ワールド座標

			スクリーン座標をワールド空間の座標に変換します。
		*/
		virtual Math::Vector3D TransformFromScreen( const Math::Vector3D &vPosition ) = 0;

		/**
			@brief アクターオブジェクトのレイヤー数取得
			@author 葉迩倭
			@return アクターオブジェクトのレイヤー数

			@note
			レンダリングするアクターオブジェクトのレイヤー数を取得します。<BR>
			レイヤー数自体は3で固定されており、内部的に下のように固定されています<BR>
			0=未使用<BR>
			1=不透明モデル<BR>
			2=半透明モデル
		*/
		virtual Sint32 GetRenderObjectLayerCount( void ) = 0;

		/**
			@brief アクターオブジェクトの取得
			@author 葉迩倭
			@param Layer	[in] オブジェクトレイヤー
			@return アクターオブジェクト

			@note
			レンダリングするアクターオブジェクトを取得します。
		*/
		virtual ICustomizedSceneRenderObject *GetRenderObject( Sint32 Layer ) = 0;
	};
}
}

