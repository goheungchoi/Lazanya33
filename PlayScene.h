#pragma once
#include "SceneGraph.h"
#include "Player.h"
class PlayScene :public IScene
{
	class IRenderable* _drawableObject;
	IPlayer* player = new Player();
public:
	PlayScene();
	~PlayScene() {};
	
	void Update(double DeltaTime)override;
	void Draw()override;
};

