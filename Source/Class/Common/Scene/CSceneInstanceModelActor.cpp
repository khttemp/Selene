

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CSceneInstanceModelActor.h"
#include "Class/Common/Render/Model/CModel.h"
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
CInstanceModelActor::CInstanceModelActor( Sint32 InstanceCount, CSceneManagerBase *pSceneMgr, Renderer::Object::IModel *pObject, Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr ) : Renderer::CRenderObject( pRender, pMgr )
	, m_pModel				( NULL )
	, m_ObjectCount			( 0 )
	, m_pObjectTbl			( NULL )
{
	Sint32 Max;

	m_pModel = (Renderer::Object::CModel*)pObject;
	m_pModel->AddRef();

	// �q�ɘA��
	pSceneMgr->AddChild( this );

	// �C���X�^���X
	m_InstanceCount = InstanceCount;
	m_pControllerTbl = new CInstanceModelController * [ m_InstanceCount ];
	for ( Sint32 i = 0; i < InstanceCount; i++ )
	{
		m_pControllerTbl[i] = new CInstanceModelController( pSceneMgr, pObject, pRender, pMgr );
	}

	// ���b�V����
	m_ObjectCount = m_pModel->GetMeshCount();
	// ���b�V���f�[�^
	m_pObjectTbl = new CSceneInstanceModelActorObject * [ m_ObjectCount ];
	Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pObjectTbl[i] = new CSceneInstanceModelActorObject( pSceneMgr );
		// �C���X�^���X�ƘA��
		m_pObjectTbl[i]->SetControllerCount( InstanceCount );
		for ( Sint32 j = 0; j < InstanceCount; j++ )
		{
			m_pObjectTbl[i]->SetControllerObject( j, m_pControllerTbl[j]->GetControllerObject( i ) );
		}
		// ���b�V���f�[�^�擾
		m_pModel->GetMesh( i )->CreateRenderActor( m_pObjectTbl[i], InstanceCount );
	}

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

		Max = m_ObjectCount;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			// �V�F�[�_�[�p�p�����[�^�[
			Bool IsTangentEnable = m_pObjectTbl[i]->IsSupportVertexBump();

			Plugin::Shader::SModelParameter Param;
			Param.IsBoneEnable		= false;
			Param.IsNormalEnable	= m_pObjectTbl[i]->IsSupportVertexNormal()  != false;
			Param.IsTextureEnable	= m_pObjectTbl[i]->IsSupportVertexTexture() != false;

			// �}�e���A�����Ƃɐݒ�
			Sint32 MtrlCnt = m_pObjectTbl[i]->GetMaterialCount();
			for ( Sint32 j = 0; j < MtrlCnt; j++ )
			{
				CSceneActorMaterial &Mtrl = m_pObjectTbl[i]->GetSceneRenderMaterial( j );

				Param.IsLightMap		= Mtrl.GetTexture( TEXTURE_STAGE_LIGHT ) != NULL;
				Param.IsBumpMap			= Mtrl.GetTexture( TEXTURE_STAGE_NORMAL ) != NULL;
				Param.IsSpecularMap		= Mtrl.GetSpecularType() == SPECULAR_TYPE_ENABLE;
				Param.IsEnvironmentMap	= Mtrl.GetTexture( TEXTURE_STAGE_ENVIRONMENT ) != NULL;

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
CInstanceModelActor::~CInstanceModelActor()
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
IInstanceModelController *CInstanceModelActor::GetController( Sint32 Index )
{
	return m_pControllerTbl[Index];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelActor::Begin( void )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CInstanceModelActor::End( void )
{
	CSceneManagerBase *pScene = (CSceneManagerBase*)GetParent();

	// �����_�����O�L���[�ɒǉ�
	Sint32 Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		pScene->AddObject( m_pObjectTbl[i] );
	}
}

