#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Network/INetworkManager.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Network
{
	/**
		@brief TCP接続サーバーに接続されたクライアントクラス
		@author 葉迩倭

		@note
		Seleneで使用するネットワーク処理を行います。
	*/
	class IServerClientTCP : public IInterface
	{
	public:
		virtual ~IServerClientTCP() {}

/**
@brief データ送信
@author 葉迩倭
@param pData	[in] データ格納バッファ
@param Size		[in] 送信サイズ
@retval false	失敗
@retval true	成功

@note
データの送信を行います。<BR>
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
    const Uint32 MAX_PACKET_SIZE = 256;
    Sint8 PacketBuffer[MAX_PACKET_SIZE];

    // クライアントへパケットを送る
    if ( !pClient->Send( PacketBuffer, sizeof(PacketBuffer) ) )
    {
      // エラーor切断
      return;
    }
  }
}
@endcode
*/
		virtual Bool Send( const void *pData, Sint32 Size ) = 0;

/**
@brief データ受信
@author 葉迩倭
@param pData	[in] データ格納バッファ
@param Size		[in] 受信サイズ
@retval false	失敗
@retval true	成功

@note
データの受信を行います。<BR>
指定サイズの受信が完了するまで関数から抜けてきません。

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
    const Uint32 MAX_PACKET_SIZE = 256;
    Sint8 PacketBuffer[MAX_PACKET_SIZE];

    // クライアントからのパケットを待つ
    if ( !pClient->Recv( PacketBuffer, sizeof(PacketBuffer) ) )
    {
      // エラーor切断
      return;
    }
  }
}
@endcode
*/
		virtual Bool Recv( void *pData, Sint32 Size ) = 0;

/**
@brief 接続されたクライアントの情報取得
@author 葉迩倭
@param Info	[in] クライアント情報

@note
接続されたクライアントの情報を取得します。

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
    const Uint32 MAX_PACKET_SIZE = 256;
    Sint8 PacketBuffer[MAX_PACKET_SIZE];

    // クライアントからのパケットを待つ
    if ( !pClient->Recv( PacketBuffer, sizeof(PacketBuffer) ) )
    {
      // エラーor切断
      return;
    }
  }
}
@endcode
*/
		virtual void GetHostInfo( SHostInfo &Info ) = 0;
	};
}
}

