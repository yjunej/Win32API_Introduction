#include "pch.h"
#include "CEnemySpawner.h"

#include "CEnemy.h"
#include "AI.h"

#include "CIdleState.h"
#include "CTraceState.h"
#include "CRigidBody.h"
#include "CResourceMgr.h"
#include "CAnimator.h"

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

		// Load Texture, Animation
		CTexture* pTexWalkLeft = CResourceMgr::GetInstance()->LoadTexture(L"ORC_WALK_LEFT", L"texture\\OrcWalkLeft200.bmp");
		CTexture* pTexWalkRight = CResourceMgr::GetInstance()->LoadTexture(L"ORC_WALK_RIGHT", L"texture\\OrcWalkRight200.bmp");
		pEnemy->CreateAnimator();
		pEnemy->GetAnimator()->CreateAnimation(L"WALK_LEFT_ANIM", pTexWalkLeft, Vec2(0.f, 0.f), Vec2(200.f, 200.f), Vec2(200.f, 0.f), 0.2f, 8);
		pEnemy->GetAnimator()->CreateAnimation(L"WALK_RIGHT_ANIM", pTexWalkRight, Vec2(0.f, 0.f), Vec2(200.f, 200.f), Vec2(200.f, 0.f), 0.2f, 8);
		pEnemy->GetAnimator()->Play(L"WALK_LEFT_ANIM", true);



		tEnemyInfo info = {};
		info.fAttackPower = 10.f;
		info.fAttackRange = 50.f;
		info.fLOS = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 150.f;

		pEnemy->SetEnemyInfo(info);
		pEnemy->CreateRigidBody();
		pEnemy->GetRigidBody()->SetMass(1.f);

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
