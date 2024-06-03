#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::Update()
{
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Execute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventMgr::Execute(const tEvent& _event)
{
	switch (_event.eEvent)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam: Object Addr
		// wParam: Group Type
		CObject* pObj = (CObject*)_event.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_event.wParam;

		CSceneMgr::GetInstance()->GetCurScene()->AddObject(pObj, eType);
		break;
	}
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam: Object Addr 

		CObject* pDeadObj = (CObject*)_event.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);

		break;
	}
	case EVENT_TYPE::SCENE_CHANGE:
	{
		break;
	}
	default:
		break;
	}
}
