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


CPlayer::CPlayer()
	: m_pTexture(nullptr)
{
	// Load Texture
    m_pTexture = CResourceMgr::GetInstance()->LoadTexture(L"PlayerTexture", L"\\texture\\player.bmp");
    
    CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(-2.f, 5.f));
    GetCollider()->SetScale(Vec2(30.f, 50.f));
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
}

void CPlayer::Render(HDC _hdc)
{
	int iWidth = (int)m_pTexture->GetWidth();
	int iHeight = (int)m_pTexture->GetHeight();

	Vec2 vPos = GetPos();

	/*BitBlt(_hdc,
		int(vPos.x - (float)(iWidth / 2)),
		int(vPos.y - (float)(iHeight / 2)),
		iWidth, iHeight,
		m_pTexture->GetDC(),
		0, 0, SRCCOPY
	);	*/

    

    //SaveHBITMAPToFile(CreateCompatibleBitmap(_hdc, CCore::GetInstance()->GetResolution().x, CCore::GetInstance()->GetResolution().y), L"t.bmp");

	TransparentBlt(_hdc,
		int(vPos.x - (float)(iWidth / 2)),
		int(vPos.y - (float)(iHeight / 2)),
		iWidth, iHeight,
		m_pTexture->GetDC(),
		0, 0, iWidth, iHeight,
		RGB(0, 0, 0)
	);

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
