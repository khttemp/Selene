

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Render/Model/CAnimationData.h"


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
CAnimationData::CAnimationData()
	: m_pScaleX			( NULL )
	, m_pScaleY			( NULL )
	, m_pScaleZ			( NULL )
	, m_pTranslateX		( NULL )
	, m_pTranslateY		( NULL )
	, m_pTranslateZ		( NULL )
	, m_pRotateNo		( NULL )
	, m_pRotate			( NULL )
	, m_fSx				( 1.0f )
	, m_fSy				( 1.0f )
	, m_fSz				( 1.0f )
	, m_fTx				( 0.0f )
	, m_fTy				( 0.0f )
	, m_fTz				( 0.0f )
{
	m_qRotate.Identity();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CAnimationData::~CAnimationData()
{
	SAFE_DELETE_ARRAY( m_pRotate );
	SAFE_DELETE( m_pScaleX )
	SAFE_DELETE( m_pScaleY )
	SAFE_DELETE( m_pScaleZ )
	SAFE_DELETE( m_pTranslateX )
	SAFE_DELETE( m_pTranslateY )
	SAFE_DELETE( m_pTranslateZ )
	SAFE_DELETE( m_pRotateNo );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CAnimationData::SetScaleKey( const SMF_ANIMATIONKEY_SCALE *pData, Sint32 Count )
{
	m_pScaleX = new Math::Animation( Count );
	m_pScaleY = new Math::Animation( Count );
	m_pScaleZ = new Math::Animation( Count );

	for ( Sint32 i = 0; i < Count; i++ )
	{
		m_pScaleX->SetKey( i, toF(pData[i].Time), pData[i].x, false, false, 0.0f, 0.0f );
		m_pScaleY->SetKey( i, toF(pData[i].Time), pData[i].y, false, false, 0.0f, 0.0f );
		m_pScaleZ->SetKey( i, toF(pData[i].Time), pData[i].z, false, false, 0.0f, 0.0f );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CAnimationData::SetRotateKey( const SMF_ANIMATIONKEY_ROTATE *pData, Sint32 Count )
{
	m_pRotate = new Math::Quaternion [ Count + 1 ];
	m_pRotateNo = new Math::Animation( Count );

	for ( Sint32 i = 0; i < Count; i++ )
	{
		m_pRotateNo->SetKey( i, toF(pData[i].Time), toF(i), false, false, 0.0f, 0.0f );
		m_pRotate[i].x = pData[i].x;
		m_pRotate[i].y = pData[i].y;
		m_pRotate[i].z = pData[i].z;
		m_pRotate[i].w = pData[i].w;
	}

	m_pRotate[Count] = m_pRotate[Count-1];
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CAnimationData::SetTranslateKey( const SMF_ANIMATIONKEY_TRANSLATE *pData, Sint32 Count )
{
	m_pTranslateX = new Math::Animation( Count );
	m_pTranslateY = new Math::Animation( Count );
	m_pTranslateZ = new Math::Animation( Count );

	for ( Sint32 i = 0; i < Count; i++ )
	{
		m_pTranslateX->SetKey( i, toF(pData[i].Time), pData[i].x, false, false, 0.0f, 0.0f );
		m_pTranslateY->SetKey( i, toF(pData[i].Time), pData[i].y, false, false, 0.0f, 0.0f );
		m_pTranslateZ->SetKey( i, toF(pData[i].Time), pData[i].z, false, false, 0.0f, 0.0f );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CAnimationData::GetParameter( Float &fSx, Float &fSy, Float &fSz, Float &fTx, Float &fTy, Float &fTz, Math::Quaternion &qRotate )
{
	fSx = m_fSx;
	fSy = m_fSy;
	fSz = m_fSz;
	fTx = m_fTx;
	fTy = m_fTy;
	fTz = m_fTz;
	qRotate = m_qRotate;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CAnimationData::Update( Float fTime, eAnimationType Type )
{
	// Šg‘åk¬
	m_fSx = m_pScaleX->GetParameter( fTime, Type, 1.0f );
	m_fSy = m_pScaleY->GetParameter( fTime, Type, 1.0f );
	m_fSz = m_pScaleZ->GetParameter( fTime, Type, 1.0f );

	// ˆÚ“®
	m_fTx = m_pTranslateX->GetParameter( fTime, Type, 0.0f );
	m_fTy = m_pTranslateY->GetParameter( fTime, Type, 0.0f );
	m_fTz = m_pTranslateZ->GetParameter( fTime, Type, 0.0f );

	// ‰ñ“]
	Float fNo = m_pRotateNo->GetParameter( fTime, Type, 0.0f );
	Sint32 No = toI(fNo);
	m_qRotate.Slerp( m_pRotate[No], m_pRotate[No+1], fNo - toF(No) );
}


