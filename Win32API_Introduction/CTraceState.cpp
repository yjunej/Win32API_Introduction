#include "pch.h"
#include "CTraceState.h"


#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CTimeMgr.h"
#include "CAnimator.h"

void CTraceState::Update()
{
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInstance()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();
	Vec2 vEnemyPos = GetOwner()->GetPos();
	Vec2 vToPlayer = vPlayerPos - vEnemyPos;
	if (vToPlayer.IsZero())
		return;

	if (vToPlayer.x > 1 && m_iDirection == -1)
	{
		GetOwner()->GetAnimator()->Play(L"WALK_RIGHT_ANIM", true);
		m_iDirection = 1;
	}
	else if (vToPlayer.x < 1 && m_iDirection == 1)
	{
		GetOwner()->GetAnimator()->Play(L"WALK_LEFT_ANIM", true);
		m_iDirection = -1;
	}
	vToPlayer.Normalize();


	vEnemyPos += vToPlayer * GetOwner()->GetInfo().fSpeed * fDT;
	GetOwner()->SetPos(vEnemyPos);
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}

CTraceState::CTraceState()
	: CState(ENEMY_STATE::TRACE)
	, m_iDirection(-1)
{
}

CTraceState::~CTraceState()
{
}
