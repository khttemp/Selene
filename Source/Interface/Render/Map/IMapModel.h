#pragma once


/**
	@file
	@brief �}�b�v���f���C���^�[�t�F�C�X
	@author �t���`
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
		@brief �}�b�v���f���f�[�^�p�C���^�[�t�F�C�X
		@author �t���`

		@note
		�}�b�v���f���f�[�^��ێ����邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IMapModel : public IInterface
	{
	public:
		virtual ~IMapModel() {}
	};
}
}
}

