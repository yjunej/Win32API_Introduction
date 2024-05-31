// Win32API_Introduction.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Win32API_Introduction.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND g_hWnd; // for Timer


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32APIINTRODUCTION, szWindowClass, MAX_LOADSTRING);

    // Class Register
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

     
    // Load HotKey Table
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32APIINTRODUCTION));

    MSG msg;


    //SetTimer(g_hWnd, 0, 0, nullptr);


    // Main message loop:
    // GetMessage: Return if Messages exist, return false if msg.message == WM_QUIT
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32APIINTRODUCTION));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32APIINTRODUCTION);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   //g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
   //    CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//


#include <vector>

using std::vector;

struct tObjInfo
{
    POINT g_ptrObjPos;
    POINT g_ptrObjScale;
};

vector<tObjInfo> g_vecInfo;

POINT g_ptrLeftTop;
POINT g_ptrRightBottom;

bool bLBDown = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT: // paint invalidate area (최소화 후 다시 클릭 / 드래그)
        {
            PAINTSTRUCT ps;

            /*
              struct __HWND {int a;} typedef HWND;
            id값을 포함하는 구조체
            */
            HDC hdc = BeginPaint(hWnd, &ps); // Device Context를 만들고 ID 반환
            // Pen, Brush를 가지고 hWnd에 그리는 Device Context
 
            //GetStockObject() - 미리 만들어진 Object Get
            HPEN hRedPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));



            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

            SelectObject(hdc, hDefaultPen);
            SelectObject(hdc, hDefaultBrush);

            // Draw Rectangle created by current cursor
            if (bLBDown)
            {
                Rectangle(hdc,
                    g_ptrLeftTop.x,
                    g_ptrLeftTop.y,
                    g_ptrRightBottom.x,
                    g_ptrRightBottom.y
                );
            }

            for (size_t i = 0; i < g_vecInfo.size(); ++i)
            {
                Rectangle(hdc,
                    g_vecInfo[i].g_ptrObjPos.x - g_vecInfo[i].g_ptrObjScale.x / 2,
                    g_vecInfo[i].g_ptrObjPos.y - g_vecInfo[i].g_ptrObjScale.y / 2,
                    g_vecInfo[i].g_ptrObjPos.x + g_vecInfo[i].g_ptrObjScale.x / 2,
                    g_vecInfo[i].g_ptrObjPos.y + g_vecInfo[i].g_ptrObjScale.y / 2
                );
            }
            


            DeleteObject(hRedPen);
            DeleteObject(hBlueBrush);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    // Keyboard
    case WM_KEYDOWN:
    {

        switch (wParam)
        {

        case 'Q':
            //g_ptrObjScale.x -= 10;
            //g_ptrObjScale.y -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case 'W':
            //g_ptrObjScale.x += 10;
            //g_ptrObjScale.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_UP:
            //g_ptrObjPos.y -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_LEFT:
            //g_ptrObjPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_DOWN:
            //g_ptrObjPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_RIGHT:
            //g_ptrObjPos.x += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;


        default:
            break;
        }
    }

    case WM_LBUTTONDOWN:
    {
        // LPARAM <- int64 
        g_ptrLeftTop.x = LOWORD(lParam); // Cursot X-pos
        g_ptrLeftTop.y = HIWORD(lParam); // Cursor Y-pos
        bLBDown = true;
        break;
    }

    case WM_MOUSEMOVE:
    {
        g_ptrRightBottom.x = LOWORD(lParam);
        g_ptrRightBottom.y = HIWORD(lParam);
        InvalidateRect(hWnd, nullptr, true);
        break;
    }

    case WM_LBUTTONUP:
    {
        tObjInfo objInfo = {};
        objInfo.g_ptrObjPos.x = g_ptrLeftTop.x + (g_ptrRightBottom.x - g_ptrLeftTop.x) / 2;
        objInfo.g_ptrObjPos.y = g_ptrLeftTop.y + (g_ptrRightBottom.y - g_ptrLeftTop.y) / 2;
        objInfo.g_ptrObjScale.x = abs(g_ptrRightBottom.x - g_ptrLeftTop.x);
        objInfo.g_ptrObjScale.y = abs(g_ptrRightBottom.y - g_ptrLeftTop.y);

        g_vecInfo.push_back(objInfo);
        bLBDown = false;
        InvalidateRect(hWnd, nullptr, true);
        break;
    }
    
    // Timer Case
    //case WM_TIMER:
    //    break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
