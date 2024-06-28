#include "SceneGraph.h"

// Scenes
#include "EntryScene.h"
#include "LetterScene.h"
#include "PlayScene.h"
#include "DecoratorScene.h"
#include "DeveloperScene.h"
#include "BlcokIntroduction.h"
#include "ArtWorkScene1.h"
#include "ArtWorkScene2.h"
#include "ArtWorkScene3.h"
#include "DescriptionScene.h"

SceneGraph::SceneGraph()
{
	IScene::_sceneManager = this;

	_pGameDataHub = new GameDataHub();
	_pGameDataHub->LoadHistoryFromFile(L"Data//records.txt");
}

SceneGraph::~SceneGraph()
{
	// Save all data when destructing this scene graph.
	_pGameDataHub->SaveHistoryToFile();
	delete _pGameDataHub;

	/*for (auto it = _sceneRegistry.begin(); it != _sceneRegistry.end(); ++it)
	{
		delete it->second;
	}*/
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
	_sceneRegistry["ArtWork2"] = new ArtWorkScene2;
	_sceneRegistry["ArtWork3"] = new ArtWorkScene3;
	_sceneRegistry["Play"] = new PlayScene;
	_sceneRegistry["Block"] = new BlcokIntroduction;
	_sceneRegistry["Description"] = new DescriptionScene;
	//...scene Ãß°¡

	_sceneRegistry["Entry"]->AddSceneDependency(_sceneRegistry["Letter"], "Letter");
	_sceneRegistry["Entry"]->AddSceneDependency(_sceneRegistry["Decorator"], "Decorator");
	_sceneRegistry["Entry"]->AddSceneDependency(_sceneRegistry["Developer"], "Developer");
	_sceneRegistry["Entry"]->AddSceneDependency(_sceneRegistry["ArtWork1"], "ArtWork1");
	_sceneRegistry["Entry"]->AddSceneDependency(_sceneRegistry["Block"], "Block");
	_sceneRegistry["Entry"]->AddSceneDependency(_sceneRegistry["Description"], "Description");

	_sceneRegistry["Letter"]->AddSceneDependency(_sceneRegistry["Play"], "Play");

	_sceneRegistry["Play"]->AddSceneDependency(_sceneRegistry["Entry"], "Entry");

	_sceneRegistry["Developer"]->AddSceneDependency(_sceneRegistry["Entry"], "Entry");

	_sceneRegistry["Decorator"]->AddSceneDependency(_sceneRegistry["Entry"], "Entry");

	_sceneRegistry["ArtWork1"]->AddSceneDependency(_sceneRegistry["Entry"], "Entry");
	_sceneRegistry["ArtWork1"]->AddSceneDependency(_sceneRegistry["ArtWork2"], "ArtWork2");

	_sceneRegistry["ArtWork2"]->AddSceneDependency(_sceneRegistry["ArtWork1"], "ArtWork1");
	_sceneRegistry["ArtWork2"]->AddSceneDependency(_sceneRegistry["ArtWork3"], "ArtWork3");

	_sceneRegistry["ArtWork3"]->AddSceneDependency(_sceneRegistry["ArtWork2"], "ArtWork2");

	_sceneRegistry["Block"]->AddSceneDependency(_sceneRegistry["Entry"], "Entry");

	_sceneRegistry["Description"]->AddSceneDependency(_sceneRegistry["Entry"], "Entry");


	//Ã¹ ¾À
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
