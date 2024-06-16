#pragma once
#include "CScene.h"

class CTexture;

class CScene_GameOver : public CScene
{
private:
	CTexture* m_pTex;

public:
	virtual void Update() override {};
	virtual void Enter() override {};
	virtual void Exit() override {};
	virtual void Render(HDC _hdc) override;

public:
	CScene_GameOver();
	~CScene_GameOver();
};


