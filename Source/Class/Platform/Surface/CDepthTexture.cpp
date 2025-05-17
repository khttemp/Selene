

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Math/Math.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/File/CFileManager.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Surface/CDepthTexture.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CDepthTexture::CDepthTexture( CRenderObjectMgr *pMgr ) : CBaseTexture( pMgr )
	, m_DepthBufferType	( DEPTH_BUFFER_SURFACE )
	, m_pTexture		( NULL )
	, m_pSurface		( NULL )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CDepthTexture::~CDepthTexture()
{
	Log_PrintTable( 0xFF0000, 0x000000, "���", "�[�x�e�N�X�`��", m_Name );
	Log_TableLine( 1 );

	m_pRender->ReleaseTexture( this );

	SAFE_RELEASE( m_pSurface );
	SAFE_RELEASE( m_pTexture );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDepthTexture::OnLostDevice( void )
{
	SAFE_RELEASE( m_pSurface );
	SAFE_RELEASE( m_pTexture );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CDepthTexture::OnResetDevice( void )
{
	HRESULT hr;

	//---------------------------------------------------------------------------
	// �[�x�o�b�t�@�̐���
	//---------------------------------------------------------------------------
	switch ( m_DepthBufferType )
	{
	case DEPTH_BUFFER_SURFACE:
		//---------------------------------------------
		// �T�[�t�F�C�X�̐���
		//---------------------------------------------
		hr = m_pRender->CreateDepthStencilSurface( m_Size.x, m_Size.y, m_Format, &m_pSurface );
		if FAILED( hr )
		{
			Log_PrintLine( 0xFF00000, "�T�[�t�F�C�X�̕����Ɏ��s���܂��� [%dx%d] [%s]", m_Size.x, m_Size.y, m_pGraphicCard->GetPixelFormat(m_Format) );
			Log_PrintLine( 0xFF00000, "%s", m_pGraphicCard->GetD3DError(hr) );
		}
		break;

	case DEPTH_BUFFER_TEXTURE_NVIDIA:
	case DEPTH_BUFFER_TEXTURE_ATI:
		//---------------------------------------------
		// �e�N�X�`���̐���
		//---------------------------------------------
		hr = m_pRender->CreateTexture( m_Size.x, m_Size.y, 1, D3DUSAGE_DEPTHSTENCIL, m_Format, m_Pool, &m_pTexture );
		if FAILED( hr )
		{
			Log_PrintLine( 0xFF00000, "�e�N�X�`���̕����Ɏ��s���܂��� [%dx%d] [%s]", m_Size.x, m_Size.y, m_pGraphicCard->GetPixelFormat(m_Format) );
			Log_PrintLine( 0xFF00000, "%s", m_pGraphicCard->GetD3DError(hr) );
		}
		// �T�[�t�F�C�X�擾
		m_pTexture->GetSurfaceLevel( 0, &m_pSurface );
		break;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CDepthTexture::CreateTextureDepthBuffer( Sint32 Width, Sint32 Height )
{
	HRESULT hr;

	//---------------------------------------------------------------------------
	// �ʏ�t�H�[�}�b�g
	//---------------------------------------------------------------------------
	m_DepthBufferType = DEPTH_BUFFER_SURFACE;
	m_Format = m_pGraphicCard->GetFormat( FORMAT_DEPTHBUFFER_SURFACE );

	//---------------------------------------------------------------------------
	// HW�V���h�E�}�b�v�g���邩���ׂ�
	//---------------------------------------------------------------------------
	D3DFORMAT TempFormat = m_pGraphicCard->GetFormat( FORMAT_DEPTHBUFFER_TEXTURE );
	switch ( (Uint32)TempFormat )
	{
	case D3DFMT_UNKNOWN:
		break;
	case D3DFMT_DF24:
		m_DepthBufferType = DEPTH_BUFFER_TEXTURE_ATI;
		m_Format = TempFormat;
		break;
	default:
		m_DepthBufferType = DEPTH_BUFFER_TEXTURE_NVIDIA;
		m_Format = TempFormat;
		break;
	}

	//---------------------------------------------------------------------------
	// �C���[�W���
	//---------------------------------------------------------------------------
	m_ImageInfo.Format		= m_Format;
	m_ImageInfo.Width		= Width;
	m_ImageInfo.Height		= Height;
	m_SurfaceType			= SURFACE_TYPE_DEPTHSTENCIL;
	m_Pool					= D3DPOOL_DEFAULT;
	m_Size					= m_pGraphicCard->GetTextureSize( Math::Point2DI( m_ImageInfo.Width, m_ImageInfo.Height ), FORMAT_DEPTHBUFFER_SURFACE, false );
	m_PixelToTexel.x		= 1.0f / toF(m_ImageInfo.Width);
	m_PixelToTexel.y		= 1.0f / toF(m_ImageInfo.Height);

	//---------------------------------------------------------------------------
	// �[�x�o�b�t�@�̐���
	//---------------------------------------------------------------------------
	switch ( m_DepthBufferType )
	{
	case DEPTH_BUFFER_SURFACE:
		//---------------------------------------------
		// �T�[�t�F�C�X�̐���
		//---------------------------------------------
		hr = m_pRender->CreateDepthStencilSurface( m_Size.x, m_Size.y, m_Format, &m_pSurface );
		if FAILED( hr )
		{
			Log_PrintLine( 0xFF00000, "�T�[�t�F�C�X�̐����Ɏ��s���܂��� [%dx%d] [%s]", m_Size.x, m_Size.y, m_pGraphicCard->GetPixelFormat(m_Format) );
			Log_PrintLine( 0xFF00000, "%s", m_pGraphicCard->GetD3DError(hr) );
			return false;
		}
		break;

	case DEPTH_BUFFER_TEXTURE_NVIDIA:
	case DEPTH_BUFFER_TEXTURE_ATI:
		//---------------------------------------------
		// �e�N�X�`���̐���
		//---------------------------------------------
		hr = m_pRender->CreateTexture( m_Size.x, m_Size.y, 1, D3DUSAGE_DEPTHSTENCIL, m_Format, m_Pool, &m_pTexture );
		if FAILED( hr )
		{
			Log_PrintLine( 0xFF00000, "�e�N�X�`���̐����Ɏ��s���܂��� [%dx%d] [%s]", m_Size.x, m_Size.y, m_pGraphicCard->GetPixelFormat(m_Format) );
			Log_PrintLine( 0xFF00000, "%s", m_pGraphicCard->GetD3DError(hr) );
			return false;
		}
		// �T�[�t�F�C�X�擾
		m_pTexture->GetSurfaceLevel( 0, &m_pSurface );
		break;
	}

	//---------------------------------------------------------------------------
	// ���O
	//---------------------------------------------------------------------------
	Log_PrintLine( 0x0000000, "�T�C�Y [%dx%d] �t�H�[�}�b�g [%s]", m_Size.x, m_Size.y, m_pGraphicCard->GetPixelFormat(m_Format) );
	Log_PrintLine( 0x0000000, "�cVRAM�e�� %.3lfMB", m_pRender->GetRestVRAM() );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CDepthTexture::BackupTargetBuffer( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CDepthTexture::GetTexture( IDirect3DBaseTexture9 *&pTexture, eCubemapFaceType FaceType )
{
	if ( m_pTexture != NULL )
	{
		pTexture = m_pTexture;
		m_pTexture->AddRef();
	}
	else
	{
		pTexture = NULL;
	}

	return pTexture != NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CDepthTexture::GetSurface( IDirect3DSurface9 *&pSurface, eCubemapFaceType FaceType )
{
	if ( m_pSurface != NULL )
	{
		pSurface = m_pSurface;
		m_pSurface->AddRef();
	}
	else
	{
		pSurface = NULL;
	}

	return pSurface != NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DF CDepthTexture::GetPixelToTexelTransform( void )
{
	return m_PixelToTexel;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CDepthTexture::SaveToTGA( const char *pFileName )
{
	if ( m_pTexture != NULL )
	{
/*		// �����_�����O�^�[�Q�b�g�̏ꍇ�̓V�X�e���ɃR�s�|
		DownloadToSystem();

		// �ۑ�
		HRESULT hr;
		hr = ::D3DXSaveTextureToFile(
					pFileName,
					D3DXIFF_TGA,
					m_pBaseTexture != NULL ? m_pBaseTexture : m_pTexture,
					NULL );
		return SUCCEEDED( hr );
*/	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CDepthTexture::SaveToPNG( const char *pFileName )
{
	if ( m_pTexture != NULL )
	{
/*		// �����_�����O�^�[�Q�b�g�̏ꍇ�̓V�X�e���ɃR�s�|
		DownloadToSystem();

		// �ۑ�
		HRESULT hr;
		hr = ::D3DXSaveTextureToFile(
					pFileName,
					D3DXIFF_PNG,
					m_pBaseTexture != NULL ? m_pBaseTexture : m_pTexture,
					NULL );
		return SUCCEEDED( hr );
*/	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CDepthTexture::IsStencilFormat( void )
{
	switch ( m_Format )
	{
	case D3DFMT_D24S8:
	case D3DFMT_D24FS8:
	case D3DFMT_D24X4S4:
	case D3DFMT_D15S1:
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DI CDepthTexture::GetSize( void )
{
	return m_Size;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DI CDepthTexture::GetOriginalSize( void )
{
	return Math::Point2DI( m_ImageInfo.Width, m_ImageInfo.Height );
}

