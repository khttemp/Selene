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
		@brief �V�[���J��������p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���̃J�����𑀍삷�邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class ICamera
	{
	public:
		virtual ~ICamera() {}

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
			@brief ���[���h���X�N���[�����W�ϊ��s��擾
			@author �t���`
			@return �ϊ��s��

			���[���h��Ԃ���X�N���[�����W�ւ̋t�ϊ��s����擾���܂��B
		*/
		virtual const Math::Matrix &WorldToScreen( void ) = 0;

		/**
			@brief ���[���h���r���[�ϊ��s��擾
			@author �t���`
			@return �ϊ��s��

			���[���h��Ԃ���J������Ԃւ̋t�ϊ��s����擾���܂��B
		*/
		virtual const Math::Matrix &WorldToView( void ) = 0;

		/**
			@brief �X�N���[�������[���h�ϊ��s��擾
			@author �t���`
			@return �ϊ��s��

			�X�N���[�����W���烏�[���h��Ԃւ̋t�ϊ��s����擾���܂��B
		*/
		virtual const Math::Matrix &ScreenToWorld( void ) = 0;

		/**
			@brief �r���[�����[���h�ϊ��s��擾
			@author �t���`
			@return �ϊ��s��

			�J������Ԃ��烏�[���h��Ԃւ̋t�ϊ��s����擾���܂��B
		*/
		virtual const Math::Matrix &ViewToWorld( void ) = 0;

		/**
			@brief �J�����ʒu�擾
			@author �t���`
			@return �J�����ʒu�x�N�g��

			���[���h��Ԃł̃J�����̈ʒu���擾���܂��B
		*/
		virtual const Math::Vector3D &Position( void ) = 0;

		/**
			@brief �j�A�N���b�v�l�擾
			@author �t���`

			@return �j�A�N���b�v�l

			�j�A�N���b�v�l���擾���܂��B
		*/
		virtual Float GetNearClip( void ) = 0;

		/**
			@brief �t�@�[�N���b�v�l�擾
			@author �t���`

			@return �t�@�[�N���b�v�l

			�t�@�[�N���b�v�l���擾���܂��B
		*/
		virtual Float GetFarClip( void ) = 0;

		/**
			@brief �v���W�F�N�V�����s��X�V
			@author �t���`

			@param fNearClip	[in] �j�A�N���b�v�l
			@param fFarClip		[in] �t�@�[�N���b�v�l
			@param FovAngle		[in] ��p�i1��65536�Ƃ����p�x�j
			@param Width		[in] �\������
			@param Height		[in] �\���c��

			�v���W�F�N�V�����s����X�V���܂��B<BR>
			�J�������g�p����ꍇ�ɂ͕K�����̊֐��Ńv���W�F�N�V�������쐬���ĉ������B<BR>
			�܂�FovAngle��0���w�肷��ƕ��s���e�ɂȂ�܂��B
		*/
		virtual void UpdateProjection( Float fNearClip, Float fFarClip, Sint32 FovAngle, Sint32 Width, Sint32 Height ) = 0;

		/**
			@brief �J�����f�[�^������
			@author �t���`

			�J�����f�[�^�����������܂��B<BR>
			���W(0,0,0)����Z��+��������������ԂɂȂ�܂��B
		*/
		virtual void Reset( void ) = 0;

		/**
			@brief �J�����f�[�^�X�V
			@author �t���`

			�J�����̃f�[�^���X�V���܂��B<BR>
			�e��s���o�E���f�B���O�{�b�N�X�Ȃǂ�<BR>
			���̊֐����Ăяo�����Ƃō쐬����܂��B
		*/
		virtual void Update( void ) = 0;

		/**
			@brief �J������ϊ�
			@author �t���`

			@param vPosition	[in] �J�����̌��݈ʒu
			@param vTarget		[in] �J�����̃^�[�Q�b�g�ʒu
			@param Bank			[in] �o���N(�X��)�p�x

			CStyle���g�킸���ڃJ�����̎p������ݒ肵�܂��B
		*/
		virtual void SetTransformSimple( Math::Vector3D &vPosition, Math::Vector3D &vTarget, Sint32 Bank ) = 0;

		/**
			@brief �J������ϊ�
			@author �t���`

			@param Style	[in] �J�����ϊ��pStyle

			CStyle�f�[�^�Œ�`���ꂽ�ϊ�������<BR>
			�J�����ɓK�p���܂��B<BR>
			�J�����Ŏg�p�����͈̂ړ�/��]�ɂȂ�܂��B
		*/
		virtual void SetTransform( Math::Style &Style ) = 0;

		/**
			@brief �J�����O�p�o�E���f�B���O�����_�����O
			@author �t���`
			@param pLine	[in] ���C���v���~�e�B�u�C���^�[�t�F�C�X

			�o�E���f�B���O�{�b�N�X���w�肵�����C���f�[�^�ɑ΂��Ēǉ����܂��B
		*/
		virtual void RenderingBounding( Renderer::Object::ILine3D *pLine ) = 0;
	};
}
}

