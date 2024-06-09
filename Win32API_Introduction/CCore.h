#pragma once

class CTexture;

class CCore
{
	SINGLE(CCore)

private:
	HWND m_hWnd; // main window handle
	POINT m_ptResolution; // main window resolution
	HDC m_hDC; // main window device context

	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];

	CTexture* m_pMemTex; // Back Buffer

	HMENU m_hMenu;

public:
	int Init(HWND m_hWnd, POINT m_ptResolution);
	void Progress();
	void ClearScreen();
	void CreatePaintTools();
	void AttachMenubar();
	void DetachMenubar();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);

public:
	HWND GetMainHwnd() const { return m_hWnd; }
	POINT GetResolution() const { return m_ptResolution; }
	HDC GetMainDC() const { return m_hDC; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) const { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) const { return m_arrPen[(UINT)_eType]; }
	HMENU GetMenu() const { return m_hMenu; }
};


//class CCore
//{
//
//public:
//	static CCore* GetInstance()
//	{
//		static CCore* pCore = nullptr;
//		if (nullptr == pCore)
//		{
//			pCore = new CCore;
//		}
//		return pCore; // pCore Addr: 0x00007FF7DEC25720, Val: 0x000001f55b626570
//	}
//
//	static void* Release()
//	{
//		//if (nullptr != pCore)
//		//{
//			//delete pCore;
//			//pCore = nullptr;
//			CCore* p = GetInstance(); // p Addr: 0x00000022FB6FF418, Val: 0x000001f55b626570
//			delete p;
//			//*p = nullptr;
//			int a = 1;
//			return nullptr;
//		//}
//	}
//
//private:
//	CCore() {};
//	~CCore() {};
//
//
//	// Disable Copy, Assignment Operator
//	CCore(const CCore&) = delete;
//	CCore& operator=(const CCore&) = delete;
//
//	static CCore* pCore;
//};