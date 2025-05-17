


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CSceneInstanceModelControllerObject.h"
#include "Class/Common/Scene/CSceneInstanceModelActorObject.h"
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
CSceneInstanceModelActorObject::CSceneInstanceModelActorObject( CSceneManagerBase *pScene ) : CActorObject( pScene )
	, m_ControllerCount		( 0 )
	, m_ppControllerTbl		( NULL )
	, m_IsParallax			( false )
	, m_IsSpecular			( false )
	, m_IsEnvironment		( false )
	, m_pVB_BaseOrg			( NULL )
	, m_pVB_LightOrg		( NULL )
	, m_pVB_BumpOrg			( NULL )
	, m_pVB_AnimationOrg	( NULL )
	, m_InstanceCount		( 0 )
	, m_InstanceMaxCount	( 0 )
	, m_pInstanceMaterlaTbl	( NULL )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSceneInstanceModelActorObject::~CSceneInstanceModelActorObject()
{
	SAFE_DELETE_ARRAY( m_ppControllerTbl );

	Sint32 MaterialCount = GetMaterialCount();
	for ( Sint32 i = 0; i < MaterialCount; i++ )
	{
		SInstanceMaterial &Instance = m_pInstanceMaterlaTbl[i];
		SAFE_RELEASE( Instance.pVB_Base );
		SAFE_RELEASE( Instance.pVB_Light );
		SAFE_RELEASE( Instance.pVB_Bump );
		SAFE_RELEASE( Instance.pVB_Tex );
		SAFE_RELEASE( Instance.pIB );
	}
	SAFE_DELETE_ARRAY( m_pInstanceMaterlaTbl );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::BeginInstance( void )
{
	Sint32 MaterialCount = GetMaterialCount();
	for ( Sint32 i = 0; i < MaterialCount; i++ )
	{
		SInstanceMaterial &Instance = m_pInstanceMaterlaTbl[i];
		if ( Instance.pVB_Base	!= NULL ) Instance.pVB_Base->Lock();
		if ( Instance.pVB_Light	!= NULL ) Instance.pVB_Light->Lock();
		if ( Instance.pVB_Bump	!= NULL ) Instance.pVB_Bump->Lock();
		if ( Instance.pVB_Tex	!= NULL ) Instance.pVB_Tex->Lock();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::EndInstance( void )
{
	Sint32 MaterialCount = GetMaterialCount();
	for ( Sint32 i = 0; i < MaterialCount; i++ )
	{
		SInstanceMaterial &Instance = m_pInstanceMaterlaTbl[i];
		if ( Instance.pVB_Base	!= NULL ) Instance.pVB_Base->UnLock();
		if ( Instance.pVB_Light	!= NULL ) Instance.pVB_Light->UnLock();
		if ( Instance.pVB_Bump	!= NULL ) Instance.pVB_Bump->UnLock();
		if ( Instance.pVB_Tex	!= NULL ) Instance.pVB_Tex->UnLock();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::TransformB( const Math::Matrix &mWorld, Sint32 Position )
{
	Renderer::SVertex3DBase  *pSrcB = (Renderer::SVertex3DBase*)m_pVB_Base->GetBufferAddress( 0 );

	Sint32 MaterialCount = GetMaterialCount();
	for ( Sint32 i = 0; i < MaterialCount; i++ )
	{
		CSceneActorMaterial *pMaterial = (CSceneActorMaterial*)GetMaterialPointer( i );
		SInstanceMaterial &Instance = m_pInstanceMaterlaTbl[i];

		Sint32 VertexStart = pMaterial->GetVertexStart();
		Sint32 VertexCount = pMaterial->GetVertexCount();

		Renderer::SVertex3DBase  *pDstB = (Renderer::SVertex3DBase*)Instance.pVB_Base->GetBufferPointer( VertexCount );

		Sint32 Offset = 0;

		for ( Sint32 j = VertexStart; j < VertexStart + VertexCount; j++ )
		{
			pDstB[Offset].Pos.TransformCoord( pSrcB[j].Pos, mWorld );
			pDstB[Offset].Col = pSrcB[j].Col;
			Offset++;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::TransformBN( const Math::Matrix &mWorld, Sint32 Position )
{
	Renderer::SVertex3DBase  *pSrcB = (Renderer::SVertex3DBase*)m_pVB_Base->GetBufferAddress( 0 );
	Renderer::SVertex3DLight *pSrcN = (Renderer::SVertex3DLight*)m_pVB_Light->GetBufferAddress( 0 );

	Sint32 MaterialCount = GetMaterialCount();
	for ( Sint32 i = 0; i < MaterialCount; i++ )
	{
		CSceneActorMaterial *pMaterial = (CSceneActorMaterial*)GetMaterialPointer( i );
		SInstanceMaterial &Instance = m_pInstanceMaterlaTbl[i];

		Sint32 VertexStart = pMaterial->GetVertexStart();
		Sint32 VertexCount = pMaterial->GetVertexCount();

		Renderer::SVertex3DBase  *pDstB = (Renderer::SVertex3DBase*)Instance.pVB_Base->GetBufferPointer( VertexCount );
		Renderer::SVertex3DLight *pDstN = (Renderer::SVertex3DLight*)Instance.pVB_Light->GetBufferPointer( VertexCount );

		Sint32 Offset = 0;

		for ( Sint32 j = VertexStart; j < VertexStart + VertexCount; j++ )
		{
			pDstB[Offset].Pos.TransformCoord( pSrcB[j].Pos, mWorld );
			pDstB[Offset].Col = pSrcB[j].Col;
			pDstN[Offset].Norm.TransformNormal( pSrcN[j].Norm, mWorld );
			Offset++;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::TransformBNT( const Math::Matrix &mWorld, Sint32 Position )
{
	Renderer::SVertex3DBase  *pSrcB = (Renderer::SVertex3DBase*)m_pVB_Base->GetBufferAddress( 0 );
	Renderer::SVertex3DLight *pSrcN = (Renderer::SVertex3DLight*)m_pVB_Light->GetBufferAddress( 0 );
	Renderer::SVertex3DBump  *pSrcT = (Renderer::SVertex3DBump*)m_pVB_Bump->GetBufferAddress( 0 );

	Sint32 MaterialCount = GetMaterialCount();
	for ( Sint32 i = 0; i < MaterialCount; i++ )
	{
		CSceneActorMaterial *pMaterial = (CSceneActorMaterial*)GetMaterialPointer( i );
		SInstanceMaterial &Instance = m_pInstanceMaterlaTbl[i];

		Sint32 VertexStart = pMaterial->GetVertexStart();
		Sint32 VertexCount = pMaterial->GetVertexCount();

		Renderer::SVertex3DBase  *pDstB = (Renderer::SVertex3DBase*)Instance.pVB_Base->GetBufferPointer( VertexCount );
		Renderer::SVertex3DLight *pDstN = (Renderer::SVertex3DLight*)Instance.pVB_Light->GetBufferPointer( VertexCount );
		Renderer::SVertex3DBump  *pDstT = (Renderer::SVertex3DBump*)Instance.pVB_Bump->GetBufferPointer( VertexCount );

		Sint32 Offset = 0;

		for ( Sint32 j = VertexStart; j < VertexStart + VertexCount; j++ )
		{
			pDstB[Offset].Pos.TransformCoord( pSrcB[j].Pos, mWorld );
			pDstB[Offset].Col = pSrcB[j].Col;
			pDstN[Offset].Norm.TransformNormal( pSrcN[j].Norm, mWorld );
			pDstT[Offset].Tangent.TransformNormal( pSrcT[j].Tangent, mWorld );
			Offset++;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::TransformAB( const Math::SMatrix4x4 *pBoneMatrixTbl, Sint32 Position )
{
	Renderer::SVertex3DAnimation *pSrcBone = (Renderer::SVertex3DAnimation*)m_pVB_Animation->GetBufferAddress( 0 );

	Renderer::SVertex3DBase  *pSrcB = (Renderer::SVertex3DBase*)m_pVB_Base->GetBufferAddress( 0 );

	Sint32 MaterialCount = GetMaterialCount();
	for ( Sint32 i = 0; i < MaterialCount; i++ )
	{
		CSceneActorMaterial *pMaterial = (CSceneActorMaterial*)GetMaterialPointer( i );
		SInstanceMaterial &Instance = m_pInstanceMaterlaTbl[i];

		Sint32 VertexStart = pMaterial->GetVertexStart();
		Sint32 VertexCount = pMaterial->GetVertexCount();

		Renderer::SVertex3DBase  *pDstB = (Renderer::SVertex3DBase*)Instance.pVB_Base->GetBufferPointer( VertexCount );

		Sint32 Offset = 0;

		for ( Sint32 j = VertexStart; j < VertexStart + VertexCount; j++ )
		{
			if ( pSrcBone[j].Weight >= 0.5f )
			{
				const Math::SMatrix4x4 &mWorld = pBoneMatrixTbl[pSrcBone[j].Index[0]];
				pDstB[Offset].Pos.TransformCoord( pSrcB[j].Pos, mWorld );
			}
			else
			{
				const Math::SMatrix4x4 &mWorld = pBoneMatrixTbl[pSrcBone[j].Index[1]];
				pDstB[Offset].Pos.TransformCoord( pSrcB[j].Pos, mWorld );
			}
			Offset++;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::TransformABN( const Math::SMatrix4x4 *pBoneMatrixTbl, Sint32 Position )
{
	Renderer::SVertex3DAnimation *pSrcBone = (Renderer::SVertex3DAnimation*)m_pVB_Animation->GetBufferAddress( 0 );

	Renderer::SVertex3DBase  *pSrcB = (Renderer::SVertex3DBase*)m_pVB_Base->GetBufferAddress( 0 );
	Renderer::SVertex3DLight *pSrcN = (Renderer::SVertex3DLight*)m_pVB_Light->GetBufferAddress( 0 );

	Sint32 MaterialCount = GetMaterialCount();
	for ( Sint32 i = 0; i < MaterialCount; i++ )
	{
		CSceneActorMaterial *pMaterial = (CSceneActorMaterial*)GetMaterialPointer( i );
		SInstanceMaterial &Instance = m_pInstanceMaterlaTbl[i];

		Sint32 VertexStart = pMaterial->GetVertexStart();
		Sint32 VertexCount = pMaterial->GetVertexCount();

		Renderer::SVertex3DBase  *pDstB = (Renderer::SVertex3DBase*)Instance.pVB_Base->GetBufferPointer( VertexCount );
		Renderer::SVertex3DLight *pDstN = (Renderer::SVertex3DLight*)Instance.pVB_Light->GetBufferPointer( VertexCount );

		Sint32 Offset = 0;

		for ( Sint32 j = VertexStart; j < VertexStart + VertexCount; j++ )
		{
			if ( pSrcBone[j].Weight >= 0.5f )
			{
				const Math::SMatrix4x4 &mWorld = pBoneMatrixTbl[pSrcBone[j].Index[0]];
				pDstB[Offset].Pos.TransformCoord( pSrcB[j].Pos, mWorld );
				pDstN[Offset].Norm.TransformNormal( pSrcN[j].Norm, mWorld );
			}
			else
			{
				const Math::SMatrix4x4 &mWorld = pBoneMatrixTbl[pSrcBone[j].Index[1]];
				pDstB[Offset].Pos.TransformCoord( pSrcB[j].Pos, mWorld );
				pDstN[Offset].Norm.TransformNormal( pSrcN[j].Norm, mWorld );
			}
			Offset++;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::TransformABNT( const Math::SMatrix4x4 *pBoneMatrixTbl, Sint32 Position )
{
	Renderer::SVertex3DAnimation *pSrcBone = (Renderer::SVertex3DAnimation*)m_pVB_Animation->GetBufferAddress( 0 );

	Renderer::SVertex3DBase  *pSrcB = (Renderer::SVertex3DBase*)m_pVB_Base->GetBufferAddress( 0 );
	Renderer::SVertex3DLight *pSrcN = (Renderer::SVertex3DLight*)m_pVB_Light->GetBufferAddress( 0 );
	Renderer::SVertex3DBump  *pSrcT = (Renderer::SVertex3DBump*)m_pVB_Bump->GetBufferAddress( 0 );

	Sint32 MaterialCount = GetMaterialCount();
	for ( Sint32 i = 0; i < MaterialCount; i++ )
	{
		CSceneActorMaterial *pMaterial = (CSceneActorMaterial*)GetMaterialPointer( i );
		SInstanceMaterial &Instance = m_pInstanceMaterlaTbl[i];

		Sint32 VertexStart = pMaterial->GetVertexStart();
		Sint32 VertexCount = pMaterial->GetVertexCount();

		Renderer::SVertex3DBase  *pDstB = (Renderer::SVertex3DBase*)Instance.pVB_Base->GetBufferPointer( VertexCount );
		Renderer::SVertex3DLight *pDstN = (Renderer::SVertex3DLight*)Instance.pVB_Light->GetBufferPointer( VertexCount );
		Renderer::SVertex3DBump  *pDstT = (Renderer::SVertex3DBump*)Instance.pVB_Bump->GetBufferPointer( VertexCount );

		Sint32 Offset = 0;

		for ( Sint32 j = VertexStart; j < VertexStart + VertexCount; j++ )
		{
			if ( pSrcBone[j].Weight >= 0.5f )
			{
				const Math::SMatrix4x4 &mWorld = pBoneMatrixTbl[pSrcBone[j].Index[0]];
				pDstB[Offset].Pos.TransformCoord( pSrcB[j].Pos, mWorld );
				pDstN[Offset].Norm.TransformNormal( pSrcN[j].Norm, mWorld );
				pDstT[Offset].Tangent.TransformNormal( pSrcT[j].Tangent, mWorld );
			}
			else
			{
				const Math::SMatrix4x4 &mWorld = pBoneMatrixTbl[pSrcBone[j].Index[1]];
				pDstB[Offset].Pos.TransformCoord( pSrcB[j].Pos, mWorld );
				pDstN[Offset].Norm.TransformNormal( pSrcN[j].Norm, mWorld );
				pDstT[Offset].Tangent.TransformNormal( pSrcT[j].Tangent, mWorld );
			}
			Offset++;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::UpdateInsntaceVertex( Sint32 Index, Sint32 Position )
{
	CInstanceModelControllerObject *pObject = GetControllerObject( Index );

	//----------------------------------------------------------------------
	// ボーンなし
	//----------------------------------------------------------------------
	if ( pObject->GetBoneCount() == 0 )
	{
		if ( m_pVB_Light != NULL )
		{
			if ( m_pVB_Bump != NULL )
			{
				TransformBNT( pObject->GetWorldMatrix(), Position );
			}
			else
			{
				TransformBN( pObject->GetWorldMatrix(), Position );
			}
		}
		else
		{
			TransformB( pObject->GetWorldMatrix(), Position );
		}
	}
	//----------------------------------------------------------------------
	// ボーンあり
	//----------------------------------------------------------------------
	else
	{
		if ( m_pVB_Light != NULL )
		{
			if ( m_pVB_Bump != NULL )
			{
				TransformABNT( pObject->GetBoneMatrixArray(), Position );
			}
			else
			{
				TransformABN( pObject->GetBoneMatrixArray(), Position );
			}
		}
		else
		{
			TransformAB( pObject->GetBoneMatrixArray(), Position );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CSceneInstanceModelActorObject::GetControllerCount( void )
{
	return m_ControllerCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CInstanceModelControllerObject *CSceneInstanceModelActorObject::GetControllerObject( Sint32 Index )
{
	return m_ppControllerTbl[Index];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::SetControllerCount( Sint32 Count )
{
	m_ppControllerTbl = new CInstanceModelControllerObject * [ Count ];
	m_ControllerCount = Count;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::SetControllerObject( Sint32 Index, CInstanceModelControllerObject *pController )
{
	m_ppControllerTbl[Index] = pController;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::Update( void )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::SetStreamSource( Renderer::CRender *pRender )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CSceneInstanceModelActorObject::Rendering( Sint32 MaterialNo, Renderer::CRender *pRender )
{
	CSceneActorMaterial &Mtrl = m_pMaterial[MaterialNo];
	SInstanceMaterial &Instance = m_pInstanceMaterlaTbl[MaterialNo];

	pRender->SetVertexStream( m_pVS );
	pRender->SetIndexBuffer( Instance.pIB );

	Renderer::CVertexBuffer *pBufferTbl[] = {
		Instance.pVB_Base,
		Instance.pVB_Tex,
		Instance.pVB_Light,
		Instance.pVB_Bump,
		NULL,
	};
	pRender->SetVertexBuffer( pBufferTbl, 5 );

	Sint32 VertexStart		= 0;
	Sint32 VertexCount		= Mtrl.GetVertexCount()    * m_InstanceCount;
	Sint32 IndexStart		= 0;
	Sint32 PrimitiveCount	= Mtrl.GetIndexCount() / 3 * m_InstanceCount;

	// レンダリング
	pRender->DrawMesh( VertexStart, VertexCount, IndexStart, PrimitiveCount );

	return PrimitiveCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CSceneInstanceModelActorObject::Rendering_Velocity( Renderer::CRender *pRender )
{
	return 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneInstanceModelActorObject::IsAlphaEnable( void )
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
void CSceneInstanceModelActorObject::SetParallaxEnable( Bool IsEnable )
{
	m_IsParallax = IsEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::SetSpecularEnable( Bool IsEnable )
{
	m_IsSpecular = IsEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::SetEnvironmentEnable( Bool IsEnable )
{
	m_IsEnvironment = IsEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::CreateMaterialVertex( Sint32 Count )
{
	m_pInstanceMaterlaTbl = new SInstanceMaterial[ Count ];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::SetMaterialData( Sint32 Index, Renderer::CVertexBuffer *pVB_Base, Renderer::CVertexBuffer *pVB_Light, Renderer::CVertexBuffer *pVB_Bump, Renderer::CVertexBuffer *pVB_Tex, Renderer::CIndexBuffer *pIB )
{
	SInstanceMaterial &Instance = m_pInstanceMaterlaTbl[Index];
	Instance.pVB_Base	= pVB_Base;
	Instance.pVB_Light	= pVB_Light;
	Instance.pVB_Bump	= pVB_Bump;
	Instance.pVB_Tex	= pVB_Tex;
	Instance.pIB		= pIB;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::SetInstanceMaxCount( Sint32 InstanceCount )
{
	m_InstanceMaxCount = InstanceCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneInstanceModelActorObject::SetRenderInstanceCount( Sint32 InstanceCount )
{
	m_InstanceCount = InstanceCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CSceneInstanceModelActorObject::GetRenderInstanceCount( void )
{
	return m_InstanceCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneInstanceModelActorObject::IsInstanceModel( void )
{
	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneInstanceModelActorObject::GetSoftBillboardEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneInstanceModelActorObject::GetCullTestEnable( void )
{
	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneInstanceModelActorObject::GetParallaxEnable( void )
{
	return m_IsParallax;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneInstanceModelActorObject::GetSpecularEnable( void )
{
	return m_IsSpecular;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneInstanceModelActorObject::GetEnvironmentEnable( void )
{
	return m_IsEnvironment;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
eTransformType CSceneInstanceModelActorObject::GetTransformType( void )
{
	return TRANSFORM_TYPE_MODEL;
}

