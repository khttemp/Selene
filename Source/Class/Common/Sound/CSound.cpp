

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Local.h"
#include "System.h"
#include "Class/Common/Core/CCore.h"
#include "Class/Common/Sound/CSound.h"
#include "Class/Common/File/CFileManager.h"
#include "Class/Common/File/CResourceFile.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Sound;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSound::CSound( CCore *pCore, CResourceObjectMgr *pMgr )
	: CResourceObject	( pMgr )
	, m_pCore			( pCore )
	, m_LayerMax		( 0 )
	, m_pSound			( NULL )
{
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CSound::~CSound( void )
{
	Log_PrintTable( 0xFF0000, 0x000000, "解放", "サウンド", m_Name );
	Log_TableLine( 1 );

	Sint32 Layer = m_LayerMax;
	for ( Sint32 i = 0; i < Layer; i++ )
	{
		SAFE_RELEASE( m_pSound[i].pBuffer );
	}

	SAFE_DELETE_ARRAY( m_pSound );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSound::CreateFromFile( const char *pFileName, Sint32 Layer, Bool IsGlobalScope, IDirectSound8 *pDS )
{
	DSBUFFERDESC Desc = { sizeof(DSBUFFERDESC) };
	File::IResourceFile *pFile = NULL;
	void *pSoundData1 = NULL;
	void *pSoundData2 = NULL;
	WAVEFORMATEX *pFormat = NULL;
	Uint32 Size1 = 0;
	Uint32 Size2 = 0;
	Bool IsRet = false;

	Sint32 DataSize;
	HRESULT hr;

	//--------------------------------------------------------------
	// レイヤー数
	//--------------------------------------------------------------
	Layer = MAX( Layer, 1 );
	m_LayerMax = Layer;

	m_pSound = new SSoundData [ Layer ];
	for ( Sint32 i = 0; i < Layer; i++ )
	{
		m_pSound[i].pBuffer = NULL;
		m_pSound[i].IsLoop = false;
	}

	//--------------------------------------------------------------
	// データの読み込み
	//--------------------------------------------------------------
	pFile = m_pCore->GetFileMgrPointer()->FileOpen( pFileName );
	if ( pFile->IsInvalid() )
	{
		Log_PrintStrong( 0xFF0000, "ファイルが開けませんでした" );
		goto EXIT;
	}

	//--------------------------------------------------------------
	// WAVEデータの取得
	//--------------------------------------------------------------
	if ( !GetWaveData( pFile, pFormat, DataSize ) )
	{
		goto EXIT;
	}

	Log_PrintLine( 0x000000, "再生時間 %.3lfsec", toF(DataSize) / toF(pFormat->nAvgBytesPerSec) );
	Log_PrintLine( 0x000000, "%uBit / %uHz / %s", pFormat->wBitsPerSample, pFormat->nSamplesPerSec, (pFormat->nChannels == 1) ? "モノラル" : "ステレオ" );

	//--------------------------------------------------------------
	// DirectSoundBuffer設定
	//--------------------------------------------------------------
	Desc.dwBufferBytes = DataSize;
	Desc.lpwfxFormat = pFormat;
	Desc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_LOCSOFTWARE;
	if ( IsGlobalScope )
	{
		Desc.dwFlags |= DSBCAPS_GLOBALFOCUS;
	}

	//--------------------------------------------------------------
	// DirectSoundBuffer生成
	//--------------------------------------------------------------
	hr = pDS->CreateSoundBuffer( &Desc, &m_pSound[0].pBuffer, NULL );
	if FAILED( hr )
	{
		Log_PrintStrong( 0xFF0000, "サウンドバッファの生成に失敗。" );
		goto EXIT;
	}

	//--------------------------------------------------------------
	// バッファ書き込み
	//--------------------------------------------------------------
	hr = m_pSound[0].pBuffer->Lock(
						0, DataSize,
						&pSoundData1, &Size1,
						&pSoundData2, &Size2,
						DSBLOCK_ENTIREBUFFER );
	if FAILED( hr )
	{
		Log_PrintStrong( 0xFF0000, "サウンドバッファの書き込みに失敗。" );
		goto EXIT;
	}

	// サウンドデータコピー
	pFile->Read( pSoundData1, DataSize );

	// ロック解除
	m_pSound[0].pBuffer->Unlock( pSoundData1, Size1, pSoundData2, Size2 );

	//--------------------------------------------------------------
	// バッファの複製
	//--------------------------------------------------------------
	for ( Sint32 i = 1; i < Layer; i++ )
	{
		pDS->DuplicateSoundBuffer( m_pSound[0].pBuffer, &m_pSound[i].pBuffer );
	}

	IsRet = true;

EXIT:
	MemoryFree( pFormat );
	// ファイルクローズ
	SAFE_RELEASE( pFile );

	return IsRet;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSound::Play( Sint32 Layer, Bool IsLoop )
{
	if ( Layer >= m_LayerMax ) return;

	if ( Layer < 0 )
	{
		long Max = m_LayerMax;
		for ( long i = 0; i < Max; i++ )
		{
			m_pSound[i].IsLoop = IsLoop;
			if ( IsLoop )
			{
				m_pSound[i].pBuffer->Play( 0, 0, DSBPLAY_LOOPING );
			}
			else
			{
				m_pSound[i].pBuffer->Play( 0, 0, 0 );
			}
		}
	}
	else
	{
		if ( m_pSound[Layer].pBuffer == NULL ) return;

		m_pSound[Layer].IsLoop = IsLoop;
		if ( IsLoop )
		{
			m_pSound[Layer].pBuffer->Play( 0, 0, DSBPLAY_LOOPING );
		}
		else
		{
			m_pSound[Layer].pBuffer->Play( 0, 0, 0 );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSound::Stop( Sint32 Layer )
{
	if ( Layer >= m_LayerMax ) return;

	if ( Layer < 0 )
	{
		long Max = m_LayerMax;
		for ( long i = 0; i < Max; i++ )
		{
			m_pSound[i].IsLoop = false;
			m_pSound[i].pBuffer->Stop();
			m_pSound[i].pBuffer->SetCurrentPosition( 0 );
		}
	}
	else
	{
		if ( m_pSound[Layer].pBuffer == NULL ) return;

		m_pSound[Layer].IsLoop = false;
		m_pSound[Layer].pBuffer->Stop();
		m_pSound[Layer].pBuffer->SetCurrentPosition( 0 );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSound::Pause( Sint32 Layer )
{
	if ( Layer >= m_LayerMax ) return;

	if ( Layer < 0 )
	{
		long Max = m_LayerMax;
		for ( long i = 0; i < Max; i++ )
		{
			// 再生中？
			if ( IsPlay( i ) )
			{
				m_pSound[i].pBuffer->Stop();
			}
			else
			{
				Play( i, m_pSound[i].IsLoop );
			}
		}
	}
	else
	{
		if ( m_pSound[Layer].pBuffer == NULL ) return;

		// 再生中？
		if ( IsPlay( Layer ) )
		{
			m_pSound[Layer].pBuffer->Stop();
		}
		else
		{
			Play( Layer, m_pSound[Layer].IsLoop );
		}
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSound::SetVolume( Sint32 Layer, Float fVolume )
{
	if ( Layer >= m_LayerMax ) return;

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

	if ( Layer < 0 )
	{
		long Max = m_LayerMax;
		for ( long i = 0; i < Max; i++ )
		{
			m_pSound[i].pBuffer->SetVolume( toI(fVolume) );
		}
	}
	else
	{
		if ( m_pSound[Layer].pBuffer == NULL ) return;

		m_pSound[Layer].pBuffer->SetVolume( toI(fVolume) );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CSound::SetPan( Sint32 Layer, Float fPan )
{
	if ( Layer >= m_LayerMax ) return;

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

	if ( Layer < 0 )
	{
		long Max = m_LayerMax;
		for ( long i = 0; i < Max; i++ )
		{
			m_pSound[i].pBuffer->SetPan( toI(fPan) );
		}
	}
	else
	{
		if ( m_pSound[Layer].pBuffer == NULL ) return;

		m_pSound[Layer].pBuffer->SetPan( toI(fPan) );
	}
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSound::IsPlay( Sint32 Layer )
{
	if ( Layer >= m_LayerMax ) return false;
	if ( m_pSound[Layer].pBuffer == NULL ) return false;

	Uint32 Status;
	m_pSound[Layer].pBuffer->GetStatus( &Status );

	// 再生中？
	return Status == DSBSTATUS_PLAYING;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CSound::GetWaveData( File::IResourceFile *pFile, WAVEFORMATEX *&pWaveFmt, Sint32 &DataSize )
{
	Bool IsRet = false;
	char Chunk[5] = "";

	pFile->SeekStart( 0 );

	//--------------------------------------------------------
	// "RIFF"の文字列
	//--------------------------------------------------------
	pFile->Read( Chunk, 4 );
	if ( ::CompareString( LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, "RIFF", -1, Chunk, -1 ) != CSTR_EQUAL )
	{
		Log_PrintStrong( 0xFF0000, "WAVEファイルではありません。" );
		goto EXIT_DATALOAD;
	}

	//--------------------------------------------------------
	// RIFFデータサイズ
	//--------------------------------------------------------
	pFile->Read( Chunk, 4 );

	//--------------------------------------------------------
	// "WAVE"の文字列
	//--------------------------------------------------------
	pFile->Read( Chunk, 4 );
	if ( ::CompareString( LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, "WAVE", -1, Chunk, -1 ) != CSTR_EQUAL )
	{
		Log_PrintStrong( 0xFF0000, "WAVEファイルではありません。" );
		goto EXIT_DATALOAD;
	}

	//========================================================
	// チャンク情報取得
	//========================================================
	for ( ; ; )
	{
		Sint32 ChunkSize;

		//-------------------------------------------------
		// チャンク読み
		//-------------------------------------------------
		if ( pFile->Read( Chunk, 4 ) == 0 )
		{
			Log_PrintStrong( 0xFF0000, "不正なファイルです。" );
			goto EXIT_DATALOAD;
		}

		//-------------------------------------------------
		// フォーマット
		//-------------------------------------------------
		if ( ::CompareString( LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, "fmt ", -1, Chunk, -1 ) == CSTR_EQUAL )
		{
			// チャンクサイズ取得
			pFile->Read( &ChunkSize, 4 );
			// チャンクデータ取得
			pWaveFmt = (WAVEFORMATEX*)MemoryAlloc( ChunkSize );
			pFile->Read( pWaveFmt, ChunkSize );
			// PCM？
			if ( pWaveFmt->wFormatTag != WAVE_FORMAT_PCM )
			{
				Log_PrintStrong( 0xFF0000, "無圧縮WAVEではありません。" );
				goto EXIT_DATALOAD;
			}
		}
		//-------------------------------------------------
		// データ
		//-------------------------------------------------
		ef ( ::CompareString( LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, "data", -1, Chunk, -1 ) == CSTR_EQUAL )
		{
			// チャンクサイズ取得
			pFile->Read( &ChunkSize, 4 );
			DataSize = ChunkSize;
			IsRet = true;

			goto EXIT_DATALOAD;
		}
		//-------------------------------------------------
		// わかんね
		//-------------------------------------------------
		else
		{
			pFile->Read( &ChunkSize, 4 );
			pFile->Seek( ChunkSize );
		}
	}

	// 終了
EXIT_DATALOAD:

	return IsRet;
}

