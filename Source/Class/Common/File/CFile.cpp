

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "System.h"
#include "Class/Common/File/CFile.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace File;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFile::CFile( const char *pFileName, eFileOpenType Type )
{
	Sint32 Generic;
	Sint32 Create;

	m_hFile = INVALID_HANDLE_VALUE;
	m_Type  = FILE_OPEN_TYPE_INVALID;

	switch ( Type )
	{
	case FILE_OPEN_TYPE_WRITE:
		Generic = GENERIC_WRITE;
		Create  = CREATE_ALWAYS;
		break;

	case FILE_OPEN_TYPE_READ:
		Generic = GENERIC_READ;
		Create  = OPEN_EXISTING;
		break;

	case FILE_OPEN_TYPE_READ_WRITE:
		Generic = GENERIC_READ | GENERIC_WRITE;
		Create  = OPEN_EXISTING;
		break;

	default:
		return;
	}

	System::ResetCurrentDirectory();

	m_hFile = ::CreateFile( pFileName, Generic, FILE_SHARE_READ, NULL, Create, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( m_hFile == INVALID_HANDLE_VALUE ) return;

	::GetFileTime( m_hFile, &m_TimeCreate, &m_TimeAccess, &m_TimeLastWrite );
	m_Type = Type;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFile::~CFile()
{
	if ( m_hFile == INVALID_HANDLE_VALUE ) return;

	::SetFileTime( m_hFile, &m_TimeCreate, &m_TimeAccess, &m_TimeLastWrite );
	::CloseHandle( m_hFile );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CFile::IsOpened( void )
{
	return m_hFile != INVALID_HANDLE_VALUE;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFile::Write( const void *pData, Sint32 Size )
{
	if ( m_hFile == INVALID_HANDLE_VALUE ) return 0;

	Uint32 WriteBytes;
	::WriteFile( m_hFile, pData, Size, &WriteBytes, NULL);
	return WriteBytes;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFile::Read( void *pData, Sint32 Size )
{
	if ( m_hFile == INVALID_HANDLE_VALUE ) return 0;

	Uint32 ReadBytes;
	::ReadFile( m_hFile, pData, Size, &ReadBytes, NULL);
	return ReadBytes;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFile::GetFileSize( void )
{
	if ( m_hFile == INVALID_HANDLE_VALUE ) return 0;

	return ::GetFileSize( m_hFile, NULL );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFile::SeekStart( Sint32 Offset )
{
	if ( m_hFile == INVALID_HANDLE_VALUE ) return 0;

	return ::SetFilePointer( m_hFile, Offset, NULL, FILE_BEGIN );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFile::SeekEnd( Sint32 Offset )
{
	if ( m_hFile == INVALID_HANDLE_VALUE ) return 0;

	return ::SetFilePointer( m_hFile, Offset, NULL, FILE_END );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFile::Seek( Sint32 Offset )
{
	if ( m_hFile == INVALID_HANDLE_VALUE ) return 0;

	return ::SetFilePointer( m_hFile, Offset, NULL, FILE_CURRENT );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFile::GetFilePosition( void )
{
	return CFile::Seek( 0 );
}	
