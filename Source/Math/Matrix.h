#pragma once


/**
	@file
	@brief s—ñ‰‰Z
	@author —t“ô˜`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Vector4D.h"
#include "Quaternion.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Math
{
	/**
		@brief s—ñ\‘¢‘Ì
	*/
	struct SELENE_DLL_API SMatrix4x4
	{
		union {
			struct {
				Vector4D x;
				Vector4D y;
				Vector4D z;
				Vector4D w;
			};
			Float m[4][4];
		};
	};

	/**
		@brief s—ñƒNƒ‰ƒX
	*/
	class SELENE_DLL_API Matrix : public SMatrix4x4
	{
	public:
		/**
			@brief ƒRƒ“ƒXƒgƒ‰ƒNƒ^
			@author —t“ô˜`
		*/
		Matrix();

		/**
			@brief ƒRƒ“ƒXƒgƒ‰ƒNƒ^
			@author —t“ô˜`
		*/
		Matrix( const Matrix &Mat );

		/**
			@brief ƒRƒ“ƒXƒgƒ‰ƒNƒ^
			@author —t“ô˜`
		*/
		Matrix( const SMatrix4x4 &Mat );

		/**
			@brief ƒRƒ“ƒXƒgƒ‰ƒNƒ^
			@author —t“ô˜`
		*/
		Matrix( const Quaternion &In );

		/**
			@brief ƒRƒ“ƒXƒgƒ‰ƒNƒ^
			@author —t“ô˜`
		*/
		Matrix(
			Float _11, Float _12, Float _13, Float _14,
			Float _21, Float _22, Float _23, Float _24,
			Float _31, Float _32, Float _33, Float _34,
			Float _41, Float _42, Float _43, Float _44 );

		/**
			@brief s—ñ‚Ì’PˆÊ‰»
			@author —t“ô˜`
		*/
		void Identity( void );

		/**
			@brief s—ñ‚Ì“]’u‰»
			@author —t“ô˜`
			@param In	[in] ˆ—Œ³s—ñ
		*/
		Matrix &Transpose( const Matrix &In );

		/**
			@brief s—ñ‚Ì‹ts—ñ‰»
			@author —t“ô˜`
			@param In	[in] ˆ—Œ³s—ñ
		*/
		Matrix &Inverse( const Matrix &In );

		/**
			@brief s—ñ‚Ì‡¬
			@author —t“ô˜`
			@param In1		[in] ‡¬Œ³s—ñ‚P
			@param In2		[in] ‡¬Œ³s—ñ‚Q
		*/
		Matrix &Multiply( const Matrix &In1, const Matrix &In2 );

		/**
			@brief s—ñ‚Ì“]’us—ñ‰»
			@author —t“ô˜`
		*/
		Matrix &Transpose( void );

		/**
			@brief s—ñ‚Ì‹ts—ñ‰»
			@author —t“ô˜`
		*/
		Matrix &Inverse( void );

		/**
			@brief s—ñ‚Ì‡¬
			@author —t“ô˜`
			@param In	[in] ‡¬Œ³s—ñ
		*/
		Matrix &Multiply( const Matrix &In );

		/**
			@brief ‚w²‰ñ“]
			@author —t“ô˜`
			@param Angle	[in] ‰ñ“]Šp“x
		*/
		Matrix &RotationX( Sint32 Angle );

		/**
			@brief ‚x²‰ñ“]
			@author —t“ô˜`
			@param Angle	[in] ‰ñ“]Šp“x
		*/
		Matrix &RotationY( Sint32 Angle );

		/**
			@brief ‚y²‰ñ“]
			@author —t“ô˜`
			@param Angle	[in] ‰ñ“]Šp“x
		*/
		Matrix &RotationZ( Sint32 Angle );

		/**
			@brief ‚y‚w‚x‰ñ“]s—ñ‚ğ¶¬
			@author —t“ô˜`
			@param AngleX	[in] ‚w²‰ñ“]Šp“x
			@param AngleY	[in] ‚x²‰ñ“]Šp“x
			@param AngleZ	[in] ‚y²‰ñ“]Šp“x
		*/
		Matrix &RotationZXY( Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ );

		/**
			@brief ”CˆÓ²‰ñ“]
			@author —t“ô˜`
			@param Angle	[in] Šp“x
			@param Axis		[in] ‰ñ“]²
		*/
		Matrix &RotationAxis( Sint32 Angle, const Vector3D &Axis );

		/**
			@brief Šg‘åk¬s—ñ¶¬
			@author —t“ô˜`
			@param sx	[in] ‚w•ûŒüŠg‘å—¦
			@param sy	[in] ‚x•ûŒüŠg‘å—¦
			@param sz	[in] ‚y•ûŒüŠg‘å—¦
		*/
		Matrix &Scaling( Float sx, Float sy, Float sz );

		/**
			@brief ˆÚ“®s—ñ¶¬
			@author —t“ô˜`
			@param px	[in] ‚wˆÊ’u
			@param py	[in] ‚xˆÊ’u
			@param pz	[in] ‚yˆÊ’u
		*/
		Matrix &Translation( Float px, Float py, Float pz );

		/**
			@brief “§‹•ÏŠ·—ps—ñ¶¬
			@author —t“ô˜`
			@param Fov		[in] ‰æŠp
			@param NearZ	[in] ‹ßÚƒNƒŠƒbƒv–Ê
			@param FarZ		[in] ‰“•ûƒNƒŠƒbƒv–Ê
			@param Aspect	[in] ƒAƒXƒyƒNƒg”äi•`‰æƒGƒŠƒA‰¡•€•`‰æƒGƒŠƒAc•j
		*/
		Matrix &Perspective( Sint32 Fov, Float NearZ, Float FarZ, Float Aspect );

		/**
			@brief •Às“Š‰e—ps—ñ¶¬
			@author —t“ô˜`
			@param Width	[in] ‰¡•
			@param Height	[in] c•
			@param NearZ	[in] ‹ßÚƒNƒŠƒbƒv–Ê
			@param FarZ		[in] ‰“•ûƒNƒŠƒbƒv–Ê
		*/
		Matrix &Ortho( Float Width, Float Height, Float NearZ, Float FarZ );

		/**
			@brief ”CˆÓ“_’‹s—ñì¬
			@author —t“ô˜`
			@param Eye	[in] ‹“_
			@param At	[in] ’‹“_
			@param Up	[in] ã•ûŒü
		*/
		Matrix &LookAt( const Vector3D &Eye, const Vector3D &At, const Vector3D &Up );

		/**
			@brief s—ñ‚Ì•ª‰ğ
			@author —t“ô˜`
			@param vTranslate	[in] ˆÚ“®
			@param vScale		[in] Šg‘åk¬
			@param qRotate		[in] ‰ñ“]
		*/
		void Resolution( Vector3D &vTranslate, Vector3D &vScale, Quaternion &qRotate );

		/**
			@brief ƒIƒyƒŒ[ƒ^[
			@author —t“ô˜`
		*/
		Matrix &operator = ( const Quaternion &q )
		{
			Float xx = q.x * q.x;
			Float yy = q.y * q.y;
			Float zz = q.z * q.z;
			Float xy = q.x * q.y;
			Float xz = q.x * q.z;
			Float yz = q.y * q.z;
			Float wx = q.w * q.x;
			Float wy = q.w * q.y;
			Float wz = q.w * q.z;

			x.x = 1.0f - 2.0f * (yy + zz);
			x.y =        2.0f * (xy - wz);
			x.z =        2.0f * (xz + wy);
			x.w = 0.0f;

			y.x =        2.0f * (xy + wz);
			y.y = 1.0f - 2.0f * (xx + zz);
			y.z =        2.0f * (yz - wx);
			y.w = 0.0f;

			z.x =        2.0f * (xz - wy);
			z.y =        2.0f * (yz + wx);
			z.z = 1.0f - 2.0f * (xx + yy);
			z.w = 0.0f;

			w.x = 0.0f;
			w.y = 0.0f;
			w.z = 0.0f;
			w.w = 1.0f;

			return *this;
		}

		/**
			@brief ƒIƒyƒŒ[ƒ^[
			@author —t“ô˜`
		*/
		Matrix &operator = ( const Matrix &m )
		{
			MemoryCopy( this->m, m.m, sizeof(Float[4][4]) );
			return *this;
		}

		/**
			@brief ƒIƒyƒŒ[ƒ^[
			@author —t“ô˜`
		*/
		Matrix &operator = ( const SMatrix4x4 &m )
		{
			MemoryCopy( this->m, m.m, sizeof(Float[4][4]) );
			return *this;
		}

		/**
			@brief ƒIƒyƒŒ[ƒ^[
			@author —t“ô˜`
		*/
		Matrix operator * ( const Matrix &m )
		{
			Matrix mTemp;
			return mTemp.Multiply( *this, m );
		}

		/**
			@brief ƒIƒyƒŒ[ƒ^[
			@author —t“ô˜`
		*/
		Matrix &operator *= ( const Matrix &m )
		{
			return Multiply( m );
		}

		/**
			@brief ’PˆÊs—ñ
			@author —t“ô˜`
			@return ’PˆÊs—ñ
		*/
		static Matrix GetIdentity( void )
		{
			Matrix mTemp;
			mTemp.Identity();
			return mTemp;
		}

		/**
			@brief ˆÚ“®s—ñ¶¬
			@author —t“ô˜`
			@param px	[in] ‚wˆÊ’u
			@param py	[in] ‚xˆÊ’u
			@param pz	[in] ‚yˆÊ’u
			@return ˆÚ“®s—ñ
		*/
		static Matrix GetTranslation( Float px, Float py, Float pz )
		{
			Matrix mTemp;
			mTemp.Translation( px, py, pz );
			return mTemp;
		}

		/**
			@brief ‚w²‰ñ“]
			@author —t“ô˜`
			@param Angle	[in] ‰ñ“]Šp“x
			@return ‰ñ“]s—ñ
		*/
		static Matrix GetRotationX( Sint32 Angle )
		{
			Matrix mTemp;
			mTemp.RotationX( Angle );
			return mTemp;
		}

		/**
			@brief ‚x²‰ñ“]
			@author —t“ô˜`
			@param Angle	[in] ‰ñ“]Šp“x
			@return ‰ñ“]s—ñ
		*/
		static Matrix GetRotationY( Sint32 Angle )
		{
			Matrix mTemp;
			mTemp.RotationY( Angle );
			return mTemp;
		}

		/**
			@brief ‚y²‰ñ“]
			@author —t“ô˜`
			@param Angle	[in] ‰ñ“]Šp“x
			@return ‰ñ“]s—ñ
		*/
		static Matrix GetRotationZ( Sint32 Angle )
		{
			Matrix mTemp;
			mTemp.RotationZ( Angle );
			return mTemp;
		}
		
		/**
			@brief Šg‘åk¬s—ñ
			@author —t“ô˜`
			@param sx	[in] ‚w•ûŒüŠg‘å—¦
			@param sy	[in] ‚x•ûŒüŠg‘å—¦
			@param sz	[in] ‚y•ûŒüŠg‘å—¦
			@return Šg‘åk¬s—ñ
		*/
		static Matrix GetScaling( Float sx, Float sy, Float sz )
		{
			Matrix mTemp;
			mTemp.Scaling( sx, sy, sz );
			return mTemp;
		}
	};
}
}

