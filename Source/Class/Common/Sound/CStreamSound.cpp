

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Sound/CStreamSound.h"
#include "class/Common/File/CFileManager.h"
#include "Class/Common/File/CResourceFile.h"


//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
#define LOOP_INFINITY		(-1)


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Sound;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStreamSound::SoundThread( void *pData )
{
	((CStreamSound*)pData)->MainProc();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CStreamSound::CStreamSound( CCore *pCore, CResourceObjectMgr *pMgr )
	: CResourceObject	( pMgr )
	, m_pCore			( pCore )
	, m_hDLL			( NULL )
	, m_pFile			( NULL )
	, m_Event			( false, EVENT_HANDLE_MAX )
	, m_EventPos		( 0 )
	, m_EventEnd		( 0 )
	, m_FillPosition	( 0 )
	, m_FillBytes		( 0 )
	, m_DecodeSample	( 0 )
	, m_IsPlay			( false )
	, m_IsPause			( false )
	, m_IsPlayEnd		( false )
	, m_IsBufferEnd		( false )
	, m_pSoundBuffer	( NULL )
	, m_pSoundNotify	( NULL )
	, m_pPlayTbl		( NULL )
	, m_PlayTblCount	( 0 )
	, m_PlayTblPosition	( 0 )
{
	// キューバッファ初期化
	MemoryClear( m_EventQue, sizeof(m_EventQue) );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CStreamSound::~CStreamSound( void )
{
	Log_PrintTable( 0xFF0000, 0x000000, "解放", "ストリームサウンド", m_Name );
	Log_TableLine( 1 );

	// 終了
	SEventQue Que = { true, EVENT_RELEASE };
	AddQue( Que );

	// スレッド終了待ち
	while ( !m_Thread.WaitForExit() )
	{
		::SleepEx( 100, TRUE );
	}

	// バッファ解放
	SAFE_RELEASE( m_pSoundNotify );
	SAFE_RELEASE( m_pSoundBuffer );

	// ファイル解放
	SAFE_RELEASE( m_pFile );

	// デコーダー解放
	SAFE_RELEASE( m_pDecoder );

	// プラグイン解放
	::FreeLibrary( m_hDLL );

	// テーブル解放
	SAFE_DELETE_ARRAY( m_pPlayTbl );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CStreamSound::CreateFromFile( const char *pFileName, Bool IsGlobalScope, const char *pPluginName, IDirectSound8 *pDS )
{
	//--------------------------------------------------------------
	// データの読み込み
	//--------------------------------------------------------------
	m_pFile = m_pCore->GetFileMgrPointer()->FileOpen( pFileName );
	if ( m_pFile->IsInvalid() )
	{
		Log_PrintStrong( 0xFF0000, "ファイルが開けませんでした" );
		return false;
	}

	//--------------------------------------------------------------
	// サウンドのデコーダーを取得
	//--------------------------------------------------------------
	char Path[MAX_PATH] = "";
	StringCbPrintf( Path, sizeof(Path), "%sSound\\%s.ssp", m_pCore->GetPluginDirectory(), pPluginName );

	// DLL
	m_hDLL = ::LoadLibrary( Path );
	if ( m_hDLL == NULL )
	{
		Log_PrintStrong( 0xFF0000, "サウンドプラグイン[%s.ssp]が開けませんでした", pPluginName );
		return false;
	}

	// 関数
	void *pProc = ::GetProcAddress( m_hDLL, "CreateSoundStreamDecoder" );
	if ( pProc == NULL )
	{
		Log_PrintStrong( 0xFF0000, "サウンドプラグインから関数が開けませんでした" );
		return false;
	}

	// デコーダー
	m_pDecoder = ((Plugin::Sound::ISoundStreamDecoder*(*)(void))pProc)();
	if ( m_pDecoder == NULL )
	{
		Log_PrintStrong( 0xFF0000, "サウンドプラグインからデコーダーが取得できませんでした。" );
		return false;
	}

	//--------------------------------------------------------------
	// ローダーの設定
	//--------------------------------------------------------------
	m_pDecoder->SetStreamLoader( (File::CResourceFile*)m_pFile );
	// データチェック
	if ( !m_pDecoder->CheckData() )
	{
		Log_PrintStrong( 0xFF0000, "プラグインから不正なファイルとしてエラーが返されました。" );
		return false;
	}

	//--------------------------------------------------------------
	// PCMフォーマットからバッファを生成
	//--------------------------------------------------------------
	if ( !CreateSoundBuffer( IsGlobalScope, pDS ) )
	{
		return false;
	}

	//--------------------------------------------------------------
	// データ
	//--------------------------------------------------------------
	Log_PrintLine( 0x000000, "再生時間 %.3lfsec", toF(m_pDecoder->GetTotalSamples()) / toF(m_Format.nAvgBytesPerSec) );
	Log_PrintLine( 0x000000, "%uBit / %uHz / %s", m_Format.wBitsPerSample, m_Format.nSamplesPerSec, (m_Format.nChannels == 1) ? "モノラル" : "ステレオ" );

	//--------------------------------------------------------------
	// スレッド生成
	//--------------------------------------------------------------
	m_Thread.Create( SoundThread, this );

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CStreamSound::CreateSoundBuffer( Bool IsGlobalScope, IDirectSound8 *pDS )
{
	DSBUFFERDESC Desc = { sizeof(DSBUFFERDESC) };
	DSBPOSITIONNOTIFY DSPosNotfy[BUFFER_NOTIFY_COUNT];
	HRESULT hr;

	m_Format = m_pDecoder->GetWaveFormat();

	//--------------------------------------------------------------
	// １回のフィルサイズ
	//--------------------------------------------------------------
	m_FillBytes = m_Format.nAvgBytesPerSec / 2;

	//--------------------------------------------------------------
	// DirectSoundBuffer設定
	//--------------------------------------------------------------
	Desc.lpwfxFormat	= &m_Format;
	Desc.dwBufferBytes	= m_FillBytes * BUFFER_NOTIFY_COUNT;
	Desc.dwFlags		= DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME;

	if ( IsGlobalScope )
	{
		Desc.dwFlags |= DSBCAPS_GLOBALFOCUS;
	}

	//--------------------------------------------------------------
	// DirectSoundBuffer生成
	//--------------------------------------------------------------
	hr = pDS->CreateSoundBuffer( &Desc, &m_pSoundBuffer, NULL );
	if FAILED( hr )
	{
		Log_PrintStrong( 0xFF0000, "サウンドバッファの生成に失敗しました。" );
		return false;
	}

	//--------------------------------------------------------------
	// バッファ初期化
	//--------------------------------------------------------------
	m_pSoundBuffer->SetCurrentPosition( 0 );
	m_pSoundBuffer->SetVolume( 0 );
	m_pSoundBuffer->SetPan( 0 );

	//--------------------------------------------------------------
	// イベント用インターフェース取得
	//--------------------------------------------------------------
	hr = m_pSoundBuffer->QueryInterface( IID_IDirectSoundNotify, (void**)&m_pSoundNotify );
	if FAILED( hr )
	{
		Log_PrintStrong( 0xFF0000, "イベント用インターフェイスの生成に失敗しました。" );
		return false;
	}

	//--------------------------------------------------------------
	// DirectSound通知用イベント
	//--------------------------------------------------------------
	for ( Sint32 i = 0; i < BUFFER_NOTIFY_COUNT; i++ )
	{
		DSPosNotfy[i].dwOffset = m_FillBytes * i;
		DSPosNotfy[i].hEventNotify = m_Event.GetHandle( EVENT_WRITE_BUFFER0 + i );
	}

	//--------------------------------------------------------------
	// 通知イベント設定
	//--------------------------------------------------------------
	hr = m_pSoundNotify->SetNotificationPositions( BUFFER_NOTIFY_COUNT, DSPosNotfy );
	if FAILED( hr )
	{
		Log_PrintStrong( 0xFF0000, "通知イベントの設定に失敗" );
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CStreamSound::Play( SPlayBlock *pTbl, Sint32 Count )
{
	if ( (pTbl == NULL) || (Count <= 0) ) return Play( 1 );

	SEventQue Que = { true, EVENT_PLAY };

	Que.Play.pTable = new SPlayBlock [ Count ];
	Que.Play.Count = Count;
	for ( Sint32 i = 0; i < Count; i++ )
	{
		Que.Play.pTable[i] = pTbl[i];
		if ( Que.Play.pTable[i].LoopCount <= 0 )
		{
			Que.Play.pTable[i].LoopCount = LOOP_INFINITY;
		}
	}

	// キューに追加
	return AddQue( Que );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CStreamSound::Play( Sint32 LoopCount )
{
	SEventQue Que = { true, EVENT_LOOP };

	if ( LoopCount <= 0 )
	{
		LoopCount = LOOP_INFINITY;
	}

	Que.Loop.Count = LoopCount;

	// キューに追加
	return AddQue( Que );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CStreamSound::Stop( void )
{
	SEventQue Que = { true, EVENT_STOP };

	// キューに追加
	return AddQue( Que );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CStreamSound::Pause( void )
{
	SEventQue Que = { true, EVENT_PAUSE };

	// キューに追加
	return AddQue( Que );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CStreamSound::SetVolume( Float fVolume )
{
	SEventQue Que = { true, EVENT_VOLUME };

	Que.Volume.fVolume = fVolume;

	// キューに追加
	return AddQue( Que );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CStreamSound::SetPan( Float fPan )
{
	SEventQue Que = { true, EVENT_PAN };

	Que.Pan.fPan = fPan;

	// キューに追加
	return AddQue( Que );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CStreamSound::IsPlay( void )
{
	Thread::CAutoLock Lock( m_CS );

	return m_IsPlay;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CStreamSound::AddQue( SEventQue &Que )
{
	Thread::CAutoLock Lock( m_CS );

	// キューは一杯ではないよねぇ？
	if ( !m_EventQue[m_EventEnd].IsActive )
	{
		// データコピー
		m_EventQue[m_EventEnd] = Que;
		// イベントON
		m_Event.Set( m_EventEnd );
		// オフセット加算
		m_EventEnd = (m_EventEnd + 1) % EVENT_QUE_MAX;

		// 処理成功
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStreamSound::MainProc( void )
{
	Bool IsActive = true;

	//------------------------------------------------------------
	// 処理ループ
	//------------------------------------------------------------
	while ( IsActive )
	{
		// イベント待ち
		Sint32 Result = m_Event.Wait( -1 );
		if ( Result == -1 ) break;

		// イベント処理待ち
		switch ( Result )
		{
		case WAIT_OBJECT_0 + EVENT_WRITE_BUFFER0:
		case WAIT_OBJECT_0 + EVENT_WRITE_BUFFER1:
			{
				if ( m_IsPlayEnd )
				{
					Thread::CAutoLock Lock( m_CS );

					StopSubstance();
				}
				else
				{
					// バッファ更新
					if ( m_IsBufferEnd )
					{
						// 終了フラグ
						m_IsPlayEnd = true;
					}

					// バッファ埋め
					WriteBuffer();
				}
			}
			break;

		default:
			{
				Thread::CAutoLock Lock( m_CS );

				// キューデータ取得
				SEventQue &Que = m_EventQue[m_EventPos];

				// イベント処理
				switch ( Que.EventType )
				{
				case EVENT_PLAY:
					PlaySubstance( Que );
					SAFE_DELETE_ARRAY( Que.Play.pTable );
					break;
				case EVENT_LOOP:
					LoopSubstance( Que );
					break;
				case EVENT_STOP:
					StopSubstance();
					break;
				case EVENT_PAUSE:
					PauseSubstance();
					break;
				case EVENT_VOLUME:
					SetVolumeSubstance( Que.Volume.fVolume );
					break;
				case EVENT_PAN:
					SetPanSubstance( Que.Pan.fPan );
					break;
				case EVENT_RELEASE:
					IsActive = false;
					break;
				}

				// キュー解放
				MemoryClear( &Que, sizeof(SEventQue) );

				// キューのオフセットを進める
				m_EventPos = (m_EventPos + 1) % EVENT_QUE_MAX;
			}
			break;
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CStreamSound::DecodeEnd( Sint8 *pDst, Uint32 Size )
{
	Sint64 CurrentSample = m_pPlayTbl[m_PlayTblPosition].EndSample;
	Sint32 OldPlayTblPosition = m_PlayTblPosition;

	// 無限ループ
	if ( m_pPlayTbl[m_PlayTblPosition].LoopCount != LOOP_INFINITY )
	{
		// ループ数-1
		m_pPlayTbl[m_PlayTblPosition].LoopCount--;
		// ループ終了
		if ( m_pPlayTbl[m_PlayTblPosition].LoopCount == 0 )
		{
			// テーブル+1
			m_PlayTblPosition++;
			// テーブル終了
			if ( m_PlayTblPosition == m_PlayTblCount )
			{
				// 終わり
				Sint32 Val = m_Format.wBitsPerSample != 8 ? 0x00 : 0x80;
				MemoryFill( pDst, Val, Size );
				return true;
			}
		}
	}

	// 次開始
	if ( (m_pPlayTbl[m_PlayTblPosition].StartSample != CurrentSample) || (OldPlayTblPosition == m_PlayTblPosition) )
	{
		m_pDecoder->Seek( m_pPlayTbl[m_PlayTblPosition].StartSample );
	}

	// デコードサイズ
	m_DecodeSample = m_pPlayTbl[m_PlayTblPosition].DecodeSample;

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CStreamSound::Decode( Sint8 *pDst, Uint32 Size )
{
	while ( Size > 0 )
	{
		// なくなった？
		if ( m_DecodeSample == 0 )
		{
			if ( DecodeEnd( pDst, Size ) )
			{
				return true;
			}
		}

		// 実デコードサイズ
		Sint32 ReadSize = (Sint32)(MIN( m_DecodeSample, (Sint64)Size ));

		// デコード
		Sint32 DecodeSize = m_pDecoder->Read( pDst, ReadSize );
		if ( DecodeSize == 0 )
		{
			if ( DecodeEnd( pDst, Size ) )
			{
				return true;
			}
		}

		pDst += DecodeSize;
		Size -= DecodeSize;
		m_DecodeSample -= DecodeSize;
	}

	return false;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStreamSound::WriteBuffer( void )
{
	Sint8 *pSoundData[2];
	Uint32 Size[2];

	//--------------------------------------------------------------
	// サウンドバッファロック
	//--------------------------------------------------------------
	m_pSoundBuffer->Lock(
		m_FillPosition * m_FillBytes,
		m_FillBytes,
		(void**)&pSoundData[0], &Size[0],
		(void**)&pSoundData[1], &Size[1],
		0 );

	//--------------------------------------------------------------
	// サウンドバッファにデータ書き込み
	//--------------------------------------------------------------
	if ( m_IsBufferEnd )
	{
		Sint32 Val = m_Format.wBitsPerSample != 8 ? 0x00 : 0x80;
		if ( Size[0] > 0 ) MemoryFill( pSoundData[0], Val, Size[0] );
		if ( Size[1] > 0 ) MemoryFill( pSoundData[1], Val, Size[1] );
	}
	else
	{
		if ( (Size[0] > 0) && Decode( pSoundData[0], Size[0] ) ) m_IsBufferEnd = true;
		if ( (Size[1] > 0) && Decode( pSoundData[1], Size[1] ) ) m_IsBufferEnd = true;
	}

	//--------------------------------------------------------------
	// サウンドバッファロック解除
	//--------------------------------------------------------------
	m_pSoundBuffer->Unlock(
		(void**)pSoundData[0], Size[0],
		(void**)pSoundData[1], Size[1] );

	//--------------------------------------------------------------
	// バッファ埋める場所
	//--------------------------------------------------------------
	m_FillPosition = (m_FillPosition + 1) % BUFFER_NOTIFY_COUNT;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CStreamSound::SecToSample( Float fSec )
{
	Sint32 Sample = toI(fSec * toF(m_Format.nAvgBytesPerSec));

	return (Sample + 0x3) & ~0x3;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStreamSound::PlaySubstance( const SEventQue &Que )
{
	if ( m_IsPlay ) return;

	//------------------------------------------------------------
	// ループ設定
	//------------------------------------------------------------
	m_pPlayTbl = new SEventPlayTable [ Que.Play.Count ];
	m_PlayTblCount = Que.Play.Count;
	m_PlayTblPosition = 0;

	Sint32 TotalSample = m_pDecoder->GetTotalSamples();
	for ( Sint32 i = 0; i < Que.Play.Count; i++ )
	{
		SPlayBlock &Src = Que.Play.pTable[i];
		SEventPlayTable &Dst = m_pPlayTbl[i];

		// ループ数
		Dst.LoopCount = Src.LoopCount;

		// 開始点
		if (Src.fStartTime <= 0.0f )
		{
			Dst.StartSample = 0;
		}
		else
		{
			Dst.StartSample = SecToSample( Src.fStartTime );
		}

		// 終了点
		if ( Src.fEndTime <= 0.0f )
		{
			Dst.EndSample = TotalSample;
		}
		else
		{
			Dst.EndSample = SecToSample( Src.fEndTime );
		}

		// 範囲チェック
		if ( Dst.EndSample > TotalSample )
		{
			Dst.EndSample = TotalSample;
		}

		// デコードサンプル数
		Dst.DecodeSample = Dst.EndSample - Dst.StartSample;
		if ( Dst.DecodeSample <= 0 )
		{
			// ダメ
			return;
		}
	}

	//------------------------------------------------------------
	// Oggのバッファを初期位置に
	//------------------------------------------------------------
	m_pDecoder->Seek( m_pPlayTbl[0].StartSample );
	m_DecodeSample = m_pPlayTbl[0].DecodeSample;

	//------------------------------------------------------------
	// バッファ再生開始位置を先頭に
	//------------------------------------------------------------
	m_pSoundBuffer->SetCurrentPosition( 0 );
	m_FillPosition = 0;

	//------------------------------------------------------------
	// フラグ
	//------------------------------------------------------------
	m_IsPlay = true;
	m_IsPause = false;
	m_IsPlayEnd = false;
	m_IsBufferEnd = false;

	//------------------------------------------------------------
	// 最初のバッファは埋めておく
	//------------------------------------------------------------
	WriteBuffer();

	//------------------------------------------------------------
	// 再生開始
	//------------------------------------------------------------
	m_pSoundBuffer->Play( 0, 0, DSBPLAY_LOOPING );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStreamSound::LoopSubstance( const SEventQue &Que )
{
	if ( m_IsPlay ) return;

	//------------------------------------------------------------
	// フラグ
	//------------------------------------------------------------
	m_IsPlay = true;
	m_IsPause = false;
	m_IsPlayEnd = false;
	m_IsBufferEnd = false;

	//------------------------------------------------------------
	// ループ設定
	//------------------------------------------------------------
	m_pPlayTbl = new SEventPlayTable [ 1 ];
	m_PlayTblCount = 1;
	m_PlayTblPosition = 0;
	m_pPlayTbl[0].LoopCount = Que.Loop.Count;
	m_pPlayTbl[0].StartSample = 0;
	m_pPlayTbl[0].EndSample = m_pDecoder->GetTotalSamples();
	m_pPlayTbl[0].DecodeSample = m_pPlayTbl[0].EndSample - m_pPlayTbl[0].StartSample;

	//------------------------------------------------------------
	// Oggのバッファを初期位置に
	//------------------------------------------------------------
	m_pDecoder->Seek( m_pPlayTbl[0].StartSample );
	m_DecodeSample = m_pPlayTbl[0].DecodeSample;

	//------------------------------------------------------------
	// バッファ再生開始位置を先頭に
	//------------------------------------------------------------
	m_pSoundBuffer->SetCurrentPosition( 0 );
	m_FillPosition = 0;

	//------------------------------------------------------------
	// 最初のバッファは埋めておく
	//------------------------------------------------------------
	WriteBuffer();

	//------------------------------------------------------------
	// 再生開始
	//------------------------------------------------------------
	m_pSoundBuffer->Play( 0, 0, DSBPLAY_LOOPING );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStreamSound::StopSubstance( void )
{
	if ( !m_IsPlay ) return;

	// 停止
	m_pSoundBuffer->Stop();

	SAFE_DELETE_ARRAY( m_pPlayTbl );

	m_IsPlay = false;
	m_IsPause = false;
	m_IsPlayEnd = false;
	m_IsBufferEnd = false;

	m_PlayTblCount = 0;
	m_PlayTblPosition = 0;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStreamSound::PauseSubstance( void )
{
	if ( !m_IsPlay ) return;

	if ( m_IsPause )
	{
		m_pSoundBuffer->Play( 0, 0, DSBPLAY_LOOPING );
	}
	else
	{
		m_pSoundBuffer->Stop();
	}

	m_IsPause = !m_IsPause;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStreamSound::SetVolumeSubstance( Float fVolume )
{
	if ( !m_IsPlay ) return;

	if ( fVolume >= 100.0f )
	{
		fVolume = 0.0f;
	}
	ef ( fVolume <= 0.0f )
	{
		fVolume = -10000.0f;
	}
	else
	{
		fVolume = -powf( 100.0f, log10f( 100.0f - fVolume ) );
	}

	m_pSoundBuffer->SetVolume( toI(fVolume) );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CStreamSound::SetPanSubstance( Float fPan )
{
	if ( !m_IsPlay ) return;

	if ( fPan >= +100.0f )
	{
		fPan = +10000.0f;
	}
	ef( fPan <= -100.0f )
	{
		fPan = -10000.0f;
	}
	ef( fPan > 0.0f )
	{
		fPan = +powf( 100.0f, log10f( +fPan ) );
	}
	ef( fPan < 0.0f )
	{
		fPan = -powf( 100.0f, log10f( -fPan ) );
	}

	m_pSoundBuffer->SetPan( toI(fPan) );
}

