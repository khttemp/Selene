

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Collision/Collision.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Class/Common/Render/Model/CCollisionController.h"
#include "Class/Common/Render/Model/CModel.h"
#include "Class/Common/Render/Model/CFrame.h"
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
CCollisionController::CCollisionController( CModel *pModel, Sint32 Count )
	: m_pModel		( pModel )
	, m_pBoxTbl		( NULL )
	, m_BoxCount	( Count )
	, m_HitFrame	( -1 )
	, m_vHitPosision( 0.0f, 0.0f, 0.0f )
{
	m_pBoxTbl = new Collision::CBox [ m_BoxCount ];
	m_pFrameRefTbl = new CFrame * [ m_BoxCount ];

	m_pModel->AddRef();

	for ( Sint32 i = 0; i < Count; i++ )
	{
		SetEnable( i, true );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCollisionController::~CCollisionController()
{
	SAFE_DELETE_ARRAY( m_pFrameRefTbl );
	SAFE_DELETE_ARRAY( m_pBoxTbl );
	SAFE_RELEASE( m_pModel );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CCollisionController::SetEnable( Sint32 Index, Bool IsEnable )
{
	if ( IsEnable )
	{
		m_pFrameRefTbl[Index] = m_pModel->GetFrame( Index );
		if ( m_pFrameRefTbl[Index]->GetCollisionPoint() == NULL )
		{
			m_pFrameRefTbl[Index] = NULL;
		}
	}
	else
	{
		m_pFrameRefTbl[Index] = NULL;
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CCollisionController::SetEnable( const char *pName, Bool IsEnable )
{
	Sint32 Max = m_pModel->GetFrameCount();
	for ( Sint32 i = 0; i < Max; i++ )
	{
		if ( m_pModel->GetFrame( i )->IsSame( pName ) )
		{
			SetEnable( i, IsEnable );
		}
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CCollisionController::Update( void )
{
	Sint32 Max = m_BoxCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		if ( m_pFrameRefTbl[i] != NULL )
		{
			m_pBoxTbl[i].Transform(
							m_pFrameRefTbl[i]->GetCollisionPoint(),
							m_pFrameRefTbl[i]->GetMatrixTransform() );
		}
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CCollisionController::GetCollisionResult( Sint32 &FrameNo, Math::Vector3D &vPos )
{
	FrameNo = m_HitFrame;
	vPos    = m_vHitPosision;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CCollisionController::Check( CCollisionController *pSrc )
{
	m_HitFrame = -1;
	m_vHitPosision = Math::Vector3D( 0.0f, 0.0f, 0.0f );
	m_vHitNormal = Math::Vector3D( 0.0f, 0.0f, 0.0f );

	Sint32 Max1			=       m_BoxCount;
	Sint32 Max2			= pSrc->m_BoxCount;
	CFrame **pFrmTbl1	=       m_pFrameRefTbl;
	CFrame **pFrmTbl2	= pSrc->m_pFrameRefTbl;
	Collision::CBox *pBoxTbl1		=       m_pBoxTbl;
	Collision::CBox *pBoxTbl2		= pSrc->m_pBoxTbl;

	for ( Sint32 i = 0; i < Max1; i++ )
	{
		if ( pFrmTbl1[i] != NULL )
		{
			for ( Sint32 j = 0; j < Max2; j++ )
			{
				if ( pFrmTbl2[j] != NULL )
				{
					if ( Collision::Box_Box_3D( pBoxTbl1[i], pBoxTbl2[j] ) )
					{
						m_HitFrame = i;
						m_vHitPosision = (m_pBoxTbl[i].Points[0] + m_pBoxTbl[i].Points[6]) / 2.0f;
						return true;
					}
				}
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CCollisionController::Check( Collision::CBox &Src )
{
	m_HitFrame = -1;
	m_vHitPosision = Math::Vector3D( 0.0f, 0.0f, 0.0f );
	m_vHitNormal = Math::Vector3D( 0.0f, 0.0f, 0.0f );

	Sint32 Max = m_BoxCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		if ( m_pFrameRefTbl[i] != NULL )
		{
			if ( Collision::Box_Box_3D( Src, m_pBoxTbl[i] ) )
			{
				m_HitFrame = i;
				m_vHitPosision = (m_pBoxTbl[i].Points[0] + m_pBoxTbl[i].Points[6]) / 2.0f;
				return true;
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CCollisionController::Check( Collision::CLine3D &Src )
{
	m_HitFrame = -1;
	m_vHitPosision = Math::Vector3D( 0.0f, 0.0f, 0.0f );
	m_vHitNormal = Math::Vector3D( 0.0f, 0.0f, 0.0f );

	Sint32 Max = m_BoxCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		if ( m_pFrameRefTbl[i] != NULL )
		{
			if ( Collision::Line_Box_3D( Src, m_pBoxTbl[i] ) )
			{
				m_HitFrame = i;
				return true;
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CCollisionController::Check( Math::Vector3D &Src )
{
	m_HitFrame = -1;
	m_vHitPosision = Math::Vector3D( 0.0f, 0.0f, 0.0f );
	m_vHitNormal = Math::Vector3D( 0.0f, 0.0f, 0.0f );

	Sint32 Max = m_BoxCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		if ( m_pFrameRefTbl[i] != NULL )
		{
			if ( Collision::Point_Box_3D( Src, m_pBoxTbl[i] ) )
			{
				m_HitFrame = i;
				m_vHitPosision = Src;
				return true;
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Bool CCollisionController::CheckOnScreen( Math::Vector2D &Src, Scene::ISceneManager *pSceneMgr )
{
	Math::Vector3D vStart = Math::Vector3D( Src.x, Src.y, 0.0f );
	Math::Vector3D vEnd   = Math::Vector3D( Src.x, Src.y, 1.0f );

	vStart = pSceneMgr->TransformFromScreen( vStart );
	vEnd   = pSceneMgr->TransformFromScreen( vEnd );

	Collision::CLine3D Line( vStart, vEnd );
	return Check( Line );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CCollisionController::Rendering( Renderer::Object::ILine3D *pLine )
{
	Sint32 Max = m_BoxCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		if ( m_pFrameRefTbl[i] != NULL )
		{
			pLine->PushBox( m_pBoxTbl[i], 0xFFFFFFFF );
		}
	}
}


