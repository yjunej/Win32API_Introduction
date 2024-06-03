#pragma once

#include "CResource.h"

class CResourceMgr;

class CTexture : public CResource
{
private:
	HDC m_hdc;
	HBITMAP m_hBitmap;
	BITMAP m_bitmap;

public:
	void Load(const wstring& _strPath);

	UINT GetWidth() { return (UINT)m_bitmap.bmWidth; }
	UINT GetHeight() { return (UINT)m_bitmap.bmHeight; }

	HDC GetDC() { return m_hdc; }

private:
	CTexture();
	virtual ~CTexture();

	friend class CResourceMgr;

};

