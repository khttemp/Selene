

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Peripheral/CInputController.h"
#include "Class/Common/Peripheral/CMouse.h"
#include "Class/Common/Peripheral/CKeyboard.h"
#include "Class/Common/Peripheral/CJoystick.h"
#include "Class/Common/Core/CCore.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Peripheral;


//=============================================================================
// ACCESS TABLE
//=============================================================================
static const Uint32 g_PadSortBitTbl[] = {
	1U <<  0,		// BUTTON_AXIS1_UP
	1U <<  1,		// BUTTON_AXIS1_DOWN
	1U <<  2,		// BUTTON_AXIS1_LEFT
	1U <<  3,		// BUTTON_AXIS1_RIGHT

	1U <<  4,		// BUTTON_AXIS2_UP
	1U <<  5,		// BUTTON_AXIS2_DOWN
	1U <<  6,		// BUTTON_AXIS2_LEFT
	1U <<  7,		// BUTTON_AXIS2_RIGHT

	1U <<  8,		// BUTTON_AXIS3_UP
	1U <<  9,		// BUTTON_AXIS3_DOWN
	1U << 10,		// BUTTON_AXIS3_LEFT
	1U << 11,		// BUTTON_AXIS3_RIGHT

	1U << 12,		// BUTTON_AXIS3_UP
	1U << 13,		// BUTTON_AXIS3_DOWN
	1U << 14,		// BUTTON_AXIS3_LEFT
	1U << 15,		// BUTTON_AXIS3_RIGHT

	1U << 16,		// BUTTON_01
	1U << 17,		// BUTTON_02
	1U << 18,		// BUTTON_03
	1U << 19,		// BUTTON_04
	1U << 20,		// BUTTON_05
	1U << 21,		// BUTTON_06
	1U << 22,		// BUTTON_07
	1U << 23,		// BUTTON_08
	1U << 24,		// BUTTON_09
	1U << 25,		// BUTTON_10
	1U << 26,		// BUTTON_11
	1U << 27,		// BUTTON_12
	1U << 28,		// BUTTON_13
	1U << 29,		// BUTTON_14
	1U << 30,		// BUTTON_15
	1U << 31,		// BUTTON_16

	0xFFFFFFFF,
};

static const eInputButtonType g_AxisUpTbl[] = {
	BUTTON_AXIS1_UP, BUTTON_AXIS2_UP, BUTTON_AXIS3_UP, BUTTON_AXIS4_UP,
};

static const eInputButtonType g_AxisDownTbl[] = {
	BUTTON_AXIS1_DOWN, BUTTON_AXIS2_DOWN, BUTTON_AXIS3_DOWN, BUTTON_AXIS4_DOWN,
};

static const eInputButtonType g_AxisLeftTbl[] = {
	BUTTON_AXIS1_LEFT, BUTTON_AXIS2_LEFT, BUTTON_AXIS3_LEFT, BUTTON_AXIS4_LEFT,
};

