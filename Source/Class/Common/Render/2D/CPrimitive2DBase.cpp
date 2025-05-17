

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Math/Vector4D.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Render/2D/CPrimitive2DBase.h"


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
CPrimitive2DBase::CPrimitive2DBase( CRender *pRender, CRenderObjectMgr *pMgr ) : CRenderPrimitiveObject( pRender, pMgr )
	, m_IsScissoring	( false )
	, m_fScissorX1		( 0.0f )
	, m_fScissorY1		( 0.0f )
	, m_fScissorX2		( 0.0f )
	, m_fScissorY2		( 0.0f )
	, m_ResizeStep		( false )
	, m_IsAutoResize	( false )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CPrimitive2DBase::~CPrimitive2DBase()
{
	char Temp[64] = "";
	StringCbPrintf( Temp, sizeof(Temp), "0x%08X", (Uint64)this );
	Log_PrintTable( 0xFF0000, 0x000000, "‰ð•ú", m_Name, Temp );
	Log_TableLine( 1 );
}

//-----------------------------------------------------------------------------------
/*
*/
//-----------------------------------------------------------------------------------
void CPrimitive2DBase::SetScissoring( Math::Rect2DF *pRect )
{
	if ( pRect != NULL )
	{
		m_IsScissoring = true;

		m_fScissorX1 = pRect->x;
		m_fScissorY1 = pRect->y;
		m_fScissorX2 = pRect->x + pRect->w;
		m_fScissorY2 = pRect->y + pRect->h;
	}
	else
	{
		m_IsScissoring = false;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2DBase::SetVertexLinear( SVertex2D *pPtIn1, SVertex2D *pPtIn2, SVertex2D *pPtOut, Float fAve )
{
	pPtOut->Pos.x = pPtIn1->Pos.x + ((pPtIn2->Pos.x - pPtIn1->Pos.x) * fAve);
	pPtOut->Pos.y = pPtIn1->Pos.y + ((pPtIn2->Pos.y - pPtIn1->Pos.y) * fAve);
	pPtOut->Pos.z = pPtIn1->Pos.z + ((pPtIn2->Pos.z - pPtIn1->Pos.z) * fAve);
	pPtOut->Pos.w = pPtIn1->Pos.w + ((pPtIn2->Pos.w - pPtIn1->Pos.w) * fAve);

	pPtOut->Col.a = (Uint8)(toF(pPtIn1->Col.a) + (toF(pPtIn2->Col.a - pPtIn1->Col.a) * fAve));
	pPtOut->Col.r = (Uint8)(toF(pPtIn1->Col.r) + (toF(pPtIn2->Col.r - pPtIn1->Col.r) * fAve));
	pPtOut->Col.g = (Uint8)(toF(pPtIn1->Col.g) + (toF(pPtIn2->Col.g - pPtIn1->Col.g) * fAve));
	pPtOut->Col.b = (Uint8)(toF(pPtIn1->Col.b) + (toF(pPtIn2->Col.b - pPtIn1->Col.b) * fAve));
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CPrimitive2DBase::SetVertexLinear( SVertex2DTex *pPtIn1, SVertex2DTex *pPtIn2, SVertex2DTex *pPtOut, Float fAve )
{
	pPtOut->Pos.x = pPtIn1->Pos.x + ((pPtIn2->Pos.x - pPtIn1->Pos.x) * fAve);
	pPtOut->Pos.y = pPtIn1->Pos.y + ((pPtIn2->Pos.y - pPtIn1->Pos.y) * fAve);
	pPtOut->Pos.z = pPtIn1->Pos.z + ((pPtIn2->Pos.z - pPtIn1->Pos.z) * fAve);
	pPtOut->Pos.w = pPtIn1->Pos.w + ((pPtIn2->Pos.w - pPtIn1->Pos.w) * fAve);
	pPtOut->Tex[0].x = pPtIn1->Tex[0].x + ((pPtIn2->Tex[0].x - pPtIn1->Tex[0].x) * fAve);
	pPtOut->Tex[0].y = pPtIn1->Tex[0].y + ((pPtIn2->Tex[0].y - pPtIn1->Tex[0].y) * fAve);
	pPtOut->Tex[1].x = pPtIn1->Tex[1].x + ((pPtIn2->Tex[1].x - pPtIn1->Tex[1].x) * fAve);
	pPtOut->Tex[1].y = pPtIn1->Tex[1].y + ((pPtIn2->Tex[1].y - pPtIn1->Tex[1].y) * fAve);

	pPtOut->Col.a = (Uint8)(toF(pPtIn1->Col.a) + (toF(pPtIn2->Col.a - pPtIn1->Col.a) * fAve));
	pPtOut->Col.r = (Uint8)(toF(pPtIn1->Col.r) + (toF(pPtIn2->Col.r - pPtIn1->Col.r) * fAve));
	pPtOut->Col.g = (Uint8)(toF(pPtIn1->Col.g) + (toF(pPtIn2->Col.g - pPtIn1->Col.g) * fAve));
	pPtOut->Col.b = (Uint8)(toF(pPtIn1->Col.b) + (toF(pPtIn2->Col.b - pPtIn1->Col.b) * fAve));
}

