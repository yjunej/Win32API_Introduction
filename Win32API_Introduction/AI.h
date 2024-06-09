#pragma once

class CEnemy;
class CState;	

class AI
{
private:
	map<ENEMY_STATE, CState*> m_mapState;
	CState* m_pCurState;
	CEnemy* m_pOwner;
	
public:
	void Update();
	void AddState(CState* _pState);
	CState* GetState(ENEMY_STATE _eState);

	CEnemy* GetOwner() const { return m_pOwner; }
	void SetCurState(ENEMY_STATE _eState);
	void ChangeState(ENEMY_STATE _eNewState);


public:
	AI();
	~AI();
	friend class CEnemy;
};

