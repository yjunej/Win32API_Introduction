#include "pch.h"
#include "CScene_Tool.h"

#include "CKeyMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "CResourceMgr.h"
#include "CSceneMgr.h"
#include "CUI.h"

#include "resource.h"


CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Update()
{
	CScene::Update();
	SetTileIdx();
}

void CScene_Tool::Enter()
{
	// Create Initial Tiles
	CreateTile(4, 4);

	// Create UI
	Vec2 vResolution = CCore::GetInstance()->GetResolution();


	CUI* pUI = new CUI(false);

	pUI->SetScale(Vec2(500.f, 300.f));
	pUI->SetPos(Vec2(vResolution.x - pUI->GetScale().x, 0.f));

	//CUI* pChildUI = new CUI;
	//pChildUI->SetScale(Vec2(100.f, 40.f));
	//pChildUI->SetPos(Vec2(0.f, 0.f));

	//pUI->AddChild(pChildUI);

	AddObject(pUI, GROUP_TYPE::UI);

	// Move Camera
	CCamera::GetInstance()->SetLookPos(vResolution / 2.f);
}

void CScene_Tool::Exit()
{
}

void CScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousPos = MOUSE_POS;
		vMousPos = CCamera::GetInstance()->RenderPosToScreenPos(vMousPos);

		int iXCount = (int)GetXTileCount();
		int iYCount = (int)GetYTileCount();

		int iCol = (int)vMousPos.x / TILE_SIZE;
		int iRow = (int)vMousPos.y / TILE_SIZE;

		if (vMousPos.x < 0.f || iXCount <= iCol ||
			vMousPos.y < 0.f || iYCount <= iRow)
		{
			return;
		}
		UINT iIdx = iRow * iXCount + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->IncImgIdx();
	}
	
}


// ||========================||
// || Tile Count Window Proc ||
// ||========================||
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);
			CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();

			// Check Tool Scene
			CScene* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

