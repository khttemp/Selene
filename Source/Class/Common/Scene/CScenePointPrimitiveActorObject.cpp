

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CScenePointPrimitiveActorObject.h"
#include "Class/Platform/Render/CVertexLayout.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Class/Common/Render/Model/CFrame.h"
#include "Class/Common/Core/CCore.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CScenePointActorObject::CScenePointActorObject( CSceneManagerBase *pScene ) : CActorObject( pScene )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CScenePointActorObject::~CScenePointActorObject()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CScenePointActorObject::Update( Math::Matrix &mWorld, Math::Matrix &mWorldInverse )
{
	m_mWorld[m_Page] = mWorld;
	m_mWorldInverse[m_Page] = mWorldInverse;

	m_vCenter.TransformCoord( m_vCenterBase, mWorld );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CScenePointActorObject::SetStreamSource( Renderer::CRender *pRender )
{
	pRender->SetVertexStream( m_pVS );
	pRender->SetVertexBuffer( &m_pVB_Base, 1 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CScenePointActorObject::Rendering( Sint32 MaterialNo, Renderer::CRender *pRender )
{
	if ( MaterialNo == 0 )
	{
		Sint32 PrimitiveCount = m_pVB_Base->GetCount();

		// レンダリング
		pRender->DrawPrimitive( PRIMITIVE_POINT, PrimitiveCount );

		return PrimitiveCount;
	}

	return 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CScenePointActorObject::Rendering_Velocity( Renderer::CRender *pRender )
{
	Sint32 PrimitiveCount = m_pVB_Base->GetCount();

	// レンダリング
	pRender->DrawPrimitive( PRIMITIVE_POINT, PrimitiveCount );

	return PrimitiveCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CScenePointActorObject::IsAlphaEnable( void )
{
	return m_pMaterial[0].GetDrawType() != DRAW_TYPE_NORMAL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CScenePointActorObject::GetSoftBillboardEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CScenePointActorObject::GetCullTestEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CScenePointActorObject::GetParallaxEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CScenePointActorObject::GetSpecularEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CScenePointActorObject::GetEnvironmentEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eTransformType CScenePointActorObject::GetTransformType( void )
{
	return TRANSFORM_TYPE_MODEL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CScenePointActorObject::UpdateMaterial( Renderer::CRender *pRender )
{
	Renderer::SRenderState &State = pRender->GetRenderState();

	m_pMaterial[0].SetDrawType( State.DrawType );
	m_pMaterial[0].SetCullType( State.CullType );
	m_pMaterial[0].SetAlphaBoundary( State.AlphaBoundary );
	m_pMaterial[0].SetAlphaTestEnable( State.IsAlphaTestEnable );
	m_pMaterial[0].SetZTestEnable( State.IsDepthTestEnable );
	m_pMaterial[0].SetZWriteEnable( State.IsDepthWriteEnable );
}

