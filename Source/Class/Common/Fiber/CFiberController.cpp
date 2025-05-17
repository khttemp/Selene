

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
		// �֐��R�[��
		pData->pData->pFiberInterface->Control();
		pData->pData->pFiberInterface->Release();
		pData->pData->pFiberInterface = NULL;
		// ���X�g�X�V
		pData->pContrler->UpdateList();
		// �؂�ւ�
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
	// �}�C�N���X���b�h����
	//--------------------------------------------------
	for ( Sint32 i = 0; i < m_FiberMax; i++ )
	{
		m_pFiberData[i].pFiber = CreateFiber( 32 * 1024, CFiberController::Routine, &m_pRoutineData[i] );
	}

	//--------------------------------------------------
	// �X���b�h���}�C�N���X���b�h��
	//--------------------------------------------------
	m_pFiberData[m_FiberRoot].pFiber			= ConvertThreadToFiber( NULL );
	m_pFiberData[m_FiberRoot].pFiberInterface	= (IFiber*)0xFFFFFFFFFFFFFFFF;

	//--------------------------------------------------
	// ���X�g�X�V
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
	// �t�@�C�o�[�I���X
	//--------------------------------------------------
	while ( m_pFiberData[m_FiberRoot].Next != m_FiberRoot )
	{
		Switch();
	}

	//--------------------------------------------------
	// �Q�ƃ��X�g
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
	// �}�C�N���X���b�h�L���H
	//--------------------------------------------------
	if ( pFiberData->pFiberInterface != NULL )
	{
		return false;
	}

	//--------------------------------------------------
	// �}�C�N���X���b�h�֐��ݒ�
	//--------------------------------------------------
	pFiberData->pFiberInterface = pFiber;
	pFiber->AddRef();

	pFiber->SetController( this );

	//--------------------------------------------------
	// ���X�g�X�V
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
	// �}�C�N���X���b�h�̐؂�ւ�
	//--------------------------------------------------
	if ( m_FiberDataId != m_pFiberData[m_FiberDataId].Next )
	{
		m_FiberDataId = m_pFiberData[m_FiberDataId].Next;
		SwitchToFiber( m_pFiberData[m_FiberDataId].pFiber );
	}

	return m_IsRun;
}

