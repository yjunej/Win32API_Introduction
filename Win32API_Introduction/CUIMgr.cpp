#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"
#include "CKeyMgr.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{

}
CUIMgr::~CUIMgr()
{

}

void CUIMgr::Update()
{

	// Get FocusedUI
	m_pFocusedUI = GetFocusedUI();
	if (nullptr == m_pFocusedUI)
	{
		return;
	}
	

	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	bool bLBTap = KEY_TAP(KEY::LBTN);
	bool bLBAway = KEY_AWAY(KEY::LBTN);

	if (nullptr != pTargetUI)
	{
		pTargetUI->OnMouseHovered();

		if (bLBTap)
		{
			pTargetUI->OnMouseLBPressed();
			pTargetUI->m_bLBPressed = true;

		}
		else if (bLBAway)
		{
			pTargetUI->OnMouseLBReleased();
			if (pTargetUI->m_bLBPressed)
			{
				pTargetUI->OnMouseLBClicked();
			}
			pTargetUI->m_bLBPressed = false;
		}
	}
}

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	if (m_pFocusedUI == _pUI || nullptr == _pUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;

	CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroupObject();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (*iter == m_pFocusedUI)
		{
			break;
		}
	}
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);


}

CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroupObject();

	bool bLBTap = KEY_TAP(KEY::LBTN);
	
	CUI* pFocusedUI = m_pFocusedUI;
	if (!bLBTap) return pFocusedUI;

	vector<CObject*>::iterator itTarget = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseHovered())
		{
			itTarget = iter;
		}
	}

	// No Focused UI
	if (vecUI.end() == itTarget)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*itTarget;

	vecUI.erase(itTarget);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLBAway = KEY_AWAY(KEY::LBTN);
	CUI* pTargetUI = nullptr;


	// Check Child
	static	list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// Pop from queue
		CUI* pUI = queue.front();
		queue.pop_front();

		// Check TargetUI
		if (pUI->IsMouseHovered())
		{
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}

		const vector<CUI*>& vecChildren = pUI->GetChildren();
		for (size_t i = 0; i < vecChildren.size(); i++)
		{
			queue.push_back(vecChildren[i]);
		}
	}

	if (bLBAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); i++)
		{
			vecNoneTarget[i]->m_bLBPressed = false;	
		}
	}

	
	return pTargetUI;
}
