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
		@brief 3D�v���~�e�B�u�`��p�C���^�[�t�F�C�X
		@author �t���`

		3D�v���~�e�B�u�`���ێ����邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IPrimitive3D
	{
	public:
		virtual ~IPrimitive3D() {}

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
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( const SVertex3DBase *pVtx, Sint32 Count ) = 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( const SVertex3DTexture *pVtx, Sint32 Count ) = 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( const SVertex3DLight *pVtx, Sint32 Count ) = 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( const SVertex3DBump *pVtx, Sint32 Count ) = 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( const SVertex3DAnimation *pVtx, Sint32 Count ) = 0;

		/**
			@brief �C���f�b�N�X�f�[�^��ǉ�
			@author �t���`
			@param pIndex		[in] �C���f�b�N�X�f�[�^
			@param IndexCount	[in] �C���f�b�N�X��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�փC���f�b�N�X�f�[�^��ǉ����܂��B<BR>
			�������Ɏw�肵���C���f�b�N�X�t�H�[�}�b�g�ɓK�������C���f�b�N�X�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( const void *pIndex, Sint32 IndexCount ) = 0;

		/**
			@brief ���_���擾
			@author �t���`
			@return �ǉ��v�����������_�̐�

			�ǉ��v�����s����SVertex3DBase���_�̐����擾���܂��B<BR>
			���̒l�͎��ۂɒǉ����ꂽ���ł͂Ȃ��APush���s���Ēǉ����ꂽ����<BR>
			�擾����̂ŁA���ۂɎ��Ă�ő吔�ȏ�̐���Ԃ��ꍇ������܂��B
		*/
		virtual Sint32 GetVertexCount( void ) = 0;

		/**
			@brief �C���f�b�N�X���擾
			@author �t���`
			@return �ǉ��v���������C���f�b�N�X�̐�

			�ǉ��v�����s�����C���f�b�N�X�̐����擾���܂��B<BR>
			���̒l�͎��ۂɒǉ����ꂽ���ł͂Ȃ��APush���s���Ēǉ����ꂽ����<BR>
			�擾����̂ŁA���ۂɎ��Ă�ő吔�ȏ�̐���Ԃ��ꍇ������܂��B
		*/
		virtual Sint32 GetIndexCount( void ) = 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`
			@param IsVertex		[in] ���_�������ݍs��
			@param IsIndex		[in] �C���f�b�N�X�������ݍs��
			@param IsDirect		[in] �o�b�t�@���ڏ�������

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( Bool IsVertex = true, Bool IsIndex = true, Bool IsDirect = true ) = 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void ) = 0;
	};
}
}
}
