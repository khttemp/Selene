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
namespace File
{
	/**
		@brief �t�@�C���Ǘ��N���X
		@author �t���`

		Selene�Ŏg�p����t�@�C���̊Ǘ����s���܂��B
	*/
	class IFileManager
	{
	public:
		virtual ~IFileManager() {}

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
			@brief �t�@�C�����[�h�p�X�ݒ�
			@author �t���`
			@param Priority		[in] �����v���C�I���e�B
			@param pRootPath	[in] ���[�g�f�B���N�g��
			@param pPassword	[in] �p�b�N�t�@�C���̏ꍇ�̃p�X���[�h�i�Ȃ��ꍇ��NULL�j

			�t�@�C���̓ǂݍ��݂��s�����[�g�̃f�B���N�g����ݒ肵�܂��B<BR>
			�����Őݒ肳�ꂽ �p�X ����� �p�X.Pack �t�@�C���͓���Ɉ����܂��B<BR>
			�܂�v���O�����̕ύX�Ȃ��o���ɂ܂����������悤�ɃA�N�Z�X�\�ł��B
		*/
		virtual void SetRootPath( Sint32 Priority, const char *pRootPath, const char *pPassword = NULL ) = 0;

		/**
			@brief �J�����g�f�B���N�g���ݒ�
			@author �t���`
			@param pCurrentDir	[in] �f�B���N�g����

			�t�@�C���������s���ۂ̃J�����g�̃f�B���N�g����ݒ肵�܂��B<BR>
			�����Őݒ肳�ꂽ�f�B���N�g�������[�g�Ƃ��ăt�@�C���̌������s���܂��B<BR>
			<BR>
			SetRootPath( 0, "Data", "Data.Pack" ); �Ƃ����ݒ肪�s��ꂢ�āA<BR>
			SetCurrentPath( "texture" ); �ƂȂ��Ă���Ƃ��usample.bmp�v�Ǝw�肵�ēǂݍ��݂����ꍇ<BR>
			<BR>
			�uData\texture\sample.bmp�v��T���ɍs���A������Ȃ��ꍇ��<BR>
			�uData.Pack�v�t�@�C�����́utexture\sample.bmp�v�t�@�C����T���ɍs���܂��B
		*/
		virtual void SetCurrentPath( const char *pCurrentDir ) = 0;

		/**
			@brief �t�@�C�����[�h
			@author �t���`
			@param pFile	[in] �t�@�C����
			@param ppData	[out] �t�@�C���f�[�^�i�[��
			@param pSize	[out] �t�@�C���T�C�Y�i�[��
			@retval true	����
			@retval false	���s

			�t�@�C�������[�h���A�������ɓW�J���܂��B
		*/
		virtual Bool Load( const char *pFile, void **ppData, Sint32 *pSize ) = 0;

		/**
			@brief �f�[�^���
			@author �t���`
			@param pData	[in] �f�[�^

			Load()�֐��Ŏ擾�����f�[�^�����������������܂��B<BR>
			���̊֐����g�������@�ȊO�ł̉���͊��ˑ����邽�߁A<BR>
			�������������Ȃ��\��������܂��B
		*/
		virtual void Free( void *pData ) = 0;

		/**
			@brief �t�@�C���I�[�v��
			@author �t���`
			@param pFile		[in] �t�@�C����
			@retval NULL		���s
			@retval NULL�ȊO	�t�@�C���C���^�[�t�F�C�X

			���\�[�X�t�@�C�����I�[�v�����܂��B<BR>
			�����ł������\�[�X�t�@�C���̓Q�[���Ŏg����f�[�^�S�ʂ̎��ł��B<BR>
			�܂�p�b�N�t�@�C���̓��e�A����у��[�g�f�B���N�g���ȉ��̃f�[�^�ł��B<BR>
			SetRootPath()�Ŏw�肳��Ă���[�t�H���_]��[�p�b�N�t�@�C��]��<BR>
			���Ƀt�@�C�����������܂��B<BR>
			�I�[�v�������t�@�C���̓p�b�N�t�@�C���ł����Ă��A<BR>
			�ʏ�̃t�@�C���Ɠ����悤�ɃA�N�Z�X���邱�Ƃ��o���܂��B<BR>
			�܂����̊֐�����擾����IFIle�C���^�[�t�F�C�X�͓ǂݎ���p�ł��B<BR>
			�g�p���I������IFile�C���^�[�t�F�C�X��Release()�ŉ�����Ă��������B
		*/
		virtual IResourceFile *FileOpen( const char *pFile ) = 0;
	};
}
}

