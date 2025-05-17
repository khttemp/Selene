

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

	// �t�@�C���̌��݈ʒu���擾
	Sint32 Pos = GetFilePosition();

	// ���ۂɏ�������o�C�g��
	ReadByte = Size;
	if ( ReadByte > m_Size - Pos )
	{
		ReadByte = m_Size - Pos;
	}

	// �t�@�C���ǂݍ���
	Sint32 Read = CFile::Read( pData, ReadByte );

	// ������
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
	// �t�@�C���̌��݈ʒu���擾
	Sint32 Pos = m_Start + Offset;

	// �ʒu���s�����`�F�b�N
	if ( Pos < m_Start ) return 0;
	if ( Pos > m_Start + m_Size ) return 0;

	// �t�@�C���ʒu�ݒ�
	CFile::SeekStart( Pos );

	return Pos - m_Start;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CResourceFile::SeekEnd( Sint32 Offset )
{
	// �t�@�C���̌��݈ʒu���擾
	Sint32 Pos = m_Start + m_Size + Offset;

	// �ʒu���s�����`�F�b�N
	if ( Pos < m_Start ) return 0;
	if ( Pos > m_Start + m_Size ) return 0;

	// �t�@�C���ʒu�ݒ�
	CFile::SeekStart( Pos );

	return Pos - m_Start;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CResourceFile::Seek( Sint32 Offset )
{
	// �t�@�C���̌��݈ʒu���擾
	Sint32 Pos = m_Start + GetFilePosition() + Offset;

	// �ʒu���s�����`�F�b�N
	if ( Pos < m_Start ) return 0;
	if ( Pos > m_Start + m_Size ) return 0;

	// �t�@�C���ʒu�ݒ�
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

