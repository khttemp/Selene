#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CBaseObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	class COcclusion : public CBaseObject
	{
	protected:
		IDirect3DQuery9 *m_pQuery;

	public:
		COcclusion( CRender *pRender );
		virtual ~COcclusion();

		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

		virtual void Begin( void );
		virtual void End( void );
		virtual Sint32 GetPixels( void );
	};
}
}
