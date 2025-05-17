

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
	// シーン構築が終わるまでブロック
	//==============================================================
	WaitForSceneConstruct();

	//==============================================================
	// 現在時刻
	//==============================================================
	m_TimeStart = m_pCore->GetSystemTimer();

	//==============================================================
	// ステート
	//==============================================================
	m_pRender->StatePush();

	// ステート
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
	// ステート
	//==============================================================
	m_pRender->StatePop();

	//==============================================================
	// シーンオブジェクト解放
	//==============================================================
	ReleaseObjectList();

	//==============================================================
	// 終了時刻
	//==============================================================
	Uint64 TimeEnd = m_pCore->GetSystemTimer();

	// 経過時間
	m_SceneRenderingTime = (100 * 60 * (TimeEnd - m_TimeStart)) / m_pCore->GetSystemTimerBySec();

	//==============================================================
	// 一応戻す
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

