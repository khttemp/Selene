#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Common/SMF.h"
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
	class CModelActorObject : public CActorObject
	{
	protected:
		Renderer::Object::CFrame *m_ppBoneFramePointer[MAX_BONE_COUNT];
		Renderer::Object::CFrame *m_pParentFrame;
		Sint32 m_BoneCount;
		Math::SMatrix4x4 m_mBone[2][MAX_BONE_COUNT];

		Math::Vector3D m_vCullBoxPoints[8];
		Collision::CBox m_CullBox;
		Renderer::Object::CMesh *m_pMesh;

		Bool m_IsCullTest;
		Bool m_IsParallax;
		Bool m_IsSpecular;
		Bool m_IsEnvironment;
		Bool m_IsDrawEnable;

	public:
		CModelActorObject( CSceneManagerBase *pScene );
		~CModelActorObject();

		virtual void Update( void );
		virtual void SetMeshPointer( Renderer::Object::CMesh *pMesh );
		virtual void SetParentFrame( Renderer::Object::CFrame *pParentFrame );
		virtual void SetBoneCount( Sint32 Count, Renderer::Object::CFrame *pFrameTbl[] );
		virtual void SetParallaxEnable( Bool IsEnable );
		virtual void SetSpecularEnable( Bool IsEnable );
		virtual void SetEnvironmentEnable( Bool IsEnable );
		virtual void SetCullTestEnable( Bool IsEnable );
		virtual void SetCullBoxPoints( const Math::Vector3D *pPts );

		virtual void RenderingBounding( Renderer::Object::ILine3D *pLine );

		virtual const Collision::CBox &GetCullBox( void );
		virtual Sint32 GetBoneCount( void );
		virtual const Math::SMatrix4x4 *GetBoneMatrixArray( void );
		virtual const Math::SMatrix4x4 *GetBoneMatrixArrayPrev( void );

	public:
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

		virtual void SetDrawEnable( Bool IsDrawEnable );
		virtual Bool GetDrawEnable( void );

		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out, Collision::CBox &Box );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out, Collision::CBox &Box );

		virtual void CreateCollisionDrawPrimitive( Renderer::Object::ILine3D *pLine );
	};
}
}
