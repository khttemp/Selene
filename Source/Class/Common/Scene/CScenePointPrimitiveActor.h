#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Class/Common/Scene/CSceneActorMaterial.h"
#include "Class/Common/Scene/CScenePointPrimitiveActorObject.h"
#include "Class/Common/Object/CRenderObject.h"
#include "Class/Platform/Render/CVertexLayout.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Class/Common/Render/Model/CFrame.h"
#include "Interface/Surface/ITexture.h"
#include "Interface/Scene/IScenePrimitiveActor.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class CScenePointActor : public Renderer::CRenderObject, public IPrimitiveActor
	{
	protected:
		Renderer::Object::CPoint3D *m_pPoint;
		CScenePointActorObject *m_pObject;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CScenePointActor( CSceneManagerBase *pSceneMgr, Renderer::Object::IPoint3D *pObject, Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr );
		virtual ~CScenePointActor();

	public:
		virtual void TransformReset( void );
		virtual void TransformUpdate( void );
		virtual void RenderingRequest( void );
		virtual void SetBoneMatrixArray( Math::Matrix *pMatrix, Sint32 Count ){}
		virtual void SetShader( Renderer::Shader::IShader *pShader );
		virtual void SetMaterialColor( Math::Vector4D &vColor ){}
		virtual void SetEmissiveColor( Math::Vector4D &vColor ){}
		virtual void SetSpecularColor( Math::Vector4D &vColor ){}
		virtual void SetSpecularRefractive( Float fParam ){}
		virtual void SetSpecularRoughly( Float fParam ){}
	};
}
}
