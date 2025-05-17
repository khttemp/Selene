

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Render/Model/CAnimationController.h"
#include "Class/Common/Render/Model/CAnimationData.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;
using namespace Object;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CAnimationController::CAnimationController()
	: m_AnimationCount	( 0 )
	, m_pAnimationList	( NULL )
	, m_fLastTime		( 0.0f )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CAnimationController::~CAnimationController()
{
	Sint32 Max = m_AnimationCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		SAFE_DELETE( m_pAnimationList[i] );
	}
	SAFE_DELETE_ARRAY( m_pAnimationList );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CAnimationController::CreateAnimationData( Sint32 Count )
{
	m_AnimationCount = Count;
	m_pAnimationList = new CAnimationData * [ Count ];
	for ( Sint32 i = 0; i < Count; i++ )
	{
		m_pAnimationList[i] = new CAnimationData();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CAnimationController::SetLastTime( Float fTime )
{
	m_fLastTime = fTime;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CAnimationData *CAnimationController::GetCAnimationDataPointer( Sint32 Index )
{
	return m_pAnimationList[Index];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CAnimationController::Update( Float fTime, eAnimationType Type )
{
	Sint32 Max = m_AnimationCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pAnimationList[i]->Update( fTime, Type );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CAnimationController::GetLastTime( void )
{
	return m_fLastTime;
}


