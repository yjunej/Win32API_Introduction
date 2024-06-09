#pragma once

class CObject;

class CCollider
{
private:

	static UINT g_iNextID;

	CObject* m_pOwner;
	Vec2 m_vOffsetPos;
	Vec2 m_vCollPos;
	Vec2 m_vScale;

	UINT m_iID;
	int m_iColl;

	bool m_bActive;

public:
	void SetOffsetPos(Vec2 _v) { m_vOffsetPos = _v; }
	void SetScale(Vec2 _v) { m_vScale = _v; }
	
	CObject* GetOwner() const { return m_pOwner; }
	Vec2 GetOffsetPos() const { return m_vOffsetPos; }
	Vec2 GetCollPos() const { return m_vCollPos; }
	Vec2 GetScale() const { return m_vScale; }
	UINT GetID() const { return m_iID; }

	void PostUpdate();
	void Render(HDC _hdc);

	void OnCollision(CCollider* _pOther);
	void OnCollisionBegin(CCollider* _pOther);
	void OnCollisionEnd(CCollider* _pOther);


public:
	CCollider();
	~CCollider();
	CCollider(const CCollider& _collider);
	CCollider& operator= (CCollider& _collider) = delete;

	friend class CObject;
};

