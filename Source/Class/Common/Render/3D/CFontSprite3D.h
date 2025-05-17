#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Math.h"
#include "Class/Common/Object/CBaseFontSheet.h"
#include "Class/Common/Scene/CSceneParticleActorObject.h"
#include "Interface/Render/3D/IFontSprite3D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	class CFontSprite3D : public CBaseFontSheet, public IFontSprite3D
	{
	protected:
		IParticle *m_pParticles[SHEET_MAX];

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		virtual void CreateRenderActor( Sint32 Index, Scene::CParticleActorObject *pActor );
		virtual Sint32 GetSheetCount( void );

	public:
		CFontSprite3D( CRender *pRender, CRenderObjectMgr *pMgr );
		virtual ~CFontSprite3D();

		virtual Bool CreateFromFile( const char *pFileName, const char *pExt, Sint32 Num );

		virtual void Begin( void );
		virtual void End( void );

		virtual void DrawString( const char *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color );
		virtual void DrawStringP( const char *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color );
		virtual Math::Point2DI GetCount( const char *pStr );

		virtual void DrawString( const wchar_t *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color );
		virtual void DrawStringP( const wchar_t *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color );
		virtual Math::Point2DI GetCount( const wchar_t *pStr );
	};
}
}
}
