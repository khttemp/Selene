

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Scene/CCustomizedSceneRenderObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCustomizedSceneRenderObject::CCustomizedSceneRenderObject()
	: pActor					( NULL )
	, fKey						( 0.0f )
	, fShadowRadius				( 1.0f )
	, ProjectionShadowType		( PROJECTION_SHADOW_DISABLE )
	, ProjectionShadowPriority	( PROJECTION_SHADOW_PRIORITY_0 )
	, MotionBlurLevel			( MOTION_BLUR_LIGHT )
	, IsActive					( false )
	, IsRender					( false )
	, IsSkydoom					( false )
	, PointLightCount			( 0 )
	, pNext						( NULL )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCustomizedSceneRenderObject::~CCustomizedSceneRenderObject()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCustomizedSceneRenderObject::IsSupportVertexBone( void )
{
	return pActor->IsSupportVertexBone();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCustomizedSceneRenderObject::IsSupportVertexTexture( void )
{
	return pActor->IsSupportVertexTexture();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCustomizedSceneRenderObject::IsSupportVertexNormal( void )
{
	return pActor->IsSupportVertexNormal();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCustomizedSceneRenderObject::IsSupportVertexBump( void )
{
	return pActor->IsSupportVertexBump();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CCustomizedSceneRenderObject::GetMaterialCount( void )
{
	return pActor->GetMaterialCount();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ICustomizedSceneRenderMaterial *CCustomizedSceneRenderObject::GetMaterialPointer( Sint32 Index )
{
	return pActor->GetMaterialPointer( Index );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CCustomizedSceneRenderObject::GetBoneCount( void )
{
	return pActor->GetBoneCount();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CCustomizedSceneRenderObject::GetWorldViewMatrix( void )
{
	return mWorldView;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CCustomizedSceneRenderObject::GetWorldViewPrevMatrix( void )
{
	return mWorldViewPrev;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CCustomizedSceneRenderObject::GetWorldViewProjectionMatrix( void )
{
	return mWorldViewProjection;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CCustomizedSceneRenderObject::GetWorldViewProjectionPrevMatrix( void )
{
	return mWorldViewProjectionPrev;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CCustomizedSceneRenderObject::GetWorldMatrix( void )
{
	return pActor->GetWorldMatrix();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CCustomizedSceneRenderObject::GetWorldMatrixPrev( void )
{
	return pActor->GetWorldMatrixPrev();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CCustomizedSceneRenderObject::GetWorldInverseMatrix( void )
{
	return pActor->GetWorldInverseMatrix();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CCustomizedSceneRenderObject::GetWorldInverseMatrixPrev( void )
{
	return pActor->GetWorldInverseMatrixPrev();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::SMatrix4x4 *CCustomizedSceneRenderObject::GetBoneMatrixArray( void )
{
	return pActor->GetBoneMatrixArray();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::SMatrix4x4 *CCustomizedSceneRenderObject::GetBoneMatrixArrayPrev( void )
{
	return pActor->GetBoneMatrixArrayPrev();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCustomizedSceneRenderObject::SetStreamSource( Renderer::IRender *pRender )
{
	pActor->SetStreamSource( (Renderer::CRender*)pRender );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CCustomizedSceneRenderObject::Rendering( Sint32 MaterialNo, Renderer::IRender *pRender )
{
	return pActor->Rendering( MaterialNo, (Renderer::CRender*)pRender );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CCustomizedSceneRenderObject::Rendering_Velocity( Renderer::IRender *pRender )
{
	return pActor->Rendering_Velocity( (Renderer::CRender*)pRender );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eTransformType CCustomizedSceneRenderObject::GetTransformType( void )
{
	return pActor->GetTransformType();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCustomizedSceneRenderObject::IsAlphaEnable( void )
{
	return pActor->IsAlphaEnable();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCustomizedSceneRenderObject::GetSoftBillboardEnable( void )
{
	return pActor->GetSoftBillboardEnable();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCustomizedSceneRenderObject::GetCullTestEnable( void )
{
	return pActor->GetCullTestEnable();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCustomizedSceneRenderObject::GetParallaxEnable( void )
{
	return pActor->GetParallaxEnable();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCustomizedSceneRenderObject::GetSpecularEnable( void )
{
	return pActor->GetSpecularEnable();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCustomizedSceneRenderObject::GetEnvironmentEnable( void )
{
	return pActor->GetEnvironmentEnable();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ICustomizedSceneRenderObject *CCustomizedSceneRenderObject::GetNextObject( void )
{
	return pNext;
}

