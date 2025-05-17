

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Object/CRenderObject.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CVertexLayout.h"
#include "Class/Platform/Render/CRender.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRenderObject::CRenderObject( CRender *pRender, CRenderObjectMgr *pMgr )
	: CResourceObject	( pMgr )
	, m_pRender			( pRender )
	, m_pGraphicCard	( pRender->GetGraphicCardPointer() )
	, m_pCore			( pRender->GetGraphicCardPointer()->GetCorePointer() )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRenderObject::~CRenderObject()
{
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
char *CRenderObject::GetError( HRESULT hr )
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

	return String;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRender *CRenderObject::GetRenderPointer( void )
{
	return m_pRender;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CGraphicCard *CRenderObject::GetGraphicCardPointer( void )
{
	return m_pGraphicCard;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCore *CRenderObject::GetCorePointer( void )
{
	return m_pCore;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DI CRenderObject::GetTextureMaxSize( void )
{
	return m_pGraphicCard->GetTextureMaxSize();
}

