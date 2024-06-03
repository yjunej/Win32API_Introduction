#pragma once

struct tEvent
{
	EVENT_TYPE eEvent;
	DWORD_PTR lParam;
	DWORD_PTR wParam;
};


class CEventMgr
{
	SINGLE(CEventMgr);

private:
	vector<tEvent> m_vecEvent;
	vector<CObject*> m_vecDead;

public:
	void Update();


private:
	void Execute(const tEvent& _event);

public:
	void AddEvent(const tEvent& _t) { m_vecEvent.push_back(_t); }
};

