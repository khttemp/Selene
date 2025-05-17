#pragma once


/**
	@file
	@brief 数値補間
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
namespace Interpolation
{
/**
@brief 等速運動
@author 葉迩倭
@param Start	[in] 開始値
@param End		[in] 終了値
@param TimeAll	[in] End到達時間
@param Time		[in] 現在時間
@return Timeにおける値

@note
等速運動を行うときの補間値を取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      Time++;

      // 60カウントで0から100まで移動する
      Sint32 Pos = Interpolation::Flat( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA Flat( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		Float fRate = toF(Time) / toF(TimeAll);
		return (TypeA)(toF(Start) + toF(End - Start) * fRate);
	}

/**
@brief 加速運動
@author 葉迩倭
@param Start	[in] 開始値
@param End		[in] 終了値
@param TimeAll	[in] End到達時間
@param Time		[in] 現在時間
@return Timeにおける値

@note
加速運動を行うときの補間値を取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      Time++;

      // 60カウントで0から100まで移動する
      Sint32 Pos = Interpolation::Add( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA Add( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		Float fRate = toF(Time) / toF(TimeAll);
		fRate *= fRate;
		return (TypeA)(toF(Start) + toF(End - Start) * fRate);
	}

/**
@brief 減速運動
@author 葉迩倭
@param Start	[in] 開始値
@param End		[in] 終了値
@param TimeAll	[in] End到達時間
@param Time		[in] 現在時間
@return Timeにおける値

@note
減速運動を行うときの補間値を取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      Time++;

      // 60カウントで0から100まで移動する
      Sint32 Pos = Interpolation::Sub( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA Sub( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		Float fRate = toF(TimeAll-Time) / toF(TimeAll);
		fRate *= fRate;
		return (TypeA)(toF(End) + toF(Start - End) * fRate);
	}

/**
@brief 加速運動
@author 葉迩倭
@param Start	[in] 開始値
@param End		[in] 終了値
@param TimeAll	[in] End到達時間
@param Time		[in] 現在時間
@return Timeにおける値

@note
加速運動を行うときの補間値を取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      Time++;

      // 60カウントで0から100まで移動する
      Sint32 Pos = Interpolation::Add2( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA Add2( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		Float fRate = toF(Time) / toF(TimeAll);
		fRate *= fRate;
		fRate *= fRate;
		return (TypeA)(toF(Start) + toF(End - Start) * fRate);
	}

/**
@brief 減速運動
@author 葉迩倭
@param Start	[in] 開始値
@param End		[in] 終了値
@param TimeAll	[in] End到達時間
@param Time		[in] 現在時間
@return Timeにおける値

@note
減速運動を行うときの補間値を取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      Time++;

      // 60カウントで0から100まで移動する
      Sint32 Pos = Interpolation::Sub2( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA Sub2( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		Float fRate = toF(TimeAll-Time) / toF(TimeAll);
		fRate *= fRate;
		fRate *= fRate;
		return (TypeA)(toF(End) + toF(Start - End) * fRate);
	}

/**
@brief 加速運動
@author 葉迩倭
@param Start	[in] 開始値
@param End		[in] 終了値
@param TimeAll	[in] End到達時間
@param Time		[in] 現在時間
@return Timeにおける値

@note
加速運動を行うときの補間値を取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      Time++;

      // 60カウントで0から100まで移動する
      Sint32 Pos = Interpolation::Add4( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA Add4( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		Float fRate = toF(Time) / toF(TimeAll);
		fRate *= fRate;
		fRate *= fRate;
		fRate *= fRate;
		return (TypeA)(toF(Start) + toF(End - Start) * fRate);
	}

/**
@brief 減速運動
@author 葉迩倭
@param Start	[in] 開始値
@param End		[in] 終了値
@param TimeAll	[in] End到達時間
@param Time		[in] 現在時間
@return Timeにおける値

@note
減速運動を行うときの補間値を取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      Time++;

      // 60カウントで0から100まで移動する
      Sint32 Pos = Interpolation::Sub4( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA Sub4( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		Float fRate = toF(TimeAll-Time) / toF(TimeAll);
		fRate *= fRate;
		fRate *= fRate;
		fRate *= fRate;
		return (TypeA)(toF(End) + toF(Start - End) * fRate);
	}

/**
@brief 加速→減速運動
@author 葉迩倭
@param Start	[in] 開始値
@param End		[in] 終了値
@param TimeAll	[in] End到達時間
@param Time		[in] 現在時間
@return Timeにおける値

@note
加速→減速運動を行うときの補間値を取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      Time++;

      // 60カウントで0から100まで移動する
      Sint32 Pos = Interpolation::AddSub( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA AddSub( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Add( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Sub( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

/**
@brief 減速→加速運動
@author 葉迩倭
@param Start	[in] 開始値
@param End		[in] 終了値
@param TimeAll	[in] End到達時間
@param Time		[in] 現在時間
@return Timeにおける値

@note
加速→減速運動を行うときの補間値を取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      Time++;

      // 60カウントで0から100まで移動する
      Sint32 Pos = Interpolation::SubAdd( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA SubAdd( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Sub( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Add( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

/**
@brief 加速→減速運動
@author 葉迩倭
@param Start	[in] 開始値
@param End		[in] 終了値
@param TimeAll	[in] End到達時間
@param Time		[in] 現在時間
@return Timeにおける値

@note
加速→減速運動を行うときの補間値を取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      Time++;

      // 60カウントで0から100まで移動する
      Sint32 Pos = Interpolation::AddSub2( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA AddSub2( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Add2( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Sub2( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

/**
@brief 減速→加速運動
@author 葉迩倭
@param Start	[in] 開始値
@param End		[in] 終了値
@param TimeAll	[in] End到達時間
@param Time		[in] 現在時間
@return Timeにおける値

@note
減速→加速運動を行うときの補間値を取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      Time++;

      // 60カウントで0から100まで移動する
      Sint32 Pos = Interpolation::SubAdd2( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA SubAdd2( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Sub2( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Add2( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

/**
@brief 加速→減速運動
@author 葉迩倭
@param Start	[in] 開始値
@param End		[in] 終了値
@param TimeAll	[in] End到達時間
@param Time		[in] 現在時間
@return Timeにおける値

@note
加速→減速運動を行うときの補間値を取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      Time++;

      // 60カウントで0から100まで移動する
      Sint32 Pos = Interpolation::AddSub4( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA AddSub4( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Add4( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Sub4( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

/**
@brief 減速→加速運動
@author 葉迩倭
@param Start	[in] 開始値
@param End		[in] 終了値
@param TimeAll	[in] End到達時間
@param Time		[in] 現在時間
@return Timeにおける値

@note
減速→加速運動を行うときの補間値を取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      Time++;

      // 60カウントで0から100まで移動する
      Sint32 Pos = Interpolation::SubAdd4( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA SubAdd4( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Sub4( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Add4( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

/**
@brief sin運動
@author 葉迩倭
@param Start	[in] 開始値
@param End		[in] 終了値
@param TimeAll	[in] End到達時間
@param Time		[in] 現在時間
@return Timeにおける値

@note
sin波で運動を行うときの補間値を取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      Time++;

      // 60カウントで0から100まで移動する
      Sint32 Pos = Interpolation::Sin( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA Sin( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		Sint32 Angle = (Sint32)(DEG_TO_ANGLE(180) * Time / TimeAll);
		Float fRate = Math::Sin( Angle );
		return (TypeA)(toF(Start) + toF(End - Start) * fRate);
	}

/**
@brief ネヴィル補間
@author 葉迩倭
@param Start	[in] 開始値
@param Center	[in] 中間値
@param End		[in] 終了値
@param fTime	[in] 現在時間（0.0～1.0）
@return Timeにおける値

@note
ネヴィル補間を行うときの補間値を取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // システムの起動
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICoreの生成
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICoreにはNullDeviceがないので失敗するとNULLが返る

  // コアの初期化
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // アプリケーションの開始
    pCore->Start( 640, 480, true );

    // メインループ
    while ( pCore->Run() )
    {
      Time++;

      // 60カウントで0から100まで中間で30を経由して移動する
      Sint32 Pos = Interpolation::Neville( 0.0f, 30.0f, 100.0f, toF(Time) / 60.0f );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
	inline Float Neville( Float Start, Float Center, Float End, Float fTime )
	{
		fTime *= 2.0f;
		Start = Center + (Center - Start) * (fTime - 1.0f);
		Center = End + (End - Center) * (fTime - 2.0f);
		return Center + (Center - Start) * (fTime - 2.0f) * 0.5f;
	}
}
}

