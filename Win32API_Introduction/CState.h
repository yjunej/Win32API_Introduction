#pragma once

class AI;
class CEnemy;

class CState
{

private:
	AI* m_pAI;
	ENEMY_STATE m_eState;


public:
	AI* GetAI() const { return m_pAI; };
	ENEMY_STATE GetStateEnum() const { return m_eState; }
	CEnemy* GetOwner() const;


	virtual void Update() = 0;
	virtual void Enter()= 0;
	virtual void Exit()= 0;

public:
	CState(ENEMY_STATE _eState);
	virtual ~CState();
	friend class AI;
};

