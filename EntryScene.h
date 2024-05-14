#pragma once
#include "IScene.h"

class EntryScene: public IScene
{
	class IRenderable* _drawableObject;
public:
	EntryScene();
	~EntryScene() {};
	void Update(double DeltaTime)override;
	void Draw()override;
};

