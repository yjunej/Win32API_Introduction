#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);

private:
	// Entire Scenes
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];
	// Current Scene
	CScene* m_pCurScene;

public:
	int Init();
	void Update();
	void Render(HDC _hdc);

	CScene* GetCurScene() { return m_pCurScene; }
	
private:
	void ChangeScene(SCENE_TYPE _eScene);
	friend class CEventMgr;
};

