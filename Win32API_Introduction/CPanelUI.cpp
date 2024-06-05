#include "CPanelUI.h"

#include "CKeyMgr.h"

CPanelUI::CPanelUI()
	: CUI(false)
{
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::Update()
{
}

void CPanelUI::Render(HDC _hdc)
{
	CUI::Render(_hdc);
}

void CPanelUI::OnMouseHovered()
{
	if (IsLBPressed())
	{
		Vec2 vDiff = MOUSE_POS - m_vDragStartPos;
		SetPos(GetPos() + vDiff);
		m_vDragStartPos = MOUSE_POS;
	}
}

void CPanelUI::OnMouseLBPressed()
{
	m_vDragStartPos = MOUSE_POS;
}

void CPanelUI::OnMouseLBReleased()
{
}


