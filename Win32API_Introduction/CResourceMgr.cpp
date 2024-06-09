#include "pch.h"
#include "CResourceMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"
#include "CSound.h"

CResourceMgr::CResourceMgr()
{
}

CResourceMgr::~CResourceMgr()
{
    DeleteMapSafe<wstring, CResource*> (m_mapTex);
}

CTexture* CResourceMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelPath)
{
    CTexture* pTexture = FindTexture(_strKey);
    if (nullptr != pTexture)
    {
        return pTexture;
    }   

    wstring strPath = CPathMgr::GetInstance()->GetContentPath();
    strPath += _strRelPath;

    pTexture = new CTexture;

    pTexture->Load(strPath);
    pTexture->SetKey(_strKey);
    pTexture->SetRelPath(_strRelPath);

    m_mapTex.insert(make_pair(_strKey, pTexture));

    return pTexture;
}

CTexture* CResourceMgr::FindTexture(const wstring& _strKey)
{
    map<wstring, CResource*>::iterator iter = m_mapTex.find(_strKey);
    if (iter == m_mapTex.end())
    {
        return nullptr;
    }
    return (CTexture*)iter->second;
}

CTexture* CResourceMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
    CTexture* pTexture = FindTexture(_strKey);
    if (nullptr != pTexture)
    {
        return pTexture;
    }

    pTexture = new CTexture;

    pTexture->Create(_iWidth, _iHeight);
    pTexture->SetKey(_strKey);

    m_mapTex.insert(make_pair(_strKey, pTexture));

    return pTexture;
}

CSound* CResourceMgr::LoadSound(const wstring& _strKey, const wstring& _strRelPath)
{
	CSound* pSound = FindSound(_strKey);
	if (nullptr != pSound)
	{
		return pSound;
	}

	wstring strPath = CPathMgr::GetInstance()->GetContentPath();
	strPath += _strRelPath;

	pSound = new CSound;

	pSound->Load(strPath);
	pSound->SetKey(_strKey);
	pSound->SetRelPath(_strRelPath);

	m_mapTex.insert(make_pair(_strKey, pSound));

	return pSound;


}

CSound* CResourceMgr::FindSound(const wstring& _strKey)
{
	map<wstring, CResource*>::iterator iter = m_mapTex.find(_strKey);
	if (iter == m_mapTex.end())
	{
		return nullptr;
	}
	return (CSound*)iter->second;
}
