#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Object/CBaseObject.h"
#include "Interface/Peripheral/IMouse.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Peripheral
{
	class CMouse : public CBaseObject, public IMouse
	{
	protected:
		HWND			m_hWindow;

		Sint32			m_PosX;
		Sint32			m_PosY;
		Sint32			m_PosW;
		Sint32			m_PosWOld;

		Sint32			m_MoveX;
		Sint32			m_MoveY;
		Sint32			m_MoveW;

		eMouseState		m_StateL;
		eMouseState		m_StateR;
		eMouseState		m_StateW;

		Bool			m_ClickL;
		Bool			m_ClickR;
		Bool			m_ClickW;

		Bool			m_DoubleClickL;
		Bool			m_DoubleClickR;
		Bool			m_DoubleClickW;

		Bool			m_DoubleClickLNew;
		Bool			m_DoubleClickRNew;
		Bool			m_DoubleClickWNew;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CMouse( HWND hWnd );
		virtual ~CMouse();

		virtual void Refresh( void );

		virtual void SetMouseWheel( Sint16 w );
		virtual void SetDoubleClickL( void );
		virtual void SetDoubleClickR( void );
		virtual void SetDoubleClickM( void );

		virtual Sint32 GetPosX( void ) { return m_PosX; }
		virtual Sint32 GetPosY( void ) { return m_PosY; }
		virtual Sint32 GetPosW( void ) { return m_PosW; }

		virtual Sint32 GetMoveX( void ) { return m_MoveX; }
		virtual Sint32 GetMoveY( void ) { return m_MoveY; }
		virtual Sint32 GetMoveW( void ) { return m_MoveW; }

		virtual Bool GetClickL( void ) { return m_ClickL; }
		virtual Bool GetClickR( void ) { return m_ClickR; }
		virtual Bool GetClickW( void ) { return m_ClickW; }

		virtual Bool GetDoubleClickL( void ) { return m_DoubleClickL; }
		virtual Bool GetDoubleClickR( void ) { return m_DoubleClickR; }
		virtual Bool GetDoubleClickW( void ) { return m_DoubleClickW; }

		virtual eMouseState GetStateL( void ) { return m_StateL; }
		virtual eMouseState	GetStateR( void ) { return m_StateR; }
		virtual eMouseState	GetStateW( void ) { return m_StateW; }

		virtual void SetPosition( Math::Point2DI &Pos );
	};
}
}
