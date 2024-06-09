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

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GetInstance()->RenderPosToScreenPos(MOUSE_POS);

}

CScene_Start::CScene_Start()
	:m_bUseForce(false)
	, m_fForceRadius(500.f)
	, m_fCurRadius(0.f)
	, m_fForce(500.f)
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Update()
{

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
	}

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);

	}

	if (KEY_TAP(KEY::RBTN))
	{
		Vec2 vFocusPos = CCamera::GetInstance()->RenderPosToScreenPos(MOUSE_POS);
		CCamera::GetInstance()->SetLookPos(vFocusPos);
	}


}

void CScene_Start::Render(HDC _hdc)
{
	CScene::Render(_hdc);

	if (!m_bUseForce)
	{
		return;

	}
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

void CScene_Start::Enter()
{

	// Add Object
	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	// Copy Player Example

	//CObject* pOtherPlayer = pObj->Clone();
	//pOtherPlayer->SetPos(Vec2(
	//	pOtherPlayer->GetPos().x + pOtherPlayer->GetScale().x,
	//	pOtherPlayer->GetPos().y));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	// Camera Follow Player

	//CCamera::GetInstance()->SetFocus(pObj);


	// Spawn Enemy
	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	CEnemy* pEnemy = CEnemySpawner::SpawnEnemy(ENEMY_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f, 300.f));
	AddObject(pEnemy, GROUP_TYPE::ENEMY);

	// Create Ground
	CObject* pGround = new CGround;
	pGround->SetName(L"Ground");
	pGround->SetPos(Vec2(640.f, 500.f));
	pGround->SetScale(Vec2(200.f, 65.f));
	AddObject(pGround, GROUP_TYPE::GROUND);



	// LoadTile
	//LoadTile(L"Tile\\Start.tile");


	// Collision
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ENEMY);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::ENEMY);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);

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
