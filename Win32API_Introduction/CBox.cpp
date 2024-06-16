#include "CBox.h"
#include "CTexture.h"
#include "CResourceMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CPlayer.h"

CBox::CBox()
	: m_iBulletCountUp(0)
	, m_fHPUp(0.f)
	, m_fDamageUp(0.f)
	, m_fAttackSpeedUp(0.f)
{
	CTexture* pTexBoxIdle = CResourceMgr::GetInstance()->LoadTexture(L"BOX_IDLE", L"texture\\ItemBoxIdle.bmp");
	CTexture* pTexBoxOpen = CResourceMgr::GetInstance()->LoadTexture(L"BOX_OPEN", L"texture\\ItemBox.bmp");


	CreateAnimator();
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(32.f, 32.f));
	GetAnimator()->CreateAnimation(L"BOX_IDLE_ANIM", pTexBoxIdle, Vec2(0.f, 0.f), Vec2(31.f, 32.f), Vec2(0.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"BOX_OPEN_ANIM", pTexBoxOpen, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 4);
	GetAnimator()->Play(L"BOX_IDLE_ANIM", true);

}

CBox::~CBox()
{
}


void CBox::Update()
{
	CAnimation* pCurAnim = GetAnimator()->GetCurAnimation();
	if (pCurAnim->GetName().find(L"OPEN") != wstring::npos && pCurAnim->IsFinish())
	{
		DeleteObject(this);
	}
}

void CBox::Render(HDC _hdc)
{
	//Vec2 vRenderPos = CCamera::GetInstance()->ScreenPosToRenderPos(GetPos());
	//wchar_t szText[256] = {};
	//swprintf_s(szText, L"Player Pos : %.2f, %.2f", PlayerPos.x, PlayerPos.y);
	//TextOut(_hdc, 0, 0, szText, (int)wcslen(szText));

	RenderComponent(_hdc);
}

void CBox::OnCollisionBegin(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetOwner();

	if (pOtherObj->GetName() == L"Player")
	{
		GetAnimator()->Play(L"BOX_OPEN_ANIM", false);
		CPlayer* pPlayer = (CPlayer*)_pOther->GetOwner();
		pPlayer->SetAttackPower(
			pPlayer->GetAttackPower() + m_fDamageUp
		);
		pPlayer->SetNumBullets(
			pPlayer->GetNumBullets() + m_iBulletCountUp
		);
		pPlayer->SetHP(
			 pPlayer->GetHP() + m_fHPUp < 100 ? pPlayer->GetHP() + m_fHPUp : 100.f
		);
		pPlayer->SetAttackSpeed(
			pPlayer->GetAttackSpeed() + m_fAttackSpeedUp
		);

		pPlayer->GetAnimator()->SetDuration(L"BOW_ATTACK_LEFT_ANIM", 1 / pPlayer->GetAttackSpeed() / 9.f);
		pPlayer->GetAnimator()->SetDuration(L"BOW_ATTACK_RIGHT_ANIM", 1 / pPlayer->GetAttackSpeed() / 9.f);
	}
}
