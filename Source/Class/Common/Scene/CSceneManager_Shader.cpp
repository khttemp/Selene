

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Scene/CSceneManager_Shader.h"
#include "Class/Common/Scene/CSceneParticleActor.h"
#include "Class/Common/Scene/CCustomizedSceneRenderObject.h"
#include "Class/Platform/Render/COcclusion.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Render/CPostEffect.h"
#include "Class/Platform/Surface/CDepthTexture.h"
#include "Class/Platform/Surface/CTexture.h"
#include "Common/SMF.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
// TABLE
//-----------------------------------------------------------------------------------
static const Math::Vector4D g_vProjectionReadMaskTbl[] = {
	Math::Vector4D( 0.0f, 0.0f, 0.0f, 1.0f ),	// PROJECTION_SHADOW_PRIORITY_0
	Math::Vector4D( 0.0f, 0.0f, 1.0f, 0.0f ),	// PROJECTION_SHADOW_PRIORITY_1
	Math::Vector4D( 0.0f, 1.0f, 0.0f, 0.0f ),	// PROJECTION_SHADOW_PRIORITY_2
	Math::Vector4D( 1.0f, 0.0f, 0.0f, 0.0f ),	// PROJECTION_SHADOW_PRIORITY_3
	Math::Vector4D( 0.0f, 0.0f, 0.0f, 0.0f ),	// PROJECTION_SHADOW_PRIORITY_4
};

