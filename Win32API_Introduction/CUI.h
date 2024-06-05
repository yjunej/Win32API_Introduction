#pragma once
#include "CObject.h"

class CUI :public CObject
{

private:
	vector<CUI*> m_vecChildUI;
	CUI* m_pParentUI;
	Vec2 m_vUIPos;

	bool m_bCamDetached;
	bool m_bMouseHovered;
	bool m_bLBPressed;

public:
	Vec2 GetUIPos() const { return m_vUIPos; }
	CUI* GetParent() { return m_pParentUI; }
	const vector<CUI*>& GetChildren() const { return m_vecChildUI; }
	void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }
	bool IsMouseHovered() const { return m_bMouseHovered; }
	bool IsLBPressed() const { return m_bLBPressed; }

private:
	void CheckHovered();

	void UpdateChildren();
	void PostUpdateChildren();
	void RenderChildren(HDC _hdc);

public:
	virtual void Update() override;
	virtual void PostUpdate() override;
	virtual void Render(HDC _hdc) override;

	virtual void OnMouseHovered();
	virtual void OnMouseLBPressed();
	virtual void OnMouseLBReleased();
	virtual void OnMouseLBClicked();

	virtual CUI* Clone() = 0;

public:
	CUI(bool _bFollowCam);
	CUI(const CUI& _cUI);
	
	virtual ~CUI();


	friend class CUIMgr;
};

