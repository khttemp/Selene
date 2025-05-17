#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include <windows.h>


//-----------------------------------------------------------------------------------
// WARNING
//-----------------------------------------------------------------------------------
#pragma inline_depth ( 255 )
#pragma inline_recursion ( on )

#pragma warning ( disable: 4100 )
#pragma warning ( disable: 4819 )
#pragma warning ( disable: 4201 )
#pragma warning ( disable: 4239 )
#pragma warning ( disable: 4995 )
#pragma warning ( disable: 4996 )
#pragma warning ( disable: 4324 )


//-----------------------------------------------------------------------------------
// LIBRARY
//-----------------------------------------------------------------------------------
#pragma comment( lib, "ole32.lib" )
#pragma comment( lib, "gdi32.lib" )
#pragma comment( lib, "user32.lib" )
#pragma comment( lib, "comdlg32.lib" )
#pragma comment( lib, "advapi32.lib" )


//-----------------------------------------------------------------------------------
// TYPEDEF
//-----------------------------------------------------------------------------------
typedef char					Sint8;					///< signed char 型の別定義
typedef short					Sint16;					///< signed short 型の別定義
typedef long					Sint32;					///< signed long 型の別定義
typedef long long				Sint64;					///< signed long 型の別定義
typedef unsigned char			Uint8;					///< unsigned char 型の別定義
typedef unsigned short			Uint16;					///< unsigned short 型の別定義
typedef unsigned long			Uint32;					///< unsigned long 型の別定義
typedef unsigned long long		Uint64;					///< unsigned long long 型の別定義
typedef float					Float;					///< float 型の別定義
typedef double					Double;					///< double 型の別定義
typedef long					Bool;					///< bool 型の別定義


//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
#define ef									else if															///< else if 簡略用マクロ

#define PI									(3.141592653589793238462643383279f)								///< π
#define PI2									(6.283185307179586476925286766559f)								///< 2π
#define REV(val)							(1.0f/toF(val))													///< 逆数算出マクロ

#define AXIS_RANGE_MAX						(4096)															///< ジョイスティックの軸の最大値

#define toF(val)							((Float)(val))													///< floatへのキャスト
#define toI(val)							((Sint32)(val))													///< intへのキャスト

#define MIN(N1,N2)							((N1 < N2) ? (N1) : (N2))										///< 最小値取得マクロ
#define MAX(N1,N2)							((N1 > N2) ? (N1) : (N2))										///< 最大値取得マクロ
#define SWAP(N1,N2)							{ N1 = N2 - N1; N2 -= N1; N1 += N2; }							///< 値交換マクロ

#define SAFE_ADDREF(val)					if ( (val) != NULL ) { (val)->AddRef(); }						///< COM安全AddRefマクロ
#define SAFE_RELEASE(val)					if ( (val) != NULL ) { (val)->Release(); (val) = NULL; }		///< COM安全Releaseマクロ
#define SAFE_DELETE(val)					if ( (val) != NULL ) { delete (val); (val) = NULL; }			///< newメモリ安全解放
#define SAFE_DELETE_ARRAY(val)				if ( (val) != NULL ) { delete [] (val); (val) = NULL; }			///< new[]メモリ安全解放

#define ANGLE_TABLE_BIT						(16)															///< サインテーブルのビット数
#define ANGLE_MAX							(1 << ANGLE_TABLE_BIT)											///< サインテーブルのサイズ
#define ANGLE_TABLE_MASK					(ANGLE_MAX - 1)													///< サインテーブルのアクセス用マスク
#define NORMALIZE_ANGLE(val)				((val) & ANGLE_TABLE_MASK)										///< 角度の正規化
#define DEG_TO_ANGLE(val)					toI(toF(val) * toF(ANGLE_MAX) / 360.0f)							///< 度数法から専用角度
#define ANGLE_TO_DEG(val)					((val) * 360 / ANGLE_MAX)										///< 度数法から専用角度
#define PI_TO_ANGLE(val)					toI(toF(val) * toF(ANGLE_MAX) / PI2)							///< 弧度法から専用角度
#define ANGLE_TO_PI(val)					(toF(val) * PI2 / toF(ANGLE_MAX))								///< 専用角度から弧度法

#define MemoryClear(PD,S)					::FillMemory((PD),(S),0x00)										///< メモリクリア
#define MemoryFill(PD,PS,S)					::FillMemory((PD),(S),(PS))										///< メモリ塗りつぶし
#define MemoryMove(PD,PS,S)					::MoveMemory((PD),(PS),(S))										///< メモリ移動
#define MemoryCopy(PD,PS,S)					::CopyMemory((PD),(PS),(S))										///< メモリコピー