static const Bool g_vProjectionWriteMaskTbl[][4] = {
	{ false, false, false, false },				// PROJECTION_SHADOW_PRIORITY_0
	{ false, false, false,  true },				// PROJECTION_SHADOW_PRIORITY_1
	{ false, false,  true,  true },				// PROJECTION_SHADOW_PRIORITY_2
	{ false,  true,  true,  true },				// PROJECTION_SHADOW_PRIORITY_3
	{  true,  true,  true,  true },				// PROJECTION_SHADOW_PRIORITY_4
};


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSceneManager_Shader::CSceneManager_Shader( Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr, Sint32 QueMax ) : CSceneManagerBase( pRender, pMgr, QueMax )
	, m_pDS_Shadow		( NULL )
	, m_pRT_Temp_DOF	( NULL )
	, m_pRT_Temp_HDR	( NULL )
	, m_pRT_HDR			( NULL )
	, m_pRT_HDR1		( NULL )
	, m_pRT_HDR2		( NULL )
	, m_pRT_HDR3		( NULL )
	, m_pRT_HDR1_GausA	( NULL )
	, m_pRT_HDR1_GausB	( NULL )
	, m_pRT_HDR2_GausA	( NULL )
	, m_pRT_HDR2_GausB	( NULL )
	, m_pRT_HDR3_GausA	( NULL )
	, m_pRT_HDR3_GausB	( NULL )
	, m_pRT_Shadow		( NULL )
	, m_pRT_Velocity	( NULL )
	, m_pRT_VelocityTemp( NULL )
	, m_pRT_DepthNormal	( NULL )
	, m_pRT_Final		( NULL )
{
	m_ShadowMapOffset[0].Set( 0.0f, 0.0f, 0.0f, 0.0f );
	m_ShadowMapOffset[1].Set( 0.0f, 0.0f, 0.0f, 0.0f );
	m_ShadowMapOffset[2].Set( 0.0f, 0.0f, 0.0f, 0.0f );
	m_ShadowMapOffset[3].Set( 0.0f, 0.0f, 0.0f, 0.0f );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSceneManager_Shader::~CSceneManager_Shader()
{
	SAFE_RELEASE( m_pDS_Shadow );
	SAFE_RELEASE( m_pRT_Temp_DOF );
	SAFE_RELEASE( m_pRT_Temp_HDR );
	SAFE_RELEASE( m_pRT_HDR );
	SAFE_RELEASE( m_pRT_HDR1 );
	SAFE_RELEASE( m_pRT_HDR2 );
	SAFE_RELEASE( m_pRT_HDR3 );
	SAFE_RELEASE( m_pRT_HDR1_GausA );
	SAFE_RELEASE( m_pRT_HDR1_GausB );
	SAFE_RELEASE( m_pRT_HDR2_GausA );
	SAFE_RELEASE( m_pRT_HDR2_GausB );
	SAFE_RELEASE( m_pRT_HDR3_GausA );
	SAFE_RELEASE( m_pRT_HDR3_GausB );
	SAFE_RELEASE( m_pRT_Shadow );
	SAFE_RELEASE( m_pRT_Velocity );
	SAFE_RELEASE( m_pRT_VelocityTemp );
	SAFE_RELEASE( m_pRT_DepthNormal );
	SAFE_RELEASE( m_pRT_Final );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_Shader::Rendering( Bool IsDrawBuffer )
{
	m_SceneRenderingTime = 0;

	//==============================================================
	// �J�n���ĂȂ�
	//==============================================================
	if ( m_SceneState != SCENE_STATE_END )
	{
		ClearBackground( false );
		return;
	}

	m_SceneState = SCENE_STATE_STANDBY;

	//==============================================================
	// �V�[���\�z���I���܂Ńu���b�N
	//==============================================================
	WaitForSceneConstruct();

	//==============================================================
	// ���ݎ���
	//==============================================================
	Uint64 TimeStart = m_pCore->GetSystemTimer();

	//==============================================================
	// �X�e�[�g
	//==============================================================
	m_pRender->StatePush();

	//==============================================================
	// �V���h�E�}�b�v����
	//==============================================================
	CreateShadowmap();

	//==============================================================
	// �����Ǘ������_�����O
	//==============================================================
	Rendering();

	//==============================================================
	// �f�o�b�O�p
	//==============================================================
	if ( IsDrawBuffer )
	{
		Rendering_DebugBuffer();
	}

	//==============================================================
	// �X�e�[�g
	//==============================================================
	m_pRender->StatePop();

	//==============================================================
	// �V�[���I�u�W�F�N�g���
	//==============================================================
	ReleaseObjectList();

	//==============================================================
	// �I������
	//==============================================================
	Uint64 TimeEnd = m_pCore->GetSystemTimer();

	// �o�ߎ���
	m_SceneRenderingTime = (100 * 60 * (TimeEnd - TimeStart)) / m_pCore->GetSystemTimerBySec();

	//==============================================================
	// �ꉞ�߂�
	//==============================================================
	m_pRender->SetColorWriteEnable( true, true, true, true );
	m_pRender->ResetRenderTarget();
	m_pRender->SetDepthBuffer( NULL );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_Shader::Rendering( void )
{
	//------------------------------------------------------------------------
	// �^�[�Q�b�g
	//------------------------------------------------------------------------
	Renderer::ITexture *pTargetTexture = m_pRT_Final;
	if ( IsAntiAliasEnable() || IsDepthOfFieldEnable() || IsHDREnable() )
	{
		pTargetTexture = m_pRT_Temp;
	}

	//------------------------------------------------------------------------
	// ���x�}�b�v
	//------------------------------------------------------------------------
	if ( IsVelocityEnable() )
	{
		// �^�[�Q�b�g
		m_pRender->SetRenderTarget( m_pRT_Velocity );
		m_pRender->SetDepthBuffer( m_pDS_Normal );
		// �N���A
		m_pRender->Clear( 0x00000000 );
		ClearDepthBuffer();
		// �����_�����O
		Rendering_Velocity();
	}

	//------------------------------------------------------------------------
	// �[�x�E�@���}�b�v
	//------------------------------------------------------------------------
	// �^�[�Q�b�g
	m_pRender->SetRenderTarget( m_pRT_DepthNormal );
	m_pRender->SetDepthBuffer( m_pDS_Normal );
	// �N���A
	m_pRender->Clear( 0x00000000 );
	ClearDepthBuffer();
	// �����_�����O
	Rendering_DepthNormal();

	//------------------------------------------------------------------------
	// ��{���f��
	//------------------------------------------------------------------------
	// �^�[�Q�b�g
	m_pRender->SetRenderTarget( IsVelocityEnable() ? m_pRT_VelocityTemp : pTargetTexture );
	// �N���A
	ClearBackground( true );

	// �s�������f���̃����_�����O
	Rendering_AlphaDisable();

	//------------------------------------------------------------------------
	// �G�b�W�̕`��
	//------------------------------------------------------------------------
	if ( IsToonEnable() )
	{
		DrawToonEDGE();
	}

	//------------------------------------------------------------------------
	// ���[�V�����u���[
	//------------------------------------------------------------------------
	if ( IsVelocityEnable() )
	{
		// �^�[�Q�b�g
		m_pRender->SetRenderTarget( pTargetTexture );

		// �`�惂�[�h
		m_pRender->SetDrawType( DRAW_TYPE_NORMAL );

		// �u���[
		switch ( m_MotionBlurType )
		{
		case MOTION_BLUR_TYPE_LOW:
			Renderer::Shader::ShaderManager::GetPostEffect()->Velocity_Low( m_pRender->GetViewport(), m_pRT_VelocityTemp, m_pRT_Velocity );
			break;
		case MOTION_BLUR_TYPE_HIGH:
			Renderer::Shader::ShaderManager::GetPostEffect()->Velocity_High( m_pRender->GetViewport(), m_pRT_VelocityTemp, m_pRT_Velocity );
			break;
		}
	}

	//------------------------------------------------------------------------
	// ���������f���̃����_�����O
	//------------------------------------------------------------------------
	Rendering_AlphaEnable();

	//------------------------------------------------------------------------
	// �|�X�g�G�t�F�N�g
	//------------------------------------------------------------------------
	if ( pTargetTexture == m_pRT_Temp )
	{
		PostEffect();

		// �A���t�@�`�����l���Ԃ�
		if ( m_pRenderTarget != NULL )
		{
			m_pRender->SetRenderTarget( m_pRenderTarget );
			m_pRender->SetDepthBuffer( NULL );

			m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
			m_pRender->SetAlphaTestEnable( false );
			m_pRender->SetCullType( CULL_NONE );

			m_pRender->SetColorWriteEnable( true, false, false, false );
			m_pRender->FillRect( m_RenderRect, CColor(255,255,255,255) );
			m_pRender->SetColorWriteEnable( true, true, true, true );
		}
	}
	//------------------------------------------------------------------------
	// �ŏI�p�X
	//------------------------------------------------------------------------
	else
	{
		m_pRender->SetRenderTarget( m_pRenderTarget );
		m_pRender->SetDepthBuffer( NULL );

		m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
		m_pRender->SetDepthTestEnable( false );
		m_pRender->SetDepthWriteEnable( false );
		m_pRender->SetAlphaTestEnable( false );
		m_pRender->SetCullType( CULL_NONE );

		m_pRender->SetColorWriteEnable( true, true, true, true );
		Renderer::Shader::ShaderManager::GetPostEffect()->Simple( m_RenderRect, m_pRT_Final );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_Shader::PostEffect( void )
{
	Math::Rect2DF Dst, Src;
	Renderer::ITexture *pSourceDOF = m_pRT_Temp;
	Renderer::ITexture *pSourceHDR = m_pRT_Temp;

	//------------------------------------------------------------------------
	// ���ʃX�e�[�g
	//------------------------------------------------------------------------
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
	m_pRender->SetDepthBuffer( NULL );

	//------------------------------------------------------------------------
	// �}���`�T���v�����O�A���`�G�C���A�X����
	//------------------------------------------------------------------------
	if ( IsAntiAliasEnable() )
	{
		// ��ʊE�[�x������ꍇ
		if ( IsDepthOfFieldEnable() )
		{
			m_pRender->SetRenderTarget( m_pRT_Temp_DOF );
			Renderer::Shader::ShaderManager::GetPostEffect()->MSAA( m_pRender->GetViewport(), m_pRT_Temp, m_fAntiAliasPower );
			pSourceDOF = m_pRT_Temp_DOF;
		}
		// ��ʊE�[�x���Ȃ��ꍇ
		else
		{
			// HDR������ꍇ
			if ( IsHDREnable() )
			{
				m_pRender->SetRenderTarget( m_pRT_Temp_HDR );
				Renderer::Shader::ShaderManager::GetPostEffect()->MSAA( m_pRender->GetViewport(), m_pRT_Temp, m_fAntiAliasPower );
				pSourceHDR = m_pRT_Temp_HDR;
			}
			// HDR���Ȃ��ꍇ
			else
			{
				// ���ڍŏI�p�X��
				m_pRender->SetRenderTarget( m_pRenderTarget );
				Renderer::Shader::ShaderManager::GetPostEffect()->MSAA( m_pRender->GetViewport(), m_pRT_Temp, m_fAntiAliasPower );
				return;
			}
		}
	}

	//------------------------------------------------------------------------
	// ��ʊE�[�x����
	//------------------------------------------------------------------------
	if ( IsDepthOfFieldEnable() )
	{
		// HDR������ꍇ
		if ( IsHDREnable() )
		{
			// HDR�^�[�Q�b�g�p�ꎞ�p�X��
			m_pRender->SetRenderTarget( m_pRT_Temp_HDR );
			Renderer::Shader::ShaderManager::GetPostEffect()->DOF_Blur( m_pRender->GetViewport(), pSourceDOF, m_pRT_DepthNormal, m_fFocusDepth, m_fFocusPower );
			pSourceHDR = m_pRT_Temp_HDR;
		}
		// HDR���Ȃ��ꍇ
		else
		{
			// ���ڍŏI�p�X��
			m_pRender->SetRenderTarget( m_pRenderTarget );
			Renderer::Shader::ShaderManager::GetPostEffect()->DOF_Blur( m_pRender->GetViewport(), pSourceDOF, m_pRT_DepthNormal, m_fFocusDepth, m_fFocusPower );
			return;
		}
	}

	//------------------------------------------------------------------------
	// HDR�p�u���[���`��
	//------------------------------------------------------------------------
	switch ( m_HdrType )
	{
	case HDR_TYPE_ENABLE:
		switch ( m_HdrEffect )
		{
		case HDR_EFFECT_BLOOM:
			// ���P�x�������o(Target -> HDR)
			m_pRender->SetRenderTarget( m_pRT_HDR );
			Renderer::Shader::ShaderManager::GetPostEffect()->HDR_DownSample( m_pRender->GetViewport(), pSourceHDR, m_fHDRPower, m_fHDRBoundary );

			// �k���o�b�t�@
			m_pRender->SetRenderTarget( m_pRT_HDR1 );
			Renderer::Shader::ShaderManager::GetPostEffect()->DownSample( m_pRender->GetViewport(), m_pRT_HDR );
			// �K�E�X(HDR -> A)
			m_pRender->SetRenderTarget( m_pRT_HDR1_GausA );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR1, DEG_TO_ANGLE(0) );
			// �K�E�X(A -> B)
			m_pRender->SetRenderTarget( m_pRT_HDR1_GausB );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR1_GausA, DEG_TO_ANGLE(90) );

			// �k���o�b�t�@
			m_pRender->SetRenderTarget( m_pRT_HDR2 );
			Renderer::Shader::ShaderManager::GetPostEffect()->DownSample( m_pRender->GetViewport(), m_pRT_HDR1_GausB );
			// �K�E�X(HDR -> A)
			m_pRender->SetRenderTarget( m_pRT_HDR2_GausA );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR2, DEG_TO_ANGLE(-45) );
			// �K�E�X(A -> B)
			m_pRender->SetRenderTarget( m_pRT_HDR2_GausB );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR2_GausA, DEG_TO_ANGLE(+45) );

			// �k���o�b�t�@
			m_pRender->SetRenderTarget( m_pRT_HDR3 );
			Renderer::Shader::ShaderManager::GetPostEffect()->DownSample( m_pRender->GetViewport(), m_pRT_HDR2_GausB );
			// �K�E�X(HDR -> A)
			m_pRender->SetRenderTarget( m_pRT_HDR3_GausA );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR3, DEG_TO_ANGLE(0) );
			// �K�E�X(A -> B)
			m_pRender->SetRenderTarget( m_pRT_HDR3_GausB );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR3_GausA, DEG_TO_ANGLE(90) );

			//------------------------------------------------------------------------
			// �^�[�Q�b�g
			//------------------------------------------------------------------------
			m_pRender->SetRenderTarget( m_pRenderTarget );
			m_pRender->SetDepthBuffer( NULL );

			//------------------------------------------------------------------------
			// �^�[�Q�b�g�ɕ`��(-> Target)
			//------------------------------------------------------------------------
			{
				Renderer::ITexture *pTexTbl[] = {
					pSourceHDR,
					m_pRT_HDR1_GausB,
					m_pRT_HDR2_GausB,
					m_pRT_HDR3_GausB,
				};

				m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
				Renderer::Shader::ShaderManager::GetPostEffect()->HDR_BloomFx( m_RenderRect, pTexTbl );
			}
			break;

		case HDR_EFFECT_CROSS:
			// ���P�x�������o(Target -> HDR)
			m_pRender->SetRenderTarget( m_pRT_HDR );
			Renderer::Shader::ShaderManager::GetPostEffect()->HDR_DownSample( m_pRender->GetViewport(), pSourceHDR, m_fHDRPower, m_fHDRBoundary );

			// �k���o�b�t�@
			m_pRender->SetRenderTarget( m_pRT_HDR1 );
			Renderer::Shader::ShaderManager::GetPostEffect()->DownSample( m_pRender->GetViewport(), m_pRT_HDR );
			// �K�E�X(HDR -> A)
			m_pRender->SetRenderTarget( m_pRT_HDR1_GausA );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR1, DEG_TO_ANGLE(-45) );
			// �k���o�b�t�@
			m_pRender->SetRenderTarget( m_pRT_HDR2 );
			Renderer::Shader::ShaderManager::GetPostEffect()->DownSample( m_pRender->GetViewport(), m_pRT_HDR1_GausA );
			// �K�E�X(HDR -> A)
			m_pRender->SetRenderTarget( m_pRT_HDR2_GausA );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR2, DEG_TO_ANGLE(-45) );
			// �k���o�b�t�@
			m_pRender->SetRenderTarget( m_pRT_HDR3 );
			Renderer::Shader::ShaderManager::GetPostEffect()->DownSample( m_pRender->GetViewport(), m_pRT_HDR2_GausA );
			// �K�E�X(HDR -> A)
			m_pRender->SetRenderTarget( m_pRT_HDR3_GausA );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR3, DEG_TO_ANGLE(-45) );

			// �k���o�b�t�@
			m_pRender->SetRenderTarget( m_pRT_HDR1 );
			Renderer::Shader::ShaderManager::GetPostEffect()->DownSample( m_pRender->GetViewport(), m_pRT_HDR );
			// �K�E�X(A -> B)
			m_pRender->SetRenderTarget( m_pRT_HDR1_GausB );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR1, DEG_TO_ANGLE(+45) );
			// �k���o�b�t�@
			m_pRender->SetRenderTarget( m_pRT_HDR2 );
			Renderer::Shader::ShaderManager::GetPostEffect()->DownSample( m_pRender->GetViewport(), m_pRT_HDR1_GausB );
			// �K�E�X(A -> B)
			m_pRender->SetRenderTarget( m_pRT_HDR2_GausB );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR2, DEG_TO_ANGLE(+45) );
			// �k���o�b�t�@
			m_pRender->SetRenderTarget( m_pRT_HDR3 );
			Renderer::Shader::ShaderManager::GetPostEffect()->DownSample( m_pRender->GetViewport(), m_pRT_HDR2_GausB );
			// �K�E�X(A -> B)
			m_pRender->SetRenderTarget( m_pRT_HDR3_GausB );
			Renderer::Shader::ShaderManager::GetPostEffect()->Gaussian( m_pRender->GetViewport(), m_pRT_HDR3, DEG_TO_ANGLE(+45) );

			//------------------------------------------------------------------------
			// �^�[�Q�b�g
			//------------------------------------------------------------------------
			m_pRender->SetRenderTarget( m_pRenderTarget );
			m_pRender->SetDepthBuffer( NULL );

			//------------------------------------------------------------------------
			// �^�[�Q�b�g�ɕ`��(-> Target)
			//------------------------------------------------------------------------
			{
				Renderer::ITexture *pTexTbl[] = {
					pSourceHDR,
					m_pRT_HDR2_GausA,
					m_pRT_HDR2_GausB,
					m_pRT_HDR3_GausA,
					m_pRT_HDR3_GausB,
				};

				m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
				Renderer::Shader::ShaderManager::GetPostEffect()->HDR_CrossFx( m_RenderRect, pTexTbl );
			}
			break;
		}
		break;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_Shader::DrawToonEDGE( void )
{
	m_pRender->SetDrawType( DRAW_TYPE_SUB );
	Renderer::Shader::ShaderManager::GetPostEffect()->NormalDepthEdge( m_pRender->GetViewport(), m_pRT_DepthNormal, m_fEdgeNormalPower, m_fEdgeDepthPower, m_IsToonBold );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_Shader::Rendering_DebugBuffer( void )
{
	Math::Rect2DF Dst, Src;

	Math::Point2DF Size = Math::Point2DF( toF(m_RenderRect.w / 6), toF(m_RenderRect.h / 6) );

	// �X�e�[�g
	m_pRender->SetCullType( CULL_FRONT );
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
	m_pRender->SetAlphaTestEnable( false );

	// �`���
	Dst = Math::Rect2DF( toF(m_RenderRect.x), toF(m_RenderRect.y), Size.x, Size.y );

	// �V�[���̐[�x
	Renderer::Shader::ShaderManager::GetPostEffect()->Simple( Dst, m_pRT_DepthNormal );
	Dst.y += Size.y;

	// ���x�}�b�v
	if ( IsVelocityEnable() )
	{
		Src.Set( 0.0f, 0.0f, toF(m_pRT_Velocity->GetOriginalSize().x), toF(m_pRT_Velocity->GetOriginalSize().y) );
		m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_Velocity );
		Dst.y += Size.y;
	}

	// �V���h�E�}�b�v
	if ( IsShadowEnable() && (GetHardwareShadowType() == HW_SHADOW_NONE) )
	{
		Dst = m_RenderRect;
		Dst.x = Dst.x + Dst.w - 64.0f;
		Dst.w = 64.0f;
		Dst.h = 64.0f;
		Src.Set( 0.0f, 0.0f, toF(m_pRT_Shadow->GetOriginalSize().x), toF(m_pRT_Shadow->GetOriginalSize().y) );
		m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_Shadow );
	}

	// HDR
	if ( IsHDREnable() )
	{
		Float x = Size.x;
		Float y = 0.0f;
		Float w = Size.x / 2.0f;
		Float h = Size.y / 2.0f;

		switch ( m_HdrEffect )
		{
		case HDR_EFFECT_BLOOM:
			Dst.Set( x, y, w, h );
			Src.Set( 0.0f, 0.0f, toF(m_pRT_HDR->GetOriginalSize().x), toF(m_pRT_HDR->GetOriginalSize().y) );
			m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_HDR );

			Dst.Set( x + w, y, w, h );
			Src.Set( 0.0f, 0.0f, toF(m_pRT_HDR1_GausB->GetOriginalSize().x), toF(m_pRT_HDR1_GausB->GetOriginalSize().y) );
			m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_HDR1_GausB );

			Dst.Set( x, y + h, w, h );
			Src.Set( 0.0f, 0.0f, toF(m_pRT_HDR2_GausB->GetOriginalSize().x), toF(m_pRT_HDR2_GausB->GetOriginalSize().y) );
			m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_HDR2_GausB );

			Dst.Set( x + w, y + h, w, h );
			Src.Set( 0.0f, 0.0f, toF(m_pRT_HDR3_GausB->GetOriginalSize().x), toF(m_pRT_HDR3_GausB->GetOriginalSize().y) );
			m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_HDR3_GausB );
			break;

		case HDR_EFFECT_CROSS:
			Dst.Set( x, y, w, h );
			Src.Set( 0.0f, 0.0f, toF(m_pRT_HDR->GetOriginalSize().x), toF(m_pRT_HDR->GetOriginalSize().y) );
			m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_HDR );

			Dst.Set( x, y + h, w, h );
			Src.Set( 0.0f, 0.0f, toF(m_pRT_HDR2_GausA->GetOriginalSize().x), toF(m_pRT_HDR2_GausA->GetOriginalSize().y) );
			m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_HDR2_GausA );

			Dst.Set( x + w, y + h, w, h );
			Src.Set( 0.0f, 0.0f, toF(m_pRT_HDR2_GausB->GetOriginalSize().x), toF(m_pRT_HDR2_GausB->GetOriginalSize().y) );
			m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_HDR2_GausB );

			Dst.Set( x, y + h + h, w, h );
			Src.Set( 0.0f, 0.0f, toF(m_pRT_HDR3_GausA->GetOriginalSize().x), toF(m_pRT_HDR3_GausA->GetOriginalSize().y) );
			m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_HDR3_GausA );

			Dst.Set( x + w, y + h + h, w, h );
			Src.Set( 0.0f, 0.0f, toF(m_pRT_HDR3_GausB->GetOriginalSize().x), toF(m_pRT_HDR3_GausB->GetOriginalSize().y) );
			m_pRender->DrawTexture( Dst, 0xFFFFFFFF, Src, m_pRT_HDR3_GausB );
			break;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_Shader::ClearBackground( Bool IsRendering )
{
	if ( m_pTextureBG != NULL )
	{
		Math::Rect2DF Src( 0.0f, 0.0f, toF(m_pTextureBG->GetSize().x), toF(m_pTextureBG->GetSize().y) );
		m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
		if ( IsHDREnable() && IsRendering )
		{
			m_pRender->DrawTexture( m_RenderRect, CColor(127,127,127), Src, m_pTextureBG );
		}
		else
		{
			m_pRender->DrawTexture( m_RenderRect, CColor(255,255,255), Src, m_pTextureBG );
		}
	}
	else
	if ( m_IsClear )
	{
		CColor Color( 0, 0, 0, 0 );
		if ( IsHDREnable() && IsRendering )
		{
			Color.r = (Uint8)(m_ClearColor.x * 127.0f);
			Color.g = (Uint8)(m_ClearColor.y * 127.0f);
			Color.b = (Uint8)(m_ClearColor.z * 127.0f);
		}
		else
		{
			Color.r = (Uint8)(m_ClearColor.x * 255.0f);
			Color.g = (Uint8)(m_ClearColor.y * 255.0f);
			Color.b = (Uint8)(m_ClearColor.z * 255.0f);
		}
		m_pRender->Clear( Color );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_Shader::CreateShadowmap( void )
{
	switch ( m_ShadowType )
	{
	case SHADOW_TYPE_PROJECTION:
		{
			m_pRender->SetDepthBuffer( NULL );

			//------------------------------------------------------------------------
			// PASS 1
			//------------------------------------------------------------------------
			// �^�[�Q�b�g
			m_pRender->SetRenderTarget( m_pRT_Shadow );
			m_pRender->SetDepthBuffer( NULL );
			m_pRender->Clear( 0x00000000 );

			// �V�U�����O
			Math::Rect2DI Rc( 1, 1, m_pRT_Shadow->GetSize().x - 2, m_pRT_Shadow->GetSize().y - 2 );
			m_pRender->SetScissorRect( &Rc );

			// �����_�����O
			Rendering_ShadowProjection( m_pRT_Shadow->GetSize() );

			// �V�U�����O
			m_pRender->SetScissorRect( NULL );

			//------------------------------------------------------------------------
			// �V���h�E�}�b�v
			//------------------------------------------------------------------------
			m_pRender->SetTexture( TEXTURE_STAGE_SHADOW, m_pRT_Shadow );
			m_pRender->SetTextureFilterType( TEXTURE_STAGE_SHADOW, TEXTURE_FILTER_3D_LOW );
		}
		break;

	case SHADOW_TYPE_SHADOWMAP:
		{
			//------------------------------------------------------------------------
			// �p�����[�^�[
			//------------------------------------------------------------------------
			m_ShadowParameter.Set(
				m_fShadowMapPower,
				1.0f - m_fShadowMapPower,
				m_fShadowMapBias,
				0.0f );

			//------------------------------------------------------------------------
			// �^�[�Q�b�g
			//------------------------------------------------------------------------
			m_pRender->SetRenderTarget( m_pRT_Shadow );
			m_pRender->SetDepthBuffer( m_pDS_Shadow );

			//------------------------------------------------------------------------
			// �����_�����O
			//------------------------------------------------------------------------
			Rendering_Shadowmap( m_pRT_Shadow->GetSize() );

			//------------------------------------------------------------------------
			// �V���h�E�}�b�v
			//------------------------------------------------------------------------
			switch ( GetHardwareShadowType() )
			{
			case HW_SHADOW_NONE:
				m_pRender->SetTexture( TEXTURE_STAGE_SHADOW, m_pRT_Shadow );
				m_pRender->SetTextureFilterType( TEXTURE_STAGE_SHADOW, m_pRT_Shadow->IsFilterEnable() ? TEXTURE_FILTER_3D_LOW : TEXTURE_FILTER_DISABLE );
				break;
			case HW_SHADOW_NVIDIA:
				m_pRender->SetTexture( TEXTURE_STAGE_SHADOW, m_pDS_Shadow );
				m_pRender->SetTextureFilterType( TEXTURE_STAGE_SHADOW, TEXTURE_FILTER_3D_LOW );
				break;
			case HW_SHADOW_ATI:
				m_pRender->SetTexture( TEXTURE_STAGE_SHADOW, m_pDS_Shadow );
				m_pRender->SetTextureFilterType( TEXTURE_STAGE_SHADOW, TEXTURE_FILTER_3D_LOW );
				break;
			}
		}
		break;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_Shader::Rendering_ShadowProjection( Math::Point2DI Size )
{
	Renderer::Shader::ShaderVariable *pVariable = Renderer::Shader::ShaderManager::GetShaderVariable();
	Renderer::Shader::ShaderEffect *pEffect = Renderer::Shader::ShaderManager::GetShaderEffect();
	CCustomizedSceneRenderObject *pObj;

	Sint32 Polygon = 0;

	// �J�����̋t�ϊ�
	Math::Matrix mViewInverse;
	mViewInverse.Transpose( m_mShadowView );
	pVariable->SetViewInverse( &mViewInverse );

	//================================================================================================
	// �X�v���C�g�X�V
	//================================================================================================
	for ( Sint32 i = 0; i < PROJECTION_SHADOW_PRIORITY_MAX; i++ )
	{
		m_pParticleShadow[i]->Begin();
	}

	// UV
	Math::Rect2DF Src( 0.0f, 0.0f, toF(m_pTextureShadowProjection->GetOriginalSize().x), toF(m_pTextureShadowProjection->GetOriginalSize().y) );

	// �e�𗎂Ƃ��I�u�W�F�N�g��`��
	pObj = m_pObjectList[ID_ALPHA_DISABLE];
	while ( pObj != NULL )
	{
		if ( pObj->ProjectionShadowType == PROJECTION_SHADOW_DROP_SIMPLE )
		{
			Math::Point2DF fSize( pObj->fShadowRadius, pObj->fShadowRadius );
			m_pParticleShadow[pObj->ProjectionShadowPriority]->Draw( pObj->pActor->GetCenter(), fSize, Src, CColor(255,255,255,255) );
		}

		// ��
		pObj = pObj->pNext;
	}

	for ( Sint32 i = 0; i < PROJECTION_SHADOW_PRIORITY_MAX; i++ )
	{
		m_pParticleShadow[i]->End();
	}

	//--------------------------------------------------
	// �����_�����O�X�e�[�g�X�V
	//--------------------------------------------------
	m_pRender->SetDepthWriteEnable( false );
	m_pRender->SetDepthTestEnable( false );

	// �`�惂�[�h
	m_pRender->SetDrawType( DRAW_TYPE_ADD );

	// �A���t�@�e�X�g
	m_pRender->SetAlphaTestEnable( true );
	m_pRender->SetAlphaBoundary( 0 );

	// �J�����O
	m_pRender->SetCullType( CULL_NONE );

	//================================================================================================
	// �ۉe��`��
	//================================================================================================
	// �e�N�j�b�N
	pEffect->SetTechnique( TECHNIQUE_EFFECT_SHADOW_PROJECTION, false );

	// WorldViewProjection
	pVariable->SetWorldViewProjection( &m_mShadowViewProj );

	// �p�����[�^�[�X�V
	pVariable->Update();

	// �p�X�J�n
	pEffect->Begin();

	// �����_�����O
	for ( Sint32 i = 0; i < PROJECTION_SHADOW_PRIORITY_MAX; i++ )
	{
		// �s�N�Z���}�X�N
		const Bool *pTbl = g_vProjectionWriteMaskTbl[i];
		m_pRender->SetColorWriteEnable( pTbl[3], pTbl[0], pTbl[1], pTbl[2] );
		// �����_�����O
		m_pRender->SetTexture( TEXTURE_STAGE_COLOR, m_pTextureShadowProjection );
		((CParticleActor*)m_pActorShadow[i])->RenderingDirect();
	}

	// �p�X�I��
	pEffect->End();

	//================================================================================================
	// ���f���`��̉e�𗎂Ƃ��I�u�W�F�N�g��`��
	//================================================================================================

	// �e�N�X�`��
	m_pRender->SetTexture( TEXTURE_STAGE_LIGHT, NULL );

	// �`��
	for ( Sint32 i = ID_ALPHA_DISABLE; i <= ID_ALPHA_ENABLE; i++ )
	{
		pObj = m_pObjectList[i];
		while ( pObj != NULL )
		{
			if ( pObj->ProjectionShadowType == PROJECTION_SHADOW_DROP_SHAPE )
			{
				if ( pObj->ProjectionShadowPriority != PROJECTION_SHADOW_PRIORITY_0 )
				{
					// ShadowWorldViewProjection
					pVariable->SetShadowWorldViewProjection( &pObj->mShadowWorldViewProjection );

					// �{�[������H
					Sint32 BoneCnt = pObj->pActor->GetBoneCount();
					if ( BoneCnt > 0 )
					{
						// BoneMatrixArray
						pVariable->SetBoneMatrixArray( pObj->pActor->GetBoneMatrixArray(), BoneCnt );
					}

					// �p�����[�^�[�X�V
					pVariable->Update();

					// �e�N�j�b�N
					switch ( pObj->pActor->GetTransformType() )
					{
					case TRANSFORM_TYPE_MODEL:
						pEffect->SetTechnique( pObj->pActor->IsSupportVertexTexture() ? TECHNIQUE_EFFECT_SHADOW_PROJECTION_SHAPE_TEXTURE : TECHNIQUE_EFFECT_SHADOW_PROJECTION_SHAPE, pObj->pActor->IsSupportVertexBone() );
						break;
					case TRANSFORM_TYPE_BILLBOARD:
						pEffect->SetTechnique( TECHNIQUE_EFFECT_SHADOW_PROJECTION, false );
						break;
					}

					// �p�X�J�n
					pEffect->Begin();

					// �s�N�Z���}�X�N
					const Bool *pTbl = g_vProjectionWriteMaskTbl[pObj->ProjectionShadowPriority];
					m_pRender->SetColorWriteEnable( pTbl[3], pTbl[0], pTbl[1], pTbl[2] );

					// �X�g���[��
					pObj->pActor->SetStreamSource( m_pRender );

					// �����_�����O
					Sint32 MtrlCnt = pObj->pActor->GetMaterialCount();
					for ( Sint32 j = 0; j < MtrlCnt; j++ )
					{
						CSceneActorMaterial &Mtrl = pObj->pActor->GetSceneRenderMaterial( j );

						// �e�N�X�`��
						m_pRender->SetTexture( TEXTURE_STAGE_COLOR, Mtrl.GetTexture( TEXTURE_STAGE_COLOR ) );

						// MaterialColor
						pVariable->SetMaterialColor( Mtrl.GetDiffuseColor() );

						// Texture Offset
						pVariable->SetTextureOffset( Mtrl.GetTextureOffset() );

						// �����_�����O�X�e�[�g�X�V
						m_pRender->SetDepthWriteEnable( Mtrl.GetZWriteEnable() );
						m_pRender->SetDepthTestEnable( Mtrl.GetZTestEnable() );

						// �A���t�@�e�X�g
						m_pRender->SetAlphaTestEnable( Mtrl.GetAlphaTestEnable() );
						m_pRender->SetAlphaBoundary( Mtrl.GetAlphaBoundary() );

						// �J�����O
						m_pRender->SetCullType( Mtrl.GetCullType() );

						Polygon += pObj->pActor->Rendering( j, m_pRender );
					}

					// �p�X�I��
					pEffect->End();
				}
			}

			// ��
			pObj = pObj->pNext;
		}
	}

	//--------------------------------------------------
	// �`�搔
	//--------------------------------------------------
	m_pCore->DrawPolygon( Polygon );

	//--------------------------------------------------
	// �A���t�@���C�gON
	//--------------------------------------------------
	m_pRender->SetColorWriteEnable( true, true, true, true );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_Shader::Rendering_Shadowmap( Math::Point2DI Size )
{
	Sint32 Polygon = 0;

	//--------------------------------------------------
	// �F�X
	//--------------------------------------------------
	if ( GetHardwareShadowType() != HW_SHADOW_NONE )
	{
		m_pRender->SetColorWriteEnable( false, false, false, false );
		ClearDepthBuffer();
	}
	else
	{
		m_pRender->Clear( 0xFFFFFFFF );
		ClearDepthBuffer();
	}

	//--------------------------------------------------
	// �V�U�����O
	//--------------------------------------------------
	Math::Rect2DI Rc( 1, 1, Size.x - 2, Size.y - 2 );
	m_pRender->SetScissorRect( &Rc );

	//--------------------------------------------------
	// �X�e�[�g
	//--------------------------------------------------
	// �����_�����O�X�e�[�g�X�V
	m_pRender->SetDepthWriteEnable( true );
	m_pRender->SetDepthTestEnable( true );

	// �A���t�@�e�X�g
	m_pRender->SetAlphaTestEnable( false );

	// �`�惂�[�h
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );

	//================================================================================================
	// ���ʕϐ��p
	//================================================================================================
	Renderer::Shader::ShaderVariable *pVariable = Renderer::Shader::ShaderManager::GetShaderVariable();

	//================================================================================================
	// �I�u�W�F�N�g�����_�����O
	//================================================================================================
	CCustomizedSceneRenderObject *pObj = m_pObjectList[ID_ALPHA_DISABLE];
	while ( pObj != NULL )
	{
		Renderer::Shader::ShaderEffect *pEffect = Renderer::Shader::ShaderManager::GetShaderEffect();

		// �e�N�j�b�N
		pEffect->SetTechnique( TECHNIQUE_EFFECT_SHADOWMAP, pObj->pActor->IsSupportVertexBone() );

		// WorldViewProjection
		pVariable->SetWorldViewProjection( &pObj->mWorldViewProjection );
		// ShadowWorldViewProjection
		pVariable->SetShadowWorldViewProjection( &pObj->mShadowWorldViewProjection );
		// �{�[������H
		Sint32 BoneCnt = pObj->pActor->GetBoneCount();
		if ( BoneCnt > 0 )
		{
			// BoneMatrixArray
			pVariable->SetBoneMatrixArray( pObj->pActor->GetBoneMatrixArray(), BoneCnt );
		}

		// �p�����[�^�[�X�V
		pVariable->Update();

		// �p�X�J�n
		pEffect->Begin();

		// �X�g���[��
		pObj->pActor->SetStreamSource( m_pRender );

		// �}�e���A���P�ʂ�
		Sint32 MtrlCnt = pObj->pActor->GetMaterialCount();
		for ( Sint32 i = 0; i < MtrlCnt; i++ )
		{
			CSceneActorMaterial &Mtrl = pObj->pActor->GetSceneRenderMaterial( i );

			// �J�����O
			if ( Mtrl.GetCullType() == CULL_FRONT )
			{
				m_pRender->SetCullType( CULL_BACK );
			}
			ef ( Mtrl.GetCullType() == CULL_BACK )
			{
				m_pRender->SetCullType( CULL_FRONT );
			}
			else
			{
				m_pRender->SetCullType( CULL_NONE );
			}

			// �����_�����O
			Polygon += pObj->pActor->Rendering( i, m_pRender );
		}

		// �p�X�I��
		pEffect->End();

		// ��
		pObj = pObj->pNext;
	}

	//--------------------------------------------------
	// �`�搔
	//--------------------------------------------------
	m_pCore->DrawPolygon( Polygon );

	//--------------------------------------------------
	// �V�U�����O
	//--------------------------------------------------
	m_pRender->SetScissorRect( NULL );

	//--------------------------------------------------
	// �F��������
	//--------------------------------------------------
	if ( GetHardwareShadowType() != HW_SHADOW_NONE )
	{
		m_pRender->SetColorWriteEnable( true, true, true, true );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_Shader::Rendering_Velocity( void )
{
	if ( m_pObjectList[ID_ALPHA_DISABLE] == NULL ) return;

	Sint32 Polygon = 0;

	//--------------------------------------------------
	// �����_�����O�X�e�[�g
	//--------------------------------------------------
	// �A���t�@�e�X�g
	m_pRender->SetAlphaTestEnable( false );

	// �����_�����O�X�e�[�g�X�V
	m_pRender->SetDepthWriteEnable( true );
	m_pRender->SetDepthTestEnable( true );

	// �`�惂�[�h
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );

	// �J�����O
	m_pRender->SetCullType( CULL_NONE );

	// ����
	m_pRender->Start3D();

	//================================================================================================
	// ���ʕϐ��p
	//================================================================================================
	Renderer::Shader::ShaderVariable *pVariable = Renderer::Shader::ShaderManager::GetShaderVariable();

	// Projection
	pVariable->SetProjection( &m_mProjection );

	//================================================================================================
	// �I�u�W�F�N�g�����_�����O
	//================================================================================================
	CCustomizedSceneRenderObject *pObj = m_pObjectList[ID_ALPHA_DISABLE];
	while ( pObj != NULL )
	{
		// �u���[
		Bool IsLight = (pObj->MotionBlurLevel == MOTION_BLUR_LIGHT) || !pObj->pActor->IsSupportVertexNormal();

		// �V�F�[�_�[
		Renderer::Shader::ShaderEffect *pEffect = Renderer::Shader::ShaderManager::GetShaderEffect();

		// �e�N�j�b�N
		pEffect->SetTechnique( IsLight ? TECHNIQUE_EFFECT_VELOCITY_SIMPLE : TECHNIQUE_EFFECT_VELOCITY, pObj->pActor->IsSupportVertexBone() );

		if ( IsLight )
		{
			// WorldViewProjection
			pVariable->SetWorldViewProjection( &pObj->mWorldViewProjection );

			// WorldViewProjectionPrev
			pVariable->SetWorldViewProjectionPrev( &pObj->mWorldViewProjectionPrev );
		}
		else
		{
			// WorldView
			pVariable->SetWorldView( &pObj->mWorldView );

			// WorldViewPrev
			pVariable->SetWorldViewPrev( &pObj->mWorldViewPrev );
		}

		// �{�[������H
		Sint32 BoneCnt = pObj->pActor->GetBoneCount();
		if ( BoneCnt > 0 )
		{
			// BoneMatrixArray
			pVariable->SetBoneMatrixArray( pObj->pActor->GetBoneMatrixArray(), BoneCnt );
			// BoneMatrixArray
			pVariable->SetBoneMatrixArrayPrev( pObj->pActor->GetBoneMatrixArrayPrev(), BoneCnt );
		}

		// �p�����[�^�[�X�V
		pVariable->Update();

		// �p�X�J�n
		pEffect->Begin();

		// �X�g���[��
		pObj->pActor->SetStreamSource( m_pRender );

		// �����_�����O
		Polygon += pObj->pActor->Rendering_Velocity( m_pRender );

		// �p�X�I��
		pEffect->End();

		// ��
		pObj = pObj->pNext;
	}

	//--------------------------------------------------
	// �`�搔
	//--------------------------------------------------
	m_pCore->DrawPolygon( Polygon );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_Shader::Rendering_DepthNormal( void )
{
	if ( m_pObjectList[ID_ALPHA_DISABLE] == NULL ) return;

	Sint32 Polygon = 0;
	Math::Vector4D vPositionTbl[4];
	Math::Vector4D vColorTbl[4];
	Math::Matrix mTemp;
	Math::Vector4D vTemp;

	//--------------------------------------------------
	// �X�e�[�g
	//--------------------------------------------------
	// �A���t�@�e�X�g
	m_pRender->SetAlphaTestEnable( true );
	m_pRender->SetAlphaBoundary( 0 );

	// �`�惂�[�h
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );

	// ����
	m_pRender->Start3D();

	Bool IsToon = IsToonEnable();

	//================================================================================================
	// ���ʕϐ��p
	//================================================================================================
	Renderer::Shader::ShaderVariable *pVariable = Renderer::Shader::ShaderManager::GetShaderVariable();

	// DepthParameter
	pVariable->SetDepthParameter( m_DepthParameter );

	//================================================================================================
	// �I�u�W�F�N�g�����_�����O
	//================================================================================================
	CCustomizedSceneRenderObject *pObj = m_pObjectList[ID_ALPHA_DISABLE];
	while ( pObj != NULL )
	{
		Renderer::Shader::ShaderEffect *pEffect = Renderer::Shader::ShaderManager::GetShaderEffect();

		// �e�N�j�b�N
		pEffect->SetTechnique( IsToon ? TECHNIQUE_EFFECT_DEPTH_NORMAL : TECHNIQUE_EFFECT_DEPTH, pObj->pActor->IsSupportVertexBone() );

		// World
		pVariable->SetWorld( &pObj->pActor->GetWorldMatrix() );

		// WorldViewProjection
		pVariable->SetWorldViewProjection( &pObj->mWorldViewProjection );

		// �{�[������H
		Sint32 BoneCnt = pObj->pActor->GetBoneCount();
		if ( BoneCnt > 0 )
		{
			// BoneMatrixArray
			pVariable->SetBoneMatrixArray( pObj->pActor->GetBoneMatrixArray(), BoneCnt );
		}

		// �p�����[�^�[�X�V
		pVariable->Update();

		// �f�[�^�X�g���[��
		pObj->pActor->SetStreamSource( m_pRender );

		// �}�e���A���P�ʂ�
		Sint32 MtrlCnt = pObj->pActor->GetMaterialCount();
		for ( Sint32 j = 0; j < MtrlCnt; j++ )
		{
			CSceneActorMaterial &Mtrl = pObj->pActor->GetSceneRenderMaterial( j );

			// �����_�����O�X�e�[�g�X�V
			m_pRender->SetDepthWriteEnable( Mtrl.GetZWriteEnable() );
			m_pRender->SetDepthTestEnable( Mtrl.GetZTestEnable() );

			// �J�����O
			m_pRender->SetCullType( Mtrl.GetCullType() );

			// �p�X�J�n
			pEffect->Begin();

			// �����_�����O
			Polygon += pObj->pActor->Rendering( j, m_pRender );

			// �p�X�I��
			pEffect->End();
		}

		// ��
		pObj = pObj->pNext;
	}

	//--------------------------------------------------
	// �`�搔
	//--------------------------------------------------
	m_pCore->DrawPolygon( Polygon );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_Shader::Rendering_AlphaDisable( void )
{
	if ( (m_pObjectList[ID_SKYDOOM] == NULL) && (m_pObjectList[ID_ALPHA_DISABLE] == NULL) ) return;

	Renderer::Shader::ShaderVariable *pVariable = Renderer::Shader::ShaderManager::GetShaderVariable();

	Uint32 ActiveShaderID = 0xFFFFFFFF;
	Renderer::Shader::CShader *pActiveShader = NULL;
	Sint32 Polygon = 0;
	Math::Vector4D vPositionTbl[4];
	Math::Vector4D vColorTbl[4];
	Math::Matrix mTemp;
	Math::Vector4D vTemp;
	Renderer::ITexture *pTex;

	// ����
	m_pRender->Start3D();

	//--------------------------------------------------
	// �V�[�����
	//--------------------------------------------------
	Bool IsShadow = IsShadowEnable();
	Bool IsToon = IsToonEnable();
	Bool IsFog = IsFogEnable();

	//================================================================================================
	// ���ʕϐ��p
	//================================================================================================

	// FogParameter
	if ( IsFog )
	{
		pVariable->SetFogParameter( m_FogParameter );
		pVariable->SetFogColor( m_FogColor );
	}

	// ShadowMapParameter
	if ( IsShadow )
	{
		pVariable->SetShadowMapParameter( m_ShadowParameter );
		pVariable->SetShadowMapOffset( m_ShadowMapOffset );
		if ( GetHardwareShadowType() == HW_SHADOW_ATI )
		{
			m_pRender->SetHardwareShadowATI( true, GetShadingType() == SHADING_TYPE_NORMAL );
		}
	}

	// ToonParameter
	if ( IsToon )
	{
		pVariable->SetToonParameter( m_vToonRenderParameter );
	}

	// DepthParameter
	pVariable->SetDepthParameter( m_DepthParameter );

	//--------------------------------------------------
	// ���C�g
	//--------------------------------------------------
	// AmbientLightColorSky
	pVariable->SetLightParameter_AmbientColorSky( m_vLightColor[LIGHT_AMBIENT_SKY] );

	// AmbientLightColorEarth
	pVariable->SetLightParameter_AmbientColorEarth( m_vLightColor[LIGHT_AMBIENT_EARTH] );

	// DirectionalLightColor
	pVariable->SetDirectionalLightColor( m_vLightColor[LIGHT_DIRECTION] );

	//================================================================================================
	// �I�u�W�F�N�g�����_�����O
	//================================================================================================
	for ( Sint32 i = 0; i <= ID_ALPHA_DISABLE; i++ )
	{
		CCustomizedSceneRenderObject *pObj = m_pObjectList[i];
		while ( pObj != NULL )
		{
			// WorldViewProjection
			pVariable->SetWorldViewProjection( &pObj->mWorldViewProjection );

			// �V���h�E�}�b�v����H
			if ( IsShadow )
			{
				// ShadowWorldViewProjection
				mTemp.Multiply( pObj->mShadowWorldViewProjection, m_mShadowOffset );
				pVariable->SetShadowWorldViewProjection( &mTemp );
				// �p�����[�^�[
				if ( pObj->ProjectionShadowType != PROJECTION_SHADOW_DISABLE )
				{
					pVariable->SetShadowMapParameter( g_vProjectionReadMaskTbl[pObj->ProjectionShadowPriority] );
				}
			}

			// CameraPosition
			if ( pObj->pActor->GetParallaxEnable() || pObj->pActor->GetSpecularEnable() || pObj->pActor->GetEnvironmentEnable() )
			{
				vTemp.TransformCoord( m_Camera.Position(), pObj->pActor->GetWorldInverseMatrix() );
				pVariable->SetCameraPosition( vTemp );
			}

			// World
			if ( pObj->pActor->GetEnvironmentEnable() )
			{
				pVariable->SetWorld( &pObj->pActor->GetWorldMatrix() );
			}

			// ���C�g����H
			if ( pObj->pActor->IsSupportVertexNormal() )
			{
				// DirectionalLightDirection
				pVariable->SetDirectionalLightDirection( pObj->vLightDiection );
				// PointLight Count
				pVariable->SetPointLightCount( pObj->PointLightCount );
				// �|�C���g���C�g����H
				if ( pObj->PointLightCount > 0 )
				{
					// PointLightPosition
					pVariable->SetPointLightPosition( pObj->vPointLightPositionTbl, pObj->PointLightCount );
					pVariable->SetPointLightColor( pObj->vPointLightColorTbl, pObj->PointLightCount );
				}
			}

			// �{�[������H
			Sint32 BoneCnt = pObj->pActor->GetBoneCount();
			if ( BoneCnt > 0 )
			{
				// BoneMatrixArray
				pVariable->SetBoneMatrixArray( pObj->pActor->GetBoneMatrixArray(), BoneCnt );
			}

			// �f�[�^�X�g���[��
			pObj->pActor->SetStreamSource( m_pRender );

			// �}�e���A���P�ʂ�
			Sint32 MtrlCnt = pObj->pActor->GetMaterialCount();
			for ( Sint32 j = 0; j < MtrlCnt; j++ )
			{
				CSceneActorMaterial &Mtrl = pObj->pActor->GetSceneRenderMaterial( j );
				Renderer::Shader::CShader *pShader = (Renderer::Shader::CShader*)Mtrl.GetShader();

				if ( pShader == NULL ) continue;

				// �V�F�[�_�[�ύX
				if ( ActiveShaderID != pShader->GetID() )
				{
					ActiveShaderID = pShader->GetID();
					// �Â��̏I��
					if ( pActiveShader != NULL )
					{
						pActiveShader->SimpleEnd();
					}
					// �V�����̊J�n
					pActiveShader = pShader;
					pActiveShader->SimpleBegin();
				}

				Math::Vector3D vBrightness = pObj->vBrightness;

				// �J���[�e�N�X�`��
				pTex = Mtrl.GetTexture( TEXTURE_STAGE_COLOR );
				m_pRender->SetTexture( TEXTURE_STAGE_COLOR, pTex );

				// ���C�g�}�b�v
				if ( !IsToon )
				{
					pTex = Mtrl.GetTexture( TEXTURE_STAGE_LIGHT );
					m_pRender->SetTexture( TEXTURE_STAGE_LIGHT, pTex );
					if ( pTex != NULL )
					{
						vBrightness *= 2.0f;
					}
				}

				// ���}�b�v
				if ( !IsToon )
				{
					pTex = Mtrl.GetTexture( TEXTURE_STAGE_ENVIRONMENT );
					m_pRender->SetTexture( TEXTURE_STAGE_ENVIRONMENT, pTex );
					if ( pTex != NULL )
					{
						vBrightness *= 2.0f;
					}
				}

				// �o���v�}�b�v
				if ( Mtrl.GetBumpType() != BUMP_TYPE_NONE )
				{
					pTex = Mtrl.GetTexture( TEXTURE_STAGE_NORMAL );
					m_pRender->SetTexture( TEXTURE_STAGE_NORMAL, pTex );

					// ParallaxDepth
					pVariable->SetParallaxDepth( Mtrl.GetParallaxDepth() );
				}

				// �X�y�L�����}�b�v
				if ( Mtrl.GetSpecularType() != SPECULAR_TYPE_NONE )
				{
					pTex = Mtrl.GetTexture( TEXTURE_STAGE_SPECULAR );
					m_pRender->SetTexture( TEXTURE_STAGE_SPECULAR, pTex );

					// SpecularColor
					pVariable->SetSpecularColor( Mtrl.GetSpecularColor() );
					// Specular Refractive
					pVariable->SetRefractive( Mtrl.GetSpecularRefractive() );
					// Specular Roughly
					pVariable->SetRoughly( Mtrl.GetSpecularRoughly() );
				}

				// MaterialColor
				vTemp.x = Mtrl.GetDiffuseColor().x * vBrightness.x;
				vTemp.y = Mtrl.GetDiffuseColor().y * vBrightness.y;
				vTemp.z = Mtrl.GetDiffuseColor().z * vBrightness.z;
				vTemp.w = Mtrl.GetDiffuseColor().w;
				pVariable->SetMaterialColor( vTemp );

				// EmissiveColor
				pVariable->SetEmissiveColor( Mtrl.GetEmissiveColor() );

				// Texture Offset
				pVariable->SetTextureOffset( Mtrl.GetTextureOffset() );

				// �p�����[�^�[�X�V
				pVariable->Update();

				// �����_�����O�X�e�[�g�X�V
				m_pRender->SetDepthWriteEnable( Mtrl.GetZWriteEnable() );
				m_pRender->SetDepthTestEnable( Mtrl.GetZTestEnable() );

				// �A���t�@�e�X�g
				m_pRender->SetAlphaTestEnable( Mtrl.GetAlphaTestEnable() );
				m_pRender->SetAlphaBoundary( Mtrl.GetAlphaBoundary() );

				// �J�����O
				m_pRender->SetCullType( Mtrl.GetCullType() );

				// �`�惂�[�h
				m_pRender->SetDrawType( Mtrl.GetDrawType() );

				// �p�X�J�n
				pActiveShader->BeginPass( 0 );
				Polygon += pObj->pActor->Rendering( j, m_pRender );
				pActiveShader->EndPass();
			}
		
			// ��
			pObj = pObj->pNext;
		}
	}

	// �I���
	if ( pActiveShader != NULL )
	{
		pActiveShader->SimpleEnd();
	}

	if ( IsShadow )
	{
		if ( GetHardwareShadowType() == HW_SHADOW_ATI )
		{
			m_pRender->SetHardwareShadowATI( false, false );
		}
	}

	//--------------------------------------------------
	// �`�搔
	//--------------------------------------------------
	m_pCore->DrawPolygon( Polygon );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_Shader::Rendering_AlphaEnable( void )
{
	if ( m_pObjectList[ID_ALPHA_ENABLE] == NULL ) return;

	Renderer::Shader::ShaderVariable *pVariable = Renderer::Shader::ShaderManager::GetShaderVariable();

	Uint32 ActiveShaderID = 0xFFFFFFFF;
	Renderer::Shader::CShader *pActiveShader = NULL;
	Sint32 Polygon = 0;
	Math::Vector4D vPositionTbl[4];
	Math::Vector4D vColorTbl[4];
	Math::Matrix mTemp;
	Math::Vector4D vTemp;
	Renderer::ITexture *pTex;

	//--------------------------------------------------
	// ���ʃp�����[�^�[
	//--------------------------------------------------
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_TOON, TEXTURE_FILTER_2D );
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_DEPTH, TEXTURE_FILTER_2D );
	m_pRender->SetTexture( TEXTURE_STAGE_DEPTH, m_pRT_DepthNormal );

	//--------------------------------------------------
	// �V���h�E�}�b�vON/OFF
	//--------------------------------------------------
	Bool IsShadow = IsShadowEnable();
	Bool IsToon = IsToonEnable();
	Bool IsFog = IsFogEnable();

	//--------------------------------------------------
	// ����
	//--------------------------------------------------
	m_pRender->Start3D();

	//--------------------------------------------------
	// �A���t�@��������OFF
	//--------------------------------------------------
	m_pRender->SetColorWriteEnable( false, true, true, true );

	//================================================================================================
	// ���ʕϐ��p
	//================================================================================================

	// FogParameter
	if ( IsFog )
	{
		pVariable->SetFogParameter( m_FogParameter );
		pVariable->SetFogColor( m_FogColor );
	}

	// ShadowMapParameter
	if ( IsShadow )
	{
		pVariable->SetShadowMapParameter( m_ShadowParameter );
		pVariable->SetShadowMapOffset( m_ShadowMapOffset );
		if ( GetHardwareShadowType() == HW_SHADOW_ATI )
		{
			m_pRender->SetHardwareShadowATI( true, GetShadingType() == SHADING_TYPE_NORMAL );
		}
	}

	// ToonParameter
	if ( IsToon )
	{
		pVariable->SetToonParameter( m_vToonRenderParameter );
	}

	// DepthParameter
	pVariable->SetDepthParameter( m_DepthParameter );

	// SoftParticleScale
	pVariable->SetSoftParticleScale( m_fSoftParticleScale );

	// �J�����̋t�ϊ�
	Math::Matrix mViewInverse;
	mViewInverse.Transpose( m_Camera.WorldToView() );
	pVariable->SetViewInverse( &mViewInverse );

	//--------------------------------------------------
	// ���C�g
	//--------------------------------------------------
	// AmbientLightColorSky
	pVariable->SetLightParameter_AmbientColorSky( m_vLightColor[LIGHT_AMBIENT_SKY] );

	// AmbientLightColorEarth
	pVariable->SetLightParameter_AmbientColorEarth( m_vLightColor[LIGHT_AMBIENT_EARTH] );

	// DirectionalLightColor
	pVariable->SetDirectionalLightColor( m_vLightColor[LIGHT_DIRECTION] );

	//================================================================================================
	// �I�u�W�F�N�g�����_�����O
	//================================================================================================
	CCustomizedSceneRenderObject *pObj = m_pObjectList[ID_ALPHA_ENABLE];
	while ( pObj != NULL )
	{
		// PointLight Count
		pVariable->SetPointLightCount( pObj->PointLightCount );

		// WorldViewProjection
		pVariable->SetWorldViewProjection( &pObj->mWorldViewProjection );

		// �V���h�E�}�b�v����H
		if ( IsShadow )
		{
			// ShadowWorldViewProjection
			mTemp.Multiply( pObj->mShadowWorldViewProjection, m_mShadowOffset );
			pVariable->SetShadowWorldViewProjection( &mTemp );
			// �p�����[�^�[
			if ( pObj->ProjectionShadowType != PROJECTION_SHADOW_DISABLE )
			{
				pVariable->SetShadowMapParameter( g_vProjectionReadMaskTbl[pObj->ProjectionShadowPriority] );
			}
		}

		// CameraPosition
		if ( pObj->pActor->GetParallaxEnable() || pObj->pActor->GetSpecularEnable() || pObj->pActor->GetEnvironmentEnable() )
		{
			vTemp.TransformCoord( m_Camera.Position(), pObj->pActor->GetWorldInverseMatrix() );
			pVariable->SetCameraPosition( vTemp );
		}

		// World
		if ( pObj->pActor->GetEnvironmentEnable() )
		{
			pVariable->SetWorld( &pObj->pActor->GetWorldMatrix() );
		}

		// ���C�g����H
		if ( pObj->pActor->IsSupportVertexNormal() )
		{
			// DirectionalLightDirection
			pVariable->SetDirectionalLightDirection( pObj->vLightDiection );
			// �|�C���g���C�g����H
			if ( pObj->PointLightCount > 0 )
			{
				// PointLightPosition & PointLightColor
				pVariable->SetPointLightPosition( pObj->vPointLightPositionTbl, pObj->PointLightCount );
				pVariable->SetPointLightColor( pObj->vPointLightColorTbl, pObj->PointLightCount );
			}
		}

		// �{�[������H
		Sint32 BoneCnt = pObj->pActor->GetBoneCount();
		if ( BoneCnt > 0 )
		{
			// BoneMatrixArray
			pVariable->SetBoneMatrixArray( pObj->pActor->GetBoneMatrixArray(), BoneCnt );
		}

		// �f�[�^�X�g���[��
		pObj->pActor->SetStreamSource( m_pRender );

		// �}�e���A���P�ʂ�
		Sint32 MtrlCnt = pObj->pActor->GetMaterialCount();
		for ( Sint32 j = 0; j < MtrlCnt; j++ )
		{
			CSceneActorMaterial &Mtrl = pObj->pActor->GetSceneRenderMaterial( j );
			Renderer::Shader::CShader *pShader = (Renderer::Shader::CShader*)Mtrl.GetShader();

			if ( pShader == NULL ) continue;

			// �V�F�[�_�[�ύX
			if ( ActiveShaderID != pShader->GetID() )
			{
				ActiveShaderID = pShader->GetID();
				// �Â��̏I��
				if ( pActiveShader != NULL )
				{
					pActiveShader->SimpleEnd();
				}
				// �V�����̊J�n
				pActiveShader = pShader;
				pActiveShader->SimpleBegin();
			}

			Math::Vector3D vBrightness = pObj->vBrightness;

			// �J���[�e�N�X�`��
			pTex = Mtrl.GetTexture( TEXTURE_STAGE_COLOR );
			m_pRender->SetTexture( TEXTURE_STAGE_COLOR, pTex );

			// ���C�g�}�b�v
			if ( !IsToon )
			{
				pTex = Mtrl.GetTexture( TEXTURE_STAGE_LIGHT );
				m_pRender->SetTexture( TEXTURE_STAGE_LIGHT, pTex );
				if ( pTex != NULL )
				{
					vBrightness *= 2.0f;
				}
			}

			// ���}�b�v
			if ( !IsToon )
			{
				pTex = Mtrl.GetTexture( TEXTURE_STAGE_ENVIRONMENT );
				m_pRender->SetTexture( TEXTURE_STAGE_ENVIRONMENT, pTex );
				if ( pTex != NULL )
				{
					vBrightness *= 2.0f;
				}
			}

			// �o���v�}�b�v
			if ( Mtrl.GetBumpType() != BUMP_TYPE_NONE )
			{
				pTex = Mtrl.GetTexture( TEXTURE_STAGE_NORMAL );
				m_pRender->SetTexture( TEXTURE_STAGE_NORMAL, pTex );

				// ParallaxDepth
				pVariable->SetParallaxDepth( Mtrl.GetParallaxDepth() );
			}

			// �X�y�L�����}�b�v
			if ( Mtrl.GetSpecularType() != SPECULAR_TYPE_NONE )
			{
				pTex = Mtrl.GetTexture( TEXTURE_STAGE_SPECULAR );
				m_pRender->SetTexture( TEXTURE_STAGE_SPECULAR, pTex );

				// SpecularColor
				pVariable->SetSpecularColor( Mtrl.GetSpecularColor() );
				// Specular Refractive
				pVariable->SetRefractive( Mtrl.GetSpecularRefractive() );
				// Specular Roughly
				pVariable->SetRoughly( Mtrl.GetSpecularRoughly() );
			}

			// MaterialColor
			vTemp.x = Mtrl.GetDiffuseColor().x * vBrightness.x;
			vTemp.y = Mtrl.GetDiffuseColor().y * vBrightness.y;
			vTemp.z = Mtrl.GetDiffuseColor().z * vBrightness.z;
			vTemp.w = Mtrl.GetDiffuseColor().w;
			pVariable->SetMaterialColor( vTemp );

			// EmissiveColor
			pVariable->SetEmissiveColor( Mtrl.GetEmissiveColor() );

			// Texture Offset
			pVariable->SetTextureOffset( Mtrl.GetTextureOffset() );

			// �p�����[�^�[�X�V
			pVariable->Update();

			// �����_�����O�X�e�[�g�X�V
			m_pRender->SetDepthWriteEnable( Mtrl.GetZWriteEnable() );
			m_pRender->SetDepthTestEnable( Mtrl.GetZTestEnable() );

			// �A���t�@�e�X�g
			m_pRender->SetAlphaTestEnable( Mtrl.GetAlphaTestEnable() );
			m_pRender->SetAlphaBoundary( Mtrl.GetAlphaBoundary() );

			// �J�����O
			m_pRender->SetCullType( Mtrl.GetCullType() );

			// �`�惂�[�h
			m_pRender->SetDrawType( Mtrl.GetDrawType() );

			// �����_�����O
			pActiveShader->BeginPass( 0 );
			Polygon += pObj->pActor->Rendering( j, m_pRender );
			pActiveShader->EndPass();
		}

		// ��
		pObj = pObj->pNext;
	}

	// �I���
	if ( pActiveShader != NULL )
	{
		pActiveShader->SimpleEnd();
	}

	if ( IsShadow )
	{
		if ( GetHardwareShadowType() == HW_SHADOW_ATI )
		{
			m_pRender->SetHardwareShadowATI( false, false );
		}
	}

	//--------------------------------------------------
	// �A���t�@�������݂���
	//--------------------------------------------------
	m_pRender->SetColorWriteEnable( true, true, true, true );

	//--------------------------------------------------
	// �`�搔
	//--------------------------------------------------
	m_pCore->DrawPolygon( Polygon );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneManager_Shader::CreateRenderTargetBuffer( void )
{
	//-----------------------------------------------------------------------
	// �ŏI�C���[�W
	//-----------------------------------------------------------------------
	m_pRT_Final = m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y, FORMAT_TARGET_UCHAR4 );

	//-----------------------------------------------------------------------
	// �[�x�o�b�t�@
	//-----------------------------------------------------------------------
	m_pDS_Normal = m_pRender->CreateTextureDepthBuffer( m_TargetSize.x, m_TargetSize.y );

	//-----------------------------------------------------------------------
	// ��{�`��^�[�Q�b�g
	//-----------------------------------------------------------------------
	// �^�[�Q�b�g
	m_pRT_Temp	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y, FORMAT_TARGET_UCHAR4 );
	m_pRT_DepthNormal = m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y, IsToonEnable() ? FORMAT_TARGET_FLOAT4 : FORMAT_TARGET_FLOAT1 );

	//-----------------------------------------------------------------------
	// HDR�摜
	//-----------------------------------------------------------------------
	if ( IsHDREnable() )
	{
		m_pRT_Temp_HDR		= m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR			= m_pRender->CreateTextureRenderTarget( m_TargetSize.x /  2, m_TargetSize.y /  2, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR1			= m_pRender->CreateTextureRenderTarget( m_TargetSize.x /  4, m_TargetSize.y /  4, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR1_GausA	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x /  4, m_TargetSize.y /  4, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR1_GausB	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x /  4, m_TargetSize.y /  4, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR2			= m_pRender->CreateTextureRenderTarget( m_TargetSize.x /  8, m_TargetSize.y /  8, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR2_GausA	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x /  8, m_TargetSize.y /  8, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR2_GausB	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x /  8, m_TargetSize.y /  8, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR3			= m_pRender->CreateTextureRenderTarget( m_TargetSize.x / 16, m_TargetSize.y / 16, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR3_GausA	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x / 16, m_TargetSize.y / 16, FORMAT_TARGET_UCHAR4 );
		m_pRT_HDR3_GausB	= m_pRender->CreateTextureRenderTarget( m_TargetSize.x / 16, m_TargetSize.y / 16, FORMAT_TARGET_UCHAR4 );
		if ( m_pRT_Temp_HDR->IsInvalid() || m_pRT_HDR->IsInvalid() ||
			m_pRT_HDR1->IsInvalid() || m_pRT_HDR2->IsInvalid() || m_pRT_HDR3->IsInvalid() ||
			m_pRT_HDR1_GausA->IsInvalid() || m_pRT_HDR1_GausB->IsInvalid() ||
			m_pRT_HDR2_GausA->IsInvalid() || m_pRT_HDR2_GausB->IsInvalid() ||
			m_pRT_HDR3_GausA->IsInvalid() || m_pRT_HDR3_GausB->IsInvalid() )
		{
			SAFE_RELEASE( m_pRT_Temp_HDR );
			SAFE_RELEASE( m_pRT_HDR );
			SAFE_RELEASE( m_pRT_HDR1 );
			SAFE_RELEASE( m_pRT_HDR2 );
			SAFE_RELEASE( m_pRT_HDR3 );
			SAFE_RELEASE( m_pRT_HDR1_GausA );
			SAFE_RELEASE( m_pRT_HDR1_GausB );
			SAFE_RELEASE( m_pRT_HDR2_GausA );
			SAFE_RELEASE( m_pRT_HDR2_GausB );
			SAFE_RELEASE( m_pRT_HDR3_GausA );
			SAFE_RELEASE( m_pRT_HDR3_GausB );
			m_HdrType = HDR_TYPE_DISABLE;
		}
	}

	//-----------------------------------------------------------------------
	// ���x�}�b�v
	//-----------------------------------------------------------------------
	if ( IsVelocityEnable() )
	{
		m_pRT_Velocity = m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y, FORMAT_TARGET_FLOAT2 );
		m_pRT_VelocityTemp = m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y, FORMAT_TARGET_UCHAR4 );
		if ( m_pRT_Velocity->IsInvalid() || m_pRT_VelocityTemp->IsInvalid() )
		{
			SAFE_RELEASE( m_pRT_Velocity );
			SAFE_RELEASE( m_pRT_VelocityTemp );
			m_MotionBlurType = MOTION_BLUR_TYPE_DISABLE;
		}
	}

	//-----------------------------------------------------------------------
	// ��ʊE�[�x
	//-----------------------------------------------------------------------
	if ( IsDepthOfFieldEnable() )
	{
		m_pRT_Temp_DOF = m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y, FORMAT_TARGET_UCHAR4 );
		if ( m_pRT_Temp_DOF->IsInvalid() )
		{
			SAFE_RELEASE( m_pRT_Temp_DOF );
			m_DofType = DOF_TYPE_DISABLE;
		}
	}

	//-----------------------------------------------------------------------
	// �V���h�E�}�b�v�p
	//-----------------------------------------------------------------------
	const Sint32 ShadowSizeTbl[] = { 512, 1024, 2048, 4096 };
	switch ( m_ShadowType )
	{
	case SHADOW_TYPE_SHADOWMAP:
		{
			Sint32 w = ShadowSizeTbl[m_ShadowQuarity];
			Sint32 h = ShadowSizeTbl[m_ShadowQuarity];

			// �`��^�[�Q�b�g
			m_pRT_Shadow = m_pRender->CreateTextureRenderTarget( w, h, FORMAT_TARGET_FLOAT1 );
			m_pDS_Shadow = m_pRender->CreateTextureDepthBuffer( w, h );
			if ( m_pDS_Shadow->IsInvalid() || m_pRT_Shadow->IsInvalid() )
			{
				SAFE_RELEASE( m_pRT_Shadow );
				SAFE_RELEASE( m_pDS_Shadow );
				m_ShadowType = SHADOW_TYPE_DISABLE;
				break;
			}

			// �n�[�h�E�F�A�V���h�E�}�b�v����H
			if ( m_IsHardwareShadowmap )
			{
				// �n�[�h�E�F�A�V���h�E�}�b�v�ł���H
				switch ( m_pDS_Shadow->GetDepthBufferType() )
				{
				case Renderer::DEPTH_BUFFER_TEXTURE_NVIDIA:
					m_HardwareShadowType = HW_SHADOW_NVIDIA;
					break;
				case Renderer::DEPTH_BUFFER_TEXTURE_ATI:
					m_HardwareShadowType = HW_SHADOW_ATI;
					break;
				}
			}

			m_ShadowMapOffset[0].Set( -1.0f / toF(w), -1.0f / toF(h), 0.0f, 0.0f );
			m_ShadowMapOffset[1].Set( +1.0f / toF(w), -1.0f / toF(h), 0.0f, 0.0f );
			m_ShadowMapOffset[2].Set( -1.0f / toF(w), +1.0f / toF(h), 0.0f, 0.0f );
			m_ShadowMapOffset[3].Set( +1.0f / toF(w), +1.0f / toF(h), 0.0f, 0.0f );

			m_pRender->SetRenderTarget( m_pRT_Shadow );
			m_pRender->SetDepthBuffer( m_pDS_Shadow );
			m_pRender->Clear( CColor( 0, 0, 0, 0 ) );
			m_pRender->ClearDepthStencil();
			m_pRender->SetDepthBuffer( NULL );
			m_pRender->SetRenderTarget( NULL );

			m_mShadowOffset.Identity();
			m_mShadowOffset.x.x = +0.5f;
			m_mShadowOffset.y.y = -0.5f;
			m_mShadowOffset.w.x = +0.5f + (0.5f / toF(w));
			m_mShadowOffset.w.y = +0.5f + (0.5f / toF(h));
		}
		break;

	case SHADOW_TYPE_PROJECTION:
		{
			Sint32 w = ShadowSizeTbl[m_ShadowQuarity];
			Sint32 h = ShadowSizeTbl[m_ShadowQuarity];

			// �����_�����V���h�E�}�b�v
			m_pRT_Shadow = m_pRender->CreateTextureRenderTarget( w, h, FORMAT_TARGET_UCHAR4 );

			// ���s�H
			if ( m_pRT_Shadow->IsInvalid() )
			{
				SAFE_RELEASE( m_pRT_Shadow );
				m_ShadowType = SHADOW_TYPE_DISABLE;
			}

			// �e�����_�����O�p
			for ( Sint32 i = 0; i < PROJECTION_SHADOW_PRIORITY_MAX; i++ )
			{
				m_pParticleShadow[i] = m_pRender->CreateParticle( m_QueMax * MAX_BONE_COUNT, m_pTextureShadowProjection, PARTICLE_TYPE_NORMAL, false );
				m_pActorShadow[i] = CreateActor( m_pParticleShadow[i] );
			}

			m_pRender->SetRenderTarget( m_pRT_Shadow );
			m_pRender->Clear( CColor( 0, 0, 0, 0 ) );
			m_pRender->SetRenderTarget( NULL );

			m_mShadowOffset.Identity();
			m_mShadowOffset.x.x = +0.5f;
			m_mShadowOffset.y.y = -0.5f;
			m_mShadowOffset.w.x = +0.5f + (0.5f / toF(w));
			m_mShadowOffset.w.y = +0.5f + (0.5f / toF(h));
		}
		break;
	}

	return !m_pRT_Final->IsInvalid() && !m_pDS_Normal->IsInvalid() && !m_pRT_Temp->IsInvalid() && !m_pRT_DepthNormal->IsInvalid();
}

