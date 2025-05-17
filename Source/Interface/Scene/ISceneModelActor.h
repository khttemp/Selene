#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Style.h"
#include "Collision/Line3D.h"
#include "Collision/Box.h"
#include "Interface/Render/IRender.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �V�[�����f���A�N�^�[�p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���Ǘ����ꂽ���f���A�N�^�[�������ׂ̃C���^�[�t�F�C�X�ł��B
	*/
	class IModelActor : public Math::Style
	{
	public:
		virtual ~IModelActor() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`

			ISceneManager�ɑ΂��ă����_�����O���N�G�X�g�𔭍s���܂��B<BR>
			�擾����ISceneManager��Begin()/End()���łȂ��ꍇ���̊֐��͎��s���܂��B
		*/
		virtual void RenderingRequest( void ) = 0;

		/**
			@brief �J�����O�p�o�E���f�B���O�����_�����O
			@author �t���`
			@param pLine	[in] ���C���v���~�e�B�u�C���^�[�t�F�C�X

			�o�E���f�B���O�{�b�N�X���w�肵�����C���f�[�^�ɑ΂��Ēǉ����܂��B
		*/
		virtual void RenderingBounding( Renderer::Object::ILine3D *pLine ) = 0;

		/**
			@brief ���W�ϊ�������
			@author �t���`

			�A�N�^�[�̍��W�ϊ������������܂��B<BR>
			�A�j���[�V�����̏��Ȃǂ����̊֐����ł��ׂď���������܂��B
		*/
		virtual void TransformReset( void ) = 0;

		/**
			@brief ���W�ϊ��X�V
			@author �t���`

			�A�N�^�[�̍��W�ϊ����X�V���܂��B<BR>
			�A�j���[�V�����̏��Ȃǂ����̊֐����ł��ׂčX�V����܂��B<BR>
			�����I�ɂ́@TransformUpdateCollisionOnly() �� TransformUpdateActorOnly() ���Ăяo���Ă��܂��B
		*/
		virtual void TransformUpdate( void ) = 0;

		/**
			@brief ���W�ϊ��X�V
			@author �t���`

			�A�N�^�[�̃R���W�����̍��W�ϊ����X�V���܂��B<BR>
			�R���W�����Ɋ֌W����f�[�^�������ōX�V����܂��B
		*/
		virtual void TransformUpdateCollisionOnly( void ) = 0;

		/**
			@brief ���W�ϊ��X�V
			@author �t���`

			�A�N�^�[�̍��W�ϊ����X�V���܂��B<BR>
			�`��p�̃A�N�^�[�������X�V����܂��B
		*/
		virtual void TransformUpdateActorOnly( void ) = 0;

		/**
			@brief ���f���ɑ΂��ăA�j���[�V�����f�[�^�����擾
			@author �t���`
			@return	�A�j���[�V������

			�A�N�^�[�̏�������A�j���[�V�����̐����擾���܂��B
		*/
		virtual Sint32 GetAnimationCount( void ) = 0;

		/**
			@brief �A�j���[�V�����f�[�^�̍ŏI���Ԃ��擾
			@author �t���`
			@param AnimationNo		[in] �K�p����A�j���[�V�����ԍ�
			@return	�A�j���[�V�����̍ŏI����

			�A�j���[�V�����̍ŏI�t���[�����擾���܂��B
		*/
		virtual Float GetAnimationLastTime( Sint32 AnimationNo ) = 0;

		/**
			@brief ���f���ɑ΂��ăA�j���[�V�����f�[�^���X�V
			@author �t���`
			@param AnimationNo		[in] �K�p����A�j���[�V�����ԍ�
			@param fAnimationTime	[in] �A�j���[�V�����̎��ԁi�P�ʂ͍쐬�����c�[���ɂ��j

			�P��̃A�j���[�V�����f�[�^�̍X�V�����܂��B
		*/
		virtual void UpdateAnimation( Sint32 AnimationNo, Float fAnimationTime ) = 0;

		/**
			@brief ���f���ɑ΂��ăA�j���[�V�����f�[�^���X�V
			@author �t���`
			@param AnimationNo1		[in] �K�p����A�j���[�V�����ԍ�
			@param fAnimationTime1	[in] �A�j���[�V�����̎��ԁi�P�ʂ͍쐬�����c�[���ɂ��j
			@param AnimationNo2		[in] �K�p����A�j���[�V�����ԍ�
			@param fAnimationTime2	[in] �A�j���[�V�����̎��ԁi�P�ʂ͍쐬�����c�[���ɂ��j
			@param fWeight			[in] �u�����h�����i0.0f�̎�AnimationNo0�A1.0�̎�AnimationNo1)

			�Q�̃A�j���[�V�������u�����h���ăA�j���[�V�����f�[�^���X�V���܂��B
		*/
		virtual void UpdateAnimation( Sint32 AnimationNo1, Float fAnimationTime1, Sint32 AnimationNo2, Float fAnimationTime2, Float fWeight ) = 0;

		/**
			@brief �J�����O�����ɗL���ݒ�
			@author �t���`
			@param IsEnable	[in] �J�����O�̗L��

			���f�����̊e�A�N�^�[�ɑ΂��ăr���[�t���X�^���J�����O���s������ݒ肵�܂��B<BR>
			�r���[�t���X�^���J�����O�Ƃ̓J�����̕`��̈���ɂȂ��A�N�^�[��`��Ɋւ����A�̏�������<BR>
			�Ȃ����߂̏����ŁA�s������CPU���ׂ͑����܂�����ʊO�ɏo��A�N�^�[�ɑ΂��Ă̕`�敉�ׂ��y���ł��܂��B
		*/
		virtual void SetCullTestEnable( Bool IsEnable ) = 0;

		/**
			@brief ���f�����̃t���[�����擾
			@author �t���`
			@return	���f�����̃t���[���̐�

			���f�����̃t���[���̐����擾���܂��B<BR>
			�X�L�����b�V���Ɋ֘A�t�����Ă���t���[����<BR>
			�����I�ɂ̓{�[���ɂȂ�܂��B
		*/
		virtual Sint32 GetFrameCount( void ) = 0;

		/**
			@brief ���f�����̃t���[�����擾
			@author �t���`
			@return	���f�����̃t���[���̐�

			���f�����̃t���[���̐����擾���܂��B
		*/
		virtual Sint32 Frame_GetIndex( const char *pName ) = 0;

		/**
			@brief �t���[���̕ϊ��s����擾
			@author �t���`
			@param Index	[in] �t���[���̔ԍ�
			@return	�t���[���̕ϊ��s��

			�t���[���̕ϊ��s����擾���܂��B
		*/
		virtual Math::Matrix &Frame_GetTransformLocal( Sint32 Index ) = 0;

		/**
			@brief �t���[���̕ϊ��s����擾
			@author �t���`
			@param Index	[in] �t���[���̔ԍ�
			@return	�t���[���̕ϊ��s��

			�t���[���̕ϊ��s����擾���܂��B
		*/
		virtual Math::Matrix &Frame_GetTransformWorld( Sint32 Index ) = 0;

		/**
			@brief ���f�����̃��b�V�����擾
			@author �t���`
			@return	���f�����̃��b�V���̐�

			���f�����̃��b�V���̐����擾���܂��B<BR>
			���b�V���̐����`��A�N�^�[�̐��ɂȂ�܂��B
		*/
		virtual Sint32 GetMeshCount( void ) = 0;

		/**
			@brief ���f�����̃��b�V���`��ON/OFF
			@author �t���`
			@param Index		[in] ���b�V���ԍ�
			@param IsDrawEnable	[in] �`�悷�邩�ۂ�

			���f�����̃��b�V����`�悷�邩�ǂ�����ݒ肵�܂��B
		*/
		virtual void GetMesh_DrawEnable( Sint32 Index, Bool IsDrawEnable ) = 0;

		/**
			@brief ���b�V�����̃}�e���A�����擾
			@author �t���`
			@param MeshIndex	[in] ���b�V���ԍ�
			@return	���b�V�����̃}�e���A����

			���b�V�����̃}�e���A�������擾���܂��B
		*/
		virtual Sint32 GetMeshMaterialCount( Sint32 MeshIndex ) = 0;

		/**
			@brief �}�e���A���̃V�F�[�_�[�ݒ�
			@author �t���`
			@param MeshIndex		[in] ���b�V���ԍ�
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param pShader			[in] �V�F�[�_�[

			���b�V�����̃}�e���A���̃V�F�[�_�[��ݒ肵�܂��B
		*/
		virtual void MeshMaterial_SetShader( Sint32 MeshIndex, Sint32 MaterialIndex, Renderer::Shader::IShader *pShader ) = 0;

		/**
			@brief �}�e���A���̊g�U���ːF�ݒ�
			@author �t���`
			@param MeshIndex		[in] ���b�V���ԍ�
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param vColor			[in] �F

			���b�V�����̃}�e���A���̊g�U���ːF��ݒ肵�܂��B
		*/
		virtual void MeshMaterial_SetMaterialColor( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector4D &vColor ) = 0;

		/**
			@brief �}�e���A���̎��Ȕ����F�ݒ�
			@author �t���`
			@param MeshIndex		[in] ���b�V���ԍ�
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param vColor			[in] �F

			���b�V�����̃}�e���A���̎��Ȕ����F��ݒ肵�܂��B
		*/
		virtual void MeshMaterial_SetEmissiveColor( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector4D &vColor )										= 0;

		/**
			@brief �}�e���A���̋��ʔ��ːF�ݒ�
			@author �t���`
			@param MeshIndex		[in] ���b�V���ԍ�
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param vColor			[in] �F

			���b�V�����̃}�e���A���̋��ʔ��ːF��ݒ肵�܂��B
		*/
		virtual void MeshMaterial_SetSpecularColor( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector4D &vColor )										= 0;

		/**
			@brief �}�e���A���̋��ʔ��˂̋����ݒ�
			@author �t���`
			@param MeshIndex		[in] ���b�V���ԍ�
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param fParam			[in] ����

			���b�V�����̃}�e���A���̋��ʔ��˂̋�����ݒ肵�܂��B
		*/
		virtual void MeshMaterial_SetSpecularRefractive( Sint32 MeshIndex, Sint32 MaterialIndex, Float fParam )									= 0;

		/**
			@brief �}�e���A���̋��ʔ��˂̍r���ݒ�
			@author �t���`
			@param MeshIndex		[in] ���b�V���ԍ�
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param fParam			[in] �r��

			���b�V�����̃}�e���A���̋��ʔ��˂̍r����ݒ肵�܂��B
		*/
		virtual void MeshMaterial_SetSpecularRoughly( Sint32 MeshIndex, Sint32 MaterialIndex, Float fParam )									= 0;

		/**
			@brief �}�e���A���̕`��^�C�v�ݒ�
			@author �t���`
			@param MeshIndex		[in] ���b�V���ԍ�
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param Type				[in] �`��^�C�v

			���b�V�����̃}�e���A���̕`��^�C�v��ݒ肵�܂��B
		*/
		virtual void MeshMaterial_SetDrawType( Sint32 MeshIndex, Sint32 MaterialIndex, eDrawType Type )											= 0;

		/**
			@brief �}�e���A���̃e�N�X�`���ݒ�
			@author �t���`
			@param MeshIndex		[in] ���b�V���ԍ�
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param pTexture			[in] �e�N�X�`��

			���b�V�����̃}�e���A���̃e�N�X�`����ݒ肵�܂��B
		*/
		virtual void MeshMaterial_SetTexture( Sint32 MeshIndex, Sint32 MaterialIndex, Renderer::ITexture *pTexture )										= 0;

		/**
			@brief �}�e���A���̃e�N�X�`��UV�̃I�t�Z�b�g�ݒ�
			@author �t���`
			@param MeshIndex		[in] ���b�V���ԍ�
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param vOffset			[in] �I�t�Z�b�g�i0.0->1.0)

			���b�V�����̃}�e���A���̃e�N�X�`��UV�̃I�t�Z�b�g��ݒ肵�܂��B
		*/
		virtual void MeshMaterial_SetTextureOffset( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector2D &vOffset )									= 0;

		/**
			@brief �R���W��������
			@author �t���`

			�A�N�^�[�ɑ΂��ẴR���W��������p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			������s����Collision_***()�n�̊֐����L���ɂȂ�܂��B
		*/
		virtual void Collision_Create( void ) = 0;

		/**
			@brief �R���W�����L���ݒ�
			@author �t���`
			@param Index	[in] �t���[���ԍ�
			@param IsEnable	[in] true�̎��R���W����ON�i�f�t�H���g��ON�j

			�w��ԍ��̃t���[���̃R���W������ON/OFF���܂��B
		*/
		virtual void Collision_SetEnable( Sint32 Index, Bool IsEnable ) = 0;

		/**
			@brief �R���W�����L���ݒ�
			@author �t���`
			@param pName	[in] ����
			@param IsEnable	[in] true�̎��R���W����ON�i�f�t�H���g��ON�j

			�w�薼�̃t���[���̃R���W������ON/OFF���܂��B
		*/
		virtual void Collision_SetEnable( const char *pName, Bool IsEnable ) = 0;

		/**
			@brief �R���W�����f�[�^�`��
			@author �t���`
			@param pLine	[in] �`��p���C���v���~�e�B�u�C���^�[�t�F�C�X

			�����蔻��f�[�^�������_�����O���邽�߂̊֐��ł��B
		*/
		virtual void Collision_Rendering( Renderer::Object::ILine3D *pLine ) = 0;

		/**
			@brief �R���W�����̌��ʎ擾
			@author �t���`
			@param FrameNo	[in,out] �Փ˂����t���[���ԍ��i�[��
			@param vPos		[in,out] �Փ˂����ʒu�i�[��

			�����蔻��f�[�^���擾���܂��B<BR>
			�����_�ł͏Փ˂�����܂��Ȉʒu�ƏՓ˂���<BR>
			�t���[���ԍ������擾���邱�Ƃ͂ł��܂���B
		*/
		virtual void Collision_GetResult( Sint32 &FrameNo, Math::Vector3D &vPos ) = 0;

		/**
			@brief �R���W�����`�F�b�N
			@author �t���`
			@param pSrc	[in] �`�F�b�N����IModelActor

			�w�肳�ꂽ�f�[�^�Ƃ̏Փˌ��o���s���܂��B<BR>
			�Փ˂̌��ʂ�Collision_GetResult()�Ŏ擾�ł��܂��B
		*/
		virtual Bool Collision_Check( IModelActor *pSrc ) = 0;

		/**
			@brief �R���W�����`�F�b�N
			@author �t���`
			@param Src	[in] �`�F�b�N����{�b�N�X�f�[�^

			�w�肳�ꂽ�f�[�^�Ƃ̏Փˌ��o���s���܂��B<BR>
			�Փ˂̌��ʂ�Collision_GetResult()�Ŏ擾�ł��܂��B
		*/
		virtual Bool Collision_Check( Collision::CBox &Src ) = 0;

		/**
			@brief �R���W�����`�F�b�N
			@author �t���`
			@param Src	[in] �`�F�b�N���郉�C���f�[�^

			�w�肳�ꂽ�f�[�^�Ƃ̏Փˌ��o���s���܂��B<BR>
			�Փ˂̌��ʂ�Collision_GetResult()�Ŏ擾�ł��܂��B
		*/
		virtual Bool Collision_Check( Collision::CLine3D &Src ) = 0;

		/**
			@brief �R���W�����`�F�b�N
			@author �t���`
			@param Src	[in] �`�F�b�N����_�f�[�^

			�w�肳�ꂽ�f�[�^�Ƃ̏Փˌ��o���s���܂��B<BR>
			�Փ˂̌��ʂ�Collision_GetResult()�Ŏ擾�ł��܂��B
		*/
		virtual Bool Collision_Check( Math::Vector3D &Src ) = 0;

		/**
			@brief �R���W�����`�F�b�N
			@author �t���`
			@param Src			[in] �`�F�b�N����_�f�[�^
			@param pSceneMgr	[in] �����_�����O���s�����V�[���̃C���^�[�t�F�C�X

			�X�N���[�����W�Ƃ̏Փˌ��o���s���܂��B<BR>
			�Փ˂̌��ʂ�Collision_GetResult()�Ŏ擾�ł��܂��B
		*/
		virtual Bool Collision_CheckOnScreen( Math::Vector2D &Src, ISceneManager *pSceneMgr ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out, Collision::CBox &Box ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out, Collision::CBox &Box ) = 0;

		/**
			@brief �R���W�������f���\��
			@author �t���`
			@param pLine		[in] ���C���v���~�e�B�u�C���^�[�t�F�C�X

			�}�b�v���f�������R���W�����f�[�^��Renderer::Object::ILine3D���g����<BR>
			���o����悤�ɕ`�悵�܂��B
		*/
		virtual void CreateCollisionDrawPrimitive( Renderer::Object::ILine3D *pLine ) = 0;
	};
}
}

