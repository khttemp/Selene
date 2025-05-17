#pragma once


/**
	@file
	@brief �l�����Ǘ�
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Math
{
	/**
		@brief �l�����N���X
	*/
	class SELENE_DLL_API Quaternion
	{
	public:
		Float x;
		Float y;
		Float z;
		Float w;

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Quaternion();
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param x	[in] X�v�f
			@param y	[in] Y�v�f
			@param z	[in] Z�v�f
			@param w	[in] W�v�f
		*/
		Quaternion( Float x, Float y, Float z, Float w );
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param In	[in] �N�H�[�^�j�I��
		*/
		Quaternion( const Quaternion &In );
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param mIn	[in] �}�g���b�N�X
		*/
		Quaternion( const Matrix &mIn );
		/**
			@brief ���Z
			@author �t���`
			@param In1	[in] ���̓N�H�[�^�j�I���P
			@param In2	[in] ���̓N�H�[�^�j�I���Q
			@return �v�Z���ʌ��*this
			@note
			��̃N�H�[�^�j�I�������Z���܂��B
		*/
		Quaternion& Add( const Quaternion &In1, const Quaternion &In2 );
		/**
			@brief ���Z
			@author �t���`
			@param In1	[in] ���̓N�H�[�^�j�I���P
			@param In2	[in] ���̓N�H�[�^�j�I���Q
			@return �v�Z���ʌ��*this
			@note
			��̃N�H�[�^�j�I�������Z���܂��B
		*/
		Quaternion& Sub( const Quaternion &In1, const Quaternion &In2 );
		/**
			@brief ��Z
			@author �t���`
			@param In1	[in] ���̓N�H�[�^�j�I���P
			@param In2	[in] ���̓N�H�[�^�j�I���Q
			@return �v�Z���ʌ��*this
			@note
			��̃N�H�[�^�j�I������Z���܂��B
		*/
		Quaternion& Mul( const Quaternion &In1, const Quaternion &In2 );
		/**
			@brief ���`���
			@author �t���`
			@param In0		[in] ���̓N�H�[�^�j�I���P
			@param In1		[in] ���̓N�H�[�^�j�I���Q
			@param fRate	[in] �u�����h��(0.0�`1.0f)
			@return �v�Z���ʌ��*this
			@note
			��̃N�H�[�^�j�I������`��Ԃ��܂�
		*/
		Quaternion& Lerp( const Quaternion &In0, const Quaternion &In1, Float fRate );
		/**
			@brief ���ʐ��`���
			@author �t���`
			@param In0		[in] ���̓N�H�[�^�j�I���P
			@param In1		[in] ���̓N�H�[�^�j�I���Q
			@param fRate	[in] �u�����h��(0.0�`1.0f)
			@return �v�Z���ʌ��*this
			@note
			��̃N�H�[�^�j�I�������ʐ��`��Ԃ��܂�
		*/
		Quaternion& Slerp( const Quaternion &In0, const Quaternion &In1, Float fRate );
		/**
			@brief ���Z
			@author �t���`
			@param In	[in] ���̓N�H�[�^�j�I��
			@note
			��̃N�H�[�^�j�I�������Z���܂��B
		*/
		Quaternion& Add( const Quaternion &In );
		/**
			@brief ���Z
			@author �t���`
			@param In	[in] ���̓N�H�[�^�j�I��
			@return �v�Z���ʌ��*this
			@note
			��̃N�H�[�^�j�I�������Z���܂��B
		*/
		Quaternion& Sub( const Quaternion &In );
		/**
			@brief ��Z
			@author �t���`
			@param In	[in] ���̓N�H�[�^�j�I��
			@return �v�Z���ʌ��*this
			@note
			��̃N�H�[�^�j�I������Z���܂��B
		*/
		Quaternion& Mul( const Quaternion &In );
		/**
			@brief ���`���
			@author �t���`
			@param In		[in] ���̓N�H�[�^�j�I��
			@param fRate	[in] �u�����h��(0.0�`1.0f)
			@return �v�Z���ʌ��*this
			@note
			��̃N�H�[�^�j�I������`��Ԃ��܂�
		*/
		Quaternion& Lerp( const Quaternion &In, Float fRate );
		/**
			@brief ���ʐ��`���
			@author �t���`
			@param In		[in] ���̓N�H�[�^�j�I��
			@param fRate	[in] �u�����h��(0.0�`1.0f)
			@return �v�Z���ʌ��*this
			@note
			��̃N�H�[�^�j�I�������ʐ��`��Ԃ��܂�
		*/
		Quaternion& Slerp( const Quaternion &In, Float fRate );
		/**
			@brief ������
			@author �t���`
			@return �v�Z���ʌ��*this
			@note
			xyz=0.0�Aw=1.0�ɏ��������܂��B
		*/
		Quaternion& Identity( void );
		/**
			@brief �����̓����擾
			@author �t���`
			@return �����̓��
			@note
			�����̓����擾���܂��B
		*/
		Float LengthSq( void ) const;
		/**
			@brief �������擾
			@author �t���`
			@return ����
			@note
			�������擾���܂��B
		*/
		Float Length( void ) const;
		/**
			@brief ���ς��擾
			@author �t���`
			@return ����
			@note
			���ς��擾���܂�
		*/
		Float Dot( const Quaternion &In ) const;
		/**
			@brief ����
			@author �t���`
			@return �v�Z���ʌ��*this
			@note
			�N�H�[�^�j�I�����������܂��B
		*/
		Quaternion& Conjugate( void );
		/**
			@brief ����
			@author �t���`
			@return �v�Z���ʌ��*this
			@note
			�N�H�[�^�j�I�����������Ċi�[���܂��B
		*/
		Quaternion& Conjugate( const Quaternion &In );
	};
}
}

