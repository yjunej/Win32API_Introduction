#pragma once
#include "CUI.h"

// Function
#include "CScene.h"
#include "CObject.h"

//class CScene;
//class CObject;

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);
typedef void(CScene::*SCENE_MEMFUNC)(void);
typedef void(CObject::*OBJECT_MEMFUNC)(void);


class CButtonUI : public CUI
{

private:
	BTN_FUNC m_pFunc;
	DWORD_PTR m_pParam1;
	DWORD_PTR m_pParam2;

	SCENE_MEMFUNC m_pSceneFunc;
	CScene* m_pSceneInst;

public:

	virtual void OnMouseHovered();
	virtual void OnMouseLBPressed();
	virtual void OnMouseLBReleased();
	virtual void OnMouseLBClicked();


	// Overloading Callback
	void SetClickCallback(BTN_FUNC _pFunc, DWORD_PTR _pParam1, DWORD_PTR _pParam2)
	{ 
		m_pFunc = _pFunc;
		m_pParam1 = _pParam1;
		m_pParam2 = _pParam2;
	}

	void SetClickCallback(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);


	CLONE(CButtonUI)


public:
    CButtonUI();	
    ~CButtonUI();

};

