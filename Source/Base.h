#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include <windows.h>


//-----------------------------------------------------------------------------------
// WARNING
//-----------------------------------------------------------------------------------
#pragma inline_depth ( 255 )
#pragma inline_recursion ( on )

#pragma warning ( disable: 4100 )
#pragma warning ( disable: 4819 )
#pragma warning ( disable: 4201 )
#pragma warning ( disable: 4239 )
#pragma warning ( disable: 4995 )
#pragma warning ( disable: 4996 )
#pragma warning ( disable: 4324 )


//-----------------------------------------------------------------------------------
// LIBRARY
//-----------------------------------------------------------------------------------
#pragma comment( lib, "ole32.lib" )
#pragma comment( lib, "gdi32.lib" )
#pragma comment( lib, "user32.lib" )
#pragma comment( lib, "comdlg32.lib" )
#pragma comment( lib, "advapi32.lib" )


//-----------------------------------------------------------------------------------
// TYPEDEF
//-----------------------------------------------------------------------------------
typedef char					Sint8;					///< signed char �^�̕ʒ�`
typedef short					Sint16;					///< signed short �^�̕ʒ�`
typedef long					Sint32;					///< signed long �^�̕ʒ�`
typedef long long				Sint64;					///< signed long �^�̕ʒ�`
typedef unsigned char			Uint8;					///< unsigned char �^�̕ʒ�`
typedef unsigned short			Uint16;					///< unsigned short �^�̕ʒ�`
typedef unsigned long			Uint32;					///< unsigned long �^�̕ʒ�`
typedef unsigned long long		Uint64;					///< unsigned long long �^�̕ʒ�`
typedef float					Float;					///< float �^�̕ʒ�`
typedef double					Double;					///< double �^�̕ʒ�`
typedef long					Bool;					///< bool �^�̕ʒ�`


//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
#define ef									else if															///< else if �ȗ��p�}�N��

#define PI									(3.141592653589793238462643383279f)								///< ��
#define PI2									(6.283185307179586476925286766559f)								///< 2��
#define REV(val)							(1.0f/toF(val))													///< �t���Z�o�}�N��

#define AXIS_RANGE_MAX						(4096)															///< �W���C�X�e�B�b�N�̎��̍ő�l

#define toF(val)							((Float)(val))													///< float�ւ̃L���X�g
#define toI(val)							((Sint32)(val))													///< int�ւ̃L���X�g

#define MIN(N1,N2)							((N1 < N2) ? (N1) : (N2))										///< �ŏ��l�擾�}�N��
#define MAX(N1,N2)							((N1 > N2) ? (N1) : (N2))										///< �ő�l�擾�}�N��
#define SWAP(N1,N2)							{ N1 = N2 - N1; N2 -= N1; N1 += N2; }							///< �l�����}�N��

#define SAFE_ADDREF(val)					if ( (val) != NULL ) { (val)->AddRef(); }						///< COM���SAddRef�}�N��
#define SAFE_RELEASE(val)					if ( (val) != NULL ) { (val)->Release(); (val) = NULL; }		///< COM���SRelease�}�N��
#define SAFE_DELETE(val)					if ( (val) != NULL ) { delete (val); (val) = NULL; }			///< new���������S���
#define SAFE_DELETE_ARRAY(val)				if ( (val) != NULL ) { delete [] (val); (val) = NULL; }			///< new[]���������S���

#define ANGLE_TABLE_BIT						(16)															///< �T�C���e�[�u���̃r�b�g��
#define ANGLE_MAX							(1 << ANGLE_TABLE_BIT)											///< �T�C���e�[�u���̃T�C�Y
#define ANGLE_TABLE_MASK					(ANGLE_MAX - 1)													///< �T�C���e�[�u���̃A�N�Z�X�p�}�X�N
#define NORMALIZE_ANGLE(val)				((val) & ANGLE_TABLE_MASK)										///< �p�x�̐��K��
#define DEG_TO_ANGLE(val)					toI(toF(val) * toF(ANGLE_MAX) / 360.0f)							///< �x���@�����p�p�x
#define ANGLE_TO_DEG(val)					((val) * 360 / ANGLE_MAX)										///< �x���@�����p�p�x
#define PI_TO_ANGLE(val)					toI(toF(val) * toF(ANGLE_MAX) / PI2)							///< �ʓx�@�����p�p�x
#define ANGLE_TO_PI(val)					(toF(val) * PI2 / toF(ANGLE_MAX))								///< ��p�p�x����ʓx�@

#define MemoryClear(PD,S)					::FillMemory((PD),(S),0x00)										///< �������N���A
#define MemoryFill(PD,PS,S)					::FillMemory((PD),(S),(PS))										///< �������h��Ԃ�
#define MemoryMove(PD,PS,S)					::MoveMemory((PD),(PS),(S))										///< �������ړ�
#define MemoryCopy(PD,PS,S)					::CopyMemory((PD),(PS),(S))										///< �������R�s�[


