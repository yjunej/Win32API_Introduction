#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CObject g_obj;

CCore::CCore()
	: m_hWnd(0)
	, m_ptrResolution{}	
	, m_hDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
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

	// Initialize TimeManager
	CTimeMgr::GetInstance()->Init();
	CKeyMgr::GetInstance()->Init();


	g_obj.SetPos(Vec2(m_ptrResolution.x / 2.f, m_ptrResolution.y / 2.f));
	g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}



void CCore::Progress()
{
	// Update TimeManager
	CTimeMgr::GetInstance()->Update();


	update();
	render();
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vPos.x -= 100.f * fDT;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 100.f * DT;
	}

	g_obj.SetPos(vPos);
}

void CCore::render()
{
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_hDC,
		int(vPos.x - vScale.x / 2.f),
		int(vPos.y - vScale.y / 2.f),
		int(vPos.x + vScale.x / 2.f),
		int(vPos.y + vScale.y / 2.f));
}

