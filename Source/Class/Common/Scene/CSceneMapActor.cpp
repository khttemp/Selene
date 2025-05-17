

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CSceneMapActor.h"
#include "Class/Common/Render/Map/CMapModel.h"
#include "Class/Common/Render/Map/CMapMesh.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapActor::CMapActor( CSceneManagerBase *pSceneMgr, Renderer::Object::IMapModel *pObject, Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr ) : Renderer::CRenderObject( pRender, pMgr )
	, m_pModel				( NULL )
	, m_ObjectCount			( 0 )
	, m_pObjectTbl			( NULL )
{
	m_pModel = (Renderer::Object::CMapModel*)pObject;
	m_pModel->AddRef();

	// 子に連結
	pSceneMgr->AddChild( this );

	Sint32 Max;

	// オブジェクト
	m_ObjectCount = m_pModel->GetMeshCount();
	m_pObjectTbl = new CMapActorObject * [ m_ObjectCount ];
	Max = m_ObjectCount;
	for ( Sint32 i = 0; i < m_ObjectCount; i++ )
	{
		m_pObjectTbl[i] = new CMapActorObject( pSceneMgr );
		m_pModel->GetMeshPointer( i )->CreateRenderActor( m_pObjectTbl[i] );
	}

	// カスタムじゃないシェーダーの時はシェーダーの検索
	if ( pSceneMgr->GetShaderVersion() != SHADER_MODEL_CUSTOM )
	{
		// シェーダーを取得
		eSceneShadingType			ShadingType		= pSceneMgr->GetShadingType();
		eSceneFogType				FogType			= pSceneMgr->GetFogType();
		eSceneHighDynamicRangeType	HdrType			= pSceneMgr->GetHdrType();
		eSceneShadowType			ShadowType		= pSceneMgr->GetShadowType();
		eShaderVersion				ShaderVersion	= pSceneMgr->GetShaderVersion();
		eHardwareShadowType			HwShadowType	= pSceneMgr->GetHardwareShadowType();
		Bool						IsSoftShadow	= pSceneMgr->IsSoftShadowEnable();

		Max = m_ObjectCount;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			// マテリアルごとに設定
			Sint32 MtrlCnt = m_pObjectTbl[i]->GetMaterialCount();
			for ( Sint32 j = 0; j < MtrlCnt; j++ )
			{
				CSceneActorMaterial &Mtrl = m_pObjectTbl[i]->GetSceneRenderMaterial( j );

				// シェーダー用パラメーター
				Plugin::Shader::SModelParameter Param;

				Bool IsTangentEnable = m_pObjectTbl[i]->IsSupportVertexBump();

				Param.IsBoneEnable		= m_pObjectTbl[i]->IsSupportVertexBone()    != false;
				Param.IsNormalEnable	= m_pObjectTbl[i]->IsSupportVertexNormal()  != false;
				Param.IsTextureEnable	= m_pObjectTbl[i]->IsSupportVertexTexture() != false;

				Param.IsBumpMap			= Mtrl.GetBumpType() == BUMP_TYPE_ENABLE;
				Param.IsSpecularMap		= Mtrl.GetSpecularType() == SPECULAR_TYPE_ENABLE;
				Param.IsLightMap		= Mtrl.GetTexture( TEXTURE_STAGE_LIGHT ) != NULL;
				Param.IsEnvironmentMap	= Mtrl.GetTexture( TEXTURE_STAGE_ENVIRONMENT ) != NULL;

				if ( !Mtrl.GetLightEnable() ) Param.IsNormalEnable = false;
				if ( !IsTangentEnable       ) Param.IsBumpMap = false;
				if ( !Param.IsTextureEnable ) Param.IsBumpMap = false;
				if ( !Param.IsNormalEnable  ) Param.IsBumpMap = false;
				if ( !Param.IsTextureEnable ) Param.IsLightMap = false;
				if ( !Param.IsNormalEnable  ) Param.IsSpecularMap = false;
				if ( !Param.IsNormalEnable  ) Param.IsEnvironmentMap = false;

				Renderer::Shader::IShader *pShader = Renderer::Shader::ShaderManager::GetShader(
																	ShaderVersion,
																	Param,
																	ShadingType,
																	FogType,
																	HdrType,
																	ShadowType,
																	HwShadowType,
																	IsSoftShadow );
				Mtrl.SetShader( pShader );
				SAFE_RELEASE( pShader );
			}
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CMapActor::~CMapActor()
{
	for ( Sint32 i = 0; i < m_ObjectCount; i++ )
	{
		SAFE_DELETE( m_pObjectTbl[i] );
	}
	SAFE_DELETE_ARRAY( m_pObjectTbl );

	SAFE_RELEASE( m_pModel );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapActor::RenderingRequest( void )
{
	CSceneManagerBase *pScene = (CSceneManagerBase*)GetParent();

	// ビューフラスタム更新
	m_pModel->UpdateFrustumCulling( pScene );

	// レンダリングキューに追加
	Sint32 Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		// カリング結果
		if ( m_pModel->GetMeshDrawEnable( i ) )
		{
			pScene->AddObject( m_pObjectTbl[i] );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapActor::RenderingBounding( Renderer::Object::ILine3D *pLine )
{
	m_pModel->RenderingBounding( pLine );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CMapActor::GetCellCount( void )
{
	return m_ObjectCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CMapActor::GetRenderingCellCount( void )
{
	Sint32 Count = 0;

	Sint32 Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		// カリング結果
		if ( m_pModel->GetMeshDrawEnable( i ) )
		{
			Count++;
		}
	}

	return Count;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapActor::HitCheckByRay( const Collision::CLine3D &Ray )
{
	return m_pModel->HitCheckByRay( Ray );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapActor::HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box )
{
	return m_pModel->HitCheckByRay( Ray, Box );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapActor::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out )
{
	return m_pModel->HitCheckByRay( Ray, Out );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapActor::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out, Collision::CBox &Box )
{
	return m_pModel->HitCheckByRay( Ray, Out, Box );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapActor::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out )
{
	return m_pModel->HitCheckByRay( Ray, Out );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapActor::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out, Collision::CBox &Box )
{
	return m_pModel->HitCheckByRay( Ray, Out, Box );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapActor::HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius )
{
	return m_pModel->HitCheckBySphere( Ray, fRadius );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapActor::HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Collision::CBox &Box )
{
	return m_pModel->HitCheckBySphere( Ray, fRadius, Box );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapActor::HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphere &Out )
{
	return m_pModel->HitCheckBySphere( Ray, fRadius, Out );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapActor::HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphere &Out, Collision::CBox &Box )
{
	return m_pModel->HitCheckBySphere( Ray, fRadius, Out, Box );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapActor::HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphereExtend &Out )
{
	return m_pModel->HitCheckBySphere( Ray, fRadius, Out );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CMapActor::HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphereExtend &Out, Collision::CBox &Box )
{
	return m_pModel->HitCheckBySphere( Ray, fRadius, Out, Box );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CMapActor::CreateCollisionDrawPrimitive( Renderer::Object::ILine3D *pLine )
{
	m_pModel->CreateCollisionDrawPrimitive( pLine );
}

