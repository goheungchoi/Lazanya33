#pragma once

class Engine
{
private:
	static Engine* _instance;

	class	SceneGraph* _sceneGraph;
	class GDIRenderer* _renderer;
	class RenderSystem* _renderSystem;
	class IRenderable* _drawableObject;
public:
	Engine();
	~Engine();

	void Initialize();

	void Update(double DeltaTime);

	void Render();

	void Finalize();

	void Run();

	static Engine* GetInstance();

	static void DestroyInstance();
};

inline Engine* Engine::_instance = nullptr;