#pragma once
#include "CObject.h"

class CTexture;

class CPlayer : public CObject
{

private:
	CTexture* m_pTexture;

public:
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;


private:
	void Fire();

public:
	CPlayer();
	~CPlayer();
};