//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
#ifdef LIB_SELENE
#	define SELENE_DLL_API
#else // LIB_SELENE
#	ifdef DLL_SELENE
#		define SELENE_DLL_API	__declspec(dllexport)
#	else // DLL_SELENE
#		define SELENE_DLL_API	__declspec(dllimport)
#	endif // DLL_SELENE
#endif // LIB_SELENE


//-----------------------------------------------------------------------------------
// ENUM
//-----------------------------------------------------------------------------------
/**
	@brief ���C�u�������O���
*/
namespace Selene
{
	/**
		@brief ���_��`
		@author �t���`

		���_��`�N���X�̍쐬���Ɏw�肷��t���O�ł��B<BR>
		�Ȃ� VERTEX_ELEMENT_PRIMITIVE�AVERTEX_ELEMENT_SPRITE�AVERTEX_ELEMENT_3DBASE ��<BR>
		�Ɨ����Ă���r���ł��B
	*/
	enum eVertexElement
	{
		VERTEX_ELEMENT_PRIMITIVE	= 1 << 0,			///< �ʒu�ƐF�������܂ލł��P����2D�p���_
		VERTEX_ELEMENT_SPRITE		= 1 << 1,			///< �ʒu�ƐF�ƃe�N�X�`��UV���܂�2D�p���_
		VERTEX_ELEMENT_3DBASE		= 1 << 2,			///< �ʒu�ƐF���܂ނ����Ƃ��P����3D���_
		VERTEX_ELEMENT_3DTEXTURE	= 1 << 3,			///< �e�N�X�`��UV���܂ފ�{�I��3D�p���_
		VERTEX_ELEMENT_3DLIGHT		= 1 << 4,			///< ���C�e�B���O�Ɋւ���@�����܂�3D���_
		VERTEX_ELEMENT_3DBUMP		= 1 << 5,			///< �o���v�}�b�v�Ɋւ���ڐ����܂�3D���_
		VERTEX_ELEMENT_3DANIMATION	= 1 << 6,			///< �X�L�j���O�Ɋւ���{�[���̃C���f�b�N�X���E�F�C�g���܂�3D���_
	};

	/**
		@brief IParticle�p�^�C�v
		@author �t���`
	*/
	enum eParticleType
	{
		PARTICLE_TYPE_NORMAL,				///< �ʏ�p�[�e�B�N��
		PARTICLE_TYPE_VOLUME,				///< �^���{�����[���p�[�e�B�N��
	};

	/**
		@brief �t���[�����[�g��`
		@author �t���`
	*/
	enum eFrameRate
	{
		FRAME_RATE_60,					///< 1�t���[��1/60�b
		FRAME_RATE_30,					///< 1�t���[��1/30�b
		FRAME_RATE_20,					///< 1�t���[��1/20�b
		FRAME_RATE_15,					///< 1�t���[��1/15�b
	};

	/**
		@brief �A�_�v�^�[�^�C�v
		@author �t���`
	*/
	enum eGraphicCardNo
	{
		GRAPHIC_CARD_NO1,									///< �P�Ԗڂɐڑ����ꂽ�r�f�I�J�[�h
		GRAPHIC_CARD_NO2,									///< �Q�Ԗڂɐڑ����ꂽ�r�f�I�J�[�h

		GRAPHIC_CARD_DEFAULT_NO		= GRAPHIC_CARD_NO1,		///< �f�t�H���g�̃r�f�I�J�[�h
		GRAPHIC_CARD_NV_PERF_HUD	= 0xFFFFFFFF,			///< NVPerfHUD��p�̃r�f�I�J�[�h
	};

	/**
		@brief �T�[�t�F�C�X�t�H�[�}�b�g��`
		@author �t���`
	*/
	enum eSurfaceFormat
	{
		FORMAT_INVALID,						///< ����

		FORMAT_TEXTURE_32BIT,				///< 32Bit�e�N�X�`���t�H�[�}�b�g�ɏ���
		FORMAT_TEXTURE_16BIT,				///< 16Bit�e�N�X�`���t�H�[�}�b�g�ɏ���
		FORMAT_TEXTURE_DXT,					///< DXT���k�t�H�[�}�b�g�e�N�X�`��

		FORMAT_TARGET_UCHAR4,				///< unsnged char x4 �����_�����O�^�[�Q�b�g
		FORMAT_TARGET_FLOAT1,				///< float x1 �����_�����O�^�[�Q�b�g
		FORMAT_TARGET_FLOAT2,				///< float x2 �����_�����O�^�[�Q�b�g
		FORMAT_TARGET_FLOAT4,				///< float x4 �����_�����O�^�[�Q�b�g
		FORMAT_TARGET_FLOAT4_ALPHA,			///< float x4 �A���t�@�\�����_�����O�^�[�Q�b�g

