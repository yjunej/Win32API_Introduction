#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CResourceMgr.h"

#include "CScene.h"
#include "CObject.h"

#include "CBullet.h"
#include "CTexture.h"

#include "CCore.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"


CPlayer::CPlayer()
{
    
    CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(-2.f, 5.f));
    GetCollider()->SetScale(Vec2(30.f, 50.f));

	// Load Texture
	//CTexture* pTex = CResourceMgr::GetInstance()->LoadTexture(L"PlayerTexture", L"\\texture\\galaga.bmp");
	CTexture* pTex = CResourceMgr::GetInstance()->LoadTexture(L"PlayerTexture", L"texture\\RedHoodAttack.bmp");


	CreateAnimator();
	//GetAnimator()->CreateAnimation(L"TEST", pTex, Vec2(4.f, 4.f), Vec2(64.f, 64.f), Vec2(72.f, 0.f), 0.2f,7);
	GetAnimator()->CreateAnimation(L"TEST", pTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(80.f, 0.f), 0.03f, 26);

	GetAnimator()->Play(L"TEST", true);

	//CAnimation* pAnim = GetAnimator()->FindAnimation(L"TEST");
	//pAnim->GetFrame(0).vOffset = Vec2(0.f, -20.f);
}

CPlayer::~CPlayer()
{

}


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
	GetAnimator()->Update();
}

void CPlayer::Render(HDC _hdc)
{

	//Vec2 vPos = GetPos();

	/*BitBlt(_hdc,
		int(vPos.x - (float)(iWidth / 2)),
		int(vPos.y - (float)(iHeight / 2)),
		iWidth, iHeight,
		m_pTexture->GetDC(),
		0, 0, SRCCOPY
	);	*/

    

    //SaveHBITMAPToFile(CreateCompatibleBitmap(_hdc, CCore::GetInstance()->GetResolution().x, CCore::GetInstance()->GetResolution().y), L"t.bmp");

	//TransparentBlt(_hdc,
	//	int(vPos.x - (float)(iWidth / 2)),
	//	int(vPos.y - (float)(iHeight / 2)),
	//	iWidth, iHeight,
	//	m_pTexture->GetDC(),
	//	0, 0, iWidth, iHeight,
	//	RGB(0, 0, 0)
	//);

    RenderComponent(_hdc);
}

void CPlayer::Fire()
{
	Vec2 vPos = GetPos();
	vPos.y -= GetScale().y / 2.f;

	// Create Object
	CBullet* pBullet = new CBullet;
	pBullet->SetName(L"PlayerBullet");
	pBullet->SetPos(vPos);
	pBullet->SetScale(Vec2(25.f, 25.f));
	pBullet->SetDirection(Vec2(0.f, -1.f));

	// Deprecated - Manage by EventMGr
	//CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
	//pCurScene->AddObject(pBullet, GROUP_TYPE::DEFAULT);
	CreateObject(pBullet, GROUP_TYPE::PROJ_PLAYER);
}
