#pragma once

class CCollider;

class CObject
{

private:	
	Vec2 m_vPos;
	Vec2 m_vScale;

	CCollider* m_pCollider;

public:
	virtual void Update() = 0;
	virtual void PostUpdate() final;
	virtual void Render(HDC _hdc);


	void CreateCollider();
	void RenderComponent(HDC _hdc);

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	CCollider* GetCollider() { return m_pCollider; }

	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	


public:
	CObject();
	virtual ~CObject();

};

