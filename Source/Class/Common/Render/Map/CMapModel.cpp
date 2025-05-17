

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Render/Map/CMapModel.h"
#include "Class/Common/Render/Map/CMapFrame.h"
#include "Class/Common/Render/Map/CMapMesh.h"
#include "Class/Common/Render/Map/CMapMaterial.h"
#include "Class/Common/Render/3D/CPrimitive3D.h"
#include "Class/Common/Render/3D/CLinePrimitive3D.h"
#include "Class/Platform/Surface/CTexture.h"


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
CMapModel::CMapModel( CRender *pRender, CRenderObjectMgr *pMgr ) : CRenderObject( pRender, pMgr )
	, m_MaterialListCount	( 0 )
	, m_pMaterial			( NULL )
	, m_pMeshMgr			( NULL )
	, m_pTreeDraw			( NULL )
	, m_pTreeCollision		( NULL )
{
	SetName( "マップ" );

	m_pMeshMgr = new CRenderObjectMgr( pRender, "マップ:メッシュ" );
	m_pTreeDraw = new CTreeItem<CMapMesh>;
	m_pTreeCollision = new CTreeItem<CCollision>;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapModel::~CMapModel()
{
	Log_TableBegin();
	Log_PrintCellTitle( 0xFF0000, "解放" );
	Log_PrintCellKind( "マップ" );
	Log_CellBegin( 0 );
	Log_Print( 0x000000, m_Name );

	SAFE_DELETE_ARRAY( m_pMaterial );
	SAFE_DELETE_ARRAY( m_MeshDrawEnableTbl );

	SAFE_DELETE( m_pTreeDraw );
	SAFE_DELETE( m_pTreeCollision );

	SAFE_DELETE( m_pMeshMgr );

	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModel::RenderingBounding( Renderer::Object::ILine3D *pLine )
{
	Sint32 Max = m_pTreeDraw->m_FrameListCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		if ( m_pTreeDraw->m_pFrameList[i]->GetConnectMesh() != -1 )
		{
			m_pTreeDraw->m_pFrameList[i]->RenderingBounding( pLine );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModel::SetAreaInfo( Math::Point3DI Count, Math::Point3DF Size )
{
	m_pTreeDraw->m_pAreaID = new Sint32 [ Count.x * Count.y * Count.z ];
	m_pTreeDraw->m_AreaCount = Count;
	m_pTreeDraw->m_AreaSize = Size;
}

//-----------------------------------------------------------------------------------
/**
//-----------------------------------------------------------------------------------
void CMapModel::SetAreaID( Sint32 *pTbl )
{
	MemoryCopy(
		m_pTreeDraw->m_pAreaID,
		pTbl,
		sizeof(Sint32) * m_pTreeDraw->m_AreaCount.x * m_pTreeDraw->m_AreaCount.y * m_pTreeDraw->m_AreaCount.z );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModel::UpdateMesh( void )
{
	Sint32 Max = m_pTreeDraw->m_ObjectListCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pTreeDraw->m_pObjectList[i]->UpdateStream();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModel::SetFirstFrame( Sint32 FirstFrame )
{
	m_pTreeDraw->m_FirstFrameNo = FirstFrame;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModel::CreateFrameList( Sint32 FrameCount )
{
	m_pTreeDraw->m_FrameListCount = FrameCount;
	m_pTreeDraw->m_pFrameList = new CMapFrame * [ FrameCount ];
	// フレーム生成
	for ( Sint32 i = 0; i < FrameCount; i++ )
	{
		m_pTreeDraw->m_pFrameList[i] = new CMapFrame();
		AddChild( m_pTreeDraw->m_pFrameList[i] );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModel::CreateMeshList( Sint32 MeshCount )
{
	m_pTreeDraw->m_ObjectListCount = MeshCount;
	m_pTreeDraw->m_pObjectList = new CMapMesh * [ MeshCount ];
	m_MeshDrawEnableTbl = new Bool [ MeshCount ];
	// メッシュ生成
	for ( Sint32 i = 0; i < MeshCount; i++ )
	{
		m_MeshDrawEnableTbl[i] = false;
		m_pTreeDraw->m_pObjectList[i] = new CMapMesh( m_pRender, m_pMeshMgr );
		AddChild( m_pTreeDraw->m_pObjectList[i] );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModel::CreateMaterialList( Sint32 MaterialCount )
{
	m_MaterialListCount = MaterialCount;
	m_pMaterial = new CMapMaterial [ MaterialCount ];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModel::Collision_SetAreaInfo( Math::Point3DI Count, Math::Point3DF Size )
{
	m_pTreeCollision->m_pAreaID = new Sint32 [ Count.x * Count.y * Count.z ];
	m_pTreeCollision->m_AreaCount = Count;
	m_pTreeCollision->m_AreaSize = Size;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModel::Collision_SetAreaID( Sint32 *pTbl )
{
	MemoryCopy(
		m_pTreeCollision->m_pAreaID,
		pTbl,
		sizeof(Sint32) * m_pTreeCollision->m_AreaCount.x * m_pTreeCollision->m_AreaCount.y * m_pTreeCollision->m_AreaCount.z );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModel::Collision_SetFirstFrame( Sint32 FirstFrame )
{
	m_pTreeCollision->m_FirstFrameNo = FirstFrame;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModel::Collision_CreateFrameList( Sint32 FrameCount )
{
	m_pTreeCollision->m_FrameListCount = FrameCount;
	m_pTreeCollision->m_pFrameList = new CMapFrame * [ FrameCount ];
	// フレーム生成
	for ( Sint32 i = 0; i < FrameCount; i++ )
	{
		m_pTreeCollision->m_pFrameList[i] = new CMapFrame();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModel::Collision_CreateList( Sint32 CollisionCount )
{
	m_pTreeCollision->m_ObjectListCount = CollisionCount;
	m_pTreeCollision->m_pObjectList = new CCollision * [ CollisionCount ];
	// メッシュ生成
	for ( Sint32 i = 0; i < CollisionCount; i++ )
	{
		m_pTreeCollision->m_pObjectList[i] = new CCollision;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapFrame *CMapModel::Collision_GetFramePointer( Sint32 Index )
{
	return m_pTreeCollision->m_pFrameList[Index];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCollision *CMapModel::Collision_GetPointer( Sint32 Index )
{
	return m_pTreeCollision->m_pObjectList[Index];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapFrame *CMapModel::GetFramePointer( Sint32 Index )
{
	return m_pTreeDraw->m_pFrameList[Index];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapMesh *CMapModel::GetMeshPointer( Sint32 Index )
{
	return m_pTreeDraw->m_pObjectList[Index];
}	

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapMaterial *CMapModel::GetMaterialPointer( Sint32 Index )
{
	return &m_pMaterial[Index];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModel::SetMeshDrawEnable( Sint32 Index )
{
	m_MeshDrawEnableTbl[Index] = true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapModel::GetMeshDrawEnable( Sint32 Index )
{
	return m_MeshDrawEnableTbl[Index];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CMapModel::GetMeshCount( void )
{
	return m_pTreeDraw->m_ObjectListCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CMapModel::GetCollisionCount( void )
{
	return m_pTreeCollision->m_ObjectListCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModel::UpdateFrustumCulling( Scene::CSceneManagerBase *pScene )
{
	// 描画フラグクリア
	MemoryClear( m_MeshDrawEnableTbl, sizeof(Bool) * m_pTreeDraw->m_ObjectListCount );

	// オクトツリーのカリング
	m_pTreeDraw->m_pFrameList[m_pTreeDraw->m_FirstFrameNo]->RenderingTree( pScene->GetActiveCamera() );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Point3DI CMapModel::Collision_GetAreaPosition( const Math::Vector3D &vPos )
{
	const Collision::CBox &Box = m_pTreeCollision->m_pFrameList[m_pTreeCollision->m_FirstFrameNo]->GetOBB();

	return Math::Point3DI(
				toI((vPos.x - Box.Points[0].x) / m_pTreeCollision->m_AreaSize.x),
				toI((vPos.y - Box.Points[0].y) / m_pTreeCollision->m_AreaSize.y),
				toI((vPos.z - Box.Points[0].z) / m_pTreeCollision->m_AreaSize.z) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapModel::Collision_ComputeMapArea( Collision::CLine3D Ray, Float fRadius, Math::Point3DI &PtStart, Math::Point3DI &PtEnd )
{
	Math::Vector3D vMin, vMax;
	m_pTreeCollision->m_pFrameList[m_pTreeCollision->m_FirstFrameNo]->GetOBB( vMin, vMax );

	// 大小関係解決
	if ( Ray.vStart.x > Ray.vEnd.x ) SWAP( Ray.vStart.x, Ray.vEnd.x );
	if ( Ray.vStart.y > Ray.vEnd.y ) SWAP( Ray.vStart.y, Ray.vEnd.y );
	if ( Ray.vStart.z > Ray.vEnd.z ) SWAP( Ray.vStart.z, Ray.vEnd.z );

	// 半径分拡大
	vMin -= fRadius;
	vMax += fRadius;

	// 範囲チェック
	if ( Ray.vEnd.x < vMin.x ) return false;
	if ( Ray.vEnd.y < vMin.y ) return false;
	if ( Ray.vEnd.z < vMin.z ) return false;
	if ( Ray.vStart.x > vMax.x ) return false;
	if ( Ray.vStart.y > vMax.y ) return false;
	if ( Ray.vStart.z > vMax.z ) return false;

	// 開始＆終了－箱番号
	PtStart = Collision_GetAreaPosition( Ray.vStart );
	PtEnd   = Collision_GetAreaPosition( Ray.vEnd );

	// 判定漏れ対策
	PtStart = PtStart - Math::Point3DI(1, 1, 1);
	PtEnd   = PtEnd   + Math::Point3DI(1, 1, 1);

	// 範囲丸めこみ
	if ( PtStart.x < 0 ) PtStart.x = 0;
	if ( PtStart.y < 0 ) PtStart.y = 0;
	if ( PtStart.z < 0 ) PtStart.z = 0;
	if ( PtEnd.x >= m_pTreeCollision->m_AreaCount.x ) PtEnd.x = m_pTreeCollision->m_AreaCount.x - 1;
	if ( PtEnd.y >= m_pTreeCollision->m_AreaCount.y ) PtEnd.y = m_pTreeCollision->m_AreaCount.y - 1;
	if ( PtEnd.z >= m_pTreeCollision->m_AreaCount.z ) PtEnd.z = m_pTreeCollision->m_AreaCount.z - 1;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCollision *CMapModel::Collision_GetArea( Sint32 x, Sint32 y, Sint32 z )
{
	Sint32 ax = x;
	Sint32 ay = m_pTreeCollision->m_AreaCount.x * y;
	Sint32 az = m_pTreeCollision->m_AreaCount.x * m_pTreeCollision->m_AreaCount.y * z;

	Sint32 No = m_pTreeCollision->m_pAreaID[ ax + ay + az ];
	if ( No != -1 )
	{
		return m_pTreeCollision->m_pObjectList[No];
	}
	return NULL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapModel::HitCheckByRay( const Collision::CLine3D &Ray )
{
	Math::Point3DI PtStart, PtEnd;

	//----------------------------------------------------------------
	// 当たり判定用事前処理
	//----------------------------------------------------------------
	if ( !Collision_ComputeMapArea( Ray, 0.0f, PtStart, PtEnd ) )
	{
		return false;
	}

	//----------------------------------------------------------------
	// 当たり判定処理開始
	//----------------------------------------------------------------
	// OBBツリーの中を検索
	for ( Sint32 z = PtStart.z; z <= PtEnd.z; z++ )
	{
		for ( Sint32 y = PtStart.y; y <= PtEnd.y; y++ )
		{
			for ( Sint32 x = PtStart.x; x <= PtEnd.x; x++ )
			{
				// メッシュに対して当たり判定
				CCollision *pCollision = Collision_GetArea( x, y, z );

				if ( (pCollision != NULL) && pCollision->HitCheckByRay( Ray ) )
				{
					return true;
				}
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapModel::HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box )
{
	Math::Point3DI PtStart, PtEnd;

	//----------------------------------------------------------------
	// 当たり判定用事前処理
	//----------------------------------------------------------------
	if ( !Collision_ComputeMapArea( Ray, 0.0f, PtStart, PtEnd ) )
	{
		return false;
	}

	//----------------------------------------------------------------
	// 当たり判定処理開始
	//----------------------------------------------------------------
	// OBBツリーの中を検索
	for ( Sint32 z = PtStart.z; z <= PtEnd.z; z++ )
	{
		for ( Sint32 y = PtStart.y; y <= PtEnd.y; y++ )
		{
			for ( Sint32 x = PtStart.x; x <= PtEnd.x; x++ )
			{
				// メッシュに対して当たり判定
				CCollision *pCollision = Collision_GetArea( x, y, z );
				if ( (pCollision != NULL) && pCollision->HitCheckByRay( Ray, Box ) )
				{
					return true;
				}
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapModel::HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResult &Out )
{
	Math::Point3DI PtStart, PtEnd;

	//----------------------------------------------------------------
	// 当たり判定用事前処理
	//----------------------------------------------------------------
	if ( !Collision_ComputeMapArea( Ray, 0.0f, PtStart, PtEnd ) )
	{
		return false;
	}

	//----------------------------------------------------------------
	// 当たり判定処理開始
	//----------------------------------------------------------------
	Bool bRet = false;
	Float fLengthSq = FLT_MAX;

	// OBBツリーの中を検索
	for ( Sint32 z = PtStart.z; z <= PtEnd.z; z++ )
	{
		for ( Sint32 y = PtStart.y; y <= PtEnd.y; y++ )
		{
			for ( Sint32 x = PtStart.x; x <= PtEnd.x; x++ )
			{
				// メッシュに対して当たり判定
				SCollisionResult Ret;
				CCollision *pCollision = Collision_GetArea( x, y, z );
				if ( (pCollision != NULL) && pCollision->HitCheckByRay( Ray, Ret ) )
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
		}
	}

	return bRet;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapModel::HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResult &Out, Collision::CBox &Box )
{
	Math::Point3DI PtStart, PtEnd;

	//----------------------------------------------------------------
	// 当たり判定用事前処理
	//----------------------------------------------------------------
	if ( !Collision_ComputeMapArea( Ray, 0.0f, PtStart, PtEnd ) )
	{
		return false;
	}

	//----------------------------------------------------------------
	// 当たり判定処理開始
	//----------------------------------------------------------------
	Bool bRet = false;
	Float fLengthSq = FLT_MAX;

	// OBBツリーの中を検索
	for ( Sint32 z = PtStart.z; z <= PtEnd.z; z++ )
	{
		for ( Sint32 y = PtStart.y; y <= PtEnd.y; y++ )
		{
			for ( Sint32 x = PtStart.x; x <= PtEnd.x; x++ )
			{
				// メッシュに対して当たり判定
				Collision::CBox TempOBB;
				SCollisionResult Ret;
				CCollision *pCollision = Collision_GetArea( x, y, z );
				if ( (pCollision != NULL) && pCollision->HitCheckByRay( Ray, Ret, TempOBB ) )
				{
					// 始点からの距離がより短いなら代入
					Float fLen = (Ret.vHitPosition - Ray.vStart).LengthSq();
					if ( fLengthSq > fLen )
					{
						fLengthSq = fLen;
						Out = Ret;
						Box = TempOBB;
					}
					bRet = true;
				}
			}
		}
	}

	return bRet;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapModel::HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResultExtend &Out )
{
	Math::Point3DI PtStart, PtEnd;

	//----------------------------------------------------------------
	// 当たり判定用事前処理
	//----------------------------------------------------------------
	if ( !Collision_ComputeMapArea( Ray, 0.0f, PtStart, PtEnd ) )
	{
		return false;
	}

	//----------------------------------------------------------------
	// 当たり判定処理開始
	//----------------------------------------------------------------
	Bool bRet = false;
	Float fLengthSq = FLT_MAX;

	// OBBツリーの中を検索
	for ( Sint32 z = PtStart.z; z <= PtEnd.z; z++ )
	{
		for ( Sint32 y = PtStart.y; y <= PtEnd.y; y++ )
		{
			for ( Sint32 x = PtStart.x; x <= PtEnd.x; x++ )
			{
				// メッシュに対して当たり判定
				Collision::CBox TempOBB;
				SCollisionResultExtend Ret;
				CCollision *pCollision = Collision_GetArea( x, y, z );
				if ( (pCollision != NULL) && pCollision->HitCheckByRay( Ray, Ret ) )
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
		}
	}

	return bRet;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapModel::HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResultExtend &Out, Collision::CBox &Box )
{
	Math::Point3DI PtStart, PtEnd;

	//----------------------------------------------------------------
	// 当たり判定用事前処理
	//----------------------------------------------------------------
	if ( !Collision_ComputeMapArea( Ray, 0.0f, PtStart, PtEnd ) )
	{
		return false;
	}

	//----------------------------------------------------------------
	// 当たり判定処理開始
	//----------------------------------------------------------------
	Bool bRet = false;
	Float fLengthSq = FLT_MAX;

	// OBBツリーの中を検索
	for ( Sint32 z = PtStart.z; z <= PtEnd.z; z++ )
	{
		for ( Sint32 y = PtStart.y; y <= PtEnd.y; y++ )
		{
			for ( Sint32 x = PtStart.x; x <= PtEnd.x; x++ )
			{
				// メッシュに対して当たり判定
				Collision::CBox TempOBB;
				SCollisionResultExtend Ret;
				CCollision *pCollision = Collision_GetArea( x, y, z );
				if ( (pCollision != NULL) && pCollision->HitCheckByRay( Ray, Ret, TempOBB ) )
				{
					// 始点からの距離がより短いなら代入
					Float fLen = (Ret.vHitPosition - Ray.vStart).LengthSq();
					if ( fLengthSq > fLen )
					{
						fLengthSq = fLen;
						Out = Ret;
						Box = TempOBB;
					}
					bRet = true;
				}
			}
		}
	}

	return bRet;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapModel::HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius )
{
	Math::Point3DI PtStart, PtEnd;

	//----------------------------------------------------------------
	// 当たり判定用事前処理
	//----------------------------------------------------------------
	if ( !Collision_ComputeMapArea( Ray, fRadius, PtStart, PtEnd ) )
	{
		return false;
	}

	//----------------------------------------------------------------
	// 当たり判定処理開始
	//----------------------------------------------------------------
	// OBBツリーの中を検索
	for ( Sint32 z = PtStart.z; z <= PtEnd.z; z++ )
	{
		for ( Sint32 y = PtStart.y; y <= PtEnd.y; y++ )
		{
			for ( Sint32 x = PtStart.x; x <= PtEnd.x; x++ )
			{
				// メッシュに対して当たり判定
				CCollision *pCollision = Collision_GetArea( x, y, z );
				if ( (pCollision != NULL) && pCollision->HitCheckBySphere( Ray, fRadius ) )
				{
					return true;
				}
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapModel::HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Collision::CBox &Box )
{
	Math::Point3DI PtStart, PtEnd;

	//----------------------------------------------------------------
	// 当たり判定用事前処理
	//----------------------------------------------------------------
	if ( !Collision_ComputeMapArea( Ray, fRadius, PtStart, PtEnd ) )
	{
		return false;
	}

	//----------------------------------------------------------------
	// 当たり判定処理開始
	//----------------------------------------------------------------
	// OBBツリーの中を検索
	for ( Sint32 z = PtStart.z; z <= PtEnd.z; z++ )
	{
		for ( Sint32 y = PtStart.y; y <= PtEnd.y; y++ )
		{
			for ( Sint32 x = PtStart.x; x <= PtEnd.x; x++ )
			{
				// メッシュに対して当たり判定
				CCollision *pCollision = Collision_GetArea( x, y, z );
				if ( (pCollision != NULL) && pCollision->HitCheckBySphere( Ray, fRadius, Box ) )
				{
					return true;
				}
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapModel::HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, SCollisionResultSphere &Out )
{
	Math::Point3DI PtStart, PtEnd;

	//----------------------------------------------------------------
	// 当たり判定用事前処理
	//----------------------------------------------------------------
	if ( !Collision_ComputeMapArea( Ray, fRadius, PtStart, PtEnd ) )
	{
		return false;
	}

	//----------------------------------------------------------------
	// 当たり判定処理開始
	//----------------------------------------------------------------
	Bool bRet = false;
	Float fLengthSq = FLT_MAX;

	// OBBツリーの中を検索
	for ( Sint32 z = PtStart.z; z <= PtEnd.z; z++ )
	{
		for ( Sint32 y = PtStart.y; y <= PtEnd.y; y++ )
		{
			for ( Sint32 x = PtStart.x; x <= PtEnd.x; x++ )
			{
				// メッシュに対して当たり判定
				SCollisionResultSphere Ret;
				CCollision *pCollision = Collision_GetArea( x, y, z );
				if ( (pCollision != NULL) && pCollision->HitCheckBySphere( Ray, fRadius, Ret ) )
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
		}
	}

	return bRet;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapModel::HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, SCollisionResultSphere &Out, Collision::CBox &Box )
{
	Math::Point3DI PtStart, PtEnd;

	//----------------------------------------------------------------
	// 当たり判定用事前処理
	//----------------------------------------------------------------
	if ( !Collision_ComputeMapArea( Ray, fRadius, PtStart, PtEnd ) )
	{
		return false;
	}

	//----------------------------------------------------------------
	// 当たり判定処理開始
	//----------------------------------------------------------------
	Bool bRet = false;
	Float fLengthSq = FLT_MAX;

	// OBBツリーの中を検索
	for ( Sint32 z = PtStart.z; z <= PtEnd.z; z++ )
	{
		for ( Sint32 y = PtStart.y; y <= PtEnd.y; y++ )
		{
			for ( Sint32 x = PtStart.x; x <= PtEnd.x; x++ )
			{
				// メッシュに対して当たり判定
				Collision::CBox TempOBB;
				SCollisionResultSphere Ret;
				CCollision *pCollision = Collision_GetArea( x, y, z );
				if ( (pCollision != NULL) && pCollision->HitCheckBySphere( Ray, fRadius, Ret, TempOBB ) )
				{
					// 始点からの距離がより短いなら代入
					Float fLen = (Ret.vHitPosition - Ray.vStart).LengthSq();
					if ( fLengthSq > fLen )
					{
						fLengthSq = fLen;
						Out = Ret;
						Box = TempOBB;
					}
					bRet = true;
				}
			}
		}
	}

	return bRet;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapModel::HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, SCollisionResultSphereExtend &Out )
{
	Math::Point3DI PtStart, PtEnd;

	//----------------------------------------------------------------
	// 当たり判定用事前処理
	//----------------------------------------------------------------
	if ( !Collision_ComputeMapArea( Ray, fRadius, PtStart, PtEnd ) )
	{
		return false;
	}

	//----------------------------------------------------------------
	// 当たり判定処理開始
	//----------------------------------------------------------------
	Bool bRet = false;
	Float fLengthSq = FLT_MAX;

	// OBBツリーの中を検索
	for ( Sint32 z = PtStart.z; z <= PtEnd.z; z++ )
	{
		for ( Sint32 y = PtStart.y; y <= PtEnd.y; y++ )
		{
			for ( Sint32 x = PtStart.x; x <= PtEnd.x; x++ )
			{
				// メッシュに対して当たり判定
				Collision::CBox TempOBB;
				SCollisionResultSphereExtend Ret;
				CCollision *pCollision = Collision_GetArea( x, y, z );
				if ( (pCollision != NULL) && pCollision->HitCheckBySphere( Ray, fRadius, Ret ) )
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
		}
	}

	return bRet;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapModel::HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, SCollisionResultSphereExtend &Out, Collision::CBox &Box )
{
	Math::Point3DI PtStart, PtEnd;

	//----------------------------------------------------------------
	// 当たり判定用事前処理
	//----------------------------------------------------------------
	if ( !Collision_ComputeMapArea( Ray, fRadius, PtStart, PtEnd ) )
	{
		return false;
	}

	//----------------------------------------------------------------
	// 当たり判定処理開始
	//----------------------------------------------------------------
	Bool bRet = false;
	Float fLengthSq = FLT_MAX;

	// OBBツリーの中を検索
	for ( Sint32 z = PtStart.z; z <= PtEnd.z; z++ )
	{
		for ( Sint32 y = PtStart.y; y <= PtEnd.y; y++ )
		{
			for ( Sint32 x = PtStart.x; x <= PtEnd.x; x++ )
			{
				// メッシュに対して当たり判定
				Collision::CBox TempOBB;
				SCollisionResultSphereExtend Ret;
				CCollision *pCollision = Collision_GetArea( x, y, z );
				if ( (pCollision != NULL) && pCollision->HitCheckBySphere( Ray, fRadius, Ret, TempOBB ) )
				{
					// 始点からの距離がより短いなら代入
					Float fLen = (Ret.vHitPosition - Ray.vStart).LengthSq();
					if ( fLengthSq > fLen )
					{
						fLengthSq = fLen;
						Out = Ret;
						Box = TempOBB;
					}
					bRet = true;
				}
			}
		}
	}

	return bRet;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModel::CreateCollisionDrawPrimitive( Renderer::Object::ILine3D *pLine )
{
	for ( Sint32 z = 0; z < m_pTreeCollision->m_AreaCount.z; z++ )
	{
		for ( Sint32 y = 0; y < m_pTreeCollision->m_AreaCount.y; y++ )
		{
			for ( Sint32 x = 0; x < m_pTreeCollision->m_AreaCount.x; x++ )
			{
				CCollision *pCollision = Collision_GetArea( x, y, z );
				if ( pCollision != NULL )
				{
					Sint32 FaceCnt = pCollision->GetPolygonCount();
					for ( Sint32 i = 0; i < FaceCnt; i++ )
					{
						SCollisionFace &Face = pCollision->GetFace( i );

						SCollisionVertex &Vtx0 = pCollision->GetVertex( Face.Index[0] );
						SCollisionVertex &Vtx1 = pCollision->GetVertex( Face.Index[1] );
						SCollisionVertex &Vtx2 = pCollision->GetVertex( Face.Index[2] );

						Renderer::SLineVertex3D Line[] = {
							{
								{ Vtx0.Position, 0xFF00FF00 },
								{ Vtx1.Position, 0xFF00FF00 },
							},
							{
								{ Vtx1.Position, 0xFF00FF00 },
								{ Vtx2.Position, 0xFF00FF00 },
							},
							{
								{ Vtx2.Position, 0xFF00FF00 },
								{ Vtx0.Position, 0xFF00FF00 },
							},
						};
						pLine->Push( Line, 3 );
					}
				}
			}
		}
	}
}

