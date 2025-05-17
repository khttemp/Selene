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
		eContactMode	Mode;				///< ���[�h
		Float			Friction;			///< ���C�W��
		Float			FrictionEx;			///< ���C�W��
		Float			Bounce;				///< ���ˌW��
		Float			BounceVelocity;		///< ���ˍŒᑬ�x
		Float			SoftErp;
		Float			SoftCfm;
		Float			Motion;
		Float			MotionEx;
		Float			Slip;
		Float			SlipEx;
	};

	/**
		@brief �ڐG�_�����p�C���^�[�t�F�C�X
		@author �t���`

		�_�C�i�~�N�X�̐ڐG�_���Ǘ����邽�߂̃C���^�[�t�F�C�X�ł��B
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

