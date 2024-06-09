#include "pch.h"
#include "CGround.h"

#include "CCollider.h"
#include "CObject.h"
#include "CGravity.h"

void CGround::OnCollisionBegin(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetOwner();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(true);
		Vec2 vOtherCollPos = _pOther->GetCollPos();
		Vec2 vOtherCollScale = _pOther->GetScale();
		Vec2 vPos = GetCollider()->GetCollPos();
		Vec2 vScale = GetCollider()->GetScale();

		float fLength = abs(vOtherCollPos.y - vPos.y);
		float fLiftPos = (vOtherCollScale.y / 2.f + vScale.y / 2.f) - fLength;
		Vec2 vObjPos = pOtherObj->GetPos();
		vObjPos.y -= fLiftPos;

		pOtherObj->SetPos(vObjPos);
	}
}

void CGround::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetOwner();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(true);
		Vec2 vOtherCollPos = _pOther->GetCollPos();
		Vec2 vOtherCollScale = _pOther->GetScale();
		Vec2 vPos = GetCollider()->GetCollPos();
		Vec2 vScale = GetCollider()->GetScale();

		float fLength = abs(vOtherCollPos.y - vPos.y);
		float fLiftPos = (vOtherCollScale.y / 2.f + vScale.y / 2.f) - fLength;
		Vec2 vObjPos = pOtherObj->GetPos();
		vObjPos.y -= fLiftPos;
		pOtherObj->SetPos(vObjPos);
	}
}

void CGround::OnCollisionEnd(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetOwner();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(false);
	}
}

void CGround::Update()
{
}

void CGround::BeginPlay()
{
	GetCollider()->SetScale(GetScale());
}

CGround::CGround()
{
	CreateCollider();
}

CGround::~CGround()
{
}
