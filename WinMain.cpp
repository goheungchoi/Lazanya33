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

	try {
       
	global::GetWinApp().Initialize(hInstance);

	global::GetWinApp().Run();

	global::GetWinApp().Finalize();

	} catch (const std::exception& e) {
    const char* w = e.what();
		std::wstring wstr;
		wstr.append(L"\t-> ");
		for (std::size_t i=0; w[i] != '\0'; ++i) {
			wstr.push_back(static_cast<wchar_t>(w[i]));
		}
		wstr.push_back(L'\n');
		OutputDebugString(wstr.data());
	}

	return EXIT_SUCCESS; //0
}