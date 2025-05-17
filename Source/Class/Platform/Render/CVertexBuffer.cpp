

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CRender.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CVertexBuffer::CVertexBuffer( CRenderObjectMgr *pMgr ) : CRenderObject( pMgr->GetRenderPointer(), pMgr )
	, m_pBuffer				( NULL )
	, m_RequestedCount		( 0 )
	, m_RequestedCountMax	( 0 )
	, m_MaxCount			( 0 )
	, m_Offset				( 0 )
	, m_VertexSize			( 0 )
	, m_IsDynamic			( false )
	, m_IsDirect			( false )
	, m_pSystemData			( NULL )
	, m_pLockData			( NULL )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CVertexBuffer::~CVertexBuffer()
{
	MemoryFree( m_pSystemData );
	SAFE_RELEASE( m_pBuffer	);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CVertexBuffer::OnLostDevice( void )
{
	SAFE_RELEASE( m_pBuffer	);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CVertexBuffer::OnResetDevice( void )
{
	// 再生成
	m_pRender->CreateVertexBuffer( m_VertexSize * m_MaxCount, &m_pBuffer, m_IsDynamic );
	if ( !m_IsDynamic )
	{
		void *pLockData;
		m_pBuffer->Lock( 0, 0, &pLockData, 0 );
		MemoryCopy( pLockData, m_pSystemData, m_VertexSize * m_Offset );
		m_pBuffer->Unlock();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CVertexBuffer::Lock( Bool IsDirect )
{
	m_IsDirect			= m_IsDynamic && IsDirect;
	m_Offset			= 0;
	m_RequestedCount	= 0;
	m_pLockData			= NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CVertexBuffer::UnLock( void )
{
	if ( m_IsDirect )
	{
		if ( m_pLockData != NULL )
		{
			m_pBuffer->Unlock();
			m_pLockData = NULL;
		}
	}
	else
	{
		if ( m_Offset > 0 )
		{
			// リクエスト数
			if ( m_RequestedCountMax < m_RequestedCount )
			{
				m_RequestedCountMax = m_RequestedCount;
			}

			// バッファ更新
			void *pLockData;
			m_pBuffer->Lock( 0, 0, &pLockData, m_IsDynamic ? D3DLOCK_DISCARD : 0 );
			MemoryCopy( pLockData, m_pSystemData, m_VertexSize * m_Offset );
			m_pBuffer->Unlock();
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void *CVertexBuffer::GetBufferPointer( Sint32 Count, Bool IsAutoResize, Sint32 ResizeStep )
{
	m_RequestedCount += Count;

	if ( m_Offset + Count <= m_MaxCount )
	{
		Uint8 *pPtr = m_pSystemData + (m_VertexSize * m_Offset);
		m_Offset += Count;
		return pPtr;
	}
	ef ( IsAutoResize )
	{
		m_MaxCount += ResizeStep;

		// 再生成
		Uint8 *pNew = (Uint8*)MemoryAlloc( m_VertexSize * m_MaxCount );
		MemoryCopy( pNew, m_pSystemData, m_VertexSize * m_Offset ); 
		MemoryFree( m_pSystemData );
		m_pSystemData = pNew;

		// 再生成
		SAFE_RELEASE( m_pBuffer );
		m_pRender->CreateVertexBuffer( m_VertexSize * m_MaxCount, &m_pBuffer, m_IsDynamic );

		// コピー
		Uint8 *pPtr = m_pSystemData + (m_VertexSize * m_Offset);
		m_Offset += Count;
		return pPtr;
	}

	return NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void *CVertexBuffer::GetBufferAddress( Sint32 Position )
{
	return m_pSystemData + (Position * m_VertexSize);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CVertexBuffer::Push( const void *pVtx, Sint32 Count, Bool IsAutoResize, Sint32 ResizeStep )
{
	if ( m_IsDirect )
	{
		if ( m_pLockData == NULL )
		{
			m_pBuffer->Lock( 0, 0, (void**)&m_pLockData, D3DLOCK_DISCARD );
		}

		m_RequestedCount += Count;

		if ( m_Offset + Count <= m_MaxCount )
		{
			Uint8 *pPtr = m_pLockData + (m_VertexSize * m_Offset);
			MemoryCopy( pPtr, pVtx, m_VertexSize * Count );
			m_Offset += Count;
			return true;
		}
	}
	else
	{
		void *pDst = GetBufferPointer( Count, IsAutoResize, ResizeStep );
		if ( pDst != NULL )
		{
			MemoryCopy( pDst, pVtx, m_VertexSize * Count );
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CVertexBuffer::Create( Sint32 Count, Sint32 VertexSize, Bool IsDynamic )
{
	m_VertexSize		= VertexSize;
	m_MaxCount			= Count;
	m_RequestedCount	= 0;
	m_Offset			= 0;
	m_IsDynamic			= IsDynamic;

	m_pSystemData = (Uint8*)MemoryAlloc( m_VertexSize * m_MaxCount );

	HRESULT hr = m_pRender->CreateVertexBuffer( m_VertexSize * m_MaxCount, &m_pBuffer, m_IsDynamic );
	if SUCCEEDED( hr )
	{
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CVertexBuffer::GetInterface( IDirect3DVertexBuffer9 *&pBuffer, Uint32 &Size )
{
	pBuffer = m_pBuffer;
	Size = m_VertexSize;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CVertexBuffer::Add( CVertexBuffer *pSrc, Sint32 SrcPos, Sint32 SrcCount )
{
	void *pDst = GetBufferPointer( SrcCount );
	if ( pDst != NULL )
	{
		MemoryCopy( pDst, pSrc->GetBufferAddress( SrcPos ), SrcCount * m_VertexSize );
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CVertexBuffer::GetCount( void ) const
{
	return m_Offset;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CVertexBuffer::GetRequestedCount( void ) const
{
	return m_RequestedCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CVertexBuffer::GetRequestedCountMax( void ) const
{
	return m_RequestedCountMax;
}
