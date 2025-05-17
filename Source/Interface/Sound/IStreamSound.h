#pragma once


/**
	@file
	@brief ストリームサウンドインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Sound
{
	static const Float PLAY_TIME_AUTO = -1.0f;

	/**
		@brief ストリームサウンド再生パラメーター
		@author 葉迩倭

		@note
		ストリームサウンドの再生を行うためのテーブルデータです。
	*/
	struct SPlayBlock
	{
		Sint32 LoopCount;		// このテーブルのループ数（-1で無限ループ）
		Float fStartTime;		// 再生開始位置（秒指定）（PLAY_TIME_AUTO指定で最初から）
		Float fEndTime;			// 再生終了位置（秒指定）（PLAY_TIME_AUTO指定で最後まで）
	};

	/**
		@brief ストリームサウンド管理クラス
		@author 葉迩倭

		@note
		ストリームサウンドの処理を行うクラスです。<BR>
		未圧縮Wave/圧縮Wave/OggVorbisの再生に対応しています。<BR>
		BGMや音声の再生用途を想定しています。
	*/
	class IStreamSound : public IInterface
	{
	public:
		virtual ~IStreamSound() {}

/**
@brief 再生
@author 葉迩倭
@param pTbl			[in] 再生テーブル
@param Count		[in] 再生テーブル数
@retval false		処理に失敗
@retval true		処理に成功

@note
読み込んだサウンドデータの再生を開始します。<BR>
再生テーブルの定義にそって再生されていきます。

@code
IStreamSound *pSnd;
// 再生テーブル
Sound::SPlayBlock Tbl[] = {
  {
    3,				// 3回
    0.0f,			// 0.0秒から
    5.0f,			// 5.0秒まで
  },
};
pSnd->Play( Tbl, sizeof(Tbl) / sizeof(Sound::SPlayBlock) );
@endcode
*/
		virtual Bool Play( SPlayBlock *pTbl, Sint32 Count ) = 0;

/**
@brief 再生
@author 葉迩倭
@param LoopCount	[in] ループ数(-1で無限)
@retval false		処理に失敗
@retval true		処理に成功

@note
読み込んだサウンドデータの再生を開始します。

@code
IStreamSound *pSnd;
// 普通に1回再生
pSnd->Play();
@endcode
*/
		virtual Bool Play( Sint32 LoopCount = 0 ) = 0;

/**
@brief 停止
@author 葉迩倭

@retval false		処理に失敗
@retval true		処理に成功

@note
再生中のサウンドを停止します。

@code
IStreamSound *pSnd;
// 再生停止
pSnd->Stop();
@endcode
*/
		virtual Bool Stop( void ) = 0;

/**
@brief 一時停止/解除
@author 葉迩倭

@retval false		処理に失敗
@retval true		処理に成功

@note
再生中のサウンドを一時停止、<BR>
一時停止中のサウンドを再生します。

@code
IStreamSound *pSnd;
// 一時停止
pSnd->Pause();
@endcode
*/
		virtual Bool Pause( void ) = 0;

/**
@brief ボリューム変更
@author 葉迩倭
@param fVolume	[in] ボリューム（0～100）
@retval false		処理に失敗
@retval true		処理に成功

@note
ボリュームの変更を行います。

@code
IStreamSound *pSnd;
// ボリューム最大に
pSnd->SetVolume( 100.0f );
@endcode
*/
		virtual Bool SetVolume( Float fVolume ) = 0;

/**
@brief パン移動
@author 葉迩倭
@param fPan	[in] パン（-100～+100）
@retval false		処理に失敗
@retval true		処理に成功

@note
パンの移動を行います。

@code
IStreamSound *pSnd;
// 右からだけ音を鳴らす
pSnd->SetPan( +100.0f );
@endcode
*/
		virtual Bool SetPan( Float fPan ) = 0;

/**
@brief 再生チェック
@author 葉迩倭
@retval false	再生していない
@retval true	再生している

@note
現在再生中のサウンドかどうか調べます。

@code
IStreamSound *pSnd;
// 再生中か調べる
if ( !pSnd->IsPlay() )
{
	// 再生終了
}
@endcode
*/
		virtual Bool IsPlay( void ) = 0;
	};
}
}

