#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Class/Common/Scene/CSceneMapActorObject.h"
#include "Class/Common/Object/CRenderObject.h"
#include "Interface/Surface/ITexture.h"
#include "Interface/Scene/ISceneMapActor.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class CMapActor : public Renderer::CRenderObject, public IMapActor
	{
	protected:
		Renderer::Object::CMapModel *m_pModel;
		Sint32 m_ObjectCount;
		CMapActorObject **m_pObjectTbl;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CMapActor( CSceneManagerBase *pSceneMgr, Renderer::Object::IMapModel *pObject, Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr );
		virtual ~CMapActor();

	public:
		virtual void RenderingRequest( void );
		virtual void RenderingBounding( Renderer::Object::ILine3D *pLine );

		virtual Sint32 GetCellCount( void );
		virtual Sint32 GetRenderingCellCount( void );

		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out, Collision::CBox &Box );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out, Collision::CBox &Box );

		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius );
		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Collision::CBox &Box );
		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphere &Out );
		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphere &Out, Collision::CBox &Box );
		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphereExtend &Out );
		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphereExtend &Out, Collision::CBox &Box );

		virtual void CreateCollisionDrawPrimitive( Renderer::Object::ILine3D *pLine );
	};
}
}
