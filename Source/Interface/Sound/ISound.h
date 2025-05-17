#pragma once


/**
	@file
	@brief サウンドインターフェイス
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
	/**
		@brief サウンド管理クラス
		@author 葉迩倭

		@note
		サウンドの処理を行うクラスです。<BR>
		未圧縮Waveのみのオンメモリ多重再生に対応しています。<BR>
		SEの再生用途を想定しています。
	*/
	class ISound : public IInterface
	{
	public:
		virtual ~ISound() {}

/**
@brief 再生
@author 葉迩倭
@param Layer	[in] レイヤー番号（-1指定で全レイヤーに対して）
@param IsLoop	[in] ループ有無フラグ

@note
読み込んだサウンドデータの再生を開始します。<BR>
ループの有無を指定できます。

@code
ISound *pSnd;
// 同一サウンドであってもLayerが違うものは多重再生が出来る。
// 下の３つは10ms毎に多重再生される。
pSnd->Play( 0, false );
Sleep( 10 );
pSnd->Play( 1, false );
Sleep( 10 );
pSnd->Play( 2, false );
@endcode
*/
		virtual void Play( Sint32 Layer, Bool IsLoop = false ) = 0;

/**
@brief 停止
@author 葉迩倭
@param Layer	[in] レイヤー番号（-1指定で全レイヤーに対して）

@note
再生中のサウンドを停止します。

@code
ISound *pSnd;
// 同一ファイル=サウンドであってもLayerが違えば別のものとして扱われる
pSnd->Play( 0, false );
Sleep( 10 );
pSnd->Play( 1, false );
Sleep( 10 );
// この場合Layer=0のサウンドは停止するが、Layer=1のサウンドは再生されたままになる
pSnd->Stop( 0, false );
@endcode
*/
		virtual void Stop( Sint32 Layer ) = 0;

/**
@brief 一時停止/解除
@author 葉迩倭
@param Layer	[in] レイヤー番号（-1指定で全レイヤーに対して）

@note
再生中のサウンドを一時停止、<BR>
一時停止中のサウンドを再生します。

@code
ISound *pSnd;
// 同一ファイル=サウンドであってもLayerが違えば別のものとして扱われる
pSnd->Play( 0, false );
Sleep( 10 );
pSnd->Play( 1, false );
Sleep( 10 );
// この場合Layer=0のサウンドは一時停止するが、Layer=1のサウンドは再生されたままになる
pSnd->Pause( 0, false );
@endcode
*/
		virtual void Pause( Sint32 Layer ) = 0;

/**
@brief ボリューム変更
@author 葉迩倭
@param Layer	[in] レイヤー番号（-1指定で全レイヤーに対して）
@param fVolume	[in] ボリューム（0～100%）

@note
ボリュームの変更を行います。

@code
ISound *pSnd;
// 同一ファイル=サウンドであってもLayerが違えば別のものとして扱われる
pSnd->Play( 0, false );
Sleep( 10 );
pSnd->Play( 1, false );
Sleep( 10 );
// この場合Layer=0のサウンドは音量が半分になるが、Layer=1のサウンドはそのままになる
pSnd->SetVolume( 0, 50.0f );
@endcode
*/
		virtual void SetVolume( Sint32 Layer, Float fVolume ) = 0;

/**
@brief パン移動
@author 葉迩倭
@param Layer	[in] レイヤー番号（-1指定で全レイヤーに対して）
@param fPan	[in] パン（左:-100～右:+100）

@note
パンの移動を行います。

@code
ISound *pSnd;
// 同一ファイル=サウンドであってもLayerが違えば別のものとして扱われる
pSnd->Play( 0, false );
Sleep( 10 );
pSnd->Play( 1, false );
Sleep( 10 );
// この場合Layer=0のサウンドは左からのみ鳴るが、Layer=1のサウンドはそのままになる
pSnd->SetPan( 0, -100.0f );
@endcode
*/
		virtual void SetPan( Sint32 Layer, Float fPan ) = 0;

/**
@brief 再生チェック
@author 葉迩倭
@param Layer	[in] レイヤー番号
@retval false	再生していない
@retval true	再生している

@note
現在再生中のサウンドかどうか調べます。

@code
ISound *pSnd;
// サウンドのLayer=1が再生中か調べる
if ( pSnd->IsPlay( 1 ) )
{
	// 再生中
}
@endcode
*/
		virtual Bool IsPlay( Sint32 Layer ) = 0;
	};
}
}
