#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CCore.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCamera.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "SelectGDI.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
#include "CGround.h"
#include "CBox.h"

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GetInstance()->RenderPosToScreenPos(MOUSE_POS);

}

void CScene_Start::DrawHealthBar(HDC _hdc)
{
	// BackGround
	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	RECT rcBackground = { 50, vResolution.y - 80, 50 + 200, vResolution.y - 80 + 20 };
	HBRUSH hBrushBackground = CreateSolidBrush(RGB(200, 200, 200));
	FillRect(_hdc, &rcBackground, hBrushBackground);
	DeleteObject(hBrushBackground);

	// Health Bar
	CPlayer* pPlayer = (CPlayer*)GetPlayer();
	int barWidth = static_cast<int>((static_cast<double>(pPlayer->GetHP()) / 100) * 200);
	RECT rcHealth = { 50, vResolution.y - 80, 50 + barWidth, vResolution.y - 80 + 20 };
	HBRUSH hBrushHealth = CreateSolidBrush(RGB(255, 0, 0));
	FillRect(_hdc, &rcHealth, hBrushHealth);
	DeleteObject(hBrushHealth);

	// Border
	HGDIOBJ hOldPen = SelectObject(_hdc, GetStockObject(BLACK_PEN));
	SelectObject(_hdc, GetStockObject(NULL_BRUSH));
	Rectangle(_hdc, 50, vResolution.y - 80, 50 + 200, vResolution.y - 80 + 20);
	SelectObject(_hdc, hOldPen);
	
}

CScene_Start::CScene_Start()
	:m_bUseForce(false)
	, m_fForceRadius(500.f)
	, m_fCurRadius(0.f)
	, m_fForce(500.f)
	, m_vScreenSize(Vec2(2560.f, 1440.f))
	, m_fEnemySpawnInterval(5.f)
	, m_fTimeAcc(0.f)
{
	m_vCameraBoundary = m_vScreenSize;
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Update()
{
	LoadTile(L"tile\\80_45_2560_1440.tile");

	if (KEY_HOLD(KEY::LBTN))
	{
		m_bUseForce = true;
		CreateForce();
	}
	else
	{
		m_bUseForce = false;
	}


	// CScene::Update();
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		const vector<CObject*>& arrObj = GetGroupObject((GROUP_TYPE)i);

		for (size_t j = 0; j < arrObj.size(); ++j)
		{
			if (!arrObj[j]->IsDead())
			{
				if (m_bUseForce && nullptr != arrObj[j]->GetRigidBody())
				{
					Vec2 vDiff =arrObj[j]->GetPos() - m_vForcePos;
					if (vDiff.GetLength() <= m_fForceRadius)
					{
						float fForceRatio = 1.f - (vDiff.GetLength() / m_fForceRadius);
						float fForce = m_fForce * fForceRatio;
						vDiff.Normalize();
						arrObj[j]->GetRigidBody()->AddForce(vDiff.Normalize() * fForce);
					}
				}
				arrObj[j]->Update();
			}
		}


		// Delete Player Projectile Over screen
		const vector<CObject*>& vecProj = GetGroupObject(GROUP_TYPE::PROJ_PLAYER);
		for (size_t i = 0; i < vecProj.size(); i++)
		{
			if (vecProj[i]->GetPos().x < 0 || vecProj[i]->GetPos().x > m_vScreenSize.x ||
				vecProj[i]->GetPos().y < 0 || vecProj[i]->GetPos().y > m_vScreenSize.y)
			{
				if (!vecProj[i]->IsDead())
				{
					DeleteObject(vecProj[i]);
				}
			}

		}
	}

	// Block Character
	Vec2 vCharacterPos = GetPlayer()->GetPos();
	Vec2 vCharacterScale = GetPlayer()->GetScale();
	POINT pt = { 0, 0 };
	ClientToScreen(CCore::GetInstance()->GetMainHwnd(), &pt);

	if (vCharacterPos.x - vCharacterScale.x / 2.f < TILE_SIZE)
		vCharacterPos.x = TILE_SIZE + vCharacterScale.x / 2.f;
	if (vCharacterPos.x + vCharacterScale.x / 2.f> m_vScreenSize.x - TILE_SIZE)
		vCharacterPos.x = m_vScreenSize.x - TILE_SIZE - vCharacterScale.x/2.f;
	if (vCharacterPos.y - vCharacterScale.y / 2.f < TILE_SIZE)
		vCharacterPos.y = TILE_SIZE + vCharacterScale.y / 2.f;
	if (vCharacterPos.y + vCharacterScale.y / 2.f > m_vScreenSize.y - pt.y - TILE_SIZE)
		vCharacterPos.y = m_vScreenSize.y - pt.y -TILE_SIZE - vCharacterScale.y / 2.f ;
	GetPlayer()->SetPos(vCharacterPos);

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);

	}

	if (KEY_TAP(KEY::RBTN))
	{
		Vec2 vFocusPos = CCamera::GetInstance()->RenderPosToScreenPos(MOUSE_POS);
		CCamera::GetInstance()->SetLookPos(vFocusPos);
	}

	m_fTimeAcc += fDT;
	if (m_fTimeAcc >= m_fEnemySpawnInterval)
	{
		m_fTimeAcc -= m_fEnemySpawnInterval;

		int iRandomX = rand();
		int iRandomY = rand();
		Vec2 SpawnPoint = {
			 iRandomX % int(m_vScreenSize.x), iRandomY % int(m_vScreenSize.y)
		};
		Vec2 vToSpawnPoint = SpawnPoint - CCamera::GetInstance()->GetCurLookPos();
		float vDistToPlayer = (SpawnPoint - CCamera::GetInstance()->GetCurLookPos()).GetLength();
		Vec2 vResolution = CCore::GetInstance()->GetResolution();
		if (vDistToPlayer < (vResolution / 2.f).GetLength())
		{
			vToSpawnPoint.Normalize();
			vToSpawnPoint *= (vResolution / 2.f).GetLength();
			vToSpawnPoint += CCamera::GetInstance()->GetCurLookPos();
		}


		CEnemy* pEnemy = CEnemySpawner::SpawnEnemy(ENEMY_TYPE::NORMAL,SpawnPoint);
		AddObject(pEnemy, GROUP_TYPE::ENEMY);

		// Level Difficulty Control
		m_fEnemySpawnInterval *= 0.98;

	}

}

