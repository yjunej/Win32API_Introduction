#pragma once

class CTexture;
class CResource;

class CResourceMgr
{
	SINGLE(CResourceMgr);

private:
	map<wstring, CResource*> m_mapTex;
	

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelPath);
	CTexture* FindTexture(const wstring& _strKey);
};

