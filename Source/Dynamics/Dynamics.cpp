

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Dynamics.h"
#include "Dynamics/Class/CDynamicsSimulationWorld.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Dynamics;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
static void *AllocFunction( size_t size )
{
	return malloc( size );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
static void *ReallocFunction( void *ptr, size_t oldsize, size_t newsize )
{
	return realloc( ptr, newsize );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
static void FreeFunction( void *ptr, size_t size )
{
	free( ptr );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
SELENE_DLL_API ISimulationWorld *Dynamics::CreateWorld( Scene::ISceneManager *pScene )
{
	dSetAllocHandler( AllocFunction );
	dSetReallocHandler( ReallocFunction );
	dSetFreeHandler( FreeFunction );

	return new CSimulationWorld( pScene );
}
