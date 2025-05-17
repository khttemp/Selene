#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Collision/Box.h"
#include "Collision/Line3D.h"
#include "Math/Math.h"
#include "Class/Common/Object/CBaseObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CCollisionController : public CBaseObject
	{
	protected:
		CModel				*m_pModel;
		CFrame				**m_pFrameRefTbl;
		Collision::CBox		*m_pBoxTbl;
		Sint32				m_BoxCount;
		Sint32				m_HitFrame;
		Math::Vector3D		m_vHitPosision;
		Math::Vector3D		m_vHitNormal;

	public:
		CCollisionController( CModel *pModel, Sint32 Count );
		virtual ~CCollisionController();

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

		virtual void SetEnable( Sint32 Index, Bool IsEnable );
		virtual void SetEnable( const char *pName, Bool IsEnable );
		virtual void Update( void );
		virtual void Rendering( ILine3D *pLine );

		virtual void GetCollisionResult( Sint32 &FrameNo, Math::Vector3D &vPos );

		virtual Bool Check( CCollisionController *pSrc );
		virtual Bool Check( Collision::CBox &Src );
		virtual Bool Check( Collision::CLine3D &Src );
		virtual Bool Check( Math::Vector3D &Src );
		virtual Bool CheckOnScreen( Math::Vector2D &Src, Scene::ISceneManager *pSceneMgr );
	};
}
}
}

