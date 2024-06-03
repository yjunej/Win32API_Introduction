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

	// Covariant return type
	virtual CLONE(CPlayer);

private:
	void Fire();

public:
	CPlayer();
	~CPlayer();
};

