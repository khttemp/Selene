#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CResourceObject.h"
#include "Thread/Event.h"
#include "Thread/Thread.h"
#include "Thread/CriticalSection.h"
#include "Interface/Sound/IStreamSound.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Sound
{
	static const Sint32 EVENT_QUE_MAX = 32;

	enum eEventType
	{
		EVENT_PLAY,
		EVENT_LOOP,
		EVENT_STOP,
		EVENT_PAUSE,
		EVENT_VOLUME,
		EVENT_PAN,
		EVENT_RELEASE,

		EVENT_WRITE_BUFFER0 = EVENT_QUE_MAX + 0,
		EVENT_WRITE_BUFFER1,

		EVENT_HANDLE_MAX,

		BUFFER_NOTIFY_COUNT = EVENT_HANDLE_MAX - EVENT_WRITE_BUFFER0,
	};

	struct SEventQue_Volume
	{
		Float fVolume;
	};

	struct SEventQue_Pan
	{
		Float fPan;
	};

	struct SEventQue_Play
	{
		SPlayBlock *pTable;
		Sint32 Count;
	};

	struct SEventQue_Loop
	{
		Sint32 Count;
	};

	struct SEventQue
	{
		Bool IsActive;
		eEventType EventType;

		union
		{
			SEventQue_Play		Play;
			SEventQue_Loop		Loop;
			SEventQue_Volume	Volume;
			SEventQue_Pan		Pan;
		};
	};

	struct SEventPlayTable
	{
		Sint32 LoopCount;
		Sint32 StartSample;
		Sint32 EndSample;
		Sint32 DecodeSample;
	};

	class CStreamSound : public CResourceObject, public IStreamSound
	{
	private:
		static void SoundThread( void *pData );

	protected:
		CCore								*m_pCore;
		HMODULE								m_hDLL;
		Plugin::Sound::ISoundStreamDecoder	*m_pDecoder;
		File::IResourceFile					*m_pFile;
		Thread::CThread						m_Thread;
		Thread::CCriticalSection			m_CS;
		Thread::CEvent						m_Event;
		SEventQue							m_EventQue[EVENT_QUE_MAX];
		Sint32								m_EventPos;
		Sint32								m_EventEnd;
		Sint32								m_FillPosition;
		Sint32								m_FillBytes;
		Sint64								m_DecodeSample;
		Bool								m_IsPlay;
		Bool								m_IsPause;
		Bool								m_IsPlayEnd;
		Bool								m_IsBufferEnd;
		IDirectSoundBuffer					*m_pSoundBuffer;
		IDirectSoundNotify					*m_pSoundNotify;
		WAVEFORMATEX						m_Format;
		SEventPlayTable						*m_pPlayTbl;
		Sint32								m_PlayTblCount;
		Sint32								m_PlayTblPosition;

	private:
		virtual void MainProc( void );
		virtual Bool CreateSoundBuffer( Bool IsGlobalScope, IDirectSound8 *pDS );
		virtual Bool AddQue( SEventQue &Que );

		virtual Sint32 SecToSample( Float fSec );
		virtual Bool DecodeEnd( Sint8 *pDst, Uint32 Size );
		virtual Bool Decode( Sint8 *pDst, Uint32 Size );
		virtual void WriteBuffer( void );
		virtual void PlaySubstance( const SEventQue &Que );
		virtual void LoopSubstance( const SEventQue &Que );
		virtual void StopSubstance( void );
		virtual void PauseSubstance( void );
		virtual void SetVolumeSubstance( Float fVolume );
		virtual void SetPanSubstance( Float fPan );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CStreamSound( CCore *pCore, CResourceObjectMgr *pMgr );
		virtual ~CStreamSound( void );

		virtual Bool CreateFromFile( const char *pFileName, Bool IsGlobalScope, const char *pPluginName, IDirectSound8 *pDS );

		virtual Bool Play( SPlayBlock *pTbl, Sint32 Count );
		virtual Bool Play( Sint32 LoopCount );
		virtual Bool Stop( void );
		virtual Bool Pause( void );
		virtual Bool SetVolume( Float fVolume );
		virtual Bool SetPan( Float fPan );
		virtual Bool IsPlay( void );
	};
}
}