//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
#ifdef LIB_SELENE
#	define SELENE_DLL_API
#else // LIB_SELENE
#	ifdef DLL_SELENE
#		define SELENE_DLL_API	__declspec(dllexport)
#	else // DLL_SELENE
#		define SELENE_DLL_API	__declspec(dllimport)
#	endif // DLL_SELENE
#endif // LIB_SELENE


//-----------------------------------------------------------------------------------
// ENUM
//-----------------------------------------------------------------------------------
/**
	@brief ライブラリ名前空間
*/
namespace Selene
{
	/**
		@brief 頂点定義
		@author 葉迩倭

		頂点定義クラスの作成時に指定するフラグです。<BR>
		なお VERTEX_ELEMENT_PRIMITIVE、VERTEX_ELEMENT_SPRITE、VERTEX_ELEMENT_3DBASE は<BR>
		独立しており排他です。
	*/
	enum eVertexElement
	{
		VERTEX_ELEMENT_PRIMITIVE	= 1 << 0,			///< 位置と色だけを含む最も単純な2D用頂点
		VERTEX_ELEMENT_SPRITE		= 1 << 1,			///< 位置と色とテクスチャUVを含む2D用頂点
		VERTEX_ELEMENT_3DBASE		= 1 << 2,			///< 位置と色を含むもっとも単純な3D頂点
		VERTEX_ELEMENT_3DTEXTURE	= 1 << 3,			///< テクスチャUVを含む基本的な3D用頂点
		VERTEX_ELEMENT_3DLIGHT		= 1 << 4,			///< ライティングに関する法線を含む3D頂点
		VERTEX_ELEMENT_3DBUMP		= 1 << 5,			///< バンプマップに関する接線を含む3D頂点
		VERTEX_ELEMENT_3DANIMATION	= 1 << 6,			///< スキニングに関するボーンのインデックス＆ウェイトを含む3D頂点
	};

	/**
		@brief IParticle用タイプ
		@author 葉迩倭
	*/
	enum eParticleType
	{
		PARTICLE_TYPE_NORMAL,				///< 通常パーティクル
		PARTICLE_TYPE_VOLUME,				///< 疑似ボリュームパーティクル
	};

	/**
		@brief フレームレート定義
		@author 葉迩倭
	*/
	enum eFrameRate
	{
		FRAME_RATE_60,					///< 1フレーム1/60秒
		FRAME_RATE_30,					///< 1フレーム1/30秒
		FRAME_RATE_20,					///< 1フレーム1/20秒
		FRAME_RATE_15,					///< 1フレーム1/15秒
	};

	/**
		@brief アダプタータイプ
		@author 葉迩倭
	*/
	enum eGraphicCardNo
	{
		GRAPHIC_CARD_NO1,									///< １番目に接続されたビデオカード
		GRAPHIC_CARD_NO2,									///< ２番目に接続されたビデオカード

		GRAPHIC_CARD_DEFAULT_NO		= GRAPHIC_CARD_NO1,		///< デフォルトのビデオカード
		GRAPHIC_CARD_NV_PERF_HUD	= 0xFFFFFFFF,			///< NVPerfHUD専用のビデオカード
	};

	/**
		@brief サーフェイスフォーマット定義
		@author 葉迩倭
	*/
	enum eSurfaceFormat
	{
		FORMAT_INVALID,						///< 無効

		FORMAT_TEXTURE_32BIT,				///< 32Bitテクスチャフォーマットに準拠
		FORMAT_TEXTURE_16BIT,				///< 16Bitテクスチャフォーマットに準拠
		FORMAT_TEXTURE_DXT,					///< DXT圧縮フォーマットテクスチャ

		FORMAT_TARGET_UCHAR4,				///< unsnged char x4 レンダリングターゲット
		FORMAT_TARGET_FLOAT1,				///< float x1 レンダリングターゲット
		FORMAT_TARGET_FLOAT2,				///< float x2 レンダリングターゲット
		FORMAT_TARGET_FLOAT4,				///< float x4 レンダリングターゲット
		FORMAT_TARGET_FLOAT4_ALPHA,			///< float x4 アルファ可能レンダリングターゲット

		FORMAT_DEPTHBUFFER_SURFACE,			///< 深度バッファ
		FORMAT_DEPTHBUFFER_TEXTURE,			///< 深度バッファ

