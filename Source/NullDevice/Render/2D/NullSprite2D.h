#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/2D/ISprite2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class NullSprite2D : public ISprite2D
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

		virtual void Begin( void )
		{
		}

		virtual void End( void )
		{
		}

		virtual void Rendering( void )
		{
		}

		virtual Sint32 GetRequestedVertexCount( void )
		{
			return 0;
		}

		virtual Sint32 GetRequestedVertexCountMax( void )
		{
			return 0;
		}

		virtual Bool Push( SPrimitiveVertex2D *pPrimitive, Sint32 Count )
		{
			return false;
		}

		virtual void SetDecoration( ITexture *pTex )
		{
		}

		virtual void DrawSquare( Math::Rect2DF &DstRect, Math::Rect2DF &SrcRect, CColor Color )
		{
		}

		virtual void DrawSquareRotate( Math::Rect2DF &DstRect, Math::Rect2DF &SrcRect, CColor Color, Sint32 Angle )
		{
		}

		virtual void DrawSquareRotateXYZ( Math::Rect2DF &DstRect, Math::Rect2DF &SrcRect, CColor Color, Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ )
		{
		}

		virtual void DrawSquareMatrix( Math::Matrix &mWorld, Math::Rect2DF &Src, CColor Color )
		{
		}

		virtual void DrawList( Math::Point2DF Pos[], Sint32 Angle[], CColor Color[], Sint32 Count, Float Width, Math::Rect2DF &Src )
		{
		}

		virtual void DrawList( Math::Point2DF Pos[], Float Width[], Sint32 Angle[], CColor Color[], Sint32 Count, Math::Rect2DF &Src )
		{
		}

		virtual void DrawList( SSpriteListData2D List[], Sint32 Count, Math::Rect2DF &Src )
		{
		}

		virtual void CircleFade( Math::Rect2DF &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha )
		{
		}

		virtual void CircleRoundFade( Math::Rect2DF &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha )
		{
		}
	};
}
}
}
