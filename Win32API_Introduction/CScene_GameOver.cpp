#include "pch.h"
#include "CScene_GameOver.h"
#include "CTexture.h"
#include "CResourceMgr.h"
#include "CCore.h"

void CScene_GameOver::Render(HDC _hdc)
{
	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	BitBlt(
		_hdc,
		0, 0, vResolution.x, vResolution.y,
		m_pTex->GetDC(), 0, 0, SRCCOPY
	);
}

CScene_GameOver::CScene_GameOver()
	:m_pTex(nullptr)
{
	m_pTex = CResourceMgr::GetInstance()->LoadTexture(L"GameOver", L"texture\\gameover.bmp");
}

CScene_GameOver::~CScene_GameOver()
{
}
