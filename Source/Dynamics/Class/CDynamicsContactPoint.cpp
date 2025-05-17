

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Dynamics/Class/CDynamicsContactPoint.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Dynamics;


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
CContactPoint::CContactPoint( Sint32 Max )
	: m_Count			( 0 )
	, m_MaxCount		( Max )
	, m_pContactPoint	( new dContact [ Max ] )
{
	MemoryClear( m_pContactPoint, sizeof(dContact) * Max );
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
CContactPoint::~CContactPoint( void )
{
	SAFE_DELETE_ARRAY( m_pContactPoint );
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
dContact *CContactPoint::GetContactPointTbl( void )
{
	return m_pContactPoint;
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
Sint32 CContactPoint::GetCount( void )
{
	return m_Count;
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
Sint32 CContactPoint::GetMaxCount( void )
{
	return m_MaxCount;
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void CContactPoint::SetCount( Sint32 Count )
{
	m_Count = Count;
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void CContactPoint::SetSurfaceParameter( Sint32 Index, SSurfaceParameter &Param )
{
	dSurfaceParameters &Surface = m_pContactPoint[Index].surface;

	Surface.mode		= Param.Mode;
	Surface.mu			= Param.Friction;
	Surface.mu2			= Param.FrictionEx;
	Surface.bounce		= Param.Bounce;
	Surface.bounce_vel	= Param.BounceVelocity;
	Surface.soft_erp	= Param.SoftErp;
	Surface.soft_cfm	= Param.SoftCfm;
	Surface.motion1		= Param.Motion;
	Surface.motion2		= Param.MotionEx;
	Surface.slip1		= Param.Slip;
	Surface.slip2		= Param.SlipEx;
}
