

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/File/CFileManager.h"
#include "Class/Common/Render/Model/CModel.h"
#include "Class/Common/Render/Model/CModelMgr.h"
#include "Class/Common/Render/Model/CModelLoader.h"
#include "Class/Platform/Render/CRender.h"
#include "Interface/Surface/ITexture.h"


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
CModelMgr::CModelMgr( CRender *pRender ) : CRenderObjectMgr( pRender, "モデル" )
{
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CModelMgr::~CModelMgr()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CModel *CModelMgr::SearchInstance( const char *pFileName )
{
	return (CModel*)SearchFromName( pFileName );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CModel *CModelMgr::CreateFromFile( const char *pFileName, CRender *pRender )
{
	File::IFileManager *pFileMgr = m_pCore->GetFileMgrPointer();
	if ( (pFileMgr == NULL) || pFileMgr->IsInvalid() )
	{
		return NULL;
	}

	File::CFileManager *pFileMgrSubstance = (File::CFileManager*)pFileMgr;

	CModel *pModel = NULL;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( "モデル" );
	Log_CellBegin( 0 );

	char FilePath[MAX_PATH];
	if ( !pFileMgrSubstance->GetFilePath( FilePath, sizeof(FilePath), pFileName ) )
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

			pModel = new CModel( pRender, this );
			CModelLoader Loader( pModel, pRender );
			if ( !pFileMgrSubstance->Load( pFileName, &pData, &Size ) )
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

			pFileMgrSubstance->Free( pData );
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
CModel *CModelMgr::CreateFromMemory( const void *pData, Sint32 Size, CRender *pRender )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( "モデル" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, "メモリ上のモデルから生成" );

	CModel *pModel = new CModel( pRender, this );
	CModelLoader Loader( pModel, pRender );
	if ( !Loader.LoadFromMemory( (Uint8*)pData, Size ) )
	{
		SAFE_RELEASE( pModel );
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
CModel *CModelMgr::SceneSkydoom_Create( Float fRadius, CColor TopColor, CColor BottomColor, ITexture *pTexCloud, CRender *pRender )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( "モデル" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, "スカイドームの生成" );

	CModel *pModel = new CModel( pRender, this );
	CModelLoader Loader( pModel, pRender );
	if ( (pTexCloud != NULL) && !pTexCloud->IsInvalid() )
	{
		if ( !Loader.SceneSkydoomWithCloud_Create( fRadius, TopColor, BottomColor, pTexCloud ) )
		{
			SAFE_RELEASE( pModel );
		}
	}
	else
	{
		if ( !Loader.SceneSkydoom_Create( fRadius, TopColor, BottomColor ) )
		{
			SAFE_RELEASE( pModel );
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pModel;
}


