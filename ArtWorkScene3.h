#pragma once
#include"SceneGraph.h"

template<class T>
class SingleSpriteRenderable;
class Container;
class Button;
class ButtonEventHandler;

class ArtWorkScene3 :public IScene
{
	ButtonEventHandler* _buttonEventHandle;
	class Container* _artWork3Container;
	struct ArtWork3Components
	{
		SingleSpriteRenderable<ArtWork3Components>* background;
		Button* prevButton;
		Button* nextButton;
	}_artWork3Comps;
public:
	ArtWorkScene3();
	~ArtWorkScene3() {};
	void Update(double deltaTime)override;
	void Draw()override;
	void InitScene()override;
	void EndScene()override;
};

