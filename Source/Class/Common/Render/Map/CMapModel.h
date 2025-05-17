#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Object/CRenderObject.h"
#include "Class/Common/Render/CCollision.h"
#include "Interface/Render/Map/IMapModel.h"
#include "Interface/Render/IRender.h"
#include "Math/Style.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	template <typename Type>
	struct CTreeItem
	{
	public:
		Sint32 m_FirstFrameNo;

		CMapFrame **m_pFrameList;
		Sint32 m_FrameListCount;

		Type **m_pObjectList;
		Sint32 m_ObjectListCount;

		Sint32 *m_pAreaID;
		Math::Point3DI m_AreaCount;
		Math::Point3DF m_AreaSize;

	public:
		CTreeItem()
			: m_FirstFrameNo	( 0 )
			, m_pFrameList		( NULL )
			, m_FrameListCount	( 0 )
			, m_pObjectList		( NULL )
			, m_ObjectListCount	( 0 )
			, m_pAreaID			( NULL )
			, m_AreaCount		( 0, 0, 0 )
			, m_AreaSize		( 0.0f, 0.0f, 0.0f )
		{
		}

		~CTreeItem()
		{
			Sint32 Max;
			Max = m_FrameListCount;
			for ( Sint32 i = 0; i < Max; i++ )
			{
				SAFE_DELETE( m_pFrameList[i] );
			}
			SAFE_DELETE_ARRAY( m_pFrameList );

			Max = m_ObjectListCount;
			for ( Sint32 i = 0; i < Max; i++ )
			{
				SAFE_DELETE( m_pObjectList[i] );
			}
			SAFE_DELETE_ARRAY( m_pObjectList );

			SAFE_DELETE_ARRAY( m_pAreaID );
		}
	};

	class CMapModel : public CRenderObject, public IMapModel
	{
	private:
		CMapMaterial			*m_pMaterial;
		Sint32					m_MaterialListCount;

		CRenderObjectMgr		*m_pMeshMgr;
		Bool					*m_MeshDrawEnableTbl;

		CTreeItem<CMapMesh>		*m_pTreeDraw;
		CTreeItem<CCollision>	*m_pTreeCollision;

	private:
		virtual Bool Collision_ComputeMapArea( Collision::CLine3D Ray, Float fRadius, Math::Point3DI &PtStart, Math::Point3DI &PtEnd );
		virtual Math::Point3DI Collision_GetAreaPosition( const Math::Vector3D &vPos );
		virtual CCollision *Collision_GetArea( Sint32 x, Sint32 y, Sint32 z );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CMapModel( CRender *pRender, CRenderObjectMgr *pMgr );
		virtual ~CMapModel();

		virtual void RenderingBounding( Renderer::Object::ILine3D *pLine );

		virtual void SetAreaInfo( Math::Point3DI Count, Math::Point3DF Size );
		virtual void SetAreaID( Sint32 *pTbl );
		virtual void SetFirstFrame( Sint32 FirstFrame );
		virtual void CreateFrameList( Sint32 FrameCount );
		virtual void CreateMeshList( Sint32 MeshCount );
		virtual void CreateMaterialList( Sint32 MaterialCount );
		virtual CMapFrame *GetFramePointer( Sint32 Index );
		virtual CMapMesh *GetMeshPointer( Sint32 Index );
		virtual CMapMaterial *GetMaterialPointer( Sint32 Index );

		virtual void Collision_SetAreaInfo( Math::Point3DI Count, Math::Point3DF Size );
		virtual void Collision_SetAreaID( Sint32 *pTbl );
		virtual void Collision_SetFirstFrame( Sint32 FirstFrame );
		virtual void Collision_CreateFrameList( Sint32 FrameCount );
		virtual void Collision_CreateList( Sint32 FrameCount );
		virtual CMapFrame *Collision_GetFramePointer( Sint32 Index );
		virtual CCollision *Collision_GetPointer( Sint32 Index );

		virtual void UpdateMesh( void );
		virtual Sint32 GetMeshCount( void );
		virtual Sint32 GetCollisionCount( void );

		virtual void SetMeshDrawEnable( Sint32 Index );
		virtual Bool GetMeshDrawEnable( Sint32 Index );

	public:
		virtual void UpdateFrustumCulling( Scene::CSceneManagerBase *pScene );

		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResult &Out );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResult &Out, Collision::CBox &Box );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResultExtend &Out );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResultExtend &Out, Collision::CBox &Box );

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
}
