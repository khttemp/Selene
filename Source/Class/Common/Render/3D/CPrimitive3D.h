#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Platform/Render/CRender.h"
#include "Class/Common/Render/3D/CPrimitive3DBase.h"
#include "Class/Common/Scene/CScenePrimitiveActorObject.h"
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
	class CPrimitive3D : public CPrimitive3DBase, public IPrimitive3D
	{
	protected:
		Bool m_IsSoftBillboard;
		Bool m_IsBillboard;
		Sint32 m_VertexFlag;
		Bool IsVertexBegin;
		Bool IsIndexBegin;

	public:
		virtual void CreateRenderActor( Scene::CPrimitiveActorObject *pActor );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

		virtual Bool IsSupportVertexBone( void )    { return m_pVB_Animation != NULL; } 
		virtual Bool IsSupportVertexTexture( void ) { return m_pVB_Tex != NULL; } 
		virtual Bool IsSupportVertexNormal( void )  { return m_pVB_Light != NULL; }
		virtual Bool IsSupportVertexBump( void )    { return false; }

	public:
		CPrimitive3D( CRender *pRender, CRenderObjectMgr *pMgr, Bool IsBillboard, Bool IsSoftBillboard );
		virtual ~CPrimitive3D();

		virtual Bool Create( Sint32 VertexMax, Sint32 IndexMax, Sint32 VertexFlag, Bool IsDynamicVertex, Bool IsDynamicIndex );

		virtual Bool Push( const void *pIndex, Sint32 IndexCount );

		virtual Bool Push( const SVertex3DBase *pVtx, Sint32 Count );
		virtual Bool Push( const SVertex3DTexture *pVtx, Sint32 Count );
		virtual Bool Push( const SVertex3DLight *pVtx, Sint32 Count );
		virtual Bool Push( const SVertex3DBump *pVtx, Sint32 Count );
		virtual Bool Push( const SVertex3DAnimation *pVtx, Sint32 Count );

		virtual Sint32 GetVertexCount( void );
		virtual Sint32 GetIndexCount( void );

		virtual void Begin( Bool IsVertex, Bool IsIndex, Bool IsDirect );
		virtual void End( void );
	};
}
}
}
