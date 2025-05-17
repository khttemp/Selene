#pragma once


/**
	@file
	@brief �Փ˔���
	@author �t���`
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
@brief 2D�_��2D�_�̏Փ˔���
@author �t���`
@param Pt1		[in] 2D���ʏ�̓_
@param Pt2		[in] 2D���ʏ�̓_
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ��2�̓_�̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector2D Pt1, Pt2;
  // �Փ˔���
  if ( Collision::Point_Point( Pt1, Pt2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Point( const Math::Vector2D &Pt1, const Math::Vector2D &Pt2 );
/**
@brief 2D�_��2D�����̏Փ˔���
@author �t���`
@param Pt		[in] 2D���ʏ�̓_
@param Line		[in] 2D���ʏ�̐���
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̓_�Ɛ����̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector2D Pt;
  Collision::CLine2D Line;
  // �Փ˔���
  if ( Collision::Point_Line( Pt, Line ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Line( const Math::Vector2D &Pt, const CLine2D &Line );
/**
@brief 2D�_��2D��`�̏Փ˔���
@author �t���`
@param Pt		[in] 2D���ʏ�̓_
@param Rect		[in] 2D���ʏ�̋�`
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̓_�Ƌ�`�̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector2D Pt;
  Math::Rect2D<Float> Rect;
  // �Փ˔���
  if ( Collision::Point_Rect( Pt, Rect ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Rect( const Math::Vector2D &Pt, const Math::Rect2D<Float> &Rect );
/**
@brief 2D�_��2D��`�̏Փ˔���
@author �t���`
@param Pt		[in] 2D���ʏ�̓_
@param Cir		[in] 2D���ʏ�̉~
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̓_�Ɖ~�̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector2D Pt;
  Collision::CCircle Cir;
  // �Փ˔���
  if ( Collision::Point_Circle( Pt, Cir ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Circle( const Math::Vector2D &Pt, const CCircle &Cir );
/**
@brief 2D�_��2D���p�`�̏Փ˔���
@author �t���`
@param Pt		[in] 2D���ʏ�̓_
@param Poly		[in] 2D���ʏ�̑��p�`
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̓_�Ƒ��p�`�̏Փ˔�����s���܂��B<BR>
CPolygon2D�Ɋւ��ẮA���v���A���邢�͔����v����<BR>
�ʌ`������Ă���K�v������܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector2D Pt;
  Collision::CPolygon2D Poly;
  // �Փ˔���
  if ( Collision::Point_Polygon( Pt, Poly ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Polygon( const Math::Vector2D &Pt, const CPolygon2D &Poly );
/**
@brief 2D��`��2D��`�̏Փ˔���
@author �t���`
@param Rect1		[in] 2D���ʏ�̋�`
@param Rect2		[in] 2D���ʏ�̋�`
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̋�`���m�̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Rect2D<Float> Rect1, Rect2;
  // �Փ˔���
  if ( Collision::Rect_Rect( Rect1, Rect2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Rect_Rect( const Math::Rect2D<Float> &Rect1, const Math::Rect2D<Float> &Rect2 );
/**
@brief 2D��`��2D�~�̏Փ˔���
@author �t���`
@param Rect		[in] 2D���ʏ�̋�`
@param Cir		[in] 2D���ʏ�̉~
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̋�`�Ɖ~�̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Rect2D<Float> Rect;
  Collision::CCircle Cir;
  // �Փ˔���
  if ( Collision::Rect_Circle( Rect, Cir ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Rect_Circle( const Math::Rect2D<Float> &Rect, const CCircle &Cir );
/**
@brief 2D��`��2D�����̏Փ˔���
@author �t���`
@param Rect		[in] 2D���ʏ�̋�`
@param Line		[in] 2D���ʏ�̐���
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̋�`�Ɛ����̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Rect2D<Float> Rect;
  Collision::CLine2D Line;
  // �Փ˔���
  if ( Collision::Rect_Line( Rect, Line ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Rect_Line( const Math::Rect2D<Float> &Rect, const CLine2D &Line );
/**
@brief 2D��`��2D���p�`�̏Փ˔���
@author �t���`
@param Rect		[in] 2D���ʏ�̋�`
@param Poly		[in] 2D���ʏ�̑��p�`
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̋�`�Ƒ��p�`�̏Փ˔�����s���܂��B<BR>
CPolygon2D�Ɋւ��ẮA���v���A���邢�͔����v����<BR>
�ʌ`������Ă���K�v������܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Rect2D<Float> Rect;
  Collision::CPolygon2D Poly;
  // �Փ˔���
  if ( Collision::Rect_Polygon( Rect, Poly ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Rect_Polygon( const Math::Rect2D<Float> &Rect, const CPolygon2D &Poly );
/**
@brief 2D�~��2D�~�̏Փ˔���
@author �t���`
@param Cir1		[in] 2D���ʏ�̉~
@param Cir2		[in] 2D���ʏ�̉~
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̉~���m�̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CCircle Cir1, Cir2;
  // �Փ˔���
  if ( Collision::Circle_Circle( Cir1, Cir2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Circle_Circle( const CCircle &Cir1, const CCircle &Cir2 );
/**
@brief 2D�~��2D�����̏Փ˔���
@author �t���`
@param Cir		[in] 2D���ʏ�̉~
@param Line		[in] 2D���ʏ�̐���
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̉~���m�̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CCircle Cir;
  Collision::CLine2D Line;
  // �Փ˔���
  if ( Collision::Circle_Line( Cir, Line ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Circle_Line( const CCircle &Cir, const CLine2D &Line );
/**
@brief 2D�~��2D���p�`�̏Փ˔���
@author �t���`
@param Cir		[in] 2D���ʏ�̉~
@param Poly		[in] 2D���ʏ�̑��p�`
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̉~�Ƒ��p�`�̏Փ˔�����s���܂��B<BR>
CPolygon2D�Ɋւ��ẮA���v���A���邢�͔����v����<BR>
�ʌ`������Ă���K�v������܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CCircle Cir;
  Collision::CPolygon2D Poly;
  // �Փ˔���
  if ( Collision::Circle_Polygon( Cir, Poly ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Circle_Polygon( const CCircle &Cir, const CPolygon2D &Poly );
/**
@brief 2D������2D�����̏Փ˔���
@author �t���`
@param Line1	[in] 2D���ʏ�̐���
@param Line2	[in] 2D���ʏ�̐���
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̐������m�̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CLine2D Line1, Line2;
  // �Փ˔���
  if ( Collision::Line_Line( Line1, Line2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Line_Line( const CLine2D &Line1, const CLine2D &Line2 );
/**
@brief 2D������2D���p�`�̏Փ˔���
@author �t���`
@param Line		[in] 2D���ʏ�̐���
@param Poly		[in] 2D���ʏ�̑��p�`
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̐����Ƒ��p�`�̏Փ˔�����s���܂��B<BR>
CPolygon2D�Ɋւ��ẮA���v���A���邢�͔����v����<BR>
�ʌ`������Ă���K�v������܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CLine2D Line1;
  Collision::CPolygon2D Poly;
  // �Փ˔���
  if ( Collision::Line_Polygon( Line, Poly ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Line_Polygon( const CLine2D &Line, const CPolygon2D &Poly );
/**
@brief 2D���p�`��2D���p�`�̏Փ˔���
@author �t���`
@param Poly1	[in] 2D���ʏ�̑��p�`
@param Poly2	[in] 2D���ʏ�̑��p�`
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̑��p�`���m�̂̏Փ˔�����s���܂��B<BR>
CPolygon2D�Ɋւ��ẮA���v���A���邢�͔����v����<BR>
�ʌ`������Ă���K�v������܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CPolygon2D Poly1, Poly2;
  // �Փ˔���
  if ( Collision::Polygon_Polygon( Poly1, Poly2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Polygon_Polygon( const CPolygon2D &Poly1, const CPolygon2D &Poly2 );
/**
@brief 3D�_��3D�_�̏Փ˔���
@author �t���`
@param Pt1		[in] 3D��Ԃ̓_
@param Pt2		[in] 3D��Ԃ̓_
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̓_���m�̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector3D Pt1, Pt2;
  // �Փ˔���
  if ( Collision::Point_Point_3D( Pt1, Pt2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Point_3D( const Math::Vector3D &Pt1, const Math::Vector3D &Pt2 );
/**
@brief 3D�_��3D���̏Փ˔���
@author �t���`
@param Pt		[in] 3D��Ԃ̓_
@param Sph		[in] 3D��Ԃ̋�
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̓_�Ƌ��̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector3D Pt;
  Collision::CSphere Sph;
  // �Փ˔���
  if ( Collision::Point_Sphere_3D( Pt, Sph ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Sphere_3D( const Math::Vector3D &Pt, const CSphere &Sph );
/**
@brief 3D�_��3D�����̏Փ˔���
@author �t���`
@param Pt		[in] 3D��Ԃ̓_
@param Line		[in] 3D��Ԃ̐���
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̓_�Ɛ����̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector3D Pt;
  Collision::CLine3D Line;
  // �Փ˔���
  if ( Collision::Point_Line_3D( Pt, Line ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Line_3D( const Math::Vector3D &Pt, const CLine3D &Line );
/**
@brief 3D�_��3D���ʂ̏Փ˔���
@author �t���`
@param Pt		[in] 3D��Ԃ̓_
@param Plane	[in] 3D��Ԃ̕���
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̓_�ƕ��ʂ̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector3D Pt;
  Collision::CPlane Plane;
  // �Փ˔���
  if ( Collision::Point_Plane_3D( Pt, Plane ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Plane_3D( const Math::Vector3D &Pt, const CPlane &Plane );
/**
@brief 3D�_��3D���̏Փ˔���
@author �t���`
@param Pt		[in] 3D��Ԃ̓_
@param Box		[in] 3D��Ԃ̔�
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̓_�ƕ��ʂ̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector3D Pt;
  Collision::CBox Box;
  // �Փ˔���
  if ( Collision::Point_Box_3D( Pt, Box ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Box_3D( const Math::Vector3D &Pt, const CBox &Box );
/**
@brief 3D����3D���̏Փ˔���
@author �t���`
@param Sph1		[in] 3D��Ԃ̋�
@param Sph2		[in] 3D��Ԃ̋�
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̋����m�̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CSphere Sph1, Sph2;
  // �Փ˔���
  if ( Collision::Sphere_Sphere_3D( Sph1, Sph2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Sphere_Sphere_3D( const CSphere &Sph1, const CSphere &Sph2 );
/**
@brief 3D����3D�����̏Փ˔���
@author �t���`
@param Sph		[in] 3D��Ԃ̋�
@param Line		[in] 3D��Ԃ̐���
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̋��Ɛ����̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CSphere Sph;
  Collision::CLine3D Line;
  // �Փ˔���
  if ( Collision::Sphere_Line_3D( Sph, Line ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Sphere_Line_3D( const CSphere &Sph, const CLine3D &Line );
/**
@brief 3D����3D���ʂ̏Փ˔���
@author �t���`
@param Sph		[in] 3D��Ԃ̋�
@param Plane	[in] 3D��Ԃ̕���
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̋��ƕ��ʂ̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CSphere Sph;
  Collision::CPlane Plane;
  // �Փ˔���
  if ( Collision::Sphere_Plane( Sph, Plane ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Sphere_Plane( const CSphere &Sph, const CPlane &Plane );
/**
@brief 3D������3D���ʂ̏Փ˔���
@author �t���`
@param Line			[in] 3D��Ԃ̐���
@param Plane		[in] 3D��Ԃ̕���
@param vIntersect	[out] �Փˈʒu
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̐����ƕ��ʂ̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CLine3D Line;
  Collision::CPlane Plane;
  Math::Vector3D vIntersect;
  // �Փ˔���
  if ( Collision::Line_Plane_3D( Line, Plane, vIntersect ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Line_Plane_3D( const CLine3D &Line, const CPlane &Plane, Math::Vector3D &vIntersect );
/**
@brief 3D������3D���̏Փ˔���
@author �t���`
@param Line			[in] 3D��Ԃ̐���
@param Box			[in] 3D��Ԃ̔�
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̐����Ɣ��̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CLine3D Line;
  Collision::CBox Box;
  // �Փ˔���
  if ( Collision::Line_Box_3D( Line, Box ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Line_Box_3D( const CLine3D &Line, const CBox &Box );
/**
@brief 3D����3D���̏Փ˔���
@author �t���`
@param Box1		[in] 3D��Ԃ̔�
@param Box2		[in] 3D��Ԃ̔�
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̔����m�̏Փ˔�����s���܂��B

@code
#include "Selene.h"

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CBox Box1, Box2;
  // �Փ˔���
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

