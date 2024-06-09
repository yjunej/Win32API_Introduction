#include "pch.h"
#include "CSoundMgr.h"
#include "CResourceMgr.h"
#include "CSound.h" 

#include "CCore.h"

CSoundMgr::CSoundMgr()
	: m_pSound(nullptr)
	, m_pBGM(nullptr)
{
}

CSoundMgr::~CSoundMgr()
{
}

int CSoundMgr::Init(void)
{
	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
	{
		MessageBox(NULL, L"Failed to Create Sound Device!", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// SetCooperativeLevel
	HWND hWnd = CCore::GetInstance()->GetMainHwnd();
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag
	{
		MessageBox(NULL, L"Failed to Set Sound Device Cooperative Level!", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	return true;
}

void CSoundMgr::RegisterToBGM(CSound* _pSound)
{
	if (m_pBGM != nullptr)
		m_pBGM->Stop(true);

	m_pBGM = _pSound;
}