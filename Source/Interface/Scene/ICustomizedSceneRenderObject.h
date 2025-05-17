#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Matrix.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �J�X�^���V�[���`��I�u�W�F�N�g�C���^�[�t�F�C�X
		@author �t���`

		@note
		�J�X�^���V�[���̕`��I�u�W�F�N�g���������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class ICustomizedSceneRenderObject : public IInterface
	{
	protected:
		virtual ~ICustomizedSceneRenderObject() {}

	public:
		/**
			@brief �{�[���p���_�̗L�����擾
			@author �t���`
			@retval false	����
			@retval true	�L��

			@note
			�`��I�u�W�F�N�g���{�[���p���_�������Ă��邩���擾���܂��B
		*/
		virtual Bool IsSupportVertexBone( void ) = 0;

		/**
			@brief �e�N�X�`���p���_�̗L�����擾
			@author �t���`
			@retval false	����
			@retval true	�L��

			@note
			�`��I�u�W�F�N�g���e�N�X�`���p���_�������Ă��邩���擾���܂��B
		*/
		virtual Bool IsSupportVertexTexture( void ) = 0;

		/**
			@brief �@���p���_�̗L�����擾
			@author �t���`
			@retval false	����
			@retval true	�L��

			@note
			�`��I�u�W�F�N�g���@���p���_�������Ă��邩���擾���܂��B
		*/
		virtual Bool IsSupportVertexNormal( void ) = 0;

		/**
			@brief �o���v�p�ڐ��p���_�̗L�����擾
			@author �t���`
			@retval false	����
			@retval true	�L��

			@note
			�`��I�u�W�F�N�g���o���v�p�ڐ��p���_�������Ă��邩���擾���܂��B
		*/
		virtual Bool IsSupportVertexBump( void ) = 0;

		/**
			@brief �}�e���A�����擾
			@author �t���`
			@return �}�e���A����

			@note
			�`��I�u�W�F�N�g�����L����}�e���A�������擾���܂��B
		*/
		virtual Sint32 GetMaterialCount( void ) = 0;

		/**
			@brief �`��}�e���A���擾
			@author �t���`
			@param Index	[in] �}�e���A���ԍ�

			@note
			�`��I�u�W�F�N�g�����L����}�e���A���f�[�^���擾���܂��B
		*/
		virtual ICustomizedSceneRenderMaterial *GetMaterialPointer( Sint32 Index ) = 0;

		/**
			@brief �{�[�������擾
			@author �t���`
			@return �{�[����

			@note
			�`��I�u�W�F�N�g���������Ă���{�[�������擾���܂��B
		*/
		virtual Sint32 GetBoneCount( void ) = 0;

		/**
			@brief ���[���h�s��擾
			@author �t���`
			@return ���[���h�s��

			@note
			�`��I�u�W�F�N�g�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::Matrix &GetWorldMatrix( void ) = 0;


		/**
			@brief �O�t���[���̃��[���h�s��擾
			@author �t���`
			@return ���[���h�s��

			@note
			�`��I�u�W�F�N�g�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::Matrix &GetWorldMatrixPrev( void ) = 0;

		/**
			@brief ���[���h���r���[�s��擾
			@author �t���`
			@return ���[���h���r���[�s��

			@note
			�`��I�u�W�F�N�g�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::Matrix &GetWorldViewMatrix( void ) = 0;

		/**
			@brief �O�t���[���̃��[���h���r���[�s��擾
			@author �t���`
			@return ���[���h���r���[�s��

			@note
			�`��I�u�W�F�N�g�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::Matrix &GetWorldViewPrevMatrix( void ) = 0;

		/**
			@brief ���[���h���r���[���v���W�F�N�V�����s��擾
			@author �t���`
			@return ���[���h���r���[���v���W�F�N�V�����s��

			@note
			�`��I�u�W�F�N�g�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::Matrix &GetWorldViewProjectionMatrix( void ) = 0;

		/**
			@brief �O�t���[���̃��[���h���r���[���v���W�F�N�V�����s��擾
			@author �t���`
			@return ���[���h���r���[���v���W�F�N�V�����s��

			@note
			�`��I�u�W�F�N�g�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::Matrix &GetWorldViewProjectionPrevMatrix( void ) = 0;

		/**
			@brief ���[���h�t�s��擾
			@author �t���`
			@return ���[���h�t�s��

			@note
			�`��I�u�W�F�N�g�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::Matrix &GetWorldInverseMatrix( void ) = 0;

		/**
			@brief �O�t���[���̃��[���h�t�s��擾
			@author �t���`
			@return ���[���h�t�s��

			@note
			�`��I�u�W�F�N�g�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::Matrix &GetWorldInverseMatrixPrev( void ) = 0;

		/**
			@brief �{�[���p�ϊ��s��擾
			@author �t���`
			@return �{�[���ϊ��s��

			@note
			�`��I�u�W�F�N�g�̃{�[���p�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::SMatrix4x4 *GetBoneMatrixArray( void ) = 0;

		/**
			@brief �O�t���[���̃{�[���p�ϊ��s��擾
			@author �t���`
			@return �{�[���ϊ��s��

			@note
			�`��I�u�W�F�N�g�̃{�[���p�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::SMatrix4x4 *GetBoneMatrixArrayPrev( void ) = 0;

		/**
			@brief �����_�����O�p���_�f�[�^�ݒ�
			@author �t���`
			@param pRender		[in] �֘A����IRender�C���^�[�t�F�C�X

			@note
			�����_�����O���s�����߂̒��_�X�g���[���̐ݒ���s���܂��B
		*/
		virtual void SetStreamSource( Renderer::IRender *pRender ) = 0;

		/**
			@brief �ʏ탌���_�����O
			@author �t���`
			@param MaterialNo	[in] �`�悷��}�e���A���ԍ�
			@param pRender		[in] �֘A����IRender�C���^�[�t�F�C�X

			@note
			�ʏ�̃����_�����O�������s���܂��B
		*/
		virtual Sint32 Rendering( Sint32 MaterialNo, Renderer::IRender *pRender ) = 0;

		/**
			@brief ���x�}�b�v�p�k�ރ|���S�����背���_�����O
			@author �t���`
			@param pRender	[in] �֘A����IRender�C���^�[�t�F�C�X

			@note
			���x�}�b�v�`��p�̏k�ރ|���S������̃����_�����O���s���܂��B
		*/
		virtual Sint32 Rendering_Velocity( Renderer::IRender *pRender ) = 0;

		/**
			@brief ���_�ϊ��^�C�v���擾
			@author �t���`
			@retval false	����
			@retval true	�L��

			@note
			�`��I�u�W�F�N�g�̒��_�ϊ��^�C�v���擾���܂��B
		*/
		virtual eTransformType GetTransformType( void ) = 0;

		/**
			@brief �\�t�g�p�[�e�B�N���̗L�����擾
			@author �t���`
			@retval false	�\�t�g�p�[�e�B�N���ł͂Ȃ�
			@retval true	�\�t�g�p�[�e�B�N��

			@note
			�`��I�u�W�F�N�g���\�t�g�p�[�e�B�N�����ǂ������擾���܂��B
		*/
		virtual Bool GetSoftBillboardEnable( void ) = 0;

		/**
			@brief �����o���v�}�b�v�̗L�����擾
			@author �t���`
			@retval false	����
			@retval true	�L��

			@note
			�`��I�u�W�F�N�g�������o���v�}�b�v�������Ă��邩���擾���܂��B
		*/
		virtual Bool GetParallaxEnable( void ) = 0;

		/**
			@brief �X�y�L�����[�ݒ�̗̂L�����擾
			@author �t���`
			@retval false	����
			@retval true	�L��

			@note
			�`��I�u�W�F�N�g���X�y�L�����[�ݒ�̂������Ă��邩���擾���܂��B
		*/
		virtual Bool GetSpecularEnable( void ) = 0;

		/**
			@brief ���}�b�v�ݒ�̗̂L�����擾
			@author �t���`
			@retval false	����
			@retval true	�L��

			@note
			�`��I�u�W�F�N�g�����}�b�v�ݒ�̂������Ă��邩���擾���܂��B
		*/
		virtual Bool GetEnvironmentEnable( void ) = 0;

		/**
			@brief ���X�g�ɂȂ���Ă��鎟�̕`��I�u�W�F�N�g���擾
			@author �t���`
			@return �`��I�u�W�F�N�g�C���^�[�t�F�C�X

			@note
			���X�g�ɂȂ���Ă���`��I�u�W�F�N�g�̎����̎��̕`��I�u�W�F�N�g���擾���܂��B
		*/
		virtual ICustomizedSceneRenderObject *GetNextObject( void ) = 0;
	};
}
}

