#pragma once
#include "SceneGraph.h"
#include "Player.h"

class EntryScene: public IScene
{
	class IRenderable* _drawableObject;
	Player* player=new Player;

public:
	EntryScene();
	~EntryScene() {};
	void Update(double DeltaTime)override;
	void Draw()override;
};

