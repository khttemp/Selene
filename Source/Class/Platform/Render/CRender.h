#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Color.h"
#include "Math/Vector2D.h"
#include "Math/Vector3D.h"
#include "Math/Vector4D.h"
#include "Class/Common/Object/CRenderObject.h"
#include "Class/Common/Scene/CSceneCamera.h"
#include "Class/Platform/Render/Shader/CShader.h"
#include "Thread/CriticalSection.h"
#include "Interface/Render/IRender.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	enum eHardwareShadowType
	{
		HW_SHADOW_NONE,
		HW_SHADOW_NVIDIA,
		HW_SHADOW_ATI,
	};

	enum eDeviceCreateType
	{
		DEVICE_CREATE_PUREDEVICE,
		DEVICE_CREATE_HARDWARE_TNL,
		DEVICE_CREATE_SOFTWARE_TNL,
		DEVICE_CREATE_MAX,
	};

	enum ePrimitiveType
	{
		PRIMITIVE_POINT,
		PRIMITIVE_LINE,
		PRIMITIVE_LINE_STRIP,
		PRIMITIVE_TRIANGLE,
		PRIMITIVE_TRIANGLE_STRIP,
		PRIMITIVE_TRIANGLE_FAN,
	};

namespace Renderer
{
	enum eVertexElementLocal
	{
		VERTEX_ELEMENT_POSTEFFECT	= 1 << 31,			///< ポストエフェクト用
	};

	struct SVertexPostEffect
	{
		Math::Vector4D Pos;
		Math::Vector4D Tex[8];
	};

	struct SRenderState
	{
		ITexture *pTextureTbl[TEXTURE_STAGE_MAX];
		eTextureFilterType FilterType[TEXTURE_STAGE_MAX];
		eDrawType DrawType;
		eCullType CullType;
		Sint32 AlphaBoundary;
		Bool IsDepthTestEnable;
		Bool IsDepthWriteEnable;
		Bool IsAlphaTestEnable;
	};

	class CRender : public CBaseObject, public IRender
	{
		enum { STATE_STACK_MAX = 16 };

	public:
		IDirect3DDevice9					*m_pD3DDevice;
		IDirect3DSurface9					*m_pBackBuffer;
		ID3DXEffectPool						*m_pEffectPool;
		ID3DXFont							*m_pFont;

		D3DPRESENT_PARAMETERS				m_AcitivePresentParam;

		D3DCAPS9							m_Caps;
		D3DVIEWPORT9						m_Viewport;
		Sint32								m_MaxUseVertexShaderVersion;

		D3DDISPLAYMODE						m_WindowType;
		D3DDISPLAYMODE						m_FullScreenType[2];
		Bool								m_IsLockEnableBackBuffer;
		Bool								m_IsWaitVSync;
		Bool								m_IsDynamicBufferEnable;

		CCore								*m_pCore;
		CGraphicCard						*m_pGraphicCard;

		CRenderObjectMgr					*m_pSceneMgr;
		CRenderObjectMgr					*m_pVertexStreamMgr;
		CRenderObjectMgr					*m_pVertexBufferMgr;
		CRenderObjectMgr					*m_pIndexBufferMgr;
		CRenderObjectMgr					*m_pShaderMgr;
		Object::CPrimitive2DBaseMgr			*m_pListPrimitive2DMgr;
		Object::CPrimitive3DBaseMgr			*m_pListPrimitive3DMgr;
		Object::CModelMgr					*m_pListModelMgr;
		Object::CMapModelMgr				*m_pListMapModelMgr;
		CDepthTextureMgr					*m_pSurfaceMgr;
		CTextureMgr							*m_pTextureMgr;
		Scene::CSceneManagerBase			*m_pActiveScene;
		CTextureConfig						m_TextureConfig;
		SRenderState						m_RenderState[STATE_STACK_MAX];
		Sint32								m_RenderStatePos;
		CVertexBuffer						*m_pVertexBuffer2D;
		CVertexLayout						*m_pVertexStream2D;
		Shader::IShader						*m_pShader2D;

		CTextureInterface					*m_pTextureDefault[TEXTURE_STAGE_MAX];
		CTextureInterface					*m_pDepthBuffer;

