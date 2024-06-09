#pragma once

#include "CObject.h"

class AI;

struct tEnemyInfo
{
	float fSpeed;
	float fHP;
	float fLOS; // Sight Range
	float fAttackRange;  // Attack Range
	float fAttackPower;
};

class AI;
class CCollider;

class CEnemy : public CObject
{

private:
	tEnemyInfo m_tInfo;
	AI*   m_pAI;

public:
	float GetSpeed() const { return m_tInfo.fSpeed; }
	void SetSpeed(float _f) { m_tInfo.fSpeed = _f; }
	const tEnemyInfo& GetInfo() const { return m_tInfo; }

	void SetAI(AI* pAI);


	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionBegin(CCollider* _pOther);
	virtual void OnCollisionEnd(CCollider* _pOther);

private:
	void SetEnemyInfo(const tEnemyInfo& _tInfo)
	{
		m_tInfo = _tInfo;
	}

public:
	virtual void Update() override;
	virtual CLONE(CEnemy)

public:
	CEnemy();
	~CEnemy();
	friend class CEnemySpawner;	
};

