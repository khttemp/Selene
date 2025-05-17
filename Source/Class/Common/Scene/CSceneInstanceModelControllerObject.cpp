

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CSceneInstanceModelControllerObject.h"
#include "Class/Platform/Render/CVertexLayout.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Class/Common/Render/Model/CFrame.h"
#include "Class/Common/Render/Model/CMesh.h"
#include "Class/Common/Render/3D/CLinePrimitive3D.h"
#include "Collision/Collision.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CInstanceModelControllerObject::CInstanceModelControllerObject()
	: m_BoneCount		( 0 )
	, m_IsCullTest		( true )
	, m_IsDrawEnable	( false )
	, m_pParentFrame	( NULL )
	, m_pMesh			( NULL )
{
	m_mWorld.Identity();
	for ( Sint32 i = 0; i < MAX_BONE_COUNT; i++ )
	{
		m_ppBoneFramePointer[i] = NULL;
		m_mBone[i] = m_mWorld;
	}

	m_vCullBoxPoints[0].Set( -0.01f, -0.01f, -0.01f );
	m_vCullBoxPoints[1].Set( -0.01f, +0.01f, -0.01f );
	m_vCullBoxPoints[2].Set( -0.01f, +0.01f, +0.01f );
	m_vCullBoxPoints[3].Set( -0.01f, -0.01f, +0.01f );
	m_vCullBoxPoints[4].Set( +0.01f, -0.01f, -0.01f );
	m_vCullBoxPoints[5].Set( +0.01f, +0.01f, -0.01f );
	m_vCullBoxPoints[6].Set( +0.01f, +0.01f, +0.01f );
	m_vCullBoxPoints[7].Set( +0.01f, -0.01f, +0.01f );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CInstanceModelControllerObject::~CInstanceModelControllerObject()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CInstanceModelControllerObject::GetWorldMatrix( void )
{
	return m_mWorld;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::Matrix &CInstanceModelControllerObject::GetWorldInverseMatrix( void )
{
	return m_mWorldInverse;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInstanceModelControllerObject::GetDrawEnable( void )
{
	return m_IsDrawEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelControllerObject::SetDrawEnable( Bool IsEnable )
{
	m_IsDrawEnable = IsEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelControllerObject::Update( void )
{
	Sint32 BoneCnt = m_BoneCount;

	// 変換行列
	if ( BoneCnt == 0 )
	{
		Math::Matrix &mWorld = m_mWorld;

		m_pParentFrame->GetTransform( mWorld );
		m_pParentFrame->GetTransformInverse( m_mWorldInverse );

		m_CullBox.Transform( m_vCullBoxPoints, mWorld );
	}
	else
	{
		Math::Matrix mWorld;
		m_pParentFrame->GetTransform( mWorld );
		m_pParentFrame->GetTransformInverse( m_mWorldInverse );

		m_CullBox.Transform( m_vCullBoxPoints, mWorld );

		// ボーン行列
		Math::SMatrix4x4 *pMtx = m_mBone;
		for ( Sint32 i = 0; i < BoneCnt; i++ )
		{
			MemoryCopy(
				&pMtx[i],
				&m_ppBoneFramePointer[i]->GetMatrixTransform(),
				sizeof(Math::SMatrix4x4) );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelControllerObject::SetMeshPointer( Renderer::Object::CMesh *pMesh )
{
	m_pMesh = pMesh;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelControllerObject::SetParentFrame( Renderer::Object::CFrame *pParentFrame )
{
	m_pParentFrame = pParentFrame;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelControllerObject::SetBoneCount( Sint32 Count, Renderer::Object::CFrame *pFrameTbl[] )
{
	m_BoneCount = Count;
	for ( Sint32 i = 0; i < Count; i++ )
	{
		m_ppBoneFramePointer[i] = pFrameTbl[i];
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelControllerObject::SetCullTestEnable( Bool IsEnable )
{
	m_IsCullTest = IsEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelControllerObject::SetCullBoxPoints( const Math::Vector3D *pPts )
{
	MemoryCopy( m_vCullBoxPoints, pPts, sizeof(Math::Vector3D[8]) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelControllerObject::RenderingBounding( Renderer::Object::ILine3D *pLine )
{
	pLine->PushBox( m_CullBox, 0xFFFFCCCC );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CInstanceModelControllerObject::GetBoneCount( void )
{
	return m_BoneCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::SMatrix4x4 *CInstanceModelControllerObject::GetBoneMatrixArray( void )
{
	return m_mBone;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Collision::CBox &CInstanceModelControllerObject::GetCullBox( void )
{
	return m_CullBox;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInstanceModelControllerObject::GetCullTestEnable( void )
{
	return m_IsCullTest;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInstanceModelControllerObject::HitCheckByRay( const Collision::CLine3D &Ray )
{
	if ( Collision::Line_Box_3D( Ray, m_CullBox ) )
	{
		const Math::Matrix &mInverse = GetWorldInverseMatrix();

		Collision::CLine3D vRay = Ray;
		vRay.vStart.TransformCoord( mInverse );
		vRay.vEnd.TransformCoord( mInverse );

		if ( m_pMesh->HitCheckByRay( vRay ) )
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
Bool CInstanceModelControllerObject::HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box )
{
	if ( Collision::Line_Box_3D( Ray, m_CullBox ) )
	{
		const Math::Matrix &mInverse = GetWorldInverseMatrix();

		Collision::CLine3D vRay = Ray;
		vRay.vStart.TransformCoord( mInverse );
		vRay.vEnd.TransformCoord( mInverse );

		if ( m_pMesh->HitCheckByRay( vRay, Box ) )
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
Bool CInstanceModelControllerObject::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out )
{
	if ( Collision::Line_Box_3D( Ray, m_CullBox ) )
	{
		const Math::Matrix &mInverse = GetWorldInverseMatrix();

		Collision::CLine3D vRay = Ray;
		vRay.vStart.TransformCoord( mInverse );
		vRay.vEnd.TransformCoord( mInverse );

		if ( m_pMesh->HitCheckByRay( vRay, Out ) )
		{
			const Math::Matrix &mWorld = GetWorldMatrix();

			Out.vHitPosition.TransformCoord( mWorld );
			Out.vNormal.TransformNormal( mWorld );
			Out.vTriangle[0].TransformCoord( mWorld );
			Out.vTriangle[1].TransformCoord( mWorld );
			Out.vTriangle[2].TransformCoord( mWorld );

			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInstanceModelControllerObject::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out, Collision::CBox &Box )
{
	if ( Collision::Line_Box_3D( Ray, m_CullBox ) )
	{
		const Math::Matrix &mInverse = GetWorldInverseMatrix();

		Collision::CLine3D vRay = Ray;
		vRay.vStart.TransformCoord( mInverse );
		vRay.vEnd.TransformCoord( mInverse );

		if ( m_pMesh->HitCheckByRay( vRay, Out ) )
		{
			const Math::Matrix &mWorld = GetWorldMatrix();

			Box = m_CullBox;
			Out.vHitPosition.TransformCoord( mWorld );
			Out.vNormal.TransformNormal( mWorld );
			Out.vTriangle[0].TransformCoord( mWorld );
			Out.vTriangle[1].TransformCoord( mWorld );
			Out.vTriangle[2].TransformCoord( mWorld );

			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInstanceModelControllerObject::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out )
{
	if ( Collision::Line_Box_3D( Ray, m_CullBox ) )
	{
		const Math::Matrix &mInverse = GetWorldInverseMatrix();

		Collision::CLine3D vRay = Ray;
		vRay.vStart.TransformCoord( mInverse );
		vRay.vEnd.TransformCoord( mInverse );

		if ( m_pMesh->HitCheckByRay( vRay, Out ) )
		{
			const Math::Matrix &mWorld = GetWorldMatrix();

			Out.vHitPosition.TransformCoord( mWorld );
			Out.vNormal.TransformNormal( mWorld );
			Out.vRefrectPosition.TransformCoord( mWorld );
			Out.vRefrectDirection.TransformNormal( mWorld );
			Out.vSlidePosition.TransformCoord( mWorld );
			Out.vTriangle[0].TransformCoord( mWorld );
			Out.vTriangle[1].TransformCoord( mWorld );
			Out.vTriangle[2].TransformCoord( mWorld );

			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CInstanceModelControllerObject::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out, Collision::CBox &Box )
{
	if ( Collision::Line_Box_3D( Ray, m_CullBox ) )
	{
		const Math::Matrix &mInverse = GetWorldInverseMatrix();

		Collision::CLine3D vRay = Ray;
		vRay.vStart.TransformCoord( mInverse );
		vRay.vEnd.TransformCoord( mInverse );

		if ( m_pMesh->HitCheckByRay( vRay, Out ) )
		{
			const Math::Matrix &mWorld = GetWorldMatrix();

			Box = m_CullBox;
			Out.vHitPosition.TransformCoord( mWorld );
			Out.vNormal.TransformNormal( mWorld );
			Out.vRefrectPosition.TransformCoord( mWorld );
			Out.vRefrectDirection.TransformNormal( mWorld );
			Out.vSlidePosition.TransformCoord( mWorld );
			Out.vTriangle[0].TransformCoord( mWorld );
			Out.vTriangle[1].TransformCoord( mWorld );
			Out.vTriangle[2].TransformCoord( mWorld );

			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelControllerObject::CreateCollisionDrawPrimitive( Renderer::Object::ILine3D *pLine )
{
	Renderer::CCollision *pCollision = m_pMesh->GetCollision();
	if ( pCollision != NULL )
	{
		const Math::Matrix &mWorld = GetWorldMatrix();

		Sint32 FaceCnt = pCollision->GetPolygonCount();
		for ( Sint32 i = 0; i < FaceCnt; i++ )
		{
			Renderer::SCollisionFace &Face = pCollision->GetFace( i );

			Renderer::SCollisionVertex Vtx0 = pCollision->GetVertex( Face.Index[0] );
			Renderer::SCollisionVertex Vtx1 = pCollision->GetVertex( Face.Index[1] );
			Renderer::SCollisionVertex Vtx2 = pCollision->GetVertex( Face.Index[2] );

			Vtx0.Position.TransformCoord( mWorld );
			Vtx1.Position.TransformCoord( mWorld );
			Vtx2.Position.TransformCoord( mWorld );

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
