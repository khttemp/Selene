#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Object/CBaseObject.h"
#include "Interface/Peripheral/IKeyboard.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Peripheral
{
	#define KEYBOARD_DATA_MAX		(256)
	#define KEYBOARD_BUFFER_MAX		(32)

	struct SKeyBoardData
	{
		char Key[KEYBOARD_DATA_MAX];
	};

	class CKeyboard : public CBaseObject, public IKeyboard
	{
	protected:
		IDirectInputDevice8		*m_pDevice;
		DIDEVICEOBJECTDATA		m_KeyBuffer[KEYBOARD_BUFFER_MAX];
		SKeyBoardData			m_KeyboardData;
		Uint32					m_KeyBufferCount;
		Uint32					m_KeyBufferMax;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CKeyboard( IDirectInputDevice8 *pDevice );
		virtual ~CKeyboard();

		virtual void Initialize( void );
		virtual void Refresh( void );

		virtual void ClearKeyBuffer( void );
		virtual eVirtualKeyCode GetKeyBuffer( void );
		virtual Bool GetKeyData( eVirtualKeyCode Key );
	};
}
}
