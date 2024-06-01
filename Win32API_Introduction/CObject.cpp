#include "pch.h"
#include "CObject.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
{
}

CObject::~CObject()
{
}

void CObject::Update()
{
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::W) == KEY_STATE::HOLD)
	{
		m_vPos.y -= 200.f * fDT;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::A) == KEY_STATE::HOLD)
	{
		m_vPos.x -= 200.f * fDT;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::S) == KEY_STATE::HOLD)
	{
		m_vPos.y += 200.f * fDT;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
	{
		m_vPos.x += 200.f * fDT;
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


}