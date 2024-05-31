#include "pch.h"
#include "CCore.h"
//CCore* CCore::pCore = nullptr;

int CCore::Init(HWND _hWnd, POINT _ptrResolution)
{
	m_hWnd = _hWnd;
	m_ptrResolution = _ptrResolution;

	// Adjust window size
	RECT rt = { 0, 0, m_ptrResolution.x, m_ptrResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPED, true);

	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	return S_OK;
}

CCore::CCore()
{
}

CCore::~CCore()
{
}