		FORMAT_MAX,

		FORMAT_TARGET_32BIT		= FORMAT_TARGET_UCHAR4,
		FORMAT_TARGET_HDR		= FORMAT_TARGET_FLOAT4_ALPHA,
	};

	/**
		@brief テクスチャステージ定義
		@author 葉迩倭

		テクスチャステージに関しての定義です。<BR>
		3Dオブジェクトに関しては基本的にシェーダー内で<BR>
		UVを計算するようになっているので、<BR>
		頂点データとして保持するUVはカラーマップとライトマップだけです。
	*/
	enum eTextureStage
	{
		TEXTURE_STAGE_COLOR			= 0,	///< カラーマップ
		TEXTURE_STAGE_LIGHT,				///< ライトマップ
		TEXTURE_STAGE_ENVIRONMENT,			///< キューブ環境
		TEXTURE_STAGE_SPECULAR,				///< スペキュラマップ
		TEXTURE_STAGE_NORMAL,				///< バンプor視差マップ用法線マップ

		TEXTURE_STAGE_SHADOW,				///< シャドウマップ
		TEXTURE_STAGE_DEPTH,				///< 深度マップ

		TEXTURE_STAGE_TOON,					///< トゥーン用特殊マップ

		TEXTURE_STAGE_MAX,					///< テクスチャステージ数

		MATERIAL_TEXTURE_MAX = TEXTURE_STAGE_NORMAL + 1,
	};

	/**
		@brief 描画タイプ定義
		@author 葉迩倭

		各種描画タイプに関しての定義です。
	*/
	enum eDrawType
	{
		DRAW_TYPE_NORMAL,					///< 通常描画
		DRAW_TYPE_BLEND,					///< 半透明描画
		DRAW_TYPE_ADD,						///< 加算描画
		DRAW_TYPE_ADD_NOALPHA,				///< 加算描画（アルファ値無効）
		DRAW_TYPE_SUB,						///< 減算描画
		DRAW_TYPE_SUB_NOALPHA,				///< 減算描画（アルファ値無効）
		DRAW_TYPE_MULTIPLE,					///< 乗算描画
	};

	/**
		@brief カリングタイプ定義
		@author 葉迩倭

		ポリゴンの表裏に描画に関しての定義です。
	*/
	enum eCullType
	{
		CULL_FRONT,							///< 表の場合のみ描画
		CULL_BACK,							///< 裏の場合のみ描画
		CULL_NONE,							///< 裏表両面描画
	};

	/**
		@brief テクスチャフィルタタイプ定義
		@author 葉迩倭

		ポリゴンの表裏に描画に関しての定義です。
	*/
	enum eTextureFilterType
	{
		TEXTURE_FILTER_DISABLE,		///< フィルタリング無し
		TEXTURE_FILTER_2D,			///< バイリニアフィルタリング
		TEXTURE_FILTER_3D_LOW,		///< バイリニアフィルタリング
		TEXTURE_FILTER_3D_MIDDLE,	///< 異方性フィルタリング/低画質
		TEXTURE_FILTER_3D_HIGH,		///< 異方性フィルタリング/高画質
	};

	/**
		@brief ファイルシーク定義
		@author 葉迩倭
	*/
	enum eSeekFlag
	{
		SEEK_FILE_CURRENT,					///< カレント位置
		SEEK_FILE_START,					///< 先頭位置
		SEEK_FILE_END,						///< 終端位置
	};

	/**
		@brief 頂点変換タイプ
		@author 葉迩倭
	*/
	enum eTransformType
	{
		TRANSFORM_TYPE_MODEL,				///< モデル用頂点変換
		TRANSFORM_TYPE_BILLBOARD,			///< ビルボード用頂点変換
	};

	/**
		@brief バンプタイプ
		@author 葉迩倭
	*/
	enum eBumpType
	{
		BUMP_TYPE_NONE,						///< バンプ処理なし
		BUMP_TYPE_ENABLE,					///< バンプ処理あり
	};

	/**
		@brief スペキュラタイプ
		@author 葉迩倭
	*/
	enum eSpecularType
	{
		SPECULAR_TYPE_NONE,					///< スペキュラ処理なし
		SPECULAR_TYPE_ENABLE,				///< スペキュラ処理あり
	};

	/**
		@brief モーションブラーレベル
		@author 葉迩倭
	*/
	enum eSceneMotionBlurQuarity
	{
		MOTION_BLUR_LIGHT,						///< モデル引き延ばしを行わない軽量なブラー
		MOTION_BLUR_FULL,						///< モデル引き延ばしを行うブラー

