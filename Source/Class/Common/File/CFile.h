#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CBaseObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �t�@�C���I�[�v�����[�h
		@author �t���`
	*/
	enum eFileOpenType
	{
		FILE_OPEN_TYPE_WRITE,			///< �������ݐ�p
		FILE_OPEN_TYPE_READ,			///< �ǂݍ��ݐ�p
		FILE_OPEN_TYPE_READ_WRITE,		///< �ǂݏ����p

		FILE_OPEN_TYPE_INVALID,			///< ����
	};

namespace File
{
	/**
		@brief �t�@�C������
		@author �t���`
	*/
	class SELENE_DLL_API CFile
	{
	private:
		HANDLE m_hFile;				///< �t�@�C���n���h��
		eFileOpenType m_Type;		///< �t�@�C���I�[�v�����[�h
		FILETIME m_TimeCreate;		///< �t�@�C���쐬����
		FILETIME m_TimeAccess;		///< �t�@�C���A�N�Z�X����
		FILETIME m_TimeLastWrite;	///< �t�@�C���������ݎ���

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CFile( const char *pFileName, eFileOpenType Type );

		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		virtual ~CFile();

		/**
			@brief �t�@�C���I�[�v���`�F�b�N
			@author �t���`
			@retval false	�t�@�C���͊J����Ă��Ȃ�
			@retval true	�t�@�C���͊J����Ă���
		*/
		virtual Bool IsOpened( void );

		/**
			@brief �t�@�C����������
			@author �t���`
			@param pData	[in] �������݃f�[�^
			@param Size		[in] �f�[�^�T�C�Y
			@return ���ۂ̏������݃T�C�Y
		*/
		virtual Sint32 Write( const void *pData, Sint32 Size );

		/**
			@brief �t�@�C���ǂݍ���
			@author �t���`
			@param pData	[in] �ǂݍ��݃f�[�^
			@param Size		[in] �f�[�^�T�C�Y
			@return ���ۂ̓ǂݍ��݃T�C�Y
		*/
		virtual Sint32 Read( void *pData, Sint32 Size );

		/**
			@brief �t�@�C���T�C�Y�擾
			@author �t���`
		*/
		virtual Sint32 GetFileSize( void );

		/**
			@brief �t�@�C���ʒu�擾
			@author �t���`
			preturn �t�@�C���ʒu
		*/
		virtual Sint32 GetFilePosition( void );

		/**
			@brief �擪����V�[�N
			@author �t���`
			@param Offset	[in] �擪����̃I�t�Z�b�g
			@param �t�@�C���ʒu
		*/
		virtual Sint32 SeekStart( Sint32 Offset );

		/**
			@brief �I�[����V�[�N
			@author �t���`
			@param Offset	[in] �I�[����̃I�t�Z�b�g
			@param �t�@�C���ʒu
		*/
		virtual Sint32 SeekEnd( Sint32 Offset );

		/**
			@brief �V�[�N
			@author �t���`
			@param Offset	[in] ���݈ʒu����̃I�t�Z�b�g
			@param �t�@�C���ʒu
		*/
		virtual Sint32 Seek( Sint32 Offset );
	};
}
}

