

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Render/Model/CCollisionController.h"
#include "Class/Common/Render/Model/CModel.h"
#include "Class/Common/Render/Model/CAnimationController.h"
#include "Class/Common/Render/Model/CFrame.h"
#include "Class/Common/Render/Model/CMesh.h"
#include "Interface/Render/3D/ILinePrimitive3D.h"


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
CModel::CModel( CRender *pRender, CRenderObjectMgr *pMgr ) : CRenderObject( pRender, pMgr )
	, m_AnimationControllerListCount	( 0 )
	, m_FrameListCount					( 0 )
	, m_MeshListCount					( 0 )
	, m_pAnimationControllerList		( NULL )
	, m_pFrameList						( NULL )
	, m_pMeshList						( NULL )
	, m_pMeshMgr						( NULL )
{
	SetName( "モデル" );

	m_pMeshMgr = new CRenderObjectMgr( pRender, "モデル:メッシュ" );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CModel::~CModel()
{
	Log_TableBegin();
	Log_PrintCellTitle( 0xFF0000, "解放" );
	Log_PrintCellKind( "モデル" );
	Log_CellBegin( 0 );
	Log_Print( 0x000000, m_Name );

	Sint32 Max;

	// アニメーションコントローラー解放
	Max = m_AnimationControllerListCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		SAFE_RELEASE( m_pAnimationControllerList[i] );
	}
	SAFE_DELETE_ARRAY( m_pAnimationControllerList );

	// フレーム解放
	Max = m_FrameListCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		SAFE_RELEASE( m_pFrameList[i] );
	}
	SAFE_DELETE_ARRAY( m_pFrameList );

	// メッシュ解放
	Max = m_MeshListCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		SAFE_RELEASE( m_pMeshList[i] );
	}
	SAFE_DELETE_ARRAY( m_pMeshList );

	SAFE_DELETE( m_pMeshMgr );

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModel::CreateAnimationController( Sint32 AnimationControllerCount )
{
	if ( AnimationControllerCount > 0 )
	{
		m_AnimationControllerListCount = AnimationControllerCount;
		m_pAnimationControllerList = new CAnimationController * [ AnimationControllerCount ];

		// アニメーション生成
		for ( Sint32 i = 0; i < AnimationControllerCount; i++ )
		{
			m_pAnimationControllerList[i] = new CAnimationController();
		}

		// フレームに通知生成
		for ( Sint32 i = 0; i < m_FrameListCount; i++ )
		{
			m_pFrameList[i]->CreateAnimationData( AnimationControllerCount );
		}
	}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModel::CreateFrameList( Sint32 FrameCount )
{
	m_FrameListCount = FrameCount;
	m_pFrameList = new CFrame * [ FrameCount ];
	// フレーム生成
	for ( Sint32 i = 0; i < FrameCount; i++ )
	{
		m_pFrameList[i] = new CFrame();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModel::CreateMeshList( Sint32 MeshCount )
{
	m_MeshListCount = MeshCount;
	m_pMeshList = new CMesh * [ MeshCount ];
	// メッシュ生成
	for ( Sint32 i = 0; i < MeshCount; i++ )
	{
		m_pMeshList[i] = new CMesh( m_pRender, m_pMeshMgr );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CAnimationController *CModel::GetAnimationControllerPointer( Sint32 Index )
{
	return m_pAnimationControllerList[Index];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFrame *CModel::GetFramePointer( Sint32 Index )
{
	return m_pFrameList[Index];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMesh *CModel::GetMeshPointer( Sint32 Index )
{
	return m_pMeshList[Index];
}	

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFrame *CModel::GetFramePointer( const char *pName )
{
	Sint32 Max = m_FrameListCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		if ( m_pFrameList[i]->IsSame( pName ) )
		{
			return m_pFrameList[i];
		}
	}

	return NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModel::UpdateMesh( void )
{
	Sint32 Max = m_MeshListCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pMeshList[i]->UpdateStream();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModel::ResetAnimationTransform( void )
{
	Sint32 Max = m_FrameListCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pFrameList[i]->ResetAnimationTransform();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModel::SetTransform( Math::Style &Style )
{
	// フレーム
	Math::Matrix mWorld;
	Style.GetTransformWithScale( mWorld );

	Sint32 Max = m_FrameListCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		if ( m_pFrameList[i]->GetParentFrameNo() == -1 )
		{
			m_pFrameList[i]->UpdateTransform( mWorld );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModel::CreateCollision( CCollisionController *&pCollision )
{
	pCollision = new CCollisionController( this, m_FrameListCount );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModel::GetAnimationController( Sint32 Index, CAnimationController *&pAnimationController )
{
	if ( Index < m_AnimationControllerListCount )
	{
		pAnimationController = m_pAnimationControllerList[Index];
		pAnimationController->AddRef();
		return true;
	}
	else
	{
		pAnimationController = NULL;
		return false;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CModel::GetAnimationControllerCount( void )
{
	return m_AnimationControllerListCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFrame *CModel::GetFrame( Sint32 Index )
{
	if ( Index < m_FrameListCount )
	{
		return m_pFrameList[Index];
	}

	return NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CModel::GetFrameCount( void )
{
	return m_FrameListCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMesh *CModel::GetMesh( Sint32 Index )
{
	if ( Index < m_MeshListCount )
	{
		return m_pMeshList[Index];
	}

	return NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CModel::GetMeshCount( void )
{
	return m_MeshListCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModel::UpdateAnimation( Sint32 AnimationNo )
{
	Sint32 Max = m_FrameListCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pFrameList[i]->UpdateAnimationTransform( AnimationNo );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModel::UpdateAnimation( Sint32 AnimationNo1, Sint32 AnimationNo2, Float fWeight )
{
	if ( AnimationNo1 == AnimationNo2 )
	{
		Sint32 Max = m_FrameListCount;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			m_pFrameList[i]->UpdateAnimationTransform( AnimationNo1 );
		}
	}
	ef ( fWeight <= 0.0f )
	{
		Sint32 Max = m_FrameListCount;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			m_pFrameList[i]->UpdateAnimationTransform( AnimationNo1 );
		}
	}
	ef ( fWeight >= 1.0f )
	{
		Sint32 Max = m_FrameListCount;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			m_pFrameList[i]->UpdateAnimationTransform( AnimationNo2 );
		}
	}
	else
	{
		Sint32 Max = m_FrameListCount;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			m_pFrameList[i]->UpdateAnimationTransform( AnimationNo1, AnimationNo2, fWeight );
		}
	}
}

