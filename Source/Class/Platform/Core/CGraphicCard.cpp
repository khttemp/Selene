

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Platform/Core/CGraphicCard.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Common/Core/CCore.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// CONSTANT
//-----------------------------------------------------------------------------------

//---------------------------------------------------------------
// バックバッファフォーマット
//---------------------------------------------------------------
static const D3DFORMAT g_BackBufferFormats[] = {
	D3DFMT_X8R8G8B8,
	D3DFMT_X1R5G5B5,
	D3DFMT_R5G6B5,

	D3DFMT_UNKNOWN,
};


//---------------------------------------------------------------
// テクスチャフォーマット
//---------------------------------------------------------------
static D3DFORMAT g_TextureFormats[] = {
	D3DFMT_A8R8G8B8,
	D3DFMT_A4R4G4B4,
	D3DFMT_A1R5G5B5,
	D3DFMT_DXT5,
	D3DFMT_DXT3,
	D3DFMT_DXT1,
	D3DFMT_R32F,
	D3DFMT_R16F,
    D3DFMT_G32R32F,
    D3DFMT_G16R16F,
	D3DFMT_A32B32G32R32F,
	D3DFMT_A16B16G16R16F,
	D3DFMT_Q16W16V16U16,
	D3DFMT_Q8W8V8U8,

	D3DFMT_UNKNOWN,
};

