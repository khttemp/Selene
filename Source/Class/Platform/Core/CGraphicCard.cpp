

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Platform/Core/CGraphicCard.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Common/Core/CCore.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// CONSTANT
//-----------------------------------------------------------------------------------

//---------------------------------------------------------------
// �o�b�N�o�b�t�@�t�H�[�}�b�g
//---------------------------------------------------------------
static const D3DFORMAT g_BackBufferFormats[] = {
	D3DFMT_X8R8G8B8,
	D3DFMT_X1R5G5B5,
	D3DFMT_R5G6B5,

	D3DFMT_UNKNOWN,
};


//---------------------------------------------------------------
// �e�N�X�`���t�H�[�}�b�g
//---------------------------------------------------------------
static D3DFORMAT g_TextureFormats[] = {
	D3DFMT_A8R8G8B8,
	D3DFMT_A4R4G4B4,
	D3DFMT_A1R5G5B5,
	D3DFMT_DXT5,
	D3DFMT_DXT3,
	D3DFMT_DXT1,
	D3DFMT_R32F,
	D3DFMT_R16F,
    D3DFMT_G32R32F,
    D3DFMT_G16R16F,
	D3DFMT_A32B32G32R32F,
	D3DFMT_A16B16G16R16F,
	D3DFMT_Q16W16V16U16,
	D3DFMT_Q8W8V8U8,

	D3DFMT_UNKNOWN,
};

