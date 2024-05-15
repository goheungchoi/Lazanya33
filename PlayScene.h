#pragma once
#include "SceneGraph.h"
#include "Player.h"
class PlayScene :public IScene
{
	class IRenderable* _drawableObject;
	IPlayer* _player = new Player();
	Wall* _walls = new Wall;

public:
	PlayScene();
	~PlayScene() {};
	
	void Update(double DeltaTime)override;
	void Draw()override;
};

