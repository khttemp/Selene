#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Collision/Line3D.h"
#include "Class/Platform/Render/Shader/ShaderManager.h"
#include "Class/Common/Scene/CSceneActorObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	struct SInstanceMaterial
	{
		Renderer::CVertexBuffer *pVB_Base;
		Renderer::CVertexBuffer *pVB_Light;
		Renderer::CVertexBuffer *pVB_Bump;
		Renderer::CVertexBuffer *pVB_Tex;
		Renderer::CIndexBuffer *pIB;
	};

	class CSceneInstanceModelActorObject : public CActorObject
	{
	protected:
		Sint32 m_ControllerCount;
		CInstanceModelControllerObject **m_ppControllerTbl;
		Sint32 m_InstanceCount;
		Sint32 m_InstanceMaxCount;
		Bool m_IsParallax;
		Bool m_IsSpecular;
		Bool m_IsEnvironment;

		Renderer::CVertexBuffer *m_pVB_BaseOrg;
		Renderer::CVertexBuffer *m_pVB_LightOrg;
		Renderer::CVertexBuffer *m_pVB_BumpOrg;
		Renderer::CVertexBuffer *m_pVB_AnimationOrg;

		SInstanceMaterial *m_pInstanceMaterlaTbl;

	public:
		CSceneInstanceModelActorObject( CSceneManagerBase *pScene );
		~CSceneInstanceModelActorObject();

		virtual void TransformB( const Math::Matrix &mWorld, Sint32 Position );
		virtual void TransformBN( const Math::Matrix &mWorld, Sint32 Position );
		virtual void TransformBNT( const Math::Matrix &mWorld, Sint32 Position );

		virtual void TransformAB( const Math::SMatrix4x4 *pBoneMatrixTbl, Sint32 Position );
		virtual void TransformABN( const Math::SMatrix4x4 *pBoneMatrixTbl, Sint32 Position );
		virtual void TransformABNT( const Math::SMatrix4x4 *pBoneMatrixTbl, Sint32 Position );

		virtual void BeginInstance( void );
		virtual void EndInstance( void );
		virtual void UpdateInsntaceVertex( Sint32 Index, Sint32 Position );

		virtual Sint32 GetControllerCount( void );
		virtual CInstanceModelControllerObject *GetControllerObject( Sint32 Index );
		virtual void SetControllerCount( Sint32 Count );
		virtual void SetControllerObject( Sint32 Index, CInstanceModelControllerObject *pController );

		virtual void Update( void );
		virtual void SetParallaxEnable( Bool IsEnable );
		virtual void SetSpecularEnable( Bool IsEnable );
		virtual void SetEnvironmentEnable( Bool IsEnable );

		virtual void CreateMaterialVertex( Sint32 Count );
		virtual void SetMaterialData( Sint32 Index, Renderer::CVertexBuffer *pVB_Base, Renderer::CVertexBuffer *pVB_Light, Renderer::CVertexBuffer *pVB_Bump, Renderer::CVertexBuffer *pVB_Tex, Renderer::CIndexBuffer *pIB );

		virtual void SetInstanceMaxCount( Sint32 InstanceCount );
		virtual void SetRenderInstanceCount( Sint32 InstanceCount );
		virtual Sint32 GetRenderInstanceCount( void );

	public:
		virtual Bool IsInstanceModel( void );
		virtual void SetStreamSource( Renderer::CRender *pRender );
		virtual Sint32 Rendering( Sint32 MaterialNo, Renderer::CRender *pRender );
		virtual Sint32 Rendering_Velocity( Renderer::CRender *pRender );
		virtual eTransformType GetTransformType( void );
		virtual Bool IsAlphaEnable( void );
		virtual Bool GetSoftBillboardEnable( void );
		virtual Bool GetCullTestEnable( void );
		virtual Bool GetParallaxEnable( void );
		virtual Bool GetSpecularEnable( void );
		virtual Bool GetEnvironmentEnable( void );
	};
}
}
