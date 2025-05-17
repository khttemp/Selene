#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Platform/Render/CRender.h"
#include "Class/Common/Render/3D/CPrimitive3DBase.h"
#include "Class/Common/Scene/CScenePointPrimitiveActorObject.h"
#include "Interface/Render/3D/IPointPrimitive3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CPoint3D : public CPrimitive3DBase, public IPoint3D
	{
	public:
		virtual void CreateRenderActor( Scene::CScenePointActorObject *pActor );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

		virtual Bool IsSupportVertexBone( void )    { return false; } 
		virtual Bool IsSupportVertexTexture( void ) { return false; } 
		virtual Bool IsSupportVertexNormal( void )  { return false; }
		virtual Bool IsSupportVertexBump( void )    { return false; }

	public:
		CPoint3D( CRender *pRender, CRenderObjectMgr *pMgr );
		virtual ~CPoint3D();

		virtual Bool Create( Sint32 VertexMax, Bool IsDynamic );

		virtual Bool Push( const SVertex3DBase *pPoint, Sint32 PointCount );

		virtual void Begin( void );
		virtual void End( void );
	};
}
}
}
