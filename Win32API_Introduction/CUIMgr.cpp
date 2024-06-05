#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"
#include "CKeyMgr.h"

CUIMgr::CUIMgr()
{

}
CUIMgr::~CUIMgr()
{

}

void CUIMgr::Update()
{
	CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	bool bLBTap = KEY_TAP(KEY::LBTN);
	bool bLBAway = KEY_AWAY(KEY::LBTN);


	for (size_t i = 0; i < vecUI.size(); i++)
	{
		CUI* pUI = (CUI*)vecUI[i];

		if (pUI->IsMouseHovered())
		{
			pUI->OnMouseHovered();
			if (bLBTap)
			{
				pUI->OnMouseLBPressed();
				pUI->m_bLBPressed = true;

			}
			else if (bLBAway)
			{
				pUI->OnMouseLBReleased();
				if (pUI->m_bLBPressed)
				{
					pUI->OnMouseLBClicked();
				}
				pUI->m_bLBPressed = false;
			}
		}
		else
		{
			if (bLBAway)
			{
				pUI->m_bLBPressed = false;
			}
		}
	}
}