		Thread::CCriticalSection			m_CS;

		Float								m_fUsedVRAM;
		Float								m_fRestVRAM;

		void (*m_pCallbackReset)( void );
		void (*m_pCallbackRestore)( void );

	public:
		virtual Bool IsInvalid( void ) { return m_pD3DDevice == NULL; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	protected:
		virtual void ResetRenderState( void );
		virtual void ResetSamplerState( void );
		virtual void ResetTextureStageState( void );
		virtual Float ToPixelX( Float fIn );
		virtual Float ToPixelY( Float fIn );
		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );
		virtual Bool CreateDeviceByNVPerfHUD( D3DPRESENT_PARAMETERS &PresentParam );
		virtual void UpdateUsedVRAM( void );

	public:
		CRender( CGraphicCard *pGraphicCard, Bool IsWindow, Bool IsLockEnableBackBuffer, Bool IsWaitVSync );
		virtual ~CRender();

		virtual void ResetDevice( Bool IsChange );
		virtual Bool ResetRenderTarget( void );
		virtual COcclusion *CeateOcclusion( void );

		virtual void AbortAllScene( void );

		virtual Sint32 GetSize( Sint32 Flag );

		virtual void ReleaseTexture( ITexture *pTex );
		virtual SRenderState &GetRenderState( void );

		virtual Scene::CSceneManagerBase *GetManagerPointer( void );
		virtual Bool ActivateScene( Scene::CSceneManagerBase *pScene );
		virtual Bool DeActivateScene( Scene::CSceneManagerBase *pScene );

		virtual CVertexLayout *CreateVertexStreamDirect( void );
		virtual CVertexLayout *CreateVertexStream( Sint32 Flag );
		virtual CVertexBuffer *CreateVertexBuffer( Sint32 Count, Sint32 VertexSize, Bool IsDynamic );
		virtual CIndexBuffer *CreateIndexBuffer( Sint32 Count, Bool IsDynamic );

		virtual Bool DrawPrimitive( ePrimitiveType PrimitiveType, Sint32 PrimitiveCount );
		virtual Bool DrawIndexedPrimitive( ePrimitiveType PrimitiveType, Sint32 VertexCount, Sint32 PrimitiveCount );
		virtual Bool DrawMesh( Sint32 VertexStart, Sint32 VertexCount, Sint32 IndexStart, Sint32 PrimitiveCount );

		virtual Bool IsSupportedPS20( void );
		virtual Bool IsSupportedPS30( void );
		virtual Bool IsPixelShaderInstructionSupport( Sint32 Count );
		virtual Sint32 GetPixelShaderSlot( void );
		virtual Sint32 GetMRTs( void );

		virtual Sint32 GetActiveRefreshRate( void );
		virtual HWND GetCreationWindow( void );

		virtual Shader::IShader *CreateShaderFromMemory( const void *pShader, Sint32 Size, Bool IsCompiled );
		virtual Shader::IShader *CreateShaderFromFile( const char *pFile, Bool IsCompiled );

		virtual Bool SetDepthBuffer( ITexture *pTexture );

		virtual void SetHardwareShadowATI( Bool IsEnable, Bool IsGet4 );

		virtual void ResetShader( void );
		virtual void Start2D( Bool IsMultiTexture );
		virtual void Start3D( void );

		virtual void SetIndexBuffer( CIndexBuffer *pBuffer );
		virtual void SetVertexBuffer( CVertexBuffer *pBufferTbl[], Sint32 Count );
		virtual void SetVertexStream( CVertexLayout *pStream );

		virtual Math::Point2DI GetBackBufferSize( void );

	public:
		virtual CGraphicCard *GetGraphicCardPointer( void );

		virtual Math::Rect2DI GetViewport( void );
		virtual void SetViewport( const Math::Rect2DI &Dst );

		virtual Bool SetRenderTarget( ITexture *pTexture );
		virtual Bool SetRenderTarget( ITexture *pTexture0, ITexture *pTexture1, ITexture *pTexture2, ITexture *pTexture3 );

		virtual void Begin( void );
		virtual void End( void );

		virtual void SetScissorPrimitive2D( const Math::Rect2DF *pRect );

