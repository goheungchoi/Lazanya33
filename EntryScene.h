#pragma once
#include "SceneGraph.h"
#include "Wall.h"

template<class T>
class SingleSpriteRenderable;
class Container;
class Button;



class EntryScene: public IScene
{
	class Container* _mainMenuContainer;
	struct MainMenuComponents
	{
		SingleSpriteRenderable<MainMenuComponents>* background;
		Container* lazanya;

	}_mainMenuComponents;

	Button* button;
public:
	EntryScene();
	~EntryScene() {};
	void Update(double deltaTime)override;
	void Draw()override;
	void InitScene()override;
	void EndScene()override;
	void GoToGameScene();
};

