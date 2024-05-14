#include "pch.h"

#include "SceneGraph.h"
#include "EntryScene.h"
#include "PlayScene.h"

SceneGraph::SceneGraph()
{
	IScene::_sceneManager = this;
}

SceneGraph::~SceneGraph()
{
	for (auto it = _sceneRegistry.begin(); it != _sceneRegistry.end(); ++it)
	{
		delete it->second;
	}
}

IScene* SceneGraph::GetCurrentScene()
{
	return _currScenePtr;
}



void SceneGraph::InitScene()
{
	_sceneRegistry["Entry"] = new EntryScene;
	_sceneRegistry["Play"] = new PlayScene;
	//...scene Ãß°¡

	_sceneRegistry["Entry"]->AddSceneDependency(_sceneRegistry["Play"], "Play");
	//Ã¹ ¾À
	_currScenePtr = _sceneRegistry.find("Entry")->second;
}



void SceneGraph::ChangeScene(IScene* newScene)
{
	
	_currScenePtr = newScene;
}

void SceneGraph::Update(double DeltaTime)
{
	_currScenePtr->Update(DeltaTime);
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
