#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CRenderObject.h"
#include "Class/Common/Object/CRenderObjectMgr.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	class CRenderPrimitiveObject : public CRenderObject
	{
	protected:
		CIndexBuffer *m_pIB;
		CVertexLayout *m_pVS;
		CVertexBuffer *m_pVB_Base;
		CVertexBuffer *m_pVB_Tex;
		CVertexBuffer *m_pVB_Light;
		CVertexBuffer *m_pVB_Bump;
		CVertexBuffer *m_pVB_Animation;

	public:
		CRenderPrimitiveObject( CRender *pRender, CRenderObjectMgr *pMgr );
		virtual ~CRenderPrimitiveObject();

	public:
		virtual Sint32 GetCount( void ) const;
		virtual Sint32 GetRequestedCount( void ) const;
	};
}
}

