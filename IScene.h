#pragma once

#include "SceneGraph.h"
#include "Timer.h"
#include "InputSystem.h"

class SceneGraph;

class IScene
{
protected:
	std::unordered_map<std::string, IScene*>_sceneDependencies;
	SceneGraph _sceneManager;

public:
	IScene() {};
	~IScene() {};
	virtual void Update(double DeltaTime) = 0;
	virtual void Draw() = 0;
	void AddSceneDependency(IScene* scene, std::string sceneName);
};


