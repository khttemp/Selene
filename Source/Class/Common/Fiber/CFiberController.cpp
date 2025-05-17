

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Fiber/CFiberController.h"
#include "Interface/Fiber/IFiber.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Fiber;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void WINAPI CFiberController::Routine( void *pParam )
{
	SRoutineData *pData = (SRoutineData*)pParam;
	for ( ; ; )
	{
		// 関数コール
		pData->pData->pFiberInterface->Control();
		pData->pData->pFiberInterface->Release();
		pData->pData->pFiberInterface = NULL;
		// リスト更新
		pData->pContrler->UpdateList();
		// 切り替え
		pData->pContrler->Switch();
	}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFiberController::CFiberController( Sint32 Max )
	: m_FiberMax		( Max )
	, m_FiberMaxCount	( Max + 1 )
	, m_FiberRoot		( Max )
	, m_FiberDataId		( Max )
	, m_pFiberData		( NULL )
	, m_IsRun			( true )
{
	m_pFiberData = new SFiberData [ m_FiberMaxCount ];
	for ( Sint32 i = 0; i < m_FiberMaxCount; i++ )
	{
		m_pFiberData[i].pFiberInterface	= NULL;
		m_pFiberData[i].pFiber			= NULL;
		m_pFiberData[i].Next			= 0;
	}

	m_pRoutineData = new SRoutineData [ m_FiberMaxCount ];
	for ( Sint32 i = 0; i < m_FiberMaxCount; i++ )
	{
		m_pRoutineData[i].pContrler	= this;
		m_pRoutineData[i].pData		= &m_pFiberData[i];
	}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFiberController::~CFiberController()
{
	SAFE_DELETE_ARRAY( m_pFiberData );
	SAFE_DELETE_ARRAY( m_pRoutineData );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFiberController::UpdateList( void )
{
	for ( Sint32 Pos = 0; Pos < m_FiberMaxCount; Pos++ )
	{
		if ( m_pFiberData[Pos].pFiberInterface != NULL )
		{
			Sint32 Next = Pos;
			do
			{
				Next = (Next + 1) % m_FiberMaxCount;
			}
			while ( m_pFiberData[Next].pFiberInterface == NULL );

			m_pFiberData[Pos].Next = Next;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFiberController::Start( void )
{
	m_IsRun = true;

	//--------------------------------------------------
	// マイクロスレッド生成
	//--------------------------------------------------
	for ( Sint32 i = 0; i < m_FiberMax; i++ )
	{
		m_pFiberData[i].pFiber = CreateFiber( 32 * 1024, CFiberController::Routine, &m_pRoutineData[i] );
	}

	//--------------------------------------------------
	// スレッドをマイクロスレッドに
	//--------------------------------------------------
	m_pFiberData[m_FiberRoot].pFiber			= ConvertThreadToFiber( NULL );
	m_pFiberData[m_FiberRoot].pFiberInterface	= (IFiber*)0xFFFFFFFFFFFFFFFF;

	//--------------------------------------------------
	// リスト更新
	//--------------------------------------------------
	UpdateList();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFiberController::Exit( void )
{
	m_IsRun = false;

	//--------------------------------------------------
	// ファイバー終了街
	//--------------------------------------------------
	while ( m_pFiberData[m_FiberRoot].Next != m_FiberRoot )
	{
		Switch();
	}

	//--------------------------------------------------
	// 参照リスト
	//--------------------------------------------------
	for ( Sint32 i = 0; i < m_FiberMax; i++ )
	{
		DeleteFiber( m_pFiberData[i].pFiber );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CFiberController::Create( Sint32 FiberId, IFiber *pFiber )
{
	SFiberData *pFiberData = &m_pFiberData[FiberId];

	//--------------------------------------------------
	// マイクロスレッド有効？
	//--------------------------------------------------
	if ( pFiberData->pFiberInterface != NULL )
	{
		return false;
	}

	//--------------------------------------------------
	// マイクロスレッド関数設定
	//--------------------------------------------------
	pFiberData->pFiberInterface = pFiber;
	pFiber->AddRef();

	pFiber->SetController( this );

	//--------------------------------------------------
	// リスト更新
	//--------------------------------------------------
	UpdateList();

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CFiberController::Switch( void )
{
	//--------------------------------------------------
	// マイクロスレッドの切り替え
	//--------------------------------------------------
	if ( m_FiberDataId != m_pFiberData[m_FiberDataId].Next )
	{
		m_FiberDataId = m_pFiberData[m_FiberDataId].Next;
		SwitchToFiber( m_pFiberData[m_FiberDataId].pFiber );
	}

	return m_IsRun;
}

