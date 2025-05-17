#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Object/CRenderObject.h"
#include "Interface/Render/Model/IModel.h"
#include "Interface/Render/IRender.h"
#include "Math/Style.h"
#include "Collision/Line3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CModel : public CRenderObject, public IModel
	{
	private:
		CAnimationController **m_pAnimationControllerList;
		CFrame **m_pFrameList;
		CMesh **m_pMeshList;
		Sint32 m_AnimationControllerListCount;
		Sint32 m_FrameListCount;
		Sint32 m_MeshListCount;
		CRenderObjectMgr *m_pMeshMgr;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CModel( CRender *pRender, CRenderObjectMgr *pMgr );
		virtual ~CModel();

		virtual void CreateAnimationController( Sint32 AnimationControllerCount );
		virtual void CreateFrameList( Sint32 FrameCount );
		virtual void CreateMeshList( Sint32 MeshCount );

		virtual CAnimationController *GetAnimationControllerPointer( Sint32 Index );
		virtual CFrame *GetFramePointer( Sint32 Index );
		virtual CMesh *GetMeshPointer( Sint32 Index );

		virtual CFrame *GetFramePointer( const char *pName );

		virtual void UpdateMesh( void );

	public:
		virtual void SetTransform( Math::Style &Style );
		virtual void CreateCollision( CCollisionController *&pCollision );

		virtual Bool GetAnimationController( Sint32 Index, CAnimationController *&pAnimationController );
		virtual Sint32 GetAnimationControllerCount( void );
		virtual CFrame *GetFrame( Sint32 Index );
		virtual Sint32 GetFrameCount( void );
		virtual CMesh *GetMesh( Sint32 Index );
		virtual Sint32 GetMeshCount( void );

		virtual void ResetAnimationTransform( void );
		virtual void UpdateAnimation( Sint32 AnimationNo );
		virtual void UpdateAnimation( Sint32 AnimationNo1, Sint32 AnimationNo2, Float fWeight );
	};
}
}
}