		virtual void ChangeDebugPrintFont( const char *pFontFace, Sint32 Size );
		virtual void DebugPrint( Math::Point2DI &Pos, CColor Color, const char *pStr, ... );

		virtual void SetDrawTextFont( const char *pFontFace, Sint32 Size );
		virtual void DrawText( Math::Point2DI &Pos, CColor Color, const char *pStr, ... );

		virtual Scene::ICustomizedSceneManager *CreateCustomizedSceneManager( Sint32 QueMax );
		virtual Scene::ISceneManager *CreateSceneManager( Sint32 QueMax, Bool IsPixelShaderEnable );
		
		virtual Object::IPoint2D *CreatePoint2D( Sint32 PointMax, Bool IsAutoResize, Sint32 ResizeStep );
		virtual Object::ILine2D *CreateLine2D( Sint32 LineMax, Bool IsAutoResize, Sint32 ResizeStep );
		virtual Object::IPrimitive2D *CreatePrimitive2D( Sint32 PrimitiveMax, Bool IsAutoResize, Sint32 ResizeStep );
		virtual Object::ISprite2D *CreateSprite2D( Sint32 PrimitiveMax, ITexture *pTexture, Bool IsFiltering, Bool IsOffset, Bool IsAutoResize, Sint32 ResizeStep );
		virtual Object::IFontSprite2D *CreateFontSprite2DFromFile( const char *pFileName, const char *pExt, Sint32 FontMax, Bool IsAutoResize, Sint32 ResizeStep );

		virtual Object::IPoint3D *CreatePoint3D( Sint32 VertexMax, Bool IsDynamic );
		virtual Object::ILine3D *CreateLine3D( Sint32 VertexMax, Bool IsDynamic );
		virtual Object::IPrimitive3D *CreatePrimitive3D( Sint32 VertexMax, Sint32 IndexMax, Sint32 VertexFlag, Bool IsDynamicVertex, Bool IsDynamicIndex );
		virtual Object::ISprite3D *CreateSprite3D( Sint32 SpriteMax, Renderer::ITexture *pTexture );
		virtual Object::IFontSprite3D *CreateFontSprite3DFromFile( const char *pFileName, const char *pExt, Sint32 FontMax );
		virtual Object::IParticle *CreateParticle( Sint32 ParticleMax, ITexture *pTexture, eParticleType Type, Bool IsSoftBillboard );

		virtual Object::IMapModel *CreateMapModelFromFile( const char *pFileName );
		virtual Object::IMapModel *CreateMapModelFromMemory( const Uint8 *pData, Sint32 Size );

		virtual Object::IModel *CreateModelFromFile( const char *pFileName );
		virtual Object::IModel *CreateModelFromMemory( const Uint8 *pData, Sint32 Size );
		virtual Object::IModel *CreateModelSkydoom( Float fRadius, CColor TopColor, CColor BottomColor, ITexture *pTexCloud );

		virtual CTextureConfig &GetTextureConfig( void );
		virtual void SetTextureConfig( CTextureConfig &Conf );

		virtual ITexture *CreateTextureDepthBuffer( Sint32 Width, Sint32 Height );
		virtual ITexture *CreateTextureRenderTarget( Sint32 Width, Sint32 Height, eSurfaceFormat Format );

		virtual ITexture *CreateTextureFromFile( const char *pFileName );
		virtual ITexture *CreateTextureFromMemory( const void *pData, Sint32 Size );

		virtual ITexture *CreateCubeTextureFromFile( const char *pFileName );
		virtual ITexture *CreateCubeTextureFromMemory( const void *pData, Sint32 Size );
		virtual ITexture *CreateCubeTextureRenderTarget( Sint32 Size );

		virtual eDrawType GetDrawType( void );
		virtual eCullType GetCullType( void );
		virtual CTexture *GetTexture( eTextureStage Stage );
		virtual eTextureFilterType GetTextureFilterType( eTextureStage Stage );
		virtual Bool GetDepthTestEnable( void );
		virtual Bool GetDepthWriteEnable( void );
		virtual Bool GetAlphaTestEnable( void );
		virtual Sint32 GetAlphaBoundary( void );

