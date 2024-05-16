#include "pch.h"
#include "WinApp.h"
#include "Engine.h"
#include "Timer.h"
#include "SceneGraph.h"
#include "InputSystem.h"
#include "CSound.h"

// Rendering Libraries
#include "RenderSystem.h"
#include "SingleRenderable.h"

Engine::Engine()
{
	_sceneGraph = new SceneGraph;

	// TODO: Drawing Test
	_renderer = new GDIRenderer(global::GetWinApp().GetWindow(), 
															{global::GetWinApp().GetWidth(), 
															 global::GetWinApp().GetHeight()});
	_renderSystem = new RenderSystem(_renderer);
	IScene::_renderSystem = _renderSystem;
}

Engine::~Engine()
{
	delete _sceneGraph;
}

void Engine::Initialize()
{
	//add Sound 11:00
	Music::soundManager->InitMusic();
	Music::soundManager->SetVolume(0.1f);
	Timer::InitTimer();
	Input::inputManager->InitInput();
	
	_sceneGraph->RegisterScene();

	// TODO: Drawing Test
}

void Engine::Update(double deltaTime)
{
	Input::inputManager->Update();
	_sceneGraph->GetCurrentScene()->Update(deltaTime);
}

void Engine::Render()
{
	_sceneGraph->GetCurrentScene()->Draw();
}

void Engine::Finalize()
{
}

void Engine::Run()
{
	MSG msg;
	double prevTime = Timer::GetTick();
	double currTime = 0.0;
	double deltaTime = 0.0;
	double accuulator = 0.0;

	//Main loop
	while (true)
	{
		//Update DT
		currTime = Timer::GetTick();
		deltaTime = currTime - prevTime;
		prevTime = currTime;

		 
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
			Update(deltaTime);

			Render();
		}
	}
}

Engine* Engine::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Engine;
	}
	return _instance;
}

void Engine::DestroyInstance()
{
	delete _instance;
}