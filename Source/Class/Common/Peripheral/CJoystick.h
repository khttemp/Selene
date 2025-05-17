#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Object/CBaseObject.h"
#include "Interface/Peripheral/IJoystick.h"
#include "Math/Math.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Peripheral
{
	const Sint32 PAD_AXISDATA_MAX	= 8;

	struct SJoystickData
	{
		Uint8 Button[PAD_BUTTON_MAX];
		Sint32 Axis[PAD_AXISDATA_MAX][PAD_AXIS_DIRECTION_MAX];
		Sint32 Slider[PAD_SLIDER_MAX];
		Sint32 Pov;
	};

	class CJoystick : public CBaseObject, public IJoystick
	{
	private:
		static BOOL CALLBACK EnumAxisCallback( const DIDEVICEOBJECTINSTANCE *pdidoi, void *pContext );

	protected:
		IDirectInputDevice8		*m_pDevice;
		Bool					m_IsForceFeedback;
		Bool					m_IsPolling;
		Float					m_AxisRange[PAD_AXISDATA_MAX][PAD_AXIS_DIRECTION_MAX];
		Float					m_AxisCenter[PAD_AXISDATA_MAX][PAD_AXIS_DIRECTION_MAX];
		Float					m_fSliderRange[PAD_SLIDER_MAX];
		Float					m_fSliderCenter[PAD_SLIDER_MAX];

		Bool					m_Button[PAD_BUTTON_MAX];
		Sint32					m_Axis[PAD_AXIS_MAX][PAD_AXIS_DIRECTION_MAX];
		Sint32					m_Slider[PAD_SLIDER_MAX];

	protected:
		virtual Sint32 AdjustAxis( Sint32 AxisSource, Float fAxisCenter, Float fAxisMax, Float fAxisRange );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CJoystick( IDirectInputDevice8 *pDevice );
		virtual ~CJoystick();

		virtual void Initialize( void );
		virtual void Refresh( void );

		virtual Sint32 GetAxis( ePadAxisType Type, ePadAxisDirection Dir );
		virtual Sint32 GetSlider( ePadSliderType Type );
		virtual Bool GetButton( ePadButtonType Type );
	};
}
}
