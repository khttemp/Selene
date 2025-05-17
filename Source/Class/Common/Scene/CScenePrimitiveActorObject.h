#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Common/SMF.h"
#include "Class/Platform/Render/Shader/ShaderManager.h"
#include "Class/Common/Scene/CSceneActorObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	class CPrimitiveActorObject : public CActorObject
	{
	protected:
		Bool m_IsBumpmap;
		Bool m_IsSpecularmap;
		Bool m_IsEnvironmentmap;
		Sint32 m_BoneCount;
		Math::SMatrix4x4 m_mBone[2][MAX_BONE_COUNT];

	public:
		CPrimitiveActorObject( CSceneManagerBase *pScene );
		~CPrimitiveActorObject();

		virtual void Update( Math::Matrix &mWorld, Math::Matrix &mWorldInverse );
		virtual void UpdateMaterial( Renderer::CRender *pRender );
		virtual void SetBoneMatrixArray( Math::Matrix *pMatrix, Sint32 Count );

		virtual Sint32 GetBoneCount( void );
		virtual const Math::SMatrix4x4 *GetBoneMatrixArray( void );
		virtual const Math::SMatrix4x4 *GetBoneMatrixArrayPrev( void );

		virtual void SetEnvironmentmapEnable( Bool IsEnvironmentmap );
		virtual void SetSpecularEnable( Bool IsSpecularmap );
		virtual void SetBumpmapEnable( Bool IsNormalmap );

	public:
		virtual void SetStreamSource( Renderer::CRender *pRender );
		virtual Sint32 Rendering( Sint32 MaterialNo, Renderer::CRender *pRender );
		virtual Sint32 Rendering_Velocity( Renderer::CRender *pRender );
		virtual eTransformType GetTransformType( void );
		virtual Bool IsAlphaEnable( void );
		virtual Bool GetSoftBillboardEnable( void );
		virtual Bool GetCullTestEnable( void );
		virtual Bool GetParallaxEnable( void );
		virtual Bool GetSpecularEnable( void );
		virtual Bool GetEnvironmentEnable( void );
		virtual void SetShader( Renderer::Shader::IShader *pShader );
		virtual void SetMaterialColor( Math::Vector4D &vColor );
		virtual void SetEmissiveColor( Math::Vector4D &vColor );
		virtual void SetSpecularColor( Math::Vector4D &vColor );
		virtual void SetSpecularRefractive( Float fParam );
		virtual void SetSpecularRoughly( Float fParam );
	};
}
}