		FORMAT_DEPTHBUFFER_SURFACE,			///< �[�x�o�b�t�@
		FORMAT_DEPTHBUFFER_TEXTURE,			///< �[�x�o�b�t�@

		FORMAT_MAX,

		FORMAT_TARGET_32BIT		= FORMAT_TARGET_UCHAR4,
		FORMAT_TARGET_HDR		= FORMAT_TARGET_FLOAT4_ALPHA,
	};

	/**
		@brief �e�N�X�`���X�e�[�W��`
		@author �t���`

		�e�N�X�`���X�e�[�W�Ɋւ��Ă̒�`�ł��B<BR>
		3D�I�u�W�F�N�g�Ɋւ��Ă͊�{�I�ɃV�F�[�_�[����<BR>
		UV���v�Z����悤�ɂȂ��Ă���̂ŁA<BR>
		���_�f�[�^�Ƃ��ĕێ�����UV�̓J���[�}�b�v�ƃ��C�g�}�b�v�����ł��B
	*/
	enum eTextureStage
	{
		TEXTURE_STAGE_COLOR			= 0,	///< �J���[�}�b�v
		TEXTURE_STAGE_LIGHT,				///< ���C�g�}�b�v
		TEXTURE_STAGE_ENVIRONMENT,			///< �L���[�u��
		TEXTURE_STAGE_SPECULAR,				///< �X�y�L�����}�b�v
		TEXTURE_STAGE_NORMAL,				///< �o���vor�����}�b�v�p�@���}�b�v

		TEXTURE_STAGE_SHADOW,				///< �V���h�E�}�b�v
		TEXTURE_STAGE_DEPTH,				///< �[�x�}�b�v

		TEXTURE_STAGE_TOON,					///< �g�D�[���p����}�b�v

		TEXTURE_STAGE_MAX,					///< �e�N�X�`���X�e�[�W��

		MATERIAL_TEXTURE_MAX = TEXTURE_STAGE_NORMAL + 1,
	};

	/**
		@brief �`��^�C�v��`
		@author �t���`

		�e��`��^�C�v�Ɋւ��Ă̒�`�ł��B
	*/
	enum eDrawType
	{
		DRAW_TYPE_NORMAL,					///< �ʏ�`��
		DRAW_TYPE_BLEND,					///< �������`��
		DRAW_TYPE_ADD,						///< ���Z�`��
		DRAW_TYPE_ADD_NOALPHA,				///< ���Z�`��i�A���t�@�l�����j
		DRAW_TYPE_SUB,						///< ���Z�`��
		DRAW_TYPE_SUB_NOALPHA,				///< ���Z�`��i�A���t�@�l�����j
		DRAW_TYPE_MULTIPLE,					///< ��Z�`��
	};

	/**
		@brief �J�����O�^�C�v��`
		@author �t���`

		�|���S���̕\���ɕ`��Ɋւ��Ă̒�`�ł��B
	*/
	enum eCullType
	{
		CULL_FRONT,							///< �\�̏ꍇ�̂ݕ`��
		CULL_BACK,							///< ���̏ꍇ�̂ݕ`��
		CULL_NONE,							///< ���\���ʕ`��
	};

	/**
		@brief �e�N�X�`���t�B���^�^�C�v��`
		@author �t���`

		�|���S���̕\���ɕ`��Ɋւ��Ă̒�`�ł��B
	*/
	enum eTextureFilterType
	{
		TEXTURE_FILTER_DISABLE,		///< �t�B���^�����O����
		TEXTURE_FILTER_2D,			///< �o�C���j�A�t�B���^�����O
		TEXTURE_FILTER_3D_LOW,		///< �o�C���j�A�t�B���^�����O
		TEXTURE_FILTER_3D_MIDDLE,	///< �ٕ����t�B���^�����O/��掿
		TEXTURE_FILTER_3D_HIGH,		///< �ٕ����t�B���^�����O/���掿
	};

	/**
		@brief �t�@�C���V�[�N��`
		@author �t���`
	*/
	enum eSeekFlag
	{
		SEEK_FILE_CURRENT,					///< �J�����g�ʒu
		SEEK_FILE_START,					///< �擪�ʒu
		SEEK_FILE_END,						///< �I�[�ʒu
	};

	/**
		@brief ���_�ϊ��^�C�v
		@author �t���`
	*/
	enum eTransformType
	{
		TRANSFORM_TYPE_MODEL,				///< ���f���p���_�ϊ�
		TRANSFORM_TYPE_BILLBOARD,			///< �r���{�[�h�p���_�ϊ�
	};

	/**
		@brief �o���v�^�C�v
		@author �t���`
	*/
	enum eBumpType
	{
		BUMP_TYPE_NONE,						///< �o���v�����Ȃ�
		BUMP_TYPE_ENABLE,					///< �o���v��������
	};

