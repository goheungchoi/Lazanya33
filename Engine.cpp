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

	/*ResourceManager::Get().LoadImageFromFile(
		L"Assets\\brick_can_00.png", 
		L"brick_can_00"
	);
	ResourceManager::Get().LoadImageFromFile(
		L"Assets\\lazanya_02.png", 
		L"lazanya_02"
	);*/
	ResourceManager::Get().LoadImages(L"Assets");
	ResourceManager::Get().CacheAllImages(_renderer->GetGraphics());

	// TODO: Sprite pack binding must be done at advance
	BDefault::AddSprite(
		ResourceManager::Get().GetImage(L"brick_can_00"),
		L"brick_can_00",
		_renderer->GetGraphics()	// Enable Caching
	);

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