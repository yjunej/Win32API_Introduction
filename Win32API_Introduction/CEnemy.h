#pragma once

#include "CObject.h"
class CEnemy : public CObject
{

private:
	Vec2  m_vCenterPos;
	float m_fSpeed;
	float m_fPatrolDistance;
	int   m_iDirection;

public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float _f) { m_fSpeed = _f; }
	void SetPatrolDistance(float _f) { m_fPatrolDistance = _f; }
	void SetCenterPos(Vec2 _vec) { m_vCenterPos = _vec; }


public:
	virtual void Update() override;

public:
	CEnemy();
	~CEnemy();

};

