#include "pch.h"
#include "CEnemy.h"

#include "CTimeMgr.h"



CEnemy::CEnemy()
	: m_fSpeed(100.f)
	, m_vCenterPos(Vec2(0.f, 0.f))
	, m_fPatrolDistance(50.f)
	, m_iDirection(1)
{
}

CEnemy::~CEnemy()
{
}

void CEnemy::Update()
{
	Vec2 vPos = GetPos();

	vPos.x += m_fSpeed * fDT * m_iDirection;

	float fDist = abs(vPos.x - m_vCenterPos.x) - m_fPatrolDistance;
	if (0.f < fDist)
	{
		m_iDirection *= -1;
		vPos.x += fDist * m_iDirection;
	}
	
	SetPos(vPos);
}

