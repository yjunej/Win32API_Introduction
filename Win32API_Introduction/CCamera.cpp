#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

CCamera::CCamera()
	: m_pFocusObj(nullptr)
	, m_fTime(0.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.5f)
{

}

CCamera::~CCamera()
{

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
		m_vCurLookPos = m_vPrevLookPos + vLookDirection.Normalize() * m_fSpeed* fDT;
	}

	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	m_vDiff = m_vCurLookPos - vCenter;
	m_vPrevLookPos = m_vCurLookPos;
}
