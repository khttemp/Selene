#pragma once


/**
	@file
	@brief アニメーション処理
	@author 葉迩倭
*/


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
		@brief アニメーションタイプ定義
		@author 葉迩倭
	*/
	enum eAnimationType
	{
		ANIMATION_TYPE_STEP,					///< ステップ補間
		ANIMATION_TYPE_LINEAR,					///< 線形補間
		ANIMATION_TYPE_TCB,						///< ＴＣＢスプライン補間
	};

	/**
		@brief キーフレームデータ
		@author 葉迩倭
	*/
	struct SKeyFrame
	{
		Bool IsIn;								///< スプライン時のIN係数を定数にするかどうか
		Bool IsOut;								///< スプライン時のOUT係数を定数にするかどうか
		Float fTime;							///< キー時間
		Float fParam;							///< キー値
		Float fIn;								///< IN係数の定数
		Float fOut;								///< OUT係数の定数

		SKeyFrame *pPrev;						///< 前方キーフレームデータポインタ
		SKeyFrame *pNext;						///< 後方キーフレームデータポインタ
	};

namespace Math
{
	/**
		@brief アニメーションクラス
		@author 葉迩倭
	*/
	class SELENE_DLL_API Animation
	{
	private:
		Float m_fTimeFirst;						///< 開始時間
		Float m_fTimeLast;						///< 終了時間
		SKeyFrame *m_pKeys;						///< キーフレームデータポインタ
		Sint32 m_KeyMax;						///< キーフレーム数

	private:
/**
@brief 指定時間から最も近いキーデータを取得します
@author 葉迩倭
@param pKeys		[in] キーフレームデータ
@param fTime		[in] 検索時間
@param KeyMax		[in] キー最大数
@return キーフレームデータポインタ

@note
指定時間からもっとも近いキー情報を、<BR>
バイナリサーチで検索します。
*/
		SKeyFrame *GetKeyData( SKeyFrame *pKeys, Float fTime, Sint32 KeyMax );

/**
@brief エルミート補間関数を処理します
@author 葉迩倭
@param fTime	[in] 時間
@param pH1		[out] パラメーター格納先１
@param pH2		[out] パラメーター格納先２
@param pH3		[out] パラメーター格納先３
@param pH4		[out] パラメーター格納先４

@note
エルミート補間関数を使って与えられたパラメーターから結果を算出します。
*/
		void Hermite( Float fTime, Float *pH1, Float *pH2, Float *pH3, Float *pH4 );

/**
@brief 前方のキーの出力先のパラメータを求めます
@author 葉迩倭
@param pKey0	[in] 前方キーデータ
@param pKey1	[in] 後方キーデータ
@return 算出されたパラメーター

@note
指定時間に対しての直前のキーの挙動を計算します。
*/
		Float InComing( SKeyFrame *pKey0, SKeyFrame *pKey1 );

/**
@brief 後方のキーの出力先のパラメータを求めます
@author 葉迩倭
@param pKey0	[in] 前方キーデータ
@param pKey1	[in] 後方キーデータ
@return 算出されたパラメーター

@note
指定時間に対しての直後のキーの挙動を計算します。
*/
		Float OutGoing( SKeyFrame *pKey0, SKeyFrame *pKey1 );

	public:
/**
@brief コンストラクタ
@author 葉迩倭
@param KeyMax		[in] キー最大数
*/
		Animation( Sint32 KeyMax );

/**
@brief デストラクタ
@author 葉迩倭
*/
		virtual ~Animation();

/**
@brief キーフレームデータにキーを設定します
@author 葉迩倭
@param KeyNo		[in] 設定先キー番号
@param fTime		[in] 設定時間
@param fParam		[in] 設定パラメータ
@param IsIn			[in] 入力パラメーター指定有無
@param IsOut		[in] 出力パラメーター指定有無
@param fIn			[in] 入力パラメーター
@param fOut			[in] 出力パラメーター
@return 成功時はtrue

@note
指定のキーに対して、補間用のパラメーターを設定します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;

  Math::Animation Anim( 3 );	// キー３つで作成
  Anim.SetKey( 0,  0.0f,   0.0f );	// キー１
  Anim.SetKey( 1,  5.0f,  40.0f );	// キー２
  Anim.SetKey( 2, 10.0f, 100.0f );	// キー３

  Float fTime = 0.0f;

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
      fTime += 0.1f;

      // 時間fTimeにおける値を取得
      // 補間方法はTCBスプライン
      Float fNow = Anim.GetParameter( fTime, ANIMATION_TYPE_TCB, 0.0f );
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
		virtual Bool SetKey( Sint32 KeyNo, Float fTime, Float fParam, Bool IsIn = false, Bool IsOut = false, Float fIn = 0.0f, Float fOut = 0.0f );

/**
@brief 指定タイプのアニメーションで指定時間における値を取得します
@author 葉迩倭
@param fTime		[in] 時間
@param Type			[in] 補間タイプ
@param fDefault		[in] デフォルト値
@return		補間結果値

@note
指定の時間に対して、補間されたパラメーターを取得します。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;

  Math::Animation Anim( 3 );	// キー３つで作成
  Anim.SetKey( 0,  0.0f,   0.0f );	// キー１
  Anim.SetKey( 1,  5.0f,  40.0f );	// キー２
  Anim.SetKey( 2, 10.0f, 100.0f );	// キー３

  Float fTime = 0.0f;

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
      fTime += 0.1f;

      // 時間fTimeにおける値を取得
      // 補間方法はTCBスプライン
      Float fNow = Anim.GetParameter( fTime, ANIMATION_TYPE_TCB, 0.0f );
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // コアの解放

  System::Finalize();                  // システムの終了処理を行う

  return 0;
}
@endcode
*/
		virtual Float GetParameter( Float fTime, eAnimationType Type, Float fDefault );
	};
}
}

