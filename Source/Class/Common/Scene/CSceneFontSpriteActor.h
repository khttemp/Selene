#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Class/Common/Scene/CSceneActorMaterial.h"
#include "Class/Common/Scene/CSceneParticleActorObject.h"
#include "Class/Common/Render/Model/CFrame.h"
#include "Class/Common/Object/CRenderObject.h"
#include "Class/Platform/Render/CVertexLayout.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Interface/Surface/ITexture.h"
#include "Interface/Scene/ISceneParticleActor.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class CSceneFontSpriteActor : public Renderer::CRenderObject, public IParticleActor
	{
	protected:
		Renderer::Object::CFontSprite3D *m_pFontSprite;
		CParticleActorObject **m_pObjectTbl;
		Sint32 m_ObjectCount;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CSceneFontSpriteActor( CSceneManagerBase *pSceneMgr, Renderer::Object::IFontSprite3D *pObject, Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr );
		virtual ~CSceneFontSpriteActor();

	public:
		virtual void TransformReset( void ) {}
		virtual void TransformUpdate( void ) {}
		virtual void RenderingRequest( void );
		virtual void SetBoneMatrixArray( Math::Matrix *pMatrix, Sint32 Count ){}
	};
}
}
