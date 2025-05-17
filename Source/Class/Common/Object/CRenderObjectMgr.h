#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CBaseList.h"
#include "Class/Common/Object/CResourceObjectMgr.h"

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	class CRenderObjectMgr : public CResourceObjectMgr
	{
	protected:
		Renderer::CRender	*m_pRender;
		CGraphicCard		*m_pGraphicCard;
		CCore				*m_pCore;

	public:
		CRenderObjectMgr( Renderer::CRender *pRender, const char *pName );
		virtual ~CRenderObjectMgr();

		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );

		virtual Renderer::CRender *GetRenderPointer( void ) const;
		virtual CGraphicCard *GetGraphicCardPointer( void ) const;
		virtual CCore *GetCorePointer( void ) const;
	};
}
}

