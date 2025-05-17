

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Scene/CScenePrimitiveActor.h"
#include "Class/Common/Render/3D/CPrimitive3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPrimitiveActor::CPrimitiveActor( CSceneManagerBase *pSceneMgr, Renderer::Object::IPrimitive3D *pObject, Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr, Bool IsLightmap, Bool IsNormalmap, Bool IsSpecularmap, Bool IsEnvironmentmap ) : Renderer::CRenderObject( pRender, pMgr )
	, m_pPrimitive		( NULL )
	, m_pObject			( NULL )
{
	m_pPrimitive = (Renderer::Object::CPrimitive3D*)pObject;
	m_pPrimitive->AddRef();

	// �q�ɘA��
	pSceneMgr->AddChild( this );

	// ���b�V���f�[�^
	m_pObject = new CPrimitiveActorObject( pSceneMgr );
	m_pPrimitive->CreateRenderActor( m_pObject );

	m_pObject->SetSpecularEnable( IsSpecularmap );
	m_pObject->SetBumpmapEnable( IsNormalmap );
	m_pObject->SetEnvironmentmapEnable( IsEnvironmentmap );

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
		Bool IsTangentEnable = m_pObject->IsSupportVertexBump();

		Plugin::Shader::SModelParameter Param;
		Param.IsBoneEnable		= m_pObject->IsSupportVertexBone()    != false;
		Param.IsNormalEnable	= m_pObject->IsSupportVertexNormal()  != false;
		Param.IsTextureEnable	= m_pObject->IsSupportVertexTexture() != false;

		// �}�e���A�����Ƃɐݒ�
		Sint32 MtrlCnt = m_pObject->GetMaterialCount();
		for ( Sint32 j = 0; j < MtrlCnt; j++ )
		{
			CSceneActorMaterial &Mtrl = m_pObject->GetSceneRenderMaterial( j );

			Param.IsLightMap		= IsLightmap       != false;
			Param.IsBumpMap			= IsNormalmap      != false;
			Param.IsSpecularMap		= IsSpecularmap    != false;
			Param.IsEnvironmentMap	= IsEnvironmentmap != false;

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

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPrimitiveActor::~CPrimitiveActor()
{
	SAFE_DELETE( m_pObject );
	SAFE_RELEASE( m_pPrimitive );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActor::TransformReset( void )
{
	// �ϊ�������
	Style::TransformReset();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActor::TransformUpdate( void )
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
void CPrimitiveActor::RenderingRequest( void )
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
void CPrimitiveActor::SetBoneMatrixArray( Math::Matrix *pMatrix, Sint32 Count )
{
	m_pObject->SetBoneMatrixArray( pMatrix, Count );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActor::SetShader( Renderer::Shader::IShader *pShader )
{
	if ( pShader == NULL ) return;
	if ( pShader->IsInvalid() ) return;

	CSceneActorMaterial &Mtrl = m_pObject->GetSceneRenderMaterial( 0 );
	Mtrl.SetShader( (Renderer::Shader::IShader*)pShader );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActor::SetMaterialColor( Math::Vector4D &vColor )
{
	m_pObject->SetMaterialColor( vColor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActor::SetEmissiveColor( Math::Vector4D &vColor )
{
	m_pObject->SetEmissiveColor( vColor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActor::SetSpecularColor( Math::Vector4D &vColor )
{
	m_pObject->SetSpecularColor( vColor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActor::SetSpecularRefractive( Float fParam )
{
	m_pObject->SetSpecularRefractive( fParam );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitiveActor::SetSpecularRoughly( Float fParam )
{
	m_pObject->SetSpecularRoughly( fParam );
}

