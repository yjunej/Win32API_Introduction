#include "pch.h"
#include "CBullet.h"

#include "CTimeMgr.h"
#include "CCollider.h"


CBullet::CBullet()
	: m_fSpeed(600.f)
	, m_fTheta(PI / 2.f)
	, m_vDirection(Vec2(1.f, 1.f))
{
	m_vDirection.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f));
}

CBullet::~CBullet()
{
}

void CBullet::Update()
{
	Vec2 vPos = GetPos();

	//vPos.x += 200.f * fDT * cosf(m_fTheta);
	//vPos.y -= 200.f * fDT * sinf(m_fTheta);
	vPos.x += m_fSpeed * fDT * m_vDirection.x;
	vPos.y += m_fSpeed * fDT * m_vDirection.y;

	SetPos(vPos);
}

void CBullet::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(
		_hdc,
		(int)(vPos.x - vScale.x / 2.f),
		(int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f),
		(int)(vPos.y + vScale.y / 2.f)
	);

	RenderComponent(_hdc);
}

void CBullet::OnCollisionBegin(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetOwner();
	if (pOtherObj->GetName() == L"Enemy")
	{
		DeleteObject(this);
	}
}