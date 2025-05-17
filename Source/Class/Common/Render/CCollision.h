
#pragma once

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Color.h"
#include "Math/Vector3D.h"
#include "Collision/Line3D.h"
#include "Collision/Plane.h"
#include "Collision/Sphere.h"
#include "Class/Common/Object/CBaseObject.h"
#include "Interface/Render/IRender.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	class CRay
	{
	public:
		Math::Vector3D vStart;
		Math::Vector3D vDirection;
		Float fLength;

	public:
		CRay( void )
		{
		}
		CRay( const Math::Vector3D &Start, const Math::Vector3D &End )
		{
			this->vStart = Start;
			this->vDirection = End - Start;
			this->fLength = this->vDirection.Length();
			this->vDirection /= fLength;
		}
	};

	class CCylinder
	{
	public:
		Math::Vector3D Pt0;
		Math::Vector3D Pt1;
		Float fRadius;

	public:
		CCylinder( void )
		{
		}

		CCylinder( Math::Vector3D &Pt0, Math::Vector3D &Pt1, Float fRadius )
		{
			this->Pt0 = Pt0;
			this->Pt1 = Pt1;
			this->fRadius = fRadius;
		}
	};

	struct SCollisionAttribute
	{
		Sint32 Start;
		Sint32 Count;
		Sint32 Attribute;
	};

	struct SCollisionFace
	{
		Sint32 Attribute;
		Sint32 Index[3];
		Collision::CPlane Plane;
	};

	struct SCollisionVertex
	{
		Math::Vector3D Position;
		CColor Color;
		Math::Vector3D Normal;
	};

	class CCollision : public CBaseObject
	{
	private:
		SCollisionAttribute *m_pAttrTbl;
		SCollisionFace *m_pFaceTbl;
		SCollisionVertex *m_pVertexTbl;
		Sint32 m_AttrMax;
		Sint32 m_FaceMax;
		Sint32 m_VertexMax;
		Collision::CBox m_Box;

	public:
		CCollision();
		~CCollision();

	public:
		Sint32 GetVertexCount( void ) { return m_VertexMax; }
		Sint32 GetAttributeCount( void ) { return m_AttrMax; }
		Sint32 GetPolygonCount( void ) { return m_FaceMax; }
		SCollisionVertex &GetVertex( Sint32 Index ) { return m_pVertexTbl[Index]; }
		SCollisionFace &GetFace( Sint32 Index ) { return m_pFaceTbl[Index]; }

		Bool Ray_Sphere( const CRay &Ray, const Collision::CSphere &Sphere, Math::Vector3D &vHitPosition, Math::Vector3D &vHitNormal );
		Bool Ray_Cylinder( const CRay &Ray, const CCylinder &Capsule, Math::Vector3D &vHitPosition, Math::Vector3D &vHitNormal );

	public:
		void CreateCollisionFace( SCollisionFace *pFace, Sint32 Max );
		void CreateCollisionAttribute( SCollisionAttribute *pAttr, Sint32 Max );
		void CreateCollisionVertex( SCollisionVertex *pVtx, Sint32 Max );
		void UpdateCollision( void );

		virtual void SetBounding( Collision::CBox &Box );

	public:
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResult &Out );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResult &Out, Collision::CBox &Box );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResultExtend &Out );
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResultExtend &Out, Collision::CBox &Box );

		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius );
		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Collision::CBox &Box );
		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphere &Out );
		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphere &Out, Collision::CBox &Box );
		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphereExtend &Out );
		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphereExtend &Out, Collision::CBox &Box );
	};
}
}
