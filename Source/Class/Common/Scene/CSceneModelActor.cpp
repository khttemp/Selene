

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CSceneModelActor.h"
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
CModelActor::CModelActor( CSceneManagerBase *pSceneMgr, Renderer::Object::IModel *pObject, Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr ) : Renderer::CRenderObject( pRender, pMgr )
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
	m_pObjectTbl = new CModelActorObject * [ m_ObjectCount ];
	Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pObjectTbl[i] = new CModelActorObject( pSceneMgr );
		m_pModel->GetMesh( i )->CreateRenderActor( m_pObjectTbl[i] );
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
				Bool IsTangentEnable = m_pObjectTbl[i]->IsSupportVertexBump();

				Plugin::Shader::SModelParameter Param;
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
CModelActor::~CModelActor()
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
Sint32 CModelActor::GetAnimationCount( void )
{
	return m_AnimationCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CModelActor::GetAnimationLastTime( Sint32 AnimationNo )
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
void CModelActor::TransformReset( void )
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
void CModelActor::TransformUpdate( void )
{
	TransformUpdateCollisionOnly();
	TransformUpdateActorOnly();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActor::TransformUpdateCollisionOnly( void )
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
void CModelActor::TransformUpdateActorOnly( void )
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
void CModelActor::UpdateAnimation( Sint32 AnimationNo, Float fAnimationTime )
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
void CModelActor::UpdateAnimation( Sint32 AnimationNo1, Float fAnimationTime1, Sint32 AnimationNo2, Float fAnimationTime2, Float fWeight )
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
void CModelActor::RenderingRequest( void )
{
	CSceneManagerBase *pScene = (CSceneManagerBase*)GetParent();

	// レンダリングキューに追加
	Sint32 Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		if ( m_pObjectTbl[i]->GetDrawEnable() )
		{
			pScene->AddObject( m_pObjectTbl[i] );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActor::RenderingBounding( Renderer::Object::ILine3D *pLine )
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
void CModelActor::SetCullTestEnable( Bool IsEnable )
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
Sint32 CModelActor::GetFrameCount( void )
{
	return m_pModel->GetFrameCount();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CModelActor::GetMeshCount( void )
{
	return m_ObjectCount;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CModelActor::GetMeshMaterialCount( Sint32 MeshIndex )
{
	return m_pObjectTbl[MeshIndex]->GetMaterialCount();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CModelActor::Frame_GetIndex( const char *pName )
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
Math::Matrix &CModelActor::Frame_GetTransformLocal( Sint32 Index )
{
	return m_pModel->GetFramePointer( Index )->GetMatrixLocal();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Math::Matrix &CModelActor::Frame_GetTransformWorld( Sint32 Index )
{
	return m_pModel->GetFramePointer( Index )->GetMatrixWorld();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActor::GetMesh_DrawEnable( Sint32 Index, Bool IsDrawEnable )
{
	m_pObjectTbl[Index]->SetDrawEnable( IsDrawEnable );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActor::MeshMaterial_SetShader( Sint32 MeshIndex, Sint32 MaterialIndex, Renderer::Shader::IShader *pShader )
{
	if ( pShader == NULL ) return;
	if ( pShader->IsInvalid() ) return;

	CSceneActorMaterial &Mtrl = m_pObjectTbl[MeshIndex]->GetSceneRenderMaterial( MaterialIndex );
	Mtrl.SetShader( (Renderer::Shader::IShader*)pShader );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActor::MeshMaterial_SetMaterialColor( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector4D &vColor )
{
	CSceneActorMaterial &Mtrl = m_pObjectTbl[MeshIndex]->GetSceneRenderMaterial( MaterialIndex );
	Mtrl.SetDiffuseColor( vColor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActor::MeshMaterial_SetEmissiveColor( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector4D &vColor )
{
	CSceneActorMaterial &Mtrl = m_pObjectTbl[MeshIndex]->GetSceneRenderMaterial( MaterialIndex );
	Mtrl.SetEmissiveColor( vColor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActor::MeshMaterial_SetSpecularColor( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector4D &vColor )
{
	CSceneActorMaterial &Mtrl = m_pObjectTbl[MeshIndex]->GetSceneRenderMaterial( MaterialIndex );
	Mtrl.SetSpecularColor( vColor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActor::MeshMaterial_SetSpecularRefractive( Sint32 MeshIndex, Sint32 MaterialIndex, Float fParam )
{
	CSceneActorMaterial &Mtrl = m_pObjectTbl[MeshIndex]->GetSceneRenderMaterial( MaterialIndex );
	Mtrl.SetSpecularRefractive( fParam );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActor::MeshMaterial_SetSpecularRoughly( Sint32 MeshIndex, Sint32 MaterialIndex, Float fParam )
{
	CSceneActorMaterial &Mtrl = m_pObjectTbl[MeshIndex]->GetSceneRenderMaterial( MaterialIndex );
	Mtrl.SetSpecularRoughly( fParam );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActor::MeshMaterial_SetDrawType( Sint32 MeshIndex, Sint32 MaterialIndex, eDrawType Type )
{
	CSceneActorMaterial &Mtrl = m_pObjectTbl[MeshIndex]->GetSceneRenderMaterial( MaterialIndex );
	Mtrl.SetDrawType( Type );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActor::MeshMaterial_SetTexture( Sint32 MeshIndex, Sint32 MaterialIndex, Renderer::ITexture *pTexture )
{
	CSceneActorMaterial &Mtrl = m_pObjectTbl[MeshIndex]->GetSceneRenderMaterial( MaterialIndex );
	Mtrl.SetTexture( TEXTURE_STAGE_COLOR, pTexture );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActor::MeshMaterial_SetTextureOffset( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector2D &vOffset )
{
	CSceneActorMaterial &Mtrl = m_pObjectTbl[MeshIndex]->GetSceneRenderMaterial( MaterialIndex );
	Mtrl.SetTextureOffset( vOffset );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActor::Collision_Create( void )
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
void CModelActor::Collision_SetEnable( Sint32 Index, Bool IsEnable )
{
	if ( m_pCollision == NULL ) return;

	m_pCollision->SetEnable( Index, IsEnable );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActor::Collision_SetEnable( const char *pName, Bool IsEnable )
{
	if ( m_pCollision == NULL ) return;

	m_pCollision->SetEnable( pName, IsEnable );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActor::Collision_Rendering( Renderer::Object::ILine3D *pLine )
{
	if ( m_pCollision == NULL ) return;

	m_pCollision->Rendering( pLine );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelActor::Collision_GetResult( Sint32 &FrameNo, Math::Vector3D &vPos )
{
	if ( m_pCollision == NULL ) return;

	m_pCollision->GetCollisionResult( FrameNo, vPos );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModelActor::Collision_Check( IModelActor *pSrc )
{
	if ( m_pCollision == NULL ) return false;
	if ( pSrc == NULL ) return false;
	if ( pSrc->IsInvalid() ) return false;

	return m_pCollision->Check( ((CModelActor*)pSrc)->m_pCollision );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModelActor::Collision_Check( Collision::CBox &Src )
{
	if ( m_pCollision == NULL ) return false;

	return m_pCollision->Check( Src );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModelActor::Collision_Check( Collision::CLine3D &Src )
{
	if ( m_pCollision == NULL ) return false;

	return m_pCollision->Check( Src );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModelActor::Collision_Check( Math::Vector3D &Src )
{
	if ( m_pCollision == NULL ) return false;

	return m_pCollision->Check( Src );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModelActor::Collision_CheckOnScreen( Math::Vector2D &Src, ISceneManager *pSceneMgr )
{
	if ( m_pCollision == NULL ) return false;

	return m_pCollision->CheckOnScreen( Src, pSceneMgr );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModelActor::HitCheckByRay( const Collision::CLine3D &Ray )
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
Bool CModelActor::HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box )
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
Bool CModelActor::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out )
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
Bool CModelActor::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out, Collision::CBox &Box )
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
Bool CModelActor::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out )
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
Bool CModelActor::HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out, Collision::CBox &Box )
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
void CModelActor::CreateCollisionDrawPrimitive( Renderer::Object::ILine3D *pLine )
{
	Sint32 Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pObjectTbl[i]->CreateCollisionDrawPrimitive( pLine );
	}
}
