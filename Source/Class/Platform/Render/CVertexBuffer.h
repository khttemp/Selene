#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CRenderObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	class CVertexBuffer : public CRenderObject
	{
	public:
		IDirect3DVertexBuffer9 *m_pBuffer;
		Sint32 m_VertexSize;
		Sint32 m_MaxCount;
		Sint32 m_Offset;
		Sint32 m_RequestedCount;
		Sint32 m_RequestedCountMax;
		Uint8 *m_pSystemData;
		Uint8 *m_pLockData;
		Bool m_IsDynamic;
		Bool m_IsDirect;

	public:
		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );

	public:
		CVertexBuffer( CRenderObjectMgr *pMgr );
		virtual ~CVertexBuffer();

		virtual void Lock( Bool IsDirect = false );
		virtual void UnLock( void );
		virtual Bool Push( const void *pVtx, Sint32 Count, Bool IsAutoResize = false, Sint32 ResizeStep = 0 );
		virtual void *GetBufferPointer( Sint32 Count, Bool IsAutoResize = false, Sint32 ResizeStep = 0 );
		virtual void *GetBufferAddress( Sint32 Position );

		virtual Bool Add( CVertexBuffer *pSrc, Sint32 SrcPos, Sint32 SrcCount );

		virtual Sint32 GetCount( void ) const;
		virtual Sint32 GetRequestedCount( void ) const;
		virtual Sint32 GetRequestedCountMax( void ) const;

		virtual Bool Create( Sint32 Count, Sint32 VertexSize, Bool IsDynamic );
		virtual void GetInterface( IDirect3DVertexBuffer9 *&pBuffer, Uint32 &Size );
	};
}
}
