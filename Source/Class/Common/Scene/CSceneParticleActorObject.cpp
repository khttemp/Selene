

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CSceneParticleActorObject.h"
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
CParticleActorObject::CParticleActorObject( CSceneManagerBase *pScene ) : CActorObject( pScene )
	, m_IsSoftBillboardEnable	( false )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CParticleActorObject::~CParticleActorObject()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CParticleActorObject::SetStreamSource( Renderer::CRender *pRender )
{
	// データ
	pRender->SetVertexStream( m_pVS );
	pRender->SetIndexBuffer( m_pIB );

	// 頂点
	Renderer::CVertexBuffer *pBufferTbl[] = {
		m_pVB_Base,
		m_pVB_Tex,
		m_pVB_Light,
		m_pVB_Bump,
		m_pVB_Animation,
	};
	pRender->SetVertexBuffer( pBufferTbl, 5 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CParticleActorObject::Rendering( Sint32 MaterialNo, Renderer::CRender *pRender )
{
	if ( MaterialNo == 0 )
	{
		Sint32 PrimitiveCount = m_pIB->GetCount() / 3;
		Sint32 VertexCount = m_pVB_Base->GetCount();

		// レンダリング
		pRender->DrawIndexedPrimitive( PRIMITIVE_TRIANGLE, VertexCount, PrimitiveCount );

		return PrimitiveCount;
	}

	return 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CParticleActorObject::Rendering_Velocity( Renderer::CRender *pRender )
{
	Sint32 PrimitiveCount = m_pIB->GetCount() / 3;
	Sint32 VertexCount = m_pVB_Base->GetCount();

	// レンダリング
	pRender->DrawIndexedPrimitive( PRIMITIVE_TRIANGLE, VertexCount, PrimitiveCount );

	return PrimitiveCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CParticleActorObject::IsAlphaEnable( void )
{
	return m_pMaterial[0].GetDrawType() != DRAW_TYPE_NORMAL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CParticleActorObject::SetSoftBillboardEnable( Bool IsSoftBillboard )
{
	m_IsSoftBillboardEnable = IsSoftBillboard;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CParticleActorObject::GetSoftBillboardEnable( void )
{
	return m_IsSoftBillboardEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CParticleActorObject::GetCullTestEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CParticleActorObject::GetParallaxEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CParticleActorObject::GetSpecularEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CParticleActorObject::GetEnvironmentEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eTransformType CParticleActorObject::GetTransformType( void )
{
	return TRANSFORM_TYPE_BILLBOARD;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CParticleActorObject::UpdateMaterial( Renderer::CRender *pRender )
{
	Renderer::SRenderState &State = pRender->GetRenderState();

	m_pMaterial[0].SetDrawType( State.DrawType );
	m_pMaterial[0].SetCullType( State.CullType );
	m_pMaterial[0].SetAlphaBoundary( State.AlphaBoundary );
	m_pMaterial[0].SetAlphaTestEnable( State.IsAlphaTestEnable );
	m_pMaterial[0].SetZTestEnable( State.IsDepthTestEnable );
	m_pMaterial[0].SetZWriteEnable( State.IsDepthWriteEnable );
}
