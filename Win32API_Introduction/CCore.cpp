#include "pch.h"
#include "CCore.h"

#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}	
	, m_hDC(0)
	, m_hBmap(0)
	, m_hSubDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
	
	DeleteDC(m_hSubDC);
	DeleteObject(m_hBmap);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// Adjust window size
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPED, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	// Double Buffering
	m_hBmap = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hSubDC = CreateCompatibleDC(m_hDC);

	HBITMAP hPrevBmap = (HBITMAP)SelectObject(m_hSubDC, m_hBmap);
	// 1pixel dummy initial bitmap 
	DeleteObject(hPrevBmap); 


	// Initialize Brush & Pen Tools
	CreatePaintTools();


	// Initialize TimeManager
	CPathMgr::GetInstance()->Init();
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
	CCollisionMgr::GetInstance()->Update();

	
	// Clear 
	Rectangle(m_hSubDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	CSceneMgr::GetInstance()->Render(m_hSubDC);
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_hSubDC, 0, 0, SRCCOPY);

}

void CCore::CreatePaintTools()
{
	// Brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);


	// Pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

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
//	Rectangle(m_hSubDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
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
//	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
//		m_hSubDC, 0, 0, SRCCOPY);
//
//}
//
