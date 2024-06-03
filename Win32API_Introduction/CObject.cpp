#include "pch.h"
#include "CObject.h"

#include "CCollider.h"
#include "CAnimator.h"

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

	if (nullptr != _cobj.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*_cobj.m_pAnimator);
		m_pAnimator->m_pOwner = this;
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
	Vec2 vRenderPos = CCamera::GetInstance()->GetRenderPos(m_vPos);
	Rectangle(
		_hdc, 
		(int)(vRenderPos.x - m_vScale.x / 2.f),
		(int)(vRenderPos.y - m_vScale.y / 2.f),
		(int)(vRenderPos.x + m_vScale.x / 2.f),
		(int)(vRenderPos.y + m_vScale.y / 2.f)
	);
	RenderComponent(_hdc);
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;

}

void CObject::RenderComponent(HDC _hdc)
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->Render(_hdc);
	}
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->Render(_hdc);
	}
}
