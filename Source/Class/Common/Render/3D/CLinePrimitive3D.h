#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Platform/Render/CRender.h"
#include "Class/Common/Render/3D/CPrimitive3DBase.h"
#include "Class/Common/Scene/CSceneLinePrimitiveActorObject.h"
#include "Interface/Render/3D/ILinePrimitive3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CLine3D : public CPrimitive3DBase, public ILine3D
	{
	public:
		virtual void CreateRenderActor( Scene::CSceneLineActorObject *pActor );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

		virtual Bool IsSupportVertexBone( void )    { return false; } 
		virtual Bool IsSupportVertexTexture( void ) { return false; } 
		virtual Bool IsSupportVertexNormal( void )  { return false; }
		virtual Bool IsSupportVertexBump( void )    { return false; }

	public:
		CLine3D( CRender *pRender, CRenderObjectMgr *pMgr );
		virtual ~CLine3D();

		virtual Bool Create( Sint32 VertexMax, Bool IsDynamic );

		virtual void PushBox( Collision::CBox &Box, CColor Color );
		virtual Bool Push( SLineVertex3D *pLine, Sint32 LineCount );

		virtual void Begin( void );
		virtual void End( void );
	};
}
}
}