	/**
		@brief �X�y�L�����^�C�v
		@author �t���`
	*/
	enum eSpecularType
	{
		SPECULAR_TYPE_NONE,					///< �X�y�L���������Ȃ�
		SPECULAR_TYPE_ENABLE,				///< �X�y�L������������
	};

	/**
		@brief ���[�V�����u���[���x��
		@author �t���`
	*/
	enum eSceneMotionBlurQuarity
	{
		MOTION_BLUR_LIGHT,						///< ���f���������΂����s��Ȃ��y�ʂȃu���[
		MOTION_BLUR_FULL,						///< ���f���������΂����s���u���[

		MOTION_BLUR_MAX
	};

	/**
		@brief ��ʊE�[�x�^�C�v
		@author �t���`
	*/
	enum eSceneDepthOfFieldType
	{
		DOF_TYPE_DISABLE,						///< ��ʊE�[�x�Ȃ�
		DOF_TYPE_ENABLE,						///< ��ʊE�[�x����
	};

	/**
		@brief �t�H�O�^�C�v
		@author �t���`
	*/
	enum eSceneFogType
	{
		FOG_TYPE_DISABLE,						///< �t�H�O�Ȃ�
		FOG_TYPE_ENABLE,						///< �t�H�O����
	};

	/**
		@brief �A���`�G�C���A�X�^�C�v
		@author �t���`
	*/
	enum eSceneAntiAliasType
	{
		AA_TYPE_DISABLE,						///< �A���`�G�C���A�X�Ȃ�
		AA_TYPE_ENABLE,							///< �A���`�G�C���A�X����
	};

	/**
		@brief �t�H�O�G�t�F�N�g
		@author �t���`
	*/
	enum eSceneFogEffect
	{
		FOG_EFFECT_LINEAR,						///< ���`�t�H�O
//		FOG_EFFECT_SCATTERING,					///< �X�L���b�^�����O
	};

	/**
		@brief �V�F�[�f�B���O�^�C�v
		@author �t���`
	*/
	enum eSceneShadingType
	{
		SHADING_TYPE_NORMAL,					///< �ʏ�̃V�F�[�f�B���O
		SHADING_TYPE_TOON,						///< �g�D�[�����V�F�[�f�B���O
		SHADING_TYPE_HATCHING,					///< �n�b�`���O���V�F�[�f�B���O
	};

	/**
		@brief �V�[���p���[�V�����u���[�^�C�v
		@author �t���`
	*/
	enum eSceneMotionBlurType
	{
		MOTION_BLUR_TYPE_DISABLE,				///< �Ȃ�
		MOTION_BLUR_TYPE_LOW,					///< �N�I���e�B��F�S�T���v�����O
		MOTION_BLUR_TYPE_HIGH,					///< �N�I���e�B���F�W�T���v�����O
	};

	/**
		@brief �V�[���p�V���h�E�}�b�v�^�C�v
		@author �t���`
	*/
	enum eSceneShadowType
	{
		SHADOW_TYPE_DISABLE,				///< �e�Ȃ�
		SHADOW_TYPE_PROJECTION,				///< �v���W�F�N�V�����V���h�E
		SHADOW_TYPE_SHADOWMAP,				///< �V���h�E�}�b�s���O
	};

	/**
		@brief �V�[���p�V���h�E�N�I���e�B�^�C�v
		@author �t���`
	*/
	enum eSceneShadowQuarity
	{
		SHADOW_QUARITY_LOW,					///< ��𑜓x(512x512)
		SHADOW_QUARITY_MIDDLE,				///< ��𑜓x(1024x1024)
		SHADOW_QUARITY_HIGH,				///< ��𑜓x(2048x2048)
		SHADOW_QUARITY_BEST,				///< ��𑜓x(4096x4096)
	};

	/**
		@brief HDR����
		@author �t���`
	*/
	enum eSceneHighDynamicRangeType
	{
		HDR_TYPE_DISABLE,						///< HDR�����Ȃ�
		HDR_TYPE_ENABLE,						///< HDR��������
	};

	/**
		@brief HDR�G�t�F�N�g
		@author �t���`
	*/
	enum eSceneHighDynamicRangeEffect
	{
		HDR_EFFECT_BLOOM,						///< �u���[������
		HDR_EFFECT_CROSS,						///< �N���X�t�B���^
	};

	/**
		@brief ���e�V���h�E�p���
		@author �t���`
	*/
	enum eProjectionShadowType
	{
		PROJECTION_SHADOW_DISABLE,				///< �e�𗎂Ƃ����A�e�̉e�����Ȃ�
		PROJECTION_SHADOW_DROP_SIMPLE,			///< �ۉe�𗎂Ƃ��A�e�̉e���͎󂯂Ȃ�
		PROJECTION_SHADOW_DROP_SHAPE,			///< ���f���̌`��̉e�𗎂Ƃ��A�e�̉e���͎󂯂Ȃ�
	};

