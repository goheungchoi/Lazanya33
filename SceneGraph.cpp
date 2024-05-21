#include "SceneGraph.h"

// Scenes
#include "EntryScene.h"
#include "LetterScene.h"
#include "PlayScene.h"
#include "DecoratorScene.h"
#include "DeveloperScene.h"
#include "ArtWorkScene1.h"


SceneGraph::SceneGraph()
{
	IScene::_sceneManager = this;

	_pGameDataHub = new GameDataHub();
	_pGameDataHub->LoadHistoryFromFile(L"Logs/records.txt");
	_pGameDataHub->Init();
}

SceneGraph::~SceneGraph()
{
	// Save all data when destructing this scene graph.
	_pGameDataHub->SaveHistoryToFile();
	delete _pGameDataHub;

	for (auto it = _sceneRegistry.begin(); it != _sceneRegistry.end(); ++it)
	{
		delete it->second;
	}
}

IScene* SceneGraph::GetCurrentScene()
{
	return _currScenePtr;
}

void SceneGraph::RegisterScene()
{
	_sceneRegistry["Entry"] = new EntryScene;
	_sceneRegistry["Letter"] = new LetterScene;
	_sceneRegistry["Decorator"] = new DecoratorScene;
	_sceneRegistry["Developer"] = new DeveloperScene;
	_sceneRegistry["ArtWork1"] = new ArtWorkScene1;
	_sceneRegistry["Play"] = new PlayScene;
	//...scene �߰�

	_sceneRegistry["Entry"]->AddSceneDependency(_sceneRegistry["Letter"], "Letter");
	_sceneRegistry["Entry"]->AddSceneDependency(_sceneRegistry["Decorator"], "Decorator");
	_sceneRegistry["Entry"]->AddSceneDependency(_sceneRegistry["Developer"], "Developer");
	_sceneRegistry["Entry"]->AddSceneDependency(_sceneRegistry["ArtWork1"], "ArtWork1");

	_sceneRegistry["Letter"]->AddSceneDependency(_sceneRegistry["Play"], "Play");

	_sceneRegistry["Play"]->AddSceneDependency(_sceneRegistry["Entry"], "Entry");

	_sceneRegistry["Developer"]->AddSceneDependency(_sceneRegistry["Entry"], "Entry");

	_sceneRegistry["Decorator"]->AddSceneDependency(_sceneRegistry["Entry"], "Entry");

	_sceneRegistry["ArtWork1"]->AddSceneDependency(_sceneRegistry["Entry"], "Entry");

	//ù ��
	//TODO: ������� ->ù �� play ���߿� Entry�� �ٲٱ�
	_currScenePtr = _sceneRegistry.find("Entry")->second;
	_currScenePtr->InitScene();
}

void SceneGraph::ChangeScene(const std::string& sceneName)
{
	IScene* newScene = _currScenePtr->_sceneDependencies.find(sceneName)->second;
	_currScenePtr->EndScene();
	_currScenePtr = newScene;
	_currScenePtr->InitScene();
}

void SceneGraph::Update(double deltaTime)
{
	_currScenePtr->Update(deltaTime);
}

void SceneGraph::Draw()
{
	_currScenePtr->Draw();
}
//-------------------------------------------------------------------

IScene::IScene()
{
}

IScene::~IScene()
{
}

void IScene::AddSceneDependency(IScene* scene, std::string sceneName)
{
	_sceneDependencies[sceneName] = scene;
}
