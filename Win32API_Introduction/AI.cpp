#include "pch.h"
#include "AI.h"

#include "CState.h"

AI::AI()
	: m_pOwner(nullptr)
	, m_pCurState(nullptr)
{
}

AI::~AI()
{
	DeleteMapSafe(m_mapState);
}

void AI::Update()
{
	m_pCurState->Update();
}

void AI::AddState(CState* _pState)
{
	// Duplicated State
	CState* pState = GetState(_pState->GetStateEnum());
	assert(!pState);

	m_mapState.insert(make_pair(_pState->GetStateEnum(), _pState));
	_pState->m_pAI = this;
}

CState* AI::GetState(ENEMY_STATE _eState)
{
	map<ENEMY_STATE, CState*>::iterator iter = m_mapState.find(_eState);
	if (iter == m_mapState.end())
		return nullptr;

	return iter->second;
}

void AI::SetCurState(ENEMY_STATE _eState)
{
	m_pCurState = GetState(_eState);
	assert(m_pCurState);
}

void AI::ChangeState(ENEMY_STATE _eNewState)
{
	CState* pNewState = GetState(_eNewState);
	assert(m_pCurState != pNewState);

	m_pCurState->Exit();
	m_pCurState = pNewState;
	m_pCurState->Enter();

}