	/**
		@brief ���e�V���h�E�p�v���C�I���e�B
		@author �t���`
	*/
	enum eProjectionShadowPriority
	{
		PROJECTION_SHADOW_PRIORITY_0,			///< �e�𗎂Ƃ��Ȃ�
		PROJECTION_SHADOW_PRIORITY_1,			///< PROJECTION_SHADOW_PRIORITY_0�ȉ��ɉe�𗎂Ƃ�
		PROJECTION_SHADOW_PRIORITY_2,			///< PROJECTION_SHADOW_PRIORITY_1�ȉ��ɉe�𗎂Ƃ�
		PROJECTION_SHADOW_PRIORITY_3,			///< PROJECTION_SHADOW_PRIORITY_2�ȉ��ɉe�𗎂Ƃ�
		PROJECTION_SHADOW_PRIORITY_4,			///< PROJECTION_SHADOW_PRIORITY_3�ȉ��ɉe�𗎂Ƃ�

		PROJECTION_SHADOW_PRIORITY_MAX,
	};

	/**
		@brief �{�^�����
		@author �t���`
	*/
	enum eInputButtonState
	{
		BUTTON_STATE_FREE,					///< �����Ă��Ȃ���Ԏ擾�p
		BUTTON_STATE_HOLD,					///< ���������Ă����Ԏ擾�p
		BUTTON_STATE_PUSH,					///< �������u�Ԏ擾�p
		BUTTON_STATE_PULL,					///< �������u�Ԏ擾�p

		BUTTON_STATE_MAX,
	};

	/**
		@brief ����`
		@author �t���`
	*/
	enum eInputAxisType
	{
		AXIS_TYPE_01,						///< 1�Ԗڂ̎�
		AXIS_TYPE_02,						///< 2�Ԗڂ̎�
		AXIS_TYPE_03,						///< 3�Ԗڂ̎�
		AXIS_TYPE_04,						///< 4�Ԗڂ̎�

		AXIS_TYPE_MAX,
	};

	/**
		@brief �{�^�����
		@author �t���`
	*/
	enum eInputButtonType
	{
		BUTTON_AXIS1_UP,					///< ������w��
		BUTTON_AXIS1_DOWN,					///< �������w��
		BUTTON_AXIS1_LEFT,					///< �������w��
		BUTTON_AXIS1_RIGHT,					///< �E�����w��

		BUTTON_AXIS2_UP,					///< ������w��
		BUTTON_AXIS2_DOWN,					///< �������w��
		BUTTON_AXIS2_LEFT,					///< �������w��
		BUTTON_AXIS2_RIGHT,					///< �E�����w��

		BUTTON_AXIS3_UP,					///< ������w��
		BUTTON_AXIS3_DOWN,					///< �������w��
		BUTTON_AXIS3_LEFT,					///< �������w��
		BUTTON_AXIS3_RIGHT,					///< �E�����w��

		BUTTON_AXIS4_UP,					///< ������w��
		BUTTON_AXIS4_DOWN,					///< �������w��
		BUTTON_AXIS4_LEFT,					///< �������w��
		BUTTON_AXIS4_RIGHT,					///< �E�����w��

		BUTTON_01,							///< �{�^��1�w��
		BUTTON_02,							///< �{�^��2�w��
		BUTTON_03,							///< �{�^��3�w��
		BUTTON_04,							///< �{�^��4�w��
		BUTTON_05,							///< �{�^��5�w��
		BUTTON_06,							///< �{�^��6�w��
		BUTTON_07,							///< �{�^��7�w��
		BUTTON_08,							///< �{�^��8�w��
		BUTTON_09,							///< �{�^��9�w��
		BUTTON_10,							///< �{�^��10�w��
		BUTTON_11,							///< �{�^��11�w��
		BUTTON_12,							///< �{�^��12�w��
		BUTTON_13,							///< �{�^��13�w��
		BUTTON_14,							///< �{�^��14�w��
		BUTTON_15,							///< �{�^��15�w��
		BUTTON_16,							///< �{�^��16�w��

		BUTTON_AXIS_MAX,
		BUTTON_MAX		= BUTTON_16 - BUTTON_01,
		AXIS_MAX		= BUTTON_AXIS4_RIGHT - BUTTON_AXIS1_UP,

		BUTTON_DISABLE,						///< ����
	};

	/**
		@brief �W���C�X�e�B�b�N��������`
		@author �t���`
	*/
	enum ePadAxisDirection
	{
		PAD_AXIS_X,							///< X��
		PAD_AXIS_Y,							///< Y��
		PAD_AXIS_Z,							///< Z��

		PAD_AXIS_DIRECTION_MAX,
	};

