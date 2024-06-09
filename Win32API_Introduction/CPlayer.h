#pragma once
#include "CObject.h"

enum class PLAYER_STATE
{
	IDLE,
	WALK,
	ATTACK,
	DASH,
	DEAD,
};

enum class PLAYER_ATTACK
{
	NORMAL_ATT_1,
	//
};



class CTexture;

class CPlayer : public CObject
{

private:
	vector<CObject*> m_vecCollObj;
	int m_iDirection;
	int m_iPrevDirection;
	PLAYER_STATE m_eCurState;
	PLAYER_STATE m_ePrevState;

public:
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void OnCollisionBegin(CCollider* _pOtherColl) override;


	PLAYER_STATE GetCurState() const { return m_eCurState; }
	void SetCurState(PLAYER_STATE val) { m_eCurState = val; }

	// Covariant return type
	virtual CLONE(CPlayer)

private:
	void Fire();
	void UpdateState();
	void UpdateMove();
	void UpdateAnimation();
	void UpdateGravity();

public:
	CPlayer();
	~CPlayer();
};

