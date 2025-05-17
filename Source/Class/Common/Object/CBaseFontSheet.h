#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CRenderObject.h"
#include "Class/Common/Object/CRenderObjectMgr.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	static const Sint32 CHARA_CODE_MAX	= 9362;
	static const Sint32 SHEET_MAX		= 256;

	struct SFontSheetData
	{
		Uint64 SheetNo	: 8;
		Uint64 Left		: 6;
		Uint64 Right	: 6;
		Uint64 x1		: 11;
		Uint64 y1		: 11;
		Uint64 x2		: 11;
		Uint64 y2		: 11;
	};

	class CBaseFontSheet : public Renderer::CRenderObject
	{
	protected:
		SFontSheetData *m_pSheetTbl;
		Renderer::ITexture *m_pTextures[SHEET_MAX];
		Uint16 m_IndexTbl[CHARA_CODE_MAX];

		Sint32 m_SheetCount;
		Sint32 m_FontSize;
		Sint16 m_FontMax;

	protected:
		CBaseFontSheet( Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr );
		virtual ~CBaseFontSheet();

	public:
		virtual Bool CreateSheetTableFromFile( const char *pFileName, const char *pExt );						///< フォントオブジェクトをSFFから生成
		virtual Bool CreateSheetTableFromMemory( void *pData, const char *pExt );								///< フォントオブジェクトをSFFから生成

		virtual Bool GetWidth( const char Chara, Sint32 *pLeft, Sint32 *pCenter, Sint32 *pRight );
		virtual void GetHeight( Sint32 *pHeight );

		virtual Uint16 GetKeyCode( Uint16 Code );
	};
}