	/**
		@brief �W���C�X�e�B�b�N����ޒ�`
		@author �t���`
	*/
	enum ePadAxisType
	{
		PAD_AXIS_POSITION,
		PAD_AXIS_POSITION_ROTATE,
		PAD_AXIS_VELOCITY,
		PAD_AXIS_VELOCITY_ROTATE,
		PAD_AXIS_ACCEL,
		PAD_AXIS_ACCEL_ROTATE,
		PAD_AXIS_FORCE,
		PAD_AXIS_FORCE_ROTATE,
		PAD_AXIS_POV,

		PAD_AXIS_MAX,
	};

	/**
		@brief �W���C�X�e�B�b�N�X���C�_�[��`
		@author �t���`
	*/
	enum ePadSliderType
	{
		PAD_SLIDER_0,							///< 1�Ԗڂ̃X���C�_�[
		PAD_SLIDER_1,							///< 2�Ԗڂ̃X���C�_�[
		PAD_SLIDER_2,							///< 3�Ԗڂ̃X���C�_�[
		PAD_SLIDER_3,							///< 4�Ԗڂ̃X���C�_�[

		PAD_SLIDER_MAX,
	};

	/**
		@brief �W���C�X�e�B�b�N�{�^����`
		@author �t���`
	*/
	enum ePadButtonType
	{
		PAD_BUTTON_01,
		PAD_BUTTON_02,
		PAD_BUTTON_03,
		PAD_BUTTON_04,
		PAD_BUTTON_05,
		PAD_BUTTON_06,
		PAD_BUTTON_07,
		PAD_BUTTON_08,
		PAD_BUTTON_09,
		PAD_BUTTON_10,
		PAD_BUTTON_11,
		PAD_BUTTON_12,
		PAD_BUTTON_13,
		PAD_BUTTON_14,
		PAD_BUTTON_15,
		PAD_BUTTON_16,

		PAD_BUTTON_MAX,
	};

