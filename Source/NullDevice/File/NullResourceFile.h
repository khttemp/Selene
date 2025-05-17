#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/File/IResourceFile.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace File
{
	/**
		@brief リソースファイル操作
		@author 葉迩倭
	*/
	class NullResourceFile : public IResourceFile
	{
	public:
		virtual Bool IsInvalid( void )
		{
			return true;
		}

		virtual Sint32 Release( void )
		{
			return 0;
		}

		virtual Sint32 AddRef( void	)
		{
			return 0;
		}

		virtual Sint32 Read( void *pData, Sint32 Size )
		{
			return 0;
		}

		virtual const char *GetNamePointer( void )
		{
			return NULL;
		}

		virtual Sint32 GetFileSize( void )
		{
			return 0;
		}

		virtual Sint32 GetFilePosition( void )
		{
			return 0;
		}

		virtual Sint32 GetFileGlobalPosition( void )
		{
			return 0;
		}

		virtual Sint32 SeekStart( Sint32 Offset )
		{
			return 0;
		}

		virtual Sint32 SeekEnd( Sint32 Offset )
		{
			return 0;
		}

		virtual Sint32 Seek( Sint32 Offset )
		{
			return 0;
		}
	};
}
}

