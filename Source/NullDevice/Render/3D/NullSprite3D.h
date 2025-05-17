#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class NullSprite3D : public ISprite3D
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

		virtual Sint32 Rendering( void )
		{
			return 0;
		}

		virtual void Begin( void )
		{
		}

		virtual void End( void )
		{
		}

		virtual void DrawListXY( const Math::Vector3D Pos[], const Sint32 Angle[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src )
		{
		}

		virtual void DrawListYZ( const Math::Vector3D Pos[], const Sint32 Angle[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src )
		{
		}

		virtual void DrawListZX( const Math::Vector3D Pos[], const Sint32 Angle[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src )
		{
		}

		virtual void Draw( const Math::Matrix &mWorld, const Math::Point2DF &Size, const Math::Rect2DI &SrcRect, CColor Color )
		{
		}

		virtual void Draw( const Math::Matrix &mWorld, const Math::Vector2D PtTbl[], const Math::Rect2DI &SrcRect, CColor Color )
		{
		}

		virtual void DrawListXY( const Math::Vector3D Pos[], const Float Width[], const Sint32 Angle[], const CColor Color[], Sint32 Count, const Math::Rect2DF &Src )
		{
		}

		virtual void DrawListYZ( const Math::Vector3D Pos[], const Float Width[], const Sint32 Angle[], const CColor Color[], Sint32 Count, const Math::Rect2DF &Src )
		{
		}

		virtual void DrawListZX( const Math::Vector3D Pos[], const Float Width[], const Sint32 Angle[], const CColor Color[], Sint32 Count, const Math::Rect2DF &Src )
		{
		}

		virtual void DrawListXY( const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src )
		{
		}

		virtual void DrawListYZ( const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src )
		{
		}

		virtual void DrawListZX( const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src )
		{
		}

		virtual void DrawPolyLine( const Math::Vector3D &vCameraPosition, const Math::Vector3D Pos[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src )
		{
		}

		virtual void DrawPolyLine( const Math::Vector3D &vCameraPosition, const Math::Vector3D Pos[], const CColor Color[], const Float Width[], Sint32 Count, const Math::Rect2DF &Src )
		{
		}

		virtual void DrawPolyLine( const Math::Vector3D &vCameraPosition, const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src )
		{
		}
	};
}
}
}
