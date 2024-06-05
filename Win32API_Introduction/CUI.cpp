#include "CUI.h"

#include "CKeyMgr.h"
#include "CCamera.h"

#include "SelectGDI.h"

CUI::CUI(bool _bCamDetached)
	: m_pParentUI(nullptr)
	, m_bCamDetached(_bCamDetached)
	, m_bMouseHovered(false)
	, m_bLBPressed(false)
{
}

CUI::CUI(const CUI& _cUI)
	: CObject(_cUI)
	, m_pParentUI(nullptr)
	, m_bCamDetached(_cUI.m_bCamDetached)
	, m_bMouseHovered(false) 
	, m_bLBPressed(false)
{
	for (size_t i = 0; i < _cUI.m_vecChildUI.size(); i++)
	{
		this->AddChild(_cUI.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	DeleteVectorSafe<CUI*>(m_vecChildUI);
}
void CUI::CheckHovered()
{
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();

	if (m_bCamDetached)
	{
		vMousePos = CCamera::GetInstance()->RenderPosToScreenPos(vMousePos);
	}

	if (m_vUIPos.x <= vMousePos.x && vMousePos.x <= m_vUIPos.x + vScale.x
		&& m_vUIPos.y <= vMousePos.y && vMousePos.y <= m_vUIPos.y + vScale.y)
	{
		m_bMouseHovered = true;
	}
	else
	{
		m_bMouseHovered = false;
	}


}
void CUI::UpdateChildren()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->Update();
	}
}

void CUI::PostUpdateChildren()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->PostUpdate();
	}
}

void CUI::RenderChildren(HDC _hdc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->Render(_hdc);
	}
}

void CUI::Update()
{

	UpdateChildren();
}

void CUI::PostUpdate()
{
	CObject::PostUpdate();

	m_vUIPos = GetPos();
	if (GetParent())
	{
		Vec2 vParentPos = GetParent()->GetUIPos();
		m_vUIPos += vParentPos;
	}

	// Check Mouse Hover
	CheckHovered();

	PostUpdateChildren();
}

void CUI::Render(HDC _hdc)
{
	Vec2 vPos = GetUIPos();
	Vec2 vScale = GetScale();

	if (m_bCamDetached)
	{
		vPos = CCamera::GetInstance()->ScreenPosToRenderPos(vPos);
	}

	if (m_bLBPressed)
	{
		SelectGDI select(_hdc, PEN_TYPE::GREEN);
		Rectangle(
			_hdc,
			(int)vPos.x,
			(int)vPos.y,
			(int)(vPos.x + vScale.x),
			(int)(vPos.y + vScale.y));
	}
	else
	{

	

	Rectangle(
		_hdc,
		(int)vPos.x,
		(int)vPos.y,
		(int)(vPos.x + vScale.x),
		(int)(vPos.y + vScale.y));
	}	
	RenderChildren(_hdc);
}

void CUI::OnMouseHovered()
{
}

void CUI::OnMouseLBPressed()
{
}

void CUI::OnMouseLBReleased()
{
}

void CUI::OnMouseLBClicked()
{
}


