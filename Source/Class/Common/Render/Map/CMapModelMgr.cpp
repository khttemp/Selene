

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/File/CFileManager.h"
#include "Class/Common/Render/Map/CMapModel.h"
#include "Class/Common/Render/Map/CMapModelMgr.h"
#include "Class/Common/Render/Map/CMapModelLoader.h"
#include "Class/Platform/Render/CRender.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;
using namespace Object;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapModelMgr::CMapModelMgr( CRender *pRender ) : CRenderObjectMgr( pRender, "マップ" )
{
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapModelMgr::~CMapModelMgr()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapModel *CMapModelMgr::SearchInstance( const char *pFileName )
{
	return (CMapModel*)SearchFromName( pFileName );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapModel *CMapModelMgr::CreateFromFile( const char *pFileName, CRender *pRender )
{
	File::IFileManager *pFileMgr = m_pCore->GetFileMgrPointer();
	if ( (pFileMgr == NULL) || pFileMgr->IsInvalid() )
	{
		return NULL;
	}

	File::CFileManager *pFileManager = (File::CFileManager*)pFileMgr;

	CMapModel *pModel = NULL;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( "モデル" );
	Log_CellBegin( 0 );

	char FilePath[MAX_PATH];
	if ( !pFileManager->GetFilePath( FilePath, sizeof(FilePath), pFileName ) )
	{
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintStrong( 0xFF0000, "ファイルが見つかりません" );
	}
	else
	{
		pModel = SearchInstance( FilePath );
		if ( pModel != NULL )
		{
			pModel->AddRef();
			Log_Print( 0x000000, "同一ファイル[%s]を取得", FilePath );
		}
		else
		{
			Log_PrintLine( 0x000000, "%s", FilePath );

			void *pData = NULL;
			Sint32 Size;

			pModel = new CMapModel( pRender, this );
			CMapModelLoader Loader( pModel, pRender );
			if ( !pFileManager->Load( pFileName, &pData, &Size ) )
			{
				SAFE_RELEASE( pModel );
			}
			ef( !Loader.LoadFromMemory( (Uint8*)pData, Size ) )
			{
				SAFE_RELEASE( pModel );
			}
			else
			{
				Log_PrintLine( 0x0000000, "残VRAM容量 %.3lfMB", pRender->GetRestVRAM() );
				Log_PrintStrongLine( 0x008000, "完了" );
				pModel->SetName( FilePath );
			}

			pFileManager->Free( pData );
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pModel;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapModel *CMapModelMgr::CreateFromMemory( const void *pData, Sint32 Size, CRender *pRender )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( "モデル" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, "メモリ上のモデルから生成" );

	CMapModel *pModel = new CMapModel( pRender, this );
	CMapModelLoader Loader( pModel, pRender );
	if ( !Loader.LoadFromMemory( (Uint8*)pData, Size ) )
	{
		SAFE_RELEASE( pModel );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pModel;
}

