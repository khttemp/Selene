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
		@brief DrawList�p�\����
		@author �t���`

		@note
		DrawList�ŗ��p����\���̂ł��B
	*/
	struct SSpriteListData3D
	{
		Math::Vector3D Pos;
		Float Width;
		Sint32 Angle;
		CColor Color;
	};

	/**
		@brief 3D�X�v���C�g�`��p�C���^�[�t�F�C�X
		@author �t���`

		3D�X�v���C�g�`���ێ����邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class ISprite3D
	{
	public:
		virtual ~ISprite3D() {}

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
			@param mWorld		[in] ���[���h�̕ϊ��s��
			@param Size			[in] �`��T�C�Y
			@param SrcRect		[in] �e�N�X�`����`
			@param Color		[in] �F

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s���܂��B<BR>
			Size�Ŏw�肵���傫���̎l�p�`�|���S����mWorld�ŕϊ����܂��B
		*/
		virtual void Draw( const Math::Matrix &mWorld, const Math::Point2DF &Size, const Math::Rect2DI &SrcRect, CColor Color ) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`
			@param mWorld		[in] ���[���h�̕ϊ��s��
			@param PtTbl		[in] �`��p�S���_�i����|�E��|�����|�E���j
			@param SrcRect		[in] �e�N�X�`����`
			@param Color		[in] �F

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s���܂��B<BR>
			vPosition����ʒu�Ƃ���PtTbl�Ŏw�肵���傫���̋�`�����mWorld�ŕϊ����܂��B
		*/
		virtual void Draw( const Math::Matrix &mWorld, const Math::Vector2D PtTbl[], const Math::Rect2DI &SrcRect, CColor Color ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param vCameraPosition	[in] �J�����̈ʒu
			@param Pos				[in] �`��ʒu�̔z��
			@param Color			[in] �`��F�̔z��
			@param Count			[in] �e�v�f�̔z��
			@param Width			[in] ���_���Ƃ̕�
			@param Src				[in] �]�����e�N�X�`���̋�`

			�J�����̈ʒu�ɉ����Ď�����]�������s��ꂽ<BR>
			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawPolyLine( const Math::Vector3D &vCameraPosition, const Math::Vector3D Pos[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param vCameraPosition	[in] �J�����̈ʒu
			@param Pos				[in] �`��ʒu�̔z��
			@param Color			[in] �`��F�̔z��
			@param Width			[in] ���_���Ƃ̕�
			@param Count			[in] �e�v�f�̔z��
			@param Src				[in] �]�����e�N�X�`���̋�`

			�J�����̈ʒu�ɉ����Ď�����]�������s��ꂽ<BR>
			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawPolyLine( const Math::Vector3D &vCameraPosition, const Math::Vector3D Pos[], const CColor Color[], const Float Width[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param vCameraPosition	[in] �J�����̈ʒu
			@param List				[in] ���_���Ƃ̔z��
			@param Count			[in] �e�v�f�̔z��
			@param Src				[in] �]�����e�N�X�`���̋�`

			�J�����̈ʒu�ɉ����Ď�����]�������s��ꂽ<BR>
			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawPolyLine( const Math::Vector3D &vCameraPosition, const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param Pos		[in] �`��ʒu�̔z��
			@param Angle	[in] 1��65536�Ƃ�����]�p�x�̔z��
			@param Color	[in] �`��F�̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Width	[in] ���_���Ƃ̕�
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawListXY( const Math::Vector3D Pos[], const Sint32 Angle[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param Pos		[in] �`��ʒu�̔z��
			@param Angle	[in] 1��65536�Ƃ�����]�p�x�̔z��
			@param Color	[in] �`��F�̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Width	[in] ���_���Ƃ̕�
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawListYZ( const Math::Vector3D Pos[], const Sint32 Angle[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param Pos		[in] �`��ʒu�̔z��
			@param Angle	[in] 1��65536�Ƃ�����]�p�x�̔z��
			@param Color	[in] �`��F�̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Width	[in] ���_���Ƃ̕�
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawListZX( const Math::Vector3D Pos[], const Sint32 Angle[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param Pos		[in] �`��ʒu�̔z��
			@param Width	[in] ���_���Ƃ̕��̔z��
			@param Angle	[in] 1��65536�Ƃ�����]�p�x�̔z��
			@param Color	[in] �`��F�̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawListXY( const Math::Vector3D Pos[], const Float Width[], const Sint32 Angle[], const CColor Color[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param Pos		[in] �`��ʒu�̔z��
			@param Width	[in] ���_���Ƃ̕��̔z��
			@param Angle	[in] 1��65536�Ƃ�����]�p�x�̔z��
			@param Color	[in] �`��F�̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawListYZ( const Math::Vector3D Pos[], const Float Width[], const Sint32 Angle[], const CColor Color[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param Pos		[in] �`��ʒu�̔z��
			@param Width	[in] ���_���Ƃ̕��̔z��
			@param Angle	[in] 1��65536�Ƃ�����]�p�x�̔z��
			@param Color	[in] �`��F�̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawListZX( const Math::Vector3D Pos[], const Float Width[], const Sint32 Angle[], const CColor Color[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param List		[in] ���_���Ƃ̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawListXY( const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param List		[in] ���_���Ƃ̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawListYZ( const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param List		[in] ���_���Ƃ̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawListZX( const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src ) = 0;
	};
}
}
}
