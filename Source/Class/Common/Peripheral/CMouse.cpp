

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Peripheral/CMouse.h"
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
CMouse::CMouse( HWND hWnd )
	: m_hWindow				( hWnd )
	, m_PosX				( 0 )
	, m_PosY				( 0 )
	, m_PosW				( 0 )
	, m_PosWOld				( 0 )
	, m_MoveX				( 0 )
	, m_MoveY				( 0 )
	, m_MoveW				( 0 )
	, m_StateL				( MOUSE_FREE )
	, m_StateR				( MOUSE_FREE )
	, m_StateW				( MOUSE_FREE )
	, m_ClickL				( false )
	, m_ClickR				( false )
	, m_ClickW				( false )
	, m_DoubleClickL		( false )
	, m_DoubleClickR		( false )
	, m_DoubleClickW		( false )
	, m_DoubleClickLNew		( false )
	, m_DoubleClickRNew		( false )
	, m_DoubleClickWNew		( false )
{
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMouse::~CMouse()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMouse::Refresh( void )
{
	Bool BtnL = (::GetKeyState( VK_LBUTTON ) >> 7) & 0x01;
	Bool BtnR = (::GetKeyState( VK_RBUTTON ) >> 7) & 0x01;
	Bool BtnW = (::GetKeyState( VK_MBUTTON ) >> 7) & 0x01;

	//------------------------------------------------------------
	// 左クリック処理
	//------------------------------------------------------------
	if ( BtnL )
	{
		if ( m_ClickL )
		{
			m_StateL = MOUSE_HOLD;
		}
		else
		{
			m_StateL = MOUSE_PUSH;
		}
	}
	else
	{
		if ( m_ClickL )
		{
			m_StateL = MOUSE_PULL;
		}
		else
		{
			m_StateL = MOUSE_FREE;
		}
	}

	//------------------------------------------------------------
	// 右クリック処理
	//------------------------------------------------------------
	if ( BtnR )
	{
		if ( m_ClickR )
		{
			m_StateR = MOUSE_HOLD;
		}
		else
		{
			m_StateR = MOUSE_PUSH;
		}
	}
	else
	{
		if ( m_ClickR )
		{
			m_StateR = MOUSE_PULL;
		}
		else
		{
			m_StateR = MOUSE_FREE;
		}
	}

	//------------------------------------------------------------
	// ホイールクリック処理
	//------------------------------------------------------------
	if ( BtnW )
	{
		if ( m_ClickW )
		{
			m_StateW = MOUSE_HOLD;
		}
		else
		{
			m_StateW = MOUSE_PUSH;
		}
	}
	else
	{
		if ( m_ClickW )
		{
			m_StateW = MOUSE_PULL;
		}
		else
		{
			m_StateW = MOUSE_FREE;
		}
	}

	//------------------------------------------------------------
	// 状態保存
	//------------------------------------------------------------
	m_ClickL = BtnL;
	m_ClickR = BtnR;
	m_ClickW = BtnW;

	//------------------------------------------------------------
	// スクリーン上の位置
	//------------------------------------------------------------
	POINT Cursor;
	::GetCursorPos( &Cursor );
	::ScreenToClient( m_hWindow, &Cursor );
	m_MoveX = Cursor.x - m_PosX;
	m_MoveY = Cursor.y - m_PosY;
	m_PosX = Cursor.x;
	m_PosY = Cursor.y;

	//------------------------------------------------------------
	// ホイール移動量
	//------------------------------------------------------------
	m_MoveW = m_PosW - m_PosWOld;
	m_PosWOld = m_PosW;

	//------------------------------------------------------------
	// ダブルクリック
	//------------------------------------------------------------
	m_DoubleClickL = m_DoubleClickLNew;
	m_DoubleClickR = m_DoubleClickRNew;
	m_DoubleClickW = m_DoubleClickWNew;
	m_DoubleClickLNew = false;
	m_DoubleClickRNew = false;
	m_DoubleClickWNew = false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMouse::SetMouseWheel( Sint16 w )
{
	m_PosW += w;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMouse::SetDoubleClickL( void )
{
	m_DoubleClickLNew = true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMouse::SetDoubleClickR( void )
{
	m_DoubleClickRNew = true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMouse::SetDoubleClickM( void )
{
	m_DoubleClickWNew = true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMouse::SetPosition( Math::Point2DI &Pos )
{
	POINT Pt = { Pos.x, Pos.y };
	::ClientToScreen( m_hWindow, &Pt );
	::SetCursorPos( Pt.x, Pt.y );
}
