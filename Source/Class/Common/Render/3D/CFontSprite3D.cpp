//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Render/3D/CParticle.h"
#include "Class/Common/Render/3D/CFontSprite3D.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Class/Platform/Surface/CTexture.h"


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
CFontSprite3D::CFontSprite3D( CRender *pRender, CRenderObjectMgr *pMgr ) : CBaseFontSheet( pRender, pMgr )
{
	MemoryClear( m_pParticles, sizeof(m_pParticles) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFontSprite3D::~CFontSprite3D()
{
	Log_PrintTable( 0xFF0000, 0x000000, "解放", "フォントスプライト", m_Name );
	Log_TableLine( 1 );

	for ( Sint32 i = 0; i < SHEET_MAX; i++ )
	{
		SAFE_RELEASE( m_pParticles[i] );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFontSprite3D::CreateRenderActor( Sint32 Index, Scene::CParticleActorObject *pActor )
{
	((CParticle*)m_pParticles[Index])->CreateRenderActor( pActor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFontSprite3D::GetSheetCount( void )
{
	return m_SheetCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CFontSprite3D::CreateFromFile( const char *pFileName, const char *pExt, Sint32 Num )
{
	Bool bRet = false;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( "フォントスプライト" );
	Log_CellBegin( 0 );

	//--------------------------------------------------------------
	// シート生成
	//--------------------------------------------------------------
	if ( !CreateSheetTableFromFile( pFileName, pExt ) )
	{
		goto EXIT;
	}

	//--------------------------------------------------------------
	// スプライト生成
	//--------------------------------------------------------------
	for ( Sint32 i = 0; i < m_SheetCount; i++ )
	{
		m_pParticles[i] = m_pRender->CreateParticle( Num, m_pTextures[i], PARTICLE_TYPE_NORMAL, false );
		if ( m_pParticles[i]->IsInvalid() ) goto EXIT;
	}

	Log_PrintLine( 0x000000, "フォント展開用テクスチャ数 %u", m_SheetCount );
	SetName( pFileName );
	Log_PrintStrongLine( 0x008000, "完了" );

	bRet = true;

EXIT:
	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return bRet;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFontSprite3D::Begin( void )
{
	Sint32 Max = m_SheetCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pParticles[i]->Begin();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFontSprite3D::End( void )
{
	Sint32 Max = m_SheetCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pParticles[i]->End();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFontSprite3D::DrawString( const char *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color )
{
	Math::Point2DI Count = GetCount( pStr );
	Float fSx = -toF(m_FontSize) * toF(Count.x) / 4.0f;
	Float fSy = +toF(m_FontSize) * toF(Count.y) / 2.0f;

	Math::Vector2D ScreenToWorld( fSize.x / toF(m_FontSize), fSize.y / toF(m_FontSize) );

	Float PosX = fSx;
	Float PosY = fSy;

	while ( *pStr != '\0' )
	{
		//----------------------------------------------------------------
		// 文字コード
		//----------------------------------------------------------------
		Uint16 Code = GetCharaCode( pStr );
		pStr += (Code <= 0xFF) ? 1 : 2;

		//----------------------------------------------------------------
		// 改行
		//----------------------------------------------------------------
		if ( (Code == '\n\r') || (Code == '\n') || (Code == '\r') )
		{
			PosX = fSx;
			PosY -= toF(m_FontSize);
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == ' ' )
		{
			PosX += toF(m_FontSize) / 2.0f;
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == '　' )
		{
			PosX += toF(m_FontSize);
			continue;
		}
		//----------------------------------------------------------------
		// タブ
		//----------------------------------------------------------------
		if ( Code == '\t' )
		{
			continue;
		}
		//----------------------------------------------------------------
		// バックスペース
		//----------------------------------------------------------------
		if ( Code == '\b' )
		{
			continue;
		}

		//-------------------------------------------------------
		// 文字データがある場合
		//-------------------------------------------------------
		Uint16 Index = m_IndexTbl[GetKeyCode( Code )];
		if ( Index != 0xFFFF )
		{
			SFontSheetData Sheet = m_pSheetTbl[Index];
			if ( Sheet.SheetNo != -1 )
			{
				// 転送先
				Sint32 w = toI(Sheet.x2 - Sheet.x1);
				Sint32 h = toI(Sheet.y2 - Sheet.y1);
				Math::Rect2DI Src( Sheet.x1, Sheet.y1, w, h );

				Math::Point2DF Size( fSize.x * toF(w) / toF(m_FontSize), fSize.y );

				Float x = PosX + toF(Sheet.Left) + toF(w/2);
				Float y = PosY + toF(h/2);

				Math::Vector3D vOffset = vPos + Math::Vector3D( x * ScreenToWorld.x, y * ScreenToWorld.y, 0.0f );

				// 描画
				m_pParticles[Sheet.SheetNo]->Draw( vOffset, Size, Src, Color );

				if ( Code <= 0xFF )
				{
					PosX += toF(m_FontSize) / 2.0f;
				}
				else
				{
					PosX += toF(m_FontSize);
				}
			}
			else
			{
				PosX += toF(m_FontSize) / 2.0f;
			}
		}
		//-------------------------------------------------------
		// 文字データが無い場合
		//-------------------------------------------------------
		else
		{
			PosX += toF(m_FontSize) / 2.0f;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFontSprite3D::DrawStringP( const char *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color )
{
	Math::Point2DI Count = GetCount( pStr );
	Float fSx = -toF(m_FontSize) * 0.25f * toF(Count.x);
	Float fSy = +toF(m_FontSize) * 0.50f * toF(Count.y);

	Math::Vector2D ScreenToWorld( fSize.x / toF(m_FontSize), fSize.y / toF(m_FontSize) );

	Float PosX = fSx;
	Float PosY = fSy;

	while ( *pStr != '\0' )
	{
		//----------------------------------------------------------------
		// 文字コード
		//----------------------------------------------------------------
		Uint16 Code = *pStr++;

		//----------------------------------------------------------------
		// 改行
		//----------------------------------------------------------------
		if ( (Code == '\n\r') || (Code == '\n') || (Code == '\r') )
		{
			PosX = fSx;
			PosY -= m_FontSize;
			continue;
		}
		//----------------------------------------------------------------
		// タブ
		//----------------------------------------------------------------
		if ( Code == '\t' )
		{
			continue;
		}
		//----------------------------------------------------------------
		// バックスペース
		//----------------------------------------------------------------
		if ( Code == '\b' )
		{
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == ' ' )
		{
			PosX += m_FontSize / 2;
			continue;
		}

		//-------------------------------------------------------
		// 文字データがある場合
		//-------------------------------------------------------
		Uint16 Index = m_IndexTbl[GetKeyCode( Code )];
		if ( Index != 0xFFFF )
		{
			SFontSheetData Sheet = m_pSheetTbl[Index];
			if ( Sheet.SheetNo != -1 )
			{
				// 転送先
				Sint32 w = toI(Sheet.x2 - Sheet.x1);
				Sint32 h = toI(Sheet.y2 - Sheet.y1);
				Math::Rect2DI Src( Sheet.x1, Sheet.y1, w, h );

				Math::Point2DF Size( fSize.x * toF(w) / toF(m_FontSize), fSize.y );

				Float x = toF(PosX) + toF(w/2);
				Float y = toF(PosY) + toF(h/2);

				Math::Vector3D vOffset = vPos + Math::Vector3D( x * ScreenToWorld.x, y * ScreenToWorld.y, 0.0f );

				// 描画
				m_pParticles[Sheet.SheetNo]->Draw( vOffset, Size, Src, Color );

				PosX += toF(Sheet.x2 - Sheet.x1 + 1);
			}
			else
			{
				PosX += m_FontSize / 2;
			}
		}
		//-------------------------------------------------------
		// 文字データが無い場合
		//-------------------------------------------------------
		else
		{
			PosX += m_FontSize / 2;
		}
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Math::Point2DI CFontSprite3D::GetCount( const char *pStr )
{
	Math::Point2DI Count( 0, 1 );

	for ( ; ; )
	{
		// 長さ算出
		Sint32 Temp = 0;
		while ( (*pStr != '\n') && (*pStr != '\0') )
		{
			if ( GetCharaCode( pStr ) <= 0xFF )
			{
				if ( (*pStr != '\t') && (*pStr != '\b') )
				{
					Temp += 1;
				}
				pStr += 1;
			}
			else
			{
				Temp += 2;
				pStr += 2;
			}
		}

		// 以前の文字列より長ければ更新
		if ( Temp > Count.x ) Count.x = Temp;

		// 終了
		if ( *pStr == '\0' ) break;

		Count.y++;

		// 次
		pStr++;
	}

	return Count;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CFontSprite3D::DrawString( const wchar_t *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color )
{
	char Temp[1024] = "";
	WCtoMB( pStr, Temp, 1024 );
	DrawString( Temp, vPos, fSize, Color );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CFontSprite3D::DrawStringP( const wchar_t *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color )
{
	char Temp[1024] = "";
	WCtoMB( pStr, Temp, 1024 );
	DrawStringP( Temp, vPos, fSize, Color );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Math::Point2DI CFontSprite3D::GetCount( const wchar_t *pStr )
{
	char Temp[1024] = "";
	WCtoMB( pStr, Temp, 1024 );
	return GetCount( Temp );
}
