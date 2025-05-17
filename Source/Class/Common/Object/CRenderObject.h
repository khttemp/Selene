#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Math.h"
#include "Class/Common/Object/CResourceObject.h"
#include "Class/Common/Object/CRenderObjectMgr.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	class CRenderObject : public CResourceObject
	{
	protected:
		CRenderObjectMgr *m_pManager;
		CRender *m_pRender;
		CGraphicCard *m_pGraphicCard;
		CCore *m_pCore;

	public:
		CRenderObject( CRender *pRender, CRenderObjectMgr *pMgr );
		virtual ~CRenderObject();

		virtual char *GetError( HRESULT hr );
		virtual CRender *GetRenderPointer( void );
		virtual CGraphicCard *GetGraphicCardPointer( void );
		virtual CCore *GetCorePointer( void );
		virtual Math::Point2DI GetTextureMaxSize( void );

	public:
		virtual void OnLostDevice( void )  {}
		virtual void OnResetDevice( void ) {}
	};
}
}

