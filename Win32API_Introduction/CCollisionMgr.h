#pragma once

class CCollider;

union COLLIDER_ID
{
	struct {
		UINT iLID;
		UINT iRID;
	};
	ULONGLONG ID;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr)

private:
	map<ULONGLONG, bool> m_mapCollInfo; // Previous Frame Collision Info
	UINT m_arrCheck[(UINT)GROUP_TYPE::END]; // Collide Check Matrix between Obj Groups

public:
	void Update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset();

private:
	void UpdateCollisionGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollide(CCollider* _pLeftColl , CCollider* _pRightColl);
};