void CScene_Start::Render(HDC _hdc)
{
	CScene::Render(_hdc);

	// DEBUG - print player pos, at left top
	Vec2 PlayerPos = GetPlayer()->GetPos(); // .x float, .y float
	wchar_t szPlayerPos[256] = {};
	swprintf_s(szPlayerPos, L"Player Pos : %.2f, %.2f", PlayerPos.x, PlayerPos.y);
	TextOut(_hdc, 0, 0, szPlayerPos, (int)wcslen(szPlayerPos));

	// DEBUG - print player pos, at left top
	wchar_t szPos[256] = {};
	wchar_t szPos2[256] = {};

	swprintf_s(szPos, L"MOUSE Pos : %.2f, %.2f", MOUSE_POS.x, MOUSE_POS.y);
	TextOut(_hdc, 0, 20, szPos, (int)wcslen(szPos));
	Vec2 MouseScreenPos = CCamera::GetInstance()->RenderPosToScreenPos(MOUSE_POS);
	swprintf_s(szPos2, L"MOUSE Screen Pos : %.2f, %.2f", MouseScreenPos.x, MouseScreenPos.y);
	TextOut(_hdc, 0, 40, szPos2, (int)wcslen(szPos2));
	//

	
	//

	if (m_bUseForce)
	{
		SelectGDI _g1(_hdc, BRUSH_TYPE::HOLLOW);
		SelectGDI _g2(_hdc, PEN_TYPE::GREEN);

		m_fCurRadius += m_fForceRadius * 3.f * fDT;
		if (m_fCurRadius > m_fForceRadius)
		{
			m_fCurRadius = 0.f;
		}

		Vec2 vRenderPos = CCamera::GetInstance()->ScreenPosToRenderPos(m_vForcePos);

		Ellipse(
			_hdc,
			(int)(vRenderPos.x - m_fCurRadius),
			(int)(vRenderPos.y - m_fCurRadius),
			(int)(vRenderPos.x + m_fCurRadius),
			(int)(vRenderPos.y + m_fCurRadius)
		);

	}

	// Draw Health Bar
	DrawHealthBar(_hdc);

}

void CScene_Start::Enter()
{
	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	

	// Add Object
	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(m_vScreenSize/2.f);
	pObj->SetScale(Vec2(36.f, 48.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	// Copy Player Example


	// Add Box
	int iBoxCount = 20;
	for (int i = 0; i < iBoxCount; i++)
	{
		CBox* pBoxObj = new CBox;
		pBoxObj->SetName(L"Box");
		pBoxObj->SetScale(Vec2(32.f, 32.f));
		switch (rand() % 4)
		{
		case 0:
			pBoxObj->SetBulletCountUp(2);
			break;
		case 1:
			pBoxObj->SetDamageUp(10.f);
			break;
		case 2:
			pBoxObj->SetHPUP(10.f);
			break;
		case 3:
			pBoxObj->SetAttackSpeedUp(1.f);
			break;
		default:
			break;
		}
		pBoxObj->SetPos(
			Vec2(
			rand() % (int)(m_vScreenSize.x - 32.f),
			rand() % (int)(m_vScreenSize.x - 32.f)));


		AddObject((CObject*)pBoxObj, GROUP_TYPE::ITEM);
	}


	//CObject* pOtherPlayer = pObj->Clone();
	//pOtherPlayer->SetPos(Vec2(
	//	pOtherPlayer->GetPos().x + pOtherPlayer->GetScale().x,
	//	pOtherPlayer->GetPos().y));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	// Camera Follow Player
	CCamera::GetInstance()->SetCameraBoundary(m_vCameraBoundary);
	CCamera::GetInstance()->SetFocus(pObj);


	// Spawn Enemy
	CEnemy* pEnemy = CEnemySpawner::SpawnEnemy(ENEMY_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f, 200.f));
	AddObject(pEnemy, GROUP_TYPE::ENEMY);

	// Create Ground
	//CObject* pGround = new CGround;
	//pGround->SetName(L"Ground");
	//pGround->SetPos(Vec2(640.f, 500.f));
	//pGround->SetScale(Vec2(200.f, 65.f));
	//AddObject(pGround, GROUP_TYPE::GROUND);



	// LoadTile
	//LoadTile(L"Tile\\Start.tile");


	// Collision
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ENEMY);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::ENEMY);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ITEM);


	// Set Camera
	CCamera::GetInstance()->SetLookPos(vResolution / 2.f);

	// Camera Effect
	CCamera::GetInstance()->FadeOut(1.f);
	CCamera::GetInstance()->FadeIn(1.f);

	// BeginPlay
	BeginPlay();
}

void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInstance()->Reset();
}

