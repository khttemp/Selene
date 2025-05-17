#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Common/SMF.h"
#include "Collision/Line3D.h"
#include "Class/Platform/Render/Shader/ShaderManager.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class CInstanceModelControllerObject
	{
	protected:
		Renderer::Object::CFrame *m_ppBoneFramePointer[MAX_BONE_COUNT];
		Renderer::Object::CFrame *m_pParentFrame;
		Sint32 m_BoneCount;
		Math::SMatrix4x4 m_mBone[MAX_BONE_COUNT];
		Math::Matrix m_mWorld;
		Math::Matrix m_mWorldInverse;

		Math::Vector3D m_vCullBoxPoints[8];
		Collision::CBox m_CullBox;
		Renderer::Object::CMesh *m_pMesh;

		Bool m_IsCullTest;
		Bool m_IsDrawEnable;

	public:
		CInstanceModelControllerObject();
		~CInstanceModelControllerObject();

		virtual const Math::Matrix &GetWorldMatrix( void );
		virtual const Math::Matrix &GetWorldInverseMatrix( void );

		virtual Bool GetDrawEnable( void );
		virtual void SetDrawEnable( Bool IsEnable );

		virtual void Update( void );

		virtual void SetMeshPointer( Renderer::Object::CMesh *pMesh );
		virtual void SetParentFrame( Renderer::Object::CFrame *pParentFrame );

		virtual void SetBoneCount( Sint32 Count, Renderer::Object::CFrame *pFrameTbl[] );
		virtual Sint32 GetBoneCount( void );
		virtual const Math::SMatrix4x4 *GetBoneMatrixArray( void );

		virtual void SetCullTestEnable( Bool IsEnable );
		virtual void SetCullBoxPoints( const Math::Vector3D *pPts );
		virtual const Collision::CBox &GetCullBox( void );

	public:
		virtual Bool GetCullTestEnable( void );

		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out, Collision::CBox &Box );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out, Collision::CBox &Box );

		virtual void CreateCollisionDrawPrimitive( Renderer::Object::ILine3D *pLine );

		virtual void RenderingBounding( Renderer::Object::ILine3D *pLine );
	};
}
}
