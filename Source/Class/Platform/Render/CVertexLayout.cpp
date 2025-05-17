

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Platform/Render/CVertexLayout.h"
#include "Class/Platform/Render/CRender.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CVertexLayout::CVertexLayout( CRenderObjectMgr *pMgr ) : CRenderObject( pMgr->GetRenderPointer(), pMgr )
{
	m_pDeclaration = NULL;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CVertexLayout::~CVertexLayout()
{
	SAFE_RELEASE( m_pDeclaration );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CVertexLayout::Create( const D3DVERTEXELEMENT9 *pElements )
{
	HRESULT hr = m_pRender->CreateVertexDeclaration( pElements, &m_pDeclaration );

	return SUCCEEDED( hr );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CVertexLayout::GetInterface( IDirect3DVertexDeclaration9 *&pDeclaration )
{
	pDeclaration = m_pDeclaration;
}

