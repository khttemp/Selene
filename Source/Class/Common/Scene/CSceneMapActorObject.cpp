

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CSceneMapActorObject.h"
#include "Class/Platform/Render/CVertexLayout.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Class/Common/Render/Model/CFrame.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapActorObject::CMapActorObject( CSceneManagerBase *pScene ) : CActorObject( pScene )
	, m_IsParallax		( false )
	, m_IsSpecular		( false )
	, m_IsEnvironment	( false )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapActorObject::~CMapActorObject()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapActorObject::SetStreamSource( Renderer::CRender *pRender )
{
	pRender->SetVertexStream( m_pVS );
	pRender->SetIndexBuffer( m_pIB );

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
Sint32 CMapActorObject::Rendering( Sint32 MaterialNo, Renderer::CRender *pRender )
{
	CSceneActorMaterial &Mtrl = m_pMaterial[MaterialNo];

	Sint32 VertexStart		= Mtrl.GetVertexStart();
	Sint32 VertexCount		= Mtrl.GetVertexCount();
	Sint32 IndexStart		= Mtrl.GetIndexStart();
	Sint32 PrimitiveCount	= Mtrl.GetIndexCount() / 3;

	// レンダリング
	pRender->DrawMesh( VertexStart, VertexCount, IndexStart, PrimitiveCount );

	return PrimitiveCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CMapActorObject::Rendering_Velocity( Renderer::CRender *pRender )
{
	Sint32 VertexStart		= 0;
	Sint32 VertexCount		= m_pVB_Base->GetCount();
	Sint32 IndexStart		= 0;
	Sint32 PrimitiveCount	= m_pIB->GetCount() / 3;

	// レンダリング
	pRender->DrawMesh( VertexStart, VertexCount, IndexStart, PrimitiveCount );

	return PrimitiveCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapActorObject::IsAlphaEnable( void )
{
	Sint32 MtrlCnt = m_MaterialCount;
	for ( Sint32 i = 0; i < MtrlCnt; i++ )
	{
		if ( m_pMaterial[i].GetDrawType() != DRAW_TYPE_NORMAL )
		{
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapActorObject::SetParallaxEnable( Bool IsEnable )
{
	m_IsParallax = IsEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapActorObject::SetSpecularEnable( Bool IsEnable )
{
	m_IsSpecular = IsEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapActorObject::SetEnvironmentEnable( Bool IsEnable )
{
	m_IsEnvironment = IsEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapActorObject::GetSoftBillboardEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapActorObject::GetCullTestEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapActorObject::GetParallaxEnable( void )
{
	return m_IsParallax;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapActorObject::GetSpecularEnable( void )
{
	return m_IsSpecular;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapActorObject::GetEnvironmentEnable( void )
{
	return m_IsEnvironment;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eTransformType CMapActorObject::GetTransformType( void )
{
	return TRANSFORM_TYPE_MODEL;
}
