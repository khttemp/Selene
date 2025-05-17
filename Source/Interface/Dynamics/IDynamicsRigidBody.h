#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Vector3D.h"
#include "Math/Matrix.h"
#include "Interface/IInterface.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	enum eBodyType
	{
		BODY_TYPE_GEOMETRY,
		BODY_TYPE_MODEL,
		BODY_TYPE_MAP,
	};

namespace Dynamics
{
	/**
		@brief ダイナミクス用剛体インターフェイス
		@author 葉迩倭

		ダイナミクスを処理する剛体のインターフェイスです。
	*/
	class IRigidBody : public IInterface
	{
	public:
		virtual ~IRigidBody() {}

		virtual void SetUserData( void *pUser ) = 0;
		virtual void *GetUserData( void ) = 0;
		virtual eBodyType GetType( void ) = 0;

		virtual void SetPosition( Math::Vector3D &vPos ) = 0;
		virtual void SetRotation( Math::Matrix &mRot ) = 0;
		virtual void SetLinearSpeed( Math::Vector3D &vDir ) = 0;
		virtual void SetAngularSpeed( Math::Vector3D &vDir ) = 0;

		virtual Math::Matrix &GetMatrix( void ) = 0;
		virtual void GetPosition( Math::Vector3D &vPos ) = 0;

		virtual void SetFixed( void ) = 0;
	};
}
}

