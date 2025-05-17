

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Render/CVertexBuffer.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Render/2D/CPointPrimitive2D.h"


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
CPoint2D::CPoint2D( CRender *pRender, CRenderObjectMgr *pMgr ) : CPrimitive2DBase( pRender, pMgr )
{
	SetName( "2D�|�C���g�v���~�e�B�u" );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPoint2D::~CPoint2D()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CPoint2D::Create( Sint32 PointMax, Bool IsAutoResize, Sint32 ResizeStep )
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
	m_pVB_Base = m_pRender->CreateVertexBuffer( PointMax, m_pRender->GetSize(VERTEX_ELEMENT_PRIMITIVE), true );
	if ( m_pVB_Base == NULL )
	{
		Log_PrintStrong( 0xFF0000, "���_�o�b�t�@�̐����Ɏ��s" );
		goto EXIT;
	}

	//--------------------------------------------------------------
	// ���_�X�g���[��
	//--------------------------------------------------------------
	m_pVS = m_pRender->CreateVertexStream( VERTEX_ELEMENT_PRIMITIVE );
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
Bool CPoint2D::Push( SVertex2D *pPoint, Sint32 Count )
{
	Math::Point2DF Transform = m_pCore->Virtual2RealTransform();
	SVertex2D PointTemp;

	//-------------------------------------------------------------------------------------
	// �|���S������
	//-------------------------------------------------------------------------------------
	if ( m_IsScissoring )
	{
		for ( Sint32 i = 0; i < Count; i++ )
		{
			//--------------------------------------------------
			// �ʒu
			//--------------------------------------------------
			PointTemp.Pos.x = (pPoint[i].Pos.x * Transform.x) - 0.5f;
			PointTemp.Pos.y = (pPoint[i].Pos.y * Transform.y) - 0.5f;

			//--------------------------------------------------
			// �V�U�����O
			//--------------------------------------------------
			if ( PointTemp.Pos.x < m_fScissorX1 ) continue;
			if ( PointTemp.Pos.x > m_fScissorX2 ) continue;
			if ( PointTemp.Pos.y < m_fScissorY1 ) continue;
			if ( PointTemp.Pos.y > m_fScissorY2 ) continue;

			//--------------------------------------------------
			// ���f�[�^
			//--------------------------------------------------
			PointTemp.Pos.z = 0.0f;
			PointTemp.Pos.w = 1.0f;
			PointTemp.Col = pPoint[i].Col;

			//--------------------------------------------------
			// �f�[�^�R�s�[
			//--------------------------------------------------
			if ( !m_pVB_Base->Push( &PointTemp, 1, m_IsAutoResize, m_ResizeStep ) )
			{
				break;
			}

			return true;
		}
	}
	else
	{
		SVertex2D *pDst = (SVertex2D*)m_pVB_Base->GetBufferPointer( Count, m_IsAutoResize, m_ResizeStep );
		if ( pDst != NULL )
		{
			for ( Sint32 i = 0; i < Count; i++ )
			{
				pDst[i].Pos.x = (pPoint[i].Pos.x * Transform.x) - 0.5f;
				pDst[i].Pos.y = (pPoint[i].Pos.y * Transform.y) - 0.5f;
				pDst[i].Pos.z = 0.0f;
				pDst[i].Pos.w = 1.0f;
				pDst[i].Col = pPoint[i].Col;
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
void CPoint2D::Begin( void )
{
	m_pVB_Base->Lock();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPoint2D::End( void )
{
	m_pVB_Base->UnLock();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPoint2D::Rendering( void )
{
	Sint32 PrimitiveCount = m_pVB_Base->GetCount();

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
		m_pRender->DrawPrimitive( PRIMITIVE_POINT, PrimitiveCount );

		// �`��|���S�����ǉ�
		m_pRender->ResetShader();
		m_pRender->Start2D( false );
		m_pCore->DrawPolygon( PrimitiveCount );
	}
}

