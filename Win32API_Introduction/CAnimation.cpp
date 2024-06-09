#include "pch.h"
#include "CAnimation.h"

#include "CTimeMgr.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CObject.h"
#include "CPathMgr.h"
#include "CResourceMgr.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}


void CAnimation::Update()
{
	if (m_bFinish) return;

	m_fAccTime += fDT;
	if (m_fAccTime >= m_vecFrm[m_iCurFrm].fDuration)
	{
		m_iCurFrm++;
		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0;
			return;
		}
		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;

	}
}

void CAnimation::Render(HDC _hdc)
{
	if (m_bFinish) return;
	CObject* pObj = m_pAnimator->GetOwner();
	Vec2 vObjPos = pObj->GetPos();

	vObjPos += m_vecFrm[m_iCurFrm].vOffset;
	
	// Convert to Rendering position
	vObjPos = CCamera::GetInstance()->ScreenPosToRenderPos(vObjPos);

	TransparentBlt(
		_hdc,
		(int)(vObjPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f),
		(int)(vObjPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f),
		(int)m_vecFrm[m_iCurFrm].vSlice.x,
		(int)m_vecFrm[m_iCurFrm].vSlice.y,
		m_pTex->GetDC(),
		(int)m_vecFrm[m_iCurFrm].vLT.x,
		(int)m_vecFrm[m_iCurFrm].vLT.y,
		(int)m_vecFrm[m_iCurFrm].vSlice.x,
		(int)m_vecFrm[m_iCurFrm].vSlice.y,
		RGB(0, 0, 0)
	);

}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};

	for (UINT i = 0; i < _iFrameCount; i ++ )
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * (float)i;
		
		m_vecFrm.push_back(frm);
	}
}

void CAnimation::Save(const wstring& _strRelPath)
{
	wstring strAbsFilePath = CPathMgr::GetInstance()->GetContentPath();
	strAbsFilePath += _strRelPath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strAbsFilePath.c_str(), L"wb");
	assert(pFile);

	// Save File Name
	fprintf(pFile, "[Animation Name]\n");
	string strName = string(m_strName.begin(), m_strName.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");
	//SaveWString(m_strName, pFile);

	// Save Texture Key
	fprintf(pFile, "[Texture Name]\n");
	strName = string(m_pTex->GetKey().begin(), m_pTex->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");
	//SaveWString(m_pTex->GetKey(), pFile);

	fprintf(pFile, "[Texture Path]\n");
	strName = string(m_pTex->GetRelPath().begin(), m_pTex->GetRelPath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");
	//SaveWString(m_pTex->GetRelPath(), pFile);


	// Save Frame Info
	fprintf(pFile, "[Frame Count]\n");
	fprintf(pFile, "%d\n", (int)m_vecFrm.size());

	for (size_t i = 0; i < m_vecFrm.size(); i++)
	{	
		fprintf(pFile, "[Frame Index]\n");
		fprintf(pFile, "%d\n", (int)i);
		fprintf(pFile, "[Left Top]\n");
		fprintf(pFile, "%d %d\n", (int)m_vecFrm[i].vLT.x, (int)m_vecFrm[i].vLT.y);
		fprintf(pFile, "[Slice Size]\n");
		fprintf(pFile, "%d %d\n", (int)m_vecFrm[i].vSlice.x, (int)m_vecFrm[i].vSlice.y);
		fprintf(pFile, "[Offset]\n");
		fprintf(pFile, "%d %d\n", (int)m_vecFrm[i].vOffset.x, (int)m_vecFrm[i].vOffset.y);
		fprintf(pFile, "[Duration]\n");
		fprintf(pFile, "%f\n", m_vecFrm[i].fDuration);
		fprintf(pFile, "\n\n");
	}

	//size_t iFrameCount = m_vecFrm.size();
	//fwrite(m_vecFrm.data(), sizeof(tAnimFrm), iFrameCount, pFile);


	fclose(pFile);

}

void CAnimation::Load(const wstring& _strRelPath)
{
	wstring strAbsFilePath = CPathMgr::GetInstance()->GetContentPath();
	strAbsFilePath += _strRelPath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strAbsFilePath.c_str(), L"rb");
	assert(pFile);

	// Save File Name
	char szBuff[256] = {};
	string strData;
	
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);

	strData = szBuff;
	m_strName = wstring(strData.begin(), strData.end());


	// Load Texture Key, Path
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);

	strData = szBuff;
	wstring strTexKey = wstring(strData.begin(), strData.end());

	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	
	strData = szBuff;
	wstring strTexRelPath = wstring(strData.begin(), strData.end());


	// Load Texture
	m_pTex = CResourceMgr::GetInstance()->LoadTexture(strTexKey, strTexRelPath);

	// Load Frame Info
	FScanf(szBuff, pFile);
	int iFrameCount = 0;
	fscanf_s(pFile, "%d", &iFrameCount);

	POINT pt = {};
	tAnimFrm AnimFrm = {};
	for (int i = 0; i < iFrameCount; i++)
	{
		
		while (true)
		{
			FScanf(szBuff, pFile);
			if (!strcmp("[Frame Index]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);

			}
			else if (!strcmp("[Left Top]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);
				AnimFrm.vLT = Vec2(pt);
			}
			else if (!strcmp("[Slice Size]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);
				AnimFrm.vSlice = Vec2(pt);
			}
			else if (!strcmp("[Offset]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);
				AnimFrm.vOffset = Vec2(pt);
			}
			else if (!strcmp("[Duration]", szBuff))
			{
				fscanf_s(pFile, "%f", &AnimFrm.fDuration);
				break;
			}
		}
		m_vecFrm.push_back(AnimFrm);
	}

	//size_t iFrameCount = m_vecFrm.size();
	//fwrite(m_vecFrm.data(), sizeof(tAnimFrm), iFrameCount, pFile);


	fclose(pFile);
}
