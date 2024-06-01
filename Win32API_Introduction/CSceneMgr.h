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
	void render(HDC _hdc);

};