		virtual void SetDrawType( eDrawType Type );
		virtual void SetCullType( eCullType Type );
		virtual Bool SetTexture( eTextureStage Stage, ITexture *pTex );
		virtual void SetTextureFilterType( eTextureStage Stage, eTextureFilterType Type );
		virtual void SetDepthTestEnable( Bool Flag );
		virtual void SetDepthWriteEnable( Bool Flag );
		virtual void SetAlphaTestEnable( Bool Flag );
		virtual void SetAlphaBoundary( Sint32 Bound );
		virtual Bool StatePush( void );
		virtual Bool StatePop( void );
		virtual void StateInit( void );

		virtual void FillRect( const Math::Rect2DF &Dst, CColor Color );
		virtual void DrawTextureByShader( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) );
		virtual void DrawTexture( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) );
		virtual void DrawTextureTile( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) );
		virtual void DrawUniversal( const Math::Rect2DF &Dst, Float fRate, const Math::Rect2DF &SrcBase, ITexture *pTexBase, const Math::Rect2DF &SrcRule, ITexture *pTexRule, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) );
		virtual void DrawBlur( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) );
		virtual void DrawGrayscale( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) );
		virtual void DrawFishEye( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Float fRate );

		virtual void Refresh( HWND hWnd = NULL );

		virtual Bool Clear( CColor Color );
		virtual Bool ClearDepthStencil( void );
		virtual void SetScissorRect( const Math::Rect2DI *pRect );

		virtual void SetCallbackDeviceReset( void (*pCallback)( void ) );
		virtual void SetCallbackDeviceRestore( void (*pCallback)( void ) );

		virtual Float GetRestVRAM( void );
		virtual void SetColorWriteEnable( Bool IsAlpha, Bool IsRed, Bool IsGreen, Bool IsBlue );
		virtual void *GetDriverDevicePointer( void );
		virtual void SaveToFilePNG( const char *pFileName );
		virtual void SaveToFileJPG( const char *pFileName );
		virtual void SetGUIEnable( Bool IsEnable );

		virtual HRESULT StretchRectToBackBuffer( IDirect3DSurface9 *pSourceSurface );
		virtual HRESULT CreateOcclusionQuery( IDirect3DQuery9 *&pQuery );
		virtual HRESULT CreateTexture( Sint32 Width, Sint32 Height, Sint32 Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture );
		virtual HRESULT CreateCubeTextureFromInMemory( const void *pData, Sint32 DataSize, Sint32 Size, Sint32 Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppTexture );
		virtual HRESULT CreateCubeTexture( Sint32 Size, Sint32 Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppTexture );
		virtual HRESULT CreateRenderTarget( Sint32 Width, Sint32 Height, D3DFORMAT Format, IDirect3DSurface9** ppSurface );
		virtual HRESULT StretchRect( IDirect3DSurface9 *pSourceSurface, CONST RECT *pSourceRect, IDirect3DSurface9 *pDestSurface, CONST RECT *pDestRect, D3DTEXTUREFILTERTYPE Filter );
		virtual HRESULT GetRenderTargetData( IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface );
		virtual HRESULT CreateDepthStencilSurface( Sint32 Width, Sint32 Height, D3DFORMAT Format, IDirect3DSurface9** ppSurface );
		virtual HRESULT SetDepthStencilSurface( IDirect3DSurface9 *pZStencil );
		virtual HRESULT CreateVertexBuffer( Sint32 Length, IDirect3DVertexBuffer9** ppVertexBuffer, Bool IsDynamic );
		virtual HRESULT CreateIndexBuffer( Sint32 Length, IDirect3DIndexBuffer9** ppIndexBuffer, Bool IsDynamic, Bool Is32Bit );
		virtual HRESULT CreateVertexDeclaration( const D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl );
		virtual HRESULT CreateEffect( LPCVOID pSrcData, UINT SrcDataLen, LPD3DXEFFECT *ppEffect, LPD3DXBUFFER *ppCompilationErrors, Bool IsCompiled );
		virtual HRESULT UpdateSurface( IDirect3DSurface9* pSourceSurface, IDirect3DSurface9* pDestinationSurface );
	};
}
}
