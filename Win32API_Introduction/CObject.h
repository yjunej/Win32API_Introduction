#pragma once

#include "CCamera.h"

class CCollider;
class CAnimator;

class CObject
{

private:	
	wstring m_strName;

	Vec2 m_vPos;
	Vec2 m_vScale;

	CCollider* m_pCollider;
	CAnimator* m_pAnimator;

	bool m_bAlive;

public:
	virtual void Update() = 0;
	virtual void PostUpdate() final;
	virtual void Render(HDC _hdc);

	virtual CObject* Clone() = 0;

	void CreateCollider();
	void CreateAnimator();
	void RenderComponent(HDC _hdc);
	bool IsDead() const { return !m_bAlive; }

	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionBegin(CCollider* _pOther) {};
	virtual void OnCollisionEnd(CCollider* _pOther) {};


	Vec2 GetPos() const { return m_vPos; }
	Vec2 GetScale() const { return m_vScale; }
	CCollider* GetCollider() const { return m_pCollider; }
	CAnimator* GetAnimator() const { return m_pAnimator; }
	const wstring& GetName() const { return m_strName; }

	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetName(const wstring& _ws) { m_strName = _ws; }

private:
	void SetDead() { m_bAlive = false; }


public:
	CObject();
	virtual ~CObject();

	CObject(const CObject& _cobj);

	friend class CEventMgr;

};

