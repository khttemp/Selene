

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Platform/Render/Shader/ShaderManager.h"
#include "Class/Platform/Render/CVertexLayout.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Class/Common/Scene/CSceneActorMaterial.h"
#include "Class/Common/Scene/CSceneManagerBase.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CActorObject::CActorObject( CSceneManagerBase *pScene )
	: m_pSceneMgr		( pScene )
	, m_RenderActorID	( pScene->GetNewRenderActorID() )
	, m_Page			( 0 )
	, m_MaterialCount	( 0 )
	, m_pMaterial		( NULL )
	, m_pIB				( NULL )
	, m_pVS				( NULL )
	, m_pVB_Base		( NULL )
	, m_pVB_Tex			( NULL )
	, m_pVB_Light		( NULL )
	, m_pVB_Bump		( NULL )
	, m_pVB_Animation	( NULL )
	, m_vCenter			( 0.0f, 0.0f, 0.0f )
	, m_vCenterBase		( 0.0f, 0.0f, 0.0f )
{
	m_mWorld[0].Identity();
	m_mWorld[1].Identity();
	m_mWorldInverse[0].Identity();
	m_mWorldInverse[1].Identity();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CActorObject::~CActorObject()
{
	m_pSceneMgr->ReleaseRenderActorID( m_RenderActorID );

	SAFE_RELEASE( m_pIB );
	SAFE_RELEASE( m_pVS );
	SAFE_RELEASE( m_pVB_Base );
	SAFE_RELEASE( m_pVB_Tex );
	SAFE_RELEASE( m_pVB_Light );
	SAFE_RELEASE( m_pVB_Bump );
	SAFE_RELEASE( m_pVB_Animation );

	SAFE_DELETE_ARRAY( m_pMaterial );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CActorObject::IsInvalid( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CActorObject::Release( void )
{
	return 1;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CActorObject::AddRef( void )
{
	return 1;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CActorObject::IsSupportVertexBone( void )
{
	return m_pVB_Animation != NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CActorObject::IsSupportVertexTexture( void )
{
	return m_pVB_Tex != NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CActorObject::IsSupportVertexNormal( void )
{
	return m_pVB_Light != NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CActorObject::IsSupportVertexBump( void )
{
	return m_pVB_Bump != NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CActorObject::SetMateriaCount( Sint32 Count )
{
	m_MaterialCount = Count;
	m_pMaterial = new CSceneActorMaterial [ Count ];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CActorObject::GetMaterialCount( void )
{
	return m_MaterialCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSceneActorMaterial &CActorObject::GetSceneRenderMaterial( Sint32 Index )
{
	return m_pMaterial[Index];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ICustomizedSceneRenderMaterial *CActorObject::GetMaterialPointer( Sint32 Index )
{
	return &m_pMaterial[Index];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CActorObject::SetStream( Renderer::CIndexBuffer *pIB, Renderer::CVertexLayout *pVS, Renderer::CVertexBuffer *pVB_Base, Renderer::CVertexBuffer *pVB_Tex, Renderer::CVertexBuffer *pVB_Light, Renderer::CVertexBuffer *pVB_Bump, Renderer::CVertexBuffer *pVB_Animation )
{
	m_pIB			= pIB;
	m_pVS			= pVS;
	m_pVB_Base		= pVB_Base;
	m_pVB_Tex		= pVB_Tex;
	m_pVB_Light		= pVB_Light;
	m_pVB_Bump		= pVB_Bump;
	m_pVB_Animation	= pVB_Animation;
	SAFE_ADDREF( pIB );
	SAFE_ADDREF( pVS );
	SAFE_ADDREF( pVB_Base );
	SAFE_ADDREF( pVB_Tex );
	SAFE_ADDREF( pVB_Light );
	SAFE_ADDREF( pVB_Bump );
	SAFE_ADDREF( pVB_Animation );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CActorObject::GetRenderActorID( void )
{
	return m_RenderActorID;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CActorObject::SetCenter( const Math::Vector3D &vCenter )
{
	m_vCenterBase = vCenter;
	m_vCenter = vCenter;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Vector3D &CActorObject::GetCenter( void )
{
	return m_vCenter;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CActorObject::GetBoneCount( void )
{
	return 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CActorObject::GetWorldMatrix( void )
{
	return m_mWorld[m_Page];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CActorObject::GetWorldMatrixPrev( void )
{
	return m_mWorld[1-m_Page];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CActorObject::GetWorldInverseMatrix( void )
{
	return m_mWorldInverse[m_Page];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CActorObject::GetWorldInverseMatrixPrev( void )
{
	return m_mWorldInverse[1-m_Page];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::SMatrix4x4 *CActorObject::GetBoneMatrixArray( void )
{
	return NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::SMatrix4x4 *CActorObject::GetBoneMatrixArrayPrev( void )
{
	return NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Collision::CBox &CActorObject::GetCullBox( void )
{
	return *((Collision::CBox*)NULL);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CActorObject::Flip( void )
{
	m_Page = 1 - m_Page;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CActorObject::IsInstanceModel( void )
{
	return false;
}

