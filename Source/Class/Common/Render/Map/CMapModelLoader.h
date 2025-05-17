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
	class CMapModelLoader
	{
	private:
		CMapModel *m_pModel;
		CRender *m_pRender;

	private:
		void Load_STM( const Uint8 *pData, Sint32 Size );
		void Load_AREA( const Uint8 *pData, Sint32 Size );
		void Load_MTRL( const Uint8 *pData, Sint32 Size, Sint32 MaterialNo );
		void Load_TEXC( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl );
		void Load_TEXL( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl );
		void Load_TEXE( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl );
		void Load_TEXS( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl );
		void Load_TEXN( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl );
		void Load_LGT( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl );
		void Load_DRAW( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl );
		void Load_ZTES( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl );
		void Load_ZWRI( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl );
		void Load_ATES( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl );
		void Load_ABND( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl );
		void Load_CULL( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl );
		void Load_DIFF( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl );
		void Load_EMIS( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl );
		void Load_SPEC( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl );
		void Load_BUMP( const Uint8 *pData, Sint32 Size, CMapMaterial *pMtrl );
		void Load_FRM( const Uint8 *pData, Sint32 Size, Sint32 FrameNo );
		void Load_MESH( const Uint8 *pData, Sint32 Size, Sint32 MeshNo );
		void Load_OBB( const Uint8 *pData, Sint32 Size, CMapMesh *pMesh );
		void Load_V_PC( const Uint8 *pData, Sint32 Size, CMapMesh *pMesh );
		void Load_V_N( const Uint8 *pData, Sint32 Size, CMapMesh *pMesh );
		void Load_V_B( const Uint8 *pData, Sint32 Size, CMapMesh *pMesh );
		void Load_V_UV( const Uint8 *pData, Sint32 Size, CMapMesh *pMesh );
		void Load_IDX2( const Uint8 *pData, Sint32 Size, CMapMesh *pMesh );
		void Load_REND( const Uint8 *pData, Sint32 Size, CMapMesh *pMesh, Sint32 RenderDataNo );
		void Load_CLSN( const Uint8 *pData, Sint32 Size );
		void Load_CLSN_AREA( const Uint8 *pData, Sint32 Size );
		void Load_CLSN_FRM( const Uint8 *pData, Sint32 Size, Sint32 FrameNo );
		void Load_CLSN_DATA( const Uint8 *pData, Sint32 Size, Sint32 CollisionNo );
		void Load_CLSN_DATA_C_AT( const Uint8 *pData, Sint32 Size, CCollision *pCollision );
		void Load_CLSN_DATA_C_FC( const Uint8 *pData, Sint32 Size, CCollision *pCollision );
		void Load_CLSN_DATA_C_VX( const Uint8 *pData, Sint32 Size, CCollision *pCollision );

	public:
		CMapModelLoader( CMapModel *pModel, CRender *pRender );
		~CMapModelLoader();

		Bool LoadFromMemory( const Uint8 *pData, Sint32 Size );
	};
}
}
}
