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
	class CFrame : public Math::Style, public CBaseObject
	{
	private:
		Math::Matrix m_mDefaultLocal;
		Math::Matrix m_mTransform;
		Math::Matrix m_mWorld;
		Math::Matrix m_mLocal;
		Math::Matrix m_mBoneOffset;
		CBaseList m_Child;
		Sint32 m_ParentFrameNo;
		Bool m_IsBone;
		Math::Vector3D *m_pBoxPoints;
		Sint32 m_AnimationCount;
		CAnimationData **m_pAnimationDataTbl;

	public:
		CFrame();
		virtual ~CFrame();

		virtual void CreateAnimationData( Sint32 AnimationCount );
		virtual void SetAnimationData( Sint32 AnimationControllerNo, CAnimationData *pAnimationData );

		virtual void ConnectChildFrame( CFrame *pFrame );
		virtual void SetParentFrameNo( Sint32 No );
		virtual Sint32 GetParentFrameNo( void );

		virtual Math::Vector3D *GetCollisionPoint( void );

		virtual Math::Matrix &GetMatrixTransform( void );
		virtual Math::Matrix &GetMatrixWorld( void );
		virtual Math::Matrix &GetMatrixLocal( void );

		virtual void GetTransform( Math::Matrix &Mtx );
		virtual void GetTransformInverse( Math::Matrix &Mtx );

		virtual void SetDefaultLocalMatrix( const Math::Matrix &mDefault );
		virtual void SetAnimationMatrix( const Math::Matrix &mAnimation );
		virtual void SetBoneOffsetMatrix( const Math::Matrix &mOffset );

		virtual void UpdateTransform( const Math::Matrix &mWorld );
		virtual void ResetAnimationTransform( void );
		virtual void UpdateAnimationTransform( Sint32 AnimationNo );
		virtual void UpdateAnimationTransform( Sint32 AnimationNo1, Sint32 AnimationNo2, Float fWeight );

		virtual void SetBounding( const Collision::CBox &OBB );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }
	};
}
}
}

