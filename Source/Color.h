#pragma once


/**
	@file
	@brief 色表現用クラス
	@author 葉迩倭
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
		@brief 色情報管理クラス
		@author 葉迩倭

		@note
			各種データの色を定義するためのクラスです。<BR>
			ライブラリ内で色を指定する場合はすべてこのクラスを使います。
	*/
	class CColor
	{
	public:
		union {
			struct {
				Uint8 b;		///< 色の青成分
				Uint8 g;		///< 色の緑成分
				Uint8 r;		///< 色の赤成分
				Uint8 a;		///< 色の透明度成分
			};
			Sint32 Color;		///< 色の32Bit整数表記
		};

	public:
/**
@brief コンストラクタ
@author 葉迩倭
*/
		CColor()
		{
		}

/**
@brief コンストラクタ
@author 葉迩倭
@param r		[in] 赤成分（０～２５５）
@param g		[in] 緑成分（０～２５５）
@param b		[in] 青成分（０～２５５）
@param a		[in] アルファ成分（０～２５５）
*/
		CColor( Sint32 r, Sint32 g, Sint32 b, Sint32 a = 255 )
		{
			this->a = (Uint8)a;
			this->r = (Uint8)r;
			this->g = (Uint8)g;
			this->b = (Uint8)b;
		}

/**
@brief コンストラクタ
@author 葉迩倭
@param Color	[in] 色成分
*/
		CColor( Sint32 Color )
		{
			this->Color = Color;
		}

/**
@brief 色ブレンド
@author 葉迩倭
@param SrcA		[in] 色成分
@param SrcB		[in] 色成分
@param fRate	[in] ブレンド率

@note
2つの色をブレンドします。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Selene::CColor ColorA( 255, 255, 255, 255 );
  Selene::CColor ColorB( 128, 128, 128, 128 );

  // ColorAとColorBを50%でブレンド
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
@brief オペレーター=演算子
@author 葉迩倭
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
@brief オペレーター=演算子
@author 葉迩倭
*/
		CColor operator = ( Sint32 Color )
		{
			this->Color = Color;

			return *this;
		}

/**
@brief 型変換
@author 葉迩倭
*/
		operator Sint32 () const
		{
			return Color;
		}

	public:
/**
@brief 色取得
@author 葉迩倭

@note
RGBAカラー取得

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
@brief 色取得
@author 葉迩倭

@note
BGRAカラー取得

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
@brief 色取得
@author 葉迩倭

@note
ARGBカラー取得

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
@brief 色取得
@author 葉迩倭

@note
XRGBカラー取得

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
