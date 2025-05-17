

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/File/CFileManager.h"
#include "Class/Common/Render/Map/CMapModel.h"
#include "Class/Common/Render/Map/CMapModelLoader.h"
#include "Class/Common/Render/Map/CMapFrame.h"
#include "Class/Common/Render/Map/CMapMesh.h"
#include "Class/Common/Render/Map/CMapMaterial.h"
#include "Class/Platform/Surface/CTexture.h"
#include "Common/STM.h"


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
CMapModelLoader::CMapModelLoader( CMapModel *pModel, CRender *pRender )
{
	m_pModel = pModel;
	m_pModel->AddRef();

	m_pRender = pRender;
	m_pRender->AddRef();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapModelLoader::~CMapModelLoader()
{
	SAFE_RELEASE( m_pModel );
	SAFE_RELEASE( m_pRender );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapModelLoader::LoadFromMemory( const Uint8 *pData, Sint32 Size )
{
	Sint32 Pos				= 0;
	Sint32 FrameIndex		= 0;
	Sint32 MeshIndex		= 0;
	Sint32 MaterialIndex	= 0;

	//--------------------------------------------------------------------
	// データ取得ループ
	//--------------------------------------------------------------------
	while ( Pos < Size )
	{
		// チャンク取得
		const STM_CHUNK *pChunk = (const STM_CHUNK*)pData;
		pData += sizeof(STM_CHUNK);
		Pos += sizeof(STM_CHUNK);

		// チャンク解析
		switch ( pChunk->Chunk )
		{
		case 'STM':
			Load_STM( pData, pChunk->Size );
			break;
		case 'AREA':
			Load_AREA( pData, pChunk->Size );
			break;
		case 'MTRL':
			Load_MTRL( pData, pChunk->Size, MaterialIndex++ );
			break;
		case 'FRM':
			Load_FRM( pData, pChunk->Size, FrameIndex++ );
			break;
		case 'MESH':
			Load_MESH( pData, pChunk->Size, MeshIndex++ );
			break;
		case 'CLSN':
			Load_CLSN( pData, pChunk->Size );
			break;
		}

		// チャンクサイズ分進める
		pData += pChunk->Size;
		Pos += pChunk->Size;
	}

	//--------------------------------------------------------------------
	// メッシュのアップデート
	//--------------------------------------------------------------------
	m_pModel->UpdateMesh();

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_STM( const Uint8 *pData, Sint32 Size )
{
	STM_FILEHEAD Head = *((STM_FILEHEAD*)pData);

	// メッシュとフレームを生成
	m_pModel->SetFirstFrame( Head.FirstFrame );
	m_pModel->CreateFrameList( Head.FrameCount );
	m_pModel->CreateMeshList( Head.MeshCount );
	m_pModel->CreateMaterialList( Head.MaterialCount );

	m_pModel->SetAreaInfo(
		Math::Point3DI(Head.CellCountX,Head.CellCountY,Head.CellCountZ),
		Math::Point3DF(Head.fCellSizeX,Head.fCellSizeY,Head.fCellSizeZ) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_AREA( const Uint8 *pData, Sint32 Size )
{
	m_pModel->SetAreaID( (Sint32*)pData );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_MTRL( const Uint8 *pData, Sint32 Size, Sint32 MaterialNo )
{
	CMapMaterial *pMtrl = m_pModel->GetMaterialPointer( MaterialNo );

	//-----------------------------------------------------------
	// チャンク解析
	//-----------------------------------------------------------
	Sint32 Pos = 0;
	while ( Pos < Size )
	{
		const STM_CHUNK *pChunk = (const STM_CHUNK*)pData;
		pData += sizeof(STM_CHUNK);
		Pos += sizeof(STM_CHUNK);

		switch ( pChunk->Chunk )
		{
		case 'TEXC': //------------------------------------ テクスチャ
			Load_TEXC( pData, pChunk->Size, pMtrl );
			break;
		case 'TEXL': //------------------------------------ テクスチャ
			Load_TEXL( pData, pChunk->Size, pMtrl );
			break;
		case 'TEXE': //------------------------------------ テクスチャ
			Load_TEXE( pData, pChunk->Size, pMtrl );
			break;
		case 'TEXS': //------------------------------------ テクスチャ
			Load_TEXS( pData, pChunk->Size, pMtrl );
			break;
		case 'TEXN': //------------------------------------ テクスチャ
			Load_TEXN( pData, pChunk->Size, pMtrl );
			break;
		case 'LGT':  //------------------------------------ ライトON/OFF
			Load_LGT( pData, pChunk->Size, pMtrl );
			break;
		case 'DRAW': //------------------------------------ 描画モード
			Load_DRAW( pData, pChunk->Size, pMtrl );
			break;
		case 'ZTES': //------------------------------------ Zテスト
			Load_ZTES( pData, pChunk->Size, pMtrl );
			break;
		case 'ZWRI': //------------------------------------ Z書き込み
			Load_ZWRI( pData, pChunk->Size, pMtrl );
			break;
		case 'ATES': //------------------------------------ アルファテスト
			Load_ATES( pData, pChunk->Size, pMtrl );
			break;
		case 'ABND': //------------------------------------ アルファテスト
			Load_ABND( pData, pChunk->Size, pMtrl );
			break;
		case 'CULL': //------------------------------------ カリング
			Load_CULL( pData, pChunk->Size, pMtrl );
			break;
		case 'DIFF': //------------------------------------ 拡散反射
			Load_DIFF( pData, pChunk->Size, pMtrl );
			break;
		case 'EMIS': //------------------------------------ 自己発光
			Load_EMIS( pData, pChunk->Size, pMtrl );
			break;
		case 'SPEC': //------------------------------------ スペキュラ
			Load_SPEC( pData, pChunk->Size, pMtrl );
			break;
		case 'BUMP': //------------------------------------ バンプ
			Load_BUMP( pData, pChunk->Size, pMtrl );
			break;
		}

		// チャンクサイズ分進める
		pData += pChunk->Size;
		Pos += pChunk->Size;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_TEXC( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl )
{
	ITexture *pTex;
	pTex = m_pRender->CreateTextureFromMemory( pData, Size );
	pMtrl->SetTexture( TEXTURE_STAGE_COLOR, pTex );
	SAFE_RELEASE( pTex );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_TEXL( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl )
{
	ITexture *pTex;
	pTex = m_pRender->CreateTextureFromMemory( pData, Size );
	pMtrl->SetTexture( TEXTURE_STAGE_LIGHT, pTex );
	SAFE_RELEASE( pTex );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_TEXE( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl )
{
	ITexture *pTex;
	pTex = m_pRender->CreateCubeTextureFromMemory( pData, Size );
	pMtrl->SetTexture( TEXTURE_STAGE_ENVIRONMENT, pTex );
	SAFE_RELEASE( pTex );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_TEXS( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl )
{
	ITexture *pTex;
	pTex = m_pRender->CreateTextureFromMemory( pData, Size );
	pMtrl->SetTexture( TEXTURE_STAGE_SPECULAR, pTex );
	SAFE_RELEASE( pTex );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_TEXN( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl )
{
	ITexture *pTex;
	pTex = m_pRender->CreateTextureFromMemory( pData, Size );
	pMtrl->SetTexture( TEXTURE_STAGE_NORMAL, pTex );
	SAFE_RELEASE( pTex );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_LGT( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl )
{
	Sint32 IsLight;
	MemoryCopy( &IsLight, pData, sizeof(Sint32) );

	pMtrl->SetLightEnable( IsLight != 0 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_DRAW( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl )
{
	Sint32 DrawType;
	MemoryCopy( &DrawType, pData, sizeof(Sint32) );

	pMtrl->SetDrawType( (eDrawType)DrawType );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_ZTES( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl )
{
	Sint32 IsEnable;
	MemoryCopy( &IsEnable, pData, sizeof(Sint32) );

	pMtrl->SetDepthTestEnable( IsEnable != FALSE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_ZWRI( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl )
{
	Sint32 IsEnable;
	MemoryCopy( &IsEnable, pData, sizeof(Sint32) );

	pMtrl->SetDepthWriteEnable( IsEnable != FALSE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_ATES( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl )
{
	Sint32 IsEnable;
	MemoryCopy( &IsEnable, pData, sizeof(Sint32) );

	pMtrl->SetAlphaTestEnable( IsEnable != FALSE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_ABND( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl )
{
	Sint32 Bound;
	MemoryCopy( &Bound, pData, sizeof(Sint32) );

	pMtrl->SetAlphaBoundary( Bound );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_CULL( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl )
{
	Sint32 IsEnable;
	MemoryCopy( &IsEnable, pData, sizeof(Sint32) );

	pMtrl->SetCullType( IsEnable != FALSE ? CULL_FRONT : CULL_NONE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_DIFF( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl )
{
	STM_VECTOR4 vDiffuse;
	MemoryCopy( &vDiffuse, pData, sizeof(STM_VECTOR4) );

	Math::Vector4D vColor( vDiffuse.x, vDiffuse.y, vDiffuse.z, vDiffuse.w );
	pMtrl->SetDiffuseColor( vColor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_EMIS( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl )
{
	STM_VECTOR3 vEmissive;
	MemoryCopy( &vEmissive, pData, sizeof(STM_VECTOR3) );

	Math::Vector4D vColor( vEmissive.x, vEmissive.y, vEmissive.z, 0.0f );
	pMtrl->SetEmissiveColor( vColor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_SPEC( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl )
{
	STM_SPECULAR Spec;
	MemoryCopy( &Spec, pData, sizeof(STM_SPECULAR) );

	Math::Vector4D vColor( Spec.vSpecular.x, Spec.vSpecular.y, Spec.vSpecular.z, 0.0f );

	pMtrl->SetSpecularColor( vColor );
	pMtrl->SetSpecularRoughly( Spec.fRoughly );
	pMtrl->SetSpecularRefractive( Spec.fRefractive );
	pMtrl->SetSpecularType( SPECULAR_TYPE_ENABLE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_BUMP( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl )
{
	STM_BUMPMAP Bump;
	MemoryCopy( &Bump, pData, sizeof(STM_BUMPMAP) );

	pMtrl->SetParallaxDepth( Bump.fParallaxDepth );
	pMtrl->SetBumpmapMode( BUMP_TYPE_ENABLE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_FRM( const Uint8 *pData, Sint32 Size, Sint32 FrameNo )
{
	STM_FRAMEDATA Frame;
	MemoryCopy( &Frame, pData, sizeof(STM_FRAMEDATA) );

	CMapFrame *pFrame = m_pModel->GetFramePointer( FrameNo );

	// メッシュ
	if ( Frame.MeshNo != -1 )
	{
		pFrame->ConnectMesh( Frame.MeshNo );
		m_pModel->GetMeshPointer( Frame.MeshNo )->SetParentFrame( pFrame );
	}

	// フレーム
	for ( Sint32 x = 0; x < 2; x++ )
	{
		for ( Sint32 y = 0; y < 2; y++ )
		{
			for ( Sint32 z = 0; z < 2; z++ )
			{
				if ( Frame.FrameNo[x][y][z] != -1 )
				{
					CMapFrame *pChild = m_pModel->GetFramePointer( Frame.FrameNo[x][y][z] );
					pFrame->ConnectChildFrame( x, y, z, pChild );
				}
			}
		}
	}

	// バウンディング
	pFrame->SetBounding( (Math::Vector3D&)Frame.OBB.vMin, (Math::Vector3D&)Frame.OBB.vMax );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_MESH( const Uint8 *pData, Sint32 Size, Sint32 MeshNo )
{
	Sint32 RenderDataIndex = 0;

	STM_MESHDATA Mesh = *((STM_MESHDATA*)pData);
	pData += sizeof(STM_MESHDATA);

	CMapMesh *pMesh = m_pModel->GetMeshPointer( MeshNo );
	pMesh->CreateRenderTable( Mesh.RenderIdCount );

	//-----------------------------------------------------------
	// チャンク解析
	//-----------------------------------------------------------
	Sint32 Pos = sizeof(STM_MESHDATA);
	while ( Pos < Size )
	{
		const STM_CHUNK *pChunk = (const STM_CHUNK*)pData;
		pData += sizeof(STM_CHUNK);
		Pos += sizeof(STM_CHUNK);

		switch ( pChunk->Chunk )
		{
		case 'OBB':
			Load_OBB( pData, pChunk->Size, pMesh );
			break;
		case 'V_PC': //------------------------------------ 頂点：位置＋色
			Load_V_PC( pData, pChunk->Size, pMesh );
			break;
		case 'V_N':  //------------------------------------ 頂点：法線
			Load_V_N( pData, pChunk->Size, pMesh );
			break;
		case 'V_B':  //------------------------------------ 頂点：接線
			Load_V_B( pData, pChunk->Size, pMesh );
			break;
		case 'V_UV': //------------------------------------ 頂点：テクスチャUV
			Load_V_UV( pData, pChunk->Size, pMesh );
			break;
		case 'IDX2': //------------------------------------ インデックス
			Load_IDX2( pData, pChunk->Size, pMesh );
			break;
		case 'REND': //------------------------------------ レンダリングテーブル
			Load_REND( pData, pChunk->Size, pMesh, RenderDataIndex++ );
			break;
		}

		// チャンクサイズ分進める
		pData += pChunk->Size;
		Pos += pChunk->Size;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_OBB( const Uint8 *pData, Sint32 Size, CMapMesh *pMesh )
{
	STM_OBBDATA OBB = *((STM_OBBDATA*)pData);

	// バウンディング
	Math::Matrix Mtx;
	Mtx.Identity();
	Collision::CBox Box;
	Box.CreateBox( (Math::Vector3D&)OBB.vMin, (Math::Vector3D&)OBB.vMax, Mtx );

	pMesh->SetCenter( (Math::Vector3D&)OBB.vMax - (Math::Vector3D&)OBB.vMin );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_V_PC( const Uint8 *pData, Sint32 Size, CMapMesh *pMesh )
{
	Sint32 Count = Size / sizeof(SVertex3DBase);

	pMesh->CreateVertex( VERTEX_ELEMENT_3DBASE, Count );
	pMesh->LockVertex( VERTEX_ELEMENT_3DBASE );
	pMesh->Push( (const SVertex3DBase*)pData, Count );
	pMesh->UnLockVertex( VERTEX_ELEMENT_3DBASE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_V_N( const Uint8 *pData, Sint32 Size, CMapMesh *pMesh )
{
	Sint32 Count = Size / sizeof(SVertex3DLight);

	pMesh->CreateVertex( VERTEX_ELEMENT_3DLIGHT, Count );
	pMesh->LockVertex( VERTEX_ELEMENT_3DLIGHT );
	pMesh->Push( (const SVertex3DLight*)pData, Count );
	pMesh->UnLockVertex( VERTEX_ELEMENT_3DLIGHT );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_V_B( const Uint8 *pData, Sint32 Size, CMapMesh *pMesh )
{
	Sint32 Count = Size / sizeof(SVertex3DBump);

	pMesh->CreateVertex( VERTEX_ELEMENT_3DBUMP, Count );
	pMesh->LockVertex( VERTEX_ELEMENT_3DBUMP );
	pMesh->Push( (const SVertex3DBump*)pData, Count );
	pMesh->UnLockVertex( VERTEX_ELEMENT_3DBUMP );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_V_UV( const Uint8 *pData, Sint32 Size, CMapMesh *pMesh )
{
	Sint32 Count = Size / sizeof(SVertex3DTexture);

	pMesh->CreateVertex( VERTEX_ELEMENT_3DTEXTURE, Count );
	pMesh->LockVertex( VERTEX_ELEMENT_3DTEXTURE );
	pMesh->Push( (const SVertex3DTexture*)pData, Count );
	pMesh->UnLockVertex( VERTEX_ELEMENT_3DTEXTURE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_IDX2( const Uint8 *pData, Sint32 Size, CMapMesh *pMesh )
{
	Sint32 Count = Size / sizeof(Uint16);

	pMesh->CreateIndex( Count );
	pMesh->LockIndex();
	pMesh->Push( pData, Count );
	pMesh->UnLockIndex();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_REND( const Uint8 *pData, Sint32 Size, CMapMesh *pMesh, Sint32 RenderDataNo )
{
	STM_RENDERDATA RD = *((STM_RENDERDATA*)pData);

	SRenderTable Tbl;
	Tbl.MaterialId		= RD.MaterialId;
	Tbl.PolygonStart	= RD.PolygonStart;
	Tbl.PolygonCount		= RD.PolygonCount;
	Tbl.VertexStart		= RD.VertexStart;
	Tbl.VertexCount		= RD.VertexCount;

	pMesh->SetRenderTable( RenderDataNo, Tbl );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_CLSN( const Uint8 *pData, Sint32 Size )
{
	STM_COLLISIONHEAD *pColl = (STM_COLLISIONHEAD*)pData;

	m_pModel->Collision_CreateFrameList( pColl->FrameCount );
	m_pModel->Collision_CreateList( pColl->CollisionCount );
	m_pModel->Collision_SetFirstFrame( pColl->FirstFrame );

	m_pModel->Collision_SetAreaInfo(
		Math::Point3DI(pColl->CellCountX,pColl->CellCountY,pColl->CellCountZ),
		Math::Point3DF(pColl->fCellSizeX,pColl->fCellSizeY,pColl->fCellSizeZ) );

	Sint32 FrameIndex = 0;
	Sint32 CollisionIndex = 0;

	pData += sizeof(STM_COLLISIONHEAD);
	Sint32 Pos = sizeof(STM_COLLISIONHEAD);
	while ( Pos < Size )
	{
		STM_CHUNK *pChunk = (STM_CHUNK*)pData;
		pData += sizeof(STM_CHUNK);
		Pos += sizeof(STM_CHUNK);

		switch ( pChunk->Chunk )
		{
		case 'AREA':
			Load_CLSN_AREA( pData, pChunk->Size );
			break;
		case 'FRM':
			Load_CLSN_FRM( pData, pChunk->Size, FrameIndex++ );
			break;
		case 'DATA':
			Load_CLSN_DATA( pData, pChunk->Size, CollisionIndex++ );
			break;
		}

		// チャンクサイズ分進める
		pData += pChunk->Size;
		Pos += pChunk->Size;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_CLSN_AREA( const Uint8 *pData, Sint32 Size )
{
	m_pModel->Collision_SetAreaID( (Sint32*)pData );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_CLSN_FRM( const Uint8 *pData, Sint32 Size, Sint32 FrameNo )
{
	STM_FRAMEDATA Frame;
	MemoryCopy( &Frame, pData, sizeof(STM_FRAMEDATA) );

	CMapFrame *pFrame = m_pModel->Collision_GetFramePointer( FrameNo );

	// メッシュ
	if ( Frame.MeshNo != -1 )
	{
		pFrame->ConnectMesh( Frame.MeshNo );
	}

	// フレーム
	for ( Sint32 x = 0; x < 2; x++ )
	{
		for ( Sint32 y = 0; y < 2; y++ )
		{
			for ( Sint32 z = 0; z < 2; z++ )
			{
				if ( Frame.FrameNo[x][y][z] != -1 )
				{
					CMapFrame *pChild = m_pModel->Collision_GetFramePointer( Frame.FrameNo[x][y][z] );
					pFrame->ConnectChildFrame( x, y, z, pChild );
				}
			}
		}
	}

	// バウンディング
	pFrame->SetBounding( (Math::Vector3D&)Frame.OBB.vMin, (Math::Vector3D&)Frame.OBB.vMax );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_CLSN_DATA( const Uint8 *pData, Sint32 Size, Sint32 CollisionNo )
{
	CCollision *pCollision = m_pModel->Collision_GetPointer( CollisionNo );

	Sint32 Pos = 0;
	while ( Pos < Size )
	{
		STM_CHUNK *pChunk = (STM_CHUNK*)pData;
		pData += sizeof(STM_CHUNK);
		Pos += sizeof(STM_CHUNK);

		switch ( pChunk->Chunk )
		{
		case 'C_AT':
			Load_CLSN_DATA_C_AT( pData, pChunk->Size, pCollision );
			break;
		case 'C_FC':
			Load_CLSN_DATA_C_FC( pData, pChunk->Size, pCollision );
			break;
		case 'C_VX':
			Load_CLSN_DATA_C_VX( pData, pChunk->Size, pCollision );
			break;
		}

		// チャンクサイズ分進める
		pData += pChunk->Size;
		Pos += pChunk->Size;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_CLSN_DATA_C_AT( const Uint8 *pData, Sint32 Size, CCollision *pCollision )
{
	STM_COLLISION_ATTRIBUTE *pFace = (STM_COLLISION_ATTRIBUTE*)pData;
	Sint32 Count = Size / sizeof(STM_COLLISION_ATTRIBUTE);

	pCollision->CreateCollisionAttribute( (SCollisionAttribute*)pFace, Count );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_CLSN_DATA_C_FC( const Uint8 *pData, Sint32 Size, CCollision *pCollision )
{
	STM_COLLISION_FACE *pFace = (STM_COLLISION_FACE*)pData;
	Sint32 Count = Size / sizeof(STM_COLLISION_FACE);

	pCollision->CreateCollisionFace( (SCollisionFace*)pFace, Count );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapModelLoader::Load_CLSN_DATA_C_VX( const Uint8 *pData, Sint32 Size, CCollision *pCollision )
{
	STM_COLLISION_VERTEX *pFace = (STM_COLLISION_VERTEX*)pData;
	Sint32 Count = Size / sizeof(STM_COLLISION_VERTEX);

	pCollision->CreateCollisionVertex( (SCollisionVertex*)pFace, Count );
}
