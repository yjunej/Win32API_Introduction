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
	SWORD_ATT_1,
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
	Vec2 m_vMove;

	PLAYER_STATE m_eCurState;
	PLAYER_STATE m_ePrevState;

	float m_fAccTime;

	// Stat
	int m_iAttackPower = 0;
	float m_fAttackSpeed = 0; // Attack per sec
	int m_iHP = 0;

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

