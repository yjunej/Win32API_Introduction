#include "pch.h"
#include "CPathMgr.h"
#include "CCore.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{
}

CPathMgr::~CPathMgr()
{
}

void CPathMgr::Init()
{
	GetCurrentDirectory(255, m_szContentPath);
	int iLength = wcslen(m_szContentPath);

	// Parent Path
	for (int i = iLength - 1; i >= 0; --i)
	{
		if (m_szContentPath[i] == '\\')
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\Release\\Content");

	SetWindowText(CCore::GetInstance()->GetMainHwnd(), m_szContentPath);

}
