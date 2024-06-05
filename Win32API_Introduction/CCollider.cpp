#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"
#include "CCamera.h"

#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
	, m_iColl(0)
{
}

CCollider::~CCollider()
{
}

CCollider::CCollider(const CCollider& _collider)
	: m_pOwner(nullptr)
	, m_vOffsetPos(_collider.m_vOffsetPos)
	, m_vScale(_collider.m_vScale)
	, m_iID(g_iNextID++)
	, m_iColl(0)
{

}


void CCollider::PostUpdate()
{
	Vec2 vOwnerPos = m_pOwner->GetPos();
	m_vCollPos = vOwnerPos + m_vOffsetPos;
	assert(m_iColl >= 0);
}

void CCollider::Render(HDC _hdc)
{
	PEN_TYPE ePenType = PEN_TYPE::GREEN;
	BRUSH_TYPE eBrushType = BRUSH_TYPE::HOLLOW;

	if (m_iColl) { ePenType = PEN_TYPE::RED; }

	SelectGDI _n0(_hdc, ePenType);
	SelectGDI _n1(_hdc, eBrushType);

	Vec2 vRenderPos = CCamera::GetInstance()->ScreenPosToRenderPos(m_vCollPos);

	Rectangle(
		_hdc,
		(int)(vRenderPos.x - m_vScale.x / 2.f),
		(int)(vRenderPos.y - m_vScale.y / 2.f),
		(int)(vRenderPos.x + m_vScale.x / 2.f),
		(int)(vRenderPos.y + m_vScale.y / 2.f)
	);

}

void CCollider::OnCollision(CCollider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void CCollider::OnCollisionBegin(CCollider* _pOther)
{
	++m_iColl;
	m_pOwner->OnCollisionBegin(_pOther);
}

void CCollider::OnCollisionEnd(CCollider* _pOther)
{
	--m_iColl;
	m_pOwner->OnCollisionEnd(_pOther);
}
