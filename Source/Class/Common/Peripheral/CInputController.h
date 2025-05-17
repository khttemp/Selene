#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CBaseObject.h"
#include "Interface/Peripheral/IKeyboard.h"
#include "Interface/Peripheral/IInputController.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Peripheral
{
	enum eInputAxis
	{
		INPUT_AXIS_X,
		INPUT_AXIS_Y,
		INPUT_AXIS_MAX,
	};

	class CInputController : public CBaseObject, public IInputController
	{
	private:
		IKeyboard			*m_pKeyboard;
		IJoystick			*m_pJoystick;

		Sint32				m_KeyRepeatStartTime;
		Sint32				m_KeyRepeatInterval;

		Sint32				m_KeyStateOld;
		Sint32				m_KeyStateNew;
		Sint32				m_KeyLock;
		Sint32				m_KeyState[BUTTON_STATE_MAX];
		Sint32				m_KeyRepeatCounter[BUTTON_AXIS_MAX];
		ePadButtonType		m_KeyMap[BUTTON_AXIS_MAX];
		eVirtualKeyCode		m_KeyAlias[BUTTON_AXIS_MAX];
		ePadAxisType		m_AxisType[AXIS_TYPE_MAX][INPUT_AXIS_MAX];
		ePadAxisDirection	m_AxisDir[AXIS_TYPE_MAX][INPUT_AXIS_MAX];
		Bool				m_IsAxisEnable[AXIS_TYPE_MAX][INPUT_AXIS_MAX];

	public:
		CInputController( Sint32 KeyRepeatStartTime, Sint32 KeyRepeatInterval, IKeyboard *pKeyboard, IJoystick *pJoystick );
		virtual ~CInputController();

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual void Refresh( void );
		virtual void SetAxisX( eInputAxisType Type, ePadAxisType AxisX, ePadAxisDirection AxisDirX );
		virtual void SetAxisY( eInputAxisType Type, ePadAxisType AxisY, ePadAxisDirection AxisDirY );
		virtual void SetButton( eInputButtonType Type, ePadButtonType Button );
		virtual void SetAlias( eInputButtonType Type, eVirtualKeyCode Key );

		virtual Bool IsPushAnyKey( void );
		virtual void ClearState( void );
		virtual Bool GetState( eInputButtonState PadState, eInputButtonType Type );
		virtual void SetState( eInputButtonState PadState, eInputButtonType Type );

		virtual eInputButtonType CursorRepeatUpDown( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max );
		virtual eInputButtonType CursorRepeatLeftRight( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max );
		virtual eInputButtonType CursorClampUpDown( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max );
		virtual eInputButtonType CursorClampLeftRight( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max );
	};
}
}
