#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Class/Platform/Render/CRender.h"
#include "Class/Common/Render/3D/CPrimitive3D.h"
#include "Class/Common/Scene/CSceneSpriteActorObject.h"
#include "Interface/Render/3D/ISprite3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CSprite3D : public CPrimitive3D, public ISprite3D
	{
	private:
		ITexture *m_pTexture;

	public:
		virtual void CreateRenderActor( Scene::CSpriteActorObject *pActor );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

		virtual Bool IsSupportVertexBone( void )    { return false; } 
		virtual Bool IsSupportVertexTexture( void ) { return true; } 
		virtual Bool IsSupportVertexNormal( void )  { return false; }
		virtual Bool IsSupportVertexBump( void )    { return false; }

	public:
		CSprite3D( CRender *pRender, CRenderObjectMgr *pMgr );
		virtual ~CSprite3D();

		virtual Bool Create( Sint32 VertexMax, Sint32 IndexMax, ITexture *pTexture );

		virtual void Begin( void );
		virtual void End( void );

		virtual void Draw( const Math::Matrix &mWorld, const Math::Point2DF &Size, const Math::Rect2DI &SrcRect, CColor Color );
		virtual void Draw( const Math::Matrix &mWorld, const Math::Vector2D PtTbl[], const Math::Rect2DI &SrcRect, CColor Color );

		virtual void DrawPolyLine( const Math::Vector3D &vCameraPosition, const Math::Vector3D Pos[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src );
		virtual void DrawPolyLine( const Math::Vector3D &vCameraPosition, const Math::Vector3D Pos[], const CColor Color[], const Float Width[], Sint32 Count, const Math::Rect2DF &Src );
		virtual void DrawPolyLine( const Math::Vector3D &vCameraPosition, const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src );

		virtual void DrawListXY( const Math::Vector3D Pos[], const Sint32 Angle[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src );
		virtual void DrawListYZ( const Math::Vector3D Pos[], const Sint32 Angle[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src );
		virtual void DrawListZX( const Math::Vector3D Pos[], const Sint32 Angle[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src );

		virtual void DrawListXY( const Math::Vector3D Pos[], const Float Width[], const Sint32 Angle[], const CColor Color[], Sint32 Count, const Math::Rect2DF &Src );
		virtual void DrawListYZ( const Math::Vector3D Pos[], const Float Width[], const Sint32 Angle[], const CColor Color[], Sint32 Count, const Math::Rect2DF &Src );
		virtual void DrawListZX( const Math::Vector3D Pos[], const Float Width[], const Sint32 Angle[], const CColor Color[], Sint32 Count, const Math::Rect2DF &Src );

		virtual void DrawListXY( const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src );
		virtual void DrawListYZ( const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src );
		virtual void DrawListZX( const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src );
	};
}
}
}
