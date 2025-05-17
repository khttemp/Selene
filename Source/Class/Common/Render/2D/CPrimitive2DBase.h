#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CRenderPrimitiveObject.h"
#include "Class/Platform/Render/CRender.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CPrimitive2DBase : public CRenderPrimitiveObject
	{
	protected:
		Bool m_IsScissoring;
		Float m_fScissorX1;
		Float m_fScissorY1;
		Float m_fScissorX2;
		Float m_fScissorY2;

		Sint32 m_ResizeStep;
		Bool m_IsAutoResize;

	protected:
		CPrimitive2DBase( CRender *pRender, CRenderObjectMgr *pMgr );
		virtual ~CPrimitive2DBase();

	protected:
		void SetVertexLinear( SVertex2D *pPtIn1, SVertex2D *pPtIn2, SVertex2D *pPtOut, Float Ave );
		void SetVertexLinear( SVertex2DTex *pPtIn1, SVertex2DTex *pPtIn2, SVertex2DTex *pPtOut, Float Ave );

	public:
		virtual void Begin( void )								= 0;
		virtual void End( void )								= 0;
		virtual void Rendering( void )							= 0;

	public:
		virtual void SetScissoring( Math::Rect2DF *pRect );
	};
}
}
}
