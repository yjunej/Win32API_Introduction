#pragma once

#include "CObject.h"

class CCollider;

class CEnemy : public CObject
{

private:
	Vec2  m_vCenterPos;
	float m_fSpeed;
	float m_fPatrolDistance;
	int   m_iDirection;
	int	  m_iHP;

public:
	float GetSpeed() const { return m_fSpeed; }
	void SetSpeed(float _f) { m_fSpeed = _f; }
	void SetPatrolDistance(float _f) { m_fPatrolDistance = _f; }
	void SetCenterPos(Vec2 _vec) { m_vCenterPos = _vec; }

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionBegin(CCollider* _pOther);
	virtual void OnCollisionEnd(CCollider* _pOther);



public:
	virtual void Update() override;

public:
	CEnemy();
	~CEnemy();

};

