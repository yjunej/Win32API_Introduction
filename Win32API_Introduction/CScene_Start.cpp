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

	// Copy Player Example

	//CObject* pOtherPlayer = pObj->Clone();
	//pOtherPlayer->SetPos(Vec2(
	//	pOtherPlayer->GetPos().x + pOtherPlayer->GetScale().x,
	//	pOtherPlayer->GetPos().y));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	// Camera Follow Player
	//CCamera::GetInstance()->SetFocus(pObj);

	int iNumEnemy = 2;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;

	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	float fInterval = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iNumEnemy-1);

	CEnemy* pEnemy = nullptr;

	for (int i = 0; i < iNumEnemy; ++i)
	{
		pEnemy = new CEnemy;
		pEnemy->SetName(L"Enemy");
		pEnemy->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i * fInterval, 50.f));
		pEnemy->SetCenterPos(pEnemy->GetPos()); 
		pEnemy->SetPatrolDistance(fMoveDist);
		pEnemy->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pEnemy, GROUP_TYPE::ENEMY);
	}

	// Collision
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ENEMY);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::ENEMY);

	// Set Camera
	CCamera::GetInstance()->SetLookPos(vResolution / 2.f);
}

void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInstance()->Reset();
}
