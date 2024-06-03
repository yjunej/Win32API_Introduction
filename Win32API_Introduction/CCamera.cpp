#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"

CCamera::CCamera()
	: m_pFocusObj(nullptr)
{

}

CCamera::~CCamera()
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
}

void CCamera::Update()
{
}

void CCamera::CalDiff()
{
	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	m_vDiff = m_vLookPos - vCenter;
}
