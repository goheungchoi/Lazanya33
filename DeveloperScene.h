#pragma once
#include "SceneGraph.h"

template<class T>
class SingleSpriteRenderable;
class Container;
class Button;
class ButtonEventHandler;

class DeveloperScene:public IScene
{
	ButtonEventHandler* _buttonEventHandle;
	class Container* _creditContainer;
	struct CreditComponents
	{
		SingleSpriteRenderable<CreditComponents>* background;
		Button* EntryButton;
	}_creditComs;
public:
	DeveloperScene();
	~DeveloperScene() {};
	void Update(double deltaTime)override;
	void Draw()override;
	void InitScene()override;
	void EndScene()override;
};

