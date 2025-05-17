#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �J�X�^���V�[���}�e���A���C���^�[�t�F�C�X
		@author �t���`

		@note
		�J�X�^���V�[���̃A�N�^�[�̃}�e���A�����������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class ICustomizedSceneRenderMaterial
	{
	protected:
		virtual ~ICustomizedSceneRenderMaterial() {}

	public:
		/**
			@brief �V�F�[�_�[�C���^�[�t�F�C�X�擾
			@author �t���`
			@return �V�F�[�_�[�C���^�[�t�F�C�X

			@note
			�}�e���A���Ɋ֘A�t�����Ă���V�F�[�_�[���擾���܂��B
		*/
		virtual Renderer::Shader::IShader *GetShader( void ) = 0;

		/**
			@brief �e�N�X�`���C���^�[�t�F�C�X�擾
			@author �t���`
			@return �e�N�X�`���C���^�[�t�F�C�X

			@note
			�}�e���A���Ɋ֘A�t�����Ă���e�N�X�`�����擾���܂��B
		*/
		virtual Renderer::ITexture *GetTexture( Sint32 Stage ) = 0;

		/**
			@brief �g�U���ːF�擾
			@author �t���`
			@return �g�U���ːF

			@note
			�}�e���A���Ɋ֘A�t�����Ă���g�U���ːF���擾���܂��B
		*/
		virtual Math::Vector4D &GetDiffuseColor( void ) = 0;

		/**
			@brief ���Ȕ����F�擾
			@author �t���`
			@return ���Ȕ����F

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鎩�Ȕ����F���擾���܂��B
		*/
		virtual Math::Vector4D &GetEmissiveColor( void ) = 0;

		/**
			@brief ���ʔ��ːF�擾
			@author �t���`
			@return ���ʔ��ːF

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��ːF���擾���܂��B
		*/
		virtual Math::Vector4D &GetSpecularColor( void ) = 0;

		/**
			@brief �e�N�X�`��UV�I�t�Z�b�g�擾
			@author �t���`
			@return �e�N�X�`��UV�I�t�Z�b�g

			@note
			�}�e���A���Ɋ֘A�t�����Ă���e�N�X�`��UV�I�t�Z�b�g���擾���܂��B
		*/
		virtual Math::Vector2D &GetTextureOffset( void ) = 0;

		/**
			@brief ���ʔ��˔��˗��擾
			@author �t���`
			@return ���ʔ��˔��˗�

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˔��˗����擾���܂��B
		*/
		virtual Float GetSpecularRefractive( void ) = 0;

		/**
			@brief ���ʔ��ˍr���擾
			@author �t���`
			@return ���ʔ��ˍr��

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��ˍr�����擾���܂��B
		*/
		virtual Float GetSpecularRoughly( void ) = 0;

		/**
			@brief �����}�b�v�[�x�擾
			@author �t���`
			@return �����}�b�v�[�x

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鎋���}�b�v�[�x���擾���܂��B
		*/
		virtual Float GetParallaxDepth( void ) = 0;

		/**
			@brief ���ʔ��˃^�C�v�擾
			@author �t���`
			@return ���ʔ��˃^�C�v

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˃^�C�v���擾���܂��B
		*/
		virtual eSpecularType GetSpecularType( void ) = 0;

		/**
			@brief ���ʔ��˔��˗��擾
			@author �t���`
			@return ���ʔ��˔��˗�

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˔��˗����擾���܂��B
		*/
		virtual eBumpType GetBumpType( void ) = 0;

		/**
			@brief ���ʔ��˔��˗��擾
			@author �t���`
			@return ���ʔ��˔��˗�

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˔��˗����擾���܂��B
		*/
		virtual eDrawType GetDrawType( void ) = 0;

		/**
			@brief ���ʔ��˔��˗��擾
			@author �t���`
			@return ���ʔ��˔��˗�

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˔��˗����擾���܂��B
		*/
		virtual eCullType GetCullType( void ) = 0;

		/**
			@brief ���ʔ��˔��˗��擾
			@author �t���`
			@return ���ʔ��˔��˗�

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˔��˗����擾���܂��B
		*/
		virtual Sint32 GetAlphaBoundary( void ) = 0;

		/**
			@brief ���ʔ��˔��˗��擾
			@author �t���`
			@return ���ʔ��˔��˗�

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˔��˗����擾���܂��B
		*/
		virtual Bool GetAlphaTestEnable( void ) = 0;

		/**
			@brief ���ʔ��˔��˗��擾
			@author �t���`
			@return ���ʔ��˔��˗�

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˔��˗����擾���܂��B
		*/
		virtual Bool GetZTestEnable( void ) = 0;

		/**
			@brief ���ʔ��˔��˗��擾
			@author �t���`
			@return ���ʔ��˔��˗�

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˔��˗����擾���܂��B
		*/
		virtual Bool GetZWriteEnable( void ) = 0;

		/**
			@brief ���ʔ��˔��˗��擾
			@author �t���`
			@return ���ʔ��˔��˗�

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˔��˗����擾���܂��B
		*/
		virtual Bool GetLightEnable( void ) = 0;
	};
}
}

