#pragma once

class CObject;

class CScene
{

private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // Object Manage
	wstring			 m_strName; // Scene Name 

public:
	void SetName(const wstring& _strName) { m_strName =		_strName; }
	const wstring& GetName() { return m_strName; }

	void Update();
	void Render(HDC _hdc);


	virtual void Enter() = 0; // Enter Scene
	virtual void Exit() = 0; // Exit Scene

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType);

public:
	CScene();
	virtual ~CScene();
};

