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
namespace Renderer
{
namespace Object
{
	/**
		@brief 3Dスプライト描画用インターフェイス
		@author 葉迩倭

		3Dスプライト描画を保持するためのインターフェイスです。
	*/
	class IParticle
	{
	public:
		virtual ~IParticle() {}

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
			@brief 基準位置設定
			@author 葉迩倭
			@param vPos		[in] 基準位置

			内部バッファに対する全ての基準となる位置を設定します。<BR>
			ここで指定された位置はソートにも利用されます。
		*/
		virtual void SetBasePosition( const Math::Vector3D &vPos ) = 0;

		/**
			@brief データ追加開始宣言
			@author 葉迩倭

			内部バッファへのデータの追加を行うことを通知します。<BR>
			この関数を呼ばずにPush*系の関数を呼ばないようにしてください。
		*/
		virtual void Begin( void ) = 0;

		/**
			@brief データ追加終了宣言
			@author 葉迩倭

			内部バッファへのデータの追加を完了したことを通知します。<BR>
			この関数を呼ぶ前に必ずBegin関数を呼ぶようにしてください。
		*/
		virtual void End( void ) = 0;

		/**
			@brief 描画リクエスト
			@author 葉迩倭
			@param vPosition	[in] スプライトの位置
			@param Size			[in] 描画サイズ
			@param SrcRect		[in] テクスチャ矩形
			@param Color		[in] 色

			内部バッファへのデータの追加を行います。<BR>
			vPositionを基準位置としてSizeで指定した大きさの矩形を作り、
			カメラの方へ向くように頂点シェーダーで計算されます。
		*/
		virtual void Draw( const Math::Vector3D &vPosition, const Math::Point2DF &Size, const Math::Rect2DI &SrcRect, CColor Color ) = 0;

		/**
			@brief 描画リクエスト
			@author 葉迩倭
			@param vPosition	[in] スプライトの位置
			@param PtTbl		[in] 描画用４頂点（左上－右上－左下－右下）
			@param SrcRect		[in] テクスチャ矩形
			@param Color		[in] 色

			内部バッファへのデータの追加を行います。<BR>
			vPositionを基準位置としてPtTblで指定した大きさの矩形を作り、
			カメラの方へ向くように頂点シェーダーで計算されます。
		*/
		virtual void Draw( const Math::Vector3D &vPosition, const Math::Vector2D PtTbl[], const Math::Rect2DI &SrcRect, CColor Color ) = 0;

		/**
			@brief 描画リクエスト
			@author 葉迩倭
			@param vPosition	[in] スプライトの位置
			@param Size			[in] 描画サイズ
			@param SrcRect		[in] テクスチャ矩形
			@param Color		[in] 色
			@param Angle		[in] 回転角度

			内部バッファへのデータの追加を行います。<BR>
			vPositionを基準位置としてSizeで指定した大きさの矩形を作り、
			カメラの方へ向くように頂点シェーダーで計算されます。
		*/
		virtual void DrawRotate( const Math::Vector3D &vPosition, const Math::Point2DF &Size, const Math::Rect2DI &SrcRect, CColor Color, Sint32 Angle ) = 0;

		/**
			@brief 描画リクエスト
			@author 葉迩倭
			@param vPosition	[in] スプライトの位置
			@param PtTbl		[in] 描画用４頂点（左上－右上－左下－右下）
			@param SrcRect		[in] テクスチャ矩形
			@param Color		[in] 色
			@param Angle		[in] 回転角度

			内部バッファへのデータの追加を行います。<BR>
			vPositionを基準位置としてPtTblで指定した大きさの矩形を作り、
			カメラの方へ向くように頂点シェーダーで計算されます。
		*/
		virtual void DrawRotate( const Math::Vector3D &vPosition, const Math::Vector2D PtTbl[], const Math::Rect2DI &SrcRect, CColor Color, Sint32 Angle ) = 0;
	};
}
}
}
