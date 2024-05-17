#include "pch.h"
#include "WinApp.h"
#include "Engine.h"
#include "Timer.h"
#include "SceneGraph.h"
#include "InputSystem.h"
#include "CSound.h"
#include "DebugConsole.h"

// Rendering Libraries
#include "RenderSystem.h"
#include "SingleRenderable.h"
#include "ResourceManager.h"

// Attach images to the brick types
#ifndef NDEBUG
#include "Brick.h"
#endif

Engine::Engine()
{
	// Initialize ResourceManager Singleton
  ResourceManager::Create();

	_sceneGraph = new SceneGraph;

	// TODO: Drawing Test
	_renderer = new GDIRenderer(global::GetWinApp().GetWindow(), 
															{global::GetWinApp().GetWidth(), 
															 global::GetWinApp().GetHeight()});
	_renderSystem = new RenderSystem(_renderer);
	// Pass the render system to IScene
	// So that IScene can handle draw calls from IRenderable objects
	IScene::_renderSystem = _renderSystem;
}

Engine::~Engine()
{
	// Destroy ResourceManager Singleton
	ResourceManager::Destory();
	delete _sceneGraph;
}

void Engine::Initialize()
{
	ResourceManager::Get().LoadImageFromFile(
		L"Assets\\brick_can_00.png", 
		L"brick_can_00"
	);
	ResourceManager::Get().LoadImageFromFile(
		L"Assets\\lazanya_02.png", 
		L"lazanya_02"
	);

	// DEBUG
	BDefault bd;
	bd.BindSpriteWithTag(
		ResourceManager::Get().GetImage(L"brick_can_00"),
		L"brick_can_00"
	);
	_renderSystem->CachingHelper(&bd);

	Music::soundManager->InitMusic();
	Music::soundManager->SetVolume(0.1f);
	Timer::InitTimer();
	Input::inputManager->InitInput();
	
	_sceneGraph->RegisterScene();

	//Doing Debug:
	Debug.Get_Console();
}

void Engine::Update(const double deltaTime)
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
	//Doing Debug:
	Debug.Close_Console();
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
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// WM_QUIT, break the loop
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//Update dt
		currTime = Timer::GetTick();
		deltaTime = currTime - prevTime;
		prevTime = currTime;

		Update(deltaTime);

		Render();
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