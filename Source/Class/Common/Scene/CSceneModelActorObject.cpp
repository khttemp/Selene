

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CSceneModelActorObject.h"
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
CModelActorObject::CModelActorObject( CSceneManagerBase *pScene ) : CActorObject( pScene )
	, m_BoneCount		( 0 )
	, m_IsCullTest		( true )
	, m_IsParallax		( false )
	, m_IsSpecular		( false )
	, m_IsEnvironment	( false )
	, m_IsDrawEnable	( true )
	, m_pParentFrame	( NULL )
	, m_pMesh			( NULL )
{
	for ( Sint32 i = 0; i < MAX_BONE_COUNT; i++ )
	{
		m_ppBoneFramePointer[i] = NULL;
		m_mBone[0][i] = m_mWorld[0];
		m_mBone[1][i] = m_mWorld[1];
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
CModelActorObject::~CModelActorObject()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActorObject::Update( void )
{
	Sint32 BoneCnt = m_BoneCount;

	// �ϊ��s��
	if ( BoneCnt == 0 )
	{
		Math::Matrix &mWorld = m_mWorld[m_Page];
		Math::Matrix &mWorldInverse = m_mWorldInverse[m_Page];

		m_pParentFrame->GetTransform( mWorld );
		m_pParentFrame->GetTransformInverse( mWorldInverse );

		m_vCenter.TransformCoord( m_vCenterBase, mWorld );

		m_CullBox.Transform( m_vCullBoxPoints, mWorld );
	}
	else
	{
		Math::Matrix mWorld;
		m_pParentFrame->GetTransform( mWorld );
		m_vCenter.TransformCoord( m_vCenterBase, mWorld );
		m_CullBox.Transform( m_vCullBoxPoints, mWorld );

		// �{�[���s��
		Math::SMatrix4x4 *pMtx = m_mBone[m_Page];
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
void CModelActorObject::SetStreamSource( Renderer::CRender *pRender )
{
	pRender->SetVertexStream( m_pVS );
	pRender->SetIndexBuffer( m_pIB );

	Renderer::CVertexBuffer *pBufferTbl[] = {
		m_pVB_Base,
		m_pVB_Tex,
		m_pVB_Light,
		m_pVB_Bump,
		m_pVB_Animation,
	};
	pRender->SetVertexBuffer( pBufferTbl, 5 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CModelActorObject::Rendering( Sint32 MaterialNo, Renderer::CRender *pRender )
{
	CSceneActorMaterial &Mtrl = m_pMaterial[MaterialNo];

	Sint32 VertexStart		= Mtrl.GetVertexStart();
	Sint32 VertexCount		= Mtrl.GetVertexCount();
	Sint32 IndexStart		= Mtrl.GetIndexStart();
	Sint32 PrimitiveCount	= Mtrl.GetIndexCount() / 3;

	// �����_�����O
	pRender->DrawMesh( VertexStart, VertexCount, IndexStart, PrimitiveCount );

	return PrimitiveCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CModelActorObject::Rendering_Velocity( Renderer::CRender *pRender )
{
	Sint32 VertexStart		= 0;
	Sint32 VertexCount		= m_pVB_Base->GetCount();
	Sint32 IndexStart		= 0;
	Sint32 PrimitiveCount	= m_pIB->GetCount() / 3;

	// �����_�����O
	pRender->DrawMesh( VertexStart, VertexCount, IndexStart, PrimitiveCount );

	return PrimitiveCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActorObject::SetMeshPointer( Renderer::Object::CMesh *pMesh )
{
	m_pMesh = pMesh;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActorObject::SetParentFrame( Renderer::Object::CFrame *pParentFrame )
{
	m_pParentFrame = pParentFrame;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActorObject::SetBoneCount( Sint32 Count, Renderer::Object::CFrame *pFrameTbl[] )
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
Bool CModelActorObject::IsAlphaEnable( void )
{
	Sint32 MtrlCnt = m_MaterialCount;
	for ( Sint32 i = 0; i < MtrlCnt; i++ )
	{
		if ( m_pMaterial[i].GetDrawType() != DRAW_TYPE_NORMAL )
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
void CModelActorObject::SetCullTestEnable( Bool IsEnable )
{
	m_IsCullTest = IsEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActorObject::SetParallaxEnable( Bool IsEnable )
{
	m_IsParallax = IsEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActorObject::SetSpecularEnable( Bool IsEnable )
{
	m_IsSpecular = IsEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActorObject::SetEnvironmentEnable( Bool IsEnable )
{
	m_IsEnvironment = IsEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActorObject::SetCullBoxPoints( const Math::Vector3D *pPts )
{
	MemoryCopy( m_vCullBoxPoints, pPts, sizeof(Math::Vector3D[8]) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActorObject::RenderingBounding( Renderer::Object::ILine3D *pLine )
{
	pLine->PushBox( m_CullBox, 0xFFFFCCCC );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CModelActorObject::GetBoneCount( void )
{
	return m_BoneCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::SMatrix4x4 *CModelActorObject::GetBoneMatrixArray( void )
{
	return m_mBone[m_Page];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Math::SMatrix4x4 *CModelActorObject::GetBoneMatrixArrayPrev( void )
{
	return m_mBone[1-m_Page];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
const Collision::CBox &CModelActorObject::GetCullBox( void )
{
	return m_CullBox;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModelActorObject::GetSoftBillboardEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModelActorObject::GetCullTestEnable( void )
{
	return m_IsCullTest;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModelActorObject::GetParallaxEnable( void )
{
	return m_IsParallax;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModelActorObject::GetSpecularEnable( void )
{
	return m_IsSpecular;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModelActorObject::GetEnvironmentEnable( void )
{
	return m_IsEnvironment;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActorObject::SetDrawEnable( Bool IsDrawEnable )
{
	m_IsDrawEnable = IsDrawEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModelActorObject::GetDrawEnable( void )
{
	return m_IsDrawEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eTransformType CModelActorObject::GetTransformType( void )
{
	return TRANSFORM_TYPE_MODEL;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModelActorObject::HitCheckByRay( const Collision::CLine3D &Ray )
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
Bool CModelActorObject::HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box )
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
Bool CModelActorObject::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out )
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
Bool CModelActorObject::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out, Collision::CBox &Box )
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
Bool CModelActorObject::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out )
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
Bool CModelActorObject::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out, Collision::CBox &Box )
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
void CModelActorObject::CreateCollisionDrawPrimitive( Renderer::Object::ILine3D *pLine )
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
