#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/2D/IPrimitive2D.h"


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
	struct SSpriteListData2D
	{
		Math::Vector2D Pos;
		Float Width;
		Sint32 Angle;
		CColor Color;
	};

	/**
		@brief 2D�X�v���C�g�Ǘ��C���^�[�t�F�C�X
		@author �t���`

		2D�X�v���C�g�`��p�̃C���^�[�t�F�C�X�ł��B
	*/
	class ISprite2D
	{
	public:
		virtual ~ISprite2D() {}

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
		virtual Sint32 AddRef( void ) = 0;

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
			@brief �����_�����O
			@author �t���`

			�����o�b�t�@�̓��e�̃����_�����O���s���܂��B
		*/
		virtual void Rendering( void ) = 0;

		/**
			@brief ���_���N�G�X�g���擾
			@author �t���`
			@return ���N�G�X�g�������_��

			Push�����ő咸�_�����擾���܂��B
		*/
		virtual Sint32 GetRequestedVertexCount( void ) = 0;

		/**
			@brief ���_���N�G�X�g���擾
			@author �t���`
			@return ���N�G�X�g�������_��

			Push�����ő咸�_�����擾���܂��B
		*/
		virtual Sint32 GetRequestedVertexCountMax( void ) = 0;

		/**
			@brief �����o�b�t�@�փf�[�^�ǉ�
			@author �t���`
			@param pPrimitive	[in] �v���~�e�B�u�f�[�^
			@param Count		[in] �ǉ���

			�����o�b�t�@�̃f�[�^�̒ǉ����s���܂��B<BR>
			���̊֐����Ăяo���O�ɕK��Being�֐��Ńf�[�^�ǉ��̊J�n��錾���ĉ������B
		*/
		virtual Bool Push( SPrimitiveVertex2D *pPrimitive, Sint32 Count ) = 0;

		/**
			@brief �����p�e�N�X�`���̐ݒ�
			@author �t���`

			@param pTex		[in] �e�N�X�`���C���^�[�t�F�C�X

			�����p�̃e�N�X�`����ݒ肵�܂��B
		*/
		virtual void SetDecoration( ITexture *pTex ) = 0;

		/**
			@brief �l�p�`�`��
			@author �t���`

			@param DstRect		[in] �]����X�N���[���̋�`
			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Color		[in] ���_�F

			�ł��P���ȃX�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawSquare( Math::Rect2DF &DstRect, Math::Rect2DF &SrcRect, CColor Color ) = 0;

		/**
			@brief ��]�t���l�p�`�`��
			@author �t���`

			@param DstRect		[in] �]����X�N���[���̋�`
			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Color		[in] ���_�F
			@param Angle		[in] 1��65536�Ƃ�����]�p�x

			��]�t���X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawSquareRotate( Math::Rect2DF &DstRect, Math::Rect2DF &SrcRect, CColor Color, Sint32 Angle ) = 0;

		/**
			@brief ��]�t���l�p�`�`��
			@author �t���`

			@param DstRect		[in] �]����X�N���[���̋�`
			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Color		[in] ���_�F
			@param AngleX		[in] 1��65536�Ƃ�����]�p�x
			@param AngleY		[in] 1��65536�Ƃ�����]�p�x
			@param AngleZ		[in] 1��65536�Ƃ�����]�p�x

			��]�t���X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawSquareRotateXYZ( Math::Rect2DF &DstRect, Math::Rect2DF &SrcRect, CColor Color, Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ ) = 0;

		/**
			@brief �s��ϊ��l�p�`�`��
			@author �t���`

			@param mWorld		[in] �ϊ��s��
			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Color		[in] ���_�F

			�s��ϊ��t���X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawSquareMatrix( Math::Matrix &mWorld, Math::Rect2DF &SrcRect, CColor Color ) = 0;

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
		virtual void DrawList( Math::Point2DF Pos[], Sint32 Angle[], CColor Color[], Sint32 Count, Float Width, Math::Rect2DF &Src ) = 0;

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
		virtual void DrawList( Math::Point2DF Pos[], Float Width[], Sint32 Angle[], CColor Color[], Sint32 Count, Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param Pos		[in] �`��ʒu�̔z��
			@param List		[in] ���X�g���̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawList( SSpriteListData2D List[], Sint32 Count, Math::Rect2DF &Src ) = 0;

		/**
			@brief ���ˏ�t�F�[�h
			@author �t���`

			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Divide		[in] �~���̃|���S���̕�����
			@param Side			[in] �P�ӂ�����̃|���S���̕�����
			@param Alpha		[in] �����x

			���S�Ɍ������ăt�F�[�h����G�t�F�N�g�ł��B<BR>
			��ʂ̐؂�ւ����Ȃǂɗ��p�ł���Ǝv���܂��B
		*/
		virtual void CircleFade( Math::Rect2DF &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha ) = 0;

		/**
			@brief �~���]�t�F�[�h
			@author �t���`

			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Divide		[in] �~���̃|���S���̕�����
			@param Side			[in] �P�ӂ�����̃|���S���̕�����
			@param Alpha		[in] �����x

			���v���Ƀt�F�[�h����G�t�F�N�g�ł��B<BR>
			��ʂ̐؂�ւ����Ȃǂɗ��p�ł���Ǝv���܂��B
		*/
		virtual void CircleRoundFade( Math::Rect2DF &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha ) = 0;
	};
}
}
}