		MOTION_BLUR_MAX
	};

	/**
		@brief 被写界深度タイプ
		@author 葉迩倭
	*/
	enum eSceneDepthOfFieldType
	{
		DOF_TYPE_DISABLE,						///< 被写界深度なし
		DOF_TYPE_ENABLE,						///< 被写界深度あり
	};

	/**
		@brief フォグタイプ
		@author 葉迩倭
	*/
	enum eSceneFogType
	{
		FOG_TYPE_DISABLE,						///< フォグなし
		FOG_TYPE_ENABLE,						///< フォグあり
	};

	/**
		@brief アンチエイリアスタイプ
		@author 葉迩倭
	*/
	enum eSceneAntiAliasType
	{
		AA_TYPE_DISABLE,						///< アンチエイリアスなし
		AA_TYPE_ENABLE,							///< アンチエイリアスあり
	};

	/**
		@brief フォグエフェクト
		@author 葉迩倭
	*/
	enum eSceneFogEffect
	{
		FOG_EFFECT_LINEAR,						///< 線形フォグ
//		FOG_EFFECT_SCATTERING,					///< スキャッタリング
	};

	/**
		@brief シェーディングタイプ
		@author 葉迩倭
	*/
	enum eSceneShadingType
	{
		SHADING_TYPE_NORMAL,					///< 通常のシェーディング
		SHADING_TYPE_TOON,						///< トゥーン風シェーディング
		SHADING_TYPE_HATCHING,					///< ハッチング風シェーディング
	};

	/**
		@brief シーン用モーションブラータイプ
		@author 葉迩倭
	*/
	enum eSceneMotionBlurType
	{
		MOTION_BLUR_TYPE_DISABLE,				///< なし
		MOTION_BLUR_TYPE_LOW,					///< クオリティ低：４サンプリング
		MOTION_BLUR_TYPE_HIGH,					///< クオリティ高：８サンプリング
	};

	/**
		@brief シーン用シャドウマップタイプ
		@author 葉迩倭
	*/
	enum eSceneShadowType
	{
		SHADOW_TYPE_DISABLE,				///< 影なし
		SHADOW_TYPE_PROJECTION,				///< プロジェクションシャドウ
		SHADOW_TYPE_SHADOWMAP,				///< シャドウマッピング
	};

	/**
		@brief シーン用シャドウクオリティタイプ
		@author 葉迩倭
	*/
	enum eSceneShadowQuarity
	{
		SHADOW_QUARITY_LOW,					///< 低解像度(512x512)
		SHADOW_QUARITY_MIDDLE,				///< 低解像度(1024x1024)
		SHADOW_QUARITY_HIGH,				///< 低解像度(2048x2048)
		SHADOW_QUARITY_BEST,				///< 低解像度(4096x4096)
	};

	/**
		@brief HDR処理
		@author 葉迩倭
	*/
	enum eSceneHighDynamicRangeType
	{
		HDR_TYPE_DISABLE,						///< HDR処理なし
		HDR_TYPE_ENABLE,						///< HDR処理あり
	};

	/**
		@brief HDRエフェクト
		@author 葉迩倭
	*/
	enum eSceneHighDynamicRangeEffect
	{
		HDR_EFFECT_BLOOM,						///< ブルーム処理
		HDR_EFFECT_CROSS,						///< クロスフィルタ
	};

	/**
		@brief 投影シャドウ用種類
		@author 葉迩倭
	*/
	enum eProjectionShadowType
	{
		PROJECTION_SHADOW_DISABLE,				///< 影を落とさず、影の影響もない
		PROJECTION_SHADOW_DROP_SIMPLE,			///< 丸影を落とし、影の影響は受けない
		PROJECTION_SHADOW_DROP_SHAPE,			///< モデルの形状の影を落とし、影の影響は受けない
	};

	/**
		@brief 投影シャドウ用プライオリティ
		@author 葉迩倭
	*/
	enum eProjectionShadowPriority
	{
		PROJECTION_SHADOW_PRIORITY_0,			///< 影を落とさない
		PROJECTION_SHADOW_PRIORITY_1,			///< PROJECTION_SHADOW_PRIORITY_0以下に影を落とす
		PROJECTION_SHADOW_PRIORITY_2,			///< PROJECTION_SHADOW_PRIORITY_1以下に影を落とす
		PROJECTION_SHADOW_PRIORITY_3,			///< PROJECTION_SHADOW_PRIORITY_2以下に影を落とす
		PROJECTION_SHADOW_PRIORITY_4,			///< PROJECTION_SHADOW_PRIORITY_3以下に影を落とす

