#include "pch.h"
#include "CTexture.h"

#include "CCore.h"

CTexture::CTexture()
	: m_hdc(0)
	, m_hBitmap(0)
	, m_bitmap{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_hdc);
	DeleteObject(m_hBitmap);
}

void CTexture::Load(const wstring& _strPath)
{
	m_hBitmap = (HBITMAP)LoadImage(nullptr, _strPath.c_str(), IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBitmap);
	
	// Create DC
	m_hdc = CreateCompatibleDC(CCore::GetInstance()->GetMainDC());
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(m_hdc, m_hBitmap);
	DeleteObject(hPrevBitmap);

	// Get Width, Height
	GetObject(m_hBitmap, sizeof(BITMAP), &m_bitmap);
}

