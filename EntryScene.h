#pragma once
#include "SceneGraph.h"
#include "Wall.h"

class EntryScene: public IScene
{
	class IRenderable* _drawableObject;
public:
	EntryScene();
	~EntryScene() {};
	void Update(double deltaTime)override;
	void Draw()override;
	void InitScene()override;
	void EndScene()override;
};

