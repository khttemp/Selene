#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CRenderPrimitiveObject.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Render/Shader/ShaderManager.h"
#include "Math/Matrix.h"
#include "Math/Vector3D.h"
#include "Math/Vector4D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CPrimitive3DBase : public CRenderPrimitiveObject
	{
	private:
		Bool m_IsVertexLock;
		Bool m_IsIndexLock;

	protected:
		CPrimitive3DBase( CRender *pRender, CRenderObjectMgr *pMgr );
		virtual ~CPrimitive3DBase();

	public:
		virtual Bool Push( const void *pIndex, Sint32 IndexCount );

		virtual Bool Push( const SVertex3DBase *pVtx, Sint32 Count );
		virtual Bool Push( const SVertex3DTexture *pVtx, Sint32 Count );
		virtual Bool Push( const SVertex3DLight *pVtx, Sint32 Count );
		virtual Bool Push( const SVertex3DBump *pVtx, Sint32 Count );
		virtual Bool Push( const SVertex3DAnimation *pVtx, Sint32 Count );

		virtual Sint32 GetVertexCount( void );
		virtual Sint32 GetIndexCount( void );

		virtual void Begin( Bool IsVertex, Bool IsIndex, Bool IsDirect );
		virtual void End( void );
	};
}
}
}
