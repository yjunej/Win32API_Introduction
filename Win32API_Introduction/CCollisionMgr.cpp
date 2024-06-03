#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CCollider.h"
#include "CObject.h"

CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::Update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				UpdateCollisionGroup((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
}

void CCollisionMgr::Reset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
}

void CCollisionMgr::UpdateCollisionGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (nullptr == vecLeft[i]->GetCollider()) continue;
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (nullptr == vecRight[j]->GetCollider() ||
				vecLeft[i] == vecRight[j]) continue;


			CCollider* pLeftColl = vecLeft[i]->GetCollider();
			CCollider* pRightColl = vecRight[j]->GetCollider();


			// Collision ID
			COLLIDER_ID ID;
			ID.iLID = pLeftColl->GetID();
			ID.iRID = pRightColl->GetID();

			iter = m_mapCollInfo.find(ID.ID);

			// Collide status check
			if (m_mapCollInfo.end() == iter)
			{
				m_mapCollInfo.insert(make_pair(ID.ID, false));
				iter = m_mapCollInfo.find(ID.ID);
			}

			
			if (IsCollide(pLeftColl, pRightColl))
			{
				// Collide Ongoing
				if (iter->second)
				{
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						pLeftColl->OnCollisionEnd(pRightColl);
						pRightColl->OnCollisionEnd(pLeftColl);
						iter->second = false;
					}
					else
					{
						pLeftColl->OnCollision(pRightColl);
						pRightColl->OnCollision(pLeftColl);
					}

				}
				// Collide Begin Tick
				else
				{
					// Ignore Collide if one of Objects supposed to delete
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						pLeftColl->OnCollisionBegin(pRightColl);
						pRightColl->OnCollisionBegin(pLeftColl);
						iter->second = true;
					}
				}
			}
			else // No Collision
			{
				if (iter->second) // Collision End
				{
					pLeftColl->OnCollisionEnd(pRightColl);
					pRightColl->OnCollisionEnd(pLeftColl);
					iter->second = false;
				}
			}

		}

	}

}

bool CCollisionMgr::IsCollide(CCollider* _pLeftColl, CCollider* _pRightColl)
{
	Vec2 vLeftPos = _pLeftColl->GetCollPos();
	Vec2 vLeftScale = _pLeftColl->GetScale();
	Vec2 vRightPos = _pRightColl->GetCollPos();
	Vec2 vRightScale = _pRightColl->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.f &&
		abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}
