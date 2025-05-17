#pragma once


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
namespace Network
{
	/**
		@brief	ホスト情報
		@author 葉迩倭
	*/
	struct SHostInfo
	{
		char Name[64];						///< ホスト名
		char Alias[16][64];					///< ホスト別名テーブル
		char Address[16][64];				///< IPアドレステーブル
		Sint32 Type;						///< データタイプ
		Sint32 Length;						///< データサイズ
		Sint32 AliasCount;					///< エイリアス数
		Sint32 AddressCount;				///< IPアドレス数
	};

	/**
		@brief ネットワーク管理クラス
		@author 葉迩倭

		@note
		Seleneで使用するネットワークの管理を行います。
	*/
	class INetworkManager : public IInterface
	{
	public:
		virtual ~INetworkManager() {}

/**
@brief エラー文字列取得
@author 葉迩倭
@return	文字列のポインタ

@note
一連のネットワーク処理発生したエラーメッセージを取得します。

@code
#include "Selene.h"
#include <stdio.h>

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Network::INetworkManager	*pNetworkMgr	= NULL;

  // システムの初期化
  System::Initialize();

  // ネットワークマネージャーの生成
  pNetworkMgr = Network::CreateManager();

  // サーバーにTCPを使って接続する
  pTCP = pNetworkMgr->ConnectByTCP( "127.0.0.1", 80 );
  if ( pTCP == NULL )
  {
    // エラーメッセージ
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // ネットワークマネージャーの解放
  SAFE_RELEASE( pNetworkMgr );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual const char *GetLastErrorString( void ) = 0;

/**
@brief クライアント生成
@author 葉迩倭
@param pTargetHost	[in] 接続先のホスト名（IPアドレス）
@param TargetPort	[in] 接続先のポート
@retval	NULL		失敗
@retval	NULL以外	クライアントのインターフェイス

@note
指定したホストへのTCP接続を試みます。<BR>
接続できた場合はTCP操作用のインターフェイスが返ります。

@code
#include "Selene.h"
#include <stdio.h>

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Network::INetworkManager	*pNetworkMgr	= NULL;
  Network::ISocketTCP		*pTCP			= NULL;

  // システムの初期化
  System::Initialize();

  // ネットワークマネージャーの生成
  pNetworkMgr = Network::CreateManager();

  // サーバーにTCPを使って接続する
  pTCP = pNetworkMgr->ConnectByTCP( "127.0.0.1", 80 );
  if ( pTCP == NULL )
  {
    // エラーメッセージ
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // TCP接続を解放
  SAFE_RELEASE( pTCP );

  // ネットワークマネージャーの解放
  SAFE_RELEASE( pNetworkMgr );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual ISocketTCP *ConnectByTCP( const char *pTargetHost, Uint16 TargetPort ) = 0;

/**
@brief サーバー機能を生成します
@author 葉迩倭
@param Port			[in] ポート番号
@param ConnectMax	[in] 接続最大数
@retval	NULL		失敗
@retval	NULL以外	サーバーのインターフェイス

@note
サーバー機能を生成し、そのインターフェイスを取得します。<BR>
接続できた場合はTCP操作用のインターフェイスが返ります。

@code
#include "Selene.h"
#include <stdio.h>

using namespace Selene;

int main()
{
  Network::INetworkManager  *pNetworkMgr  = NULL;
  Network::IServerTCP      *pServer    = NULL;

  // システムの初期化
  System::Initialize();

  // ネットワークマネージャーの生成
  pNetworkMgr = Network::CreateManager();

  // サーバーを生成する
  pServer = pNetworkMgr->CreateServer( HOST_PORT, 16 );
  if ( pServer == NULL )
  {
    // 失敗
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // キー入力で終了
  getchar();

  // サーバーを解放
  SAFE_RELEASE( pServer );

  // ネットワークマネージャーの解放
  SAFE_RELEASE( pNetworkMgr );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
	virtual IServerTCP *CreateServer( Uint16 Port, Uint32 ConnectMax = 32 ) = 0;

/**
@brief ホスト情報取得
@author 葉迩倭
@param Info		[out] ホスト情報

@note
一連のネットワーク処理発生したエラーメッセージを取得します。

@code
#include "Selene.h"
#include <stdio.h>

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Network::INetworkManager	*pNetworkMgr	= NULL;

  // システムの初期化
  System::Initialize();

  // ネットワークマネージャーの生成
  pNetworkMgr = Network::CreateManager();

  // アプリケーションが動作しているPCのホスト情報を取得
  SHostInfo Info;
  pNetworkMgr->GetHostInfo( Info );

  // ネットワークマネージャーの解放
  SAFE_RELEASE( pNetworkMgr );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void GetHostInfo( SHostInfo &Info ) = 0;
	};
}
}

