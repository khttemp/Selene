#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CRenderObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	class CVertexLayout : public CRenderObject
	{
	private:
		IDirect3DVertexDeclaration9 *m_pDeclaration;

	public:
		CVertexLayout( CRenderObjectMgr *pMgr );
		virtual ~CVertexLayout();

		virtual Bool Create( const D3DVERTEXELEMENT9 *pElements );
		virtual void GetInterface( IDirect3DVertexDeclaration9 *&pDeclaration );
	};
}
}
