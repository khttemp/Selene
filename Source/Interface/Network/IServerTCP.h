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
	typedef void (*ClientControlCallback)( IServerClientTCP *pClient );		///< クライアント制御用

	/**
		@brief TCP接続サーバークラス
		@author 葉迩倭

		@note
		Seleneで使用するネットワーク処理を行います。
	*/
	class IServerTCP : public IInterface
	{
	public:
		virtual ~IServerTCP() {}

/**
@brief サーバー機能を開始
@author 葉迩倭
@param pCallback	[in] クライアント処理用コールバック関数

@note
サーバー機能を開始し、クライアントからの接続を待ちます。<BR>
クライアントが接続されるたびにスレッドが作られ、その中からpCallbackで<BR>
指定した関数に処理がきます。

@code
#include "Selene.h"
#include <stdio.h>

using namespace Selene;

static void ClientRecieve( Network::IServerClientTCP *pClient );

int main()
{
  Network::INetworkManager  *pNetworkMgr  = NULL;
  Network::IServerTCP      *pServer    = NULL;

  // システムの初期化
  System::Initialize();

  // ネットワークマネージャーの生成
  pNetworkMgr = Network::CreateManager();

  // サーバーを生成する
  pServer = pNetworkMgr->CreateServer( 80, 16 );
  if ( pServer == NULL )
  {
    // 失敗
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // サーバー処理開始
  pServer->Start( ClientRecieve );

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

void ClientRecieve( Network::IServerClientTCP *pClient )
{
  // 接続元クライアント情報
  Network::SHostInfo HostInfo;
  pClient->GetHostInfo( HostInfo );

  // クライアント用メイン通信ループ
  for ( ; ; )
  {
  }
}
@endcode
*/
		virtual Bool Start( ClientControlCallback pCallback ) = 0;

/**
@brief データ送信
@author 葉迩倭
@param pData	[in] データ格納バッファ
@param Size		[in] 送信サイズ
@retval false	失敗
@retval true	成功

@note
接続されている全てのクライアントにデータの送信を行います。<BR>
指定サイズの送信が完了するまで関数から抜けてきません。

@code
#include "Selene.h"
#include <stdio.h>

using namespace Selene;

static void ClientRecieve( Network::IServerClientTCP *pClient );

int main()
{
  Network::INetworkManager  *pNetworkMgr  = NULL;
  Network::IServerTCP      *pServer    = NULL;

  // システムの初期化
  System::Initialize();

  // ネットワークマネージャーの生成
  pNetworkMgr = Network::CreateManager();

  // サーバーを生成する
  pServer = pNetworkMgr->CreateServer( 80, 16 );
  if ( pServer == NULL )
  {
    // 失敗
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // サーバー処理開始
  pServer->Start( ClientRecieve );

  // 全てのクライアントに送信
  pServer->SendAllClient( "めっせーじ", strlen("めっせーじ") + 1 );

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

void ClientRecieve( Network::IServerClientTCP *pClient )
{
  // 接続元クライアント情報
  Network::SHostInfo HostInfo;
  pClient->GetHostInfo( HostInfo );

  // クライアント用メイン通信ループ
  for ( ; ; )
  {
  }
}
@endcode
*/
		virtual Bool SendAllClient( const void *pData, Sint32 Size ) = 0;
	};
}
}

