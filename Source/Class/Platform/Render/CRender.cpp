

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Platform/Render/Shader/CShader.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CVertexLayout.h"
#include "Class/Platform/Surface/CTextureMgr.h"
#include "Class/Platform/Surface/CDepthTexture.h"
#include "Class/Platform/Surface/CTargetTexture.h"
#include "Class/Platform/Surface/CTexture.h"
#include "Class/Platform/Surface/CCubeTexture.h"
#include "Class/Platform/Render/COcclusion.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/File/CFileManager.h"
#include "Class/Common/Object/CRenderObjectMgr.h"
#include "Class/Common/Render/2D/CPrimitive2DBaseMgr.h"
#include "Class/Common/Render/2D/CFontSprite2D.h"
#include "Class/Common/Render/2D/CSprite2D.h"
#include "Class/Common/Render/2D/CPointPrimitive2D.h"
#include "Class/Common/Render/2D/CLinePrimitive2D.h"
#include "Class/Common/Render/3D/CPrimitive3DBaseMgr.h"
#include "Class/Common/Render/2D/CPrimitive2D.h"
#include "Class/Common/Render/3D/CPointPrimitive3D.h"
#include "Class/Common/Render/3D/CLinePrimitive3D.h"
#include "Class/Common/Render/3D/CPrimitive3D.h"
#include "Class/Common/Render/3D/CSprite3D.h"
#include "Class/Common/Render/3D/CFontSprite3D.h"
#include "Class/Common/Render/3D/CParticle.h"
#include "Class/Common/Render/Model/CModel.h"
#include "Class/Common/Render/Model/CModelMgr.h"
#include "Class/Common/Render/Map/CMapModel.h"
#include "Class/Common/Render/Map/CMapModelMgr.h"
#include "Class/Common/Scene/CSceneManager_Shader.h"
#include "Class/Common/Scene/CSceneManager_Fixed.h"
#include "Class/Common/Scene/CCustomizedSceneManager.h"
#include "NullDevice/Surface/NullTexture.h"
#include "NullDevice/Render/2D/NullPointPrimitive2D.h"
#include "NullDevice/Render/2D/NullLinePrimitive2D.h"
#include "NullDevice/Render/2D/NullPrimitive2D.h"
#include "NullDevice/Render/2D/NullSprite2D.h"
#include "NullDevice/Render/2D/NullFontSprite2D.h"
#include "NullDevice/Render/3D/NullPointPrimitive3D.h"
#include "NullDevice/Render/3D/NullLinePrimitive3D.h"
#include "NullDevice/Render/3D/NullPrimitive3D.h"
#include "NullDevice/Render/3D/NullSprite3D.h"
#include "NullDevice/Render/3D/NullFontSprite3D.h"
#include "NullDevice/Render/3D/NullParticle.h"
#include "NullDevice/Render/Model/NullModel.h"
#include "NullDevice/Render/Map/NullMapModel.h"
#include "NullDevice/Scene/NullSceneManager.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;


//-----------------------------------------------------------------------------------
// TABLE
//-----------------------------------------------------------------------------------
static const D3DPRIMITIVETYPE g_PrimitiveTypeTbl[] = {
	D3DPT_POINTLIST,		// PRIMITIVE_POINT
	D3DPT_LINELIST,			// PRIMITIVE_LINE
	D3DPT_LINESTRIP,		// PRIMITIVE_LINE_STRIP
	D3DPT_TRIANGLELIST,		// PRIMITIVE_TRIANGLE
	D3DPT_TRIANGLESTRIP,	// PRIMITIVE_TRIANGLE_STRIP
	D3DPT_TRIANGLEFAN,		// PRIMITIVE_TRIANGLE_FAN
};

// ポストエフェクト用
static const D3DVERTEXELEMENT9 g_VertexElementPostEffect[] = {
    { 0, STRUCT_OFFSET(SVertexPostEffect,Pos),    D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },
	{ 0, STRUCT_OFFSET(SVertexPostEffect,Tex[0]), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  0 },
	{ 0, STRUCT_OFFSET(SVertexPostEffect,Tex[1]), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  1 },
	{ 0, STRUCT_OFFSET(SVertexPostEffect,Tex[2]), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  2 },
	{ 0, STRUCT_OFFSET(SVertexPostEffect,Tex[3]), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  3 },
	{ 0, STRUCT_OFFSET(SVertexPostEffect,Tex[4]), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  4 },
	{ 0, STRUCT_OFFSET(SVertexPostEffect,Tex[5]), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  5 },
	{ 0, STRUCT_OFFSET(SVertexPostEffect,Tex[6]), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  6 },
	{ 0, STRUCT_OFFSET(SVertexPostEffect,Tex[7]), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  7 },
};

// ２Ｄ用
static const D3DVERTEXELEMENT9 g_VertexElement2D[] = {
    { 0, STRUCT_OFFSET(SVertex2D,Pos), D3DDECLTYPE_FLOAT4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },
	{ 0, STRUCT_OFFSET(SVertex2D,Col), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,     0 },
};

// ２Ｄ＋テクスチャ用
static const D3DVERTEXELEMENT9 g_VertexElementTex2D[] = {
    { 0, STRUCT_OFFSET(SVertex2DTex,Pos),    D3DDECLTYPE_FLOAT4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },
	{ 0, STRUCT_OFFSET(SVertex2DTex,Col),    D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,     0 },
	{ 0, STRUCT_OFFSET(SVertex2DTex,Tex[0]), D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  0 },
	{ 0, STRUCT_OFFSET(SVertex2DTex,Tex[1]), D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  1 },
};

