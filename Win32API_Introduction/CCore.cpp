#include "pch.h"
#include "CCore.h"

#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"


CCore::CCore()
	: m_hWnd(0)
	, m_ptrResolution{}	
	, m_hDC(0)
	, m_hBmap(0)
	, m_hSubDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
	
	DeleteDC(m_hSubDC);
	DeleteObject(m_hBmap);
}

int CCore::Init(HWND _hWnd, POINT _ptrResolution)
{
	m_hWnd = _hWnd;
	m_ptrResolution = _ptrResolution;

	// Adjust window size
	RECT rt = { 0, 0, m_ptrResolution.x, m_ptrResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPED, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	// Double Buffering
	m_hBmap = CreateCompatibleBitmap(m_hDC, m_ptrResolution.x, m_ptrResolution.y);
	m_hSubDC = CreateCompatibleDC(m_hDC);

	HBITMAP hPrevBmap = (HBITMAP)SelectObject(m_hSubDC, m_hBmap);
	// 1pixel dummy initial bitmap 
	DeleteObject(hPrevBmap); 


	// Initialize TimeManager
	CTimeMgr::GetInstance()->Init();
	CKeyMgr::GetInstance()->Init();
	CSceneMgr::GetInstance()->Init();

	return S_OK;
}



void CCore::Progress()
{
	// Update Managers
	CTimeMgr::GetInstance()->Update();
	CKeyMgr::GetInstance()->Update();
	CSceneMgr::GetInstance()->Update();

	
	// Clear 
	Rectangle(m_hSubDC, -1, -1, m_ptrResolution.x + 1, m_ptrResolution.y + 1);
	CSceneMgr::GetInstance()->render(m_hSubDC);
	BitBlt(m_hDC, 0, 0, m_ptrResolution.x, m_ptrResolution.y,
		m_hSubDC, 0, 0, SRCCOPY);

}

//void CCore::update()
//{
//	Vec2 vPos = g_obj.GetPos();
//
//	//if (GetAsyncKeyState(VK_LEFT) & 0x8000)
//	if (CKeyMgr::GetInstance()->GetKeyState(KEY::LEFT) == KEY_STATE::TAP)
//	{
//		vPos.x -= 200.f * fDT;
//	}
//	//if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
//	if (CKeyMgr::GetInstance()->GetKeyState(KEY::RIGHT) == KEY_STATE::TAP)
//	{
//		vPos.x += 200.f * fDT;
//	}
//
//	g_obj.SetPos(vPos);
//}
//
//void CCore::render()
//{
//	// Clear 
//	Rectangle(m_hSubDC, -1, -1, m_ptrResolution.x + 1, m_ptrResolution.y + 1);
//
//
//	Vec2 vPos = g_obj.GetPos();
//	Vec2 vScale = g_obj.GetScale();
//
//	Rectangle(m_hSubDC,
//		int(vPos.x - vScale.x / 2.f),
//		int(vPos.y - vScale.y / 2.f),
//		int(vPos.x + vScale.x / 2.f),
//		int(vPos.y + vScale.y / 2.f));
//
//	// Copy
//	BitBlt(m_hDC, 0, 0, m_ptrResolution.x, m_ptrResolution.y,
//		m_hSubDC, 0, 0, SRCCOPY);
//
//}
//
