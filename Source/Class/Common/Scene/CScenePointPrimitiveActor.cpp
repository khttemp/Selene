

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CScenePointPrimitiveActor.h"
#include "Class/Common/Render/3D/CPointPrimitive3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CScenePointActor::CScenePointActor( CSceneManagerBase *pSceneMgr, Renderer::Object::IPoint3D *pObject, Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr ) : Renderer::CRenderObject( pRender, pMgr )
	, m_pPoint		( NULL )
	, m_pObject				( NULL )
{
	m_pPoint = (Renderer::Object::CPoint3D*)pObject;
	m_pPoint->AddRef();

	// 子に連結
	pSceneMgr->AddChild( this );

	// メッシュデータ
	m_pObject = new CScenePointActorObject( pSceneMgr );
	m_pPoint->CreateRenderActor( m_pObject );

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

		// シェーダー用パラメーター
		Plugin::Shader::SModelParameter Param;
		Param.IsBoneEnable		= false;
		Param.IsNormalEnable	= false;
		Param.IsTextureEnable	= false;

		// マテリアルごとに設定
		Sint32 MtrlCnt = m_pObject->GetMaterialCount();
		for ( Sint32 j = 0; j < MtrlCnt; j++ )
		{
			CSceneActorMaterial &Mtrl = m_pObject->GetSceneRenderMaterial( j );

			Param.IsLightMap		= false;
			Param.IsBumpMap			= false;
			Param.IsSpecularMap		= false;
			Param.IsEnvironmentMap	= false;

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

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CScenePointActor::~CScenePointActor()
{
	SAFE_DELETE( m_pObject );
	SAFE_RELEASE( m_pPoint );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CScenePointActor::TransformReset( void )
{
	// 変換初期化
	Style::TransformReset();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CScenePointActor::TransformUpdate( void )
{
	Math::Matrix mWorld, mWorldInverse;

	GetTransformWithScale( mWorld );
	GetTransformInverseWithScale( mWorldInverse );

	// レンダリングアクターの更新
	m_pObject->Update( mWorld, mWorldInverse );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CScenePointActor::RenderingRequest( void )
{
	CSceneManagerBase *pScene = (CSceneManagerBase*)GetParent();

	// レンダリングキューに追加
	m_pObject->UpdateMaterial( m_pRender );
	pScene->AddObject( m_pObject );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CScenePointActor::SetShader( Renderer::Shader::IShader *pShader )
{
	if ( pShader == NULL ) return;
	if ( pShader->IsInvalid() ) return;

	CSceneActorMaterial &Mtrl = m_pObject->GetSceneRenderMaterial( 0 );
	Mtrl.SetShader( (Renderer::Shader::IShader*)pShader );
}

