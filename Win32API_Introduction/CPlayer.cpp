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
#include "CRigidBody.h"
#include "CGravity.h"
#include "CCamera.h"


CPlayer::CPlayer()
	: m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::WALK)
	, m_iAttackPower(10)
	, m_iDirection(-1)
	, m_fAttackSpeed(2.f)
	, m_iHP(100)
	, m_fAccTime(0.f)
{
    
    CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
    GetCollider()->SetScale(Vec2(30.f, 40.f));

	// Load Texture
	CTexture* pTexIdleLeft = CResourceMgr::GetInstance()->LoadTexture(L"IDLE_LEFT", L"texture\\SoldierIdleLeft200.bmp");
	CTexture* pTexIdleRight = CResourceMgr::GetInstance()->LoadTexture(L"IDLE_RIGHT", L"texture\\SoldierIdleRight200.bmp");
	CTexture* pTexWalkLeft = CResourceMgr::GetInstance()->LoadTexture(L"WALK_LEFT", L"texture\\SoldierWalkLeft200.bmp");
	CTexture* pTexWalkRight = CResourceMgr::GetInstance()->LoadTexture(L"WALK_RIGHT", L"texture\\SoldierWalkRight200.bmp");
	CTexture* pTexSwordAttackLeft = CResourceMgr::GetInstance()->LoadTexture(L"SWORD_ATTACK_LEFT", L"texture\\SoldierSwordAttackLeft200.bmp");
	CTexture* pTexSwordAttackRight = CResourceMgr::GetInstance()->LoadTexture(L"SWORD_ATTACK_RIGHT", L"texture\\SoldierSwordAttackRight200.bmp");

	//CTexture* pTexIdleRight = CResourceMgr::GetInstance()->LoadTexture(L"IDLE_RIGHT", L"texture\\RedHoodIdleRight.bmp");





	CreateAnimator();

	// Load Animation
	//GetAnimator()->LoadAnimation(L"animation\\RedHoodIdleLeft.anim");
	//GetAnimator()->LoadAnimation(L"animation\\RedHoodIdleRight.anim");
	//GetAnimator()->LoadAnimation(L"animation\\RedHoodAttackRight.anim");

	//GetAnimator()->CreateAnimation(L"ATTACK_RIGHT_ANIM", pTexAttackRight, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(80.f, 0.f), 0.05f, 26);
	GetAnimator()->CreateAnimation(L"IDLE_LEFT_ANIM", pTexIdleLeft, Vec2(0.f, 0.f), Vec2(200.f, 200.f), Vec2(200.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT_ANIM", pTexIdleRight, Vec2(0.f, 0.f), Vec2(200.f, 200.f), Vec2(200.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"WALK_LEFT_ANIM", pTexWalkLeft, Vec2(0.f, 0.f), Vec2(200.f, 200.f), Vec2(200.f, 0.f), 0.1f, 8);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT_ANIM", pTexWalkRight, Vec2(0.f, 0.f), Vec2(200.f, 200.f), Vec2(200.f, 0.f), 0.1f, 8);
	GetAnimator()->CreateAnimation(L"SWORD_ATTACK_LEFT_ANIM", pTexSwordAttackLeft, Vec2(1000.f, 0.f), Vec2(200.f, 200.f), Vec2(-200.f, 0.f), 0.3f, 6);
	GetAnimator()->CreateAnimation(L"SWORD_ATTACK_RIGHT_ANIM", pTexSwordAttackRight, Vec2(0.f, 0.f), Vec2(200.f, 200.f), Vec2(200.f, 0.f), 0.3f, 6);

	//GetAnimator()->FindAnimation(L"IDLE_LEFT_ANIM")->Save(L"animation\\RedHoodIdleLeft.anim");
	//GetAnimator()->FindAnimation(L"IDLE_RIGHT_ANIM")->Save(L"animation\\RedHoodIdleRight.anim");
	//GetAnimator()->FindAnimation(L"ATTACK_RIGHT_ANIM")->Save(L"animation\\RedHoodAttackRight.anim");


	GetAnimator()->Play(L"IDLE_LEFT_ANIM", true);

	//CAnimation* pAnim = GetAnimator()->FindAnimation(L"TEST");
	//pAnim->GetFrame(0).vOffset = Vec2(0.f, -20.f);

	//CreateRigidBody();
	//CreateGravity();
}

CPlayer::~CPlayer()
{

}


void CPlayer::Update()
{
	// No Rigid Body
	//Vec2 vPos = GetPos();
 	UpdateMove();
	UpdateState();
	UpdateAnimation();

	/*if (KEY_TAP(KEY::SPACE))
	{
		Fire();
	}*/

	//m_fAccTime += fDT;
	//if (m_fAccTime > 1.f / m_fAttackSpeed)
	//{
	//	Fire();
	//	m_fAccTime = 0;
	//}


	//SetPos(vPos);
	GetAnimator()->Update();

	if ((GetAnimator()->GetCurAnimation()->GetName()).find(L"SWORD") != wstring::npos
		&& GetAnimator()->GetCurAnimation()->GetCurFrame() == 3)
	{
		Fire();
	}

	m_ePrevState = m_eCurState;
	m_iPrevDirection = m_iDirection;

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


	//TransparentBlt(_hdc,
	//	int(vPos.x - (float)(iWidth / 2)),
	//	int(vPos.y - (float)(iHeight / 2)),
	//	iWidth, iHeight,
	//	m_pTexture->GetDC(),
	//	0, 0, iWidth, iHeight,
	//	RGB(0, 0, 0)
	//);

    RenderComponent(_hdc);

	// AlphaBlend
	/*CTexture* pTex = CResourceMgr::GetInstance()->LoadTexture(L"PlayerTexture", L"texture\\RedHoodAttack.bmp");

	Vec2 vPos = GetPos();
	vPos = CCamera::GetInstance()->ScreenPosToRenderPos(vPos);

	float width = (float)pTex->GetWidth();
	float height = (float)pTex->GetHeight();

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;

	AlphaBlend(
		_hdc,
		vPos.x - width / 2.f,
		vPos.y - height / 2.f,
		width,
		height,
		pTex->GetDC(),
		0, 0, width, height, bf
	);*/


}

void CPlayer::OnCollisionBegin(CCollider* _pOtherColl)
{
	CObject* pOhterObj = _pOtherColl->GetOwner();
	if (L"Ground" == pOhterObj->GetName())
	{
		Vec2 vPos = GetPos();
		if (vPos.y < pOhterObj->GetPos().y)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}
}

void CPlayer::Fire()
{
	Vec2 vPos = GetPos();
	//vPos.y -= GetScale().y / 2.f;

	// Create Object
	CBullet* pBullet = new CBullet;
	pBullet->SetName(L"PlayerBullet");
	pBullet->SetPos(vPos);
	pBullet->SetScale(Vec2(25.f, 25.f));
	pBullet->SetDamage(m_iAttackPower);
	pBullet->SetDirection(
		CCamera::GetInstance()->RenderPosToScreenPos(MOUSE_POS) - GetPos()
	);

	// Deprecated - Manage by EventMGr
	//CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
	//pCurScene->AddObject(pBullet, GROUP_TYPE::DEFAULT);
	CreateObject(pBullet, GROUP_TYPE::PROJ_PLAYER);
}

void CPlayer::UpdateState()
{

	if (m_ePrevState == PLAYER_STATE::ATTACK
		&& GetAnimator()->GetCurAnimation()->IsFinish())
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}

	m_vMove = Vec2(0.f, 0.f);

	if (KEY_TAP(KEY::R))
	{
		SetPos(Vec2(640.f, 390.f));
	}
		
	if (KEY_HOLD(KEY::A))
	{
		m_iDirection = -1;
		m_vMove.x -= 1;
		if (m_eCurState != PLAYER_STATE::ATTACK)
		{
			m_eCurState = PLAYER_STATE::WALK;
		}
	}
	if (KEY_HOLD(KEY::D))
	{
		m_vMove.x += 1;
		m_iDirection = 1;
		if (m_eCurState != PLAYER_STATE::ATTACK)
		{
			m_eCurState = PLAYER_STATE::WALK;
		}
	}

	if (KEY_HOLD(KEY::W))
	{
		m_vMove.y += 1;
		if (m_eCurState != PLAYER_STATE::ATTACK)
		{
			m_eCurState = PLAYER_STATE::WALK;
		}
	}
	if (KEY_HOLD(KEY::S))
	{
		m_vMove.y -= 1;
		if (m_eCurState != PLAYER_STATE::ATTACK)
		{
			m_eCurState = PLAYER_STATE::WALK;
		}
	}
	//if (0.f == GetRigidBody()->GetSpeed() && KEY_NONE(KEY::A) && KEY_NONE(KEY::D))
	/*if(KEY_NONE(KEY::A) && KEY_NONE(KEY::D) && KEY_NONE(KEY::W) && KEY_NONE(KEY::S))
	{
		if (m_eCurState != PLAYER_STATE::DASH)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}*/

	if (m_vMove.IsZero())
	{
		if (m_eCurState != PLAYER_STATE::ATTACK)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}

	// Priority Index 0




	if (KEY_HOLD(KEY::SPACE))
	{
		m_eCurState = PLAYER_STATE::ATTACK;
	}
	



	//if (KEY_TAP(KEY::F))
	//{
	//	m_eCurState = PLAYER_STATE::DASH;
	//	if (GetRigidBody())
	//	{
	//		Vec2 vDashVelocity(0.f, 0.f);
	//		if (KEY_HOLD(KEY::W))
	//			vDashVelocity.y -= 1;
	//		if (KEY_HOLD(KEY::A))
	//			vDashVelocity.x -= 1;
	//		if (KEY_HOLD(KEY::S))
	//			vDashVelocity.y += 1;
	//		if (KEY_HOLD(KEY::D))
	//			vDashVelocity.x += 1;
	//		if (vDashVelocity.IsZero())
	//		{
	//			vDashVelocity = Vec2(m_iDirection, 0);
	//		}
	//		vDashVelocity.Normalize();
	//		//GetRigidBody()->AddVelocity(vDashVelocity * 1200);
	//	}
	//}
	
}

