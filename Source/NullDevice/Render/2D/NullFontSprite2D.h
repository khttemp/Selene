#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
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
	class NullFontSprite2D : public IFontSprite2D
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

		virtual Sint32 AddRef( void )
		{
			return 0;
		}

		virtual void Begin( Sint32 Space )
		{
		}

		virtual void End( void )
		{
		}

		virtual void SetDecoration( ITexture *pTex )
		{
		}

		virtual void Rendering( void )
		{
		}

		virtual Sint32 GetSize( void )
		{
			return 0;
		}

		virtual void DrawString( const char *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length )
		{
		}

		virtual void DrawStringP( const char *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length )
		{
		}

		virtual Sint32 DrawChara( const char *pChara, Math::Rect2DF &Dst, CColor Color )
		{
			return 0;
		}

		virtual Sint32 DrawCharaRotate( const char *pChara, Math::Rect2DF &Dst, CColor Color, Sint32 Angle )
		{
			return 0;
		}

		virtual Math::Point2DF GetStringLastPos( const char *pStr, Math::Point2DF Pos, Sint32 Length )
		{
			return Math::Point2DF( 0, 0 );
		}

		virtual Math::Point2DF GetStringLastPosP( const char *pStr, Math::Point2DF Pos, Sint32 Length )
		{
			return Math::Point2DF( 0, 0 );
		}

		virtual Math::Point2DF GetStringSize( const char *pStr )
		{
			return Math::Point2DF( 0, 0 );
		}

		virtual Math::Point2DF GetStringSizeP( const char *pStr )
		{
			return Math::Point2DF( 0, 0 );
		}

		virtual void DrawString( const wchar_t *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length )
		{
		}

		virtual void DrawStringP( const wchar_t *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length )
		{
		}

		virtual Sint32 DrawChara( const wchar_t *pChara, Math::Rect2DF &Dst, CColor Color )
		{
			return 0;
		}

		virtual Sint32 DrawCharaRotate( const wchar_t *pChara, Math::Rect2DF &Dst, CColor Color, Sint32 Angle )
		{
			return 0;
		}

		virtual Math::Point2DF GetStringLastPos( const wchar_t *pStr, Math::Point2DF Pos, Sint32 Length )
		{
			return Math::Point2DF( 0, 0 );
		}

		virtual Math::Point2DF GetStringLastPosP( const wchar_t *pStr, Math::Point2DF Pos, Sint32 Length )
		{
			return Math::Point2DF( 0, 0 );
		}

		virtual Math::Point2DF GetStringSize( const wchar_t *pStr )
		{
			return Math::Point2DF( 0, 0 );
		}

		virtual Math::Point2DF GetStringSizeP( const wchar_t *pStr )
		{
			return Math::Point2DF( 0, 0 );
		}
	};
}
}
}
