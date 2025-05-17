

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Dynamics/Class/CDynamicsSimulationWorld.h"
#include "Dynamics/Class/CDynamicsRigidBody.h"
#include "Dynamics/Class/CDynamicsRigidModel.h"
#include "Class/Platform/Render/CRender.h"
#include "Class/Common/Render/3D/CPrimitive3D.h"
#include "Class/Common/Render/Map/CMapModel.h"
#include "Class/Common/Render/Model/CModel.h"
#include "Class/Common/Render/Model/CMesh.h"
#include "Class/Common/Scene/CSceneManagerBase.h"
#include "Class/Common/Scene/CScenePrimitiveActor.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Dynamics;


//-----------------------------------------------------------------------------------
// STRUCT
//-----------------------------------------------------------------------------------
struct CALLBACK_DATA
{
	CollisionProc CallbackProc;
	CSimulationWorld *pWorld;
	CContactPoint *pContactPoint;
};


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSimulationWorld::GeometoryCallback( void *pData, dGeomID Obj1, dGeomID Obj2 )
{
	CRigidBody *pBody1 = (CRigidBody*)dGeomGetData( Obj1 );
	CRigidBody *pBody2 = (CRigidBody*)dGeomGetData( Obj2 );

	//------------------------------------------------------
	// �����}�b�v�Ȃ疳��
	//------------------------------------------------------
	if ( (pBody1->GetType() == BODY_TYPE_MAP) && (pBody2->GetType() == BODY_TYPE_MAP) )
	{
		return;
	}

	//------------------------------------------------------
	// �ǂ��������X�y�[�X�Ȃ�ʏ�����
	//------------------------------------------------------
	if ( dGeomIsSpace( Obj1 ) || dGeomIsSpace( Obj2 ) )
	{
		// colliding a space with something	
		dSpaceCollide2( Obj1, Obj2, pData, &GeometoryCallback );
		// Note we do not want to test intersections within a space,
		// only between spaces.
		return;
	}

	//------------------------------------------------------
	// �R���W��������
	//------------------------------------------------------
	CALLBACK_DATA *pCallback = (CALLBACK_DATA*)pData;
	CContactPoint *pContactPoint = pCallback->pContactPoint;
	dContact *pContact = pContactPoint->GetContactPointTbl();

	//------------------------------------------------------
	// �Փ˔���
	//------------------------------------------------------
	Sint32 Count = dCollide(
						Obj1,							// �I�u�W�F�P
						Obj2,							// �I�u�W�F�Q
						pContactPoint->GetMaxCount(),	// �ő吔
						&pContact->geom,				// �i�[��̃A�h���X
						sizeof(dContact) );				// �T�C�Y���̃X�L�b�v��
	pContactPoint->SetCount( Count );

	//------------------------------------------------------
	// �A�v���P�[�V�����ւ̃R�[���o�b�N
	//------------------------------------------------------
	pCallback->CallbackProc(
					pCallback->pWorld,
					pBody1,
					pBody2,
					pContactPoint );

	//------------------------------------------------------
	// �Փˌ�W���C���g����
	//------------------------------------------------------
	for ( Sint32 i = 0; i < Count; i++ )
	{
		// �R���^�N�g�W���C���g����
		dJointID Joint = dJointCreateContact(
							((CSimulationWorld*)(pCallback->pWorld))->m_World,
							((CSimulationWorld*)(pCallback->pWorld))->m_JointGroup,
							&pContact[i] );

		// �ڐG���Ă���Q��geometry���R���^�N�g�W���C���g�ōS��
		dJointAttach(
			Joint,
			dGeomGetBody( pContact[i].geom.g1 ),
			dGeomGetBody( pContact[i].geom.g2 ) );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSimulationWorld::CSimulationWorld( Scene::ISceneManager *pScene )
	: m_World			( dWorldCreate() )
	, m_Space			( dHashSpaceCreate( 0 ) )
	, m_JointGroup		( dJointGroupCreate( 0 ) )
	, m_pContactPoint	( NULL )
	, m_pRenderScene	( NULL )
	, m_pActorEarth		( NULL )
{
	// �����l
	SetContactPointCount( 8 );
	dWorldSetQuickStepNumIterations( m_World, 10 );

	// �V�[����ݒ�
	m_pRenderScene = pScene;
	if ( (m_pRenderScene != NULL) && !m_pRenderScene->IsInvalid() )
	{
		m_pRenderScene->AddRef();
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSimulationWorld::~CSimulationWorld( void )
{
	SAFE_RELEASE( m_pActorEarth );
	SAFE_RELEASE( m_pRenderScene );
	// �R���^�N�g�|�C���g���
	SAFE_DELETE( m_pContactPoint );
	// �X�y�[�X�̔j��
	dSpaceDestroy( m_Space );
	// ���[���h�̔j��
	dWorldDestroy( m_World );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSimulationWorld::SetStepNumIterations( Sint32 Count )
{
	dWorldSetQuickStepNumIterations( m_World, Count );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSimulationWorld::SetContactPointCount( Sint32 Count )
{
	SAFE_DELETE( m_pContactPoint );
	m_pContactPoint = new CContactPoint( Count );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSimulationWorld::CreateEarth( void )
{
	if ( (m_pRenderScene != NULL) && !m_pRenderScene->IsInvalid() )
	{
		Sint32 CellCount = 30;
		Sint32 Temp = CellCount + 3;

		SAFE_RELEASE( m_pActorEarth );
		Renderer::IRender *pRender = ((Scene::CSceneManagerBase*)m_pRenderScene)->GetRenderPointer();

		Renderer::Object::IPrimitive3D	*pPrimitive;
		pPrimitive = pRender->CreatePrimitive3D(
									Temp * Temp * 4,
									Temp * Temp * 6,
									VERTEX_ELEMENT_3DBASE | VERTEX_ELEMENT_3DLIGHT,
									false, false );

		pPrimitive->Begin();

		Float fAreaSize = 200.0f;
		Float fSx = fAreaSize / toF(CellCount);
		Float fSz = fAreaSize / toF(CellCount);

		CellCount /= 2;

		for ( Sint32 z = -CellCount; z <= +CellCount; z++ )
		{
			for ( Sint32 x = -CellCount; x <= +CellCount; x++ )
			{
				CColor Color = (x + z) % 2 ? CColor(160,255,160,255) : CColor(160,160,255,255);

				// ���_�ʒu
				Renderer::SVertex3DBase VtxBase[] = {
					{ Math::Vector3D( toF(x  )*fSx, 0.0f, toF(z+1)*fSz ), Color },
					{ Math::Vector3D( toF(x+1)*fSx, 0.0f, toF(z+1)*fSz ), Color },
					{ Math::Vector3D( toF(x+1)*fSx, 0.0f, toF(z  )*fSz ), Color },
					{ Math::Vector3D( toF(x  )*fSx, 0.0f, toF(z  )*fSz ), Color },
				};
				pPrimitive->Push( VtxBase, 4 );

				// ���_�@��
				Renderer::SVertex3DLight VtxNorm[] = {
					{ Math::Vector3D( 0.0f, 1.0f, 0.0f ) },
					{ Math::Vector3D( 0.0f, 1.0f, 0.0f ) },
					{ Math::Vector3D( 0.0f, 1.0f, 0.0f ) },
					{ Math::Vector3D( 0.0f, 1.0f, 0.0f ) },
				};
				pPrimitive->Push( VtxNorm, 4 );

				// �C���f�b�N�X
				Sint32 Cnt = pPrimitive->GetVertexCount();
				Uint16 Idx[] = {
					(Uint16)(Cnt+0), (Uint16)(Cnt+1), (Uint16)(Cnt+2),
					(Uint16)(Cnt+2), (Uint16)(Cnt+3), (Uint16)(Cnt+0),
				};
				pPrimitive->Push( Idx, 6 );
			}
		}

		pPrimitive->End();

		// �A�N�^�[�̐���
		m_pActorEarth = m_pRenderScene->CreateActor( pPrimitive );

		SAFE_RELEASE( pPrimitive );
	}

	dGeomID GeomId = dCreatePlane( m_Space, 0.0f, 1.0f, 0.0f, 0.0f );
	dGeomSetData( GeomId, NULL );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSimulationWorld::SetGravity( Math::Vector3D &vDir )
{
	dWorldSetGravity( m_World, vDir.x, vDir.y, vDir.z );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSimulationWorld::Update( Float fTime, CollisionProc Proc )
{
	CALLBACK_DATA Callback = {
		Proc, this, m_pContactPoint
	};

	// �Փ˔���
	dSpaceCollide( m_Space, &Callback, &GeometoryCallback );

	// �V�~�����[�V������i�߂�
	dWorldQuickStep( m_World, fTime );

	// �W���C���g�O���[�v����ɂ���
	dJointGroupEmpty( m_JointGroup );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSimulationWorld::AddBody( CRigidBody *pBody )
{
	m_BodyList.InsertEnd( pBody );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSimulationWorld::DelBody( CRigidBody *pBody )
{
	m_BodyList.Erase( pBody );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSimulationWorld::RenderingRequest( void )
{
	if ( (m_pRenderScene == NULL) || m_pRenderScene->IsInvalid() )
	{
		return;
	}

	Renderer::IRender *pRender = ((Scene::CSceneManagerBase*)m_pRenderScene)->GetRenderPointer();

	pRender->StatePush();

	pRender->SetDrawType( DRAW_TYPE_NORMAL );
	pRender->SetAlphaTestEnable( true );
	pRender->SetDepthTestEnable( true );
	pRender->SetDepthWriteEnable( true );
	pRender->SetTexture( TEXTURE_STAGE_COLOR, NULL );
	pRender->SetTexture( TEXTURE_STAGE_LIGHT, NULL );
	pRender->SetTexture( TEXTURE_STAGE_ENVIRONMENT, NULL );
	pRender->SetTexture( TEXTURE_STAGE_SPECULAR, NULL );
	pRender->SetTexture( TEXTURE_STAGE_NORMAL, NULL );

	if ( m_pActorEarth != NULL )
	{
		m_pActorEarth->TransformReset();
		m_pActorEarth->TransformUpdate();
		m_pActorEarth->RenderingRequest();
	}

	CRigidBody *pBody = (CRigidBody*)m_BodyList.GetTop();
	while ( pBody != NULL )
	{
		pBody->RenderingRequest();

		pBody = (CRigidBody*)pBody->GetNext();
	}

	pRender->StatePop();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IRigidBody *CSimulationWorld::CreateSphere( Float fRadius, Float fMass, Bool IsBody )
{
	dBodyID Body = 0;
	dGeomID Geom = 0;

	Geom = dCreateSphere( m_Space, fRadius );

	// �֘A�t��
	if ( IsBody )
	{
		Body = dBodyCreate( m_World );
		dGeomSetBody( Geom, Body );
		// ����
		dMass Mass;
		dMassSetZero( &Mass );
		dMassSetSphereTotal( &Mass, fMass, fRadius );
		dBodySetMass( Body, &Mass );
	}

	Scene::IPrimitiveActor *pActor = NULL;

	// �v���~�e�B�u�f�[�^�̐���
	if ( (m_pRenderScene != NULL) && !m_pRenderScene->IsInvalid() )
	{
		Sint32 Slices = 6;
		Sint32 Stacks = 12;

		Renderer::SVertex3DBase v1;
		Renderer::SVertex3DLight v2;

		Math::Vector3D vTemp;
		Math::Matrix Mtx;

		Sint32 Num;

		Renderer::IRender *pRender = ((Scene::CSceneManagerBase*)m_pRenderScene)->GetRenderPointer();

		Renderer::Object::IPrimitive3D *pPrimitive;
		pPrimitive = pRender->CreatePrimitive3D(
								Slices * (Stacks + 1),
								Slices * Stacks * 6,
								VERTEX_ELEMENT_3DBASE | VERTEX_ELEMENT_3DLIGHT,
								false, false );

		pPrimitive->Begin();

		// ���_����
		Float fHorz = PI2 / toF(Stacks);
		Float fVert = PI  / toF(Slices-1);

		Num = 0;
		for ( Sint32 i = 0; i < Slices; i++ )
		{
			Math::Vector3D Vertex( 0, 1, 0 );

			Mtx.RotationX( PI_TO_ANGLE(fVert * i) );
			vTemp.TransformNormal( Vertex, Mtx );

			for ( Sint32 j = 0; j < Stacks + 1; j++ )
			{
				Mtx.RotationY( PI_TO_ANGLE( PI2 - fHorz * j ) );
				Vertex.TransformCoord( vTemp, Mtx );

				Math::Vector3D vPos( Vertex.x * fRadius, Vertex.y * fRadius, Vertex.z * fRadius );

				v1.Pos = vPos;
				v1.Col = 0xFFFF80FF;
				v2.Norm = Vertex;

				pPrimitive->Push( &v1, 1 );
				pPrimitive->Push( &v2, 1 );

				Num++;
			}
		}

		// �C���f�b�N�X����
		Num = 0;
		for ( Sint32 i = 1; i < Slices; i++ )
		{
			for ( Sint32 j = 0; j < Stacks; j++ )
			{
				Uint16 Idx[] = {
					(Uint16)(Num + 0),
					(Uint16)(Num + 1),
					(Uint16)(Num + Stacks+1),
					(Uint16)(Num + 1),
					(Uint16)(Num + Stacks + 2),
					(Uint16)(Num + Stacks + 1),
				};
				pPrimitive->Push( Idx, 6 );

				Num++;
			}

			Num++;
		}

		pPrimitive->End();

		// �A�N�^�[�̐���
		pActor = m_pRenderScene->CreateActor( pPrimitive );

		SAFE_RELEASE( pPrimitive );
	}

	// �C���^�[�t�F�C�X����
	return new CRigidBody( this, m_World, Body, Geom, 0, pActor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IRigidBody *CSimulationWorld::CreateCapsule( Float fRadius, Float fLength, Float fMass, Bool IsBody )
{
	dBodyID Body = 0;
	dGeomID Geom = 0;

	Geom = dCreateCapsule( m_Space, fRadius, fLength );

	// �֘A�t��
	if ( IsBody )
	{
		Body = dBodyCreate( m_World );
		dGeomSetBody( Geom, Body );
		// ����
		dMass Mass;
		dMassSetZero( &Mass );
		dMassSetCapsuleTotal( &Mass, fMass, 3, fRadius, fLength );
		dBodySetMass( Body, &Mass );
	}

	Scene::IPrimitiveActor *pActor = NULL;

	// �v���~�e�B�u�f�[�^�̐���
	if ( (m_pRenderScene != NULL) && !m_pRenderScene->IsInvalid() )
	{
		Sint32 Slices = 4;
		Sint32 Stacks = 12;

		Renderer::SVertex3DBase v1;
		Renderer::SVertex3DLight v2;

		Math::Vector3D vTemp;
		Math::Matrix Mtx, mRotate, mTransform;

		Sint32 Num;

		mRotate.RotationZ( DEG_TO_ANGLE( 90 ) );

		Renderer::IRender *pRender = ((Scene::CSceneManagerBase*)m_pRenderScene)->GetRenderPointer();

		Renderer::Object::IPrimitive3D *pPrimitive;
		pPrimitive = pRender->CreatePrimitive3D(
								(Slices * (Stacks + 1) * 2) + ((Stacks + 1) * 2),
								(Slices * Stacks * 6 * 2) + (Stacks * 6),
								VERTEX_ELEMENT_3DBASE | VERTEX_ELEMENT_3DLIGHT,
								false, false );

		pPrimitive->Begin();

		Float fHorz = PI2 / toF(Stacks);
		Float fVert = PI  / toF(Slices-1) / 2.0f;

		// �C���f�b�N�X����
		Num = pPrimitive->GetVertexCount();
		for ( Sint32 i = 1; i < Slices; i++ )
		{
			for ( Sint32 j = 0; j < Stacks; j++ )
			{
				Uint16 Idx[] = {
					(Uint16)(Num + 0),
					(Uint16)(Num + 1),
					(Uint16)(Num + Stacks+1),
					(Uint16)(Num + 1),
					(Uint16)(Num + Stacks + 2),
					(Uint16)(Num + Stacks + 1),
				};
				pPrimitive->Push( Idx, 6 );

				Num++;
			}

			Num++;
		}

		// ���_����
		mTransform.Translation( 0.0f, 0.0f, +fLength * 0.5f );
		mTransform *= mRotate;
		for ( Sint32 i = 0; i < Slices; i++ )
		{
			Math::Vector3D Vertex( 0.0f, 0.0f, 1.0f );

			Mtx.RotationX( PI_TO_ANGLE(fVert * i) );
			vTemp.TransformNormal( Vertex, Mtx );

			for ( Sint32 j = 0; j < Stacks + 1; j++ )
			{
				Mtx.RotationZ( PI_TO_ANGLE( PI2 - fHorz * j ) );
				Vertex.TransformCoord( vTemp, Mtx );

				Math::Vector3D vPos( Vertex.x * fRadius, Vertex.y * fRadius, Vertex.z * fRadius );

				v1.Pos.TransformCoord( vPos, mTransform );
				v1.Col = 0xFF80FFFF;
				v2.Norm.TransformNormal( Vertex, mTransform );

				pPrimitive->Push( &v1, 1 );
				pPrimitive->Push( &v2, 1 );
			}
		}

		// �C���f�b�N�X����
		Num = pPrimitive->GetVertexCount();
		for ( Sint32 i = 1; i < Slices; i++ )
		{
			for ( Sint32 j = 0; j < Stacks; j++ )
			{
				Uint16 Idx[] = {
					(Uint16)(Num + 0),
					(Uint16)(Num + 1),
					(Uint16)(Num + Stacks+1),
					(Uint16)(Num + 1),
					(Uint16)(Num + Stacks + 2),
					(Uint16)(Num + Stacks + 1),
				};
				pPrimitive->Push( Idx, 6 );

				Num++;
			}

			Num++;
		}

		// ���_����
		mTransform.Translation( 0.0f, 0.0f, -fLength * 0.5f );
		for ( Sint32 i = 0; i < Slices; i++ )
		{
			Math::Vector3D Vertex( 0.0f, 0.0f, -1.0f );

			Mtx.RotationX( PI_TO_ANGLE(fVert * i) );
			vTemp.TransformNormal( Vertex, Mtx );

			for ( Sint32 j = 0; j < Stacks + 1; j++ )
			{
				Mtx.RotationZ( PI_TO_ANGLE( fHorz * j ) );
				Vertex.TransformCoord( vTemp, Mtx );

				Math::Vector3D vPos( Vertex.x * fRadius, Vertex.y * fRadius, Vertex.z * fRadius );

				v1.Pos.TransformCoord( vPos, mTransform );
				v1.Col = 0xFF80FFFF;
				v2.Norm.TransformNormal( Vertex, mTransform );

				pPrimitive->Push( &v1, 1 );
				pPrimitive->Push( &v2, 1 );
			}
		}

		// �C���f�b�N�X����
		Num = pPrimitive->GetVertexCount();
		for ( Sint32 i = 0; i < Stacks; i++ )
		{
			Uint16 Idx[] = {
				(Uint16)(Num + 0),
				(Uint16)(Num + 1),
				(Uint16)(Num + 3),
				(Uint16)(Num + 3),
				(Uint16)(Num + 2),
				(Uint16)(Num + 0),
			};
			pPrimitive->Push( Idx, 6 );

			Num += 2;
		}

		// ���_����
		Math::Vector3D Vertex( 0.0f, 1.0f, 0.0f );
		for ( Sint32 i = 0; i < Stacks + 1; i++ )
		{
			Mtx.RotationZ( PI_TO_ANGLE( fHorz * i ) );
			Vertex.TransformCoord( vTemp, Mtx );

			Math::Vector3D vPos;

			vPos.Set( Vertex.x * fRadius, Vertex.y * fRadius, Vertex.z + fLength / 2.0f );
			v1.Pos.TransformCoord( vPos, mRotate );
			v1.Col = 0xFF80FFFF;
			v2.Norm.TransformNormal( Vertex, mRotate );
			pPrimitive->Push( &v1, 1 );
			pPrimitive->Push( &v2, 1 );

			vPos.Set( Vertex.x * fRadius, Vertex.y * fRadius, Vertex.z - fLength / 2.0f );
			v1.Pos.TransformCoord( vPos, mRotate );
			v1.Col = 0xFF80FFFF;
			v2.Norm.TransformNormal( Vertex, mRotate );
			pPrimitive->Push( &v1, 1 );
			pPrimitive->Push( &v2, 1 );
		}

		pPrimitive->End();

		// �A�N�^�[�̐���
		pActor = m_pRenderScene->CreateActor( pPrimitive );

		SAFE_RELEASE( pPrimitive );
	}

	// �C���^�[�t�F�C�X����
	return new CRigidBody( this, m_World, Body, Geom, 0, pActor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IRigidBody *CSimulationWorld::CreateBox( Math::Point3DF &Size, Float fMass, Bool IsBody )
{
	dBodyID Body = 0;
	dGeomID Geom = 0;

	Geom = dCreateBox( m_Space, Size.x, Size.y, Size.z );

	// �֘A�t��
	if ( IsBody )
	{
		Body = dBodyCreate( m_World );
		dGeomSetBody( Geom, Body );
		// ����
		dMass Mass;
		dMassSetZero( &Mass );
		dMassSetBoxTotal( &Mass, fMass, Size.x, Size.y, Size.z );
		dBodySetMass( Body, &Mass );
	}

	Scene::IPrimitiveActor *pActor = NULL;

	// �v���~�e�B�u�f�[�^�̐���
	if ( (m_pRenderScene != NULL) && !m_pRenderScene->IsInvalid() )
	{
		Math::Vector3D vTemp;
		Math::Matrix Mtx;

		Sint32 Num;

		Renderer::IRender *pRender = ((Scene::CSceneManagerBase*)m_pRenderScene)->GetRenderPointer();

		Renderer::Object::IPrimitive3D *pPrimitive;
		pPrimitive = pRender->CreatePrimitive3D(
								4 * 6,
								6 * 6,
								VERTEX_ELEMENT_3DBASE | VERTEX_ELEMENT_3DLIGHT,
								false, false );

		pPrimitive->Begin();

		// ���_����
		Size.x *= 0.5f;
		Size.y *= 0.5f;
		Size.z *= 0.5f;

		Renderer::SVertex3DBase v1[] = {
			// ��
			{ Math::Vector3D(-Size.x,+Size.y,+Size.z), 0xFFFFFF80 },
			{ Math::Vector3D(+Size.x,+Size.y,+Size.z), 0xFFFFFF80 },
			{ Math::Vector3D(-Size.x,+Size.y,-Size.z), 0xFFFFFF80 },
			{ Math::Vector3D(+Size.x,+Size.y,-Size.z), 0xFFFFFF80 },
			// ��
			{ Math::Vector3D(-Size.x,-Size.y,-Size.z), 0xFFFFFF80 },
			{ Math::Vector3D(+Size.x,-Size.y,-Size.z), 0xFFFFFF80 },
			{ Math::Vector3D(-Size.x,-Size.y,+Size.z), 0xFFFFFF80 },
			{ Math::Vector3D(+Size.x,-Size.y,+Size.z), 0xFFFFFF80 },
			// �O
			{ Math::Vector3D(-Size.x,+Size.y,-Size.z), 0xFFFFFF80 },
			{ Math::Vector3D(+Size.x,+Size.y,-Size.z), 0xFFFFFF80 },
			{ Math::Vector3D(-Size.x,-Size.y,-Size.z), 0xFFFFFF80 },
			{ Math::Vector3D(+Size.x,-Size.y,-Size.z), 0xFFFFFF80 },
			// ��
			{ Math::Vector3D(+Size.x,+Size.y,+Size.z), 0xFFFFFF80 },
			{ Math::Vector3D(-Size.x,+Size.y,+Size.z), 0xFFFFFF80 },
			{ Math::Vector3D(+Size.x,-Size.y,+Size.z), 0xFFFFFF80 },
			{ Math::Vector3D(-Size.x,-Size.y,+Size.z), 0xFFFFFF80 },
			// ��
			{ Math::Vector3D(-Size.x,+Size.y,+Size.z), 0xFFFFFF80 },
			{ Math::Vector3D(-Size.x,+Size.y,-Size.z), 0xFFFFFF80 },
			{ Math::Vector3D(-Size.x,-Size.y,+Size.z), 0xFFFFFF80 },
			{ Math::Vector3D(-Size.x,-Size.y,-Size.z), 0xFFFFFF80 },
			// �E
			{ Math::Vector3D(+Size.x,+Size.y,-Size.z), 0xFFFFFF80 },
			{ Math::Vector3D(+Size.x,+Size.y,+Size.z), 0xFFFFFF80 },
			{ Math::Vector3D(+Size.x,-Size.y,-Size.z), 0xFFFFFF80 },
			{ Math::Vector3D(+Size.x,-Size.y,+Size.z), 0xFFFFFF80 },
		};
		Renderer::SVertex3DLight v2[] = {
			// ��
			{ Math::Vector3D(0.0f,+1.0f,0.0f) },
			{ Math::Vector3D(0.0f,+1.0f,0.0f) },
			{ Math::Vector3D(0.0f,+1.0f,0.0f) },
			{ Math::Vector3D(0.0f,+1.0f,0.0f) },
			// ��
			{ Math::Vector3D(0.0f,-1.0f,0.0f) },
			{ Math::Vector3D(0.0f,-1.0f,0.0f) },
			{ Math::Vector3D(0.0f,-1.0f,0.0f) },
			{ Math::Vector3D(0.0f,-1.0f,0.0f) },
			// �O
			{ Math::Vector3D(0.0f,0.0f,-1.0f) },
			{ Math::Vector3D(0.0f,0.0f,-1.0f) },
			{ Math::Vector3D(0.0f,0.0f,-1.0f) },
			{ Math::Vector3D(0.0f,0.0f,-1.0f) },
			// ��
			{ Math::Vector3D(0.0f,0.0f,+1.0f) },
			{ Math::Vector3D(0.0f,0.0f,+1.0f) },
			{ Math::Vector3D(0.0f,0.0f,+1.0f) },
			{ Math::Vector3D(0.0f,0.0f,+1.0f) },
			// ��
			{ Math::Vector3D(-1.0f,0.0f,0.0f) },
			{ Math::Vector3D(-1.0f,0.0f,0.0f) },
			{ Math::Vector3D(-1.0f,0.0f,0.0f) },
			{ Math::Vector3D(-1.0f,0.0f,0.0f) },
			// �E
			{ Math::Vector3D(+1.0f,0.0f,0.0f) },
			{ Math::Vector3D(+1.0f,0.0f,0.0f) },
			{ Math::Vector3D(+1.0f,0.0f,0.0f) },
			{ Math::Vector3D(+1.0f,0.0f,0.0f) },
		};
		pPrimitive->Push( v1, 24 );
		pPrimitive->Push( v2, 24 );

		// �C���f�b�N�X����
		Num = 0;
		for ( Sint32 i = 0; i < 6; i++ )
		{
			Uint16 Idx[] = {
				(Uint16)(Num + 0),
				(Uint16)(Num + 1),
				(Uint16)(Num + 3),
				(Uint16)(Num + 3),
				(Uint16)(Num + 2),
				(Uint16)(Num + 0),
			};
			pPrimitive->Push( Idx, 6 );
			Num += 4;
		}

		pPrimitive->End();

		// �A�N�^�[�̐���
		pActor = m_pRenderScene->CreateActor( pPrimitive );

		SAFE_RELEASE( pPrimitive );
	}

	// �C���^�[�t�F�C�X����
	return new CRigidBody( this, m_World, Body, Geom, 0, pActor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IRigidModel *CSimulationWorld::CreateMap( Renderer::Object::IMapModel *pMap )
{
	if ( (pMap == NULL) || pMap->IsInvalid() )
	{
		return NULL;
	}

	SRigidVertex *pVtx = NULL;
	SRigidIndex *pIdx = NULL;
	Sint32 VertexCount = 0;
	Sint32 IndexCount = 0;
	CRigidBody *pRigid = NULL;
	CRigidModel *pRigidModel = NULL;

	// �f�[�^�擾
	Renderer::Object::CMapModel *pModelData = (Renderer::Object::CMapModel*)pMap;
	Sint32 Count = pModelData->GetCollisionCount();
	pRigidModel = new CRigidModel( Count );
	for ( Sint32 i = 0; i < Count; i++ )
	{
		Renderer::CCollision *pCollision = pModelData->Collision_GetPointer( i );
		Sint32 VertexOffset = 0;
		Sint32 IndexOffset = 0;

		// �v���~�e�B�u��
		VertexCount = pCollision->GetVertexCount();
		IndexCount = pCollision->GetPolygonCount() * 3;

		// �i�[�p�o�b�t�@
		pVtx = new SRigidVertex [ VertexCount ];
		pIdx = new SRigidIndex [ IndexCount / 3 ];

		for ( Sint32 j = 0; j < IndexCount / 3; j++ )
		{
			pIdx[IndexOffset].Index[0] = pCollision->GetFace( j ).Index[0];
			pIdx[IndexOffset].Index[1] = pCollision->GetFace( j ).Index[1];
			pIdx[IndexOffset].Index[2] = pCollision->GetFace( j ).Index[2];
			IndexOffset++;
		}
		for ( Sint32 j = 0; j < VertexCount; j++ )
		{
			pVtx[VertexOffset].Position[0] = pCollision->GetVertex( j ).Position.x;
			pVtx[VertexOffset].Position[1] = pCollision->GetVertex( j ).Position.y;
			pVtx[VertexOffset].Position[2] = pCollision->GetVertex( j ).Position.z;
			pVtx[VertexOffset].Position[3] = 1.0f;
			VertexOffset++;
		}

		// �C���^�[�t�F�C�X����
		pRigid = CreateMesh( 0.0f, pVtx, VertexCount, pIdx, IndexCount, false );

		// �W�I���g���f�[�^������Ă���
		pRigid->SetGeometry( pVtx, pIdx );

		// �}�b�v�ł���
		pRigid->SetType( BODY_TYPE_MAP );

		// �ݒ�
		pRigidModel->Set( i, pRigid );
	}

	return pRigidModel;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
IRigidModel *CSimulationWorld::CreateModel( Renderer::Object::IModel *pModel, Bool IsBody )
{
	if ( (pModel == NULL) || pModel->IsInvalid() )
	{
		return NULL;
	}

	SRigidVertex *pVtx = NULL;
	SRigidIndex *pIdx = NULL;
	Sint32 VertexCount = 0;
	Sint32 IndexCount = 0;
	CRigidBody *pRigid = NULL;
	CRigidModel *pRigidModel = NULL;

	// �f�[�^�擾
	Renderer::Object::CModel *pModelData = (Renderer::Object::CModel*)pModel;
	Sint32 Count = pModelData->GetMeshCount();
	pRigidModel = new CRigidModel( Count );
	for ( Sint32 i = 0; i < Count; i++ )
	{
		Renderer::Object::CMesh *pMesh = pModelData->GetMesh( i );
		Renderer::CCollision *pCollision = pMesh->GetCollision();

		Sint32 VertexOffset = 0;
		Sint32 IndexOffset = 0;

		// �v���~�e�B�u��
		VertexCount = pCollision->GetVertexCount();
		IndexCount = pCollision->GetPolygonCount() * 3;

		// �i�[�p�o�b�t�@
		pVtx = new SRigidVertex [ VertexCount ];
		pIdx = new SRigidIndex [ IndexCount / 3 ];

		for ( Sint32 j = 0; j < IndexCount / 3; j++ )
		{
			pIdx[IndexOffset].Index[0] = pCollision->GetFace( j ).Index[0];
			pIdx[IndexOffset].Index[1] = pCollision->GetFace( j ).Index[1];
			pIdx[IndexOffset].Index[2] = pCollision->GetFace( j ).Index[2];
			IndexOffset++;
		}
		for ( Sint32 j = 0; j < VertexCount; j++ )
		{
			pVtx[VertexOffset].Position[0] = pCollision->GetVertex( j ).Position.x;
			pVtx[VertexOffset].Position[1] = pCollision->GetVertex( j ).Position.y;
			pVtx[VertexOffset].Position[2] = pCollision->GetVertex( j ).Position.z;
			pVtx[VertexOffset].Position[3] = 1.0f;
			VertexOffset++;
		}

		// �C���^�[�t�F�C�X����
		pRigid = CreateMesh( 0.0f, pVtx, VertexCount, pIdx, IndexCount, IsBody );

		// �W�I���g���f�[�^������Ă���
		pRigid->SetGeometry( pVtx, pIdx );

		// �}�b�v�ł���
		pRigid->SetType( BODY_TYPE_MODEL );

		// �ݒ�
		pRigidModel->Set( i, pRigid );
	}

	return pRigidModel;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRigidBody *CSimulationWorld::CreateMesh( Float fMass, SRigidVertex *pVtx, Sint32 VertexCount, SRigidIndex *pIdx, Sint32 IndexCount, Bool IsBody )
{
	dBodyID Body = 0;
	dGeomID Geom = 0;
	dTriMeshDataID Data = 0;

	// ���b�V���𐶐�
	Data = dGeomTriMeshDataCreate();
	dGeomTriMeshDataBuildSingle(
		Data, 
		&pVtx[0].Position,
		sizeof(SRigidVertex),
		VertexCount,
		&pIdx[0].Index[0],
		IndexCount,
		sizeof(SRigidIndex) );
	Geom = dCreateTriMesh( m_Space, Data, 0, 0, 0 );

	// �֘A�t��
	if ( IsBody )
	{
		Body = dBodyCreate( m_World );
		dGeomSetBody( Geom, Body );
		// ����
		dMass Mass;
		dMassSetZero( &Mass );
		dMassSetTrimeshTotal( &Mass, fMass, Geom );
		dGeomSetPosition( Geom, -Mass.c[0], -Mass.c[1], -Mass.c[2] );
		dMassTranslate( &Mass, -Mass.c[0], -Mass.c[1], -Mass.c[2]); 
		dBodySetMass( Body, &Mass );
	}

	// �C���^�[�t�F�C�X����
	return new CRigidBody( this, m_World, Body, Geom, Data, NULL );
}
