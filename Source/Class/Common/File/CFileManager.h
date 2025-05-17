#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/ClassReference.h"
#include "Class/Common/Object/CBaseObject.h"
#include "Interface/File/IFileManager.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace File
{
	#define FILE_SEARCH_MAX		(16)

	struct SPackFileList
	{
		char FileName[64];
		Uint32 NameCrc;
		Uint32 DataCrc;
		Uint32 Address;
		Uint32 Size;
		Uint32 IsEncypt;
	};

	struct SPackFileHeader
	{
		Uint32 Guid;
		Uint32 FileCount;
	};

	struct SFileSearchTable
	{
		char FileRootPath[MAX_PATH];
		char FilePackName[MAX_PATH];

		SPackFileList *pList;
		Uint32 ListCount;
		CFile *pFile;
		ICrypt *pCrypt;
	};

	class CFileManager : public CBaseObject, public IFileManager
	{
	protected:
		char m_CurrentDirectory[MAX_PATH];
		SFileSearchTable m_FileSearchTbl[FILE_SEARCH_MAX];

	protected:
		virtual Bool GetFileAddress( const char *pFile, SPackFileList *pList, Sint32 Count, Sint32 &Address, Sint32 &Size, Uint32 &Crc, Bool &IsCrypt );
		virtual Uint32 GetCRC( const Uint8 Data[], Uint32 Size );
		virtual Bool LoadFromFile( const char *pFile, void **ppData, Sint32 *pSize );
		virtual Bool LoadFromPack( const char *pFile, Sint32 Priority, void **ppData, Sint32 *pSize );
		virtual CResourceFile *FileOpenFromFile( const char *pFile );
		virtual CResourceFile *FileOpenFromPack( const char *pFile, Sint32 Priority );

		virtual void ConvertFileName( char *pDst, const char *pSrc );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CFileManager();
		virtual ~CFileManager();

		virtual void SetCurrentPath( const char *pCurrentDir );
		virtual void SetRootPath( Sint32 Priority, const char *pRootPath, const char *pPassword = NULL );

		virtual Bool GetFilePath( char *pFilePath, Sint32 FilePathSize, const char *pSrcFile );

		virtual Bool Load( const char *pFile, void **ppData, Sint32 *pSize );
		virtual void Free( void *pData );
		virtual IResourceFile *FileOpen( const char *pFile );
	};
}
}

