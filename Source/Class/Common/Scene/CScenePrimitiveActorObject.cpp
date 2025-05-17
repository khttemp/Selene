

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CScenePrimitiveActorObject.h"
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
CPrimitiveActorObject::CPrimitiveActorObject( CSceneManagerBase *pScene ) : CActorObject( pScene )
	, m_IsBumpmap		( false )
	, m_IsSpecularmap	( false )
	, m_IsEnvironmentmap( false )
	, m_BoneCount		( 0 )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPrimitiveActorObject::~CPrimitiveActorObject()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActorObject::Update( Math::Matrix &mWorld, Math::Matrix &mWorldInverse )
{
	m_mWorld[m_Page] = mWorld;
	m_mWorldInverse[m_Page] = mWorldInverse;

	m_vCenter.TransformCoord( m_vCenterBase, mWorld );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActorObject::SetStreamSource( Renderer::CRender *pRender )
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
Sint32 CPrimitiveActorObject::Rendering( Sint32 MaterialNo, Renderer::CRender *pRender )
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
Sint32 CPrimitiveActorObject::Rendering_Velocity( Renderer::CRender *pRender )
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
Bool CPrimitiveActorObject::IsAlphaEnable( void )
{
	return m_pMaterial[0].GetDrawType() != DRAW_TYPE_NORMAL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CPrimitiveActorObject::GetBoneCount( void )
{
	return m_BoneCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActorObject::SetEnvironmentmapEnable( Bool IsEnvironmentmap )
{
	m_IsEnvironmentmap = IsEnvironmentmap;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActorObject::SetSpecularEnable( Bool IsSpecularmap )
{
	m_IsSpecularmap = IsSpecularmap;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActorObject::SetBumpmapEnable( Bool IsNormalmap )
{
	m_IsBumpmap = IsNormalmap;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::SMatrix4x4 *CPrimitiveActorObject::GetBoneMatrixArray( void )
{
	return m_mBone[m_Page];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::SMatrix4x4 *CPrimitiveActorObject::GetBoneMatrixArrayPrev( void )
{
	return m_mBone[1-m_Page];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActorObject::SetBoneMatrixArray( Math::Matrix *pMatrix, Sint32 Count )
{
	m_BoneCount = Count;
	for ( Sint32 i = 0; i < Count; i++ )
	{
		m_mBone[m_Page][i] = pMatrix[i];
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPrimitiveActorObject::GetSoftBillboardEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPrimitiveActorObject::GetCullTestEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPrimitiveActorObject::GetParallaxEnable( void )
{
	return m_IsBumpmap;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPrimitiveActorObject::GetSpecularEnable( void )
{
	return m_IsSpecularmap;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPrimitiveActorObject::GetEnvironmentEnable( void )
{
	return m_IsEnvironmentmap;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActorObject::SetShader( Renderer::Shader::IShader *pShader )
{
	m_pMaterial[0].SetShader( (Renderer::Shader::IShader*)pShader );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActorObject::SetMaterialColor( Math::Vector4D &vColor )
{
	m_pMaterial[0].SetDiffuseColor( vColor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActorObject::SetEmissiveColor( Math::Vector4D &vColor )
{
	m_pMaterial[0].SetEmissiveColor( vColor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActorObject::SetSpecularColor( Math::Vector4D &vColor )
{
	m_pMaterial[0].SetSpecularColor( vColor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActorObject::SetSpecularRefractive( Float fParam )
{
	m_pMaterial[0].SetSpecularRefractive( fParam );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActorObject::SetSpecularRoughly( Float fParam )
{
	m_pMaterial[0].SetSpecularRoughly( fParam );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eTransformType CPrimitiveActorObject::GetTransformType( void )
{
	return TRANSFORM_TYPE_MODEL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActorObject::UpdateMaterial( Renderer::CRender *pRender )
{
	Renderer::SRenderState &State = pRender->GetRenderState();

	for ( Sint32 i = 0; i < MATERIAL_TEXTURE_MAX; i++ )
	{
		m_pMaterial[0].SetTexture( (eTextureStage)i, State.pTextureTbl[i] );
	}

	m_pMaterial[0].SetDrawType( State.DrawType );
	m_pMaterial[0].SetCullType( State.CullType );
	m_pMaterial[0].SetAlphaBoundary( State.AlphaBoundary );
	m_pMaterial[0].SetAlphaTestEnable( State.IsAlphaTestEnable );
	m_pMaterial[0].SetZTestEnable( State.IsDepthTestEnable );
	m_pMaterial[0].SetZWriteEnable( State.IsDepthWriteEnable );
}
