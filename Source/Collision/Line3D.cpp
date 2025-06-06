

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Collision/Line3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Collision;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CLine3D::CLine3D( void )
{
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CLine3D::CLine3D( Float x0, Float y0, Float z0, Float x1, Float y1, Float z1 )
{
	this->vStart.x = x0;
	this->vStart.y = y0;
	this->vStart.z = z0;
	this->vEnd.x = x1;
	this->vEnd.y = y1;
	this->vEnd.z = z1;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CLine3D::CLine3D( const Math::Vector3D &Start, const Math::Vector3D &End )
{
	this->vStart = Start;
	this->vEnd = End;
}

