#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Platform/Render/Shader/ShaderManager.h"
#include "Class/Platform/Render/CVertexLayout.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Class/Common/Scene/CSceneActorMaterial.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class CActorObject
	{
	protected:
		Sint32 m_RenderActorID;
		Sint32 m_Page;
		Sint32 m_MaterialCount;
		CSceneActorMaterial *m_pMaterial;
		CSceneManagerBase *m_pSceneMgr;

		Renderer::CIndexBuffer *m_pIB;
		Renderer::CVertexLayout *m_pVS;
		Renderer::CVertexBuffer *m_pVB_Base;
		Renderer::CVertexBuffer *m_pVB_Tex;
		Renderer::CVertexBuffer *m_pVB_Light;
		Renderer::CVertexBuffer *m_pVB_Bump;
		Renderer::CVertexBuffer *m_pVB_Animation;

		Math::Matrix m_mWorld[2];
		Math::Matrix m_mWorldInverse[2];

		Math::Vector3D m_vCenter;
		Math::Vector3D m_vCenterBase;

	public:
		CActorObject( CSceneManagerBase *pScene );
		virtual ~CActorObject();
		virtual Bool IsInvalid( void );
		virtual Sint32 Release( void );
		virtual Sint32 AddRef( void );
		virtual Bool IsSupportVertexBone( void );
		virtual Bool IsSupportVertexTexture( void );
		virtual Bool IsSupportVertexNormal( void );
		virtual Bool IsSupportVertexBump( void );
		virtual void SetMateriaCount( Sint32 Count );
		virtual Sint32 GetMaterialCount( void );
		virtual CSceneActorMaterial &GetSceneRenderMaterial( Sint32 Index );
		virtual ICustomizedSceneRenderMaterial *GetMaterialPointer( Sint32 Index );
		virtual void SetStream( Renderer::CIndexBuffer *pIB, Renderer::CVertexLayout *pVS, Renderer::CVertexBuffer *pVB_Base, Renderer::CVertexBuffer *pVB_Tex, Renderer::CVertexBuffer *pVB_Light, Renderer::CVertexBuffer *pVB_Bump, Renderer::CVertexBuffer *pVB_Animation );
		virtual Sint32 GetRenderActorID( void );
		virtual void SetCenter( const Math::Vector3D &vCenter );
		virtual const Math::Vector3D &GetCenter( void );
		virtual Sint32 GetBoneCount( void );
		virtual const Math::Matrix &GetWorldMatrix( void );
		virtual const Math::Matrix &GetWorldMatrixPrev( void );
		virtual const Math::Matrix &GetWorldInverseMatrix( void );
		virtual const Math::Matrix &GetWorldInverseMatrixPrev( void );
		virtual const Math::SMatrix4x4 *GetBoneMatrixArray( void );
		virtual const Math::SMatrix4x4 *GetBoneMatrixArrayPrev( void );
		virtual const Collision::CBox &GetCullBox( void );
		virtual void Flip( void );
		virtual Bool IsInstanceModel( void );

	public:
		virtual void SetStreamSource( Renderer::CRender *pRender )							= 0;
		virtual Sint32 Rendering( Sint32 MaterialNo, Renderer::CRender *pRender )			= 0;
		virtual Sint32 Rendering_Velocity( Renderer::CRender *pRender )						= 0;
		virtual eTransformType GetTransformType( void )										= 0;
		virtual Bool IsAlphaEnable( void )													= 0;
		virtual Bool GetSoftBillboardEnable( void )											= 0;
		virtual Bool GetCullTestEnable( void )												= 0;
		virtual Bool GetParallaxEnable( void )												= 0;
		virtual Bool GetSpecularEnable( void )												= 0;
		virtual Bool GetEnvironmentEnable( void )											= 0;
	};
}
}
