#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"

#include "CScene.h"
#include "CObject.h"
#include "CBullet.h"

void CPlayer::Update()
{
	Vec2 vPos = GetPos();
	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT;
	}
	if (KEY_TAP(KEY::SPACE))
	{
		Fire();
	}

	SetPos(vPos);
}

void CPlayer::Fire()
{
	Vec2 vPos = GetPos();
	vPos.y -= GetScale().y / 2.f;

	// Create Object
	CBullet* pBullet = new CBullet;
	pBullet->SetPos(vPos);
	pBullet->SetScale(Vec2(25.f, 25.f));
	pBullet->SetDirection(Vec2(-5.f, -5.f));

	CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
	pCurScene->AddObject(pBullet, GROUP_TYPE::DEFAULT);
}
