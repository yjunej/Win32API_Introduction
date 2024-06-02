#pragma once

class CCollisionMgr
{
	SINGLE(CCollisionMgr);

private:


	UINT m_arrCheck[(UINT)GROUP_TYPE::END]; // Collide Check Matrix between Obj Groups

public:
	void Update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset();

private:
	void UpdateCollisionGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollide(CCollider* _pLeftCol, CCollider* _pRightCol);
};

