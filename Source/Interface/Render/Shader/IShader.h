#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Vector4D.h"
#include "Math/Matrix.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	typedef void *FX_HANDLE;

namespace Renderer
{
namespace Shader
{
	class IShader : public IInterface
	{
	protected:
		virtual ~IShader() {}

	public:
		virtual Bool Begin( Sint32 *pPassMax, Bool IsSave = false ) = 0;
		virtual void End( void ) = 0;
		virtual void BeginPass( Sint32 Pass ) = 0;
		virtual void EndPass( void ) = 0;
		virtual void UpdateParameter( void ) = 0;

		virtual FX_HANDLE GetParameterByName( const char *pName ) = 0;
		virtual FX_HANDLE GetParameterBySemantic( const char *pSemantic ) = 0;

		virtual FX_HANDLE GetTechnique( const char *pName ) = 0;
		virtual void SetTechnique( FX_HANDLE Handle ) = 0;

		virtual void SetFloat( FX_HANDLE Handle, Float Param ) = 0;
		virtual void SetFloatArray( FX_HANDLE Handle, const Float *pParam, Sint32 Num ) = 0;
		virtual void SetInt( FX_HANDLE Handle, Sint32 Param ) = 0;
		virtual void SetIntArray( FX_HANDLE Handle, const Sint32 *pParam, Sint32 Num ) = 0;
		virtual void SetMatrix( FX_HANDLE Handle, const Math::SMatrix4x4 *pMatrix ) = 0;
		virtual void SetMatrixArray( FX_HANDLE Handle, const Math::SMatrix4x4 *pMatrix, Sint32 Num ) = 0;
		virtual void SetMatrixPointerArray( FX_HANDLE Handle, const Math::SMatrix4x4 **ppMatrix, Sint32 Num ) = 0;
		virtual void SetMatrixTranspose( FX_HANDLE Handle, const Math::SMatrix4x4 *pMatrix ) = 0;
		virtual void SetMatrixTransposeArray( FX_HANDLE Handle, const Math::SMatrix4x4 *pMatrix, Sint32 Num ) = 0;
		virtual void SetTexture( FX_HANDLE Handle, Renderer::ITexture *pTex ) = 0;
		virtual void SetVector( FX_HANDLE Handle, const Math::Vector4D *pVec ) = 0;
		virtual void SetVectorArray( FX_HANDLE Handle, const Math::Vector4D *pVec, Sint32 Num ) = 0;
	};
}
}
}
