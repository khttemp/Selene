#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CSceneModelActor.h"
#include "Class/Common/Scene/CSceneInstanceModelActorObject.h"
#include "Class/Common/Object/CRenderPrimitiveObject.h"
#include "Class/Common/Render/Model/CMaterial.h"
#include "Class/Common/Render/CCollision.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CMesh : public CRenderPrimitiveObject
	{
	protected:
		CFrame *m_pParentFrame;
		Sint32 m_MaterialCount;
		CMaterial *m_pMaterials;
		Sint32 m_VertexFlag;
		Sint32 m_BoneCount;
		CFrame **m_ppBoneFramePointer;
		Math::Vector3D m_vCenter;
		Math::Vector3D m_vCullBoxPoints[8];

		CCollision *m_pCollision;

	public:
		virtual void CreateRenderActor( Scene::CModelActorObject *pActor );
		virtual void CreateRenderActor( Scene::CSceneInstanceModelActorObject *pActor, Sint32 InstanceCount );

	public:
		CMesh( CRender *pRender, CRenderObjectMgr *pMgr );
		virtual ~CMesh();

		virtual Bool IsSupportVertexBone( void )    { return m_pVB_Animation != NULL; } 
		virtual Bool IsSupportVertexTexture( void ) { return m_pVB_Tex != NULL; } 
		virtual Bool IsSupportVertexNormal( void )  { return m_pVB_Light != NULL; }
		virtual Bool IsSupportVertexBump( void )    { return m_pVB_Bump != NULL; }

		virtual void CreateMaterialList( Sint32 MaterialCount );

		virtual void CreateVertex( eVertexElement Type, Sint32 Count );
		virtual void CreateIndex( Sint32 Count );
		virtual void UpdateStream( void );

		virtual void LockVertex( eVertexElement Type );
		virtual void UnLockVertex( eVertexElement Type );

		virtual void LockIndex( void );
		virtual void UnLockIndex( void );

		virtual Bool Push( const SVertex3DBase *pVtx, Sint32 Count );
		virtual Bool Push( const SVertex3DTexture *pVtx, Sint32 Count );
		virtual Bool Push( const SVertex3DLight *pVtx, Sint32 Count );
		virtual Bool Push( const SVertex3DBump *pVtx, Sint32 Count );
		virtual Bool Push( const SVertex3DAnimation *pVtx, Sint32 Count );

		virtual Bool Push( const void *pIndex, Sint32 IndexCount );

		virtual Bool GetSupportTexture( void );
		virtual Bool GetSupportLight( void );
		virtual Bool GetSupportBump( void );

		virtual void SetParentFrame( CFrame *pFrame );

		virtual void SetBoneCount( Sint32 Count );
		virtual void SetBoneData( Sint32 Index, CFrame *pFrame );

		virtual void SetBounding( Collision::CBox &Box );

		virtual void CreateCollisionAttribute( SCollisionAttribute *pAttr, Sint32 Count );
		virtual void CreateCollisionFace( SCollisionFace *pFace, Sint32 Count );
		virtual void CreateCollisionVertex( SCollisionVertex *pVtx, Sint32 Count );

		virtual CCollision *GetCollision( void );

		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResult &Out );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResult &Out, Collision::CBox &Box );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResultExtend &Out );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResultExtend &Out, Collision::CBox &Box );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual Sint32 GetMaterialCount( void );
		virtual Bool GetMaterial( Sint32 Index, CMaterial *&pMaterial );
	};
}
}
}
