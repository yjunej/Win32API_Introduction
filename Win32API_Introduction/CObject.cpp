#include "pch.h"
#include "CObject.h"

#include "CCollider.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
{
}

CObject::~CObject()
{
	if (nullptr != m_pCollider)
	{
		delete m_pCollider;
	}
}


void CObject::PostUpdate()
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->PostUpdate();
	}
}

void CObject::Render(HDC _hdc)
{
	Rectangle(
		_hdc, 
		(int)(m_vPos.x - m_vScale.x / 2.f),
		(int)(m_vPos.y - m_vScale.y / 2.f),
		(int)(m_vPos.x + m_vScale.x / 2.f),
		(int)(m_vPos.y + m_vScale.y / 2.f)
	);
	RenderComponent(_hdc);
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CObject::RenderComponent(HDC _hdc)
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->Render(_hdc);
	}
}
