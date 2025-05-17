#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Color.h"
#include "Math/Math.h"
#include "Math/Vector2D.h"
#include "Math/Vector3D.h"
#include "Math/Vector4D.h"
#include "Collision/Box.h"
#include "Interface/Render/3D/IParticle.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	/**
		@brief コリジョン結果保持用
		@author 葉迩倭

		コリジョンの結果を保持するための構造体です。
	*/
	struct SCollisionResult
	{
		Uint32 Attribute;				///< 属性
		Math::Vector3D vHitPosition;	///< 衝突点
		Math::Vector3D vNormal;			///< 衝突面の法線
		Math::Vector3D vTriangle[3];	///< 衝突三角形をなす頂点
		CColor Color[3];				///< 衝突三角形をなす頂点の色
	};

	/**
		@brief コリジョン結果保持用
		@author 葉迩倭

		コリジョンの結果を保持するための構造体です。
	*/
	struct SCollisionResultExtend
	{
		Uint32 Attribute;					///< 属性（Almeria上でのマテリアルの番号）
		Math::Vector3D vHitPosition;		///< 衝突点
		Math::Vector3D vNormal;				///< 衝突面の法線
		Math::Vector3D vTriangle[3];		///< 衝突三角形をなす頂点
		Math::Vector3D vRefrectDirection;	///< 反射後の方向
		Math::Vector3D vRefrectPosition;	///< 反射後の位置
		Math::Vector3D vSlidePosition;		///< 面上をスライドした場合の位置
		CColor Color[3];					///< 衝突三角形をなす頂点の色
	};

	/**
		@brief コリジョン結果保持用
		@author 葉迩倭

		コリジョンの結果を保持するための構造体です。
	*/
	struct SCollisionResultSphere
	{
		Math::Vector3D vHitPosition;	///< 衝突点
		Math::Vector3D vNormal;			///< 衝突面の法線
	};

	/**
		@brief コリジョン結果保持用
		@author 葉迩倭

		コリジョンの結果を保持するための構造体です。
	*/
	struct SCollisionResultSphereExtend
	{
		Math::Vector3D vHitPosition;		///< 衝突点
		Math::Vector3D vNormal;				///< 衝突面の法線
		Math::Vector3D vRefrectDirection;	///< 反射後の方向
		Math::Vector3D vRefrectPosition;	///< 反射後の位置
		Math::Vector3D vSlidePosition;		///< 面上をスライドした場合の位置
	};

	/**
		@brief 2D描画用頂点
		@author 葉迩倭

		2D描画用の基本頂点データです。<BR>
		主にIPoint2D/ILine2Dクラスで使用します。<BR>
		VERTEX_ELEMENT_PRIMITIVEフラグを指定して作成した<BR>
		頂点定義ではこの構造体を使います。
	*/
	struct SVertex2D
	{
		Math::Vector4D Pos;		///< 位置
		CColor Col;				///< 頂点色
	};

	/**
		@brief 2D描画用頂点
		@author 葉迩倭

		2D描画用のテクスチャUV付き頂点データです。<BR>
		主にIPrimitive2D/ISprite2D/IFontSprite2Dクラスで使用します。<BR>
		VERTEX_ELEMENT_SPRITEフラグを指定して作成した<BR>
		頂点定義ではこの構造体を使います。
	*/
	struct SVertex2DTex
	{
		Math::Vector4D Pos;		///< 位置
		CColor Col;				///< 頂点色
		Math::Vector2D Tex[2];	///< テクスチャUV
	};

	/**
		@brief 3D描画用頂点
		@author 葉迩倭

		3D描画用の基本頂点データです。<BR>
		VERTEX_ELEMENT_BASEフラグを指定して作成した<BR>
		頂点定義に対して定義されます。
	*/
	struct SVertex3DBase
	{
		Math::Vector3D Pos;		///< 位置
		CColor Col;				///< 頂点色
	};

	/**
		@brief 3D描画用頂点
		@author 葉迩倭

		3D描画用のテクスチャUV用頂点データです。<BR>
		VERTEX_ELEMENT_3DTEXTUREフラグを指定して作成した<BR>
		頂点定義に対して定義されます。
	*/
	struct SVertex3DTexture
	{
		Math::Vector2D TexColor;		///< テクスチャUV
		Math::Vector2D TexLight;		///< テクスチャUV
	};

	/**
		@brief 3D描画用頂点
		@author 葉迩倭

		3D描画用のライティング用頂点データです。<BR>
		VERTEX_ELEMENT_3DLIGHTフラグを指定して作成した<BR>
		頂点定義に対して定義されます。
	*/
	struct SVertex3DLight
	{
		Math::Vector3D Norm;		///< 法線
	};

	/**
		@brief 3D描画用頂点
		@author 葉迩倭

		3D描画用のバンプマッピング用頂点データです。<BR>
		VERTEX_ELEMENT_3DBUMPフラグを指定して作成した<BR>
		頂点定義に対して定義されます。
	*/
	struct SVertex3DBump
	{
		Math::Vector3D Tangent;	///< 接線
	};

	/**
		@brief 3D描画用頂点
		@author 葉迩倭

		3D描画用のスキニング用頂点データです。<BR>
		VERTEX_ELEMENT_3DANIMATIONフラグを指定して作成した<BR>
		頂点定義に対して定義されます。
		１つの頂点につき２つのボーンの計算が行われます。
	*/
	struct SVertex3DAnimation
	{
		Float Weight;		///< ウェイト（１番目のウェイトだけを指定、２番目はシェーダー内で1.0-Weightで算出）
		Uint8 Index[4];		///< ボーンインデックス
	};

	/**
		@brief ラインプリミティブ用頂点データ
		@author 葉迩倭
	*/
	struct SLineVertex2D
	{
		SVertex2D v1;
		SVertex2D v2;
	};

	/**
		@brief プリミティブ用頂点データ
		@author 葉迩倭
	*/
	struct SPrimitiveVertex2D
	{
		SVertex2DTex v1;
		SVertex2DTex v2;
		SVertex2DTex v3;
	};

	/**
		@brief 3Dプリミティブ基本データ
		@author 葉迩倭

		ILine3Dで描画を行う際に使用する頂点データ。
	*/
	struct SLineVertex3D
	{
		SVertex3DBase v1;			///< 位置・頂点色
		SVertex3DBase v2;			///< 位置・頂点色
	};

	/**
		@brief テクスチャ生成用コンフィグ
		@author 葉迩倭

		テクスチャ生成時に参照される<BR>
		作成用パラメーターが定義されるクラスです。
	*/
	class CTextureConfig
	{
	private:
		eSurfaceFormat m_Format;	///< サーフェイスフォーマット
		CColor m_KeyColor;			///< カラーキーの色
		Bool m_IsMipmap;			///< ミップマップ
		Bool m_IsHalfSize;			///< 半分サイズ

	public:
		/**
			@brief コンストラクタ
		*/
		CTextureConfig()
			: m_Format		( FORMAT_TEXTURE_32BIT )
			, m_KeyColor	( 0x00000000 )
			, m_IsMipmap	( false )
			, m_IsHalfSize	( false )
		{
		}

		/**
			@brief デストラクタ
		*/
		~CTextureConfig()
		{
		}

		/**
			@brief カラーキー（透明色）設定
			@author 葉迩倭
			@param Col	[in] カラーキー（透明色）に使う色<BR>0x00000000の時カラーキー（透明色）OFF

			テクスチャを読み込んだ際に指定した色のアルファを0にし、<BR>
			カラーキー処理を行ったようにそのピクセルを描画<BR>
			されないようにします。
		*/
		void SetColorKey( CColor Col )
		{
			m_KeyColor = Col;
		}

		/**
			@brief サーフェイスフォーマット設定
			@author 葉迩倭
			@param Fmt	[in] サーフェイスフォーマット

			テクスチャ読み込み時のサーフェイスフォーマットを設定します。<BR>
			無効なフォーマットを指定した場合、作成は失敗します。
		*/
		void SetFormat( eSurfaceFormat Fmt )
		{
			m_Format = Fmt;
		}

		/**
			@brief ミップマップ有無設定
			@author 葉迩倭
			@param IsEnable	[in] ミップマップ有無

			テクスチャ読み込み時のミップマップの有無を設定します。
		*/
		void SetMipmapEnable( Bool IsEnable ) 
		{
			m_IsMipmap = IsEnable;
		}

		/**
			@brief 1/2サイズテクスチャ有無設定
			@author 葉迩倭
			@param IsEnable	[in] 1/2サイズテクスチャ有無

			テクスチャ読み込み時の1/2サイズテクスチャの有無を設定します。<BR>
			このフラグは純粋にテクスチャの使用量を抑える時に使います。
		*/
		void SetHalfSizeEnable( Bool IsEnable ) 
		{
			m_IsHalfSize = IsEnable;
		}

		/**
			@brief カラーキーを取得
			@author 葉迩倭
			@retval	0		カラーキー処理を行わない
			@retval	0以外	その色をカラーキーとする
		*/
		CColor GetColorKey( void )
		{
			return m_KeyColor;
		}

		/**
			@brief サーフェイスフォーマットを取得します
			@author 葉迩倭
			@return サーフェイスフォーマット
		*/
		eSurfaceFormat GetFormat( void )
		{
			return m_Format;
		}

		/**
			@brief ミップマップの有無を取得します
			@author 葉迩倭
			@return ミップマップの有無
		*/
		Bool IsMipmap( void )
		{
			return m_IsMipmap;
		}

		/**
			@brief 1/2サイズテクスチャの有無を取得します
			@author 葉迩倭
			@return 1/2サイズテクスチャの有無
		*/
		Bool IsHalfSize( void )
		{
			return m_IsHalfSize;
		}
	};

	/**
		@brief レンダラーインターフェイス
		@author 葉迩倭

		画面に対する全ての描画処理を管理します。<BR>
		描画用の各種クラスも全てこのクラスから取得します<BR>
		またこのインターフェイスは１つのIDeviceインターフェイスに対して１つしか作成されません。
	*/
	class IRender
	{
	public:
		virtual ~IRender() {}

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
			@brief シェーダーバージョンチェック
			@author 葉迩倭
			@retval false	未対応
			@retval true	対応

			シェーダーモデル2.0に対応しているかどうかを調べます。
		*/
		virtual Bool IsSupportedPS20( void ) = 0;

		/**
			@brief シェーダーバージョンチェック
			@author 葉迩倭
			@retval false	未対応
			@retval true	対応

			シェーダーモデル3.0に対応しているかどうかを調べます。
		*/
		virtual Bool IsSupportedPS30( void ) = 0;

		/**
			@brief ピクセルシェーダーの命令数チェック
			@author 葉迩倭
			@parma Count	[in] 命令数
			@retval false	未対応
			@retval true	対応

			指定した命令数に対応している稼動を調べます。
		*/
		virtual Bool IsPixelShaderInstructionSupport( Sint32 Count ) = 0;

		/**
			@brief ピクセルシェーダーの命令数チェック
			@author 葉迩倭
			@retval マルチレンダリングターゲット数

			マルチレンダリングターゲットの対応数を取得します。
		*/
		virtual Sint32 GetMRTs( void ) = 0;

		/**
			@brief レンダリングターゲットクリア
			@author 葉迩倭
			@param Color	[in] クリアに使う色
			@retval false	失敗
			@retval true	成功

			設定されたレンダリングターゲットを指定された色でクリアーします。
		*/
		virtual Bool Clear( CColor Color = 0x00000000 ) = 0;

		/**
			@brief 深度ステンシルバッファクリア
			@author 葉迩倭
			@retval false	失敗
			@retval true	成功

			設定された深度ステンシルバッファをクリアします。<BR>
			深度ステンシルバッファが存在しない場合失敗します。
		*/
		virtual Bool ClearDepthStencil( void ) = 0;

		/**
			@brief 描画領域シザリング
			@author 葉迩倭
			@param pRect		[in] 描画領域(NULLで解除)

			指定した描画領域内にしかレンダリングされないようになります。<BR>
			ビューポートには影響を与えません。
		*/
		virtual void SetScissorRect( const Math::Rect2DI *pRect ) = 0;

		/**
			@brief デバイスリセット時コールバック関数登録
			@author 葉迩倭
			@param pCallback	[in] コールバック関数

			デバイスロスト時にコールバックされる関数を設定します。<BR>
			通常の用途では使用する必要はありません。<BR>
			なんらかの理由で直接デバイスを操作する時にのみ使用してください。
		*/
		virtual void SetCallbackDeviceReset( void (*pCallback)( void ) ) = 0;

		/**
			@brief 利用可能なVRAM残量を取得
			@author 葉迩倭
			@return VRAM残量

			使用可能なVRAM残量を取得します。<BR>
			この値はビデオカードに搭載されているVRAM量とは違い、<BR>
			ドライバが使用可能な容量を返します。
		*/
		virtual Float GetRestVRAM( void ) = 0;

		/**
			@brief デバイスリスト時コールバック関数登録
			@author 葉迩倭
			@param pCallback	[in] コールバック関数

			デバイスリストア時にコールバックされる関数を設定します。<BR>
			通常の用途では使用する必要はありません。<BR>
			なんらかの理由で直接デバイスを操作する時にのみ使用してください。
		*/
		virtual void SetCallbackDeviceRestore( void (*pCallback)( void ) ) = 0;

		/**
			@brief カラー書き込みマスクを設定
			@author 葉迩倭
			@param IsAlpha		[in] アルファ書き込みマスクON/OFF
			@param IsRed		[in] 赤成分書き込みマスクON/OFF
			@param IsGreen		[in] 緑成分書き込みマスクON/OFF
			@param IsBlue		[in] 青成分書き込みマスクON/OFF

			フラグをtrueにした色への書き込みを行います。<BR>
			falseにするとその色への書き込みを行いません。
		*/
		virtual void SetColorWriteEnable( Bool IsAlpha, Bool IsRed, Bool IsGreen, Bool IsBlue ) = 0;

		/**
			@brief 内部デバイスを取得
			@author 葉迩倭
			@return		デバイスのポインター

			内部で使用しているデバイスを特例的に取得します。<BR>
			通常の用途では使用する必要はありません。<BR>
			なんらかの理由で直接デバイスを操作する時にのみ使用してください。<BR>
			ここで取得したデバイスを経由してステートなどの変更を行った場合、<BR>
			その後のSeleneでのステート管理はサポート外になります。<BR>
		*/
		virtual void *GetDriverDevicePointer( void ) = 0;

		/**
			@brief レンダリングターゲットの内容をPNGファイルに保存
			@author 葉迩倭
			@param pFileName	[in] ファイル名(*.png)

			レンダリングターゲットの内容をPNGファイルとして保存します。<BR>
			この機能を使うにはレンダリングターゲットがロック可能なサーフェイスでなければいけません。
		*/
		virtual void SaveToFilePNG( const char *pFileName ) = 0;

		/**
			@brief レンダリングターゲットの内容をJPGファイルに保存
			@author 葉迩倭
			@param pFileName	[in] ファイル名(*.jpg)

			レンダリングターゲットの内容をJPGファイルとして保存します。<BR>
			この機能を使うにはレンダリングターゲットがロック可能なサーフェイスでなければいけません。
		*/
		virtual void SaveToFileJPG( const char *pFileName ) = 0;

		/**
			@brief 標準のコントロールを表示するためのクリッピングのON/OFF
			@author 葉迩倭
			@param IsEnable	[in] クリップ処理のON/OFF

			trueを指定することでクリッピングが有効になりデバイス上でも正しく表示されるようになります。<BR>
		*/
		virtual void SetGUIEnable( Bool IsEnable ) = 0;

		/**
			@brief テクスチャ設定
			@author 葉迩倭
			@param Stage	[in] 設定するステージ（０～７）
			@param pTex		[in] 設定するテクスチャ（NULLで無効化）
			@retval false	失敗
			@retval true	成功

			テクスチャをレンダラーに設定します。<BR>
			一度設定されたテクスチャはNULLを設定するまで<BR>
			有効になっています。
		*/
		virtual Bool SetTexture( eTextureStage Stage, ITexture *pTex ) = 0;

		/**
			@brief 深度バッファ設定
			@author 葉迩倭
			@param pSurface	[in] 設定するサーフェイス
			@retval false	失敗
			@retval true	成功

			深度バッファを設定します。
		*/
		virtual Bool SetDepthBuffer( ITexture *pTexture ) = 0;

		/**
			@brief レンダリングターゲット設定
			@author 葉迩倭
			@retval false	失敗
			@retval true	成功

			レンダリングターゲットをバックバッファに戻します。
		*/
		virtual Bool ResetRenderTarget( void ) = 0;

		/**
			@brief レンダリングターゲット設定
			@author 葉迩倭
			@retval false	失敗
			@retval true	成功

			レンダリングターゲットとして設定します。<BR>
			CreateRenderTarget()で生成されたテクスチャ以外は失敗します。
		*/
		virtual Bool SetRenderTarget( ITexture *pTexture ) = 0;

		/**
			@brief レンダリング処理開始通知
			@author 葉迩倭

			レンダラーに対してこれからレンダリング処理を<BR>
			開始するという事を通知します。
		*/
		virtual void Begin( void ) = 0;

		/**
			@brief レンダリング処理終了通知
			@author 葉迩倭

			レンダラーに対してこれでレンダリング処理を<BR>
			終了するということを通知します。
		*/
		virtual void End( void ) = 0;

		/**
			@brief 2D描画シザリング設定
			@author 葉迩倭
			@param pRect	[in] シザリング領域(NULLで解除)

			レンダラーに関連する２Ｄ描画のシザリングを行います。
		*/
		virtual void SetScissorPrimitive2D( const Math::Rect2DF *pRect ) = 0;

		/**
			@brief カスタムシーン管理インターフェイス生成
			@author 葉迩倭
			@param QueMax			[in] シーンの描画キューの最大数
			@return カスタムシーン管理インターフェイス

			全てをプロジェクト側で管理するカスタムシーンマネージャーを生成します。<BR>
			レンダリングシステムを自前で管理したい場合に利用して下さい。
		*/
		virtual Scene::ICustomizedSceneManager *CreateCustomizedSceneManager( Sint32 QueMax ) = 0;

		/**
			@brief シーン管理インターフェイス生成
			@author 葉迩倭
			@param QueMax				[in] シーンの描画キューの最大数
			@param IsPixelShaderEnable	[in] ピクセルシェーダーの有無
			@return シーン管理インターフェイス

			シェーダーモデル2.0ベースのシーン管理用のインターフェイスを生成します。<BR>
			3Dに関するレンダリング処理は全てこのインターフェイスを介します。
		*/
		virtual Scene::ISceneManager *CreateSceneManager( Sint32 QueMax, Bool IsPixelShaderEnable ) = 0;

		/**
			@brief 2Dポイントプリミティブインターフェイス生成
			@author 葉迩倭
			@param PointMax		[in] 内部バッファ格納可能ポイント数
			@param IsAutoResize	[in] 自動リサイズ
			@param ResizeStep	[in] リサイズ時拡張サイズ
			@return 2Dポイントプリミティブインターフェイス

			2Dの点描画用のインターフェイスを生成します。<BR>
			画面に点を打つ場合はこのインターフェイスを使います。
		*/
		virtual Object::IPoint2D *CreatePoint2D( Sint32 PointMax, Bool IsAutoResize = false, Sint32 ResizeStep = 0 ) = 0;

		/**
			@brief 2Dラインプリミティブインターフェイス生成
			@author 葉迩倭
			@param LineMax	[in] 内部バッファ格納可能ライン数
			@param IsAutoResize	[in] 自動リサイズ
			@param ResizeStep	[in] リサイズ時拡張サイズ
			@return 2Dラインプリミティブインターフェイス

			2Dの点描画用のインターフェイスを生成します。<BR>
			画面に線を引く場合はこのインターフェイスを使います。
		*/
		virtual Object::ILine2D *CreateLine2D( Sint32 LineMax, Bool IsAutoResize = false, Sint32 ResizeStep = 0 ) = 0;

		/**
			@brief 2Dポリゴンプリミティブインターフェイス生成
			@author 葉迩倭
			@param PrimitiveMax	[in] 内部バッファ格納可能頂点数（通常１つの三角形に三頂点消費する）
			@param IsAutoResize	[in] 自動リサイズ
			@param ResizeStep	[in] リサイズ時拡張サイズ
			@return 2Dポリゴンプリミティブインターフェイス

			2Dのポリゴン（三角形）を描画するためのインターフェイスを生成します。<BR>
			最小単位である三角形ごとの描画を行う場合はこのインターフェイスを使います。
		*/
		virtual Object::IPrimitive2D *CreatePrimitive2D( Sint32 PrimitiveMax, Bool IsAutoResize = false, Sint32 ResizeStep = 0 ) = 0;

		/**
			@brief 2Dスプライトインターフェイス生成
			@author 葉迩倭
			@param PrimitiveMax	[in] 内部バッファ格納可能頂点数（通常１つの三角形に三頂点消費する）
			@param pTexture		[in] スプライトに関連付けるテクスチャインターフェイス
			@param IsFiltering	[in] テクスチャフィルタを使うか否か
			@param IsOffset		[in] フィルタ使用時のテクスチャUV補正値を行うか否か
			@param IsAutoResize	[in] 自動リサイズ
			@param ResizeStep	[in] リサイズ時拡張サイズ
			@return 2Dスプライトインターフェイス

			2Dのスプライトを描画するためのインターフェイスを生成します。<BR>
			IPrimitive2Dを継承しており、内部的にはIPrimitive2Dでの描画を行っています。<BR>
			テクスチャを使った最も簡単なスプライト描画が可能なインターフェイスです。<BR>
			<BR>
			IsFilteringがtrueの時、描画にバイリニアフィルタリングが適用され、拡大縮小、回転などの時に<BR>
			補間され綺麗な描画行われますが、逆に通常の等倍表示の時にぼやけてしまうという欠点があります。<BR>
			この欠点を解消するにはIsFitlerをtrueにし、IsOffsetをfalseにする事で可能ですが、<BR>
			バイリニアフィルタの隣接ピクセルを参照してしまうという問題は画像データの方で解消する必要があります。<BR>
			具体的には周囲に１ドットに余白として何も描画されないピクセルを置くことです。
		*/
		virtual Object::ISprite2D *CreateSprite2D( Sint32 PrimitiveMax, ITexture *pTexture, Bool IsFiltering = false, Bool IsOffset = false, Bool IsAutoResize = false, Sint32 ResizeStep = 0 ) = 0;

		/**
			@brief 2D用フォントスプライトインターフェイス生成
			@author 葉迩倭
			@param pFileName	[in] フォントスプライト用定義ファイル
			@param pExt			[in] フォントスプライト用画像ファイル拡張子
			@param FontMax		[in] 最大フォント数（内部の頂点バッファ数）
			@param IsAutoResize	[in] 自動リサイズ
			@param ResizeStep	[in] リサイズ時拡張サイズ
			@return 2Dフォントスプライトインターフェイス

			2Dのフォントスプライトを描画するためのインターフェイスを生成します。<BR>
			ISprite2Dを利用しており、内部的にはISprite2Dでの描画を行っています。<BR>
			FontUtilityで生成した定義ファイルとテクスチャを使って、高速に文字列の<BR>
			描画を行うことが可能です。
		*/
		virtual Object::IFontSprite2D *CreateFontSprite2DFromFile( const char *pFileName, const char *pExt, Sint32 FontMax, Bool IsAutoResize = false, Sint32 ResizeStep = 0 ) = 0;

		/**
			@brief 3Dポイントプリミティブインターフェイス生成
			@author 葉迩倭
			@param VertexMax	[in] ポイントの最大数
			@param IsDynamic	[in] ダイナミックバッファの使用ON/OFF（頻繁に書き換える場合はtrueにして下さい）
			@return 3Dポイントプリミティブインターフェイス

			3Dのポイント描画用のインターフェイスを生成します。<BR>
			位置及び色データのみで、テクスチャやライトなどの不可効果をつけることは出来ません。
		*/
		virtual Object::IPoint3D *CreatePoint3D( Sint32 VertexMax, Bool IsDynamic ) = 0;

		/**
			@brief 3Dラインプリミティブインターフェイス生成
			@author 葉迩倭
			@param VertexMax	[in] ラインの最大数
			@param IsDynamic	[in] ダイナミックバッファの使用ON/OFF（頻繁に書き換える場合はtrueにして下さい）
			@return 3Dラインプリミティブインターフェイス

			3Dのライン描画用のインターフェイスを生成します。<BR>
			位置及び色データのみで、テクスチャやライトなどの不可効果をつけることは出来ません。
		*/
		virtual Object::ILine3D *CreateLine3D( Sint32 VertexMax, Bool IsDynamic ) = 0;

		/**
			@brief 3Dポリゴンプリミティブインターフェイス生成
			@author 葉迩倭
			@param VertexMax		[in] 内部頂点バッファの最大数
			@param IndexMax			[in] 内部インデックスバッファの最大数
			@param VertexFlag		[in] 頂点データフラグ（eVertexElementの組み合わせ）
			@param IsDynamicVertex	[in] ダイナミック頂点バッファの使用ON/OFF（頻繁に書き換える場合はtrueにして下さい）
			@param IsDynamicIndex	[in] ダイナミックインデックスバッファの使用ON/OFF（頻繁に書き換える場合はtrueにして下さい）
			@return 3Dポリゴンプリミティブインターフェイス

			3Dのポリゴン（三角形）を描画するためのインターフェイスを生成します。<BR>
			最小単位である三角形ごとの描画を行う場合はこのインターフェイスを使います。<BR>
			またインデックスを使用した効率的な描画をサポートします。<BR>
			VertexFlagは頂点のフォーマットを指定するもので eVertexElement 列挙型の中から<BR>
			VERTEX_ELEMENT_PRIMITIVE と VERTEX_ELEMENT_SPRITE を除いたものを指定します。<BR>
			複数組み合わせる場合は | 演算子で指定してください。<BR>
			利用されるシェーダーは内部で作成された固定シェーダーが利用されます。<BR>
			現在のバージョンではバンプマップに関する処理は行われません。<BR>
			<BR>
			（例）法線を持ちライティング可能な頂点 -> VERTEX_ELEMENT_3DTEXTURE | VERTEX_ELEMENT_3DLIGHT
		*/
		virtual Object::IPrimitive3D *CreatePrimitive3D( Sint32 VertexMax, Sint32 IndexMax, Sint32 VertexFlag, Bool IsDynamicVertex, Bool IsDynamicIndex ) = 0;

		/**
			@brief 3Dスプライトインターフェイス生成
			@author 葉迩倭
			@param SpriteMax		[in] 内部バッファ格納可能スプライト数
			@param pTexture			[in] スプライトに関連付けるテクスチャインターフェイス
			@return 3Dスプライトインターフェイス

			3Dのスプライトを描画するためのインターフェイスを生成します。<BR>
			IPrimitive3Dを継承しており、内部的にはIPrimitive3Dでの描画を行っています。<BR>
			テクスチャを使った最も簡単なスプライト描画が可能なインターフェイスです。
		*/
		virtual Object::ISprite3D *CreateSprite3D( Sint32 SpriteMax, ITexture *pTexture ) = 0;

		/**
			@brief パーティクルインターフェイス生成
			@author 葉迩倭
			@param ParticleMax		[in] 内部バッファ格納可能パーティクル数
			@param pTexture			[in] パーティクルに関連付けるテクスチャインターフェイス
			@param Type				[in] パーティクルに関する頂点フォーマットタイプ
			@param IsSoftBillboard	[in] ソフトパーティクル化するかどうか
			@return パーティクルインターフェイス

			パーティクルを描画するためのインターフェイスを生成します。<BR>
			IPrimitive3Dを継承しており、内部的にはIPrimitive3Dでの描画を行っています。
		*/
		virtual Object::IParticle *CreateParticle( Sint32 ParticleMax, ITexture *pTexture, eParticleType Type, Bool IsSoftBillboard = false ) = 0;

		/**
			@brief 3D用フォントスプライトインターフェイス生成
			@author 葉迩倭
			@param pFileName	[in] フォントスプライト用定義ファイル
			@param pExt			[in] フォントスプライト用画像ファイル拡張子
			@param FontMax		[in] 最大フォント数（内部の頂点バッファ数）
			@return 3Dフォントスプライトインターフェイス

			3Dのフォントスプライトを描画するためのインターフェイスを生成します。<BR>
			IParticleを利用しており、内部的にはIParticleでの描画を行っています。<BR>
			FontUtilityで生成した定義ファイルとテクスチャを使って、高速に文字列の<BR>
			描画を行うことが可能です。
		*/
		virtual Object::IFontSprite3D *CreateFontSprite3DFromFile( const char *pFileName, const char *pExt, Sint32 FontMax ) = 0;

		/**
			@brief ツリーモデルをファイルから生成
			@author 葉迩倭
			@param pFileName	[in] モデル名

			SMF形式のモデルファイルを読み込みます。<BR>
			SMFファイルはAmaryllisを使うことでXファイルから生成できます。
		*/
		virtual Object::IMapModel *CreateMapModelFromFile( const char *pFileName ) = 0;

		/**
			@brief ツリーモデルをメモリから生成
			@author 葉迩倭
			@param pData	[in] モデルデータ
			@param Size		[in] データサイズ

			SMF形式のモデルデータを読み込みます。<BR>
			SMFファイルはAmaryllisを使うことでXファイルから生成できます。
		*/
		virtual Object::IMapModel *CreateMapModelFromMemory( const Uint8 *pData, Sint32 Size ) = 0;

		/**
			@brief モデルをファイルから生成
			@author 葉迩倭
			@param pFileName	[in] モデル名

			SMF形式のモデルファイルを読み込みます。<BR>
			SMFファイルはAmaryllisを使うことでXファイルから生成できます。
		*/
		virtual Object::IModel *CreateModelFromFile( const char *pFileName ) = 0;

		/**
			@brief モデルをメモリから生成
			@author 葉迩倭
			@param pData	[in] モデルデータ
			@param Size		[in] データサイズ

			SMF形式のモデルデータを読み込みます。<BR>
			SMFファイルはAmaryllisを使うことでXファイルから生成できます。
		*/
		virtual Object::IModel *CreateModelFromMemory( const Uint8 *pData, Sint32 Size ) = 0;

		/**
			@brief テクスチャ読み込み用コンフィグデータを取得
			@author 葉迩倭
			@return テクスチャコンフィグデータ
		*/
		virtual CTextureConfig &GetTextureConfig( void ) = 0;

		/**
			@brief テクスチャ読み込み用コンフィグデータ設定
			@author 葉迩倭
			@param Conf		[in] テクスチャコンフィグデータ
		*/
		virtual void SetTextureConfig( CTextureConfig &Conf ) = 0;

		/**
			@brief デバイスからサーフェイスを生成
			@author 葉迩倭
			@param Width	[in] 横幅
			@param Height	[in] 縦幅
			@return サーフェイスインターフェイス
		*/
		virtual ITexture *CreateTextureDepthBuffer( Sint32 Width, Sint32 Height ) = 0;

		/**
			@brief デバイスからテクスチャを生成
			@author 葉迩倭
			@param Width	[in] テクスチャの横幅
			@param Height	[in] テクスチャの縦幅
			@param Format	[in] テクスチャフォーマット
			@return テクスチャインターフェイス
		*/
		virtual ITexture *CreateTextureRenderTarget( Sint32 Width, Sint32 Height, eSurfaceFormat Format ) = 0;

		/**
			@brief デバイスからテクスチャを生成
			@author 葉迩倭
			@param pFileName	[in] テクスチャファイル名
			@return テクスチャインターフェイス
		*/
		virtual ITexture *CreateTextureFromFile( const char *pFileName ) = 0;

		/**
			@brief デバイスからテクスチャを生成
			@author 葉迩倭
			@param pData	[in] データのポインタ
			@param Size		[in] データサイズ
			@return テクスチャインターフェイス
		*/
		virtual ITexture *CreateTextureFromMemory( const void *pData, Sint32 Size ) = 0;

		/**
			@brief デバイスからキューブテクスチャを生成
			@author 葉迩倭
			@param pFileName	[in] テクスチャファイル名
			@return テクスチャインターフェイス
		*/
		virtual ITexture *CreateCubeTextureFromFile( const char *pFileName ) = 0;

		/**
			@brief デバイスからキューブテクスチャを生成
			@author 葉迩倭
			@param pData	[in] データのポインタ
			@param Size		[in] データサイズ
			@return テクスチャインターフェイス
		*/
		virtual ITexture *CreateCubeTextureFromMemory( const void *pData, Sint32 Size ) = 0;

		/**
			@brief シェーダーの生成
			@author 葉迩倭
			@param pShader		[in] シェーダーデータのポインタ
			@param Size			[in] シェーダーデータのサイズ
			@param IsCompiled	[in] コンパイル済みか否か
			@return シェーダーインターフェイス

			シェーダーファイルからシェーダーインターフェイスを生成します。
		*/
		virtual Shader::IShader *CreateShaderFromMemory( const void *pShader, Sint32 Size, Bool IsCompiled = false ) = 0;

		/**
			@brief シェーダーの生成
			@author 葉迩倭
			@param pShader		[in] シェーダーファイル
			@param IsCompiled	[in] コンパイル済みか否か
			@return シェーダーインターフェイス

			シェーダーファイルからシェーダーインターフェイスを生成します。
		*/
		virtual Shader::IShader *CreateShaderFromFile( const char *pFile, Bool IsCompiled = false ) = 0;

		/**
			@brief 描画タイプ設定
			@author 葉迩倭
			@param Type		[in] 描画タイプ

			ポリゴンの描画タイプを設定します。
		*/
		virtual void SetDrawType( eDrawType Type ) = 0;

		/**
			@brief 表裏判定タイプ設定
			@author 葉迩倭
			@param Type		[in] 表裏判定タイプ

			ポリゴンの表裏判定タイプを設定します。
		*/
		virtual void SetCullType( eCullType Type ) = 0;

		/**
			@brief フィルタリングタイプ設定
			@author 葉迩倭
			@param Stage	[in] 設定ステージ
			@param Type		[in] フィルタリングタイプ

			テクスチャステージ毎のフィルタリングタイプを設定します。<BR>
			TEXTURE_FILTER_ANISOTROPY系 のフィルタがサポートされないハードウェアでは<BR>
			TEXTURE_FILTER_2D が使われます。
		*/
		virtual void SetTextureFilterType( eTextureStage Stage, eTextureFilterType Type ) = 0;

		/**
			@brief 深度テストON/OFF設定
			@author 葉迩倭
			@param Flag		[in] 深度テストON/OFF

			深度テストのON/OFFを設定します。
		*/
		virtual void SetDepthTestEnable( Bool Flag ) = 0;

		/**
			@brief 深度バッファ書き込みON/OFF設定
			@author 葉迩倭
			@param Flag		[in] 深度バッファ書き込みON/OFF

			深度バッファ書き込みのON/OFFを設定します。
		*/
		virtual void SetDepthWriteEnable( Bool Flag ) = 0;

		/**
			@brief アルファテストON/OFF設定
			@author 葉迩倭
			@param Flag		[in] アルファテストON/OFF

			アルファテストのON/OFFを設定します。
		*/
		virtual void SetAlphaTestEnable( Bool Flag ) = 0;

		/**
			@brief アルファテスト閾値設定
			@author 葉迩倭
			@param Bound	[in] アルファテスト閾値

			アルファテストの閾値を設定します。
		*/
		virtual void SetAlphaBoundary( Sint32 Bound ) = 0;

		/**
			@brief ステートの設定をスタックに退避します
			@author 葉迩倭
			@retval false	スタックオーバーフロー
			@retval true	エラー無し

			現在のステートをスタックに退避させます。<BR>
			この関数によって退避されるステートは以下の関数で設定したものです。<BR>
			・void SetDrawType( eDrawType Type )<BR>
			・void SetCullType( eCullType Type )<BR>
			・void SetTextureFilterType( Sint32 Stage, eTextureFilterType Type )<BR>
			・void SetTextureAddressType( Sint32 Stage, eTextureAddressType Type )<BR>
			・void SetDepthTestEnable( Bool Flag )<BR>
			・void SetDepthWriteEnable( Bool Flag )<BR>
			・void SetAlphaTestEnable( Bool Flag )<BR>
			・void SetAlphaBoundary( Sint32 Bound )<BR>
			・Bool SetTexture( Sint32 Stage, ITexture *pTex )
		*/
		virtual Bool StatePush( void ) = 0;

		/**
			@brief ステートの設定をスタックから復帰します
			@author 葉迩倭
			@retval false	スタックオーバーフロー
			@retval true	エラー無し

			現在のステートをスタックに退避去れているステートに戻します。
		*/
		virtual Bool StatePop( void ) = 0;

		/**
			@brief ステートの設定を初期状態にリセットします
			@author 葉迩倭

			現在のステートをスタックに退避去れているステートに戻します。<BR>
			・SetDrawType( DRAW_TYPE_NORMAL )<BR>
			・SetCullType( CULL_FRONT )<BR>
			・SetDepthTestEnable( false )<BR>
			・SetDepthWriteEnable( false )<BR>
			・void SetAlphaTestEnable( true )<BR>
			・void SetAlphaBoundary( Sint32 Bound )<BR>
			・SetTextureFilterType( \\<Stage\\>, TEXTURE_FILTER_DISABLE )<BR>
			・SetTextureAddressType( \\<Stage\\>, TEXTURE_ADDRESS_REPEAT )<BR>
			・SetTexture( \\<Stage\\>, NULL )
		*/
		virtual void StateInit( void ) = 0;

		/**
			@brief デバッグ用文字設定変更
			@author 葉迩倭
			@param pFontFace	[in] フォント種類
			@param Size			[in] フォントサイズ

			デバッグ用の文字の設定を変更します。
		*/
		virtual void ChangeDebugPrintFont( const char *pFontFace, Sint32 Size ) = 0;

		/**
			@brief デバッグ用文字描画処理
			@author 葉迩倭
			@param Pos		[in] 描画位置
			@param Color	[in] 描画色
			@param pStr		[in] 描画文字列

			デバッグ用の文字描画を行います。
		*/
		virtual void DebugPrint( Math::Point2DI &Pos, CColor Color, const char *pStr, ... ) = 0;

		/**
			@brief 簡易文字描画用フォント設定
			@author 葉迩倭
			@param pFontFace	[in] フォント種類
			@param Size			[in] フォントサイズ

			簡易文字描画のフォントの設定をします
		*/
		virtual void SetDrawTextFont( const char *pFontFace, Sint32 Size ) = 0;

		/**
			@brief 簡易文字描画処理
			@author 葉迩倭
			@param Pos		[in] 描画位置
			@param Color	[in] 描画色
			@param pStr		[in] 描画文字列

			簡易文字描画を行います。
		*/
		virtual void DrawText( Math::Point2DI &Pos, CColor Color, const char *pStr, ... ) = 0;

		/**
			@brief 矩形レンダリング
			@author 葉迩倭
			@param Dst			[in] 描画先矩形
			@param Color		[in] 描画色

			単純な矩形を塗りつぶします。
		*/
		virtual void FillRect( const Math::Rect2DF &Dst, CColor Color ) = 0;

		/**
			@brief シェーダーを利用する場合のテクスチャを使った矩形回転付きのレンダリング
			@author 葉迩倭
			@param Dst		[in] 描画先矩形
			@param Color	[in] 描画色
			@param Src		[in] テクスチャUV矩形
			@param pTex		[in] テクスチャ
			@param Angle	[in] 回転角度
			@param Offset	[in] 回転の中心の画像の中心からのオフセット

			外部のシェーダーを利用する場合の回転付きの単純な矩形をテクスチャ対応でレンダリングします。
		*/
		virtual void DrawTextureByShader( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) ) = 0;

		/**
			@brief テクスチャを使った矩形回転付きのレンダリング
			@author 葉迩倭
			@param Dst		[in] 描画先矩形
			@param Color	[in] 描画色
			@param Src		[in] テクスチャUV矩形
			@param pTex		[in] テクスチャ
			@param Angle	[in] 回転角度
			@param Offset	[in] 回転の中心の画像の中心からのオフセット

			回転付きの単純な矩形をテクスチャ対応でレンダリングします。
		*/
		virtual void DrawTexture( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) ) = 0;

		/**
			@brief テクスチャを使った矩形回転付きのレンダリング
			@author 葉迩倭
			@param Dst		[in] 描画先矩形
			@param Color	[in] 描画色
			@param Src		[in] テクスチャUV矩形
			@param pTex		[in] テクスチャ
			@param Angle	[in] 回転角度
			@param Offset	[in] 回転の中心の画像の中心からのオフセット

			回転付きの単純な矩形をテクスチャ対応でレンダリングします。
		*/
		virtual void DrawTextureTile( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) ) = 0;

		/**
			@brief ユニバーサルトランジション描画
			@author 葉迩倭
			@param Dst			[in] 描画先矩形
			@param fRate		[in] 透明度（0.0～1.0）
			@param SrcBase		[in] ベース画像テクスチャUV矩形
			@param pTexBase		[in] ベース画像テクスチャ
			@param SrcRule		[in] アルファ用ルールテクスチャUV矩形
			@param pTexRule		[in] アルファ用ルールテクスチャ
			@param Angle		[in] 回転角度
			@param Offset		[in] 回転の中心の画像の中心からのオフセット

			ルール画像を用いたユニバーサルトランジションを行います。<BR>
			PixelShader2.0がない環境ではDrawTextureに置き換えられます。
		*/
		virtual void DrawUniversal( const Math::Rect2DF &Dst, Float fRate, const Math::Rect2DF &SrcBase, ITexture *pTexBase, const Math::Rect2DF &SrcRule, ITexture *pTexRule, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) ) = 0;

		/**
			@brief 4x4コーンぼかしフィルタ描画
			@author 葉迩倭
			@param Dst		[in] 描画先矩形
			@param Color	[in] 描画色
			@param Src		[in] テクスチャUV矩形
			@param pTex		[in] テクスチャ
			@param Angle	[in] 回転角度
			@param Offset	[in] 回転の中心の画像の中心からのオフセット

			4x4のボックスぼかしのフィルタをかけて描画します。<BR>
			PixelShader2.0がない環境ではDrawTextureに置き換えられます。
		*/
		virtual void DrawBlur( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) ) = 0;

		/**
			@brief グレースケールフィルタ描画
			@author 葉迩倭
			@param Dst		[in] 描画先矩形
			@param Color	[in] 描画色
			@param Src		[in] テクスチャUV矩形
			@param pTex		[in] テクスチャ
			@param Angle	[in] 回転角度
			@param Offset	[in] 回転の中心の画像の中心からのオフセット

			グレースケールのフィルタをかけて描画します。<BR>
			PixelShader2.0がない環境ではDrawTextureに置き換えられます。
		*/
		virtual void DrawGrayscale( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) ) = 0;

		/**
			@brief 魚眼レンズ描画
			@author 葉迩倭
			@param Dst		[in] 描画先矩形
			@param Color	[in] 描画色
			@param Src		[in] テクスチャUV矩形
			@param pTex		[in] テクスチャ
			@param fRate	[in] 魚眼レンズ歪み度（０で歪みなし）

			魚眼レンズのフィルタをかけて描画します。<BR>
			PixelShader2.0がない環境ではDrawTextureに置き換えられます。
		*/
		virtual void DrawFishEye( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Float fRate ) = 0;
	};
}
}

