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
namespace Renderer
{
namespace Object
{
	/**
		@brief 3D�X�v���C�g�`��p�C���^�[�t�F�C�X
		@author �t���`

		3D�X�v���C�g�`���ێ����邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IParticle
	{
	public:
		virtual ~IParticle() {}

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
			@brief ��ʒu�ݒ�
			@author �t���`
			@param vPos		[in] ��ʒu

			�����o�b�t�@�ɑ΂���S�Ă̊�ƂȂ�ʒu��ݒ肵�܂��B<BR>
			�����Ŏw�肳�ꂽ�ʒu�̓\�[�g�ɂ����p����܂��B
		*/
		virtual void SetBasePosition( const Math::Vector3D &vPos ) = 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void ) = 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void ) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`
			@param vPosition	[in] �X�v���C�g�̈ʒu
			@param Size			[in] �`��T�C�Y
			@param SrcRect		[in] �e�N�X�`����`
			@param Color		[in] �F

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s���܂��B<BR>
			vPosition����ʒu�Ƃ���Size�Ŏw�肵���傫���̋�`�����A
			�J�����̕��֌����悤�ɒ��_�V�F�[�_�[�Ōv�Z����܂��B
		*/
		virtual void Draw( const Math::Vector3D &vPosition, const Math::Point2DF &Size, const Math::Rect2DI &SrcRect, CColor Color ) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`
			@param vPosition	[in] �X�v���C�g�̈ʒu
			@param PtTbl		[in] �`��p�S���_�i����|�E��|�����|�E���j
			@param SrcRect		[in] �e�N�X�`����`
			@param Color		[in] �F

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s���܂��B<BR>
			vPosition����ʒu�Ƃ���PtTbl�Ŏw�肵���傫���̋�`�����A
			�J�����̕��֌����悤�ɒ��_�V�F�[�_�[�Ōv�Z����܂��B
		*/
		virtual void Draw( const Math::Vector3D &vPosition, const Math::Vector2D PtTbl[], const Math::Rect2DI &SrcRect, CColor Color ) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`
			@param vPosition	[in] �X�v���C�g�̈ʒu
			@param Size			[in] �`��T�C�Y
			@param SrcRect		[in] �e�N�X�`����`
			@param Color		[in] �F
			@param Angle		[in] ��]�p�x

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s���܂��B<BR>
			vPosition����ʒu�Ƃ���Size�Ŏw�肵���傫���̋�`�����A
			�J�����̕��֌����悤�ɒ��_�V�F�[�_�[�Ōv�Z����܂��B
		*/
		virtual void DrawRotate( const Math::Vector3D &vPosition, const Math::Point2DF &Size, const Math::Rect2DI &SrcRect, CColor Color, Sint32 Angle ) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`
			@param vPosition	[in] �X�v���C�g�̈ʒu
			@param PtTbl		[in] �`��p�S���_�i����|�E��|�����|�E���j
			@param SrcRect		[in] �e�N�X�`����`
			@param Color		[in] �F
			@param Angle		[in] ��]�p�x

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s���܂��B<BR>
			vPosition����ʒu�Ƃ���PtTbl�Ŏw�肵���傫���̋�`�����A
			�J�����̕��֌����悤�ɒ��_�V�F�[�_�[�Ōv�Z����܂��B
		*/
		virtual void DrawRotate( const Math::Vector3D &vPosition, const Math::Vector2D PtTbl[], const Math::Rect2DI &SrcRect, CColor Color, Sint32 Angle ) = 0;
	};
}
}
}
