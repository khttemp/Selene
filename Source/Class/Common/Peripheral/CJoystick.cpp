

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Peripheral/CJoystick.h"
#include "Class/Common/Peripheral/CInput.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Peripheral;


//-----------------------------------------------------------------------------------
// SJoystickData
//-----------------------------------------------------------------------------------
static DIOBJECTDATAFORMAT g_JoystickDataFormat[] =
{
	// ボタン
	{ &GUID_Button,	FIELD_OFFSET(SJoystickData,  Button[ 0]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
	{ &GUID_Button,	FIELD_OFFSET(SJoystickData,  Button[ 1]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
	{ &GUID_Button,	FIELD_OFFSET(SJoystickData,  Button[ 2]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
	{ &GUID_Button,	FIELD_OFFSET(SJoystickData,  Button[ 3]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
	{ &GUID_Button,	FIELD_OFFSET(SJoystickData,  Button[ 4]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
	{ &GUID_Button,	FIELD_OFFSET(SJoystickData,  Button[ 5]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
	{ &GUID_Button,	FIELD_OFFSET(SJoystickData,  Button[ 6]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
	{ &GUID_Button,	FIELD_OFFSET(SJoystickData,  Button[ 7]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
	{ &GUID_Button,	FIELD_OFFSET(SJoystickData,  Button[ 8]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
	{ &GUID_Button,	FIELD_OFFSET(SJoystickData,  Button[ 9]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
	{ &GUID_Button,	FIELD_OFFSET(SJoystickData,  Button[10]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
	{ &GUID_Button,	FIELD_OFFSET(SJoystickData,  Button[11]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
	{ &GUID_Button,	FIELD_OFFSET(SJoystickData,  Button[12]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
	{ &GUID_Button,	FIELD_OFFSET(SJoystickData,  Button[13]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
	{ &GUID_Button,	FIELD_OFFSET(SJoystickData,  Button[14]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
	{ &GUID_Button,	FIELD_OFFSET(SJoystickData,  Button[15]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
	// 軸
	{ &GUID_XAxis,	FIELD_OFFSET(SJoystickData,  Axis[0][0]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTPOSITION },
	{ &GUID_YAxis,	FIELD_OFFSET(SJoystickData,  Axis[0][1]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTPOSITION },
	{ &GUID_ZAxis,	FIELD_OFFSET(SJoystickData,  Axis[0][2]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTPOSITION },
	// 回転軸
	{ &GUID_RxAxis,	FIELD_OFFSET(SJoystickData,  Axis[4][0]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTPOSITION },
	{ &GUID_RyAxis,	FIELD_OFFSET(SJoystickData,  Axis[4][1]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTPOSITION },
	{ &GUID_RzAxis,	FIELD_OFFSET(SJoystickData,  Axis[4][2]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTPOSITION },
	// 軸の速度
	{ &GUID_XAxis,	FIELD_OFFSET(SJoystickData,  Axis[1][0]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTVELOCITY },
	{ &GUID_YAxis,	FIELD_OFFSET(SJoystickData,  Axis[1][1]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTVELOCITY },
	{ &GUID_ZAxis,	FIELD_OFFSET(SJoystickData,  Axis[1][2]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTVELOCITY },
	// 軸の角速度
	{ &GUID_RxAxis,	FIELD_OFFSET(SJoystickData,  Axis[5][0]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTVELOCITY },
	{ &GUID_RyAxis,	FIELD_OFFSET(SJoystickData,  Axis[5][1]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTVELOCITY },
	{ &GUID_RzAxis,	FIELD_OFFSET(SJoystickData,  Axis[5][2]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTVELOCITY },
	// 軸の加速度
	{ &GUID_XAxis,	FIELD_OFFSET(SJoystickData,  Axis[2][0]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTACCEL },
	{ &GUID_YAxis,	FIELD_OFFSET(SJoystickData,  Axis[2][1]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTACCEL },
	{ &GUID_ZAxis,	FIELD_OFFSET(SJoystickData,  Axis[2][2]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTACCEL },
	// 軸の角加速度
	{ &GUID_RxAxis,	FIELD_OFFSET(SJoystickData,  Axis[6][0]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTACCEL },
	{ &GUID_RyAxis,	FIELD_OFFSET(SJoystickData,  Axis[6][1]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTACCEL },
	{ &GUID_RzAxis,	FIELD_OFFSET(SJoystickData,  Axis[6][2]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTACCEL },
	// 軸のフォース
	{ &GUID_XAxis,	FIELD_OFFSET(SJoystickData,  Axis[3][0]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTFORCE },
	{ &GUID_YAxis,	FIELD_OFFSET(SJoystickData,  Axis[3][1]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTFORCE },
	{ &GUID_ZAxis,	FIELD_OFFSET(SJoystickData,  Axis[3][2]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTFORCE },
	// 軸のトルク
	{ &GUID_RxAxis,	FIELD_OFFSET(SJoystickData,  Axis[7][0]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTFORCE },
	{ &GUID_RyAxis,	FIELD_OFFSET(SJoystickData,  Axis[7][1]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTFORCE },
	{ &GUID_RzAxis,	FIELD_OFFSET(SJoystickData,  Axis[7][2]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTFORCE },	
	// スライダー
	{ &GUID_Slider,	FIELD_OFFSET(SJoystickData,   Slider[0]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTPOSITION },
	{ &GUID_Slider,	FIELD_OFFSET(SJoystickData,   Slider[1]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTVELOCITY },
	{ &GUID_Slider,	FIELD_OFFSET(SJoystickData,   Slider[2]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTACCEL },
	{ &GUID_Slider,	FIELD_OFFSET(SJoystickData,   Slider[3]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTFORCE },
	// POV
	{ &GUID_POV,	FIELD_OFFSET(SJoystickData,         Pov), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_POV, 0 },
};

static const Sint32 g_JoyDataNum = sizeof(g_JoystickDataFormat) / sizeof(DIOBJECTDATAFORMAT);

static DIDATAFORMAT g_DIJoystickDataFormat = { 
	sizeof(DIDATAFORMAT),			// この構造体のサイズ
	sizeof(DIOBJECTDATAFORMAT),		// オブジェクト データ形式のサイズ
	DIDF_ABSAXIS,					// 絶対軸の座標
	sizeof(SJoystickData),			// デバイス データのサイズ
	g_JoyDataNum,					// オブジェクト数
	g_JoystickDataFormat,			// データ位置
};


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
BOOL CALLBACK CJoystick::EnumAxisCallback( const DIDEVICEOBJECTINSTANCE *pdidoi, void *pContext )
{
	CJoystick *pJoy = (CJoystick*)pContext;

	Float *pRange = NULL;
	Float *pCenter = NULL;
	char Title[64] = "";

	//-----------------------------------------------------------
	// 軸の範囲取得
	//-----------------------------------------------------------
	DIPROPRANGE diprg = { sizeof(DIPROPRANGE), sizeof(DIPROPHEADER) };
    diprg.diph.dwHow = DIPH_BYID; 
    diprg.diph.dwObj = pdidoi->dwType;

	if FAILED( pJoy->m_pDevice->GetProperty( DIPROP_RANGE, &diprg.diph ) )
	{
		Log_PrintLine( 0xFF0000, "軸データ取得に失敗" );
		return DIENUM_CONTINUE;
	}

	//-----------------------------------------------------------
	// 軸ごとの設定
	//-----------------------------------------------------------
	if ( pdidoi->guidType == GUID_XAxis )
	{
		StringCbPrintf( Title, sizeof(Title), "Ｘ軸" );
		switch ( pdidoi->dwFlags & DIDOI_ASPECTMASK )
		{
		case DIDOI_ASPECTPOSITION:	pRange = &pJoy->m_AxisRange[PAD_AXIS_POSITION][PAD_AXIS_X]; pCenter = &pJoy->m_AxisCenter[0][PAD_AXIS_X];	break;
		case DIDOI_ASPECTVELOCITY:	pRange = &pJoy->m_AxisRange[PAD_AXIS_VELOCITY][PAD_AXIS_X]; pCenter = &pJoy->m_AxisCenter[1][PAD_AXIS_X];	break;
		case DIDOI_ASPECTACCEL:		pRange = &pJoy->m_AxisRange[PAD_AXIS_ACCEL][PAD_AXIS_X]; pCenter = &pJoy->m_AxisCenter[2][PAD_AXIS_X];	break;
		case DIDOI_ASPECTFORCE:		pRange = &pJoy->m_AxisRange[PAD_AXIS_FORCE][PAD_AXIS_X]; pCenter = &pJoy->m_AxisCenter[3][PAD_AXIS_X];	break;
		}
	}
	ef ( pdidoi->guidType == GUID_YAxis )
	{
		StringCbPrintf( Title, sizeof(Title), "Ｙ軸" );
		switch ( pdidoi->dwFlags & DIDOI_ASPECTMASK )
		{
		case DIDOI_ASPECTPOSITION:	pRange = &pJoy->m_AxisRange[PAD_AXIS_POSITION][PAD_AXIS_Y]; pCenter = &pJoy->m_AxisCenter[0][PAD_AXIS_Y];	break;
		case DIDOI_ASPECTVELOCITY:	pRange = &pJoy->m_AxisRange[PAD_AXIS_VELOCITY][PAD_AXIS_Y]; pCenter = &pJoy->m_AxisCenter[1][PAD_AXIS_Y];	break;
		case DIDOI_ASPECTACCEL:		pRange = &pJoy->m_AxisRange[PAD_AXIS_ACCEL][PAD_AXIS_Y]; pCenter = &pJoy->m_AxisCenter[2][PAD_AXIS_Y];	break;
		case DIDOI_ASPECTFORCE:		pRange = &pJoy->m_AxisRange[PAD_AXIS_FORCE][PAD_AXIS_Y]; pCenter = &pJoy->m_AxisCenter[3][PAD_AXIS_Y];	break;
		}
	}
	ef ( pdidoi->guidType == GUID_ZAxis )
	{
		StringCbPrintf( Title, sizeof(Title), "Ｚ軸" );
		switch ( pdidoi->dwFlags & DIDOI_ASPECTMASK )
		{
		case DIDOI_ASPECTPOSITION:	pRange = &pJoy->m_AxisRange[PAD_AXIS_POSITION][PAD_AXIS_Z]; pCenter = &pJoy->m_AxisCenter[0][PAD_AXIS_Z];	break;
		case DIDOI_ASPECTVELOCITY:	pRange = &pJoy->m_AxisRange[PAD_AXIS_VELOCITY][PAD_AXIS_Z]; pCenter = &pJoy->m_AxisCenter[1][PAD_AXIS_Z];	break;
		case DIDOI_ASPECTACCEL:		pRange = &pJoy->m_AxisRange[PAD_AXIS_ACCEL][PAD_AXIS_Z]; pCenter = &pJoy->m_AxisCenter[2][PAD_AXIS_Z];	break;
		case DIDOI_ASPECTFORCE:		pRange = &pJoy->m_AxisRange[PAD_AXIS_FORCE][PAD_AXIS_Z]; pCenter = &pJoy->m_AxisCenter[3][PAD_AXIS_Z];	break;
		}
	}
	ef ( pdidoi->guidType == GUID_RxAxis )
	{
		StringCbPrintf( Title, sizeof(Title), "Ｘ軸回転" );
		switch ( pdidoi->dwFlags & DIDOI_ASPECTMASK )
		{
		case DIDOI_ASPECTPOSITION:	pRange = &pJoy->m_AxisRange[PAD_AXIS_POSITION_ROTATE][PAD_AXIS_X]; pCenter = &pJoy->m_AxisCenter[4][PAD_AXIS_X];	break;
		case DIDOI_ASPECTVELOCITY:	pRange = &pJoy->m_AxisRange[PAD_AXIS_VELOCITY_ROTATE][PAD_AXIS_X]; pCenter = &pJoy->m_AxisCenter[5][PAD_AXIS_X];	break;
		case DIDOI_ASPECTACCEL:		pRange = &pJoy->m_AxisRange[PAD_AXIS_ACCEL_ROTATE][PAD_AXIS_X]; pCenter = &pJoy->m_AxisCenter[6][PAD_AXIS_X];	break;
		case DIDOI_ASPECTFORCE:		pRange = &pJoy->m_AxisRange[PAD_AXIS_FORCE_ROTATE][PAD_AXIS_X]; pCenter = &pJoy->m_AxisCenter[7][PAD_AXIS_X];	break;
		}
	}
	ef ( pdidoi->guidType == GUID_RyAxis )
	{
		StringCbPrintf( Title, sizeof(Title), "Ｙ軸回転" );
		switch ( pdidoi->dwFlags & DIDOI_ASPECTMASK )
		{
		case DIDOI_ASPECTPOSITION:	pRange = &pJoy->m_AxisRange[PAD_AXIS_POSITION_ROTATE][PAD_AXIS_Y]; pCenter = &pJoy->m_AxisCenter[4][PAD_AXIS_Y];	break;
		case DIDOI_ASPECTVELOCITY:	pRange = &pJoy->m_AxisRange[PAD_AXIS_VELOCITY_ROTATE][PAD_AXIS_Y]; pCenter = &pJoy->m_AxisCenter[5][PAD_AXIS_Y];	break;
		case DIDOI_ASPECTACCEL:		pRange = &pJoy->m_AxisRange[PAD_AXIS_ACCEL_ROTATE][PAD_AXIS_Y]; pCenter = &pJoy->m_AxisCenter[6][PAD_AXIS_Y];	break;
		case DIDOI_ASPECTFORCE:		pRange = &pJoy->m_AxisRange[PAD_AXIS_FORCE_ROTATE][PAD_AXIS_Y]; pCenter = &pJoy->m_AxisCenter[7][PAD_AXIS_Y];	break;
		}
	}
	ef ( pdidoi->guidType == GUID_RzAxis )
	{
		StringCbPrintf( Title, sizeof(Title), "Ｚ軸回転" );
		switch ( pdidoi->dwFlags & DIDOI_ASPECTMASK )
		{
		case DIDOI_ASPECTPOSITION:	pRange = &pJoy->m_AxisRange[PAD_AXIS_POSITION_ROTATE][PAD_AXIS_Z]; pCenter = &pJoy->m_AxisCenter[4][PAD_AXIS_Z];	break;
		case DIDOI_ASPECTVELOCITY:	pRange = &pJoy->m_AxisRange[PAD_AXIS_VELOCITY_ROTATE][PAD_AXIS_Z]; pCenter = &pJoy->m_AxisCenter[5][PAD_AXIS_Z];	break;
		case DIDOI_ASPECTACCEL:		pRange = &pJoy->m_AxisRange[PAD_AXIS_ACCEL_ROTATE][PAD_AXIS_Z]; pCenter = &pJoy->m_AxisCenter[6][PAD_AXIS_Z];	break;
		case DIDOI_ASPECTFORCE:		pRange = &pJoy->m_AxisRange[PAD_AXIS_FORCE_ROTATE][PAD_AXIS_Z]; pCenter = &pJoy->m_AxisCenter[7][PAD_AXIS_Z];	break;
		}
	}
	ef ( pdidoi->guidType == GUID_Slider )
	{
		StringCbPrintf( Title, sizeof(Title), "スライダー" );
		switch ( pdidoi->dwFlags & DIDOI_ASPECTMASK )
		{
		case DIDOI_ASPECTPOSITION:	pRange = &pJoy->m_fSliderRange[0]; pCenter = &pJoy->m_fSliderCenter[0];	break;
		case DIDOI_ASPECTVELOCITY:	pRange = &pJoy->m_fSliderRange[1]; pCenter = &pJoy->m_fSliderCenter[1];	break;
		case DIDOI_ASPECTACCEL:		pRange = &pJoy->m_fSliderRange[2]; pCenter = &pJoy->m_fSliderCenter[2];	break;
		case DIDOI_ASPECTFORCE:		pRange = &pJoy->m_fSliderRange[3]; pCenter = &pJoy->m_fSliderCenter[3];	break;
		}
	}
	else
	{
		StringCbPrintf( Title, sizeof(Title), "不明" );
		goto EXIT;
	}

	//-----------------------------------------------------------
	// データ設定
	//-----------------------------------------------------------
	if ( (pRange != NULL) && (pCenter != NULL) )
	{
		*pCenter = toF(diprg.lMin + diprg.lMax) * 0.5f;
		*pRange = toF(diprg.lMax) - *pCenter;
		Log_PrintTable( 128, Title, "( %d ～ %d )", diprg.lMin, diprg.lMax );
	}

EXIT:
	return DIENUM_CONTINUE;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CJoystick::CJoystick( IDirectInputDevice8 *pDevice )
{
	m_pDevice = pDevice;
	m_pDevice->AddRef();

	m_IsForceFeedback	= false;
	m_IsPolling			= false;

	for ( Sint32 i = 0; i < PAD_AXISDATA_MAX; i++ )
	{
		m_AxisRange[i][PAD_AXIS_X] = toF(AXIS_RANGE_MAX);
		m_AxisRange[i][PAD_AXIS_Y] = toF(AXIS_RANGE_MAX);
		m_AxisRange[i][PAD_AXIS_Z] = toF(AXIS_RANGE_MAX);
		m_AxisCenter[i][PAD_AXIS_X] = 0.0f;
		m_AxisCenter[i][PAD_AXIS_Y] = 0.0f;
		m_AxisCenter[i][PAD_AXIS_Z] = 0.0f;
	}

	for ( Sint32 i = 0; i < PAD_SLIDER_MAX; i++ )
	{
		m_fSliderRange[i] = AXIS_RANGE_MAX;
		m_fSliderCenter[i] = 0;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CJoystick::~CJoystick()
{
	// デバイス解放
	SAFE_RELEASE( m_pDevice );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CJoystick::Initialize( void )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "初期化" );
	Log_PrintCellKind( "ジョイスティック" );
	Log_CellBegin( 0 );

	DIDEVCAPS				caps	= { sizeof(DIDEVCAPS) };
	DIDEVICEINSTANCE		ddi		= { sizeof(DIDEVICEINSTANCE) };
	DIDEVICEOBJECTINSTANCE	didoi	= { sizeof(DIDEVICEOBJECTINSTANCE) };

	HRESULT hr;

	//----------------------------------------------------------
	// データフォーマットの設定
	//----------------------------------------------------------
	hr = m_pDevice->SetDataFormat( &g_DIJoystickDataFormat );
	if FAILED( hr )
	{
		Log_PrintLine( 0xFF0000, "データフォーマットの設定に失敗" );
		SAFE_RELEASE( m_pDevice );
		goto EXIT;
	}

	//----------------------------------------------------------
	// デバイス情報取得
	//----------------------------------------------------------
	m_pDevice->GetDeviceInfo( &ddi );
	m_pDevice->GetCapabilities( &caps );
	m_pDevice->GetObjectInfo( &didoi, 0, 0 );

	m_IsForceFeedback	= (caps.dwFlags & (DIDC_FORCEFEEDBACK                       )) != 0;
	m_IsPolling			= (caps.dwFlags & (DIDC_POLLEDDEVICE | DIDC_POLLEDDATAFORMAT)) != 0;

	Log_PrintStrongLine( 0x000000, "%s", ddi.tszProductName );
	Log_PrintTable( 128, "軸", "%d", caps.dwAxes );
	Log_PrintTable( 128, "ボタン", "%d", caps.dwButtons );
	Log_PrintTable( 128, "Pov", "%d", caps.dwPOVs );
	Log_PrintTable( 128, "ForceFeedback", "%s", m_IsForceFeedback ? "可" : "不可" );
	Log_PrintTable( 128, "Polling", "%s", m_IsPolling ? "必要" : "不要" );

	//----------------------------------------------------------
	// 軸モード設定
	//----------------------------------------------------------

	//----------------------------------------------------------
	// 軸列挙
	//----------------------------------------------------------
	Log_TableBegin();
	Log_CellBegin( 256 );
	Log_PrintStrong( 0x0000000, "軸の列挙" );
	Log_CellEnd();
	hr = m_pDevice->EnumObjects( EnumAxisCallback, this, DIDFT_AXIS );
	if FAILED( hr )
	{
		Log_TableEnd();
		Log_PrintLine( 0xFF0000, "軸の列挙に失敗" );
		SAFE_RELEASE( m_pDevice );
		goto EXIT;
	}

	Log_TableEnd();

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
void CJoystick::Refresh( void )
{
	if ( m_pDevice != NULL )
	{
		// ポーリングが必要な場合
		if ( m_IsPolling )
		{
			m_pDevice->Poll();
		}

		// データ取得
		SJoystickData Data;
		HRESULT hr = m_pDevice->GetDeviceState( sizeof(SJoystickData), &Data );
		if SUCCEEDED( hr )
		{
			// 軸を(-AXIS_RANGE_MAX ～ +AXIS_RANGE_MAX)に変換
			for ( Sint32 i = 0; i < PAD_AXISDATA_MAX; i++ )
			{
				m_Axis[i][PAD_AXIS_X] = AdjustAxis( Data.Axis[i][PAD_AXIS_X], m_AxisCenter[i][PAD_AXIS_X], m_AxisRange[i][PAD_AXIS_X], toF(AXIS_RANGE_MAX) );
				m_Axis[i][PAD_AXIS_Y] = AdjustAxis( Data.Axis[i][PAD_AXIS_Y], m_AxisCenter[i][PAD_AXIS_Y], m_AxisRange[i][PAD_AXIS_Y], toF(AXIS_RANGE_MAX) );
				m_Axis[i][PAD_AXIS_Z] = AdjustAxis( Data.Axis[i][PAD_AXIS_Z], m_AxisCenter[i][PAD_AXIS_Z], m_AxisRange[i][PAD_AXIS_Z], toF(AXIS_RANGE_MAX) );
			}

			// POV
			if ( LOWORD(Data.Pov) == 0xFFFF )
			{
				m_Axis[PAD_AXIS_POV][PAD_AXIS_X] = 0;
				m_Axis[PAD_AXIS_POV][PAD_AXIS_Y] = 0;
				m_Axis[PAD_AXIS_POV][PAD_AXIS_Z] = 0;
			}
			else
			{
				Sint32 Angle = DEG_TO_ANGLE( toF(Data.Pov) * 0.01f ) - DEG_TO_ANGLE( 90 );
				m_Axis[PAD_AXIS_POV][PAD_AXIS_X] = toI(Math::Cos( Angle ) * toF(AXIS_RANGE_MAX));
				m_Axis[PAD_AXIS_POV][PAD_AXIS_Y] = toI(Math::Sin( Angle ) * toF(AXIS_RANGE_MAX));
				m_Axis[PAD_AXIS_POV][PAD_AXIS_Z] = 0;
			}

			// スライダーを(-toF(AXIS_RANGE_MAX)～+toF(AXIS_RANGE_MAX))に変換
			for ( Sint32 i = 0; i < PAD_SLIDER_MAX; i++ )
			{
				m_Slider[i] = AdjustAxis( Data.Slider[i], m_fSliderCenter[i], m_fSliderRange[i], toF(AXIS_RANGE_MAX) );
			}

			// ボタン
			for ( Sint32 i = 0; i < PAD_BUTTON_MAX; i++ )
			{
				m_Button[i] = (Data.Button[i] & 0x80) != 0;
			}
		}
		else
		{
			// デバイス再アクセス
			m_pDevice->Acquire();

			// 入力クリア
			MemoryClear( &m_Axis, sizeof(m_Axis) );
			MemoryClear( &m_Slider, sizeof(m_Slider) );
			MemoryClear( &m_Button, sizeof(m_Button) );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CJoystick::AdjustAxis( Sint32 AxisSource, Float fAxisCenter, Float fAxisMax, Float fAxisRange )
{
	return toI((toF(AxisSource) - fAxisCenter) * fAxisRange / fAxisMax);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CJoystick::GetAxis( ePadAxisType Type, ePadAxisDirection Dir )
{
	return m_Axis[Type][Dir];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CJoystick::GetSlider( ePadSliderType Type )
{
	return m_Slider[Type];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CJoystick::GetButton( ePadButtonType Type )
{
	return m_Button[Type];
}

