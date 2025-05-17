#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Math.h"
#include "Class/Common/Object/CBaseFontSheet.h"
#include "Interface/Render/2D/IFontSprite2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CFontSprite2D : public CBaseFontSheet, public IFontSprite2D
	{
	protected:
		ISprite2D *m_pParticles[SHEET_MAX];
		Sint32 m_Space;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CFontSprite2D( CRender *pRender, CRenderObjectMgr *pMgr );
		virtual ~CFontSprite2D();

		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );

		virtual Bool CreateFromFile( const char *pFileName, const char *pExt, Sint32 Num, Bool IsAutoResize, Sint32 ResizeStep );

		virtual void Begin( Sint32 Space );
		virtual void End( void );
		virtual void Rendering( void );

		virtual void SetDecoration( ITexture *pTex );

		virtual Sint32 GetSize( void );

		virtual void DrawString( const char *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length );
		virtual void DrawStringP( const char *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length );
		virtual Sint32 DrawChara( const char *pChara, Math::Rect2DF &Dst, CColor Color );
		virtual Sint32 DrawCharaRotate( const char *pChara, Math::Rect2DF &Dst, CColor Color, Sint32 Angle );

		virtual Math::Point2DF GetStringLastPos( const char *pStr, Math::Point2DF Pos, Sint32 Length );
		virtual Math::Point2DF GetStringLastPosP( const char *pStr, Math::Point2DF Pos, Sint32 Length );

		virtual Math::Point2DF GetStringSize( const char *pStr );
		virtual Math::Point2DF GetStringSizeP( const char *pStr );

		virtual void DrawString( const wchar_t *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length );
		virtual void DrawStringP( const wchar_t *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length );
		virtual Sint32 DrawChara( const wchar_t *pChara, Math::Rect2DF &Dst, CColor Color );
		virtual Sint32 DrawCharaRotate( const wchar_t *pChara, Math::Rect2DF &Dst, CColor Color, Sint32 Angle );

		virtual Math::Point2DF GetStringLastPos( const wchar_t *pStr, Math::Point2DF Pos, Sint32 Length );
		virtual Math::Point2DF GetStringLastPosP( const wchar_t *pStr, Math::Point2DF Pos, Sint32 Length );

		virtual Math::Point2DF GetStringSize( const wchar_t *pStr );
		virtual Math::Point2DF GetStringSizeP( const wchar_t *pStr );
	};
}
}
}
