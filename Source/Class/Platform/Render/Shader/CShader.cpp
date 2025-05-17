

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "System.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/File/CFileManager.h"
#include "Class/Platform/Surface/CTexture.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Render/Shader/CShader.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;
using namespace Shader;


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
Uint32 CShader::m_GlobalShaderID = 0;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CShader::CShader( CRenderObjectMgr *pMgr ) : CRenderObject( pMgr->GetRenderPointer(), pMgr )
	, m_pEffect			( NULL )
	, m_hTechniqueMain	( NULL )
	, m_ShaderID		( m_GlobalShaderID++ )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CShader::~CShader()
{
	SAFE_RELEASE( m_pEffect );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::OnLostDevice( void )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->OnLostDevice();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::OnResetDevice( void )
{
	if ( m_pEffect != NULL )
	{
		m_pEffect->OnResetDevice();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint32 CShader::GetID( void )
{
	return m_ShaderID;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetMainTechnique( const char *pName )
{
	FX_HANDLE hTech = GetTechnique( pName );
	if ( hTech != NULL )
	{
		m_hTechniqueMain = hTech;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CShader::CreateFromMemory( const void *pShader, Sint32 Size, Bool IsCompiled )
{
	ID3DXBuffer *pError = NULL;

	// ファイルからエフェクト読み出し
	HRESULT hr = m_pRender->CreateEffect( pShader, Size, &m_pEffect, &pError, IsCompiled );
	if FAILED( hr )
	{
		Log_PrintStrong( 0xFF0000, "エフェクトの読み込みに失敗しました。[%s]", m_pGraphicCard->GetD3DError( hr ) );
		if ( pError != NULL )
		{
			char *pBuff = new char [ pError->GetBufferSize() + 1 ];
			if ( pBuff != NULL )
			{
				MemoryCopy( pBuff, pError->GetBufferPointer(), pError->GetBufferSize() + 1 );
				Log_PrintStrong( 0xFF0000, "  -> Shader Compile Error [ %s ]", pBuff );
				SAFE_DELETE_ARRAY( pBuff );
			}
			SAFE_RELEASE( pError );
		}

		return false;
	}

	// メインテクニックの取得
	SetMainTechnique( "Technique_Main" );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SimpleBegin( void )
{
	SetDefaultTechnique();
	Begin( NULL );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SimpleEnd( void )
{
	End();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetDefaultTechnique( const FX_HANDLE hTechnique )
{
	FX_HANDLE Handle = hTechnique != NULL ? hTechnique : m_hTechniqueMain;
	m_pEffect->SetTechnique( (D3DXHANDLE)Handle );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CShader::Begin( Sint32 *pPassMax, Bool IsSave )
{
	return SUCCEEDED( m_pEffect->Begin( (unsigned int*)pPassMax, IsSave ? 0 : D3DXFX_DONOTSAVESTATE | D3DXFX_DONOTSAVESAMPLERSTATE ) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::End( void )
{
	m_pEffect->End();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::BeginPass( Sint32 Pass )
{
	m_pEffect->BeginPass( Pass );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::EndPass( void )
{
	m_pEffect->EndPass();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::UpdateParameter( void )
{
	m_pEffect->CommitChanges();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
FX_HANDLE CShader::GetParameterByName( const char *pName )
{
	return (FX_HANDLE)m_pEffect->GetParameterByName( NULL, pName );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
FX_HANDLE CShader::GetParameterBySemantic( const char *pSemantic )
{
	return (FX_HANDLE)m_pEffect->GetParameterBySemantic( NULL, pSemantic );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
FX_HANDLE CShader::GetTechnique( const char *pTechnique )
{
	return (FX_HANDLE)m_pEffect->GetTechniqueByName( pTechnique );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetTechnique( FX_HANDLE Handle )
{
	m_pEffect->SetTechnique( (D3DXHANDLE)Handle );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetFloat( FX_HANDLE Handle, Float Param )
{
	m_pEffect->SetFloat( (D3DXHANDLE)Handle, Param );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetFloatArray( FX_HANDLE Handle, const Float *pParam, Sint32 Num )
{
	m_pEffect->SetFloatArray( (D3DXHANDLE)Handle, pParam, Num );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetInt( FX_HANDLE Handle, Sint32 Param )
{

	m_pEffect->SetInt( (D3DXHANDLE)Handle, Param );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetIntArray( FX_HANDLE Handle, const Sint32 *pParam, Sint32 Num )
{
	m_pEffect->SetIntArray( (D3DXHANDLE)Handle, (const int*)pParam, Num );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetMatrix( FX_HANDLE Handle, const Math::SMatrix4x4 *pMatrix )
{
	m_pEffect->SetMatrix( (D3DXHANDLE)Handle, (const D3DXMATRIX*)pMatrix );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetMatrixArray( FX_HANDLE Handle, const Math::SMatrix4x4 *pMatrix, Sint32 Num )
{
	m_pEffect->SetMatrixArray( (D3DXHANDLE)Handle, (const D3DXMATRIX*)pMatrix, Num );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetMatrixPointerArray( FX_HANDLE Handle, const Math::SMatrix4x4 **ppMatrix, Sint32 Num )
{
	m_pEffect->SetMatrixPointerArray( (D3DXHANDLE)Handle, (const D3DXMATRIX**)ppMatrix, Num );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetMatrixTranspose( FX_HANDLE Handle, const Math::SMatrix4x4 *pMatrix )
{
	m_pEffect->SetMatrixTranspose( (D3DXHANDLE)Handle, (const D3DXMATRIX*)pMatrix );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetMatrixTransposeArray( FX_HANDLE Handle, const Math::SMatrix4x4 *pMatrix, Sint32 Num )
{
	m_pEffect->SetMatrixTransposeArray( (D3DXHANDLE)Handle, (const D3DXMATRIX*)pMatrix, Num );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetTexture( FX_HANDLE Handle, ITexture *pTex )
{
	if ( pTex == NULL )
	{
		m_pEffect->SetTexture( (D3DXHANDLE)Handle, NULL );
	}
	else
	{
		CTextureInterface *pTexData = (CTextureInterface*)pTex;
		IDirect3DBaseTexture9 *pTexture = NULL;
		pTexData->GetTexture( pTexture );
		m_pEffect->SetTexture( (D3DXHANDLE)Handle, pTexture );
		SAFE_RELEASE( pTexture );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetVector( FX_HANDLE Handle, const Math::Vector4D *pVec )
{
	m_pEffect->SetVector( (D3DXHANDLE)Handle, (const D3DXVECTOR4*)pVec );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CShader::SetVectorArray( FX_HANDLE Handle, const Math::Vector4D *pVec, Sint32 Num )
{
	m_pEffect->SetVectorArray( (D3DXHANDLE)Handle, (const D3DXVECTOR4*)pVec, Num );
}

