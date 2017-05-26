// game.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "game.h"

#define MAX_LOADSTRING 100

using namespace Gdiplus;
using namespace std;

// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.
TCHAR szTitle[MAX_LOADSTRING];					// 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 여기에 코드를 입력합니다.
	
	ULONG_PTR gpToken;
	GdiplusStartupInput gpsi;
	if (GdiplusStartup(&gpToken,&gpsi,NULL) != Ok)
	{
		MessageBox(NULL,TEXT("GDI+ 라이브러리를 초기화할 수 없습니다."), TEXT("알림"),MB_OK);
		return 0;
	}

	MSG msg;
	HACCEL hAccelTable;

	// 전역 문자열을 초기화합니다.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAME));
	wstring wsWindowClass(szWindowClass);
	wstring wsTitle(szTitle);
	string sWindowClass;
	string sTitle;
	sWindowClass.assign(wsWindowClass.begin(), wsWindowClass.end());
	sTitle.assign(wsTitle.begin(), wsTitle.end());

	/*
		Main Loop 시작
	*/

	// Frame 제어를 위해 필요
	auto oldtime = chrono::system_clock::now();
	auto newtime = chrono::system_clock::now();
	std::chrono::microseconds deltatime(0);
	std::chrono::microseconds timestep(16600);

	// 이용자에게 루프 시작을 알려줌
	StartEvent();
	while (1)
	{
		// 윈도우 메시지를 먼저 처리함
		while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			// if quit
			if (!GetMessage(&msg, NULL, 0, 0))
			{
				GdiplusShutdown(gpToken);
				return (int)msg.wParam;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		while(deltatime < timestep)
		{
			newtime = chrono::system_clock::now();
			deltatime = chrono::duration_cast<chrono::microseconds>(newtime - oldtime);
		}
		scene->Update(chrono::duration_cast<chrono::milliseconds>(deltatime));
		scene->Render();
		oldtime = newtime;
	}

	// never gets here
	GdiplusShutdown(gpToken);
	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
//  설명:
//
//    Windows 95에서 추가된 'RegisterClassEx' 함수보다 먼저
//    해당 코드가 Win32 시스템과 호환되도록
//    하려는 경우에만 이 함수를 사용합니다. 이 함수를 호출해야
//    해당 응용 프로그램에 연결된
//    '올바른 형식의' 작은 아이콘을 가져올 수 있습니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAME));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   RECT rect;
   LONG width = SCREEN_WIDTH, height = SCREEN_HEIGHT;
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   hWnd = CreateWindow(szWindowClass, szTitle, WS_BORDER,
      (GetSystemMetrics(0) - width) / 2, (GetSystemMetrics(1) - height) / 2, width, height, NULL, NULL, hInstance, NULL);
   GetClientRect(hWnd, &rect);
   width = width + width - rect.right;
   height = height + height - rect.bottom;
   // 완벽히 해상도를 맞춤
   SetWindowPos(hWnd, HWND_TOP, (GetSystemMetrics(0) - width) / 2, (GetSystemMetrics(1) - height) / 2, width, height, SWP_SHOWWINDOW);

   if (!hWnd)
   {
      return FALSE;
   }

   // Scene 초기화
   scene = new Scene(hWnd);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 그리기 코드를 추가합니다.
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
