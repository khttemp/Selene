

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Render/2D/CPrimitive2D.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Surface/CTexture.h"
#include "Class/Platform/Render/CVertexBuffer.h"


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
CPrimitive2D::CPrimitive2D( CRender *pRender, CRenderObjectMgr *pMgr ) : CPrimitive2DBase( pRender, pMgr )
{
	SetName( "2D�v���~�e�B�u" );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPrimitive2D::~CPrimitive2D()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive2D::Create( Sint32 PrimitiveMax, Bool IsAutoResize, Sint32 ResizeStep )
{
	Bool bRet = false;

	Log_TableBegin();
	Log_PrintCellTitle( 0x0000FF, "����" );
	Log_PrintCellKind( m_Name );
	Log_CellBegin( 0 );

	m_IsAutoResize = IsAutoResize && (ResizeStep > 0);
	m_ResizeStep = ResizeStep;

	//--------------------------------------------------------------
	// ���_�o�b�t�@
	//--------------------------------------------------------------
	m_pVB_Base = m_pRender->CreateVertexBuffer( PrimitiveMax, m_pRender->GetSize(VERTEX_ELEMENT_SPRITE), true );
	if ( m_pVB_Base == NULL )
	{
		Log_PrintStrong( 0xFF0000, "���_�o�b�t�@�̐����Ɏ��s" );
		goto EXIT;
	}

	//--------------------------------------------------------------
	// ���_�X�g���[��
	//--------------------------------------------------------------
	m_pVS = m_pRender->CreateVertexStream( VERTEX_ELEMENT_SPRITE );
	if ( m_pVS == NULL )
	{
		Log_PrintStrong( 0xFF0000, "���_�X�g���[���̐����Ɏ��s" );
		goto EXIT;
	}

	char Temp[64] = "";
	StringCbPrintf( Temp, sizeof(Temp), "0x%08X", (Uint64)this );
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
Sint32 CPrimitive2D::GetRequestedVertexCount( void )
{
	return m_pVB_Base->GetRequestedCount();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CPrimitive2D::GetRequestedVertexCountMax( void )
{
	return m_pVB_Base->GetRequestedCountMax();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPrimitive2D::Push( SPrimitiveVertex2D *pPrimitive, Sint32 Count )
{
	Math::Point2DF Transform = m_pCore->Virtual2RealTransform();

	//------------------------------------------------------------------
	// �|���S������
	//------------------------------------------------------------------
	if ( m_IsScissoring )
	{
		static SVertex2DTex ScissorPoint[32];

		for ( Sint32 i = 0; i < Count; i++ )
		{
			//----------------------------------
			// �������
			//----------------------------------
			pPrimitive[i].v1.Pos.x = (pPrimitive[i].v1.Pos.x * Transform.x) - 0.5f;
			pPrimitive[i].v1.Pos.y = (pPrimitive[i].v1.Pos.y * Transform.y) - 0.5f;
			pPrimitive[i].v2.Pos.x = (pPrimitive[i].v2.Pos.x * Transform.x) - 0.5f;
			pPrimitive[i].v2.Pos.y = (pPrimitive[i].v2.Pos.y * Transform.y) - 0.5f;
			pPrimitive[i].v3.Pos.x = (pPrimitive[i].v3.Pos.x * Transform.x) - 0.5f;
			pPrimitive[i].v3.Pos.y = (pPrimitive[i].v3.Pos.y * Transform.y) - 0.5f;

			//----------------------------------
			// �V�U�����O
			//----------------------------------
			Sint32 AddVertexCount = ScissorPolygon( ScissorPoint, &pPrimitive[i].v1 );
			if ( AddVertexCount == 0 ) continue;

			//----------------------------------
			// �f�[�^�R�s�[
			//----------------------------------
			SVertex2DTex *pDst = (SVertex2DTex*)m_pVB_Base->GetBufferPointer( AddVertexCount, m_IsAutoResize, m_ResizeStep );
			if ( pDst != NULL )
			{
				for ( Sint32 j = 0; j < AddVertexCount; j++ )
				{
					pDst[j].Pos.x	= ScissorPoint[j].Pos.x;
					pDst[j].Pos.y	= ScissorPoint[j].Pos.y;
					pDst[j].Pos.z	= 0.0f;
					pDst[j].Pos.w	= 1.0f;
					pDst[j].Col		= ScissorPoint[j].Col;
					pDst[j].Tex[0]	= ScissorPoint[j].Tex[0];
					pDst[j].Tex[1]	= ScissorPoint[j].Tex[1];
				}
			}
		}

		return true;
	}
	//------------------------------------------------------------------
	// �L���b�V���ǉ�
	//------------------------------------------------------------------
	else
	{
		SPrimitiveVertex2D *pDst = (SPrimitiveVertex2D*)m_pVB_Base->GetBufferPointer( Count * PRIMITIVE_POINT_COUNT, m_IsAutoResize, m_ResizeStep );
		if ( pDst != NULL )
		{
			for ( Sint32 i = 0; i < Count; i++ )
			{
				pDst[i].v1.Pos.x = (pPrimitive[i].v1.Pos.x * Transform.x) - 0.5f;
				pDst[i].v1.Pos.y = (pPrimitive[i].v1.Pos.y * Transform.y) - 0.5f;
				pDst[i].v2.Pos.x = (pPrimitive[i].v2.Pos.x * Transform.x) - 0.5f;
				pDst[i].v2.Pos.y = (pPrimitive[i].v2.Pos.y * Transform.y) - 0.5f;
				pDst[i].v3.Pos.x = (pPrimitive[i].v3.Pos.x * Transform.x) - 0.5f;
				pDst[i].v3.Pos.y = (pPrimitive[i].v3.Pos.y * Transform.y) - 0.5f;

				pDst[i].v1.Pos.z = 0.0f;		pDst[i].v1.Pos.w = 1.0f;
				pDst[i].v2.Pos.z = 0.0f;		pDst[i].v2.Pos.w = 1.0f;
				pDst[i].v3.Pos.z = 0.0f;		pDst[i].v3.Pos.w = 1.0f;

				pDst[i].v1.Col = pPrimitive[i].v1.Col;
				pDst[i].v2.Col = pPrimitive[i].v2.Col;
				pDst[i].v3.Col = pPrimitive[i].v3.Col;

				pDst[i].v1.Tex[0] = pPrimitive[i].v1.Tex[0];
				pDst[i].v2.Tex[0] = pPrimitive[i].v2.Tex[0];
				pDst[i].v3.Tex[0] = pPrimitive[i].v3.Tex[0];

				pDst[i].v1.Tex[1] = pPrimitive[i].v1.Tex[1];
				pDst[i].v2.Tex[1] = pPrimitive[i].v2.Tex[1];
				pDst[i].v3.Tex[1] = pPrimitive[i].v3.Tex[1];
			}

			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::Begin( void )
{
	m_pVB_Base->Lock();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::End( void )
{
	m_pVB_Base->UnLock();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::Rendering( void )
{
	Sint32 PrimitiveCount = m_pVB_Base->GetCount() / PRIMITIVE_POINT_COUNT;

	//--------------------------------------------------------------------------
	// �����_�����O
	//--------------------------------------------------------------------------
	if ( PrimitiveCount > 0 )
	{
		// �`��
		m_pRender->ResetShader();
		m_pRender->Start2D( false );
		m_pRender->SetVertexStream( m_pVS );
		m_pRender->SetVertexBuffer( &m_pVB_Base, 1 );
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE, PrimitiveCount );

		// �`��|���S�����ǉ�
		m_pCore->DrawPolygon( PrimitiveCount );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::RenderingNoStateChange( void )
{
	Sint32 PrimitiveCount = m_pVB_Base->GetCount() / PRIMITIVE_POINT_COUNT;

	//--------------------------------------------------------------------------
	// �����_�����O
	//--------------------------------------------------------------------------
	if ( PrimitiveCount > 0 )
	{
		// �`��
		m_pRender->SetVertexStream( m_pVS );
		m_pRender->SetVertexBuffer( &m_pVB_Base, 1 );
		m_pRender->DrawPrimitive( PRIMITIVE_TRIANGLE, PrimitiveCount );

		// �`��|���S�����ǉ�
		m_pCore->DrawPolygon( PrimitiveCount );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CPrimitive2D::ScissorPolygon( SVertex2DTex *pDst, SVertex2DTex *pSrc )
{
	if ( (pSrc[0].Pos.x < m_fScissorX1) && (pSrc[1].Pos.x < m_fScissorX1) && (pSrc[2].Pos.x < m_fScissorX1) ) return 0;
	if ( (pSrc[0].Pos.x > m_fScissorX2) && (pSrc[1].Pos.x > m_fScissorX2) && (pSrc[2].Pos.x > m_fScissorX2) ) return 0;
	if ( (pSrc[0].Pos.y < m_fScissorY1) && (pSrc[1].Pos.y < m_fScissorY1) && (pSrc[2].Pos.y < m_fScissorY1) ) return 0;
	if ( (pSrc[0].Pos.y > m_fScissorY2) && (pSrc[1].Pos.y > m_fScissorY2) && (pSrc[2].Pos.y > m_fScissorY2) ) return 0;

	static SVertex2DTex VxResult[4][16];
	Sint32 VertexCount = PRIMITIVE_POINT_COUNT;
	Sint32 VertexNum = 0;

	// ��
	VertexCount = ScissorPolygonLeft( pSrc, VxResult[0], VertexCount );

	// �E
	VertexCount = ScissorPolygonRight( VxResult[0], VxResult[1], VertexCount );

	// ��
	VertexCount = ScissorPolygonTop( VxResult[1], VxResult[2], VertexCount );

	// ��
	VertexCount = ScissorPolygonBottom( VxResult[2], VxResult[3], VertexCount );

	if ( VertexCount == 0 ) return 0;

	// ���X�g�ɓW�J
	for ( Sint32 i = 0; i < VertexCount - 2; i++ )
	{
		pDst[VertexNum++] = VxResult[3][0];
		pDst[VertexNum++] = VxResult[3][i + 1];
		pDst[VertexNum++] = VxResult[3][i + 2];
	}

	return VertexNum;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CPrimitive2D::ScissorPolygonLeft( SVertex2DTex *pPtIn, SVertex2DTex *pPtOut, Sint32 VxNum )
{
	static Bool IsClip[16];
	Sint32 VxTempNum = 0;

	//--------------------------------------------------------
	// �N���b�s���O
	//--------------------------------------------------------
	for ( Sint32 i = 0; i < VxNum; i++ )
	{
		IsClip[i] = (pPtIn[i].Pos.x < m_fScissorX1);
	}

	//--------------------------------------------------------
	// �V�U�����O
	//--------------------------------------------------------
	for ( Sint32 i = 0; i < VxNum; i++ )
	{
		Sint32 next = (i + 1) % VxNum;
		// ���̒��_�̓N���b�v����Ă���H
		if ( IsClip[i] )
		{
			// ���̒��_�̓N���b�v����Ă��Ȃ�
			if ( !IsClip[next] )
			{
				SVertex2DTex *p1 = &pPtIn[i];
				SVertex2DTex *p2 = &pPtIn[next];

				// �ʒu����
				Float Ave = (m_fScissorX1 - p1->Pos.x) / (p2->Pos.x - p1->Pos.x);

				// ���_�ǉ�
				CPrimitive2D::SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );

				VxTempNum++;
			}
		}
		// ���̒��_�̓N���b�v����Ă��Ȃ�
		else
		{
			// ���_�ǉ�
			pPtOut[VxTempNum++] = pPtIn[i];

			// ���̒��_�̓N���b�v����Ă���
			if ( IsClip[next] )
			{
				SVertex2DTex *p1 = &pPtIn[i];
				SVertex2DTex *p2 = &pPtIn[next];

				// �ʒu����
				Float Ave = (m_fScissorX1 - p1->Pos.x) / (p2->Pos.x - p1->Pos.x);

				// ���_�ǉ�
				CPrimitive2D::SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );

				VxTempNum++;
			}
		}
	}

	return VxTempNum;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CPrimitive2D::ScissorPolygonRight( SVertex2DTex *pPtIn, SVertex2DTex *pPtOut, Sint32 VxNum )
{
	static Bool IsClip[16];
	Sint32 VxTempNum = 0;

	//--------------------------------------------------------
	// �N���b�s���O
	//--------------------------------------------------------
	for ( Sint32 i = 0; i < VxNum; i++ )
	{
		IsClip[i] = (pPtIn[i].Pos.x > m_fScissorX2);
	}

	//--------------------------------------------------------
	// �V�U�����O
	//--------------------------------------------------------
	for ( Sint32 i = 0; i < VxNum; i++ )
	{
		Sint32 next = (i + 1) % VxNum;
		// ���̒��_�̓N���b�v����Ă���H
		if ( IsClip[i] )
		{
			// ���̒��_�̓N���b�v����Ă��Ȃ�
			if ( !IsClip[next] )
			{
				SVertex2DTex *p1 = &pPtIn[i];
				SVertex2DTex *p2 = &pPtIn[next];

				// �ʒu����
				Float Ave = (m_fScissorX2 - p1->Pos.x) / (p2->Pos.x - p1->Pos.x);

				// ���_�ǉ�
				CPrimitive2D::SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );

				VxTempNum++;
			}
		}
		// ���̒��_�̓N���b�v����Ă��Ȃ�
		else
		{
			// ���_�ǉ�
			pPtOut[VxTempNum++] = pPtIn[i];

			// ���̒��_�̓N���b�v����Ă���
			if ( IsClip[next] )
			{
				SVertex2DTex *p1 = &pPtIn[i];
				SVertex2DTex *p2 = &pPtIn[next];

				// �ʒu����
				Float Ave = (m_fScissorX2 - p1->Pos.x) * (1.0f / (p2->Pos.x - p1->Pos.x));

				// ���_�ǉ�
				CPrimitive2D::SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );

				VxTempNum++;
			}
		}
	}

	return VxTempNum;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CPrimitive2D::ScissorPolygonTop( SVertex2DTex *pPtIn, SVertex2DTex *pPtOut, Sint32 VxNum )
{
	static Bool IsClip[16];
	Sint32 VxTempNum = 0;

	//--------------------------------------------------------
	// �N���b�s���O
	//--------------------------------------------------------
	for ( Sint32 i = 0; i < VxNum; i++ )
	{
		IsClip[i] = (pPtIn[i].Pos.y < m_fScissorY1);
	}

	//--------------------------------------------------------
	// �V�U�����O
	//--------------------------------------------------------
	for ( Sint32 i = 0; i < VxNum; i++ )
	{
		Sint32 next = (i + 1) % VxNum;
		// ���̒��_�̓N���b�v����Ă���H
		if ( IsClip[i] )
		{
			// ���̒��_�̓N���b�v����Ă��Ȃ�
			if ( !IsClip[next] )
			{
				SVertex2DTex *p1 = &pPtIn[i];
				SVertex2DTex *p2 = &pPtIn[next];

				// �ʒu����
				Float Ave = (m_fScissorY1 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));

				// ���_�ǉ�
				CPrimitive2D::SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );

				VxTempNum++;
			}
		}
		// ���̒��_�̓N���b�v����Ă��Ȃ�
		else
		{
			// ���_�ǉ�
			pPtOut[VxTempNum++] = pPtIn[i];

			// ���̒��_�̓N���b�v����Ă���
			if ( IsClip[next] )
			{
				SVertex2DTex *p1 = &pPtIn[i];
				SVertex2DTex *p2 = &pPtIn[next];

				// �ʒu����
				Float Ave = (m_fScissorY1 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));

				// ���_�ǉ�
				CPrimitive2D::SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );

				VxTempNum++;
			}
		}
	}

	return VxTempNum;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CPrimitive2D::ScissorPolygonBottom( SVertex2DTex *pPtIn, SVertex2DTex *pPtOut, Sint32 VxNum )
{
	static Bool IsClip[16];
	Sint32 VxTempNum = 0;

	//--------------------------------------------------------
	// �N���b�s���O
	//--------------------------------------------------------
	for ( Sint32 i = 0; i < VxNum; i++ )
	{
		IsClip[i] = (pPtIn[i].Pos.y > m_fScissorY2);
	}

	//--------------------------------------------------------
	// �V�U�����O
	//--------------------------------------------------------
	for ( Sint32 i = 0; i < VxNum; i++ )
	{
		Sint32 next = (i + 1) % VxNum;
		// ���̒��_�̓N���b�v����Ă���H
		if ( IsClip[i] )
		{
			// ���̒��_�̓N���b�v����Ă��Ȃ�
			if ( !IsClip[next] )
			{
				SVertex2DTex *p1 = &pPtIn[i];
				SVertex2DTex *p2 = &pPtIn[next];

				// �ʒu����
				Float Ave = (m_fScissorY2 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));

				// ���_�ǉ�
				CPrimitive2D::SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );

				VxTempNum++;
			}
		}
		// ���̒��_�̓N���b�v����Ă��Ȃ�
		else
		{
			// ���_�ǉ�
			pPtOut[VxTempNum++] = pPtIn[i];

			// ���̒��_�̓N���b�v����Ă���
			if ( IsClip[next] )
			{
				SVertex2DTex *p1 = &pPtIn[i];
				SVertex2DTex *p2 = &pPtIn[next];

				// �ʒu����
				Float Ave = (m_fScissorY2 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));

				// ���_�ǉ�
				CPrimitive2D::SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );

				VxTempNum++;
			}
		}
	}

	return VxTempNum;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::Square( Math::Rect2DI &DstRect, CColor Color )
{
	Float x1 = toF(DstRect.x);
	Float y1 = toF(DstRect.y);
	Float x2 = toF(DstRect.x + DstRect.w);
	Float y2 = toF(DstRect.y + DstRect.h);

	SPrimitiveVertex2D Vtx[] = {
		{
			{ Math::Vector4D(x1, y1, 0.0f, 1.0f), Color },
			{ Math::Vector4D(x2, y1, 0.0f, 1.0f), Color },
			{ Math::Vector4D(x2, y2, 0.0f, 1.0f), Color },
		},
		{
			{ Math::Vector4D(x2, y2, 0.0f, 1.0f), Color },
			{ Math::Vector4D(x1, y2, 0.0f, 1.0f), Color },
			{ Math::Vector4D(x1, y1, 0.0f, 1.0f), Color },
		},
	};

	// �v���~�e�B�u�ɒǉ�
	Push( Vtx, 2 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::SquareRotate( Math::Rect2DI &DstRect, CColor Color, Sint32 Angle )
{
	Float x1 = toF(DstRect.x);
	Float y1 = toF(DstRect.y);
	Float x2 = toF(DstRect.x + DstRect.w);
	Float y2 = toF(DstRect.y + DstRect.h);

	Math::Vector2D Center( (x1 + x2) * 0.5f, (y1 + y2) * 0.5f );

	// ��]
	Math::Vector2D Pt[4] = {
		Math::Vector2D( x1, y1 ),
		Math::Vector2D( x2, y1 ),
		Math::Vector2D( x1, y2 ),
		Math::Vector2D( x2, y2 ),
	};

	for ( Sint32 i = 0; i < 4; i++ )
	{
		Pt[i] -= Center;
		Pt[i].RotationZ( Angle );
		Pt[i] += Center;
	}

	for ( Sint32 i = 0; i < 4; i++ )
	{
		Pt[i].x -= 0.5f;
		Pt[i].y -= 0.5f;
	}

	SPrimitiveVertex2D Vtx[] = {
		{
			{ Math::Vector4D( Pt[0].x, Pt[0].y, 0.0f, 1.0f), Color },
			{ Math::Vector4D( Pt[1].x, Pt[1].y, 0.0f, 1.0f), Color },
			{ Math::Vector4D( Pt[3].x, Pt[3].y, 0.0f, 1.0f), Color },
		},
		{
			{ Math::Vector4D( Pt[3].x, Pt[3].y, 0.0f, 1.0f), Color },
			{ Math::Vector4D( Pt[2].x, Pt[2].y, 0.0f, 1.0f), Color },
			{ Math::Vector4D( Pt[0].x, Pt[0].y, 0.0f, 1.0f), Color },
		},
	};

	// �v���~�e�B�u�ɒǉ�
	Push( Vtx, 2 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::Polygon( Math::Point2DI Pos, Float fRadius, CColor Color, Sint32 Num )
{
	Float fPx = toF(Pos.x);
	Float fPy = toF(Pos.y);

	for ( Sint32 i = 0; i < Num; i++ )
	{
		Sint32 a1 = (ANGLE_MAX * (i + 0) / Num) - (ANGLE_MAX / 2);
		Sint32 a2 = (ANGLE_MAX * (i + 1) / Num) - (ANGLE_MAX / 2);

		SPrimitiveVertex2D Vtx[] = {
			{ Math::Vector4D(fPx                           , fPy                           , 0.0f, 1.0f), Color },
			{ Math::Vector4D(fPx+toI(Math::Cos(a1)*fRadius), fPy+toI(Math::Sin(a1)*fRadius), 0.0f, 1.0f), Color },
			{ Math::Vector4D(fPx+toI(Math::Cos(a2)*fRadius), fPy+toI(Math::Sin(a2)*fRadius), 0.0f, 1.0f), Color },
		};

		// �v���~�e�B�u�ɒǉ�
		Push( Vtx, 1 );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::PolygonRotate( Math::Point2DI Pos, Float fRadius, CColor Color, Sint32 Num, Sint32 Angle )
{
	Float fPx = toF(Pos.x);
	Float fPy = toF(Pos.y);

	for ( Sint32 i = 0; i < Num; i++ )
	{
		Sint32 a1 = (ANGLE_MAX * (i + 0) / Num) - (ANGLE_MAX / 2) + Angle;
		Sint32 a2 = (ANGLE_MAX * (i + 1) / Num) - (ANGLE_MAX / 2) + Angle;

		SPrimitiveVertex2D Vtx[] = {
			{ Math::Vector4D(fPx                      , fPy                      , 0.0f, 1.0f), Color },
			{ Math::Vector4D(fPx+Math::Cos(a1)*fRadius, fPy+Math::Sin(a1)*fRadius, 0.0f, 1.0f), Color },
			{ Math::Vector4D(fPx+Math::Cos(a2)*fRadius, fPy+Math::Sin(a2)*fRadius, 0.0f, 1.0f), Color },
		};

		// �v���~�e�B�u�ɒǉ�
		Push( Vtx, 1 );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::Ring( Math::Point2DI Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num )
{
	Float fPx = toF(Pos.x);
	Float fPy = toF(Pos.y);

	for ( Sint32 i = 0; i < Num; i++ )
	{
		Sint32 a1 = (ANGLE_MAX * (i + 0) / Num) - (ANGLE_MAX / 2);
		Sint32 a2 = (ANGLE_MAX * (i + 1) / Num) - (ANGLE_MAX / 2);

		SPrimitiveVertex2D Vtx[] = {
			{
				{ Math::Vector4D(fPx+Math::Cos(a1)* fInRadius, fPy+Math::Sin(a1)* fInRadius, 0.0f, 1.0f),  InColor },
				{ Math::Vector4D(fPx+Math::Cos(a1)*fOutRadius, fPy+Math::Sin(a1)*fOutRadius, 0.0f, 1.0f), OutColor },
				{ Math::Vector4D(fPx+Math::Cos(a2)*fOutRadius, fPy+Math::Sin(a2)*fOutRadius, 0.0f, 1.0f), OutColor },
			},
			{
				{ Math::Vector4D(fPx+Math::Cos(a2)*fOutRadius, fPy+Math::Sin(a2)*fOutRadius, 0.0f, 1.0f), OutColor },
				{ Math::Vector4D(fPx+Math::Cos(a2)* fInRadius, fPy+Math::Sin(a2)* fInRadius, 0.0f, 1.0f),  InColor },
				{ Math::Vector4D(fPx+Math::Cos(a1)* fInRadius, fPy+Math::Sin(a1)* fInRadius, 0.0f, 1.0f),  InColor },
			},
		};

		// �v���~�e�B�u�ɒǉ�
		Push( Vtx, 2 );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2D::RingRotate( Math::Point2DI Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num, Sint32 Angle )
{
	Float fPx = toF(Pos.x);
	Float fPy = toF(Pos.y);

	for ( Sint32 i = 0; i < Num; i++ )
	{
		Sint32 a1 = (ANGLE_MAX * (i + 0) / Num) - (ANGLE_MAX / 2) + Angle;
		Sint32 a2 = (ANGLE_MAX * (i + 1) / Num) - (ANGLE_MAX / 2) + Angle;

		SPrimitiveVertex2D Vtx[] = {
			{
				{ Math::Vector4D(fPx+(Math::Cos(a1)* fInRadius), fPy+(Math::Sin(a1)* fInRadius), 0.0f, 1.0f),  InColor },
				{ Math::Vector4D(fPx+(Math::Cos(a1)*fOutRadius), fPy+(Math::Sin(a1)*fOutRadius), 0.0f, 1.0f), OutColor },
				{ Math::Vector4D(fPx+(Math::Cos(a2)*fOutRadius), fPy+(Math::Sin(a2)*fOutRadius), 0.0f, 1.0f), OutColor },
			},
			{
				{ Math::Vector4D(fPx+(Math::Cos(a2)*fOutRadius), fPy+(Math::Sin(a2)*fOutRadius), 0.0f, 1.0f), OutColor },
				{ Math::Vector4D(fPx+(Math::Cos(a2)* fInRadius), fPy+(Math::Sin(a2)* fInRadius), 0.0f, 1.0f),  InColor },
				{ Math::Vector4D(fPx+(Math::Cos(a1)* fInRadius), fPy+(Math::Sin(a1)* fInRadius), 0.0f, 1.0f),  InColor },
			},
		};

		// �v���~�e�B�u�ɒǉ�
		Push( Vtx, 2 );
	}
}




