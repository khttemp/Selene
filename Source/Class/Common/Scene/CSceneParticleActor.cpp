

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CSceneParticleActor.h"
#include "Class/Common/Render/3D/CParticle.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CParticleActor::CParticleActor( CSceneManagerBase *pSceneMgr, Renderer::Object::IParticle *pObject, Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr ) : CRenderObject( pRender, pMgr )
	, m_pParticle	( NULL )
	, m_pObject		( NULL )
{
	m_pParticle = (Renderer::Object::CParticle*)pObject;
	m_pParticle->AddRef();

	// 子に連結
	pSceneMgr->AddChild( this );

	// メッシュデータ
	m_pObject = new CParticleActorObject( pSceneMgr );
	m_pParticle->CreateRenderActor( m_pObject );

	// カスタムじゃないシェーダーの時はシェーダーの検索
	if ( pSceneMgr->GetShaderVersion() != SHADER_MODEL_CUSTOM )
	{
		// シェーダーを取得
		eSceneShadingType			ShadingType		= pSceneMgr->GetShadingType();
		eSceneFogType				FogType			= pSceneMgr->GetFogType();
		eSceneHighDynamicRangeType	HdrType			= pSceneMgr->GetHdrType();
		eShaderVersion				ShaderVersion	= pSceneMgr->GetShaderVersion();

		// シェーダー用パラメーター
		Plugin::Shader::SBillboardParameter Param;
		Param.IsSoftParticle = m_pObject->GetSoftBillboardEnable() != false;
		Param.IsNormalEnable = m_pObject->IsSupportVertexNormal()  != false;

		// マテリアルごとに設定
		Sint32 MtrlCnt = m_pObject->GetMaterialCount();
		for ( Sint32 i = 0; i < MtrlCnt; i++ )
		{
			CSceneActorMaterial &Mtrl = m_pObject->GetSceneRenderMaterial( i );
			Renderer::Shader::IShader *pShader = Renderer::Shader::ShaderManager::GetShader(
																ShaderVersion,
																Param,
																ShadingType,
																FogType,
																HdrType );
			Mtrl.SetShader( pShader );
			SAFE_RELEASE( pShader );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CParticleActor::~CParticleActor()
{
	SAFE_DELETE( m_pObject );
	SAFE_RELEASE( m_pParticle );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CParticleActor::RenderingRequest( void )
{
	CSceneManagerBase *pScene = (CSceneManagerBase*)GetParent();

	// ソート用
	m_pObject->SetCenter( m_pParticle->GetCenter() );

	// レンダリングキューに追加
	m_pObject->UpdateMaterial( m_pRender );
	pScene->AddObject( m_pObject );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CParticleActor::RenderingDirect( void )
{
	m_pObject->SetStreamSource( m_pRender );
	m_pObject->Rendering( 0, m_pRender );
}

