#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
#define STRUCT_OFFSET(type,field)			((Uint16)(&((type*)0x00000000)->field))


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	void MBtoWC( const char In[], wchar_t Out[], Sint32 Size );
	void WCtoMB( const wchar_t In[], char Out[], Sint32 Size );

	void GetExePath( char *pPath, Sint32 Size );

	Uint16 GetCharaCode( const char *pStr );

	char *GetSocketError( Sint32 ErrorCode, char *pErrStr = NULL, Sint32 ErrStrSize = 0 );

	void *MemoryAlloc( Sint32 Size );
	void *MemoryClearAlloc( Sint32 Size );
	void MemoryFree( void *pMem );

	void Log_Initialize( const char *pDir );
	void Log_Finalize( void );
	void Log_Print( Sint32 Color, const char *pStr,... );
	void Log_PrintStrong( Sint32 Color, const char *pStr,... );
	void Log_PrintLine( Sint32 Color, const char *pStr,... );
	void Log_PrintStrongLine( Sint32 Color, const char *pStr,... );
	void Log_PrintTable( Sint32 Width, const char *pTitle, const char *pStr,... );
	void Log_PrintTable( Sint32 ColorTitle, Sint32 Color, const char *pTitle, const char *pKind, const char *pStr,... );
	void Log_PrintCellTitle( Sint32 Color, const char *pTitle );
	void Log_PrintCellKind( const char *pKind,... );
	void Log_TableBegin( void );
	void Log_TableEnd( void );
	void Log_TableLine( Sint32 Bold );
	void Log_CellBegin( Sint32 Width );
	void Log_CellEnd( void );

	void GetLongFullPathName( const char *pSrcPath, char *pDstPath, Sint32 DstPathSize );
	Bool GetDesktopDirectory( char *pPath, Sint32 PathSize );
}

