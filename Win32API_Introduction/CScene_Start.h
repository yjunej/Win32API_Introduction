#pragma once
#include "CScene.h"

class CScene_Start : public CScene
{
private:
	Vec2 m_vForcePos;
	float m_fForceRadius;
	float m_fCurRadius;
	bool m_bUseForce;
	float m_fForce;
	Vec2 m_vScreenSize;
	Vec2 m_vCameraBoundary;


public:
	virtual void Update() override;
	virtual void Render(HDC _hdc);
	virtual void Enter() override;
	virtual void Exit() override;

public:
	void CreateForce();
	CScene_Start();
	~CScene_Start();
};