void CPlayer::UpdateMove()
{
	//CRigidBody* pRigidBody = GetRigidBody();
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT;
		//pRigidBody->AddForce(Vec2(0.f, -200.f));
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;
		//pRigidBody->AddForce(Vec2(-200.f, 0.f));

	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;
		//pRigidBody->AddForce(Vec2(0.f, 200.f));
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT;
		//pRigidBody->AddForce(Vec2(200.f, 0.f));
	}
	SetPos(vPos);

	//if (KEY_TAP(KEY::W))
	//{
	//	//vPos.y -= 200.f * fDT;
	//	//pRigidBody->AddVelocity(Vec2(0.f, -100.f));
	//}
	//if (KEY_TAP(KEY::A))
	//{
	//	//vPos.x -= 200.f * fDT;
	//	pRigidBody->AddVelocity(Vec2(-100.f, 0.f));

	//}
	//if (KEY_TAP(KEY::S))
	//{
	//	//vPos.y += 200.f * fDT;
	//	pRigidBody->AddVelocity(Vec2(0.f, 100.f));
	//}
	//if (KEY_TAP(KEY::D))
	//{
	//	//vPos.x += 200.f * fDT;
	//	pRigidBody->AddVelocity(Vec2(100.f, 0.f));
	//}
}

void CPlayer::UpdateAnimation()
{
	// Check State Changed
	if (m_ePrevState == m_eCurState && m_iPrevDirection == m_iDirection && m_ePrevState != PLAYER_STATE::ATTACK)
	{
		return;
	}
	switch	(m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (m_iDirection == 1)
		{
			GetAnimator()->Play(L"IDLE_RIGHT_ANIM", true);
		}
		else
		{
			GetAnimator()->Play(L"IDLE_LEFT_ANIM", true);
		}
	}
		break;
	case PLAYER_STATE::WALK:
	{
		if (m_iDirection == 1)
		{
			GetAnimator()->Play(L"WALK_RIGHT_ANIM", true);
		}
		else
		{
			GetAnimator()->Play(L"WALK_LEFT_ANIM", true);
		}
	}
		break;
	case PLAYER_STATE::ATTACK:
	{
 		if (m_ePrevState == PLAYER_STATE::ATTACK && !(GetAnimator()->GetCurAnimation()->IsFinish()))
		{
			break;
		}
		if (m_iDirection == 1)
		{
			GetAnimator()->Play(L"SWORD_ATTACK_RIGHT_ANIM", false);
			GetAnimator()->GetCurAnimation()->ResetAnim();
		}
		else
		{
			GetAnimator()->Play(L"SWORD_ATTACK_LEFT_ANIM", false);
			GetAnimator()->GetCurAnimation()->ResetAnim();
		}
	}
		break;
	case PLAYER_STATE::DEAD:
		break;
	default:
		break;
	}
}

void CPlayer::UpdateGravity()
{
	GetRigidBody()->AddForce(Vec2(0.f,500.f));
}
