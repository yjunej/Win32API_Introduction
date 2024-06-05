#include "CButtonUI.h"

CButtonUI::CButtonUI()
	: CUI(false)
	, m_pFunc(nullptr)
{
}

CButtonUI::~CButtonUI()
{
}

void CButtonUI::OnMouseHovered()
{
}

void CButtonUI::OnMouseLBPressed()
{
}

void CButtonUI::OnMouseLBReleased()
{
}

void CButtonUI::OnMouseLBClicked()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_pParam1, m_pParam2);
	}
}


