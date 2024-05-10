#pragma once

class WinApp
{
private:
	HINSTANCE _hInstance = { 0, };
	HWND _hWnd = { 0, };

	int _screenWidth = 1600;
	int _screenHeight = 900;

public:
	WinApp() = default;
	~WinApp() = default;

	void Initialize(HINSTANCE hInstance);
	void Run();
	void Finalize();

	HINSTANCE GetInstance() const
	{
		return _hInstance;
	}

	HWND GetWindow()const
	{
		return _hWnd;
	}

	const int GetWidth()const
	{
		return _screenWidth;
	}

	const int GetHeight()const
	{
		return _screenHeight;
	}


	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


};

namespace global
{
	WinApp& GetWinApp();
}



