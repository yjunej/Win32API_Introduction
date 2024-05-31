#pragma once

class CKeyMgr
{
public:
	SINGLE(CKeyMgr);

private:
	CKeyMgr();
	~CKeyMgr();
	CKeyMgr(const CKeyMgr&) = delete;
	CKeyMgr& operator=(const CKeyMgr&) = delete;
};

