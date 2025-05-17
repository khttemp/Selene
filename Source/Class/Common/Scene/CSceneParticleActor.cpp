

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

	// �q�ɘA��
	pSceneMgr->AddChild( this );

	// ���b�V���f�[�^
	m_pObject = new CParticleActorObject( pSceneMgr );
	m_pParticle->CreateRenderActor( m_pObject );

	// �J�X�^������Ȃ��V�F�[�_�[�̎��̓V�F�[�_�[�̌���
	if ( pSceneMgr->GetShaderVersion() != SHADER_MODEL_CUSTOM )
	{
		// �V�F�[�_�[���擾
		eSceneShadingType			ShadingType		= pSceneMgr->GetShadingType();
		eSceneFogType				FogType			= pSceneMgr->GetFogType();
		eSceneHighDynamicRangeType	HdrType			= pSceneMgr->GetHdrType();
		eShaderVersion				ShaderVersion	= pSceneMgr->GetShaderVersion();

		// �V�F�[�_�[�p�p�����[�^�[
		Plugin::Shader::SBillboardParameter Param;
		Param.IsSoftParticle = m_pObject->GetSoftBillboardEnable() != false;
		Param.IsNormalEnable = m_pObject->IsSupportVertexNormal()  != false;

		// �}�e���A�����Ƃɐݒ�
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

	// �\�[�g�p
	m_pObject->SetCenter( m_pParticle->GetCenter() );

	// �����_�����O�L���[�ɒǉ�
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

