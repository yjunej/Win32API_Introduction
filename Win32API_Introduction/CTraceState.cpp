#include "pch.h"
#include "CTraceState.h"


#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CTimeMgr.h"

void CTraceState::Update()
{
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInstance()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();
	Vec2 vEnemyPos = GetOwner()->GetPos();
	Vec2 vToPlayer = vPlayerPos - vEnemyPos;
	if (vToPlayer.IsZero())
		return;

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
{
}

CTraceState::~CTraceState()
{
}