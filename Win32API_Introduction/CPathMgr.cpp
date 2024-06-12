#include "pch.h"
#include "CPathMgr.h"
#include "CCore.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
	, m_szRelativePath{}
{
}

CPathMgr::~CPathMgr()
{
}

void CPathMgr::Init()
{
	GetCurrentDirectory(255, m_szContentPath);
	int iLength = (int)wcslen(m_szContentPath);

	// Parent Path
	for (int i = iLength - 1; i >= 0; --i)
	{
		if (m_szContentPath[i] == '\\')
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\x64\\Release\\Content\\");

	SetWindowText(CCore::GetInstance()->GetMainHwnd(), m_szContentPath);

}

wstring CPathMgr::AbsToRelPath(const wchar_t* _absPath)
{
	wstring strFilePath = _absPath;
	
	size_t iAbsLen = wcslen(m_szContentPath);
	size_t iFullLen = strFilePath.length();

	wstring strRelPath = strFilePath.substr(iAbsLen, iFullLen - iAbsLen);


	return strRelPath;
}
