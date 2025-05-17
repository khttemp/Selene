#pragma once


/**
	@file
	@brief シーン管理系クラス
	@author 葉迩倭
*/


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
		@brief シーン管理用インターフェイス
		@author 葉迩倭

		シーン管理を行うためのインターフェイスです。
	*/
	class ISceneManager : public IInterface
	{
	protected:
		virtual ~ISceneManager() {}

	public:
		/**
			@brief シーンアクター取得
			@author 葉迩倭
			@param pObject			[in] アクターに関連付ける描画インターフェイス
			@param InstanceCount	[in] インスタンス数
			@return	IInstanceModelActorインターフェイス

			@note
			ISceneManagerでレンダリングを行うためのアクターを取得します。<BR>
			ジオメトリインスタンシングを行うための特殊なアクターで、<BR>
			このアクターからさらに個別のコントローラーを取得し、ワールド変換やボーンの設定を行います。<BR>
			<B>必ずInitParameterUpdateの後に実行してください。</B>
		*/
		virtual IInstanceModelActor *CreateActor( Renderer::Object::IModel *pObject, Sint32 InstanceCount ) = 0;

		/**
			@brief シーンアクター取得
			@author 葉迩倭
			@param pObject	[in] アクターに関連付ける描画インターフェイス
			@return	IModelActorインターフェイス

			ISceneManagerでレンダリングを行うためのアクターを取得します。<BR>
			ワールド変換やレンダリングの操作はIModelActorを経由して行います。<BR>
			<B>必ずInitParameterUpdateの後に実行してください。</B>
		*/
		virtual IModelActor *CreateActor( Renderer::Object::IModel *pObject ) = 0;

		/**
			@brief シーンアクター取得
			@author 葉迩倭
			@param pObject	[in] アクターに関連付ける描画インターフェイス
			@return	IMapActorインターフェイス

			ISceneManagerでレンダリングを行うためのアクターを取得します。<BR>
			ワールド変換やレンダリングの操作はIMapActorを経由して行います。<BR>
			<B>必ずInitParameterUpdateの後に実行してください。</B>
		*/

		virtual IMapActor *CreateActor( Renderer::Object::IMapModel *pObject ) = 0;

		/**
			@brief シーンアクター取得
			@author 葉迩倭
			@param pObject	[in] アクターに関連付ける描画インターフェイス
			@return	IPrimitiveActorインターフェイス

			ISceneManagerでレンダリングを行うためのアクターを取得します。<BR>
			ワールド変換やレンダリングの操作はIPrimitiveActorを経由して行います。<BR>
			<B>必ずInitParameterUpdateの後に実行してください。</B>
		*/
		virtual IPrimitiveActor *CreateActor( Renderer::Object::IPoint3D *pObject ) = 0;

		/**
			@brief シーンアクター取得
			@author 葉迩倭
			@param pObject	[in] アクターに関連付ける描画インターフェイス
			@return	IPrimitiveActorインターフェイス

			ISceneManagerでレンダリングを行うためのアクターを取得します。<BR>
			ワールド変換やレンダリングの操作はIPrimitiveActorを経由して行います。<BR>
			<B>必ずInitParameterUpdateの後に実行してください。</B>
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
			ワールド変換やレンダリングの操作はIPrimitiveActorを経由して行います。<BR>
			<B>必ずInitParameterUpdateの後に実行してください。</B>
		*/
		virtual IPrimitiveActor *CreateActor( Renderer::Object::IPrimitive3D *pObject, Bool IsLightmap = false, Bool IsNormalmap = false, Bool IsSpecularmap = false, Bool IsEnvironmentmap = false ) = 0;

		/**
			@brief シーンアクター取得
			@author 葉迩倭
			@param pObject	[in] アクターに関連付ける描画インターフェイス
			@return	ISpriteActorインターフェイス

			ISceneManagerでレンダリングを行うためのアクターを取得します。<BR>
			ワールド変換やレンダリングの操作はISpriteActorを経由して行います。<BR>
			<B>必ずInitParameterUpdateの後に実行してください。</B>
		*/
		virtual ISpriteActor *CreateActor( Renderer::Object::ISprite3D *pObject ) = 0;

		/**
			@brief シーンアクター取得
			@author 葉迩倭
			@param pObject	[in] アクターに関連付ける描画インターフェイス
			@return	IParticleActorインターフェイス

			ISceneManagerでレンダリングを行うためのアクターを取得します。<BR>
			ワールド変換やレンダリングの操作はIParticleActorを経由して行います。<BR>
			<B>必ずInitParameterUpdateの後に実行してください。</B>
		*/
		virtual IParticleActor *CreateActor( Renderer::Object::IFontSprite3D *pObject ) = 0;

		/**
			@brief シーンアクター取得
			@author 葉迩倭
			@param pObject	[in] アクターに関連付ける描画インターフェイス
			@return	IParticleActorインターフェイス

			ISceneManagerでレンダリングを行うためのアクターを取得します。<BR>
			ワールド変換やレンダリングの操作はIParticleActorを経由して行います。<BR>
			<B>必ずInitParameterUpdateの後に実行してください。</B>
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
			@brief シーンレンダリング
			@author 葉迩倭
			@param IsDrawBuffer	[in] 内部用バッファの表示

			シーンの管理で構築されたシーンをレンダリングします。<BR>
			この関数をコールした段階で内部で描画処理が開始されます。<BR>
			必ずIRender::Begin()～IRender::End()間で呼び出してください。
		*/
		virtual void Rendering( Bool IsDrawBuffer = false ) = 0;

		/**
			@brief アンビエントライト設定
			@author 葉迩倭
			@param vColorSky	[in] シーン内の天球の環境光の色
			@param vColorEarth	[in] シーン内の地表の環境光の色

			シーンの環境光を設定します。<BR>
			半球ライティングを行うために、天球と地表の色を設定します。<BR>
			この関数はBegin()-End()内で呼び出すと失敗します。
		*/
		virtual void SetLightParameter_Ambient( const Math::Vector3D &vColorSky, const Math::Vector3D &vColorEarth ) = 0;

		/**
			@brief ディレクションライト設定
			@author 葉迩倭
			@param vDirect	[in] シーン内の平行光源の方向
			@param vColor	[in] シーン内の平行光源の色

			シーンに大して１つだけ平行光源を割り当てることができます。<BR>
			太陽のように遥か遠方に存在し、オブジェクトの位置によって<BR>
			光の方向が変わらないようなライトに向いています。<BR>
			この関数はBegin()-End()内で呼び出すと失敗します。<BR>
			またシーンモードの影生成を指定している時はvDirectは無効です。<BR>
			方向に関してはSetParameter_Shadow()で指定した値が使用されます。
		*/
		virtual void SetLightParameter_Directional( const Math::Vector3D &vDirect, const Math::Vector3D &vColor ) = 0;

		/**
			@brief ポイントライト追加
			@author 葉迩倭
			@param vPosition	[in] シーン内の点光源の位置
			@param vColor		[in] シーン内の点光源の色
			@param fDistance	[in] シーン内の点光源の影響距離

			シーンに対して点光源を追加します<BR>
			最大で32個のライトを設定でき、そのうち最もオブジェクトに近い<BR>
			4つのライトがオブジェクトに適用されます。<BR>
			この関数はBegin()-End()内で呼び出すと失敗します。
		*/
		virtual void SetLightParameter_AddPoint( const Math::Vector3D &vPosition, const Math::Vector3D &vColor, Float fDistance ) = 0;

		/**
			@brief レンダリングリクエスト数取得
			@author 葉迩倭
			@return レンダリングリクエスト数

			シーンにリクエストレンダリング数を取得します。
		*/
		virtual Sint32 GetResult_RenderingRequestActorCount( void ) = 0;

		/**
			@brief レンダリング数取得
			@author 葉迩倭
			@return レンダリング数

			シーンで実行されたレンダリング数を取得します。<BR>
			2Pass系の処理等もカウントされるので、<BR>
			リクエスト数以上の値になることもあります。
		*/
		virtual Sint32 GetResult_RenderingActorCount( void ) = 0;

		/**
			@brief シーンの構築にかかった時間を取得
			@author 葉迩倭
			@return シーンの構築にかかった時間（１フレームに対する％）

			１フレームあたりのシーン構築にかかった時間を％で取得します。
		*/
		virtual Sint32 GetResult_BackgroundThreadTime( void ) = 0;

		/**
			@brief シーンの描画にかかった時間を取得
			@author 葉迩倭
			@return シーンの描画にかかった時間（１フレームに対する％）

			１フレームあたりのシーン描画にかかった時間を％で取得します。
		*/
		virtual Sint32 GetResult_RenderingTme( void ) = 0;

		/**
			@brief モーションブラーレベルの設定
			@author 葉迩倭
			@param Level		[in] 使用するレベル

			モーションブラー処理のレベルを設定します。<BR>
			MOTION_BLUR_FULL指定の場合はモデルデータが閉じていて法線を保持している必要があります。
		*/
		virtual void SetActorParameter_MotionBlur( eSceneMotionBlurQuarity MotionBlurQuarity ) = 0;

		/**
			@brief 影の生成オプションのON/OFF
			@author 葉迩倭
			@param Type		[in] 影処理の方法
			@param Priority	[in] 影のプライオリティ
			@param fRadius	[in] 丸影の場合の大きさ

			シーンに適用される影処理が「SHADOW_TYPE_PROJECTION_*」か「SHADOW_TYPE_SOFT_PROJECTION_*」の時に<BR>
			レンダリングするモデルが影を落とすかどうかを設定します。<BR>
			影を落とすモデルには他のモデルの影が落ちず、影を落とさないモデルには他のモデルの影が落ちます。
		*/
		virtual void SetActorParameter_ProjectionShadow( eProjectionShadowType Type, eProjectionShadowPriority Priority, Float fRadius = 0.0f ) = 0;

		/**
			@brief シーン全体の明るさの設定
			@author 葉迩倭
			@param vBrightness	[in] 色

			シーンにライトマップを基準とした明るさを設定します。<BR>
			1.0fを指定することでAmaryllis上で設定したパラメーターそのままの明るさになり、<BR>
			それ以上で明るく、それ以下で暗くすることが出来ます。
		*/
		virtual void SetParameter_SceneBrightness( const Math::Vector3D &vBrightness ) = 0;

		/**
			@brief 線形フォグ情報設定
			@author 葉迩倭
			@param vColor	[in] フォグの色
			@param fNear	[in] フォグ開始点
			@param fFar		[in] フォグ終了点

			シーンに適用される線形フォグのパラメーターを設定します。<BR>
			この関数はBegin()-End()内で呼び出すと失敗します。
		*/
		virtual void SetParameter_Fog( Math::Vector3D &vColor, Float fNear, Float fFar ) = 0;

		/**
			@brief 被写界深度用のフォーカス位置を設定します。
			@author 葉迩倭

			@param fForcusZ	[in] フォーカスのＺ（カメラ基準）
			@param fPower	[in] 被写界深度強度

			被写界深度のフォーカス位置を設定します。
		*/
		virtual void SetParameter_DepthOfField( Float fForcusZ, Float fPower ) = 0;

		/**
			@brief ソフトパーティクル用スケール値
			@author 葉迩倭

			@param fSoftParticleScale	[in] ソフトパーティクルのアルファ値用のスケール

			ソフトパーティクル時の深度値の差異からアルファを算出するときのスケール値です。<BR>
			この値が大きいほどアルファの境界がシャープになります。
		*/
		virtual void SetParameter_SoftParticleScale( Float fSoftParticleScale ) = 0;

		/**
			@brief HDRエフェクト設定
			@author 葉迩倭
			@param HdrEffect	[in] HDRエフェクトの種類
			@param fHDRPower	[in] HDRの倍率
			@param fHDRBoundary	[in] HDRとして扱う閾値（1.0が白）

			シーンの描画時のHDRエフェクトの設定をします。
		*/
		virtual void SetParameter_HighDynamicRange( Float fHDRPower, Float fHDRBoundary ) = 0;

		/**
			@brief トゥーン用パラメーター設定
			@author 葉迩倭
			@param vHatchingColor	[in] ハッチング用の斜線の色
			@param fToonPower		[in] トゥーンマップ用の影部分の暗さ（0.0～1.0)

			トゥーンレンダリング用のパラメーターを設定します。
		*/
		virtual void SetParameter_Toon( Math::Vector3D &vHatchingColor, Float fToonPower ) = 0;

		/**
			@brief トゥーン用エッジ検出パラメーター設定
			@author 葉迩倭
			@param fEdgeNormalPower	[in] 法線エッジの検出パラメーター
			@param fEdgeDepthPower	[in] 深度エッジの検出パラメーター
			@param IsToonBold		[in] 輪郭線を太くするか否か

			トゥーン用のエッジ検出用のパラメーターを設定します。<BR>
			いずれのパラメーターも大きいほど境界線が引かれる範囲が増えます。
		*/
		virtual void SetParameter_ToonEdge( Float fEdgeNormalPower, Float fEdgeDepthPower, Bool IsToonBold ) = 0;

		/**
			@brief シャドウ用カメラ設定
			@author 葉迩倭
			@param vPosition	[in] カメラ位置
			@param vTarget		[in] カメラ注視点
			@param fSize		[in] レンダリングサイズ
			@param fNear		[in] 近クリップ面
			@param fFar			[in] 遠クリップ面
			@param fBias		[in] シャドウマップ用深度バイアス
			@param fPower		[in] 影の部分の明るさ(0.0から1.0まで、1.0の時影は完全なアンビエントになる）

			シャドウ用のカメラデータを設定します。
		*/
		virtual void SetParameter_Shadow( Math::Vector3D &vPosition, Math::Vector3D &vTarget, Float fSize, Float fNear, Float fFar, Float fBias, Float fPower ) = 0;

		/**
			@brief レンダリングターゲットの矩形を設定
			@author 葉迩倭
			@param Dst		[in] レンダリング矩形

			シーンのレンダリングターゲットの矩形を指定します。<BR>
			最終的に表示される位置に関係します。
		*/
		virtual void SetParameter_RenderRect( Math::Rect2DF &Dst ) = 0;

		/**
			@brief 背景塗りつぶし色設定
			@author 葉迩倭
			@param ClearColor	[in] バッファクリア色
			@param IsClear		[in] クリア有無

			シーンの描画時の背景の塗りつぶし色を設定します。
		*/
		virtual void SetParameter_BGColor( Math::Vector4D &ClearColor, Bool IsClear = true ) = 0;

		/**
			@brief 背景塗りつぶし色設定
			@author 葉迩倭
			@param ClearColor	[in] バッファクリア色
			@param IsClear		[in] クリア有無

			シーンの描画時の背景の塗りつぶし色を設定します。
		*/
		virtual void SetParameter_BGColor( CColor ClearColor, Bool IsClear = true ) = 0;

		/**
			@brief 背景塗りつぶしテクスチャ設定
			@author 葉迩倭
			@param pTex		[in] テクスチャ

			シーンの描画時の背景のテクスチャを設定します。
		*/
		virtual void SetParameter_BGTexture( Renderer::ITexture *pTex ) = 0;

		/**
			@brief シーン情報を更新
			@author 葉迩倭

			シーンをこれまでの情報を元に更新します。<BR>
			必要な設定後にこの関数を呼び出さない限りIActorを生成することが出来ません。
		*/
		virtual Bool InitParameter_Update( void ) = 0;

		/**
			@brief レンダリングターゲットのサイズを設定
			@author 葉迩倭
			@param pTarget				[in] レンダリングターゲットのテクスチャ（NULLでバックバッファへ直接レンダリング）
			@param Size					[in] サイズ（pTargetが有効な場合はpTargetのサイズに自動設定されます）
			@param IsTextureSizePow2	[in] サイズを強制的に２の累乗にするかどうか

			シーンのレンダリングターゲットのサイズを指定します。<BR>
			レンダリング使われる各種バッファのサイズに関係します。<BR>
			<B>必ずInitParameterUpdateの前に実行してください。</B>
		*/
		virtual void InitParameter_RenderTargetData( Renderer::ITexture *pTarget, Math::Point2DI Size = Math::Point2DI(0,0), Bool IsTextureSizePow2 = false ) = 0;

		/**
			@brief シェーディング用パラメーターの初期化
			@author 葉迩倭
			@param ShadingType		[in] シェーディングの種類

			シーンで行うシェーディングの処理を初期化します。<BR>
			<B>必ずInitParameterUpdateの前に実行してください。</B>
		*/
		virtual void InitParameter_Shading( eSceneShadingType ShadingType ) = 0;

		/**
			@brief アンチエイリアス用パラメーターの初期化
			@author 葉迩倭
			@param AntiAliasType	[in] アンチエイリアスの種類
			@param fPower			[in] アンチエイリアスのかかり具合(0.0～1.0)

			シーンで行うアンチエイリアスの処理を初期化します。<BR>
			<B>必ずInitParameterUpdateの前に実行してください。</B>
		*/
		virtual void InitParameter_AntiAliasType( eSceneAntiAliasType AntiAliasType, Float fPower ) = 0;

		/**
			@brief 影用パラメーターの初期化
			@author 葉迩倭
			@param ShadowType			[in] 影の種類
			@param ShadowQuarity		[in] 影の品質
			@param IsSoftShadow			[in] ソフトシャドウを使うかどうか
			@param IsHardwareShadowmap	[in] ハードウェアシャドウマップを使うかどうか

			シーンで行う影の処理を初期化します。<BR>
			<B>必ずInitParameterUpdateの前に実行してください。</B>
		*/
		virtual void InitParameter_Shadow( eSceneShadowType ShadowType, eSceneShadowQuarity ShadowQuarity, Bool IsSoftShadow = false, Bool IsHardwareShadowmap = true ) = 0;

		/**
			@brief モーションブラー用パラメーターの初期化
			@author 葉迩倭
			@param MotionBlurType	[in] モーションブラーの種類

			シーンで行うモーションブラーの処理を初期化します。<BR>
			<B>必ずInitParameterUpdateの前に実行してください。</B>
		*/
		virtual void InitParameter_MotionBlur( eSceneMotionBlurType MotionBlurType ) = 0;

		/**
			@brief 被写界深度用パラメーターの初期化
			@author 葉迩倭
			@param DofType	[in] 被写界深度の種類

			シーンで行う被写界深度の処理を初期化します。<BR>
			<B>必ずInitParameterUpdateの前に実行してください。</B>
		*/
		virtual void InitParameter_DepthOfField( eSceneDepthOfFieldType DofType ) = 0;

		/**
			@brief フォグ用パラメーターの初期化
			@author 葉迩倭
			@param FogType		[in] フォグの種類
			@param FogEffect	[in] フォグのエフェクト

			シーンで行うフォグの処理を初期化します。<BR>
			<B>必ずInitParameterUpdateの前に実行してください。</B>
		*/
		virtual void InitParameter_Fog( eSceneFogType FogType, eSceneFogEffect FogEffect ) = 0;

		/**
			@brief HDRレンダリング用パラメーターの初期化
			@author 葉迩倭
			@param HdrType		[in] HDRレンダリングの種類
			@param HdrEffect	[in] HDRレンダリングのエフェクト

			シーンで行うHDRレンダリングの処理を初期化します。<BR>
			<B>必ずInitParameterUpdateの前に実行してください。</B>
		*/
		virtual void InitParameter_HighDynamicRange( eSceneHighDynamicRangeType HdrType, eSceneHighDynamicRangeEffect HdrEffect ) = 0;

		/**
			@brief スカイドームの生成
			@author 葉迩倭
			@param fRadius		[in] 半径
			@param TopColor		[in] 天球の頭頂部の色
			@param BottomColor	[in] 天球の地面部分の色
			@param pTexCloud	[in] 雲テクスチャ

			シーンに適用するスカイドームを生成します。<BR>
		*/
		virtual Bool SceneSkydoom_Create( Float fRadius, CColor TopColor, CColor BottomColor, Renderer::ITexture *pTexCloud ) = 0;

		/**
			@brief スカイドームのレンダリング
			@author 葉迩倭

			シーンに登録されているスカイドームのレンダリングをします。
		*/
		virtual void SceneSkydoom_Rendering( void ) = 0;

		/**
			@brief スカイドームの雲テクスチャの色を設定
			@author 葉迩倭
			@param Color		[in] 色

			シーンに適用するスカイドームの雲の色を設定します。
		*/
		virtual void SceneSkydoom_SetCloudColor( const CColor &Color ) = 0;

		/**
			@brief スカイドームの雲テクスチャの移動量オフセット
			@author 葉迩倭
			@param vOffset		[in] 移動量(1.0でテクスチャサイズ)

			シーンに適用するスカイドームの雲の流れを制御します。<BR>
			この関数で与えたオフセット分雲が移動します。
		*/
		virtual void SceneSkydoom_SetCloudOffset( const Math::Vector2D &vOffset ) = 0;

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
	};
}
}

