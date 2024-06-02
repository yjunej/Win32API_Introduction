#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"

#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
{
}

CCollider::~CCollider()
{
}


void CCollider::PostUpdate()
{
	Vec2 vOwnerPos = m_pOwner->GetPos();
	m_vCollPos = vOwnerPos + m_vOffsetPos;
}

void CCollider::Render(HDC _hdc)
{
	SelectGDI _n0(_hdc, PEN_TYPE::GREEN);
	SelectGDI _n1(_hdc, BRUSH_TYPE::HOLLOW);

	Rectangle(
		_hdc,
		(int)(m_vCollPos.x - m_vScale.x / 2.f),
		(int)(m_vCollPos.y - m_vScale.y / 2.f),
		(int)(m_vCollPos.x + m_vScale.x / 2.f),
		(int)(m_vCollPos.y + m_vScale.y / 2.f)
	);

}
