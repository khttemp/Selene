

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "System.h"
#include "Class/Common/File/CFileManager.h"
#include "Class/Common/File/CResourceFile.h"
#include "NullDevice/File/NullResourceFile.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace File;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFileManager::CFileManager()
{
	MemoryClear( m_CurrentDirectory, sizeof(m_CurrentDirectory) );
	MemoryClear( m_FileSearchTbl, sizeof(m_FileSearchTbl) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFileManager::~CFileManager()
{
	for ( Sint32 i = 0; i < FILE_SEARCH_MAX; i++ )
	{
		MemoryFree( m_FileSearchTbl[i].pList );
		SAFE_RELEASE( m_FileSearchTbl[i].pCrypt );
		SAFE_DELETE( m_FileSearchTbl[i].pFile );
	}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFileManager::ConvertFileName( char *pDst, const char *pSrc )
{
	while ( *pSrc != '\0' )
	{
		if ( Is2ByteChara( *pSrc ) )
		{
			*pDst++ = *pSrc++;
			*pDst++ = *pSrc++;
		}
		else
		{
			switch ( *pSrc )
			{
			case 'a':	*pDst = 'A';		break;
			case 'b':	*pDst = 'B';		break;
			case 'c':	*pDst = 'C';		break;
			case 'd':	*pDst = 'D';		break;
			case 'e':	*pDst = 'E';		break;
			case 'f':	*pDst = 'F';		break;
			case 'g':	*pDst = 'G';		break;
			case 'h':	*pDst = 'H';		break;
			case 'i':	*pDst = 'I';		break;
			case 'j':	*pDst = 'J';		break;
			case 'k':	*pDst = 'K';		break;
			case 'l':	*pDst = 'L';		break;
			case 'm':	*pDst = 'M';		break;
			case 'n':	*pDst = 'N';		break;
			case 'o':	*pDst = 'O';		break;
			case 'p':	*pDst = 'P';		break;
			case 'q':	*pDst = 'Q';		break;
			case 'r':	*pDst = 'R';		break;
			case 's':	*pDst = 'S';		break;
			case 't':	*pDst = 'T';		break;
			case 'u':	*pDst = 'U';		break;
			case 'v':	*pDst = 'V';		break;
			case 'w':	*pDst = 'W';		break;
			case 'x':	*pDst = 'X';		break;
			case 'y':	*pDst = 'Y';		break;
			case 'z':	*pDst = 'Z';		break;
			case '/':	*pDst = '\\';		break;
			default:	*pDst = *pSrc;		break;
			}

			pSrc++;
			pDst++;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CFileManager::Load( const char *pFile, void **ppData, Sint32 *pSize )
{
	char DataPath[MAX_PATH] = "";

	//-----------------------------------------------------------
	// プライオリティごとの処理
	//-----------------------------------------------------------
	for ( Sint32 i = 0; i < FILE_SEARCH_MAX; i++ )
	{
		//----------------------------------------------------
		// ディレクトリから読み込み
		//----------------------------------------------------
		StringCbPrintf( DataPath, sizeof(DataPath),"%s%s%s", m_FileSearchTbl[i].FileRootPath, m_CurrentDirectory, pFile );
		// ディレクトリから
		if ( LoadFromFile( DataPath, ppData, pSize ) )
		{
			return true;
		}

		//----------------------------------------------------
		// パックファイルから
		//----------------------------------------------------
		StringCbPrintf( DataPath, sizeof(DataPath), "%s%s", m_CurrentDirectory, pFile );
		if ( LoadFromPack( DataPath, i, ppData, pSize ) )
		{
			return true;
		}
	}

	//-----------------------------------------------------------
	// 直接読み込み
	//-----------------------------------------------------------
	if ( LoadFromFile( pFile, ppData, pSize ) )
	{
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFileManager::Free( void *pData )
{
	MemoryFree( pData );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CFileManager::LoadFromFile( const char *pFile, void **ppData, Sint32 *pSize )
{
	//---------------------------------------------------
	// ファイルオープン
	//---------------------------------------------------
	CFile File( pFile, FILE_OPEN_TYPE_READ );
	if ( !File.IsOpened() ) return false;

	//---------------------------------------------------
	// データ展開領域チェック
	//---------------------------------------------------
	if ( ppData == NULL ) return true;

	//---------------------------------------------------
	// ファイルサイズ取得
	//---------------------------------------------------
	(*pSize) = File.GetFileSize();

	//---------------------------------------------------
	// メモリ確保
	//---------------------------------------------------
	(*ppData) = MemoryAlloc( (*pSize) );

	//---------------------------------------------------
	// ファイル読み込み
	//---------------------------------------------------
	File.Read( *ppData, *pSize );

	return true;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CFileManager::LoadFromPack( const char *pFile, Sint32 Priority, void **ppData, Sint32 *pSize )
{
	Bool bRet = false;

	Sint32 Address;
	Sint32 Size;
	Uint32 Crc;
	Bool IsCrypt;
	char FileName[MAX_PATH] = "";

	SFileSearchTable &List = m_FileSearchTbl[Priority];

	//-----------------------------------------------------------
	// ファイルチェック
	//-----------------------------------------------------------
	if ( List.pFile == NULL )
	{
		goto EXIT;
	}

	//-----------------------------------------------------------
	// 小文字は大文字にしつつコピー
	//-----------------------------------------------------------
	ConvertFileName( FileName, pFile );

	//-----------------------------------------------------------
	// 該当ファイル検索
	//-----------------------------------------------------------
	if ( !GetFileAddress( FileName, List.pList, List.ListCount, Address, Size, Crc, IsCrypt ) )
	{
		goto EXIT;
	}

	//-----------------------------------------------------------
	// データ展開領域チェック
	//-----------------------------------------------------------
	if ( ppData == NULL )
	{
		bRet = true;
		goto EXIT;
	}

	//-----------------------------------------------------------
	// 該当アドレスまで移動
	//-----------------------------------------------------------
	List.pFile->SeekStart( Address );

	//-----------------------------------------------------------
	// サイズコピー
	//-----------------------------------------------------------
	(*pSize) = Size;

	//-----------------------------------------------------------
	// サイズ分のメモリ確保
	//-----------------------------------------------------------
	(*ppData) = MemoryAlloc( (*pSize) );

	//-----------------------------------------------------------
	// 読み込み
	//-----------------------------------------------------------
	List.pFile->Read( *ppData, *pSize );

	//-----------------------------------------------------------
	// 複合化
	//-----------------------------------------------------------
	if ( (List.pCrypt != NULL) && IsCrypt )
	{
		List.pCrypt->Decrypt( (Uint8*)(*ppData), (Uint8*)(*ppData), *pSize, 0 );
	}

	bRet = true;

EXIT:
	return bRet;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IResourceFile *CFileManager::FileOpen( const char *pFile )
{
	CResourceFile *pFileData = NULL;
	char DataPath[MAX_PATH] = "";

	//-----------------------------------------------------------
	// プライオリティごと
	//-----------------------------------------------------------
	for ( Sint32 i = 0; i < FILE_SEARCH_MAX; i++ )
	{
		//---------------------------------------------------
		// ディレクトリから読み込み
		//---------------------------------------------------
		StringCbPrintf( DataPath, sizeof(DataPath), "%s%s%s", m_FileSearchTbl[i].FileRootPath, m_CurrentDirectory, pFile );
		// ディレクトリから
		pFileData = FileOpenFromFile( DataPath );
		if ( pFileData != NULL ) return pFileData;

		//---------------------------------------------------
		// パックファイルから
		//---------------------------------------------------
		StringCbPrintf( DataPath, sizeof(DataPath), "%s%s", m_CurrentDirectory, pFile );
		pFileData = FileOpenFromPack( DataPath, i );
		if ( pFileData != NULL ) return pFileData;
	}

	//---------------------------------------------------
	// 直接読み込み
	//---------------------------------------------------
	pFileData = FileOpenFromFile( pFile );
	if ( pFileData != NULL ) return pFileData;

	//---------------------------------------------------
	// ダメでした
	//---------------------------------------------------
	static NullResourceFile Dummy;
	return &Dummy;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CResourceFile *CFileManager::FileOpenFromFile( const char *pFile )
{
	CResourceFile *pFD = NULL;

	//--------------------------------------------------------
	// ファイルオープン
	//--------------------------------------------------------
	pFD = new CResourceFile( pFile );
	if ( !pFD->IsOpened() )
	{
		SAFE_RELEASE( pFD );
		return NULL;
	}

	return pFD;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CResourceFile *CFileManager::FileOpenFromPack( const char *pFile, Sint32 Priority )
{
	CResourceFile *pFD = NULL;
	char FileName[MAX_PATH] = "";

	SFileSearchTable &List = m_FileSearchTbl[Priority];

	//-----------------------------------------------------------
	// 小文字は大文字にしつつコピー
	//-----------------------------------------------------------
	ConvertFileName( FileName, pFile );

	//-----------------------------------------------------------
	// ファイルオープン
	//-----------------------------------------------------------
	pFD = new CResourceFile( List.FilePackName );
	if ( !pFD->IsOpened() )
	{
		SAFE_RELEASE( pFD );
		return NULL;
	}

	//-----------------------------------------------------------
	// ヘッダ読み込み
	//-----------------------------------------------------------
	Sint32 Start, Size;
	Uint32 Crc;
	Bool IsCrypt;
	if ( !GetFileAddress( FileName, List.pList, List.ListCount, Start, Size, Crc, IsCrypt ) )
	{
		SAFE_RELEASE( pFD );
		return NULL;
	}

	pFD->SetStart( Start );
	pFD->SetSize( Size );
	pFD->SetCrypt( IsCrypt ? List.pCrypt : NULL );

	//-----------------------------------------------------------
	// 先頭位置にシーク
	//-----------------------------------------------------------
	pFD->SeekStart( 0 );

	return pFD;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CFileManager::GetCRC( const Uint8 Data[], Uint32 Size )
{
	Uint32 r = 0xFFFFFFFF;

	for ( Uint32 i = 0; i < Size; i++ )
	{
		r ^= (Uint32)Data[i];
		for ( Uint32 j = 0; j < 8; j++ )
		{
			if ( (r & 1) != 0 )
			{
				r = (r >> 1) ^ 0xEDB88320;
			}
			else
			{
				r >>= 1;
			}
		}
	}

	return r ^ 0xFFFFFFFF;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CFileManager::GetFileAddress( const char *pFile, SPackFileList *pList, Sint32 Count, Sint32 &Address, Sint32 &Size, Uint32 &Crc, Bool &IsCrypt )
{
	//------------------------------------------------------
	// 数チェック
	//------------------------------------------------------
	if ( Count == 0 ) return false;

	//------------------------------------------------------
	// ファイル名のCRCを取得
	//------------------------------------------------------
	Uint32 NameCrc = GetCRC( (Uint8*)pFile, (Uint32)strlen(pFile) );

	//------------------------------------------------------
	// ファイル検索
	//------------------------------------------------------
#if 1
	Sint32 Left  = 0;
	Sint32 Right = Count - 1;

	// おかしい？
	if ( NameCrc < pList[Left ].NameCrc ) return false;
	if ( NameCrc > pList[Right].NameCrc ) return false;

	// バイナリサーチ
	while ( Left <= Right )
	{
		Sint32 Middle = Left + (Right - Left + 1) / 2;
		if ( Right - Left < 8 )
		{
			for ( Sint32 i = Left; i <= Right; i++ )
			{
				if ( NameCrc == pList[i].NameCrc )
				{
					Address = pList[i].Address;
					Size    = pList[i].Size;
					Crc		= pList[i].DataCrc;
					IsCrypt	= pList[i].IsEncypt != 0;
					return true;
				}
			}
			return false;
		}
		ef ( NameCrc == pList[Middle].NameCrc )
		{
			Address = pList[Middle].Address;
			Size    = pList[Middle].Size;
			Crc     = pList[Middle].DataCrc;
			IsCrypt	= pList[Middle].IsEncypt != 0;
			return true;
		}
		ef ( NameCrc < pList[Middle].NameCrc )
		{
			Right = Middle;
		}
		ef ( NameCrc > pList[Middle].NameCrc )
		{
			Left = Middle;
		}
	}
#else
	// リニアサーチ
	for ( Sint32 i = 0; i < Count; i++ )
	{
		if ( NameCrc == pList[i].NameCrc )
		{
			if ( ::CompareString( LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, pList[i].FileName, -1, pFile, -1 ) == CSTR_EQUAL )
			{
				Address = pList[i].Address;
				Size    = pList[i].Size;
				Crc     = pList[i].DataCrc;
				IsCrypt	= pList[i].IsEncypt != 0;
				return true;
			}
		}
	}
#endif

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFileManager::SetCurrentPath( const char *pCurrentDir )
{
	MemoryClear( m_CurrentDirectory, sizeof(m_CurrentDirectory) );
	if ( (pCurrentDir != NULL) && (pCurrentDir[0] != '\0') )
	{
		ConvertFileName( m_CurrentDirectory, pCurrentDir );
		Sint32 Len = (Sint32)strlen( m_CurrentDirectory );

		if ( m_CurrentDirectory[Len-1] != '\\' )
		{
			m_CurrentDirectory[Len] = '\\';
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFileManager::SetRootPath( Sint32 Priority, const char *pRootPath, const char *pPassword )
{
	SFileSearchTable &Tbl = m_FileSearchTbl[Priority];

	// 通常ディレクトリ
	MemoryClear( Tbl.FileRootPath, sizeof(Tbl.FileRootPath) );
	if ( (pRootPath != NULL) && (pRootPath[0] != '\0') )
	{
		ConvertFileName( Tbl.FileRootPath, pRootPath );
		Sint32 Len = (Sint32)strlen( Tbl.FileRootPath );

		if ( Tbl.FileRootPath[Len-1] != '\\' )
		{
			Tbl.FileRootPath[Len] = '\\';
		}
	}

	// パックファイル
	MemoryClear( Tbl.FilePackName, sizeof(Tbl.FilePackName) );
	if ( (pRootPath != NULL) && (pRootPath[0] != '\0') )
	{
		ConvertFileName( Tbl.FilePackName, pRootPath );
		StringCbCat( Tbl.FilePackName, sizeof(Tbl.FilePackName), ".PACK" );
	}

	MemoryFree( Tbl.pList );
	SAFE_DELETE( Tbl.pFile );
	SAFE_RELEASE( Tbl.pCrypt );

	// ファイルオープン
	Tbl.pFile = new CFile( Tbl.FilePackName, FILE_OPEN_TYPE_READ );
	if ( !Tbl.pFile->IsOpened() )
	{
		SAFE_DELETE( Tbl.pFile );
		return;
	}

	// ファイルチェック
	SPackFileHeader Head;
	Tbl.pFile->Read( &Head, sizeof(SPackFileHeader) );
	if ( Head.Guid != 'PACK' )
	{
		SAFE_DELETE( Tbl.pFile );
		return;
	}

	// ヘッダチェック
	if ( Head.FileCount == 0 )
	{
		SAFE_DELETE( Tbl.pFile );
		return;
	}

	// ヘッダ読み込み
	Tbl.ListCount = Head.FileCount;
	Tbl.pList = (SPackFileList*)MemoryAlloc( sizeof(SPackFileList) * Tbl.ListCount );
	Tbl.pFile->Read( Tbl.pList, sizeof(SPackFileList) * Tbl.ListCount );
	Tbl.pCrypt = (pPassword == NULL) ? NULL : GetCryptInterface( pPassword );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CFileManager::GetFilePath( char *pFilePath, Sint32 FilePathSize, const char *pSrcFile )
{
	char DataPath[MAX_PATH] = "";

	//-----------------------------------------------------------
	// プライオリティごとの処理
	//-----------------------------------------------------------
	for ( Sint32 i = 0; i < FILE_SEARCH_MAX; i++ )
	{
		//------------------------------------------------
		// ディレクトリから読み込み
		//------------------------------------------------
		StringCbPrintf( DataPath, sizeof(DataPath), "%s%s%s", m_FileSearchTbl[i].FileRootPath, m_CurrentDirectory, pSrcFile );
		// ディレクトリから
		if ( LoadFromFile( DataPath, NULL, NULL ) )
		{
			StringCbCopy( pFilePath, FilePathSize, DataPath );
			return true;
		}

		//------------------------------------------------
		// パックファイルから
		//------------------------------------------------
		StringCbPrintf( DataPath, sizeof(DataPath), "%s%s", m_CurrentDirectory, pSrcFile );
		if ( LoadFromPack( DataPath, i, NULL, NULL ) )
		{
			StringCbCopy( pFilePath, FilePathSize, DataPath );
			return true;
		}
	}

	//-----------------------------------------------------------
	// 直接読み込み
	//-----------------------------------------------------------
	StringCbPrintf( DataPath, sizeof(DataPath), "%s", pSrcFile );
	if ( LoadFromFile( DataPath, NULL, NULL ) )
	{
		StringCbCopy( pFilePath, FilePathSize, DataPath );
		return true;
	}

	return false;
}


