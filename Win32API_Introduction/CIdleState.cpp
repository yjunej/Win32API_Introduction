#include "pch.h"
#include "CIdleState.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CEnemy.h"

CIdleState::CIdleState()
	: CState(ENEMY_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::Update()
{
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInstance()->GetCurScene()->GetPlayer();

	Vec2 vPlayerPos = pPlayer->GetPos();

	CEnemy* pEnemy = GetOwner();
	Vec2 vEnemyPos = pEnemy->GetPos();

	Vec2 vDiff = vPlayerPos - vEnemyPos;
	if (vDiff.GetLength() <= pEnemy->GetInfo().fLOS)
	{
		ChangeAIState(GetAI(), ENEMY_STATE::TRACE);
	}


}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}

