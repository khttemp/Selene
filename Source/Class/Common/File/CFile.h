#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CBaseObject.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief ファイルオープンモード
		@author 葉迩倭
	*/
	enum eFileOpenType
	{
		FILE_OPEN_TYPE_WRITE,			///< 書き込み専用
		FILE_OPEN_TYPE_READ,			///< 読み込み専用
		FILE_OPEN_TYPE_READ_WRITE,		///< 読み書き用

		FILE_OPEN_TYPE_INVALID,			///< 無効
	};

namespace File
{
	/**
		@brief ファイル操作
		@author 葉迩倭
	*/
	class SELENE_DLL_API CFile
	{
	private:
		HANDLE m_hFile;				///< ファイルハンドル
		eFileOpenType m_Type;		///< ファイルオープンモード
		FILETIME m_TimeCreate;		///< ファイル作成時間
		FILETIME m_TimeAccess;		///< ファイルアクセス時間
		FILETIME m_TimeLastWrite;	///< ファイル書き込み時間

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CFile( const char *pFileName, eFileOpenType Type );

		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		virtual ~CFile();

		/**
			@brief ファイルオープンチェック
			@author 葉迩倭
			@retval false	ファイルは開かれていない
			@retval true	ファイルは開かれている
		*/
		virtual Bool IsOpened( void );

		/**
			@brief ファイル書き込み
			@author 葉迩倭
			@param pData	[in] 書き込みデータ
			@param Size		[in] データサイズ
			@return 実際の書き込みサイズ
		*/
		virtual Sint32 Write( const void *pData, Sint32 Size );

		/**
			@brief ファイル読み込み
			@author 葉迩倭
			@param pData	[in] 読み込みデータ
			@param Size		[in] データサイズ
			@return 実際の読み込みサイズ
		*/
		virtual Sint32 Read( void *pData, Sint32 Size );

		/**
			@brief ファイルサイズ取得
			@author 葉迩倭
		*/
		virtual Sint32 GetFileSize( void );

		/**
			@brief ファイル位置取得
			@author 葉迩倭
			preturn ファイル位置
		*/
		virtual Sint32 GetFilePosition( void );

		/**
			@brief 先頭からシーク
			@author 葉迩倭
			@param Offset	[in] 先頭からのオフセット
			@param ファイル位置
		*/
		virtual Sint32 SeekStart( Sint32 Offset );

		/**
			@brief 終端からシーク
			@author 葉迩倭
			@param Offset	[in] 終端からのオフセット
			@param ファイル位置
		*/
		virtual Sint32 SeekEnd( Sint32 Offset );

		/**
			@brief シーク
			@author 葉迩倭
			@param Offset	[in] 現在位置からのオフセット
			@param ファイル位置
		*/
		virtual Sint32 Seek( Sint32 Offset );
	};
}
}

