#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �r�f�I�J�[�h�Ǘ��C���^�[�t�F�C�X
		@author �t���`
	*/
	class IGraphicCard
	{
	public:
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
			@brief 16Bit�J���[���[�h���g�p
			@author �t���`

			�t���X�N���[�����̉�ʃJ���[��32Bit�ł͂Ȃ�16Bit�ɂ��܂��B<BR>
			�t�B�����[�g�̌��������ő��x�̌��オ�]�߂܂����A<BR>
			�}�b�n�o���h�Ȃǂ̉掿�I�Ȗ����o�܂��B
		*/
		virtual void EnableHighlColorScreen( void ) = 0;

		/**
			@brief �s�N�Z���V�F�[�_�[���T�|�[�g����Ă��邩�擾
			@author �t���`
			@param Major	[in] ���W���[�o�[�W����
			@param Minor	[in] �}�C�i�[�o�[�W����

			���݂̃f�o�C�X�Ŏw�肵���s�N�Z���V�F�[�_�[���T�|�[�g<BR>
			���Ă��邩�ǂ������擾���܂��B
		*/
		virtual Bool GetPixelShaderSupport( Uint16 Major, Uint16 Minor ) = 0;

		/**
			@brief ��ʉ𑜓x���擾
			@author �t���`
			@param IsFullColor	[in] �t���J���[(32Bit)�̉�ʉ𑜓x���ۂ�
			@return ��ʉ𑜓x��

			�g�p�\�ȉ�ʉ𑜓x�̐����擾�ł��܂��B<BR>
			IsFullColor�t���O�ɉ����āA16Bit/32Bit�J���[�̉�ʉ𑜓x�����擾�o���܂��B
		*/
		virtual Sint32 GetScreenModeCount( Bool IsFullColor ) = 0;

		/**
			@brief ��ʉ𑜓x
			@author �t���`
			@param IsFullColor	[in] �t���J���[(32Bit)�̉�ʉ𑜓x���ۂ�
			@param No			[in] ��ʉ𑜓x�̃C���f�b�N�X�i�ő吔��GetScreenModeCount()�Ŏ擾�j
			@param Width		[out] ��ʉ����i�[��
			@param Height		[out] ��ʏc���i�[��

			�g�p�\�ȉ�ʉ𑜓x���擾���܂��B
		*/
		virtual void GetScreenMode( Bool IsFullColor, Sint32 No, Sint32 &Width, Sint32 &Height ) = 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y���擾
			@author �t���`
			@return �����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y��

			�g�p�\�ȃ����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y�̐����擾�ł��܂��B
		*/
		virtual Sint32 CreateRenderTargetTextureSizeCount( void ) = 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y
			@author �t���`
			@param No			[in] �����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y�̃C���f�b�N�X�i�ő吔��CreateRenderTargetTextureSizeCount()�Ŏ擾�j
			@param pWidth		[out] ��ʉ����i�[��
			@param pHeight		[out] ��ʏc���i�[��

			�g�p�\�ȃ����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y���擾���܂��B
		*/
		virtual void CreateRenderTargetTextureSize( Sint32 No, Sint32 *pWidth, Sint32 *pHeight ) = 0;

		/**
			@brief �O���t�B�b�N�J�[�h���̎擾
			@author �t���`
			@param pName		[out] ���̊i�[��
			@param NameSize		[in] pName�̃o�b�t�@�T�C�Y

			�ڑ�����Ă���O���t�B�b�N�J�[�h�̖��̂��擾���܂��B
		*/
		virtual void GetGraphicCardName( char *pName, Sint32 NameSize ) = 0;

		/**
			@brief ���_�V�F�[�_�[�̃o�[�W�������擾
			@author �t���`
			@param pName		[out] �o�[�W�����i�[��
			@param NameSize		[in] pName�̃o�b�t�@�T�C�Y

			�ڑ�����Ă���O���t�B�b�N�J�[�h�̒��_�V�F�[�_�[�̃o�[�W�������擾���܂��B
		*/
		virtual void GetVertexShaderVersion( char *pName, Sint32 NameSize ) = 0;

		/**
			@brief �s�N�Z���V�F�[�_�[�̃o�[�W�������擾
			@author �t���`
			@param pName		[out] �o�[�W�����i�[��
			@param NameSize		[in] pName�̃o�b�t�@�T�C�Y

			�ڑ�����Ă���O���t�B�b�N�J�[�h�̃s�N�Z���V�F�[�_�[�̃o�[�W�������擾���܂��B
		*/
		virtual void GetPixelShaderVersion( char *pName, Sint32 NameSize ) = 0;

		/**
			@brief IRender�C���^�[�t�F�C�X����
			@author �t���`
			@param IsLockEnableBackBuffer	[in] �o�b�N�o�b�t�@�̃��b�N�L��
			@param IsWaitVSync				[in] ��ʍX�V����VSYNC��҂�
			@return IRender�C���^�[�t�F�C�X

			�O���t�B�b�N�J�[�h��̃����_���[����p��IRender�C���^�[�t�F�C�X���擾���܂��B<BR>
			IRender�C���^�[�t�F�C�X�͂P��IGraphicCard�ɑ΂��ĂP�������݂��܂���B
		*/
		virtual Renderer::IRender *CreateRender( Bool IsLockEnableBackBuffer = false, Bool IsWaitVSync = true ) = 0;
	};
}