//---------------------------------------------------------------
// 深度バッファフォーマット
//---------------------------------------------------------------
static D3DFORMAT g_DepthFormats[] = {
	D3DFMT_DF24,
	D3DFMT_D32F_LOCKABLE,
	D3DFMT_D32,
	D3DFMT_D24FS8,
	D3DFMT_D24S8,
	D3DFMT_D24X4S4,
	D3DFMT_D24X8,
	D3DFMT_D16_LOCKABLE,
	D3DFMT_D16,
	D3DFMT_D15S1,

	D3DFMT_UNKNOWN,
};

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CGraphicCard::CGraphicCard( CCore *pCore )
	: m_pCore						( pCore )
	, m_pDirect3D					( NULL )
	, m_pRender						( NULL )
	, m_IsHighColor					( false )
	, m_IsHVPerfHUD					( false )
	, m_GraphicCardNo				( GRAPHIC_CARD_DEFAULT_NO )
	, m_MaxUseVertexShaderVersion	( 0 )
	, m_ScreenTypeCount				( 0 )
	, m_DepthSurfaceFormatCount		( 0 )
	, m_DepthTextureFormatCount		( 0 )
	, m_TextureFormatCount			( 0 )
	, m_TargetFormatCount			( 0 )
	, m_TargetAlphaFormatCount		( 0 )
	, m_FullScreen16BitInfo			( D3DFMT_UNKNOWN )
	, m_FullScreen32BitInfo			( D3DFMT_UNKNOWN )
{
	MemoryClear( m_GraphicCardName, sizeof(m_GraphicCardName) );

	MemoryClear( &m_DeviceInfo, sizeof(m_DeviceInfo) );
	MemoryClear( &m_WindowModeInfo, sizeof(m_WindowModeInfo) );

	MemoryClear( m_ScreenType, sizeof(m_ScreenType) );
	MemoryClear( m_DepthSurfaceFormats, sizeof(m_DepthSurfaceFormats) );
	MemoryClear( m_DepthTextureFormats, sizeof(m_DepthTextureFormats) );
	MemoryClear( m_TextureFormats, sizeof(m_TextureFormats) );
	MemoryClear( m_TargetFormats, sizeof(m_TargetFormats) );
	MemoryClear( m_TargetAlphaFormats, sizeof(m_TargetAlphaFormats) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CGraphicCard::~CGraphicCard()
{
	// グラフィックカード解放
	if ( m_pDirect3D != NULL )
	{
		Sint32 Num = m_pDirect3D->Release();
		m_pDirect3D = NULL;

		Log_TableBegin();
		Log_PrintCellTitle( 0x008000, "解放" );
		Log_PrintCellKind( "IDirect3D9Object" );
		Log_CellBegin( 0 );
		Log_Print( 0x000000, "参照数 %d", Num );
		Log_CellEnd();
		Log_TableEnd();
		Log_TableLine( 2 );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::Initialize( eGraphicCardNo GraphicCardNo )
{
	//---------------------------------------------------------------
	// ビデオカード番号
	//---------------------------------------------------------------
	m_GraphicCardNo = GraphicCardNo;

	//---------------------------------------------------------------
	// シェーダーバージョン
	//---------------------------------------------------------------
	m_MaxUseVertexShaderVersion = D3DVS_VERSION(2,0);

	//---------------------------------------------------------------
	// Direct3Dオブジェクトの生成
	//---------------------------------------------------------------
	if ( !CreateDirect3DObject() )
	{
		return false;
	}

	//---------------------------------------------------------------
	// "NVPerfHUD"チェック
	//---------------------------------------------------------------
	if ( m_GraphicCardNo == GRAPHIC_CARD_NV_PERF_HUD )
	{
		const char *pDriverName[] = {
			"NVIDIA NVPerfHUD",
			"NVIDIA PerfHUD",
			NULL,
		};

		m_GraphicCardNo = GRAPHIC_CARD_DEFAULT_NO;
		Sint32 MaxGraphicCard = (Sint32)m_pDirect3D->GetAdapterCount();
		for ( Sint32 i= 0; i< MaxGraphicCard; i++ )
		{
			D3DADAPTER_IDENTIFIER9 Identifier;
			m_pDirect3D->GetAdapterIdentifier( i, 0, &Identifier );

			for ( Sint32 j = 0; pDriverName[j] != NULL; j++ )
			{
				Sint32 Compare = ::CompareString( LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, Identifier.Description, -1, pDriverName[j], -1 );
				if ( Compare == CSTR_EQUAL )
				{
					m_IsHVPerfHUD = true;
					m_GraphicCardNo = (eGraphicCardNo)i;
					goto EXIT;
				}
			}
		}
	}

EXIT:
	//---------------------------------------------------------------
	// ビデオカード情報のチェック
	//---------------------------------------------------------------
	if ( !CheckGraphicCardInfo() )
	{
		return false;
	}

	//---------------------------------------------------------------
	// デバイス情報のチェック
	//---------------------------------------------------------------
	if ( !CheckGraphicCardCaps() )
	{
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::CreateDirect3DObject( void )
{
	CCore *pCore = (CCore*)GetParent();

	//---------------------------------------------------------------
	// Create Direct3D Object
	//---------------------------------------------------------------
	m_pDirect3D = Direct3DCreate9( D3D_SDK_VERSION );
	if ( m_pDirect3D == NULL )
	{
		pCore->MsgBox( MB_ICONERROR, "Error", "Direct3Dオブジェクトの生成に失敗\nDirectX9.0cが正しくインストールされているか\n確認して下さい" );
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::CheckGraphicCardInfo( void )
{
	D3DADAPTER_IDENTIFIER9 Identifier;
	HRESULT hr;

	//---------------------------------------------------------------
	// ビデオカード情報
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "調査" );
	Log_PrintCellKind( "ビデオカード情報" );
	Log_CellBegin( 0 );

	hr = m_pDirect3D->GetAdapterIdentifier( m_GraphicCardNo, 0, &Identifier );
	if SUCCEEDED( hr )
	{
		StringCbCopy( m_GraphicCardName, sizeof(m_GraphicCardName), Identifier.Description );

		Log_PrintTable( 128, "Name", "%s", m_GraphicCardName );
		Log_PrintTable( 128, "Driver", "%s", Identifier.Driver );
		Log_PrintTable( 128, "Version", "%u.%u.%u", LOWORD(Identifier.DriverVersion.HighPart), HIWORD(Identifier.DriverVersion.LowPart), LOWORD(Identifier.DriverVersion.LowPart) );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// 現在の画面モード取得
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "調査" );
	Log_PrintCellKind( "現在の画面情報" );
	Log_CellBegin( 0 );

	hr = m_pDirect3D->GetAdapterDisplayMode( m_GraphicCardNo, &m_WindowModeInfo );
	if SUCCEEDED( hr )
	{
		Log_PrintTable( 128, "Width", "%u", m_WindowModeInfo.Width );
		Log_PrintTable( 128, "Height", "%u", m_WindowModeInfo.Height );
		Log_PrintTable( 128, "RefreshRate", "%uHz", m_WindowModeInfo.RefreshRate );
		Log_PrintTable( 128, "Format", "%s", GetPixelFormat(m_WindowModeInfo.Format) );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// フルスクリーン時に使用可能な画面モードを列挙する
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "調査" );
	Log_PrintCellKind( "使用可能な画面モード" );
	Log_CellBegin( 0 );

	for ( Sint32 i = 0; g_BackBufferFormats[i] != D3DFMT_UNKNOWN; i++ )
	{
		// ディスプレイモード数の取得
		D3DDISPLAYMODE DisplayType;
		Sint32 TypeCount = (Sint32)m_pDirect3D->GetAdapterModeCount( m_GraphicCardNo, g_BackBufferFormats[i] );

		if ( TypeCount > 0 )
		{
			Log_PrintStrongLine( 0x000000, "BackBuffer Format %s", GetPixelFormat(g_BackBufferFormats[i]) );

			// モードを列挙
			for ( Sint32 j = 0; j < TypeCount; j++ )
			{
				hr = m_pDirect3D->EnumAdapterModes( m_GraphicCardNo, g_BackBufferFormats[i], j, &DisplayType );
				if SUCCEEDED( hr )
				{
					Sint32 No = -1;

					// 同一サイズ検索
					for ( Sint32 k = 0; k < m_ScreenTypeCount; k++ )
					{
						if ( m_ScreenType[k].Format == g_BackBufferFormats[i] )
						{
							if ( m_ScreenType[k].Width == DisplayType.Width )
							{
								if ( m_ScreenType[k].Height == DisplayType.Height )
								{
									// 既にあったりして
									No = k;
									// ウィンドウモードのリフレッシュレートを超えない
									// 最大のリフレッシュレートを使う（念のため）
									if ( m_ScreenType[No].RefreshRate < DisplayType.RefreshRate )
									{
										if ( DisplayType.RefreshRate <= m_WindowModeInfo.RefreshRate )
										{
											m_ScreenType[No] = DisplayType;
										}
									}
								}
							}
						}
					}

					// 同一画面サイズが見つからなかった場合は追加
					if ( No == -1 )
					{
						m_ScreenType[m_ScreenTypeCount++] = DisplayType;
					}
				}
			}

			// ログ
			for ( Sint32 j = 0; j < m_ScreenTypeCount; j++ )
			{
				if ( m_ScreenType[j].Format == g_BackBufferFormats[i] )
				{
					Log_PrintLine( 0x000000, "%4u x %4u : %uHz", m_ScreenType[j].Width, m_ScreenType[j].Height, m_ScreenType[j].RefreshRate );
				}
			}
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// フルスクリーンモード用のディスプレイモード設定
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "調査" );
	Log_PrintCellKind( "フルスクリーン用<BR>ディスプレイモード" );
	Log_CellBegin( 0 );

	Sint32 Width, Height;
	m_pCore->GetScreenData( &Width, &Height, NULL );

	// 検索
	for ( Sint32 j = 0; j < m_ScreenTypeCount; j++ )
	{
		switch ( m_ScreenType[j].Format )
		{
		// 16Bit
		case D3DFMT_X1R5G5B5:
		case D3DFMT_R5G6B5:
			m_FullScreen16BitInfo = m_ScreenType[j].Format;
			break;
		// 32Bit
		case D3DFMT_X8R8G8B8:
			m_FullScreen32BitInfo = m_ScreenType[j].Format;
			break;
		}
	}

	// ログ
	Log_PrintLine( 0x000000, "16BitColor %s", GetPixelFormat(m_FullScreen16BitInfo) );
	Log_PrintLine( 0x000000, "32BitColor %s", GetPixelFormat(m_FullScreen32BitInfo) );

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// テクスチャフォーマットから使用可能なものを検索
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "調査" );
	Log_PrintCellKind( "使用可能な<BR>テクスチャフォーマット" );
	Log_CellBegin( 0 );

	D3DFORMAT BaseFormat = m_FullScreen32BitInfo == D3DFMT_UNKNOWN ? m_WindowModeInfo.Format : m_FullScreen32BitInfo;

	for ( Sint32 i = 0; g_TextureFormats[i] != D3DFMT_UNKNOWN; i++ )
	{
		hr = m_pDirect3D->CheckDeviceFormat(
							m_GraphicCardNo,
							D3DDEVTYPE_HAL,
							BaseFormat,
							0,
							D3DRTYPE_TEXTURE,
							g_TextureFormats[i] );
		if SUCCEEDED( hr )
		{
			Log_PrintLine( 0x000000, "%s", GetPixelFormat(g_TextureFormats[i]) );
			m_TextureFormats[m_TextureFormatCount++] = g_TextureFormats[i];
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// レンダリングターゲットテクスチャフォーマットから使用可能なものを検索
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "調査" );
	Log_PrintCellKind( "使用可能な<BR>レンダリングターゲット<BR>フォーマット" );
	Log_CellBegin( 0 );

	for ( Sint32 i = 0; g_TextureFormats[i] != D3DFMT_UNKNOWN; i++ )
	{
		hr = m_pDirect3D->CheckDeviceFormat(
							m_GraphicCardNo,
							D3DDEVTYPE_HAL,
							BaseFormat,
							D3DUSAGE_RENDERTARGET,
							D3DRTYPE_TEXTURE,
							g_TextureFormats[i] );
		if SUCCEEDED( hr )
		{
			hr = m_pDirect3D->CheckDeviceFormat(
								m_GraphicCardNo,
								D3DDEVTYPE_HAL,
								BaseFormat,
								D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
								D3DRTYPE_TEXTURE,
								g_TextureFormats[i] );
			if SUCCEEDED( hr )
			{
				m_TargetAlphaFormats[m_TargetAlphaFormatCount++] = g_TextureFormats[i];
				m_TargetFormats[m_TargetFormatCount++] = g_TextureFormats[i];
				Log_PrintTable( 128, GetPixelFormat(g_TextureFormats[i]), "アルファブレンド ○" );
			}
			else
			{
				m_TargetFormats[m_TargetFormatCount++] = g_TextureFormats[i];
				Log_PrintTable( 128, GetPixelFormat(g_TextureFormats[i]), "アルファブレンド ×" );
			}
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// 深度バッファフォーマットから使用可能なものを検索
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "調査" );
	Log_PrintCellKind( "使用可能な<BR>デプスステンシル<BR>フォーマット" );
	Log_CellBegin( 0 );

	for ( Sint32 i = 0; g_DepthFormats[i] != D3DFMT_UNKNOWN; i++ )
	{
		hr = m_pDirect3D->CheckDeviceFormat(
								m_GraphicCardNo,
								D3DDEVTYPE_HAL,
								BaseFormat,
								D3DUSAGE_DEPTHSTENCIL,
								D3DRTYPE_SURFACE,
								g_DepthFormats[i] );
		if SUCCEEDED( hr )
		{
			hr = m_pDirect3D->CheckDeviceFormat(
									m_GraphicCardNo,
									D3DDEVTYPE_HAL,
									BaseFormat,
									D3DUSAGE_DEPTHSTENCIL,
									D3DRTYPE_TEXTURE,
									g_DepthFormats[i] );

			if SUCCEEDED( hr )
			{
				m_DepthTextureFormats[ m_DepthTextureFormatCount++ ] = g_DepthFormats[i];
				m_DepthSurfaceFormats[ m_DepthSurfaceFormatCount++ ] = g_DepthFormats[i];
				Log_PrintTable( 128, GetPixelFormat(g_DepthFormats[i]), "ハードウェアシャドウマップ ○" );
			}
			else
			{
				m_DepthSurfaceFormats[ m_DepthSurfaceFormatCount++ ] = g_DepthFormats[i];
				Log_PrintTable( 128, GetPixelFormat(g_DepthFormats[i]), "ハードウェアシャドウマップ ×" );
			}
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// R2VBのサポートチェック
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "調査" );
	Log_PrintCellKind( "R2VBの使用可能チェック" );
	Log_CellBegin( 0 );

	hr = m_pDirect3D->CheckDeviceFormat(
						D3DADAPTER_DEFAULT,
						D3DDEVTYPE_HAL,
						BaseFormat,
						0,
						D3DRTYPE_SURFACE,
						D3DFMT_R2VB );
	if SUCCEEDED( hr )
	{
		Log_PrintLine( 0x000080, "Render to VertexBuffer をサポートする" );
	}
	else
	{
		Log_PrintLine( 0x800000, "Render to VertexBuffer をサポートしない" );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// サーフェイスフォーマットテーブル
	//---------------------------------------------------------------
	CreateSurfaceFormatTable();

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::CheckGraphicCardCaps( void )
{
	D3DCAPS9 Caps;

	//-----------------------------------------------------------
	// ハードウェアデバイスの性能を取得
	//-----------------------------------------------------------
	m_pDirect3D->GetDeviceCaps( m_GraphicCardNo, D3DDEVTYPE_HAL, &Caps );
	GetDeviceCaps( &Caps, &m_DeviceInfo );

	//-----------------------------------------------------------
	// ハードウェアデバイスの性能を列挙
	//-----------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "調査" );
	Log_PrintCellKind( "ビデオカード性能" );
	Log_CellBegin( 0 );

	Log_PrintTable( 256, "ピュアデバイス", "[ %s ]", m_DeviceInfo.IsPureDevice ? "○" : "×" );
	Log_PrintTable( 256, "キューブマップ", "[ %s ]", m_DeviceInfo.IsCubeTexture ? "○" : "×" );
	Log_PrintTable( 256, "ヴォリュームマップ", "[ %s ]", m_DeviceInfo.IsVolumeTexture ? "○" : "×" );
	Log_PrintTable( 256, "動的テクスチャ", "[ %s ]", m_DeviceInfo.IsDynamicTexture ? "○" : "×" );
	Log_PrintTable( 256, "異方性フィルタ：拡大", "[ %s ]", m_DeviceInfo.IsMagAnisotropy ? "○" : "×" );
	Log_PrintTable( 256, "異方性フィルタ：縮小", "[ %s ]", m_DeviceInfo.IsMinAnisotropy ? "○" : "×" );

	Log_PrintTable( 256, "テクスチャ最大横幅", "[ %u ]", m_DeviceInfo.MaxTextureWidth );
	Log_PrintTable( 256, "テクスチャ最大縦幅", "[ %u ]", m_DeviceInfo.MaxTextureHeight );
	Log_PrintTable( 256, "テクスチャ異方性の次数", "[ %u ]", m_DeviceInfo.MaxAnisotropy );

	Log_PrintTable( 256, "テクスチャ２の累乗制限", "[ %s ]", m_DeviceInfo.IsSupportNonePow2Texture ? "なし" : "あり" );
	Log_PrintTable( 256, "テクスチャ２の累乗制限の限定解除", "[ %s ]", m_DeviceInfo.IsSupportNonePow2ConditionalTexture ? "あり" : "なし" );
	Log_PrintTable( 256, "テクスチャ正方形制限", "[ %s ]", m_DeviceInfo.IsSupportNoneSquareTexture ? "なし" : "あり" );

	Log_PrintTable( 256, "最大プリミティブ数", "[ %u ]", m_DeviceInfo.MaxPrimitiveCount );
	Log_PrintTable( 256, "最大インデックス数", "[ %u ]", m_DeviceInfo.MaxVertexIndex );
	Log_PrintTable( 256, "頂点シェーダーバージョン", "[ %u.%u ]", D3DSHADER_VERSION_MAJOR(m_DeviceInfo.VertexShaderVersion), D3DSHADER_VERSION_MINOR(m_DeviceInfo.VertexShaderVersion) );
	Log_PrintTable( 256, "頂点シェーダー命令数", "[ %u ]", m_DeviceInfo.VertexShaderInstructions );
	Log_PrintTable( 256, "頂点シェーダー定数レジスタ数", "[ %u ]", m_DeviceInfo.VertexShaderConstMax );
	Log_PrintTable( 256, "ピクセルシェーダーバージョン", "[ %u.%u ]", D3DSHADER_VERSION_MAJOR(m_DeviceInfo.PixelShaderVersion), D3DSHADER_VERSION_MINOR(m_DeviceInfo.PixelShaderVersion) );
	Log_PrintTable( 256, "ピクセルシェーダー命令数", "[ %u ]", m_DeviceInfo.PixelShaderInstructions );
	Log_PrintTable( 256, "動的フロー制御命令のネスティング", "[ %u ]", m_DeviceInfo.DynamicFlowControlDepth );
	Log_PrintTable( 256, "静的フロー制御命令のネスティング", "[ %u ]", m_DeviceInfo.StaticFlowControlDepth );

	Log_PrintTable( 256, "マルチレンダリングターゲット数", "[ %u ]", m_DeviceInfo.MultiRenderTargetCount );

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::GetDeviceCaps( D3DCAPS9 *pCaps, DEVICEINFORMATION *pDevInfo )
{
	// ピュアデバイス
	pDevInfo->IsPureDevice							= (pCaps->DevCaps & D3DDEVCAPS_PUREDEVICE) != 0;
	// テクスチャ
	pDevInfo->MaxTextureWidth						= pCaps->MaxTextureWidth;
	pDevInfo->MaxTextureHeight						= pCaps->MaxTextureHeight;
	pDevInfo->MaxAnisotropy							= pCaps->MaxAnisotropy;
	pDevInfo->IsDynamicTexture						= (pCaps->Caps2 & D3DCAPS2_DYNAMICTEXTURES) != 0;
	pDevInfo->IsMagAnisotropy						= (pCaps->TextureFilterCaps & D3DPTFILTERCAPS_MAGFANISOTROPIC) != 0;
	pDevInfo->IsMinAnisotropy						= (pCaps->TextureFilterCaps & D3DPTFILTERCAPS_MINFANISOTROPIC) != 0;
	// テクスチャ
	pDevInfo->IsCubeTexture							= (pCaps->TextureCaps & D3DPTEXTURECAPS_CUBEMAP) != 0;
	pDevInfo->IsVolumeTexture						= (pCaps->TextureCaps & D3DPTEXTURECAPS_VOLUMEMAP) != 0;
	pDevInfo->IsSupportNonePow2Texture				= (pCaps->TextureCaps & D3DPTEXTURECAPS_POW2) == 0;
	pDevInfo->IsSupportNonePow2ConditionalTexture	= (pCaps->TextureCaps & D3DPTEXTURECAPS_NONPOW2CONDITIONAL) != 0;
	pDevInfo->IsSupportNoneSquareTexture			= (pCaps->TextureCaps & D3DPTEXTURECAPS_SQUAREONLY) == 0;
	// 他
	pDevInfo->MaxPrimitiveCount						= pCaps->MaxPrimitiveCount;
	pDevInfo->MaxVertexIndex						= pCaps->MaxVertexIndex;
	// シェーダー
	pDevInfo->DynamicFlowControlDepth				= pCaps->VS20Caps.DynamicFlowControlDepth;
	pDevInfo->StaticFlowControlDepth				= pCaps->VS20Caps.StaticFlowControlDepth;
	pDevInfo->VertexShaderVersion					= pCaps->VertexShaderVersion;
	pDevInfo->VertexShaderInstructions				= pCaps->MaxVShaderInstructionsExecuted;
	pDevInfo->VertexShaderConstMax					= pCaps->MaxVertexShaderConst;
	pDevInfo->PixelShaderVersion					= pCaps->PixelShaderVersion;
	pDevInfo->PixelShaderInstructions				= pCaps->MaxPShaderInstructionsExecuted;
	// マルチレンダリングターゲット
	pDevInfo->MultiRenderTargetCount				= pCaps->NumSimultaneousRTs;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::GetAnisotropyFilterSupport( Bool &IsMin, Bool &IsMag, Sint32 &Max )
{
	IsMag = m_DeviceInfo.IsMagAnisotropy;
	IsMin = m_DeviceInfo.IsMinAnisotropy;
	Max = m_DeviceInfo.MaxAnisotropy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::EnableHighlColorScreen( void )
{
	m_IsHighColor = true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HMONITOR CGraphicCard::GetMonitorHandle( void )
{
	return m_pDirect3D->GetAdapterMonitor( m_GraphicCardNo );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::GetPixelShaderSupport( Uint16 Major, Uint16 Minor )
{
	return m_DeviceInfo.PixelShaderVersion >= D3DPS_VERSION( Major, Minor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::GetNonePow2ConditionalTextureSupport( void )
{
	return m_DeviceInfo.IsSupportNonePow2ConditionalTexture;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::GetNonePow2TextureSupport( void )
{
	return m_DeviceInfo.IsSupportNonePow2Texture;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::GetNoneSquareTextureSupport( void )
{
	return m_DeviceInfo.IsSupportNoneSquareTexture;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::IsHightColorMode( void )
{
	return m_IsHighColor;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::IsNVPerfHUDEnable( void )
{
	return m_IsHVPerfHUD;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CGraphicCard::GetDeviceTypeNo( void )
{
	// 指定バーテックスシェーダーを完全にサポート？
	if ( m_DeviceInfo.VertexShaderVersion >= m_MaxUseVertexShaderVersion )
	{
		// 32Bitインデックスをサポート？
		if ( (m_DeviceInfo.MaxPrimitiveCount > 0xFFFF) && (m_DeviceInfo.MaxVertexIndex > 0xFFFF) )
		{
			// ピュアデバイスをサポート？
			if ( m_DeviceInfo.IsPureDevice )
			{
				return DEVICE_CREATE_PUREDEVICE;
			}
			else
			{
				return DEVICE_CREATE_HARDWARE_TNL;
			}
		}
	}

	return DEVICE_CREATE_SOFTWARE_TNL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
D3DPRESENT_PARAMETERS CGraphicCard::MakePresentParameters( Bool IsWindow, Bool IsHightColor, Bool IsLockEnableBackBuffer, Bool IsWaitVSync )
{
	Sint32 Width, Height;
	D3DPRESENT_PARAMETERS PresentParam;
	D3DFORMAT ScreenFormat = D3DFMT_UNKNOWN;
	Sint32 RefreshRate = 0;

	//-----------------------------------------------------------
	// 画面サイズ取得
	//-----------------------------------------------------------
	m_pCore->GetScreenData( &Width, &Height, NULL );

	//-----------------------------------------------------------
	// モード
	//-----------------------------------------------------------
	if ( IsWindow )
	{
		ScreenFormat = m_WindowModeInfo.Format;
		RefreshRate = 0;
	}
	else
	{
		if ( IsHightColor )
		{
			for ( Sint32 i = 0; i < m_ScreenTypeCount; i++ )
			{
				if ( m_ScreenType[i].Format == m_FullScreen16BitInfo )
				{
					if ( m_ScreenType[i].Width == (Uint32)Width )
					{
						if ( m_ScreenType[i].Height == (Uint32)Height )
						{
							ScreenFormat = m_ScreenType[i].Format;
							RefreshRate = m_ScreenType[i].RefreshRate;
						}
					}
				}
			}
		}
		else
		{
			for ( Sint32 i = 0; i < m_ScreenTypeCount; i++ )
			{
				if ( m_ScreenType[i].Format == m_FullScreen32BitInfo )
				{
					if ( m_ScreenType[i].Width == (Uint32)Width )
					{
						if ( m_ScreenType[i].Height == (Uint32)Height )
						{
							ScreenFormat = m_ScreenType[i].Format;
							RefreshRate = m_ScreenType[i].RefreshRate;
						}
					}
				}
			}
		}
	}

	//-----------------------------------------------------------
	// パラメーター生成
	//-----------------------------------------------------------
	PresentParam.BackBufferWidth			= (Uint32)Width;
	PresentParam.BackBufferHeight			= (Uint32)Height;
	PresentParam.BackBufferFormat			= ScreenFormat;
	PresentParam.BackBufferCount			= 1;
	PresentParam.MultiSampleType			= D3DMULTISAMPLE_NONE;
	PresentParam.MultiSampleQuality			= 0;
	PresentParam.SwapEffect					= D3DSWAPEFFECT_DISCARD;
	PresentParam.hDeviceWindow				= m_pCore->GetWindowHandle();
	PresentParam.Windowed					= IsWindow;
	PresentParam.EnableAutoDepthStencil		= false;
	PresentParam.AutoDepthStencilFormat		= D3DFMT_UNKNOWN;
	PresentParam.Flags						= 0;
	PresentParam.FullScreen_RefreshRateInHz	= RefreshRate;
	PresentParam.PresentationInterval		= D3DPRESENT_INTERVAL_DEFAULT;

	if ( !IsWaitVSync || m_pCore->IsBenchMode() )
	{
		PresentParam.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}

	if ( IsLockEnableBackBuffer )
	{
		PresentParam.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	}

	return PresentParam;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
D3DFORMAT CGraphicCard::GetFormat( eSurfaceFormat Format )
{
	return m_SurfaceFormatTbl[Format];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::CheckAlphaBlending( D3DFORMAT Format )
{
	Sint32 Max = m_TargetAlphaFormatCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		if ( Format == m_TargetAlphaFormats[i] )
		{
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::CreateSurfaceFormatTable( void )
{
	//------------------------------------------------------------
	// フォーマット情報検索
	//------------------------------------------------------------
	for ( Sint32 Format = 0; Format < FORMAT_MAX; Format++ )
	{
		D3DFORMAT SurfaceFormat = D3DFMT_UNKNOWN;

		switch ( Format )
		{
		// 32Bitレンダリングターゲット
		case FORMAT_TARGET_UCHAR4:
			{
				static D3DFORMAT FmtTbl[] = {
					D3DFMT_A8R8G8B8, D3DFMT_UNKNOWN,
				};

				for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_TargetAlphaFormatCount; j++ )
					{
						if ( FmtTbl[i] == m_TargetAlphaFormats[j] )
						{
							SurfaceFormat = FmtTbl[i];
							goto EXIT;
						}
					}
				}
			}
			break;

		// HDRレンダリングターゲット
		case FORMAT_TARGET_FLOAT4_ALPHA:
			{
				static D3DFORMAT FmtTbl[] = {
					D3DFMT_A16B16G16R16F, D3DFMT_A32B32G32R32F, D3DFMT_A8R8G8B8, D3DFMT_UNKNOWN,
				};

				for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_TargetAlphaFormatCount; j++ )
					{
						if ( FmtTbl[i] == m_TargetAlphaFormats[j] )
						{
							SurfaceFormat = FmtTbl[i];
							goto EXIT;
						}
					}
				}
			}
			break;

		// シャドウマップ用
		case FORMAT_TARGET_FLOAT1:
			{
				static D3DFORMAT FmtTbl[] = {
					D3DFMT_R32F, D3DFMT_R16F, D3DFMT_A32B32G32R32F, D3DFMT_A16B16G16R16F, D3DFMT_UNKNOWN,
				};

				for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_TargetFormatCount; j++ )
					{
						if ( FmtTbl[i] == m_TargetFormats[j] )
						{
							SurfaceFormat = FmtTbl[i];
							goto EXIT;
						}
					}
				}
			}
			break;

		// ソフトシャドウマップ用
		case FORMAT_TARGET_FLOAT2:
			{
				static D3DFORMAT FmtTbl[] = {
					D3DFMT_G16R16F, D3DFMT_G32R32F, D3DFMT_A16B16G16R16F, D3DFMT_A32B32G32R32F, D3DFMT_UNKNOWN,
				};

				for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_TargetFormatCount; j++ )
					{
						if ( FmtTbl[i] == m_TargetFormats[j] )
						{
							SurfaceFormat = FmtTbl[i];
							goto EXIT;
						}
					}
				}
			}
			break;

		// 深度＆速度マップ用レンダリングターゲット
		case FORMAT_TARGET_FLOAT4:
			{
				static D3DFORMAT FmtTbl[] = {
					D3DFMT_A16B16G16R16F, D3DFMT_A32B32G32R32F, D3DFMT_UNKNOWN,
				};

				for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_TargetFormatCount; j++ )
					{
						if ( FmtTbl[i] == m_TargetFormats[j] )
						{
							SurfaceFormat = FmtTbl[i];
							goto EXIT;
						}
					}
				}
			}
			break;

		// 32Bitテクスチャフォーマットに準拠
		case FORMAT_TEXTURE_32BIT:
			{
				static D3DFORMAT FmtTbl[] = {
					D3DFMT_A8R8G8B8, D3DFMT_A4R4G4B4, D3DFMT_UNKNOWN,
				};

				for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_TextureFormatCount; j++ )
					{
						if ( FmtTbl[i] == m_TextureFormats[j] )
						{
							SurfaceFormat = FmtTbl[i];
							goto EXIT;
						}
					}
				}
			}
			break;

		// 16Bitテクスチャフォーマットに準拠
		case FORMAT_TEXTURE_16BIT:
			{
				static D3DFORMAT FmtTbl[] = {
					D3DFMT_A4R4G4B4, D3DFMT_A8R8G8B8, D3DFMT_UNKNOWN,
				};

				for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_TextureFormatCount; j++ )
					{
						if ( FmtTbl[i] == m_TextureFormats[j] )
						{
							SurfaceFormat = FmtTbl[i];
							goto EXIT;
						}
					}
				}
			}
			break;

		// DXT圧縮フォーマットテクスチャ
		case FORMAT_TEXTURE_DXT:
			{
				static D3DFORMAT FmtTbl[] = {
					D3DFMT_DXT5, D3DFMT_DXT3, D3DFMT_DXT1, D3DFMT_A8R8G8B8, D3DFMT_A4R4G4B4, D3DFMT_A1R5G5B5, D3DFMT_UNKNOWN,
				};

				for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_TextureFormatCount; j++ )
					{
						if ( FmtTbl[i] == m_TextureFormats[j] )
						{
							SurfaceFormat = FmtTbl[i];
							goto EXIT;
						}
					}
				}
			}
			break;

		// 深度バッファ
		case FORMAT_DEPTHBUFFER_SURFACE:
			{
				for ( Sint32 i = 0; g_DepthFormats[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_DepthSurfaceFormatCount; j++ )
					{
						if ( g_DepthFormats[i] == m_DepthSurfaceFormats[j] )
						{
							SurfaceFormat = g_DepthFormats[i];
							goto EXIT;
						}
					}
				}
			}
			break;

		// 深度バッファ
		case FORMAT_DEPTHBUFFER_TEXTURE:
			{
				for ( Sint32 i = 0; g_DepthFormats[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_DepthTextureFormatCount; j++ )
					{
						if ( g_DepthFormats[i] == m_DepthTextureFormats[j] )
						{
							SurfaceFormat = g_DepthFormats[i];
							goto EXIT;
						}
					}
				}
			}
			break;
		}
EXIT:
		m_SurfaceFormatTbl[Format] = SurfaceFormat;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CGraphicCard::GetScreenModeCount( Bool IsFullColor )
{
	Sint32 Count = 0;

	if ( IsFullColor )
	{
		for ( Sint32 i = 0; i < m_ScreenTypeCount; i++ )
		{
			if ( m_ScreenType[i].Format == m_FullScreen16BitInfo )
			{
				Count++;
			}
		}
	}
	else
	{
		for ( Sint32 i = 0; i < m_ScreenTypeCount; i++ )
		{
			if ( m_ScreenType[i].Format == m_FullScreen32BitInfo )
			{
				Count++;
			}
		}
	}

	return Count;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::GetScreenMode( Bool IsFullColor, Sint32 No, Sint32 &Width, Sint32 &Height )
{
	if ( IsFullColor )
	{
		for ( Sint32 i = 0; i < m_ScreenTypeCount; i++ )
		{
			if ( m_ScreenType[i].Format == m_FullScreen32BitInfo )
			{
				if ( No-- == 0 )
				{
					Width = m_ScreenType[i].Width;
					Height = m_ScreenType[i].Height;
					return;
				}
			}
		}
	}
	else
	{
		for ( Sint32 i = 0; i < m_ScreenTypeCount; i++ )
		{
			if ( m_ScreenType[i].Format == m_FullScreen16BitInfo )
			{
				if ( No-- == 0 )
				{
					Width = m_ScreenType[i].Width;
					Height = m_ScreenType[i].Height;
					return;
				}
			}
		}
	}

	Width = 0;
	Height = 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CGraphicCard::CreateRenderTargetTextureSizeCount( void )
{
	Sint32 Count = 0;

	if ( m_DeviceInfo.MaxTextureWidth <  m_DeviceInfo.MaxTextureHeight )
	{
		for ( Sint32 i = 32; i <= m_DeviceInfo.MaxTextureWidth; i <<= 1 ) Count++;
	}
	else
	{
		for ( Sint32 i = 32; i <= m_DeviceInfo.MaxTextureHeight; i <<= 1 ) Count++;
	}

	return Count;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::CreateRenderTargetTextureSize( Sint32 No, Sint32 *pWidth, Sint32 *pHeight )
{
	Sint32 Count = 0;

	if ( m_DeviceInfo.MaxTextureWidth <  m_DeviceInfo.MaxTextureHeight )
	{
		for ( Sint32 i = 32; i <= m_DeviceInfo.MaxTextureWidth; i <<= 1 )
		{
			if ( Count++ == No )
			{
				*pWidth = *pHeight = i;
				return;
			}
		}
	}
	else
	{
		for ( Sint32 i = 32; i <= m_DeviceInfo.MaxTextureHeight; i <<= 1 )
		{
			if ( Count++ == No )
			{
				*pWidth = *pHeight = i;
				return;
			}
		}
	}

	*pWidth = *pHeight = 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::GetGraphicCardName( char *pName, Sint32 NameSize )
{
	StringCbCopy( pName, NameSize, m_GraphicCardName );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::GetVertexShaderVersion( char *pName, Sint32 NameSize )
{
	StringCbPrintf( pName, NameSize, "VertexShader %u.%u", D3DSHADER_VERSION_MAJOR(m_DeviceInfo.VertexShaderVersion), D3DSHADER_VERSION_MINOR(m_DeviceInfo.VertexShaderVersion) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::GetPixelShaderVersion( char *pName, Sint32 NameSize )
{
	StringCbPrintf( pName, NameSize, "PixelShader %u.%u", D3DSHADER_VERSION_MAJOR(m_DeviceInfo.PixelShaderVersion), D3DSHADER_VERSION_MINOR(m_DeviceInfo.PixelShaderVersion) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Renderer::IRender *CGraphicCard::CreateRender( Bool IsLockEnableBackBuffer, Bool IsWaitVSync )
{
	if ( m_pRender == NULL )
	{
		Bool IsWindow;
		m_pCore->GetScreenData( NULL, NULL, &IsWindow );

		m_pRender = new Renderer::CRender( this, IsWindow, IsLockEnableBackBuffer, IsWaitVSync );
		if ( m_pRender->GetDriverDevicePointer() == NULL )
		{
			SAFE_RELEASE( m_pRender );
		}			
	}
	else
	{
		m_pRender->AddRef();
	}

	return m_pRender;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DI CGraphicCard::GetTextureMaxSize( void )
{
	return Math::Point2DI( m_DeviceInfo.MaxTextureWidth, m_DeviceInfo.MaxTextureHeight );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DI CGraphicCard::GetTextureSize( Math::Point2DI Size, eSurfaceFormat Format, Bool IsMipmap )
{
	Math::Point2DI SizeMax = GetTextureMaxSize();
	Math::Point2DI SizeNew;

	// 制限つき２の累乗縛りあり
	if ( GetNonePow2ConditionalTextureSupport() )
	{
		// 圧縮
		if ( (Format == FORMAT_TEXTURE_DXT) || IsMipmap )
		{
			// ２の累乗の変更
			for ( SizeNew.x = 1; SizeNew.x < Size.x; SizeNew.x <<= 1 );
			for ( SizeNew.y = 1; SizeNew.y < Size.y; SizeNew.y <<= 1 );
		}
		// 非圧縮
		else
		{
			// そのまま
			SizeNew = Size;
		}
	}
	// ２の累乗縛りなし？
	ef ( GetNonePow2TextureSupport() )
	{
		// そのまま
		SizeNew = Size;
	}
	// 縛り
	else
	{
		// ２の累乗の変更
		for ( SizeNew.x = 1; SizeNew.x < Size.x; SizeNew.x <<= 1 );
		for ( SizeNew.y = 1; SizeNew.y < Size.y; SizeNew.y <<= 1 );
	}

	// 正方形縛りあり？
	if ( !GetNoneSquareTextureSupport() )
	{
		// 大きい方に合わせて正方形にする
		if ( SizeNew.x < SizeNew.y )
		{
			SizeNew.x = SizeNew.y;
		}
		else
		{
			SizeNew.y = SizeNew.x;
		}
	}

	// サポートサイズ超えてる？
	if ( SizeNew.x > SizeMax.x ) SizeNew.x = SizeMax.x;
	if ( SizeNew.y > SizeMax.y ) SizeNew.y = SizeMax.y;

	return SizeNew;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCore *CGraphicCard::GetCorePointer( void )
{
	return m_pCore;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CGraphicCard::CreateDeviceObject( D3DDEVTYPE DeviceType, Sint32 CreateFlag, D3DPRESENT_PARAMETERS &Param, IDirect3DDevice9 *&pDevice )
{
	HRESULT hr = m_pDirect3D->CreateDevice(
					m_GraphicCardNo,
					DeviceType,
					m_pCore->GetWindowHandle(),
					CreateFlag,
					&Param,
					&pDevice );
	return hr;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
char *CGraphicCard::GetPixelFormat( D3DFORMAT Format, char *pErrStr, Sint32 ErrStrSize )
{
	static char String[64] = "";

	switch ( (Uint32)Format )
	{
	case D3DFMT_UNKNOWN:			StringCbCopy( String, sizeof(String), "UNKNOWN" );			break;
	case D3DFMT_R8G8B8:				StringCbCopy( String, sizeof(String), "R8G8B8" );			break;
	case D3DFMT_A8R8G8B8:			StringCbCopy( String, sizeof(String), "A8R8G8B8" );			break;
	case D3DFMT_X8R8G8B8:			StringCbCopy( String, sizeof(String), "X8R8G8B8" );			break;
	case D3DFMT_R5G6B5:				StringCbCopy( String, sizeof(String), "R5G6B5" );			break;
	case D3DFMT_X1R5G5B5:			StringCbCopy( String, sizeof(String), "X1R5G5B5" );			break;
	case D3DFMT_A1R5G5B5:			StringCbCopy( String, sizeof(String), "A1R5G5B5" );			break;
	case D3DFMT_A4R4G4B4:			StringCbCopy( String, sizeof(String), "A4R4G4B4" );			break;
	case D3DFMT_R3G3B2:				StringCbCopy( String, sizeof(String), "R3G3B2" );			break;
	case D3DFMT_A8:					StringCbCopy( String, sizeof(String), "A8" );				break;
	case D3DFMT_A8R3G3B2:			StringCbCopy( String, sizeof(String), "A8R3G3B2" );			break;
	case D3DFMT_X4R4G4B4:			StringCbCopy( String, sizeof(String), "X4R4G4B4" );			break;
	case D3DFMT_A2B10G10R10:		StringCbCopy( String, sizeof(String), "A2B10G10R10" );		break;
	case D3DFMT_A8B8G8R8:			StringCbCopy( String, sizeof(String), "A8B8G8R8" );			break;
	case D3DFMT_X8B8G8R8:			StringCbCopy( String, sizeof(String), "X8B8G8R8" );			break;
	case D3DFMT_G16R16:				StringCbCopy( String, sizeof(String), "G16R16" );			break;
	case D3DFMT_A2R10G10B10:		StringCbCopy( String, sizeof(String), "A2R10G10B10" );		break;
	case D3DFMT_A16B16G16R16:		StringCbCopy( String, sizeof(String), "A16B16G16R16" );		break;
	case D3DFMT_A8P8:				StringCbCopy( String, sizeof(String), "A8P8" );				break;
	case D3DFMT_P8:					StringCbCopy( String, sizeof(String), "P8" );				break;
	case D3DFMT_L8:					StringCbCopy( String, sizeof(String), "L8" );				break;
	case D3DFMT_L16:				StringCbCopy( String, sizeof(String), "L16" );				break;
	case D3DFMT_A8L8:				StringCbCopy( String, sizeof(String), "A8L8" );				break;
	case D3DFMT_A4L4:				StringCbCopy( String, sizeof(String), "A4L4" );				break;
	case D3DFMT_V8U8:				StringCbCopy( String, sizeof(String), "V8U8" );				break;
	case D3DFMT_Q8W8V8U8:			StringCbCopy( String, sizeof(String), "Q8W8V8U8" );			break;
	case D3DFMT_V16U16:				StringCbCopy( String, sizeof(String), "V16U16" );			break;
	case D3DFMT_Q16W16V16U16:		StringCbCopy( String, sizeof(String), "Q16W16V16U16" );		break;
	case D3DFMT_CxV8U8:				StringCbCopy( String, sizeof(String), "CxV8U8" );			break;
	case D3DFMT_L6V5U5:				StringCbCopy( String, sizeof(String), "L6V5U5" );			break;
	case D3DFMT_X8L8V8U8:			StringCbCopy( String, sizeof(String), "X8L8V8U8" );			break;
	case D3DFMT_A2W10V10U10:		StringCbCopy( String, sizeof(String), "A2W10V10U10" );		break;
	case D3DFMT_G8R8_G8B8:			StringCbCopy( String, sizeof(String), "G8R8_G8B8" );		break;
	case D3DFMT_R8G8_B8G8:			StringCbCopy( String, sizeof(String), "R8G8_B8G8" );		break;
	case D3DFMT_DXT1:				StringCbCopy( String, sizeof(String), "DXT1" );				break;
	case D3DFMT_DXT2:				StringCbCopy( String, sizeof(String), "DXT2" );				break;
	case D3DFMT_DXT3:				StringCbCopy( String, sizeof(String), "DXT3" );				break;
	case D3DFMT_DXT4:				StringCbCopy( String, sizeof(String), "DXT4" );				break;
	case D3DFMT_DXT5:				StringCbCopy( String, sizeof(String), "DXT5" );				break;
	case D3DFMT_UYVY:				StringCbCopy( String, sizeof(String), "UYVY" );				break;
	case D3DFMT_YUY2:				StringCbCopy( String, sizeof(String), "YUY2" );				break;
	case D3DFMT_D16_LOCKABLE:		StringCbCopy( String, sizeof(String), "D16_LOCKABLE" );		break;
	case D3DFMT_D32:				StringCbCopy( String, sizeof(String), "D32" );				break;
	case D3DFMT_D15S1:				StringCbCopy( String, sizeof(String), "D15S1" );			break;
	case D3DFMT_D24S8:				StringCbCopy( String, sizeof(String), "D24S8" );			break;
	case D3DFMT_D24X8:				StringCbCopy( String, sizeof(String), "D24X8" );			break;
	case D3DFMT_D24X4S4:			StringCbCopy( String, sizeof(String), "D24X4S4" );			break;
	case D3DFMT_D32F_LOCKABLE:		StringCbCopy( String, sizeof(String), "D32F_LOCKABLE" );	break;
	case D3DFMT_D24FS8:				StringCbCopy( String, sizeof(String), "D24FS8" );			break;
	case D3DFMT_DF24:				StringCbCopy( String, sizeof(String), "DF24" );				break;
	case D3DFMT_D16:				StringCbCopy( String, sizeof(String), "D16" );				break;
	case D3DFMT_R2VB:				StringCbCopy( String, sizeof(String), "R2VB" );				break;
	case D3DFMT_VERTEXDATA:			StringCbCopy( String, sizeof(String), "VERTEXDATA" );		break;
	case D3DFMT_INDEX16:			StringCbCopy( String, sizeof(String), "INDEX16" );			break;
	case D3DFMT_INDEX32:			StringCbCopy( String, sizeof(String), "INDEX32" );			break;
	case D3DFMT_R16F:				StringCbCopy( String, sizeof(String), "R16F" );				break;
	case D3DFMT_G16R16F:			StringCbCopy( String, sizeof(String), "G16R16F" );			break;
	case D3DFMT_A16B16G16R16F:		StringCbCopy( String, sizeof(String), "A16B16G16R16F" );	break;
	case D3DFMT_R32F:				StringCbCopy( String, sizeof(String), "R32F" );				break;
	case D3DFMT_G32R32F:			StringCbCopy( String, sizeof(String), "G32R32F" );			break;
	case D3DFMT_A32B32G32R32F:		StringCbCopy( String, sizeof(String), "A32B32G32R32F" );	break;
	}

	if ( pErrStr != NULL ) StringCbCopy( pErrStr, ErrStrSize, String );

	return String;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
char *CGraphicCard::GetD3DError( HRESULT hr, char *pErrStr, Sint32 ErrStrSize )
{
	static char String[128] = "";

	switch ( hr )
	{
	case D3D_OK:							StringCbCopy( String, sizeof(String), "エラーは発生していない。" );																																					break;
	case D3DERR_CONFLICTINGRENDERSTATE:		StringCbCopy( String, sizeof(String), "現在設定されているレンダリング ステートは一緒に使用できない。" );																											break;
	case D3DERR_CONFLICTINGTEXTUREFILTER:	StringCbCopy( String, sizeof(String), "現在のテクスチャ フィルタは一緒に使用できない。" );																															break;
	case D3DERR_CONFLICTINGTEXTUREPALETTE:	StringCbCopy( String, sizeof(String), "現在のテクスチャは同時に使用できない。一般にマルチテクスチャ デバイスにおいて、同時に有効にされたパレット化テクスチャで同じパレットを共有する必要がある場合に発生する。" );	break;
	case D3DERR_DEVICELOST:					StringCbCopy( String, sizeof(String), "デバイスが失われていて、現時点では復元できないため、レンダリングは不可能である。" );																							break;
	case D3DERR_DEVICENOTRESET:				StringCbCopy( String, sizeof(String), "デバイスはリセットできない。" );																																				break;
	case D3DERR_DRIVERINTERNALERROR:		StringCbCopy( String, sizeof(String), "内部ドライバ エラー。" );																																					break;
	case D3DERR_INVALIDCALL:				StringCbCopy( String, sizeof(String), "メソッドの呼び出しが無効である。たとえば、メソッドのパラメータに無効な値が設定されている場合など。" );																		break;
	case D3DERR_INVALIDDEVICE:				StringCbCopy( String, sizeof(String), "要求されたデバイスの種類が有効でない。" );																																	break;
	case D3DERR_MOREDATA:					StringCbCopy( String, sizeof(String), "指定されたバッファ サイズに保持できる以上のデータが存在する。" );																											break;
	case D3DERR_NOTAVAILABLE:				StringCbCopy( String, sizeof(String), "このデバイスは、照会されたテクニックをサポートしていない。" );																												break;
	case D3DERR_NOTFOUND:					StringCbCopy( String, sizeof(String), "要求された項目が見つからなかった。" );																																		break;
	case D3DERR_OUTOFVIDEOMEMORY:			StringCbCopy( String, sizeof(String), "Direct3D が処理を行うのに十分なディスプレイ メモリがない。" );																												break;
	case D3DERR_TOOMANYOPERATIONS:			StringCbCopy( String, sizeof(String), "デバイスがサポートしている以上のテクスチャ フィルタリング処理を、アプリケーションが要求している。" );																		break;
	case D3DERR_UNSUPPORTEDALPHAARG:		StringCbCopy( String, sizeof(String), "アルファ チャネルに対して指定されているテクスチャ ブレンディング引数を、デバイスがサポートしていない。" );																	break;
	case D3DERR_UNSUPPORTEDALPHAOPERATION:	StringCbCopy( String, sizeof(String), "アルファ チャネルに対して指定されているテクスチャ ブレンディング処理を、デバイスがサポートしていない。" );																	break;
	case D3DERR_UNSUPPORTEDCOLORARG:		StringCbCopy( String, sizeof(String), "カラー値に対して指定されているテクスチャ ブレンディング引数を、デバイスがサポートしていない。" );																			break;
	case D3DERR_UNSUPPORTEDCOLOROPERATION:	StringCbCopy( String, sizeof(String), "カラー値に対して指定されているテクスチャ ブレンディング処理を、デバイスがサポートしていない。" );																			break;
	case D3DERR_UNSUPPORTEDFACTORVALUE:		StringCbCopy( String, sizeof(String), "デバイスが指定されたテクスチャ係数値をサポートしていない。" );																												break;
	case D3DERR_UNSUPPORTEDTEXTUREFILTER:	StringCbCopy( String, sizeof(String), "デバイスが指定されたテクスチャ フィルタをサポートしていない。" );																											break;
	case D3DERR_WRONGTEXTUREFORMAT:			StringCbCopy( String, sizeof(String), "テクスチャ サーフェスのピクセル フォーマットが有効でない。" );																												break;
	case E_FAIL:							StringCbCopy( String, sizeof(String), "Direct3D サブシステム内で原因不明のエラーが発生した。" );																													break;
	case E_INVALIDARG:						StringCbCopy( String, sizeof(String), "無効なパラメータが戻ってくる関数に渡された。" );																																break;
	case E_OUTOFMEMORY:						StringCbCopy( String, sizeof(String), "Direct3D が呼び出しを完了するための十分なメモリを割り当てることができなかった。" );																							break;
	case D3DXERR_CANNOTATTRSORT:			StringCbCopy( String, sizeof(String), "最適化テクニックとして属性のソート (D3DXMESHOPT_ATTRSORT) はサポートされていない。 " );																						break;
	case D3DXERR_CANNOTMODIFYINDEXBUFFER:	StringCbCopy( String, sizeof(String), "インデックス バッファを変更できない。 " );																																	break;
	case D3DXERR_INVALIDMESH:				StringCbCopy( String, sizeof(String), "メッシュが無効である。 " );																																					break;
	case D3DXERR_SKINNINGNOTSUPPORTED:		StringCbCopy( String, sizeof(String), "スキニングはサポートされていない。 " );																																		break;
	case D3DXERR_TOOMANYINFLUENCES:			StringCbCopy( String, sizeof(String), "指定された影響が多すぎる。 " );																																				break;
	case D3DXERR_INVALIDDATA:				StringCbCopy( String, sizeof(String), "データが無効である。" );																																						break;
	default:								StringCbCopy( String, sizeof(String), "未知のエラー。" );																																							break;
	}

	if ( pErrStr != NULL ) StringCbCopy( pErrStr, ErrStrSize, String );

	return String;
}

