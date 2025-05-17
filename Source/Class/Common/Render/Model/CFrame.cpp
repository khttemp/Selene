

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Render/Model/CFrame.h"
#include "Class/Common/Render/Model/CMesh.h"
#include "Class/Common/Render/Model/CAnimationData.h"
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
CFrame::CFrame()
	: m_pBoxPoints			( NULL )
	, m_pAnimationDataTbl	( NULL )
	, m_AnimationCount		( 0 )
	, m_ParentFrameNo		( -1 )
	, m_IsBone				( false )
{
	SetName( "フレーム" );

	m_mDefaultLocal.Identity();
	m_mLocal.Identity();
	m_mTransform.Identity();
	m_mBoneOffset.Identity();
	m_mWorld.Identity();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CFrame::~CFrame()
{
	Log_TableBegin();
	Log_PrintCellTitle( 0xFF0000, "解放" );
	Log_PrintCellKind( "フレーム" );
	Log_CellBegin( 0 );
	Log_Print( 0x000000, m_Name );

	SAFE_DELETE_ARRAY( m_pBoxPoints );
	SAFE_DELETE_ARRAY( m_pAnimationDataTbl );

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CFrame::CreateAnimationData( Sint32 AnimationCount )
{
	m_AnimationCount = AnimationCount;
	m_pAnimationDataTbl = new CAnimationData * [ AnimationCount ];
	for ( Sint32 i = 0; i < AnimationCount; i++ )
	{
		m_pAnimationDataTbl[i] = NULL;
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CFrame::SetAnimationData( Sint32 AnimationControllerNo, CAnimationData *pAnimationData )
{
	m_pAnimationDataTbl[AnimationControllerNo] = pAnimationData;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CFrame::ConnectChildFrame( CFrame *pFrame )
{
	m_Child.InsertEnd( pFrame );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CFrame::SetParentFrameNo( Sint32 No )
{
	m_ParentFrameNo = No;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Sint32 CFrame::GetParentFrameNo( void )
{
	return m_ParentFrameNo;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Math::Vector3D *CFrame::GetCollisionPoint( void )
{
	return m_pBoxPoints;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Matrix &CFrame::GetMatrixTransform( void )
{
	return m_mTransform;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Math::Matrix &CFrame::GetMatrixWorld( void )
{
	return m_mWorld;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
Math::Matrix &CFrame::GetMatrixLocal( void )
{
	return m_mLocal;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CFrame::GetTransform( Math::Matrix &Mtx )
{
	Mtx = m_mTransform;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CFrame::GetTransformInverse( Math::Matrix &Mtx )
{
	Mtx.Inverse( m_mTransform );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CFrame::UpdateTransform( const Math::Matrix &mWorld )
{
	// アニメーションあり
	if ( m_IsBone )
	{
		// ローカルの変換をワールドへ
		m_mWorld.Multiply( m_mLocal, mWorld );

		// 子の階層へ
		CBaseObject *pObj = m_Child.GetTop();
		while ( pObj != NULL )
		{
			((CFrame*)pObj)->UpdateTransform( m_mWorld );
			pObj = pObj->GetNext();
		}

		// オフセットを適用
		m_mTransform = m_mBoneOffset * m_mWorld;
	}
	// アニメーションなし
	else
	{
		// ローカルの変換をワールドへ
		m_mTransform.Multiply( m_mLocal, mWorld );

		// 子の階層へ
		CBaseObject *pObj = m_Child.GetTop();
		while ( pObj != NULL )
		{
			((CFrame*)pObj)->UpdateTransform( m_mTransform );
			pObj = pObj->GetNext();
		}

		m_mWorld = m_mTransform;
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CFrame::SetDefaultLocalMatrix( const Math::Matrix &mDefault )
{
	m_mDefaultLocal = mDefault;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CFrame::SetAnimationMatrix( const Math::Matrix &mAnimation )
{
	m_mLocal = mAnimation;
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CFrame::SetBoneOffsetMatrix( const Math::Matrix &mOffset )
{
	m_mBoneOffset = mOffset;
	m_IsBone = true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFrame::SetBounding( const Collision::CBox &OBB )
{
	m_pBoxPoints = new Math::Vector3D [ 8 ];
	for ( Sint32 i = 0; i < 8; i++ )
	{
		m_pBoxPoints[i] = OBB.Points[i];
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CFrame::ResetAnimationTransform( void )
{
	SetAnimationMatrix( m_mDefaultLocal );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CFrame::UpdateAnimationTransform( Sint32 AnimationNo )
{
	CAnimationData *pSrc = NULL;

	// 範囲内？
	if ( AnimationNo < m_AnimationCount )
	{
		pSrc = m_pAnimationDataTbl[AnimationNo];
	}

	// アニメーションある？
	if ( pSrc == NULL )
	{
		return;
	}

	Math::Quaternion qRotate;
	Float fSx, fSy, fSz;
	Float fTx, fTy, fTz;

	pSrc->GetParameter( fSx, fSy, fSz, fTx, fTy, fTz, qRotate );

	// 回転行列
	Math::Matrix mRotate = qRotate;
	// 変換行列
	Math::Matrix mLocal;
	mLocal.Scaling( fSx, fSy, fSz );
	mLocal *= mRotate;
	mLocal.w.Set( fTx, fTy, fTz );
	// ターゲットフレームに設定
	SetAnimationMatrix( mLocal );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CFrame::UpdateAnimationTransform( Sint32 AnimationNo1, Sint32 AnimationNo2, Float fWeight )
{
	CAnimationData *pSrc0 = NULL;
	CAnimationData *pSrc1 = NULL;

	// 範囲内？
	if ( AnimationNo1 < m_AnimationCount )
	{
		pSrc0 = m_pAnimationDataTbl[AnimationNo1];
	}

	// 範囲内？
	if ( AnimationNo2 < m_AnimationCount )
	{
		pSrc1 = m_pAnimationDataTbl[AnimationNo2];
	}

	// アニメーションある？
	if ( (pSrc0 == NULL) && (pSrc0 == NULL) )
	{
		return;
	}
	ef ( (pSrc0 == NULL) || (fWeight == 1.0f) )
	{
		UpdateAnimationTransform( AnimationNo2 );
		return;
	}
	ef ( (pSrc1 == NULL) || (fWeight == 0.0f) )
	{
		UpdateAnimationTransform( AnimationNo1 );
		return;
	}

	Math::Quaternion qRotate0, qRotate1;
	Float fSx0, fSy0, fSz0, fSx1, fSy1, fSz1;
	Float fTx0, fTy0, fTz0, fTx1, fTy1, fTz1;
	Math::Quaternion qRotate;
	Float fSx, fSy, fSz;
	Float fTx, fTy, fTz;

	// パラメーター取得
	pSrc0->GetParameter( fSx0, fSy0, fSz0, fTx0, fTy0, fTz0, qRotate0 );
	pSrc1->GetParameter( fSx1, fSy1, fSz1, fTx1, fTy1, fTz1, qRotate1 );

	// ブレンド
	qRotate.Slerp( qRotate0, qRotate1, fWeight );
	fSx = fSx0 + ((fSx1 - fSx0) * fWeight);
	fSy = fSy0 + ((fSy1 - fSy0) * fWeight);
	fSz = fSz0 + ((fSz1 - fSz0) * fWeight);
	fTx = fTx0 + ((fTx1 - fTx0) * fWeight);
	fTy = fTy0 + ((fTy1 - fTy0) * fWeight);
	fTz = fTz0 + ((fTz1 - fTz0) * fWeight);

	// 回転行列
	Math::Matrix mRotate = qRotate;
	// 変換行列
	Math::Matrix mLocal;
	mLocal.Scaling( fSx, fSy, fSz );
	mLocal *= mRotate;
	mLocal.w.Set( fTx, fTy, fTz );
	// ターゲットフレームに設定
	SetAnimationMatrix( mLocal );
}

