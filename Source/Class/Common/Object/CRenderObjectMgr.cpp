

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Object/CRenderObjectMgr.h"
#include "Class/Common/Object/CRenderObject.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Core/CGraphicCard.h"
#include "Class/Common/Core/CCore.h"
#include "Local.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRenderObjectMgr::CRenderObjectMgr( CRender *pRender, const char *pName )
	: CResourceObjectMgr	( pName )
	, m_pRender				( pRender )
	, m_pGraphicCard		( pRender->GetGraphicCardPointer() )
	, m_pCore				( pRender->GetGraphicCardPointer()->GetCorePointer() )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRenderObjectMgr::~CRenderObjectMgr()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRender *CRenderObjectMgr::GetRenderPointer( void ) const
{
	return m_pRender;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CGraphicCard *CRenderObjectMgr::GetGraphicCardPointer( void ) const
{
	return m_pGraphicCard;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCore *CRenderObjectMgr::GetCorePointer( void ) const
{
	return m_pCore;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRenderObjectMgr::OnLostDevice( void )
{
	CBaseObject *pObj = GetTop();
	while ( pObj != NULL )
	{
		((CRenderObject*)pObj)->OnLostDevice();

		pObj = pObj->GetNext();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRenderObjectMgr::OnResetDevice( void )
{
	CBaseObject *pObj = GetTop();
	while ( pObj != NULL )
	{
		((CRenderObject*)pObj)->OnResetDevice();

		pObj = pObj->GetNext();
	}
}

