#pragma once

#include "global.h"
#include "CEnemySpawner.h"


class CObject;

class CScene
{

private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // Object Manage
	wstring			 m_strName; // Scene Name 

	UINT			 m_iXTileCount; // Num of Tiles
	UINT			 m_iYTileCount;

	CObject*		 m_pPlayer;


	

public:
	void SetName(const wstring& _strName) { m_strName =		_strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetXTileCount() const { return m_iXTileCount; }
	UINT GetYTileCount() const { return m_iYTileCount; }

	CObject* GetPlayer() const { return m_pPlayer; }

	virtual void BeginPlay();
	virtual void Update();
	void PostUpdate();
	virtual void Render(HDC _hdc);
	void RenderTile(HDC _hdc);


	virtual void Enter() = 0; // Enter Scene
	virtual void Exit() = 0; // Exit Scene

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType);
	void RegisterPlayer(CObject* _pObj) { m_pPlayer = _pObj; }


	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) const { return m_arrObj[(UINT)_eType]; }
	vector<CObject*>& GetUIGroupObject() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }



	void DeleteGroup(GROUP_TYPE _eType);
	void DeleteAll();

	void CreateTile(UINT _iXCount, UINT _iYCount);
	void LoadTile(const wstring& _strRelPath);

public:
	CScene();
	virtual ~CScene();
};

