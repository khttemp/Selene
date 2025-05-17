

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Thread/Thread.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Thread;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CThread::CThread()
	: m_pData		( NULL )
	, m_hThread		( NULL )
	, m_pMainProc	( NULL )
	, m_ThreadId	( 0 )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CThread::~CThread()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CThread::Create( void (*pCThreadFunc)( void* ), void *pData )
{
	CAutoLock Lock( m_cs );

	if ( m_hThread == NULL )
	{
		m_pData		= pData;
		m_pMainProc	= pCThreadFunc;
		m_hThread	= ::CreateThread( NULL, 0, CThreadFunc, this, 0, &m_ThreadId );
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CThread::WaitForExit( void )
{
	CAutoLock Lock( m_cs );

	return m_hThread == NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CThread::SetPriority( Sint32 Priority )
{
	CAutoLock Lock( m_cs );

	if ( m_hThread == NULL ) return false;

	return ::SetThreadPriority( m_hThread, Priority ) != FALSE;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CThread::Resume( void )
{
	CAutoLock Lock( m_cs );

	if ( m_hThread == NULL ) return;

	::ResumeThread( m_hThread );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CThread::Suspend( void )
{
	CAutoLock Lock( m_cs );

	if ( m_hThread == NULL ) return;

	::SuspendThread( m_hThread );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CThread::Terminate( void )
{
	CAutoLock Lock( m_cs );

	if ( m_hThread == NULL ) return;

	::TerminateThread( m_hThread, 0 );

	m_ThreadId	= 0;
	m_pMainProc	= NULL;
	m_pData		= NULL;
	m_hThread	= NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 __stdcall CThread::CThreadFunc( void* pArguments )
{
	CThread *pThread = (CThread*)pArguments;

	pThread->m_pMainProc( pThread->m_pData );

	CAutoLock Lock( pThread->m_cs );

	pThread->m_ThreadId		= 0;
	pThread->m_pMainProc	= NULL;
	pThread->m_pData		= NULL;
	pThread->m_hThread		= NULL;

	return 0;
}

