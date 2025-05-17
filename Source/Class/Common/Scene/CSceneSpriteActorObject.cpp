

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CSceneSpriteActorObject.h"
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
CSpriteActorObject::CSpriteActorObject( CSceneManagerBase *pScene ) : CActorObject( pScene )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSpriteActorObject::~CSpriteActorObject()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSpriteActorObject::Update( Math::Matrix &mWorld, Math::Matrix &mWorldInverse )
{
	m_mWorld[m_Page] = mWorld;
	m_mWorldInverse[m_Page] = mWorldInverse;

	m_vCenter.TransformCoord( m_vCenterBase, mWorld );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSpriteActorObject::SetStreamSource( Renderer::CRender *pRender )
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
Sint32 CSpriteActorObject::Rendering( Sint32 MaterialNo, Renderer::CRender *pRender )
{
	if ( MaterialNo == 0 )
	{
		Sint32 SpriteCount = m_pIB->GetCount() / 3;
		Sint32 VertexCount = m_pVB_Base->GetCount();

		// レンダリング
		pRender->DrawIndexedPrimitive( PRIMITIVE_TRIANGLE, VertexCount, SpriteCount );

		return SpriteCount;
	}

	return 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CSpriteActorObject::Rendering_Velocity( Renderer::CRender *pRender )
{
	Sint32 SpriteCount = m_pIB->GetCount() / 3;
	Sint32 VertexCount = m_pVB_Base->GetCount();

	// レンダリング
	pRender->DrawIndexedPrimitive( PRIMITIVE_TRIANGLE, VertexCount, SpriteCount );

	return SpriteCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSpriteActorObject::IsAlphaEnable( void )
{
	return m_pMaterial[0].GetDrawType() != DRAW_TYPE_NORMAL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CSpriteActorObject::GetBoneCount( void )
{
	return 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSpriteActorObject::GetSoftBillboardEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSpriteActorObject::GetCullTestEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSpriteActorObject::GetParallaxEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSpriteActorObject::GetSpecularEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSpriteActorObject::GetEnvironmentEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eTransformType CSpriteActorObject::GetTransformType( void )
{
	return TRANSFORM_TYPE_MODEL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSpriteActorObject::UpdateMaterial( Renderer::CRender *pRender )
{
	Renderer::SRenderState &State = pRender->GetRenderState();

	m_pMaterial[0].SetDrawType( State.DrawType );
	m_pMaterial[0].SetCullType( State.CullType );
	m_pMaterial[0].SetAlphaBoundary( State.AlphaBoundary );
	m_pMaterial[0].SetAlphaTestEnable( State.IsAlphaTestEnable );
	m_pMaterial[0].SetZTestEnable( State.IsDepthTestEnable );
	m_pMaterial[0].SetZWriteEnable( State.IsDepthWriteEnable );
}
