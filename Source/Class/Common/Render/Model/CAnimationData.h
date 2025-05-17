#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Object/CBaseObject.h"
#include "Class/Common/Object/CBaseList.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Math/Animation.h"
#include "Common/SMF.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CAnimationData : public CBaseObject
	{
	private:
		Math::Animation *m_pScaleX;
		Math::Animation *m_pScaleY;
		Math::Animation *m_pScaleZ;
		Math::Animation *m_pTranslateX;
		Math::Animation *m_pTranslateY;
		Math::Animation *m_pTranslateZ;
		Math::Animation *m_pRotateNo;

		Math::Quaternion *m_pRotate;

		Float m_fSx;
		Float m_fSy;
		Float m_fSz;
		Float m_fTx;
		Float m_fTy;
		Float m_fTz;
		Math::Quaternion m_qRotate;

	public:
		CAnimationData();
		virtual ~CAnimationData();

		virtual void SetScaleKey( const SMF_ANIMATIONKEY_SCALE *pData, Sint32 Count );
		virtual void SetRotateKey( const SMF_ANIMATIONKEY_ROTATE *pData, Sint32 Count );
		virtual void SetTranslateKey( const SMF_ANIMATIONKEY_TRANSLATE *pData, Sint32 Count );
		virtual void GetParameter( Float &fSx, Float &fSy, Float &fSz, Float &fTx, Float &fTy, Float &fTz, Math::Quaternion &qRotate );

	public:

		virtual void Update( Float fTime, eAnimationType Type );
	};
}
}
}