	/**
		@brief ���z�L�[�R�[�h
		@author �t���`
	*/
	enum eVirtualKeyCode
	{
		SELENE_VK_ESCAPE          = 0x01,
		SELENE_VK_1               = 0x02,
		SELENE_VK_2               = 0x03,
		SELENE_VK_3               = 0x04,
		SELENE_VK_4               = 0x05,
		SELENE_VK_5               = 0x06,
		SELENE_VK_6               = 0x07,
		SELENE_VK_7               = 0x08,
		SELENE_VK_8               = 0x09,
		SELENE_VK_9               = 0x0A,
		SELENE_VK_0               = 0x0B,
		SELENE_VK_MINUS           = 0x0C,
		SELENE_VK_EQUALS          = 0x0D,
		SELENE_VK_BACK            = 0x0E,
		SELENE_VK_TAB             = 0x0F,
		SELENE_VK_Q               = 0x10,
		SELENE_VK_W               = 0x11,
		SELENE_VK_E               = 0x12,
		SELENE_VK_R               = 0x13,
		SELENE_VK_T               = 0x14,
		SELENE_VK_Y               = 0x15,
		SELENE_VK_U               = 0x16,
		SELENE_VK_I               = 0x17,
		SELENE_VK_O               = 0x18,
		SELENE_VK_P               = 0x19,
		SELENE_VK_LBRACKET        = 0x1A,
		SELENE_VK_RBRACKET        = 0x1B,
		SELENE_VK_RETURN          = 0x1C,
		SELENE_VK_LCONTROL        = 0x1D,
		SELENE_VK_A               = 0x1E,
		SELENE_VK_S               = 0x1F,
		SELENE_VK_D               = 0x20,
		SELENE_VK_F               = 0x21,
		SELENE_VK_G               = 0x22,
		SELENE_VK_H               = 0x23,
		SELENE_VK_J               = 0x24,
		SELENE_VK_K               = 0x25,
		SELENE_VK_L               = 0x26,
		SELENE_VK_SEMICOLON       = 0x27,
		SELENE_VK_APOSTROPHE      = 0x28,
		SELENE_VK_GRAVE           = 0x29,
		SELENE_VK_LSHIFT          = 0x2A,
		SELENE_VK_BACKSLASH       = 0x2B,
		SELENE_VK_Z               = 0x2C,
		SELENE_VK_X               = 0x2D,
		SELENE_VK_C               = 0x2E,
		SELENE_VK_V               = 0x2F,
		SELENE_VK_B               = 0x30,
		SELENE_VK_N               = 0x31,
		SELENE_VK_M               = 0x32,
		SELENE_VK_COMMA           = 0x33,
		SELENE_VK_PERIOD          = 0x34,
		SELENE_VK_SLASH           = 0x35,
		SELENE_VK_RSHIFT          = 0x36,
		SELENE_VK_MULTIPLY        = 0x37,
		SELENE_VK_LMENU           = 0x38,
		SELENE_VK_SPACE           = 0x39,
		SELENE_VK_CAPITAL         = 0x3A,
		SELENE_VK_F1              = 0x3B,
		SELENE_VK_F2              = 0x3C,
		SELENE_VK_F3              = 0x3D,
		SELENE_VK_F4              = 0x3E,
		SELENE_VK_F5              = 0x3F,
		SELENE_VK_F6              = 0x40,
		SELENE_VK_F7              = 0x41,
		SELENE_VK_F8              = 0x42,
		SELENE_VK_F9              = 0x43,
		SELENE_VK_F10             = 0x44,
		SELENE_VK_NUMLOCK         = 0x45,
		SELENE_VK_SCROLL          = 0x46,
		SELENE_VK_NUMPAD7         = 0x47,
		SELENE_VK_NUMPAD8         = 0x48,
		SELENE_VK_NUMPAD9         = 0x49,
		SELENE_VK_SUBTRACT        = 0x4A,
		SELENE_VK_NUMPAD4         = 0x4B,
		SELENE_VK_NUMPAD5         = 0x4C,
		SELENE_VK_NUMPAD6         = 0x4D,
		SELENE_VK_ADD             = 0x4E,
		SELENE_VK_NUMPAD1         = 0x4F,
		SELENE_VK_NUMPAD2         = 0x50,
		SELENE_VK_NUMPAD3         = 0x51,
		SELENE_VK_NUMPAD0         = 0x52,
		SELENE_VK_DECIMAL         = 0x53,
		SELENE_VK_OEM_102         = 0x56,
		SELENE_VK_F11             = 0x57,
		SELENE_VK_F12             = 0x58,
		SELENE_VK_KANA            = 0x70,
		SELENE_VK_ABNT_C1         = 0x73,
		SELENE_VK_CONVERT         = 0x79,
		SELENE_VK_NOCONVERT       = 0x7B,
		SELENE_VK_YEN             = 0x7D,
		SELENE_VK_ABNT_C2         = 0x7E,
		SELENE_VK_NUMPADEQUALS    = 0x8D,
		SELENE_VK_PREVTRACK       = 0x90,
		SELENE_VK_NUMPADENTER     = 0x9C,
		SELENE_VK_RCONTROL        = 0x9D,
		SELENE_VK_NUMPADCOMMA     = 0xB3,
		SELENE_VK_DIVIDE          = 0xB5,
		SELENE_VK_SYSRQ           = 0xB7,
		SELENE_VK_RMENU           = 0xB8,
		SELENE_VK_PAUSE           = 0xC5,
		SELENE_VK_HOME            = 0xC7,
		SELENE_VK_UP              = 0xC8,
		SELENE_VK_PRIOR           = 0xC9,
		SELENE_VK_LEFT            = 0xCB,
		SELENE_VK_RIGHT           = 0xCD,
		SELENE_VK_END             = 0xCF,
		SELENE_VK_DOWN            = 0xD0,
		SELENE_VK_NEXT            = 0xD1,
		SELENE_VK_INSERT          = 0xD2,
		SELENE_VK_DELETE          = 0xD3,
		SELENE_VK_LWIN            = 0xDB,
		SELENE_VK_RWIN            = 0xDC,

		SELENE_VK_DISABLE         = 0x00
	};

	/**
		@brief �}�E�X�{�^����Ԓ�`
		@author �t���`
	*/
	enum eMouseState
	{
		MOUSE_FREE,							///< �}�E�X�{�^���͉�����Ă��Ȃ�
		MOUSE_PULL,							///< �}�E�X�{�^���͗����ꂽ
		MOUSE_PUSH,							///< �}�E�X�{�^���͉����ꂽ
		MOUSE_HOLD,							///< �}�E�X�{�^���͉�����Â��Ă���
	};

	/**
		@brief �����V�~�����[�V�����p�ڐG�_��`
		@author �t���`
	*/
	enum eContactMode
	{
		ContactMu2			= 0x001,
		ContactFDir1		= 0x002,
		ContactBounce		= 0x004,
		ContactSoftERP		= 0x008,
		ContactSoftCFM		= 0x010,
		ContactMotion1		= 0x020,
		ContactMotion2		= 0x040,
		ContactSlip1		= 0x080,
		ContactSlip2		= 0x100,

		ContactApprox0		= 0x0000,
		ContactApprox1_1	= 0x1000,
		ContactApprox1_2	= 0x2000,
		ContactApprox1		= 0x3000,
	};

	/**
		@brief �`��n
	*/
	namespace Renderer
	{
		/**
			@brief �V�F�[�_�[�n
		*/
		namespace Shader
		{
		}

		/**
			@brief �`��I�u�W�F�N�g�n
		*/
		namespace Object
		{
		}
	}

	/**
		@brief �t�@�C���n
	*/
	namespace File
	{
	}

	namespace Scene
	{
	}

