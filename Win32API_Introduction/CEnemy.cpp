#include "pch.h"
#include "CEnemy.h"

#include "CTimeMgr.h"
#include "CCollider.h"


CEnemy::CEnemy()
	: m_fSpeed(100.f)
	, m_vCenterPos(Vec2(0.f, 0.f))
	, m_fPatrolDistance(50.f)
	, m_iDirection(1)
	, m_iHP(5)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CEnemy::~CEnemy()
{
}

void CEnemy::OnCollision(CCollider* _pOther)
{
}

void CEnemy::OnCollisionBegin(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetOwner();

	if (pOtherObj->GetName() == L"PlayerBullet")
	{
		m_iHP -= 1;
		if (m_iHP <= 0)
		{
			DeleteObject(this);
		}
	}
}

void CEnemy::OnCollisionEnd(CCollider* _pOther)
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

