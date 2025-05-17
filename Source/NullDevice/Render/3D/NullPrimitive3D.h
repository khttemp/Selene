#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/3D/IPrimitive3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class NullPrimitive3D : public IPrimitive3D
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
			return -1;
		}

		virtual Bool Push( const SVertex3DBase *pVtx, Sint32 Count )
		{
			return false;
		}

		virtual Bool Push( const SVertex3DTexture *pVtx, Sint32 Count )
		{
			return false;
		}

		virtual Bool Push( const SVertex3DLight *pVtx, Sint32 Count )
		{
			return false;
		}

		virtual Bool Push( const SVertex3DBump *pVtx, Sint32 Count )
		{
			return false;
		}

		virtual Bool Push( const SVertex3DAnimation *pVtx, Sint32 Count )
		{
			return false;
		}

		virtual Bool Push( const void *pIndex, Sint32 IndexCount )
		{
			return false;
		}

		virtual Bool Get( SVertex3DBase &Vtx, Sint32 Index )
		{
			return false;
		}

		virtual Bool Get( SVertex3DTexture &Vtx, Sint32 Index )
		{
			return false;
		}

		virtual Bool Get( SVertex3DLight &Vtx, Sint32 Index )
		{
			return false;
		}

		virtual Bool Get( SVertex3DBump &Vtx, Sint32 Index )
		{
			return false;
		}

		virtual Bool Get( SVertex3DAnimation &Vtx, Sint32 Index )
		{
			return false;
		}

		virtual Sint32 GetVertexCount( void )
		{
			return 0;
		}

		virtual Sint32 GetIndexCount( void )
		{
			return 0;
		}

		virtual void Begin( Bool IsVertex, Bool IsIndex, Bool IsDynamic )
		{
		}

		virtual void End( void )
		{
		}

		virtual void SetBoneCount( Sint32 BoneCount )
		{
		}

		virtual void SetBoneOffsetMatrix( Sint32 No, Math::Matrix &Matrix )
		{
		}

		virtual void SetBoneTransformMatrix( Sint32 No, Math::Matrix &Matrix )
		{
		}

		virtual void SetTransform( Math::Style &Style )
		{
		}

		virtual void SetDiffuseColor( CColor Color )
		{
		}

		virtual void SetEmissiveColor( CColor Color )
		{
		}

		virtual void SetSpecularColor( CColor Color )
		{
		}

		virtual void SetSpecularRefractive( Float fRefractive )
		{
		}

		virtual void SetSpecularRoughly( Float fRoughly )
		{
		}
	};
}
}
}

