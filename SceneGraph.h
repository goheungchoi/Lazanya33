#pragma once
#include "Timer.h"

#include "GameDataHub.h"

// Singleton Classes
#include "WinApp.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "CSound.h"

class IScene;

class SceneGraph
{
	friend class IScene;
	GameDataHub* _pGameDataHub;

private:
	IScene* _currScenePtr;
	std::unordered_map<std::string,IScene*>_sceneRegistry;

public:
	SceneGraph();
	~SceneGraph();

	IScene* GetCurrentScene();
	
	void ChangeScene(const std::string &sceneName);
	void Update(double deltaTime);
	void Draw();
	void RegisterScene();
};

class IScene
{
protected:
	friend class SceneGraph;

	std::unordered_map<std::string, IScene*>_sceneDependencies;
	static SceneGraph* _sceneManager;
	
	bool DidInit = false;

public:
	IScene();
	~IScene();
	virtual void Update(const double deltaTime) = 0;
	virtual void Draw() = 0;
	virtual void InitScene() = 0;
	virtual void EndScene() = 0;

	void AddSceneDependency(IScene* scene, std::string sceneName);
	
	GameDataHub& GetGameDataHub() {
		return *_sceneManager->_pGameDataHub;
	}

	static class RenderSystem* _renderSystem;
};

inline RenderSystem* IScene::_renderSystem = nullptr;
inline SceneGraph* IScene::_sceneManager = nullptr;


