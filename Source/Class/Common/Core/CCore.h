#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/ClassReference.h"
#include "Class/Common/Object/CBaseObject.h"
#include "Class/Common/Object/CResourceObjectMgr.h"
#include "Class/Platform/Core/CGraphicCard.h"
#include "Thread/CriticalSection.h"
#include "Interface/Core/ICore.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class CCore : public CBaseObject, public ICore
	{
		enum { CORE_DATA_MAX = 16 };

	private:
		static CCore *m_pCoreTbl[CORE_DATA_MAX];

	private:
		static LRESULT CALLBACK CommonMsgProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

	public:
		static ICore *CreateCore( void );
		static Sint32 GetCoreID( void );

	protected:
		Sint32 m_ID;
		HANDLE m_hMutex;
		HINSTANCE m_hInstance;
		char m_ApplicationName[64];
		Uint64 m_OneSecondCount;
		Uint64 m_NowTime;
		Uint64 m_OldTime;
		Uint64 m_BeforeTime;
		Thread::CCriticalSection m_CS;

		HWND m_hWindow;
		Sint32 m_ScreenWidth;
		Sint32 m_ScreenHeight;
		Bool m_IsWindow;
		Bool m_IsActiveWindow;
		Bool m_IsDrawTitleInfo;
		Bool m_IsHideCursor;
		Sint32 m_VirtualScreenWidth;
		Sint32 m_VirtualScreenHeight;
		Float m_fVirtual2RealX;
		Float m_fVirtual2RealY;
		Float m_fBackUpVirtual2RealX;
		Float m_fBackUpVirtual2RealY;

		Bool m_IsBenchMode;
		Bool m_IsSleepUse;
		Sint32 m_SyncCount;
		eFrameRate m_FrameRate;
		Uint64 m_CPUTimeSave;
		Uint64 m_CPUTimeTemp;
		Float m_fCPUTime;
		Sint32 m_FPSTemp;
		Float m_fFPS;
		Sint32 m_PPFTemp;
		Float m_fPPF;

		IDirectSound8 *m_pDirectSound;
		IDirectSoundBuffer *m_pPrimaryBuffer;
		Fiber::CFiberController *m_pFiberCtrl;
		File::CFileManager *m_pFileManager;
		CGraphicCard *m_pGraphicCard;
		Renderer::CRender *m_pRender;
		Peripheral::CInput *m_pInput;
		Peripheral::CKeyboard *m_pKeyboard;
		Peripheral::CJoystick *m_pJoystick[Peripheral::JOYSTICK_MAX];
		Peripheral::CMouse *m_pMouse;

		CResourceObjectMgr *m_pSoundMgr;
		CResourceObjectMgr *m_pStreamSoundMgr;

		char m_PluginDirectory[MAX_PATH];

	private:
		CCore( Sint32 ID );
		virtual ~CCore( void );

	protected:
		virtual Bool RegisterWindowClass( void );
		virtual Bool WindowCreate( void );
		virtual void UpdateWidow( void );
		virtual void Message( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
		virtual void ControlFrameRate( void );
		virtual void SetWindowCenter( HWND hWnd, HWND hWndParent );
		virtual Bool ControlMsgLoop( Bool IsFullActive );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual void SetRender( Renderer::CRender *pRender );

		virtual Bool Initialize( const char *pAppName, eFrameRate FrameRate );
		virtual void Start( Sint32 ScreenWidth, Sint32 ScreenHeight, Bool IsWindow );

		virtual void Exit( void );
		virtual Bool Run( Bool IsFullActive );

		virtual void SetVirtualScreenSize( Sint32 RealWidth, Sint32 RealHeight, Sint32 VirtualWidth, Sint32 VirtualHeight );

		virtual HWND GetWindowHandle( void );
		virtual HINSTANCE GetInstanceHandle( void );
		virtual Float GetCPU( void );
		virtual Float GetFPS( void );
		virtual Float GetPPF( void );
		virtual void GetApplicationName( char *pAppName, Sint32 AppNameSize );
		virtual void GetScreenData( Sint32 *pWidth, Sint32 *pHeight, Bool *pIsWindow );
		virtual void GetVirtualScreenSize( Sint32 *pWidth, Sint32 *pHeight );
		virtual Float Virtual2RealX( Float Pos );
		virtual Float Virtual2RealY( Float Pos );
		virtual Math::Point2DF Virtual2RealTransform( void );

		virtual void DrawPolygon( Sint32 Cnt );
		virtual Bool IsWindowMode( void );
		virtual void ChangeScreenMode( void );
		virtual void ResizeWindowSize( Math::Point2DI Size );
		virtual void SetVirtualScreenEnable( Bool IsEnable );
		virtual void SetBenchMode( Bool IsEnable );
		virtual void SetSleepUse( Bool IsEnable );
		virtual Bool IsBenchMode( void );

		virtual Uint64 GetSystemTimer( void );
		virtual Uint64 GetSystemTimerBySec( void );
		virtual Sint32 GetSyncCount( void );
		virtual Uint32 GetMultiMediaTime( void );
		virtual void EnableDrawTitleInformation( Bool IsEnable );
		virtual void EnableDrawMouseCursor( Bool IsEnable );

		virtual Bool PlayMovie( const char *pFileName, Bool IsLoop, Bool (__stdcall *pCallback)( void ) );

		virtual void MsgBox( Sint32 Flag, const char *pTitle, const char *pStr,... );
		virtual Bool SelectBox( const char *pTitle, const char *pStr,... );
		virtual Bool FolderSelect( char *pDirPath, Sint32 DirPathSize );
		virtual Bool FileOpenDialog( char *pPath, const char *pTitle, const char *pFilter, const char *pExt );
		virtual Bool FileSaveDialog( char *pPath, const char *pTitle, const char *pFilter, const char *pExt );
		virtual Bool OpenColorDialog( Sint32 *pR, Sint32 *pG, Sint32 *pB );

		virtual IGraphicCard *CreateGraphicCard( eGraphicCardNo GraphicCardNo );

		virtual Sint32 GetJoystickCount( void );
		virtual Peripheral::IMouse *GetMouse( void );
		virtual Peripheral::IKeyboard *GetKeyboard( void );
		virtual Peripheral::IJoystick *GetJoystick( Sint32 No );
		virtual Peripheral::IInputController *GetInputController( Sint32 No, Sint32 KeyRepeatStartTime, Sint32 KeyRepeatInterval );

		virtual File::IFileManager *CreateFileManager( void );
		virtual File::IFileManager *GetFileMgrPointer( void );
		virtual void SetFileManager( File::IFileManager *pMgr );

		virtual Sound::IStreamSound *CreateStreamSoundFromFile( const char *pFileName, Bool IsGlobalScope, const char *pPluginName );
		virtual Sound::ISound *CreateSoundFromFile( const char *pFileName, Sint32 LayerCount, Bool IsGlobalScope );

		virtual Fiber::IFiberController *CreateFiberController( Sint32 Max );

		virtual const char *GetPluginDirectory( void );
		virtual void SetPluginDirectory( const char *pDirectory );
	};
}

