#include "pch.h"
#include "CRigidBody.h"
#include "CObject.h"
#include "CTimeMgr.h"

void CRigidBody::PostUpdate()	
{
	// Unit Vector * Scalar - Divide 

	float fForceSize = m_vForce.IsZero() ? 0.f : m_vForce.GetLength(); 
	if (fForceSize != 0.f)
	{
		m_vForce.Normalize(); // Convert to Direction Vector

		float fAccelSize = fForceSize / m_fMass; // 
		m_vAccel = m_vForce * fAccelSize;

		//m_vAccel = m_vForce / m_fMass; // a = F / m
	}

	m_vAccel += m_vAdditiveAccel;
	SetVelocity(GetVelocity() + m_vAccel * fDT);


	// Friction
	if (!GetVelocity().IsZero())
	{
		Vec2 vFrictionDirection = -GetVelocity();
		vFrictionDirection.Normalize();
		
		Vec2 vFriction = vFrictionDirection* m_fFrictionCoef * fDT;
		if (GetVelocity().GetLength() <= vFriction.GetLength())
		{
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity = GetVelocity() + vFriction;
		}

	}
	if (abs(m_vMaxVelocity.x) < abs(m_vVelocity.x))
	{
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}
	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}
	Move();
	ClearPhysics();
}

void CRigidBody::ClearPhysics()
{
	m_vForce = Vec2(0.f, 0.f);
	m_vAdditiveAccel = Vec2(0.f, 0.f);
	m_vAccel = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	if (GetVelocity().IsZero())
		return;
	float fSpeed = GetVelocity().GetLength();
	Vec2 vPos = m_pOwner->GetPos();
	vPos += GetVelocity() * fDT;
	m_pOwner->SetPos(vPos);
}

CRigidBody::CRigidBody()
	: m_fMass(1.f)
	, m_pOwner(nullptr)
	, m_fFrictionCoef(100.f)
	, m_vMaxVelocity(Vec2(2000.f, 6000.f))
{
}

CRigidBody::~CRigidBody()
{
}
