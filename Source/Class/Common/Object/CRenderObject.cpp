

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Object/CRenderObject.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CVertexLayout.h"
#include "Class/Platform/Render/CRender.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRenderObject::CRenderObject( CRender *pRender, CRenderObjectMgr *pMgr )
	: CResourceObject	( pMgr )
	, m_pRender			( pRender )
	, m_pGraphicCard	( pRender->GetGraphicCardPointer() )
	, m_pCore			( pRender->GetGraphicCardPointer()->GetCorePointer() )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRenderObject::~CRenderObject()
{
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
char *CRenderObject::GetError( HRESULT hr )
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

	return String;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRender *CRenderObject::GetRenderPointer( void )
{
	return m_pRender;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CGraphicCard *CRenderObject::GetGraphicCardPointer( void )
{
	return m_pGraphicCard;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCore *CRenderObject::GetCorePointer( void )
{
	return m_pCore;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DI CRenderObject::GetTextureMaxSize( void )
{
	return m_pGraphicCard->GetTextureMaxSize();
}

