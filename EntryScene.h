#pragma once
#include "SceneGraph.h"
#include "Wall.h"

template<class T>
class SingleSpriteRenderable;
class Container;
class Button;
class ButtonEventHandler;


class EntryScene: public IScene
{
	ButtonEventHandler* _buttonEventHandler;
	class Container* _mainMenuContainer;
	struct MainMenuComponents
	{
		SingleSpriteRenderable<MainMenuComponents>* background;
		Container* lazanya;
		Container* title;
		Container* highScore;
		Button* playbutton;
		Button* decoratorButton;
		Button* developerButton;
		Button* artWorkButton;

	}_mainComs;

public:
	EntryScene();
	~EntryScene() {};
	void Update(double deltaTime)override;
	void Draw()override;
	void InitScene()override;
	void EndScene()override;
};

