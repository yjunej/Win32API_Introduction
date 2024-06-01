#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"

// Key Matching with WinAPI 
int g_arrVK[(int)KEY::LAST]
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',

	VK_MENU, //ALT
	VK_CONTROL,//CTRL
	VK_LSHIFT,//LSHIFT
	VK_SPACE,//SPACE
	VK_RETURN,//ENTER
	VK_ESCAPE,//ESC

	//LAST
};

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

int CKeyMgr::Init()
{
	for (size_t i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
	return 0;
}

void CKeyMgr::Update()
{

	// Investigate Focusing
	// HWND hMainWnd = CCore::GetInstance()->GetMainHwnd();
	HWND hWnd = GetFocus();

	if (nullptr != hWnd)
	{


		for (size_t i = 0; i < (int)KEY::LAST; ++i)
		{
			// Check Pressed
			//  & 1000 0000 0000 0000 , GetAsyncKeyState returns short
			// MSB indicates the key has pressed
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPressed)
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPressed = true;
			}
			else
			{
				if (m_vecKey[i].bPressed)
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPressed = false;
			}
		}
	}
	else
	{
		for (size_t i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPressed = false;
			if (m_vecKey[i].eState == KEY_STATE::TAP || m_vecKey[i].eState == KEY_STATE::HOLD)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (m_vecKey[i].eState == KEY_STATE::AWAY)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}

		}

	}
}
