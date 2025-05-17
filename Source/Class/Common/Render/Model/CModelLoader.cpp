

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/File/CFileManager.h"
#include "Class/Common/Render/Model/CModel.h"
#include "Class/Common/Render/Model/CModelLoader.h"
#include "Class/Common/Render/Model/CAnimationController.h"
#include "Class/Common/Render/Model/CAnimationData.h"
#include "Class/Common/Render/Model/CFrame.h"
#include "Class/Common/Render/Model/CMesh.h"
#include "Class/Common/Render/Model/CMaterial.h"
#include "Class/Platform/Surface/CTexture.h"
#include "Math/Interpolation.h"
#include "Common/SMF.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Renderer;
using namespace Object;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CModelLoader::CModelLoader( CModel *pModel, CRender *pRender )
{
	m_pModel = pModel;
	m_pModel->AddRef();

	m_pRender = pRender;
	m_pRender->AddRef();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CModelLoader::~CModelLoader()
{
	SAFE_RELEASE( m_pModel );
	SAFE_RELEASE( m_pRender );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModelLoader::LoadFromMemory( const Uint8 *pData, Sint32 Size )
{
	Sint32 Pos						= 0;
	Sint32 AnimationControllerNo	= 0;
	Sint32 FrameNo					= 0;
	Sint32 MeshNo					= 0;

	//--------------------------------------------------------------------
	// �f�[�^�擾���[�v
	//--------------------------------------------------------------------
	while ( Pos < Size )
	{
		// �`�����N�擾
		const SMF_CHUNK *pChunk = (const SMF_CHUNK*)pData;
		pData += sizeof(SMF_CHUNK);
		Pos += sizeof(SMF_CHUNK);

		// �`�����N���
		switch ( pChunk->Chunk )
		{
		case 'SMF':  //------------------------------------ �t�@�C���w�b�_
			if ( !Load_SMF( pData, pChunk->Size ) )
			{
				return false;
			}
			MeshNo = 0;
			break;
		case 'FRM':  //------------------------------------ �t���[��
			Load_FRM( pData, pChunk->Size, FrameNo++ );
			break;
		case 'ANIS': //------------------------------------ �A�j���[�V�����Z�b�g
			Load_ANIS( pData, pChunk->Size, AnimationControllerNo++ );
			break;
		case 'MESH': //------------------------------------ ���b�V��
			Load_MESH( pData, pChunk->Size, MeshNo++ );
			break;
		}

		// �`�����N�T�C�Y���i�߂�
		pData += pChunk->Size;
		Pos += pChunk->Size;
	}

	//--------------------------------------------------------------------
	// ���b�V���̃A�b�v�f�[�g
	//--------------------------------------------------------------------
	m_pModel->UpdateMesh();

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModelLoader::SceneSkydoom_Create( Float fRadius, CColor TopColor, CColor BottomColor )
{
	CFrame *pFrame;
	CMesh *pMesh;

	//--------------------------------------------------------------
	// ���b�V���ƃt���[���𐶐�
	//--------------------------------------------------------------
	m_pModel->CreateFrameList( 1 );
	m_pModel->CreateMeshList( 1 );

	//--------------------------------------------------------------
	// �t���[���ݒ�
	//--------------------------------------------------------------
	pFrame = m_pModel->GetFramePointer( 0L );
	pMesh = m_pModel->GetMeshPointer( 0L );

	// ����
	pFrame->SetName( "Frame_SKYDOOM" );
	pMesh->SetName( "Mesh_SKYDOOM" );

	// ���b�V���̐ݒ�
	pMesh->SetParentFrame( pFrame );
	pMesh->CreateMaterialList( 1 );

	//--------------------------------------------------------------
	// �V�����b�V������
	//--------------------------------------------------------------
	{
		SVertex3DBase v1;

		Float fHeight	= fRadius;
		Sint32 Stacks	= 32;
		Sint32 Slices	= 32;
		Sint32 VtxCnt	= (Stacks + 1) * Slices;
		Sint32 IdxCnt	= (Slices - 1) * Stacks * 6;

		// OBB
		Collision::CBox Box;
		Box.CreateBox(
				Math::Vector3D( -fRadius,     0.0f, -fRadius ),
				Math::Vector3D( +fRadius, +fHeight, +fRadius ),
				Math::Matrix::GetIdentity() );
		pMesh->SetBounding( Box );

		// ���_���쐬����
		pMesh->CreateVertex( VERTEX_ELEMENT_3DBASE, VtxCnt );
		pMesh->CreateIndex( IdxCnt );

		// ���_�f�[�^�̐���
		pMesh->LockVertex( VERTEX_ELEMENT_3DBASE );

		for ( Sint32 i = 0; i < Slices; i++ )
		{
			for ( Sint32 j = 0; j < Stacks+1; j++ )
			{
				Math::Vector3D Vertex( 0.0f, 1.0f, 0.0f );
				Vertex.TransformNormal( Math::Matrix::GetRotationX( DEG_TO_ANGLE( 120 * i / Slices ) ) );
				Vertex.TransformNormal( Math::Matrix::GetRotationY( DEG_TO_ANGLE( 360 * j / Stacks ) ) );

				v1.Pos.x = Vertex.x * fRadius;
				v1.Pos.y = Vertex.y * fHeight;
				v1.Pos.z = Vertex.z * fRadius;
				v1.Col.a = 0xFF;
				v1.Col.r = Interpolation::Sub( BottomColor.r, TopColor.r, 1.0f, Vertex.y < 0.0f ? 0.0f : Vertex.y );
				v1.Col.g = Interpolation::Sub( BottomColor.g, TopColor.g, 1.0f, Vertex.y < 0.0f ? 0.0f : Vertex.y );
				v1.Col.b = Interpolation::Sub( BottomColor.b, TopColor.b, 1.0f, Vertex.y < 0.0f ? 0.0f : Vertex.y );

				pMesh->Push( &v1, 1 );
			}
		}
		pMesh->UnLockVertex( VERTEX_ELEMENT_3DBASE );

		// �C���f�b�N�X�f�[�^�̐���
		pMesh->LockIndex();
		Sint32 Num = 0;
		for ( Sint32 i = 1; i < Slices; i++ )
		{
			for ( Sint32 j = 0; j < Stacks; j++ )
			{
				Uint16 Idx[] = {
					(Uint16)(Num + 0),
					(Uint16)(Num + 1),
					(Uint16)(Num + Stacks + 1),
					(Uint16)(Num + 1),
					(Uint16)(Num + Stacks + 2),
					(Uint16)(Num + Stacks + 1),
				};
				pMesh->Push( Idx, 6 );

				Num++;
			}

			Num++;
		}
		pMesh->UnLockIndex();

		//--------------------------------------------------------------
		// �}�e���A��
		//--------------------------------------------------------------
		CMaterial *pMtrl;
		pMesh->GetMaterial( 0, pMtrl );
		// �F
		pMtrl->SetDiffuseColor( Math::Vector4D(1.0f,1.0f,1.0f,1.0f ) );
		// �C���f�b�N�X
		pMtrl->SetIndexStart( 0 );
		pMtrl->SetIndexCount( IdxCnt );
		// �o�[�e�b�N�X
		pMtrl->SetVertexStart( 0 );
		pMtrl->SetVertexCount( VtxCnt );
		// �X�e�[�g
		pMtrl->SetDrawType( DRAW_TYPE_NORMAL );
		pMtrl->SetCullType( CULL_FRONT );
		pMtrl->SetAlphaTestEnable( false );
		pMtrl->SetAlphaBoundary( 0 );
		pMtrl->SetDepthTestEnable( false );
		pMtrl->SetDepthWriteEnable( false );
		pMtrl->SetLightEnable( false );
		// �ݒ�
		SAFE_RELEASE( pMtrl );
	}

	//--------------------------------------------------------------
	// ���b�V���̃A�b�v�f�[�g
	//--------------------------------------------------------------
	m_pModel->UpdateMesh();

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModelLoader::SceneSkydoomWithCloud_Create( Float fRadius, CColor TopColor, CColor BottomColor, ITexture *pTexCloud )
{
	CFrame *pFrame0, *pFrame1, *pFrame2;
	CMesh *pMesh0, *pMesh1;

	//--------------------------------------------------------------
	// ���b�V���ƃt���[���𐶐�
	//--------------------------------------------------------------
	m_pModel->CreateFrameList( 3 );
	m_pModel->CreateMeshList( 2 );

	//--------------------------------------------------------------
	// �t���[���ݒ�
	//--------------------------------------------------------------
	pFrame0 = m_pModel->GetFramePointer( 0L );
	pFrame1 = m_pModel->GetFramePointer( 1L );
	pFrame2 = m_pModel->GetFramePointer( 2L );
	pMesh0 = m_pModel->GetMeshPointer( 1L );
	pMesh1 = m_pModel->GetMeshPointer( 0L );

	// ����
	pFrame0->SetName( "Frame_ROOT" );
	pFrame1->SetName( "Frame_SKYDOOM" );
	pFrame2->SetName( "Frame_CLOUD" );
	pMesh0->SetName( "Mesh_SKYDOOM" );
	pMesh1->SetName( "Mesh_CLOUD" );

	// �t���[���̐ݒ�
	pFrame0->ConnectChildFrame( pFrame1 );
	pFrame0->ConnectChildFrame( pFrame2 );

	// ���b�V���̐ݒ�
	pMesh0->SetParentFrame( pFrame0 );
	pMesh0->CreateMaterialList( 1 );
	pMesh1->SetParentFrame( pFrame1 );
	pMesh1->CreateMaterialList( 1 );

	//--------------------------------------------------------------
	// �V�����b�V������
	//--------------------------------------------------------------
	{
		SVertex3DBase v1;

		Float fHeight	= fRadius;
		Sint32 Stacks	= 16;
		Sint32 Slices	= 8;
		Sint32 VtxCnt	= (Stacks + 1) * Slices;
		Sint32 IdxCnt	= (Slices - 1) * Stacks * 6;

		// OBB
		Collision::CBox Box;
		Box.CreateBox(
				Math::Vector3D( -fRadius,     0.0f, -fRadius ),
				Math::Vector3D( +fRadius, +fHeight, +fRadius ),
				Math::Matrix::GetIdentity() );
		pMesh0->SetBounding( Box );

		// ���_���쐬����
		pMesh0->CreateVertex( VERTEX_ELEMENT_3DBASE, VtxCnt );
		pMesh0->CreateIndex( IdxCnt );

		// ���_�f�[�^�̐���
		pMesh0->LockVertex( VERTEX_ELEMENT_3DBASE );

		for ( Sint32 i = 0; i < Slices; i++ )
		{
			for ( Sint32 j = 0; j < Stacks+1; j++ )
			{
				Math::Vector3D Vertex( 0.0f, 1.0f, 0.0f );
				Vertex.TransformNormal( Math::Matrix::GetRotationX( DEG_TO_ANGLE( 120 * i / Slices ) ) );
				Vertex.TransformNormal( Math::Matrix::GetRotationY( DEG_TO_ANGLE( 360 * j / Stacks ) ) );

				v1.Pos.x = Vertex.x * fRadius;
				v1.Pos.y = Vertex.y * fHeight;
				v1.Pos.z = Vertex.z * fRadius;
				v1.Col.a = 0xFF;
				v1.Col.r = Interpolation::Sub( BottomColor.r, TopColor.r, 1.0f, Vertex.y < 0.0f ? 0.0f : Vertex.y );
				v1.Col.g = Interpolation::Sub( BottomColor.g, TopColor.g, 1.0f, Vertex.y < 0.0f ? 0.0f : Vertex.y );
				v1.Col.b = Interpolation::Sub( BottomColor.b, TopColor.b, 1.0f, Vertex.y < 0.0f ? 0.0f : Vertex.y );

				pMesh0->Push( &v1, 1 );
			}
		}
		pMesh0->UnLockVertex( VERTEX_ELEMENT_3DBASE );

		// �C���f�b�N�X�f�[�^�̐���
		pMesh0->LockIndex();
		Sint32 Num = 0;
		for ( Sint32 i = 1; i < Slices; i++ )
		{
			for ( Sint32 j = 0; j < Stacks; j++ )
			{
				Uint16 Idx[] = {
					(Uint16)(Num + 0),
					(Uint16)(Num + 1),
					(Uint16)(Num + Stacks + 1),
					(Uint16)(Num + 1),
					(Uint16)(Num + Stacks + 2),
					(Uint16)(Num + Stacks + 1),
				};
				pMesh0->Push( Idx, 6 );

				Num++;
			}

			Num++;
		}
		pMesh0->UnLockIndex();

		//--------------------------------------------------------------
		// �}�e���A��
		//--------------------------------------------------------------
		CMaterial *pMtrl;
		pMesh0->GetMaterial( 0, pMtrl );
		// �F
		pMtrl->SetDiffuseColor( Math::Vector4D(1.0f,1.0f,1.0f,1.0f ) );
		// �C���f�b�N�X
		pMtrl->SetIndexStart( 0 );
		pMtrl->SetIndexCount( IdxCnt );
		// �o�[�e�b�N�X
		pMtrl->SetVertexStart( 0 );
		pMtrl->SetVertexCount( VtxCnt );
		// �X�e�[�g
		pMtrl->SetDrawType( DRAW_TYPE_NORMAL );
		pMtrl->SetCullType( CULL_FRONT );
		pMtrl->SetAlphaTestEnable( false );
		pMtrl->SetAlphaBoundary( 0 );
		pMtrl->SetDepthTestEnable( false );
		pMtrl->SetDepthWriteEnable( false );
		pMtrl->SetLightEnable( false );
		// �ݒ�
		SAFE_RELEASE( pMtrl );
	}

	//--------------------------------------------------------------
	// �_���b�V������
	//--------------------------------------------------------------
	{
		SVertex3DBase v1;
		SVertex3DTexture v2;

		Float fHeight	= fRadius * 0.3f;
		Sint32 Stacks	= 16;
		Sint32 Slices	= 8;
		Sint32 VtxCnt	= (Stacks + 1) * Slices;
		Sint32 IdxCnt	= (Slices - 1) * Stacks * 6;

		// OBB
		Collision::CBox Box;
		Box.CreateBox(
				Math::Vector3D( -fRadius,     0.0f, -fRadius ),
				Math::Vector3D( +fRadius, +fHeight, +fRadius ),
				Math::Matrix::GetIdentity() );
		pMesh1->SetBounding( Box );

		// ���_���쐬����
		pMesh1->CreateVertex( VERTEX_ELEMENT_3DBASE, VtxCnt );
		pMesh1->CreateVertex( VERTEX_ELEMENT_3DTEXTURE, VtxCnt );
		pMesh1->CreateIndex( IdxCnt );

		// ���_�f�[�^�̐���
		pMesh1->LockVertex( VERTEX_ELEMENT_3DBASE );
		pMesh1->LockVertex( VERTEX_ELEMENT_3DTEXTURE );

		for ( Sint32 i = 0; i < Slices; i++ )
		{
			for ( Sint32 j = 0; j < Stacks+1; j++ )
			{
				Math::Vector3D Vertex( 0.0f, 1.0f, 0.0f );
				Vertex.TransformNormal( Math::Matrix::GetRotationX( DEG_TO_ANGLE( 120 * i / Slices ) ) );
				Vertex.TransformNormal( Math::Matrix::GetRotationY( DEG_TO_ANGLE( 360 * j / Stacks ) ) );

				v1.Pos.x = Vertex.x * fRadius;
				v1.Pos.y = Vertex.y * fHeight + (fHeight / 3.0f);
				v1.Pos.z = Vertex.z * fRadius;
				v1.Col.r = 0xFF;
				v1.Col.g = 0xFF;
				v1.Col.b = 0xFF;
				v1.Col.a = 0xFF;
				if ( i == Slices - 1 )
				{
					v1.Col.a = 0x00;
				}

				pMesh1->Push( &v1, 1 );

				Math::Vector3D vUV( 0.0f, 0.0f, -1.0f );
				vUV.TransformNormal( Math::Matrix::GetRotationY( DEG_TO_ANGLE( 360 * j / Stacks ) ) );

				v2.TexColor.x = vUV.x * (toF(i) / toF(Slices));
				v2.TexColor.y = vUV.z * (toF(i) / toF(Slices));
				v2.TexLight = v2.TexColor;

				pMesh1->Push( &v2, 1 );
			}
		}
		pMesh1->UnLockVertex( VERTEX_ELEMENT_3DBASE );
		pMesh1->UnLockVertex( VERTEX_ELEMENT_3DTEXTURE );

		// �C���f�b�N�X�f�[�^�̐���
		pMesh1->LockIndex();
		Sint32 Num = 0;
		for ( Sint32 i = 1; i < Slices; i++ )
		{
			for ( Sint32 j = 0; j < Stacks; j++ )
			{
				Uint16 Idx[] = {
					(Uint16)(Num + 0),
					(Uint16)(Num + 1),
					(Uint16)(Num + Stacks + 1),
					(Uint16)(Num + 1),
					(Uint16)(Num + Stacks + 2),
					(Uint16)(Num + Stacks + 1),
				};
				pMesh1->Push( Idx, 6 );

				Num++;
			}

			Num++;
		}
		pMesh1->UnLockIndex();

		//--------------------------------------------------------------
		// �}�e���A��
		//--------------------------------------------------------------
		CMaterial *pMtrl;
		pMesh1->GetMaterial( 0, pMtrl );
		// �F
		pMtrl->SetDiffuseColor( Math::Vector4D(1.0f,1.0f,1.0f,1.0f ) );
		// �C���f�b�N�X
		pMtrl->SetIndexStart( 0 );
		pMtrl->SetIndexCount( IdxCnt );
		// �o�[�e�b�N�X
		pMtrl->SetVertexStart( 0 );
		pMtrl->SetVertexCount( VtxCnt );
		// �X�e�[�g
		pMtrl->SetDrawType( DRAW_TYPE_BLEND );
		pMtrl->SetCullType( CULL_FRONT );
		pMtrl->SetAlphaTestEnable( false );
		pMtrl->SetAlphaBoundary( 0 );
		pMtrl->SetDepthTestEnable( false );
		pMtrl->SetDepthWriteEnable( false );
		pMtrl->SetLightEnable( false );
		// �e�N�X�`��
		pMtrl->SetTexture( TEXTURE_STAGE_COLOR, pTexCloud );
		// �ݒ�
		SAFE_RELEASE( pMtrl );
	}

	//--------------------------------------------------------------
	// ���b�V���̃A�b�v�f�[�g
	//--------------------------------------------------------------
	m_pModel->UpdateMesh();

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CModelLoader::Load_SMF( const Uint8 *pData, Sint32 Size )
{
	SMF_FILEHEAD Head;
	MemoryCopy( &Head, pData, sizeof(SMF_FILEHEAD) );

	if ( Head.Guid != SMF_VERSION_GUID )
	{
		return false;
	}

	// ���b�V���ƃt���[���𐶐�
	m_pModel->CreateFrameList( Head.FrameCount );
	m_pModel->CreateMeshList( Head.MeshCount );
	m_pModel->CreateAnimationController( Head.AnimationSetCount );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_FRM( const Uint8 *pData, Sint32 Size, Sint32 FrameNo )
{
	SMF_FRAMEDATA Frame;
	MemoryCopy( &Frame, pData, sizeof(SMF_FRAMEDATA) );
	pData += sizeof(SMF_FRAMEDATA);

	CFrame *pFrame = m_pModel->GetFramePointer( FrameNo );
	// ����
	pFrame->SetName( Frame.Name );
	// �g�����X�t�H�[���}�g���b�N�X
	Math::Matrix mTemp(
				Frame.mTransform.x.x, Frame.mTransform.x.y, Frame.mTransform.x.z, Frame.mTransform.x.w,
				Frame.mTransform.y.x, Frame.mTransform.y.y, Frame.mTransform.y.z, Frame.mTransform.y.w,
				Frame.mTransform.z.x, Frame.mTransform.z.y, Frame.mTransform.z.z, Frame.mTransform.z.w,
				Frame.mTransform.w.x, Frame.mTransform.w.y, Frame.mTransform.w.z, Frame.mTransform.w.w );
	pFrame->SetDefaultLocalMatrix( mTemp );
	// ���b�V��
	if ( Frame.MeshNo != -1 )
	{
		m_pModel->GetMeshPointer( Frame.MeshNo )->SetParentFrame( pFrame );
	}
	// �t���[��
	if ( Frame.ParentFrameNo != -1 )
	{
		m_pModel->GetFramePointer( Frame.ParentFrameNo )->ConnectChildFrame( pFrame );
		pFrame->SetParentFrameNo( Frame.ParentFrameNo );
	}

	// �T�u�`�����N
	Sint32 Pos = sizeof(SMF_FRAMEDATA);
	while ( Pos < Size )
	{
		const SMF_CHUNK *pChunk = (const SMF_CHUNK*)pData;
		pData += sizeof(SMF_CHUNK);
		Pos += sizeof(SMF_CHUNK);

		switch ( pChunk->Chunk )
		{
		case 'OBB':  //-------------------- �o�E���f�B���O
			Load_OBB( pData, pChunk->Size, pFrame );
			break;
		}

		// �`�����N�T�C�Y���i�߂�
		pData += pChunk->Size;
		Pos += pChunk->Size;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_OBB( const Uint8 *pData, Sint32 Size, CFrame *pFrame )
{
	SMF_OBBDATA OBB;
	MemoryCopy( &OBB, pData, sizeof(SMF_OBBDATA) );

	// �o�E���f�B���O
	Collision::CBox Bound;
	Math::Vector3D vCenter( OBB.vCenter.x, OBB.vCenter.y, OBB.vCenter.z );
	Math::Vector3D vAxis[] = {
		Math::Vector3D( OBB.vAxis[0].x, OBB.vAxis[0].y, OBB.vAxis[0].z ),
		Math::Vector3D( OBB.vAxis[1].x, OBB.vAxis[1].y, OBB.vAxis[1].z ),
		Math::Vector3D( OBB.vAxis[2].x, OBB.vAxis[2].y, OBB.vAxis[2].z ),
	};
	Bound.UpdatePoints( vCenter, vAxis, OBB.fLength );
	pFrame->SetBounding( Bound );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_ANIS( const Uint8 *pData, Sint32 Size, Sint32 AnimationControllerNo )
{
	SMF_ANIMATIONSETDATA AnimationSet;
	MemoryCopy( &AnimationSet, pData, sizeof(SMF_ANIMATIONSETDATA) );
	pData += sizeof(SMF_ANIMATIONSETDATA);

	CAnimationController *pAnimationController = m_pModel->GetAnimationControllerPointer( AnimationControllerNo );
	// ����
	pAnimationController->SetName( AnimationSet.Name );
	// �A�j���[�V������
	pAnimationController->CreateAnimationData( AnimationSet.AnimationCount );
	// ����
	pAnimationController->SetLastTime( toF(AnimationSet.LastTime) );

	//-----------------------------------------------------------
	// �`�����N���
	//-----------------------------------------------------------
	Sint32 CAnimationDataNo = 0;
	Sint32 Pos = sizeof(SMF_ANIMATIONSETDATA);
	while ( Pos < Size )
	{
		const SMF_CHUNK *pChunk = (const SMF_CHUNK*)pData;
		pData += sizeof(SMF_CHUNK);
		Pos += sizeof(SMF_CHUNK);

		switch ( pChunk->Chunk )
		{
		case 'ANI':  //-------------------- �A�j���[�V�����f�[�^
			Load_ANI( pData, pChunk->Size, AnimationControllerNo, pAnimationController->GetCAnimationDataPointer( CAnimationDataNo++ ) );
			break;
		}

		// �`�����N�T�C�Y���i�߂�
		pData += pChunk->Size;
		Pos += pChunk->Size;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_ANI( const Uint8 *pData, Sint32 Size, Sint32 CAnimationControllerNo, CAnimationData *pAnimationData )
{
	SMF_ANIMATIONDATA Animation;
	MemoryCopy( &Animation, pData, sizeof(SMF_ANIMATIONDATA) );
	pData += sizeof(SMF_ANIMATIONDATA);

	// �^�[�Q�b�g
	CFrame *pFrame = m_pModel->GetFramePointer( Animation.TargetFrame );
	pFrame->SetAnimationData( CAnimationControllerNo, pAnimationData );

	// �g��k��
	pAnimationData->SetScaleKey( (const SMF_ANIMATIONKEY_SCALE*)pData, Animation.KeyMaxScale );
	pData += sizeof(SMF_ANIMATIONKEY_SCALE) * Animation.KeyMaxScale;

	// ��]
	pAnimationData->SetRotateKey( (const SMF_ANIMATIONKEY_ROTATE*)pData, Animation.KeyMaxRotate );
	pData += sizeof(SMF_ANIMATIONKEY_ROTATE) * Animation.KeyMaxRotate;

	// �ړ�
	pAnimationData->SetTranslateKey( (const SMF_ANIMATIONKEY_TRANSLATE*)pData, Animation.KeyMaxTranslate );
	pData += sizeof(SMF_ANIMATIONKEY_TRANSLATE) * Animation.KeyMaxTranslate;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_MESH( const Uint8 *pData, Sint32 Size, Sint32 MeshNo )
{
	SMF_MESHDATA Mesh;
	MemoryCopy( &Mesh, pData, sizeof(SMF_MESHDATA) );
	pData += sizeof(SMF_MESHDATA);

	CMesh *pMesh = m_pModel->GetMeshPointer( MeshNo );
	// ����
	pMesh->SetName( Mesh.Name );
	// �}�e���A��
	pMesh->CreateMaterialList( Mesh.MaterialCount );

	//-----------------------------------------------------------
	// �`�����N���
	//-----------------------------------------------------------
	Sint32 MaterialNo = 0;
	Sint32 Pos = sizeof(SMF_MESHDATA);
	while ( Pos < Size )
	{
		const SMF_CHUNK *pChunk = (const SMF_CHUNK*)pData;
		pData += sizeof(SMF_CHUNK);
		Pos += sizeof(SMF_CHUNK);

		switch ( pChunk->Chunk )
		{
		case 'OBB':  //------------------------------------ �o�E���f�B���O
			Load_OBB( pData, pChunk->Size, pMesh );
			break;
		case 'BONE': //------------------------------------ �{�[��
			Load_BONE( pData, pChunk->Size, pMesh );
			break;
		case 'V_PC': //------------------------------------ ���_�F�ʒu�{�F
			Load_V_PC( pData, pChunk->Size, pMesh );
			break;
		case 'V_N':  //------------------------------------ ���_�F�@��
			Load_V_N( pData, pChunk->Size, pMesh );
			break;
		case 'V_B':  //------------------------------------ ���_�F�ڐ�
			Load_V_B( pData, pChunk->Size, pMesh );
			break;
		case 'V_A':  //------------------------------------ ���_�F�E�F�C�g�{�C���f�b�N�X
			Load_V_A( pData, pChunk->Size, pMesh );
			break;
		case 'V_UV': //------------------------------------ ���_�F�e�N�X�`��UV
			Load_V_UV( pData, pChunk->Size, pMesh );
			break;
		case 'IDX2': //------------------------------------ �C���f�b�N�X
			Load_IDX2( pData, pChunk->Size, pMesh );
			break;
		case 'IDX4': //------------------------------------ �C���f�b�N�X
			Load_IDX4( pData, pChunk->Size, pMesh );
			break;
		case 'C_AT': //------------------------------------ �R���W���������f�[�^
			Load_C_AT( pData, pChunk->Size, pMesh );
			break;
		case 'C_FC': //------------------------------------ �R���W�����ʃf�[�^
			Load_C_FC( pData, pChunk->Size, pMesh );
			break;
		case 'C_VX': //------------------------------------ �R���W�������_�f�[�^
			Load_C_VX( pData, pChunk->Size, pMesh );
			break;
		case 'MTRL': //------------------------------------ �}�e���A��
			Load_MTRL( pData, pChunk->Size, pMesh, MaterialNo++ );
			break;
		}

		// �`�����N�T�C�Y���i�߂�
		pData += pChunk->Size;
		Pos += pChunk->Size;
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_OBB( const Uint8 *pData, Sint32 Size, CMesh *pMesh )
{
	SMF_OBBDATA OBB;
	MemoryCopy( &OBB, pData, sizeof(SMF_OBBDATA) );

	// �o�E���f�B���O
	Collision::CBox Bound;
	Math::Vector3D vCenter( OBB.vCenter.x, OBB.vCenter.y, OBB.vCenter.z );
	Math::Vector3D vAxis[] = {
		Math::Vector3D( OBB.vAxis[0].x, OBB.vAxis[0].y, OBB.vAxis[0].z ),
		Math::Vector3D( OBB.vAxis[1].x, OBB.vAxis[1].y, OBB.vAxis[1].z ),
		Math::Vector3D( OBB.vAxis[2].x, OBB.vAxis[2].y, OBB.vAxis[2].z ),
	};
	Bound.UpdatePoints( vCenter, vAxis, OBB.fLength );
	pMesh->SetBounding( Bound );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_BONE( const Uint8 *pData, Sint32 Size, CMesh *pMesh )
{
	Sint32 Count = Size / sizeof(SMF_BONEDATA);

	// �{�[����
	pMesh->SetBoneCount( Count );

	// �{�[���f�[�^
	const SMF_BONEDATA *pBone = (const SMF_BONEDATA*)pData;
	for ( Sint32 i = 0; i < Count; i++ )
	{
		// �I�t�Z�b�g
		Math::Matrix mOffset(
			pBone[i].mBoneOffset.x.x, pBone[i].mBoneOffset.x.y, pBone[i].mBoneOffset.x.z, pBone[i].mBoneOffset.x.w,
			pBone[i].mBoneOffset.y.x, pBone[i].mBoneOffset.y.y, pBone[i].mBoneOffset.y.z, pBone[i].mBoneOffset.y.w,
			pBone[i].mBoneOffset.z.x, pBone[i].mBoneOffset.z.y, pBone[i].mBoneOffset.z.z, pBone[i].mBoneOffset.z.w,
			pBone[i].mBoneOffset.w.x, pBone[i].mBoneOffset.w.y, pBone[i].mBoneOffset.w.z, pBone[i].mBoneOffset.w.w );
		// �ݒ�
		CFrame *pFrame = m_pModel->GetFramePointer( pBone[i].FrameNo );
		pFrame->SetBoneOffsetMatrix( mOffset );
		pMesh->SetBoneData( i, pFrame );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_V_PC( const Uint8 *pData, Sint32 Size, CMesh *pMesh )
{
	Sint32 Count = Size / sizeof(SVertex3DBase);

	pMesh->CreateVertex( VERTEX_ELEMENT_3DBASE, Count );
	pMesh->LockVertex( VERTEX_ELEMENT_3DBASE );
	pMesh->Push( (const SVertex3DBase*)pData, Count );
	pMesh->UnLockVertex( VERTEX_ELEMENT_3DBASE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_V_N( const Uint8 *pData, Sint32 Size, CMesh *pMesh )
{
	Sint32 Count = Size / sizeof(SVertex3DLight);

	pMesh->CreateVertex( VERTEX_ELEMENT_3DLIGHT, Count );
	pMesh->LockVertex( VERTEX_ELEMENT_3DLIGHT );
	pMesh->Push( (const SVertex3DLight*)pData, Count );
	pMesh->UnLockVertex( VERTEX_ELEMENT_3DLIGHT );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_V_B( const Uint8 *pData, Sint32 Size, CMesh *pMesh )
{
	Sint32 Count = Size / sizeof(SVertex3DBump);

	pMesh->CreateVertex( VERTEX_ELEMENT_3DBUMP, Count );
	pMesh->LockVertex( VERTEX_ELEMENT_3DBUMP );
	pMesh->Push( (const SVertex3DBump*)pData, Count );
	pMesh->UnLockVertex( VERTEX_ELEMENT_3DBUMP );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_V_A( const Uint8 *pData, Sint32 Size, CMesh *pMesh )
{
	Sint32 Count = Size / sizeof(SVertex3DAnimation);

	pMesh->CreateVertex( VERTEX_ELEMENT_3DANIMATION, Count );
	pMesh->LockVertex( VERTEX_ELEMENT_3DANIMATION );
	pMesh->Push( (const SVertex3DAnimation*)pData, Count );
	pMesh->UnLockVertex( VERTEX_ELEMENT_3DANIMATION );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_V_UV( const Uint8 *pData, Sint32 Size, CMesh *pMesh )
{
	Sint32 Count = Size / sizeof(SVertex3DTexture);

	pMesh->CreateVertex( VERTEX_ELEMENT_3DTEXTURE, Count );
	pMesh->LockVertex( VERTEX_ELEMENT_3DTEXTURE );
	pMesh->Push( (const SVertex3DTexture*)pData, Count );
	pMesh->UnLockVertex( VERTEX_ELEMENT_3DTEXTURE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_IDX2( const Uint8 *pData, Sint32 Size, CMesh *pMesh )
{
	Sint32 Count = Size / sizeof(Uint16);

	pMesh->CreateIndex( Count );
	pMesh->LockIndex();
	pMesh->Push( pData, Count );
	pMesh->UnLockIndex();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_IDX4( const Uint8 *pData, Sint32 Size, CMesh *pMesh )
{
	Sint32 Count = Size / sizeof(Uint32);

	pMesh->CreateIndex( Count );
	pMesh->LockIndex();
	pMesh->Push( pData, Count );
	pMesh->UnLockIndex();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_C_AT( const Uint8 *pData, Sint32 Size, CMesh *pMesh )
{
	SMF_COLLISION_ATTRIBUTE *pAttr = (SMF_COLLISION_ATTRIBUTE*)pData;
	Sint32 Count = Size / sizeof(SMF_COLLISION_ATTRIBUTE);

	pMesh->CreateCollisionAttribute( (SCollisionAttribute*)pAttr, Count );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_C_FC( const Uint8 *pData, Sint32 Size, CMesh *pMesh )
{
	SMF_COLLISION_FACE *pFace = (SMF_COLLISION_FACE*)pData;
	Sint32 Count = Size / sizeof(SMF_COLLISION_FACE);

	pMesh->CreateCollisionFace( (SCollisionFace*)pFace, Count );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_C_VX( const Uint8 *pData, Sint32 Size, CMesh *pMesh )
{
	SMF_COLLISIONVERTEX *pVtx = (SMF_COLLISIONVERTEX*)pData;
	Sint32 Count = Size / sizeof(SMF_COLLISIONVERTEX);

	pMesh->CreateCollisionVertex( (SCollisionVertex*)pVtx, Count );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_MTRL( const Uint8 *pData, Sint32 Size, CMesh *pMesh, Sint32 MaterialNo )
{
	SMF_MATERIAL Mtrl;
	MemoryCopy( &Mtrl, pData, sizeof(SMF_MATERIAL) );
	pData += sizeof(SMF_MATERIAL);

	// �}�e���A��
	CMaterial *pMtrl;
	pMesh->GetMaterial( MaterialNo, pMtrl );

	// �C���f�b�N�X
	pMtrl->SetIndexStart( Mtrl.PolygonStart * 3 );
	pMtrl->SetIndexCount( Mtrl.PolygonCount * 3 );

	// �o�[�e�b�N�X
	pMtrl->SetVertexStart( Mtrl.VertexStart );
	pMtrl->SetVertexCount( Mtrl.VertexCount );

	//-----------------------------------------------------------
	// �`�����N���
	//-----------------------------------------------------------
	Sint32 Pos = sizeof(SMF_MATERIAL);
	while ( Pos < Size )
	{
		const SMF_CHUNK *pChunk = (const SMF_CHUNK*)pData;
		pData += sizeof(SMF_CHUNK);
		Pos += sizeof(SMF_CHUNK);

		switch ( pChunk->Chunk )
		{
		case 'TEXC': //------------------------------------ �e�N�X�`��
			Load_TEXC( pData, pChunk->Size, pMtrl);
			break;
		case 'TEXL': //------------------------------------ �e�N�X�`��
			Load_TEXL( pData, pChunk->Size, pMtrl );
			break;
		case 'TEXE': //------------------------------------ �e�N�X�`��
			Load_TEXE( pData, pChunk->Size, pMtrl );
			break;
		case 'TEXS': //------------------------------------ �e�N�X�`��
			Load_TEXS( pData, pChunk->Size, pMtrl );
			break;
		case 'TEXN': //------------------------------------ �e�N�X�`��
			Load_TEXN( pData, pChunk->Size, pMtrl );
			break;
		case 'DRAW': //------------------------------------ �`�惂�[�h
			Load_DRAW( pData, pChunk->Size, pMesh, pMtrl );
			break;
		case 'ZTES': //------------------------------------ Z�e�X�g
			Load_ZTES( pData, pChunk->Size, pMesh, pMtrl );
			break;
		case 'ZWRI': //------------------------------------ Z��������
			Load_ZWRI( pData, pChunk->Size, pMesh, pMtrl );
			break;
		case 'ATES': //------------------------------------ �A���t�@�e�X�g
			Load_ATES( pData, pChunk->Size, pMesh, pMtrl );
			break;
		case 'ABND': //------------------------------------ �A���t�@�e�X�g
			Load_ABND( pData, pChunk->Size, pMesh, pMtrl );
			break;
		case 'CULL': //------------------------------------ �J�����O
			Load_CULL( pData, pChunk->Size, pMesh, pMtrl );
		case 'LGT':  //------------------------------------ ���C�e�B���O
			Load_LGT( pData, pChunk->Size, pMesh, pMtrl );
			break;
		case 'DIFF': //------------------------------------ �g�U����
			Load_DIFF( pData, pChunk->Size, pMesh, pMtrl );
			break;
		case 'EMIS': //------------------------------------ ���Ȕ���
			Load_EMIS( pData, pChunk->Size, pMesh, pMtrl );
			break;
		case 'SPEC': //------------------------------------ �X�y�L����
			Load_SPEC( pData, pChunk->Size, pMesh, pMtrl );
			break;
		case 'BUMP': //------------------------------------ �o���v
			Load_BUMP( pData, pChunk->Size, pMesh, pMtrl );
			break;
		}

		// �`�����N�T�C�Y���i�߂�
		pData += pChunk->Size;
		Pos += pChunk->Size;
	}

	SAFE_RELEASE( pMtrl );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_TEXC( const Uint8 *pData, Sint32 Size, CMaterial *pMtrl )
{
	ITexture *pTex;
	pTex = m_pRender->CreateTextureFromFile( (const char *)pData );
	pMtrl->SetTexture( TEXTURE_STAGE_COLOR, pTex );
	SAFE_RELEASE( pTex );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_TEXL( const Uint8 *pData, Sint32 Size, CMaterial *pMtrl )
{
	ITexture *pTex;
	pTex = m_pRender->CreateTextureFromFile( (const char *)pData );
	pMtrl->SetTexture( TEXTURE_STAGE_LIGHT, pTex );
	SAFE_RELEASE( pTex );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_TEXE( const Uint8 *pData, Sint32 Size, CMaterial *pMtrl )
{
	ITexture *pTex;
	pTex = m_pRender->CreateCubeTextureFromFile( (const char *)pData );
	pMtrl->SetTexture( TEXTURE_STAGE_ENVIRONMENT, pTex );
	SAFE_RELEASE( pTex );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_TEXS( const Uint8 *pData, Sint32 Size, CMaterial *pMtrl )
{
	ITexture *pTex;
	pTex = m_pRender->CreateTextureFromFile( (const char *)pData );
	pMtrl->SetTexture( TEXTURE_STAGE_SPECULAR, pTex );
	SAFE_RELEASE( pTex );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_TEXN( const Uint8 *pData, Sint32 Size, CMaterial *pMtrl )
{
	ITexture *pTex;
	pTex = m_pRender->CreateTextureFromFile( (const char *)pData );
	pMtrl->SetTexture( TEXTURE_STAGE_NORMAL, pTex );
	SAFE_RELEASE( pTex );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_DRAW( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl )
{
	Sint32 DrawType;
	MemoryCopy( &DrawType, pData, sizeof(Sint32) );

	pMtrl->SetDrawType( (eDrawType)DrawType );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_ZTES( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl )
{
	Sint32 IsEnable;
	MemoryCopy( &IsEnable, pData, sizeof(Sint32) );

	pMtrl->SetDepthTestEnable( IsEnable != FALSE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_ZWRI( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl )
{
	Sint32 IsEnable;
	MemoryCopy( &IsEnable, pData, sizeof(Sint32) );

	pMtrl->SetDepthWriteEnable( IsEnable != FALSE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_ATES( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl )
{
	Sint32 IsEnable;
	MemoryCopy( &IsEnable, pData, sizeof(Sint32) );

	pMtrl->SetAlphaTestEnable( IsEnable != FALSE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_ABND( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl )
{
	Sint32 Bound;
	MemoryCopy( &Bound, pData, sizeof(Sint32) );

	pMtrl->SetAlphaBoundary( Bound );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_CULL( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl )
{
	Sint32 IsEnable;
	MemoryCopy( &IsEnable, pData, sizeof(Sint32) );

	pMtrl->SetCullType( IsEnable != 0 ? CULL_FRONT : CULL_NONE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_LGT( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl )
{
	Sint32 IsEnable;
	MemoryCopy( &IsEnable, pData, sizeof(Sint32) );

	pMtrl->SetLightEnable( IsEnable != 0 );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_DIFF( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl )
{
	SMF_VECTOR4 vDiffuse;
	MemoryCopy( &vDiffuse, pData, sizeof(SMF_VECTOR4) );

	Math::Vector4D vColor( vDiffuse.x, vDiffuse.y, vDiffuse.z, vDiffuse.w );
	pMtrl->SetDiffuseColor( vColor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_EMIS( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl )
{
	SMF_VECTOR3 vEmissive;
	MemoryCopy( &vEmissive, pData, sizeof(SMF_VECTOR3) );

	Math::Vector4D vColor( vEmissive.x, vEmissive.y, vEmissive.z, 0.0f );
	pMtrl->SetEmissiveColor( vColor );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_SPEC( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl )
{
	SMF_SPECULAR Spec;
	MemoryCopy( &Spec, pData, sizeof(SMF_SPECULAR) );

	Math::Vector4D vColor( Spec.vSpecular.x, Spec.vSpecular.y, Spec.vSpecular.z, 0.0f );

	pMtrl->SetSpecularColor( vColor );
	pMtrl->SetSpecularRoughly( Spec.fRoughly );
	pMtrl->SetSpecularRefractive( Spec.fRefractive );
	pMtrl->SetSpecularType( SPECULAR_TYPE_ENABLE );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CModelLoader::Load_BUMP( const Uint8 *pData, Sint32 Size, CMesh *pMesh, CMaterial *pMtrl )
{
	SMF_BUMPMAP Bump;
	MemoryCopy( &Bump, pData, sizeof(SMF_BUMPMAP) );

	pMtrl->SetParallaxDepth( Bump.fParallaxDepth );
	pMtrl->SetBumpmapMode( BUMP_TYPE_ENABLE );
}
