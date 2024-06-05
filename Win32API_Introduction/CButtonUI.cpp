#include "CButtonUI.h"


CButtonUI::CButtonUI()
	: CUI(false)
	, m_pFunc(nullptr)
	, m_pParam1(0)
	, m_pParam2(0)
	, m_pSceneInst(nullptr)
	, m_pSceneFunc(nullptr)
{
}

CButtonUI::~CButtonUI()
{
}

void CButtonUI::OnMouseHovered()
{
}

void CButtonUI::OnMouseLBPressed()
{
}

void CButtonUI::OnMouseLBReleased()
{
}

void CButtonUI::OnMouseLBClicked()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_pParam1, m_pParam2);
	}
	if (m_pSceneInst && m_pSceneFunc)
	{
		(m_pSceneInst->*m_pSceneFunc)();
	}
}

void CButtonUI::SetClickCallback(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
{
	m_pSceneInst = _pScene;
	m_pSceneFunc = _pSceneFunc;
}