//---------------------------------------------------------------
// �[�x�o�b�t�@�t�H�[�}�b�g
//---------------------------------------------------------------
static D3DFORMAT g_DepthFormats[] = {
	D3DFMT_DF24,
	D3DFMT_D32F_LOCKABLE,
	D3DFMT_D32,
	D3DFMT_D24FS8,
	D3DFMT_D24S8,
	D3DFMT_D24X4S4,
	D3DFMT_D24X8,
	D3DFMT_D16_LOCKABLE,
	D3DFMT_D16,
	D3DFMT_D15S1,

	D3DFMT_UNKNOWN,
};

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CGraphicCard::CGraphicCard( CCore *pCore )
	: m_pCore						( pCore )
	, m_pDirect3D					( NULL )
	, m_pRender						( NULL )
	, m_IsHighColor					( false )
	, m_IsHVPerfHUD					( false )
	, m_GraphicCardNo				( GRAPHIC_CARD_DEFAULT_NO )
	, m_MaxUseVertexShaderVersion	( 0 )
	, m_ScreenTypeCount				( 0 )
	, m_DepthSurfaceFormatCount		( 0 )
	, m_DepthTextureFormatCount		( 0 )
	, m_TextureFormatCount			( 0 )
	, m_TargetFormatCount			( 0 )
	, m_TargetAlphaFormatCount		( 0 )
	, m_FullScreen16BitInfo			( D3DFMT_UNKNOWN )
	, m_FullScreen32BitInfo			( D3DFMT_UNKNOWN )
{
	MemoryClear( m_GraphicCardName, sizeof(m_GraphicCardName) );

	MemoryClear( &m_DeviceInfo, sizeof(m_DeviceInfo) );
	MemoryClear( &m_WindowModeInfo, sizeof(m_WindowModeInfo) );

	MemoryClear( m_ScreenType, sizeof(m_ScreenType) );
	MemoryClear( m_DepthSurfaceFormats, sizeof(m_DepthSurfaceFormats) );
	MemoryClear( m_DepthTextureFormats, sizeof(m_DepthTextureFormats) );
	MemoryClear( m_TextureFormats, sizeof(m_TextureFormats) );
	MemoryClear( m_TargetFormats, sizeof(m_TargetFormats) );
	MemoryClear( m_TargetAlphaFormats, sizeof(m_TargetAlphaFormats) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CGraphicCard::~CGraphicCard()
{
	// �O���t�B�b�N�J�[�h���
	if ( m_pDirect3D != NULL )
	{
		Sint32 Num = m_pDirect3D->Release();
		m_pDirect3D = NULL;

		Log_TableBegin();
		Log_PrintCellTitle( 0x008000, "���" );
		Log_PrintCellKind( "IDirect3D9Object" );
		Log_CellBegin( 0 );
		Log_Print( 0x000000, "�Q�Ɛ� %d", Num );
		Log_CellEnd();
		Log_TableEnd();
		Log_TableLine( 2 );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::Initialize( eGraphicCardNo GraphicCardNo )
{
	//---------------------------------------------------------------
	// �r�f�I�J�[�h�ԍ�
	//---------------------------------------------------------------
	m_GraphicCardNo = GraphicCardNo;

	//---------------------------------------------------------------
	// �V�F�[�_�[�o�[�W����
	//---------------------------------------------------------------
	m_MaxUseVertexShaderVersion = D3DVS_VERSION(2,0);

	//---------------------------------------------------------------
	// Direct3D�I�u�W�F�N�g�̐���
	//---------------------------------------------------------------
	if ( !CreateDirect3DObject() )
	{
		return false;
	}

	//---------------------------------------------------------------
	// "NVPerfHUD"�`�F�b�N
	//---------------------------------------------------------------
	if ( m_GraphicCardNo == GRAPHIC_CARD_NV_PERF_HUD )
	{
		const char *pDriverName[] = {
			"NVIDIA NVPerfHUD",
			"NVIDIA PerfHUD",
			NULL,
		};

		m_GraphicCardNo = GRAPHIC_CARD_DEFAULT_NO;
		Sint32 MaxGraphicCard = (Sint32)m_pDirect3D->GetAdapterCount();
		for ( Sint32 i= 0; i< MaxGraphicCard; i++ )
		{
			D3DADAPTER_IDENTIFIER9 Identifier;
			m_pDirect3D->GetAdapterIdentifier( i, 0, &Identifier );

			for ( Sint32 j = 0; pDriverName[j] != NULL; j++ )
			{
				Sint32 Compare = ::CompareString( LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, Identifier.Description, -1, pDriverName[j], -1 );
				if ( Compare == CSTR_EQUAL )
				{
					m_IsHVPerfHUD = true;
					m_GraphicCardNo = (eGraphicCardNo)i;
					goto EXIT;
				}
			}
		}
	}

EXIT:
	//---------------------------------------------------------------
	// �r�f�I�J�[�h���̃`�F�b�N
	//---------------------------------------------------------------
	if ( !CheckGraphicCardInfo() )
	{
		return false;
	}

	//---------------------------------------------------------------
	// �f�o�C�X���̃`�F�b�N
	//---------------------------------------------------------------
	if ( !CheckGraphicCardCaps() )
	{
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::CreateDirect3DObject( void )
{
	CCore *pCore = (CCore*)GetParent();

	//---------------------------------------------------------------
	// Create Direct3D Object
	//---------------------------------------------------------------
	m_pDirect3D = Direct3DCreate9( D3D_SDK_VERSION );
	if ( m_pDirect3D == NULL )
	{
		pCore->MsgBox( MB_ICONERROR, "Error", "Direct3D�I�u�W�F�N�g�̐����Ɏ��s\nDirectX9.0c���������C���X�g�[������Ă��邩\n�m�F���ĉ�����" );
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::CheckGraphicCardInfo( void )
{
	D3DADAPTER_IDENTIFIER9 Identifier;
	HRESULT hr;

	//---------------------------------------------------------------
	// �r�f�I�J�[�h���
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "����" );
	Log_PrintCellKind( "�r�f�I�J�[�h���" );
	Log_CellBegin( 0 );

	hr = m_pDirect3D->GetAdapterIdentifier( m_GraphicCardNo, 0, &Identifier );
	if SUCCEEDED( hr )
	{
		StringCbCopy( m_GraphicCardName, sizeof(m_GraphicCardName), Identifier.Description );

		Log_PrintTable( 128, "Name", "%s", m_GraphicCardName );
		Log_PrintTable( 128, "Driver", "%s", Identifier.Driver );
		Log_PrintTable( 128, "Version", "%u.%u.%u", LOWORD(Identifier.DriverVersion.HighPart), HIWORD(Identifier.DriverVersion.LowPart), LOWORD(Identifier.DriverVersion.LowPart) );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// ���݂̉�ʃ��[�h�擾
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "����" );
	Log_PrintCellKind( "���݂̉�ʏ��" );
	Log_CellBegin( 0 );

	hr = m_pDirect3D->GetAdapterDisplayMode( m_GraphicCardNo, &m_WindowModeInfo );
	if SUCCEEDED( hr )
	{
		Log_PrintTable( 128, "Width", "%u", m_WindowModeInfo.Width );
		Log_PrintTable( 128, "Height", "%u", m_WindowModeInfo.Height );
		Log_PrintTable( 128, "RefreshRate", "%uHz", m_WindowModeInfo.RefreshRate );
		Log_PrintTable( 128, "Format", "%s", GetPixelFormat(m_WindowModeInfo.Format) );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// �t���X�N���[�����Ɏg�p�\�ȉ�ʃ��[�h��񋓂���
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "����" );
	Log_PrintCellKind( "�g�p�\�ȉ�ʃ��[�h" );
	Log_CellBegin( 0 );

	for ( Sint32 i = 0; g_BackBufferFormats[i] != D3DFMT_UNKNOWN; i++ )
	{
		// �f�B�X�v���C���[�h���̎擾
		D3DDISPLAYMODE DisplayType;
		Sint32 TypeCount = (Sint32)m_pDirect3D->GetAdapterModeCount( m_GraphicCardNo, g_BackBufferFormats[i] );

		if ( TypeCount > 0 )
		{
			Log_PrintStrongLine( 0x000000, "BackBuffer Format %s", GetPixelFormat(g_BackBufferFormats[i]) );

			// ���[�h���
			for ( Sint32 j = 0; j < TypeCount; j++ )
			{
				hr = m_pDirect3D->EnumAdapterModes( m_GraphicCardNo, g_BackBufferFormats[i], j, &DisplayType );
				if SUCCEEDED( hr )
				{
					Sint32 No = -1;

					// ����T�C�Y����
					for ( Sint32 k = 0; k < m_ScreenTypeCount; k++ )
					{
						if ( m_ScreenType[k].Format == g_BackBufferFormats[i] )
						{
							if ( m_ScreenType[k].Width == DisplayType.Width )
							{
								if ( m_ScreenType[k].Height == DisplayType.Height )
								{
									// ���ɂ������肵��
									No = k;
									// �E�B���h�E���[�h�̃��t���b�V�����[�g�𒴂��Ȃ�
									// �ő�̃��t���b�V�����[�g���g���i�O�̂��߁j
									if ( m_ScreenType[No].RefreshRate < DisplayType.RefreshRate )
									{
										if ( DisplayType.RefreshRate <= m_WindowModeInfo.RefreshRate )
										{
											m_ScreenType[No] = DisplayType;
										}
									}
								}
							}
						}
					}

					// �����ʃT�C�Y��������Ȃ������ꍇ�͒ǉ�
					if ( No == -1 )
					{
						m_ScreenType[m_ScreenTypeCount++] = DisplayType;
					}
				}
			}

			// ���O
			for ( Sint32 j = 0; j < m_ScreenTypeCount; j++ )
			{
				if ( m_ScreenType[j].Format == g_BackBufferFormats[i] )
				{
					Log_PrintLine( 0x000000, "%4u x %4u : %uHz", m_ScreenType[j].Width, m_ScreenType[j].Height, m_ScreenType[j].RefreshRate );
				}
			}
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// �t���X�N���[�����[�h�p�̃f�B�X�v���C���[�h�ݒ�
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "����" );
	Log_PrintCellKind( "�t���X�N���[���p<BR>�f�B�X�v���C���[�h" );
	Log_CellBegin( 0 );

	Sint32 Width, Height;
	m_pCore->GetScreenData( &Width, &Height, NULL );

	// ����
	for ( Sint32 j = 0; j < m_ScreenTypeCount; j++ )
	{
		switch ( m_ScreenType[j].Format )
		{
		// 16Bit
		case D3DFMT_X1R5G5B5:
		case D3DFMT_R5G6B5:
			m_FullScreen16BitInfo = m_ScreenType[j].Format;
			break;
		// 32Bit
		case D3DFMT_X8R8G8B8:
			m_FullScreen32BitInfo = m_ScreenType[j].Format;
			break;
		}
	}

	// ���O
	Log_PrintLine( 0x000000, "16BitColor %s", GetPixelFormat(m_FullScreen16BitInfo) );
	Log_PrintLine( 0x000000, "32BitColor %s", GetPixelFormat(m_FullScreen32BitInfo) );

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// �e�N�X�`���t�H�[�}�b�g����g�p�\�Ȃ��̂�����
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "����" );
	Log_PrintCellKind( "�g�p�\��<BR>�e�N�X�`���t�H�[�}�b�g" );
	Log_CellBegin( 0 );

	D3DFORMAT BaseFormat = m_FullScreen32BitInfo == D3DFMT_UNKNOWN ? m_WindowModeInfo.Format : m_FullScreen32BitInfo;

	for ( Sint32 i = 0; g_TextureFormats[i] != D3DFMT_UNKNOWN; i++ )
	{
		hr = m_pDirect3D->CheckDeviceFormat(
							m_GraphicCardNo,
							D3DDEVTYPE_HAL,
							BaseFormat,
							0,
							D3DRTYPE_TEXTURE,
							g_TextureFormats[i] );
		if SUCCEEDED( hr )
		{
			Log_PrintLine( 0x000000, "%s", GetPixelFormat(g_TextureFormats[i]) );
			m_TextureFormats[m_TextureFormatCount++] = g_TextureFormats[i];
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// �����_�����O�^�[�Q�b�g�e�N�X�`���t�H�[�}�b�g����g�p�\�Ȃ��̂�����
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "����" );
	Log_PrintCellKind( "�g�p�\��<BR>�����_�����O�^�[�Q�b�g<BR>�t�H�[�}�b�g" );
	Log_CellBegin( 0 );

	for ( Sint32 i = 0; g_TextureFormats[i] != D3DFMT_UNKNOWN; i++ )
	{
		hr = m_pDirect3D->CheckDeviceFormat(
							m_GraphicCardNo,
							D3DDEVTYPE_HAL,
							BaseFormat,
							D3DUSAGE_RENDERTARGET,
							D3DRTYPE_TEXTURE,
							g_TextureFormats[i] );
		if SUCCEEDED( hr )
		{
			hr = m_pDirect3D->CheckDeviceFormat(
								m_GraphicCardNo,
								D3DDEVTYPE_HAL,
								BaseFormat,
								D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
								D3DRTYPE_TEXTURE,
								g_TextureFormats[i] );
			if SUCCEEDED( hr )
			{
				m_TargetAlphaFormats[m_TargetAlphaFormatCount++] = g_TextureFormats[i];
				m_TargetFormats[m_TargetFormatCount++] = g_TextureFormats[i];
				Log_PrintTable( 128, GetPixelFormat(g_TextureFormats[i]), "�A���t�@�u�����h ��" );
			}
			else
			{
				m_TargetFormats[m_TargetFormatCount++] = g_TextureFormats[i];
				Log_PrintTable( 128, GetPixelFormat(g_TextureFormats[i]), "�A���t�@�u�����h �~" );
			}
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// �[�x�o�b�t�@�t�H�[�}�b�g����g�p�\�Ȃ��̂�����
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "����" );
	Log_PrintCellKind( "�g�p�\��<BR>�f�v�X�X�e���V��<BR>�t�H�[�}�b�g" );
	Log_CellBegin( 0 );

	for ( Sint32 i = 0; g_DepthFormats[i] != D3DFMT_UNKNOWN; i++ )
	{
		hr = m_pDirect3D->CheckDeviceFormat(
								m_GraphicCardNo,
								D3DDEVTYPE_HAL,
								BaseFormat,
								D3DUSAGE_DEPTHSTENCIL,
								D3DRTYPE_SURFACE,
								g_DepthFormats[i] );
		if SUCCEEDED( hr )
		{
			hr = m_pDirect3D->CheckDeviceFormat(
									m_GraphicCardNo,
									D3DDEVTYPE_HAL,
									BaseFormat,
									D3DUSAGE_DEPTHSTENCIL,
									D3DRTYPE_TEXTURE,
									g_DepthFormats[i] );

			if SUCCEEDED( hr )
			{
				m_DepthTextureFormats[ m_DepthTextureFormatCount++ ] = g_DepthFormats[i];
				m_DepthSurfaceFormats[ m_DepthSurfaceFormatCount++ ] = g_DepthFormats[i];
				Log_PrintTable( 128, GetPixelFormat(g_DepthFormats[i]), "�n�[�h�E�F�A�V���h�E�}�b�v ��" );
			}
			else
			{
				m_DepthSurfaceFormats[ m_DepthSurfaceFormatCount++ ] = g_DepthFormats[i];
				Log_PrintTable( 128, GetPixelFormat(g_DepthFormats[i]), "�n�[�h�E�F�A�V���h�E�}�b�v �~" );
			}
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// R2VB�̃T�|�[�g�`�F�b�N
	//---------------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "����" );
	Log_PrintCellKind( "R2VB�̎g�p�\�`�F�b�N" );
	Log_CellBegin( 0 );

	hr = m_pDirect3D->CheckDeviceFormat(
						D3DADAPTER_DEFAULT,
						D3DDEVTYPE_HAL,
						BaseFormat,
						0,
						D3DRTYPE_SURFACE,
						D3DFMT_R2VB );
	if SUCCEEDED( hr )
	{
		Log_PrintLine( 0x000080, "Render to VertexBuffer ���T�|�[�g����" );
	}
	else
	{
		Log_PrintLine( 0x800000, "Render to VertexBuffer ���T�|�[�g���Ȃ�" );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	//---------------------------------------------------------------
	// �T�[�t�F�C�X�t�H�[�}�b�g�e�[�u��
	//---------------------------------------------------------------
	CreateSurfaceFormatTable();

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::CheckGraphicCardCaps( void )
{
	D3DCAPS9 Caps;

	//-----------------------------------------------------------
	// �n�[�h�E�F�A�f�o�C�X�̐��\���擾
	//-----------------------------------------------------------
	m_pDirect3D->GetDeviceCaps( m_GraphicCardNo, D3DDEVTYPE_HAL, &Caps );
	GetDeviceCaps( &Caps, &m_DeviceInfo );

	//-----------------------------------------------------------
	// �n�[�h�E�F�A�f�o�C�X�̐��\���
	//-----------------------------------------------------------
	Log_TableBegin();
	Log_PrintCellTitle( 0x008000, "����" );
	Log_PrintCellKind( "�r�f�I�J�[�h���\" );
	Log_CellBegin( 0 );

	Log_PrintTable( 256, "�s���A�f�o�C�X", "[ %s ]", m_DeviceInfo.IsPureDevice ? "��" : "�~" );
	Log_PrintTable( 256, "�L���[�u�}�b�v", "[ %s ]", m_DeviceInfo.IsCubeTexture ? "��" : "�~" );
	Log_PrintTable( 256, "���H�����[���}�b�v", "[ %s ]", m_DeviceInfo.IsVolumeTexture ? "��" : "�~" );
	Log_PrintTable( 256, "���I�e�N�X�`��", "[ %s ]", m_DeviceInfo.IsDynamicTexture ? "��" : "�~" );
	Log_PrintTable( 256, "�ٕ����t�B���^�F�g��", "[ %s ]", m_DeviceInfo.IsMagAnisotropy ? "��" : "�~" );
	Log_PrintTable( 256, "�ٕ����t�B���^�F�k��", "[ %s ]", m_DeviceInfo.IsMinAnisotropy ? "��" : "�~" );

	Log_PrintTable( 256, "�e�N�X�`���ő剡��", "[ %u ]", m_DeviceInfo.MaxTextureWidth );
	Log_PrintTable( 256, "�e�N�X�`���ő�c��", "[ %u ]", m_DeviceInfo.MaxTextureHeight );
	Log_PrintTable( 256, "�e�N�X�`���ٕ����̎���", "[ %u ]", m_DeviceInfo.MaxAnisotropy );

	Log_PrintTable( 256, "�e�N�X�`���Q�̗ݏ搧��", "[ %s ]", m_DeviceInfo.IsSupportNonePow2Texture ? "�Ȃ�" : "����" );
	Log_PrintTable( 256, "�e�N�X�`���Q�̗ݏ搧���̌������", "[ %s ]", m_DeviceInfo.IsSupportNonePow2ConditionalTexture ? "����" : "�Ȃ�" );
	Log_PrintTable( 256, "�e�N�X�`�������`����", "[ %s ]", m_DeviceInfo.IsSupportNoneSquareTexture ? "�Ȃ�" : "����" );

	Log_PrintTable( 256, "�ő�v���~�e�B�u��", "[ %u ]", m_DeviceInfo.MaxPrimitiveCount );
	Log_PrintTable( 256, "�ő�C���f�b�N�X��", "[ %u ]", m_DeviceInfo.MaxVertexIndex );
	Log_PrintTable( 256, "���_�V�F�[�_�[�o�[�W����", "[ %u.%u ]", D3DSHADER_VERSION_MAJOR(m_DeviceInfo.VertexShaderVersion), D3DSHADER_VERSION_MINOR(m_DeviceInfo.VertexShaderVersion) );
	Log_PrintTable( 256, "���_�V�F�[�_�[���ߐ�", "[ %u ]", m_DeviceInfo.VertexShaderInstructions );
	Log_PrintTable( 256, "���_�V�F�[�_�[�萔���W�X�^��", "[ %u ]", m_DeviceInfo.VertexShaderConstMax );
	Log_PrintTable( 256, "�s�N�Z���V�F�[�_�[�o�[�W����", "[ %u.%u ]", D3DSHADER_VERSION_MAJOR(m_DeviceInfo.PixelShaderVersion), D3DSHADER_VERSION_MINOR(m_DeviceInfo.PixelShaderVersion) );
	Log_PrintTable( 256, "�s�N�Z���V�F�[�_�[���ߐ�", "[ %u ]", m_DeviceInfo.PixelShaderInstructions );
	Log_PrintTable( 256, "���I�t���[���䖽�߂̃l�X�e�B���O", "[ %u ]", m_DeviceInfo.DynamicFlowControlDepth );
	Log_PrintTable( 256, "�ÓI�t���[���䖽�߂̃l�X�e�B���O", "[ %u ]", m_DeviceInfo.StaticFlowControlDepth );

	Log_PrintTable( 256, "�}���`�����_�����O�^�[�Q�b�g��", "[ %u ]", m_DeviceInfo.MultiRenderTargetCount );

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 2 );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::GetDeviceCaps( D3DCAPS9 *pCaps, DEVICEINFORMATION *pDevInfo )
{
	// �s���A�f�o�C�X
	pDevInfo->IsPureDevice							= (pCaps->DevCaps & D3DDEVCAPS_PUREDEVICE) != 0;
	// �e�N�X�`��
	pDevInfo->MaxTextureWidth						= pCaps->MaxTextureWidth;
	pDevInfo->MaxTextureHeight						= pCaps->MaxTextureHeight;
	pDevInfo->MaxAnisotropy							= pCaps->MaxAnisotropy;
	pDevInfo->IsDynamicTexture						= (pCaps->Caps2 & D3DCAPS2_DYNAMICTEXTURES) != 0;
	pDevInfo->IsMagAnisotropy						= (pCaps->TextureFilterCaps & D3DPTFILTERCAPS_MAGFANISOTROPIC) != 0;
	pDevInfo->IsMinAnisotropy						= (pCaps->TextureFilterCaps & D3DPTFILTERCAPS_MINFANISOTROPIC) != 0;
	// �e�N�X�`��
	pDevInfo->IsCubeTexture							= (pCaps->TextureCaps & D3DPTEXTURECAPS_CUBEMAP) != 0;
	pDevInfo->IsVolumeTexture						= (pCaps->TextureCaps & D3DPTEXTURECAPS_VOLUMEMAP) != 0;
	pDevInfo->IsSupportNonePow2Texture				= (pCaps->TextureCaps & D3DPTEXTURECAPS_POW2) == 0;
	pDevInfo->IsSupportNonePow2ConditionalTexture	= (pCaps->TextureCaps & D3DPTEXTURECAPS_NONPOW2CONDITIONAL) != 0;
	pDevInfo->IsSupportNoneSquareTexture			= (pCaps->TextureCaps & D3DPTEXTURECAPS_SQUAREONLY) == 0;
	// ��
	pDevInfo->MaxPrimitiveCount						= pCaps->MaxPrimitiveCount;
	pDevInfo->MaxVertexIndex						= pCaps->MaxVertexIndex;
	// �V�F�[�_�[
	pDevInfo->DynamicFlowControlDepth				= pCaps->VS20Caps.DynamicFlowControlDepth;
	pDevInfo->StaticFlowControlDepth				= pCaps->VS20Caps.StaticFlowControlDepth;
	pDevInfo->VertexShaderVersion					= pCaps->VertexShaderVersion;
	pDevInfo->VertexShaderInstructions				= pCaps->MaxVShaderInstructionsExecuted;
	pDevInfo->VertexShaderConstMax					= pCaps->MaxVertexShaderConst;
	pDevInfo->PixelShaderVersion					= pCaps->PixelShaderVersion;
	pDevInfo->PixelShaderInstructions				= pCaps->MaxPShaderInstructionsExecuted;
	// �}���`�����_�����O�^�[�Q�b�g
	pDevInfo->MultiRenderTargetCount				= pCaps->NumSimultaneousRTs;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::GetAnisotropyFilterSupport( Bool &IsMin, Bool &IsMag, Sint32 &Max )
{
	IsMag = m_DeviceInfo.IsMagAnisotropy;
	IsMin = m_DeviceInfo.IsMinAnisotropy;
	Max = m_DeviceInfo.MaxAnisotropy;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::EnableHighlColorScreen( void )
{
	m_IsHighColor = true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HMONITOR CGraphicCard::GetMonitorHandle( void )
{
	return m_pDirect3D->GetAdapterMonitor( m_GraphicCardNo );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::GetPixelShaderSupport( Uint16 Major, Uint16 Minor )
{
	return m_DeviceInfo.PixelShaderVersion >= D3DPS_VERSION( Major, Minor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::GetNonePow2ConditionalTextureSupport( void )
{
	return m_DeviceInfo.IsSupportNonePow2ConditionalTexture;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::GetNonePow2TextureSupport( void )
{
	return m_DeviceInfo.IsSupportNonePow2Texture;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::GetNoneSquareTextureSupport( void )
{
	return m_DeviceInfo.IsSupportNoneSquareTexture;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::IsHightColorMode( void )
{
	return m_IsHighColor;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::IsNVPerfHUDEnable( void )
{
	return m_IsHVPerfHUD;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CGraphicCard::GetDeviceTypeNo( void )
{
	// �w��o�[�e�b�N�X�V�F�[�_�[�����S�ɃT�|�[�g�H
	if ( m_DeviceInfo.VertexShaderVersion >= m_MaxUseVertexShaderVersion )
	{
		// 32Bit�C���f�b�N�X���T�|�[�g�H
		if ( (m_DeviceInfo.MaxPrimitiveCount > 0xFFFF) && (m_DeviceInfo.MaxVertexIndex > 0xFFFF) )
		{
			// �s���A�f�o�C�X���T�|�[�g�H
			if ( m_DeviceInfo.IsPureDevice )
			{
				return DEVICE_CREATE_PUREDEVICE;
			}
			else
			{
				return DEVICE_CREATE_HARDWARE_TNL;
			}
		}
	}

	return DEVICE_CREATE_SOFTWARE_TNL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
D3DPRESENT_PARAMETERS CGraphicCard::MakePresentParameters( Bool IsWindow, Bool IsHightColor, Bool IsLockEnableBackBuffer, Bool IsWaitVSync )
{
	Sint32 Width, Height;
	D3DPRESENT_PARAMETERS PresentParam;
	D3DFORMAT ScreenFormat = D3DFMT_UNKNOWN;
	Sint32 RefreshRate = 0;

	//-----------------------------------------------------------
	// ��ʃT�C�Y�擾
	//-----------------------------------------------------------
	m_pCore->GetScreenData( &Width, &Height, NULL );

	//-----------------------------------------------------------
	// ���[�h
	//-----------------------------------------------------------
	if ( IsWindow )
	{
		ScreenFormat = m_WindowModeInfo.Format;
		RefreshRate = 0;
	}
	else
	{
		if ( IsHightColor )
		{
			for ( Sint32 i = 0; i < m_ScreenTypeCount; i++ )
			{
				if ( m_ScreenType[i].Format == m_FullScreen16BitInfo )
				{
					if ( m_ScreenType[i].Width == (Uint32)Width )
					{
						if ( m_ScreenType[i].Height == (Uint32)Height )
						{
							ScreenFormat = m_ScreenType[i].Format;
							RefreshRate = m_ScreenType[i].RefreshRate;
						}
					}
				}
			}
		}
		else
		{
			for ( Sint32 i = 0; i < m_ScreenTypeCount; i++ )
			{
				if ( m_ScreenType[i].Format == m_FullScreen32BitInfo )
				{
					if ( m_ScreenType[i].Width == (Uint32)Width )
					{
						if ( m_ScreenType[i].Height == (Uint32)Height )
						{
							ScreenFormat = m_ScreenType[i].Format;
							RefreshRate = m_ScreenType[i].RefreshRate;
						}
					}
				}
			}
		}
	}

	//-----------------------------------------------------------
	// �p�����[�^�[����
	//-----------------------------------------------------------
	PresentParam.BackBufferWidth			= (Uint32)Width;
	PresentParam.BackBufferHeight			= (Uint32)Height;
	PresentParam.BackBufferFormat			= ScreenFormat;
	PresentParam.BackBufferCount			= 1;
	PresentParam.MultiSampleType			= D3DMULTISAMPLE_NONE;
	PresentParam.MultiSampleQuality			= 0;
	PresentParam.SwapEffect					= D3DSWAPEFFECT_DISCARD;
	PresentParam.hDeviceWindow				= m_pCore->GetWindowHandle();
	PresentParam.Windowed					= IsWindow;
	PresentParam.EnableAutoDepthStencil		= false;
	PresentParam.AutoDepthStencilFormat		= D3DFMT_UNKNOWN;
	PresentParam.Flags						= 0;
	PresentParam.FullScreen_RefreshRateInHz	= RefreshRate;
	PresentParam.PresentationInterval		= D3DPRESENT_INTERVAL_DEFAULT;

	if ( !IsWaitVSync || m_pCore->IsBenchMode() )
	{
		PresentParam.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}

	if ( IsLockEnableBackBuffer )
	{
		PresentParam.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	}

	return PresentParam;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
D3DFORMAT CGraphicCard::GetFormat( eSurfaceFormat Format )
{
	return m_SurfaceFormatTbl[Format];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CGraphicCard::CheckAlphaBlending( D3DFORMAT Format )
{
	Sint32 Max = m_TargetAlphaFormatCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		if ( Format == m_TargetAlphaFormats[i] )
		{
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::CreateSurfaceFormatTable( void )
{
	//------------------------------------------------------------
	// �t�H�[�}�b�g��񌟍�
	//------------------------------------------------------------
	for ( Sint32 Format = 0; Format < FORMAT_MAX; Format++ )
	{
		D3DFORMAT SurfaceFormat = D3DFMT_UNKNOWN;

		switch ( Format )
		{
		// 32Bit�����_�����O�^�[�Q�b�g
		case FORMAT_TARGET_UCHAR4:
			{
				static D3DFORMAT FmtTbl[] = {
					D3DFMT_A8R8G8B8, D3DFMT_UNKNOWN,
				};

				for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_TargetAlphaFormatCount; j++ )
					{
						if ( FmtTbl[i] == m_TargetAlphaFormats[j] )
						{
							SurfaceFormat = FmtTbl[i];
							goto EXIT;
						}
					}
				}
			}
			break;

		// HDR�����_�����O�^�[�Q�b�g
		case FORMAT_TARGET_FLOAT4_ALPHA:
			{
				static D3DFORMAT FmtTbl[] = {
					D3DFMT_A16B16G16R16F, D3DFMT_A32B32G32R32F, D3DFMT_A8R8G8B8, D3DFMT_UNKNOWN,
				};

				for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_TargetAlphaFormatCount; j++ )
					{
						if ( FmtTbl[i] == m_TargetAlphaFormats[j] )
						{
							SurfaceFormat = FmtTbl[i];
							goto EXIT;
						}
					}
				}
			}
			break;

		// �V���h�E�}�b�v�p
		case FORMAT_TARGET_FLOAT1:
			{
				static D3DFORMAT FmtTbl[] = {
					D3DFMT_R32F, D3DFMT_R16F, D3DFMT_A32B32G32R32F, D3DFMT_A16B16G16R16F, D3DFMT_UNKNOWN,
				};

				for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_TargetFormatCount; j++ )
					{
						if ( FmtTbl[i] == m_TargetFormats[j] )
						{
							SurfaceFormat = FmtTbl[i];
							goto EXIT;
						}
					}
				}
			}
			break;

		// �\�t�g�V���h�E�}�b�v�p
		case FORMAT_TARGET_FLOAT2:
			{
				static D3DFORMAT FmtTbl[] = {
					D3DFMT_G16R16F, D3DFMT_G32R32F, D3DFMT_A16B16G16R16F, D3DFMT_A32B32G32R32F, D3DFMT_UNKNOWN,
				};

				for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_TargetFormatCount; j++ )
					{
						if ( FmtTbl[i] == m_TargetFormats[j] )
						{
							SurfaceFormat = FmtTbl[i];
							goto EXIT;
						}
					}
				}
			}
			break;

		// �[�x�����x�}�b�v�p�����_�����O�^�[�Q�b�g
		case FORMAT_TARGET_FLOAT4:
			{
				static D3DFORMAT FmtTbl[] = {
					D3DFMT_A16B16G16R16F, D3DFMT_A32B32G32R32F, D3DFMT_UNKNOWN,
				};

				for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_TargetFormatCount; j++ )
					{
						if ( FmtTbl[i] == m_TargetFormats[j] )
						{
							SurfaceFormat = FmtTbl[i];
							goto EXIT;
						}
					}
				}
			}
			break;

		// 32Bit�e�N�X�`���t�H�[�}�b�g�ɏ���
		case FORMAT_TEXTURE_32BIT:
			{
				static D3DFORMAT FmtTbl[] = {
					D3DFMT_A8R8G8B8, D3DFMT_A4R4G4B4, D3DFMT_UNKNOWN,
				};

				for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_TextureFormatCount; j++ )
					{
						if ( FmtTbl[i] == m_TextureFormats[j] )
						{
							SurfaceFormat = FmtTbl[i];
							goto EXIT;
						}
					}
				}
			}
			break;

		// 16Bit�e�N�X�`���t�H�[�}�b�g�ɏ���
		case FORMAT_TEXTURE_16BIT:
			{
				static D3DFORMAT FmtTbl[] = {
					D3DFMT_A4R4G4B4, D3DFMT_A8R8G8B8, D3DFMT_UNKNOWN,
				};

				for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_TextureFormatCount; j++ )
					{
						if ( FmtTbl[i] == m_TextureFormats[j] )
						{
							SurfaceFormat = FmtTbl[i];
							goto EXIT;
						}
					}
				}
			}
			break;

		// DXT���k�t�H�[�}�b�g�e�N�X�`��
		case FORMAT_TEXTURE_DXT:
			{
				static D3DFORMAT FmtTbl[] = {
					D3DFMT_DXT5, D3DFMT_DXT3, D3DFMT_DXT1, D3DFMT_A8R8G8B8, D3DFMT_A4R4G4B4, D3DFMT_A1R5G5B5, D3DFMT_UNKNOWN,
				};

				for ( Sint32 i = 0; FmtTbl[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_TextureFormatCount; j++ )
					{
						if ( FmtTbl[i] == m_TextureFormats[j] )
						{
							SurfaceFormat = FmtTbl[i];
							goto EXIT;
						}
					}
				}
			}
			break;

		// �[�x�o�b�t�@
		case FORMAT_DEPTHBUFFER_SURFACE:
			{
				for ( Sint32 i = 0; g_DepthFormats[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_DepthSurfaceFormatCount; j++ )
					{
						if ( g_DepthFormats[i] == m_DepthSurfaceFormats[j] )
						{
							SurfaceFormat = g_DepthFormats[i];
							goto EXIT;
						}
					}
				}
			}
			break;

		// �[�x�o�b�t�@
		case FORMAT_DEPTHBUFFER_TEXTURE:
			{
				for ( Sint32 i = 0; g_DepthFormats[i] != D3DFMT_UNKNOWN; i++ )
				{
					for ( Sint32 j = 0; j < m_DepthTextureFormatCount; j++ )
					{
						if ( g_DepthFormats[i] == m_DepthTextureFormats[j] )
						{
							SurfaceFormat = g_DepthFormats[i];
							goto EXIT;
						}
					}
				}
			}
			break;
		}
EXIT:
		m_SurfaceFormatTbl[Format] = SurfaceFormat;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CGraphicCard::GetScreenModeCount( Bool IsFullColor )
{
	Sint32 Count = 0;

	if ( IsFullColor )
	{
		for ( Sint32 i = 0; i < m_ScreenTypeCount; i++ )
		{
			if ( m_ScreenType[i].Format == m_FullScreen16BitInfo )
			{
				Count++;
			}
		}
	}
	else
	{
		for ( Sint32 i = 0; i < m_ScreenTypeCount; i++ )
		{
			if ( m_ScreenType[i].Format == m_FullScreen32BitInfo )
			{
				Count++;
			}
		}
	}

	return Count;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::GetScreenMode( Bool IsFullColor, Sint32 No, Sint32 &Width, Sint32 &Height )
{
	if ( IsFullColor )
	{
		for ( Sint32 i = 0; i < m_ScreenTypeCount; i++ )
		{
			if ( m_ScreenType[i].Format == m_FullScreen32BitInfo )
			{
				if ( No-- == 0 )
				{
					Width = m_ScreenType[i].Width;
					Height = m_ScreenType[i].Height;
					return;
				}
			}
		}
	}
	else
	{
		for ( Sint32 i = 0; i < m_ScreenTypeCount; i++ )
		{
			if ( m_ScreenType[i].Format == m_FullScreen16BitInfo )
			{
				if ( No-- == 0 )
				{
					Width = m_ScreenType[i].Width;
					Height = m_ScreenType[i].Height;
					return;
				}
			}
		}
	}

	Width = 0;
	Height = 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CGraphicCard::CreateRenderTargetTextureSizeCount( void )
{
	Sint32 Count = 0;

	if ( m_DeviceInfo.MaxTextureWidth <  m_DeviceInfo.MaxTextureHeight )
	{
		for ( Sint32 i = 32; i <= m_DeviceInfo.MaxTextureWidth; i <<= 1 ) Count++;
	}
	else
	{
		for ( Sint32 i = 32; i <= m_DeviceInfo.MaxTextureHeight; i <<= 1 ) Count++;
	}

	return Count;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::CreateRenderTargetTextureSize( Sint32 No, Sint32 *pWidth, Sint32 *pHeight )
{
	Sint32 Count = 0;

	if ( m_DeviceInfo.MaxTextureWidth <  m_DeviceInfo.MaxTextureHeight )
	{
		for ( Sint32 i = 32; i <= m_DeviceInfo.MaxTextureWidth; i <<= 1 )
		{
			if ( Count++ == No )
			{
				*pWidth = *pHeight = i;
				return;
			}
		}
	}
	else
	{
		for ( Sint32 i = 32; i <= m_DeviceInfo.MaxTextureHeight; i <<= 1 )
		{
			if ( Count++ == No )
			{
				*pWidth = *pHeight = i;
				return;
			}
		}
	}

	*pWidth = *pHeight = 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::GetGraphicCardName( char *pName, Sint32 NameSize )
{
	StringCbCopy( pName, NameSize, m_GraphicCardName );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::GetVertexShaderVersion( char *pName, Sint32 NameSize )
{
	StringCbPrintf( pName, NameSize, "VertexShader %u.%u", D3DSHADER_VERSION_MAJOR(m_DeviceInfo.VertexShaderVersion), D3DSHADER_VERSION_MINOR(m_DeviceInfo.VertexShaderVersion) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CGraphicCard::GetPixelShaderVersion( char *pName, Sint32 NameSize )
{
	StringCbPrintf( pName, NameSize, "PixelShader %u.%u", D3DSHADER_VERSION_MAJOR(m_DeviceInfo.PixelShaderVersion), D3DSHADER_VERSION_MINOR(m_DeviceInfo.PixelShaderVersion) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Renderer::IRender *CGraphicCard::CreateRender( Bool IsLockEnableBackBuffer, Bool IsWaitVSync )
{
	if ( m_pRender == NULL )
	{
		Bool IsWindow;
		m_pCore->GetScreenData( NULL, NULL, &IsWindow );

		m_pRender = new Renderer::CRender( this, IsWindow, IsLockEnableBackBuffer, IsWaitVSync );
		if ( m_pRender->GetDriverDevicePointer() == NULL )
		{
			SAFE_RELEASE( m_pRender );
		}			
	}
	else
	{
		m_pRender->AddRef();
	}

	return m_pRender;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DI CGraphicCard::GetTextureMaxSize( void )
{
	return Math::Point2DI( m_DeviceInfo.MaxTextureWidth, m_DeviceInfo.MaxTextureHeight );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DI CGraphicCard::GetTextureSize( Math::Point2DI Size, eSurfaceFormat Format, Bool IsMipmap )
{
	Math::Point2DI SizeMax = GetTextureMaxSize();
	Math::Point2DI SizeNew;

	// �������Q�̗ݏ攛�肠��
	if ( GetNonePow2ConditionalTextureSupport() )
	{
		// ���k
		if ( (Format == FORMAT_TEXTURE_DXT) || IsMipmap )
		{
			// �Q�̗ݏ�̕ύX
			for ( SizeNew.x = 1; SizeNew.x < Size.x; SizeNew.x <<= 1 );
			for ( SizeNew.y = 1; SizeNew.y < Size.y; SizeNew.y <<= 1 );
		}
		// �񈳏k
		else
		{
			// ���̂܂�
			SizeNew = Size;
		}
	}
	// �Q�̗ݏ攛��Ȃ��H
	ef ( GetNonePow2TextureSupport() )
	{
		// ���̂܂�
		SizeNew = Size;
	}
	// ����
	else
	{
		// �Q�̗ݏ�̕ύX
		for ( SizeNew.x = 1; SizeNew.x < Size.x; SizeNew.x <<= 1 );
		for ( SizeNew.y = 1; SizeNew.y < Size.y; SizeNew.y <<= 1 );
	}

	// �����`���肠��H
	if ( !GetNoneSquareTextureSupport() )
	{
		// �傫�����ɍ��킹�Đ����`�ɂ���
		if ( SizeNew.x < SizeNew.y )
		{
			SizeNew.x = SizeNew.y;
		}
		else
		{
			SizeNew.y = SizeNew.x;
		}
	}

	// �T�|�[�g�T�C�Y�����Ă�H
	if ( SizeNew.x > SizeMax.x ) SizeNew.x = SizeMax.x;
	if ( SizeNew.y > SizeMax.y ) SizeNew.y = SizeMax.y;

	return SizeNew;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCore *CGraphicCard::GetCorePointer( void )
{
	return m_pCore;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
HRESULT CGraphicCard::CreateDeviceObject( D3DDEVTYPE DeviceType, Sint32 CreateFlag, D3DPRESENT_PARAMETERS &Param, IDirect3DDevice9 *&pDevice )
{
	HRESULT hr = m_pDirect3D->CreateDevice(
					m_GraphicCardNo,
					DeviceType,
					m_pCore->GetWindowHandle(),
					CreateFlag,
					&Param,
					&pDevice );
	return hr;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
char *CGraphicCard::GetPixelFormat( D3DFORMAT Format, char *pErrStr, Sint32 ErrStrSize )
{
	static char String[64] = "";

	switch ( (Uint32)Format )
	{
	case D3DFMT_UNKNOWN:			StringCbCopy( String, sizeof(String), "UNKNOWN" );			break;
	case D3DFMT_R8G8B8:				StringCbCopy( String, sizeof(String), "R8G8B8" );			break;
	case D3DFMT_A8R8G8B8:			StringCbCopy( String, sizeof(String), "A8R8G8B8" );			break;
	case D3DFMT_X8R8G8B8:			StringCbCopy( String, sizeof(String), "X8R8G8B8" );			break;
	case D3DFMT_R5G6B5:				StringCbCopy( String, sizeof(String), "R5G6B5" );			break;
	case D3DFMT_X1R5G5B5:			StringCbCopy( String, sizeof(String), "X1R5G5B5" );			break;
	case D3DFMT_A1R5G5B5:			StringCbCopy( String, sizeof(String), "A1R5G5B5" );			break;
	case D3DFMT_A4R4G4B4:			StringCbCopy( String, sizeof(String), "A4R4G4B4" );			break;
	case D3DFMT_R3G3B2:				StringCbCopy( String, sizeof(String), "R3G3B2" );			break;
	case D3DFMT_A8:					StringCbCopy( String, sizeof(String), "A8" );				break;
	case D3DFMT_A8R3G3B2:			StringCbCopy( String, sizeof(String), "A8R3G3B2" );			break;
	case D3DFMT_X4R4G4B4:			StringCbCopy( String, sizeof(String), "X4R4G4B4" );			break;
	case D3DFMT_A2B10G10R10:		StringCbCopy( String, sizeof(String), "A2B10G10R10" );		break;
	case D3DFMT_A8B8G8R8:			StringCbCopy( String, sizeof(String), "A8B8G8R8" );			break;
	case D3DFMT_X8B8G8R8:			StringCbCopy( String, sizeof(String), "X8B8G8R8" );			break;
	case D3DFMT_G16R16:				StringCbCopy( String, sizeof(String), "G16R16" );			break;
	case D3DFMT_A2R10G10B10:		StringCbCopy( String, sizeof(String), "A2R10G10B10" );		break;
	case D3DFMT_A16B16G16R16:		StringCbCopy( String, sizeof(String), "A16B16G16R16" );		break;
	case D3DFMT_A8P8:				StringCbCopy( String, sizeof(String), "A8P8" );				break;
	case D3DFMT_P8:					StringCbCopy( String, sizeof(String), "P8" );				break;
	case D3DFMT_L8:					StringCbCopy( String, sizeof(String), "L8" );				break;
	case D3DFMT_L16:				StringCbCopy( String, sizeof(String), "L16" );				break;
	case D3DFMT_A8L8:				StringCbCopy( String, sizeof(String), "A8L8" );				break;
	case D3DFMT_A4L4:				StringCbCopy( String, sizeof(String), "A4L4" );				break;
	case D3DFMT_V8U8:				StringCbCopy( String, sizeof(String), "V8U8" );				break;
	case D3DFMT_Q8W8V8U8:			StringCbCopy( String, sizeof(String), "Q8W8V8U8" );			break;
	case D3DFMT_V16U16:				StringCbCopy( String, sizeof(String), "V16U16" );			break;
	case D3DFMT_Q16W16V16U16:		StringCbCopy( String, sizeof(String), "Q16W16V16U16" );		break;
	case D3DFMT_CxV8U8:				StringCbCopy( String, sizeof(String), "CxV8U8" );			break;
	case D3DFMT_L6V5U5:				StringCbCopy( String, sizeof(String), "L6V5U5" );			break;
	case D3DFMT_X8L8V8U8:			StringCbCopy( String, sizeof(String), "X8L8V8U8" );			break;
	case D3DFMT_A2W10V10U10:		StringCbCopy( String, sizeof(String), "A2W10V10U10" );		break;
	case D3DFMT_G8R8_G8B8:			StringCbCopy( String, sizeof(String), "G8R8_G8B8" );		break;
	case D3DFMT_R8G8_B8G8:			StringCbCopy( String, sizeof(String), "R8G8_B8G8" );		break;
	case D3DFMT_DXT1:				StringCbCopy( String, sizeof(String), "DXT1" );				break;
	case D3DFMT_DXT2:				StringCbCopy( String, sizeof(String), "DXT2" );				break;
	case D3DFMT_DXT3:				StringCbCopy( String, sizeof(String), "DXT3" );				break;
	case D3DFMT_DXT4:				StringCbCopy( String, sizeof(String), "DXT4" );				break;
	case D3DFMT_DXT5:				StringCbCopy( String, sizeof(String), "DXT5" );				break;
	case D3DFMT_UYVY:				StringCbCopy( String, sizeof(String), "UYVY" );				break;
	case D3DFMT_YUY2:				StringCbCopy( String, sizeof(String), "YUY2" );				break;
	case D3DFMT_D16_LOCKABLE:		StringCbCopy( String, sizeof(String), "D16_LOCKABLE" );		break;
	case D3DFMT_D32:				StringCbCopy( String, sizeof(String), "D32" );				break;
	case D3DFMT_D15S1:				StringCbCopy( String, sizeof(String), "D15S1" );			break;
	case D3DFMT_D24S8:				StringCbCopy( String, sizeof(String), "D24S8" );			break;
	case D3DFMT_D24X8:				StringCbCopy( String, sizeof(String), "D24X8" );			break;
	case D3DFMT_D24X4S4:			StringCbCopy( String, sizeof(String), "D24X4S4" );			break;
	case D3DFMT_D32F_LOCKABLE:		StringCbCopy( String, sizeof(String), "D32F_LOCKABLE" );	break;
	case D3DFMT_D24FS8:				StringCbCopy( String, sizeof(String), "D24FS8" );			break;
	case D3DFMT_DF24:				StringCbCopy( String, sizeof(String), "DF24" );				break;
	case D3DFMT_D16:				StringCbCopy( String, sizeof(String), "D16" );				break;
	case D3DFMT_R2VB:				StringCbCopy( String, sizeof(String), "R2VB" );				break;
	case D3DFMT_VERTEXDATA:			StringCbCopy( String, sizeof(String), "VERTEXDATA" );		break;
	case D3DFMT_INDEX16:			StringCbCopy( String, sizeof(String), "INDEX16" );			break;
	case D3DFMT_INDEX32:			StringCbCopy( String, sizeof(String), "INDEX32" );			break;
	case D3DFMT_R16F:				StringCbCopy( String, sizeof(String), "R16F" );				break;
	case D3DFMT_G16R16F:			StringCbCopy( String, sizeof(String), "G16R16F" );			break;
	case D3DFMT_A16B16G16R16F:		StringCbCopy( String, sizeof(String), "A16B16G16R16F" );	break;
	case D3DFMT_R32F:				StringCbCopy( String, sizeof(String), "R32F" );				break;
	case D3DFMT_G32R32F:			StringCbCopy( String, sizeof(String), "G32R32F" );			break;
	case D3DFMT_A32B32G32R32F:		StringCbCopy( String, sizeof(String), "A32B32G32R32F" );	break;
	}

	if ( pErrStr != NULL ) StringCbCopy( pErrStr, ErrStrSize, String );

	return String;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
char *CGraphicCard::GetD3DError( HRESULT hr, char *pErrStr, Sint32 ErrStrSize )
{
	static char String[128] = "";

	switch ( hr )
	{
	case D3D_OK:							StringCbCopy( String, sizeof(String), "�G���[�͔������Ă��Ȃ��B" );																																					break;
	case D3DERR_CONFLICTINGRENDERSTATE:		StringCbCopy( String, sizeof(String), "���ݐݒ肳��Ă��郌���_�����O �X�e�[�g�͈ꏏ�Ɏg�p�ł��Ȃ��B" );																											break;
	case D3DERR_CONFLICTINGTEXTUREFILTER:	StringCbCopy( String, sizeof(String), "���݂̃e�N�X�`�� �t�B���^�͈ꏏ�Ɏg�p�ł��Ȃ��B" );																															break;
	case D3DERR_CONFLICTINGTEXTUREPALETTE:	StringCbCopy( String, sizeof(String), "���݂̃e�N�X�`���͓����Ɏg�p�ł��Ȃ��B��ʂɃ}���`�e�N�X�`�� �f�o�C�X�ɂ����āA�����ɗL���ɂ��ꂽ�p���b�g���e�N�X�`���œ����p���b�g�����L����K�v������ꍇ�ɔ�������B" );	break;
	case D3DERR_DEVICELOST:					StringCbCopy( String, sizeof(String), "�f�o�C�X�������Ă��āA�����_�ł͕����ł��Ȃ����߁A�����_�����O�͕s�\�ł���B" );																							break;
	case D3DERR_DEVICENOTRESET:				StringCbCopy( String, sizeof(String), "�f�o�C�X�̓��Z�b�g�ł��Ȃ��B" );																																				break;
	case D3DERR_DRIVERINTERNALERROR:		StringCbCopy( String, sizeof(String), "�����h���C�o �G���[�B" );																																					break;
	case D3DERR_INVALIDCALL:				StringCbCopy( String, sizeof(String), "���\�b�h�̌Ăяo���������ł���B���Ƃ��΁A���\�b�h�̃p�����[�^�ɖ����Ȓl���ݒ肳��Ă���ꍇ�ȂǁB" );																		break;
	case D3DERR_INVALIDDEVICE:				StringCbCopy( String, sizeof(String), "�v�����ꂽ�f�o�C�X�̎�ނ��L���łȂ��B" );																																	break;
	case D3DERR_MOREDATA:					StringCbCopy( String, sizeof(String), "�w�肳�ꂽ�o�b�t�@ �T�C�Y�ɕێ��ł���ȏ�̃f�[�^�����݂���B" );																											break;
	case D3DERR_NOTAVAILABLE:				StringCbCopy( String, sizeof(String), "���̃f�o�C�X�́A�Ɖ�ꂽ�e�N�j�b�N���T�|�[�g���Ă��Ȃ��B" );																												break;
	case D3DERR_NOTFOUND:					StringCbCopy( String, sizeof(String), "�v�����ꂽ���ڂ�������Ȃ������B" );																																		break;
	case D3DERR_OUTOFVIDEOMEMORY:			StringCbCopy( String, sizeof(String), "Direct3D ���������s���̂ɏ\���ȃf�B�X�v���C ���������Ȃ��B" );																												break;
	case D3DERR_TOOMANYOPERATIONS:			StringCbCopy( String, sizeof(String), "�f�o�C�X���T�|�[�g���Ă���ȏ�̃e�N�X�`�� �t�B���^�����O�������A�A�v���P�[�V�������v�����Ă���B" );																		break;
	case D3DERR_UNSUPPORTEDALPHAARG:		StringCbCopy( String, sizeof(String), "�A���t�@ �`���l���ɑ΂��Ďw�肳��Ă���e�N�X�`�� �u�����f�B���O�������A�f�o�C�X���T�|�[�g���Ă��Ȃ��B" );																	break;
	case D3DERR_UNSUPPORTEDALPHAOPERATION:	StringCbCopy( String, sizeof(String), "�A���t�@ �`���l���ɑ΂��Ďw�肳��Ă���e�N�X�`�� �u�����f�B���O�������A�f�o�C�X���T�|�[�g���Ă��Ȃ��B" );																	break;
	case D3DERR_UNSUPPORTEDCOLORARG:		StringCbCopy( String, sizeof(String), "�J���[�l�ɑ΂��Ďw�肳��Ă���e�N�X�`�� �u�����f�B���O�������A�f�o�C�X���T�|�[�g���Ă��Ȃ��B" );																			break;
	case D3DERR_UNSUPPORTEDCOLOROPERATION:	StringCbCopy( String, sizeof(String), "�J���[�l�ɑ΂��Ďw�肳��Ă���e�N�X�`�� �u�����f�B���O�������A�f�o�C�X���T�|�[�g���Ă��Ȃ��B" );																			break;
	case D3DERR_UNSUPPORTEDFACTORVALUE:		StringCbCopy( String, sizeof(String), "�f�o�C�X���w�肳�ꂽ�e�N�X�`���W���l���T�|�[�g���Ă��Ȃ��B" );																												break;
	case D3DERR_UNSUPPORTEDTEXTUREFILTER:	StringCbCopy( String, sizeof(String), "�f�o�C�X���w�肳�ꂽ�e�N�X�`�� �t�B���^���T�|�[�g���Ă��Ȃ��B" );																											break;
	case D3DERR_WRONGTEXTUREFORMAT:			StringCbCopy( String, sizeof(String), "�e�N�X�`�� �T�[�t�F�X�̃s�N�Z�� �t�H�[�}�b�g���L���łȂ��B" );																												break;
	case E_FAIL:							StringCbCopy( String, sizeof(String), "Direct3D �T�u�V�X�e�����Ō����s���̃G���[�����������B" );																													break;
	case E_INVALIDARG:						StringCbCopy( String, sizeof(String), "�����ȃp�����[�^���߂��Ă���֐��ɓn���ꂽ�B" );																																break;
	case E_OUTOFMEMORY:						StringCbCopy( String, sizeof(String), "Direct3D ���Ăяo�����������邽�߂̏\���ȃ����������蓖�Ă邱�Ƃ��ł��Ȃ������B" );																							break;
	case D3DXERR_CANNOTATTRSORT:			StringCbCopy( String, sizeof(String), "�œK���e�N�j�b�N�Ƃ��đ����̃\�[�g (D3DXMESHOPT_ATTRSORT) �̓T�|�[�g����Ă��Ȃ��B " );																						break;
	case D3DXERR_CANNOTMODIFYINDEXBUFFER:	StringCbCopy( String, sizeof(String), "�C���f�b�N�X �o�b�t�@��ύX�ł��Ȃ��B " );																																	break;
	case D3DXERR_INVALIDMESH:				StringCbCopy( String, sizeof(String), "���b�V���������ł���B " );																																					break;
	case D3DXERR_SKINNINGNOTSUPPORTED:		StringCbCopy( String, sizeof(String), "�X�L�j���O�̓T�|�[�g����Ă��Ȃ��B " );																																		break;
	case D3DXERR_TOOMANYINFLUENCES:			StringCbCopy( String, sizeof(String), "�w�肳�ꂽ�e������������B " );																																				break;
	case D3DXERR_INVALIDDATA:				StringCbCopy( String, sizeof(String), "�f�[�^�������ł���B" );																																						break;
	default:								StringCbCopy( String, sizeof(String), "���m�̃G���[�B" );																																							break;
	}

	if ( pErrStr != NULL ) StringCbCopy( pErrStr, ErrStrSize, String );

	return String;
}

