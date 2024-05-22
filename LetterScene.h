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
		Container* runningInFamily;
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
	std::wstring __WStringifyLetterText() {
		wchar_t buffer[256];

		swprintf_s(buffer, 
			L"자랑스러운 라자브 가문의 장녀,\n" L"라자냐 %d세여, "
			L"폭탄산 무크티니로 가거라.\n\n"

			L"누구보다 무크티니를 깊게 파\n"
			L"가문의 영광이 되거라.\n\n"

			L"학교를 안 가는걸 명예로 여겨온\n"
			L"라자브 가문의 후손답게 글을 모르겠지.\n"
			L"그림으로 설명하마."
			, GetGameDataHub().GetCurrentGeneration());
		return std::wstring(buffer);
	}
};