		PROJECTION_SHADOW_PRIORITY_MAX,
	};

	/**
		@brief ボタン状態
		@author 葉迩倭
	*/
	enum eInputButtonState
	{
		BUTTON_STATE_FREE,					///< 押していない状態取得用
		BUTTON_STATE_HOLD,					///< 押し続けている状態取得用
		BUTTON_STATE_PUSH,					///< 押した瞬間取得用
		BUTTON_STATE_PULL,					///< 離した瞬間取得用

		BUTTON_STATE_MAX,
	};

	/**
		@brief 軸定義
		@author 葉迩倭
	*/
	enum eInputAxisType
	{
		AXIS_TYPE_01,						///< 1番目の軸
		AXIS_TYPE_02,						///< 2番目の軸
		AXIS_TYPE_03,						///< 3番目の軸
		AXIS_TYPE_04,						///< 4番目の軸

		AXIS_TYPE_MAX,
	};

	/**
		@brief ボタン種類
		@author 葉迩倭
	*/
	enum eInputButtonType
	{
		BUTTON_AXIS1_UP,					///< 上方向指定
		BUTTON_AXIS1_DOWN,					///< 下方向指定
		BUTTON_AXIS1_LEFT,					///< 左方向指定
		BUTTON_AXIS1_RIGHT,					///< 右方向指定

		BUTTON_AXIS2_UP,					///< 上方向指定
		BUTTON_AXIS2_DOWN,					///< 下方向指定
		BUTTON_AXIS2_LEFT,					///< 左方向指定
		BUTTON_AXIS2_RIGHT,					///< 右方向指定

		BUTTON_AXIS3_UP,					///< 上方向指定
		BUTTON_AXIS3_DOWN,					///< 下方向指定
		BUTTON_AXIS3_LEFT,					///< 左方向指定
		BUTTON_AXIS3_RIGHT,					///< 右方向指定

		BUTTON_AXIS4_UP,					///< 上方向指定
		BUTTON_AXIS4_DOWN,					///< 下方向指定
		BUTTON_AXIS4_LEFT,					///< 左方向指定
		BUTTON_AXIS4_RIGHT,					///< 右方向指定

		BUTTON_01,							///< ボタン1指定
		BUTTON_02,							///< ボタン2指定
		BUTTON_03,							///< ボタン3指定
		BUTTON_04,							///< ボタン4指定
		BUTTON_05,							///< ボタン5指定
		BUTTON_06,							///< ボタン6指定
		BUTTON_07,							///< ボタン7指定
		BUTTON_08,							///< ボタン8指定
		BUTTON_09,							///< ボタン9指定
		BUTTON_10,							///< ボタン10指定
		BUTTON_11,							///< ボタン11指定
		BUTTON_12,							///< ボタン12指定
		BUTTON_13,							///< ボタン13指定
		BUTTON_14,							///< ボタン14指定
		BUTTON_15,							///< ボタン15指定
		BUTTON_16,							///< ボタン16指定

		BUTTON_AXIS_MAX,
		BUTTON_MAX		= BUTTON_16 - BUTTON_01,
		AXIS_MAX		= BUTTON_AXIS4_RIGHT - BUTTON_AXIS1_UP,

		BUTTON_DISABLE,						///< 無効
	};

	/**
		@brief ジョイスティック軸方向定義
		@author 葉迩倭
	*/
	enum ePadAxisDirection
	{
		PAD_AXIS_X,							///< X軸
		PAD_AXIS_Y,							///< Y軸
		PAD_AXIS_Z,							///< Z軸

		PAD_AXIS_DIRECTION_MAX,
	};

	/**
		@brief ジョイスティック軸種類定義
		@author 葉迩倭
	*/
	enum ePadAxisType
	{
		PAD_AXIS_POSITION,
		PAD_AXIS_POSITION_ROTATE,
		PAD_AXIS_VELOCITY,
		PAD_AXIS_VELOCITY_ROTATE,
		PAD_AXIS_ACCEL,
		PAD_AXIS_ACCEL_ROTATE,
		PAD_AXIS_FORCE,
		PAD_AXIS_FORCE_ROTATE,
		PAD_AXIS_POV,

		PAD_AXIS_MAX,
	};

