#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CCore.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCamera.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Update()
{
	CScene::Update();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vFocusPos = CCamera::GetInstance()->RenderPosToScreenPos(MOUSE_POS);
		CCamera::GetInstance()->SetLookPos(vFocusPos);

	}

}

void CScene_Start::Enter()
{

	// Add Object
	CObject* pObj = new CPlayer;
	
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	// Copy Player Example

	//CObject* pOtherPlayer = pObj->Clone();
	//pOtherPlayer->SetPos(Vec2(
	//	pOtherPlayer->GetPos().x + pOtherPlayer->GetScale().x,
	//	pOtherPlayer->GetPos().y));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	// Camera Follow Player

	//CCamera::GetInstance()->SetFocus(pObj);


	// Spawn Enemy
	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	CEnemy* pEnemy = CEnemySpawner::SpawnEnemy(ENEMY_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f, 300.f));
	AddObject(pEnemy, GROUP_TYPE::ENEMY);


	// LoadTile
	//LoadTile(L"Tile\\Start.tile");


	// Collision
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ENEMY);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::ENEMY);

	// Set Camera
	CCamera::GetInstance()->SetLookPos(vResolution / 2.f);

	// Camera Effect
	CCamera::GetInstance()->FadeOut(4.f);
	CCamera::GetInstance()->FadeIn(4.f);

}

void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInstance()->Reset();
}
