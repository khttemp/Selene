#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CModelLoader
	{
	private:
		CModel *m_pModel;
		CRender *m_pRender;

	private:
		Bool Load_SMF( const Uint8 *pData, Sint32 Size );
		void Load_FRM( const Uint8 *pData, Sint32 Size, Sint32 FrameNo );
		void Load_OBB( const Uint8 *pData, Sint32 Size, CFrame *pFrame );
		void Load_ANIS( const Uint8 *pData, Sint32 Size, Sint32 CAnimationControllerNo );
		void Load_ANI( const Uint8 *pData, Sint32 Size, Sint32 CAnimationControllerNo, CAnimationData *pAnimationData );
		void Load_ANI( const Uint8 *pData, Sint32 Size, CAnimationData *pAnimationData );
		void Load_MESH( const Uint8 *pData, Sint32 Size, Sint32 MeshNo );
		void Load_OBB( const Uint8 *pData, Sint32 Size, CMesh *pMesh );
		void Load_BONE( const Uint8 *pData, Sint32 Size, CMesh *pMesh );
		void Load_V_PC( const Uint8 *pData, Sint32 Size, CMesh *pMesh );
		void Load_V_N( const Uint8 *pData, Sint32 Size, CMesh *pMesh );
		void Load_V_B( const Uint8 *pData, Sint32 Size, CMesh *pMesh );
		void Load_V_A( const Uint8 *pData, Sint32 Size, CMesh *pMesh );
		void Load_V_UV( const Uint8 *pData, Sint32 Size, CMesh *pMesh );
		void Load_IDX2( const Uint8 *pData, Sint32 Size, CMesh *pMesh );
		void Load_IDX4( const Uint8 *pData, Sint32 Size, CMesh *pMesh );
		void Load_C_AT( const Uint8 *pData, Sint32 Size, CMesh *pMesh );
		void Load_C_FC( const Uint8 *pData, Sint32 Size, CMesh *pMesh );
		void Load_C_VX( const Uint8 *pData, Sint32 Size, CMesh *pMesh );
		void Load_MTRL( const Uint8 *pData, Sint32 Size, CMesh *pMesh, Sint32 MaterialNo );
		void Load_TEXC( const Uint8 *pData, Sint32 Size, CMaterial *pMtrl );
		void Load_TEXL( const Uint8 *pData, Sint32 Size, CMaterial *pMtrl );
		void Load_TEXE( const Uint8 *pData, Sint32 Size, CMaterial *pMtrl );
		void Load_TEXS( const Uint8 *pData, Sint32 Size, CMaterial *pMtrl );
		void Load_TEXN( const Uint8 *pData, Sint32 Size, CMaterial *pMtrl );
		void Load_DRAW( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl );
		void Load_ZTES( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl );
		void Load_ZWRI( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl );
		void Load_ATES( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl );
		void Load_ABND( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl );
		void Load_CULL( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl );
		void Load_LGT( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl );
		void Load_DIFF( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl );
		void Load_EMIS( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl );
		void Load_SPEC( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl );
		void Load_BUMP( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl );

	public:
		CModelLoader( CModel *pModel, CRender *pRender );
		~CModelLoader();

		Bool LoadFromMemory( const Uint8 *pData, Sint32 Size );
		Bool SceneSkydoom_Create( Float fRadius, CColor TopColor, CColor BottomColor );
		Bool SceneSkydoomWithCloud_Create( Float fRadius, CColor TopColor, CColor BottomColor, ITexture *pTexCloud );
	};
}
}
}
