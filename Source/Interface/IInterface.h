#pragma once


/**
	@file
	@brief インターフェイス基底クラス
	@author 葉迩倭
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
	/**
		@brief インターフェース基底クラス
		@author 葉迩倭
	*/
	class IInterface
	{
	public:
		virtual ~IInterface() {}

/**
@brief 有効性チェック
@author 葉迩倭
@retval true 無効
@retval false 有効

@note
インターフェイスが有効か無効かを調べます。

@code
// 有効かチェック
if ( this->IsInvalid() )
{
	// 無効なインターフェイス
	reutrn false;
}
*/
		virtual Bool IsInvalid( void ) = 0;

/**
@brief 参照カウンタデクリメント
@author 葉迩倭
@return デクリメント後の参照カウント

@note
参照カウンタをデクリメントし、<BR>
参照カウントが0になった時点でメモリから解放します。

@code
// 解放（参照カウンタを-1するだけ。実際には参照カウントが0になるとメモリから消される）
this->Release();
@endcode
*/
		virtual Sint32 Release( void ) = 0;

/**
@brief 参照カウンタインクリメント
@author 葉迩倭
@return インクリメント後の参照カウント

@note
参照カウンタをインクリメントします。<BR>
インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
AddRef()をしたインターフェイスは必ずRelease()で解放してください。

@code
IInterface *pCopy = this;
// 他でも参照するので参照数+1
this->AddRef();
@endcode
*/
		virtual Sint32 AddRef( void ) = 0;
	};
}

