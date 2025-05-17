#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Common/Object/CBaseObject.h"
#include "Class/Common/Object/CBaseList.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Math/Style.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CMapFrame : public CBaseObject
	{
	private:
		CMapFrame *m_pChild[2][2][2];
		Sint32 m_MeshIndex;
		Collision::CBox m_OBB;
		Math::Vector3D m_vMin;
		Math::Vector3D m_vMax;

	public:
		CMapFrame();
		virtual ~CMapFrame();

		virtual void ConnectChildFrame( Sint32 x, Sint32 y, Sint32 z, CMapFrame *pFrame );
		virtual void ConnectMesh( Sint32 Index );
		virtual Sint32 GetConnectMesh( void );

		virtual void SetBounding( const Math::Vector3D &vMin, const Math::Vector3D &vMax );

		virtual void RenderingTree( Scene::CCamera &Camera );
		virtual void RenderingBounding( ILine3D *pLine );

		virtual const Collision::CBox &GetOBB( void ) { return m_OBB; }
		virtual void GetOBB( Math::Vector3D &vMin, Math::Vector3D &vMax ) { vMin = m_vMin; vMax = m_vMax; }

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }
	};
}
}
}