// トランスフォーム用
static const D3DVERTEXELEMENT9 g_VertexElement3DBase[] = {
    { 0, STRUCT_OFFSET(SVertex3DBase,Pos), D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, STRUCT_OFFSET(SVertex3DBase,Col), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
};

// テクスチャ用
static const D3DVERTEXELEMENT9 g_VertexElement3DTexture[] = {
	{ 1, STRUCT_OFFSET(SVertex3DTexture,TexColor), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	{ 1, STRUCT_OFFSET(SVertex3DTexture,TexLight), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },
};

// ライティング用
static const D3DVERTEXELEMENT9 g_VertexElement3DLight[] = {
    { 2, STRUCT_OFFSET(SVertex3DLight,Norm), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
};

// バンプ用
static const D3DVERTEXELEMENT9 g_VertexElement3DBump[] = {
    { 3, STRUCT_OFFSET(SVertex3DBump,Tangent), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },
};

// アニメーション用
static const D3DVERTEXELEMENT9 g_VertexElement3DAnimation[] = {
    { 4, STRUCT_OFFSET(SVertex3DAnimation,Weight),   D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT,  0 },
    { 4, STRUCT_OFFSET(SVertex3DAnimation,Index[0]), D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },
};


//-----------------------------------------------------------------------------------
// シェーダー
//-----------------------------------------------------------------------------------
static const Uint8 g_Shader2D[] = {
	#include "Shader/ShaderFile/Draw2D.inc"
};


//-----------------------------------------------------------------------------------
// テクスチャ
//-----------------------------------------------------------------------------------
static const Uint8 g_ColorMap[] = {
	#include "Resource/ColorMap.dds.inc"
};

static const Uint8 g_LightMap[] = {
	#include "Resource/LightMap.dds.inc"
};

static const Uint8 g_EnvironmentMap[] = {
	#include "Resource/EnvironmentMap.dds.inc"
};

static const Uint8 g_SpecularMap[] = {
	#include "Resource/SpecularMap.dds.inc"
};

static const Uint8 g_NormalMap[] = {
	#include "Resource/NormalMap.dds.inc"
};

static const Uint8 g_ToonMap[] = {
	#include "Resource/ToonMap.dds.inc"
};


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRender::CRender( CGraphicCard *pGraphicCard, Bool IsWindow, Bool IsLockEnableBackBuffer, Bool IsWaitVSync )
	: m_pGraphicCard				( pGraphicCard )
	, m_pCore						( pGraphicCard->GetCorePointer() )
	, m_pD3DDevice					( NULL )
	, m_pBackBuffer					( NULL )
	, m_pEffectPool					( NULL )
	, m_pFont						( NULL )
	, m_pSceneMgr					( NULL )
	, m_pVertexStreamMgr			( NULL )
	, m_pVertexBufferMgr			( NULL )
	, m_pIndexBufferMgr				( NULL )
	, m_pShaderMgr					( NULL )
	, m_pListPrimitive2DMgr			( NULL )
	, m_pListPrimitive3DMgr			( NULL )
	, m_pListModelMgr				( NULL )
	, m_pListMapModelMgr			( NULL )
	, m_pTextureMgr					( NULL )
	, m_pActiveScene				( NULL )
	, m_pVertexBuffer2D				( NULL )
	, m_pVertexStream2D				( NULL )
	, m_pShader2D					( NULL )
	, m_pCallbackReset				( NULL )
	, m_pCallbackRestore			( NULL )
	, m_pDepthBuffer				( NULL )
	, m_IsDynamicBufferEnable		( false )
	, m_MaxUseVertexShaderVersion	( 0 )
	, m_IsLockEnableBackBuffer		( IsLockEnableBackBuffer )
	, m_IsWaitVSync					( IsWaitVSync )
	, m_fUsedVRAM					( 0.0f )
	, m_fRestVRAM					( 0.0f )
{
	for ( Sint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		m_pTextureDefault[i] = NULL;
	}

	//------------------------------------------------------------------
	// ウィンドウに対して所有デバイスを設定
	//------------------------------------------------------------------
	m_pCore->SetRender( this );

	//------------------------------------------------------------------
	// デバイス生成用パラメーターの設定
	//------------------------------------------------------------------
	m_AcitivePresentParam = m_pGraphicCard->MakePresentParameters( IsWindow, m_pGraphicCard->IsHightColorMode(), m_IsLockEnableBackBuffer, m_IsWaitVSync );

	//------------------------------------------------------------------
	// 頂点処理
	//------------------------------------------------------------------
	const Sint32 CreateFlag[] = {
		D3DCREATE_MULTITHREADED | D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,	// DEVICE_CREATE_PUREDEVICE
		D3DCREATE_MULTITHREADED | D3DCREATE_HARDWARE_VERTEXPROCESSING,							// DEVICE_CREATE_HARDWARE_TNL
		D3DCREATE_MULTITHREADED | D3DCREATE_SOFTWARE_VERTEXPROCESSING,							// DEVICE_CREATE_SOFTWARE_TNL
	};

	Sint32 DeviceNo = m_pGraphicCard->GetDeviceTypeNo();

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( "Direct3Dデバイス" );
	Log_CellBegin( 0 );

	//------------------------------------------------------------------
	// NVPerfHUDでデバイスの作成を試みる
	//------------------------------------------------------------------
	if ( !CreateDeviceByNVPerfHUD( m_AcitivePresentParam ) )
	{
		HRESULT hr;
		// 通常のデバイス作成
		for ( ; ; )
		{
			// デバイス生成
			hr = m_pGraphicCard->CreateDeviceObject(
								D3DDEVTYPE_HAL,
								CreateFlag[DeviceNo],
								m_AcitivePresentParam,
								m_pD3DDevice );
			if SUCCEEDED( hr )
			{
				break;
			}

			// デバイスタイプを変更してやり直し
			if ( ++DeviceNo == DEVICE_CREATE_MAX )
			{
				break;
			}
		}

		// デバイス生成終了
		switch ( DeviceNo )
		{
		case DEVICE_CREATE_PUREDEVICE:
			Log_PrintStrongLine( 0x000000, "ピュアデバイスを生成" );
			Log_PrintLine( 0x000000, "D3DDEVTYPE_HAL" );
			Log_PrintLine( 0x000000, "D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE" );
			m_pD3DDevice->SetSoftwareVertexProcessing( false );
			m_IsDynamicBufferEnable = true;
			break;
		case DEVICE_CREATE_HARDWARE_TNL:
			Log_PrintStrongLine( 0x000000, "ハードウェアTnLデバイスを生成" );
			Log_PrintLine( 0x000000, "D3DDEVTYPE_HAL" );
			Log_PrintLine( 0x000000, "D3DCREATE_HARDWARE_VERTEXPROCESSING" );
			m_pD3DDevice->SetSoftwareVertexProcessing( false );
			m_IsDynamicBufferEnable = true;
			break;
		case DEVICE_CREATE_SOFTWARE_TNL:
			Log_PrintStrongLine( 0x000000, "ソフトウェアTnLデバイスを生成" );
			Log_PrintLine( 0x000000, "D3DDEVTYPE_HAL" );
			Log_PrintLine( 0x000000, "D3DCREATE_SOFTWARE_VERTEXPROCESSING" );
			m_pD3DDevice->SetSoftwareVertexProcessing( true );
			m_IsDynamicBufferEnable = false;
			break;
		default:
			Log_PrintStrongLine( 0xFF0000, "デバイス生成エラー" );
			Log_PrintLine( 0xFF0000, m_pGraphicCard->GetD3DError(hr) );
			Log_CellEnd();
			Log_TableEnd();
			Log_TableLine( 2 );
			m_pD3DDevice = NULL;
			return;
		}
	}

	m_fUsedVRAM = 0.0f;
	m_fRestVRAM = GetRestVRAM();
	Log_PrintLine( 0x000000, "使用可能テクスチャメモリ容量 %.3lfMB", m_fRestVRAM );
	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//------------------------------------------------------------------
	// レンダリングターゲット取得
	//------------------------------------------------------------------
	m_pD3DDevice->GetRenderTarget( 0, &m_pBackBuffer );
	m_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0x00000000, 1.0f, 0 );
	m_pD3DDevice->Present( NULL, NULL, NULL, NULL );
	m_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0x00000000, 1.0f, 0 );

	//------------------------------------------------------------------
	// デバイス性能
	//------------------------------------------------------------------
	m_pD3DDevice->GetDeviceCaps( &m_Caps );

	//------------------------------------------------------------------
	// エフェクトプール
	//------------------------------------------------------------------
	::D3DXCreateEffectPool( &m_pEffectPool );

	//------------------------------------------------------------------
	// 文字
	//------------------------------------------------------------------
	ChangeDebugPrintFont( "ＭＳ ゴシック", 12 );

	//------------------------------------------------------------------
	// ビューポート初期化
	//------------------------------------------------------------------
	Sint32 Width, Height;
	m_pGraphicCard->GetCorePointer()->GetScreenData( &Width, &Height, NULL );
	m_Viewport.X		= 0;
	m_Viewport.Y		= 0;
	m_Viewport.Width	= Width;
	m_Viewport.Height	= Height;
    m_Viewport.MinZ		= 0.0f;
	m_Viewport.MaxZ		= 1.0f;
	m_pD3DDevice->SetViewport( &m_Viewport );

	//------------------------------------------------------------------
	// 変換行列
	//------------------------------------------------------------------
	D3DXMATRIX Mtx;
	::D3DXMatrixIdentity( &Mtx );
    m_pD3DDevice->SetTransform( D3DTS_WORLD,		&Mtx );
    m_pD3DDevice->SetTransform( D3DTS_VIEW,			&Mtx );
    m_pD3DDevice->SetTransform( D3DTS_PROJECTION,	&Mtx );
    m_pD3DDevice->SetTransform( D3DTS_TEXTURE0,		&Mtx );
    m_pD3DDevice->SetTransform( D3DTS_TEXTURE1,		&Mtx );
    m_pD3DDevice->SetTransform( D3DTS_TEXTURE2,		&Mtx );
    m_pD3DDevice->SetTransform( D3DTS_TEXTURE3,		&Mtx );
    m_pD3DDevice->SetTransform( D3DTS_TEXTURE4,		&Mtx );
    m_pD3DDevice->SetTransform( D3DTS_TEXTURE5,		&Mtx );
    m_pD3DDevice->SetTransform( D3DTS_TEXTURE6,		&Mtx );
    m_pD3DDevice->SetTransform( D3DTS_TEXTURE7,		&Mtx );

	//------------------------------------------------------------------
	// マウスカーソル
	//------------------------------------------------------------------
	POINT Pt = { Width, Height };
	::SetCursorPos( Pt.x, Pt.y );

	//------------------------------------------------------------------
	// 必須オブジェクト
	//------------------------------------------------------------------
	m_pVertexStreamMgr		= new CRenderObjectMgr( this, "頂点ストリーム" );
	m_pVertexBufferMgr		= new CRenderObjectMgr( this, "頂点データ" );
	m_pIndexBufferMgr		= new CRenderObjectMgr( this, "頂点インデックス" );
	m_pShaderMgr			= new CRenderObjectMgr( this, "シェーダー" );
	m_pTextureMgr			= new CTextureMgr( this );

	m_pSceneMgr				= new CRenderObjectMgr( this, "シーン" );
	m_pListModelMgr			= new Renderer::Object::CModelMgr( this );
	m_pListMapModelMgr		= new Renderer::Object::CMapModelMgr( this );
	m_pListPrimitive2DMgr	= new Renderer::Object::CPrimitive2DBaseMgr( this );
	m_pListPrimitive3DMgr	= new Renderer::Object::CPrimitive3DBaseMgr( this );

	//------------------------------------------------------------------
	// マルチテクスチャ用
	//------------------------------------------------------------------
	m_pVertexStream2D = CreateVertexStream( VERTEX_ELEMENT_SPRITE );
	m_pVertexBuffer2D = CreateVertexBuffer( 4, GetSize(VERTEX_ELEMENT_SPRITE), true );
	m_pShader2D = CreateShaderFromMemory( g_Shader2D, sizeof(g_Shader2D), true );

	//------------------------------------------------------------------
	// シェーダー
	//------------------------------------------------------------------
	Shader::ShaderManager::Initialize( this, m_pCore->GetPluginDirectory() );

	//------------------------------------------------------------------
	// 変数初期化
	//------------------------------------------------------------------
	m_pActiveScene = NULL;
	m_RenderStatePos = 0;
	for ( Sint32 i = 0; i < STATE_STACK_MAX; i++ )
	{
		m_RenderState[i].DrawType           = DRAW_TYPE_NORMAL;
		m_RenderState[i].CullType           = CULL_FRONT;
		m_RenderState[i].AlphaBoundary      = 0;
		m_RenderState[i].IsAlphaTestEnable  = true;
		m_RenderState[i].IsDepthTestEnable  = false;
		m_RenderState[i].IsDepthWriteEnable = false;
		for ( Sint32 j = 0; j < TEXTURE_STAGE_MAX; j++ )
		{
			m_RenderState[i].FilterType[j]	  = TEXTURE_FILTER_DISABLE;
			m_RenderState[i].pTextureTbl[j]   = NULL;
		}
	}

	m_TextureConfig.SetFormat( FORMAT_TEXTURE_32BIT );
	m_TextureConfig.SetColorKey( 0x00000000 );
	m_TextureConfig.SetMipmapEnable( false );

	//------------------------------------------------------------------
	// テクスチャ
	//------------------------------------------------------------------
	m_pTextureDefault[TEXTURE_STAGE_COLOR]       = (CTextureInterface*)CreateTextureFromMemory( g_ColorMap, sizeof(g_ColorMap) );
	m_pTextureDefault[TEXTURE_STAGE_LIGHT]       = (CTextureInterface*)CreateTextureFromMemory( g_LightMap, sizeof(g_LightMap) );
	m_pTextureDefault[TEXTURE_STAGE_ENVIRONMENT] = (CTextureInterface*)CreateCubeTextureFromMemory( g_EnvironmentMap, sizeof(g_EnvironmentMap) );
	m_pTextureDefault[TEXTURE_STAGE_SPECULAR]    = (CTextureInterface*)CreateTextureFromMemory( g_SpecularMap, sizeof(g_SpecularMap) );
	m_pTextureDefault[TEXTURE_STAGE_NORMAL]      = (CTextureInterface*)CreateTextureFromMemory( g_NormalMap, sizeof(g_NormalMap) );
	m_pTextureDefault[TEXTURE_STAGE_SHADOW]      = NULL;
	m_pTextureDefault[TEXTURE_STAGE_DEPTH]       = NULL;
	m_pTextureDefault[TEXTURE_STAGE_TOON]        = (CTextureInterface*)CreateTextureFromMemory( g_ToonMap, sizeof(g_ToonMap) );

	//------------------------------------------------------------------
	// ステート
	//------------------------------------------------------------------
	ResetTextureStageState();
	ResetSamplerState();
	ResetRenderState();

	for ( Sint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		SetTexture( (eTextureStage)i, NULL );
	}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRender::~CRender()
{
	// ウィンドウに対して所有デバイスを設定
	m_pCore->SetRender( NULL );

	// シェーダー
	Shader::ShaderManager::Finalize();

	for ( Sint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		SAFE_RELEASE( m_pTextureDefault[i] );
	}

	SAFE_RELEASE( m_pShader2D );
	SAFE_RELEASE( m_pVertexStream2D );
	SAFE_RELEASE( m_pVertexBuffer2D );

	SAFE_DELETE( m_pTextureMgr );
	SAFE_DELETE( m_pListPrimitive2DMgr );
	SAFE_DELETE( m_pVertexStreamMgr );
	SAFE_DELETE( m_pVertexBufferMgr );
	SAFE_DELETE( m_pIndexBufferMgr );
	SAFE_DELETE( m_pShaderMgr );
	SAFE_DELETE( m_pListModelMgr );
	SAFE_DELETE( m_pListMapModelMgr );
	SAFE_DELETE( m_pListPrimitive3DMgr );
	SAFE_DELETE( m_pSceneMgr );

	SAFE_RELEASE( m_pBackBuffer );
	SAFE_RELEASE( m_pEffectPool );
	SAFE_RELEASE( m_pFont );

	// デバイス解放
	if ( m_pD3DDevice != NULL )
	{
		Sint32 Width, Height;
		m_pGraphicCard->GetCorePointer()->GetScreenData( &Width, &Height, NULL );

		Sint32 Num = m_pD3DDevice->Release();
		m_pD3DDevice = NULL;

		Log_TableBegin();
		Log_PrintCellTitle( 0x008000, "解放" );
		Log_PrintCellKind( "IDirect3DDevice9" );
		Log_CellBegin( 0 );
		Log_Print( 0x000000, "参照数 %d", Num );
		Log_PrintTable( 128, "推定最大使用メモリ", "%lfMB", m_fUsedVRAM + (toF(Width * Height * 4 * 2) / 1024.0f / 1024.0f) );
		Log_CellEnd();
		Log_TableEnd();
		Log_TableLine( 2 );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::CreateDeviceByNVPerfHUD( D3DPRESENT_PARAMETERS &PresentParam )
{
	if ( GetGraphicCardPointer()->IsNVPerfHUDEnable() )
	{
		HRESULT hr = GetGraphicCardPointer()->CreateDeviceObject(
							D3DDEVTYPE_REF,
							D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE | D3DCREATE_MULTITHREADED,
							PresentParam,
							m_pD3DDevice );
		if SUCCEEDED( hr )
		{
			Log_PrintStrongLine( 0x000000, "NVPerfHUDデバイスを生成" );
			Log_PrintLine( 0x000000, "D3DDEVTYPE_REF" );
			Log_PrintLine( 0x000000, "D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE" );
			m_pD3DDevice->SetSoftwareVertexProcessing( false );

			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::ResetRenderState( void )
{
	Float fPointSize	= 64.0f;
	Float fZero			= 0.0f;
	Float fOne			= 1.0f;
	Uint32 PointSize	= *((Uint32*)&fPointSize);
	Uint32 Zero			= *((Uint32*)&fZero);
	Uint32 One			= *((Uint32*)&fOne);

	m_pD3DDevice->SetRenderState( D3DRS_COLORWRITEENABLE,				D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_ZENABLE,						D3DZB_FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_FILLMODE,						D3DFILL_SOLID );
	m_pD3DDevice->SetRenderState( D3DRS_SHADEMODE,						D3DSHADE_GOURAUD );
	m_pD3DDevice->SetRenderState( D3DRS_ZWRITEENABLE,					FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_LASTPIXEL,						TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND,						D3DBLEND_ONE );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND,						D3DBLEND_ZERO );
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE,						D3DCULL_CCW );
	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC,							D3DCMP_LESSEQUAL );
	m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,				TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_ALPHATESTENABLE,				TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_ALPHAREF,						0x00000000 );
	m_pD3DDevice->SetRenderState( D3DRS_ALPHAFUNC,						D3DCMP_GREATER );
	m_pD3DDevice->SetRenderState( D3DRS_DITHERENABLE,					FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_FOGENABLE,						FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_SPECULARENABLE,					FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_FOGCOLOR,						0x00000000 );
	m_pD3DDevice->SetRenderState( D3DRS_FOGTABLEMODE,					D3DFOG_NONE );
	m_pD3DDevice->SetRenderState( D3DRS_FOGVERTEXMODE,					D3DFOG_LINEAR );
	m_pD3DDevice->SetRenderState( D3DRS_FOGSTART,						Zero );
	m_pD3DDevice->SetRenderState( D3DRS_FOGEND,							One );
	m_pD3DDevice->SetRenderState( D3DRS_FOGDENSITY,						One );
	m_pD3DDevice->SetRenderState( D3DRS_RANGEFOGENABLE,					FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_STENCILENABLE,					FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_STENCILFAIL,					D3DSTENCILOP_KEEP );
	m_pD3DDevice->SetRenderState( D3DRS_STENCILZFAIL,					D3DSTENCILOP_KEEP );
	m_pD3DDevice->SetRenderState( D3DRS_STENCILPASS,					D3DSTENCILOP_KEEP );
	m_pD3DDevice->SetRenderState( D3DRS_STENCILFUNC,					D3DCMP_ALWAYS );
	m_pD3DDevice->SetRenderState( D3DRS_STENCILREF,						0x00000000 );
	m_pD3DDevice->SetRenderState( D3DRS_STENCILMASK,					0xFFFFFFFF );
	m_pD3DDevice->SetRenderState( D3DRS_STENCILWRITEMASK,				0xFFFFFFFF );
	m_pD3DDevice->SetRenderState( D3DRS_TEXTUREFACTOR,					0xFFFFFFFF );
	m_pD3DDevice->SetRenderState( D3DRS_CLIPPING,						TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING,						FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_AMBIENT,						0x00000000 );
	m_pD3DDevice->SetRenderState( D3DRS_COLORVERTEX,					TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_LOCALVIEWER,					TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_NORMALIZENORMALS,				FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE,			D3DMCS_COLOR1 );
	m_pD3DDevice->SetRenderState( D3DRS_SPECULARMATERIALSOURCE,			D3DMCS_COLOR2 );
	m_pD3DDevice->SetRenderState( D3DRS_AMBIENTMATERIALSOURCE,			D3DMCS_MATERIAL );
	m_pD3DDevice->SetRenderState( D3DRS_EMISSIVEMATERIALSOURCE,			D3DMCS_MATERIAL );
	m_pD3DDevice->SetRenderState( D3DRS_VERTEXBLEND,					D3DVBF_DISABLE );
	m_pD3DDevice->SetRenderState( D3DRS_CLIPPLANEENABLE,				0x00000000 );
	m_pD3DDevice->SetRenderState( D3DRS_POINTSIZE,						0 );
	m_pD3DDevice->SetRenderState( D3DRS_POINTSIZE_MIN,					One );
	m_pD3DDevice->SetRenderState( D3DRS_POINTSPRITEENABLE,				FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_POINTSCALEENABLE,				FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_POINTSCALE_A,					One );
	m_pD3DDevice->SetRenderState( D3DRS_POINTSCALE_B,					Zero );
	m_pD3DDevice->SetRenderState( D3DRS_POINTSCALE_C,					Zero );
	m_pD3DDevice->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS,			FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_MULTISAMPLEMASK,				0xFFFFFFFF );
	m_pD3DDevice->SetRenderState( D3DRS_PATCHEDGESTYLE,					D3DPATCHEDGE_DISCRETE );
	m_pD3DDevice->SetRenderState( D3DRS_DEBUGMONITORTOKEN,				D3DDMT_ENABLE );
	m_pD3DDevice->SetRenderState( D3DRS_POINTSIZE_MAX,					PointSize );
	m_pD3DDevice->SetRenderState( D3DRS_INDEXEDVERTEXBLENDENABLE,		FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_TWEENFACTOR,					Zero );
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP,						D3DBLENDOP_ADD );
	m_pD3DDevice->SetRenderState( D3DRS_POSITIONDEGREE,					D3DDEGREE_CUBIC );
	m_pD3DDevice->SetRenderState( D3DRS_NORMALDEGREE,					D3DDEGREE_LINEAR );
	m_pD3DDevice->SetRenderState( D3DRS_SCISSORTESTENABLE,				FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_SLOPESCALEDEPTHBIAS,			0 );
	m_pD3DDevice->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE,			FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_MINTESSELLATIONLEVEL,			One );
	m_pD3DDevice->SetRenderState( D3DRS_MAXTESSELLATIONLEVEL,			One );
	m_pD3DDevice->SetRenderState( D3DRS_ADAPTIVETESS_X,					Zero );
	m_pD3DDevice->SetRenderState( D3DRS_ADAPTIVETESS_Y,					Zero );
	m_pD3DDevice->SetRenderState( D3DRS_ADAPTIVETESS_Z,					One );
	m_pD3DDevice->SetRenderState( D3DRS_ADAPTIVETESS_W,					Zero );
	m_pD3DDevice->SetRenderState( D3DRS_ENABLEADAPTIVETESSELLATION,		FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_TWOSIDEDSTENCILMODE,			FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_CCW_STENCILFAIL,				D3DSTENCILOP_KEEP );
	m_pD3DDevice->SetRenderState( D3DRS_CCW_STENCILZFAIL,				D3DSTENCILOP_KEEP );
	m_pD3DDevice->SetRenderState( D3DRS_CCW_STENCILPASS,				D3DSTENCILOP_KEEP );
	m_pD3DDevice->SetRenderState( D3DRS_CCW_STENCILFUNC,				D3DCMP_ALWAYS );
	m_pD3DDevice->SetRenderState( D3DRS_COLORWRITEENABLE1,				0x0000000F );
	m_pD3DDevice->SetRenderState( D3DRS_COLORWRITEENABLE2,				0x0000000F );
	m_pD3DDevice->SetRenderState( D3DRS_COLORWRITEENABLE3,				0x0000000F );
	m_pD3DDevice->SetRenderState( D3DRS_BLENDFACTOR,					0xFFFFFFFF );
	m_pD3DDevice->SetRenderState( D3DRS_SRGBWRITEENABLE,				0 );
	m_pD3DDevice->SetRenderState( D3DRS_DEPTHBIAS,						0 );
	m_pD3DDevice->SetRenderState( D3DRS_WRAP0,							0 );
	m_pD3DDevice->SetRenderState( D3DRS_WRAP1,							0 );
	m_pD3DDevice->SetRenderState( D3DRS_WRAP2,							0 );
	m_pD3DDevice->SetRenderState( D3DRS_WRAP3,							0 );
	m_pD3DDevice->SetRenderState( D3DRS_WRAP4,							0 );
	m_pD3DDevice->SetRenderState( D3DRS_WRAP5,							0 );
	m_pD3DDevice->SetRenderState( D3DRS_WRAP6,							0 );
	m_pD3DDevice->SetRenderState( D3DRS_WRAP7,							0 );
	m_pD3DDevice->SetRenderState( D3DRS_WRAP8,							0 );
	m_pD3DDevice->SetRenderState( D3DRS_WRAP9,							0 );
	m_pD3DDevice->SetRenderState( D3DRS_WRAP10,							0 );
	m_pD3DDevice->SetRenderState( D3DRS_WRAP11,							0 );
	m_pD3DDevice->SetRenderState( D3DRS_WRAP12,							0 );
	m_pD3DDevice->SetRenderState( D3DRS_WRAP13,							0 );
	m_pD3DDevice->SetRenderState( D3DRS_WRAP14,							0 );
	m_pD3DDevice->SetRenderState( D3DRS_WRAP15,							0 );
	m_pD3DDevice->SetRenderState( D3DRS_SEPARATEALPHABLENDENABLE,		FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLENDALPHA,					D3DBLEND_ONE );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLENDALPHA,					D3DBLEND_ZERO );
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOPALPHA,					D3DBLENDOP_ADD );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::ResetSamplerState( void )
{
	Float fBias		= -1.0f;
	Uint32 Bias		= *((Uint32*)&fBias);

	for ( Sint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		m_pD3DDevice->SetSamplerState( i, D3DSAMP_ADDRESSU,			D3DTADDRESS_CLAMP );
		m_pD3DDevice->SetSamplerState( i, D3DSAMP_ADDRESSV,			D3DTADDRESS_CLAMP );
		m_pD3DDevice->SetSamplerState( i, D3DSAMP_ADDRESSW,			D3DTADDRESS_CLAMP );
		m_pD3DDevice->SetSamplerState( i, D3DSAMP_BORDERCOLOR,		0x00000000 );
		m_pD3DDevice->SetSamplerState( i, D3DSAMP_MAGFILTER,		D3DTEXF_POINT );
		m_pD3DDevice->SetSamplerState( i, D3DSAMP_MINFILTER,		D3DTEXF_POINT );
		m_pD3DDevice->SetSamplerState( i, D3DSAMP_MIPFILTER,		D3DTEXF_NONE );
		m_pD3DDevice->SetSamplerState( i, D3DSAMP_MIPMAPLODBIAS,	Bias );
		m_pD3DDevice->SetSamplerState( i, D3DSAMP_MAXMIPLEVEL,		0 );
		m_pD3DDevice->SetSamplerState( i, D3DSAMP_SRGBTEXTURE,		0 );
		m_pD3DDevice->SetSamplerState( i, D3DSAMP_ELEMENTINDEX,		0 );
		m_pD3DDevice->SetSamplerState( i, D3DSAMP_DMAPOFFSET,		0 );
		m_pD3DDevice->SetSamplerState( i, D3DSAMP_MAXANISOTROPY,	m_Caps.MaxAnisotropy );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::ResetTextureStageState( void )
{
	Float fZero		= 0.0f;
	Uint32 Zero		= *((Uint32*)&fZero);

	for ( Sint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		m_pD3DDevice->SetTextureStageState( i, D3DTSS_COLOROP,					D3DTOP_DISABLE );
		m_pD3DDevice->SetTextureStageState( i, D3DTSS_COLORARG1,				D3DTA_TEXTURE );
		m_pD3DDevice->SetTextureStageState( i, D3DTSS_COLORARG2,				D3DTA_CURRENT );
		m_pD3DDevice->SetTextureStageState( i, D3DTSS_ALPHAOP,					D3DTOP_DISABLE );
		m_pD3DDevice->SetTextureStageState( i, D3DTSS_ALPHAARG1,				D3DTA_TEXTURE );
		m_pD3DDevice->SetTextureStageState( i, D3DTSS_ALPHAARG2,				D3DTA_CURRENT );
		m_pD3DDevice->SetTextureStageState( i, D3DTSS_BUMPENVMAT00,				Zero );
		m_pD3DDevice->SetTextureStageState( i, D3DTSS_BUMPENVMAT01,				Zero );
		m_pD3DDevice->SetTextureStageState( i, D3DTSS_BUMPENVMAT10,				Zero );
		m_pD3DDevice->SetTextureStageState( i, D3DTSS_BUMPENVMAT11,				Zero );
		m_pD3DDevice->SetTextureStageState( i, D3DTSS_BUMPENVLSCALE,			Zero );
		m_pD3DDevice->SetTextureStageState( i, D3DTSS_BUMPENVLOFFSET,			Zero );
		m_pD3DDevice->SetTextureStageState( i, D3DTSS_TEXCOORDINDEX,			i );
		m_pD3DDevice->SetTextureStageState( i, D3DTSS_TEXTURETRANSFORMFLAGS,	D3DTTFF_DISABLE );
		m_pD3DDevice->SetTextureStageState( i, D3DTSS_COLORARG0,				D3DTA_CURRENT );
		m_pD3DDevice->SetTextureStageState( i, D3DTSS_ALPHAARG0,				D3DTA_CURRENT );
		m_pD3DDevice->SetTextureStageState( i, D3DTSS_RESULTARG,				D3DTA_CURRENT );
		m_pD3DDevice->SetTextureStageState( i, D3DTSS_CONSTANT,					0x00000000 );
	}

	// 初期値
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetHardwareShadowATI( Bool IsEnable, Bool IsGet4 )
{
	if ( IsEnable )
	{
		m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_SHADOW, D3DSAMP_MIPMAPLODBIAS, IsGet4 ? FOURCC_GET4 : FOURCC_GET1 );
	}
	else
	{
		Float fBias = -1.0f;
		Uint32 Bias = *((Uint32*)&fBias);
		m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_SHADOW, D3DSAMP_MIPMAPLODBIAS, Bias );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::ResetShader( void )
{
	m_pD3DDevice->SetVertexShader( NULL );
	m_pD3DDevice->SetPixelShader( NULL );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::Start2D( Bool IsMultiTexture )
{
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_COLOR, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_COLOR, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_LIGHT, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_LIGHT, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );

	m_pD3DDevice->SetTextureStageState( TEXTURE_STAGE_LIGHT, D3DTSS_COLOROP, IsMultiTexture ? D3DTOP_MODULATE2X : D3DTOP_DISABLE );
	m_pD3DDevice->SetTextureStageState( TEXTURE_STAGE_LIGHT, D3DTSS_ALPHAOP, D3DTOP_DISABLE );

	m_pD3DDevice->SetTextureStageState( TEXTURE_STAGE_ENVIRONMENT, D3DTSS_COLOROP, D3DTOP_DISABLE );
	m_pD3DDevice->SetTextureStageState( TEXTURE_STAGE_ENVIRONMENT, D3DTSS_ALPHAOP, D3DTOP_DISABLE );

	m_pD3DDevice->SetRenderState( D3DRS_SPECULARENABLE, false );
	m_pD3DDevice->SetRenderState( D3DRS_FOGENABLE, false );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::Start3D( void )
{
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_COLOR, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_COLOR, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_LIGHT, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_LIGHT, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_ENVIRONMENT, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_ENVIRONMENT, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_SPECULAR, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_SPECULAR, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_NORMAL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_NORMAL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_SHADOW, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_SHADOW, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_DEPTH, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_DEPTH, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_TOON, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_TOON, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );

	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_DEPTH, D3DSAMP_ADDRESSU, D3DTEXF_LINEAR );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_DEPTH, D3DSAMP_ADDRESSV, D3DTEXF_LINEAR );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_TOON, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	m_pD3DDevice->SetSamplerState( TEXTURE_STAGE_TOON, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );

	m_pD3DDevice->SetTextureStageState( TEXTURE_STAGE_LIGHT, D3DTSS_COLOROP, D3DTOP_MODULATE2X );
	m_pD3DDevice->SetTextureStageState( TEXTURE_STAGE_LIGHT, D3DTSS_ALPHAOP, D3DTOP_DISABLE );

	m_pD3DDevice->SetTextureStageState( TEXTURE_STAGE_ENVIRONMENT, D3DTSS_COLOROP, D3DTOP_MODULATE2X );
	m_pD3DDevice->SetTextureStageState( TEXTURE_STAGE_ENVIRONMENT, D3DTSS_ALPHAOP, D3DTOP_DISABLE );

	m_pD3DDevice->SetRenderState( D3DRS_SPECULARENABLE, true );
	m_pD3DDevice->SetRenderState( D3DRS_FOGENABLE, false );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetIndexBuffer( CIndexBuffer *pBuffer )
{
	IDirect3DIndexBuffer9 *pIndex;

	pBuffer->GetInterface( pIndex );
	m_pD3DDevice->SetIndices( pIndex );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetVertexBuffer( CVertexBuffer *pBufferTbl[], Sint32 Count )
{
	IDirect3DVertexBuffer9 *pVertex;
	Uint32 Size;

	for ( Sint32 i = 0; i < Count; i++ )
	{
		if ( pBufferTbl[i] != NULL )
		{
			pBufferTbl[i]->GetInterface( pVertex, Size );
			m_pD3DDevice->SetStreamSource( i, pVertex, 0, Size );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetVertexStream( CVertexLayout *pStream )
{
	IDirect3DVertexDeclaration9 *pDeclaration;

	pStream->GetInterface( pDeclaration ); 
	m_pD3DDevice->SetVertexDeclaration( pDeclaration );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DI CRender::GetBackBufferSize( void )
{
	D3DSURFACE_DESC Desc;
	m_pBackBuffer->GetDesc( &Desc );

	return Math::Point2DI( Desc.Width, Desc.Height );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CGraphicCard *CRender::GetGraphicCardPointer( void )
{
	return m_pGraphicCard;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::ResetDevice( Bool IsChange )
{
	//-------------------------------------------------------
	// デバイスがまだ生成されていない場合は終了
	//-------------------------------------------------------
	if ( m_pD3DDevice == NULL ) return;

	//-------------------------------------------------------
	// スクリーンモードの変更でない時、デバイスが問題ないなら終了
	//-------------------------------------------------------
	if ( !IsChange && (m_pD3DDevice->TestCooperativeLevel() == D3D_OK) ) return;

	//-------------------------------------------------------
	// プレゼンテーションパラメータ取得
	//-------------------------------------------------------
	Bool IsWindow = false;
	m_pCore->GetScreenData( NULL, NULL, &IsWindow );
	m_AcitivePresentParam = GetGraphicCardPointer()->MakePresentParameters( IsWindow, GetGraphicCardPointer()->IsHightColorMode(), m_IsLockEnableBackBuffer, m_IsWaitVSync );

	//-------------------------------------------------------
	// ビデオメモリ内のリソース全解放
	//-------------------------------------------------------
	// ユーザー指定コールバック
	if ( m_pCallbackReset != NULL )
	{
		m_pCallbackReset();
	}

	// バッファ解除
	SetRenderTarget( NULL );
	SetDepthBuffer( NULL );

	// レンダラー
	OnLostDevice();

	// レンダリングターゲット
	SAFE_RELEASE( m_pBackBuffer );

	//-------------------------------------------------------
	// デバイスのリセット
	//-------------------------------------------------------
	if FAILED( m_pD3DDevice->Reset( &m_AcitivePresentParam ) )
	{
		m_pCore->MsgBox( MB_ICONERROR, "ERROR", "デバイスの復帰に失敗" );
		return;
	}

	//-------------------------------------------------------
	// ビデオメモリ内のリソース全復旧
	//-------------------------------------------------------
	// レンダリングターゲット
	m_pD3DDevice->GetRenderTarget( 0, &m_pBackBuffer );

	// レンダラー
	OnResetDevice();

	// ユーザー指定コールバック
	if ( m_pCallbackRestore != NULL )
	{
		m_pCallbackRestore();
	}

	//-------------------------------------------------------
	// ステート
	//-------------------------------------------------------
	ResetRenderState();
	ResetSamplerState();
	ResetTextureStageState();
	GetGraphicCardPointer()->CreateSurfaceFormatTable();

	//-------------------------------------------------------
	// 変換行列
	//-------------------------------------------------------
	D3DXMATRIX Mtx;
	D3DXMatrixIdentity( &Mtx );
    m_pD3DDevice->SetTransform( D3DTS_WORLD,      &Mtx );
    m_pD3DDevice->SetTransform( D3DTS_VIEW,       &Mtx );
    m_pD3DDevice->SetTransform( D3DTS_PROJECTION, &Mtx );
    m_pD3DDevice->SetTransform( D3DTS_TEXTURE0,   &Mtx );
    m_pD3DDevice->SetTransform( D3DTS_TEXTURE1,   &Mtx );
    m_pD3DDevice->SetTransform( D3DTS_TEXTURE2,   &Mtx );
    m_pD3DDevice->SetTransform( D3DTS_TEXTURE3,   &Mtx );
    m_pD3DDevice->SetTransform( D3DTS_TEXTURE4,   &Mtx );
    m_pD3DDevice->SetTransform( D3DTS_TEXTURE5,   &Mtx );
    m_pD3DDevice->SetTransform( D3DTS_TEXTURE6,   &Mtx );
    m_pD3DDevice->SetTransform( D3DTS_TEXTURE7,   &Mtx );

	//-------------------------------------------------------
	// ステート
	//-------------------------------------------------------
	SRenderState &Temp = m_RenderState[m_RenderStatePos];
	// 前回のステートで再設定
	SetDrawType( Temp.DrawType );
	SetCullType( Temp.CullType );
	SetDepthTestEnable( Temp.IsDepthTestEnable );
	SetDepthWriteEnable( Temp.IsDepthWriteEnable );
	SetAlphaTestEnable( Temp.IsAlphaTestEnable );
	SetAlphaBoundary( Temp.AlphaBoundary );
	for ( Sint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		SetTexture( (eTextureStage)i, Temp.pTextureTbl[i] );
		SetTextureFilterType( (eTextureStage)i, Temp.FilterType[i] );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetCallbackDeviceReset( void (*pCallback)( void ) )
{
	m_pCallbackReset = pCallback;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetCallbackDeviceRestore( void (*pCallback)( void ) )
{
	m_pCallbackRestore = pCallback;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void *CRender::GetDriverDevicePointer( void )
{
	return m_pD3DDevice;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::Clear( CColor Color )
{
	return SUCCEEDED( m_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET, (D3DCOLOR)Color, 1.0f, 0 ) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::ClearDepthStencil( void )
{
	if ( m_pDepthBuffer != NULL )
	{
		if ( m_pDepthBuffer->IsStencilFormat() )
		{
			return SUCCEEDED( m_pD3DDevice->Clear( 0, NULL, D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0 ) );
		}
		else
		{
			return SUCCEEDED( m_pD3DDevice->Clear( 0, NULL, D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0 ) );
		}
	}
	return D3D_OK;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::Refresh( HWND hWnd )
{
	//----------------------------------------------------------
	// 画面更新
	//----------------------------------------------------------
	switch ( m_pD3DDevice->Present( NULL, NULL, hWnd, NULL ) )
	{
		// ドライバ内部の意味不明なエラー
	case D3DERR_DRIVERINTERNALERROR:
		m_pCore->Exit();
		break;
		// デバイスロスト
	case D3DERR_DEVICELOST:
		switch ( m_pD3DDevice->TestCooperativeLevel() )
		{
			// デバイスロスト
		case D3DERR_DEVICELOST:
			::SleepEx( 10, true );
			break;
			// デバイスロスト：リセット可能状態
		case D3DERR_DEVICENOTRESET:
			ResetDevice( false );
			break;
		}
		break;
	}

	ResetRenderTarget();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CRender::GetRestVRAM( void )
{
	return toF(m_pD3DDevice->GetAvailableTextureMem()) / 1024.0f / 1024.0f;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::UpdateUsedVRAM( void )
{
	Float fUsedVRAM = m_fRestVRAM - GetRestVRAM();
	if ( m_fUsedVRAM < fUsedVRAM )
	{
		m_fUsedVRAM = fUsedVRAM;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::IsSupportedPS20( void )
{
	return m_Caps.PixelShaderVersion >= D3DPS_VERSION( 2, 0 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::IsSupportedPS30( void )
{
	return m_Caps.PixelShaderVersion >= D3DPS_VERSION( 3, 0 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::IsPixelShaderInstructionSupport( Sint32 Count )
{
	return m_Caps.MaxPShaderInstructionsExecuted >= (Uint32)Count;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CRender::GetPixelShaderSlot( void )
{
	return m_Caps.MaxPShaderInstructionsExecuted;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CRender::GetMRTs( void )
{
	return m_Caps.NumSimultaneousRTs >= 4 ? 4 : m_Caps.NumSimultaneousRTs;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Rect2DI CRender::GetViewport( void )
{
	return Math::Rect2DI( m_Viewport.X, m_Viewport.Y, m_Viewport.Width, m_Viewport.Height );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetViewport( const Math::Rect2DI &Dst )
{
	m_Viewport.X      = Dst.x;
	m_Viewport.Y      = Dst.y;
	m_Viewport.Width  = Dst.w;
	m_Viewport.Height = Dst.h;
	m_pD3DDevice->SetViewport( &m_Viewport );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CRender::GetActiveRefreshRate( void )
{
	return m_AcitivePresentParam.FullScreen_RefreshRateInHz;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HWND CRender::GetCreationWindow( void )
{
	D3DDEVICE_CREATION_PARAMETERS Param;
	m_pD3DDevice->GetCreationParameters( &Param );
	return Param.hFocusWindow;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetScissorRect( const Math::Rect2DI *pRect )
{
	if ( pRect != NULL )
	{
		RECT Scissor = { pRect->x, pRect->y, pRect->x + pRect->w, pRect->y + pRect->h };
		m_pD3DDevice->SetScissorRect( &Scissor );
		m_pD3DDevice->SetRenderState( D3DRS_SCISSORTESTENABLE, true );
	}
	else
	{
		m_pD3DDevice->SetRenderState( D3DRS_SCISSORTESTENABLE, false );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetColorWriteEnable( Bool IsAlpha, Bool IsRed, Bool IsGreen, Bool IsBlue )
{
	Sint32 Flag = 0;

	if ( IsAlpha ) Flag |= D3DCOLORWRITEENABLE_ALPHA;
	if ( IsRed   ) Flag |= D3DCOLORWRITEENABLE_RED;
	if ( IsGreen ) Flag |= D3DCOLORWRITEENABLE_GREEN;
	if ( IsBlue  ) Flag |= D3DCOLORWRITEENABLE_BLUE;

	m_pD3DDevice->SetRenderState( D3DRS_COLORWRITEENABLE, Flag );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::AbortAllScene( void )
{
	Scene::CSceneManagerBase *pScene = (Scene::CSceneManagerBase*)m_pSceneMgr->GetTop();
	while ( pScene != NULL )
	{
		pScene->Abort();
		pScene = (Scene::CSceneManagerBase*)pScene->GetNext();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
COcclusion *CRender::CeateOcclusion( void )
{
	Thread::CAutoLock Lock( m_CS );

	return new COcclusion( this );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::OnLostDevice( void )
{
	m_pFont->OnLostDevice();

	m_pTextureMgr->OnLostDevice();

	m_pVertexStreamMgr->OnLostDevice();
	m_pVertexBufferMgr->OnLostDevice();
	m_pIndexBufferMgr->OnLostDevice();
	m_pShaderMgr->OnLostDevice();

	m_pListPrimitive2DMgr->OnLostDevice();
	m_pListPrimitive3DMgr->OnLostDevice();

	m_pSceneMgr->OnLostDevice();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::OnResetDevice( void )
{
	m_pTextureMgr->OnResetDevice();

	m_pShaderMgr->OnResetDevice();
	m_pVertexStreamMgr->OnResetDevice();
	m_pVertexBufferMgr->OnResetDevice();
	m_pIndexBufferMgr->OnResetDevice();

	m_pListPrimitive2DMgr->OnResetDevice();
	m_pListPrimitive3DMgr->OnResetDevice();

	m_pSceneMgr->OnResetDevice();

	m_pFont->OnResetDevice();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CRender::GetSize( Sint32 Flag )
{
	Sint32 Size = 0;

	if ( Flag & VERTEX_ELEMENT_PRIMITIVE   ) Size += sizeof(SVertex2D);
	if ( Flag & VERTEX_ELEMENT_SPRITE      ) Size += sizeof(SVertex2DTex);
	if ( Flag & VERTEX_ELEMENT_3DBASE      ) Size += sizeof(SVertex3DBase);
	if ( Flag & VERTEX_ELEMENT_3DTEXTURE   ) Size += sizeof(SVertex3DTexture);
	if ( Flag & VERTEX_ELEMENT_3DLIGHT     ) Size += sizeof(SVertex3DLight);
	if ( Flag & VERTEX_ELEMENT_3DBUMP      ) Size += sizeof(SVertex3DBump);
	if ( Flag & VERTEX_ELEMENT_3DANIMATION ) Size += sizeof(SVertex3DAnimation);

	return Size;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::DrawPrimitive( ePrimitiveType PrimitiveType, Sint32 PrimitiveCount )
{
	if ( PrimitiveCount == 0 ) return false;

	HRESULT hr = m_pD3DDevice->DrawPrimitive( g_PrimitiveTypeTbl[PrimitiveType], 0, PrimitiveCount );

	return SUCCEEDED( hr );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::DrawIndexedPrimitive( ePrimitiveType PrimitiveType, Sint32 VertexCount, Sint32 PrimitiveCount )
{
	if ( PrimitiveCount == 0 ) return false;

	HRESULT hr = m_pD3DDevice->DrawIndexedPrimitive( g_PrimitiveTypeTbl[PrimitiveType], 0, 0, VertexCount, 0, PrimitiveCount );

	return SUCCEEDED( hr );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::DrawMesh( Sint32 VertexStart, Sint32 VertexCount, Sint32 IndexStart, Sint32 PrimitiveCount )
{
	if ( PrimitiveCount == 0 ) return false;

	HRESULT hr = m_pD3DDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, VertexStart, VertexCount, IndexStart, PrimitiveCount );

	return SUCCEEDED( hr );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::ResetRenderTarget( void )
{
	// バックバッファ
	m_pD3DDevice->SetRenderTarget( 0, m_pBackBuffer );

	Sint32 Max = GetMRTs();
	for ( Sint32 i = 1; i < Max; i++ )
	{
		m_pD3DDevice->SetRenderTarget( i, NULL );
	}

	// ビューポートをサーフェイスに合わせる
	D3DSURFACE_DESC Desc;
	m_pBackBuffer->GetDesc( &Desc );
	m_Viewport.X      = 0;
	m_Viewport.Y      = 0;
	m_Viewport.Width  = Desc.Width;
	m_Viewport.Height = Desc.Height;
	m_pD3DDevice->SetViewport( &m_Viewport );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::SetRenderTarget( ITexture *pTexture )
{
	if ( pTexture == NULL )
	{
		return ResetRenderTarget();
	}
	else
	{
		return SetRenderTarget( pTexture, NULL, NULL, NULL );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::SetRenderTarget( ITexture *pTexture0, ITexture *pTexture1, ITexture *pTexture2, ITexture *pTexture3 )
{
	if ( (pTexture0 == NULL) || pTexture0->IsInvalid() )
	{
		return ResetRenderTarget();
	}
	else
	{
		CTextureInterface *pTexTbl[] = {
			(CTextureInterface*)pTexture0,
			(CTextureInterface*)pTexture1,
			(CTextureInterface*)pTexture2,
			(CTextureInterface*)pTexture3,
		};

		// レンダリングターゲット設定
		Sint32 Max = GetMRTs();
		for ( Sint32 i = 0; i < Max; i++ )
		{
			IDirect3DSurface9 *pTarget = NULL;

			// レンダリングターゲット
			if ( (pTexTbl[i] == NULL) || pTexTbl[i]->IsInvalid() || (pTexTbl[i]->GetType() != TEXTURE_TYPE_TARGET) )
			{
				m_pD3DDevice->SetRenderTarget( i, NULL );
			}
			else
			{
				pTexTbl[i]->GetSurface( pTarget, CUBEMAP_FACE_NONE );
				m_pD3DDevice->SetRenderTarget( i, pTarget );

				// ビューポートをサーフェイスに合わせる
				if ( i == 0 )
				{
					D3DSURFACE_DESC Desc;
					pTarget->GetDesc( &Desc );
					m_Viewport.X      = 0;
					m_Viewport.Y      = 0;
					m_Viewport.Width  = Desc.Width;
					m_Viewport.Height = Desc.Height;
					m_pD3DDevice->SetViewport( &m_Viewport );
				}
			}

			SAFE_RELEASE( pTarget );
		}
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::SetDepthBuffer( ITexture *pTexture )
{
	HRESULT hr;

	// バックアップ
	m_pDepthBuffer = (CTextureInterface*)pTexture;

	if ( (m_pDepthBuffer == NULL) || m_pDepthBuffer->IsInvalid() || (m_pDepthBuffer->GetType() != TEXTURE_TYPE_DEPTH))
	{
		m_pDepthBuffer = NULL;
		hr = m_pD3DDevice->SetDepthStencilSurface( NULL );
	}
	else
	{
		IDirect3DSurface9 *pTarget;
		m_pDepthBuffer->GetSurface( pTarget, CUBEMAP_FACE_NONE );
		hr = m_pD3DDevice->SetDepthStencilSurface( pTarget );
		SAFE_RELEASE( pTarget );
	}

	return SUCCEEDED( hr );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Scene::ICustomizedSceneManager *CRender::CreateCustomizedSceneManager( Sint32 QueMax )
{
	Thread::CAutoLock Lock( m_CS );

	Scene::ICustomizedSceneManager *pScene = new Scene::CCustomizedSceneManager( this, m_pSceneMgr, QueMax );
	if ( pScene != NULL )
	{
		return pScene;
	}

	static Scene::NullManager Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Scene::ISceneManager *CRender::CreateSceneManager( Sint32 QueMax, Bool IsPixelShaderEnable )
{
	if ( Shader::ShaderManager::IsDfaulteShaderEnable() )
	{
		Thread::CAutoLock Lock( m_CS );

		if ( IsSupportedPS20() && IsPixelShaderEnable )
		{
			Scene::ISceneManager *pScene = new Scene::CSceneManager_Shader( this, m_pSceneMgr, QueMax );
			if ( pScene != NULL )
			{
				return pScene;
			}
		}
		else
		{
			Scene::ISceneManager *pScene = new Scene::CSceneManager_Fixed( this, m_pSceneMgr, QueMax );
			if ( pScene != NULL )
			{
				return pScene;
			}
		}
	}
	else
	{
		GetGraphicCardPointer()->GetCorePointer()->MsgBox( MB_ICONERROR, "CreateSceneManager", "シェーダープラグインがないのでSceneManagerの生成が出来ませんでした" ); 
	}

	static Scene::NullManager Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::ActivateScene( Scene::CSceneManagerBase *pScene )
{
	if ( m_pActiveScene == NULL )
	{
		if ( pScene->IsInvalid() )
		{
			return false;
		}
		else
		{
			m_pActiveScene = pScene;
		}
		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::DeActivateScene( Scene::CSceneManagerBase *pScene )
{
	if ( m_pActiveScene == pScene )
	{
		m_pActiveScene = NULL;
		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Scene::CSceneManagerBase *CRender::GetManagerPointer( void )
{
	return m_pActiveScene;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::Begin( void )
{
	m_pD3DDevice->BeginScene();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::End( void )
{
	m_pD3DDevice->EndScene();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CVertexLayout *CRender::CreateVertexStreamDirect( void )
{
	Thread::CAutoLock Lock( m_CS );

	return new CVertexLayout( m_pVertexStreamMgr );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CVertexLayout *CRender::CreateVertexStream( Sint32 Flag )
{
	Thread::CAutoLock Lock( m_CS );

	D3DVERTEXELEMENT9 ElementEnd = D3DDECL_END();
	D3DVERTEXELEMENT9 VertexElement[32];
	Sint32 Offset = 0;

	// ポストエフェクト
	if ( (Flag & VERTEX_ELEMENT_POSTEFFECT) != 0 )
	{
		Sint32 Cnt = sizeof(g_VertexElementPostEffect) / sizeof(D3DVERTEXELEMENT9);
		for ( Sint32 i = 0; i < Cnt; i++ )
		{
			VertexElement[Offset] = g_VertexElementPostEffect[i];
			Offset++;
		}
	}
	// ２Ｄ
	ef ( (Flag & VERTEX_ELEMENT_PRIMITIVE) != 0 )
	{
		Sint32 Cnt = sizeof(g_VertexElement2D) / sizeof(D3DVERTEXELEMENT9);
		for ( Sint32 i = 0; i < Cnt; i++ )
		{
			VertexElement[Offset] = g_VertexElement2D[i];
			Offset++;
		}
	}
	// ２Ｄ
	ef ( (Flag & VERTEX_ELEMENT_SPRITE) != 0 )
	{
		Sint32 Cnt = sizeof(g_VertexElementTex2D) / sizeof(D3DVERTEXELEMENT9);
		for ( Sint32 i = 0; i < Cnt; i++ )
		{
			VertexElement[Offset] = g_VertexElementTex2D[i];
			Offset++;
		}
	}
	// ３Ｄ座標
	ef ( (Flag & VERTEX_ELEMENT_3DBASE) != 0 )
	{
		Sint32 Cnt = sizeof(g_VertexElement3DBase) / sizeof(D3DVERTEXELEMENT9);
		for ( Sint32 i = 0; i < Cnt; i++ )
		{
			VertexElement[Offset] = g_VertexElement3DBase[i];
			Offset++;
		}

		// テクスチャ
		if ( (Flag & VERTEX_ELEMENT_3DTEXTURE) != 0 )
		{
			Sint32 Cnt = sizeof(g_VertexElement3DTexture) / sizeof(D3DVERTEXELEMENT9);
			for ( Sint32 i = 0; i < Cnt; i++ )
			{
				VertexElement[Offset] = g_VertexElement3DTexture[i];
				Offset++;
			}
		}

		// ライト
		if ( (Flag & VERTEX_ELEMENT_3DLIGHT) != 0 )
		{
			Sint32 Cnt = sizeof(g_VertexElement3DLight) / sizeof(D3DVERTEXELEMENT9);
			for ( Sint32 i = 0; i < Cnt; i++ )
			{
				VertexElement[Offset] = g_VertexElement3DLight[i];
				Offset++;
			}
		}

		// ３Ｄバンプ
		if ( (Flag & VERTEX_ELEMENT_3DBUMP) != 0 )
		{
			Sint32 Cnt = sizeof(g_VertexElement3DBump) / sizeof(D3DVERTEXELEMENT9);
			for ( Sint32 i = 0; i < Cnt; i++ )
			{
				VertexElement[Offset] = g_VertexElement3DBump[i];
				Offset++;
			}
		}

		// ３Ｄアニメーション
		if ( (Flag & VERTEX_ELEMENT_3DANIMATION) != 0 )
		{
			Sint32 Cnt = sizeof(g_VertexElement3DAnimation) / sizeof(D3DVERTEXELEMENT9);
			for ( Sint32 i = 0; i < Cnt; i++ )
			{
				VertexElement[Offset] = g_VertexElement3DAnimation[i];
				Offset++;
			}
		}
	}

	// 終端
	VertexElement[Offset] = ElementEnd;
	Offset++;

	// ストリーム定義生成
	CVertexLayout *pData = new CVertexLayout( m_pVertexStreamMgr );
	if ( !pData->Create( VertexElement ) )
	{
		SAFE_RELEASE( pData );
		return NULL;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CVertexBuffer *CRender::CreateVertexBuffer( Sint32 Count, Sint32 VertexSize, Bool IsDynamic )
{
	Thread::CAutoLock Lock( m_CS );

	if ( !m_IsDynamicBufferEnable )
	{
		IsDynamic = false;
	}

	CVertexBuffer *pData = new CVertexBuffer( m_pVertexBufferMgr );
	if ( !pData->Create( Count, VertexSize, IsDynamic ) )
	{
		SAFE_RELEASE( pData );
		return NULL;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CIndexBuffer *CRender::CreateIndexBuffer( Sint32 Count, Bool IsDynamic )
{
	Thread::CAutoLock Lock( m_CS );

	if ( !m_IsDynamicBufferEnable )
	{
		IsDynamic = false;
	}

	CIndexBuffer *pData = new CIndexBuffer( m_pIndexBufferMgr );
	if ( !pData->Create( Count, IsDynamic ) )
	{
		SAFE_RELEASE( pData );
		return NULL;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Shader::IShader *CRender::CreateShaderFromMemory( const void *pShader, Sint32 Size, Bool IsCompiled )
{
	Thread::CAutoLock Lock( m_CS );

	Shader::CShader *pData = new Shader::CShader( m_pShaderMgr );
	if ( !pData->CreateFromMemory( pShader, Size, IsCompiled ) )
	{
		SAFE_RELEASE( pData );
		return NULL;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Shader::IShader *CRender::CreateShaderFromFile( const char *pFile, Bool IsCompiled )
{
	Thread::CAutoLock Lock( m_CS );

	File::IFileManager *pFileMgr = GetGraphicCardPointer()->GetCorePointer()->GetFileMgrPointer();
	Shader::CShader *pData = NULL;

	void *pShader;
	Sint32 Size;
	if ( pFileMgr->Load( pFile, &pShader, &Size ) )
	{
		pData = new Shader::CShader( m_pShaderMgr );
		if ( !pData->CreateFromMemory( pShader, Size, IsCompiled ) )
		{
			pFileMgr->Free( pShader );

			SAFE_RELEASE( pData );
			return NULL;
		}

		pFileMgr->Free( pShader );
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Renderer::Object::IPoint2D *CRender::CreatePoint2D( Sint32 PointMax, Bool IsAutoResize, Sint32 ResizeStep )
{
	Thread::CAutoLock Lock( m_CS );

	Renderer::Object::CPoint2D *pData = new Renderer::Object::CPoint2D( this, m_pListPrimitive2DMgr );
	if ( !pData->Create( PointMax, IsAutoResize, ResizeStep ) )
	{
		SAFE_RELEASE( pData );
		static Renderer::Object::NullPoint2D Dummy;
		return &Dummy;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Renderer::Object::ILine2D *CRender::CreateLine2D( Sint32 LineMax, Bool IsAutoResize, Sint32 ResizeStep )
{
	Thread::CAutoLock Lock( m_CS );

	Renderer::Object::CLine2D *pData = new Renderer::Object::CLine2D( this, m_pListPrimitive2DMgr );
	if ( !pData->Create( LineMax, IsAutoResize, ResizeStep ) )
	{
		SAFE_RELEASE( pData );
		static Renderer::Object::NullLine2D Dummy;
		return &Dummy;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Renderer::Object::IPrimitive2D *CRender::CreatePrimitive2D( Sint32 PrimitiveMax, Bool IsAutoResize, Sint32 ResizeStep )
{
	Thread::CAutoLock Lock( m_CS );

	Renderer::Object::CPrimitive2D *pData = new Renderer::Object::CPrimitive2D( this, m_pListPrimitive2DMgr );
	if ( !pData->Create( PrimitiveMax, IsAutoResize, ResizeStep ) )
	{
		SAFE_RELEASE( pData );
		static Renderer::Object::NullPrimitive2D Dummy;
		return &Dummy;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Renderer::Object::ISprite2D *CRender::CreateSprite2D( Sint32 PrimitiveMax, ITexture *pTexture, Bool IsFiltering, Bool IsOffset, Bool IsAutoResize, Sint32 ResizeStep )
{
	Thread::CAutoLock Lock( m_CS );

	Renderer::Object::CSprite2D *pData = new Renderer::Object::CSprite2D( this, m_pListPrimitive2DMgr, pTexture, IsFiltering, IsOffset );
	if ( !pData->Create( PrimitiveMax, IsAutoResize, ResizeStep ) )
	{
		SAFE_RELEASE( pData );
		static Renderer::Object::NullSprite2D Dummy;
		return &Dummy;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Renderer::Object::IFontSprite2D *CRender::CreateFontSprite2DFromFile( const char *pFileName, const char *pExt, Sint32 FontMax, Bool IsAutoResize, Sint32 ResizeStep )
{
	Thread::CAutoLock Lock( m_CS );

	Renderer::Object::CFontSprite2D *pData = new Renderer::Object::CFontSprite2D( this, m_pListPrimitive2DMgr );
	if ( !pData->CreateFromFile( pFileName, pExt, FontMax, IsAutoResize, ResizeStep ) )
	{
		SAFE_RELEASE( pData );
		static Renderer::Object::NullFontSprite2D Dummy;
		return &Dummy;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Renderer::Object::IPoint3D *CRender::CreatePoint3D( Sint32 VertexMax, Bool IsDynamic )
{
	Thread::CAutoLock Lock( m_CS );

	if ( !m_IsDynamicBufferEnable )
	{
		IsDynamic = false;
	}

	Renderer::Object::CPoint3D *pData = new Renderer::Object::CPoint3D( this, m_pListPrimitive3DMgr );
	if ( !pData->Create( VertexMax, IsDynamic ) )
	{
		SAFE_RELEASE( pData );
		static Renderer::Object::NullPoint3D Dummy;
		return &Dummy;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Renderer::Object::ILine3D *CRender::CreateLine3D( Sint32 VertexMax, Bool IsDynamic )
{
	Thread::CAutoLock Lock( m_CS );

	if ( !m_IsDynamicBufferEnable )
	{
		IsDynamic = false;
	}

	Renderer::Object::CLine3D *pData = new Renderer::Object::CLine3D( this, m_pListPrimitive3DMgr );
	if ( !pData->Create( VertexMax, IsDynamic ) )
	{
		SAFE_RELEASE( pData );
		static Renderer::Object::NullLine3D Dummy;
		return &Dummy;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Renderer::Object::IPrimitive3D *CRender::CreatePrimitive3D( Sint32 VertexMax, Sint32 IndexMax, Sint32 VertexFlag, Bool IsDynamicVertex, Bool IsDynamicIndex )
{
	Thread::CAutoLock Lock( m_CS );

	if ( !m_IsDynamicBufferEnable )
	{
		IsDynamicVertex = false;
		IsDynamicIndex = false;
	}

	Renderer::Object::CPrimitive3D *pData = new Renderer::Object::CPrimitive3D( this, m_pListPrimitive3DMgr, false, false );
	if ( !pData->Create( VertexMax, IndexMax, VertexFlag, IsDynamicVertex, IsDynamicIndex ) )
	{
		SAFE_RELEASE( pData );
		static Renderer::Object::NullPrimitive3D Dummy;
		return &Dummy;
	}

	return pData;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Renderer::Object::ISprite3D *CRender::CreateSprite3D( Sint32 SpriteMax, ITexture *pTexture )
{
	Thread::CAutoLock Lock( m_CS );

	Renderer::Object::CSprite3D *pData = new Renderer::Object::CSprite3D( this, m_pListPrimitive3DMgr );
	if ( pData != NULL )
	{
		if ( pData->Create( SpriteMax * 6, SpriteMax * 4, pTexture ) )
		{
			return pData;
		}

		SAFE_RELEASE( pData );
	}

	static Renderer::Object::NullSprite3D Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Renderer::Object::IParticle *CRender::CreateParticle( Sint32 ParticleMax, ITexture *pTexture, eParticleType Type, Bool IsSoftBillboard )
{
	Thread::CAutoLock Lock( m_CS );

	Renderer::Object::CParticle *pData = new Renderer::Object::CParticle( this, m_pListPrimitive3DMgr, IsSoftBillboard );
	if ( pData != NULL )
	{
		if ( pData->Create( ParticleMax * 6, ParticleMax * 4, pTexture, Type ) )
		{
			return pData;
		}

		SAFE_RELEASE( pData );
	}

	static Renderer::Object::NullParticle Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Renderer::Object::IFontSprite3D *CRender::CreateFontSprite3DFromFile( const char *pFileName, const char *pExt, Sint32 FontMax )
{
	Thread::CAutoLock Lock( m_CS );

	Renderer::Object::CFontSprite3D *pData = new Renderer::Object::CFontSprite3D( this, m_pListPrimitive3DMgr );
	if ( pData->CreateFromFile( pFileName, pExt, FontMax ) )
	{
		return pData;
	}

	SAFE_RELEASE( pData );

	static Renderer::Object::NullFontSprite3D Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Renderer::Object::IMapModel *CRender::CreateMapModelFromFile( const char *pFileName )
{
	Thread::CAutoLock Lock( m_CS );

	Renderer::Object::IMapModel *pModel = m_pListMapModelMgr->CreateFromFile( pFileName, this );
	if ( pModel != NULL )
	{
		return pModel;
	}

	static Renderer::Object::NullMapModel Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Renderer::Object::IMapModel *CRender::CreateMapModelFromMemory( const Uint8 *pData, Sint32 Size )
{
	Thread::CAutoLock Lock( m_CS );

	Renderer::Object::IMapModel *pModel = m_pListMapModelMgr->CreateFromMemory( pData, Size, this );
	if ( pModel != NULL )
	{
		return pModel;
	}

	static Renderer::Object::NullMapModel Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Renderer::Object::IModel *CRender::CreateModelFromFile( const char *pFileName )
{
	Thread::CAutoLock Lock( m_CS );

	Renderer::Object::IModel *pModel = m_pListModelMgr->CreateFromFile( pFileName, this );
	if ( pModel != NULL )
	{
		return pModel;
	}

	static Renderer::Object::NullModel Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Renderer::Object::IModel *CRender::CreateModelFromMemory( const Uint8 *pData, Sint32 Size )
{
	Thread::CAutoLock Lock( m_CS );

	Renderer::Object::IModel *pModel = m_pListModelMgr->CreateFromMemory( pData, Size, this );
	if ( pModel != NULL )
	{
		return pModel;
	}

	static Renderer::Object::NullModel Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Renderer::Object::IModel *CRender::CreateModelSkydoom( Float fRadius, CColor TopColor, CColor BottomColor, ITexture *pTexCloud )
{
	Thread::CAutoLock Lock( m_CS );

	Renderer::Object::IModel *pModel = m_pListModelMgr->SceneSkydoom_Create( fRadius, TopColor, BottomColor, pTexCloud, this );
	if ( pModel != NULL )
	{
		return pModel;
	}

	static Renderer::Object::NullModel Dummy;
	return &Dummy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetScissorPrimitive2D( const Math::Rect2DF *pRect )
{
	//------------------------------------------------
	// 仮想画面から実画面へ
	//------------------------------------------------
	if ( pRect != NULL )
	{
		Math::Rect2DF Rc;
		Rc.x = m_pCore->Virtual2RealX( pRect->x ) - 0.5f;
		Rc.y = m_pCore->Virtual2RealX( pRect->y ) - 0.5f;
		Rc.w = m_pCore->Virtual2RealY( pRect->w ) - 0.5f;
		Rc.h = m_pCore->Virtual2RealY( pRect->h ) - 0.5f;
		Rc.w += 1.0f;
		Rc.h += 1.0f;
		m_pListPrimitive2DMgr->SetScissoring( &Rc );
	}
	else
	{
		m_pListPrimitive2DMgr->SetScissoring( NULL );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::ChangeDebugPrintFont( const char *pFontFace, Sint32 Size )
{
	SAFE_RELEASE( m_pFont );
	::D3DXCreateFont( m_pD3DDevice, Size, 0, FW_HEAVY, 1, FALSE, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, pFontFace, &m_pFont );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::DebugPrint( Math::Point2DI &Pos, CColor Color, const char *pStr, ... )
{
	if ( m_pFont != NULL )
	{
		m_pD3DDevice->SetTextureStageState( TEXTURE_STAGE_LIGHT, D3DTSS_COLOROP, D3DTOP_DISABLE );
		m_pD3DDevice->SetTextureStageState( TEXTURE_STAGE_LIGHT, D3DTSS_ALPHAOP, D3DTOP_DISABLE );
		m_pD3DDevice->SetTextureStageState( TEXTURE_STAGE_ENVIRONMENT, D3DTSS_COLOROP, D3DTOP_DISABLE );
		m_pD3DDevice->SetTextureStageState( TEXTURE_STAGE_ENVIRONMENT, D3DTSS_ALPHAOP, D3DTOP_DISABLE );

		char Temp[256];
		::StringCbVPrintf( Temp, sizeof(Temp), pStr, (char*)(&pStr + 1) );

		RECT Rect = { Pos.x, Pos.y, 0, 0 };
		m_pFont->DrawText( NULL, Temp, -1, &Rect, DT_LEFT | DT_TOP | DT_NOCLIP, Color );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetDrawTextFont( const char *pFontFace, Sint32 Size )
{
	SAFE_RELEASE( m_pFont );
	::D3DXCreateFont( m_pD3DDevice, Size, 0, FW_HEAVY, 1, FALSE, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, pFontFace, &m_pFont );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::DrawText( Math::Point2DI &Pos, CColor Color, const char *pStr, ... )
{
	if ( m_pFont != NULL )
	{
		m_pD3DDevice->SetTextureStageState( TEXTURE_STAGE_LIGHT, D3DTSS_COLOROP, D3DTOP_DISABLE );
		m_pD3DDevice->SetTextureStageState( TEXTURE_STAGE_LIGHT, D3DTSS_ALPHAOP, D3DTOP_DISABLE );
		m_pD3DDevice->SetTextureStageState( TEXTURE_STAGE_ENVIRONMENT, D3DTSS_COLOROP, D3DTOP_DISABLE );
		m_pD3DDevice->SetTextureStageState( TEXTURE_STAGE_ENVIRONMENT, D3DTSS_ALPHAOP, D3DTOP_DISABLE );

		char Temp[256];
		::StringCbVPrintf( Temp, sizeof(Temp), pStr, (char*)(&pStr + 1) );

		RECT Rect = { Pos.x, Pos.y, 0, 0 };
		m_pFont->DrawText( NULL, Temp, -1, &Rect, DT_LEFT | DT_TOP | DT_NOCLIP, Color );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CTextureConfig &CRender::GetTextureConfig( void )
{
	Thread::CAutoLock Lock( m_CS );

	return m_TextureConfig;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetTextureConfig( CTextureConfig &Conf )
{
	Thread::CAutoLock Lock( m_CS );

	m_TextureConfig = Conf;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ITexture *CRender::CreateTextureDepthBuffer( Sint32 Width, Sint32 Height )
{
	Thread::CAutoLock Lock( m_CS );

	ITexture *pTex = m_pTextureMgr->CreateTextureDepthBuffer( Width, Height );
	if ( pTex == NULL )
	{
		static NullTexture Dummy;
		return &Dummy;
	}
	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ITexture *CRender::CreateTextureRenderTarget( Sint32 Width, Sint32 Height, eSurfaceFormat Format )
{
	Thread::CAutoLock Lock( m_CS );

	ITexture *pTex = m_pTextureMgr->CreateRenderTarget( Width, Height, Format );
	if ( pTex == NULL )
	{
		static NullTexture Dummy;
		return &Dummy;
	}
	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ITexture *CRender::CreateCubeTextureFromFile( const char *pFileName )
{
	Thread::CAutoLock Lock( m_CS );

	ITexture *pTex = m_pTextureMgr->CubeCreateFromFile( pFileName, m_TextureConfig.GetFormat(), m_TextureConfig.GetColorKey(), m_TextureConfig.IsMipmap(), m_TextureConfig.IsHalfSize() );
	if ( pTex == NULL )
	{
		static NullTexture Dummy;
		return &Dummy;
	}
	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ITexture *CRender::CreateCubeTextureFromMemory( const void *pData, Sint32 Size )
{
	Thread::CAutoLock Lock( m_CS );

	ITexture *pTex = m_pTextureMgr->CubeCreateFromMemory( pData, Size, m_TextureConfig.GetFormat(), m_TextureConfig.GetColorKey(), m_TextureConfig.IsMipmap(), m_TextureConfig.IsHalfSize() );
	if ( pTex == NULL )
	{
		static NullTexture Dummy;
		return &Dummy;
	}
	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ITexture *CRender::CreateCubeTextureRenderTarget( Sint32 Size )
{
	Thread::CAutoLock Lock( m_CS );

	ITexture *pTex = m_pTextureMgr->CubeCreateRenderTarget( Size, m_TextureConfig.GetFormat(), m_TextureConfig.IsHalfSize() );
	if ( pTex == NULL )
	{
		static NullTexture Dummy;
		return &Dummy;
	}
	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ITexture *CRender::CreateTextureFromFile( const char *pFileName )
{
	Thread::CAutoLock Lock( m_CS );

	ITexture *pTex = m_pTextureMgr->CreateFromFile( pFileName, m_TextureConfig.GetFormat(), m_TextureConfig.GetColorKey(), m_TextureConfig.IsMipmap(), m_TextureConfig.IsHalfSize() );
	if ( pTex == NULL )
	{
		static NullTexture Dummy;
		return &Dummy;
	}
	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ITexture *CRender::CreateTextureFromMemory( const void *pData, Sint32 Size )
{
	Thread::CAutoLock Lock( m_CS );

	ITexture *pTex = m_pTextureMgr->CreateFromMemory( pData, Size, m_TextureConfig.GetFormat(), m_TextureConfig.GetColorKey(), m_TextureConfig.IsMipmap(), m_TextureConfig.IsHalfSize() );
	if ( pTex == NULL )
	{
		static NullTexture Dummy;
		return &Dummy;
	}
	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eDrawType CRender::GetDrawType( void )
{
	return m_RenderState[m_RenderStatePos].DrawType;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eCullType CRender::GetCullType( void )
{
	return m_RenderState[m_RenderStatePos].CullType;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eTextureFilterType CRender::GetTextureFilterType( eTextureStage Stage )
{
	return m_RenderState[m_RenderStatePos].FilterType[Stage];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::GetDepthTestEnable( void )
{
	return m_RenderState[m_RenderStatePos].IsDepthTestEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::GetDepthWriteEnable( void )
{
	return m_RenderState[m_RenderStatePos].IsDepthWriteEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::GetAlphaTestEnable( void )
{
	return m_RenderState[m_RenderStatePos].IsAlphaTestEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CRender::GetAlphaBoundary( void )
{
	return m_RenderState[m_RenderStatePos].AlphaBoundary;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CTexture *CRender::GetTexture( eTextureStage Stage )
{
	return (CTexture*)m_RenderState[m_RenderStatePos].pTextureTbl[Stage];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetDrawType( eDrawType Type )
{
	m_RenderState[m_RenderStatePos].DrawType = Type;

	switch ( Type )
	{
	case DRAW_TYPE_NORMAL:
		m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
		m_pD3DDevice->SetRenderState( D3DRS_BLENDOP,   D3DBLENDOP_ADD );
		m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_ONE );
		m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ZERO );
		break;

	case DRAW_TYPE_BLEND:
		m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		m_pD3DDevice->SetRenderState( D3DRS_BLENDOP,   D3DBLENDOP_ADD );
		m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
		m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		break;

	case DRAW_TYPE_ADD:
		m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		m_pD3DDevice->SetRenderState( D3DRS_BLENDOP,   D3DBLENDOP_ADD );
		m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
		m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
		break;

	case DRAW_TYPE_ADD_NOALPHA:
		m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		m_pD3DDevice->SetRenderState( D3DRS_BLENDOP,   D3DBLENDOP_ADD );
		m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_ONE );
		m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
		break;

	case DRAW_TYPE_SUB:
		m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		m_pD3DDevice->SetRenderState( D3DRS_BLENDOP,   D3DBLENDOP_REVSUBTRACT );
		m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
		m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
		break;

	case DRAW_TYPE_SUB_NOALPHA:
		m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		m_pD3DDevice->SetRenderState( D3DRS_BLENDOP,   D3DBLENDOP_REVSUBTRACT );
		m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_ONE );
		m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
		break;

	case DRAW_TYPE_MULTIPLE:
		m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		m_pD3DDevice->SetRenderState( D3DRS_BLENDOP,   D3DBLENDOP_ADD );
		m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_ZERO );
		m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR );
		break;

//@	case DRAW_TYPE_SCREEN:
//@		m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
//@		m_pD3DDevice->SetRenderState( D3DRS_BLENDOP,   D3DBLENDOP_ADD );
//@		m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_ONE );
//@		m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR );
//@		m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
//@		m_pD3DDevice->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_MODULATE );
//@		m_pD3DDevice->SetTextureStageState( 1, D3DTSS_COLORARG1, D3DTA_CURRENT | D3DTA_ALPHAREPLICATE );
//@		break;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetCullType( eCullType Type )
{
	m_RenderState[m_RenderStatePos].CullType = Type;

	switch ( Type )
	{
	case CULL_FRONT:
		m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
		break;
	case CULL_BACK:
		m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
		break;
	case CULL_NONE:
		m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
		break;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetTextureFilterType( eTextureStage Stage, eTextureFilterType Type )
{
	Bool IsMin, IsMag;
	Sint32 Max;

	m_RenderState[m_RenderStatePos].FilterType[Stage] = Type;

	switch ( Type )
	{
	case TEXTURE_FILTER_DISABLE:
		m_pD3DDevice->SetSamplerState( Stage, D3DSAMP_MAGFILTER, D3DTEXF_POINT );
		m_pD3DDevice->SetSamplerState( Stage, D3DSAMP_MINFILTER, D3DTEXF_POINT );
		m_pD3DDevice->SetSamplerState( Stage, D3DSAMP_MIPFILTER, D3DTEXF_POINT );
		break;
	case TEXTURE_FILTER_2D:
	case TEXTURE_FILTER_3D_LOW:
		m_pD3DDevice->SetSamplerState( Stage, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
		m_pD3DDevice->SetSamplerState( Stage, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
		m_pD3DDevice->SetSamplerState( Stage, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
		break;
	case TEXTURE_FILTER_3D_MIDDLE:
		m_pGraphicCard->GetAnisotropyFilterSupport( IsMin, IsMag, Max );
		m_pD3DDevice->SetSamplerState( Stage, D3DSAMP_MAXANISOTROPY, (Max + 3) / 4 );
		m_pD3DDevice->SetSamplerState( Stage, D3DSAMP_MAGFILTER, IsMag ? D3DTEXF_ANISOTROPIC : D3DTEXF_LINEAR );
		m_pD3DDevice->SetSamplerState( Stage, D3DSAMP_MINFILTER, IsMin ? D3DTEXF_ANISOTROPIC : D3DTEXF_LINEAR );
		m_pD3DDevice->SetSamplerState( Stage, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
		break;
	case TEXTURE_FILTER_3D_HIGH:
		m_pGraphicCard->GetAnisotropyFilterSupport( IsMin, IsMag, Max );
		m_pD3DDevice->SetSamplerState( Stage, D3DSAMP_MAXANISOTROPY, Max );
		m_pD3DDevice->SetSamplerState( Stage, D3DSAMP_MAGFILTER, IsMag ? D3DTEXF_ANISOTROPIC : D3DTEXF_LINEAR );
		m_pD3DDevice->SetSamplerState( Stage, D3DSAMP_MINFILTER, IsMin ? D3DTEXF_ANISOTROPIC : D3DTEXF_LINEAR );
		m_pD3DDevice->SetSamplerState( Stage, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
		break;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetDepthTestEnable( Bool Flag )
{
	m_RenderState[m_RenderStatePos].IsDepthTestEnable = Flag;

	m_pD3DDevice->SetRenderState( D3DRS_ZENABLE, Flag ? D3DZB_TRUE : D3DZB_FALSE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetDepthWriteEnable( Bool Flag )
{
	m_RenderState[m_RenderStatePos].IsDepthWriteEnable = Flag;

	m_pD3DDevice->SetRenderState( D3DRS_ZWRITEENABLE, Flag ? TRUE : FALSE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetAlphaTestEnable( Bool Flag )
{
	m_RenderState[m_RenderStatePos].IsAlphaTestEnable = Flag;

	m_pD3DDevice->SetRenderState( D3DRS_ALPHATESTENABLE, Flag ? TRUE : FALSE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetAlphaBoundary( Sint32 Bound )
{
	m_RenderState[m_RenderStatePos].AlphaBoundary = Bound;

	m_pD3DDevice->SetRenderState( D3DRS_ALPHAREF, Bound );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::SetTexture( eTextureStage Stage, ITexture *pTex )
{
	// ない？
	if ( (pTex != NULL) && pTex->IsInvalid() )
	{
		pTex = NULL;
	}

	// 保存
	m_RenderState[m_RenderStatePos].pTextureTbl[Stage] = pTex;

	// ない場合はデフォルトを設定
	if ( pTex == NULL )
	{
		pTex = m_pTextureDefault[Stage];
	}

	// 設定
	HRESULT hr = E_FAIL;
	if ( pTex != NULL )
	{
		CTextureInterface *pTexData = (CTextureInterface*)pTex;
		IDirect3DBaseTexture9 *pTexture = NULL;
		pTexData->GetTexture( pTexture );
		hr = m_pD3DDevice->SetTexture( Stage, pTexture );
		SAFE_RELEASE( pTexture );
	}
	else
	{
		// デバイスに設定
		hr = m_pD3DDevice->SetTexture( Stage, NULL );
	}

	return SUCCEEDED( hr );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::StatePush( void )
{
	m_RenderStatePos++;

	m_RenderState[m_RenderStatePos] = m_RenderState[m_RenderStatePos-1];

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CRender::StatePop( void )
{
	if ( m_RenderStatePos == 0 )
	{
		return false;
	}

	Sint32 Pos = m_RenderStatePos - 1;

	SetDrawType( m_RenderState[Pos].DrawType );
	SetCullType( m_RenderState[Pos].CullType );
	SetDepthTestEnable( m_RenderState[Pos].IsDepthTestEnable );
	SetDepthWriteEnable( m_RenderState[Pos].IsDepthWriteEnable );
	SetAlphaTestEnable( m_RenderState[Pos].IsAlphaTestEnable );
	SetAlphaBoundary( m_RenderState[Pos].AlphaBoundary );

	for ( Sint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		SetTexture( (eTextureStage)i, m_RenderState[Pos].pTextureTbl[i] );
		SetTextureFilterType( (eTextureStage)i, m_RenderState[Pos].FilterType[i] );
	}

	m_RenderStatePos--;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::StateInit( void )
{
	SetDrawType( DRAW_TYPE_NORMAL );
	SetCullType( CULL_FRONT );
	SetDepthTestEnable( false );
	SetDepthWriteEnable( false );
	SetAlphaTestEnable( true );
	SetAlphaBoundary( 0 );

	for ( Sint32 i = 0; i < TEXTURE_STAGE_MAX; i++ )
	{
		SetTexture( (eTextureStage)i, NULL );
		SetTextureFilterType( (eTextureStage)i, TEXTURE_FILTER_DISABLE );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::ReleaseTexture( ITexture *pTex )
{
	if ( m_pDepthBuffer == pTex )
	{
		SetDepthBuffer( NULL );
	}

	for ( Sint32 i = 0; i < STATE_STACK_MAX; i++ )
	{
		for ( Sint32 j = 0; j < TEXTURE_STAGE_MAX; j++ )
		{
			if ( m_RenderState[i].pTextureTbl[j] == pTex )
			{
				m_RenderState[i].pTextureTbl[j] = NULL;
			}
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
SRenderState &CRender::GetRenderState( void )
{
	return m_RenderState[m_RenderStatePos];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CRender::ToPixelX( Float fIn )
{
	return m_pCore->Virtual2RealX( fIn ) - 0.5f;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CRender::ToPixelY( Float fIn )
{
	return m_pCore->Virtual2RealY( fIn ) - 0.5f;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SaveToFilePNG( const char *pFileName )
{
	::D3DXSaveSurfaceToFile( pFileName, D3DXIFF_PNG, m_pBackBuffer, NULL, NULL );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SaveToFileJPG( const char *pFileName )
{
	::D3DXSaveSurfaceToFile( pFileName, D3DXIFF_JPG, m_pBackBuffer, NULL, NULL );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::SetGUIEnable( Bool IsEnable )
{
	if ( m_pD3DDevice != NULL )
	{
		m_pD3DDevice->SetDialogBoxMode( IsEnable );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::FillRect( const Math::Rect2DF &Dst, CColor Color )
{
	// 頂点更新
	SVertex2DTex Vtx[4] = {
		{ Math::Vector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ) ), Color },
		{ Math::Vector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ) ), Color },
		{ Math::Vector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h) ), Color },
		{ Math::Vector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h) ), Color },
	};

	// 2D描画設定
	Start2D( false );

	// テクスチャ
	SetTexture( TEXTURE_STAGE_COLOR, NULL );
	SetTexture( TEXTURE_STAGE_LIGHT, NULL );

	// 頂点データ
	m_pVertexBuffer2D->Lock( true );
	m_pVertexBuffer2D->Push( Vtx, 4 );
	m_pVertexBuffer2D->UnLock();

	// 頂点定義
	SetVertexStream( m_pVertexStream2D );

	// 頂点バッファ
	SetVertexBuffer( &m_pVertexBuffer2D, 1 );

	// レンダリング
	m_pShader2D->SetTechnique( "TECH_Base" );
	m_pShader2D->Begin( NULL, true );
	m_pShader2D->BeginPass( 0 );
	DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );
	m_pShader2D->EndPass();
	m_pShader2D->End();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::DrawTextureByShader( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle, const Math::Point2DF &Offset )
{
	// 頂点更新
	SVertex2DTex Vtx[4] = {
		{ Math::Vector4D( toF(Dst.x      -0.5f), toF(Dst.y      -0.5f) ), Color },
		{ Math::Vector4D( toF(Dst.x+Dst.w-0.5f), toF(Dst.y      -0.5f) ), Color },
		{ Math::Vector4D( toF(Dst.x      -0.5f), toF(Dst.y+Dst.h-0.5f) ), Color },
		{ Math::Vector4D( toF(Dst.x+Dst.w-0.5f), toF(Dst.y+Dst.h-0.5f) ), Color },
	};

	// 回転
	if ( Angle != 0 )
	{
		Math::Vector2D vCenter( (Vtx[0].Pos.x + Vtx[1].Pos.x) / 2.0f, (Vtx[1].Pos.y + Vtx[2].Pos.y) / 2.0f );
		vCenter.x += Offset.x;
		vCenter.y += Offset.y;
		for ( Sint32 i = 0; i < 4; i++ )
		{
			Vtx[i].Pos -= vCenter;
			Vtx[i].Pos.RotationZ( Angle );
			Vtx[i].Pos += vCenter;
		}
	}

	// テクスチャUV更新
	if ( (pTex != NULL) && !pTex->IsInvalid() )
	{
		eTextureFilterType Filter = GetTextureFilterType( TEXTURE_STAGE_COLOR );
		Float fOffset = (Filter != TEXTURE_FILTER_DISABLE) ? 0.0f : 0.5f;

		// テクスチャUV更新
		Vtx[0].Tex[0] = Math::Vector2D( toF(Src.x      )+fOffset, toF(Src.y      )+fOffset );
		Vtx[1].Tex[0] = Math::Vector2D( toF(Src.x+Src.w)-fOffset, toF(Src.y      )+fOffset );
		Vtx[2].Tex[0] = Math::Vector2D( toF(Src.x      )+fOffset, toF(Src.y+Src.h)-fOffset );
		Vtx[3].Tex[0] = Math::Vector2D( toF(Src.x+Src.w)-fOffset, toF(Src.y+Src.h)-fOffset );

		Math::Point2DF P2T = pTex->GetPixelToTexelTransform();
		for ( Sint32 i = 0; i < 4; i++ )
		{
			Vtx[i].Tex[0].x *= P2T.x;
			Vtx[i].Tex[0].y *= P2T.y;
		}
	}

	// 位置
	Vtx[0].Tex[1] = Math::Vector2D( Vtx[0].Pos.x, Vtx[0].Pos.y );
	Vtx[1].Tex[1] = Math::Vector2D( Vtx[1].Pos.x, Vtx[1].Pos.y );
	Vtx[2].Tex[1] = Math::Vector2D( Vtx[2].Pos.x, Vtx[2].Pos.y );
	Vtx[3].Tex[1] = Math::Vector2D( Vtx[3].Pos.x, Vtx[3].Pos.y );

	// 2D描画設定
	Start2D( false );

	// テクスチャ
	SetTexture( TEXTURE_STAGE_COLOR, pTex );

	// 頂点データ
	m_pVertexBuffer2D->Lock( true );
	m_pVertexBuffer2D->Push( Vtx, 4 );
	m_pVertexBuffer2D->UnLock();

	// 頂点定義
	SetVertexStream( m_pVertexStream2D );

	// 頂点バッファ
	SetVertexBuffer( &m_pVertexBuffer2D, 1 );

	// レンダリング
	DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::DrawTexture( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle, const Math::Point2DF &Offset )
{
	if ( pTex == NULL ) return;
	if ( pTex->IsInvalid() ) return;

	// 頂点更新
	SVertex2DTex Vtx[4] = {
		{ Math::Vector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ) ), Color },
		{ Math::Vector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ) ), Color },
		{ Math::Vector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h) ), Color },
		{ Math::Vector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h) ), Color },
	};

	// 回転
	if ( Angle != 0 )
	{
		Math::Vector2D vCenter( (Vtx[0].Pos.x + Vtx[1].Pos.x) / 2.0f, (Vtx[1].Pos.y + Vtx[2].Pos.y) / 2.0f );
		vCenter.x += Offset.x;
		vCenter.y += Offset.y;
		for ( Sint32 i = 0; i < 4; i++ )
		{
			Vtx[i].Pos -= vCenter;
			Vtx[i].Pos.RotationZ( Angle );
			Vtx[i].Pos += vCenter;
		}
	}

	eTextureFilterType Filter = GetTextureFilterType( TEXTURE_STAGE_COLOR );
	Float fOffset = (Filter != TEXTURE_FILTER_DISABLE) ? 0.0f : 0.5f;

	// テクスチャUV更新
	Vtx[0].Tex[0] = Math::Vector2D( toF(Src.x      )+fOffset, toF(Src.y      )+fOffset );
	Vtx[1].Tex[0] = Math::Vector2D( toF(Src.x+Src.w)-fOffset, toF(Src.y      )+fOffset );
	Vtx[2].Tex[0] = Math::Vector2D( toF(Src.x      )+fOffset, toF(Src.y+Src.h)-fOffset );
	Vtx[3].Tex[0] = Math::Vector2D( toF(Src.x+Src.w)-fOffset, toF(Src.y+Src.h)-fOffset );

	Math::Point2DF P2T = pTex->GetPixelToTexelTransform();
	for ( Sint32 i = 0; i < 4; i++ )
	{
		Vtx[i].Tex[0].x *= P2T.x;
		Vtx[i].Tex[0].y *= P2T.y;
	}

	// 2D描画設定
	Start2D( false );

	// テクスチャ
	SetTexture( TEXTURE_STAGE_COLOR, pTex );
	SetTexture( TEXTURE_STAGE_LIGHT, NULL );

	// 頂点データ
	m_pVertexBuffer2D->Lock( true );
	m_pVertexBuffer2D->Push( Vtx, 4 );
	m_pVertexBuffer2D->UnLock();

	// 頂点定義
	SetVertexStream( m_pVertexStream2D );

	// 頂点バッファ
	SetVertexBuffer( &m_pVertexBuffer2D, 1 );

	// レンダリング
	Start2D( false );
	m_pShader2D->SetTechnique( "TECH_Base" );
	m_pShader2D->Begin( NULL, true );
	m_pShader2D->BeginPass( 0 );
	DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );
	m_pShader2D->EndPass();
	m_pShader2D->End();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::DrawTextureTile( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle, const Math::Point2DF &Offset )
{
	if ( pTex == NULL ) return;
	if ( pTex->IsInvalid() ) return;

	// 頂点更新
	SVertex2DTex Vtx[4] = {
		{ Math::Vector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ) ), Color },
		{ Math::Vector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ) ), Color },
		{ Math::Vector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h) ), Color },
		{ Math::Vector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h) ), Color },
	};

	// 回転
	if ( Angle != 0 )
	{
		Math::Vector2D vCenter( (Vtx[0].Pos.x + Vtx[1].Pos.x) / 2.0f, (Vtx[1].Pos.y + Vtx[2].Pos.y) / 2.0f );
		vCenter.x += Offset.x;
		vCenter.y += Offset.y;
		for ( Sint32 i = 0; i < 4; i++ )
		{
			Vtx[i].Pos -= vCenter;
			Vtx[i].Pos.RotationZ( Angle );
			Vtx[i].Pos += vCenter;
		}
	}

	eTextureFilterType Filter = GetTextureFilterType( TEXTURE_STAGE_COLOR );
	Float fOffset = (Filter != TEXTURE_FILTER_DISABLE) ? 0.0f : 0.5f;

	// テクスチャUV更新
	Vtx[0].Tex[0] = Math::Vector2D( toF(Src.x      )+fOffset, toF(Src.y      )+fOffset );
	Vtx[1].Tex[0] = Math::Vector2D( toF(Src.x+Src.w)-fOffset, toF(Src.y      )+fOffset );
	Vtx[2].Tex[0] = Math::Vector2D( toF(Src.x      )+fOffset, toF(Src.y+Src.h)-fOffset );
	Vtx[3].Tex[0] = Math::Vector2D( toF(Src.x+Src.w)-fOffset, toF(Src.y+Src.h)-fOffset );

	Math::Point2DF P2T = pTex->GetPixelToTexelTransform();
	for ( Sint32 i = 0; i < 4; i++ )
	{
		Vtx[i].Tex[0].x *= P2T.x;
		Vtx[i].Tex[0].y *= P2T.y;
	}

	// 2D描画設定
	Start2D( false );

	// テクスチャ
	SetTexture( TEXTURE_STAGE_COLOR, pTex );
	SetTexture( TEXTURE_STAGE_LIGHT, NULL );

	// 頂点データ
	m_pVertexBuffer2D->Lock( true );
	m_pVertexBuffer2D->Push( Vtx, 4 );
	m_pVertexBuffer2D->UnLock();

	// 頂点定義
	SetVertexStream( m_pVertexStream2D );

	// 頂点バッファ
	SetVertexBuffer( &m_pVertexBuffer2D, 1 );

	// レンダリング
	m_pShader2D->SetTechnique( "TECH_BaseTile" );
	m_pShader2D->Begin( NULL, true );
	m_pShader2D->BeginPass( 0 );
	DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );
	m_pShader2D->EndPass();
	m_pShader2D->End();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::DrawUniversal( const Math::Rect2DF &Dst, Float fRate, const Math::Rect2DF &SrcBase, ITexture *pTexBase, const Math::Rect2DF &SrcRule, ITexture *pTexRule, Sint32 Angle, const Math::Point2DF &Offset )
{
	// レートクランプ
	if ( fRate < 0.0f ) fRate = 0.0f;
	if ( fRate > 1.0f ) fRate = 1.0f;

	// ピクセルシェーダーなしは通常描画
	if ( !IsSupportedPS20() )
	{
		DrawTexture( Dst, CColor(255,255,255,(Uint32)(255.0f*fRate)), SrcBase, pTexBase, Angle, Offset );
		return;
	}

	// テクスチャなしはキャンセル
	if ( pTexBase == NULL ) return;
	if ( pTexBase->IsInvalid() ) return;
	if ( pTexRule == NULL ) return;
	if ( pTexRule->IsInvalid() ) return;

	// 頂点更新
	SVertex2DTex Vtx[4] = {
		{ Math::Vector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ) ) },
		{ Math::Vector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ) ) },
		{ Math::Vector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h) ) },
		{ Math::Vector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h) ) },
	};

	// 回転
	if ( Angle != 0 )
	{
		Math::Vector2D vCenter( (Vtx[0].Pos.x + Vtx[1].Pos.x) / 2.0f, (Vtx[1].Pos.y + Vtx[2].Pos.y) / 2.0f );
		vCenter.x += Offset.x;
		vCenter.y += Offset.y;
		for ( Sint32 i = 0; i < 4; i++ )
		{
			Vtx[i].Pos -= vCenter;
			Vtx[i].Pos.RotationZ( Angle );
			Vtx[i].Pos += vCenter;
		}
	}

	ITexture *pTexTbl[] = { pTexBase, pTexRule };
	const Math::Rect2DF *pSrcTbl[] = { &SrcBase, &SrcRule };
	for ( Sint32 i = 0; i < 2; i++ )
	{
		eTextureFilterType Filter = GetTextureFilterType( (eTextureStage)i );
		Float fOffset = (Filter != TEXTURE_FILTER_DISABLE) ? 0.0f : 0.5f;

		// テクスチャUV更新
		Vtx[0].Tex[i] = Math::Vector2D( toF(pSrcTbl[i]->x              )+fOffset, toF(pSrcTbl[i]->y              )+fOffset );
		Vtx[1].Tex[i] = Math::Vector2D( toF(pSrcTbl[i]->x+pSrcTbl[i]->w)-fOffset, toF(pSrcTbl[i]->y              )+fOffset );
		Vtx[2].Tex[i] = Math::Vector2D( toF(pSrcTbl[i]->x              )+fOffset, toF(pSrcTbl[i]->y+pSrcTbl[i]->h)-fOffset );
		Vtx[3].Tex[i] = Math::Vector2D( toF(pSrcTbl[i]->x+pSrcTbl[i]->w)-fOffset, toF(pSrcTbl[i]->y+pSrcTbl[i]->h)-fOffset );

		Math::Point2DF P2T = pTexTbl[i]->GetPixelToTexelTransform();
		for ( Sint32 j = 0; j < 4; j++ )
		{
			Vtx[j].Tex[i].x *= P2T.x;
			Vtx[j].Tex[i].y *= P2T.y;
		}
	}

	// 2D描画設定
	Start2D( false );

	// テクスチャ
	SetTexture( TEXTURE_STAGE_COLOR, pTexBase );
	SetTexture( TEXTURE_STAGE_LIGHT, pTexRule );

	// 頂点データ
	m_pVertexBuffer2D->Lock( true );
	m_pVertexBuffer2D->Push( Vtx, 4 );
	m_pVertexBuffer2D->UnLock();

	// 頂点定義
	SetVertexStream( m_pVertexStream2D );

	// 頂点バッファ
	SetVertexBuffer( &m_pVertexBuffer2D, 1 );

	// データ
	m_pShader2D->SetFloat( m_pShader2D->GetParameterBySemantic("UNIVERSAL_RATE"), (fRate * 2.0f) - 1.0f );
	m_pShader2D->UpdateParameter();

	// レンダリング
	m_pShader2D->SetTechnique( "TECH_Universal" );
	m_pShader2D->Begin( NULL, true );
	m_pShader2D->BeginPass( 0 );
	DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );
	m_pShader2D->EndPass();
	m_pShader2D->End();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::DrawBlur( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle, const Math::Point2DF &Offset )
{
	// ピクセルシェーダーなしは通常描画
	if ( !IsSupportedPS20() )
	{
		DrawTexture( Dst, Color, Src, pTex, Angle, Offset );
		return;
	}

	if ( pTex == NULL ) return;
	if ( pTex->IsInvalid() ) return;

	// 頂点更新
	SVertex2DTex Vtx[4] = {
		{ Math::Vector4D( ToPixelX(Dst.x      )+0.5f, ToPixelY(Dst.y      )+0.5f ), Color },
		{ Math::Vector4D( ToPixelX(Dst.x+Dst.w)+0.5f, ToPixelY(Dst.y      )+0.5f ), Color },
		{ Math::Vector4D( ToPixelX(Dst.x      )+0.5f, ToPixelY(Dst.y+Dst.h)+0.5f ), Color },
		{ Math::Vector4D( ToPixelX(Dst.x+Dst.w)+0.5f, ToPixelY(Dst.y+Dst.h)+0.5f ), Color },
	};

	// 回転
	if ( Angle != 0 )
	{
		Math::Vector2D vCenter( (Vtx[0].Pos.x + Vtx[1].Pos.x) / 2.0f, (Vtx[1].Pos.y + Vtx[2].Pos.y) / 2.0f );
		vCenter.x += Offset.x;
		vCenter.y += Offset.y;
		for ( Sint32 i = 0; i < 4; i++ )
		{
			Vtx[i].Pos -= vCenter;
			Vtx[i].Pos.RotationZ( Angle );
			Vtx[i].Pos += vCenter;
		}
	}

	// テクスチャUV更新
	Vtx[0].Tex[0] = Math::Vector2D( toF(Src.x      ), toF(Src.y      ) );
	Vtx[1].Tex[0] = Math::Vector2D( toF(Src.x+Src.w), toF(Src.y      ) );
	Vtx[2].Tex[0] = Math::Vector2D( toF(Src.x      ), toF(Src.y+Src.h) );
	Vtx[3].Tex[0] = Math::Vector2D( toF(Src.x+Src.w), toF(Src.y+Src.h) );

	Math::Point2DF P2T = pTex->GetPixelToTexelTransform();
	for ( Sint32 i = 0; i < 4; i++ )
	{
		Vtx[i].Tex[0].x *= P2T.x;
		Vtx[i].Tex[0].y *= P2T.y;
	}

	Math::Vector4D vOffset[4] = {
		Math::Vector4D(-1.0f,-1.0f), Math::Vector4D(+1.0f,-1.0f),
		Math::Vector4D(-1.0f,+1.0f), Math::Vector4D(+1.0f,+1.0f),
	};
	for ( Sint32 i = 0; i < 4; i++ )
	{
		vOffset[i].x *= P2T.x;
		vOffset[i].y *= P2T.y;
	}

	// 2D描画設定
	Start2D( false );

	// テクスチャ
	SetTexture( TEXTURE_STAGE_COLOR, pTex );
	SetTexture( TEXTURE_STAGE_LIGHT, NULL );

	// 頂点データ
	m_pVertexBuffer2D->Lock( true );
	m_pVertexBuffer2D->Push( Vtx, 4 );
	m_pVertexBuffer2D->UnLock();

	// 頂点定義
	SetVertexStream( m_pVertexStream2D );

	// 頂点バッファ
	SetVertexBuffer( &m_pVertexBuffer2D, 1 );

	// データ
	m_pShader2D->SetVectorArray( m_pShader2D->GetParameterBySemantic("UV_OFFSET"), vOffset, 4 );
	m_pShader2D->UpdateParameter();

	// レンダリング
	m_pShader2D->SetTechnique( "TECH_Blur" );
	m_pShader2D->Begin( NULL, true );
	m_pShader2D->BeginPass( 0 );
	DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );
	m_pShader2D->EndPass();
	m_pShader2D->End();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::DrawGrayscale( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle, const Math::Point2DF &Offset )
{
	// ピクセルシェーダーなしは通常描画
	if ( !IsSupportedPS20() )
	{
		DrawTexture( Dst, Color, Src, pTex, Angle, Offset );
		return;
	}

	if ( pTex == NULL ) return;
	if ( pTex->IsInvalid() ) return;

	// 頂点更新
	SVertex2DTex Vtx[4] = {
		{ Math::Vector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ) ), Color },
		{ Math::Vector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ) ), Color },
		{ Math::Vector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h) ), Color },
		{ Math::Vector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h) ), Color },
	};

	// 回転
	if ( Angle != 0 )
	{
		Math::Vector2D vCenter( (Vtx[0].Pos.x + Vtx[1].Pos.x) / 2.0f, (Vtx[1].Pos.y + Vtx[2].Pos.y) / 2.0f );
		vCenter.x += Offset.x;
		vCenter.y += Offset.y;
		for ( Sint32 i = 0; i < 4; i++ )
		{
			Vtx[i].Pos -= vCenter;
			Vtx[i].Pos.RotationZ( Angle );
			Vtx[i].Pos += vCenter;
		}
	}

	eTextureFilterType Filter = GetTextureFilterType( TEXTURE_STAGE_COLOR );
	Float fOffset = (Filter != TEXTURE_FILTER_DISABLE) ? 0.0f : 0.5f;

	// テクスチャUV更新
	Vtx[0].Tex[0] = Math::Vector2D( toF(Src.x      )+fOffset, toF(Src.y      )+fOffset );
	Vtx[1].Tex[0] = Math::Vector2D( toF(Src.x+Src.w)-fOffset, toF(Src.y      )+fOffset );
	Vtx[2].Tex[0] = Math::Vector2D( toF(Src.x      )+fOffset, toF(Src.y+Src.h)-fOffset );
	Vtx[3].Tex[0] = Math::Vector2D( toF(Src.x+Src.w)-fOffset, toF(Src.y+Src.h)-fOffset );

	Math::Point2DF P2T = pTex->GetPixelToTexelTransform();
	for ( Sint32 i = 0; i < 4; i++ )
	{
		Vtx[i].Tex[0].x *= P2T.x;
		Vtx[i].Tex[0].y *= P2T.y;
	}

	// 2D描画設定
	Start2D( false );

	// テクスチャ
	SetTexture( TEXTURE_STAGE_COLOR, pTex );
	SetTexture( TEXTURE_STAGE_LIGHT, NULL );

	// 頂点データ
	m_pVertexBuffer2D->Lock( true );
	m_pVertexBuffer2D->Push( Vtx, 4 );
	m_pVertexBuffer2D->UnLock();

	// 頂点定義
	SetVertexStream( m_pVertexStream2D );

	// 頂点バッファ
	SetVertexBuffer( &m_pVertexBuffer2D, 1 );

	// レンダリング
	m_pShader2D->SetTechnique( "TECH_Grayscale" );
	m_pShader2D->Begin( NULL, true );
	m_pShader2D->BeginPass( 0 );
	DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );
	m_pShader2D->EndPass();
	m_pShader2D->End();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRender::DrawFishEye( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Float fRate )
{
	// ピクセルシェーダーなしは通常描画
	if ( !IsSupportedPS20() )
	{
		DrawTexture( Dst, Color, Src, pTex );
		return;
	}

	if ( pTex == NULL ) return;
	if ( pTex->IsInvalid() ) return;

	// 頂点更新
	SVertex2DTex Vtx[4] = {
		{ Math::Vector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y      ) ), Color },
		{ Math::Vector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y      ) ), Color },
		{ Math::Vector4D( ToPixelX(Dst.x      ), ToPixelY(Dst.y+Dst.h) ), Color },
		{ Math::Vector4D( ToPixelX(Dst.x+Dst.w), ToPixelY(Dst.y+Dst.h) ), Color },
	};

	// テクスチャUV更新
	Vtx[0].Tex[0] = Math::Vector2D( toF(Src.x      ), toF(Src.y      ) );
	Vtx[1].Tex[0] = Math::Vector2D( toF(Src.x+Src.w), toF(Src.y      ) );
	Vtx[2].Tex[0] = Math::Vector2D( toF(Src.x      ), toF(Src.y+Src.h) );
	Vtx[3].Tex[0] = Math::Vector2D( toF(Src.x+Src.w), toF(Src.y+Src.h) );

	Math::Point2DF P2T = pTex->GetPixelToTexelTransform();
	for ( Sint32 i = 0; i < 4; i++ )
	{
		Vtx[i].Tex[0].x *= P2T.x;
		Vtx[i].Tex[0].y *= P2T.y;
	}

	// 2D描画設定
	Start2D( false );

	// テクスチャ
	SetTexture( TEXTURE_STAGE_COLOR, pTex );
	SetTexture( TEXTURE_STAGE_LIGHT, NULL );

	// 頂点データ
	m_pVertexBuffer2D->Lock( true );
	m_pVertexBuffer2D->Push( Vtx, 4 );
	m_pVertexBuffer2D->UnLock();

	// 頂点定義
	SetVertexStream( m_pVertexStream2D );

	// 頂点バッファ
	SetVertexBuffer( &m_pVertexBuffer2D, 1 );

	// データ
	m_pShader2D->SetFloat( m_pShader2D->GetParameterBySemantic("CURVATURE"), fRate );
	m_pShader2D->UpdateParameter();

	// レンダリング
	m_pShader2D->SetTechnique( "TECH_FishEye" );
	m_pShader2D->Begin( NULL, true );
	m_pShader2D->BeginPass( 0 );
	DrawPrimitive( PRIMITIVE_TRIANGLE_STRIP, 2 );
	m_pShader2D->EndPass();
	m_pShader2D->End();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CRender::StretchRectToBackBuffer( IDirect3DSurface9 *pSourceSurface )
{
	HRESULT hr;

	hr = m_pD3DDevice->StretchRect( pSourceSurface, NULL, m_pBackBuffer, NULL, D3DTEXF_LINEAR );
	if FAILED( hr )
	{
		hr = m_pD3DDevice->StretchRect( pSourceSurface, NULL, m_pBackBuffer, NULL, D3DTEXF_NONE );
	}

	return hr;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CRender::StretchRect( IDirect3DSurface9 *pSourceSurface, CONST RECT *pSourceRect, IDirect3DSurface9 *pDestSurface, CONST RECT *pDestRect, D3DTEXTUREFILTERTYPE Filter )
{
	return m_pD3DDevice->StretchRect( pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CRender::GetRenderTargetData( IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface )
{
	return m_pD3DDevice->GetRenderTargetData( pRenderTarget, pDestSurface );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CRender::UpdateSurface( IDirect3DSurface9* pSourceSurface, IDirect3DSurface9* pDestinationSurface )
{
	return m_pD3DDevice->UpdateSurface( pSourceSurface, NULL, pDestinationSurface, NULL );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CRender::CreateOcclusionQuery( IDirect3DQuery9 *&pQuery )
{
	HRESULT hr = m_pD3DDevice->CreateQuery( D3DQUERYTYPE_OCCLUSION, &pQuery );
	UpdateUsedVRAM();
	return hr;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CRender::CreateDepthStencilSurface( Sint32 Width, Sint32 Height, D3DFORMAT Format, IDirect3DSurface9** ppSurface )
{
	HRESULT hr = m_pD3DDevice->CreateDepthStencilSurface( Width, Height, Format, D3DMULTISAMPLE_NONE, D3DMULTISAMPLE_NONE, true, ppSurface, NULL );
	UpdateUsedVRAM();
	return hr;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CRender::CreateTexture( Sint32 Width, Sint32 Height, Sint32 Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture )
{
	HRESULT hr = m_pD3DDevice->CreateTexture( Width, Height, Levels, Usage, Format, Pool, ppTexture, NULL );
	UpdateUsedVRAM();
	return hr;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CRender::CreateCubeTextureFromInMemory( const void *pData, Sint32 DataSize, Sint32 Size, Sint32 Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppTexture )
{
	HRESULT hr = D3DXCreateCubeTextureFromFileInMemoryEx( m_pD3DDevice, pData, DataSize, Size, Levels, Usage, Format, Pool, D3DX_FILTER_TRIANGLE, D3DX_FILTER_TRIANGLE, 0x00000000, NULL, NULL, ppTexture );
	UpdateUsedVRAM();
	return hr;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CRender::CreateCubeTexture( Sint32 Size, Sint32 Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppTexture )
{
	HRESULT hr = m_pD3DDevice->CreateCubeTexture( Size, Levels, Usage, Format, Pool, ppTexture, NULL );
	UpdateUsedVRAM();
	return hr;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CRender::CreateRenderTarget( Sint32 Width, Sint32 Height, D3DFORMAT Format, IDirect3DSurface9** ppSurface )
{
	HRESULT hr = m_pD3DDevice->CreateRenderTarget( Width, Height, Format, D3DMULTISAMPLE_NONE, D3DMULTISAMPLE_NONE, true, ppSurface, NULL );
	UpdateUsedVRAM();
	return hr;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CRender::SetDepthStencilSurface( IDirect3DSurface9 *pZStencil )
{
	HRESULT hr = m_pD3DDevice->SetDepthStencilSurface( pZStencil );
	UpdateUsedVRAM();
	return hr;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CRender::CreateVertexBuffer( Sint32 Length, IDirect3DVertexBuffer9** ppVertexBuffer, Bool IsDynamic )
{
	Sint32 Usage = IsDynamic ? D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC : D3DUSAGE_WRITEONLY;
	HRESULT hr = m_pD3DDevice->CreateVertexBuffer( Length, Usage, 0, D3DPOOL_DEFAULT, ppVertexBuffer, NULL );
	UpdateUsedVRAM();
	return hr;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CRender::CreateIndexBuffer( Sint32 Length, IDirect3DIndexBuffer9** ppIndexBuffer, Bool IsDynamic, Bool Is32Bit )
{
	Sint32 Usage = IsDynamic ? D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC : D3DUSAGE_WRITEONLY;
	HRESULT hr = m_pD3DDevice->CreateIndexBuffer( Length, Usage, Is32Bit ? D3DFMT_INDEX32 : D3DFMT_INDEX16, D3DPOOL_DEFAULT, ppIndexBuffer, NULL );
	UpdateUsedVRAM();
	return hr;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CRender::CreateVertexDeclaration( const D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl )
{
	HRESULT hr = m_pD3DDevice->CreateVertexDeclaration( pVertexElements, ppDecl );
	UpdateUsedVRAM();
	return hr;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CRender::CreateEffect( LPCVOID pSrcData, UINT SrcDataLen, LPD3DXEFFECT *ppEffect, LPD3DXBUFFER *ppCompilationErrors, Bool IsCompiled )
{
	HRESULT hr = ::D3DXCreateEffect(
					m_pD3DDevice,
					pSrcData,
					SrcDataLen,
					NULL,
					NULL,
					IsCompiled ? D3DXSHADER_SKIPVALIDATION : 0,
					m_pEffectPool,
					ppEffect,
					ppCompilationErrors );
	UpdateUsedVRAM();
	return hr;
}

