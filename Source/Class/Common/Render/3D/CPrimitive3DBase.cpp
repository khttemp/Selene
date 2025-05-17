

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Math/Vector4D.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Render/3D/CPrimitive3DBase.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Class/Platform/Render/Shader/CShader.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;
using namespace Object;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPrimitive3DBase::CPrimitive3DBase( CRender *pRender, CRenderObjectMgr *pMgr ) : CRenderPrimitiveObject( pRender, pMgr )
	, m_IsVertexLock( false )
	, m_IsIndexLock	( false )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPrimitive3DBase::~CPrimitive3DBase()
{
	char Temp[64] = "";
	StringCbPrintf( Temp, sizeof(Temp), "0x%08X", (Uint64)this );
	Log_PrintTable( 0xFF0000, 0x000000, "‰ð•ú", m_Name, Temp );
	Log_TableLine( 1 );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3DBase::Push( const void *pIndex, Sint32 IndexCount )
{
	if ( m_pIB == NULL ) return false;
	if ( !m_pIB->Push( pIndex, IndexCount ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3DBase::Push( const SVertex3DBase *pVtx, Sint32 Count )
{
	if ( m_pVB_Base == NULL ) return false;
	if ( !m_pVB_Base->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3DBase::Push( const SVertex3DTexture *pVtx, Sint32 Count )
{
	if ( m_pVB_Tex == NULL ) return false;
	if ( !m_pVB_Tex->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3DBase::Push( const SVertex3DLight *pVtx, Sint32 Count )
{
	if ( m_pVB_Light == NULL ) return false;
	if ( !m_pVB_Light->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3DBase::Push( const SVertex3DBump *pVtx, Sint32 Count )
{
	if ( m_pVB_Bump == NULL ) return false;
	if ( !m_pVB_Bump->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive3DBase::Push( const SVertex3DAnimation *pVtx, Sint32 Count )
{
	if ( m_pVB_Animation == NULL ) return false;
	if ( !m_pVB_Animation->Push( pVtx, Count ) ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CPrimitive3DBase::GetVertexCount( void )
{
	if ( m_pVB_Base == NULL ) return 0;

	return m_pVB_Base->GetRequestedCount();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CPrimitive3DBase::GetIndexCount( void )
{
	if ( m_pIB == NULL ) return 0;

	return m_pIB->GetRequestedCount();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive3DBase::Begin( Bool IsVertex, Bool IsIndex, Bool IsDirect )
{
	if ( IsVertex )
	{
		if ( m_pVB_Base != NULL )
		{
			m_pVB_Base->Lock( IsDirect );
		}
		if ( m_pVB_Tex != NULL )
		{
			m_pVB_Tex->Lock( IsDirect );
		}
		if ( m_pVB_Light != NULL )
		{
			m_pVB_Light->Lock( IsDirect );
		}
		if ( m_pVB_Bump != NULL )
		{
			m_pVB_Bump->Lock( IsDirect );
		}
		if ( m_pVB_Animation != NULL )
		{
			m_pVB_Animation->Lock( IsDirect );
		}
	}

	if ( IsIndex )
	{
		if ( m_pIB != NULL )
		{
			m_pIB->Lock( IsDirect );
		}
	}

	m_IsVertexLock = IsVertex;
	m_IsIndexLock = IsIndex;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive3DBase::End( void )
{
	if ( m_IsVertexLock )
	{
		if ( m_pVB_Base != NULL )
		{
			m_pVB_Base->UnLock();
		}
		if ( m_pVB_Tex != NULL )
		{
			m_pVB_Tex->UnLock();
		}
		if ( m_pVB_Light != NULL )
		{
			m_pVB_Light->UnLock();
		}
		if ( m_pVB_Bump != NULL )
		{
			m_pVB_Bump->UnLock();
		}
		if ( m_pVB_Animation != NULL )
		{
			m_pVB_Animation->UnLock();
		}
	}

	if ( m_IsIndexLock )
	{
		if ( m_pIB != NULL )
		{
			m_pIB->UnLock();
		}
	}
}

