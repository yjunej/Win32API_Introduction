#include "pch.h"
#include "SelectGDI.h"

#include "CCore.h"

SelectGDI::SelectGDI(HDC _hdc, PEN_TYPE _ePenType)
	: m_hdc(_hdc)
	, m_hDefaultPen(nullptr)
	, m_hDefaultBrush(nullptr)
{
	HPEN hPen = CCore::GetInstance()->GetPen(_ePenType);
	m_hDefaultPen = (HPEN)SelectObject(_hdc, hPen);
}

SelectGDI::SelectGDI(HDC _hdc, BRUSH_TYPE _eBrushType)
	: m_hdc(_hdc)
	, m_hDefaultPen(nullptr)
	, m_hDefaultBrush(nullptr)
{
	HBRUSH hBrush = CCore::GetInstance()->GetBrush(_eBrushType);
	m_hDefaultBrush = (HBRUSH)SelectObject(_hdc, hBrush);
}

SelectGDI::~SelectGDI()
{
	SelectObject(m_hdc, m_hDefaultPen);
	SelectObject(m_hdc, m_hDefaultBrush);
}
