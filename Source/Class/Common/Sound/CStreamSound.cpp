

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
	// �L���[�o�b�t�@������
	MemoryClear( m_EventQue, sizeof(m_EventQue) );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CStreamSound::~CStreamSound( void )
{
	Log_PrintTable( 0xFF0000, 0x000000, "���", "�X�g���[���T�E���h", m_Name );
	Log_TableLine( 1 );

	// �I��
	SEventQue Que = { true, EVENT_RELEASE };
	AddQue( Que );

	// �X���b�h�I���҂�
	while ( !m_Thread.WaitForExit() )
	{
		::SleepEx( 100, TRUE );
	}

	// �o�b�t�@���
	SAFE_RELEASE( m_pSoundNotify );
	SAFE_RELEASE( m_pSoundBuffer );

	// �t�@�C�����
	SAFE_RELEASE( m_pFile );

	// �f�R�[�_�[���
	SAFE_RELEASE( m_pDecoder );

	// �v���O�C�����
	::FreeLibrary( m_hDLL );

	// �e�[�u�����
	SAFE_DELETE_ARRAY( m_pPlayTbl );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CStreamSound::CreateFromFile( const char *pFileName, Bool IsGlobalScope, const char *pPluginName, IDirectSound8 *pDS )
{
	//--------------------------------------------------------------
	// �f�[�^�̓ǂݍ���
	//--------------------------------------------------------------
	m_pFile = m_pCore->GetFileMgrPointer()->FileOpen( pFileName );
	if ( m_pFile->IsInvalid() )
	{
		Log_PrintStrong( 0xFF0000, "�t�@�C�����J���܂���ł���" );
		return false;
	}

	//--------------------------------------------------------------
	// �T�E���h�̃f�R�[�_�[���擾
	//--------------------------------------------------------------
	char Path[MAX_PATH] = "";
	StringCbPrintf( Path, sizeof(Path), "%sSound\\%s.ssp", m_pCore->GetPluginDirectory(), pPluginName );

	// DLL
	m_hDLL = ::LoadLibrary( Path );
	if ( m_hDLL == NULL )
	{
		Log_PrintStrong( 0xFF0000, "�T�E���h�v���O�C��[%s.ssp]���J���܂���ł���", pPluginName );
		return false;
	}

	// �֐�
	void *pProc = ::GetProcAddress( m_hDLL, "CreateSoundStreamDecoder" );
	if ( pProc == NULL )
	{
		Log_PrintStrong( 0xFF0000, "�T�E���h�v���O�C������֐����J���܂���ł���" );
		return false;
	}

	// �f�R�[�_�[
	m_pDecoder = ((Plugin::Sound::ISoundStreamDecoder*(*)(void))pProc)();
	if ( m_pDecoder == NULL )
	{
		Log_PrintStrong( 0xFF0000, "�T�E���h�v���O�C������f�R�[�_�[���擾�ł��܂���ł����B" );
		return false;
	}

	//--------------------------------------------------------------
	// ���[�_�[�̐ݒ�
	//--------------------------------------------------------------
	m_pDecoder->SetStreamLoader( (File::CResourceFile*)m_pFile );
	// �f�[�^�`�F�b�N
	if ( !m_pDecoder->CheckData() )
	{
		Log_PrintStrong( 0xFF0000, "�v���O�C������s���ȃt�@�C���Ƃ��ăG���[���Ԃ���܂����B" );
		return false;
	}

	//--------------------------------------------------------------
	// PCM�t�H�[�}�b�g����o�b�t�@�𐶐�
	//--------------------------------------------------------------
	if ( !CreateSoundBuffer( IsGlobalScope, pDS ) )
	{
		return false;
	}

	//--------------------------------------------------------------
	// �f�[�^
	//--------------------------------------------------------------
	Log_PrintLine( 0x000000, "�Đ����� %.3lfsec", toF(m_pDecoder->GetTotalSamples()) / toF(m_Format.nAvgBytesPerSec) );
	Log_PrintLine( 0x000000, "%uBit / %uHz / %s", m_Format.wBitsPerSample, m_Format.nSamplesPerSec, (m_Format.nChannels == 1) ? "���m����" : "�X�e���I" );

	//--------------------------------------------------------------
	// �X���b�h����
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
	// �P��̃t�B���T�C�Y
	//--------------------------------------------------------------
	m_FillBytes = m_Format.nAvgBytesPerSec / 2;

	//--------------------------------------------------------------
	// DirectSoundBuffer�ݒ�
	//--------------------------------------------------------------
	Desc.lpwfxFormat	= &m_Format;
	Desc.dwBufferBytes	= m_FillBytes * BUFFER_NOTIFY_COUNT;
	Desc.dwFlags		= DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME;

	if ( IsGlobalScope )
	{
		Desc.dwFlags |= DSBCAPS_GLOBALFOCUS;
	}

	//--------------------------------------------------------------
	// DirectSoundBuffer����
	//--------------------------------------------------------------
	hr = pDS->CreateSoundBuffer( &Desc, &m_pSoundBuffer, NULL );
	if FAILED( hr )
	{
		Log_PrintStrong( 0xFF0000, "�T�E���h�o�b�t�@�̐����Ɏ��s���܂����B" );
		return false;
	}

	//--------------------------------------------------------------
	// �o�b�t�@������
	//--------------------------------------------------------------
	m_pSoundBuffer->SetCurrentPosition( 0 );
	m_pSoundBuffer->SetVolume( 0 );
	m_pSoundBuffer->SetPan( 0 );

	//--------------------------------------------------------------
	// �C�x���g�p�C���^�[�t�F�[�X�擾
	//--------------------------------------------------------------
	hr = m_pSoundBuffer->QueryInterface( IID_IDirectSoundNotify, (void**)&m_pSoundNotify );
	if FAILED( hr )
	{
		Log_PrintStrong( 0xFF0000, "�C�x���g�p�C���^�[�t�F�C�X�̐����Ɏ��s���܂����B" );
		return false;
	}

	//--------------------------------------------------------------
	// DirectSound�ʒm�p�C�x���g
	//--------------------------------------------------------------
	for ( Sint32 i = 0; i < BUFFER_NOTIFY_COUNT; i++ )
	{
		DSPosNotfy[i].dwOffset = m_FillBytes * i;
		DSPosNotfy[i].hEventNotify = m_Event.GetHandle( EVENT_WRITE_BUFFER0 + i );
	}

	//--------------------------------------------------------------
	// �ʒm�C�x���g�ݒ�
	//--------------------------------------------------------------
	hr = m_pSoundNotify->SetNotificationPositions( BUFFER_NOTIFY_COUNT, DSPosNotfy );
	if FAILED( hr )
	{
		Log_PrintStrong( 0xFF0000, "�ʒm�C�x���g�̐ݒ�Ɏ��s" );
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

	// �L���[�ɒǉ�
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

	// �L���[�ɒǉ�
	return AddQue( Que );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CStreamSound::Stop( void )
{
	SEventQue Que = { true, EVENT_STOP };

	// �L���[�ɒǉ�
	return AddQue( Que );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Bool CStreamSound::Pause( void )
{
	SEventQue Que = { true, EVENT_PAUSE };

	// �L���[�ɒǉ�
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

	// �L���[�ɒǉ�
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

	// �L���[�ɒǉ�
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

	// �L���[�͈�t�ł͂Ȃ���˂��H
	if ( !m_EventQue[m_EventEnd].IsActive )
	{
		// �f�[�^�R�s�[
		m_EventQue[m_EventEnd] = Que;
		// �C�x���gON
		m_Event.Set( m_EventEnd );
		// �I�t�Z�b�g���Z
		m_EventEnd = (m_EventEnd + 1) % EVENT_QUE_MAX;

		// ��������
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
	// �������[�v
	//------------------------------------------------------------
	while ( IsActive )
	{
		// �C�x���g�҂�
		Sint32 Result = m_Event.Wait( -1 );
		if ( Result == -1 ) break;

		// �C�x���g�����҂�
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
					// �o�b�t�@�X�V
					if ( m_IsBufferEnd )
					{
						// �I���t���O
						m_IsPlayEnd = true;
					}

					// �o�b�t�@����
					WriteBuffer();
				}
			}
			break;

		default:
			{
				Thread::CAutoLock Lock( m_CS );

				// �L���[�f�[�^�擾
				SEventQue &Que = m_EventQue[m_EventPos];

				// �C�x���g����
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

				// �L���[���
				MemoryClear( &Que, sizeof(SEventQue) );

				// �L���[�̃I�t�Z�b�g��i�߂�
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

	// �������[�v
	if ( m_pPlayTbl[m_PlayTblPosition].LoopCount != LOOP_INFINITY )
	{
		// ���[�v��-1
		m_pPlayTbl[m_PlayTblPosition].LoopCount--;
		// ���[�v�I��
		if ( m_pPlayTbl[m_PlayTblPosition].LoopCount == 0 )
		{
			// �e�[�u��+1
			m_PlayTblPosition++;
			// �e�[�u���I��
			if ( m_PlayTblPosition == m_PlayTblCount )
			{
				// �I���
				Sint32 Val = m_Format.wBitsPerSample != 8 ? 0x00 : 0x80;
				MemoryFill( pDst, Val, Size );
				return true;
			}
		}
	}

	// ���J�n
	if ( (m_pPlayTbl[m_PlayTblPosition].StartSample != CurrentSample) || (OldPlayTblPosition == m_PlayTblPosition) )
	{
		m_pDecoder->Seek( m_pPlayTbl[m_PlayTblPosition].StartSample );
	}

	// �f�R�[�h�T�C�Y
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
		// �Ȃ��Ȃ����H
		if ( m_DecodeSample == 0 )
		{
			if ( DecodeEnd( pDst, Size ) )
			{
				return true;
			}
		}

		// ���f�R�[�h�T�C�Y
		Sint32 ReadSize = (Sint32)(MIN( m_DecodeSample, (Sint64)Size ));

		// �f�R�[�h
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
	// �T�E���h�o�b�t�@���b�N
	//--------------------------------------------------------------
	m_pSoundBuffer->Lock(
		m_FillPosition * m_FillBytes,
		m_FillBytes,
		(void**)&pSoundData[0], &Size[0],
		(void**)&pSoundData[1], &Size[1],
		0 );

	//--------------------------------------------------------------
	// �T�E���h�o�b�t�@�Ƀf�[�^��������
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
	// �T�E���h�o�b�t�@���b�N����
	//--------------------------------------------------------------
	m_pSoundBuffer->Unlock(
		(void**)pSoundData[0], Size[0],
		(void**)pSoundData[1], Size[1] );

	//--------------------------------------------------------------
	// �o�b�t�@���߂�ꏊ
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
	// ���[�v�ݒ�
	//------------------------------------------------------------
	m_pPlayTbl = new SEventPlayTable [ Que.Play.Count ];
	m_PlayTblCount = Que.Play.Count;
	m_PlayTblPosition = 0;

	Sint32 TotalSample = m_pDecoder->GetTotalSamples();
	for ( Sint32 i = 0; i < Que.Play.Count; i++ )
	{
		SPlayBlock &Src = Que.Play.pTable[i];
		SEventPlayTable &Dst = m_pPlayTbl[i];

		// ���[�v��
		Dst.LoopCount = Src.LoopCount;

		// �J�n�_
		if (Src.fStartTime <= 0.0f )
		{
			Dst.StartSample = 0;
		}
		else
		{
			Dst.StartSample = SecToSample( Src.fStartTime );
		}

		// �I���_
		if ( Src.fEndTime <= 0.0f )
		{
			Dst.EndSample = TotalSample;
		}
		else
		{
			Dst.EndSample = SecToSample( Src.fEndTime );
		}

		// �͈̓`�F�b�N
		if ( Dst.EndSample > TotalSample )
		{
			Dst.EndSample = TotalSample;
		}

		// �f�R�[�h�T���v����
		Dst.DecodeSample = Dst.EndSample - Dst.StartSample;
		if ( Dst.DecodeSample <= 0 )
		{
			// �_��
			return;
		}
	}

	//------------------------------------------------------------
	// Ogg�̃o�b�t�@�������ʒu��
	//------------------------------------------------------------
	m_pDecoder->Seek( m_pPlayTbl[0].StartSample );
	m_DecodeSample = m_pPlayTbl[0].DecodeSample;

	//------------------------------------------------------------
	// �o�b�t�@�Đ��J�n�ʒu��擪��
	//------------------------------------------------------------
	m_pSoundBuffer->SetCurrentPosition( 0 );
	m_FillPosition = 0;

	//------------------------------------------------------------
	// �t���O
	//------------------------------------------------------------
	m_IsPlay = true;
	m_IsPause = false;
	m_IsPlayEnd = false;
	m_IsBufferEnd = false;

	//------------------------------------------------------------
	// �ŏ��̃o�b�t�@�͖��߂Ă���
	//------------------------------------------------------------
	WriteBuffer();

	//------------------------------------------------------------
	// �Đ��J�n
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
	// �t���O
	//------------------------------------------------------------
	m_IsPlay = true;
	m_IsPause = false;
	m_IsPlayEnd = false;
	m_IsBufferEnd = false;

	//------------------------------------------------------------
	// ���[�v�ݒ�
	//------------------------------------------------------------
	m_pPlayTbl = new SEventPlayTable [ 1 ];
	m_PlayTblCount = 1;
	m_PlayTblPosition = 0;
	m_pPlayTbl[0].LoopCount = Que.Loop.Count;
	m_pPlayTbl[0].StartSample = 0;
	m_pPlayTbl[0].EndSample = m_pDecoder->GetTotalSamples();
	m_pPlayTbl[0].DecodeSample = m_pPlayTbl[0].EndSample - m_pPlayTbl[0].StartSample;

	//------------------------------------------------------------
	// Ogg�̃o�b�t�@�������ʒu��
	//------------------------------------------------------------
	m_pDecoder->Seek( m_pPlayTbl[0].StartSample );
	m_DecodeSample = m_pPlayTbl[0].DecodeSample;

	//------------------------------------------------------------
	// �o�b�t�@�Đ��J�n�ʒu��擪��
	//------------------------------------------------------------
	m_pSoundBuffer->SetCurrentPosition( 0 );
	m_FillPosition = 0;

	//------------------------------------------------------------
	// �ŏ��̃o�b�t�@�͖��߂Ă���
	//------------------------------------------------------------
	WriteBuffer();

	//------------------------------------------------------------
	// �Đ��J�n
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

	// ��~
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