	/**
		@brief ジョイスティックスライダー定義
		@author 葉迩倭
	*/
	enum ePadSliderType
	{
		PAD_SLIDER_0,							///< 1番目のスライダー
		PAD_SLIDER_1,							///< 2番目のスライダー
		PAD_SLIDER_2,							///< 3番目のスライダー
		PAD_SLIDER_3,							///< 4番目のスライダー

		PAD_SLIDER_MAX,
	};

	/**
		@brief ジョイスティックボタン定義
		@author 葉迩倭
	*/
	enum ePadButtonType
	{
		PAD_BUTTON_01,
		PAD_BUTTON_02,
		PAD_BUTTON_03,
		PAD_BUTTON_04,
		PAD_BUTTON_05,
		PAD_BUTTON_06,
		PAD_BUTTON_07,
		PAD_BUTTON_08,
		PAD_BUTTON_09,
		PAD_BUTTON_10,
		PAD_BUTTON_11,
		PAD_BUTTON_12,
		PAD_BUTTON_13,
		PAD_BUTTON_14,
		PAD_BUTTON_15,
		PAD_BUTTON_16,

		PAD_BUTTON_MAX,
	};

	/**
		@brief 仮想キーコード
		@author 葉迩倭
	*/
	enum eVirtualKeyCode
	{
		SELENE_VK_ESCAPE          = 0x01,
		SELENE_VK_1               = 0x02,
		SELENE_VK_2               = 0x03,
		SELENE_VK_3               = 0x04,
		SELENE_VK_4               = 0x05,
		SELENE_VK_5               = 0x06,
		SELENE_VK_6               = 0x07,
		SELENE_VK_7               = 0x08,
		SELENE_VK_8               = 0x09,
		SELENE_VK_9               = 0x0A,
		SELENE_VK_0               = 0x0B,
		SELENE_VK_MINUS           = 0x0C,
		SELENE_VK_EQUALS          = 0x0D,
		SELENE_VK_BACK            = 0x0E,
		SELENE_VK_TAB             = 0x0F,
		SELENE_VK_Q               = 0x10,
		SELENE_VK_W               = 0x11,
		SELENE_VK_E               = 0x12,
		SELENE_VK_R               = 0x13,
		SELENE_VK_T               = 0x14,
		SELENE_VK_Y               = 0x15,
		SELENE_VK_U               = 0x16,
		SELENE_VK_I               = 0x17,
		SELENE_VK_O               = 0x18,
		SELENE_VK_P               = 0x19,
		SELENE_VK_LBRACKET        = 0x1A,
		SELENE_VK_RBRACKET        = 0x1B,
		SELENE_VK_RETURN          = 0x1C,
		SELENE_VK_LCONTROL        = 0x1D,
		SELENE_VK_A               = 0x1E,
		SELENE_VK_S               = 0x1F,
		SELENE_VK_D               = 0x20,
		SELENE_VK_F               = 0x21,
		SELENE_VK_G               = 0x22,
		SELENE_VK_H               = 0x23,
		SELENE_VK_J               = 0x24,
		SELENE_VK_K               = 0x25,
		SELENE_VK_L               = 0x26,
		SELENE_VK_SEMICOLON       = 0x27,
		SELENE_VK_APOSTROPHE      = 0x28,
		SELENE_VK_GRAVE           = 0x29,
		SELENE_VK_LSHIFT          = 0x2A,
		SELENE_VK_BACKSLASH       = 0x2B,
		SELENE_VK_Z               = 0x2C,
		SELENE_VK_X               = 0x2D,
		SELENE_VK_C               = 0x2E,
		SELENE_VK_V               = 0x2F,
		SELENE_VK_B               = 0x30,
		SELENE_VK_N               = 0x31,
		SELENE_VK_M               = 0x32,
		SELENE_VK_COMMA           = 0x33,
		SELENE_VK_PERIOD          = 0x34,
		SELENE_VK_SLASH           = 0x35,
		SELENE_VK_RSHIFT          = 0x36,
		SELENE_VK_MULTIPLY        = 0x37,
		SELENE_VK_LMENU           = 0x38,
		SELENE_VK_SPACE           = 0x39,
		SELENE_VK_CAPITAL         = 0x3A,
		SELENE_VK_F1              = 0x3B,
		SELENE_VK_F2              = 0x3C,
		SELENE_VK_F3              = 0x3D,
		SELENE_VK_F4              = 0x3E,
		SELENE_VK_F5              = 0x3F,
		SELENE_VK_F6              = 0x40,
		SELENE_VK_F7              = 0x41,
		SELENE_VK_F8              = 0x42,
		SELENE_VK_F9              = 0x43,
		SELENE_VK_F10             = 0x44,
		SELENE_VK_NUMLOCK         = 0x45,
		SELENE_VK_SCROLL          = 0x46,
		SELENE_VK_NUMPAD7         = 0x47,
		SELENE_VK_NUMPAD8         = 0x48,
		SELENE_VK_NUMPAD9         = 0x49,
		SELENE_VK_SUBTRACT        = 0x4A,
		SELENE_VK_NUMPAD4         = 0x4B,
		SELENE_VK_NUMPAD5         = 0x4C,
		SELENE_VK_NUMPAD6         = 0x4D,
		SELENE_VK_ADD             = 0x4E,
		SELENE_VK_NUMPAD1         = 0x4F,
		SELENE_VK_NUMPAD2         = 0x50,
		SELENE_VK_NUMPAD3         = 0x51,
		SELENE_VK_NUMPAD0         = 0x52,
		SELENE_VK_DECIMAL         = 0x53,
		SELENE_VK_OEM_102         = 0x56,
		SELENE_VK_F11             = 0x57,
		SELENE_VK_F12             = 0x58,
		SELENE_VK_KANA            = 0x70,
		SELENE_VK_ABNT_C1         = 0x73,
		SELENE_VK_CONVERT         = 0x79,
		SELENE_VK_NOCONVERT       = 0x7B,
		SELENE_VK_YEN             = 0x7D,
		SELENE_VK_ABNT_C2         = 0x7E,
		SELENE_VK_NUMPADEQUALS    = 0x8D,
		SELENE_VK_PREVTRACK       = 0x90,
		SELENE_VK_NUMPADENTER     = 0x9C,
		SELENE_VK_RCONTROL        = 0x9D,
		SELENE_VK_NUMPADCOMMA     = 0xB3,
		SELENE_VK_DIVIDE          = 0xB5,
		SELENE_VK_SYSRQ           = 0xB7,
		SELENE_VK_RMENU           = 0xB8,
		SELENE_VK_PAUSE           = 0xC5,
		SELENE_VK_HOME            = 0xC7,
		SELENE_VK_UP              = 0xC8,
		SELENE_VK_PRIOR           = 0xC9,
		SELENE_VK_LEFT            = 0xCB,
		SELENE_VK_RIGHT           = 0xCD,
		SELENE_VK_END             = 0xCF,
		SELENE_VK_DOWN            = 0xD0,
		SELENE_VK_NEXT            = 0xD1,
		SELENE_VK_INSERT          = 0xD2,
		SELENE_VK_DELETE          = 0xD3,
		SELENE_VK_LWIN            = 0xDB,
		SELENE_VK_RWIN            = 0xDC,

