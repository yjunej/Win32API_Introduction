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

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (nullptr == vecLeft[i]->GetCollider()) continue;
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (nullptr == vecRight[j]->GetCollider() ||
				vecLeft[i] == vecRight[j]) continue;

			if (IsCollide(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider()))
			{

			}
			else
			{

			}

		}

	}

}

bool CCollisionMgr::IsCollide(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	return false;
}
