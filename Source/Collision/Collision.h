#pragma once


/**
	@file
	@brief 衝突判定
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Math.h"
#include "Collision/Plane.h"
#include "Collision/Sphere.h"
#include "Collision/Box.h"
#include "Collision/Line2D.h"
#include "Collision/Line3D.h"
#include "Collision/Polygon2D.h"
#include "Collision/Circle.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
/**
@brief 2D点と2D点の衝突判定
@author 葉迩倭
@param Pt1		[in] 2D平面上の点
@param Pt2		[in] 2D平面上の点
@retval false	衝突していない
@retval true	衝突している

@note
2D平面上の2つの点の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector2D Pt1, Pt2;
  // 衝突判定
  if ( Collision::Point_Point( Pt1, Pt2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Point( const Math::Vector2D &Pt1, const Math::Vector2D &Pt2 );
/**
@brief 2D点と2D線分の衝突判定
@author 葉迩倭
@param Pt		[in] 2D平面上の点
@param Line		[in] 2D平面上の線分
@retval false	衝突していない
@retval true	衝突している

@note
2D平面上の点と線分の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector2D Pt;
  Collision::CLine2D Line;
  // 衝突判定
  if ( Collision::Point_Line( Pt, Line ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Line( const Math::Vector2D &Pt, const CLine2D &Line );
/**
@brief 2D点と2D矩形の衝突判定
@author 葉迩倭
@param Pt		[in] 2D平面上の点
@param Rect		[in] 2D平面上の矩形
@retval false	衝突していない
@retval true	衝突している

@note
2D平面上の点と矩形の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector2D Pt;
  Math::Rect2D<Float> Rect;
  // 衝突判定
  if ( Collision::Point_Rect( Pt, Rect ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Rect( const Math::Vector2D &Pt, const Math::Rect2D<Float> &Rect );
/**
@brief 2D点と2D矩形の衝突判定
@author 葉迩倭
@param Pt		[in] 2D平面上の点
@param Cir		[in] 2D平面上の円
@retval false	衝突していない
@retval true	衝突している

@note
2D平面上の点と円の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector2D Pt;
  Collision::CCircle Cir;
  // 衝突判定
  if ( Collision::Point_Circle( Pt, Cir ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Circle( const Math::Vector2D &Pt, const CCircle &Cir );
/**
@brief 2D点と2D多角形の衝突判定
@author 葉迩倭
@param Pt		[in] 2D平面上の点
@param Poly		[in] 2D平面上の多角形
@retval false	衝突していない
@retval true	衝突している

@note
2D平面上の点と多角形の衝突判定を行います。<BR>
CPolygon2Dに関しては、時計回り、あるいは反時計回りの<BR>
凸形状をしている必要があります。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector2D Pt;
  Collision::CPolygon2D Poly;
  // 衝突判定
  if ( Collision::Point_Polygon( Pt, Poly ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Polygon( const Math::Vector2D &Pt, const CPolygon2D &Poly );
/**
@brief 2D矩形と2D矩形の衝突判定
@author 葉迩倭
@param Rect1		[in] 2D平面上の矩形
@param Rect2		[in] 2D平面上の矩形
@retval false	衝突していない
@retval true	衝突している

@note
2D平面上の矩形同士の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Rect2D<Float> Rect1, Rect2;
  // 衝突判定
  if ( Collision::Rect_Rect( Rect1, Rect2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Rect_Rect( const Math::Rect2D<Float> &Rect1, const Math::Rect2D<Float> &Rect2 );
/**
@brief 2D矩形と2D円の衝突判定
@author 葉迩倭
@param Rect		[in] 2D平面上の矩形
@param Cir		[in] 2D平面上の円
@retval false	衝突していない
@retval true	衝突している

@note
2D平面上の矩形と円の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Rect2D<Float> Rect;
  Collision::CCircle Cir;
  // 衝突判定
  if ( Collision::Rect_Circle( Rect, Cir ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Rect_Circle( const Math::Rect2D<Float> &Rect, const CCircle &Cir );
/**
@brief 2D矩形と2D線分の衝突判定
@author 葉迩倭
@param Rect		[in] 2D平面上の矩形
@param Line		[in] 2D平面上の線分
@retval false	衝突していない
@retval true	衝突している

@note
2D平面上の矩形と線分の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Rect2D<Float> Rect;
  Collision::CLine2D Line;
  // 衝突判定
  if ( Collision::Rect_Line( Rect, Line ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Rect_Line( const Math::Rect2D<Float> &Rect, const CLine2D &Line );
/**
@brief 2D矩形と2D多角形の衝突判定
@author 葉迩倭
@param Rect		[in] 2D平面上の矩形
@param Poly		[in] 2D平面上の多角形
@retval false	衝突していない
@retval true	衝突している

@note
2D平面上の矩形と多角形の衝突判定を行います。<BR>
CPolygon2Dに関しては、時計回り、あるいは反時計回りの<BR>
凸形状をしている必要があります。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Rect2D<Float> Rect;
  Collision::CPolygon2D Poly;
  // 衝突判定
  if ( Collision::Rect_Polygon( Rect, Poly ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Rect_Polygon( const Math::Rect2D<Float> &Rect, const CPolygon2D &Poly );
/**
@brief 2D円と2D円の衝突判定
@author 葉迩倭
@param Cir1		[in] 2D平面上の円
@param Cir2		[in] 2D平面上の円
@retval false	衝突していない
@retval true	衝突している

@note
2D平面上の円同士の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CCircle Cir1, Cir2;
  // 衝突判定
  if ( Collision::Circle_Circle( Cir1, Cir2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Circle_Circle( const CCircle &Cir1, const CCircle &Cir2 );
/**
@brief 2D円と2D線分の衝突判定
@author 葉迩倭
@param Cir		[in] 2D平面上の円
@param Line		[in] 2D平面上の線分
@retval false	衝突していない
@retval true	衝突している

@note
2D平面上の円同士の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CCircle Cir;
  Collision::CLine2D Line;
  // 衝突判定
  if ( Collision::Circle_Line( Cir, Line ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Circle_Line( const CCircle &Cir, const CLine2D &Line );
/**
@brief 2D円と2D多角形の衝突判定
@author 葉迩倭
@param Cir		[in] 2D平面上の円
@param Poly		[in] 2D平面上の多角形
@retval false	衝突していない
@retval true	衝突している

@note
2D平面上の円と多角形の衝突判定を行います。<BR>
CPolygon2Dに関しては、時計回り、あるいは反時計回りの<BR>
凸形状をしている必要があります。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CCircle Cir;
  Collision::CPolygon2D Poly;
  // 衝突判定
  if ( Collision::Circle_Polygon( Cir, Poly ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Circle_Polygon( const CCircle &Cir, const CPolygon2D &Poly );
/**
@brief 2D線分と2D線分の衝突判定
@author 葉迩倭
@param Line1	[in] 2D平面上の線分
@param Line2	[in] 2D平面上の線分
@retval false	衝突していない
@retval true	衝突している

@note
2D平面上の線分同士の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CLine2D Line1, Line2;
  // 衝突判定
  if ( Collision::Line_Line( Line1, Line2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Line_Line( const CLine2D &Line1, const CLine2D &Line2 );
/**
@brief 2D線分と2D多角形の衝突判定
@author 葉迩倭
@param Line		[in] 2D平面上の線分
@param Poly		[in] 2D平面上の多角形
@retval false	衝突していない
@retval true	衝突している

@note
2D平面上の線分と多角形の衝突判定を行います。<BR>
CPolygon2Dに関しては、時計回り、あるいは反時計回りの<BR>
凸形状をしている必要があります。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CLine2D Line1;
  Collision::CPolygon2D Poly;
  // 衝突判定
  if ( Collision::Line_Polygon( Line, Poly ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Line_Polygon( const CLine2D &Line, const CPolygon2D &Poly );
/**
@brief 2D多角形と2D多角形の衝突判定
@author 葉迩倭
@param Poly1	[in] 2D平面上の多角形
@param Poly2	[in] 2D平面上の多角形
@retval false	衝突していない
@retval true	衝突している

@note
2D平面上の多角形同士のの衝突判定を行います。<BR>
CPolygon2Dに関しては、時計回り、あるいは反時計回りの<BR>
凸形状をしている必要があります。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CPolygon2D Poly1, Poly2;
  // 衝突判定
  if ( Collision::Polygon_Polygon( Poly1, Poly2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Polygon_Polygon( const CPolygon2D &Poly1, const CPolygon2D &Poly2 );
/**
@brief 3D点と3D点の衝突判定
@author 葉迩倭
@param Pt1		[in] 3D空間の点
@param Pt2		[in] 3D空間の点
@retval false	衝突していない
@retval true	衝突している

@note
3D空間内の点同士の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector3D Pt1, Pt2;
  // 衝突判定
  if ( Collision::Point_Point_3D( Pt1, Pt2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Point_3D( const Math::Vector3D &Pt1, const Math::Vector3D &Pt2 );
/**
@brief 3D点と3D球の衝突判定
@author 葉迩倭
@param Pt		[in] 3D空間の点
@param Sph		[in] 3D空間の球
@retval false	衝突していない
@retval true	衝突している

@note
3D空間内の点と球の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector3D Pt;
  Collision::CSphere Sph;
  // 衝突判定
  if ( Collision::Point_Sphere_3D( Pt, Sph ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Sphere_3D( const Math::Vector3D &Pt, const CSphere &Sph );
/**
@brief 3D点と3D線分の衝突判定
@author 葉迩倭
@param Pt		[in] 3D空間の点
@param Line		[in] 3D空間の線分
@retval false	衝突していない
@retval true	衝突している

@note
3D空間内の点と線分の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector3D Pt;
  Collision::CLine3D Line;
  // 衝突判定
  if ( Collision::Point_Line_3D( Pt, Line ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Line_3D( const Math::Vector3D &Pt, const CLine3D &Line );
/**
@brief 3D点と3D平面の衝突判定
@author 葉迩倭
@param Pt		[in] 3D空間の点
@param Plane	[in] 3D空間の平面
@retval false	衝突していない
@retval true	衝突している

@note
3D空間内の点と平面の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector3D Pt;
  Collision::CPlane Plane;
  // 衝突判定
  if ( Collision::Point_Plane_3D( Pt, Plane ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Plane_3D( const Math::Vector3D &Pt, const CPlane &Plane );
/**
@brief 3D点と3D箱の衝突判定
@author 葉迩倭
@param Pt		[in] 3D空間の点
@param Box		[in] 3D空間の箱
@retval false	衝突していない
@retval true	衝突している

@note
3D空間内の点と平面の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector3D Pt;
  Collision::CBox Box;
  // 衝突判定
  if ( Collision::Point_Box_3D( Pt, Box ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Box_3D( const Math::Vector3D &Pt, const CBox &Box );
/**
@brief 3D球と3D球の衝突判定
@author 葉迩倭
@param Sph1		[in] 3D空間の球
@param Sph2		[in] 3D空間の球
@retval false	衝突していない
@retval true	衝突している

@note
3D空間内の球同士の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CSphere Sph1, Sph2;
  // 衝突判定
  if ( Collision::Sphere_Sphere_3D( Sph1, Sph2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Sphere_Sphere_3D( const CSphere &Sph1, const CSphere &Sph2 );
/**
@brief 3D球と3D線分の衝突判定
@author 葉迩倭
@param Sph		[in] 3D空間の球
@param Line		[in] 3D空間の線分
@retval false	衝突していない
@retval true	衝突している

@note
3D空間内の球と線分の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CSphere Sph;
  Collision::CLine3D Line;
  // 衝突判定
  if ( Collision::Sphere_Line_3D( Sph, Line ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Sphere_Line_3D( const CSphere &Sph, const CLine3D &Line );
/**
@brief 3D球と3D平面の衝突判定
@author 葉迩倭
@param Sph		[in] 3D空間の球
@param Plane	[in] 3D空間の平面
@retval false	衝突していない
@retval true	衝突している

@note
3D空間内の球と平面の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CSphere Sph;
  Collision::CPlane Plane;
  // 衝突判定
  if ( Collision::Sphere_Plane( Sph, Plane ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Sphere_Plane( const CSphere &Sph, const CPlane &Plane );
/**
@brief 3D線分と3D平面の衝突判定
@author 葉迩倭
@param Line			[in] 3D空間の線分
@param Plane		[in] 3D空間の平面
@param vIntersect	[out] 衝突位置
@retval false	衝突していない
@retval true	衝突している

@note
3D空間内の線分と平面の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CLine3D Line;
  Collision::CPlane Plane;
  Math::Vector3D vIntersect;
  // 衝突判定
  if ( Collision::Line_Plane_3D( Line, Plane, vIntersect ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Line_Plane_3D( const CLine3D &Line, const CPlane &Plane, Math::Vector3D &vIntersect );
/**
@brief 3D線分と3D箱の衝突判定
@author 葉迩倭
@param Line			[in] 3D空間の線分
@param Box			[in] 3D空間の箱
@retval false	衝突していない
@retval true	衝突している

@note
3D空間内の線分と箱の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CLine3D Line;
  Collision::CBox Box;
  // 衝突判定
  if ( Collision::Line_Box_3D( Line, Box ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Line_Box_3D( const CLine3D &Line, const CBox &Box );
/**
@brief 3D箱と3D箱の衝突判定
@author 葉迩倭
@param Box1		[in] 3D空間の箱
@param Box2		[in] 3D空間の箱
@retval false	衝突していない
@retval true	衝突している

@note
3D空間内の箱同士の衝突判定を行います。

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CBox Box1, Box2;
  // 衝突判定
  if ( Collision::Box_Box_3D( Box1, Box2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Box_Box_3D( const CBox &Box1, const CBox &Box2 );
}
}

