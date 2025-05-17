

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/File/CFileHtmlLog.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace File;


//-----------------------------------------------------------------------------------
// VARIABLE
//-----------------------------------------------------------------------------------
static const char g_HtmlHeadStart[] = {
	"<HTML>\r\n"
	"<HEAD>\r\n"
	"<TITLE>%s</TITLE>\r\n"
	"<META http-equiv=\"Content-Type\" content=\"text/html\">\r\n"
	"<STYLE type=\"text/css\">\r\n"
	"<!--\r\n"
	"BODY{\r\n"
	"  font-size : 12px;\r\n"
	"  font-family : \"‚l‚r ƒSƒVƒbƒN\";\r\n"
	"  font-weight : normal;\r\n"
	"}\r\n"
	"TABLE{\r\n"
	"  font-size : 12px;\r\n"
	"  font-family : \"‚l‚r ƒSƒVƒbƒN\";\r\n"
	"  font-weight : normal;\r\n"
	"}\r\n"
	"-->\r\n"
	"</STYLE>\r\n"
	"</HEAD>\r\n"
	"<BODY text=\"#000000\" bgcolor=\"#FFFFFF\">\r\n"
};

static const char g_HtmlHeadEnd[] = {
	"</BODY>\r\n"
	"</HTML>\r\n"
};


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFileHtmlLog::CFileHtmlLog( const char *pFileName, const char *pTitle ) : CFile( pFileName, FILE_OPEN_TYPE_WRITE )
{
	Thread::CAutoLock Lock( m_CS );

	char Buff[1024] = "";
	size_t Len;

	StringCbPrintf( Buff, sizeof(Buff), g_HtmlHeadStart, pTitle );
	Len = strlen( Buff );
	Write( (const void*)Buff, (Sint32)Len );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFileHtmlLog::~CFileHtmlLog()
{
	Thread::CAutoLock Lock( m_CS );

	Write( (const void*)g_HtmlHeadEnd, sizeof(g_HtmlHeadEnd) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFileHtmlLog::Print( Sint32 Color, const char *pStr,... )
{
	Thread::CAutoLock Lock( m_CS );

	char Buff[128] = "";
	char InBuff[64] = "";

	StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );

	static char In[] = "<FONT COLOR=\"#%06X\">";
	static char Out[] = "</FONT>";

	StringCbPrintf( InBuff, sizeof(InBuff), In, Color );

	Sint32 WriteBytes = 0;
	if ( Color != 0x000000 )
	{
		WriteBytes += Write( (const void*)InBuff, (Sint32)strlen(InBuff) );
		WriteBytes += Write( (const void*)Buff, (Sint32)strlen(Buff) );
		WriteBytes += Write( (const void*)Out, (Sint32)strlen(Out) );
	}
	else
	{
		WriteBytes += Write( (const void*)Buff, (Sint32)strlen(Buff) );
	}
	return WriteBytes;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFileHtmlLog::PrintStrong( Sint32 Color, const char *pStr,... )
{
	Thread::CAutoLock Lock( m_CS );

	char Buff[128] = "";
	char Str[128] = "";
	char InBuff[64] = "";

	StringCbPrintf( Str, sizeof(Str), "<B>%s</B>", pStr );
	StringCbVPrintf( Buff, sizeof(Buff), Str, (char*)(&pStr + 1) );

	static char In[] = "<FONT COLOR=\"#%06X\">";
	static char Out[] = "</FONT>\r\n";

	StringCbPrintf( InBuff, sizeof(InBuff), In, Color );

	Sint32 WriteBytes = 0;
	if ( Color != 0x000000 )
	{
		WriteBytes += Write( (const void*)InBuff, (Sint32)strlen(InBuff) );
		WriteBytes += Write( (const void*)Buff, (Sint32)strlen(Buff) );
		WriteBytes += Write( (const void*)Out, (Sint32)strlen(Out) );
	}
	else
	{
		WriteBytes += Write( (const void*)Buff, (Sint32)strlen(Buff) );
	}
	return WriteBytes;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFileHtmlLog::PrintLine( Sint32 Color, const char *pStr,... )
{
	Thread::CAutoLock Lock( m_CS );

	char Buff[128] = "";

	StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );

	Sint32 WriteBytes = 0;
	WriteBytes += Print( Color, Buff );
	WriteBytes += Print( 0x000000, "<BR>\r\n" );
	return WriteBytes;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFileHtmlLog::PrintStrongLine( Sint32 Color, const char *pStr,... )
{
	char Buff[128] = "";

	StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );

	Sint32 WriteBytes = 0;
	WriteBytes += PrintStrong( Color, Buff );
	WriteBytes += Print( 0x000000, "<BR>\r\n" );
	return WriteBytes;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFileHtmlLog::TableBegin( void )
{
	Thread::CAutoLock Lock( m_CS );

	static const char Table[] = {
		"<TABLE width=\"100%\">\r\n"
		"  <TBODY>\r\n"
		"    <TR>\r\n"
	};

	return Write( (const void*)Table, (Sint32)strlen(Table) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFileHtmlLog::TableEnd( void )
{
	Thread::CAutoLock Lock( m_CS );

	static const char Table[] = {
		"    </TR>\r\n"
		"  </TBODY>\r\n"
		"</TABLE>\r\n"
	};

	return Write( (const void*)Table, (Sint32)strlen(Table) );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFileHtmlLog::CellBegin( Sint32 Width )
{
	Thread::CAutoLock Lock( m_CS );

	static const char Table1[] = {
		"<TD width=\"%d\" valign=\"top\">\r\n"
	};

	static const char Table2[] = {
		"<TD width=\"%d\" valign=\"top\">\r\n"
	};

	char Buff[64] = "";
	StringCbPrintf( Buff, sizeof(Buff), (Width == 0) ? Table2 : Table1, Width );

	return Write( (const void*)Buff, (Sint32)strlen(Buff) );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFileHtmlLog::CellEnd( void )
{
	Thread::CAutoLock Lock( m_CS );

	static const char Table[] = {
		"</TD>\r\n"
	};

	return Write( (const void*)Table, (Sint32)strlen(Table) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFileHtmlLog::TableLine( Sint32 Bold )
{
	Thread::CAutoLock Lock( m_CS );

	static const char Table[] = {
		"<TABLE width=\"100%%\">\r\n"
		"  <TR>\r\n"
		"    <TD height=\"%d\" bgcolor=\"#000000\"></TD>\r\n"
		"  </TR>\r\n"
		"</TABLE>\r\n"
	};

	char Buff[128] = "";
	StringCbPrintf( Buff, sizeof(Buff), Table, Bold );

	size_t Len = strlen( Buff );
	return Write( (const void*)Buff, (Sint32)Len );
}

