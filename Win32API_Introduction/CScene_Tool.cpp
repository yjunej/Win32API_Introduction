#include "pch.h"
#include "CScene_Tool.h"

#include "CKeyMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "CResourceMgr.h"
#include "CSceneMgr.h"

#include "CPanelUI.h"
#include "CButtonUI.h"
#include "CPathMgr.h"

#include "resource.h"

void ChangeToStartScene(DWORD_PTR, DWORD_PTR);

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
	if (KEY_TAP(KEY::LSHIFT))
	{
		ChangeScene(SCENE_TYPE::START);
	}
	if (KEY_TAP(KEY::CTRL))
	{
		LoadTileData();
	}
}

void CScene_Tool::Enter()
{
	// Create Initial Tiles
	CreateTile(100, 100);

	// Create UI
	Vec2 vResolution = CCore::GetInstance()->GetResolution();


	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(500.f, 300.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));

	CButtonUI* pButtonUI = new CButtonUI;
	pButtonUI->SetName(L"ChildUI");
	pButtonUI->SetScale(Vec2(100.f, 40.f));
	pButtonUI->SetPos(Vec2(0.f, 0.f));
	//pButtonUI->SetClickCallback(ChangeToStartScene, 0, 0);

	pPanelUI->AddChild(pButtonUI);

	AddObject(pPanelUI, GROUP_TYPE::UI);

	CUI* pClonePanelUI = (CUI*)pPanelUI->Clone();
	pClonePanelUI->SetPos(pClonePanelUI->GetPos() + Vec2(-100.f, 0.f));
	((CButtonUI*)(pClonePanelUI->GetChildren()[0]))->SetClickCallback(this, (SCENE_MEMFUNC) & CScene_Tool::SaveTileData);

	AddObject(pClonePanelUI, GROUP_TYPE::UI);


	// Move Camera
	CCamera::GetInstance()->SetLookPos(vResolution / 2.f);
}

void CScene_Tool::Exit()
{
	DeleteAll();
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

void CScene_Tool::SaveTileData()
{
	OPENFILENAME ofn = {};
	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInstance()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInstance()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}

void CScene_Tool::LoadTileData()
{
	OPENFILENAME ofn = {};
	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInstance()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInstance()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		wstring strRelPath = CPathMgr::GetInstance()->AbsToRelPath(szName);
		LoadTile(strRelPath);
	}
}

void CScene_Tool::SaveTile(const wstring& _strAbsPath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strAbsPath.c_str(), L"wb");
	assert(pFile);

	UINT iXCount = GetXTileCount();
	UINT iYCount = GetYTileCount();

	fwrite(&iXCount, sizeof(UINT), 1, pFile);
	fwrite(&iYCount, sizeof(UINT), 1, pFile);

	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}


	fclose(pFile);
}

void ChangeToStartScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
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

