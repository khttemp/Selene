

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Peripheral/CKeyboard.h"
#include "Class/Common/Peripheral/CInput.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Peripheral;


//-----------------------------------------------------------------------------------
// SKeyBoardData
//-----------------------------------------------------------------------------------
static DIOBJECTDATAFORMAT g_KeyboardDataFormat[KEYBOARD_DATA_MAX];

static DIDATAFORMAT g_DIKeyboardDataFormat = { 
	sizeof(DIDATAFORMAT),
	sizeof(DIOBJECTDATAFORMAT),
	DIDF_RELAXIS,
	sizeof(SKeyBoardData),
	KEYBOARD_DATA_MAX,
	g_KeyboardDataFormat,
};


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CKeyboard::CKeyboard( IDirectInputDevice8 *pDevice )
{
	m_pDevice = pDevice;
	m_pDevice->AddRef();

	m_KeyBufferCount	= 0;
	m_KeyBufferMax		= 0;

	MemoryClear( &m_KeyboardData, sizeof(m_KeyboardData) );
	MemoryClear( m_KeyBuffer, sizeof(m_KeyBuffer) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CKeyboard::~CKeyboard()
{
	// デバイス解放
	SAFE_RELEASE( m_pDevice );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CKeyboard::Initialize( void )
{
	DIPROPDWORD diprop = { sizeof(DIPROPDWORD), sizeof(DIPROPHEADER) };
	DIDEVCAPS DiCaps = { sizeof(DIDEVCAPS) };
	HRESULT hr;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "初期化" );
	Log_PrintCellKind( "キーボード" );
	Log_CellBegin( 0 );

	//----------------------------------------------------------
	// データフォーマットの設定
	//----------------------------------------------------------
	for ( Sint32 i = 0; i < KEYBOARD_DATA_MAX; i ++ )
	{
		g_DIKeyboardDataFormat.rgodf[i].pguid	= &GUID_Key;
		g_DIKeyboardDataFormat.rgodf[i].dwOfs	= FIELD_OFFSET(SKeyBoardData, Key[i]);
		g_DIKeyboardDataFormat.rgodf[i].dwType	= 0x80000000 | DIDFT_BUTTON | DIDFT_ENUMCOLLECTION(i);
		g_DIKeyboardDataFormat.rgodf[i].dwFlags	= 0;
	}

	hr = m_pDevice->SetDataFormat( &g_DIKeyboardDataFormat );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF0000, "キーボードのデータフォーマットの設定に失敗" );
		SAFE_RELEASE( m_pDevice );
		goto EXIT;
	}

	//----------------------------------------------------------
	// バッファ・サイズを設定
	//----------------------------------------------------------
	diprop.diph.dwObj	= 0;
	diprop.diph.dwHow	= DIPH_DEVICE;
	diprop.dwData		= KEYBOARD_BUFFER_MAX;

	hr = m_pDevice->SetProperty( DIPROP_BUFFERSIZE, &diprop.diph );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF0000, "キーボードのプロパティの設定に失敗" );
		SAFE_RELEASE( m_pDevice );
		goto EXIT;
	}

	//----------------------------------------------------------
	// デバイス情報取得
	//----------------------------------------------------------
	m_pDevice->GetCapabilities( &DiCaps );

	Log_PrintLine( 0x000000, "%dキー キーボード", DiCaps.dwButtons );

	//----------------------------------------------------------
	// 入力制御開始
	//----------------------------------------------------------
	m_pDevice->Acquire();

EXIT:
	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CKeyboard::Refresh( void )
{
	HRESULT hr;

	//--------------------------------------------------------
	// キーバッファ
	//--------------------------------------------------------
	m_KeyBufferMax = KEYBOARD_BUFFER_MAX;
	m_KeyBufferCount = 0;
	hr = m_pDevice->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), m_KeyBuffer, &m_KeyBufferMax, 0 );
	if FAILED( hr )
	{
		m_pDevice->Acquire();
		m_KeyBufferMax		= 0;
		m_KeyBufferCount	= 0;
	}
	else
	{
		if ( hr == DI_BUFFEROVERFLOW )
		{
			// バッファがオーバーフローした
		}
	}

	//--------------------------------------------------------
	// キーボード状態取得
	//--------------------------------------------------------
	hr = m_pDevice->GetDeviceState( KEYBOARD_DATA_MAX, m_KeyboardData.Key );
	if FAILED( hr )
	{
		// デバイス再アクセス
		m_pDevice->Acquire();
		MemoryClear( m_KeyboardData.Key, sizeof(m_KeyboardData.Key) );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CKeyboard::GetKeyData( eVirtualKeyCode Key )
{
	return m_KeyboardData.Key[Key] < 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CKeyboard::ClearKeyBuffer( void )
{
	m_KeyBufferMax = 0;
	m_KeyBufferCount = 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eVirtualKeyCode CKeyboard::GetKeyBuffer( void )
{
	eVirtualKeyCode Key = SELENE_VK_DISABLE;

	if ( m_KeyBufferCount < m_KeyBufferMax )
	{
		if ( (m_KeyBuffer[m_KeyBufferCount].dwData & 0x80) == 0x80 )
		{
			Key = (eVirtualKeyCode)m_KeyBuffer[m_KeyBufferCount].dwOfs;
		}
		
		m_KeyBufferCount++;
	}

	return Key;
}

