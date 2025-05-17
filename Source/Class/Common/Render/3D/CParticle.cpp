

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Surface/CTexture.h"
#include "Class/Platform/Render/CIndexBuffer.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Render/3D/CParticle.h"
#include "Class/Common/Scene/CSceneManagerBase.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;
using namespace Object;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CParticle::CParticle( CRender *pRender, CRenderObjectMgr *pMgr, Bool IsSoftBillboard ) : CPrimitive3D( pRender, pMgr, true, IsSoftBillboard )
	, m_pTexture		( NULL )
	, m_vCenter			( 0.0f, 0.0f, 0.0f )
{
	SetName( "パーティクル" );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CParticle::~CParticle()
{
	SAFE_RELEASE( m_pTexture );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CParticle::Create( Sint32 VertexMax, Sint32 IndexMax, ITexture *pTexture, eParticleType Type )
{
	static const Sint32 VertexFlag[] = {
		VERTEX_ELEMENT_3DBASE | VERTEX_ELEMENT_3DTEXTURE,							// PARTICLE_NORMAL
		VERTEX_ELEMENT_3DBASE | VERTEX_ELEMENT_3DTEXTURE | VERTEX_ELEMENT_3DLIGHT,	// PARTICLE_VOLUME
	};

	Bool bRet = false;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "生成" );
	Log_PrintCellKind( m_Name );
	Log_CellBegin( 0 );

	m_VertexType = Type;

	//--------------------------------------------------------------
	// ポリゴンタイプ
	//--------------------------------------------------------------
	m_VertexFlag = VertexFlag[Type];

	//--------------------------------------------------------------
	// 頂点バッファ
	//--------------------------------------------------------------
	if ( (VertexFlag[Type] & VERTEX_ELEMENT_3DBASE) != 0 )
	{
		Sint32 Size = m_pRender->GetSize( VERTEX_ELEMENT_3DBASE );
		m_pVB_Base = m_pRender->CreateVertexBuffer( VertexMax, Size, true );
		if ( m_pVB_Base == NULL )
		{
			Log_PrintStrong( 0xFF0000, "頂点バッファの生成に失敗" );
			goto EXIT;
		}
	}

	if ( (VertexFlag[Type] & VERTEX_ELEMENT_3DTEXTURE) != 0 )
	{
		Sint32 Size = m_pRender->GetSize( VERTEX_ELEMENT_3DTEXTURE );
		m_pVB_Tex = m_pRender->CreateVertexBuffer( VertexMax, Size, true );
		if ( m_pVB_Tex == NULL )
		{
			Log_PrintStrong( 0xFF0000, "頂点バッファの生成に失敗" );
			goto EXIT;
		}
	}

	if ( (VertexFlag[Type] & VERTEX_ELEMENT_3DLIGHT) != 0 )
	{
		Sint32 Size = m_pRender->GetSize( VERTEX_ELEMENT_3DLIGHT );
		m_pVB_Light = m_pRender->CreateVertexBuffer( VertexMax, Size, true );
		if ( m_pVB_Light == NULL )
		{
			Log_PrintStrong( 0xFF0000, "頂点バッファの生成に失敗" );
			goto EXIT;
		}
	}

	//--------------------------------------------------------------
	// インデックスバッファ
	//--------------------------------------------------------------
	m_pIB = m_pRender->CreateIndexBuffer( IndexMax, false );
	if ( m_pIB == NULL )
	{
		Log_PrintStrong( 0xFF0000, "インデックスバッファの生成に失敗" );
		goto EXIT;
	}

	//--------------------------------------------------------------
	// 頂点ストリーム
	//--------------------------------------------------------------
	m_pVS = m_pRender->CreateVertexStream( VertexFlag[Type] );
	if ( m_pVS == NULL )
	{
		Log_PrintStrong( 0xFF0000, "頂点ストリームの生成に失敗" );
		goto EXIT;
	}

	//--------------------------------------------------------------
	// テクスチャ
	//--------------------------------------------------------------
	if ( (pTexture != NULL) && pTexture->IsInvalid() )
	{
		pTexture = NULL;
	}

	m_pTexture = pTexture;
	if ( pTexture != NULL )
	{
		m_pTexture->AddRef();
	}

	char Temp[64] = "";
	StringCbPrintf( Temp, sizeof(Temp), "0x%016X", (Uint64)this );
	Log_PrintLine( 0x0000000, Temp );

	bRet = true;

EXIT:
	Log_CellEnd();
	Log_TableEnd();
	Log_TableLine( 1 );

	return bRet;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CParticle::Begin( void )
{
	CPrimitive3D::Begin( true, true, true );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CParticle::End( void )
{
	CPrimitive3D::End();
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CParticle::CreateRenderActor( Scene::CParticleActorObject *pActor )
{
	//------------------------------------------------------------
	// メッシュデータ
	//------------------------------------------------------------
	pActor->SetStream( m_pIB, m_pVS, m_pVB_Base, m_pVB_Tex, m_pVB_Light, m_pVB_Bump, m_pVB_Animation );

	//------------------------------------------------------------
	// ポリゴンタイプ
	//------------------------------------------------------------
	pActor->SetSoftBillboardEnable( m_IsSoftBillboard );

	//------------------------------------------------------------
	// マテリアル
	//------------------------------------------------------------
	pActor->SetMateriaCount( 1 );
	Scene::CSceneActorMaterial &Mtrl = pActor->GetSceneRenderMaterial( 0 );
	// テクスチャ
	Mtrl.SetTexture( TEXTURE_STAGE_COLOR, m_pTexture );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CParticle::Draw( const Math::Vector3D &vPosition, const Math::Point2DF &Size, const Math::Rect2DI &SrcRect, CColor Color )
{
	Float fSx = Size.x * 0.5f;
	Float fSy = Size.y * 0.5f;

	Math::Vector2D PtTbl[] = {
		Math::Vector2D( -fSx, +fSy ), Math::Vector2D( +fSx, +fSy ),
		Math::Vector2D( -fSx, -fSy ), Math::Vector2D( +fSx, -fSy ),
	};

	Draw( vPosition, PtTbl, SrcRect, Color );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CParticle::Draw( const Math::Vector3D &vPosition, const Math::Vector2D PtTbl[], const Math::Rect2DI &SrcRect, CColor Color )
{
	//--------------------------------------------------
	// インデックス
	//--------------------------------------------------
	Uint16 Idx = (Uint16)m_pVB_Base->GetCount();
	Uint16 IdxTbl[6] = {
		Idx + 0, Idx + 1, Idx + 2,
		Idx + 2, Idx + 1, Idx + 3,
	};
	Push( IdxTbl, 6 );

	//--------------------------------------------------
	// 位置
	//--------------------------------------------------
	SVertex3DBase VtxBase[4] = {
		{ vPosition + m_vCenter, Color },
		{ vPosition + m_vCenter, Color },
		{ vPosition + m_vCenter, Color },
		{ vPosition + m_vCenter, Color },
	};
	Push( VtxBase, 4 );

	//--------------------------------------------------
	// テクスチャ
	//--------------------------------------------------
	Float u1, v1, u2, v2;
	if ( m_pTexture != NULL )
	{
		Math::Point2DF vTransform = m_pTexture->GetPixelToTexelTransform();
		u1 = toF(SrcRect.x            ) * vTransform.x;
		v1 = toF(SrcRect.y            ) * vTransform.y;
		u2 = toF(SrcRect.x + SrcRect.w) * vTransform.x;
		v2 = toF(SrcRect.y + SrcRect.h) * vTransform.y;
	}
	else
	{
		u1 = v1 = u2 = v2= 0.0f;
	}

	SVertex3DTexture VtxTex[4] = {
		{ Math::Vector2D( u1, v1 ), Math::Vector2D( PtTbl[0].x, PtTbl[0].y ) },
		{ Math::Vector2D( u2, v1 ), Math::Vector2D( PtTbl[1].x, PtTbl[1].y ) },
		{ Math::Vector2D( u1, v2 ), Math::Vector2D( PtTbl[2].x, PtTbl[2].y ) },
		{ Math::Vector2D( u2, v2 ), Math::Vector2D( PtTbl[3].x, PtTbl[3].y ) },
	};

	Push( VtxTex, 4 );

	//--------------------------------------------------
	// 法線
	//--------------------------------------------------
	if ( m_VertexType == PARTICLE_TYPE_VOLUME )
	{
		static const Math::Vector3D vNormal = Math::Vector3D( 1.5f, 1.5f, 1.0f ).Normalize();

		SVertex3DLight VtxLight[4] = {
			{ Math::Vector3D( -vNormal.x, +vNormal.y, -vNormal.z ) },
			{ Math::Vector3D( +vNormal.x, +vNormal.y, -vNormal.z ) },
			{ Math::Vector3D( -vNormal.x, -vNormal.y, -vNormal.z ) },
			{ Math::Vector3D( +vNormal.x, -vNormal.y, -vNormal.z ) },
		};

		Push( VtxLight, 4 );
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CParticle::DrawRotate( const Math::Vector3D &vPosition, const Math::Point2DF &Size, const Math::Rect2DI &SrcRect, CColor Color, Sint32 Angle )
{
	if ( NORMALIZE_ANGLE( Angle ) == 0 )
	{
		Draw( vPosition, Size, SrcRect, Color );
	}
	else
	{
		Float fSx = Size.x * 0.5f;
		Float fSy = Size.y * 0.5f;

		Math::Vector2D PtTbl[] = {
			Math::Vector2D( -fSx, +fSy ), Math::Vector2D( +fSx, +fSy ),
			Math::Vector2D( -fSx, -fSy ), Math::Vector2D( +fSx, -fSy ),
		};

		DrawRotate( vPosition, PtTbl, SrcRect, Color, Angle );
	}
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CParticle::DrawRotate( const Math::Vector3D &vPosition, const Math::Vector2D PtTbl[], const Math::Rect2DI &SrcRect, CColor Color, Sint32 Angle )
{
	if ( NORMALIZE_ANGLE( Angle ) == 0 )
	{
		Draw( vPosition, PtTbl, SrcRect, Color );
	}
	else
	{
		//--------------------------------------------------
		// インデックス
		//--------------------------------------------------
		Uint16 Idx = (Uint16)m_pVB_Base->GetCount();
		Uint16 IdxTbl[6] = {
			Idx + 0, Idx + 1, Idx + 2,
			Idx + 2, Idx + 1, Idx + 3,
		};
		Push( IdxTbl, 6 );

		//--------------------------------------------------
		// 位置
		//--------------------------------------------------
		SVertex3DBase VtxBase[4] = {
			{ vPosition + m_vCenter, Color },
			{ vPosition + m_vCenter, Color },
			{ vPosition + m_vCenter, Color },
			{ vPosition + m_vCenter, Color },
		};

		Push( VtxBase, 4 );

		//--------------------------------------------------
		// テクスチャ
		//--------------------------------------------------
		Float u1, v1, u2, v2;
		if ( m_pTexture != NULL )
		{
			Math::Point2DF vTransform = m_pTexture->GetPixelToTexelTransform();
			u1 = toF(SrcRect.x            ) * vTransform.x;
			v1 = toF(SrcRect.y            ) * vTransform.y;
			u2 = toF(SrcRect.x + SrcRect.w) * vTransform.x;
			v2 = toF(SrcRect.y + SrcRect.h) * vTransform.y;
		}
		else
		{
			u1 = v1 = u2 = v2= 0.0f;
		}

		SVertex3DTexture VtxTex[4] = {
			{ Math::Vector2D( u1, v1 ), Math::Vector2D( PtTbl[0].x, PtTbl[0].y ) },
			{ Math::Vector2D( u2, v1 ), Math::Vector2D( PtTbl[1].x, PtTbl[1].y ) },
			{ Math::Vector2D( u1, v2 ), Math::Vector2D( PtTbl[2].x, PtTbl[2].y ) },
			{ Math::Vector2D( u2, v2 ), Math::Vector2D( PtTbl[3].x, PtTbl[3].y ) },
		};

		VtxTex[0].TexLight.RotationZ( Angle );
		VtxTex[1].TexLight.RotationZ( Angle );
		VtxTex[2].TexLight.RotationZ( Angle );
		VtxTex[3].TexLight.RotationZ( Angle );

		Push( VtxTex, 4 );

		//--------------------------------------------------
		// 法線
		//--------------------------------------------------
		if ( m_VertexType == PARTICLE_TYPE_VOLUME )
		{
			static const Math::Vector3D vNormal = Math::Vector3D( 1.5f, 1.5f, 1.0f ).Normalize();

			SVertex3DLight VtxLight[4] = {
				{ Math::Vector3D( -vNormal.x, +vNormal.y, -vNormal.z ) },
				{ Math::Vector3D( +vNormal.x, +vNormal.y, -vNormal.z ) },
				{ Math::Vector3D( -vNormal.x, -vNormal.y, -vNormal.z ) },
				{ Math::Vector3D( +vNormal.x, -vNormal.y, -vNormal.z ) },
			};

			VtxLight[0].Norm.RotationZ( Angle );
			VtxLight[1].Norm.RotationZ( Angle );
			VtxLight[2].Norm.RotationZ( Angle );
			VtxLight[3].Norm.RotationZ( Angle );

			Push( VtxLight, 4 );
		}
	}
}

