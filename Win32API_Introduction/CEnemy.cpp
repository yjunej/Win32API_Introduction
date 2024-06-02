#include "pch.h"
#include "CEnemy.h"

#include "CTimeMgr.h"
#include "CCollider.h"


CEnemy::CEnemy()
	: m_fSpeed(100.f)
	, m_vCenterPos(Vec2(0.f, 0.f))
	, m_fPatrolDistance(50.f)
	, m_iDirection(1)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
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

