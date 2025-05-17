

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Scene/CCustomizedSceneManager.h"
#include "Class/Common/Scene/CCustomizedSceneRenderObject.h"
#include "Class/Common/Scene/CSceneActorObject.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Surface/CTexture.h"
#include "Class/Platform/Surface/CDepthTexture.h"
#include "Class/Platform/Render/COcclusion.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCustomizedSceneManager::CCustomizedSceneManager( Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr, Sint32 QueMax ) : CSceneManagerBase( pRender, pMgr, QueMax )
{
	m_SceneState = SCENE_STATE_STANDBY;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCustomizedSceneManager::~CCustomizedSceneManager()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCustomizedSceneManager::RenderingStart( void )
{
	m_SceneRenderingTime = 0;

	//==============================================================
	// �V�[���\�z���I���܂Ńu���b�N
	//==============================================================
	WaitForSceneConstruct();

	//==============================================================
	// ���ݎ���
	//==============================================================
	m_TimeStart = m_pCore->GetSystemTimer();

	//==============================================================
	// �X�e�[�g
	//==============================================================
	m_pRender->StatePush();

	// �X�e�[�g
	m_pRender->Start3D();

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCustomizedSceneManager::RenderingExit( void )
{
	//==============================================================
	// �X�e�[�g
	//==============================================================
	m_pRender->StatePop();

	//==============================================================
	// �V�[���I�u�W�F�N�g���
	//==============================================================
	ReleaseObjectList();

	//==============================================================
	// �I������
	//==============================================================
	Uint64 TimeEnd = m_pCore->GetSystemTimer();

	// �o�ߎ���
	m_SceneRenderingTime = (100 * 60 * (TimeEnd - m_TimeStart)) / m_pCore->GetSystemTimerBySec();

	//==============================================================
	// �ꉞ�߂�
	//==============================================================
	m_pRender->SetColorWriteEnable( true, true, true, true );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CCustomizedSceneManager::GetRenderObjectLayerCount( void )
{
	return ID_MAX;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ICustomizedSceneRenderObject *CCustomizedSceneManager::GetRenderObject( Sint32 Layer )
{
	return m_pObjectList[Layer];
}

