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
		@brief 3D�����`��p�C���^�[�t�F�C�X
		@author �t���`

		3D�����`���ێ����邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IFontSprite3D
	{
	public:
		virtual ~IFontSprite3D() {}

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
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param vPos		[in] �`����W
			@param fSize	[in] �`��T�C�Y
			@param Color	[in] �`��F

			�����t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂������t�H���g�łȂ��ꍇ�͐������`�悳��Ȃ���������܂��B
		*/
		virtual void DrawString( const char *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color ) = 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param vPos		[in] �`����W
			@param fSize	[in] �`��T�C�Y
			@param Color	[in] �`��F

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂��v���|�[�V���i���t�H���g�łȂ��Ă��������`�悳��܂��B
		*/
		virtual void DrawStringP( const char *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color ) = 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param vPos		[in] �`����W
			@param fSize	[in] �`��T�C�Y
			@param Color	[in] �`��F

			�����t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂������t�H���g�łȂ��ꍇ�͐������`�悳��Ȃ���������܂��B
		*/
		virtual void DrawString( const wchar_t *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color ) = 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param vPos		[in] �`����W
			@param fSize	[in] �`��T�C�Y
			@param Color	[in] �`��F

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂��v���|�[�V���i���t�H���g�łȂ��Ă��������`�悳��܂��B
		*/
		virtual void DrawStringP( const wchar_t *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color ) = 0;
	};
}
}
}
