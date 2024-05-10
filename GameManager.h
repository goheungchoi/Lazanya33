#pragma once

class GameManager
{
private:
	static GameManager* _instance;
public:
	GameManager();
	~GameManager();

	void Initialize();

	void Update();

	void FixedUpdate();

	void Render();

	void Finalize();

	void Run();

	static GameManager* GetInstance();

	static void DestroyInstance();
};