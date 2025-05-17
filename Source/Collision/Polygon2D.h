#pragma once


/**
	@file
	@brief ２次元多角形
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Vector2D.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
	/**
		@brief ２次元の多角形
		@author 葉迩倭
	*/
	class SELENE_DLL_API CPolygon2D
	{
	public:
		Sint32 Count;					///< ポイント配列のポイント数
		Math::Vector2D *pPts;			///< ポリゴンを表すためのポイント配列のポインタ

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CPolygon2D( void );

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param Cnt		[in] 頂点数
			@param pPt		[in] 頂点の配列のアドレス(中でコピーはされませんので、参照元のメモリは保持しておく必要があります)

			@note
			Collisionクラスで判定を行う場合、Cntの値は4以上でpPt[0]==pPt[Cnt-1]になっており、<BR>
			pPtの内容は時計回り、あるいは反時計回りの凸形状をしている必要があります。
		*/
		CPolygon2D( Sint32 Cnt, Math::Vector2D *pPt );
	};
}
}

