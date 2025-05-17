

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "System.h"
#include "Class/Common/File/CResourceFile.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace File;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CResourceFile::CResourceFile( const char *pFileName ) : CFile( pFileName, FILE_OPEN_TYPE_READ )
	, m_pCrypt	( NULL )
	, m_Start	( 0 )
	, m_Size	( CFile::GetFileSize() )
{
	StringCbCopy( m_FileName, sizeof(m_FileName), pFileName );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CResourceFile::~CResourceFile()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CResourceFile::Read( void *pData, Sint32 Size )
{
	Sint32 ReadByte = 0;

	// ファイルの現在位置を取得
	Sint32 Pos = GetFilePosition();

	// 実際に処理するバイト数
	ReadByte = Size;
	if ( ReadByte > m_Size - Pos )
	{
		ReadByte = m_Size - Pos;
	}

	// ファイル読み込み
	Sint32 Read = CFile::Read( pData, ReadByte );

	// 複合化
	if ( m_pCrypt != NULL )
	{
		m_pCrypt->Decrypt( (Uint8*)pData, (Uint8*)pData, Size, Pos );
	}
	
	return Read;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CResourceFile::GetFileStart( void )
{
	return m_Start;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CResourceFile::GetFileSize( void )
{
	return m_Size;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CResourceFile::SeekStart( Sint32 Offset )
{
	// ファイルの現在位置を取得
	Sint32 Pos = m_Start + Offset;

	// 位置が不正かチェック
	if ( Pos < m_Start ) return 0;
	if ( Pos > m_Start + m_Size ) return 0;

	// ファイル位置設定
	CFile::SeekStart( Pos );

	return Pos - m_Start;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CResourceFile::SeekEnd( Sint32 Offset )
{
	// ファイルの現在位置を取得
	Sint32 Pos = m_Start + m_Size + Offset;

	// 位置が不正かチェック
	if ( Pos < m_Start ) return 0;
	if ( Pos > m_Start + m_Size ) return 0;

	// ファイル位置設定
	CFile::SeekStart( Pos );

	return Pos - m_Start;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CResourceFile::Seek( Sint32 Offset )
{
	// ファイルの現在位置を取得
	Sint32 Pos = m_Start + GetFilePosition() + Offset;

	// 位置が不正かチェック
	if ( Pos < m_Start ) return 0;
	if ( Pos > m_Start + m_Size ) return 0;

	// ファイル位置設定
	CFile::SeekStart( Pos );

	return Pos - m_Start;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CResourceFile::GetFilePosition( void )
{
	return CFile::Seek( 0 ) - m_Start;
}	

