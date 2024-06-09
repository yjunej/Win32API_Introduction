#include "pch.h"
#include "CScene.h"

#include "CObject.h"
#include "CTexture.h"
#include "CResourceMgr.h"
#include "CTile.h"
#include "CPathMgr.h"
#include "CCamera.h"
#include "CCore.h"

CScene::CScene()
	:m_iXTileCount(0)
	, m_iYTileCount(0)
	, m_pPlayer(nullptr)
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			delete m_arrObj[i][j];
		}
	}
}

void CScene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->Update();
			}
		}
	}
}

void CScene::PostUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->PostUpdate();
		}
	}
}



void CScene::Render(HDC _hdc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		if ((UINT)GROUP_TYPE::TILE == i)
		{
			RenderTile(_hdc);
			continue;
			// Implement Dead State Check if Needs
		}


		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (;iter != m_arrObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->Render(_hdc);
				++iter;
			}
			else
			{
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}

void CScene::RenderTile(HDC _hdc)
{

	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	Vec2 vRes = CCore::GetInstance()->GetResolution();
	Vec2 vCamPos = CCamera::GetInstance()->GetCurLookPos();

	Vec2 vLeftTop = vCamPos - vRes / 2.f;

	int iLeftTopTileCol = (int)vLeftTop.x / (int)TILE_SIZE;
	int iLeftTopTileRow = (int)vLeftTop.y / (int)TILE_SIZE;

	int iNumTilesInViewX = ((int)vRes.x / (int)TILE_SIZE)+1;
	int iNumTilesInViewY = ((int)vRes.y / (int)TILE_SIZE)+1;

	for (int iCurRow = iLeftTopTileRow; iCurRow < (iLeftTopTileRow + iNumTilesInViewY); ++iCurRow)
	{
		for (int iCurCol = iLeftTopTileCol; iCurCol < (iLeftTopTileCol + iNumTilesInViewX); ++iCurCol)
		{
			if (iCurCol < 0 || m_iXTileCount <= (UINT)iCurCol || iCurRow < 0 || m_iYTileCount <=(UINT) iCurRow)
			{
				continue;
			}
			int iIdx = (m_iXTileCount * iCurRow) + iCurCol;
			vecTile[iIdx]->Render(_hdc);
		}
	}
	
}


void CScene::AddObject(CObject* _pObj, GROUP_TYPE _eType)
{
	m_arrObj[(UINT)_eType].push_back(_pObj);
}

void CScene::DeleteGroup(GROUP_TYPE _eType)
{
	DeleteVectorSafe<CObject*> (m_arrObj[(UINT)_eType]);
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{

	DeleteGroup(GROUP_TYPE::TILE);

	m_iXTileCount = _iXCount;
	m_iYTileCount = _iYCount;

	CTexture * pTileTex = CResourceMgr::GetInstance()->LoadTexture(
		L"Tile", L"\\texture\\tile\\SereneVillageTile32.bmp");

	// Create Tile
	for (UINT i = 0 ; i <_iYCount; ++i)
	{
		for (UINT j = 0; j < _iXCount; ++j)
		{
			CTile* pTile = new CTile;
			pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTileTex);
			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}

void CScene::LoadTile(const wstring& _strRelPath)
{
	wstring strAbsFilePath = CPathMgr::GetInstance()->GetContentPath();
	strAbsFilePath += _strRelPath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strAbsFilePath.c_str(), L"rb");
	assert(pFile);

	UINT iXCount = 0;
	UINT iYCount = 0;

	fread(&iXCount, sizeof(UINT), 1, pFile);
	fread(&iYCount, sizeof(UINT), 1, pFile);

	CreateTile(iXCount, iYCount);

	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}

	
	fclose(pFile);
}
