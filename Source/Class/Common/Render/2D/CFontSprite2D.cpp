

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Render/2D/CSprite2D.h"
#include "Class/Common/Render/2D/CFontSprite2D.h"
#include "Class/Platform/Render/CRender.h"
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
CFontSprite2D::CFontSprite2D( CRender *pRender, CRenderObjectMgr *pMgr ) : CBaseFontSheet( pRender, pMgr )
	, m_Space	( 0 )
{
	MemoryClear( m_pParticles, sizeof(m_pParticles) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFontSprite2D::~CFontSprite2D()
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
void CFontSprite2D::OnLostDevice( void )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFontSprite2D::OnResetDevice( void )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CFontSprite2D::CreateFromFile( const char *pFileName, const char *pExt, Sint32 Num, Bool IsAutoResize, Sint32 ResizeStep )
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
		m_pParticles[i] = m_pRender->CreateSprite2D( Num * 6, m_pTextures[i], false, false, IsAutoResize, ResizeStep );
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
void CFontSprite2D::Begin( Sint32 Space )
{
	Sint32 Max = m_SheetCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pParticles[i]->Begin();
	}

	m_Space = Space;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFontSprite2D::End( void )
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
void CFontSprite2D::Rendering( void )
{
	Sint32 Max = m_SheetCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pParticles[i]->Rendering();
	}

	m_pRender->SetTexture( TEXTURE_STAGE_COLOR, NULL );
	m_pRender->SetTexture( TEXTURE_STAGE_LIGHT, NULL );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFontSprite2D::SetDecoration( ITexture *pTex )
{
	Sint32 Max = m_SheetCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pParticles[i]->SetDecoration( pTex );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFontSprite2D::GetSize( void )
{
	return m_FontSize;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFontSprite2D::DrawString( const char *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length )
{
	Sint32 Width = m_FontSize + m_Space;
	Float PosX = Pos.x;
	Float PosY = Pos.y;
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
			PosX = Pos.y;
			PosY += toF(m_FontSize);
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == ' ' )
		{
			PosX += toF(Width) / 2.0f;
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == '　' )
		{
			PosX += toF(Width);
			continue;
		}
		//----------------------------------------------------------------
		// タブ
		//----------------------------------------------------------------
		if ( Code == '\t' )
		{
			PosX += toF(Width * 2 / 4);
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
				Sint32 w = toI(Sheet.x2 - Sheet.x1 + 1);
				Sint32 h = toI(Sheet.y2 - Sheet.y1);
				Sint32 x = toI(PosX) + toI(Sheet.Left);
				Math::Rect2DF Dst( toF(x), toF(PosY), toF(w), toF(h) );
				Math::Rect2DF Src( toF(Sheet.x1), toF(Sheet.y1), Dst.w, Dst.h );

				// 描画
				m_pParticles[Sheet.SheetNo]->DrawSquare( Dst, Src, Color );

				if ( Code <= 0xFF )
				{
					PosX += toF(Width) / 2.0f;
				}
				else
				{
					PosX += toF(Width);
				}
			}
			else
			{
				PosX += toF(Width) / 2.0f;
			}
		}
		//-------------------------------------------------------
		// 文字データが無い場合
		//-------------------------------------------------------
		else
		{
			PosX += toF(Width) / 2.0f;
		}

		//-------------------------------------------------------
		// 指定数描画したら終わり
		//-------------------------------------------------------
		if ( --Length == 0 )
		{
			break;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFontSprite2D::DrawStringP( const char *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length )
{
	Float PosX = Pos.x;
	Float PosY = Pos.y;
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
			PosX = Pos.x;
			PosY += toF(m_FontSize);
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == ' ' )
		{
			PosX += toF(m_FontSize * 1 / 4);
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == '　' )
		{
			PosX += toF(m_FontSize * 2 / 4);
			continue;
		}
		//----------------------------------------------------------------
		// タブ
		//----------------------------------------------------------------
		if ( Code == '\t' )
		{
			PosX += toF(m_FontSize * 3 / 4);
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
				Sint32 w = toI(Sheet.x2 - Sheet.x1 + 1);
				Sint32 h = toI(Sheet.y2 - Sheet.y1);
				Sint32 x = toI(PosX);
				Math::Rect2DF Dst( toF(x), toF(PosY), toF(w), toF(h) );
				Math::Rect2DF Src( toF(Sheet.x1), toF(Sheet.y1), Dst.w, Dst.h );

				// 描画
				m_pParticles[Sheet.SheetNo]->DrawSquare( Dst, Src, Color );

				PosX += toF(w);
			}
			else
			{
				PosX += toF(m_FontSize * 1 / 4);
			}
		}
		//-------------------------------------------------------
		// 文字データが無い場合
		//-------------------------------------------------------
		else
		{
			PosX += toF(m_FontSize * 1 / 4);
		}

		//-------------------------------------------------------
		// 指定数描画したら終わり
		//-------------------------------------------------------
		if ( --Length == 0 )
		{
			break;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFontSprite2D::DrawChara( const char *pChara, Math::Rect2DF &Dst, CColor Color )
{
	Uint16 Code = GetCharaCode( pChara );
	if ( Code == ' ' )
	{
		return 1;
	}
	ef ( Code == '　' )
	{
		return 2;
	}
	else
	{
		Uint16 Index = m_IndexTbl[GetKeyCode( Code )];
		if ( Index != 0xFFFF )
		{
			SFontSheetData Sheet = m_pSheetTbl[Index];
			if ( Sheet.SheetNo != 0xFF )
			{
				Sint32 x = toI(Sheet.x1);
				Sint32 y = toI(Sheet.y1);
				Sint32 w = toI(Sheet.x2 - Sheet.x1 + 1);
				Sint32 h = toI(Sheet.y2 - Sheet.y1);
				Math::Rect2DF Src( toF(x), toF(y), toF(w), toF(h) );

				m_pParticles[Sheet.SheetNo]->DrawSquare( Dst, Src, Color );
			}

			return ((Code <= 0xFF) ? (1) : (2));
		}
	}

	return 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFontSprite2D::DrawCharaRotate( const char *pChara, Math::Rect2DF &Dst, CColor Color, Sint32 Angle )
{
	Uint16 Code = GetCharaCode( pChara );
	if ( Code == ' ' )
	{
		return 1;
	}
	ef ( Code == '　' )
	{
		return 2;
	}
	else
	{
		Uint16 Index = m_IndexTbl[GetKeyCode( Code )];
		if ( Index != 0xFFFF )
		{
			SFontSheetData Sheet = m_pSheetTbl[Index];
			if ( Sheet.SheetNo != 0xFF )
			{
				Sint32 x = toI(Sheet.x1);
				Sint32 y = toI(Sheet.y1);
				Sint32 w = toI(Sheet.x2 - Sheet.x1 + 1);
				Sint32 h = toI(Sheet.y2 - Sheet.y1);
				Math::Rect2DF Src( toF(x), toF(y), toF(w), toF(h) );

				m_pParticles[Sheet.SheetNo]->DrawSquareRotate( Dst, Src, Color, Angle );
			}

			return ((Code <= 0xFF) ? (1) : (2));
		}
	}

	return 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DF CFontSprite2D::GetStringLastPos( const char *pStr, Math::Point2DF Pos, Sint32 Length )
{
	Sint32 Width = m_FontSize + m_Space;
	Float PosX = Pos.x;
	Float PosY = Pos.y;
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
			PosX = Pos.x;
			PosY += toF(m_FontSize);
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == ' ' )
		{
			PosX += toF(Width) / 2.0f;
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == '　' )
		{
			PosX += toF(Width);
			continue;
		}
		//----------------------------------------------------------------
		// タブ
		//----------------------------------------------------------------
		if ( Code == '\t' )
		{
			PosX += toF(Width * 2 / 4);
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
				if ( Code <= 0xFF )
				{
					PosX += toF(Width / 2);
				}
				else
				{
					PosX += toF(Width);
				}
			}
			else
			{
				PosX += toF(Width);
			}
		}
		//-------------------------------------------------------
		// 文字データが無い場合
		//-------------------------------------------------------
		else
		{
			PosX += toF(Width);
		}

		//-------------------------------------------------------
		// 指定数描画したら終わり
		//-------------------------------------------------------
		if ( --Length == 0 )
		{
			break;
		}
	}

	Pos.x = PosX;
	Pos.y = PosY;

	return Pos;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DF CFontSprite2D::GetStringLastPosP( const char *pStr, Math::Point2DF Pos, Sint32 Length )
{
	Float PosX = Pos.x;
	Float PosY = Pos.y;
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
			PosX = Pos.x;
			PosY += toF(m_FontSize);
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == ' ' )
		{
			PosX += toF(m_FontSize * 1 / 4);
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == '　' )
		{
			PosX += toF(m_FontSize * 2 / 4);
			continue;
		}
		//----------------------------------------------------------------
		// タブ
		//----------------------------------------------------------------
		if ( Code == '\t' )
		{
			PosX += toF(m_FontSize * 3 / 4);
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
				PosX += toF(Sheet.x2 - Sheet.x1 + 1);
			}
			else
			{
				PosX += toF(m_FontSize);
			}
		}
		//-------------------------------------------------------
		// 文字データが無い場合
		//-------------------------------------------------------
		else
		{
			PosX += toF(m_FontSize);
		}

		//-------------------------------------------------------
		// 指定数描画したら終わり
		//-------------------------------------------------------
		if ( --Length == 0 )
		{
			break;
		}
	}

	Pos.x = PosX;
	Pos.y = PosY;

	return Pos;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DF CFontSprite2D::GetStringSize( const char *pStr )
{
	Sint32 Width = m_FontSize + m_Space;
	Float PosX   = 0.0f;
	Float fSizeX = 0.0f;
	Float fSizeY = toF(m_FontSize);
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
			if ( fSizeX < PosX )
			{
				fSizeX = PosX;
			}
			PosX = 0.0f;
			fSizeY += toF(m_FontSize);
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == ' ' )
		{
			PosX += toF(Width) / 2.0f;
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == '　' )
		{
			PosX += toF(Width);
			continue;
		}
		//----------------------------------------------------------------
		// タブ
		//----------------------------------------------------------------
		if ( Code == '\t' )
		{
			PosX += toF(Width * 2 / 4);
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
				if ( Code <= 0xFF )
				{
					PosX += toF(Width / 2);
				}
				else
				{
					PosX += toF(Width);
				}
			}
			else
			{
				PosX += toF(Width);
			}
		}
		//-------------------------------------------------------
		// 文字データが無い場合
		//-------------------------------------------------------
		else
		{
			PosX += toF(Width);
		}
	}

	if ( fSizeX < PosX )
	{
		fSizeX = PosX;
	}

	return Math::Point2DF( fSizeX, fSizeY );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DF CFontSprite2D::GetStringSizeP( const char *pStr )
{
	Float PosX		= 0.0f;
	Float Width		= 0.0f;
	Float Height	= toF(m_FontSize);
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
			if ( Width < PosX )
			{
				Width = PosX;
			}
			PosX = 0.0f;
			Height += toF(m_FontSize);
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == ' ' )
		{
			PosX += toF(m_FontSize * 1 / 4);
			continue;
		}
		//----------------------------------------------------------------
		// スペース
		//----------------------------------------------------------------
		if ( Code == '　' )
		{
			PosX += toF(m_FontSize * 2 / 4);
			continue;
		}
		//----------------------------------------------------------------
		// タブ
		//----------------------------------------------------------------
		if ( Code == '\t' )
		{
			PosX += toF(m_FontSize * 3 / 4);
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
				PosX += toF(Sheet.x2 - Sheet.x1 + 1);
			}
			else
			{
				PosX += toF(m_FontSize);
			}
		}
		//-------------------------------------------------------
		// 文字データが無い場合
		//-------------------------------------------------------
		else
		{
			PosX += toF(m_FontSize);
		}
	}

	if ( Width < PosX )
	{
		Width = PosX;
	}

	return Math::Point2DF( Width, Height );
}

