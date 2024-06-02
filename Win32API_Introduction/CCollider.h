#pragma once

class CObject;

class CCollider
{
private:
	CObject* m_pOwner;
	Vec2 m_vOffsetPos;
	Vec2 m_vCollPos;
	Vec2 m_vScale;


public:
	void SetOffsetPos(Vec2 _v) { m_vOffsetPos = _v; }
	void SetScale(Vec2 _v) { m_vScale = _v; }
	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

	void PostUpdate();
	void Render(HDC _hdc);

	CCollider();
	~CCollider();

	friend class CObject;
};

