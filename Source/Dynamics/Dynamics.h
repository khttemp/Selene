#pragma once


/**
	@file
	@brief システム系関数群
	@author 葉迩倭
*/

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CBaseList.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Dynamics
{
/**
@brief ダイナミクス用ワールド生成
@author 葉迩倭
@return ワールドのインターフェイス

@note
Dynamics(ODE)のワールドの生成を行います。

@code
int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
	// ワールドの生成
	ISimulationWorld *pWorld = CreateWorld();

	// 略
	…

	// ワールドの解放
	SAFE_RELEASE( pWorld );

	return 0;
}
@endcode
*/
SELENE_DLL_API ISimulationWorld *CreateWorld( Scene::ISceneManager *pScene = NULL );
}
}

