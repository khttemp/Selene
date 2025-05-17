#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CBaseObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Peripheral
{
	const Sint32 JOYSTICK_MAX = 16;

	class CInput : public CBaseObject
	{
	private:
		static BOOL CALLBACK EnumJoysticksCallback( const DIDEVICEINSTANCE *pdidInstance, void *pContext );

	protected:
		IDirectInput8 *m_pDirectInput;
		IDirectInputDevice8 *m_pDevKeyboard;
		IDirectInputDevice8 *m_pDevJoystick[JOYSTICK_MAX];
		Sint32 m_JoystickCount;
		CJoystick *m_pJoystick[JOYSTICK_MAX];
		CKeyboard *m_pKeyboard;
		CMouse *m_pMouse;
		CCore *m_pCore;

	protected:
		virtual IDirectInput8 *GetDirectInputPointer( void ) const;

	public:
		CInput( CCore *pCore );
		virtual ~CInput();

	public:
		virtual void Refresh( void );
		virtual Bool GetJoystick( CJoystick *&pJoystick, Sint32 No );
		virtual Bool GetKeyboard( CKeyboard *&pKeyboard );
		virtual Bool GetMouse( CMouse *&pMouse );
		virtual Sint32 GetJoystickCount( void );
	};
}
}
