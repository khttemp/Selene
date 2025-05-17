#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/File/CFile.h"
#include "Thread/CriticalSection.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace File
{
	/**
		@brief HTMLログ用ファイル操作
		@author 葉迩倭
	*/
	class SELENE_DLL_API CFileHtmlLog : public CFile
	{
	private:
		Thread::CCriticalSection m_CS;

	public:
		CFileHtmlLog( const char *pFileName, const char *pTitle );
		virtual ~CFileHtmlLog();

		virtual Sint32 Print( Sint32 Color, const char *pStr,... );
		virtual Sint32 PrintStrong( Sint32 Color, const char *pStr,... );
		virtual Sint32 PrintLine( Sint32 Color, const char *pStr,... );
		virtual Sint32 PrintStrongLine( Sint32 Color, const char *pStr,... );

		virtual Sint32 TableBegin( void );
		virtual Sint32 TableEnd( void );
		virtual Sint32 TableLine( Sint32 Bold );

		virtual Sint32 CellBegin( Sint32 Width );
		virtual Sint32 CellEnd( void );
	};
}
}


