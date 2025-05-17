

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Peripheral/CInput.h"
#include "Class/Common/Peripheral/CMouse.h"
#include "Class/Common/Peripheral/CKeyboard.h"
#include "Class/Common/Peripheral/CJoystick.h"
#include "Class/Common/Core/CCore.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Peripheral;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
BOOL CALLBACK CInput::EnumJoysticksCallback( const DIDEVICEINSTANCE *pdidInstance, void *pContext )
{
	CInput *pInput = (CInput*)pContext;

	// �񋓂��ꂽ�W���C�X�e�B�b�N�ւ̃C���^�[�t�F�C�X���擾����
	HRESULT hr = pInput->m_pDirectInput->CreateDevice(
								pdidInstance->guidInstance,
								&pInput->m_pDevJoystick[pInput->m_JoystickCount],
								NULL );
	if SUCCEEDED( hr )
	{
		pInput->m_JoystickCount++;
		if ( pInput->m_JoystickCount < JOYSTICK_MAX )
		{
			return DIENUM_CONTINUE;
		}
	}

	return DIENUM_STOP;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CInput::CInput( CCore *pCore )
	: m_pCore			( pCore )
	, m_pDirectInput	( NULL )
	, m_pDevKeyboard	( NULL )
	, m_pKeyboard		( NULL )
	, m_pMouse			( NULL )
{
	HRESULT hr;

	MemoryClear( m_pDevJoystick, sizeof(m_pDevJoystick) );
	MemoryClear( m_pJoystick, sizeof(m_pJoystick) );

	//----------------------------------------------------------
	// DirectInput�I�u�W�F�N�g�擾
	//----------------------------------------------------------
	hr = CoCreateInstance(
				CLSID_DirectInput8,
				NULL, 
				CLSCTX_ALL,
				IID_IDirectInput8,
				(void**)&m_pDirectInput );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF0000, "DirectInput�I�u�W�F�N�g�̐����Ɏ��s" );
		Log_TableLine( 1 );
		return;
	}

	//----------------------------------------------------------
	// DirectInput�I�u�W�F�N�g������
	//----------------------------------------------------------
	hr = m_pDirectInput->Initialize( pCore->GetInstanceHandle(), DIRECTINPUT_VERSION );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF0000, "DirectInput�I�u�W�F�N�g�̏������Ɏ��s" );
		Log_TableLine( 1 );
		return;
	}

	//----------------------------------------------------------
	// �f�o�C�X������
	//----------------------------------------------------------
	hr = m_pDirectInput->CreateDevice( GUID_SysKeyboard, &m_pDevKeyboard, NULL );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF0000, "�L�[�{�[�h�f�o�C�X�̐����Ɏ��s" );
		Log_TableLine( 1 );
		return;
	}

	//----------------------------------------------------------
	// �������x���̐ݒ�
	//----------------------------------------------------------
	hr = m_pDevKeyboard->SetCooperativeLevel( pCore->GetWindowHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF0000, "�L�[�{�[�h�̋������x���̐ݒ�Ɏ��s" );
		Log_TableLine( 1 );
		return;
	}

	//----------------------------------------------------------
	// �W���C�X�e�B�b�N�̗�
	//----------------------------------------------------------
	m_JoystickCount = 0;
	hr = m_pDirectInput->EnumDevices( DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, this, DIEDFL_ATTACHEDONLY );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF0000, "�W���C�X�e�B�b�N�f�o�C�X�̗񋓂Ɏ��s" );
		Log_TableLine( 1 );
	}

	//----------------------------------------------------------
	// �������x���̐ݒ�
	//----------------------------------------------------------
	for ( Sint32 i = 0; i < m_JoystickCount; i++ )
	{
		hr = m_pDevJoystick[i]->SetCooperativeLevel( pCore->GetWindowHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
		if FAILED( hr )
		{
			Log_PrintLine( 0xFF0000, "�W���C�X�e�B�b�N�̋������x���̐ݒ�Ɏ��s" );
			Log_TableLine( 1 );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CInput::~CInput()
{
	// ���L�I�u�W�F�N�g�̉��
	SAFE_RELEASE( m_pKeyboard );
	SAFE_RELEASE( m_pMouse );

	// DirectInput�f�o�C�X���
	if ( m_pDevKeyboard != NULL )
	{
		m_pDevKeyboard->Unacquire();
		SAFE_RELEASE( m_pDevKeyboard );
	}

	for ( Sint32 i = 0; i < JOYSTICK_MAX; i++ )
	{
		if ( m_pDevJoystick[i] != NULL )
		{
			m_pDevJoystick[i]->Unacquire();
			SAFE_RELEASE( m_pDevJoystick[i] );
		}
	}

	// DirectInput�I�u�W�F�N�g���
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "���" );

	if ( m_pDirectInput != NULL )
	{
		Sint32 Num = m_pDirectInput->Release();
		m_pDirectInput = NULL;

		Log_PrintCellKind( "IDirectInput" );
		Log_CellBegin( 0 );
		Log_Print( 0x000000, "�Q�Ɛ� %d", Num );
		Log_CellEnd();
	}

	Log_TableEnd();
	Log_TableLine( 2 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInput::Refresh( void )
{
	// �}�E�X
	if ( m_pMouse != NULL )
	{
		m_pMouse->Refresh();
	}

	// �L�[�{�[�h
	if ( m_pKeyboard != NULL )
	{
		m_pKeyboard->Refresh();
	}

	// �W���C�X�e�B�b�N
	for ( Sint32 i = 0; i < JOYSTICK_MAX; i++ )
	{
		if ( m_pJoystick[i] != NULL )
		{
			m_pJoystick[i]->Refresh();
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInput::GetJoystick( CJoystick *&pJoystick, Sint32 No )
{
	if ( m_pJoystick[No] == NULL )
	{
		if ( m_pDevJoystick[No] != NULL )
		{
			m_pJoystick[No] = new CJoystick( m_pDevJoystick[No] );
			m_pJoystick[No]->Initialize();
		}
		else
		{
			m_pJoystick[No] = NULL;
			return false;
		}
	}

	pJoystick = m_pJoystick[No];
	pJoystick->AddRef();

	return pJoystick != NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInput::GetKeyboard( CKeyboard *&pKeyboard )
{
	if ( m_pKeyboard == NULL )
	{
		if ( m_pDevKeyboard != NULL )
		{
			m_pKeyboard = new CKeyboard( m_pDevKeyboard );
			m_pKeyboard->Initialize();
		}
		else
		{
			pKeyboard = NULL;
			return false;
		}
	}

	pKeyboard = m_pKeyboard;
	pKeyboard->AddRef();

	return pKeyboard != NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInput::GetMouse( CMouse *&pMouse )
{
	if ( m_pMouse == NULL )
	{
		m_pMouse = new CMouse( m_pCore->GetWindowHandle() );
	}

	pMouse = m_pMouse;
	if ( pMouse != NULL )
	{
		pMouse->AddRef();
	}

	return pMouse != NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IDirectInput8 *CInput::GetDirectInputPointer( void ) const
{
	return m_pDirectInput;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CInput::GetJoystickCount( void )
{
	return m_JoystickCount;
}
