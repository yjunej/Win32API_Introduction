#include "pch.h"
#include "CState.h"

#include "AI.h"
#include "CEnemy.h"

CEnemy* CState::GetOwner() const
{
	return m_pAI->GetOwner();
}

CState::CState(ENEMY_STATE _eState)
	: m_pAI(nullptr)
	, m_eState(_eState)
{
}

CState::~CState()
{
}
