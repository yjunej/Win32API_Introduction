#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CResourceMgr.h"
#include "CTexture.h"

CCamera::CCamera()
	: m_pFocusObj(nullptr)
	, m_fTime(0.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.5f)
	, m_pVeilTex(nullptr)
{
}

CCamera::~CCamera()
{

}

void CCamera::Init()
{
	Vec2 vRes = CCore::GetInstance()->GetResolution();
	m_pVeilTex = CResourceMgr::GetInstance()->CreateTexture(
		L"CameraVeil", (UINT)vRes.x, (UINT)vRes.y);


}

void CCamera::Update()
{
	if (m_pFocusObj)
	{
		if (m_pFocusObj->IsDead())
		{
			m_pFocusObj = nullptr;
		}
		else
		{
			m_vLookPos = m_pFocusObj->GetPos();
		}
	}

	if (KEY_HOLD(KEY::UP))
	{
		m_vLookPos.y -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::LEFT))
	{
		m_vLookPos.x -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::DOWN))
	{
		m_vLookPos.y += 500.f * fDT;
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		m_vLookPos.x += 500.f * fDT;
	}
	CalDiff();
}

void CCamera::Render(HDC _hdc)
{
	if (m_listCamEffectInfo.empty())
		return;

	tCamEffectInfo& tcei = m_listCamEffectInfo.front();
	tcei.fAccTime += fDT;

	float fRatio = 0.f;
	int iAlpha = 0;

	fRatio = tcei.fAccTime / tcei.fDuration;
	
	fRatio = fRatio > 1.f ? 1.f : fRatio;
	fRatio = fRatio < 0.f ? 0.f : fRatio;

	switch (tcei.eEffect)
	{
	case CAM_EFFECT::NONE:
		return;
	case CAM_EFFECT::END:
		return;

	case CAM_EFFECT::FADE_IN:
	{
		iAlpha = (int)(255.f * (1.f-fRatio));
		break;
	}
	case CAM_EFFECT::FADE_OUT:
	{
		iAlpha = (int)(255.f * fRatio);
		break;
	}

	default:
		return;
	}

	
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;

	AlphaBlend(
		_hdc,
		0, 0, (int)m_pVeilTex->GetWidth(), (int)m_pVeilTex->GetHeight(),
		m_pVeilTex->GetDC(),
		0, 0, (int)m_pVeilTex->GetWidth(), (int)m_pVeilTex->GetHeight(),
		bf
	);

	if (tcei.fAccTime > tcei.fDuration)
	{
		m_listCamEffectInfo.pop_front();
	}

}

void CCamera::CalDiff()
{
	// Interp for Smooth moving

	m_fAccTime += fDT;

	if (m_fAccTime >= m_fTime)
	{
		m_vCurLookPos = m_vLookPos;
	}
	else
	{
		Vec2 vLookDirection = m_vLookPos - m_vPrevLookPos;
		if (!vLookDirection.IsZero())
		{
			m_vCurLookPos = m_vPrevLookPos + vLookDirection.Normalize() * m_fSpeed * fDT;
		}
	}

	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	m_vDiff = m_vCurLookPos - vCenter;
	m_vPrevLookPos = m_vCurLookPos;
}
