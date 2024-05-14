#pragma once
#include "IScene.h"

class IScene;

class SceneGraph
{
private:
	IScene* _currScenePtr;
	std::unordered_map<std::string,IScene*>_sceneRegistry;
	
public:
	SceneGraph();
	~SceneGraph();

	IScene* GetCurrentScene();
	
	void InitScene();
	void ChangeScene(IScene* newScene);
	void Update(double DeltaTime);
	void Draw();

};

