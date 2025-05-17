#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Class/Common/Scene/CSceneInstanceModelActorObject.h"
#include "Class/Common/Scene/CSceneInstanceModelController.h"
#include "Class/Common/Object/CRenderObject.h"
#include "Interface/Scene/ISceneInstanceModelActor.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class CInstanceModelActor : public Renderer::CRenderObject, public IInstanceModelActor
	{
	protected:
		Renderer::Object::CModel *m_pModel;
		Sint32 m_InstanceCount;
		CInstanceModelController **m_pControllerTbl;
		Sint32 m_ObjectCount;
		CSceneInstanceModelActorObject **m_pObjectTbl;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CInstanceModelActor( Sint32 InstanceCount, CSceneManagerBase *pSceneMgr, Renderer::Object::IModel *pObject, Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr );
		virtual ~CInstanceModelActor();

	public:
		virtual IInstanceModelController *GetController( Sint32 Index );
		virtual void Begin( void );
		virtual void End( void );
	};
}
}