		SELENE_VK_DISABLE         = 0x00
	};

	/**
		@brief マウスボタン状態定義
		@author 葉迩倭
	*/
	enum eMouseState
	{
		MOUSE_FREE,							///< マウスボタンは押されていない
		MOUSE_PULL,							///< マウスボタンは離された
		MOUSE_PUSH,							///< マウスボタンは押された
		MOUSE_HOLD,							///< マウスボタンは押されつづけている
	};

	/**
		@brief 物理シミュレーション用接触点定義
		@author 葉迩倭
	*/
	enum eContactMode
	{
		ContactMu2			= 0x001,
		ContactFDir1		= 0x002,
		ContactBounce		= 0x004,
		ContactSoftERP		= 0x008,
		ContactSoftCFM		= 0x010,
		ContactMotion1		= 0x020,
		ContactMotion2		= 0x040,
		ContactSlip1		= 0x080,
		ContactSlip2		= 0x100,

		ContactApprox0		= 0x0000,
		ContactApprox1_1	= 0x1000,
		ContactApprox1_2	= 0x2000,
		ContactApprox1		= 0x3000,
	};

	/**
		@brief 描画系
	*/
	namespace Renderer
	{
		/**
			@brief シェーダー系
		*/
		namespace Shader
		{
		}

		/**
			@brief 描画オブジェクト系
		*/
		namespace Object
		{
		}
	}

	/**
		@brief ファイル系
	*/
	namespace File
	{
	}

	namespace Scene
	{
	}

	/**
		@brief 入力デバイス系
	*/
	namespace Peripheral
	{
	}

	/**
		@brief サウンド系
	*/
	namespace Sound
	{
	}

	/**
		@brief システム系
	*/
	namespace System
	{
	}

	/**
		@brief 算術演算系
	*/
	namespace Math
	{
	}

