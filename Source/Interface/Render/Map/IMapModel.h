#pragma once


/**
	@file
	@brief マップモデルインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Color.h"
#include "Collision/Line3D.h"
#include "Collision/Box.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	/**
		@brief マップモデルデータ用インターフェイス
		@author 葉迩倭

		@note
		マップモデルデータを保持するためのインターフェイスです。
	*/
	class IMapModel : public IInterface
	{
	public:
		virtual ~IMapModel() {}
	};
}
}
}

