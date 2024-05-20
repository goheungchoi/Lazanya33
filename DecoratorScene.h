#pragma once
#include "SceneGraph.h"

class DecoratorScene:public IScene
{
public:
	DecoratorScene();
	~DecoratorScene() {};
	void Update(double deltaTime)override;
	void Draw()override;
	void InitScene()override;
	void EndScene()override;
};

