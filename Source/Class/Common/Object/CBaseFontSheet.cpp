
//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "System.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Surface/CTexture.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/File/CFileManager.h"
#include "Class/Common/Object/CBaseFontSheet.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// STRUCT
//-----------------------------------------------------------------------------------
struct SFFHEADER
{
	Uint32 Guid;
	Uint8 FontSize;
	Uint8 SheetMax;
	Uint16 FontMax;
	Uint16 IndexTbl[CHARA_CODE_MAX];
};


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
static const Uint16 g_KeyCodeTable[] = {
#include "KeyCodeTable.inc"
};


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseFontSheet::CBaseFontSheet( Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr ) : CRenderObject( pRender, pMgr )
{
	MemoryClear( m_pTextures, sizeof(m_pTextures) );
	MemoryClear( m_IndexTbl, sizeof(m_IndexTbl) );

	m_pSheetTbl		= NULL;

	m_SheetCount	= 0;
	m_FontSize		= 0;
	m_FontMax		= 0;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CBaseFontSheet::~CBaseFontSheet()
{
	SAFE_DELETE_ARRAY( m_pSheetTbl );

	for ( Sint32 i = 0; i < SHEET_MAX; i++ )
	{
		SAFE_RELEASE( m_pTextures[i] );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CBaseFontSheet::CreateSheetTableFromMemory( void *pData, const char *pExt )
{
	SFFHEADER *pSffHead;
	Bool bRet = false;

	//--------------------------------------------------------------
	// �w�b�_
	//--------------------------------------------------------------
	pSffHead = (SFFHEADER*)pData;
	pData = (char*)pData + sizeof(SFFHEADER);
	if ( pSffHead->Guid != 'SFF' ) goto EXIT;

	//--------------------------------------------------------------
	// �f�[�^
	//--------------------------------------------------------------
	m_FontSize		= pSffHead->FontSize;		// �t�H���g�T�C�Y
	m_FontMax		= pSffHead->FontMax;		// �t�H���g��
	m_SheetCount	= pSffHead->SheetMax;		// �V�[�g��

	//--------------------------------------------------------------
	// �C���f�b�N�X
	//--------------------------------------------------------------
	MemoryCopy( m_IndexTbl, pSffHead->IndexTbl, sizeof(Uint16) * CHARA_CODE_MAX );

	//--------------------------------------------------------------
	// �V�[�g��
	//--------------------------------------------------------------
	for ( Sint32 i = 0; i < m_SheetCount; i++ )
	{
		// �V�[�g���擾
		char Name[33] = "";
		MemoryCopy( Name, pData, 32 );
		pData = (char*)pData + 32;

		// �e�N�X�`������
		if ( (pExt != NULL) )
		{
			StringCbCat( Name, sizeof(Name), "." );
			StringCbCat( Name, sizeof(Name), pExt );
			m_pTextures[i] = m_pRender->CreateTextureFromFile( Name );
			if ( m_pTextures[i]->IsInvalid() ) goto EXIT;
		}
	}

	//--------------------------------------------------------------
	// �f�[�^
	//--------------------------------------------------------------
	m_pSheetTbl = new SFontSheetData [ pSffHead->FontMax ];
	MemoryCopy( m_pSheetTbl, pData, sizeof(SFontSheetData) * pSffHead->FontMax );
	pData = (char*)pData + sizeof(SFontSheetData) * pSffHead->FontMax;

	bRet = true;

EXIT:
	return bRet;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CBaseFontSheet::CreateSheetTableFromFile( const char *pFileName, const char *pExt )
{
	//--------------------------------------------------------------
	// �t�@�C������
	//--------------------------------------------------------------
	Sint32 Size;
	void *pData;

	//--------------------------------------------------------------
	// �t�@�C���ǂݍ���
	//--------------------------------------------------------------
	if ( m_pCore->GetFileMgrPointer()->Load( pFileName, &pData, &Size ) )
	{
		if ( !CreateSheetTableFromMemory( pData, pExt ) )
		{
			Log_PrintStrong( 0x000000, pFileName );
			Log_PrintStrong( 0xFF0000, "�t�@�C�����s���ł�" );
			m_pCore->GetFileMgrPointer()->Free( pData );
			return false;
		}

		m_pCore->GetFileMgrPointer()->Free( pData );
	}
	else
	{
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintStrong( 0xFF0000, "�t�@�C����������܂���" );
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CBaseFontSheet::GetWidth( const char Chara, Sint32 *pLeft, Sint32 *pCenter, Sint32 *pRight )
{
	if ( pLeft   != NULL ) *pLeft	= (Sint32)m_pSheetTbl[Chara].Left;
	if ( pCenter != NULL ) *pCenter	= (Sint32)(m_pSheetTbl[Chara].x2 - m_pSheetTbl[Chara].x1);
	if ( pRight  != NULL ) *pRight	= (Sint32)m_pSheetTbl[Chara].Right;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CBaseFontSheet::GetHeight( Sint32 *pHeight )
{
	*pHeight = m_FontSize;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint16 CBaseFontSheet::GetKeyCode( Uint16 Code )
{
	return g_KeyCodeTable[Code];
}

