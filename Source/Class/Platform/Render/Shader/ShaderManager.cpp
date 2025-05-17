

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Platform/Render/Shader/ShaderManager.h"
#include "Class/Platform/Render/Shader/CShader.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Render/CPostEffect.h"
#include "System.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;
using namespace Shader;


//-----------------------------------------------------------------------------------
// CONST
//-----------------------------------------------------------------------------------
static const char *g_pDirectoryTable[] =
{
	"SM2.0",		// SHADER_MODEL_2_0,
	"SM0.0",		// SHADER_MODEL_0_0,
	"-----",		// SHADER_MODEL_CUSTOM,
};


//-----------------------------------------------------------------------------------
// VARIABLE
//-----------------------------------------------------------------------------------
Bool					ShaderManager::m_IsDfaulteShaderEnable;
CRender					*ShaderManager::m_pRender;
CPostEffect				*ShaderManager::m_pPostEffect;
ShaderVariable			*ShaderManager::m_pShaderVariable;
ShaderEffect			*ShaderManager::m_pShaderEffect;
char					ShaderManager::m_PluginDirectory[MAX_PATH];
CBaseList				ShaderManager::m_ModelChacheList;
CBaseList				ShaderManager::m_BillboardChacheList;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool ShaderManager::Initialize( CRender *pRender, const char *pPluginDirectory )
{
	m_pRender				= NULL;
	m_pPostEffect			= NULL;
	m_pShaderVariable		= NULL;
	m_pShaderEffect			= NULL;
	m_IsDfaulteShaderEnable	= false;

	//------------------------------------------------------------------------
	// ������
	//------------------------------------------------------------------------
	m_pRender = pRender;
	StringCbCopy( m_PluginDirectory, sizeof(m_PluginDirectory), pPluginDirectory );
	StringCbCat( m_PluginDirectory, sizeof(m_PluginDirectory), "Shader\\" );

	//------------------------------------------------------------------------
	// ��{�V�F�[�_�[
	//------------------------------------------------------------------------
	char PluginName[MAX_PATH];
	::StringCbPrintf( PluginName, sizeof(PluginName), "%sCommon.ssp", m_PluginDirectory );
	HMODULE hDLL = ::LoadLibrary( PluginName );
	if ( hDLL != NULL )
	{
		void *pBuff = NULL;
		Sint32 Size = 0;
		void *pProc;

		m_IsDfaulteShaderEnable = true;

		// ���ʕϐ�
		pProc = ::GetProcAddress( hDLL, "GetCommonVariableShaderBuffer" );
		((void(__stdcall*)(void*&,long&))pProc)( pBuff, Size );

		m_pShaderVariable = new ShaderVariable;
		m_pShaderVariable->SetShader( (CShader*)m_pRender->CreateShaderFromMemory( pBuff, Size, true ) );

		// �G�t�F�N�g�p�V�F�[�_�[
		if ( pRender->IsSupportedPS20() )
		{
			pProc = ::GetProcAddress( hDLL, "GetSceneEffectShaderBuffer" );
			((void(__stdcall*)(void*&,long&))pProc)( pBuff, Size );

			m_pShaderEffect = new ShaderEffect;
			m_pShaderEffect->SetShader( m_pRender->CreateShaderFromMemory( pBuff, Size, true ) );

			pProc = ::GetProcAddress( hDLL, "GetPostEffectShaderBuffer" );
			((void(__stdcall*)(void*&,long&))pProc)( pBuff, Size );

			m_pPostEffect = new CPostEffect( pRender, pBuff, Size );
		}
	
		// DLL���
		::FreeLibrary( hDLL );
	}

	System::ResetCurrentDirectory();

	return m_IsDfaulteShaderEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void ShaderManager::Finalize( void )
{
	SAFE_RELEASE( m_pPostEffect );
	SAFE_DELETE( m_pShaderVariable );
	SAFE_DELETE( m_pShaderEffect );

	// �L���b�V���̉��
	CBaseObject *pObj, *pNext;

	pObj = m_ModelChacheList.GetTop();
	while ( pObj != NULL )
	{
		pNext = pObj->GetNext();
		SAFE_RELEASE( pObj );
		pObj = pNext;
	}

	pObj = m_BillboardChacheList.GetTop();
	while ( pObj != NULL )
	{
		pNext = pObj->GetNext();
		SAFE_RELEASE( pObj );
		pObj = pNext;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool ShaderManager::IsDfaulteShaderEnable( void )
{
	return m_IsDfaulteShaderEnable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ShaderVariable *ShaderManager::GetShaderVariable( void )
{
	return m_pShaderVariable;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
ShaderEffect *ShaderManager::GetShaderEffect( void )
{
	return m_pShaderEffect;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool ShaderManager::SearchSameShader( CShader *&pShader, const SModelCacheParameter &Param )
{
	CModelShaderCache *pObj = (CModelShaderCache*)m_ModelChacheList.GetTop();
	while ( pObj != NULL )
	{
		if ( pObj->IsSameParameter( Param ) )
		{
			pObj->GetShader( pShader );
			return true;
		}
		pObj = (CModelShaderCache*)pObj->GetNext();
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool ShaderManager::SearchSameShader( CShader *&pShader, const SBillboardCacheParameter &Param )
{
	CBillboardShaderCache *pObj = (CBillboardShaderCache*)m_BillboardChacheList.GetTop();
	while ( pObj != NULL )
	{
		if ( pObj->IsSameParameter( Param ) )
		{
			pObj->GetShader( pShader );
			return true;
		}
		pObj = (CBillboardShaderCache*)pObj->GetNext();
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void ShaderManager::AddCahcheShader( CShader *pShader, const SModelCacheParameter &Param )
{
	m_ModelChacheList.InsertTop( new CModelShaderCache( pShader, Param ) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void ShaderManager::AddCahcheShader( CShader *pShader, const SBillboardCacheParameter &Param )
{
	m_BillboardChacheList.InsertTop( new CBillboardShaderCache( pShader, Param ) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CShader *ShaderManager::GetShader( eShaderVersion ShaderVersion, const Plugin::Shader::SModelParameter &Param, eSceneShadingType ShadingType, eSceneFogType FogType, eSceneHighDynamicRangeType HdrType, eSceneShadowType ShadowType, eHardwareShadowType HardareShadowType, Bool IsSoftShadow )
{
	char PluginName[MAX_PATH] = "";
	Plugin::Shader::GetModelShaderBufferProc pProc = NULL;
	HMODULE hDLL = NULL;
	void *pBuff = NULL;
	Sint32 Size = 0;
	CShader *pShader = NULL;

	//-------------------------------------------------
	// ����V�F�[�_�[�̌���
	//-------------------------------------------------
	const SModelCacheParameter CacheParam = {
		Param,
		ShaderVersion,
		ShadingType,
		FogType,
		HdrType,
		ShadowType,
	};

	// ����
	if ( SearchSameShader( pShader, CacheParam ) )
	{
		return pShader;
	}

	//-------------------------------------------------
	// �J�����g�f�B���N�g��
	//-------------------------------------------------
	::SetCurrentDirectory( m_PluginDirectory );

	//-------------------------------------------------
	// �v���O�C���擾�p���[�v
	//-------------------------------------------------
	Plugin::Shader::SModelParameter ParamTemp = Param;
	while ( (pShader == NULL) && (ShaderVersion != SHADER_MODEL_CUSTOM) )
	{
		//------------------------------------
		// �o�[�W�������̋@�\�̔���
		//------------------------------------
		switch ( ShaderVersion )
		{
		case SHADER_MODEL_0_0:
			// �V�[���ݒ�
			ShadingType	= SHADING_TYPE_NORMAL;
			HdrType		= HDR_TYPE_DISABLE;
			// �}�e���A���ݒ�
			ParamTemp.IsBumpMap	= false;
			break;
		}

		//------------------------------------
		// �v���O�C�����擾
		//------------------------------------
		StringCbPrintf(
				PluginName, sizeof(PluginName),
				"%s\\Model\\%x%x%x%x%x%x%x%x.ssp",
				g_pDirectoryTable[ShaderVersion],
				ShadingType,
				FogType,
				HdrType,
				ShadowType,
				0,
				0,
				0,
				0 );

		//------------------------------------
		// DLL�ǂݍ���
		//------------------------------------
		hDLL = ::LoadLibrary( PluginName );
		if ( hDLL != NULL )
		{
			// �֐��擾
			pProc = (Plugin::Shader::GetModelShaderBufferProc)::GetProcAddress( hDLL, "GetModelShaderBuffer" );
			if ( pProc != NULL )
			{
				// �V�F�[�_�[�R�[�h�擾
				if ( pProc( ParamTemp, pBuff, Size ) )
				{
					// �V�F�[�_�[����
					pShader = (CShader*)m_pRender->CreateShaderFromMemory( pBuff, Size, true );
				}
			}

			::FreeLibrary( hDLL );
		}

		//------------------------------------
		// �V�F�[�_�[�o�[�W�����i�߂�
		//------------------------------------
		ShaderVersion = (eShaderVersion)(ShaderVersion + 1);
	}

	//-------------------------------------------------
	// �L���b�V���ɒǉ�
	//-------------------------------------------------
	if ( pShader != NULL )
	{
		AddCahcheShader( pShader, CacheParam );

		// �V���h�E�}�b�v�ɉ����ăe�N�j�b�N��ς���
		const char *pTechniqueTbl[][2] = {
			{ "Technique_Main",			"Technique_Main_Soft"			},
			{ "Technique_Main_NVIDIA",	"Technique_Main_NVIDIA_Soft"	},
			{ "Technique_Main_ATI",		"Technique_Main_ATI_Soft"		},
		};
		pShader->SetMainTechnique( pTechniqueTbl[HardareShadowType][IsSoftShadow?1:0] );
	}

	System::ResetCurrentDirectory();

	return pShader;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CShader *ShaderManager::GetShader( eShaderVersion ShaderVersion, const Plugin::Shader::SBillboardParameter &Param, eSceneShadingType ShadingType, eSceneFogType FogType, eSceneHighDynamicRangeType HdrType )
{
	char PluginName[MAX_PATH] = "";
	Plugin::Shader::GetBillboardShaderBufferProc pProc = NULL;
	HMODULE hDLL = NULL;
	void *pBuff = NULL;
	Sint32 Size = 0;
	CShader *pShader = NULL;

	//-------------------------------------------------
	// ����V�F�[�_�[�̌���
	//-------------------------------------------------
	const SBillboardCacheParameter CacheParam = {
		Param,
		ShaderVersion,
		ShadingType,
		FogType,
		HdrType,
	};

	// ����
	if ( SearchSameShader( pShader, CacheParam ) )
	{
		return pShader;
	}

	//-------------------------------------------------
	// �J�����g�f�B���N�g��
	//-------------------------------------------------
	::SetCurrentDirectory( m_PluginDirectory );

	//-------------------------------------------------
	// �v���O�C���擾�p���[�v
	//-------------------------------------------------
	while ( (pShader == NULL) && (ShaderVersion != SHADER_MODEL_CUSTOM) )
	{
		//------------------------------------
		// �o�[�W�������̋@�\�̔���
		//------------------------------------
		switch ( ShaderVersion )
		{
		case SHADER_MODEL_0_0:
			// �V�[���ݒ�
			ShadingType	= SHADING_TYPE_NORMAL;
			HdrType		= HDR_TYPE_DISABLE;
			break;
		}

		//------------------------------------
		// �v���O�C�����擾
		//------------------------------------
		StringCbPrintf(
				PluginName, sizeof(PluginName),
				"%s\\Billboard\\%x%x%x%x%x%x%x%x.ssp",
				g_pDirectoryTable[ShaderVersion],
				ShadingType,
				FogType,
				HdrType,
				0,
				0,
				0,
				0,
				0 );

		//------------------------------------
		// DLL�ǂݍ���
		//------------------------------------
		hDLL = ::LoadLibrary( PluginName );
		if ( hDLL != NULL )
		{
			// �֐��擾
			pProc = (Plugin::Shader::GetBillboardShaderBufferProc)::GetProcAddress( hDLL, "GetBillboardShaderBuffer" );
			if ( pProc != NULL )
			{
				// �V�F�[�_�[�R�[�h�擾
				if ( pProc( Param, pBuff, Size ) )
				{
					// �V�F�[�_�[����
					pShader = (CShader*)m_pRender->CreateShaderFromMemory( pBuff, Size, true );
				}
			}

			::FreeLibrary( hDLL );
		}

		//------------------------------------
		// �V�F�[�_�[�o�[�W�����i�߂�
		//------------------------------------
		ShaderVersion = (eShaderVersion)(ShaderVersion + 1);
	}

	//-------------------------------------------------
	// �L���b�V���ɒǉ�
	//-------------------------------------------------
	if ( pShader != NULL )
	{
		AddCahcheShader( pShader, CacheParam );
	}

	System::ResetCurrentDirectory();

	return pShader;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPostEffect *ShaderManager::GetPostEffect( void )
{
	return m_pPostEffect;
}

