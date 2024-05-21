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

		Container* age;
		Container* ageChildTextIndex;
		Container* ageChildText;

		Button* playbutton;
		Button* decoratorButton;
		Button* developerButton;
		Button* artWorkButton;

	}_mainComs;
	int testIndex = 90;
public:
	EntryScene();
	~EntryScene() {};
	void Update(double deltaTime)override;
	void Draw()override;
	void InitScene()override;
	void EndScene()override;
	
	bool playBGM = false;
private:
	std::wstring _WStringAgeIndex(int age) {
		wchar_t buffer[30];
		swprintf_s(buffer, L"%2d", age);
		return std::wstring(buffer);
	}
};

