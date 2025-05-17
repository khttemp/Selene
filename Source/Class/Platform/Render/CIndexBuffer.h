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
	enum eIndexBufferType
	{
		INDEX_TYPE_16BIT,
		INDEX_TYPE_32BIT,
	};

	class CIndexBuffer : public CRenderObject
	{
	public:
		IDirect3DIndexBuffer9 *m_pBuffer;
		Sint32 m_MaxCount;
		Sint32 m_Offset;
		Sint32 m_Size;
		Sint32 m_RequestedCount;
		Sint32 m_RequestedCountMax;
		Bool m_IsDirect;
		Uint8 *m_pLockData;
		union {
			void *m_pSystemData;
			Uint16 *m_pSystemData16;
			Uint32 *m_pSystemData32;
		};
		Bool m_IsDynamic;
		eIndexBufferType m_IndexType;

	public:
		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );

	public:
		CIndexBuffer( CRenderObjectMgr *pMgr );
		virtual ~CIndexBuffer();

		virtual void Lock( Bool IsDirect = false );
		virtual void UnLock( void );
		virtual Bool Push( const void *pIdx, Sint32 Count );
		virtual void *GetBufferPointer( Sint32 Count );
		virtual void *GetBufferAddress( Sint32 Position );

		virtual eIndexBufferType GetIndexType( void );
		virtual Bool Add( CIndexBuffer *pSrc, Sint32 SrcPos, Sint32 SrcCount, Sint32 Offset );

		virtual Sint32 GetCount( void ) const;
		virtual Sint32 GetRequestedCount( void ) const;

		virtual Bool Create( Sint32 Count, Bool IsDynamic );
		virtual void GetInterface( IDirect3DIndexBuffer9 *&pIndex );
	};
}
}
