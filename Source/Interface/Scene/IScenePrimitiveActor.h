#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Style.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �V�[���v���~�e�B�u�A�N�^�[�p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���Ǘ����ꂽ�v���~�e�B�u�A�N�^�[�������ׂ̃C���^�[�t�F�C�X�ł��B
	*/
	class IPrimitiveActor : public Math::Style
	{
	public:
		virtual ~IPrimitiveActor() {}

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
			@brief ���W�ϊ�������
			@author �t���`

			�A�N�^�[�̍��W�ϊ������������܂��B<BR>
			�A�j���[�V�����̏��Ȃǂ����̊֐����ł��ׂď���������܂��B
		*/
		virtual void TransformReset( void )	 = 0;

		/**
			@brief ���W�ϊ��X�V
			@author �t���`

			�A�N�^�[�̍��W�ϊ����X�V���܂��B<BR>
			�A�j���[�V�����̏��Ȃǂ����̊֐����ł��ׂčX�V����܂��B
		*/
		virtual void TransformUpdate( void ) = 0;

		/**
			@brief �{�[���ϊ��s���ݒ�
			@author �t���`
			@param pMatrix	[in] �{�[���s��̔z��
			@param Count	[in] �{�[���s��̐�

			�A�N�^�[�ɑ΂��ă{�[���̕ϊ��s���ݒ肵�܂��B<BR>
			�{�[���f�[�^������IPrimitive3D�ɑ΂��Ă̂ݗL���ł��B
		*/
		virtual void SetBoneMatrixArray( Math::Matrix *pMatrix, Sint32 Count ) = 0;

		/**
			@brief �V�F�[�_�[��ݒ�
			@author �t���`
			@param pShader	[in] �V�F�[�_�[�C���^�[�t�F�C�X

			�A�N�^�[�ɑ΂��ĔC�ӂ̃V�F�[�_�[��ݒ肵�܂��B
		*/
		virtual void SetShader( Renderer::Shader::IShader *pShader ) = 0;

		/**
			@brief �}�e���A���̊g�U���ːF�ݒ�
			@author �t���`
			@param vColor			[in] �F

			���b�V�����̃}�e���A���̊g�U���ːF��ݒ肵�܂��B
		*/
		virtual void SetMaterialColor( Math::Vector4D &vColor ) = 0;

		/**
			@brief �}�e���A���̎��Ȕ����F�ݒ�
			@author �t���`
			@param vColor			[in] �F

			���b�V�����̃}�e���A���̎��Ȕ����F��ݒ肵�܂��B
		*/
		virtual void SetEmissiveColor( Math::Vector4D &vColor )										= 0;

		/**
			@brief �}�e���A���̋��ʔ��ːF�ݒ�
			@author �t���`
			@param vColor			[in] �F

			���b�V�����̃}�e���A���̋��ʔ��ːF��ݒ肵�܂��B
		*/
		virtual void SetSpecularColor( Math::Vector4D &vColor )										= 0;

		/**
			@brief �}�e���A���̋��ʔ��˂̋����ݒ�
			@author �t���`
			@param fParam			[in] ����

			���b�V�����̃}�e���A���̋��ʔ��˂̋�����ݒ肵�܂��B
		*/
		virtual void SetSpecularRefractive( Float fParam )									= 0;

		/**
			@brief �}�e���A���̋��ʔ��˂̍r���ݒ�
			@author �t���`
			@param fParam			[in] �r��

			���b�V�����̃}�e���A���̋��ʔ��˂̍r����ݒ肵�܂��B
		*/
		virtual void SetSpecularRoughly( Float fParam )									= 0;
	};
}
}

