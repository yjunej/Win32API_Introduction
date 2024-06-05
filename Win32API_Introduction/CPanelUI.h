#pragma once
#include "CUI.h"


class CPanelUI : public CUI
{

private:
	Vec2 m_vDragStartPos;

private:

	virtual void Update() override;
	virtual void Render(HDC _hdc) override;

	virtual void OnMouseHovered();
	virtual void OnMouseLBPressed();
	virtual void OnMouseLBReleased();

	CLONE(CPanelUI)

public:
	CPanelUI();
	~CPanelUI();

};

