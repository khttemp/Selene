

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/File/CFileHtmlLog.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
static const char VERSION_STRING[] = "Selene/Lue - Beta 1.0.3 - 2008.04.09";


//-----------------------------------------------------------------------------------
// VARIABLE
//-----------------------------------------------------------------------------------
static File::CFileHtmlLog *g_pHtmlLogFile;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::MBtoWC( const char In[], wchar_t Out[], Sint32 Size )
{
	::MultiByteToWideChar( CP_ACP, 0, In, -1, Out, Size );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::WCtoMB( const wchar_t In[], char Out[], Sint32 Size )
{
	::WideCharToMultiByte( CP_ACP, 0, In, -1, Out, Size, NULL, NULL );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::GetExePath( char *pPath, Sint32 Size )
{
	MemoryClear( pPath, Size );

	::GetModuleFileName( ::GetModuleHandle( NULL ), pPath, Size );
	Sint32 Len = (Sint32)strlen( pPath );

	while ( pPath[Len] != '\\' )
	{
		pPath[Len] = '\0';
		if ( --Len < 0 ) break;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint16 Selene::GetCharaCode( const char *pStr )
{
	const unsigned char *pSrc = (const unsigned char*)pStr;

	if ( Is2ByteChara( pSrc[0] ) )
	{
		return (pSrc[0] << 8) | pSrc[1];
	}
	else
	{
		return pSrc[0];
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
char *Selene::GetSocketError( Sint32 ErrorCode, char *pErrStr, Sint32 ErrStrSize )
{
	static char String[128] = "";

	switch ( ErrorCode )
	{
	case WSABASEERR:				StringCbCopy( String, sizeof(String), "�G���[�͔������Ă��Ȃ�" );								break;
	case WSAEINTR:					StringCbCopy( String, sizeof(String), "�֐��Ăяo�������f���ꂽ" );								break;
	case WSAEBADF:					StringCbCopy( String, sizeof(String), "�����ȃt�@�C���n���h��" );								break;
	case WSAEACCES:					StringCbCopy( String, sizeof(String), "�A�N�Z�X�����ۂ��ꂽ" );									break;
	case WSAEFAULT:					StringCbCopy( String, sizeof(String), "�����ȃo�b�t�@�A�h���X" );								break;
	case WSAEINVAL:					StringCbCopy( String, sizeof(String), "�����Ȉ������n���ꂽ" );									break;
	case WSAEMFILE:					StringCbCopy( String, sizeof(String), "�g�p���̃\�P�b�g�̐�����������" );						break;
	case WSAEWOULDBLOCK:			StringCbCopy( String, sizeof(String), "����̓u���b�L���O�����" );								break;
	case WSAEINPROGRESS:			StringCbCopy( String, sizeof(String), "���łɃu���b�L���O�葱�������s����Ă���" );				break;
	case WSAEALREADY:				StringCbCopy( String, sizeof(String), "�v�����ꂽ����͊��Ɏ��s���A�܂��͎��s�ς�" );			break;
	case WSAENOTSOCK:				StringCbCopy( String, sizeof(String), "�w�肳�ꂽ�\�P�b�g�������ł���" );						break;
	case WSAEDESTADDRREQ:			StringCbCopy( String, sizeof(String), "����̎��s�ɑ��M��A�h���X���K�v" );						break;
	case WSAEMSGSIZE:				StringCbCopy( String, sizeof(String), "���b�Z�[�W�T�C�Y���傫������" );							break;
	case WSAEPROTOTYPE:				StringCbCopy( String, sizeof(String), "�\�P�b�g�͗v�����ꂽ�v���g�R���ɓK�����Ă��Ȃ�" );		break;
	case WSAENOPROTOOPT:			StringCbCopy( String, sizeof(String), "�s���ȃv���g�R���I�v�V����" );							break;
	case WSAEPROTONOSUPPORT:		StringCbCopy( String, sizeof(String), "�v���g�R�����T�|�[�g����Ă��Ȃ�" );						break;
	case WSAESOCKTNOSUPPORT:		StringCbCopy( String, sizeof(String), "�w�肳�ꂽ�\�P�b�g�^�C�v�̓T�|�[�g����Ă��Ȃ�" );		break;
	case WSAEOPNOTSUPP:				StringCbCopy( String, sizeof(String), "�v�����ꂽ����̓T�|�[�g����Ă��Ȃ�" );					break;
	case WSAEPFNOSUPPORT:			StringCbCopy( String, sizeof(String), "�v���g�R���t�@�~�����T�|�[�g����Ă��Ȃ�" );				break;
	case WSAEAFNOSUPPORT:			StringCbCopy( String, sizeof(String), "�A�h���X�t�@�~�����T�|�[�g����Ă��Ȃ�" );				break;
	case WSAEADDRINUSE:				StringCbCopy( String, sizeof(String), "�A�h���X�͊��Ɏg�p���ł���" );							break;
	case WSAEADDRNOTAVAIL:			StringCbCopy( String, sizeof(String), "�����ȃl�b�g���[�N�A�h���X" );							break;
	case WSAENETDOWN:				StringCbCopy( String, sizeof(String), "�l�b�g���[�N���_�E�����Ă���" );							break;
	case WSAENETUNREACH:			StringCbCopy( String, sizeof(String), "�w�肳�ꂽ�l�b�g���[�N�z�X�g�ɓ��B�ł��Ȃ�" );			break;
	case WSAENETRESET:				StringCbCopy( String, sizeof(String), "�l�b�g���[�N�ڑ����j�����ꂽ" );							break;
	case WSAECONNABORTED:			StringCbCopy( String, sizeof(String), "�l�b�g���[�N�ڑ����j�����ꂽ" );							break;
	case WSAECONNRESET:				StringCbCopy( String, sizeof(String), "�l�b�g���[�N�ڑ�������ɂ���Ĕj�����ꂽ" );				break;
	case WSAENOBUFS:				StringCbCopy( String, sizeof(String), "�o�b�t�@���s�����Ă���" );								break;
	case WSAEISCONN:				StringCbCopy( String, sizeof(String), "�\�P�b�g�͊��ɐڑ�����Ă���" );							break;
	case WSAENOTCONN:				StringCbCopy( String, sizeof(String), "�\�P�b�g�͐ڑ�����Ă��Ȃ�" );							break;
	case WSAESHUTDOWN:				StringCbCopy( String, sizeof(String), "�\�P�b�g�̓V���b�g�_�E������Ă���" );					break;
	case WSAETOOMANYREFS:			StringCbCopy( String, sizeof(String), "�Q�Ƃ̐�����������" );									break;
	case WSAETIMEDOUT:				StringCbCopy( String, sizeof(String), "�ڑ��v�����^�C���A�E�g����" );							break;
	case WSAECONNREFUSED:			StringCbCopy( String, sizeof(String), "�ڑ������ۂ��ꂽ" );										break;
	case WSAELOOP:					StringCbCopy( String, sizeof(String), "���[�v" );												break;
	case WSAENAMETOOLONG:			StringCbCopy( String, sizeof(String), "���O����������" );										break;
	case WSAEHOSTDOWN:				StringCbCopy( String, sizeof(String), "�z�X�g���_�E�����Ă���" );								break;
	case WSAEHOSTUNREACH:			StringCbCopy( String, sizeof(String), "�z�X�g�ւ̌o�H���Ȃ�" );									break;
	case WSAENOTEMPTY:				StringCbCopy( String, sizeof(String), "�f�B���N�g������ł͂Ȃ�" );								break;
	case WSAEPROCLIM:				StringCbCopy( String, sizeof(String), "�v���Z�X�̐�����������" );								break;
	case WSAEUSERS:					StringCbCopy( String, sizeof(String), "���[�U�̐�����������" );									break;
	case WSAEDQUOT:					StringCbCopy( String, sizeof(String), "�f�B�X�N�N�H�[�^" );										break;
	case WSAESTALE:					StringCbCopy( String, sizeof(String), "���s���悤�Ƃ�������͔p�~����Ă���" );					break;
	case WSAEREMOTE:				StringCbCopy( String, sizeof(String), "�����[�g" );												break;
	case WSASYSNOTREADY:			StringCbCopy( String, sizeof(String), "�l�b�g���[�N�T�u�V�X�e�������p�ł��Ȃ�" );				break;
	case WSAVERNOTSUPPORTED:		StringCbCopy( String, sizeof(String), "Winsock.dll�̃o�[�W�������͈͊O�ł���" );				break;
	case WSANOTINITIALISED:			StringCbCopy( String, sizeof(String), "WinSock�V�X�e��������������Ă��Ȃ�" );					break;
	case WSAEDISCON:				StringCbCopy( String, sizeof(String), "�V���b�g�_�E��������" );									break;
	case WSAENOMORE:				StringCbCopy( String, sizeof(String), "�f�[�^�͂���ȏ㑶�݂��Ȃ�" );							break;
	case WSAECANCELLED:				StringCbCopy( String, sizeof(String), "����͎������ꂽ" );									break;
	case WSAEINVALIDPROCTABLE:		StringCbCopy( String, sizeof(String), "�T�[�r�X�v���o�C�_�̊֐��e�[�u��������" );				break;
	case WSAEINVALIDPROVIDER:		StringCbCopy( String, sizeof(String), "�T�[�r�X�v���o�C�_������" );								break;
	case WSAEPROVIDERFAILEDINIT:	StringCbCopy( String, sizeof(String), "�T�[�r�X�v���o�C�_�̏������Ɏ��s����" );					break;
	case WSASYSCALLFAILURE:			StringCbCopy( String, sizeof(String), "�V�X�e���R�[���Ɏ��s����" );								break;
	case WSASERVICE_NOT_FOUND:		StringCbCopy( String, sizeof(String), "�T�[�r�X��������Ȃ�" );								break;
	case WSATYPE_NOT_FOUND:			StringCbCopy( String, sizeof(String), "�^�C�v��������Ȃ�" );									break;
	case WSA_E_CANCELLED:			StringCbCopy( String, sizeof(String), "�������L�����Z�����ꂽ" );								break;
	case WSAEREFUSED:				StringCbCopy( String, sizeof(String), "����͋��ۂ��ꂽ" );										break;
	case WSAHOST_NOT_FOUND:			StringCbCopy( String, sizeof(String), "�z�X�g��������Ȃ�" );									break;
	case WSATRY_AGAIN:				StringCbCopy( String, sizeof(String), "�w�肳�ꂽ�z�X�g��������Ȃ��A�܂��̓T�[�r�X�ُ̈�" );	break;
	case WSANO_RECOVERY:			StringCbCopy( String, sizeof(String), "�񕜕s�\�ȃG���[����������" );							break;
	case WSANO_DATA:				StringCbCopy( String, sizeof(String), "�v�����ꂽ�^�C�v�̃f�[�^���R�[�h��������Ȃ�" );		break;
	}

	if ( pErrStr != NULL ) StringCbCopy( pErrStr, ErrStrSize, String );

	return String;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void *Selene::MemoryAlloc( Sint32 Size )
{
	return ::HeapAlloc( ::GetProcessHeap(), HEAP_CREATE_ALIGN_16, Size );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void *Selene::MemoryClearAlloc( Sint32 Size )
{
	return ::HeapAlloc( ::GetProcessHeap(), HEAP_CREATE_ALIGN_16|HEAP_ZERO_MEMORY, Size );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::MemoryFree( void *pMem )
{
	if ( pMem != NULL )
	{
		::HeapFree( ::GetProcessHeap(), 0, pMem );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_Initialize( const char *pDir )
{
	char LogFile[MAX_PATH];
	StringCbPrintf( LogFile, sizeof(LogFile), "%sLog.html", pDir );

	g_pHtmlLogFile = new File::CFileHtmlLog( LogFile, VERSION_STRING );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_Finalize( void )
{
	SAFE_DELETE( g_pHtmlLogFile );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_Print( Sint32 Color, const char *pStr,... )
{
	if ( g_pHtmlLogFile == NULL ) return;

	char Buff[256] = "";
	StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );
	g_pHtmlLogFile->Print( Color, Buff );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintStrong( Sint32 Color, const char *pStr,... )
{
	if ( g_pHtmlLogFile == NULL ) return;

	char Buff[256] = "";
	StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );
	g_pHtmlLogFile->PrintStrong( Color, Buff );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintLine( Sint32 Color, const char *pStr,... )
{
	if ( g_pHtmlLogFile == NULL ) return;

	char Buff[256] = "";
	StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );
	g_pHtmlLogFile->PrintLine( Color, Buff );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintStrongLine( Sint32 Color, const char *pStr,... )
{
	if ( g_pHtmlLogFile == NULL ) return;

	char Buff[256] = "";
	StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );
	g_pHtmlLogFile->PrintStrongLine( Color, Buff );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintTable( Sint32 ColorTitle, Sint32 Color, const char *pTitle, const char *pKind, const char *pStr,... )
{
	char Buff[256] = "";
	StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );

	Log_TableBegin();
	Log_PrintCellTitle( ColorTitle, pTitle );
	Log_PrintCellKind( pKind );
	Log_CellBegin( 0 );
	Log_Print( Color, Buff );
	Log_CellEnd();
	Log_TableEnd();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintTable( Sint32 Width, const char *pTitle, const char *pStr,... )
{
	char Buff[256] = "";
	StringCbVPrintf( Buff, sizeof(Buff), pStr, (char*)(&pStr + 1) );

	Log_TableBegin();
	Log_CellBegin( Width );
	Log_PrintLine( 0x000000, pTitle );
	Log_CellEnd();
	Log_CellBegin( 0 );
	Log_PrintLine( 0x000000, Buff );
	Log_CellEnd();
	Log_TableEnd();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintCellTitle( Sint32 Color, const char *pTitle )
{
	Log_CellBegin( 64 );
	Log_PrintStrong( Color, pTitle );
	Log_CellEnd();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_PrintCellKind( const char *pKind,... )
{
	char Buff[256] = "";
	StringCbPrintf( Buff, sizeof(Buff), pKind, (char*)(&pKind+ 1) );

	Log_CellBegin( 192 );
	Log_Print( 0x000000, Buff );
	Log_CellEnd();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_TableBegin( void )
{
	if ( g_pHtmlLogFile == NULL ) return;
	g_pHtmlLogFile->TableBegin();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_TableEnd( void )
{
	if ( g_pHtmlLogFile == NULL ) return;
	g_pHtmlLogFile->TableEnd();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_TableLine( Sint32 Bold )
{
	if ( g_pHtmlLogFile == NULL ) return;
	g_pHtmlLogFile->TableLine( Bold );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_CellBegin( Sint32 Width )
{
	if ( g_pHtmlLogFile == NULL ) return;
	g_pHtmlLogFile->CellBegin( Width );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::Log_CellEnd( void )
{
	if ( g_pHtmlLogFile == NULL ) return;
	g_pHtmlLogFile->CellEnd();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::GetDesktopDirectory( char *pPath, Sint32 PathSize )
{
	pPath[0] = '\0';

	ITEMIDLIST *pidl = NULL;
	IMalloc *pMalloc = NULL;
	char Temp[MAX_PATH] = "";

	if FAILED( ::SHGetMalloc( &pMalloc ) ) return false;

	::SHGetSpecialFolderLocation( ::GetDesktopWindow(), CSIDL_DESKTOP, &pidl );
	::SHGetPathFromIDList( pidl, Temp );

	pMalloc->Free( pidl );
	SAFE_RELEASE( pMalloc );

	StringCbCopy( pPath, PathSize, Temp );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void Selene::GetLongFullPathName( const char *pSrcPath, char *pDstPath, Sint32 DstPathSize )
{
	pDstPath[0] = '\0';

	Sint32 Len = (Sint32)strlen( pSrcPath );
	while ( pSrcPath[Len] != '\\' ) if ( --Len < 0 ) break;
	if ( Len < 0 )
	{
		StringCbCat( pDstPath, DstPathSize, pSrcPath );
	}
	else
	{
		HANDLE hFind;
		WIN32_FIND_DATA FindData;
		char LongPath[MAX_PATH] = "";
		char Temp[MAX_PATH] = "";

		// �e�f�B���N�g�����擾
		StringCbCopy( Temp, sizeof(Temp), pSrcPath );
		Temp[Len] = '\0';
		GetLongFullPathName( Temp, LongPath, sizeof(LongPath) );

		// �t�@�C��������
		hFind = ::FindFirstFile( pSrcPath, &FindData );
		if ( hFind == INVALID_HANDLE_VALUE )
		{
			StringCbCat( pDstPath, DstPathSize, LongPath );
		}
		else
		{
			::FindClose( hFind );

			StringCbCat( pDstPath, DstPathSize, LongPath );
			StringCbCat( pDstPath, DstPathSize, "\\" );
			StringCbCat( pDstPath, DstPathSize, FindData.cFileName );
		}
	}
}

