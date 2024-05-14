#pragma once
#include "Timer.h"
#include "InputSystem.h"
#include "WinApp.h"
#include "RenderSystem.h"

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

class IScene
{
	friend class SceneGraph;
protected:
	std::unordered_map<std::string, IScene*>_sceneDependencies;
	static SceneGraph* _sceneManager;

public:
	IScene();
	~IScene();
	virtual void Update(double DeltaTime) = 0;
	virtual void Draw() = 0;
	void AddSceneDependency(IScene* scene, std::string sceneName);

	static class RenderSystem* _renderSystem;
};

inline RenderSystem* IScene::_renderSystem = nullptr;
inline SceneGraph* IScene::_sceneManager = nullptr;


