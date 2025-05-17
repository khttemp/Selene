#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/IRender.h"


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
		@brief 2D�v���~�e�B�u�Ǘ��C���^�[�t�F�C�X
		@author �t���`

		2D�v���~�e�B�u�`��p�̃C���^�[�t�F�C�X�ł��B
	*/
	class IPrimitive2D
	{
	public:
		virtual ~IPrimitive2D() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )																													= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void )																													= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void )																													= 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void )																														= 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void )																														= 0;

		/**
			@brief ���_���N�G�X�g���擾
			@author �t���`
			@return ���N�G�X�g�������_��

			Push�����ő咸�_�����擾���܂��B
		*/
		virtual Sint32 GetRequestedVertexCount( void )																									= 0;

		/**
			@brief ���_���N�G�X�g���擾
			@author �t���`
			@return ���N�G�X�g�������_��

			Push�����ő咸�_�����擾���܂��B
		*/
		virtual Sint32 GetRequestedVertexCountMax( void )																								= 0;

		/**
			@brief �����o�b�t�@�փf�[�^�ǉ�
			@author �t���`
			@param pPrimitive	[in] �v���~�e�B�u�f�[�^
			@param Count		[in] �ǉ���

			�����o�b�t�@�̃f�[�^�̒ǉ����s���܂��B<BR>
			���̊֐����Ăяo���O�ɕK��Being�֐��Ńf�[�^�ǉ��̊J�n��錾���ĉ������B
		*/
		virtual Bool Push( SPrimitiveVertex2D *pPrimitive, Sint32 Count )																				= 0;

		/**
			@brief �����_�����O
			@author �t���`

			�����o�b�t�@�̓��e�̃����_�����O���s���܂��B
		*/
		virtual void Rendering( void )																													= 0;

		/**
			@brief �l�p�`�`��
			@author �t���`
			@param DstRect	[in] �`���`�f�[�^
			@param Color	[in] �`��F

			�P���Ȏl�p�`��`�悵�܂��B
		*/
		virtual void Square( Math::Rect2DI &DstRect, CColor Color )																					= 0;

		/**
			@brief ��]�t���l�p�`�`��
			@author �t���`
			@param DstRect	[in] �`���`�f�[�^
			@param Color	[in] �`��F
			@param Angle	[in] 1����65536�Ƃ�����]�p�x

			��]�t���̎l�p�`��`�悵�܂��B
		*/
		virtual void SquareRotate( Math::Rect2DI &DstRect, CColor Color, Sint32 Angle )																= 0;

		/**
			@brief ���p�`�`��
			@author �t���`
			@param Pos		[in] ���S�ʒu
			@param fRadius	[in] �`�攼�a
			@param Color	[in] �`��F
			@param Num		[in] �p��

			�P���ȑ��p�`��`�悵�܂��B
		*/
		virtual void Polygon( Math::Point2DI Pos, Float fRadius, CColor Color, Sint32 Num )															= 0;

		/**
			@brief ��]�t�����p�`�`��
			@author �t���`
			@param Pos		[in] ���S�ʒu
			@param fRadius	[in] �`�攼�a
			@param Color	[in] �`��F
			@param Num		[in] �p��
			@param Angle	[in] 1����65536�Ƃ�����]�p�x

			��]�t�����p�`��`�悵�܂��B
		*/
		virtual void PolygonRotate( Math::Point2DI Pos, Float fRadius, CColor Color, Sint32 Num, Sint32 Angle )										= 0;

		/**
			@brief �����O��`��
			@author �t���`
			@param Pos			[in] ���S�ʒu
			@param fInRadius	[in] �������a
			@param fOutRadius	[in] �O�����a
			@param InColor		[in] �����`��F
			@param OutColor		[in] �O���`��F
			@param Num			[in] �p��

			�����O��|���S����`�悵�܂��B
		*/
		virtual void Ring( Math::Point2DI Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num )						= 0;

		/**
			@brief ��]�t�������O��`��
			@author �t���`
			@param Pos			[in] ���S�ʒu
			@param fInRadius	[in] �������a
			@param fOutRadius	[in] �O�����a
			@param InColor		[in] �����`��F
			@param OutColor		[in] �O���`��F
			@param Num			[in] �p��
			@param Angle	[in] 1����65536�Ƃ�����]�p�x

			��]�t�������O��|���S����`�悵�܂��B
		*/
		virtual void RingRotate( Math::Point2DI Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num, Sint32 Angle )	= 0;
	};
}
}
}
