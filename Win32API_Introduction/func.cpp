#include "pch.h"
#include "func.h"

#include "CEventMgr.h"

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent tEventInfo = {};
	tEventInfo.eEvent = EVENT_TYPE::CREATE_OBJECT;
	tEventInfo.lParam = (DWORD_PTR)_pObj;
	tEventInfo.wParam = (DWORD_PTR)_eGroup;

	CEventMgr::GetInstance()->AddEvent(tEventInfo);
}

void DeleteObject(CObject* _pObj)
{
	tEvent tEventInfo = {};
	tEventInfo.eEvent = EVENT_TYPE::DELETE_OBJECT;
	tEventInfo.lParam = (DWORD_PTR)_pObj;
	CEventMgr::GetInstance()->AddEvent(tEventInfo);
}

void ChangeScene(SCENE_TYPE _eScene)
{
	tEvent tEventInfo = {};
	tEventInfo.eEvent = EVENT_TYPE::SCENE_CHANGE;
	tEventInfo.lParam = (DWORD_PTR)_eScene;
	CEventMgr::GetInstance()->AddEvent(tEventInfo);
}

void ChangeAIState(AI* _pAI, ENEMY_STATE _eNewState)
{
	tEvent tevn = {};
	tevn.eEvent = EVENT_TYPE::CHANGE_AI_STATE;
	tevn.lParam = (DWORD_PTR)_pAI;
	tevn.wParam = (DWORD_PTR)_eNewState;

	CEventMgr::GetInstance()->AddEvent(tevn); 

}
