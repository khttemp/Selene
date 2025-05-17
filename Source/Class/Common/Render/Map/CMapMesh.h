#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Object/CRenderPrimitiveObject.h"
#include "Class/Common/Scene/CSceneMapActorObject.h"
#include "Interface/Render/Map/IMapModel.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	struct SRenderTable
	{
		Sint32 MaterialId;
		Sint32 PolygonStart;
		Sint32 PolygonCount;
		Sint32 VertexStart;
		Sint32 VertexCount;
	};

	class CMapMesh : public CRenderPrimitiveObject
	{
	protected:
		CMapFrame *m_pParentFrame;
		Sint32 m_VertexFlag;
		Math::Vector3D m_vCenter;
		SRenderTable *m_pRenderTable;
		Sint32 m_RenderTblCount;

	public:
		CMapMesh( CRender *pRender, CRenderObjectMgr *pMgr );
		virtual ~CMapMesh();

		virtual Bool IsSupportVertexBone( void )    { return m_pVB_Animation != NULL; } 
		virtual Bool IsSupportVertexTexture( void ) { return m_pVB_Tex != NULL; } 
		virtual Bool IsSupportVertexNormal( void )  { return m_pVB_Light != NULL; }
		virtual Bool IsSupportVertexBump( void )    { return m_pVB_Bump != NULL; }

		virtual void SetRenderTable( Sint32 Index, SRenderTable &Tbl );
		virtual void CreateRenderTable( Sint32 Count );

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

		virtual Bool Push( const void *pIndex, Sint32 IndexCount );

		virtual void SetCenter( Math::Vector3D &vCenter );
		virtual void SetParentFrame( CMapFrame *pFrame );

		virtual const Collision::CBox &GetOBB( void );

		virtual void CreateRenderActor( Scene::CMapActorObject *pActor );
	};
}
}
}
