#pragma once
#include "SceneGraph.h"

template<class T>
class SingleSpriteRenderable;
class Container;
class Button;
class ButtonEventHandler;

class DecoratorScene:public IScene
{
	ButtonEventHandler* _buttonEventHandle;
	class Container* _decoratorContainer;
	struct DecoratorComponents
	{
		SingleSpriteRenderable<DecoratorComponents>* background;
		Button* entryButton;
		Container* decorator;
	}_decoratorComps;
public:
	DecoratorScene();
	~DecoratorScene() {};
	void Update(double deltaTime)override;
	void Draw()override;
	void InitScene()override;
	void EndScene()override;
};

