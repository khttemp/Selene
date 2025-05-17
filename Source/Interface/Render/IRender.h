#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Color.h"
#include "Math/Math.h"
#include "Math/Vector2D.h"
#include "Math/Vector3D.h"
#include "Math/Vector4D.h"
#include "Collision/Box.h"
#include "Interface/Render/3D/IParticle.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	/**
		@brief �R���W�������ʕێ��p
		@author �t���`

		�R���W�����̌��ʂ�ێ����邽�߂̍\���̂ł��B
	*/
	struct SCollisionResult
	{
		Uint32 Attribute;				///< ����
		Math::Vector3D vHitPosition;	///< �Փ˓_
		Math::Vector3D vNormal;			///< �Փ˖ʂ̖@��
		Math::Vector3D vTriangle[3];	///< �ՓˎO�p�`���Ȃ����_
		CColor Color[3];				///< �ՓˎO�p�`���Ȃ����_�̐F
	};

	/**
		@brief �R���W�������ʕێ��p
		@author �t���`

		�R���W�����̌��ʂ�ێ����邽�߂̍\���̂ł��B
	*/
	struct SCollisionResultExtend
	{
		Uint32 Attribute;					///< �����iAlmeria��ł̃}�e���A���̔ԍ��j
		Math::Vector3D vHitPosition;		///< �Փ˓_
		Math::Vector3D vNormal;				///< �Փ˖ʂ̖@��
		Math::Vector3D vTriangle[3];		///< �ՓˎO�p�`���Ȃ����_
		Math::Vector3D vRefrectDirection;	///< ���ˌ�̕���
		Math::Vector3D vRefrectPosition;	///< ���ˌ�̈ʒu
		Math::Vector3D vSlidePosition;		///< �ʏ���X���C�h�����ꍇ�̈ʒu
		CColor Color[3];					///< �ՓˎO�p�`���Ȃ����_�̐F
	};

	/**
		@brief �R���W�������ʕێ��p
		@author �t���`

		�R���W�����̌��ʂ�ێ����邽�߂̍\���̂ł��B
	*/
	struct SCollisionResultSphere
	{
		Math::Vector3D vHitPosition;	///< �Փ˓_
		Math::Vector3D vNormal;			///< �Փ˖ʂ̖@��
	};

	/**
		@brief �R���W�������ʕێ��p
		@author �t���`

		�R���W�����̌��ʂ�ێ����邽�߂̍\���̂ł��B
	*/
	struct SCollisionResultSphereExtend
	{
		Math::Vector3D vHitPosition;		///< �Փ˓_
		Math::Vector3D vNormal;				///< �Փ˖ʂ̖@��
		Math::Vector3D vRefrectDirection;	///< ���ˌ�̕���
		Math::Vector3D vRefrectPosition;	///< ���ˌ�̈ʒu
		Math::Vector3D vSlidePosition;		///< �ʏ���X���C�h�����ꍇ�̈ʒu
	};

	/**
		@brief 2D�`��p���_
		@author �t���`

		2D�`��p�̊�{���_�f�[�^�ł��B<BR>
		���IPoint2D/ILine2D�N���X�Ŏg�p���܂��B<BR>
		VERTEX_ELEMENT_PRIMITIVE�t���O���w�肵�č쐬����<BR>
		���_��`�ł͂��̍\���̂��g���܂��B
	*/
	struct SVertex2D
	{
		Math::Vector4D Pos;		///< �ʒu
		CColor Col;				///< ���_�F
	};

	/**
		@brief 2D�`��p���_
		@author �t���`

		2D�`��p�̃e�N�X�`��UV�t�����_�f�[�^�ł��B<BR>
		���IPrimitive2D/ISprite2D/IFontSprite2D�N���X�Ŏg�p���܂��B<BR>
		VERTEX_ELEMENT_SPRITE�t���O���w�肵�č쐬����<BR>
		���_��`�ł͂��̍\���̂��g���܂��B
	*/
	struct SVertex2DTex
	{
		Math::Vector4D Pos;		///< �ʒu
		CColor Col;				///< ���_�F
		Math::Vector2D Tex[2];	///< �e�N�X�`��UV
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̊�{���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_BASE�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ē�`����܂��B
	*/
	struct SVertex3DBase
	{
		Math::Vector3D Pos;		///< �ʒu
		CColor Col;				///< ���_�F
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̃e�N�X�`��UV�p���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_3DTEXTURE�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ē�`����܂��B
	*/
	struct SVertex3DTexture
	{
		Math::Vector2D TexColor;		///< �e�N�X�`��UV
		Math::Vector2D TexLight;		///< �e�N�X�`��UV
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̃��C�e�B���O�p���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_3DLIGHT�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ē�`����܂��B
	*/
	struct SVertex3DLight
	{
		Math::Vector3D Norm;		///< �@��
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̃o���v�}�b�s���O�p���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_3DBUMP�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ē�`����܂��B
	*/
	struct SVertex3DBump
	{
		Math::Vector3D Tangent;	///< �ڐ�
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̃X�L�j���O�p���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_3DANIMATION�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ē�`����܂��B
		�P�̒��_�ɂ��Q�̃{�[���̌v�Z���s���܂��B
	*/
	struct SVertex3DAnimation
	{
		Float Weight;		///< �E�F�C�g�i�P�Ԗڂ̃E�F�C�g�������w��A�Q�Ԗڂ̓V�F�[�_�[����1.0-Weight�ŎZ�o�j
		Uint8 Index[4];		///< �{�[���C���f�b�N�X
	};

	/**
		@brief ���C���v���~�e�B�u�p���_�f�[�^
		@author �t���`
	*/
	struct SLineVertex2D
	{
		SVertex2D v1;
		SVertex2D v2;
	};

	/**
		@brief �v���~�e�B�u�p���_�f�[�^
		@author �t���`
	*/
	struct SPrimitiveVertex2D
	{
		SVertex2DTex v1;
		SVertex2DTex v2;
		SVertex2DTex v3;
	};

	/**
		@brief 3D�v���~�e�B�u��{�f�[�^
		@author �t���`

		ILine3D�ŕ`����s���ۂɎg�p���钸�_�f�[�^�B
	*/
	struct SLineVertex3D
	{
		SVertex3DBase v1;			///< �ʒu�E���_�F
		SVertex3DBase v2;			///< �ʒu�E���_�F
	};

	/**
		@brief �e�N�X�`�������p�R���t�B�O
		@author �t���`

		�e�N�X�`���������ɎQ�Ƃ����<BR>
		�쐬�p�p�����[�^�[����`�����N���X�ł��B
	*/
	class CTextureConfig
	{
	private:
		eSurfaceFormat m_Format;	///< �T�[�t�F�C�X�t�H�[�}�b�g
		CColor m_KeyColor;			///< �J���[�L�[�̐F
		Bool m_IsMipmap;			///< �~�b�v�}�b�v
		Bool m_IsHalfSize;			///< �����T�C�Y

	public:
		/**
			@brief �R���X�g���N�^
		*/
		CTextureConfig()
			: m_Format		( FORMAT_TEXTURE_32BIT )
			, m_KeyColor	( 0x00000000 )
			, m_IsMipmap	( false )
			, m_IsHalfSize	( false )
		{
		}

		/**
			@brief �f�X�g���N�^
		*/
		~CTextureConfig()
		{
		}

		/**
			@brief �J���[�L�[�i�����F�j�ݒ�
			@author �t���`
			@param Col	[in] �J���[�L�[�i�����F�j�Ɏg���F<BR>0x00000000�̎��J���[�L�[�i�����F�jOFF

			�e�N�X�`����ǂݍ��񂾍ۂɎw�肵���F�̃A���t�@��0�ɂ��A<BR>
			�J���[�L�[�������s�����悤�ɂ��̃s�N�Z����`��<BR>
			����Ȃ��悤�ɂ��܂��B
		*/
		void SetColorKey( CColor Col )
		{
			m_KeyColor = Col;
		}

		/**
			@brief �T�[�t�F�C�X�t�H�[�}�b�g�ݒ�
			@author �t���`
			@param Fmt	[in] �T�[�t�F�C�X�t�H�[�}�b�g

			�e�N�X�`���ǂݍ��ݎ��̃T�[�t�F�C�X�t�H�[�}�b�g��ݒ肵�܂��B<BR>
			�����ȃt�H�[�}�b�g���w�肵���ꍇ�A�쐬�͎��s���܂��B
		*/
		void SetFormat( eSurfaceFormat Fmt )
		{
			m_Format = Fmt;
		}

		/**
			@brief �~�b�v�}�b�v�L���ݒ�
			@author �t���`
			@param IsEnable	[in] �~�b�v�}�b�v�L��

			�e�N�X�`���ǂݍ��ݎ��̃~�b�v�}�b�v�̗L����ݒ肵�܂��B
		*/
		void SetMipmapEnable( Bool IsEnable ) 
		{
			m_IsMipmap = IsEnable;
		}

		/**
			@brief 1/2�T�C�Y�e�N�X�`���L���ݒ�
			@author �t���`
			@param IsEnable	[in] 1/2�T�C�Y�e�N�X�`���L��

			�e�N�X�`���ǂݍ��ݎ���1/2�T�C�Y�e�N�X�`���̗L����ݒ肵�܂��B<BR>
			���̃t���O�͏����Ƀe�N�X�`���̎g�p�ʂ�}���鎞�Ɏg���܂��B
		*/
		void SetHalfSizeEnable( Bool IsEnable ) 
		{
			m_IsHalfSize = IsEnable;
		}

		/**
			@brief �J���[�L�[���擾
			@author �t���`
			@retval	0		�J���[�L�[�������s��Ȃ�
			@retval	0�ȊO	���̐F���J���[�L�[�Ƃ���
		*/
		CColor GetColorKey( void )
		{
			return m_KeyColor;
		}

		/**
			@brief �T�[�t�F�C�X�t�H�[�}�b�g���擾���܂�
			@author �t���`
			@return �T�[�t�F�C�X�t�H�[�}�b�g
		*/
		eSurfaceFormat GetFormat( void )
		{
			return m_Format;
		}

		/**
			@brief �~�b�v�}�b�v�̗L�����擾���܂�
			@author �t���`
			@return �~�b�v�}�b�v�̗L��
		*/
		Bool IsMipmap( void )
		{
			return m_IsMipmap;
		}

		/**
			@brief 1/2�T�C�Y�e�N�X�`���̗L�����擾���܂�
			@author �t���`
			@return 1/2�T�C�Y�e�N�X�`���̗L��
		*/
		Bool IsHalfSize( void )
		{
			return m_IsHalfSize;
		}
	};

	/**
		@brief �����_���[�C���^�[�t�F�C�X
		@author �t���`

		��ʂɑ΂���S�Ă̕`�揈�����Ǘ����܂��B<BR>
		�`��p�̊e��N���X���S�Ă��̃N���X����擾���܂�<BR>
		�܂����̃C���^�[�t�F�C�X�͂P��IDevice�C���^�[�t�F�C�X�ɑ΂��ĂP�����쐬����܂���B
	*/
	class IRender
	{
	public:
		virtual ~IRender() {}

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
			@brief �V�F�[�_�[�o�[�W�����`�F�b�N
			@author �t���`
			@retval false	���Ή�
			@retval true	�Ή�

			�V�F�[�_�[���f��2.0�ɑΉ����Ă��邩�ǂ����𒲂ׂ܂��B
		*/
		virtual Bool IsSupportedPS20( void ) = 0;

		/**
			@brief �V�F�[�_�[�o�[�W�����`�F�b�N
			@author �t���`
			@retval false	���Ή�
			@retval true	�Ή�

			�V�F�[�_�[���f��3.0�ɑΉ����Ă��邩�ǂ����𒲂ׂ܂��B
		*/
		virtual Bool IsSupportedPS30( void ) = 0;

		/**
			@brief �s�N�Z���V�F�[�_�[�̖��ߐ��`�F�b�N
			@author �t���`
			@parma Count	[in] ���ߐ�
			@retval false	���Ή�
			@retval true	�Ή�

			�w�肵�����ߐ��ɑΉ����Ă���ғ��𒲂ׂ܂��B
		*/
		virtual Bool IsPixelShaderInstructionSupport( Sint32 Count ) = 0;

		/**
			@brief �s�N�Z���V�F�[�_�[�̖��ߐ��`�F�b�N
			@author �t���`
			@retval �}���`�����_�����O�^�[�Q�b�g��

			�}���`�����_�����O�^�[�Q�b�g�̑Ή������擾���܂��B
		*/
		virtual Sint32 GetMRTs( void ) = 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�N���A
			@author �t���`
			@param Color	[in] �N���A�Ɏg���F
			@retval false	���s
			@retval true	����

			�ݒ肳�ꂽ�����_�����O�^�[�Q�b�g���w�肳�ꂽ�F�ŃN���A�[���܂��B
		*/
		virtual Bool Clear( CColor Color = 0x00000000 ) = 0;

		/**
			@brief �[�x�X�e���V���o�b�t�@�N���A
			@author �t���`
			@retval false	���s
			@retval true	����

			�ݒ肳�ꂽ�[�x�X�e���V���o�b�t�@���N���A���܂��B<BR>
			�[�x�X�e���V���o�b�t�@�����݂��Ȃ��ꍇ���s���܂��B
		*/
		virtual Bool ClearDepthStencil( void ) = 0;

		/**
			@brief �`��̈�V�U�����O
			@author �t���`
			@param pRect		[in] �`��̈�(NULL�ŉ���)

			�w�肵���`��̈���ɂ��������_�����O����Ȃ��悤�ɂȂ�܂��B<BR>
			�r���[�|�[�g�ɂ͉e����^���܂���B
		*/
		virtual void SetScissorRect( const Math::Rect2DI *pRect ) = 0;

		/**
			@brief �f�o�C�X���Z�b�g���R�[���o�b�N�֐��o�^
			@author �t���`
			@param pCallback	[in] �R�[���o�b�N�֐�

			�f�o�C�X���X�g���ɃR�[���o�b�N�����֐���ݒ肵�܂��B<BR>
			�ʏ�̗p�r�ł͎g�p����K�v�͂���܂���B<BR>
			�Ȃ�炩�̗��R�Œ��ڃf�o�C�X�𑀍삷�鎞�ɂ̂ݎg�p���Ă��������B
		*/
		virtual void SetCallbackDeviceReset( void (*pCallback)( void ) ) = 0;

		/**
			@brief ���p�\��VRAM�c�ʂ��擾
			@author �t���`
			@return VRAM�c��

			�g�p�\��VRAM�c�ʂ��擾���܂��B<BR>
			���̒l�̓r�f�I�J�[�h�ɓ��ڂ���Ă���VRAM�ʂƂ͈Ⴂ�A<BR>
			�h���C�o���g�p�\�ȗe�ʂ�Ԃ��܂��B
		*/
		virtual Float GetRestVRAM( void ) = 0;

		/**
			@brief �f�o�C�X���X�g���R�[���o�b�N�֐��o�^
			@author �t���`
			@param pCallback	[in] �R�[���o�b�N�֐�

			�f�o�C�X���X�g�A���ɃR�[���o�b�N�����֐���ݒ肵�܂��B<BR>
			�ʏ�̗p�r�ł͎g�p����K�v�͂���܂���B<BR>
			�Ȃ�炩�̗��R�Œ��ڃf�o�C�X�𑀍삷�鎞�ɂ̂ݎg�p���Ă��������B
		*/
		virtual void SetCallbackDeviceRestore( void (*pCallback)( void ) ) = 0;

		/**
			@brief �J���[�������݃}�X�N��ݒ�
			@author �t���`
			@param IsAlpha		[in] �A���t�@�������݃}�X�NON/OFF
			@param IsRed		[in] �Ԑ����������݃}�X�NON/OFF
			@param IsGreen		[in] �ΐ����������݃}�X�NON/OFF
			@param IsBlue		[in] �����������݃}�X�NON/OFF

			�t���O��true�ɂ����F�ւ̏������݂��s���܂��B<BR>
			false�ɂ���Ƃ��̐F�ւ̏������݂��s���܂���B
		*/
		virtual void SetColorWriteEnable( Bool IsAlpha, Bool IsRed, Bool IsGreen, Bool IsBlue ) = 0;

		/**
			@brief �����f�o�C�X���擾
			@author �t���`
			@return		�f�o�C�X�̃|�C���^�[

			�����Ŏg�p���Ă���f�o�C�X�����I�Ɏ擾���܂��B<BR>
			�ʏ�̗p�r�ł͎g�p����K�v�͂���܂���B<BR>
			�Ȃ�炩�̗��R�Œ��ڃf�o�C�X�𑀍삷�鎞�ɂ̂ݎg�p���Ă��������B<BR>
			�����Ŏ擾�����f�o�C�X���o�R���ăX�e�[�g�Ȃǂ̕ύX���s�����ꍇ�A<BR>
			���̌��Selene�ł̃X�e�[�g�Ǘ��̓T�|�[�g�O�ɂȂ�܂��B<BR>
		*/
		virtual void *GetDriverDevicePointer( void ) = 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�̓��e��PNG�t�@�C���ɕۑ�
			@author �t���`
			@param pFileName	[in] �t�@�C����(*.png)

			�����_�����O�^�[�Q�b�g�̓��e��PNG�t�@�C���Ƃ��ĕۑ����܂��B<BR>
			���̋@�\���g���ɂ̓����_�����O�^�[�Q�b�g�����b�N�\�ȃT�[�t�F�C�X�łȂ���΂����܂���B
		*/
		virtual void SaveToFilePNG( const char *pFileName ) = 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�̓��e��JPG�t�@�C���ɕۑ�
			@author �t���`
			@param pFileName	[in] �t�@�C����(*.jpg)

			�����_�����O�^�[�Q�b�g�̓��e��JPG�t�@�C���Ƃ��ĕۑ����܂��B<BR>
			���̋@�\���g���ɂ̓����_�����O�^�[�Q�b�g�����b�N�\�ȃT�[�t�F�C�X�łȂ���΂����܂���B
		*/
		virtual void SaveToFileJPG( const char *pFileName ) = 0;

		/**
			@brief �W���̃R���g���[����\�����邽�߂̃N���b�s���O��ON/OFF
			@author �t���`
			@param IsEnable	[in] �N���b�v������ON/OFF

			true���w�肷�邱�ƂŃN���b�s���O���L���ɂȂ�f�o�C�X��ł��������\�������悤�ɂȂ�܂��B<BR>
		*/
		virtual void SetGUIEnable( Bool IsEnable ) = 0;

		/**
			@brief �e�N�X�`���ݒ�
			@author �t���`
			@param Stage	[in] �ݒ肷��X�e�[�W�i�O�`�V�j
			@param pTex		[in] �ݒ肷��e�N�X�`���iNULL�Ŗ������j
			@retval false	���s
			@retval true	����

			�e�N�X�`���������_���[�ɐݒ肵�܂��B<BR>
			��x�ݒ肳�ꂽ�e�N�X�`����NULL��ݒ肷��܂�<BR>
			�L���ɂȂ��Ă��܂��B
		*/
		virtual Bool SetTexture( eTextureStage Stage, ITexture *pTex ) = 0;

		/**
			@brief �[�x�o�b�t�@�ݒ�
			@author �t���`
			@param pSurface	[in] �ݒ肷��T�[�t�F�C�X
			@retval false	���s
			@retval true	����

			�[�x�o�b�t�@��ݒ肵�܂��B
		*/
		virtual Bool SetDepthBuffer( ITexture *pTexture ) = 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�ݒ�
			@author �t���`
			@retval false	���s
			@retval true	����

			�����_�����O�^�[�Q�b�g���o�b�N�o�b�t�@�ɖ߂��܂��B
		*/
		virtual Bool ResetRenderTarget( void ) = 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�ݒ�
			@author �t���`
			@retval false	���s
			@retval true	����

			�����_�����O�^�[�Q�b�g�Ƃ��Đݒ肵�܂��B<BR>
			CreateRenderTarget()�Ő������ꂽ�e�N�X�`���ȊO�͎��s���܂��B
		*/
		virtual Bool SetRenderTarget( ITexture *pTexture ) = 0;

		/**
			@brief �����_�����O�����J�n�ʒm
			@author �t���`

			�����_���[�ɑ΂��Ă��ꂩ�烌���_�����O������<BR>
			�J�n����Ƃ�������ʒm���܂��B
		*/
		virtual void Begin( void ) = 0;

		/**
			@brief �����_�����O�����I���ʒm
			@author �t���`

			�����_���[�ɑ΂��Ă���Ń����_�����O������<BR>
			�I������Ƃ������Ƃ�ʒm���܂��B
		*/
		virtual void End( void ) = 0;

		/**
			@brief 2D�`��V�U�����O�ݒ�
			@author �t���`
			@param pRect	[in] �V�U�����O�̈�(NULL�ŉ���)

			�����_���[�Ɋ֘A����Q�c�`��̃V�U�����O���s���܂��B
		*/
		virtual void SetScissorPrimitive2D( const Math::Rect2DF *pRect ) = 0;

		/**
			@brief �J�X�^���V�[���Ǘ��C���^�[�t�F�C�X����
			@author �t���`
			@param QueMax			[in] �V�[���̕`��L���[�̍ő吔
			@return �J�X�^���V�[���Ǘ��C���^�[�t�F�C�X

			�S�Ă��v���W�F�N�g���ŊǗ�����J�X�^���V�[���}�l�[�W���[�𐶐����܂��B<BR>
			�����_�����O�V�X�e�������O�ŊǗ��������ꍇ�ɗ��p���ĉ������B
		*/
		virtual Scene::ICustomizedSceneManager *CreateCustomizedSceneManager( Sint32 QueMax ) = 0;

		/**
			@brief �V�[���Ǘ��C���^�[�t�F�C�X����
			@author �t���`
			@param QueMax				[in] �V�[���̕`��L���[�̍ő吔
			@param IsPixelShaderEnable	[in] �s�N�Z���V�F�[�_�[�̗L��
			@return �V�[���Ǘ��C���^�[�t�F�C�X

			�V�F�[�_�[���f��2.0�x�[�X�̃V�[���Ǘ��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			3D�Ɋւ��郌���_�����O�����͑S�Ă��̃C���^�[�t�F�C�X����܂��B
		*/
		virtual Scene::ISceneManager *CreateSceneManager( Sint32 QueMax, Bool IsPixelShaderEnable ) = 0;

		/**
			@brief 2D�|�C���g�v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param PointMax		[in] �����o�b�t�@�i�[�\�|�C���g��
			@param IsAutoResize	[in] �������T�C�Y
			@param ResizeStep	[in] ���T�C�Y���g���T�C�Y
			@return 2D�|�C���g�v���~�e�B�u�C���^�[�t�F�C�X

			2D�̓_�`��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			��ʂɓ_��łꍇ�͂��̃C���^�[�t�F�C�X���g���܂��B
		*/
		virtual Object::IPoint2D *CreatePoint2D( Sint32 PointMax, Bool IsAutoResize = false, Sint32 ResizeStep = 0 ) = 0;

		/**
			@brief 2D���C���v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param LineMax	[in] �����o�b�t�@�i�[�\���C����
			@param IsAutoResize	[in] �������T�C�Y
			@param ResizeStep	[in] ���T�C�Y���g���T�C�Y
			@return 2D���C���v���~�e�B�u�C���^�[�t�F�C�X

			2D�̓_�`��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			��ʂɐ��������ꍇ�͂��̃C���^�[�t�F�C�X���g���܂��B
		*/
		virtual Object::ILine2D *CreateLine2D( Sint32 LineMax, Bool IsAutoResize = false, Sint32 ResizeStep = 0 ) = 0;

		/**
			@brief 2D�|���S���v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param PrimitiveMax	[in] �����o�b�t�@�i�[�\���_���i�ʏ�P�̎O�p�`�ɎO���_�����j
			@param IsAutoResize	[in] �������T�C�Y
			@param ResizeStep	[in] ���T�C�Y���g���T�C�Y
			@return 2D�|���S���v���~�e�B�u�C���^�[�t�F�C�X

			2D�̃|���S���i�O�p�`�j��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�ŏ��P�ʂł���O�p�`���Ƃ̕`����s���ꍇ�͂��̃C���^�[�t�F�C�X���g���܂��B
		*/
		virtual Object::IPrimitive2D *CreatePrimitive2D( Sint32 PrimitiveMax, Bool IsAutoResize = false, Sint32 ResizeStep = 0 ) = 0;

		/**
			@brief 2D�X�v���C�g�C���^�[�t�F�C�X����
			@author �t���`
			@param PrimitiveMax	[in] �����o�b�t�@�i�[�\���_���i�ʏ�P�̎O�p�`�ɎO���_�����j
			@param pTexture		[in] �X�v���C�g�Ɋ֘A�t����e�N�X�`���C���^�[�t�F�C�X
			@param IsFiltering	[in] �e�N�X�`���t�B���^���g�����ۂ�
			@param IsOffset		[in] �t�B���^�g�p���̃e�N�X�`��UV�␳�l���s�����ۂ�
			@param IsAutoResize	[in] �������T�C�Y
			@param ResizeStep	[in] ���T�C�Y���g���T�C�Y
			@return 2D�X�v���C�g�C���^�[�t�F�C�X

			2D�̃X�v���C�g��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			IPrimitive2D���p�����Ă���A�����I�ɂ�IPrimitive2D�ł̕`����s���Ă��܂��B<BR>
			�e�N�X�`�����g�����ł��ȒP�ȃX�v���C�g�`�悪�\�ȃC���^�[�t�F�C�X�ł��B<BR>
			<BR>
			IsFiltering��true�̎��A�`��Ƀo�C���j�A�t�B���^�����O���K�p����A�g��k���A��]�Ȃǂ̎���<BR>
			��Ԃ����Y��ȕ`��s���܂����A�t�ɒʏ�̓��{�\���̎��ɂڂ₯�Ă��܂��Ƃ������_������܂��B<BR>
			���̌��_����������ɂ�IsFitler��true�ɂ��AIsOffset��false�ɂ��鎖�ŉ\�ł����A<BR>
			�o�C���j�A�t�B���^�̗אڃs�N�Z�����Q�Ƃ��Ă��܂��Ƃ������͉摜�f�[�^�̕��ŉ�������K�v������܂��B<BR>
			��̓I�ɂ͎��͂ɂP�h�b�g�ɗ]���Ƃ��ĉ����`�悳��Ȃ��s�N�Z����u�����Ƃł��B
		*/
		virtual Object::ISprite2D *CreateSprite2D( Sint32 PrimitiveMax, ITexture *pTexture, Bool IsFiltering = false, Bool IsOffset = false, Bool IsAutoResize = false, Sint32 ResizeStep = 0 ) = 0;

		/**
			@brief 2D�p�t�H���g�X�v���C�g�C���^�[�t�F�C�X����
			@author �t���`
			@param pFileName	[in] �t�H���g�X�v���C�g�p��`�t�@�C��
			@param pExt			[in] �t�H���g�X�v���C�g�p�摜�t�@�C���g���q
			@param FontMax		[in] �ő�t�H���g���i�����̒��_�o�b�t�@���j
			@param IsAutoResize	[in] �������T�C�Y
			@param ResizeStep	[in] ���T�C�Y���g���T�C�Y
			@return 2D�t�H���g�X�v���C�g�C���^�[�t�F�C�X

			2D�̃t�H���g�X�v���C�g��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			ISprite2D�𗘗p���Ă���A�����I�ɂ�ISprite2D�ł̕`����s���Ă��܂��B<BR>
			FontUtility�Ő���������`�t�@�C���ƃe�N�X�`�����g���āA�����ɕ������<BR>
			�`����s�����Ƃ��\�ł��B
		*/
		virtual Object::IFontSprite2D *CreateFontSprite2DFromFile( const char *pFileName, const char *pExt, Sint32 FontMax, Bool IsAutoResize = false, Sint32 ResizeStep = 0 ) = 0;

		/**
			@brief 3D�|�C���g�v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param VertexMax	[in] �|�C���g�̍ő吔
			@param IsDynamic	[in] �_�C�i�~�b�N�o�b�t�@�̎g�pON/OFF�i�p�ɂɏ���������ꍇ��true�ɂ��ĉ������j
			@return 3D�|�C���g�v���~�e�B�u�C���^�[�t�F�C�X

			3D�̃|�C���g�`��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�ʒu�y�ѐF�f�[�^�݂̂ŁA�e�N�X�`���⃉�C�g�Ȃǂ̕s���ʂ����邱�Ƃ͏o���܂���B
		*/
		virtual Object::IPoint3D *CreatePoint3D( Sint32 VertexMax, Bool IsDynamic ) = 0;

		/**
			@brief 3D���C���v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param VertexMax	[in] ���C���̍ő吔
			@param IsDynamic	[in] �_�C�i�~�b�N�o�b�t�@�̎g�pON/OFF�i�p�ɂɏ���������ꍇ��true�ɂ��ĉ������j
			@return 3D���C���v���~�e�B�u�C���^�[�t�F�C�X

			3D�̃��C���`��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�ʒu�y�ѐF�f�[�^�݂̂ŁA�e�N�X�`���⃉�C�g�Ȃǂ̕s���ʂ����邱�Ƃ͏o���܂���B
		*/
		virtual Object::ILine3D *CreateLine3D( Sint32 VertexMax, Bool IsDynamic ) = 0;

		/**
			@brief 3D�|���S���v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param VertexMax		[in] �������_�o�b�t�@�̍ő吔
			@param IndexMax			[in] �����C���f�b�N�X�o�b�t�@�̍ő吔
			@param VertexFlag		[in] ���_�f�[�^�t���O�ieVertexElement�̑g�ݍ��킹�j
			@param IsDynamicVertex	[in] �_�C�i�~�b�N���_�o�b�t�@�̎g�pON/OFF�i�p�ɂɏ���������ꍇ��true�ɂ��ĉ������j
			@param IsDynamicIndex	[in] �_�C�i�~�b�N�C���f�b�N�X�o�b�t�@�̎g�pON/OFF�i�p�ɂɏ���������ꍇ��true�ɂ��ĉ������j
			@return 3D�|���S���v���~�e�B�u�C���^�[�t�F�C�X

			3D�̃|���S���i�O�p�`�j��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�ŏ��P�ʂł���O�p�`���Ƃ̕`����s���ꍇ�͂��̃C���^�[�t�F�C�X���g���܂��B<BR>
			�܂��C���f�b�N�X���g�p���������I�ȕ`����T�|�[�g���܂��B<BR>
			VertexFlag�͒��_�̃t�H�[�}�b�g���w�肷����̂� eVertexElement �񋓌^�̒�����<BR>
			VERTEX_ELEMENT_PRIMITIVE �� VERTEX_ELEMENT_SPRITE �����������̂��w�肵�܂��B<BR>
			�����g�ݍ��킹��ꍇ�� | ���Z�q�Ŏw�肵�Ă��������B<BR>
			���p�����V�F�[�_�[�͓����ō쐬���ꂽ�Œ�V�F�[�_�[�����p����܂��B<BR>
			���݂̃o�[�W�����ł̓o���v�}�b�v�Ɋւ��鏈���͍s���܂���B<BR>
			<BR>
			�i��j�@�����������C�e�B���O�\�Ȓ��_ -> VERTEX_ELEMENT_3DTEXTURE | VERTEX_ELEMENT_3DLIGHT
		*/
		virtual Object::IPrimitive3D *CreatePrimitive3D( Sint32 VertexMax, Sint32 IndexMax, Sint32 VertexFlag, Bool IsDynamicVertex, Bool IsDynamicIndex ) = 0;

		/**
			@brief 3D�X�v���C�g�C���^�[�t�F�C�X����
			@author �t���`
			@param SpriteMax		[in] �����o�b�t�@�i�[�\�X�v���C�g��
			@param pTexture			[in] �X�v���C�g�Ɋ֘A�t����e�N�X�`���C���^�[�t�F�C�X
			@return 3D�X�v���C�g�C���^�[�t�F�C�X

			3D�̃X�v���C�g��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			IPrimitive3D���p�����Ă���A�����I�ɂ�IPrimitive3D�ł̕`����s���Ă��܂��B<BR>
			�e�N�X�`�����g�����ł��ȒP�ȃX�v���C�g�`�悪�\�ȃC���^�[�t�F�C�X�ł��B
		*/
		virtual Object::ISprite3D *CreateSprite3D( Sint32 SpriteMax, ITexture *pTexture ) = 0;

		/**
			@brief �p�[�e�B�N���C���^�[�t�F�C�X����
			@author �t���`
			@param ParticleMax		[in] �����o�b�t�@�i�[�\�p�[�e�B�N����
			@param pTexture			[in] �p�[�e�B�N���Ɋ֘A�t����e�N�X�`���C���^�[�t�F�C�X
			@param Type				[in] �p�[�e�B�N���Ɋւ��钸�_�t�H�[�}�b�g�^�C�v
			@param IsSoftBillboard	[in] �\�t�g�p�[�e�B�N�������邩�ǂ���
			@return �p�[�e�B�N���C���^�[�t�F�C�X

			�p�[�e�B�N����`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			IPrimitive3D���p�����Ă���A�����I�ɂ�IPrimitive3D�ł̕`����s���Ă��܂��B
		*/
		virtual Object::IParticle *CreateParticle( Sint32 ParticleMax, ITexture *pTexture, eParticleType Type, Bool IsSoftBillboard = false ) = 0;

		/**
			@brief 3D�p�t�H���g�X�v���C�g�C���^�[�t�F�C�X����
			@author �t���`
			@param pFileName	[in] �t�H���g�X�v���C�g�p��`�t�@�C��
			@param pExt			[in] �t�H���g�X�v���C�g�p�摜�t�@�C���g���q
			@param FontMax		[in] �ő�t�H���g���i�����̒��_�o�b�t�@���j
			@return 3D�t�H���g�X�v���C�g�C���^�[�t�F�C�X

			3D�̃t�H���g�X�v���C�g��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			IParticle�𗘗p���Ă���A�����I�ɂ�IParticle�ł̕`����s���Ă��܂��B<BR>
			FontUtility�Ő���������`�t�@�C���ƃe�N�X�`�����g���āA�����ɕ������<BR>
			�`����s�����Ƃ��\�ł��B
		*/
		virtual Object::IFontSprite3D *CreateFontSprite3DFromFile( const char *pFileName, const char *pExt, Sint32 FontMax ) = 0;

		/**
			@brief �c���[���f�����t�@�C�����琶��
			@author �t���`
			@param pFileName	[in] ���f����

			SMF�`���̃��f���t�@�C����ǂݍ��݂܂��B<BR>
			SMF�t�@�C����Amaryllis���g�����Ƃ�X�t�@�C�����琶���ł��܂��B
		*/
		virtual Object::IMapModel *CreateMapModelFromFile( const char *pFileName ) = 0;

		/**
			@brief �c���[���f�������������琶��
			@author �t���`
			@param pData	[in] ���f���f�[�^
			@param Size		[in] �f�[�^�T�C�Y

			SMF�`���̃��f���f�[�^��ǂݍ��݂܂��B<BR>
			SMF�t�@�C����Amaryllis���g�����Ƃ�X�t�@�C�����琶���ł��܂��B
		*/
		virtual Object::IMapModel *CreateMapModelFromMemory( const Uint8 *pData, Sint32 Size ) = 0;

		/**
			@brief ���f�����t�@�C�����琶��
			@author �t���`
			@param pFileName	[in] ���f����

			SMF�`���̃��f���t�@�C����ǂݍ��݂܂��B<BR>
			SMF�t�@�C����Amaryllis���g�����Ƃ�X�t�@�C�����琶���ł��܂��B
		*/
		virtual Object::IModel *CreateModelFromFile( const char *pFileName ) = 0;

		/**
			@brief ���f�������������琶��
			@author �t���`
			@param pData	[in] ���f���f�[�^
			@param Size		[in] �f�[�^�T�C�Y

			SMF�`���̃��f���f�[�^��ǂݍ��݂܂��B<BR>
			SMF�t�@�C����Amaryllis���g�����Ƃ�X�t�@�C�����琶���ł��܂��B
		*/
		virtual Object::IModel *CreateModelFromMemory( const Uint8 *pData, Sint32 Size ) = 0;

		/**
			@brief �e�N�X�`���ǂݍ��ݗp�R���t�B�O�f�[�^���擾
			@author �t���`
			@return �e�N�X�`���R���t�B�O�f�[�^
		*/
		virtual CTextureConfig &GetTextureConfig( void ) = 0;

		/**
			@brief �e�N�X�`���ǂݍ��ݗp�R���t�B�O�f�[�^�ݒ�
			@author �t���`
			@param Conf		[in] �e�N�X�`���R���t�B�O�f�[�^
		*/
		virtual void SetTextureConfig( CTextureConfig &Conf ) = 0;

		/**
			@brief �f�o�C�X����T�[�t�F�C�X�𐶐�
			@author �t���`
			@param Width	[in] ����
			@param Height	[in] �c��
			@return �T�[�t�F�C�X�C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTextureDepthBuffer( Sint32 Width, Sint32 Height ) = 0;

		/**
			@brief �f�o�C�X����e�N�X�`���𐶐�
			@author �t���`
			@param Width	[in] �e�N�X�`���̉���
			@param Height	[in] �e�N�X�`���̏c��
			@param Format	[in] �e�N�X�`���t�H�[�}�b�g
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTextureRenderTarget( Sint32 Width, Sint32 Height, eSurfaceFormat Format ) = 0;

		/**
			@brief �f�o�C�X����e�N�X�`���𐶐�
			@author �t���`
			@param pFileName	[in] �e�N�X�`���t�@�C����
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTextureFromFile( const char *pFileName ) = 0;

		/**
			@brief �f�o�C�X����e�N�X�`���𐶐�
			@author �t���`
			@param pData	[in] �f�[�^�̃|�C���^
			@param Size		[in] �f�[�^�T�C�Y
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTextureFromMemory( const void *pData, Sint32 Size ) = 0;

		/**
			@brief �f�o�C�X����L���[�u�e�N�X�`���𐶐�
			@author �t���`
			@param pFileName	[in] �e�N�X�`���t�@�C����
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateCubeTextureFromFile( const char *pFileName ) = 0;

		/**
			@brief �f�o�C�X����L���[�u�e�N�X�`���𐶐�
			@author �t���`
			@param pData	[in] �f�[�^�̃|�C���^
			@param Size		[in] �f�[�^�T�C�Y
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateCubeTextureFromMemory( const void *pData, Sint32 Size ) = 0;

		/**
			@brief �V�F�[�_�[�̐���
			@author �t���`
			@param pShader		[in] �V�F�[�_�[�f�[�^�̃|�C���^
			@param Size			[in] �V�F�[�_�[�f�[�^�̃T�C�Y
			@param IsCompiled	[in] �R���p�C���ς݂��ۂ�
			@return �V�F�[�_�[�C���^�[�t�F�C�X

			�V�F�[�_�[�t�@�C������V�F�[�_�[�C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Shader::IShader *CreateShaderFromMemory( const void *pShader, Sint32 Size, Bool IsCompiled = false ) = 0;

		/**
			@brief �V�F�[�_�[�̐���
			@author �t���`
			@param pShader		[in] �V�F�[�_�[�t�@�C��
			@param IsCompiled	[in] �R���p�C���ς݂��ۂ�
			@return �V�F�[�_�[�C���^�[�t�F�C�X

			�V�F�[�_�[�t�@�C������V�F�[�_�[�C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Shader::IShader *CreateShaderFromFile( const char *pFile, Bool IsCompiled = false ) = 0;

		/**
			@brief �`��^�C�v�ݒ�
			@author �t���`
			@param Type		[in] �`��^�C�v

			�|���S���̕`��^�C�v��ݒ肵�܂��B
		*/
		virtual void SetDrawType( eDrawType Type ) = 0;

		/**
			@brief �\������^�C�v�ݒ�
			@author �t���`
			@param Type		[in] �\������^�C�v

			�|���S���̕\������^�C�v��ݒ肵�܂��B
		*/
		virtual void SetCullType( eCullType Type ) = 0;

		/**
			@brief �t�B���^�����O�^�C�v�ݒ�
			@author �t���`
			@param Stage	[in] �ݒ�X�e�[�W
			@param Type		[in] �t�B���^�����O�^�C�v

			�e�N�X�`���X�e�[�W���̃t�B���^�����O�^�C�v��ݒ肵�܂��B<BR>
			TEXTURE_FILTER_ANISOTROPY�n �̃t�B���^���T�|�[�g����Ȃ��n�[�h�E�F�A�ł�<BR>
			TEXTURE_FILTER_2D ���g���܂��B
		*/
		virtual void SetTextureFilterType( eTextureStage Stage, eTextureFilterType Type ) = 0;

		/**
			@brief �[�x�e�X�gON/OFF�ݒ�
			@author �t���`
			@param Flag		[in] �[�x�e�X�gON/OFF

			�[�x�e�X�g��ON/OFF��ݒ肵�܂��B
		*/
		virtual void SetDepthTestEnable( Bool Flag ) = 0;

		/**
			@brief �[�x�o�b�t�@��������ON/OFF�ݒ�
			@author �t���`
			@param Flag		[in] �[�x�o�b�t�@��������ON/OFF

			�[�x�o�b�t�@�������݂�ON/OFF��ݒ肵�܂��B
		*/
		virtual void SetDepthWriteEnable( Bool Flag ) = 0;

		/**
			@brief �A���t�@�e�X�gON/OFF�ݒ�
			@author �t���`
			@param Flag		[in] �A���t�@�e�X�gON/OFF

			�A���t�@�e�X�g��ON/OFF��ݒ肵�܂��B
		*/
		virtual void SetAlphaTestEnable( Bool Flag ) = 0;

		/**
			@brief �A���t�@�e�X�g臒l�ݒ�
			@author �t���`
			@param Bound	[in] �A���t�@�e�X�g臒l

			�A���t�@�e�X�g��臒l��ݒ肵�܂��B
		*/
		virtual void SetAlphaBoundary( Sint32 Bound ) = 0;

		/**
			@brief �X�e�[�g�̐ݒ���X�^�b�N�ɑޔ����܂�
			@author �t���`
			@retval false	�X�^�b�N�I�[�o�[�t���[
			@retval true	�G���[����

			���݂̃X�e�[�g���X�^�b�N�ɑޔ������܂��B<BR>
			���̊֐��ɂ���đޔ������X�e�[�g�͈ȉ��̊֐��Őݒ肵�����̂ł��B<BR>
			�Evoid SetDrawType( eDrawType Type )<BR>
			�Evoid SetCullType( eCullType Type )<BR>
			�Evoid SetTextureFilterType( Sint32 Stage, eTextureFilterType Type )<BR>
			�Evoid SetTextureAddressType( Sint32 Stage, eTextureAddressType Type )<BR>
			�Evoid SetDepthTestEnable( Bool Flag )<BR>
			�Evoid SetDepthWriteEnable( Bool Flag )<BR>
			�Evoid SetAlphaTestEnable( Bool Flag )<BR>
			�Evoid SetAlphaBoundary( Sint32 Bound )<BR>
			�EBool SetTexture( Sint32 Stage, ITexture *pTex )
		*/
		virtual Bool StatePush( void ) = 0;

		/**
			@brief �X�e�[�g�̐ݒ���X�^�b�N���畜�A���܂�
			@author �t���`
			@retval false	�X�^�b�N�I�[�o�[�t���[
			@retval true	�G���[����

			���݂̃X�e�[�g���X�^�b�N�ɑޔ�����Ă���X�e�[�g�ɖ߂��܂��B
		*/
		virtual Bool StatePop( void ) = 0;

		/**
			@brief �X�e�[�g�̐ݒ��������ԂɃ��Z�b�g���܂�
			@author �t���`

			���݂̃X�e�[�g���X�^�b�N�ɑޔ�����Ă���X�e�[�g�ɖ߂��܂��B<BR>
			�ESetDrawType( DRAW_TYPE_NORMAL )<BR>
			�ESetCullType( CULL_FRONT )<BR>
			�ESetDepthTestEnable( false )<BR>
			�ESetDepthWriteEnable( false )<BR>
			�Evoid SetAlphaTestEnable( true )<BR>
			�Evoid SetAlphaBoundary( Sint32 Bound )<BR>
			�ESetTextureFilterType( \\<Stage\\>, TEXTURE_FILTER_DISABLE )<BR>
			�ESetTextureAddressType( \\<Stage\\>, TEXTURE_ADDRESS_REPEAT )<BR>
			�ESetTexture( \\<Stage\\>, NULL )
		*/
		virtual void StateInit( void ) = 0;

		/**
			@brief �f�o�b�O�p�����ݒ�ύX
			@author �t���`
			@param pFontFace	[in] �t�H���g���
			@param Size			[in] �t�H���g�T�C�Y

			�f�o�b�O�p�̕����̐ݒ��ύX���܂��B
		*/
		virtual void ChangeDebugPrintFont( const char *pFontFace, Sint32 Size ) = 0;

		/**
			@brief �f�o�b�O�p�����`�揈��
			@author �t���`
			@param Pos		[in] �`��ʒu
			@param Color	[in] �`��F
			@param pStr		[in] �`�敶����

			�f�o�b�O�p�̕����`����s���܂��B
		*/
		virtual void DebugPrint( Math::Point2DI &Pos, CColor Color, const char *pStr, ... ) = 0;

		/**
			@brief �ȈՕ����`��p�t�H���g�ݒ�
			@author �t���`
			@param pFontFace	[in] �t�H���g���
			@param Size			[in] �t�H���g�T�C�Y

			�ȈՕ����`��̃t�H���g�̐ݒ�����܂�
		*/
		virtual void SetDrawTextFont( const char *pFontFace, Sint32 Size ) = 0;

		/**
			@brief �ȈՕ����`�揈��
			@author �t���`
			@param Pos		[in] �`��ʒu
			@param Color	[in] �`��F
			@param pStr		[in] �`�敶����

			�ȈՕ����`����s���܂��B
		*/
		virtual void DrawText( Math::Point2DI &Pos, CColor Color, const char *pStr, ... ) = 0;

		/**
			@brief ��`�����_�����O
			@author �t���`
			@param Dst			[in] �`����`
			@param Color		[in] �`��F

			�P���ȋ�`��h��Ԃ��܂��B
		*/
		virtual void FillRect( const Math::Rect2DF &Dst, CColor Color ) = 0;

		/**
			@brief �V�F�[�_�[�𗘗p����ꍇ�̃e�N�X�`�����g������`��]�t���̃����_�����O
			@author �t���`
			@param Dst		[in] �`����`
			@param Color	[in] �`��F
			@param Src		[in] �e�N�X�`��UV��`
			@param pTex		[in] �e�N�X�`��
			@param Angle	[in] ��]�p�x
			@param Offset	[in] ��]�̒��S�̉摜�̒��S����̃I�t�Z�b�g

			�O���̃V�F�[�_�[�𗘗p����ꍇ�̉�]�t���̒P���ȋ�`���e�N�X�`���Ή��Ń����_�����O���܂��B
		*/
		virtual void DrawTextureByShader( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) ) = 0;

		/**
			@brief �e�N�X�`�����g������`��]�t���̃����_�����O
			@author �t���`
			@param Dst		[in] �`����`
			@param Color	[in] �`��F
			@param Src		[in] �e�N�X�`��UV��`
			@param pTex		[in] �e�N�X�`��
			@param Angle	[in] ��]�p�x
			@param Offset	[in] ��]�̒��S�̉摜�̒��S����̃I�t�Z�b�g

			��]�t���̒P���ȋ�`���e�N�X�`���Ή��Ń����_�����O���܂��B
		*/
		virtual void DrawTexture( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) ) = 0;

		/**
			@brief �e�N�X�`�����g������`��]�t���̃����_�����O
			@author �t���`
			@param Dst		[in] �`����`
			@param Color	[in] �`��F
			@param Src		[in] �e�N�X�`��UV��`
			@param pTex		[in] �e�N�X�`��
			@param Angle	[in] ��]�p�x
			@param Offset	[in] ��]�̒��S�̉摜�̒��S����̃I�t�Z�b�g

			��]�t���̒P���ȋ�`���e�N�X�`���Ή��Ń����_�����O���܂��B
		*/
		virtual void DrawTextureTile( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) ) = 0;

		/**
			@brief ���j�o�[�T���g�����W�V�����`��
			@author �t���`
			@param Dst			[in] �`����`
			@param fRate		[in] �����x�i0.0�`1.0�j
			@param SrcBase		[in] �x�[�X�摜�e�N�X�`��UV��`
			@param pTexBase		[in] �x�[�X�摜�e�N�X�`��
			@param SrcRule		[in] �A���t�@�p���[���e�N�X�`��UV��`
			@param pTexRule		[in] �A���t�@�p���[���e�N�X�`��
			@param Angle		[in] ��]�p�x
			@param Offset		[in] ��]�̒��S�̉摜�̒��S����̃I�t�Z�b�g

			���[���摜��p�������j�o�[�T���g�����W�V�������s���܂��B<BR>
			PixelShader2.0���Ȃ����ł�DrawTexture�ɒu���������܂��B
		*/
		virtual void DrawUniversal( const Math::Rect2DF &Dst, Float fRate, const Math::Rect2DF &SrcBase, ITexture *pTexBase, const Math::Rect2DF &SrcRule, ITexture *pTexRule, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) ) = 0;

		/**
			@brief 4x4�R�[���ڂ����t�B���^�`��
			@author �t���`
			@param Dst		[in] �`����`
			@param Color	[in] �`��F
			@param Src		[in] �e�N�X�`��UV��`
			@param pTex		[in] �e�N�X�`��
			@param Angle	[in] ��]�p�x
			@param Offset	[in] ��]�̒��S�̉摜�̒��S����̃I�t�Z�b�g

			4x4�̃{�b�N�X�ڂ����̃t�B���^�������ĕ`�悵�܂��B<BR>
			PixelShader2.0���Ȃ����ł�DrawTexture�ɒu���������܂��B
		*/
		virtual void DrawBlur( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) ) = 0;

		/**
			@brief �O���[�X�P�[���t�B���^�`��
			@author �t���`
			@param Dst		[in] �`����`
			@param Color	[in] �`��F
			@param Src		[in] �e�N�X�`��UV��`
			@param pTex		[in] �e�N�X�`��
			@param Angle	[in] ��]�p�x
			@param Offset	[in] ��]�̒��S�̉摜�̒��S����̃I�t�Z�b�g

			�O���[�X�P�[���̃t�B���^�������ĕ`�悵�܂��B<BR>
			PixelShader2.0���Ȃ����ł�DrawTexture�ɒu���������܂��B
		*/
		virtual void DrawGrayscale( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) ) = 0;

		/**
			@brief ���჌���Y�`��
			@author �t���`
			@param Dst		[in] �`����`
			@param Color	[in] �`��F
			@param Src		[in] �e�N�X�`��UV��`
			@param pTex		[in] �e�N�X�`��
			@param fRate	[in] ���჌���Y�c�ݓx�i�O�Řc�݂Ȃ��j

			���჌���Y�̃t�B���^�������ĕ`�悵�܂��B<BR>
			PixelShader2.0���Ȃ����ł�DrawTexture�ɒu���������܂��B
		*/
		virtual void DrawFishEye( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Float fRate ) = 0;
	};
}
}

