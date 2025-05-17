#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Math/Style.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief シーンスプライトアクター用インターフェイス
		@author 葉迩倭

		シーン管理されたスプライトアクターを扱う為のインターフェイスです。
	*/
	class IParticleActor
	{
	public:
		virtual ~IParticleActor() {}

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
			@brief 描画リクエスト
			@author 葉迩倭

			ISceneManagerに対してレンダリングリクエストを発行します。<BR>
			取得元のISceneManagerがBegin()/End()中でない場合この関数は失敗します。
		*/
		virtual void RenderingRequest( void ) = 0;
	};
}
}

