#include "pch.h"
#include "CEnemySpawner.h"

#include "CEnemy.h"
#include "AI.h"

#include "CIdleState.h"
#include "CTraceState.h"

CEnemySpawner::CEnemySpawner()
{
}

CEnemySpawner::~CEnemySpawner()
{
}

CEnemy* CEnemySpawner::SpawnEnemy(ENEMY_TYPE _eType, Vec2 _vPos)
{
	CEnemy* pEnemy = nullptr;

	switch (_eType)
	{
	case ENEMY_TYPE::NORMAL:
	{
		pEnemy = new CEnemy;
		pEnemy->SetPos(_vPos);

		tEnemyInfo info = {};
		info.fAttackPower = 10.f;
		info.fAttackRange = 50.f;
		info.fLOS = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 150.f;

		pEnemy->SetEnemyInfo(info);


		AI* pAI = new AI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CTraceState);
		pAI->SetCurState(ENEMY_STATE::IDLE);

		pEnemy->SetAI(pAI);

		break;
	}
	case ENEMY_TYPE::BOSS:
		break;
	default:
		break;
	}

	assert(pEnemy);

	return pEnemy;
}
