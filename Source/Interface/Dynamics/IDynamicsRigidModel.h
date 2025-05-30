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
namespace Dynamics
{
	/**
		@brief ダイナミクス用剛体インターフェイス
		@author 葉迩倭

		ダイナミクスを処理する剛体のインターフェイスです。
	*/
	class IRigidModel : public IInterface
	{
	public:
		virtual ~IRigidModel() {}
	};
}
}

