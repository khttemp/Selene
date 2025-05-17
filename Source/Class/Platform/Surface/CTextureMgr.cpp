

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/File/CFileManager.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Platform/Surface/CTextureMgr.h"
#include "Class/Platform/Surface/CTexture.h"
#include "Class/Platform/Surface/CCubeTexture.h"
#include "Class/Platform/Surface/CDepthTexture.h"
#include "Class/Platform/Surface/CTargetTexture.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CTextureMgr::CTextureMgr( CRender *pRender ) : CRenderObjectMgr( pRender, "テクスチャ" )
{
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CTextureMgr::~CTextureMgr()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CTexture *CTextureMgr::SearchInstance( const char *pFileName )
{
	return (CTexture*)SearchFromName( pFileName );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CDepthTexture *CTextureMgr::CreateTextureDepthBuffer( Sint32 Width, Sint32 Height )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( "深度テクスチャ" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, "深度バッファを生成" );

	CDepthTexture *pTex = new CDepthTexture( this );
	if ( !pTex->CreateTextureDepthBuffer( Width, Height ) )
	{
		SAFE_RELEASE( pTex );
	}
	else
	{
		char Temp[64] = "";
		StringCbPrintf( Temp, sizeof(Temp), "CreateTextureDepthBuffer [%dx%d] 0x%016X", pTex->GetSize().x, pTex->GetSize().y, (Uint64)this );
		pTex->SetName( Temp );
		Log_PrintStrongLine( 0x008000, "完了" );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CTargetTexture *CTextureMgr::CreateRenderTarget( Sint32 Width, Sint32 Height, eSurfaceFormat Format )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( "ターゲットテクスチャ" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, "レンダリングターゲットを生成" );

	CTargetTexture *pTex = new CTargetTexture( this );
	if ( !pTex->CreateRenderTarget( Width, Height, Format ) )
	{
		SAFE_RELEASE( pTex );
	}
	else
	{
		char Temp[64] = "";
		StringCbPrintf( Temp, sizeof(Temp), "CreateRenderTarget [%dx%d] 0x%016X", pTex->GetSize().x, pTex->GetSize().y, (Uint64)this );
		pTex->SetName( Temp );
		Log_PrintStrongLine( 0x008000, "完了" );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CTexture *CTextureMgr::CreateFromFile( const char *pFileName, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize )
{
	File::IFileManager *pFileMgr = m_pCore->GetFileMgrPointer();
	if ( (pFileMgr == NULL) || pFileMgr->IsInvalid() )
	{
		return NULL;
	}

	File::CFileManager *pFileMgrSubstance = (File::CFileManager*)pFileMgr;

	CTexture *pTex = NULL;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( "テクスチャ" );
	Log_CellBegin( 0 );

	char FilePath[MAX_PATH];
	if ( !pFileMgrSubstance->GetFilePath( FilePath, sizeof(FilePath), pFileName ) )
	{
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintStrong( 0xFF0000, "ファイルが見つかりません" );
	}
	else
	{
		pTex = (CTexture*)SearchInstance( FilePath );
		if ( pTex != NULL )
		{
			pTex->AddRef();
			Log_Print( 0x000000, "同一ファイル[%s]を取得", FilePath );
		}
		else
		{
			Log_PrintLine( 0x000000, "%s", FilePath );

			pTex = new CTexture( this );

			if ( !pTex->CreateFromFile( pFileName, Format, KeyColor, IsMipmap, IsHalfSize ) )
			{
				SAFE_RELEASE( pTex );
			}
			else
			{
				Log_PrintStrongLine( 0x008000, "完了" );
				pTex->SetName( FilePath );
			}
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CTexture *CTextureMgr::CreateFromMemory( const void *pData, Sint32 Size, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( "テクスチャ" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, "メモリ上の画像から生成" );

	CTexture *pTex = new CTexture( this );

	if ( !pTex->CreateFromMemory( pData, Size, Format, KeyColor, IsMipmap, IsHalfSize ) )
	{
		SAFE_RELEASE( pTex );
	}
	else
	{
		char Temp[64] = "";
		StringCbPrintf( Temp, sizeof(Temp), "CreateFromMemory [%dx%d] 0x%016X", pTex->GetSize().x, pTex->GetSize().y, (Uint64)this );
		pTex->SetName( Temp );
		Log_PrintStrongLine( 0x008000, "完了" );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCubeTexture *CTextureMgr::CubeCreateRenderTarget( Sint32 Size, eSurfaceFormat Format, Bool IsHalfSize )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( "テクスチャ" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, "レンダリングターゲットを生成" );

	CCubeTexture *pTex = new CCubeTexture( this );
	if ( !pTex->CreateRenderTarget( Size, Format ) )
	{
		SAFE_RELEASE( pTex );
	}
	else
	{
		char Temp[64] = "";
		StringCbPrintf( Temp, sizeof(Temp), "CubeCreateRenderTarget [%dx%d] 0x%016X", pTex->GetSize().x, pTex->GetSize().y, (Uint64)this );
		pTex->SetName( Temp );
		Log_PrintStrongLine( 0x008000, "完了" );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCubeTexture *CTextureMgr::CubeCreateFromFile( const char *pFileName, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize )
{
	File::IFileManager *pFileMgr = m_pCore->GetFileMgrPointer();
	if ( (pFileMgr == NULL) || pFileMgr->IsInvalid() )
	{
		return NULL;
	}

	File::CFileManager *pFileMgrSubstance = (File::CFileManager*)pFileMgr;

	CCubeTexture *pTex = NULL;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( "テクスチャ" );
	Log_CellBegin( 0 );

	char FilePath[MAX_PATH];
	if ( !pFileMgrSubstance->GetFilePath( FilePath, sizeof(FilePath), pFileName ) )
	{
		Log_PrintStrong( 0x000000, pFileName );
		Log_PrintStrong( 0xFF0000, "ファイルが見つかりません" );
	}
	else
	{
		pTex = (CCubeTexture*)SearchInstance( FilePath );
		if ( pTex != NULL )
		{
			pTex->AddRef();
			Log_Print( 0x000000, "同一ファイル[%s]を取得", FilePath );
		}
		else
		{
			Log_PrintLine( 0x000000, "%s", FilePath );

			pTex = new CCubeTexture( this );

			if ( !pTex->CreateFromFile( pFileName, Format, KeyColor, IsMipmap, IsHalfSize ) )
			{
				SAFE_RELEASE( pTex );
			}
			else
			{
				Log_PrintStrongLine( 0x008000, "完了" );
				pTex->SetName( FilePath );
			}
		}
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCubeTexture *CTextureMgr::CubeCreateFromMemory( const void *pData, Sint32 Size, eSurfaceFormat Format, CColor KeyColor, Bool IsMipmap, Bool IsHalfSize )
{
	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( "テクスチャ" );
	Log_CellBegin( 0 );

	Log_PrintLine( 0x000000, "メモリ上の画像から生成" );

	CCubeTexture *pTex = new CCubeTexture( this );

	if ( !pTex->CreateFromMemory( pData, Size, Format, KeyColor, IsMipmap, IsHalfSize ) )
	{
		SAFE_RELEASE( pTex );
	}
	else
	{
		char Temp[64] = "";
		StringCbPrintf( Temp, sizeof(Temp), "CubeCreateFromMemory [%dx%d] 0x%016X", pTex->GetSize().x, pTex->GetSize().y, (Uint64)this );
		pTex->SetName( Temp );
		Log_PrintStrongLine( 0x008000, "完了" );
	}

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return pTex;
}

