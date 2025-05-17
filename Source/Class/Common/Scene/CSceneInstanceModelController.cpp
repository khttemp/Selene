

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CSceneInstanceModelController.h"
#include "Class/Common/Render/Model/CModel.h"
#include "Class/Common/Render/Model/CFrame.h"
#include "Class/Common/Render/Model/CMesh.h"
#include "Class/Common/Render/Model/CAnimationController.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CInstanceModelController::CInstanceModelController( CSceneManagerBase *pSceneMgr, Renderer::Object::IModel *pObject, Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr ) : Renderer::CRenderObject( pRender, pMgr )
	, m_pModel				( NULL )
	, m_ObjectCount			( 0 )
	, m_pObjectTbl			( NULL )
	, m_pCollision			( NULL )
	, m_AnimationCount		( 0 )
	, m_pAnimationCtrlTbl	( NULL )
{
	Sint32 Max;

	m_pModel = (Renderer::Object::CModel*)pObject;
	m_pModel->AddRef();

	// 子に連結
	pSceneMgr->AddChild( this );
	// メッシュ数
	m_ObjectCount = m_pModel->GetMeshCount();
	// メッシュデータ
	m_pObjectTbl = new CInstanceModelControllerObject * [ m_ObjectCount ];
	Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pObjectTbl[i] = new CInstanceModelControllerObject();
	}

	// モデル内のアニメーション数を取得
	m_AnimationCount = m_pModel->GetAnimationControllerCount();
	// アニメーションコントローラーを取得
	m_pAnimationCtrlTbl = new Renderer::Object::CAnimationController * [ m_AnimationCount ];
	Max = m_AnimationCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pModel->GetAnimationController( i, m_pAnimationCtrlTbl[i] );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CInstanceModelController::~CInstanceModelController()
{
	for ( Sint32 i = 0; i < m_ObjectCount; i++ )
	{
		SAFE_DELETE( m_pObjectTbl[i] );
	}
	SAFE_DELETE_ARRAY( m_pObjectTbl );

	for ( Sint32 i = 0; i < m_AnimationCount; i++ )
	{
		SAFE_RELEASE( m_pAnimationCtrlTbl[i] );
	}
	SAFE_DELETE_ARRAY( m_pAnimationCtrlTbl );

	SAFE_RELEASE( m_pCollision );
	SAFE_RELEASE( m_pModel );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CInstanceModelControllerObject *CInstanceModelController::GetControllerObject( Sint32 Index )
{
	return m_pObjectTbl[Index];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CInstanceModelController::GetAnimationCount( void )
{
	return m_AnimationCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CInstanceModelController::GetAnimationLastTime( Sint32 AnimationNo )
{
	if ( m_AnimationCount > 0 )
	{
		return m_pAnimationCtrlTbl[AnimationNo]->GetLastTime();
	}

	return 0.0f;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelController::TransformReset( void )
{
	// 変換初期化
	Style::TransformReset();

	// アニメーション初期化
	m_pModel->ResetAnimationTransform();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelController::TransformUpdate( void )
{
	TransformUpdateCollisionOnly();
	TransformUpdateActorOnly();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelController::TransformUpdateCollisionOnly( void )
{
	// モデルに通達
	m_pModel->SetTransform( *this );

	// コリジョン
	if ( m_pCollision != NULL )
	{
		m_pCollision->Update();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelController::TransformUpdateActorOnly( void )
{
	// レンダリングアクターの更新
	Sint32 Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pObjectTbl[i]->Update();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelController::UpdateAnimation( Sint32 AnimationNo, Float fAnimationTime )
{
	if ( m_AnimationCount > 0 )
	{
		m_pAnimationCtrlTbl[AnimationNo]->Update( fAnimationTime, ANIMATION_TYPE_LINEAR );

		// アニメーション更新
		m_pModel->UpdateAnimation( AnimationNo );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelController::UpdateAnimation( Sint32 AnimationNo1, Float fAnimationTime1, Sint32 AnimationNo2, Float fAnimationTime2, Float fWeight )
{
	if ( m_AnimationCount > 0 )
	{
		m_pAnimationCtrlTbl[AnimationNo1]->Update( fAnimationTime1, ANIMATION_TYPE_LINEAR );
		m_pAnimationCtrlTbl[AnimationNo2]->Update( fAnimationTime2, ANIMATION_TYPE_LINEAR );

		// アニメーション更新
		m_pModel->UpdateAnimation( AnimationNo1, AnimationNo2, fWeight );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelController::RenderingRequest( void )
{
	// レンダリングキューに追加
	Sint32 Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pObjectTbl[i]->SetDrawEnable( true );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelController::RenderingBounding( Renderer::Object::ILine3D *pLine )
{
	// レンダリングキューに追加
	Sint32 Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pObjectTbl[i]->RenderingBounding( pLine );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelController::SetCullTestEnable( Bool IsEnable )
{
	Sint32 Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pObjectTbl[i]->SetCullTestEnable( IsEnable );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CInstanceModelController::GetFrameCount( void )
{
	return m_pModel->GetFrameCount();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CInstanceModelController::Frame_GetIndex( const char *pName )
{
	Sint32 Cnt = m_pModel->GetFrameCount();
	for ( Sint32 i = 0; i < Cnt; i++ )
	{
		Renderer::Object::CFrame *pFrame = m_pModel->GetFramePointer( i );
		if ( pFrame->IsSame( pName ) )
		{
			return i;
		}
	}

	return -1;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Matrix &CInstanceModelController::Frame_GetTransformLocal( Sint32 Index )
{
	return m_pModel->GetFramePointer( Index )->GetMatrixLocal();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Matrix &CInstanceModelController::Frame_GetTransformWorld( Sint32 Index )
{
	return m_pModel->GetFramePointer( Index )->GetMatrixWorld();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelController::Collision_Create( void )
{
	if ( m_pCollision == NULL )
	{
		// コリジョン生成
		m_pModel->CreateCollision( m_pCollision );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelController::Collision_SetEnable( Sint32 Index, Bool IsEnable )
{
	if ( m_pCollision == NULL ) return;

	m_pCollision->SetEnable( Index, IsEnable );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelController::Collision_SetEnable( const char *pName, Bool IsEnable )
{
	if ( m_pCollision == NULL ) return;

	m_pCollision->SetEnable( pName, IsEnable );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelController::Collision_Rendering( Renderer::Object::ILine3D *pLine )
{
	if ( m_pCollision == NULL ) return;

	m_pCollision->Rendering( pLine );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelController::Collision_GetResult( Sint32 &FrameNo, Math::Vector3D &vPos )
{
	if ( m_pCollision == NULL ) return;

	m_pCollision->GetCollisionResult( FrameNo, vPos );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInstanceModelController::Collision_Check( IModelActor *pSrc )
{
	if ( m_pCollision == NULL ) return false;
	if ( pSrc == NULL ) return false;
	if ( pSrc->IsInvalid() ) return false;

	return m_pCollision->Check( ((CInstanceModelController*)pSrc)->m_pCollision );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInstanceModelController::Collision_Check( Collision::CBox &Src )
{
	if ( m_pCollision == NULL ) return false;

	return m_pCollision->Check( Src );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInstanceModelController::Collision_Check( Collision::CLine3D &Src )
{
	if ( m_pCollision == NULL ) return false;

	return m_pCollision->Check( Src );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInstanceModelController::Collision_Check( Math::Vector3D &Src )
{
	if ( m_pCollision == NULL ) return false;

	return m_pCollision->Check( Src );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInstanceModelController::Collision_CheckOnScreen( Math::Vector2D &Src, ISceneManager *pSceneMgr )
{
	if ( m_pCollision == NULL ) return false;

	return m_pCollision->CheckOnScreen( Src, pSceneMgr );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInstanceModelController::HitCheckByRay( const Collision::CLine3D &Ray )
{
	Sint32 Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		if ( m_pObjectTbl[i]->HitCheckByRay( Ray ) )
		{
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInstanceModelController::HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box )
{
	Sint32 Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		if ( m_pObjectTbl[i]->HitCheckByRay( Ray, Box ) )
		{
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInstanceModelController::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out )
{
	Bool bRet = false;
	Float fLengthSq = FLT_MAX;

	Sint32 Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		Renderer::SCollisionResult Ret;
		if ( m_pObjectTbl[i]->HitCheckByRay( Ray, Ret ) )
		{
			// 始点からの距離がより短いなら代入
			Float fLen = (Ret.vHitPosition - Ray.vStart).LengthSq();
			if ( fLengthSq > fLen )
			{
				fLengthSq = fLen;
				Out = Ret;
			}

			bRet = true;
		}
	}

	return bRet;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInstanceModelController::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out, Collision::CBox &Box )
{
	Bool bRet = false;
	Float fLengthSq = FLT_MAX;

	Sint32 Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		Collision::CBox TempOBB;
		Renderer::SCollisionResult Ret;
		if ( m_pObjectTbl[i]->HitCheckByRay( Ray, Ret, TempOBB ) )
		{
			// 始点からの距離がより短いなら代入
			Float fLen = (Ret.vHitPosition - Ray.vStart).LengthSq();
			if ( fLengthSq > fLen )
			{
				fLengthSq = fLen;
				Box = TempOBB;
				Out = Ret;
			}

			bRet = true;
		}
	}

	return bRet;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInstanceModelController::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out )
{
	Bool bRet = false;
	Float fLengthSq = FLT_MAX;

	Sint32 Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		Renderer::SCollisionResultExtend Ret;
		if ( m_pObjectTbl[i]->HitCheckByRay( Ray, Ret ) )
		{
			// 始点からの距離がより短いなら代入
			Float fLen = (Ret.vHitPosition - Ray.vStart).LengthSq();
			if ( fLengthSq > fLen )
			{
				fLengthSq = fLen;
				Out = Ret;
			}

			bRet = true;
		}
	}

	return bRet;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInstanceModelController::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out, Collision::CBox &Box )
{
	Bool bRet = false;
	Float fLengthSq = FLT_MAX;

	Sint32 Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		Collision::CBox TempOBB;
		Renderer::SCollisionResultExtend Ret;
		if ( m_pObjectTbl[i]->HitCheckByRay( Ray, Ret, TempOBB ) )
		{
			// 始点からの距離がより短いなら代入
			Float fLen = (Ret.vHitPosition - Ray.vStart).LengthSq();
			if ( fLengthSq > fLen )
			{
				fLengthSq = fLen;
				Box = TempOBB;
				Out = Ret;
			}

			bRet = true;
		}
	}

	return bRet;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelController::CreateCollisionDrawPrimitive( Renderer::Object::ILine3D *pLine )
{
	Sint32 Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pObjectTbl[i]->CreateCollisionDrawPrimitive( pLine );
	}
}
