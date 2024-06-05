#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator()
	: m_pOwner(nullptr)
	, m_pCurAnim(nullptr)
	, m_bLoop(false)
{
}

CAnimator::~CAnimator()
{
	DeleteMapSafe<wstring, CAnimation*>(m_mapAnim);
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	CAnimation* pAnim = FindAnimation(_strName);
	assert(nullptr == pAnim);

	pAnim = new CAnimation;

	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep,_fDuration, _iFrameCount);

	m_mapAnim.insert(make_pair(_strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);
	if (iter == m_mapAnim.end())
	{
		return nullptr;
	}
	return iter->second;
}

void CAnimator::Play(const wstring& _strName, bool bLoop)
{
	m_pCurAnim = FindAnimation(_strName);
	m_bLoop = bLoop;
}

void CAnimator::Update()
{

}

void CAnimator::PostUpdate()
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->Update();
		if (m_bLoop && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetCurFrame(0);
		}
	}
}

void CAnimator::Render(HDC _hdc)
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->Render(_hdc);
	}
}


