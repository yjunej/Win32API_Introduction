#pragma once

#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

class CSound;

class CSoundMgr
{
	SINGLE(CSoundMgr);

private:
	LPDIRECTSOUND8	m_pSound;	// SoundCard
	CSound* m_pBGM;	

public:
	int Init(void);
	LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }
	void RegisterToBGM(CSound* _pSound);
};