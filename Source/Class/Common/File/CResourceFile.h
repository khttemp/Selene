#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/File/CFile.h"
#include "Interface/File/IResourceFile.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace File
{
	class CResourceFile : public CFile, public CBaseObject, public IResourceFile, public Plugin::Sound::ISoundStreamLoader
	{
	private:
		ICrypt *m_pCrypt;
		Sint32 m_Start;
		Sint32 m_Size;
		char m_FileName[MAX_PATH];

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CResourceFile( const char *pFileName );
		virtual ~CResourceFile();

		virtual void SetCrypt( ICrypt *pCrypt ) { m_pCrypt = pCrypt; }
		virtual void SetStart( Sint32 Pos ) { m_Start = Pos; }
		virtual void SetSize( Sint32 Size ) { m_Size = Size; }
		virtual const char *GetNamePointer( void ) { return m_FileName; }

		virtual Sint32 Read( void *pData, Sint32 Size );
		
		virtual Sint32 GetFileStart( void );
		virtual Sint32 GetFileSize( void );
		virtual Sint32 GetFilePosition( void );

		virtual Sint32 SeekStart( Sint32 Offset );
		virtual Sint32 SeekEnd( Sint32 Offset );
		virtual Sint32 Seek( Sint32 Offset );
	};
}
}