	/**
		@brief 数値補間系
	*/
	namespace Interpolation
	{
	}

	/**
		@brief コリジョン系
	*/
	namespace Collision
	{
	}

	/**
		@brief 物理シミュレーション系
	*/
	namespace Dynamics
	{
		class IRigidModel;
		class IRigidBody;
		class IContactPoint;
		class ISimulationWorld;
	}

	/**
		@brief スレッド系
	*/
	namespace Thread
	{
	}

	/**
		@brief シーン系
	*/
	namespace Scene
	{
	}

	/**
		@brief ファイル系
	*/
	namespace File
	{
	}

	/**
		@brief ファイバー系
	*/
	namespace Fiber
	{
	}

	/**
		@brief ネットワーク系
	*/
	namespace Network
	{
		class INetworkManager;
		class ISocketTCP;
		class IServerTCP;
		class IServerClientTCP;
	}
}


//-----------------------------------------------------------------------------------
// INTERFACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class ICore;
	class IGraphicCard;

	namespace Renderer
	{
		class IRender;
		class ITexture;
		class ITexture;

		namespace Shader
		{
			class IShader;
		}

		namespace Object
		{
			class IPoint2D;
			class ILine2D;
			class IPrimitive2D;
			class ISprite2D;
			class IFontSprite2D;
			class IPoint3D;
			class ILine3D;
			class IPrimitive3D;
			class ISprite3D;
			class IFontSprite3D;
			class IParticle;
			class IModel;
			class IMapModel;
		}
	}

	namespace Fiber
	{
		class IFiber;
		class IFiberController;
	};

	namespace Peripheral
	{
		class IMouse;
		class IKeyboard;
		class IJoystick;
		class IInputController;
	}

	namespace File
	{
		class IFileManager;
		class IResourceFile;
	}

	namespace Sound
	{
		class ISound;
		class IStreamSound;
	}

	namespace Scene
	{
		class IPrimitiveActor;
		class ISpriteActor;
		class IParticleActor;
		class IModelActor;
		class IMapActor;
		class IInstanceModelActor;
		class IInstanceModelController;
		class ICamera;
		class ISceneManager;
		class ICustomizedSceneManager;
		class ICustomizedSceneRenderMaterial;
		class ICustomizedSceneRenderObject;
	}

	namespace Dynamics
	{
		class ISimulationWorld;
		class IRigidBody;
		class IRigidModel;
		class IContactPoint;
	}

	namespace Math
	{
		class Vector2D;
		class Vector3D;
		class Vector4D;
		class Quaternion;
		class Matrix;
		class Style;
	}
}


//-----------------------------------------------------------------------------------
// INLINE
//-----------------------------------------------------------------------------------
namespace Selene
{
	inline void Float2Int( Sint32 &iVal, Float fVal )
	{
		*((Uint32*)&iVal) = *((Uint32*)&fVal);
	}

	inline void Int2Float( Float &fVal, Sint32 iVal )
	{
		*((Uint32*)&fVal) = *((Uint32*)&iVal);
	}

	inline Float FastSqrt( Float fVal )
	{
		Float fRetVal;
		Sint32 iVal;

		Float2Int( iVal, fVal );

		iVal &= 0x7FFFFFFF;
		iVal -= 0x3F800000;
		iVal >>= 1;
		iVal += 0x3F800000;

		Int2Float( fRetVal, iVal );

		return fRetVal;
	}

	inline float InvSqrt( float fVal )
	{
		Sint32 iVal;
		Float fValHalf = fVal * 0.5f;

		Float2Int( iVal, fVal );

		iVal = 0x5F375A86 - (iVal >> 1);

		Int2Float( fVal, iVal );

		return fVal * (1.5f - fValHalf * fVal * fVal);
	}

	inline Float Abs( Float fVal )
	{
		Sint32 iVal;

		Float2Int( iVal, fVal );

		iVal &= 0x7FFFFFFF;

		Int2Float( fVal, iVal );

		return fVal;
	}

	inline Sint32 Abs( Sint32 iVal )
	{
		return iVal & 0x7FFFFFFF;
	}

	inline Bool Is2ByteChara( char Src )
	{
		unsigned char Code = *((unsigned char*)&Src);

		if ( Code <= 0x80 ) return false;	// 制御コード＆文字
		if ( Code <= 0x9F ) return true;
		if ( Code <= 0xDF ) return false;	// 半角カナ
		if ( Code <= 0xFE ) return true;

		return false;
	}

}