////////////////////////////////////////////////////////////////////////////////////////////////


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFontSprite2D::DrawString( const wchar_t *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length )
{
	char Temp[1024] = "";
	WCtoMB( pStr, Temp, 1024 );
	DrawString( Temp, Pos, Color, Length );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFontSprite2D::DrawStringP( const wchar_t *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length )
{
	char Temp[1024] = "";
	WCtoMB( pStr, Temp, 1024 );
	DrawStringP( Temp, Pos, Color, Length );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFontSprite2D::DrawChara( const wchar_t *pChara, Math::Rect2DF &Dst, CColor Color )
{
	char Temp[4] = "";
	WCtoMB( pChara, Temp, 2 );
	return DrawChara( Temp, Dst, Color );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CFontSprite2D::DrawCharaRotate( const wchar_t *pChara, Math::Rect2DF &Dst, CColor Color, Sint32 Angle )
{
	char Temp[4] = "";
	WCtoMB( pChara, Temp, 4 );
	return DrawCharaRotate( Temp, Dst, Color, Angle );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DF CFontSprite2D::GetStringLastPos( const wchar_t *pStr, Math::Point2DF Pos, Sint32 Length )
{
	char Temp[1024] = "";
	WCtoMB( pStr, Temp, 1024 );
	return GetStringLastPos( Temp, Pos, Length );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DF CFontSprite2D::GetStringLastPosP( const wchar_t *pStr, Math::Point2DF Pos, Sint32 Length )
{
	char Temp[1024] = "";
	WCtoMB( pStr, Temp, 1024 );
	return GetStringLastPosP( Temp, Pos, Length );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DF CFontSprite2D::GetStringSize( const wchar_t *pStr )
{
	char Temp[1024] = "";
	WCtoMB( pStr, Temp, 1024 );
	return GetStringSize( Temp );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point2DF CFontSprite2D::GetStringSizeP( const wchar_t *pStr )
{
	char Temp[1024] = "";
	WCtoMB( pStr, Temp, 1024 );
	return GetStringSizeP( Temp );
}
