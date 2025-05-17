#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Platform/Render/CRender.h"
#include "Class/Common/Render/3D/CPrimitive3D.h"
#include "Class/Common/Scene/CSceneParticleActorObject.h"
#include "Interface/Render/3D/IParticle.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CParticle : public CPrimitive3D, public IParticle
	{
	private:
		eParticleType m_VertexType;
		ITexture *m_pTexture;
		Math::Vector3D m_vCenter;

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

		virtual Bool IsSupportVertexBone( void )    { return false; } 
		virtual Bool IsSupportVertexTexture( void ) { return true; } 
		virtual Bool IsSupportVertexNormal( void )  { return m_VertexType == PARTICLE_TYPE_VOLUME; }
		virtual Bool IsSupportVertexBump( void )    { return false; }

	public:
		virtual void CreateRenderActor( Scene::CParticleActorObject *pActor );

	public:
		CParticle( CRender *pRender, CRenderObjectMgr *pMgr, Bool IsSoftBillboard );
		virtual ~CParticle();

		virtual Bool Create( Sint32 VertexMax, Sint32 IndexMax, ITexture *pTexture, eParticleType Type );

		virtual const Math::Vector3D GetCenter( void ) { return m_vCenter; }
		virtual void SetBasePosition( const Math::Vector3D &vPos ) { m_vCenter = vPos; }

		virtual void Begin( void );
		virtual void End( void );

		virtual void Draw( const Math::Vector3D &vPosition, const Math::Point2DF &Size, const Math::Rect2DI &SrcRect, CColor Color );
		virtual void Draw( const Math::Vector3D &vPosition, const Math::Vector2D PtTbl[], const Math::Rect2DI &SrcRect, CColor Color );
		virtual void DrawRotate( const Math::Vector3D &vPosition, const Math::Point2DF &Size, const Math::Rect2DI &SrcRect, CColor Color, Sint32 Angle );
		virtual void DrawRotate( const Math::Vector3D &vPosition, const Math::Vector2D PtTbl[], const Math::Rect2DI &SrcRect, CColor Color, Sint32 Angle );
	};
}
}
}
