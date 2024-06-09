#include "pch.h"
#include "CGravity.h"

#include "CObject.h"
#include "CRigidBody.h"

void CGravity::PostUpdate()
{
	m_pOwner->GetRigidBody()->SetAdditiveAccel(Vec2(0.f, 800.f));
}

void CGravity::SetGround(bool _b)
{
	m_bGround = _b;
	if (m_bGround)
	{
		Vec2 vVelocity = m_pOwner->GetRigidBody()->GetVelocity();
		m_pOwner->GetRigidBody()->SetVelocity(Vec2(vVelocity.x, 0.f));
	}

}


CGravity::CGravity()
	: m_pOwner(nullptr)
	, m_bGround(false)
{	
}

CGravity::~CGravity()
{
}
