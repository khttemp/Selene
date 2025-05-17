#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Scene/CSceneActorObject.h"
#include "Interface/Scene/ICustomizedSceneRenderObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class CCustomizedSceneRenderObject : public ICustomizedSceneRenderObject
	{
	public:
		CActorObject *pActor;
		Float fKey;
		Float fShadowRadius;
		eProjectionShadowType ProjectionShadowType;
		eProjectionShadowPriority ProjectionShadowPriority;
		eSceneMotionBlurQuarity MotionBlurLevel;

		Bool IsActive;
		Bool IsRender;
		Bool IsSkydoom;

		Math::Matrix mWorldView;
		Math::Matrix mWorldViewPrev;
		Math::Matrix mWorldViewProjection;
		Math::Matrix mWorldViewProjectionPrev;
		Math::Matrix mShadowWorldViewProjection;

		Math::Vector3D vBrightness;
		Math::Vector4D vLightDiection;
		Math::Vector4D vPointLightPositionTbl[4];
		Math::Vector4D vPointLightColorTbl[4];
		Sint32 PointLightCount;

		CCustomizedSceneRenderObject *pNext;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return 1; }
		virtual Sint32 AddRef( void )  { return 1; }

	public:
		CCustomizedSceneRenderObject();
		virtual ~CCustomizedSceneRenderObject();
		virtual Bool IsSupportVertexBone( void );
		virtual Bool IsSupportVertexTexture( void );
		virtual Bool IsSupportVertexNormal( void );
		virtual Bool IsSupportVertexBump( void );
		virtual Sint32 GetMaterialCount( void );
		virtual ICustomizedSceneRenderMaterial *GetMaterialPointer( Sint32 Index );
		virtual Sint32 GetBoneCount( void );
		virtual const Math::Matrix &GetWorldViewMatrix( void );
		virtual const Math::Matrix &GetWorldViewPrevMatrix( void );
		virtual const Math::Matrix &GetWorldViewProjectionMatrix( void );
		virtual const Math::Matrix &GetWorldViewProjectionPrevMatrix( void );
		virtual const Math::Matrix &GetWorldMatrix( void );
		virtual const Math::Matrix &GetWorldMatrixPrev( void );
		virtual const Math::Matrix &GetWorldInverseMatrix( void );
		virtual const Math::Matrix &GetWorldInverseMatrixPrev( void );
		virtual const Math::SMatrix4x4 *GetBoneMatrixArray( void );
		virtual const Math::SMatrix4x4 *GetBoneMatrixArrayPrev( void );
		virtual void SetStreamSource( Renderer::IRender *pRender );
		virtual Sint32 Rendering( Sint32 MaterialNo, Renderer::IRender *pRender );
		virtual Sint32 Rendering_Velocity( Renderer::IRender *pRender );
		virtual eTransformType GetTransformType( void );
		virtual Bool IsAlphaEnable( void );
		virtual Bool GetSoftBillboardEnable( void );
		virtual Bool GetCullTestEnable( void );
		virtual Bool GetParallaxEnable( void );
		virtual Bool GetSpecularEnable( void );
		virtual Bool GetEnvironmentEnable( void );
		virtual ICustomizedSceneRenderObject *GetNextObject( void );
	};
}
}
