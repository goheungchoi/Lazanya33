#pragma once
#include "SceneGraph.h"


class DeveloperScene:public IScene
{
public:
	DeveloperScene();
	~DeveloperScene() {};
	void Update(double deltaTime)override;
	void Draw()override;
	void InitScene()override;
	void EndScene()override;
};

