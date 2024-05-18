#include "pch.h"
#include <Windows.h>
#include "WinApp.h"
#include "Engine.h"

namespace global
{
	WinApp winApp;

	WinApp& GetWinApp()
	{
		return winApp;
	}
}


//center the screen
//void PlaceInCenterOfScreen(HWND window, DWORD style, DWORD exStyle)
//{
//	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
//	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
//
//	RECT clientRect;
//	GetClientRect(window, &clientRect);
//
//	int clientWidth = clientRect.right - clientRect.left;
//	int clientHeight = clientRect.bottom - clientRect.top;
//
//	SetWindowPos(window, NULL,
//		screenWidth / 2 - clientWidth / 2,
//		screenHeight / 2 - clientHeight / 2,
//		clientWidth, clientHeight, 0
//	);
//}

void WinApp::Initialize(HINSTANCE hInstance)
{
	_hInstance = hInstance;

	const TCHAR* appName = TEXT("input game name");//name of game
	
	//step 1. register window class
	WNDCLASS wndClass;

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = appName;

	RegisterClass(&wndClass);

	//step 2. make window
	RECT rect{ 10,10,10 + _screenWidth,10 + _screenHeight };
	
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	_hWnd = CreateWindow(appName, appName, WS_POPUP/*WS_OVERLAPPED*/ | WS_SYSMENU,
		10,10, width, height, NULL, NULL, hInstance, NULL);

	ShowWindow(_hWnd, SW_MAXIMIZE/*SW_SHOWNORMAL*/);
	UpdateWindow(_hWnd);

	Engine::GetInstance()->Initialize();
}

void WinApp::Run()
{
	Engine::GetInstance()->Run();
}

void WinApp::Finalize()
{
	Engine::GetInstance()->Finalize();
	Engine::GetInstance()->DestroyInstance();
}

LRESULT WinApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		/*PlaceInCenterOfScreen(hWnd, WS_OVERLAPPEDWINDOW, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);*/
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



