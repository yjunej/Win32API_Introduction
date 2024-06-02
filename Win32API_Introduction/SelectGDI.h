#pragma once
class SelectGDI
{
private:
	HDC m_hdc;
	HPEN m_hDefaultPen;
	HBRUSH m_hDefaultBrush;

public:
	SelectGDI(HDC _hdc, PEN_TYPE _ePenType);
	SelectGDI(HDC _hdc, BRUSH_TYPE _eBrushType);
	~SelectGDI();
};

