#pragma once


/**
	@file
	@brief システム系関数群
	@author 葉迩倭
*/

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CBaseList.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Network
{
/**
@brief ネットワークマネージャーインターフェイス生成
@author 葉迩倭
@return ネットワークマネージャーインターフェイス

@note
新規のネットワークマネージャーインターフェイスを生成します。<BR>
ネットワークのパスなどの設定は全てINetworkManagerを経由して行います。
取得したネットワークマネージャーインターフェイスは使用終了後には必ずRelease()して下さい。。

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Network::INetworkManager *pNetworkMgr = NULL;

  // システムの初期化
  System::Initialize();

  // ネットワークマネージャーの生成
  pNetworkMgr = Network::CreateManager();

  // ネットワークマネージャーの解放
  SAFE_RELEASE( pNetworkMgr );

  // コアの解放
  SAFE_RELEASE( pCore );

  // システムの解放
  System::Finalize();

  return 0;
}
@endcode
*/
SELENE_DLL_API INetworkManager *CreateManager( void );
}
}

