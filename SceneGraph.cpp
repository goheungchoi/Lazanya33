#include "pch.h"
#include "SceneGraph.h"
#include "EntryScene.h"
#include "LetterScene.h"


SceneGraph::SceneGraph()
{
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
	_sceneRegistry["Letter"] = new LetterScene;
	
	//...scene Ãß°¡
	_sceneRegistry["Entry"]->AddSceneDependency(_sceneRegistry["Letter"],"Letter");
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

void IScene::AddSceneDependency(IScene* scene, std::string sceneName)
{
	_sceneDependencies[sceneName] = scene;
}
