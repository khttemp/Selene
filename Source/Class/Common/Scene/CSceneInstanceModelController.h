#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Class/Common/Scene/CSceneInstanceModelControllerObject.h"
#include "Class/Common/Object/CRenderObject.h"
#include "Class/Common/Render/Model/CCollisionController.h"
#include "Interface/Scene/ISceneInstanceModelController.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class CInstanceModelController : public Renderer::CRenderObject, public IInstanceModelController
	{
	protected:
		Renderer::Object::CModel *m_pModel;
		Sint32 m_ObjectCount;
		CInstanceModelControllerObject **m_pObjectTbl;
		Renderer::Object::CCollisionController *m_pCollision;
		Sint32 m_AnimationCount;
		Renderer::Object::CAnimationController **m_pAnimationCtrlTbl;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CInstanceModelController( CSceneManagerBase *pSceneMgr, Renderer::Object::IModel *pObject, Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr );
		virtual ~CInstanceModelController();

	public:
		CInstanceModelControllerObject *GetControllerObject( Sint32 Index );

		virtual void UpdateAnimation( Sint32 AnimationNo, Float fAnimationTime );
		virtual void UpdateAnimation( Sint32 AnimationNo1, Float fAnimationTime1, Sint32 AnimationNo2, Float fAnimationTime2, Float fWeight );
		virtual Sint32 GetAnimationCount( void );
		virtual Float GetAnimationLastTime( Sint32 AnimationNo );
		virtual void TransformReset( void );
		virtual void TransformUpdate( void );
		virtual void TransformUpdateCollisionOnly( void );
		virtual void TransformUpdateActorOnly( void );
		virtual void RenderingRequest( void );
		virtual void RenderingBounding( Renderer::Object::ILine3D *pLine );

		virtual void SetCullTestEnable( Bool IsEnable );

		virtual Sint32 GetFrameCount( void );

		virtual Sint32 Frame_GetIndex( const char *pName );
		virtual Math::Matrix &Frame_GetTransformLocal( Sint32 Index );
		virtual Math::Matrix &Frame_GetTransformWorld( Sint32 Index );

		virtual void Collision_Create( void );
		virtual void Collision_SetEnable( Sint32 Index, Bool IsEnable );
		virtual void Collision_SetEnable( const char *pName, Bool IsEnable );
		virtual void Collision_Rendering( Renderer::Object::ILine3D *pLine );
		virtual void Collision_GetResult( Sint32 &FrameNo, Math::Vector3D &vPos );
		virtual Bool Collision_Check( IModelActor *pSrc );
		virtual Bool Collision_Check( Collision::CBox &Src );
		virtual Bool Collision_Check( Collision::CLine3D &Src );
		virtual Bool Collision_Check( Math::Vector3D &Src );
		virtual Bool Collision_CheckOnScreen( Math::Vector2D &Src, ISceneManager *pSceneMgr );

		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out, Collision::CBox &Box );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out, Collision::CBox &Box );

		virtual void CreateCollisionDrawPrimitive( Renderer::Object::ILine3D *pLine );
	};
}
}
