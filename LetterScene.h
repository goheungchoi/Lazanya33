#pragma once
#include "SceneGraph.h"
class LetterScene:public IScene
{
public:
	void Update(double DeltaTime)override;
	void Draw()override;
};

