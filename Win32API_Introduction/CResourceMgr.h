#pragma once

class CTexture;
class CResource;
class CSound;

class CResourceMgr
{
	SINGLE(CResourceMgr);

private:
	map<wstring, CResource*> m_mapTex;
	

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelPath);
	CTexture* FindTexture(const wstring& _strKey);
	CTexture* CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight);

	CSound* LoadSound(const wstring& _strKey, const wstring& _strRelPath);
	CSound* FindSound(const wstring& _strKey);

};

