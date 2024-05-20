#pragma once
#include"SceneGraph.h"


class ArtWorkScene:public IScene
{
public:
	ArtWorkScene();
	~ArtWorkScene() {};
	void Update(double deltaTime)override;
	void Draw()override;
	void InitScene()override;
	void EndScene()override;
};

