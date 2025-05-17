

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Collision/Collision.h"
#include "Class/Common/Render/CCollision.h"


//-----------------------------------------------------------------------------------
// PROTOTYPE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
	Bool Line_Triangle( const Math::Vector3D *pPtTbl[], const CPlane &Plane, const Math::Vector3D *pPlanePoints[], Math::Vector3D &vIntersect );
}
}


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCollision::CCollision()
	: m_pVertexTbl	( NULL )
	, m_pAttrTbl	( NULL )
	, m_pFaceTbl	( NULL )
	, m_AttrMax		( 0 )
	, m_FaceMax		( 0 )
	, m_VertexMax	( 0 )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CCollision::~CCollision()
{
	SAFE_DELETE_ARRAY( m_pVertexTbl );
	SAFE_DELETE_ARRAY( m_pAttrTbl );
	SAFE_DELETE_ARRAY( m_pFaceTbl );
	m_AttrMax	= 0;
	m_FaceMax	= 0;
	m_VertexMax	= 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCollision::CreateCollisionFace( SCollisionFace *pFace, Sint32 Max )
{
	m_FaceMax = Max;
	m_pFaceTbl = new SCollisionFace [ Max ];

	MemoryCopy( m_pFaceTbl, pFace, sizeof(SCollisionFace) * Max );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCollision::CreateCollisionAttribute( SCollisionAttribute *pAttr, Sint32 Max )
{
	m_AttrMax = Max;
	m_pAttrTbl = new SCollisionAttribute [ Max ];

	MemoryCopy( m_pAttrTbl, pAttr, sizeof(SCollisionAttribute) * Max );

}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCollision::CreateCollisionVertex( SCollisionVertex *pVtx, Sint32 Max )
{
	m_VertexMax = Max;
	m_pVertexTbl = new SCollisionVertex [ Max ];

	MemoryCopy( m_pVertexTbl, pVtx, sizeof(SCollisionVertex) * Max );

	Math::Vector3D vMin = pVtx[0].Position;
	Math::Vector3D vMax = pVtx[0].Position;
	for ( Sint32 i = 1; i < Max; i++ )
	{
		if ( vMin.x > pVtx[i].Position.x ) vMin.x = pVtx[i].Position.x;
		if ( vMin.y > pVtx[i].Position.y ) vMin.y = pVtx[i].Position.y;
		if ( vMin.z > pVtx[i].Position.z ) vMin.z = pVtx[i].Position.z;
		if ( vMax.x < pVtx[i].Position.x ) vMax.x = pVtx[i].Position.x;
		if ( vMax.y < pVtx[i].Position.y ) vMax.y = pVtx[i].Position.y;
		if ( vMax.z < pVtx[i].Position.z ) vMax.z = pVtx[i].Position.z;
	}

	Math::Matrix mTransform;
	mTransform.Identity();
	m_Box.CreateBox( vMin, vMax, mTransform );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCollision::UpdateCollision( void )
{
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CCollision::SetBounding( Collision::CBox &Box )
{
	m_Box = Box;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCollision::HitCheckByRay( const Collision::CLine3D &Ray )
{
	// OBBと判定
	if ( Collision::Line_Box_3D( Ray, m_Box ) )
	{
		const Math::Vector3D *pRay[] = {
			&Ray.vStart, 
			&Ray.vEnd,
		};

		Sint32 Max = m_FaceMax;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			const Math::Vector3D *pPt[] = {
				&m_pVertexTbl[m_pFaceTbl[i].Index[0]].Position,
				&m_pVertexTbl[m_pFaceTbl[i].Index[1]].Position,
				&m_pVertexTbl[m_pFaceTbl[i].Index[2]].Position,
			};

			// 面に対して交差しているか
			Math::Vector3D vHit;
			if ( Collision::Line_Triangle( pRay, m_pFaceTbl[i].Plane, pPt, vHit ) )
			{
				return true;
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCollision::HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box )
{
	// OBBと判定
	if ( Collision::Line_Box_3D( Ray, m_Box ) )
	{
		const Math::Vector3D *pRay[] = {
			&Ray.vStart, 
			&Ray.vEnd,
		};

		Sint32 Max = m_FaceMax;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			const Math::Vector3D *pPt[] = {
				&m_pVertexTbl[m_pFaceTbl[i].Index[0]].Position,
				&m_pVertexTbl[m_pFaceTbl[i].Index[1]].Position,
				&m_pVertexTbl[m_pFaceTbl[i].Index[2]].Position,
			};

			// 面に対して交差しているか
			Math::Vector3D vHit;
			if ( Collision::Line_Triangle( pRay, m_pFaceTbl[i].Plane, pPt, vHit ) )
			{
				Box = m_Box;
				return true;
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCollision::HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResult &Out )
{
	Float fLengthSq = FLT_MAX;
	Math::Vector3D vIntersectPosition;
	Sint32 IntersectID = -1;

	// OBBと判定
	if ( Collision::Line_Box_3D( Ray, m_Box ) )
	{
		const Math::Vector3D *pRay[] = {
			&Ray.vStart, 
			&Ray.vEnd,
		};

		Sint32 Max = m_FaceMax;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			const Math::Vector3D *pPt[] = {
				&m_pVertexTbl[m_pFaceTbl[i].Index[0]].Position,
				&m_pVertexTbl[m_pFaceTbl[i].Index[1]].Position,
				&m_pVertexTbl[m_pFaceTbl[i].Index[2]].Position,
			};

			// 面に対して交差しているか
			Math::Vector3D vHit;
			if ( Collision::Line_Triangle( pRay, m_pFaceTbl[i].Plane, pPt, vHit ) )
			{
				Float fLen = (vHit - Ray.vStart).LengthSq();
				if ( fLengthSq > fLen )
				{
					vIntersectPosition = vHit;
					IntersectID = i;
					fLengthSq = fLen;
				}
			}
		}
	}

	// 衝突してる？
	if ( IntersectID != -1 )
	{
		SCollisionFace &Col = m_pFaceTbl[IntersectID];
		Out.Attribute		= m_pAttrTbl[Col.Attribute].Attribute;
		Out.vNormal			= Col.Plane.n;
		Out.vHitPosition	= vIntersectPosition;
		Out.vTriangle[0]	= m_pVertexTbl[Col.Index[0]].Position;
		Out.vTriangle[1]	= m_pVertexTbl[Col.Index[1]].Position;
		Out.vTriangle[2]	= m_pVertexTbl[Col.Index[2]].Position;
		Out.Color[0]		= m_pVertexTbl[Col.Index[0]].Color;
		Out.Color[1]		= m_pVertexTbl[Col.Index[1]].Color;
		Out.Color[2]		= m_pVertexTbl[Col.Index[2]].Color;

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCollision::HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResult &Out, Collision::CBox &Box )
{
	Float fLengthSq = FLT_MAX;
	Math::Vector3D vIntersectPosition;
	Sint32 IntersectID = -1;

	// OBBと判定
	if ( Collision::Line_Box_3D( Ray, m_Box ) )
	{
		const Math::Vector3D *pRay[] = {
			&Ray.vStart, 
			&Ray.vEnd,
		};

		Sint32 Max = m_FaceMax;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			const Math::Vector3D *pPt[] = {
				&m_pVertexTbl[m_pFaceTbl[i].Index[0]].Position,
				&m_pVertexTbl[m_pFaceTbl[i].Index[1]].Position,
				&m_pVertexTbl[m_pFaceTbl[i].Index[2]].Position,
			};

			// 面に対して交差しているか
			Math::Vector3D vHit;
			if ( Collision::Line_Triangle( pRay, m_pFaceTbl[i].Plane, pPt, vHit ) )
			{
				Float fLen = (vHit - Ray.vStart).LengthSq();
				if ( fLengthSq > fLen )
				{
					fLengthSq = fLen;
					IntersectID = i;
					vIntersectPosition = vHit;
				}
			}
		}
	}

	// 衝突してる？
	if ( IntersectID != -1 )
	{
		Box = m_Box;

		SCollisionFace &Col = m_pFaceTbl[IntersectID];
		Out.Attribute		= m_pAttrTbl[Col.Attribute].Attribute;
		Out.vNormal			= Col.Plane.n;
		Out.vHitPosition	= vIntersectPosition;
		Out.vTriangle[0]	= m_pVertexTbl[Col.Index[0]].Position;
		Out.vTriangle[1]	= m_pVertexTbl[Col.Index[1]].Position;
		Out.vTriangle[2]	= m_pVertexTbl[Col.Index[2]].Position;
		Out.Color[0]		= m_pVertexTbl[Col.Index[0]].Color;
		Out.Color[1]		= m_pVertexTbl[Col.Index[1]].Color;
		Out.Color[2]		= m_pVertexTbl[Col.Index[2]].Color;

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCollision::HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResultExtend &Out )
{
	Float fLengthSq = FLT_MAX;
	Math::Vector3D vIntersectPosition;
	Sint32 IntersectID = -1;

	// OBBと判定
	if ( Collision::Line_Box_3D( Ray, m_Box ) )
	{
		const Math::Vector3D *pRay[] = {
			&Ray.vStart, 
			&Ray.vEnd,
		};

		Sint32 Max = m_FaceMax;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			const Math::Vector3D *pPt[] = {
				&m_pVertexTbl[m_pFaceTbl[i].Index[0]].Position,
				&m_pVertexTbl[m_pFaceTbl[i].Index[1]].Position,
				&m_pVertexTbl[m_pFaceTbl[i].Index[2]].Position,
			};

			// 面に対して交差しているか
			Math::Vector3D vHit;
			if ( Collision::Line_Triangle( pRay, m_pFaceTbl[i].Plane, pPt, vHit ) )
			{
				Float fLen = (vHit - Ray.vStart).LengthSq();
				if ( fLengthSq > fLen )
				{
					vIntersectPosition = vHit;
					IntersectID = i;
					fLengthSq = fLen;
				}
			}
		}
	}

	// 衝突してる？
	if ( IntersectID != -1 )
	{
		SCollisionFace &Col = m_pFaceTbl[IntersectID];
		Out.Attribute		= m_pAttrTbl[Col.Attribute].Attribute;
		Out.vNormal			= Col.Plane.n;
		Out.vHitPosition	= vIntersectPosition;
		Out.vTriangle[0]	= m_pVertexTbl[Col.Index[0]].Position;
		Out.vTriangle[1]	= m_pVertexTbl[Col.Index[1]].Position;
		Out.vTriangle[2]	= m_pVertexTbl[Col.Index[2]].Position;
		Out.Color[0]		= m_pVertexTbl[Col.Index[0]].Color;
		Out.Color[1]		= m_pVertexTbl[Col.Index[1]].Color;
		Out.Color[2]		= m_pVertexTbl[Col.Index[2]].Color;

		// 壁からの距離
		Float fDist = Col.Plane.Dot( Ray.vEnd );

		// 壁を反射後の位置
		Out.vRefrectPosition = Ray.vEnd - (Col.Plane.n * (fDist * 2.0f));

		// 壁ぞいの停止位置
		Out.vSlidePosition = Ray.vEnd - (Col.Plane.n * fDist);

		// 反射方向
		Out.vRefrectDirection = Out.vRefrectPosition - Out.vHitPosition;
		Out.vRefrectDirection.NormalizeFast();

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCollision::HitCheckByRay( const Collision::CLine3D &Ray, SCollisionResultExtend &Out, Collision::CBox &Box )
{
	Float fLengthSq = FLT_MAX;
	Math::Vector3D vIntersectPosition;
	Sint32 IntersectID = -1;

	// OBBと判定
	if ( Collision::Line_Box_3D( Ray, m_Box ) )
	{
		const Math::Vector3D *pRay[] = {
			&Ray.vStart, 
			&Ray.vEnd,
		};

		Sint32 Max = m_FaceMax;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			const Math::Vector3D *pPt[] = {
				&m_pVertexTbl[m_pFaceTbl[i].Index[0]].Position,
				&m_pVertexTbl[m_pFaceTbl[i].Index[1]].Position,
				&m_pVertexTbl[m_pFaceTbl[i].Index[2]].Position,
			};

			// 面に対して交差しているか
			Math::Vector3D vHit;
			if ( Collision::Line_Triangle( pRay, m_pFaceTbl[i].Plane, pPt, vHit ) )
			{
				Float fLen = (vHit - Ray.vStart).LengthSq();
				if ( fLengthSq > fLen )
				{
					fLengthSq = fLen;
					IntersectID = i;
					vIntersectPosition = vHit;
				}
			}
		}
	}

	// 衝突してる？
	if ( IntersectID != -1 )
	{
		Box = m_Box;

		SCollisionFace &Col = m_pFaceTbl[IntersectID];
		Out.Attribute		= m_pAttrTbl[Col.Attribute].Attribute;
		Out.vNormal			= Col.Plane.n;
		Out.vHitPosition	= vIntersectPosition;
		Out.vTriangle[0]	= m_pVertexTbl[Col.Index[0]].Position;
		Out.vTriangle[1]	= m_pVertexTbl[Col.Index[1]].Position;
		Out.vTriangle[2]	= m_pVertexTbl[Col.Index[2]].Position;
		Out.Color[0]		= m_pVertexTbl[Col.Index[0]].Color;
		Out.Color[1]		= m_pVertexTbl[Col.Index[1]].Color;
		Out.Color[2]		= m_pVertexTbl[Col.Index[2]].Color;

		// 壁反射後の位置
		Float fDist = Col.Plane.Dot( Ray.vEnd );
		Out.vRefrectPosition = Ray.vEnd;
		Out.vRefrectPosition -= Col.Plane.n * (fDist * 2.0f);

		// 壁ぞいの停止位置
		Collision::CLine3D Line( Ray.vEnd, Out.vRefrectPosition );
		Collision::Line_Plane_3D( Line, Col.Plane, Out.vSlidePosition );

		// 反射方向
		Out.vRefrectDirection = Out.vRefrectPosition - Out.vHitPosition;
		Out.vRefrectDirection.NormalizeFast();

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCollision::HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius )
{
	// OBBと判定
//	if ( Collision::Line_Box_3D( Ray, m_Box ) )
	{
		const Math::Vector3D *pRay[] = {
			&Ray.vStart, 
			&Ray.vEnd,
		};

		// 各平面に対するチェック
		Sint32 Max = m_FaceMax;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			Collision::CPlane Plane = m_pFaceTbl[i].Plane;

			Math::Vector3D Pos[] = {
				m_pVertexTbl[m_pFaceTbl[i].Index[0]].Position + (Plane.n * fRadius),
				m_pVertexTbl[m_pFaceTbl[i].Index[1]].Position + (Plane.n * fRadius),
				m_pVertexTbl[m_pFaceTbl[i].Index[2]].Position + (Plane.n * fRadius),
			};

			Plane.d = -Pos[0].Dot( Plane.n );

			const Math::Vector3D *pPt[] = {
				&Pos[0], &Pos[1], &Pos[2],
			};

			// 面に対して交差しているか
			Math::Vector3D vHit;
			if ( Collision::Line_Triangle( pRay, Plane, pPt, vHit ) )
			{
				return true;
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCollision::HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Collision::CBox &Box )
{
	// OBBと判定
//	if ( Collision::Line_Box_3D( Ray, m_Box ) )
	{
		const Math::Vector3D *pRay[] = {
			&Ray.vStart, 
			&Ray.vEnd,
		};

		// 各平面に対するチェック
		Sint32 Max = m_FaceMax;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			Collision::CPlane Plane = m_pFaceTbl[i].Plane;

			Math::Vector3D Pos[] = {
				m_pVertexTbl[m_pFaceTbl[i].Index[0]].Position + (Plane.n * fRadius),
				m_pVertexTbl[m_pFaceTbl[i].Index[1]].Position + (Plane.n * fRadius),
				m_pVertexTbl[m_pFaceTbl[i].Index[2]].Position + (Plane.n * fRadius),
			};

			Plane.d = -Pos[0].Dot( Plane.n );

			const Math::Vector3D *pPt[] = {
				&Pos[0], &Pos[1], &Pos[2],
			};

			// 面に対して交差しているか
			Math::Vector3D vHit;
			if ( Collision::Line_Triangle( pRay, Plane, pPt, vHit ) )
			{
				Box = m_Box;
				return true;
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCollision::HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, SCollisionResultSphere &Out )
{
	Float fLengthSq = FLT_MAX;
	Math::Vector3D vIntersectPosition, vIntersectNormal;
	Sint32 IntersectID = -1;
	Sint32 IntersectType = 0;

	CRay vRay( Ray.vStart, Ray.vEnd );

	// OBBと判定
//	if ( Collision::Line_Box_3D( Ray, m_Box ) )
	{
		const Math::Vector3D *pRay[] = {
			&Ray.vStart, 
			&Ray.vEnd,
		};
		Sint32 Max;

		// 各平面に対するチェック
		Max = m_FaceMax;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			Collision::CPlane Plane = m_pFaceTbl[i].Plane;

			Math::Vector3D Pos[] = {
				m_pVertexTbl[m_pFaceTbl[i].Index[0]].Position + (Plane.n * fRadius),
				m_pVertexTbl[m_pFaceTbl[i].Index[1]].Position + (Plane.n * fRadius),
				m_pVertexTbl[m_pFaceTbl[i].Index[2]].Position + (Plane.n * fRadius),
			};

			Plane.d = -Pos[0].Dot( Plane.n );

			const Math::Vector3D *pPt[] = {
				&Pos[0], &Pos[1], &Pos[2],
			};

			// 面に対して交差しているか
			Math::Vector3D vHit;
			if ( Collision::Line_Triangle( pRay, Plane, pPt, vHit ) )
			{
				Float fLen = (vHit - Ray.vStart).LengthSq();
				if ( fLengthSq > fLen )
				{
					vIntersectPosition = vHit;
					IntersectID = i;
					fLengthSq = fLen;
					IntersectType = 0;
				}
			}
		}
		// 各球に対するチェック
		Max = m_VertexMax;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			SCollisionVertex &Vtx = m_pVertexTbl[i];
			Math::Vector3D vHit, vNorm;
			if ( Ray_Sphere( vRay, Collision::CSphere( Vtx.Position, fRadius ), vHit, vNorm ) )
			{
				Float fLen = (vHit - Ray.vStart).LengthSq();
				if ( fLengthSq > fLen )
				{
					vIntersectPosition = vHit;
					vIntersectNormal = vNorm;
					IntersectID = i;
					fLengthSq = fLen;
					IntersectType = 1;
				}
			}
		}
		// 各軸に対するチェック
		Max = m_FaceMax;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			Collision::CPlane Plane = m_pFaceTbl[i].Plane;

			// 面に対して交差しているか
			for ( Sint32 j = 0; j < 3; j++ )
			{
				CCylinder Cylinder(
					m_pVertexTbl[m_pFaceTbl[i].Index[(j  )  ]].Position,
					m_pVertexTbl[m_pFaceTbl[i].Index[(j+1)%3]].Position,
					fRadius );

				Math::Vector3D vHit, vNorm;
				if ( Ray_Cylinder( vRay, Cylinder, vHit, vNorm ) )
				{
					Float fLen = (vHit - Ray.vStart).LengthSq();
					if ( fLengthSq > fLen )
					{
						vIntersectPosition = vHit;
						vIntersectNormal = vNorm;
						IntersectID = i;
						fLengthSq = fLen;
						IntersectType = 1;
					}
				}
			}
		}
	}

	// 衝突してる？
	if ( IntersectID != -1 )
	{
		Collision::CPlane Plane;
		switch ( IntersectType )
		{
		case 0:
			{
				SCollisionFace &Col = m_pFaceTbl[IntersectID];
				Plane = Col.Plane;
				Out.vNormal			= Plane.n;
				Out.vHitPosition	= vIntersectPosition;
			}
			break;
		case 1:
			{
				Plane.n = vIntersectNormal;
				Plane.d = -vIntersectPosition.Dot( Plane.n );

				Out.vNormal			= vIntersectNormal;
				Out.vHitPosition	= vIntersectPosition;
			}
			break;
		}

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCollision::HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, SCollisionResultSphere &Out, Collision::CBox &Box )
{
	Float fLengthSq = FLT_MAX;
	Math::Vector3D vIntersectPosition;
	Sint32 IntersectID = -1;

	// OBBと判定
//	if ( Collision::Line_Box_3D( Ray, m_Box ) )
	{
		const Math::Vector3D *pRay[] = {
			&Ray.vStart, 
			&Ray.vEnd,
		};

		// 各平面に対するチェック
		Sint32 Max = m_FaceMax;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			Collision::CPlane Plane = m_pFaceTbl[i].Plane;

			Math::Vector3D Pos[] = {
				m_pVertexTbl[m_pFaceTbl[i].Index[0]].Position + (Plane.n * fRadius),
				m_pVertexTbl[m_pFaceTbl[i].Index[1]].Position + (Plane.n * fRadius),
				m_pVertexTbl[m_pFaceTbl[i].Index[2]].Position + (Plane.n * fRadius),
			};

			Plane.d = -Pos[0].Dot( Plane.n );

			const Math::Vector3D *pPt[] = {
				&Pos[0], &Pos[1], &Pos[2],
			};

			// 面に対して交差しているか
			Math::Vector3D vHit;
			if ( Collision::Line_Triangle( pRay, Plane, pPt, vHit ) )
			{
				Float fLen = (vHit - Ray.vStart).LengthSq();
				if ( fLengthSq > fLen )
				{
					vIntersectPosition = vHit;
					IntersectID = i;
					fLengthSq = fLen;
				}
			}
		}
	}

	// 衝突してる？
	if ( IntersectID != -1 )
	{
		SCollisionFace &Col = m_pFaceTbl[IntersectID];
		Collision::CPlane Plane = Col.Plane;
		Math::Vector3D Pos[] = {
			m_pVertexTbl[Col.Index[0]].Position + (Plane.n * fRadius),
			m_pVertexTbl[Col.Index[1]].Position + (Plane.n * fRadius),
			m_pVertexTbl[Col.Index[2]].Position + (Plane.n * fRadius),
		};
		Plane.d = -Pos[0].Dot( Plane.n );

		Out.vNormal			= Plane.n;
		Out.vHitPosition	= vIntersectPosition;

		Box = m_Box;

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCollision::HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, SCollisionResultSphereExtend &Out )
{
	Float fLengthSq = FLT_MAX;
	Math::Vector3D vIntersectPosition, vIntersectNormal;
	Sint32 IntersectID = -1;

	CRay vRay( Ray.vStart, Ray.vEnd );

	// OBBと判定
//	if ( Collision::Line_Box_3D( Ray, m_Box ) )
	{
		const Math::Vector3D *pRay[] = {
			&Ray.vStart, 
			&Ray.vEnd,
		};
		Sint32 Max;

		// 各平面に対するチェック
		Max = m_FaceMax;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			Collision::CPlane Plane = m_pFaceTbl[i].Plane;

			Math::Vector3D Pos[] = {
				m_pVertexTbl[m_pFaceTbl[i].Index[0]].Position + (Plane.n * fRadius),
				m_pVertexTbl[m_pFaceTbl[i].Index[1]].Position + (Plane.n * fRadius),
				m_pVertexTbl[m_pFaceTbl[i].Index[2]].Position + (Plane.n * fRadius),
			};

			Plane.d = -Pos[0].Dot( Plane.n );

			const Math::Vector3D *pPt[] = {
				&Pos[0], &Pos[1], &Pos[2],
			};

			// 面に対して交差しているか
			Math::Vector3D vHit;
			if ( Collision::Line_Triangle( pRay, Plane, pPt, vHit ) )
			{
				Float fLen = (vHit - Ray.vStart).LengthSq();
				if ( fLengthSq > fLen )
				{
					vIntersectPosition = vHit;
					vIntersectNormal = Plane.n;
					IntersectID = i;
					fLengthSq = fLen;
				}
			}
		}
/*		// 各球に対するチェック
		Max = m_VertexMax;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			SCollisionVertex &Vtx = m_pVertexTbl[i];
			Math::Vector3D vHit, vNorm;
			if ( Ray_Sphere( vRay, Collision::CSphere( Vtx.Position, fRadius ), vHit, vNorm ) )
			{
				Float fLen = (vHit - Ray.vStart).LengthSq();
				if ( fLengthSq > fLen )
				{
					vIntersectPosition = vHit;
					vIntersectNormal = vNorm;
					IntersectID = i;
					fLengthSq = fLen;
					IntersectType = 1;
				}
			}
		}
		// 各軸に対するチェック
		Max = m_FaceMax;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			Collision::CPlane Plane = m_pFaceTbl[i].Plane;

			// 面に対して交差しているか
			for ( Sint32 j = 0; j < 3; j++ )
			{
				CCylinder Cylinder(
					m_pVertexTbl[m_pFaceTbl[i].Index[(j  )  ]].Position,
					m_pVertexTbl[m_pFaceTbl[i].Index[(j+1)%3]].Position,
					fRadius );

				Math::Vector3D vHit, vNorm;
				if ( Ray_Cylinder( vRay, Cylinder, vHit, vNorm ) )
				{
					Float fLen = (vHit - Ray.vStart).LengthSq();
					if ( fLengthSq > fLen )
					{
						vIntersectPosition = vHit;
						vIntersectNormal = vNorm;
						IntersectID = i;
						fLengthSq = fLen;
						IntersectType = 1;
					}
				}
			}
		}
*/	}

	// 衝突してる？
	if ( IntersectID != -1 )
	{
		Collision::CPlane Plane;
		Plane.n = vIntersectNormal;
		Plane.d = -vIntersectPosition.Dot( Plane.n );

		Out.vNormal = vIntersectNormal;
		Out.vHitPosition = vIntersectPosition;

		// 壁からの距離
		Float fDist = Plane.Dot( Ray.vEnd );

		// 壁を反射後の位置
		Out.vRefrectPosition = Ray.vEnd - (Plane.n * (fDist * 2.0f));

		// 壁ぞいの停止位置
		Out.vSlidePosition = Ray.vEnd - (Plane.n * fDist);

		// 反射方向
		Out.vRefrectDirection = Out.vRefrectPosition - Out.vHitPosition;
		Out.vRefrectDirection.NormalizeFast();

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCollision::HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, SCollisionResultSphereExtend &Out, Collision::CBox &Box )
{
	Float fLengthSq = FLT_MAX;
	Math::Vector3D vIntersectPosition;
	Sint32 IntersectID = -1;

	// OBBと判定
//	if ( Collision::Line_Box_3D( Ray, m_Box ) )
	{
		const Math::Vector3D *pRay[] = {
			&Ray.vStart, 
			&Ray.vEnd,
		};

		// 各平面に対するチェック
		Sint32 Max = m_FaceMax;
		for ( Sint32 i = 0; i < Max; i++ )
		{
			Collision::CPlane Plane = m_pFaceTbl[i].Plane;

			Math::Vector3D Pos[] = {
				m_pVertexTbl[m_pFaceTbl[i].Index[0]].Position + (Plane.n * fRadius),
				m_pVertexTbl[m_pFaceTbl[i].Index[1]].Position + (Plane.n * fRadius),
				m_pVertexTbl[m_pFaceTbl[i].Index[2]].Position + (Plane.n * fRadius),
			};

			Plane.d = -Pos[0].Dot( Plane.n );

			const Math::Vector3D *pPt[] = {
				&Pos[0], &Pos[1], &Pos[2],
			};

			// 面に対して交差しているか
			Math::Vector3D vHit;
			if ( Collision::Line_Triangle( pRay, Plane, pPt, vHit ) )
			{
				Float fLen = (vHit - Ray.vStart).LengthSq();
				if ( fLengthSq > fLen )
				{
					vIntersectPosition = vHit;
					IntersectID = i;
					fLengthSq = fLen;
				}
			}
		}
	}

	// 衝突してる？
	if ( IntersectID != -1 )
	{
		SCollisionFace &Col = m_pFaceTbl[IntersectID];
		Collision::CPlane Plane = Col.Plane;
		Math::Vector3D Pos[] = {
			m_pVertexTbl[Col.Index[0]].Position + (Plane.n * fRadius),
			m_pVertexTbl[Col.Index[1]].Position + (Plane.n * fRadius),
			m_pVertexTbl[Col.Index[2]].Position + (Plane.n * fRadius),
		};
		Plane.d = -Pos[0].Dot( Plane.n );

		Out.vNormal			= Plane.n;
		Out.vHitPosition	= vIntersectPosition;

		// 壁からの距離
		Float fDist = Plane.Dot( Ray.vEnd );

		// 壁を反射後の位置
		Out.vRefrectPosition = Ray.vEnd - (Plane.n * (fDist * 2.0f));

		// 壁ぞいの停止位置
		Out.vSlidePosition = Ray.vEnd - (Plane.n * fDist);

		// 反射方向
		Out.vRefrectDirection = Out.vRefrectPosition - Out.vHitPosition;
		Out.vRefrectDirection.NormalizeFast();

		Box = m_Box;

		return true;
	}

	return false;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCollision::Ray_Sphere( const CRay &Ray, const Collision::CSphere &Sphere, Math::Vector3D &vHitPosition, Math::Vector3D &vHitNormal )
{
	// 球への方向
	Math::Vector3D vToSphere = Sphere.vCenter - Ray.vStart;

	// レイの球に対する最近点
	Float fLengthNear = Ray.vDirection.Dot( vToSphere );
	if ( fLengthNear <= 0.0f )
	{
		return false;
	}

	Math::Vector3D vNear = Ray.vDirection * fLengthNear;

	// 最近点と球の距離
	Float fDistance2 = (Sphere.vCenter - vNear).LengthSq();
	Float fRadius2 = Sphere.fRadius * Sphere.fRadius;
	if ( fDistance2 > fRadius2 )
	{
		return false;
	}

	// 衝突点までの距離
	Float fLength = fLengthNear - FastSqrt( fRadius2 - fDistance2 );
	if ( fLength > Ray.fLength )
	{
		return false;
	}

	// 衝突点を求める
	vHitPosition = Ray.vStart + (Ray.vDirection * fLength);
	vHitNormal.NormalizeFast( vHitPosition - Sphere.vCenter );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CCollision::Ray_Cylinder( const CRay &Ray, const CCylinder &Cylinder, Math::Vector3D &vHitPosition, Math::Vector3D &vHitNormal )
{
	Math::Vector3D d = Cylinder.Pt1 - Cylinder.Pt0;
	Math::Vector3D m = Ray.vStart - Cylinder.Pt0;
	Math::Vector3D n = Ray.vDirection * Ray.fLength;

	Float md = m.Dot( d );
	Float nd = n.Dot( d );
	Float dd = d.Dot( d );

	// 円柱のどちらかの底面の外側にあるかチェック
	if ( (md < 0.0f) && (md + nd < 0.0f) )
	{
		return false;
	}
	if ( (md >   dd) && (md + nd >   dd) )
	{
		return false;
	}

	Float nn = n.Dot( n );
	Float a = (dd * nn) - (nd * nd);
	Float k = m.LengthSq() - (Cylinder.fRadius * Cylinder.fRadius);

	// 軸に平行？
	if ( Abs( a ) < 0.00001f )
	{
		return false;
	}

	Float mn = m.Dot( n );
	Float b = (dd * mn) - (nd * md);
	Float c = (dd * k) - (md * md);

	// 判別式
	Float ret = (b * b) - (a * c);
	if ( ret <= 0.0f )
	{
		return false;
	}

	// 衝突点
	Float t = (-b - FastSqrt( ret )) / a;
	if ( (t < 0.0f) || (t > 1.0f) )
	{
		return false;
	}

	vHitPosition = Ray.vStart + (Ray.vDirection * (Ray.fLength * t));

	Math::Vector3D vTemp;
	vTemp.Cross( Cylinder.Pt0 - vHitPosition, Cylinder.Pt1 - Cylinder.Pt0 );
	vHitNormal.Cross( vTemp, Cylinder.Pt1 - Cylinder.Pt0 );
	vHitNormal.NormalizeFast();

	return true;
}
