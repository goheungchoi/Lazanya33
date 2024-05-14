#include "pch.h"

#include "SceneGraph.h"
#include "EntryScene.h"
#include "LetterScene.h"


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
	_sceneRegistry["Letter"] = new LetterScene;
	
	//...scene �߰�
	_sceneRegistry["Entry"]->AddSceneDependency(_sceneRegistry["Letter"],"Letter");

	//ù ��
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
