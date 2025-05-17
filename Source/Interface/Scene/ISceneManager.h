#pragma once


/**
	@file
	@brief �V�[���Ǘ��n�N���X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/IRender.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �V�[���Ǘ��p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���Ǘ����s�����߂̃C���^�[�t�F�C�X�ł��B
	*/
	class ISceneManager : public IInterface
	{
	protected:
		virtual ~ISceneManager() {}

	public:
		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject			[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@param InstanceCount	[in] �C���X�^���X��
			@return	IInstanceModelActor�C���^�[�t�F�C�X

			@note
			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			�W�I���g���C���X�^���V���O���s�����߂̓���ȃA�N�^�[�ŁA<BR>
			���̃A�N�^�[���炳��Ɍʂ̃R���g���[���[���擾���A���[���h�ϊ���{�[���̐ݒ���s���܂��B<BR>
			<B>�K��InitParameterUpdate�̌�Ɏ��s���Ă��������B</B>
		*/
		virtual IInstanceModelActor *CreateActor( Renderer::Object::IModel *pObject, Sint32 InstanceCount ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IModelActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IModelActor���o�R���čs���܂��B<BR>
			<B>�K��InitParameterUpdate�̌�Ɏ��s���Ă��������B</B>
		*/
		virtual IModelActor *CreateActor( Renderer::Object::IModel *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IMapActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IMapActor���o�R���čs���܂��B<BR>
			<B>�K��InitParameterUpdate�̌�Ɏ��s���Ă��������B</B>
		*/

		virtual IMapActor *CreateActor( Renderer::Object::IMapModel *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IPrimitiveActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IPrimitiveActor���o�R���čs���܂��B<BR>
			<B>�K��InitParameterUpdate�̌�Ɏ��s���Ă��������B</B>
		*/
		virtual IPrimitiveActor *CreateActor( Renderer::Object::IPoint3D *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IPrimitiveActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IPrimitiveActor���o�R���čs���܂��B<BR>
			<B>�K��InitParameterUpdate�̌�Ɏ��s���Ă��������B</B>
		*/
		virtual IPrimitiveActor *CreateActor( Renderer::Object::ILine3D *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@param IsLightmap		[in] 
			@pamra IsNormalmap		[in] 
			@param IsSpecularmap	[in] 
			@param IsEnvironmentmap	[in] 
			@return	IPrimitiveActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IPrimitiveActor���o�R���čs���܂��B<BR>
			<B>�K��InitParameterUpdate�̌�Ɏ��s���Ă��������B</B>
		*/
		virtual IPrimitiveActor *CreateActor( Renderer::Object::IPrimitive3D *pObject, Bool IsLightmap = false, Bool IsNormalmap = false, Bool IsSpecularmap = false, Bool IsEnvironmentmap = false ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	ISpriteActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����ISpriteActor���o�R���čs���܂��B<BR>
			<B>�K��InitParameterUpdate�̌�Ɏ��s���Ă��������B</B>
		*/
		virtual ISpriteActor *CreateActor( Renderer::Object::ISprite3D *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IParticleActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IParticleActor���o�R���čs���܂��B<BR>
			<B>�K��InitParameterUpdate�̌�Ɏ��s���Ă��������B</B>
		*/
		virtual IParticleActor *CreateActor( Renderer::Object::IFontSprite3D *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IParticleActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IParticleActor���o�R���čs���܂��B<BR>
			<B>�K��InitParameterUpdate�̌�Ɏ��s���Ă��������B</B>
		*/
		virtual IParticleActor *CreateActor( Renderer::Object::IParticle *pObject ) = 0;

		/**
			@brief �V�[���J�����擾
			@author �t���`
			@return �J����

			�V�[���Ɋ֘A�t����ꂽ�J�������擾���܂��B
		*/
		virtual ICamera *GetCamera( void ) = 0;

		/**
			@brief �V�[��������
			@author �t���`

			�V�[���̃��C�g��t�H�O�Ȃǂ̃f�[�^�����Z�b�g���܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void Reset( void ) = 0;

		/**
			@brief �V�[���J�n
			@author �t���`
			@param IsSort	[in] �V�[�����̃I�u�W�F�N�g���\�[�g���邩�ǂ���

			�V�[���Ǘ����J�n���܂��B<BR>
			���̎��_�ŃJ�����̃f�[�^���m�肵�܂��̂�<BR>
			���̊֐����Ăяo�������Ƃ̃J�����̍X�V�͑S�Ė����ł��B
		*/
		virtual void Begin( Bool IsSort ) = 0;

		/**
			@brief �V�[���I��
			@author �t���`

			�V�[���̊Ǘ����������܂��B
		*/
		virtual void End( void ) = 0;

		/**
			@brief �I���ҋ@
			@author �t���`

			ISceneManager�Ń����_�����O�����̊��������S�ɑҋ@���܂��B<BR>
			Begin()-End()�ȍ~����Ńf�[�^�̍\�z�������s���܂��̂ŁA<BR>
			�V�[���A���邢�̓V�[���ŗ��p���Ă��郊�\�[�X���������O��<BR>
			���̊֐��ŃV�[���̍\�z�����̏I����҂��ĉ������B<BR>
			�Ȃ��A�v���P�[�V�����̏I����(ICore::Run()=false)���ɂ͓����őS�ẴV�[����<BR>
			Abort()�������I�ɌĂ΂�܂��B
		*/
		virtual void Abort( void ) = 0;

		/**
			@brief �V�[�������_�����O
			@author �t���`
			@param IsDrawBuffer	[in] �����p�o�b�t�@�̕\��

			�V�[���̊Ǘ��ō\�z���ꂽ�V�[���������_�����O���܂��B<BR>
			���̊֐����R�[�������i�K�œ����ŕ`�揈�����J�n����܂��B<BR>
			�K��IRender::Begin()�`IRender::End()�ԂŌĂяo���Ă��������B
		*/
		virtual void Rendering( Bool IsDrawBuffer = false ) = 0;

		/**
			@brief �A���r�G���g���C�g�ݒ�
			@author �t���`
			@param vColorSky	[in] �V�[�����̓V���̊����̐F
			@param vColorEarth	[in] �V�[�����̒n�\�̊����̐F

			�V�[���̊�����ݒ肵�܂��B<BR>
			�������C�e�B���O���s�����߂ɁA�V���ƒn�\�̐F��ݒ肵�܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void SetLightParameter_Ambient( const Math::Vector3D &vColorSky, const Math::Vector3D &vColorEarth ) = 0;

		/**
			@brief �f�B���N�V�������C�g�ݒ�
			@author �t���`
			@param vDirect	[in] �V�[�����̕��s�����̕���
			@param vColor	[in] �V�[�����̕��s�����̐F

			�V�[���ɑ債�ĂP�������s���������蓖�Ă邱�Ƃ��ł��܂��B<BR>
			���z�̂悤�ɗy�������ɑ��݂��A�I�u�W�F�N�g�̈ʒu�ɂ����<BR>
			���̕������ς��Ȃ��悤�ȃ��C�g�Ɍ����Ă��܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B<BR>
			�܂��V�[�����[�h�̉e�������w�肵�Ă��鎞��vDirect�͖����ł��B<BR>
			�����Ɋւ��Ă�SetParameter_Shadow()�Ŏw�肵���l���g�p����܂��B
		*/
		virtual void SetLightParameter_Directional( const Math::Vector3D &vDirect, const Math::Vector3D &vColor ) = 0;

		/**
			@brief �|�C���g���C�g�ǉ�
			@author �t���`
			@param vPosition	[in] �V�[�����̓_�����̈ʒu
			@param vColor		[in] �V�[�����̓_�����̐F
			@param fDistance	[in] �V�[�����̓_�����̉e������

			�V�[���ɑ΂��ē_������ǉ����܂�<BR>
			�ő��32�̃��C�g��ݒ�ł��A���̂����ł��I�u�W�F�N�g�ɋ߂�<BR>
			4�̃��C�g���I�u�W�F�N�g�ɓK�p����܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void SetLightParameter_AddPoint( const Math::Vector3D &vPosition, const Math::Vector3D &vColor, Float fDistance ) = 0;

		/**
			@brief �����_�����O���N�G�X�g���擾
			@author �t���`
			@return �����_�����O���N�G�X�g��

			�V�[���Ƀ��N�G�X�g�����_�����O�����擾���܂��B
		*/
		virtual Sint32 GetResult_RenderingRequestActorCount( void ) = 0;

		/**
			@brief �����_�����O���擾
			@author �t���`
			@return �����_�����O��

			�V�[���Ŏ��s���ꂽ�����_�����O�����擾���܂��B<BR>
			2Pass�n�̏��������J�E���g�����̂ŁA<BR>
			���N�G�X�g���ȏ�̒l�ɂȂ邱�Ƃ�����܂��B
		*/
		virtual Sint32 GetResult_RenderingActorCount( void ) = 0;

		/**
			@brief �V�[���̍\�z�ɂ����������Ԃ��擾
			@author �t���`
			@return �V�[���̍\�z�ɂ����������ԁi�P�t���[���ɑ΂��道�j

			�P�t���[��������̃V�[���\�z�ɂ����������Ԃ����Ŏ擾���܂��B
		*/
		virtual Sint32 GetResult_BackgroundThreadTime( void ) = 0;

		/**
			@brief �V�[���̕`��ɂ����������Ԃ��擾
			@author �t���`
			@return �V�[���̕`��ɂ����������ԁi�P�t���[���ɑ΂��道�j

			�P�t���[��������̃V�[���`��ɂ����������Ԃ����Ŏ擾���܂��B
		*/
		virtual Sint32 GetResult_RenderingTme( void ) = 0;

		/**
			@brief ���[�V�����u���[���x���̐ݒ�
			@author �t���`
			@param Level		[in] �g�p���郌�x��

			���[�V�����u���[�����̃��x����ݒ肵�܂��B<BR>
			MOTION_BLUR_FULL�w��̏ꍇ�̓��f���f�[�^�����Ă��Ė@����ێ����Ă���K�v������܂��B
		*/
		virtual void SetActorParameter_MotionBlur( eSceneMotionBlurQuarity MotionBlurQuarity ) = 0;

		/**
			@brief �e�̐����I�v�V������ON/OFF
			@author �t���`
			@param Type		[in] �e�����̕��@
			@param Priority	[in] �e�̃v���C�I���e�B
			@param fRadius	[in] �ۉe�̏ꍇ�̑傫��

			�V�[���ɓK�p�����e�������uSHADOW_TYPE_PROJECTION_*�v���uSHADOW_TYPE_SOFT_PROJECTION_*�v�̎���<BR>
			�����_�����O���郂�f�����e�𗎂Ƃ����ǂ�����ݒ肵�܂��B<BR>
			�e�𗎂Ƃ����f���ɂ͑��̃��f���̉e���������A�e�𗎂Ƃ��Ȃ����f���ɂ͑��̃��f���̉e�������܂��B
		*/
		virtual void SetActorParameter_ProjectionShadow( eProjectionShadowType Type, eProjectionShadowPriority Priority, Float fRadius = 0.0f ) = 0;

		/**
			@brief �V�[���S�̖̂��邳�̐ݒ�
			@author �t���`
			@param vBrightness	[in] �F

			�V�[���Ƀ��C�g�}�b�v����Ƃ������邳��ݒ肵�܂��B<BR>
			1.0f���w�肷�邱�Ƃ�Amaryllis��Őݒ肵���p�����[�^�[���̂܂܂̖��邳�ɂȂ�A<BR>
			����ȏ�Ŗ��邭�A����ȉ��ňÂ����邱�Ƃ��o���܂��B
		*/
		virtual void SetParameter_SceneBrightness( const Math::Vector3D &vBrightness ) = 0;

		/**
			@brief ���`�t�H�O���ݒ�
			@author �t���`
			@param vColor	[in] �t�H�O�̐F
			@param fNear	[in] �t�H�O�J�n�_
			@param fFar		[in] �t�H�O�I���_

			�V�[���ɓK�p�������`�t�H�O�̃p�����[�^�[��ݒ肵�܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void SetParameter_Fog( Math::Vector3D &vColor, Float fNear, Float fFar ) = 0;

		/**
			@brief ��ʊE�[�x�p�̃t�H�[�J�X�ʒu��ݒ肵�܂��B
			@author �t���`

			@param fForcusZ	[in] �t�H�[�J�X�̂y�i�J������j
			@param fPower	[in] ��ʊE�[�x���x

			��ʊE�[�x�̃t�H�[�J�X�ʒu��ݒ肵�܂��B
		*/
		virtual void SetParameter_DepthOfField( Float fForcusZ, Float fPower ) = 0;

		/**
			@brief �\�t�g�p�[�e�B�N���p�X�P�[���l
			@author �t���`

			@param fSoftParticleScale	[in] �\�t�g�p�[�e�B�N���̃A���t�@�l�p�̃X�P�[��

			�\�t�g�p�[�e�B�N�����̐[�x�l�̍��ق���A���t�@���Z�o����Ƃ��̃X�P�[���l�ł��B<BR>
			���̒l���傫���قǃA���t�@�̋��E���V���[�v�ɂȂ�܂��B
		*/
		virtual void SetParameter_SoftParticleScale( Float fSoftParticleScale ) = 0;

		/**
			@brief HDR�G�t�F�N�g�ݒ�
			@author �t���`
			@param HdrEffect	[in] HDR�G�t�F�N�g�̎��
			@param fHDRPower	[in] HDR�̔{��
			@param fHDRBoundary	[in] HDR�Ƃ��Ĉ���臒l�i1.0�����j

			�V�[���̕`�掞��HDR�G�t�F�N�g�̐ݒ�����܂��B
		*/
		virtual void SetParameter_HighDynamicRange( Float fHDRPower, Float fHDRBoundary ) = 0;

		/**
			@brief �g�D�[���p�p�����[�^�[�ݒ�
			@author �t���`
			@param vHatchingColor	[in] �n�b�`���O�p�̎ΐ��̐F
			@param fToonPower		[in] �g�D�[���}�b�v�p�̉e�����̈Â��i0.0�`1.0)

			�g�D�[�������_�����O�p�̃p�����[�^�[��ݒ肵�܂��B
		*/
		virtual void SetParameter_Toon( Math::Vector3D &vHatchingColor, Float fToonPower ) = 0;

		/**
			@brief �g�D�[���p�G�b�W���o�p�����[�^�[�ݒ�
			@author �t���`
			@param fEdgeNormalPower	[in] �@���G�b�W�̌��o�p�����[�^�[
			@param fEdgeDepthPower	[in] �[�x�G�b�W�̌��o�p�����[�^�[
			@param IsToonBold		[in] �֊s���𑾂����邩�ۂ�

			�g�D�[���p�̃G�b�W���o�p�̃p�����[�^�[��ݒ肵�܂��B<BR>
			������̃p�����[�^�[���傫���قǋ��E�����������͈͂������܂��B
		*/
		virtual void SetParameter_ToonEdge( Float fEdgeNormalPower, Float fEdgeDepthPower, Bool IsToonBold ) = 0;

		/**
			@brief �V���h�E�p�J�����ݒ�
			@author �t���`
			@param vPosition	[in] �J�����ʒu
			@param vTarget		[in] �J���������_
			@param fSize		[in] �����_�����O�T�C�Y
			@param fNear		[in] �߃N���b�v��
			@param fFar			[in] ���N���b�v��
			@param fBias		[in] �V���h�E�}�b�v�p�[�x�o�C�A�X
			@param fPower		[in] �e�̕����̖��邳(0.0����1.0�܂ŁA1.0�̎��e�͊��S�ȃA���r�G���g�ɂȂ�j

			�V���h�E�p�̃J�����f�[�^��ݒ肵�܂��B
		*/
		virtual void SetParameter_Shadow( Math::Vector3D &vPosition, Math::Vector3D &vTarget, Float fSize, Float fNear, Float fFar, Float fBias, Float fPower ) = 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�̋�`��ݒ�
			@author �t���`
			@param Dst		[in] �����_�����O��`

			�V�[���̃����_�����O�^�[�Q�b�g�̋�`���w�肵�܂��B<BR>
			�ŏI�I�ɕ\�������ʒu�Ɋ֌W���܂��B
		*/
		virtual void SetParameter_RenderRect( Math::Rect2DF &Dst ) = 0;

		/**
			@brief �w�i�h��Ԃ��F�ݒ�
			@author �t���`
			@param ClearColor	[in] �o�b�t�@�N���A�F
			@param IsClear		[in] �N���A�L��

			�V�[���̕`�掞�̔w�i�̓h��Ԃ��F��ݒ肵�܂��B
		*/
		virtual void SetParameter_BGColor( Math::Vector4D &ClearColor, Bool IsClear = true ) = 0;

		/**
			@brief �w�i�h��Ԃ��F�ݒ�
			@author �t���`
			@param ClearColor	[in] �o�b�t�@�N���A�F
			@param IsClear		[in] �N���A�L��

			�V�[���̕`�掞�̔w�i�̓h��Ԃ��F��ݒ肵�܂��B
		*/
		virtual void SetParameter_BGColor( CColor ClearColor, Bool IsClear = true ) = 0;

		/**
			@brief �w�i�h��Ԃ��e�N�X�`���ݒ�
			@author �t���`
			@param pTex		[in] �e�N�X�`��

			�V�[���̕`�掞�̔w�i�̃e�N�X�`����ݒ肵�܂��B
		*/
		virtual void SetParameter_BGTexture( Renderer::ITexture *pTex ) = 0;

		/**
			@brief �V�[�������X�V
			@author �t���`

			�V�[��������܂ł̏������ɍX�V���܂��B<BR>
			�K�v�Ȑݒ��ɂ��̊֐����Ăяo���Ȃ�����IActor�𐶐����邱�Ƃ��o���܂���B
		*/
		virtual Bool InitParameter_Update( void ) = 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�̃T�C�Y��ݒ�
			@author �t���`
			@param pTarget				[in] �����_�����O�^�[�Q�b�g�̃e�N�X�`���iNULL�Ńo�b�N�o�b�t�@�֒��ڃ����_�����O�j
			@param Size					[in] �T�C�Y�ipTarget���L���ȏꍇ��pTarget�̃T�C�Y�Ɏ����ݒ肳��܂��j
			@param IsTextureSizePow2	[in] �T�C�Y�������I�ɂQ�̗ݏ�ɂ��邩�ǂ���

			�V�[���̃����_�����O�^�[�Q�b�g�̃T�C�Y���w�肵�܂��B<BR>
			�����_�����O�g����e��o�b�t�@�̃T�C�Y�Ɋ֌W���܂��B<BR>
			<B>�K��InitParameterUpdate�̑O�Ɏ��s���Ă��������B</B>
		*/
		virtual void InitParameter_RenderTargetData( Renderer::ITexture *pTarget, Math::Point2DI Size = Math::Point2DI(0,0), Bool IsTextureSizePow2 = false ) = 0;

		/**
			@brief �V�F�[�f�B���O�p�p�����[�^�[�̏�����
			@author �t���`
			@param ShadingType		[in] �V�F�[�f�B���O�̎��

			�V�[���ōs���V�F�[�f�B���O�̏��������������܂��B<BR>
			<B>�K��InitParameterUpdate�̑O�Ɏ��s���Ă��������B</B>
		*/
		virtual void InitParameter_Shading( eSceneShadingType ShadingType ) = 0;

		/**
			@brief �A���`�G�C���A�X�p�p�����[�^�[�̏�����
			@author �t���`
			@param AntiAliasType	[in] �A���`�G�C���A�X�̎��
			@param fPower			[in] �A���`�G�C���A�X�̂�����(0.0�`1.0)

			�V�[���ōs���A���`�G�C���A�X�̏��������������܂��B<BR>
			<B>�K��InitParameterUpdate�̑O�Ɏ��s���Ă��������B</B>
		*/
		virtual void InitParameter_AntiAliasType( eSceneAntiAliasType AntiAliasType, Float fPower ) = 0;

		/**
			@brief �e�p�p�����[�^�[�̏�����
			@author �t���`
			@param ShadowType			[in] �e�̎��
			@param ShadowQuarity		[in] �e�̕i��
			@param IsSoftShadow			[in] �\�t�g�V���h�E���g�����ǂ���
			@param IsHardwareShadowmap	[in] �n�[�h�E�F�A�V���h�E�}�b�v���g�����ǂ���

			�V�[���ōs���e�̏��������������܂��B<BR>
			<B>�K��InitParameterUpdate�̑O�Ɏ��s���Ă��������B</B>
		*/
		virtual void InitParameter_Shadow( eSceneShadowType ShadowType, eSceneShadowQuarity ShadowQuarity, Bool IsSoftShadow = false, Bool IsHardwareShadowmap = true ) = 0;

		/**
			@brief ���[�V�����u���[�p�p�����[�^�[�̏�����
			@author �t���`
			@param MotionBlurType	[in] ���[�V�����u���[�̎��

			�V�[���ōs�����[�V�����u���[�̏��������������܂��B<BR>
			<B>�K��InitParameterUpdate�̑O�Ɏ��s���Ă��������B</B>
		*/
		virtual void InitParameter_MotionBlur( eSceneMotionBlurType MotionBlurType ) = 0;

		/**
			@brief ��ʊE�[�x�p�p�����[�^�[�̏�����
			@author �t���`
			@param DofType	[in] ��ʊE�[�x�̎��

			�V�[���ōs����ʊE�[�x�̏��������������܂��B<BR>
			<B>�K��InitParameterUpdate�̑O�Ɏ��s���Ă��������B</B>
		*/
		virtual void InitParameter_DepthOfField( eSceneDepthOfFieldType DofType ) = 0;

		/**
			@brief �t�H�O�p�p�����[�^�[�̏�����
			@author �t���`
			@param FogType		[in] �t�H�O�̎��
			@param FogEffect	[in] �t�H�O�̃G�t�F�N�g

			�V�[���ōs���t�H�O�̏��������������܂��B<BR>
			<B>�K��InitParameterUpdate�̑O�Ɏ��s���Ă��������B</B>
		*/
		virtual void InitParameter_Fog( eSceneFogType FogType, eSceneFogEffect FogEffect ) = 0;

		/**
			@brief HDR�����_�����O�p�p�����[�^�[�̏�����
			@author �t���`
			@param HdrType		[in] HDR�����_�����O�̎��
			@param HdrEffect	[in] HDR�����_�����O�̃G�t�F�N�g

			�V�[���ōs��HDR�����_�����O�̏��������������܂��B<BR>
			<B>�K��InitParameterUpdate�̑O�Ɏ��s���Ă��������B</B>
		*/
		virtual void InitParameter_HighDynamicRange( eSceneHighDynamicRangeType HdrType, eSceneHighDynamicRangeEffect HdrEffect ) = 0;

		/**
			@brief �X�J�C�h�[���̐���
			@author �t���`
			@param fRadius		[in] ���a
			@param TopColor		[in] �V���̓������̐F
			@param BottomColor	[in] �V���̒n�ʕ����̐F
			@param pTexCloud	[in] �_�e�N�X�`��

			�V�[���ɓK�p����X�J�C�h�[���𐶐����܂��B<BR>
		*/
		virtual Bool SceneSkydoom_Create( Float fRadius, CColor TopColor, CColor BottomColor, Renderer::ITexture *pTexCloud ) = 0;

		/**
			@brief �X�J�C�h�[���̃����_�����O
			@author �t���`

			�V�[���ɓo�^����Ă���X�J�C�h�[���̃����_�����O�����܂��B
		*/
		virtual void SceneSkydoom_Rendering( void ) = 0;

		/**
			@brief �X�J�C�h�[���̉_�e�N�X�`���̐F��ݒ�
			@author �t���`
			@param Color		[in] �F

			�V�[���ɓK�p����X�J�C�h�[���̉_�̐F��ݒ肵�܂��B
		*/
		virtual void SceneSkydoom_SetCloudColor( const CColor &Color ) = 0;

		/**
			@brief �X�J�C�h�[���̉_�e�N�X�`���̈ړ��ʃI�t�Z�b�g
			@author �t���`
			@param vOffset		[in] �ړ���(1.0�Ńe�N�X�`���T�C�Y)

			�V�[���ɓK�p����X�J�C�h�[���̉_�̗���𐧌䂵�܂��B<BR>
			���̊֐��ŗ^�����I�t�Z�b�g���_���ړ����܂��B
		*/
		virtual void SceneSkydoom_SetCloudOffset( const Math::Vector2D &vOffset ) = 0;

		/**
			@brief �X�N���[�����W�ɕϊ�
			@author �t���`
			@param vPosition	[in] ���[���h���W
			@return �X�N���[�����W

			���[���h��Ԃ̍��W���X�N���[�����W�ɕϊ����܂��B
		*/
		virtual Math::Vector3D TransformToScreen( const Math::Vector3D &vPosition ) = 0;

		/**
			@brief �X�N���[�����W����ϊ�
			@author �t���`
			@param vPosition	[in] �X�N���[�����W
			@return ���[���h���W

			�X�N���[�����W�����[���h��Ԃ̍��W�ɕϊ����܂��B
		*/
		virtual Math::Vector3D TransformFromScreen( const Math::Vector3D &vPosition ) = 0;
	};
}
}

