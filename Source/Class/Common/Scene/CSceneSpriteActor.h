#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Class/Common/Scene/CSceneActorMaterial.h"
#include "Class/Common/Scene/CSceneSpriteActorObject.h"
#include "Class/Common/Object/CRenderObject.h"
#include "Class/Platform/Render/CVertexLayout.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Class/Common/Render/Model/CFrame.h"
#include "Interface/Surface/ITexture.h"
#include "Interface/Scene/ISceneSpriteActor.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class CSpriteActor : public Renderer::CRenderObject, public ISpriteActor
	{
	protected:
		Renderer::Object::CSprite3D *m_pSprite;
		CSpriteActorObject *m_pObject;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CSpriteActor( CSceneManagerBase *pSceneMgr, Renderer::Object::ISprite3D *pObject, Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr );
		virtual ~CSpriteActor();

	public:
		virtual void TransformReset( void );
		virtual void TransformUpdate( void );
		virtual void RenderingRequest( void );
	};
}
}
