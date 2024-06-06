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
	void Create(UINT _iWidth, UINT _iHeight);

	UINT GetWidth() const { return (UINT)m_bitmap.bmWidth; }
	UINT GetHeight() const { return (UINT)m_bitmap.bmHeight; }

	HDC GetDC() const { return m_hdc; }

private:
	CTexture();
	virtual ~CTexture();

	friend class CResourceMgr;

};

