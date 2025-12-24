// RTS.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "RTS.h"

#include <objidl.h>
#include <gdiplus.h>

#include <windows.h>

#pragma comment (lib, "Gdiplus.lib")

typedef struct
{
    float x, y, width, heigth, speed;
    HBITMAP hBitmap;
} sprite;

sprite unit;
sprite vehicle;
sprite factory;

struct
{
    HWND hWnd;
    HDC device_context, context;
    int width, heigth;
}window;

HBITMAP map;

//#define MAX_LOADSTRING 100
//
//using namespace std;
//
//ULONG_PTR gdiplusToken;
//HWND hWnd;
//
////window size
//int ScreenX = GetSystemMetrics(SM_CXSCREEN);
//int ScreenY = GetSystemMetrics(SM_CYSCREEN);
//
//#define MAX_LOADSTRING 100
//
//// Глобальные переменные:
//HINSTANCE hInst;                                // текущий экземпляр6
////WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
////WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
//
//// Отправить объявления функций, включенных в этот модуль кода:
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
////INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


void InitGame()
{
    map = (HBITMAP)LoadImageA(NULL, "Map.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void ShowBitmap(HDC hDC,int x, int y,int x1,int y1,HBITMAP hBitmapBall, bool alpha = false)
{
    HBITMAP hbm, hOldbm;
    HDC hMemDC;
    BITMAP bm;

    hMemDC = CreateCompatibleDC(hDC);
    hOldbm = (HBITMAP)SelectObject(hMemDC, hBitmapBall);

    if (hOldbm)
    {
        GetObject(hBitmapBall, sizeof(BITMAP), (LPSTR)&bm);
        if (alpha)
        {
            TransparentBlt(window.context, x, y, x1, y1, hMemDC, 0, 0, x1, y1, RGB(0, 0, 0));
        }
        else
        {
            StretchBlt(hDC, x, y, x1, y1, hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
        }
        SelectObject(hMemDC, hOldbm);
    }

    DeleteDC(hMemDC);
}

void InitWindows()
{
    SetProcessDPIAware();
    window.hWnd = CreateWindow("edit", 0, WS_POPUP | WS_VISIBLE | WS_MAXIMIZE, 0, 0, 0, 0, 0, 0, 0, 0);

    RECT r;
    GetClientRect(window.hWnd, &r);
    window.device_context = GetDC(window.hWnd);
    window.width = r.right - r.left;
    window.heigth = r.bottom - r.top;
    window.context = CreateCompatibleDC(window.device_context);
    SelectObject(window.context, CreateCompatibleBitmap(window.device_context, window.width, window.heigth));
    GetClientRect(window.hWnd, &r);
}

int APIENTRY wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPWSTR lpCmdLine,int nCmdShow)
{
    InitGame();
    //UNREFERENCED_PARAMETER(hPrevInstance);
    //UNREFERENCED_PARAMETER(lpCmdLine);

    //Gdiplus::GdiplusStartupInput gdiplusStartupInput; // GDI+ open
    //Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    //// Инициализация глобальных строк
    ////LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    ////LoadStringW(hInstance, IDC_RTS, szWindowClass, MAX_LOADSTRING);
    //MyRegisterClass(hInstance);

    //// Выполнить инициализацию приложения:
    //if (!InitInstance(hInstance, nCmdShow))
    //{
    //    return FALSE;
    //}

    //HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RTS));

    //MSG msg;

    //// Цикл основного сообщения:
    while (!GetAsyncKeyState(VK_ESCAPE));
    //{
    //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //    {
    //        TranslateMessage(&msg);
    //        DispatchMessage(&msg);
    //    }
    //}

    //return (int)msg.wParam;
}

//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//    WNDCLASSEXW wcex;
//
//    wcex.cbSize = sizeof(WNDCLASSEX);
//
//    wcex.style = CS_HREDRAW | CS_VREDRAW;
//    wcex.lpfnWndProc = WndProc;
//    wcex.cbClsExtra = 0;
//    wcex.cbWndExtra = 0;
//    wcex.hInstance = hInstance;
//    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RTS));
//    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
//    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_RTS);
//    wcex.lpszClassName = L"FullScreenGDIPlus"/*szWindowClass*/;
//    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//    return RegisterClassExW(&wcex);
//}

//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной
//
//    HWND hWnd = CreateWindowEx
//    //(szWindowClass, szTitle, WS_VISIBLE|WS_POPUP, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
//    (WS_EX_TOPMOST, L"FullScreenGDIPlus", NULL, WS_VISIBLE|WS_POPUP,0, 0, ScreenX, ScreenY, NULL, NULL, hInstance, NULL);
//
//    if (!hWnd)
//    {
//        return FALSE;
//    }
//
//    ShowWindow(hWnd, nCmdShow);
//    UpdateWindow(hWnd);
//
//    return TRUE;
//}

//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    switch (message)
//    {
//    //case WM_COMMAND:
//    //{
//    //    int wmId = LOWORD(wParam);
//    //    // Разобрать выбор в меню:
//    //    switch (wmId)
//    //    {
//    //    case IDM_ABOUT:
//    //        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//    //        break;
//    //    case IDM_EXIT:
//    //        DestroyWindow(hWnd);
//    //        break;
//    //    default:
//    //        return DefWindowProc(hWnd, message, wParam, lParam);
//    //    }
//    //}
//    break;
//    case WM_PAINT:
//    {
//        PAINTSTRUCT ps;
//        HDC hdc = BeginPaint(hWnd, &ps);
//        Gdiplus::Bitmap backBuffer(ScreenX, ScreenY);
//        Gdiplus::Graphics* backGraphics = Gdiplus::Graphics::FromImage(&backBuffer);
//
//        Gdiplus::Image* Map = Gdiplus::Image::FromFile(L"Map.bmp");
//
//        if (Map && Map->GetLastStatus() == Gdiplus::Status::Ok)
//        {
//            backGraphics->DrawImage(Map, 0, 0);
//        }
//        delete Map;
//
//        //second buffer
//        Gdiplus::Graphics screenGraphics(hdc);
//        screenGraphics.DrawImage(&backBuffer, 0, 0, 0, 0, ScreenX, ScreenY, Gdiplus::UnitPixel);
//        delete backGraphics;
//
//        EndPaint(hWnd, &ps);
//    }
//    break;
//    case WM_DESTROY:
//        Gdiplus::GdiplusShutdown(gdiplusToken); //GDI+ close
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}

// Обработчик сообщений для окна "О программе".
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}