static const eInputButtonType g_AxisRightTbl[] = {
	BUTTON_AXIS1_RIGHT, BUTTON_AXIS2_RIGHT, BUTTON_AXIS3_RIGHT, BUTTON_AXIS4_RIGHT,
};


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CInputController::CInputController( Sint32 KeyRepeatStartTime, Sint32 KeyRepeatInterval, IKeyboard *pKeyboard, IJoystick *pJoystick )
	: m_KeyRepeatStartTime	( KeyRepeatStartTime )
	, m_KeyRepeatInterval	( KeyRepeatInterval )
	, m_KeyStateOld			( 0 )
	, m_KeyStateNew			( 0 )
	, m_KeyLock				( 0 )
{
	m_pKeyboard = pKeyboard;
	pKeyboard->AddRef();

	m_pJoystick = pJoystick;
	pJoystick->AddRef();

	MemoryClear( m_KeyState, sizeof(m_KeyState) );
	MemoryClear( m_KeyRepeatCounter, sizeof(m_KeyRepeatCounter) );
	MemoryClear( m_KeyMap, sizeof(m_KeyMap) );
	MemoryClear( m_KeyAlias, sizeof(m_KeyAlias) );
	MemoryClear( m_AxisType, sizeof(m_AxisType) );
	MemoryClear( m_AxisDir, sizeof(m_AxisDir) );
	MemoryClear( m_IsAxisEnable, sizeof(m_IsAxisEnable) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CInputController::~CInputController()
{
	// 所有オブジェクトの解体
	SAFE_RELEASE( m_pKeyboard );
	SAFE_RELEASE( m_pJoystick );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInputController::Refresh( void )
{
	//------------------------------------------------------------------
	// ワーク初期化
	//------------------------------------------------------------------
	m_KeyStateOld = m_KeyStateNew;
	m_KeyStateNew = 0x00000000;

	//------------------------------------------------------------------
	// とりあえずジョイスティックの状態を取得
	//------------------------------------------------------------------
	// ボタン
	for ( Sint32 i = (Sint32)BUTTON_01; i <= (Sint32)BUTTON_16; i++ )
	{
		if ( m_pJoystick->GetButton( m_KeyMap[i] ) )
		{
			m_KeyStateNew |= g_PadSortBitTbl[i];
		}
	}

	// 軸
	for ( Sint32 i = 0; i < AXIS_TYPE_MAX; i++ )
	{
		if ( m_IsAxisEnable[i][INPUT_AXIS_X] )
		{
			Sint32 Ax = m_pJoystick->GetAxis( m_AxisType[i][INPUT_AXIS_X], m_AxisDir[i][INPUT_AXIS_X] );
			if ( Ax < -AXIS_RANGE_MAX/4 )
			{
				m_KeyStateNew |= g_PadSortBitTbl[g_AxisLeftTbl[i]];
			}
			if ( Ax > +AXIS_RANGE_MAX/4 )
			{
				m_KeyStateNew |= g_PadSortBitTbl[g_AxisRightTbl[i]];
			}
		}

		if ( m_IsAxisEnable[i][INPUT_AXIS_Y] )
		{
			Sint32 Ay = m_pJoystick->GetAxis( m_AxisType[i][INPUT_AXIS_Y], m_AxisDir[i][INPUT_AXIS_Y] );
			if ( Ay < -AXIS_RANGE_MAX/4 )
			{
				m_KeyStateNew |= g_PadSortBitTbl[g_AxisUpTbl[i]];
			}
			if ( Ay > +AXIS_RANGE_MAX/4 )
			{
				m_KeyStateNew |= g_PadSortBitTbl[g_AxisDownTbl[i]];
			}
		}
	}

	//------------------------------------------------------------------
	// キーボードの状態を拾う
	//------------------------------------------------------------------
	for ( Sint32 i = 0; i < BUTTON_AXIS_MAX; i++ )
	{
		if ( m_KeyAlias[i] != 0 )
		{
			if ( m_pKeyboard->GetKeyData( m_KeyAlias[i] ) )
			{
				m_KeyStateNew |= g_PadSortBitTbl[i];
			}
		}
	}

	//------------------------------------------------------------------
	// 状態更新
	//------------------------------------------------------------------
	m_KeyState[BUTTON_STATE_PUSH] = ~m_KeyStateOld &  m_KeyStateNew;
	m_KeyState[BUTTON_STATE_PULL] =  m_KeyStateOld & ~m_KeyStateNew;
	m_KeyState[BUTTON_STATE_HOLD] =  m_KeyStateOld &  m_KeyStateNew;
	m_KeyState[BUTTON_STATE_FREE] = ~m_KeyStateOld & ~m_KeyStateNew;

	//------------------------------------------------------------------
	// キーリピート
	//------------------------------------------------------------------
	if ( m_KeyRepeatInterval > 0 )
	{
		for ( Sint32 i = BUTTON_AXIS1_UP; i <= BUTTON_AXIS4_RIGHT; i++ )
		{
			// 押してる？
			if ( GetState( BUTTON_STATE_HOLD, (eInputButtonType)i ) )
			{
				// 一定時間以上押しつづけてる時に一定間隔でON/OFFを繰り返す
				if ( ++m_KeyRepeatCounter[i] >= m_KeyRepeatStartTime )
				{
					Sint32 Count = m_KeyRepeatCounter[i] - m_KeyRepeatStartTime;
					if ( (Count % m_KeyRepeatInterval) == 0 )
					{
						m_KeyState[BUTTON_STATE_PUSH] |= g_PadSortBitTbl[i];
					}
				}
			}
			// 押してない
			else
			{
				// カウンタクリア
				m_KeyRepeatCounter[i] = 0;
			}
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInputController::SetAxisX( eInputAxisType Type, ePadAxisType AxisX, ePadAxisDirection AxisDirX )
{
	m_AxisType[Type][INPUT_AXIS_X]		= AxisX;
	m_AxisDir[Type][INPUT_AXIS_X]		= AxisDirX;
	m_IsAxisEnable[Type][INPUT_AXIS_X]	= true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInputController::SetAxisY( eInputAxisType Type, ePadAxisType AxisY, ePadAxisDirection AxisDirY )
{
	m_AxisType[Type][INPUT_AXIS_Y]		= AxisY;
	m_AxisDir[Type][INPUT_AXIS_Y]		= AxisDirY;
	m_IsAxisEnable[Type][INPUT_AXIS_Y]	= true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInputController::SetButton( eInputButtonType Type, ePadButtonType Button )
{
	m_KeyMap[Type] = Button;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInputController::SetAlias( eInputButtonType Type, eVirtualKeyCode Key )
{
	m_KeyAlias[Type] = Key;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInputController::IsPushAnyKey( void )
{
	if ( m_KeyState[BUTTON_STATE_PUSH] != 0x00000000 ) return true;
	if ( m_KeyState[BUTTON_STATE_HOLD] != 0x00000000 ) return true;

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInputController::ClearState( void )
{
	MemoryClear( m_KeyState, sizeof(m_KeyState) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInputController::GetState( eInputButtonState PadState, eInputButtonType Type )
{
	return ((m_KeyState[PadState] & g_PadSortBitTbl[Type]) != 0x00000000);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInputController::SetState( eInputButtonState PadState, eInputButtonType Type )
{
	m_KeyState[PadState] |= g_PadSortBitTbl[Type];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eInputButtonType CInputController::CursorRepeatUpDown( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max )
{
	if ( Max > 1 )
	{
		if ( GetState( BUTTON_STATE_PUSH, g_AxisUpTbl[AxisNo] ) )
		{
			Cursor = (Cursor + Max - 1) % Max;

			return g_AxisUpTbl[AxisNo];
		}
		ef ( GetState( BUTTON_STATE_PUSH, g_AxisDownTbl[AxisNo] ) )
		{
			Cursor = (Cursor + Max + 1) % Max;

			return g_AxisDownTbl[AxisNo];
		}
	}

	return BUTTON_DISABLE;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eInputButtonType CInputController::CursorRepeatLeftRight( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max )
{
	if ( Max > 1 )
	{
		if ( GetState( BUTTON_STATE_PUSH, g_AxisLeftTbl[AxisNo] ) )
		{
			Cursor = (Cursor + Max - 1) % Max;

			return g_AxisLeftTbl[AxisNo];
		}
		ef ( GetState( BUTTON_STATE_PUSH, g_AxisRightTbl[AxisNo] ) )
		{
			Cursor = (Cursor + Max + 1) % Max;

			return g_AxisRightTbl[AxisNo];
		}
	}

	return BUTTON_DISABLE;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eInputButtonType CInputController::CursorClampUpDown( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max )
{
	if ( Max > 1 )
	{
		if ( GetState( BUTTON_STATE_PUSH, g_AxisUpTbl[AxisNo] ) )
		{
			if ( Cursor > 0 )
			{
				Cursor--;
				return g_AxisUpTbl[AxisNo];
			}
		}
		ef ( GetState( BUTTON_STATE_PUSH, g_AxisDownTbl[AxisNo] ) )
		{
			if ( Cursor < Max - 1 )
			{
				Cursor++;
				return g_AxisDownTbl[AxisNo];
			}
		}
	}

	return BUTTON_DISABLE;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eInputButtonType CInputController::CursorClampLeftRight( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max )
{
	if ( Max > 1 )
	{
		if ( GetState( BUTTON_STATE_PUSH, g_AxisLeftTbl[AxisNo] ) )
		{
			if ( Cursor > 0 )
			{
				Cursor--;
				return g_AxisLeftTbl[AxisNo];
			}
		}
		ef ( GetState( BUTTON_STATE_PUSH, g_AxisRightTbl[AxisNo] ) )
		{
			if ( Cursor < Max - 1 )
			{
				Cursor++;
				return g_AxisRightTbl[AxisNo];
			}
		}
	}

	return BUTTON_DISABLE;
}

