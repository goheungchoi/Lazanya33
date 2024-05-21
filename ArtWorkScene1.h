#pragma once
#include"SceneGraph.h"

template<class T>
class SingleSpriteRenderable;
class Container;
class Button;
class ButtonEventHandler;

class ArtWorkScene1:public IScene
{
	ButtonEventHandler* _buttonEventHandle;
	class Container* _artWork1Container;
	struct ArtWork1Components
	{
		SingleSpriteRenderable<ArtWork1Components>* background;
		Button* entryButton;
	}_artWork1Comps;
public:
	ArtWorkScene1();
	~ArtWorkScene1() {};
	void Update(double deltaTime)override;
	void Draw()override;
	void InitScene()override;
	void EndScene()override;
};

