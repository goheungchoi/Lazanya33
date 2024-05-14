// Lazanya33.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "framework.h"

#include "WinMain.h"
#include "WinApp.h"

#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "Gdiplus.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int	nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	global::GetWinApp().Initialize(hInstance);

	global::GetWinApp().Run();

	global::GetWinApp().Finalize();

	return EXIT_SUCCESS; //0
}