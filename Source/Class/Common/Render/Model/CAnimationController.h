#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Object/CBaseObject.h"
#include "Class/Common/Object/CBaseList.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Math/Animation.h"
#include "Math/Style.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CAnimationController : public CBaseObject
	{
	private:
		Sint32 m_AnimationCount;
		CAnimationData **m_pAnimationList;
		Float m_fLastTime;

	public:
		CAnimationController();
		virtual ~CAnimationController();

		virtual void CreateAnimationData( Sint32 Count );
		virtual void SetLastTime( Float fTime );
		virtual CAnimationData *GetCAnimationDataPointer( Sint32 Index );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

		virtual void Update( Float fTime, eAnimationType Type );
		virtual Float GetLastTime( void );
	};
}
}
}
