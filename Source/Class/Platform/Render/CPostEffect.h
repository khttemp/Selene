#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CRenderObject.h"
#include "Class/Platform/Render/Shader/CShader.h"
#include "Interface/Render/IRender.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	class CPostEffect : public CBaseObject
	{
	private:
		CRender			*m_pRender;
		Shader::IShader	*m_pShader;
		CVertexBuffer	*m_pVB_PostEffect;
		CVertexLayout	*m_pVS_PostEffect;

		FX_HANDLE		m_hTech_Simple;
		FX_HANDLE		m_hTech_DownSample;
		FX_HANDLE		m_hTech_ShowAlpha;
		FX_HANDLE		m_hTech_Gaussian;
		FX_HANDLE		m_hTech_MultiSamplingAntialias;
		FX_HANDLE		m_hTech_HDR_DownSample;
		FX_HANDLE		m_hTech_HDR_BloomFx;
		FX_HANDLE		m_hTech_HDR_CrossFx;
		FX_HANDLE		m_hTech_Velocity_High;
		FX_HANDLE		m_hTech_Velocity_Low;
		FX_HANDLE		m_hTech_NormalDepthEdge;
		FX_HANDLE		m_hTech_DOF_Blur;
		FX_HANDLE		m_hTech_MSAA;

		FX_HANDLE		m_hDOF_PARAMETER;
		FX_HANDLE		m_hBLEND_RATE;
		FX_HANDLE		m_hBLUR_OFFSET;
		FX_HANDLE		m_hHDR_POWER;
		FX_HANDLE		m_hHDR_BOUNDARY;
		FX_HANDLE		m_hEDGE_POWER;
		FX_HANDLE		m_hOFFSET;
		FX_HANDLE		m_hTEXTURE[8];

		Math::Vector4D	m_vOffset[16+1];

	public:
		CPostEffect( CRender *pRender, void *pShader, long Size );
		virtual ~CPostEffect();

	public:
		virtual void Simple( const Math::Rect2DI &Dst, ITexture *pTex );
		virtual void DownSample( const Math::Rect2DI &Dst, ITexture *pTex );
		virtual void AlphaRendering( const Math::Rect2DF &Dst, ITexture *pTex );
		virtual void HDR_DownSample( const Math::Rect2DI &Dst, ITexture *pTex, Float fHDRPower, Float fHDRBoundary );
		virtual void HDR_BloomFx( const Math::Rect2DI &Dst, ITexture *pTexTbl[] );
		virtual void HDR_CrossFx( const Math::Rect2DI &Dst, ITexture *pTexTbl[] );
		virtual void DOF_Blur( const Math::Rect2DI &Dst, ITexture *pTexColor, ITexture *pTexDepth, Float fDofCenter, Float fDofScale );
		virtual void MSAA( const Math::Rect2DI &Dst, ITexture *pTex, Float fPower );
		virtual void Velocity_High( const Math::Rect2DI &Dst, ITexture *pTex, ITexture *pTexVelocity );
		virtual void Velocity_Low( const Math::Rect2DI &Dst, ITexture *pTex, ITexture *pTexVelocity );
		virtual void Gaussian( const Math::Rect2DI &Dst, ITexture *pTex, Sint32 Angle );
		virtual void NormalDepthEdge( const Math::Rect2DI &Dst, ITexture *pTex, Float fNormalPower, Float fDepthPower, Bool IsBold );
	};
}
}

