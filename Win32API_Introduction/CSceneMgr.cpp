#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_Start.h"
#include "CScene_Tool.h"
#include "CScene_GameOver.h"

CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{

}

CSceneMgr::~CSceneMgr()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}

}

int CSceneMgr::Init()
{
	// Create Start Scene
	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::GAMEOVER] = new CScene_GameOver;


	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	m_arrScene[(UINT)SCENE_TYPE::GAMEOVER]->SetName(L"GameOver Scene");

	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Start;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Start;


	// Select Scene
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();

	return S_OK;

}

void CSceneMgr::Update()
{
	m_pCurScene->Update();
	m_pCurScene->PostUpdate();
}

void CSceneMgr::Render(HDC _hdc)
{
	m_pCurScene->Render(_hdc);
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eScene)
{
	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)_eScene];
	m_pCurScene->Enter();
}
