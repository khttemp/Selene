

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Object/CRenderPrimitiveObject.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CVertexLayout.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRenderPrimitiveObject::CRenderPrimitiveObject( CRender *pRender, CRenderObjectMgr *pMgr ) : CRenderObject( pRender, pMgr )
	, m_pIB				( NULL )
	, m_pVS				( NULL )
	, m_pVB_Base		( NULL )
	, m_pVB_Tex			( NULL )
	, m_pVB_Light		( NULL )
	, m_pVB_Bump		( NULL )
	, m_pVB_Animation	( NULL )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRenderPrimitiveObject::~CRenderPrimitiveObject()
{
	SAFE_RELEASE( m_pIB );
	SAFE_RELEASE( m_pVS );
	SAFE_RELEASE( m_pVB_Base );
	SAFE_RELEASE( m_pVB_Tex );
	SAFE_RELEASE( m_pVB_Light );
	SAFE_RELEASE( m_pVB_Bump );
	SAFE_RELEASE( m_pVB_Animation );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CRenderPrimitiveObject::GetCount( void ) const
{
	return m_pVB_Base->GetCount();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CRenderPrimitiveObject::GetRequestedCount( void ) const
{
	return m_pVB_Base->GetRequestedCount();
}

