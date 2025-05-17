#pragma once


/**
	@file
	@brief ���l���
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
namespace Interpolation
{
/**
@brief �����^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::Flat( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

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
@brief �����^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::Add( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

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
@brief �����^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::Sub( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

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
@brief �����^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::Add2( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

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
@brief �����^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::Sub2( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

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
@brief �����^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::Add4( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

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
@brief �����^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::Sub4( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

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
@brief �����������^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����������^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::AddSub( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

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
@brief �����������^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����������^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::SubAdd( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

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
@brief �����������^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����������^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::AddSub2( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

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
@brief �����������^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����������^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::SubAdd2( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

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
@brief �����������^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����������^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::AddSub4( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

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
@brief �����������^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����������^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::SubAdd4( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

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
@brief sin�^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
sin�g�ŉ^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::Sin( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

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
@brief �l���B�����
@author �t���`
@param Start	[in] �J�n�l
@param Center	[in] ���Ԓl
@param End		[in] �I���l
@param fTime	[in] ���ݎ��ԁi0.0�`1.0�j
@return Time�ɂ�����l

@note
�l���B����Ԃ��s���Ƃ��̕�Ԓl���擾���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂Œ��Ԃ�30���o�R���Ĉړ�����
      Sint32 Pos = Interpolation::Neville( 0.0f, 30.0f, 100.0f, toF(Time) / 60.0f );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

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

