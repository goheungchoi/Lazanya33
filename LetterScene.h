#pragma once
#include "SceneGraph.h"

template<class T>
class SingleSpriteRenderable;
class Container;
class BlessingContainer;
class BlessingsOfGodStateController;
class Button;
class ButtonEventHandler;

class LetterScene : public IScene
{
	// Button Handler
	ButtonEventHandler* _buttonEventHandler;
	Button* _playButton;

	// Letter Scene Components
	class Container* _letterContainer;
	struct LetterComponents {
		SingleSpriteRenderable<LetterComponents>* background;
		
		Container* _leftBox;
		Container* letter;
		Container* diagrams;

		Container* _rightBox;
		Container* text1;
		Container* blessingsOfGod;
		BlessingsOfGodStateController* blessingStateController;
		BlessingContainer* firstBlessingOfGod;
		BlessingContainer* secondBlessingOfGod;
		BlessingContainer* thirdBlessingOfGod;

	} _comps;
	bool isBlessingSelected = false;

public:
	LetterScene();
	~LetterScene();
	
	void Update(double deltaTime) override;
	void Draw() override;
	void InitScene() override;
	void EndScene() override;

private:
	void __InitComponents();
};

