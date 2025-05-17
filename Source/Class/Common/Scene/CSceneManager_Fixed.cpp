

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Scene/CSceneManager_Fixed.h"
#include "Class/Common/Scene/CCustomizedSceneRenderObject.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Platform/Surface/CTexture.h"
#include "Class/Platform/Surface/CDepthTexture.h"
#include "Class/Platform/Render/COcclusion.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Scene;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSceneManager_Fixed::CSceneManager_Fixed( Renderer::CRender *pRender, Renderer::CRenderObjectMgr *pMgr, Sint32 QueMax ) : CSceneManagerBase( pRender, pMgr, QueMax )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSceneManager_Fixed::~CSceneManager_Fixed()
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_Fixed::Rendering( Bool IsDrawBuffer )
{
	m_SceneRenderingTime = 0;

	//==============================================================
	// �J�n���ĂȂ�
	//==============================================================
	if ( m_SceneState != SCENE_STATE_END )
	{
		SceneClear();
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
	// �����_�����O
	//==============================================================
	Rendering_NoPS();

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
void CSceneManager_Fixed::Rendering_NoPS( void )
{
	Math::Rect2DF Dst, Src;

	//------------------------------------------------------------------------
	// �^�[�Q�b�g
	//------------------------------------------------------------------------
	m_pRender->SetRenderTarget( m_pRT_Temp );
	m_pRender->SetDepthBuffer( m_pDS_Normal );

	//------------------------------------------------------------------------
	// �N���A
	//------------------------------------------------------------------------
	SceneClear();
	ClearDepthBuffer();

	//------------------------------------------------------------------------
	// �����_�����O
	//------------------------------------------------------------------------
	// �X�e�[�g
	m_pRender->Start3D();

	// �����_�����O
	Rendering_All();

	//------------------------------------------------------------------------
	// �^�[�Q�b�g
	//------------------------------------------------------------------------
	m_pRender->SetRenderTarget( m_pRenderTarget );
	m_pRender->SetDepthBuffer( NULL );

	//------------------------------------------------------------------------
	// �|�X�g�G�t�F�N�g
	//------------------------------------------------------------------------
	// �X�e�[�g
	m_pRender->Start2D( false );

	Src.Set( 0.0f, 0.0f, toF(m_pRT_Temp->GetOriginalSize().x), toF(m_pRT_Temp->GetOriginalSize().y ) );
	m_pRender->SetAlphaTestEnable( false );
	m_pRender->SetCullType( CULL_FRONT );
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_COLOR, (m_RenderRect.w != Src.w) || (m_RenderRect.h != Src.h) ? TEXTURE_FILTER_2D : TEXTURE_FILTER_DISABLE );
	m_pRender->DrawTexture( m_RenderRect, CColor(255,255,255), Src, m_pRT_Temp );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_Fixed::Rendering_All( void )
{
	Renderer::Shader::ShaderVariable *pVariable = Renderer::Shader::ShaderManager::GetShaderVariable();

	Uint32 ActiveShaderID = 0xFFFFFFFF;
	Renderer::Shader::CShader *pActiveShader = NULL;
	Sint32 Polygon = 0;
	Math::Vector4D vPositionTbl[4];
	Math::Vector4D vColorTbl[4];
	Math::Matrix mTemp;
	Math::Vector4D vTemp;
	Renderer::ITexture *pTex;

	//================================================================================================
	// ���ʕϐ��p
	//================================================================================================
	// �J�����̋t�ϊ�
	Math::Matrix mViewInverse;
	mViewInverse.Transpose( m_Camera.WorldToView() );
	pVariable->SetViewInverse( &mViewInverse );

	// FogParameter
	if ( IsFogEnable() )
	{
		pVariable->SetFogParameter( m_FogParameter );
		pVariable->SetFogColor( m_FogColor );
	}

	// AmbientLightColorSky
	pVariable->SetLightParameter_AmbientColorSky( m_vLightColor[LIGHT_AMBIENT_SKY] );

	// AmbientLightColorEarth
	pVariable->SetLightParameter_AmbientColorEarth( m_vLightColor[LIGHT_AMBIENT_EARTH] );

	// DirectionalLightColor
	pVariable->SetDirectionalLightColor( m_vLightColor[LIGHT_DIRECTION] );

	//================================================================================================
	// �I�u�W�F�N�g�����_�����O
	//================================================================================================
	for ( Sint32 Id = ID_SKYDOOM; Id <= ID_ALPHA_ENABLE; Id++ )
	{
		CCustomizedSceneRenderObject *pObj = m_pObjectList[Id];
		while ( pObj != NULL )
		{
			// WorldViewProjection
			pVariable->SetWorldViewProjection( &pObj->mWorldViewProjection );

			// CameraPosition
			if ( pObj->GetSpecularEnable() || pObj->GetEnvironmentEnable() )
			{
				vTemp.TransformCoord( m_Camera.Position(), pObj->GetWorldInverseMatrix() );
				pVariable->SetCameraPosition( vTemp );
			}

			// World
			if ( pObj->GetEnvironmentEnable() )
			{
				pVariable->SetWorld( &pObj->GetWorldMatrix() );
			}

			// ���C�g����H
			if ( pObj->IsSupportVertexNormal() )
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
			Sint32 BoneCnt = pObj->GetBoneCount();
			if ( BoneCnt > 0 )
			{
				// BoneMatrixArray
				pVariable->SetBoneMatrixArray( pObj->GetBoneMatrixArray(), BoneCnt );
			}

			// �f�[�^�X�g���[��
			pObj->SetStreamSource( m_pRender );

			// �}�e���A���P�ʂ�
			Sint32 MtrlCnt = pObj->GetMaterialCount();
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

				// �J���[�e�N�X�`��
				pTex = Mtrl.GetTexture( TEXTURE_STAGE_COLOR );
				m_pRender->SetTexture( TEXTURE_STAGE_COLOR, pTex );

				// ���C�g�}�b�v
				pTex = Mtrl.GetTexture( TEXTURE_STAGE_LIGHT );
				m_pRender->SetTexture( TEXTURE_STAGE_LIGHT, pTex );

				// ���}�b�v
				pTex = Mtrl.GetTexture( TEXTURE_STAGE_ENVIRONMENT );
				m_pRender->SetTexture( TEXTURE_STAGE_ENVIRONMENT, pTex );

				// �X�y�L�����}�b�v
				if ( Mtrl.GetSpecularType() != SPECULAR_TYPE_NONE )
				{
					// SpecularColor
					pVariable->SetSpecularColor( Mtrl.GetSpecularColor() );
					// Specular Refractive
					pVariable->SetRefractive( Mtrl.GetSpecularRefractive() );
					// Specular Roughly
					pVariable->SetRoughly( Mtrl.GetSpecularRoughly() );
				}

				// MaterialColor
				vTemp.x = Mtrl.GetDiffuseColor().x * pObj->vBrightness.x;
				vTemp.y = Mtrl.GetDiffuseColor().y * pObj->vBrightness.y;
				vTemp.z = Mtrl.GetDiffuseColor().z * pObj->vBrightness.z;
				vTemp.w = Mtrl.GetDiffuseColor().w;
				pVariable->SetMaterialColor( vTemp );

				// EmissiveColor
				pVariable->SetEmissiveColor( Mtrl.GetEmissiveColor() );

				// Texture Offset
				pVariable->SetTextureOffset( Mtrl.GetTextureOffset() );

				// �p�����[�^�[�X�V
				pActiveShader->UpdateParameter();

				// �����_�����O
				pActiveShader->BeginPass( 0 );
				Polygon += pObj->Rendering( j, m_pRender );
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

	//--------------------------------------------------
	// �`�搔
	//--------------------------------------------------
	m_pCore->DrawPolygon( Polygon );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSceneManager_Fixed::CreateRenderTargetBuffer( void )
{
	//-----------------------------------------------------------------------
	// �[�x�o�b�t�@
	//-----------------------------------------------------------------------
	m_pDS_Normal = (Renderer::CDepthTexture*)m_pRender->CreateTextureDepthBuffer( m_TargetSize.x, m_TargetSize.y );

	//-----------------------------------------------------------------------
	// ��{�`��^�[�Q�b�g
	//-----------------------------------------------------------------------
	// �^�[�Q�b�g
	m_pRT_Temp = m_pRender->CreateTextureRenderTarget( m_TargetSize.x, m_TargetSize.y, FORMAT_TARGET_UCHAR4 );

	return !m_pDS_Normal->IsInvalid() && !m_pRT_Temp->IsInvalid();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSceneManager_Fixed::SceneClear( void )
{
	if ( m_pTextureBG != NULL )
	{
		m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
		Math::Rect2DF Src( 0.0f, 0.0f, toF(m_pTextureBG->GetSize().x), toF(m_pTextureBG->GetSize().y) );
		m_pRender->DrawTexture( m_RenderRect, CColor(255,255,255), Src, m_pTextureBG );
	}
	else
	if ( m_IsClear )
	{
		CColor Color( 0, 0, 0, 255 );
		Color.r = (Uint8)(m_ClearColor.x * 255.0f);
		Color.g = (Uint8)(m_ClearColor.y * 255.0f);
		Color.b = (Uint8)(m_ClearColor.z * 255.0f);
		m_pRender->Clear( Color );
	}
}

