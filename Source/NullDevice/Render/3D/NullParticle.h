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
	class NullParticle : public IParticle
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

		virtual void SetBasePosition( const Math::Vector3D &vPos )
		{
		}

		virtual void Begin( void )
		{
		}

		virtual void End( void )
		{
		}

		virtual void Draw( const Math::Vector3D &vPosition, const Math::Point2DF &Size, const Math::Rect2DI &SrcRect, CColor Color )
		{
		}

		virtual void Draw( const Math::Vector3D &vPosition, const Math::Vector2D PtTbl[], const Math::Rect2DI &SrcRect, CColor Color )
		{
		}

		virtual void DrawRotate( const Math::Vector3D &vPosition, const Math::Point2DF &Size, const Math::Rect2DI &SrcRect, CColor Color, Sint32 Angle )
		{
		}

		virtual void DrawRotate( const Math::Vector3D &vPosition, const Math::Vector2D PtTbl[], const Math::Rect2DI &SrcRect, CColor Color, Sint32 Angle )
		{
		}
	};
}
}
}
