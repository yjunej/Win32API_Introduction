#pragma once
#include "CScene.h"

class CScene_Tool : public CScene
{
private:

public:
	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

	void SetTileIdx();
	void SaveTileData();
	void LoadTileData();
	void SaveTile(const wstring& _strAbsPath);

public:
	CScene_Tool();
	~CScene_Tool();
};

