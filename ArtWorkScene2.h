#pragma once
#include"SceneGraph.h"

template<class T>
class SingleSpriteRenderable;
class Container;
class Button;
class ButtonEventHandler;

class ArtWorkScene2 :public IScene
{
	ButtonEventHandler* _buttonEventHandle;
	class Container* _artWork2Container;
	struct ArtWork2Components
	{
		SingleSpriteRenderable<ArtWork2Components>* background;
		Button* prevButton;
		Button* nextButton;
	}_artWork2Comps;
public:
	ArtWorkScene2();
	~ArtWorkScene2() {};
	void Update(double deltaTime)override;
	void Draw()override;
	void InitScene()override;
	void EndScene()override;
};

