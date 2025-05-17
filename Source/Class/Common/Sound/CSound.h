#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/Common/Object/CResourceObject.h"
#include "Interface/Sound/ISound.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Sound
{
	struct SSoundData
	{
		IDirectSoundBuffer		*pBuffer;
		Bool					IsLoop;
	};

	class CSound : public CResourceObject, public ISound
	{
	protected:
		SSoundData		*m_pSound;
		Sint32			m_LayerMax;
		CCore			*m_pCore;

	private:
		Bool GetWaveData( File::IResourceFile *pFile, WAVEFORMATEX *&pWaveFmt, Sint32 &DataSize );

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void )  { return CBaseObject::AddRef(); }

	public:
		CSound( CCore *pCore, CResourceObjectMgr *pMgr );
		virtual ~CSound( void );

		Bool CreateFromFile( const char *pFileName, Sint32 Layer, Bool IsGlobalScope, IDirectSound8 *pDS );

		virtual void Play( Sint32 Layer, Bool IsLoop );
		virtual void Stop( Sint32 Layer );
		virtual void Pause( Sint32 Layer );
		virtual void SetVolume( Sint32 Layer, Float fVolume );
		virtual void SetPan( Sint32 Layer, Float fPan );
		virtual Bool IsPlay( Sint32 Layer );
	};
}
}
