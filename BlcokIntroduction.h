#pragma once
#include "SceneGraph.h"

template<class T>
class SingleSpriteRenderable;
class Container;
class Button;
class ButtonEventHandler;

class BlcokIntroduction : public IScene
{
	ButtonEventHandler* _buttonEventHandle;
	class Container* _blcokIntroContainer;
	struct BlcokIntroductionComponents
	{
		SingleSpriteRenderable<BlcokIntroductionComponents>* background;
		Button* entryButton;
	}_blockIntroComps;
public:
	BlcokIntroduction();
	~BlcokIntroduction() {};
	void Update(double deltaTime)override;
	void Draw()override;
	void InitScene()override;
	void EndScene()override;
};

