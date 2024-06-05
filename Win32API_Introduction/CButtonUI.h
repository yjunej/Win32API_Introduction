#pragma once
#include "CUI.h"

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

class CButtonUI : public CUI
{

private:
	BTN_FUNC m_pFunc;
	DWORD_PTR m_pParam1;
	DWORD_PTR m_pParam2;

public:

	virtual void OnMouseHovered();
	virtual void OnMouseLBPressed();
	virtual void OnMouseLBReleased();
	virtual void OnMouseLBClicked();

	void SetClickCallback(BTN_FUNC _pFunc, DWORD_PTR _pParam1, DWORD_PTR _pParam2)
	{ 
		m_pFunc = _pFunc;
		m_pParam1 = _pParam1;
		m_pParam2 = _pParam2;
	}


	CLONE(CButtonUI)


public:
    CButtonUI();	
    ~CButtonUI();

};

