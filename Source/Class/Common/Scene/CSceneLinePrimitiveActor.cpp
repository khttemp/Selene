

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CSceneLinePrimitiveActor.h"
#include "Class/Common/Render/3D/CLinePrimitive3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSceneLineActor::CSceneLineActor( CSceneManagerBase *pSceneMgr, Renderer::Object::ILine3D *pObject, Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr ) : Renderer::CRenderObject( pRender, pMgr )
	, m_pLine		( NULL )
	, m_pObject		( NULL )
{
	m_pLine = (Renderer::Object::CLine3D*)pObject;
	m_pLine->AddRef();

	// �q�ɘA��
	pSceneMgr->AddChild( this );

	// ���b�V���f�[�^
	m_pObject = new CSceneLineActorObject( pSceneMgr );
	m_pLine->CreateRenderActor( m_pObject );

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

		// �V�F�[�_�[�p�p�����[�^�[
		Plugin::Shader::SModelParameter Param;
		Param.IsBoneEnable		= false;
		Param.IsNormalEnable	= false;
		Param.IsTextureEnable	= false;

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
CSceneLineActor::~CSceneLineActor()
{
	SAFE_DELETE( m_pObject );
	SAFE_RELEASE( m_pLine );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneLineActor::TransformReset( void )
{
	// �ϊ�������
	Style::TransformReset();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneLineActor::TransformUpdate( void )
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
void CSceneLineActor::RenderingRequest( void )
{
	CSceneManagerBase *pScene = (CSceneManagerBase*)GetParent();

	// �����_�����O�L���[�ɒǉ�
	m_pObject->UpdateMaterial( m_pRender );
	pScene->AddObject( m_pObject );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneLineActor::SetShader( Renderer::Shader::IShader *pShader )
{
	if ( pShader == NULL ) return;
	if ( pShader->IsInvalid() ) return;

	CSceneActorMaterial &Mtrl = m_pObject->GetSceneRenderMaterial( 0 );
	Mtrl.SetShader( (Renderer::Shader::IShader*)pShader );
}

