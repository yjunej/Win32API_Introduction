#include "pch.h"
#include "CObject.h"

#include "CCollider.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_bAlive(true)
{
}

CObject::~CObject()
{
	if (nullptr != m_pCollider)
	{
		delete m_pCollider;
	}
	if (nullptr != m_pAnimator)
	{
		delete m_pAnimator;
	}
}

CObject::CObject(const CObject& _cobj)
	: m_strName(_cobj.m_strName)
	, m_vPos(_cobj.m_vPos)
	, m_vScale(_cobj.m_vScale)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_bAlive(true)
{
	if (nullptr != _cobj.m_pCollider)
	{
		m_pCollider = new CCollider(*_cobj.m_pCollider);
		m_pCollider->m_pOwner = this;
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
