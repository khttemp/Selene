

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Platform/Render/CIndexBuffer.h"
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
CIndexBuffer::CIndexBuffer( CRenderObjectMgr *pMgr ) : CRenderObject( pMgr->GetRenderPointer(), pMgr )
	, m_pBuffer				( NULL )
	, m_MaxCount			( 0 )
	, m_Offset				( 0 )
	, m_Size				( sizeof(Uint16) )
	, m_RequestedCount		( 0 )
	, m_RequestedCountMax	( 0 )
	, m_pSystemData			( NULL )
	, m_pLockData			( NULL )
	, m_IndexType			( INDEX_TYPE_16BIT )
	, m_IsDirect			( false )
{
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CIndexBuffer::~CIndexBuffer()
{
	MemoryFree( m_pSystemData );
	SAFE_RELEASE( m_pBuffer	);
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CIndexBuffer::OnLostDevice( void )
{
	SAFE_RELEASE( m_pBuffer	);
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CIndexBuffer::OnResetDevice( void )
{
	// 再生成
	m_pRender->CreateIndexBuffer( m_Size * m_MaxCount, &m_pBuffer, m_IsDynamic, m_IndexType == INDEX_TYPE_32BIT );
	if ( !m_IsDynamic )
	{
		void *pLockData;
		m_pBuffer->Lock( 0, 0, &pLockData, 0 );
		MemoryCopy( pLockData, m_pSystemData, m_Size * m_Offset );
		m_pBuffer->Unlock();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CIndexBuffer::Lock( Bool IsDirect )
{
	m_IsDirect			= IsDirect && m_IsDynamic;
	m_Offset			= 0;
	m_RequestedCount	= 0;
	m_pLockData			= NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CIndexBuffer::UnLock( void )
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
			MemoryCopy( pLockData, m_pSystemData, m_Size * m_Offset );
			m_pBuffer->Unlock();
		}
	}

	// ３個単位にする
	m_Offset -= m_Offset % 3;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void *CIndexBuffer::GetBufferPointer( Sint32 Count )
{
	m_RequestedCount += Count;

	if ( m_Offset + Count <= m_MaxCount )
	{
		Uint8 *pBuffer = (Uint8*)m_pSystemData + (m_Offset * m_Size);
		m_Offset += Count;
		return pBuffer;
	}

	return NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void *CIndexBuffer::GetBufferAddress( Sint32 Position )
{
	return (Uint8*)m_pSystemData + (Position * m_Size);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CIndexBuffer::Push( const void *pIdx, Sint32 Count )
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
			Uint8 *pPtr = m_pLockData + (m_Size * m_Offset);
			MemoryCopy( pPtr, pIdx, m_Size * Count );
			m_Offset += Count;
			return true;
		}
	}
	else
	{
		void *pDst = GetBufferPointer( Count );
		if ( pDst != NULL )
		{
			MemoryCopy( pDst, pIdx, m_Size * Count );

			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CIndexBuffer::Create( Sint32 Count, Bool IsDynamic )
{
	const Sint32 SizeTbl[] = {
		sizeof(Uint16),		// INDEX_TYPE_16BIT,
		sizeof(Uint32),		// INDEX_TYPE_32BIT,
	};

	m_IndexType	= Count > 0x0000FFFF ? INDEX_TYPE_32BIT : INDEX_TYPE_16BIT;
	m_IsDynamic	= IsDynamic;
	m_MaxCount	= Count;
	m_Offset	= 0;
	m_Size		= SizeTbl[m_IndexType];

	m_pSystemData = MemoryAlloc( m_Size * Count );
	HRESULT hr = m_pRender->CreateIndexBuffer( m_Size * Count, &m_pBuffer, IsDynamic, m_IndexType == INDEX_TYPE_32BIT );

	return SUCCEEDED( hr );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CIndexBuffer::GetInterface( IDirect3DIndexBuffer9 *&pIndex )
{
	pIndex = m_pBuffer;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eIndexBufferType CIndexBuffer::GetIndexType( void )
{
	return m_IndexType;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CIndexBuffer::Add( CIndexBuffer *pSrc, Sint32 SrcPos, Sint32 SrcCount, Sint32 Offset )
{
	void *pBuffer = GetBufferPointer( SrcCount );
	if ( pBuffer != NULL )
	{
		if ( m_IndexType == pSrc->GetIndexType() )
		{
			if ( m_IndexType == INDEX_TYPE_16BIT )
			{
				Uint16 *pDstIdx = (Uint16*)pBuffer;
				Uint16 *pSrcIdx = (Uint16*)pSrc->GetBufferAddress( SrcPos );
				for ( Sint32 i = 0; i < SrcCount; i++ )
				{
					pDstIdx[i] = (Uint16)(pSrcIdx[i] + Offset);
				}
			}
			else
			if ( m_IndexType == INDEX_TYPE_32BIT )
			{
				Uint32 *pDstIdx = (Uint32*)pBuffer;
				Uint32 *pSrcIdx = (Uint32*)pSrc->GetBufferAddress( SrcPos );
				for ( Sint32 i = 0; i < SrcCount; i++ )
				{
					pDstIdx[i] = pSrcIdx[i] + Offset;
				}
			}
		}
		else
		{
			if ( m_IndexType == INDEX_TYPE_16BIT )
			{
				Uint16 *pDstIdx = (Uint16*)pBuffer;
				Uint32 *pSrcIdx = (Uint32*)pSrc->GetBufferAddress( SrcPos );
				for ( Sint32 i = 0; i < SrcCount; i++ )
				{
					pDstIdx[i] = (Uint16)(pSrcIdx[i] + Offset);
				}
			}
			else
			if ( m_IndexType == INDEX_TYPE_32BIT )
			{
				Uint32 *pDstIdx = (Uint32*)pBuffer;
				Uint16 *pSrcIdx = (Uint16*)pSrc->GetBufferAddress( SrcPos );
				for ( Sint32 i = 0; i < SrcCount; i++ )
				{
					pDstIdx[i] = pSrcIdx[i] + Offset;
				}
			}
		}

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CIndexBuffer::GetCount( void ) const
{
	return m_Offset;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CIndexBuffer::GetRequestedCount( void ) const
{
	return m_RequestedCount;
}

