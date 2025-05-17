#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Interface/Render/Map/IMapModel.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �V�[���A�N�^�[�p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���Ǘ����ꂽ�I�u�W�F�N�g�������ׂ̃C���^�[�t�F�C�X�ł��B
	*/
	class IMapActor
	{
	public:
		virtual ~IMapActor() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`

			ISceneManager�ɑ΂��ă����_�����O���N�G�X�g�𔭍s���܂��B<BR>
			�擾����ISceneManager��Begin()/End()���łȂ��ꍇ���̊֐��͎��s���܂��B
		*/
		virtual void RenderingRequest( void ) = 0;

		/**
			@brief �J�����O�p�o�E���f�B���O�����_�����O
			@author �t���`
			@param pLine	[in] ���C���v���~�e�B�u�C���^�[�t�F�C�X

			�o�E���f�B���O�{�b�N�X���w�肵�����C���f�[�^�ɑ΂��Ēǉ����܂��B
		*/
		virtual void RenderingBounding( Renderer::Object::ILine3D *pLine ) = 0;

		/**
			@brief �Z���̑S�̐��擾
			@author �t���`
			@return �Z���̑S�̐�

			�}�b�v���̃Z���̐����擾���܂��B
		*/
		virtual Sint32 GetCellCount( void ) = 0;

		/**
			@brief �Z���̕`�搔�擾
			@author �t���`
			@return �Z���̕`�搔

			�}�b�v���̕`�悳�ꂽ�Z���̐����擾���܂��B
		*/
		virtual Sint32 GetRenderingCellCount( void ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out, Collision::CBox &Box ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out, Collision::CBox &Box ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param fRadius		[in] �Փ˔��a
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
//		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param fRadius		[in] �Փ˔��a
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
//		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Collision::CBox &Box ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param fRadius		[in] �Փ˔��a
			@param Out			[out] �Փˌ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
//		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphere &Out ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param fRadius		[in] �Փ˔��a
			@param Out			[out] �Փˌ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
//		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphere &Out, Collision::CBox &Box ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param fRadius		[in] �Փ˔��a
			@param Out			[out] �Փˌ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
//		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphereExtend &Out ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param fRadius		[in] �Փ˔��a
			@param Out			[out] �Փˌ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
//		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphereExtend &Out, Collision::CBox &Box ) = 0;

		/**
			@brief �R���W�������f���\��
			@author �t���`
			@param pLine		[in] ���C���v���~�e�B�u�C���^�[�t�F�C�X

			�}�b�v���f�������R���W�����f�[�^��Renderer::Object::ILine3D���g����<BR>
			���o����悤�ɕ`�悵�܂��B
		*/
		virtual void CreateCollisionDrawPrimitive( Renderer::Object::ILine3D *pLine ) = 0;
	};
}
}

