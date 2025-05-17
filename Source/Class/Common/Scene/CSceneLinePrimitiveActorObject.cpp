

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CSceneLinePrimitiveActorObject.h"
#include "Class/Common/Render/Model/CFrame.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Platform/Render/CVertexLayout.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CIndexBuffer.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSceneLineActorObject::CSceneLineActorObject( CSceneManagerBase *pScene ) : CActorObject( pScene )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSceneLineActorObject::~CSceneLineActorObject()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneLineActorObject::Update( Math::Matrix &mWorld, Math::Matrix &mWorldInverse )
{
	m_mWorld[m_Page] = mWorld;
	m_mWorldInverse[m_Page] = mWorldInverse;

	m_vCenter.TransformCoord( m_vCenterBase, mWorld );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneLineActorObject::SetStreamSource( Renderer::CRender *pRender )
{
	pRender->SetVertexStream( m_pVS );
	pRender->SetVertexBuffer( &m_pVB_Base, 1 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CSceneLineActorObject::Rendering( Sint32 MaterialNo, Renderer::CRender *pRender )
{
	if ( MaterialNo == 0 )
	{
		Sint32 PrimitiveCount = m_pVB_Base->GetCount() / 2;

		// レンダリング
		pRender->DrawPrimitive( PRIMITIVE_LINE, PrimitiveCount );

		return PrimitiveCount;
	}

	return 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CSceneLineActorObject::Rendering_Velocity( Renderer::CRender *pRender )
{
	Sint32 PrimitiveCount = m_pVB_Base->GetCount() / 2;

	// レンダリング
	pRender->DrawPrimitive( PRIMITIVE_LINE, PrimitiveCount );

	return PrimitiveCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneLineActorObject::IsAlphaEnable( void )
{
	return m_pMaterial[0].GetDrawType() != DRAW_TYPE_NORMAL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneLineActorObject::GetSoftBillboardEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneLineActorObject::GetCullTestEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneLineActorObject::GetParallaxEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneLineActorObject::GetSpecularEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneLineActorObject::GetEnvironmentEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eTransformType CSceneLineActorObject::GetTransformType( void )
{
	return TRANSFORM_TYPE_MODEL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneLineActorObject::UpdateMaterial( Renderer::CRender *pRender )
{
	Renderer::SRenderState &State = pRender->GetRenderState();

	m_pMaterial[0].SetDrawType( State.DrawType );
	m_pMaterial[0].SetCullType( State.CullType );
	m_pMaterial[0].SetAlphaBoundary( State.AlphaBoundary );
	m_pMaterial[0].SetAlphaTestEnable( State.IsAlphaTestEnable );
	m_pMaterial[0].SetZTestEnable( State.IsDepthTestEnable );
	m_pMaterial[0].SetZWriteEnable( State.IsDepthWriteEnable );
}

