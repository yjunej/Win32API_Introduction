#pragma once
#include "CResource.h"

#include "CSoundMgr.h"

class CSound :
	public CResource
{
private:
	LPDIRECTSOUNDBUFFER		m_pSoundBuffer;
	DSBUFFERDESC			m_tBuffInfo;
	int						m_iVolume;

public:
	int Load(const wstring& _strPath);

	void Play(bool _bLoop = false);
	void PlayToBGM(bool _bLoop = false);
	void Stop(bool _bReset = false);
	void SetVolume(float _fVolume); // 0 ~ 100 
	void SetPosition(float _fPosition); // 0 ~ 100 

private:
	bool LoadWaveSound(const wstring& _strPath);
	int GetDecibel(float _fVolume);



public:
	CSound();
	virtual ~CSound();
};

