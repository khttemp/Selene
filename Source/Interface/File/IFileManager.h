#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace File
{
	/**
		@brief ファイル管理クラス
		@author 葉迩倭

		Seleneで使用するファイルの管理を行います。
	*/
	class IFileManager
	{
	public:
		virtual ~IFileManager() {}

		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief ファイルロードパス設定
			@author 葉迩倭
			@param Priority		[in] 検索プライオリティ
			@param pRootPath	[in] ルートディレクトリ
			@param pPassword	[in] パックファイルの場合のパスワード（ない場合はNULL）

			ファイルの読み込みを行うルートのディレクトリを設定します。<BR>
			ここで設定された パス および パス.Pack ファイルは同列に扱われます。<BR>
			つまりプログラムの変更なく双方にまったく同じようにアクセス可能です。
		*/
		virtual void SetRootPath( Sint32 Priority, const char *pRootPath, const char *pPassword = NULL ) = 0;

		/**
			@brief カレントディレクトリ設定
			@author 葉迩倭
			@param pCurrentDir	[in] ディレクトリ名

			ファイル検索を行う際のカレントのディレクトリを設定します。<BR>
			ここで設定されたディレクトリをルートとしてファイルの検索を行います。<BR>
			<BR>
			SetRootPath( 0, "Data", "Data.Pack" ); という設定が行われいて、<BR>
			SetCurrentPath( "texture" ); となっているとき「sample.bmp」と指定して読み込みした場合<BR>
			<BR>
			「Data\texture\sample.bmp」を探しに行き、見つからない場合は<BR>
			「Data.Pack」ファイル内の「texture\sample.bmp」ファイルを探しに行きます。
		*/
		virtual void SetCurrentPath( const char *pCurrentDir ) = 0;

		/**
			@brief ファイルロード
			@author 葉迩倭
			@param pFile	[in] ファイル名
			@param ppData	[out] ファイルデータ格納先
			@param pSize	[out] ファイルサイズ格納先
			@retval true	成功
			@retval false	失敗

			ファイルをロードし、メモリに展開します。
		*/
		virtual Bool Load( const char *pFile, void **ppData, Sint32 *pSize ) = 0;

		/**
			@brief データ解放
			@author 葉迩倭
			@param pData	[in] データ

			Load()関数で取得したデータをメモリから解放します。<BR>
			この関数を使った方法以外での解放は環境依存するため、<BR>
			正しく解放されない可能性があります。
		*/
		virtual void Free( void *pData ) = 0;

		/**
			@brief ファイルオープン
			@author 葉迩倭
			@param pFile		[in] ファイル名
			@retval NULL		失敗
			@retval NULL以外	ファイルインターフェイス

			リソースファイルをオープンします。<BR>
			ここでいうリソースファイルはゲームで使われるデータ全般の事です。<BR>
			つまりパックファイルの内容、およびルートディレクトリ以下のデータです。<BR>
			SetRootPath()で指定されている[フォルダ]→[パックファイル]の<BR>
			順にファイルを検索します。<BR>
			オープンしたファイルはパックファイルであっても、<BR>
			通常のファイルと同じようにアクセスすることが出来ます。<BR>
			またこの関数から取得したIFIleインターフェイスは読み取り専用です。<BR>
			使用が終了したIFileインターフェイスはRelease()で解放してください。
		*/
		virtual IResourceFile *FileOpen( const char *pFile ) = 0;
	};
}
}

