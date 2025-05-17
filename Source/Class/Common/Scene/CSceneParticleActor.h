#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Class/Common/Scene/CSceneActorMaterial.h"
#include "Class/Common/Scene/CSceneParticleActorObject.h"
#include "Class/Common/Object/CRenderObject.h"
#include "Class/Platform/Render/CVertexLayout.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Class/Common/Render/Model/CFrame.h"
#include "Interface/Surface/ITexture.h"
#include "Interface/Scene/ISceneParticleActor.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class CParticleActor : public Renderer::CRenderObject, public IParticleActor
	{
	protected:
		Renderer::Object::CParticle *m_pParticle;
		CParticleActorObject *m_pObject;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

		virtual void RenderingDirect( void );

	public:
		CParticleActor( CSceneManagerBase *pSceneMgr, Renderer::Object::IParticle *pObject, Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr );
		virtual ~CParticleActor();

	public:
		virtual void RenderingRequest( void );
	};
}
}
