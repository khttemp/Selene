#pragma once


/**
	@file
	@brief �F�\���p�N���X
	@author �t���`
*/

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �F���Ǘ��N���X
		@author �t���`

		@note
			�e��f�[�^�̐F���`���邽�߂̃N���X�ł��B<BR>
			���C�u�������ŐF���w�肷��ꍇ�͂��ׂĂ��̃N���X���g���܂��B
	*/
	class CColor
	{
	public:
		union {
			struct {
				Uint8 b;		///< �F�̐���
				Uint8 g;		///< �F�̗ΐ���
				Uint8 r;		///< �F�̐Ԑ���
				Uint8 a;		///< �F�̓����x����
			};
			Sint32 Color;		///< �F��32Bit�����\�L
		};

	public:
/**
@brief �R���X�g���N�^
@author �t���`
*/
		CColor()
		{
		}

/**
@brief �R���X�g���N�^
@author �t���`
@param r		[in] �Ԑ����i�O�`�Q�T�T�j
@param g		[in] �ΐ����i�O�`�Q�T�T�j
@param b		[in] �����i�O�`�Q�T�T�j
@param a		[in] �A���t�@�����i�O�`�Q�T�T�j
*/
		CColor( Sint32 r, Sint32 g, Sint32 b, Sint32 a = 255 )
		{
			this->a = (Uint8)a;
			this->r = (Uint8)r;
			this->g = (Uint8)g;
			this->b = (Uint8)b;
		}

/**
@brief �R���X�g���N�^
@author �t���`
@param Color	[in] �F����
*/
		CColor( Sint32 Color )
		{
			this->Color = Color;
		}

/**
@brief �F�u�����h
@author �t���`
@param SrcA		[in] �F����
@param SrcB		[in] �F����
@param fRate	[in] �u�����h��

@note
2�̐F���u�����h���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Selene::CColor ColorA( 255, 255, 255, 255 );
  Selene::CColor ColorB( 128, 128, 128, 128 );

  // ColorA��ColorB��50%�Ńu�����h
  Selene::CColor Ret;
  Ret.Blend( ColorA, ColorB, 0.5f );

  return 0;
}
@endcode
*/
		CColor &Blend( const CColor &SrcA, const CColor &SrcB, Float fRate )
		{
			if ( fRate < 0.0f ) fRate = 0.0f;
			if ( fRate > 1.0f ) fRate = 1.0f;
			r = (Uint8)(toF(SrcA.r) + (toF(SrcB.r - SrcA.r) * fRate));
			g = (Uint8)(toF(SrcA.g) + (toF(SrcB.g - SrcA.g) * fRate));
			b = (Uint8)(toF(SrcA.b) + (toF(SrcB.b - SrcA.b) * fRate));
			a = (Uint8)(toF(SrcA.a) + (toF(SrcB.a - SrcA.a) * fRate));

			return *this;
		}

/**
@brief �I�y���[�^�[=���Z�q
@author �t���`
*/
		CColor operator = ( const CColor &Color )
		{
			this->a = Color.a;
			this->r = Color.r;
			this->g = Color.g;
			this->b = Color.b;

			return *this;
		}

/**
@brief �I�y���[�^�[=���Z�q
@author �t���`
*/
		CColor operator = ( Sint32 Color )
		{
			this->Color = Color;

			return *this;
		}

/**
@brief �^�ϊ�
@author �t���`
*/
		operator Sint32 () const
		{
			return Color;
		}

	public:
/**
@brief �F�擾
@author �t���`

@note
RGBA�J���[�擾

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Selene::CColor Color = Selene::CColor::RGBA( 255, 255, 255, 255 );

  return 0;
}
@endcode
*/
		static CColor RGBA( Sint32 r, Sint32 g, Sint32 b, Sint32 a )
		{
			return CColor( r, g, b, a );
		}

/**
@brief �F�擾
@author �t���`

@note
BGRA�J���[�擾

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Selene::CColor Color = Selene::CColor::BGRA( 255, 255, 255, 255 );

  return 0;
}
@endcode
*/
		static CColor BGRA( Sint32 b, Sint32 g, Sint32 r, Sint32 a )
		{
			return CColor( r, g, b, a );
		}

/**
@brief �F�擾
@author �t���`

@note
ARGB�J���[�擾

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Selene::CColor Color = Selene::CColor::ARGB( 255, 255, 255, 255 );

  return 0;
}
@endcode
*/
		static CColor ARGB( Sint32 a, Sint32 r, Sint32 g, Sint32 b )
		{
			return CColor( r, g, b, a );
		}

/**
@brief �F�擾
@author �t���`

@note
XRGB�J���[�擾

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Selene::CColor Color = Selene::CColor::XRGB( 255, 255, 255 );

  return 0;
}
@endcode
*/
		static CColor XRGB( Sint32 r, Sint32 g, Sint32 b )
		{
			return CColor( r, g, b, 255 );
		}
	};
}
