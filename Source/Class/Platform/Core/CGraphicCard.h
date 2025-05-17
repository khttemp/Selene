#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Math.h"
#include "Class/ClassReference.h"
#include "Class/Common/Object/CBaseObject.h"
#include "Interface/Core/IGraphicCard.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	struct DEVICEINFORMATION
	{
		Bool IsPureDevice;
		Bool IsCubeTexture;
		Bool IsVolumeTexture;
		Bool IsDynamicTexture;
		Bool IsMagAnisotropy;
		Bool IsMinAnisotropy;
		Bool IsSupportNonePow2ConditionalTexture;
		Bool IsSupportNonePow2Texture;
		Bool IsSupportNoneSquareTexture;

		Sint32 MaxAnisotropy;
		Sint32 MaxTextureWidth;
		Sint32 MaxTextureHeight;

		Sint32 MaxPrimitiveCount;
		Sint32 MaxVertexIndex;

		Uint32 VertexShaderVersion;
		Uint32 PixelShaderVersion;

		Sint32 VertexShaderInstructions;
		Sint32 PixelShaderInstructions;

		Sint32 VertexShaderConstMax;

		Sint32 DynamicFlowControlDepth;
		Sint32 StaticFlowControlDepth;

		Sint32 MultiRenderTargetCount;
	};

	class CGraphicCard : public CBaseObject, public IGraphicCard
	{
	protected:
		IDirect3D9 *m_pDirect3D;

		eGraphicCardNo m_GraphicCardNo;
		char m_GraphicCardName[128];

		Uint32 m_MaxUseVertexShaderVersion;
		DEVICEINFORMATION m_DeviceInfo;

		D3DDISPLAYMODE m_WindowModeInfo;
		D3DFORMAT m_FullScreen16BitInfo;
		D3DFORMAT m_FullScreen32BitInfo;

		Bool m_IsHighColor;
		Bool m_IsHVPerfHUD;

		Sint32 m_ScreenTypeCount;
		D3DDISPLAYMODE m_ScreenType[512];

		Sint32 m_TextureFormatCount;
		D3DFORMAT m_TextureFormats[64];

		Sint32 m_DepthSurfaceFormatCount;
		D3DFORMAT m_DepthSurfaceFormats[32];

		Sint32 m_DepthTextureFormatCount;
		D3DFORMAT m_DepthTextureFormats[32];

		Sint32 m_TargetFormatCount;
		D3DFORMAT m_TargetFormats[32];

		Sint32 m_TargetAlphaFormatCount;
		D3DFORMAT m_TargetAlphaFormats[32];

		D3DFORMAT m_SurfaceFormatTbl[FORMAT_MAX];

		CCore *m_pCore;
		Renderer::CRender *m_pRender;

	protected:
		virtual Bool CreateDirect3DObject( void );
		virtual Bool CheckGraphicCardInfo( void );
		virtual Bool CheckGraphicCardCaps( void );
		virtual void GetDeviceCaps( D3DCAPS9 *pCaps, DEVICEINFORMATION *pDevInfo );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CGraphicCard( CCore *pCore );
		virtual ~CGraphicCard();

		virtual Bool Initialize( eGraphicCardNo GraphicCardNo );

		virtual void GetAnisotropyFilterSupport( Bool &IsMin, Bool &IsMag, Sint32 &Max );
		virtual void CreateSurfaceFormatTable( void );
		virtual HRESULT CreateDeviceObject( D3DDEVTYPE DeviceType, Sint32 CreateFlag, D3DPRESENT_PARAMETERS &Param, IDirect3DDevice9 *&pDevice );
		virtual Sint32 GetDeviceTypeNo( void );
		virtual Bool IsHightColorMode( void );
		virtual Bool IsNVPerfHUDEnable( void );
		virtual D3DPRESENT_PARAMETERS MakePresentParameters( Bool IsWindow, Bool IsHightColor, Bool IsLockEnableBackBuffer, Bool IsWaitVSync );
		virtual D3DFORMAT GetFormat( eSurfaceFormat Format );
		virtual Bool CheckAlphaBlending( D3DFORMAT Format );
		virtual char *GetPixelFormat( D3DFORMAT Format, char *pErrStr = NULL, Sint32 ErrStrSize = 0 );
		virtual char *GetD3DError( HRESULT hr, char *pErrStr = NULL, Sint32 ErrStrSize = 0 );

		virtual void EnableHighlColorScreen( void );
		virtual HMONITOR GetMonitorHandle( void );

		virtual Bool GetPixelShaderSupport( Uint16 Major, Uint16 Minor );
		virtual Bool GetNonePow2ConditionalTextureSupport( void );
		virtual Bool GetNonePow2TextureSupport( void );
		virtual Bool GetNoneSquareTextureSupport( void );

		virtual Sint32 GetScreenModeCount( Bool IsFullColor );
		virtual void GetScreenMode( Bool IsFullColor, Sint32 No, Sint32 &Width, Sint32 &Height );

		virtual Sint32 CreateRenderTargetTextureSizeCount( void );
		virtual void CreateRenderTargetTextureSize( Sint32 No, Sint32 *pWidth, Sint32 *pHeight );

		virtual void GetGraphicCardName( char *pName, Sint32 NameSize );

		virtual void GetVertexShaderVersion( char *pName, Sint32 NameSize );
		virtual void GetPixelShaderVersion( char *pName, Sint32 NameSize );

		virtual Math::Point2DI GetTextureMaxSize( void );
		virtual Math::Point2DI GetTextureSize( Math::Point2DI Size, eSurfaceFormat Format, Bool IsMipmap );

		virtual CCore *GetCorePointer( void );

		virtual Renderer::IRender *CreateRender( Bool IsLockEnableBackBuffer, Bool IsWaitVSync );
	};
}
