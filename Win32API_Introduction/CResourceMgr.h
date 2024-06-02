#pragma once

class CTexture;

class CResourceMgr
{
	SINGLE(CResourceMgr);

private:
	map<wstring, CTexture*> m_mapTex;
	

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelPath);
	CTexture* FindTexture(const wstring& _strKey);
};

