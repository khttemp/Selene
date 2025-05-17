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
namespace Fiber
{
	/**
		@brief ファイバーインターフェイス
		@author 葉迩倭

		@note
		ファイバーを実装するための基底クラスです。
	*/
	class IFiber
	{
	private:
		Sint32 m_RefCount;
		IFiberController *m_pFiberCtrl;

	protected:
/**
@brief ファイバー切り替え
@author 葉迩倭
@retval true	アプリケーションは継続中
@retval false	アプリケーションが終了している

@note
登録されている次のIDのファイバーに処理を切り替えます。<BR>
返り値がfalseの場合アプリケーションが終了処理を行っているので<BR>
Controller()メソッドから直ちに抜けるように組んで下さい。
*/
		Bool Switch( void )
		{
			return m_pFiberCtrl->Switch();
		}

	public:
/**
@brief コンストラクタ
@author 葉迩倭
*/
		IFiber( void )
			: m_pFiberCtrl	( NULL )
			, m_RefCount	( 1 )
		{
		}

/**
@brief デストラクタ
@author 葉迩倭
*/
		virtual ~IFiber()
		{
			if ( m_pFiberCtrl != NULL )
			{
				m_pFiberCtrl->Release();
			}
		}

/**
@brief 参照カウンタデクリメント
@author 葉迩倭
@return デクリメント後の参照カウント

@note
参照カウンタをデクリメントし、<BR>
参照カウントが0になった時点でメモリから解放します。
*/
		Sint32 Release( void )
		{
			Sint32 Cnt = --m_RefCount;
			if ( Cnt == 0 )
			{
				delete this;
			}
			return Cnt;
		}

/**
@brief 参照カウンタインクリメント
@author 葉迩倭
@return インクリメント後の参照カウント

@note
参照カウンタをインクリメントします。<BR>
インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
AddRef()をしたインターフェイスは必ずRelease()で解放してください。
*/
		Sint32 AddRef( void )
		{
			return ++m_RefCount;
		}

/**
@brief コントローラー設定
@author 葉迩倭
@param pCtrl	[in] コントローラー
*/
		void SetController( IFiberController *pCtrl )
		{
			m_pFiberCtrl = pCtrl;
			m_pFiberCtrl->AddRef();
		}

	public:
/**
@brief ファイバー用制御関数
@author 葉迩倭

@note
ファイバーを実際に操作するための純粋仮想関数です。<BR>
この関数から抜けることでそのファイバーの処理が停止します。<BR>
Switch()メソッドでの切り替え時にfalseが帰ってきたらただちに<BR>
関数から抜けるようにして下さい。
*/
		virtual void Control( void ) = 0;
	};
}
}

