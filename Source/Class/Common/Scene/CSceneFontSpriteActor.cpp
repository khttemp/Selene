

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CSceneFontSpriteActor.h"
#include "Class/Common/Render/3D/CFontSprite3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSceneFontSpriteActor::CSceneFontSpriteActor( CSceneManagerBase *pSceneMgr, Renderer::Object::IFontSprite3D *pObject, Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr ) : Renderer::CRenderObject( pRender, pMgr )
	, m_pFontSprite		( NULL )
	, m_pObjectTbl		( NULL )
	, m_ObjectCount		( 0 )
{
	m_pFontSprite = (Renderer::Object::CFontSprite3D*)pObject;
	m_pFontSprite->AddRef();

	// �q�ɘA��
	pSceneMgr->AddChild( this );

	Sint32 Max;

	// ���b�V���f�[�^
	m_ObjectCount = m_pFontSprite->GetSheetCount();
	m_pObjectTbl = new CParticleActorObject * [ m_ObjectCount ];
	Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pObjectTbl[i] = new CParticleActorObject( pSceneMgr );
		m_pFontSprite->CreateRenderActor( i, m_pObjectTbl[i] );
	}

	// �J�X�^������Ȃ��V�F�[�_�[�̎��̓V�F�[�_�[�̌���
	if ( pSceneMgr->GetShaderVersion() != SHADER_MODEL_CUSTOM )
	{
		// �V�F�[�_�[���擾
		eSceneShadingType			ShadingType		= pSceneMgr->GetShadingType();
		eSceneFogType				FogType			= pSceneMgr->GetFogType();
		eSceneHighDynamicRangeType	HdrType			= pSceneMgr->GetHdrType();
		eShaderVersion				ShaderVersion	= pSceneMgr->GetShaderVersion();

		Max = m_ObjectCount;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			// �V�F�[�_�[�p�p�����[�^�[
			Plugin::Shader::SBillboardParameter Param;
			Param.IsSoftParticle = m_pObjectTbl[i]->GetSoftBillboardEnable() != false;
			Param.IsNormalEnable = m_pObjectTbl[i]->IsSupportVertexNormal()  != false;

			// �}�e���A�����Ƃɐݒ�
			Sint32 MtrlCnt = m_pObjectTbl[i]->GetMaterialCount();
			for ( Sint32 i = 0; i < MtrlCnt; i++ )
			{
				CSceneActorMaterial &Mtrl = m_pObjectTbl[i]->GetSceneRenderMaterial( i );
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
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSceneFontSpriteActor::~CSceneFontSpriteActor()
{
	for ( Sint32 i = 0; i < m_ObjectCount; i++ )
	{
		SAFE_DELETE( m_pObjectTbl[i] );
	}
	SAFE_DELETE_ARRAY( m_pObjectTbl );

	SAFE_RELEASE( m_pFontSprite );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneFontSpriteActor::RenderingRequest( void )
{
	CSceneManagerBase *pScene = (CSceneManagerBase*)GetParent();

	// �����_�����O�L���[�ɒǉ�
	Sint32 Max = m_ObjectCount;
	for ( Sint32 i = 0; i < Max; i++ )
	{
		m_pObjectTbl[i]->UpdateMaterial( m_pRender );
		pScene->AddObject( m_pObjectTbl[i] );
	}
}
