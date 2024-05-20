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



void SceneGraph::RegisterScene()
{
	_sceneRegistry["Entry"] = new EntryScene;
	_sceneRegistry["Play"] = new PlayScene;
	//...scene �߰�

	_sceneRegistry["Entry"]->AddSceneDependency(_sceneRegistry["Play"], "Play");
	//ù ��
	//TODO: ������� ->ù �� play ���߿� Entry�� �ٲٱ�
	_currScenePtr = _sceneRegistry.find("Entry")->second;
}



void SceneGraph::ChangeScene(const std::string& sceneName)
{
	IScene* newScene = _currScenePtr->_sceneDependencies.find(sceneName)->second;
	_currScenePtr = newScene;
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
