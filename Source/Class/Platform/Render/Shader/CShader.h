#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CRenderObject.h"
#include "Interface/Render/Shader/IShader.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Shader
{
	class CShader : public CRenderObject, public IShader
	{
	protected:
		static Uint32 m_GlobalShaderID;

	protected:
		ID3DXEffect *m_pEffect;
		FX_HANDLE m_hTechniqueMain;
		Uint32 m_ShaderID;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CShader( CRenderObjectMgr *pMgr );
		virtual ~CShader();

		virtual void OnLostDevice( void );
		virtual void OnResetDevice( void );

		virtual Uint32 GetID( void );

		virtual void SetMainTechnique( const char *pName );

		virtual Bool CreateFromMemory( const void *pShader, Sint32 Size, Bool IsCompiled );

		virtual void SimpleBegin( void );
		virtual void SimpleEnd( void );
		virtual void SetDefaultTechnique( const FX_HANDLE hTechnique = NULL );
		virtual Bool Begin( Sint32 *pPassMax, Bool IsSave = false );
		virtual void End( void );
		virtual void BeginPass( Sint32 Pass );
		virtual void EndPass( void );
		virtual void UpdateParameter( void );

		virtual FX_HANDLE GetParameterByName( const char *pName );
		virtual FX_HANDLE GetParameterBySemantic( const char *pSemantic );

		virtual FX_HANDLE GetTechnique( const char *pName );
		virtual void SetTechnique( FX_HANDLE Handle );

		virtual void SetFloat( FX_HANDLE Handle, Float Param );
		virtual void SetFloatArray( FX_HANDLE Handle, const Float *pParam, Sint32 Num );
		virtual void SetInt( FX_HANDLE Handle, Sint32 Param );
		virtual void SetIntArray( FX_HANDLE Handle, const Sint32 *pParam, Sint32 Num );
		virtual void SetMatrix( FX_HANDLE Handle, const Math::SMatrix4x4 *pMatrix );
		virtual void SetMatrixArray( FX_HANDLE Handle, const Math::SMatrix4x4 *pMatrix, Sint32 Num );
		virtual void SetMatrixPointerArray( FX_HANDLE Handle, const Math::SMatrix4x4 **ppMatrix, Sint32 Num );
		virtual void SetMatrixTranspose( FX_HANDLE Handle, const Math::SMatrix4x4 *pMatrix );
		virtual void SetMatrixTransposeArray( FX_HANDLE Handle, const Math::SMatrix4x4 *pMatrix, Sint32 Num );
		virtual void SetTexture( FX_HANDLE Handle, ITexture *pTex );
		virtual void SetVector( FX_HANDLE Handle, const Math::Vector4D *pVec );
		virtual void SetVectorArray( FX_HANDLE Handle, const Math::Vector4D *pVec, Sint32 Num );
	};
}
}
}
