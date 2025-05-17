#pragma once


/**
	@file
	@brief �V�X�e���n�֐��Q
	@author �t���`
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
@brief �_�C�i�~�N�X�p���[���h����
@author �t���`
@return ���[���h�̃C���^�[�t�F�C�X

@note
Dynamics(ODE)�̃��[���h�̐������s���܂��B

@code
int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
	// ���[���h�̐���
	ISimulationWorld *pWorld = CreateWorld();

	// ��
	�c

	// ���[���h�̉��
	SAFE_RELEASE( pWorld );

	return 0;
}
@endcode
*/
SELENE_DLL_API ISimulationWorld *CreateWorld( Scene::ISceneManager *pScene = NULL );
}
}

