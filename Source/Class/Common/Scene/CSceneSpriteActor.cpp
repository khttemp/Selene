

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CSceneSpriteActor.h"
#include "Class/Common/Render/3D/CSprite3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSpriteActor::CSpriteActor( CSceneManagerBase *pSceneMgr, Renderer::Object::ISprite3D *pObject, Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr ) : Renderer::CRenderObject( pRender, pMgr )
	, m_pSprite		( NULL )
	, m_pObject		( NULL )
{
	m_pSprite = (Renderer::Object::CSprite3D*)pObject;
	m_pSprite->AddRef();

	// �q�ɘA��
	pSceneMgr->AddChild( this );

	// ���b�V���f�[�^
	m_pObject = new CSpriteActorObject( pSceneMgr );
	m_pSprite->CreateRenderActor( m_pObject );

	// �J�X�^������Ȃ��V�F�[�_�[�̎��̓V�F�[�_�[�̌���
	if ( pSceneMgr->GetShaderVersion() != SHADER_MODEL_CUSTOM )
	{
		// �V�F�[�_�[���擾
		eSceneShadingType			ShadingType		= pSceneMgr->GetShadingType();
		eSceneFogType				FogType			= pSceneMgr->GetFogType();
		eSceneHighDynamicRangeType	HdrType			= pSceneMgr->GetHdrType();
		eSceneShadowType			ShadowType		= pSceneMgr->GetShadowType();
		eShaderVersion				ShaderVersion	= pSceneMgr->GetShaderVersion();
		eHardwareShadowType			HwShadowType	= pSceneMgr->GetHardwareShadowType();
		Bool						IsSoftShadow	= pSceneMgr->IsSoftShadowEnable();

		Plugin::Shader::SModelParameter Param;
		Param.IsBoneEnable		= false;
		Param.IsNormalEnable	= false;
		Param.IsTextureEnable	= true;

		// �}�e���A�����Ƃɐݒ�
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
CSpriteActor::~CSpriteActor()
{
	SAFE_DELETE( m_pObject );
	SAFE_RELEASE( m_pSprite );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSpriteActor::TransformReset( void )
{
	// �ϊ�������
	Style::TransformReset();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSpriteActor::TransformUpdate( void )
{
	Math::Matrix mWorld, mWorldInverse;

	GetTransformWithScale( mWorld );
	GetTransformInverseWithScale( mWorldInverse );

	// �����_�����O�A�N�^�[�̍X�V
	m_pObject->Update( mWorld, mWorldInverse );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSpriteActor::RenderingRequest( void )
{
	CSceneManagerBase *pScene = (CSceneManagerBase*)GetParent();

	// �����_�����O�L���[�ɒǉ�
	m_pObject->UpdateMaterial( m_pRender );
	pScene->AddObject( m_pObject );
}
