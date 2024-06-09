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

void SaveWString(const wstring& _str, FILE* _pFile)
{
	// wstring - vector base STL, Need to proceed Serialization
	const wchar_t* pStrName = _str.c_str();
	size_t iLen = _str.length();

	// save length
	fwrite(&iLen, sizeof(size_t), 1, _pFile);
	fwrite(pStrName, sizeof(wchar_t), iLen, _pFile);
}

void LoadWString(wstring& _str, FILE* _pFile)
{
	// Read Custom Format
	size_t iLen = 0;
	fread(&iLen, sizeof(size_t), 1, _pFile);

	wchar_t szBuff[256] = {};
	fread(szBuff, sizeof(wchar_t), iLen, _pFile);

	_str = szBuff;
}

void FScanf(char* _pOut, FILE* _pFile)
{
	int i = 0;
	while (true)
	{
		char c = (char)getc(_pFile);
		if (c == '\n')
		{
			_pOut[i++] = '\0';
			break;

		}
		_pOut[i++] = c;
	}
}
