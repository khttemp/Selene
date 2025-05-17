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
	struct SSurfaceParameter
	{
		eContactMode	Mode;				///< モード
		Float			Friction;			///< 摩擦係数
		Float			FrictionEx;			///< 摩擦係数
		Float			Bounce;				///< 反射係数
		Float			BounceVelocity;		///< 反射最低速度
		Float			SoftErp;
		Float			SoftCfm;
		Float			Motion;
		Float			MotionEx;
		Float			Slip;
		Float			SlipEx;
	};

	/**
		@brief 接触点処理用インターフェイス
		@author 葉迩倭

		ダイナミクスの接触点を管理するためのインターフェイスです。
	*/
	class IContactPoint : public IInterface
	{
	public:
		virtual ~IContactPoint() {}

		virtual Sint32 GetCount( void ) = 0;
		virtual void SetSurfaceParameter( Sint32 Index, SSurfaceParameter &Param ) = 0;
	};
}
}

