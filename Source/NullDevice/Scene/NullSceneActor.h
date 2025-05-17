#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Interface/Scene/ISceneInstanceModelActor.h"
#include "Interface/Scene/ISceneModelActor.h"
#include "Interface/Scene/ISceneMapActor.h"
#include "Interface/Scene/IScenePrimitiveActor.h"
#include "Interface/Scene/ISceneSpriteActor.h"
#include "Interface/Scene/ISceneParticleActor.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class NullSceneActor : public IInstanceModelActor, public IModelActor, public IMapActor, public IPrimitiveActor, public ISpriteActor, public IParticleActor
	{
	public:
		virtual Bool IsInvalid( void )
		{
			return true;
		}

		virtual Sint32 Release( void )
		{
			return 0;
		}

		virtual Sint32 AddRef( void	)
		{
			return 0;
		}

		virtual Sint32 GetObjectCount( void )
		{
			return 0;
		}

		virtual void RenderingRequest( void )
		{
		}

		virtual void RenderingBounding( Renderer::Object::ILine3D *pLine )
		{
		}

		virtual Sint32 GetCellCount( void )
		{
			return 0;
		}

		virtual Sint32 GetRenderingCellCount( void )
		{
			return 0;
		}

		virtual void TransformReset( void )
		{
		}

		virtual void TransformUpdate( void )
		{
		}

		virtual void TransformUpdateCollisionOnly( void )
		{
		}

		virtual void TransformUpdateActorOnly( void )
		{
		}

		virtual Sint32 GetAnimationCount( void )
		{
			return 0;
		}

		virtual Float GetAnimationLastTime( Sint32 AnimationNo )
		{
			return 0.0f;
		}

		virtual void UpdateAnimation( Sint32 AnimationNo, Float fAnimationTime )
		{
		}

		virtual void UpdateAnimation( Sint32 AnimationNo1, Float fAnimationTime1, Sint32 AnimationNo2, Float fAnimationTime2, Float fWeight )
		{
		}

		virtual void SetCullTestEnable( Bool IsEnable )
		{
		}

		virtual void SetBoneMatrixArray( Math::Matrix *pMatrix, Sint32 Count )
		{
		}

		virtual void SetShader( Renderer::Shader::IShader *pShader )
		{
		}

		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray )
		{
			return false;
		}

		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box )
		{
			return false;
		}

		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out )
		{
			return false;
		}

		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out, Collision::CBox &Box )
		{
			return false;
		}

		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out )
		{
			return false;
		}

		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out, Collision::CBox &Box )
		{
			return false;
		}

		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius )
		{
			return false;
		}

		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Collision::CBox &Box )
		{
			return false;
		}

		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphere &Out )
		{
			return false;
		}

		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphere &Out, Collision::CBox &Box )
		{
			return false;
		}

		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphereExtend &Out )
		{
			return false;
		}

		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphereExtend &Out, Collision::CBox &Box )
		{
			return false;
		}

		virtual Sint32 GetFrameCount( void )
		{
			return 0;
		}

		virtual Sint32 GetMeshCount( void )
		{
			return 0;
		}

		virtual void GetMesh_DrawEnable( Sint32 Index, Bool IsDrawEnable )
		{
		}

		virtual Sint32 GetMeshMaterialCount( Sint32 MeshIndex )
		{
			return 0;
		}

		virtual Sint32 Frame_GetIndex( const char *pName )
		{
			return -1;
		}

		virtual Math::Matrix &Frame_GetTransformLocal( Sint32 Index )
		{
			static Math::Matrix mTemp;
			mTemp.Identity();
			return mTemp;
		}

		virtual Math::Matrix &Frame_GetTransformWorld( Sint32 Index )
		{
			static Math::Matrix mTemp;
			mTemp.Identity();
			return mTemp;
		}

		virtual void MeshMaterial_SetShader( Sint32 MeshIndex, Sint32 MaterialIndex, Renderer::Shader::IShader *pShader )
		{
		}

		virtual void MeshMaterial_SetMaterialColor( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector4D &vColor )
		{
		}

		virtual void MeshMaterial_SetEmissiveColor( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector4D &vColor )
		{
		}

		virtual void MeshMaterial_SetSpecularColor( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector4D &vColor )
		{
		}

		virtual void MeshMaterial_SetSpecularRefractive( Sint32 MeshIndex, Sint32 MaterialIndex, Float fParam )
		{
		}

		virtual void MeshMaterial_SetSpecularRoughly( Sint32 MeshIndex, Sint32 MaterialIndex, Float fParam )
		{
		}

		virtual void MeshMaterial_SetDrawType( Sint32 MeshIndex, Sint32 MaterialIndex, eDrawType Type )
		{
		}

		virtual void MeshMaterial_SetTexture( Sint32 MeshIndex, Sint32 MaterialIndex, Renderer::ITexture *pTexture )
		{
		}

		virtual void MeshMaterial_SetTextureOffset( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector2D &Offset )
		{
		}

		virtual void Collision_Create( void )
		{
		}

		virtual void Collision_SetEnable( Sint32 Index, Bool IsEnable )
		{
		}

		virtual void Collision_SetEnable( const char *pName, Bool IsEnable )
		{
		}

		virtual void Collision_Rendering( Renderer::Object::ILine3D *pLine )
		{
		}

		virtual void Collision_GetResult( Sint32 &FrameNo, Math::Vector3D &vPos )
		{
		}

		virtual Bool Collision_Check( IModelActor *pSrc )
		{
			return false;
		}

		virtual Bool Collision_Check( Collision::CBox &Src )
		{
			return false;
		}

		virtual Bool Collision_Check( Collision::CLine3D &Src )
		{
			return false;
		}

		virtual Bool Collision_Check( Math::Vector3D &Src )
		{
			return false;
		}

		virtual Bool Collision_CheckOnScreen( Math::Vector2D &Src, ISceneManager *pSceneMgr )
		{
			return false;
		}

		virtual void CreateCollisionDrawPrimitive( Renderer::Object::ILine3D *pLine )
		{
		}

		virtual IInstanceModelController *GetController( Sint32 Index )
		{
			return NULL;
		}

		virtual void Begin( void )
		{
		}

		virtual void End( void )
		{
		}

		virtual void SetMaterialColor( Math::Vector4D &vColor )
		{
		}

		virtual void SetEmissiveColor( Math::Vector4D &vColor )
		{
		}

		virtual void SetSpecularColor( Math::Vector4D &vColor )
		{
		}

		virtual void SetSpecularRefractive( Float fParam )
		{
		}

		virtual void SetSpecularRoughly( Float fParam )
		{
		}
	};
}
}

