#pragma once


class CCore
{
public:
	SINGLE(CCore);

private:
	HWND m_hWnd; // main window handle
	POINT m_ptrResolution;


public:
	int Init(HWND m_hWnd, POINT m_ptrResolution);

private:
	CCore();
	~CCore();
	CCore(const CCore&) = delete;
	CCore& operator=(const CCore&) = delete;
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