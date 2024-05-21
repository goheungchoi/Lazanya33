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
#include "RandomGenerator.h"

// Attach images to the brick types
#ifndef NDEBUG
#include "Brick.h"
#endif

Engine::Engine()
{
	//Doing Debug:
	Debug.Get_Console();
	// Initialize ResourceManager Singleton
  ResourceManager::Create();
	// Initialize RandomGenerator Singleton
	RandomGenerator::Create();

	// Initialize Scene Graph
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
	RandomGenerator::Destory();
	delete _sceneGraph;
}

void Engine::Initialize()
{
	ResourceManager::Get().LoadImages(L"Assets");
	ResourceManager::Get().CacheAllImages(_renderer->GetGraphics());

	// TODO: Sprite pack binding must be done at advance
	InitBrickImage();

	Music::soundManager->InitMusic();
	Music::soundManager->SetVolume(0.5f);
	Timer::InitTimer();
	Input::inputManager->InitInput();
	
	_sceneGraph->RegisterScene();

	
#ifndef NDEBUG
	
	INT          count = 0;
	INT          found = 0;
	WCHAR        familyName[LF_FACESIZE];  // enough space for one family name
	WCHAR*       familyList = NULL;
	FontFamily*  pFontFamily = NULL;

	InstalledFontCollection installedFontCollection;

	// How many font families are installed?
	count = installedFontCollection.GetFamilyCount();

	// Allocate a buffer to hold the array of FontFamily
	// objects returned by GetFamilies.
	pFontFamily = new FontFamily[count];

	// Get the array of FontFamily objects.
	installedFontCollection.GetFamilies(count, pFontFamily, &found);
	Debug.Log(found);
	// The loop below creates a large string that is a comma-separated
	// list of all font family names.
	// Allocate a buffer large enough to hold that string.
	familyList = new WCHAR[count*(sizeof(familyName)+ 3)];

	for(INT j = 0; j < count; ++j)
	{
		 pFontFamily[j].GetFamilyName(familyName);  
		 Debug.Log(familyName);
	}

	delete [] pFontFamily;
	delete [] familyList;
#endif // !NDEBUG

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

void Engine::InitBrickImage()
{
	BDefault::AddSprite(
		ResourceManager::Get().GetImage(L"brick_default"),
		L"default",
		_renderer->GetGraphics()	// Enable Caching
	);
	BStone::AddSprite(
		ResourceManager::Get().GetImage(L"brick_stone"),
		L"stone",
		_renderer->GetGraphics()	// Enable Caching
	);
	BRock::AddSprite(
		ResourceManager::Get().GetImage(L"brick_rock"),
		L"rock",
		_renderer->GetGraphics()	// Enable Caching
	);
	BBomb::AddSprite(
		ResourceManager::Get().GetImage(L"brick_bomb_animation_1"),
		L"bombR",
		_renderer->GetGraphics()	// Enable Caching
	);
	BBomb::AddSprite(
		ResourceManager::Get().GetImage(L"brick_bomb_animation_2"),
		L"bombY",
		_renderer->GetGraphics()	// Enable Caching
	);
	BGold::AddSprite(
		ResourceManager::Get().GetImage(L"brick_gold"),
		L"gold",
		_renderer->GetGraphics()	// Enable Caching
	);
	BOxygen::AddSprite(
		ResourceManager::Get().GetImage(L"brick_air"),
		L"air",
		_renderer->GetGraphics()	// Enable Caching
	);
	BRasgulla::AddSprite(
		ResourceManager::Get().GetImage(L"brick_rasgulla"),
		L"rasgulla",
		_renderer->GetGraphics()	// Enable Caching
	);


	//break image
	BDefault::AddSprite(
		ResourceManager::Get().GetImage(L"B.brick_default"),
		L"B.default",
		_renderer->GetGraphics()	// Enable Caching
	);
	BStone::AddSprite(
		ResourceManager::Get().GetImage(L"B.brick_stone"),
		L"B.stone",
		_renderer->GetGraphics()	// Enable Caching
	);
	BRock::AddSprite(
		ResourceManager::Get().GetImage(L"B.brick_rock"),
		L"B.rock",
		_renderer->GetGraphics()	// Enable Caching
	);
	BBomb::AddSprite(
		ResourceManager::Get().GetImage(L"B.brick_bomb_animation_1"),
		L"B.bombR",
		_renderer->GetGraphics()	// Enable Caching
	);
	BBomb::AddSprite(
		ResourceManager::Get().GetImage(L"B.brick_bomb_animation_2"),
		L"B.bombY",
		_renderer->GetGraphics()	// Enable Caching
	);
	BGold::AddSprite(
		ResourceManager::Get().GetImage(L"B.brick_gold"),
		L"B.gold",
		_renderer->GetGraphics()	// Enable Caching
	);
	BOxygen::AddSprite(
		ResourceManager::Get().GetImage(L"B.brick_air"),
		L"B.air",
		_renderer->GetGraphics()	// Enable Caching
	);
	BRasgulla::AddSprite(
		ResourceManager::Get().GetImage(L"B.brick_rasgulla"),
		L"B.rasgulla",
		_renderer->GetGraphics()	// Enable Caching
	);


}
