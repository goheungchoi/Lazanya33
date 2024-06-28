#pragma once
#include "SceneGraph.h"

template<class T>
class SingleSpriteRenderable;
class Container;
class Button;
class ButtonEventHandler;

class DescriptionScene:public IScene
{
	ButtonEventHandler* _buttonEventHandle;
	class Container* _descriptionContainer;
	struct DescriptionComponents
	{
		SingleSpriteRenderable<DescriptionComponents>* background;
		Button* entryButton;
	}_descriptionComps;
public:
	DescriptionScene();
	~DescriptionScene(){};
	void Update(double deltaTime)override;
	void Draw()override;
	void InitScene()override;
	void EndScene()override;
};
//TODO :  png 넘어오는대로 entry에 버튼. description에 1920 1080 이미지 띄우기.