	/**
		@brief ���̓f�o�C�X�n
	*/
	namespace Peripheral
	{
	}

	/**
		@brief �T�E���h�n
	*/
	namespace Sound
	{
	}

	/**
		@brief �V�X�e���n
	*/
	namespace System
	{
	}

	/**
		@brief �Z�p���Z�n
	*/
	namespace Math
	{
	}

	/**
		@brief ���l��Ԍn
	*/
	namespace Interpolation
	{
	}

	/**
		@brief �R���W�����n
	*/
	namespace Collision
	{
	}

	/**
		@brief �����V�~�����[�V�����n
	*/
	namespace Dynamics
	{
		class IRigidModel;
		class IRigidBody;
		class IContactPoint;
		class ISimulationWorld;
	}

	/**
		@brief �X���b�h�n
	*/
	namespace Thread
	{
	}

	/**
		@brief �V�[���n
	*/
	namespace Scene
	{
	}

	/**
		@brief �t�@�C���n
	*/
	namespace File
	{
	}

	/**
		@brief �t�@�C�o�[�n
	*/
	namespace Fiber
	{
	}

	/**
		@brief �l�b�g���[�N�n
	*/
	namespace Network
	{
		class INetworkManager;
		class ISocketTCP;
		class IServerTCP;
		class IServerClientTCP;
	}
}


//-----------------------------------------------------------------------------------
// INTERFACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class ICore;
	class IGraphicCard;

	namespace Renderer
	{
		class IRender;
		class ITexture;
		class ITexture;

		namespace Shader
		{
			class IShader;
		}

		namespace Object
		{
			class IPoint2D;
			class ILine2D;
			class IPrimitive2D;
			class ISprite2D;
			class IFontSprite2D;
			class IPoint3D;
			class ILine3D;
			class IPrimitive3D;
			class ISprite3D;
			class IFontSprite3D;
			class IParticle;
			class IModel;
			class IMapModel;
		}
	}

	namespace Fiber
	{
		class IFiber;
		class IFiberController;
	};

	namespace Peripheral
	{
		class IMouse;
		class IKeyboard;
		class IJoystick;
		class IInputController;
	}

	namespace File
	{
		class IFileManager;
		class IResourceFile;
	}

	namespace Sound
	{
		class ISound;
		class IStreamSound;
	}

	namespace Scene
	{
		class IPrimitiveActor;
		class ISpriteActor;
		class IParticleActor;
		class IModelActor;
		class IMapActor;
		class IInstanceModelActor;
		class IInstanceModelController;
		class ICamera;
		class ISceneManager;
		class ICustomizedSceneManager;
		class ICustomizedSceneRenderMaterial;
		class ICustomizedSceneRenderObject;
	}

	namespace Dynamics
	{
		class ISimulationWorld;
		class IRigidBody;
		class IRigidModel;
		class IContactPoint;
	}

	namespace Math
	{
		class Vector2D;
		class Vector3D;
		class Vector4D;
		class Quaternion;
		class Matrix;
		class Style;
	}
}


//-----------------------------------------------------------------------------------
// INLINE
//-----------------------------------------------------------------------------------
namespace Selene
{
	inline void Float2Int( Sint32 &iVal, Float fVal )
	{
		*((Uint32*)&iVal) = *((Uint32*)&fVal);
	}

	inline void Int2Float( Float &fVal, Sint32 iVal )
	{
		*((Uint32*)&fVal) = *((Uint32*)&iVal);
	}

	inline Float FastSqrt( Float fVal )
	{
		Float fRetVal;
		Sint32 iVal;

		Float2Int( iVal, fVal );

		iVal &= 0x7FFFFFFF;
		iVal -= 0x3F800000;
		iVal >>= 1;
		iVal += 0x3F800000;

		Int2Float( fRetVal, iVal );

		return fRetVal;
	}

	inline float InvSqrt( float fVal )
	{
		Sint32 iVal;
		Float fValHalf = fVal * 0.5f;

		Float2Int( iVal, fVal );

		iVal = 0x5F375A86 - (iVal >> 1);

		Int2Float( fVal, iVal );

		return fVal * (1.5f - fValHalf * fVal * fVal);
	}

	inline Float Abs( Float fVal )
	{
		Sint32 iVal;

		Float2Int( iVal, fVal );

		iVal &= 0x7FFFFFFF;

		Int2Float( fVal, iVal );

		return fVal;
	}

	inline Sint32 Abs( Sint32 iVal )
	{
		return iVal & 0x7FFFFFFF;
	}

	inline Bool Is2ByteChara( char Src )
	{
		unsigned char Code = *((unsigned char*)&Src);

		if ( Code <= 0x80 ) return false;	// ����R�[�h������
		if ( Code <= 0x9F ) return true;
		if ( Code <= 0xDF ) return false;	// ���p�J�i
		if ( Code <= 0xFE ) return true;

		return false;
	}

}

