

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "System.h"
#include "Math/Random.h"
#include "Class/Platform/Core/CGraphicCard.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Surface/CTexture.h"
#include "Class/Platform/Surface/CDepthTexture.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Fiber/CFiberController.h"
#include "Class/Common/Peripheral/CInput.h"
#include "Class/Common/Peripheral/CInputController.h"
#include "Class/Common/Peripheral/CJoystick.h"
#include "Class/Common/Peripheral/CKeyboard.h"
#include "Class/Common/Peripheral/CMouse.h"
#include "Class/Common/File/CFileHtmlLog.h"
#include "Class/Common/File/CFileManager.h"
#include "Class/Common/Sound/CStreamSound.h"
#include "Class/Common/Sound/CSound.h"
#include "NullDevice/Peripheral/NullKeyboard.h"
#include "NullDevice/Peripheral/NullJoystick.h"
#include "NullDevice/Sound/NullStreamSound.h"
#include "NullDevice/Sound/NullSound.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// TABLE
//-----------------------------------------------------------------------------------
static const Uint64 g_FrameRateTbl[] = { 60, 30, 20, 15 };


//-----------------------------------------------------------------------------------
// VARIABLE
//-----------------------------------------------------------------------------------
CCore *CCore::m_pCoreTbl[CORE_DATA_MAX];


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCore::CCore( Sint32 ID )
	: m_ID						( ID )
	, m_pFileManager			( NULL )
	, m_pGraphicCard			( NULL )
	, m_pRender					( NULL )
	, m_hWindow					( NULL )
	, m_hMutex					( NULL )
	, m_pInput					( NULL )
	, m_pKeyboard				( NULL )
	, m_pMouse					( NULL )
	, m_pDirectSound			( NULL )
	, m_pPrimaryBuffer			( NULL )
	, m_pFiberCtrl				( NULL )
	, m_IsBenchMode				( false )
	, m_IsWindow				( false )
	, m_IsActiveWindow			( false )
	, m_IsDrawTitleInfo			( false )
	, m_IsHideCursor			( false )
	, m_IsSleepUse				( true )
	, m_OneSecondCount			( 0 )
	, m_NowTime					( 0 )
	, m_OldTime					( 0 )
	, m_BeforeTime				( 0 )
	, m_ScreenWidth				( 0 )
	, m_ScreenHeight			( 0 )
	, m_SyncCount				( 0 )
	, m_FrameRate				( FRAME_RATE_60 )
	, m_CPUTimeTemp				( 0 )
	, m_CPUTimeSave				( 0 )
	, m_fCPUTime				( 0 )
	, m_FPSTemp					( 0 )
	, m_fFPS					( 0 )
	, m_PPFTemp					( 0 )
	, m_fPPF					( 0 )
	, m_VirtualScreenWidth		( 0 )
	, m_VirtualScreenHeight		( 0 )
	, m_fVirtual2RealX			( 0.0f )
	, m_fVirtual2RealY			( 0.0f )
	, m_fBackUpVirtual2RealX	( 0.0f )
	, m_fBackUpVirtual2RealY	( 0.0f )
{
	m_pCoreTbl[ID] = this;

	MemoryClear( m_ApplicationName, sizeof(m_ApplicationName) );
	MemoryClear( m_pJoystick, sizeof(m_pJoystick) );

	GetExePath( m_PluginDirectory, sizeof(m_PluginDirectory) );
	::StringCbCat( m_PluginDirectory, sizeof(m_PluginDirectory), "Plugin\\" );

	m_hInstance = ::GetModuleHandle( NULL );

	m_pSoundMgr = new CResourceObjectMgr( "サウンド" );
	m_pStreamSoundMgr = new CResourceObjectMgr( "ストリームサウンド" );

	// デフォルト
	File::IFileManager *pFileMgr = CreateFileManager();
	pFileMgr->SetRootPath( 0, NULL, NULL );
	pFileMgr->SetCurrentPath( NULL );
	SetFileManager( pFileMgr );

	// スレッド指定
	System::SetThreadCPUNo( 0 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCore::~CCore( void )
{
	// 所有オブジェクトの解体
	for ( Sint32 i = 0; i < Peripheral::JOYSTICK_MAX; i++ )
	{
		SAFE_RELEASE( m_pJoystick[i] );
	}
	SAFE_RELEASE( m_pMouse );
	SAFE_RELEASE( m_pKeyboard );
	SAFE_RELEASE( m_pInput );
	SAFE_RELEASE( m_pFileManager );

	SAFE_DELETE( m_pFiberCtrl );

	SAFE_RELEASE( m_pPrimaryBuffer );
	SAFE_RELEASE( m_pDirectSound );

	SAFE_DELETE( m_pSoundMgr );
	SAFE_DELETE( m_pStreamSoundMgr );

	m_pCoreTbl[m_ID] = NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::RegisterWindowClass( void )
{
	WNDCLASS WindowClass;

	//---------------------------------------------------------
	//	ウィンドウクラス登録
	//---------------------------------------------------------
	WindowClass.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	WindowClass.lpfnWndProc		= CommonMsgProc;
	WindowClass.cbClsExtra		= 0;
	WindowClass.cbWndExtra		= 0;
	WindowClass.hInstance		= m_hInstance;
	WindowClass.hIcon			= NULL;
	WindowClass.hCursor			= ::LoadCursor( NULL, IDC_ARROW );
	WindowClass.hbrBackground	= NULL;//(HBRUSH)::GetStockObject( BLACK_BRUSH );
	WindowClass.lpszMenuName	= NULL;
	WindowClass.lpszClassName	= m_ApplicationName;

	// ウィンドウクラス登録
	return ::RegisterClass( &WindowClass ) != 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::WindowCreate( void )
{
	//---------------------------------------------------------
	// ウィンドウ生成
	//---------------------------------------------------------
	m_hWindow = ::CreateWindowEx(
							0,
							m_ApplicationName,
							m_ApplicationName,
							0,
							CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT,
							NULL,
							NULL,
							m_hInstance,
							NULL );

	//---------------------------------------------------------
	// データ
	//---------------------------------------------------------
	::SetWindowLong( m_hWindow, GWL_USERDATA, m_ID );

	//---------------------------------------------------------
	// アイコン設定
	//---------------------------------------------------------
	HICON hIcon;
	hIcon = (HICON)::LoadImage( m_hInstance, "ICON_SMALL", IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0 );
	if ( hIcon != NULL ) ::SendMessage( m_hWindow, WM_SETICON, ICON_SMALL, (LPARAM)hIcon );
	hIcon = (HICON)::LoadImage( m_hInstance, "ICON_BIG", IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), 0 );
	if ( hIcon != NULL ) ::SendMessage( m_hWindow, WM_SETICON, ICON_BIG, (LPARAM)hIcon );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::Initialize( const char *pAppName, eFrameRate FrameRate )
{
	//=========================================================
	// 変数初期化
	//=========================================================
	StringCbCopy( m_ApplicationName, sizeof(m_ApplicationName), pAppName );
	m_FrameRate = FrameRate;

	//=========================================================
	// ウィンドウクラスの登録
	//=========================================================
	if ( !RegisterWindowClass() )
	{
		MsgBox( MB_ICONERROR, "ERROR", "ウィンドウクラスの登録に失敗" );
		return false;
	}

	//=========================================================
	// ウィンドウ生成
	//=========================================================
	if ( !WindowCreate() )
	{
		MsgBox( MB_ICONERROR, "ERROR", "ウィンドウ生成に失敗" );
		return false;
	}

	//=========================================================
	// 入力デバイスクラスの初期化
	//=========================================================
	m_pInput = new Peripheral::CInput( this );
	m_pInput->GetMouse( m_pMouse );
	m_pInput->GetKeyboard( m_pKeyboard );
	for ( Sint32 i = 0; i < Peripheral::JOYSTICK_MAX; i++ )
	{
		m_pInput->GetJoystick( m_pJoystick[i], i );
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::Start( Sint32 ScreenWidth, Sint32 ScreenHeight, Bool IsWindow )
{
	HRESULT hr;

	//----------------------------------------------------
	// ウィンドウサイズ
	//----------------------------------------------------
	m_IsWindow = IsWindow;
	m_ScreenWidth  = ScreenWidth;
	m_ScreenHeight = ScreenHeight;
	SetVirtualScreenSize( m_ScreenWidth, m_ScreenHeight, m_ScreenWidth, m_ScreenHeight );

	//----------------------------------------------------
	// ウィンドウ変形
	//----------------------------------------------------
	UpdateWidow();

	//----------------------------------------------------
	// 時間保存
	//----------------------------------------------------
	::QueryPerformanceFrequency( (LARGE_INTEGER*)&m_OneSecondCount );
	m_OldTime = GetSystemTimer();
	m_BeforeTime = GetSystemTimer();

	//----------------------------------------------------
	// DirectSound8生成
	//----------------------------------------------------
	hr = ::CoCreateInstance(
				CLSID_DirectSound8,
				NULL, 
				CLSCTX_ALL,
				IID_IDirectSound8,
				(void**)&m_pDirectSound );
	if FAILED( hr )
	{
		return;
	}

	//----------------------------------------------------
	// DirectSound初期化
	//----------------------------------------------------
	m_pDirectSound->Initialize( NULL );

	//----------------------------------------------------
	// 協調レベルの設定
	//----------------------------------------------------
	hr = m_pDirectSound->SetCooperativeLevel( m_hWindow, DSSCL_PRIORITY );
	if SUCCEEDED( hr )
	{
		//------------------------------------------
		// プライマリサウンドバッファ生成
		//------------------------------------------
		DSBUFFERDESC Desc = { sizeof(DSBUFFERDESC) };
		Desc.dwFlags = DSBCAPS_PRIMARYBUFFER;
		hr = m_pDirectSound->CreateSoundBuffer( &Desc, &m_pPrimaryBuffer, NULL );
		if SUCCEEDED( hr )
		{
			//--------------------------------
			// プライマリバッファフォーマット
			//--------------------------------
			WAVEFORMATEX wfx = { 0 };
			wfx.wFormatTag		= WAVE_FORMAT_PCM;													// 形式(PCM)
			wfx.nChannels		= 2;																// チャンネル(2chステレオ)
			wfx.nSamplesPerSec	= 44100;															// サンプリングレート(44100Hz)
			wfx.wBitsPerSample	= 16;																// 量子化ビット(16bit)
			wfx.nBlockAlign		= wfx.nChannels * (wfx.wBitsPerSample / 8);							// 1サンプリングあたりのバイト数(16bit×2ch)
			wfx.nAvgBytesPerSec	= wfx.nSamplesPerSec * wfx.nChannels * (wfx.wBitsPerSample / 8);	// 1秒あたりのバイト数(16bit×2ch×44100Hz)
			m_pPrimaryBuffer->SetFormat( &wfx );
		}
	}
	else
	{
		hr = m_pDirectSound->SetCooperativeLevel( m_hWindow, DSSCL_NORMAL );
		if FAILED( hr )
		{
			return;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::Message( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
	//======================================================================
	// メッセージ処理
	//======================================================================
	switch ( Msg )
	{
	//--------------------------------------------------------- マウスホイール
	case WM_MOUSEWHEEL:
		if ( m_pMouse != NULL )
		{
			m_pMouse->SetMouseWheel( (Sint16)HIWORD(wParam) );
		}
		break;

	//--------------------------------------------------------- 左ダブルクリック
	case WM_LBUTTONDBLCLK:
		if ( m_pMouse != NULL )
		{
			m_pMouse->SetDoubleClickL();
		}
		break;

	//--------------------------------------------------------- 右ダブルクリック
	case WM_RBUTTONDBLCLK:
		if ( m_pMouse )
		{
			m_pMouse->SetDoubleClickR();
		}
		break;

	//--------------------------------------------------------- ホイールダブルクリック
	case WM_MBUTTONDBLCLK:
		if ( m_pMouse != NULL )
		{
			m_pMouse->SetDoubleClickM();
		}
		break;

	//--------------------------------------------------------- システムキー
	case WM_SYSKEYDOWN:
		// ALT+ENTERでフルスクリーン切り替え
		if ( wParam == VK_RETURN )
		{
			// 画面切り替え
			ChangeScreenMode();
		}
		break;

	//--------------------------------------------------------- フォーカス移動時
	case WM_ACTIVATEAPP:
		m_IsActiveWindow = (wParam != 0);
		break;

	//--------------------------------------------------------- 生成時
	case WM_CREATE:
		if ( m_IsHideCursor )
		{
			ShowCursor( false );
		}
		break;

	//--------------------------------------------------------- 終了時
	case WM_CLOSE:
		if ( m_IsHideCursor )
		{
			ShowCursor( true );
		}
		// もうウィンドウハンドル無効やね
		m_hWindow = NULL;
		// 終了
		::SendMessage( hWnd, WM_DESTROY, 0, 0 );
		break;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::SetRender( Renderer::CRender *pRender )
{
	m_pRender = pRender;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::MsgBox( Sint32 Flag, const char *pTitle, const char *pStr,... )
{
	char Temp[1024] = "";

	StringCbVPrintf( Temp, sizeof(Temp), pStr, (char*)(&pStr + 1) );

	if ( m_pRender != NULL ) m_pRender->SetGUIEnable( true );
	::MessageBox( m_hWindow, Temp, pTitle, Flag );
	if ( m_pRender != NULL ) m_pRender->SetGUIEnable( false );

	// FEP閉じる
	::SendMessage( ::ImmGetDefaultIMEWnd( m_hWindow ), WM_CLOSE, 0, 0 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::SelectBox( const char *pTitle, const char *pStr,... )
{
	char Temp[1024] = "";
	Sint32 Ret;

	StringCbVPrintf( Temp, sizeof(Temp), pStr, (char*)(&pStr + 1) );

	if ( m_pRender != NULL ) m_pRender->SetGUIEnable( true );
	Ret = ::MessageBox( m_hWindow, Temp, pTitle, MB_YESNO | MB_ICONQUESTION );
	if ( m_pRender != NULL ) m_pRender->SetGUIEnable( false );
	
	// FEP閉じる
	::SendMessage( ::ImmGetDefaultIMEWnd( m_hWindow ), WM_CLOSE, 0, 0 );

	return Ret == IDYES;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::ControlMsgLoop( Bool IsFullActive )
{
	MSG Msg;

	for ( ; ; )
	{
		// メッセージ処理
		while ( ::PeekMessage( &Msg, 0, 0, 0, PM_REMOVE ) )
		{
			// 終了？
			if ( Msg.message == WM_QUIT )
			{
				m_IsActiveWindow = true;
				break;
			}

			// メッセージの翻訳
			::TranslateMessage( &Msg );
			::DispatchMessage( &Msg );
		}

		// 終了
		if ( IsFullActive || m_IsActiveWindow )
		{
			break;
		}

		::SleepEx( 100, true );
	}

	return m_hWindow != NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::Run( Bool IsFullActive )
{
	//--------------------------------------------------
	// メッセージループ
	//--------------------------------------------------
	if ( !ControlMsgLoop( IsFullActive ) )
	{
		if ( m_pRender != NULL )
		{
			m_pRender->AbortAllScene();
		}
		return false;
	}

	//--------------------------------------------------
	// フレーム数加算
	//--------------------------------------------------
	m_SyncCount++;
	m_FPSTemp++;

	//--------------------------------------------------
	// CPU時間
	//--------------------------------------------------
	m_CPUTimeTemp += GetSystemTimer() - m_CPUTimeSave;

	//--------------------------------------------------
	// デバイス処理
	//--------------------------------------------------
	if ( m_pRender != NULL )
	{
		// 画面をリフレッシュ
		m_pRender->Refresh( m_hWindow );
	}

	//--------------------------------------------------
	// FPS算出
	//--------------------------------------------------
	if ( (m_NowTime - m_BeforeTime) >= GetSystemTimerBySec() )
	{
		Double fTimeDiv = 1.0 / ((Double)m_NowTime - (Double)m_BeforeTime);
		// 保存
		m_fFPS = (Float)((Double)m_FPSTemp * (Double)GetSystemTimerBySec() * fTimeDiv);
		m_fPPF = (Float)((Double)m_PPFTemp * (Double)GetSystemTimerBySec() * fTimeDiv);
		m_fCPUTime = (Float)((Double)m_CPUTimeTemp * (Double)GetSystemTimerBySec() * fTimeDiv);

		m_fCPUTime = (Float)(100.0 * m_fCPUTime / (Double)GetSystemTimerBySec());
		m_fCPUTime = m_fCPUTime * (Float)g_FrameRateTbl[m_FrameRate] / m_fFPS;

		m_fPPF /= m_fFPS;

		m_BeforeTime = m_NowTime;

		m_CPUTimeTemp = 0;
		m_FPSTemp = 0;
		m_PPFTemp = 0;

		// 描画？
		if ( m_IsDrawTitleInfo )
		{
			char Str[256] = "";
			char Temp[32];
			StringCbCat( Str, sizeof(Str), m_ApplicationName );
			StringCbPrintf( Temp, sizeof(Temp), " FPS[%.2lf]", m_fFPS );
			StringCbCat( Str, sizeof(Str), Temp );
			StringCbPrintf( Temp, sizeof(Temp), " CPU[%.2lf]", m_fCPUTime );
			StringCbCat( Str, sizeof(Str), Temp );
			StringCbPrintf( Temp, sizeof(Temp), " POLYGON[%.2lf]", m_fPPF );
			StringCbCat( Str, sizeof(Str), Temp );
			::SetWindowText( m_hWindow, Str );
		}
	}

	//--------------------------------------------------
	// フレームレート調整
	//--------------------------------------------------
	ControlFrameRate();

	//--------------------------------------------------
	// CPU時間計測用
	//--------------------------------------------------
	m_CPUTimeSave = GetSystemTimer();

	//--------------------------------------------------
	// 入力デバイス更新
	//--------------------------------------------------
	m_pInput->Refresh();

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const char *CCore::GetPluginDirectory( void )
{
	return m_PluginDirectory;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::SetPluginDirectory( const char *pDirectory )
{
	::StringCbCopy( m_PluginDirectory, sizeof(m_PluginDirectory), pDirectory );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::ControlFrameRate( void )
{
	//--------------------------------------------
	// 待ち時間
	//--------------------------------------------
	Uint64 WaitTime = GetSystemTimerBySec() / g_FrameRateTbl[m_FrameRate];

	//--------------------------------------------
	// 現在の時間取得
	//--------------------------------------------
	m_NowTime = GetSystemTimer();

	//--------------------------------------------
	// 差分
	//--------------------------------------------
	Uint64 DifferenceTime = m_NowTime - m_OldTime;

	//--------------------------------------------
	// 時間経過を待つ
	//--------------------------------------------
	if ( !m_IsBenchMode )
	{
		if ( DifferenceTime < WaitTime )
		{
			if ( m_IsSleepUse )
			{
				Sint32 SleepTime = (Sint32)((WaitTime - DifferenceTime) * 1000 / GetSystemTimerBySec());
				if ( SleepTime > 2 )
				{
					::Sleep( SleepTime - 1 );
				}
			}

			// 残り
			do
			{
				DifferenceTime = GetSystemTimer() - m_OldTime;
			}
			while ( DifferenceTime < WaitTime );
		}
	}

	//--------------------------------------------
	// 終了
	//--------------------------------------------
	m_OldTime = GetSystemTimer();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::PlayMovie( const char *pFileName, Bool IsLoop, Bool (__stdcall *pCallback)( void ) )
{
	Thread::CAutoLock Lock( m_CS );

	Uint64 StartPos, EndPos, CurrentPos;
	HRESULT hr;

	m_pRender->SetGUIEnable( true );

	//--------------------------------------------
	// ファイル名
	//--------------------------------------------
	wchar_t wFileName[MAX_PATH] = L"";
	MBtoWC( pFileName, wFileName, MAX_PATH );

	//--------------------------------------------
	// インターフェイス初期化
	//--------------------------------------------
	IGraphBuilder	*pGraphBuilder	= NULL;
	IMediaSeeking	*pMediaSeeking	= NULL;
	IMediaControl	*pMediaControl	= NULL;
	IVideoWindow	*pVideoWindow	= NULL;

	hr = ::CoCreateInstance(
				CLSID_FilterGraph,
				NULL,
				CLSCTX_INPROC,
				IID_IGraphBuilder,
				(void**)&pGraphBuilder );
	if FAILED( hr ) goto EXIT;

	hr = pGraphBuilder->QueryInterface( IID_IMediaSeeking, (void**)&pMediaSeeking );
	if FAILED( hr ) goto EXIT;

	hr = pGraphBuilder->QueryInterface( IID_IMediaControl, (void**)&pMediaControl );
	if FAILED( hr ) goto EXIT;

	hr = pMediaControl->RenderFile( wFileName );
	if FAILED( hr ) goto EXIT;

	hr = pGraphBuilder->QueryInterface( IID_IVideoWindow, (void**)&pVideoWindow );
	if FAILED( hr ) goto EXIT;

	hr = pVideoWindow->put_Owner( (OAHWND)GetWindowHandle() );
	if FAILED( hr ) goto EXIT;

	hr = pVideoWindow->put_WindowStyle( WS_CHILD | WS_CLIPSIBLINGS );
	if FAILED( hr ) goto EXIT;

	hr = pVideoWindow->SetWindowPosition( 0, 0, m_ScreenWidth, m_ScreenHeight );
	if FAILED( hr ) goto EXIT;

	hr = pVideoWindow->SetWindowForeground( OATRUE );
	if FAILED( hr ) goto EXIT;

	hr = pVideoWindow->put_Visible( OATRUE );
	if FAILED( hr ) goto EXIT;

	hr = pMediaControl->Run();
	if FAILED( hr ) goto EXIT;

	//--------------------------------------------
	// メッセージループ
	//--------------------------------------------
	while ( ControlMsgLoop( true ) )
	{
		// 適当にスリープさせる（動画の性質を考えて60フレ保障）
		::SleepEx( 10, TRUE );

		// 入力デバイスの更新
		m_pInput->Refresh();

		// コールバック
		if ( (pCallback != NULL) && !pCallback() )
		{
			break;
		}

		// 終了チェック
		pMediaSeeking->GetPositions( (LONGLONG*)&CurrentPos, (LONGLONG*)&EndPos );
		if ( CurrentPos >= EndPos )
		{
			if ( IsLoop )
			{
				// 適当にスリープさせる
				::SleepEx( 1000, TRUE );
				// 先頭にシーク
				StartPos = 0;
				pMediaSeeking->SetPositions( (LONGLONG*)&StartPos, AM_SEEKING_AbsolutePositioning, NULL, NULL );
			}
			else
			{
				// ぬける
				break;
			}
		}
	}

	//--------------------------------------------
	// 解放処理
	//--------------------------------------------
EXIT:
	SAFE_RELEASE( pVideoWindow );
	SAFE_RELEASE( pMediaControl );
	SAFE_RELEASE( pMediaSeeking );
	SAFE_RELEASE( pGraphBuilder );

	m_pRender->SetGUIEnable( false );

	return SUCCEEDED( hr );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::SetVirtualScreenSize( Sint32 RealWidth, Sint32 RealHeight, Sint32 VirtualWidth, Sint32 VirtualHeight )
{
	m_VirtualScreenWidth  = VirtualWidth;
	m_VirtualScreenHeight = VirtualHeight;

	m_fVirtual2RealX = toF(RealWidth)  / toF(VirtualWidth);
	m_fVirtual2RealY = toF(RealHeight) / toF(VirtualHeight);

	m_fBackUpVirtual2RealX = m_fVirtual2RealX;
	m_fBackUpVirtual2RealY = m_fVirtual2RealY;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::SetVirtualScreenEnable( Bool IsEnable )
{
	if ( IsEnable )
	{
		m_fVirtual2RealX = m_fBackUpVirtual2RealX;
		m_fVirtual2RealY = m_fBackUpVirtual2RealY;
	}
	else
	{
		m_fBackUpVirtual2RealX = m_fVirtual2RealX;
		m_fBackUpVirtual2RealY = m_fVirtual2RealY;
		m_fVirtual2RealX = 1.0f;
		m_fVirtual2RealY = 1.0f;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CCore::Virtual2RealX( Float Pos )
{
	return Pos * m_fVirtual2RealX;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CCore::Virtual2RealY( Float Pos )
{
	return Pos * m_fVirtual2RealY;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DF CCore::Virtual2RealTransform( void )
{
	return Math::Point2DF( m_fVirtual2RealX, m_fVirtual2RealY );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::DrawPolygon( Sint32 Cnt )
{
	m_PPFTemp += Cnt;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::SetWindowCenter( HWND hWnd, HWND hWndParent )
{
    RECT RectParent, Rect;

	::GetWindowRect( hWndParent, &RectParent );
	::GetWindowRect( hWnd, &Rect );
	Sint32 w = Rect.right-Rect.left;
	Sint32 h = Rect.bottom-Rect.top;
    Sint32 x = (RectParent.right - w) / 2;
    Sint32 y = (RectParent.bottom - h) / 2;
	::SetWindowPos( hWnd, HWND_NOTOPMOST, x, y, w, h, 0 ); 
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HWND CCore::GetWindowHandle( void )
{
	return m_hWindow;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HINSTANCE CCore::GetInstanceHandle( void )
{
	return m_hInstance;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CCore::GetCPU( void )
{
	return m_fCPUTime;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CCore::GetFPS( void )
{
	return m_fFPS;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CCore::GetPPF( void )
{
	return m_fPPF;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::GetApplicationName( char *pAppName, Sint32 AppNameSize )
{
	StringCbCopy( pAppName, AppNameSize, m_ApplicationName );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::GetScreenData( Sint32 *pWidth, Sint32 *pHeight, Bool *pIsWindow )
{
	if ( pWidth != NULL ) *pWidth = m_ScreenWidth;
	if ( pHeight != NULL ) *pHeight = m_ScreenHeight;
	if ( pIsWindow != NULL ) *pIsWindow = m_IsWindow;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::GetVirtualScreenSize( Sint32 *pWidth, Sint32 *pHeight )
{
	*pWidth = m_VirtualScreenWidth;
	*pHeight = m_VirtualScreenHeight;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::IsWindowMode( void )
{
	return m_IsWindow;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::ChangeScreenMode( void )
{
	if ( m_IsWindow )
	{
		// モードスワップ
		m_IsWindow = !m_IsWindow;
		// ウィンドウリセット
		UpdateWidow();
		// Direct3Dデバイスリセット
		if ( m_pRender != NULL )
		{
			m_pRender->ResetDevice( true );
		}

		// カーソル
		POINT Pt = { m_ScreenWidth, m_ScreenHeight };
		::ClientToScreen( m_hWindow, &Pt );
		::SetCursorPos( Pt.x, Pt.y );
	}
	else
	{
		// モードスワップ
		m_IsWindow = !m_IsWindow;
		// Direct3Dデバイスリセット
		if ( m_pRender != NULL )
		{
			m_pRender->ResetDevice( true );
		}
		// ウィンドウリセット
		UpdateWidow();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::ResizeWindowSize( Math::Point2DI Size )
{
	m_ScreenWidth	= Size.x;
	m_ScreenHeight	= Size.y;

	if ( m_IsWindow )
	{
		// ウィンドウリセット
		UpdateWidow();
		// Direct3Dデバイスリセット
		if ( m_pRender != NULL )
		{
			m_pRender->ResetDevice( true );
		}
	}
	else
	{
		// Direct3Dデバイスリセット
		if ( m_pRender != NULL )
		{
			m_pRender->ResetDevice( true );
		}
		// ウィンドウリセット
		UpdateWidow();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::UpdateWidow( void )
{
	//---------------------------------------------------------
	// メニュー
	//---------------------------------------------------------
	HMENU hMenu = ::LoadMenu( m_hInstance, "MAIN_MENU" );
	::SetMenu( m_hWindow, hMenu );

	//---------------------------------------------------------
	//	ウィンドウ生成情報の作成
	//---------------------------------------------------------
	Sint32 x = 0;
	Sint32 y = 0;
	Sint32 w = m_ScreenWidth;
	Sint32 h = m_ScreenHeight;
	Sint32 StyleFlag = WS_VISIBLE;
	Sint32 ExStyleFlag = 0;

	// ウィンドウモード
	if ( m_IsWindow )
	{
		// スタイル
		StyleFlag |= WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

		// 実ウィンドウサイズ
		RECT Rect = { 0, 0, w, h };
		::AdjustWindowRectEx( &Rect, StyleFlag, hMenu != NULL, ExStyleFlag );
		w = Rect.right - Rect.left;
		h = Rect.bottom - Rect.top;

		// センタリング
		x = ::GetSystemMetrics(SM_CXSCREEN)/2 - w/2;
		y = ::GetSystemMetrics(SM_CYSCREEN)/2 - h/2;
	}

	//---------------------------------------------------------
	// ウインドウモードにあったウインドウに再定義する
	//---------------------------------------------------------
	::SetWindowLong( m_hWindow, GWL_STYLE, StyleFlag );
	::SetWindowLong( m_hWindow, GWL_EXSTYLE, ExStyleFlag );

	//---------------------------------------------------------
	// ウインドウ表示座標をセット
	//---------------------------------------------------------
	::SetWindowPos( m_hWindow, HWND_NOTOPMOST, x, y, w, h, 0 );

	//---------------------------------------------------------
	// IME
	//---------------------------------------------------------
	HWND hIME = ::ImmGetDefaultIMEWnd( m_hWindow );
	::SendMessage( hIME, WM_IME_CONTROL, IMC_CLOSESTATUSWINDOW, 0 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::Exit( void )
{
	::PostMessage( m_hWindow, WM_CLOSE, 0, 0 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint64 CCore::GetSystemTimer( void )
{
	Uint64 Time;
	::QueryPerformanceCounter( (LARGE_INTEGER*)&Time );
	return Time;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint64 CCore::GetSystemTimerBySec( void )
{
	return m_OneSecondCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CCore::GetSyncCount( void )
{
	return m_SyncCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CCore::GetMultiMediaTime( void )
{
	return ::timeGetTime();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::EnableDrawTitleInformation( Bool IsEnable )
{
	m_IsDrawTitleInfo = IsEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::EnableDrawMouseCursor( Bool IsEnable )
{
	m_IsHideCursor = !IsEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::FolderSelect( char *pDirPath, Sint32 DirPathSize )
{
	pDirPath[0] = '\0';

    HRESULT hr;
    BROWSEINFO bi;
    ITEMIDLIST *lpid = NULL;
    LPMALLOC pMalloc = NULL;

	MemoryClear( &bi, sizeof(BROWSEINFO) );

	bi.hwndOwner	= GetWindowHandle();
	bi.ulFlags		= BIF_EDITBOX;
	bi.lpszTitle	= "ディレクトリ指定";

	lpid = ::SHBrowseForFolder( &bi );

	if ( lpid == NULL )
	{
		return false;
	}
	else
	{
		hr = ::SHGetMalloc( &pMalloc );
		if ( hr == E_FAIL )
		{
			return false;
		}

		::SHGetPathFromIDList( lpid, pDirPath );
		size_t Len = strlen( pDirPath );
		if ( pDirPath[Len - 1] != '\\' ) StringCbCat( pDirPath, DirPathSize, "\\" );

		pMalloc->Free( lpid );
		SAFE_RELEASE( pMalloc );
	}

	System::ResetCurrentDirectory();

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::FileOpenDialog( char *pPath, const char *pTitle, const char *pFilter, const char *pExt )
{
	pPath[0] = '\0';

	//=======================================================
	// ファイルオープン
	//=======================================================
	OPENFILENAME ofn;
	MemoryClear( &ofn, sizeof(OPENFILENAME) );

	ofn.lStructSize		= sizeof(OPENFILENAME);
	ofn.hwndOwner		= GetWindowHandle();
	ofn.lpstrTitle		= pTitle;
	ofn.lpstrFilter		= pFilter;
	ofn.nFilterIndex	= 1;
	ofn.lpstrFile		= pPath;
	ofn.nMaxFile		= 256;
	ofn.lpstrDefExt		= pExt;
	ofn.Flags			= OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	Bool result = (::GetOpenFileName( &ofn ) != false);

	System::ResetCurrentDirectory();

	return result;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::FileSaveDialog( char *pPath, const char *pTitle, const char *pFilter, const char *pExt )
{
	pPath[0] = '\0';
	
	OPENFILENAME ofn;
	MemoryClear( &ofn, sizeof(OPENFILENAME) );
	
	ofn.lStructSize		= sizeof(OPENFILENAME);
	ofn.hwndOwner		= GetWindowHandle();
	ofn.lpstrTitle		= pTitle;
	ofn.lpstrFilter		= pFilter;
	ofn.nFilterIndex	= 1;
	ofn.lpstrFile		= pPath;
	ofn.nMaxFile		= 256;
	ofn.lpstrDefExt		= pExt;
	ofn.lpstrInitialDir	= NULL;
	ofn.Flags			= OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;

	Bool result = (::GetSaveFileName( &ofn ) != false);

	System::ResetCurrentDirectory();

	return result;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::IsBenchMode( void )
{
	return m_IsBenchMode;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::SetBenchMode( Bool IsEnable )
{
	m_IsBenchMode = IsEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::SetSleepUse( Bool IsEnable )
{
	m_IsSleepUse = IsEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCore::OpenColorDialog( Sint32 *pR, Sint32 *pG, Sint32 *pB )
{
	COLORREF color = RGB(*pR,*pG,*pB);

	CHOOSECOLOR cc = {
		sizeof(CHOOSECOLOR),
		GetWindowHandle(),
		NULL,
		color,
		&color,
		CC_FULLOPEN | CC_RGBINIT,
	};

	if ( !::ChooseColor( &cc ) ) return false;

	*pR = (cc.rgbResult>>16) & 0xFF;
	*pG = (cc.rgbResult>> 8) & 0xFF;
	*pB = (cc.rgbResult>> 0) & 0xFF;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IGraphicCard *CCore::CreateGraphicCard( eGraphicCardNo GraphicCardNo )
{
	if ( m_pGraphicCard == NULL )
	{
		Thread::CAutoLock Lock( m_CS );
		if ( m_pGraphicCard == NULL )
		{
			m_pGraphicCard = new CGraphicCard( this );
			if ( !m_pGraphicCard->Initialize( GraphicCardNo ) )
			{
				SAFE_RELEASE( m_pGraphicCard );
				return NULL;
			}

			return m_pGraphicCard;
		}
	}

	m_pGraphicCard->AddRef();

	return m_pGraphicCard;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CCore::GetJoystickCount( void )
{
	return m_pInput->GetJoystickCount();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Peripheral::IMouse *CCore::GetMouse( void )
{
	m_pMouse->AddRef();

	return m_pMouse;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Peripheral::IKeyboard *CCore::GetKeyboard( void )
{
	if ( m_pKeyboard == NULL )
	{
		Thread::CAutoLock Lock( m_CS );
		if ( m_pKeyboard == NULL )
		{
			static Peripheral::NullKeyboard Dummy;
			return &Dummy;
		}
	}

	m_pKeyboard->AddRef();

	return m_pKeyboard;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Peripheral::IJoystick *CCore::GetJoystick( Sint32 No )
{
	if ( m_pJoystick[No] == NULL )
	{
		Thread::CAutoLock Lock( m_CS );
		if ( m_pJoystick[No] == NULL )
		{
			static Peripheral::NullJoystick Dummy;
			return &Dummy;
		}
	}

	m_pJoystick[No]->AddRef();

	return m_pJoystick[No];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Peripheral::IInputController *CCore::GetInputController( Sint32 No, Sint32 KeyRepeatStartTime, Sint32 KeyRepeatInterval )
{
	Thread::CAutoLock Lock( m_CS );

	Peripheral::IKeyboard *pKeyboard = GetKeyboard();
	Peripheral::IJoystick *pJoystick = GetJoystick( No );

	Peripheral::CInputController *pInputCtrl = new Peripheral::CInputController( KeyRepeatStartTime, KeyRepeatInterval, pKeyboard, pJoystick );

	SAFE_RELEASE( pKeyboard );
	SAFE_RELEASE( pJoystick );

	return pInputCtrl;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
File::IFileManager *CCore::CreateFileManager( void )
{
	Thread::CAutoLock Lock( m_CS );

	return new File::CFileManager;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
File::IFileManager *CCore::GetFileMgrPointer( void )
{
	Thread::CAutoLock Lock( m_CS );

	return m_pFileManager;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCore::SetFileManager( File::IFileManager *pMgr )
{
	Thread::CAutoLock Lock( m_CS );

	if ( !pMgr->IsInvalid() )
	{
		File::CFileManager *pNewMgr = (File::CFileManager*)pMgr;
		SAFE_RELEASE( m_pFileManager );
		m_pFileManager = pNewMgr;
		m_pFileManager->AddRef();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sound::IStreamSound *CCore::CreateStreamSoundFromFile( const char *pFileName, Bool IsGlobalScope, const char *pPluginName )
{
	Thread::CAutoLock Lock( m_CS );

	static Sound::NullStreamSound Dummy;
	Sound::IStreamSound *pSnd;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( "ストリームサウンド" );
	Log_CellBegin( 0 );

	char FilePath[MAX_PATH] = "";
	if ( !m_pFileManager->GetFilePath( FilePath, sizeof(FilePath), pFileName ) )
	{
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintStrong( 0xFF0000, "ファイルが見つかりません" );
		pSnd = &Dummy;
	}
	else
	{
		Log_PrintLine( 0x000000, "%s", FilePath );

		Sound::CStreamSound *pData = new Sound::CStreamSound( this, m_pStreamSoundMgr );
		if ( !pData->CreateFromFile( pFileName, IsGlobalScope, pPluginName, m_pDirectSound ) )
		{
			SAFE_RELEASE( pData );
			pSnd = &Dummy;
		}
		else
		{
			Log_PrintStrongLine( 0x008000, "完了" );
			pData->SetName( FilePath );
			pSnd = pData;
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pSnd;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sound::ISound *CCore::CreateSoundFromFile( const char *pFileName, Sint32 LayerCount, Bool IsGlobalScope )
{
	Thread::CAutoLock Lock( m_CS );

	static Sound::NullSound Dummy;
	Sound::ISound *pSnd;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( "サウンド" );
	Log_CellBegin( 0 );

	char FilePath[MAX_PATH] = "";
	if ( !m_pFileManager->GetFilePath( FilePath, sizeof(FilePath), pFileName ) )
	{
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintStrong( 0xFF0000, "ファイルが見つかりません" );
		pSnd = &Dummy;
	}
	else
	{
		Log_PrintLine( 0x000000, "%s", FilePath );

		if ( m_pDirectSound == NULL )
		{
			Log_PrintStrong( 0xFF0000, "DirectSoundが初期化されていません" );
			pSnd = &Dummy;
		}
		else
		{
			Sound::CSound *pData = new Sound::CSound( this, m_pSoundMgr );
			if ( !pData->CreateFromFile( pFileName, LayerCount, IsGlobalScope, m_pDirectSound ) )
			{
				SAFE_RELEASE( pData );
				pSnd = &Dummy;
			}
			else
			{
				Log_PrintStrongLine( 0x008000, "完了" );
				pData->SetName( FilePath );
				pSnd = pData;
			}
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pSnd;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Fiber::IFiberController *CCore::CreateFiberController( Sint32 Max )
{
	if ( m_pFiberCtrl == NULL )
	{
		Thread::CAutoLock Lock( m_CS );
		if ( m_pFiberCtrl == NULL )
		{
			m_pFiberCtrl = new Fiber::CFiberController( Max );
		}
	}

	m_pFiberCtrl->AddRef();

	return m_pFiberCtrl;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ICore *CCore::CreateCore( void )
{
	Sint32 ID = GetCoreID();
	if ( ID != -1 )
	{
		return new CCore( ID );
	}

	return NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CCore::GetCoreID( void )
{
	for ( Sint32 i = 0; i < CORE_DATA_MAX; i++ )
	{
		if ( m_pCoreTbl[i] == NULL )
		{
			return i;
		}
	}

	return -1;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
LRESULT CALLBACK CCore::CommonMsgProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
	//======================================================================
	// メッセージ処理
	//======================================================================
	switch ( Msg )
	{
	//--------------------------------------------------------- ウィンドウ解体時
	case WM_DESTROY:
		// 終了
		::PostQuitMessage( 0 );
		break;

	//--------------------------------------------------------- システムコマンド
	case WM_SYSCOMMAND:
		// スクリーンセーバー関係の処理を抑制
		switch ( wParam )
		{
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return 0;
		}
		break;

	//--------------------------------------------------------- IME表示抑制
	case WM_IME_SETCONTEXT:
        lParam = 0;
		break;

	//--------------------------------------------------------- IME表示抑制
	case WM_IME_STARTCOMPOSITION:
	case WM_IME_ENDCOMPOSITION:
	case WM_IME_COMPOSITION:
	    return 0;

	//--------------------------------------------------------- IME表示抑制
	case WM_IME_NOTIFY:
	    switch ( wParam )
		{
		case IMN_OPENSTATUSWINDOW:
		case IMN_CLOSESTATUSWINDOW:
		case IMN_CHANGECANDIDATE:
		case IMN_OPENCANDIDATE:
		case IMN_CLOSECANDIDATE:
			return 0;
		}
		break;
	}

	//======================================================================
	// 対象コアに転送
	//======================================================================
	Sint32 ID = ::GetWindowLong( hWnd, GWL_USERDATA );
	CCore *pCore = m_pCoreTbl[ID];
	if ( pCore != NULL )
	{
		// メッセージ処理
		pCore->Message( hWnd, Msg, wParam, lParam );
	}

	return ::DefWindowProc( hWnd, Msg, wParam, lParam );
}

