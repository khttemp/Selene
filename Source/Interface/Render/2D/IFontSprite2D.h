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
		@brief �t�H���g�X�v���C�g�Ǘ��C���^�[�t�F�C�X
		@author �t���`

		2D�t�H���g�`��p�̃C���^�[�t�F�C�X�ł��B
	*/
	class IFontSprite2D
	{
	public:
		virtual ~IFontSprite2D() {}

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
			@param Space	[in] �s�ԕ␳�l

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( Sint32 Space = 0 ) = 0;

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
			@brief �����p�e�N�X�`���̐ݒ�
			@author �t���`

			@param pTex		[in] �e�N�X�`���C���^�[�t�F�C�X

			�����p�̃e�N�X�`����ݒ肵�܂��B
		*/
		virtual void SetDecoration( ITexture *pTex ) = 0;

		/**
			@brief �T�C�Y�擾
			@author �t���`

			�����T�C�Y���擾
		*/
		virtual Sint32 GetSize( void ) = 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Color	[in] �`��F
			@param Length	[in] �`�敶����(-1�őS��)

			�����t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂������t�H���g�łȂ��ꍇ�͐������`�悳��Ȃ���������܂��B
		*/
		virtual void DrawString( const char *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length = -1 ) = 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Color	[in] �`��F
			@param Length	[in] �`�敶����(-1�őS��)

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂��v���|�[�V���i���t�H���g�łȂ��Ă��������`�悳��܂��B
		*/
		virtual void DrawStringP( const char *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length = -1 ) = 0;

		/**
			@brief �����`��
			@author �t���`
			@param pChara	[in] �`�敶��
			@param Dst		[in] �`���`
			@param Color	[in] �`��F

			�w��ʒu�ɕ�����`�悵�܂��B<BR>
			���̊֐��ł͕����̊g��k�����T�|�[�g���܂��B
		*/
		virtual Sint32 DrawChara( const char *pChara, Math::Rect2DF &Dst, CColor Color ) = 0;

		/**
			@brief ��]�t�������`��
			@author �t���`
			@param pChara	[in] �`�敶��
			@param Dst		[in] �`���`
			@param Color	[in] �`��F
			@param Angle	[in] 1����65536�Ƃ�����]�p�x

			�w��ʒu�ɕ�������]�t���ŕ`�悵�܂��B<BR>
			���̊֐��ł͕����̊g��k�����T�|�[�g���܂��B
		*/
		virtual Sint32 DrawCharaRotate( const char *pChara, Math::Rect2DF &Dst, CColor Color, Sint32 Angle ) = 0;

		/**
			@brief ������`�抮���ʒu�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Length	[in] �`�敶����(-1�őS��)
			@return		�`�抮�����̍��W

			�����t�H���g�ŕ�����̕`����s�����ꍇ�̍ŏI�I�ȕ`��I���ʒu���擾���܂��B<BR>
			���s���܂܂��ꍇ�͉��s���l�������ŏI�ʒu��Ԃ��̂ŁA<BR>
			������̍ő啝���擾�������ꍇ�͒��ӂ��Ă��������B
		*/
		virtual Math::Point2DF GetStringLastPos( const char *pStr, Math::Point2DF Pos, Sint32 Length = -1 ) = 0;

		/**
			@brief ������`�抮���ʒu�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Length	[in] �`�敶����(-1�őS��)
			@return		�`�抮�����̍��W

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s�����ꍇ�̍ŏI�I�ȕ`��I���ʒu���擾���܂��B<BR>
			���s���܂܂��ꍇ�͉��s���l�������ŏI�ʒu��Ԃ��̂ŁA<BR>
			������̍ő啝���擾�������ꍇ�͒��ӂ��Ă��������B
		*/
		virtual Math::Point2DF GetStringLastPosP( const char *pStr, Math::Point2DF Pos, Sint32 Length = -1 ) = 0;

		/**
			@brief ������`��T�C�Y�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@return		�`��T�C�Y

			�����t�H���g�ŕ�����̕`����s�����ꍇ�̏c���̃T�C�Y���擾���܂��B<BR>
			���s���܂܂��ꍇ�ł��ő�̉������擾�ł��܂��B
		*/
		virtual Math::Point2DF GetStringSize( const char *pStr ) = 0;

		/**
			@brief ������`��T�C�Y�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@return		�`��T�C�Y

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s�����ꍇ�̏c���̃T�C�Y���擾���܂��B<BR>
			���s���܂܂��ꍇ�ł��ő�̉������擾�ł��܂��B
		*/
		virtual Math::Point2DF GetStringSizeP( const char *pStr ) = 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Color	[in] �`��F
			@param Length	[in] �`�敶����(-1�őS��)

			�����t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂������t�H���g�łȂ��ꍇ�͐������`�悳��Ȃ���������܂��B
		*/
		virtual void DrawString( const wchar_t *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length = -1 ) = 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Color	[in] �`��F
			@param Length	[in] �`�敶����(-1�őS��)

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂��v���|�[�V���i���t�H���g�łȂ��Ă��������`�悳��܂��B
		*/
		virtual void DrawStringP( const wchar_t *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length = -1 ) = 0;

		/**
			@brief �����`��
			@author �t���`
			@param pChara	[in] �`�敶��
			@param Dst		[in] �`���`
			@param Color	[in] �`��F

			�w��ʒu�ɕ�����`�悵�܂��B<BR>
			���̊֐��ł͕����̊g��k�����T�|�[�g���܂��B
		*/
		virtual Sint32 DrawChara( const wchar_t *pChara, Math::Rect2DF &Dst, CColor Color ) = 0;

		/**
			@brief ��]�t�������`��
			@author �t���`
			@param pChara	[in] �`�敶��
			@param Dst		[in] �`���`
			@param Color	[in] �`��F
			@param Angle	[in] 1����65536�Ƃ�����]�p�x

			�w��ʒu�ɕ�������]�t���ŕ`�悵�܂��B<BR>
			���̊֐��ł͕����̊g��k�����T�|�[�g���܂��B
		*/
		virtual Sint32 DrawCharaRotate( const wchar_t *pChara, Math::Rect2DF &Dst, CColor Color, Sint32 Angle ) = 0;

		/**
			@brief ������`�抮���ʒu�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Length	[in] �`�敶����(-1�őS��)
			@return		�`�抮�����̍��W

			�����t�H���g�ŕ�����̕`����s�����ꍇ�̍ŏI�I�ȕ`��I���ʒu���擾���܂��B<BR>
			���s���܂܂��ꍇ�͉��s���l�������ŏI�ʒu��Ԃ��̂ŁA<BR>
			������̍ő啝���擾�������ꍇ�͒��ӂ��Ă��������B
		*/
		virtual Math::Point2DF GetStringLastPos( const wchar_t *pStr, Math::Point2DF Pos, Sint32 Length = -1 ) = 0;

		/**
			@brief ������`�抮���ʒu�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Length	[in] �`�敶����(-1�őS��)
			@return		�`�抮�����̍��W

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s�����ꍇ�̍ŏI�I�ȕ`��I���ʒu���擾���܂��B<BR>
			���s���܂܂��ꍇ�͉��s���l�������ŏI�ʒu��Ԃ��̂ŁA<BR>
			������̍ő啝���擾�������ꍇ�͒��ӂ��Ă��������B
		*/
		virtual Math::Point2DF GetStringLastPosP( const wchar_t *pStr, Math::Point2DF Pos, Sint32 Length = -1 ) = 0;

		/**
			@brief ������`��T�C�Y�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@return		�`��T�C�Y

			�����t�H���g�ŕ�����̕`����s�����ꍇ�̏c���̃T�C�Y���擾���܂��B<BR>
			���s���܂܂��ꍇ�ł��ő�̉������擾�ł��܂��B
		*/
		virtual Math::Point2DF GetStringSize( const wchar_t *pStr ) = 0;

		/**
			@brief ������`��T�C�Y�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@return		�`��T�C�Y

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s�����ꍇ�̏c���̃T�C�Y���擾���܂��B<BR>
			���s���܂܂��ꍇ�ł��ő�̉������擾�ł��܂��B
		*/
		virtual Math::Point2DF GetStringSizeP( const wchar_t *pStr ) = 0;
	};
}
}
}
