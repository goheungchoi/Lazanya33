#include "pch.h"
#include <Windows.h>
#include"GameManager.h"

GameManager* GameManager::_instance = nullptr;

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::Initialize()
{
}

void GameManager::Update()
{
}

void GameManager::FixedUpdate()
{
}

void GameManager::Render()
{
}

void GameManager::Finalize()
{
}

void GameManager::Run()
{
	MSG msg;
	while (true)
	{

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// WM_QUIT 메시지 확인
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			FixedUpdate();

			Update();

			Render();
		}
	}
}

GameManager* GameManager::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new GameManager;
	}
	return _instance;
}

void GameManager::DestroyInstance()
{
	delete _instance;
}