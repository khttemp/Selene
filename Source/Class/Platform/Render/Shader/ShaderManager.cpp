

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
	// 初期化
	//------------------------------------------------------------------------
	m_pRender = pRender;
	StringCbCopy( m_PluginDirectory, sizeof(m_PluginDirectory), pPluginDirectory );
	StringCbCat( m_PluginDirectory, sizeof(m_PluginDirectory), "Shader\\" );

	//------------------------------------------------------------------------
	// 基本シェーダー
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

		// 共通変数
		pProc = ::GetProcAddress( hDLL, "GetCommonVariableShaderBuffer" );
		((void(__stdcall*)(void*&,long&))pProc)( pBuff, Size );

		m_pShaderVariable = new ShaderVariable;
		m_pShaderVariable->SetShader( (CShader*)m_pRender->CreateShaderFromMemory( pBuff, Size, true ) );

		// エフェクト用シェーダー
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
	
		// DLL解放
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

	// キャッシュの解体
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
	// 同一シェーダーの検索
	//-------------------------------------------------
	const SModelCacheParameter CacheParam = {
		Param,
		ShaderVersion,
		ShadingType,
		FogType,
		HdrType,
		ShadowType,
	};

	// 検索
	if ( SearchSameShader( pShader, CacheParam ) )
	{
		return pShader;
	}

	//-------------------------------------------------
	// カレントディレクトリ
	//-------------------------------------------------
	::SetCurrentDirectory( m_PluginDirectory );

	//-------------------------------------------------
	// プラグイン取得用ループ
	//-------------------------------------------------
	Plugin::Shader::SModelParameter ParamTemp = Param;
	while ( (pShader == NULL) && (ShaderVersion != SHADER_MODEL_CUSTOM) )
	{
		//------------------------------------
		// バージョン毎の機能の縛り
		//------------------------------------
		switch ( ShaderVersion )
		{
		case SHADER_MODEL_0_0:
			// シーン設定
			ShadingType	= SHADING_TYPE_NORMAL;
			HdrType		= HDR_TYPE_DISABLE;
			// マテリアル設定
			ParamTemp.IsBumpMap	= false;
			break;
		}

		//------------------------------------
		// プラグイン名取得
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
		// DLL読み込み
		//------------------------------------
		hDLL = ::LoadLibrary( PluginName );
		if ( hDLL != NULL )
		{
			// 関数取得
			pProc = (Plugin::Shader::GetModelShaderBufferProc)::GetProcAddress( hDLL, "GetModelShaderBuffer" );
			if ( pProc != NULL )
			{
				// シェーダーコード取得
				if ( pProc( ParamTemp, pBuff, Size ) )
				{
					// シェーダー生成
					pShader = (CShader*)m_pRender->CreateShaderFromMemory( pBuff, Size, true );
				}
			}

			::FreeLibrary( hDLL );
		}

		//------------------------------------
		// シェーダーバージョン進める
		//------------------------------------
		ShaderVersion = (eShaderVersion)(ShaderVersion + 1);
	}

	//-------------------------------------------------
	// キャッシュに追加
	//-------------------------------------------------
	if ( pShader != NULL )
	{
		AddCahcheShader( pShader, CacheParam );

		// シャドウマップに応じてテクニックを変える
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
	// 同一シェーダーの検索
	//-------------------------------------------------
	const SBillboardCacheParameter CacheParam = {
		Param,
		ShaderVersion,
		ShadingType,
		FogType,
		HdrType,
	};

	// 検索
	if ( SearchSameShader( pShader, CacheParam ) )
	{
		return pShader;
	}

	//-------------------------------------------------
	// カレントディレクトリ
	//-------------------------------------------------
	::SetCurrentDirectory( m_PluginDirectory );

	//-------------------------------------------------
	// プラグイン取得用ループ
	//-------------------------------------------------
	while ( (pShader == NULL) && (ShaderVersion != SHADER_MODEL_CUSTOM) )
	{
		//------------------------------------
		// バージョン毎の機能の縛り
		//------------------------------------
		switch ( ShaderVersion )
		{
		case SHADER_MODEL_0_0:
			// シーン設定
			ShadingType	= SHADING_TYPE_NORMAL;
			HdrType		= HDR_TYPE_DISABLE;
			break;
		}

		//------------------------------------
		// プラグイン名取得
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
		// DLL読み込み
		//------------------------------------
		hDLL = ::LoadLibrary( PluginName );
		if ( hDLL != NULL )
		{
			// 関数取得
			pProc = (Plugin::Shader::GetBillboardShaderBufferProc)::GetProcAddress( hDLL, "GetBillboardShaderBuffer" );
			if ( pProc != NULL )
			{
				// シェーダーコード取得
				if ( pProc( Param, pBuff, Size ) )
				{
					// シェーダー生成
					pShader = (CShader*)m_pRender->CreateShaderFromMemory( pBuff, Size, true );
				}
			}

			::FreeLibrary( hDLL );
		}

		//------------------------------------
		// シェーダーバージョン進める
		//------------------------------------
		ShaderVersion = (eShaderVersion)(ShaderVersion + 1);
	}

	//-------------------------------------------------
	// キャッシュに追加
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

