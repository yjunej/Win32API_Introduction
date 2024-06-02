#include "pch.h"
#include "CResourceMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"

CResourceMgr::CResourceMgr()
{
}

CResourceMgr::~CResourceMgr()
{
    map<wstring, CTexture*>::iterator iter = m_mapTex.begin();
    for (; iter != m_mapTex.end(); ++iter)
    {
        delete iter->second;
    }
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
    map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);
    if (iter == m_mapTex.end())
    {
        return nullptr;
    }
    return iter->second;
}
