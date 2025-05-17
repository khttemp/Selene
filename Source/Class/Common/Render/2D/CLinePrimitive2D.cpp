

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Render/2D/CLinePrimitive2D.h"


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
CLine2D::CLine2D( CRender *pRender, CRenderObjectMgr *pMgr ) : CPrimitive2DBase( pRender, pMgr )
{
	SetName( "2D���C���v���~�e�B�u" );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CLine2D::~CLine2D()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CLine2D::Create( Sint32 LineMax, Bool IsAutoResize, Sint32 ResizeStep )
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
	m_pVB_Base = m_pRender->CreateVertexBuffer( LineMax, m_pRender->GetSize(VERTEX_ELEMENT_PRIMITIVE), true );
	if ( m_pVB_Base == NULL )
	{
		Log_PrintStrong( 0xFF0000, "���_�o�b�t�@�̐����Ɏ��s" );
		goto EXIT;
	}

	//--------------------------------------------------------------
	// ���_�X�g���[��
	//--------------------------------------------------------------
	m_pVS = m_pRender->CreateVertexStream( VERTEX_ELEMENT_PRIMITIVE);
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
Bool CLine2D::Push( SLineVertex2D *pLine, Sint32 Count )
{
	Math::Point2DF Transform = m_pCore->Virtual2RealTransform();

	//-------------------------------------------------------------------------------------
	// �|���S������
	//-------------------------------------------------------------------------------------
	if ( m_IsScissoring )
	{
		static SLineVertex2D ScissorLine;
		static SLineVertex2D LineTemp = {
			{ Math::Vector4D( 0.0f, 0.0f, 0.0f, 1.0f ) }, { Math::Vector4D( 0.0f, 0.0f, 0.0f, 1.0f ) },
		};

		for ( Sint32 i = 0; i < Count; i++ )
		{
			//--------------------------------------------------
			// �������
			//--------------------------------------------------
			LineTemp.v1.Pos.x = (pLine[i].v1.Pos.x * Transform.x) - 0.5f;
			LineTemp.v1.Pos.y = (pLine[i].v1.Pos.y * Transform.y) - 0.5f;
			LineTemp.v2.Pos.x = (pLine[i].v2.Pos.x * Transform.x) - 0.5f;
			LineTemp.v2.Pos.y = (pLine[i].v2.Pos.y * Transform.y) - 0.5f;
		
			LineTemp.v1.Col = pLine[i].v1.Col;
			LineTemp.v2.Col = pLine[i].v2.Col;

			//--------------------------------------------------
			// �V�U�����O
			//--------------------------------------------------
			Sint32 AddVertexCount = ScissorPolygon( (SVertex2D*)&ScissorLine, (SVertex2D*)&LineTemp );
			if ( AddVertexCount == 0 ) continue;

			//--------------------------------------------------
			// �f�[�^�R�s�[
			//--------------------------------------------------
			SLineVertex2D *pDst = (SLineVertex2D*)m_pVB_Base->GetBufferPointer( AddVertexCount, m_IsAutoResize, m_ResizeStep );
			if ( pDst != NULL )
			{
				*pDst = ScissorLine;
			}
		}
	}
	else
	{
		SLineVertex2D *pDst = (SLineVertex2D*)m_pVB_Base->GetBufferPointer( Count * LINE_POINT_COUNT, m_IsAutoResize, m_ResizeStep );
		if ( pDst != NULL )
		{
			for ( Sint32 i = 0; i < Count; i++ )
			{
				pDst[i].v1.Pos.x = (pLine[i].v1.Pos.x * Transform.x) - 0.5f;
				pDst[i].v1.Pos.y = (pLine[i].v1.Pos.y * Transform.y) - 0.5f;
				pDst[i].v1.Pos.z = 0.0f;
				pDst[i].v1.Pos.w = 1.0f;

				pDst[i].v2.Pos.x = (pLine[i].v2.Pos.x * Transform.x) - 0.5f;
				pDst[i].v2.Pos.y = (pLine[i].v2.Pos.y * Transform.y) - 0.5f;
				pDst[i].v2.Pos.z = 0.0f;
				pDst[i].v2.Pos.w = 1.0f;

				pDst[i].v1.Col = pLine[i].v1.Col;
				pDst[i].v2.Col = pLine[i].v2.Col;
			}
		}
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CLine2D::Begin( void )
{
	m_pVB_Base->Lock();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CLine2D::End( void )
{
	m_pVB_Base->UnLock();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CLine2D::Rendering( void )
{
	Sint32 PrimitiveCount = m_pVB_Base->GetCount() / LINE_POINT_COUNT;

	//-------------------------------------------------------------------------------------
	// �����_�����O
	//-------------------------------------------------------------------------------------
	if ( PrimitiveCount > 0 )
	{
		// �X�e�[�g
		m_pRender->SetTexture( TEXTURE_STAGE_COLOR, NULL );
		m_pRender->SetTexture( TEXTURE_STAGE_LIGHT, NULL );

		// �`��
		m_pRender->SetVertexStream( m_pVS );
		m_pRender->SetVertexBuffer( &m_pVB_Base, 1 );
		m_pRender->DrawPrimitive( PRIMITIVE_LINE, PrimitiveCount );

		// �`��|���S�����ǉ�
		m_pRender->ResetShader();
		m_pRender->Start2D( false );
		m_pCore->DrawPolygon( PrimitiveCount );
	}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CLine2D::ScissorPolygon( SVertex2D *pDst, SVertex2D *pSrc )
{
	if ( (pSrc[0].Pos.x < m_fScissorX1) && (pSrc[1].Pos.x < m_fScissorX1) ) return 0;
	if ( (pSrc[0].Pos.x > m_fScissorX2) && (pSrc[1].Pos.x > m_fScissorX2) ) return 0;
	if ( (pSrc[0].Pos.y < m_fScissorY1) && (pSrc[1].Pos.y < m_fScissorY1) ) return 0;
	if ( (pSrc[0].Pos.y > m_fScissorY2) && (pSrc[1].Pos.y > m_fScissorY2) ) return 0;

	static SVertex2D VxResult[4][16];
	Sint32 VertexCount = LINE_POINT_COUNT;
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
	pDst[VertexNum++] = VxResult[3][0];
	pDst[VertexNum++] = VxResult[3][1];

	return VertexNum;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CLine2D::ScissorPolygonLeft( SVertex2D *pPtIn, SVertex2D *pPtOut, Sint32 VxNum )
{
	static Bool IsClip[2];
	Sint32 VxTempNum = 0;

	SVertex2D *p1, *p2;
	Float Ave;

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
	if ( IsClip[0] && IsClip[1] )
	{
		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_fScissorX1 - p1->Pos.x) / (p2->Pos.x - p1->Pos.x);
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		// ���̒��_���N���b�v
		Ave = (m_fScissorX1 - p1->Pos.x) / (p2->Pos.x - p1->Pos.x);
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	ef ( IsClip[0] )
	{
		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_fScissorX1 - p1->Pos.x) / (p2->Pos.x - p1->Pos.x);
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		pPtOut[VxTempNum++] = pPtIn[1];
	}
	ef ( IsClip[1] )
	{
		pPtOut[VxTempNum++] = pPtIn[0];

		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_fScissorX1 - p1->Pos.x) / (p2->Pos.x - p1->Pos.x);
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	else
	{
		pPtOut[VxTempNum++] = pPtIn[0];
		pPtOut[VxTempNum++] = pPtIn[1];
	}

	return VxTempNum;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CLine2D::ScissorPolygonRight( SVertex2D *pPtIn, SVertex2D *pPtOut, Sint32 VxNum )
{
	static Bool IsClip[2];
	Sint32 VxTempNum = 0;

	SVertex2D *p1, *p2;
	Float Ave;

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
	if ( IsClip[0] && IsClip[1] )
	{
		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_fScissorX2 - p1->Pos.x) * (1.0f / (p2->Pos.x - p1->Pos.x));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		// ���̒��_���N���b�v
		Ave = (m_fScissorX2 - p1->Pos.x) * (1.0f / (p2->Pos.x - p1->Pos.x));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	ef ( IsClip[0] )
	{
		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_fScissorX2 - p1->Pos.x) * (1.0f / (p2->Pos.x - p1->Pos.x));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		pPtOut[VxTempNum++] = pPtIn[1];
	}
	ef ( IsClip[1] )
	{
		pPtOut[VxTempNum++] = pPtIn[0];

		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_fScissorX2 - p1->Pos.x) * (1.0f / (p2->Pos.x - p1->Pos.x));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	else
	{
		pPtOut[VxTempNum++] = pPtIn[0];
		pPtOut[VxTempNum++] = pPtIn[1];
	}

	return VxTempNum;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CLine2D::ScissorPolygonTop( SVertex2D *pPtIn, SVertex2D *pPtOut, Sint32 VxNum )
{
	static Bool IsClip[2];
	Sint32 VxTempNum = 0;

	SVertex2D *p1, *p2;
	Float Ave;

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
	if ( IsClip[0] && IsClip[1] )
	{
		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_fScissorY1 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		// ���̒��_���N���b�v
		Ave = (m_fScissorY1 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	ef ( IsClip[0] )
	{
		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_fScissorY1 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		pPtOut[VxTempNum++] = pPtIn[1];
	}
	ef ( IsClip[1] )
	{
		pPtOut[VxTempNum++] = pPtIn[0];

		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_fScissorY1 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	else
	{
		pPtOut[VxTempNum++] = pPtIn[0];
		pPtOut[VxTempNum++] = pPtIn[1];
	}

	return VxTempNum;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CLine2D::ScissorPolygonBottom( SVertex2D *pPtIn, SVertex2D *pPtOut, Sint32 VxNum )
{
	static Bool IsClip[2];
	Sint32 VxTempNum = 0;

	SVertex2D *p1, *p2;
	Float Ave;

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
	if ( IsClip[0] && IsClip[1] )
	{
		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_fScissorY2 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		// ���̒��_���N���b�v
		Ave = (m_fScissorY2 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	ef ( IsClip[0] )
	{
		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_fScissorY2 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;

		pPtOut[VxTempNum++] = pPtIn[1];
	}
	ef ( IsClip[1] )
	{
		pPtOut[VxTempNum++] = pPtIn[0];

		// ���̒��_���N���b�v
		p1 = &pPtIn[0];
		p2 = &pPtIn[1];
		// �ʒu����
		Ave = (m_fScissorY2 - p1->Pos.y) * (1.0f / (p2->Pos.y - p1->Pos.y));
		// ���_�ǉ�
		SetVertexLinear( p1, p2, &pPtOut[VxTempNum], Ave );
		VxTempNum++;
	}
	else
	{
		pPtOut[VxTempNum++] = pPtIn[0];
		pPtOut[VxTempNum++] = pPtIn[1];
	}

	return VxTempNum;
}

