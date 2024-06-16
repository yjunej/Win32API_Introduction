#include "pch.h"
#include "CEnemy.h"

#include "CTimeMgr.h"
#include "CCollider.h"
#include "AI.h"
#include "CBullet.h"


CEnemy::CEnemy()
	: m_tInfo{}
	, m_pAI(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CEnemy::~CEnemy()
{
	if (nullptr != m_pAI)
		delete m_pAI;
}

void CEnemy::SetAI(AI* pAI)
{
	m_pAI = pAI;
	m_pAI->m_pOwner = this;
}

void CEnemy::OnCollision(CCollider* _pOther)
{
}

void CEnemy::OnCollisionBegin(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetOwner();

	if (pOtherObj->GetName() == L"PlayerArrow")
	{
		CBullet* pBullet = (CBullet*)pOtherObj;


		m_tInfo.fHP -= pBullet->GetDamage();
		
		if (m_tInfo.fHP <= 0)
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
	if (nullptr != m_pAI)
	{
		m_pAI->Update();
	}
}

