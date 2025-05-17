

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Collision/Collision.h"
#include "Math/Vector2D.h"
#include "Math/Vector3D.h"
#include "Math/Matrix.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Collision;


//-----------------------------------------------------------------------------------
// CONST
//-----------------------------------------------------------------------------------
static const Float NEAR_FLOAT		= 0.00001f;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
	Float Side( const Math::Vector2D &Pos, const CLine2D &Line );
	Bool IsPointInTriangle( const CPlane &Plane, const Math::Vector3D *pPlanePoints[], const Math::Vector3D &vIntersect );
	Bool IsPointInQuad( const CPlane &Plane, const Math::Vector3D *pPlanePoints[], const Math::Vector3D &vIntersect );
	Bool Line_Quad( const Math::Vector3D *pPtTbl[], const CPlane &Plane, const Math::Vector3D *pPlanePoints[], Math::Vector3D &vIntersect, Math::Vector3D &vNormal );
	Bool Line_Triangle( const Math::Vector3D *pPtTbl[], const CPlane &Plane, const Math::Vector3D *pPlanePoints[], Math::Vector3D &vIntersect );
	Bool Line_Triangle_3D( const CLine3D &Line, const Math::Vector3D Points[], Float &fDist, Float &fBary1, Float &fBary2 );
}
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Point( const Math::Vector2D &Pt1, const Math::Vector2D &Pt2 )
{
	CCircle Cir1( Pt1.x, Pt1.y, 1.0f );
	CCircle Cir2( Pt2.x, Pt2.y, 1.0f );

	return Circle_Circle( Cir1, Cir2 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Line( const Math::Vector2D &Pt, const CLine2D &Line )
{
	CCircle Cir( Pt.x, Pt.y, 1.0f );

	return Circle_Line( Cir, Line );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Rect( const Math::Vector2D &Pt, const Math::Rect2D<Float> &Rect )
{
	Float x0 = Rect.x;
	Float y0 = Rect.y;
	Float x1 = Rect.x + Rect.w;
	Float y1 = Rect.y + Rect.h;

	if ( Pt.x < x0 ) return false;
	if ( Pt.y < y0 ) return false;
	if ( Pt.x > x1 ) return false;
	if ( Pt.y > y1 ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Circle( const Math::Vector2D &Pt, const CCircle &Cir )
{
	Float rx = Pt.x - Cir.vCenter.x;
	Float ry = Pt.y - Cir.vCenter.y;
	Float r = Cir.fRadius;

	return ((rx * rx) + (ry * ry)) <= (r * r);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Polygon( const Math::Vector2D &Pt, const CPolygon2D &Poly )
{
	Math::Vector2D v1, v2;

	Sint32 Count = 0;
	Sint32 Max = Poly.Count - 1;

	for ( Sint32 i = 0; i < Max; i++ )
	{
		v1.Set( Pt.x - Poly.pPts[i+0].x, Pt.y - Poly.pPts[i+0].y );
		v2.Set( Pt.x - Poly.pPts[i+1].x, Pt.y - Poly.pPts[i+1].y );

		if ( v1.Cross( v2 ) < 0.0f )
		{
			Count++;
		}
	}

	return (Count == 0) || (Count == Max);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Rect_Rect( const Math::Rect2D<Float> &Rect1, const Math::Rect2D<Float> &Rect2 )
{
	Float x00 = Rect1.x;
	Float y00 = Rect1.y;
	Float x01 = Rect1.x + Rect1.w;
	Float y01 = Rect1.y + Rect1.h;

	Float x10 = Rect2.x;
	Float y10 = Rect2.y;
	Float x11 = Rect2.x + Rect2.w;
	Float y11 = Rect2.y + Rect2.h;

	if ( x00 > x01 ) SWAP( x00, x01 );
	if ( y00 > y01 ) SWAP( y00, y01 );
	if ( x10 > x11 ) SWAP( x10, x11 );
	if ( y10 > y11 ) SWAP( y10, y11 );

	if ( x00 > x11 ) return false;
	if ( x01 < x10 ) return false;
	if ( y00 > y11 ) return false;
	if ( y01 < y10 ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Rect_Circle( const Math::Rect2D<Float> &Rect, const CCircle &Cir )
{
	Float x0 = Rect.x;
	Float y0 = Rect.y;
	Float x1 = Rect.x + Rect.w;
	Float y1 = Rect.y + Rect.h;

	if ( Cir.vCenter.x + Cir.fRadius < x0 ) return false;
	if ( Cir.vCenter.x - Cir.fRadius > x1 ) return false;
	if ( Cir.vCenter.y + Cir.fRadius < y0 ) return false;
	if ( Cir.vCenter.y - Cir.fRadius > y1 ) return false;

	Math::Vector2D Pts[5] = {
		Math::Vector2D( x0, y0 ),
		Math::Vector2D( x1, y0 ),
		Math::Vector2D( x1, y1 ),
		Math::Vector2D( x0, y1 ),
		Math::Vector2D( x0, y0 ),
	};

	CPolygon2D Poly( 5, Pts );

	return Circle_Polygon( Cir, Poly );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Rect_Line( const Math::Rect2D<Float> &Rect, const CLine2D &Line )
{
	if ( Point_Rect( Line.vStart, Rect ) ) return true;
	if ( Point_Rect( Line.vEnd, Rect ) ) return true;

	Float x0 = Rect.x;
	Float y0 = Rect.y;
	Float x1 = Rect.x + Rect.w;
	Float y1 = Rect.y + Rect.h;

	CLine2D Lines[4] = {
		CLine2D( x0, y0, x1, y0 ),
		CLine2D( x1, y0, x1, y1 ),
		CLine2D( x1, y1, x0, y1 ),
		CLine2D( x0, y1, x0, y0 ),
	};

	for ( Sint32 i = 0; i < 4; i++ )
	{
		if ( Line_Line( Lines[i], Line ) )
		{
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Rect_Polygon( const Math::Rect2D<Float> &Rect, const CPolygon2D &Poly )
{
	Sint32 Count = Poly.Count - 1;
	for ( Sint32 i = 0; i < Count; i++ )
	{
		if ( Point_Rect( Poly.pPts[i], Rect ) )
		{
			return true;
		}
	}

	Float x0 = Rect.x;
	Float y0 = Rect.y;
	Float x1 = Rect.x + Rect.w;
	Float y1 = Rect.y + Rect.h;

	Math::Vector2D Pts[5] = {
		Math::Vector2D( x0, y0 ),
		Math::Vector2D( x1, y0 ),
		Math::Vector2D( x1, y1 ),
		Math::Vector2D( x0, y1 ),
		Math::Vector2D( x0, y0 ),
	};

	CPolygon2D PolyTemp( 5, Pts );

	return Polygon_Polygon( Poly, PolyTemp );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Circle_Circle( const CCircle &Cir1, const CCircle &Cir2 )
{
	Float rx = Cir1.vCenter.x - Cir2.vCenter.x;
	Float ry = Cir1.vCenter.y - Cir2.vCenter.y;
	Float r  = Cir1.fRadius   + Cir2.fRadius;

	return (rx * rx) + (ry * ry) < (r * r);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Circle_Line( const CCircle &Cir, const CLine2D &Line )
{
	//====================================================
	// まずは直線分の両端が円に含まれればＯＫ
	//====================================================
	if ( Point_Circle( Line.vStart, Cir ) ) return true;
	if ( Point_Circle( Line.vEnd, Cir ) ) return true;

	//====================================================
	// 円の中点と直直線までの距離を求める.
	//====================================================

	// 点から直直線に垂直な単位ベクトル(t1)を求める
	Math::Vector2D s1, s2, s3, t1, t2, v;
	Float z;

	// ベクトル la - lb
	s1 = Line.vEnd - Line.vStart;

	// ベクトル la - cir
	s2 = Cir.vCenter - Line.vStart;

	// ベクトル s1 と s2 の外積
	// ２次元空間なのでＺ軸に平行なベクトル
	z = s1.Cross( s2 );

	// 円の中心が直線上に存在するとき（外積が０になる
	if ( z <= NEAR_FLOAT )
	{
		v.x = Cir.vCenter.x;
		v.y = Cir.vCenter.y;
	}
	else
	{
		// ベクトル s1 と s3 の外積
		// このベクトルが la - lb の垂直線になる
		s3.x = +(s1.y * z);
		s3.y = -(s1.x * z);

		// 垂直線ベクトルの正規化
		t1.NormalizeFast( s3 );

		// 内積から距離を算出
		t2.x = Line.vStart.x - Cir.vCenter.x;
		t2.y = Line.vStart.y - Cir.vCenter.y;
		Float fLen = t1.Dot( t2 );

		// 交点と円の中心の距離が半径以上ならＮＧ
		if ( fLen > Cir.fRadius ) return false;

		// 円の中心から la - lb に引いた垂直線の足の座標を求める
		v = Cir.vCenter + (t1 * fLen);
	}

	// v が Line.vStart - Line.vEnd の間にあればＯＫ
	if ( (Line.vStart.x < v.x) && (v.x < Line.vEnd.x)   ) return true;
	if ( (Line.vEnd.x   < v.x) && (v.x < Line.vStart.x) ) return true;
	if ( (Line.vStart.y < v.y) && (v.y < Line.vEnd.y)   ) return true;
	if ( (Line.vEnd.y   < v.y) && (v.y < Line.vStart.y) ) return true;

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Circle_Polygon( const CCircle &Cir, const CPolygon2D &Poly )
{
	Sint32 Count = Poly.Count - 1;

	// 円の中心が多角形に含まれているならＯＫ
	if ( Point_Polygon( Cir.vCenter, Poly ) )
	{
		return true;
	}

	// 多角形の各辺と円の交差判定
	for ( Sint32 i = 0; i < Count; i++ )
	{
		CLine2D Line( Poly.pPts[i+0], Poly.pPts[i+1] );
		if ( Circle_Line( Cir, Line ) )
		{
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Line_Line( const CLine2D &Line1, const CLine2D &Line2 )
{
	Math::Rect2D<Float> Rc1, Rc2;
	Float fRet1, fRet2;
	Float n1, n2;

	//-------------------------------------------
	// 先にバウンディングで判定
	//-------------------------------------------
	Rc1.Set( Line1.vStart.x, Line1.vStart.y, Line1.vEnd.x - Line1.vStart.x, Line1.vEnd.y - Line1.vStart.y );
	Rc2.Set( Line2.vStart.x, Line2.vStart.y, Line2.vEnd.x - Line2.vStart.x, Line2.vEnd.y - Line2.vStart.y );
	if ( !Rect_Rect( Rc1, Rc2 ) ) return false;

	//-------------------------------------------
	// l1 が l2 をまたいでいるか否か
	//-------------------------------------------
	n1 = Side( Line2.vStart, Line1 );
	n2 = Side( Line2.vEnd, Line1 );
	fRet1 = (n1 * n2);

	//-------------------------------------------
	// l2 が l1 をまたいでいるか否か
	//-------------------------------------------
	n1 = Side( Line1.vStart, Line2 );
	n2 = Side( Line1.vEnd, Line2 );
	fRet2 = (n1 * n2);

	return (fRet1 <= 0.0f) && (fRet2 <= 0.0f);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Line_Polygon( const CLine2D &Line, const CPolygon2D &Poly )
{
	CLine2D LinePt;
	Sint32 Count;

	// 直線分の各端が多角形に含まれているかチェック
	if ( Point_Polygon( Line.vStart, Poly ) ) return true;
	if ( Point_Polygon( Line.vEnd, Poly ) ) return true;

	// 多角形の各辺と直線分の交差判定
	Count = Poly.Count;
	for ( Sint32 i = 0; i < Count - 1; i++ )
	{
		LinePt.vStart = Poly.pPts[i+0];
		LinePt.vEnd = Poly.pPts[i+1];
		if ( Line_Line( Line, LinePt ) )
		{
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Polygon_Polygon( const CPolygon2D &Poly1, const CPolygon2D &Poly2 )
{
	Sint32 Count1 = Poly1.Count - 1;
	Sint32 Count2 = Poly2.Count - 1;

	//----------------------------------------------------------
	// バウンディングボックス算出
	//----------------------------------------------------------
	Float x11 = Poly1.pPts[0].x,  x12 = Poly1.pPts[0].x;
	Float y11 = Poly1.pPts[0].y,  y12 = Poly1.pPts[0].y;
	Float x21 = Poly2.pPts[0].x,  x22 = Poly2.pPts[0].x;
	Float y21 = Poly2.pPts[0].y,  y22 = Poly2.pPts[0].y;

	for ( Sint32 i = 1; i < Count1; i++ )
	{
		if ( Poly1.pPts[i].x < x11 ) x11 = Poly1.pPts[i].x;
		ef ( Poly1.pPts[i].x > x12 ) x12 = Poly1.pPts[i].x;
		if ( Poly1.pPts[i].y < y11 ) y11 = Poly1.pPts[i].y;
		ef ( Poly1.pPts[i].y > y12 ) y12 = Poly1.pPts[i].y;
	}
	for ( Sint32 i = 1; i < Count2; i++ )
	{
		if ( Poly2.pPts[i].x < x21 ) x21 = Poly2.pPts[i].x;
		ef ( Poly2.pPts[i].x > x22 ) x22 = Poly2.pPts[i].x;
		if ( Poly2.pPts[i].y < y21 ) y21 = Poly2.pPts[i].y;
		ef ( Poly2.pPts[i].y > y22 ) y22 = Poly2.pPts[i].y;
	}

	//----------------------------------------------------------
	// バウンディングボックスの接触判定
	//----------------------------------------------------------
	if ( x11 > x22 ) return false;
	if ( x12 < x21 ) return false;
	if ( y11 > y22 ) return false;
	if ( y12 < y21 ) return false;

	//----------------------------------------------------------
	// p1の各頂点がp2の矩形内に入っているか
	//----------------------------------------------------------
	for ( Sint32 i = 0; i < Count1; i++ )
	{
		if ( Point_Polygon( Poly1.pPts[i], Poly2 ) )
		{
			return true;
		}
	}

	//----------------------------------------------------------
	// p2の各頂点がp1の矩形内に入っているか
	//----------------------------------------------------------
	for ( Sint32 i = 0; i < Count2; i++ )
	{
		if ( Point_Polygon( Poly2.pPts[i], Poly1 ) )
		{
			return true;
		}
	}

	//----------------------------------------------------------
	// 各頂点が作る線分の交差判定
	//----------------------------------------------------------
	CLine2D Line1, Line2;
	for ( Sint32 i = 0; i < Count1; i++ )
	{
		for ( Sint32 j = 0; j < Count2; j++ )
		{
			Line1.vStart = Poly1.pPts[i+0];
			Line1.vEnd = Poly1.pPts[i+1];
			Line2.vStart = Poly2.pPts[j+0];
			Line2.vEnd = Poly2.pPts[j+1];

			if ( Line_Line( Line1, Line2 ) )
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
Bool Selene::Collision::Point_Point_3D( const Math::Vector3D &Pt1, const Math::Vector3D &Pt2 )
{
	if ( Pt1.x != Pt2.x ) return false;
	if ( Pt1.y != Pt2.y ) return false;
	if ( Pt1.z != Pt2.z ) return false;

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Sphere_3D( const Math::Vector3D &Pt, const CSphere &Sph )
{
	CSphere SphPt( Pt, 0.0f );

	return Sphere_Sphere_3D( Sph, SphPt );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Line_3D( const Math::Vector3D &Pt, const CLine3D &Line )
{
	CSphere SphPt( Pt, 1.0f );

	return Sphere_Line_3D( SphPt, Line );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Plane_3D( const Math::Vector3D &Pt, const CPlane &Plane )
{
	Float fDist = Plane.Dot( Pt );
	return (-NEAR_FLOAT <= fDist) && (fDist <= +NEAR_FLOAT);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Point_Box_3D( const Math::Vector3D &Pt, const CBox &Box )
{
	// ポイントが6つのビューフラスタム平面すべての
	// 内部である場合ビューフラスタム内にあります
	for ( Sint32 i = 0; i < 6; i++ )
	{
		if ( Box.Planes[i].Dot( Pt ) > 0 )
		{
			return false;
		}
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Sphere_Sphere_3D( const CSphere &Sph1, const CSphere &Sph2 )
{
	Float rx = Sph1.vCenter.x - Sph2.vCenter.x;
	Float ry = Sph1.vCenter.y - Sph2.vCenter.y;
	Float rz = Sph1.vCenter.z - Sph2.vCenter.z;
	Float r  = Sph1.fRadius   + Sph2.fRadius;

	return (rx * rx) + (ry * ry) + (rz * rz) < (r * r);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Sphere_Line_3D( const CSphere &Sph, const CLine3D &Line )
{
	//====================================================
	// まずは直線分の両端が球に含まれているかチェック
	//====================================================
	if ( Point_Sphere_3D( Line.vStart, Sph ) ) return true;
	if ( Point_Sphere_3D( Line.vEnd, Sph ) ) return true;

	//====================================================
	// 球の中点と直線までの距離を求める.
	//====================================================

	// 点から直線に垂直な単位ベクトル(t1)を求める。
	Math::Vector3D s1, s2, s3, s4, t1, t2, v;

	// ベクトル la - lb
	s1 = Line.vEnd - Line.vStart;

	// ベクトル la - cir
	s2 = Sph.vCenter - Line.vStart;

	// s1, s2 の外積 s3
	s3.Cross( s1, s2 );
	if ( s3.LengthSq() <= NEAR_FLOAT )
	{
		v = Sph.vCenter;
	}
	else
	{
		// s1, s3 の外積 s4 = 垂直線
		s4.Cross( s1, s3 );

		// 正規化
		t1.NormalizeFast( s4 );

		// 内積から距離を算出
		t2 = Line.vStart - Sph.vCenter;
		Float fLen = t1.Dot( t2 );

		// 交点と円の中心の距離が半径以上ならＮＧ
		if ( fLen > Sph.fRadius ) return false;

		// 球の中心(cir)から直線(Line.a, Line.b)に引いた垂直線の足の座標(v)
		v = Sph.vCenter + (t1 * fLen);
	}

	// vがLine.aとLine.bの間にあればＯＫ
	if ( (Line.vStart.x < v.x) && (v.x < Line.vEnd.x)   ) return true;
	if ( (Line.vEnd.x   < v.x) && (v.x < Line.vStart.x) ) return true;
	if ( (Line.vStart.y < v.y) && (v.y < Line.vEnd.y)   ) return true;
	if ( (Line.vEnd.y   < v.y) && (v.y < Line.vStart.y) ) return true;
	if ( (Line.vStart.z < v.z) && (v.z < Line.vEnd.z)   ) return true;
	if ( (Line.vEnd.z   < v.z) && (v.z < Line.vStart.z) ) return true;

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Sphere_Plane( const CSphere &Sph, const CPlane &Plane )
{
	return Plane.Dot( Sph.vCenter ) <= Sph.fRadius;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Line_Plane_3D( const CLine3D &Line, const CPlane &Plane, Math::Vector3D &vIntersect )
{
	// 始点から面への距離
	Float fDistP = Plane.Dot( Line.vStart );
	if ( fDistP < 0.0f )
	{
		// 面の裏なら×
		return false;
	}

	// 終点から面への距離
	Float fDistQ = Plane.Dot( Line.vEnd );
	if ( fDistQ > 0.0f )
	{
		// 面の表なら×
		return false;
	}

	// 交点を求める
	Math::Vector3D vDir = Line.vEnd - Line.vStart;
	Float fT = fDistP / (fDistP - fDistQ);
	vIntersect = Line.vStart + (vDir * fT);

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Line_Box_3D( const CLine3D &Line, const CBox &Box )
{
	// 箱の中に点が入っているかチェック
	if ( Point_Box_3D( Line.vStart, Box ) )
	{
		return true;
	}

	// 箱の中に点が入っているかチェック
	if ( Point_Box_3D( Line.vEnd, Box ) )
	{
		return true;
	}

	// 箱の面と線分が交差しているかチェック
	const Math::Vector3D *pEdge[2] = {
		&Line.vStart,
		&Line.vEnd
	};

	const Math::Vector3D *pPlanePoint[6][4] = {
		{ &Box.Points[3], &Box.Points[2], &Box.Points[1], &Box.Points[0] }, // 左
		{ &Box.Points[4], &Box.Points[5], &Box.Points[6], &Box.Points[7] }, // 右
		{ &Box.Points[1], &Box.Points[2], &Box.Points[6], &Box.Points[5] }, // 上
		{ &Box.Points[3], &Box.Points[0], &Box.Points[4], &Box.Points[7] }, // 下
		{ &Box.Points[0], &Box.Points[1], &Box.Points[5], &Box.Points[4] }, // 前
		{ &Box.Points[2], &Box.Points[3], &Box.Points[7], &Box.Points[6] }, // 後
	};

	Math::Vector3D vIntersect, vNormal;
	for ( Sint32 i = 0; i < 6; i++ )
	{
		if ( Line_Quad( pEdge, Box.Planes[i], pPlanePoint[i], vIntersect, vNormal ) )
		{
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Line_Triangle_3D( const CLine3D &Line, const Math::Vector3D Points[], Float &fDist, Float &fBary1, Float &fBary2 )
{
    Math::Vector3D VecP, VecT, VecQ;

	Math::Vector3D vDir = Line.vEnd - Line.vStart;
	Math::Vector3D vEdge1 = Points[1] - Points[0];
	Math::Vector3D vEdge2 = Points[2] - Points[0];

    VecP.Cross( vDir, vEdge2 );

    Float fDet = vEdge1.Dot( VecP );
    if ( fDet > 0.0f )
    {
        VecT = Line.vStart - Points[0];
    }
    else
    {
        VecT = Points[0] - Line.vStart;
        fDet = -fDet;
    }

    if ( fDet < NEAR_FLOAT )
	{
		return false;
	}

    fBary1 = VecT.Dot( VecP );
    if ( (fBary1 < 0.0f) || (fBary1 > fDet) )
	{
        return false;
	}

    VecQ.Cross( VecT, vEdge1 );

    fBary2 = vDir.Dot( VecQ );
    if ( (fBary2 < 0.0f) || (fBary1 + fBary2 > fDet) )
	{
        return false;
	}

    fDist = vEdge2.Dot( VecQ );

	Float fInvDet = 1.0f / fDet;
    fDist  *= fInvDet;
    fBary1 *= fInvDet;
    fBary2 *= fInvDet;

    return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Box_Box_3D( const CBox &Box0, const CBox &Box1 )
{
	//-------------------------------------------------------------------
	// AABBでカカッとチェック
	//-------------------------------------------------------------------
	if ( Box0.vMin.x > Box1.vMax.x ) return false;
	if ( Box0.vMin.y > Box1.vMax.y ) return false;
	if ( Box0.vMin.z > Box1.vMax.z ) return false;
	if ( Box0.vMax.x < Box1.vMin.x ) return false;
	if ( Box0.vMax.y < Box1.vMin.y ) return false;
	if ( Box0.vMax.z < Box1.vMin.z ) return false;

	//-------------------------------------------------------------------
	// OBBでまじめにチェック
	//-------------------------------------------------------------------
	Math::Vector3D vIntersect, vNormal;
	Uint8 bOutside[8];

	//-------------------------------------------------------------------
	// ビューフラスタムの端のエッジのどれかが
	// バウンディングボックスの面のうちのどれかに接触するか
	// 互いの箱の中に互いの点が入っているかチェック
	//-------------------------------------------------------------------
	for ( Sint32 i = 0; i < 8; i++ )
	{
		bOutside[i] = 0x00;
		for ( Sint32 j = 0; j < 6; j++ )
		{
			if ( Box0.Planes[j].Dot( Box1.Points[i] ) > 0.0f )
			{
				bOutside[i] |= (1 << j);
			}
		}

		// ポイントが6つのビューフラスタム平面すべての内部である場合
		// ビューフラスタム内にあります
		if ( bOutside[i] == 0 ) return true;
	}

	// ポイントがすべて任意の単一のビューフラスタム平面の外部にある場合
	// オブジェクトはビューフラスタム外にあります。
	if ( (bOutside[0] & bOutside[1] & bOutside[2] & bOutside[3] & bOutside[4] & bOutside[5] & bOutside[6] & bOutside[7]) != 0x00 )
	{
		return false;
	}

	//-------------------------------------------------------------------
	// ビューフラスタムの端のエッジのどれかが
	// バウンディングボックスの面のうちのどれかに接触するか
	// 互いの箱の中に互いの点が入っているかチェック
	//-------------------------------------------------------------------
	for ( Sint32 i = 0; i < 8; i++ )
	{
		bOutside[i] = 0x00;
		for ( Sint32 j = 0; j < 6; j++ )
		{
			if ( Box1.Planes[j].Dot( Box0.Points[i] ) > 0.0f )
			{
				bOutside[i] |= (1 << j);
			}
		}

		// ポイントが6つのビューフラスタム平面すべての内部である場合
		// ビューフラスタム内にあります
		if ( bOutside[i] == 0 ) return true;
	}

	// ポイントがすべて任意の単一のビューフラスタム平面の外部にある場合
	// オブジェクトはビューフラスタム外にあります。
	if ( (bOutside[0] & bOutside[1] & bOutside[2] & bOutside[3] & bOutside[4] & bOutside[5] & bOutside[6] & bOutside[7]) != 0x00 )
	{
		return false;
	}

	//------------------------------------------------------------------------------
	// OBB-AのエッジのどれかがOBB=Bの面のうちのどれかに接触するか
	//------------------------------------------------------------------------------
	{
		const Math::Vector3D *pEdge[12][2] = {
			{ &Box1.Points[0], &Box1.Points[1] },
			{ &Box1.Points[1], &Box1.Points[2] },
			{ &Box1.Points[2], &Box1.Points[3] },
			{ &Box1.Points[3], &Box1.Points[0] },
			{ &Box1.Points[4], &Box1.Points[5] },
			{ &Box1.Points[5], &Box1.Points[6] },
			{ &Box1.Points[6], &Box1.Points[7] },
			{ &Box1.Points[7], &Box1.Points[4] },
			{ &Box1.Points[0], &Box1.Points[4] },
			{ &Box1.Points[1], &Box1.Points[5] },
			{ &Box1.Points[2], &Box1.Points[6] },
			{ &Box1.Points[3], &Box1.Points[7] },
		};
		const Math::Vector3D *pPlanePoint[6][4] = {
			{ &Box0.Points[3], &Box0.Points[2], &Box0.Points[1], &Box0.Points[0] }, // 左
			{ &Box0.Points[4], &Box0.Points[5], &Box0.Points[6], &Box0.Points[7] }, // 右
			{ &Box0.Points[1], &Box0.Points[2], &Box0.Points[6], &Box0.Points[5] }, // 上
			{ &Box0.Points[3], &Box0.Points[0], &Box0.Points[4], &Box0.Points[7] }, // 下
			{ &Box0.Points[0], &Box0.Points[1], &Box0.Points[5], &Box0.Points[4] }, // 前
			{ &Box0.Points[2], &Box0.Points[3], &Box0.Points[7], &Box0.Points[6] }, // 後
		};

		for ( Sint32 i = 0; i < 12; i++ )
		{
			for ( Sint32 j = 0; j < 6; j++ )
			{
				if ( Line_Quad( pEdge[i], Box0.Planes[j], pPlanePoint[j], vIntersect, vNormal ) )
				{
					return true;
				}
			}
		}
	}

	//------------------------------------------------------------------------------
	// OBB-BのエッジのどれかがOBB-Aの面のうちのどれかに接触するか
	//------------------------------------------------------------------------------
	{
		const Math::Vector3D *pEdge[12][2] = {
			{ &Box0.Points[0], &Box0.Points[1] },
			{ &Box0.Points[1], &Box0.Points[2] },
			{ &Box0.Points[2], &Box0.Points[3] },
			{ &Box0.Points[3], &Box0.Points[0] },
			{ &Box0.Points[4], &Box0.Points[5] },
			{ &Box0.Points[5], &Box0.Points[6] },
			{ &Box0.Points[6], &Box0.Points[7] },
			{ &Box0.Points[7], &Box0.Points[4] },
			{ &Box0.Points[0], &Box0.Points[4] },
			{ &Box0.Points[1], &Box0.Points[5] },
			{ &Box0.Points[2], &Box0.Points[6] },
			{ &Box0.Points[3], &Box0.Points[7] },
		};
		const Math::Vector3D *pPlanePoint[6][4] = {
			{ &Box1.Points[3], &Box1.Points[2], &Box1.Points[1], &Box1.Points[0] }, // 左
			{ &Box1.Points[4], &Box1.Points[5], &Box1.Points[6], &Box1.Points[7] }, // 右
			{ &Box1.Points[1], &Box1.Points[2], &Box1.Points[6], &Box1.Points[5] }, // 上
			{ &Box1.Points[3], &Box1.Points[0], &Box1.Points[4], &Box1.Points[7] }, // 下
			{ &Box1.Points[0], &Box1.Points[1], &Box1.Points[5], &Box1.Points[4] }, // 前
			{ &Box1.Points[2], &Box1.Points[3], &Box1.Points[7], &Box1.Points[6] }, // 後
		};

		for ( Sint32 i = 0; i < 12; i++ )
		{
			for ( Sint32 j = 0; j < 6; j++ )
			{
				if ( Line_Quad( pEdge[i], Box1.Planes[j], pPlanePoint[j], vIntersect, vNormal ) )
				{
					return true;
				}
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::IsPointInTriangle( const CPlane &Plane, const Math::Vector3D *pPlanePoints[], const Math::Vector3D &vIntersect )
{
	const Uint8 Tbl[][2] = { { 0, 1 }, { 1, 2 }, { 2, 0 } };

	Math::Vector3D Cross, v1, v2;
	for ( Sint32 i = 0; i < 3; i++ )
	{
		// 交点を使った場合の法線
		v1 = vIntersect - *pPlanePoints[Tbl[i][0]];
		v2 = vIntersect - *pPlanePoints[Tbl[i][1]];
		Cross.Cross( v2, v1 );

		// 方向チェック
		// 同じ方向のベクトル同士の内積は＋になる
		if ( Cross.Dot( Plane.n ) > 0.0f )
		{
			return false;
		}
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::IsPointInQuad( const CPlane &Plane, const Math::Vector3D *pPlanePoints[], const Math::Vector3D &vIntersect )
{
	const Uint8 Tbl[][2] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 } };

	Math::Vector3D Cross, v1, v2;
	for ( Sint32 i = 0; i < 4; i++ )
	{
		// 交点を使った場合の法線
		v1 = vIntersect - *pPlanePoints[Tbl[i][0]];
		v2 = vIntersect - *pPlanePoints[Tbl[i][1]];
		Cross.Cross( v2, v1 );

		// 方向チェック
		// 同じ方向のベクトル同士の内積は＋になる
		if ( Cross.Dot( Plane.n ) > 0.0f )
		{
			return false;
		}
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Line_Quad( const Math::Vector3D *pPtTbl[], const CPlane &Plane, const Math::Vector3D *pPlanePoints[], Math::Vector3D &vIntersect, Math::Vector3D &vNormal )
{
	CLine3D Line( *pPtTbl[0], *pPtTbl[1] );
	Math::Vector3D vHitPos;

	//------------------------------------------------------
	// 直線および平面の間の交点を見つけます
	//------------------------------------------------------
	if ( !Line_Plane_3D( Line, Plane, vHitPos ) )
	{
		return false;
	}

	//------------------------------------------------------
	// 交点が四角形の中にあるかチェック
	//------------------------------------------------------
	if ( IsPointInQuad( Plane, pPlanePoints, vHitPos ) )
	{
		vIntersect = vHitPos;
		vNormal = Plane.n;
		return true;
	}

	return false;
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool Selene::Collision::Line_Triangle( const Math::Vector3D *pPtTbl[], const CPlane &Plane, const Math::Vector3D *pPlanePoints[], Math::Vector3D &vIntersect )
{
	CLine3D Line( *pPtTbl[0], *pPtTbl[1] );
	Math::Vector3D vHitPos;

	//------------------------------------------------------
	// 直線および平面の間の交点を見つけます
	//------------------------------------------------------
	if ( !Line_Plane_3D( Line, Plane, vHitPos ) )
	{
		return false;
	}

	//------------------------------------------------------
	// 交点が三角形の中にあるかチェック
	//------------------------------------------------------
	if ( IsPointInTriangle( Plane, pPlanePoints, vHitPos ) )
	{
		vIntersect = vHitPos;
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float Selene::Collision::Side( const Math::Vector2D &Pos, const CLine2D &Line )
{
	Math::Vector2D v1, v2;

	v1.Set( Pos.x - Line.vStart.x, Pos.y - Line.vStart.y );
	v2.Set( Pos.x - Line.vEnd.x, Pos.y - Line.vEnd.y );

	return v1.Cross( v2 );
}

