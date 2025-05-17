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
		@brief TCP接続クライアントクラス
		@author 葉迩倭

		@note
		Seleneで使用するネットワーク処理を行います。
	*/
	class ISocketTCP : public IInterface
	{
	public:
		virtual ~ISocketTCP() {}

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

  const Uint32 MAX_PACKET_SIZE = 256;
  Sint8 PacketBuffer[MAX_PACKET_SIZE];

  // データ送信
  if ( !pTCP->Send( PacketBuffer, sizeof(PacketBuffer) ) )
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

  const Uint32 MAX_PACKET_SIZE = 256;
  Sint8 PacketBuffer[MAX_PACKET_SIZE];

  // データ受信
  if ( !pTCP->Recv( PacketBuffer, sizeof(PacketBuffer) ) )
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
		virtual Bool Recv( void *pData, Sint32 Size ) = 0;
	};
}
}

