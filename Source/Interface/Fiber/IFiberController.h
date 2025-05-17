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
namespace Fiber
{
	/**
		@brief ファイバーコントローラーインターフェイス
		@author 葉迩倭

		@note
		ファイバーの制御を行うためのインターフェイスです。
	*/
	class IFiberController : public IInterface
	{
	public:
		virtual ~IFiberController() {}

/**
@brief ファイバーシステム開始
@author 葉迩倭
@note
ファイバーの処理を開始します。
*/
		virtual void Start( void ) = 0;

/**
@brief ファイバーシステム終了
@author 葉迩倭
@note
ファイバーの処理を終了します。
*/
		virtual void Exit( void ) = 0;

/**
@brief ファイバー切り替え
@author 葉迩倭
@retval false	アプリケーションは終了している
@retval true	アプリケーションは継続中である
@note
ファイバーの切り替えを行います。
*/
		virtual Bool Switch( void ) = 0;

/**
@brief ファイバー生成
@author 葉迩倭
@param FiberId	[in] ファイバーID
@param pFiber	[in] ファイバーインターフェイス
@retval false	指定のFiberIdにすでにファイバーがある
@retval true	成功
@note
ファイバーの生成を行います。
*/
		virtual Bool Create( Sint32 FiberId, IFiber *pFiber ) = 0;
	};
}
}


