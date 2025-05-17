#pragma once


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
		@brief �J�X�^���V�[���Ǘ��p�C���^�[�t�F�C�X
		@author �t���`

		@note
		�J�X�^���V�[���Ǘ����s�����߂̃C���^�[�t�F�C�X�ł��B
	*/
	class ICustomizedSceneManager : public IInterface
	{
	protected:
		virtual ~ICustomizedSceneManager() {}

	public:
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
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject			[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@param InstanceCount	[in] �C���X�^���X��
			@return	IInstanceModelActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			�W�I���g���C���X�^���V���O���s�����߂̓���ȃA�N�^�[�ŁA<BR>
			���̃A�N�^�[���炳��Ɍʂ̃R���g���[���[���擾���A���[���h�ϊ���{�[���̐ݒ���s���܂��B
		*/
		virtual IInstanceModelActor *CreateActor( Renderer::Object::IModel *pObject, Sint32 InstanceCount ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IModelActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IModelActor���o�R���čs���܂��B
		*/
		virtual IModelActor *CreateActor( Renderer::Object::IModel *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IMapActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IMapActor���o�R���čs���܂��B
		*/

		virtual IMapActor *CreateActor( Renderer::Object::IMapModel *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IPrimitiveActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IPrimitiveActor���o�R���čs���܂��B
		*/
		virtual IPrimitiveActor *CreateActor( Renderer::Object::IPoint3D *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IPrimitiveActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IPrimitiveActor���o�R���čs���܂��B
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
			���[���h�ϊ��⃌���_�����O�̑����IPrimitiveActor���o�R���čs���܂��B
		*/
		virtual IPrimitiveActor *CreateActor( Renderer::Object::IPrimitive3D *pObject, Bool IsLightmap = false, Bool IsNormalmap = false, Bool IsSpecularmap = false, Bool IsEnvironmentmap = false ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	ISpriteActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����ISpriteActor���o�R���čs���܂��B
		*/
		virtual ISpriteActor *CreateActor( Renderer::Object::ISprite3D *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IParticleActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IParticleActor���o�R���čs���܂��B
		*/
		virtual IParticleActor *CreateActor( Renderer::Object::IFontSprite3D *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IParticleActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IParticleActor���o�R���čs���܂��B
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
			@brief �V�[�������_�����O�J�n
			@author �t���`
			@retval false	�V�[���Ƀ����_�����O����I�u�W�F�N�g���Ȃ�
			@retval	true	�V�[���Ƀ����_�����O����I�u�W�F�N�g������

			@note
			�V�[���̃����_�����O���J�n���鎖��錾���܂��B<BR>
			���̊֐���true��Ԃ����ꍇ�͕K��RedneringEnd()���R�[�����ĉ������B
		*/
		virtual Bool RenderingStart( void ) = 0;

		/**
			@brief �V�[�������_�����O�I��
			@author �t���`

			@note
			�V�[���̃����_�����O���I�����鎖��錾���܂��B
		*/
		virtual void RenderingExit( void ) = 0;

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

		/**
			@brief �A�N�^�[�I�u�W�F�N�g�̃��C���[���擾
			@author �t���`
			@return �A�N�^�[�I�u�W�F�N�g�̃��C���[��

			@note
			�����_�����O����A�N�^�[�I�u�W�F�N�g�̃��C���[�����擾���܂��B<BR>
			���C���[�����̂�3�ŌŒ肳��Ă���A�����I�ɉ��̂悤�ɌŒ肳��Ă��܂�<BR>
			0=���g�p<BR>
			1=�s�������f��<BR>
			2=���������f��
		*/
		virtual Sint32 GetRenderObjectLayerCount( void ) = 0;

		/**
			@brief �A�N�^�[�I�u�W�F�N�g�̎擾
			@author �t���`
			@param Layer	[in] �I�u�W�F�N�g���C���[
			@return �A�N�^�[�I�u�W�F�N�g

			@note
			�����_�����O����A�N�^�[�I�u�W�F�N�g���擾���܂��B
		*/
		virtual ICustomizedSceneRenderObject *GetRenderObject( Sint32 Layer ) = 0;
	};
}
}

